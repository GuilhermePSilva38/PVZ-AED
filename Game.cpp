#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : suns(100) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = nullptr;
        }
    }
}

Game::~Game() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != nullptr) delete board[i][j];
        }
    }
    zombies.clear();
}

int Game::getSuns() const { return suns; }
void Game::addSuns(int amount) { suns += amount; }

bool Game::spendSuns(int amount) {
    if (suns >= amount) {
        suns -= amount;
        return true;
    }
    return false;
}

void Game::placePlant(Plant* plant, int row, int col) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (board[row][col] == nullptr) {
            if (spendSuns(plant->getCost())) {
                board[row][col] = plant;
                cout << "Planta " << plant->getName() << " colocada em (" << row << "," << col << ").\n";
            } else {
                cout << "Sois insuficientes! Voce precisa de " << plant->getCost() << " sois.\n";
                delete plant;
            }
        } else {
            cout << "Posicao ja esta ocupada!\n";
            delete plant;
        }
    }
}

void Game::spawnZombie(Zombie* zombie) {
    zombies.insert(zombie);
    cout << "ATENCAO: " << zombie->getName() << " apareceu na linha " << zombie->getX() << "!\n";
}

void Game::displayBoard() {
    cout << "\n============================== TABULEIRO (SOIS: " << suns << ") ==============================\n";
    cout << "     0     1     2     3     4     5     6     7     8  (Colunas)\n";
    for (int i = 0; i < ROWS; i++) {
        cout << "L" << i << " ";
        for (int j = 0; j < COLS; j++) {
            Plant* p = board[i][j];
            Zombie* z = nullptr;

            Node<Zombie*>* currZ = zombies.getHead();
            while (currZ) {
                if (currZ->data->getX() == i && currZ->data->getY() == j) {
                    z = currZ->data;
                    break;
                }
                currZ = currZ->next;
            }

            if (p != nullptr && z != nullptr) {
                cout << "[P/Z] ";
            } else if (p != nullptr) {
                string nome = p->getName();
                char sigla = 'P';

                if (nome == "Sunflower") sigla = 'G';
                else if (nome == "Peashooter") sigla = 'E';
                else if (nome == "Repolho Boxeador") sigla = 'B';
                else if (nome == "Alfaceberg") sigla = 'A';
                else if (nome == "Erva Trepadeira") sigla = 'T';
                else if (nome == "Nos") sigla = 'N';
                else if (nome == "Repeater") sigla = 'R';
                else if (nome == "Fire Peashooter") sigla = 'F';
                else if (nome == "Potato Mine") sigla = 'M';

                cout << "[ " << sigla << " ] ";
            } else if (z != nullptr) {
                string nomeZ = z->getName();
                char siglaZ = 'Z';

                if (nomeZ == "Conehead Zombie") siglaZ = 'C';
                else if (nomeZ == "Buckethead Zombie") siglaZ = 'K';
                else if (nomeZ == "Newspaper Zombie") siglaZ = 'J';
                else if (nomeZ == "Basic Zombie") siglaZ = 'Z';

                cout << "[ " << siglaZ << " ] ";
            } else {
                cout << "[   ] ";
            }
        }
        cout << "\n";
    }
    cout << "=================================================================================\n";
    cout << "Plantas: [G] Girassol | [E] Ervilha | [R] Repetidora | [F] Fogo | [M] Mina Batata\n";
    cout << "Zumbis:  [Z] Basico   | [C] Conehead| [K] Balde de Ferro | [J] Jornal\n";
    cout << "=================================================================================\n";
}

bool Game::updateEntities() {
    cout << "\n--- EXECUTANDO ACOES DO TURNO --- \n";

    addSuns(25);
    cout << "+25 sois cairam do ceu!\n";

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != nullptr) {
                Plant* p = board[i][j];
                p->action();
                
                if (p->getName() == "Sunflower") {
                    addSuns(50);
                    cout << "   -> +50 sois gerados pela Sunflower!\n";
                }

                if (p->getName() == "Peashooter") {
                    Node<Zombie*>* target = zombies.getHead();
                    while (target) {
                        if (target->data->getX() == i && target->data->getY() >= j) {
                            target->data->setHp(target->data->getHp() - 20);
                            cout << "   -> Ervilha atingiu " << target->data->getName() << "! HP restante: " << target->data->getHp() << "\n";
                            break;
                        }
                        target = target->next;
                    }
                }

                if (p->getName() == "Repeater") {
                    Node<Zombie*>* target = zombies.getHead();
                    while (target) {
                        if (target->data->getX() == i && target->data->getY() >= j) {
                            target->data->setHp(target->data->getHp() - 40);
                            cout << "   -> DUAS ervilhas do Repeater atingiram " << target->data->getName() << "! HP restante: " << target->data->getHp() << "\n";
                            break;
                        }
                        target = target->next;
                    }
                }

                if (p->getName() == "Fire Peashooter") {
                    Node<Zombie*>* target = zombies.getHead();
                    while (target) {
                        if (target->data->getX() == i && target->data->getY() >= j) {
                            target->data->setHp(target->data->getHp() - 45);
                            cout << "   -> Ervilha de FOGO queimou " << target->data->getName() << "! HP restante: " << target->data->getHp() << "\n";
                            break;
                        }
                        target = target->next;
                    }
                }
            }
        }
    }

    Node<Zombie*>* currZ = zombies.getHead();
    while (currZ) {
        Node<Zombie*>* nextZ = currZ->next;
        Zombie* z = currZ->data;

        if (z->getHp() <= 0) {
            cout << "Zumbi " << z->getName() << " foi DERROTADO!\n";
            zombies.removeNode(currZ);
            currZ = nextZ;
            continue;
        }

        int zX = z->getX();
        int zY = z->getY();

        if (board[zX][zY] != nullptr) {
            Plant* p = board[zX][zY];

            if (p->getName() == "Potato Mine") {
                cout << "\n*** BOOM! A Mina Batata EXPLODIU no " << z->getName() << "! ***\n";
                z->setHp(z->getHp() - 500);
                delete board[zX][zY];
                board[zX][zY] = nullptr;
            } else {
                p->setHp(p->getHp() - z->getDamage());
                cout << z->getName() << " esta mordendo a planta " << p->getName() << "! HP da planta: " << p->getHp() << "\n";

                if (p->getHp() <= 0) {
                    cout << "Planta " << p->getName() << " foi DESTRUIDA pelo zumbi!\n";
                    delete board[zX][zY];
                    board[zX][zY] = nullptr;
                }
            }
        } else {
            z->setPosition(zX, zY - 1);
            cout << z->getName() << " avancou para a coluna " << z->getY() << ".\n";

            if (z->getY() < 0) {
                cout << "\n!!! O ZUMBI ENTROU NA SUA CASA !!! GAME OVER !!!\n";
                return false; 
            }
        }
        currZ = nextZ;
    }
    return true;
}

bool compareZombieHp(Zombie* z1, Zombie* z2) {
    return z1->getHp() > z2->getHp();
}

void Game::sortZombiesByHp() {
    cout << "Ordenando zumbis por HP...\n";
    zombies.sort(compareZombieHp);
    
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
            cout << "Zumbi " << name << " encontrado no mapa!\n";
            return current->data;
        }
        current = current->next;
    }
    cout << "Zumbi " << name << " nao encontrado.\n";
    return nullptr;
}