#ifndef GAME_H
#define GAME_H

#include "Plant.h"
#include "Zombie.h"
#include "LDE.h"
using namespace std;

// Classe que gerencia o jogo e o tabuleiro (matriz)
class Game {
private:
    static const int ROWS = 5;
    static const int COLS = 9;

    Plant* board[ROWS][COLS]; // Matriz de ponteiros para plantas
    LDE<Zombie*> zombies;     // LDE para gerenciar os zumbis ativos

public:
    Game();
    ~Game();

    void placePlant(Plant* plant, int row, int col);
    void spawnZombie(Zombie* zombie);
    
    // Mostra o estado do tabuleiro
    void displayBoard();
    
    // Executa ação de todas as entidades
    void updateEntities();

    // Ordenar zumbis usando LDE
    void sortZombiesByHp();

    // Buscar zumbi por tipo no LDE
    Zombie* searchZombieByName(string name);
};

#endif
