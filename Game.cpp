#include "Game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Game::Game() : suns(100) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = nullptr;
        }
    }
    initAlmanaque();
    fillZombieWave(8);
    actionHistory.push("Jogo iniciado com 100 sois.");
}

Game::~Game() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != nullptr) delete board[i][j];
        }
    }
    zombies.clear();
}

void Game::initAlmanaque() {
    almanaque.insert("Sunflower", "Custo: $50 | HP: 100 | Gera +50 sois por turno.");
    almanaque.insert("Peashooter", "Custo: $100 | HP: 100 | Atira 1 ervilha (20 de dano).");
    almanaque.insert("Repeater", "Custo: $200 | HP: 100 | Atira 2 ervilhas (40 de dano).");
    almanaque.insert("Fire Peashooter", "Custo: $175 | HP: 100 | Atira ervilha de fogo (45 de dano).");
    almanaque.insert("Potato Mine", "Custo: $25 | HP: 50 | Explode causando 500 de dano ao contato.");
    almanaque.insert("Bonk Choy", "Custo: $150 | HP: 150 | Soca zumbis proximos (35 de dano).");
    almanaque.insert("WallNut", "Custo: $50 | HP: 400 | Barreira defensiva de alta resistencia.");
}

void Game::fillZombieWave(int count) {
    for (int i = 0; i < count; i++) {
        int linha = rand() % ROWS;
        int tipo = rand() % 4;
        if (tipo == 0) zombieWave.enqueue(new BasicZombie(linha, 8));
        else if (tipo == 1) zombieWave.enqueue(new ConeheadZombie(linha, 8));
        else if (tipo == 2) zombieWave.enqueue(new BucketheadZombie(linha, 8));
        else zombieWave.enqueue(new NewspaperZombie(linha, 8));
    }
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
                string msg = "Plantou " + plant->getName() + " em (" + to_string(row + 1) + "," + to_string(col + 1) + ")";
                actionHistory.push(msg);
                cout << msg << ".\n";
            } else {
                cout << "Sois insuficientes! Voce precisa de " << plant->getCost() << " sois.\n";
                delete plant;
            }
        } else {
            cout << "Posicao ja esta ocupada!\n";
            delete plant;
        }
    } else {
        cout << "Posicao invalida! Use linhas de 1 a 5 e colunas de 1 a 9.\n";
        delete plant;
    }
}

void Game::spawnNextZombieFromQueue() {
    if (zombieWave.isEmpty()) {
        fillZombieWave(5);
    }
    Zombie* nextZ = zombieWave.dequeue();
    if (nextZ) {
        zombies.insert(nextZ);
        string msg = nextZ->getName() + " saiu da Fila e entrou na Linha " + to_string(nextZ->getX() + 1);
        actionHistory.push(msg);
        cout << "ATENCAO: " << msg << "!\n";
    }
}

void Game::displayBoard(int turno) {
    string proxZumbi = zombieWave.isEmpty() ? "Nenhum" : zombieWave.front()->getName();
    string infoFila = "  |  HORDA (" + to_string(zombieWave.size()) + "): " + proxZumbi;
    while (infoFila.length() < 68) {
        infoFila += " ";
    }
    infoFila += "|";

    string menuLateral[7] = {
        "  |  PLANTAS: [1]Girassol $50   [2]Ervilha $100   [3]Repeater $200 |",
        "  |           [4]Fogo $175      [5]Mina $25       [6]Boxeador $150 |",
        "  |           [7]Nos $50        [8]Passar Turno                    |",
        "  |  AED:     [9]Buscar LDE    [10]BubbleSort    [11]InsertionSort |",
        "  |           [12]Pilha Log    [13]Hash Almanaque [14]Sair         |",
        infoFila,
        "  +----------------------------------------------------------------+"
    };

    cout << "================================================================================================================================\n";
    cout << "  PLANTS VS ZOMBIES 2 - AED C++   |   TURNO: " << turno << "   |   SOIS: $" << suns << "   |   ZUMBIS NO MAPA (LDE): " << zombies.getSize() << "\n";
    cout << "================================================================================================================================\n";
    cout << "     1     2     3     4     5     6     7     8     9   " << menuLateral[0] << "\n";

    for (int i = 0; i < ROWS; i++) {
        cout << "L" << i + 1 << " ";
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
        cout << menuLateral[i + 1] << "\n";
    }

    cout << "=========================================================" << menuLateral[6] << "\n";
    cout << "LEGENDA -> Plantas: [G]Girassol [E]Ervilha [R]Repeater [F]Fogo [M]Mina [B]Boxeador [N]Nos | Zumbis: [Z]Basico [C]Cone [K]Balde [J]Jornal\n";
    cout << "================================================================================================================================\n";
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

                if (p->getName() == "Repolho Boxeador") {
                    Node<Zombie*>* target = zombies.getHead();
                    while (target) {
                        if (target->data->getX() == i && (target->data->getY() == j || target->data->getY() == j + 1)) {
                            target->data->setHp(target->data->getHp() - 35);
                            cout << "   -> Repolho Boxeador socou " << target->data->getName() << "! HP restante: " << target->data->getHp() << "\n";
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
            string msg = z->getName() + " foi DERROTADO!";
            cout << msg << "\n";
            actionHistory.push(msg);
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
                actionHistory.push("Mina Batata explodiu " + z->getName());
                z->setHp(z->getHp() - 500);
                delete board[zX][zY];
                board[zX][zY] = nullptr;
            } else {
                p->setHp(p->getHp() - z->getDamage());
                cout << z->getName() << " esta mordendo a planta " << p->getName() << "! HP da planta: " << p->getHp() << "\n";

                if (p->getHp() <= 0) {
                    string msg = "Planta " + p->getName() + " destruida por " + z->getName();
                    cout << msg << "!\n";
                    actionHistory.push(msg);
                    delete board[zX][zY];
                    board[zX][zY] = nullptr;
                }
            }
        } else {
            z->setPosition(zX, zY - 1);
            cout << z->getName() << " avancou para a coluna " << z->getY() + 1 << ".\n";

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
    return z1->getHp() < z2->getHp();
}

void Game::sortZombiesBubble() {
    cout << "\n[BubbleSort] Ordenando zumbis por HP (Maior -> Menor)...\n";
    zombies.bubbleSort(compareZombieHp);
    
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        cout << "  Zumbi: " << current->data->getName() << " - HP: " << current->data->getHp() << "\n";
        current = current->next;
    }
}

void Game::sortZombiesInsertion() {
    cout << "\n[InsertionSort] Ordenando zumbis por HP (Maior -> Menor)...\n";
    zombies.insertionSort(compareZombieHp);
    
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        cout << "  Zumbi: " << current->data->getName() << " - HP: " << current->data->getHp() << "\n";
        current = current->next;
    }
}

Zombie* Game::searchZombieByName(string name) {
    Node<Zombie*>* current = zombies.getHead();
    while (current) {
        if (current->data->getName() == name) {
            cout << "Zumbi " << name << " encontrado na Linha " << current->data->getX() + 1 << ", Coluna " << current->data->getY() + 1 << "!\n";
            return current->data;
        }
        current = current->next;
    }
    cout << "Zumbi " << name << " nao encontrado na LDE.\n";
    return nullptr;
}

void Game::showHistory() {
    cout << "\n=== PILHA DE HISTORICO (Ultimas acoes - LIFO) ===\n";
    actionHistory.displayTop(6);
}

void Game::consultAlmanaque(string plantName) {
    cout << "\n=== TABELA HASH - ALMANAQUE ===\n";
    cout << plantName << " -> " << almanaque.search(plantName) << "\n";
}