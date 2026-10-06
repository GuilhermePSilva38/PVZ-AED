#include "Game.h"
#include <iostream>
#include <iomanip>
using namespace std;

Game::Game() {
    // Inicializa a matriz com nulo
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = nullptr;
        }
    }
}

Game::~Game() {
    // Libera memoria das plantas
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
    }
    // Libera memoria dos zumbis na LDE
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        delete current->data;
        current = current->next;
    }
}

void Game::placePlant(Plant* plant, int row, int col) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (board[row][col] == nullptr) {
            board[row][col] = plant;
            cout << "Planta " << plant->getName() << " colocada em (" << row << "," << col << ").\n";
        } else {
            cout << "Posicao ocupada!\n";
            delete plant;
        }
    }
}

void Game::spawnZombie(Zombie* zombie) {
    zombies.insert(zombie);
    cout << "Zumbi " << zombie->getName() << " spawnou na linha " << zombie->getX() << ".\n";
}

void Game::displayBoard() {
    cout << "\n=== Tabuleiro ===\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != nullptr) {
                cout << "[P" << board[i][j]->getHp() << "] ";
            } else {
                cout << "[   ] ";
            }
        }
        cout << "\n";
    }
    cout << "=================\n";
}

void Game::updateEntities() {
    cout << "\n--- Turno --- \n";
    // Atualiza Plantas
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != nullptr) {
                board[i][j]->action();
            }
        }
    }

    // Atualiza Zumbis
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        current->data->action();
        current = current->next;
    }
    cout << "-------------\n";
}

// Funcao de comparacao para ordenacao (crescente por HP)
bool compareZombieHp(Zombie* z1, Zombie* z2) {
    return z1->getHp() > z2->getHp();
}

void Game::sortZombiesByHp() {
    cout << "Ordenando zumbis por HP...\n";
    zombies.sort(compareZombieHp);
    
    // Mostra ordem
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        cout << "Zumbi: " << current->data->getName() << " - HP: " << current->data->getHp() << "\n";
        current = current->next;
    }
}

Zombie* Game::searchZombieByName(string name) {
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        if (current->data->getName() == name) {
            cout << "Zumbi " << name << " encontrado!\n";
            return current->data;
        }
        current = current->next;
    }
    cout << "Zumbi " << name << " nao encontrado.\n";
    return nullptr;
}
//testa esse ai gui