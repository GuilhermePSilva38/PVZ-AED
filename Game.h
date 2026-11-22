#ifndef GAME_H
#define GAME_H

#include "Plant.h"
#include "Zombie.h"
#include "LDE.h"
#include "EstruturasAED.h"
#include <string>
using namespace std;

class Game {
    static const int ROWS = 5;
    static const int COLS = 9;

    Plant* board[ROWS][COLS];
    LDE<Zombie*> zombies;
    Fila<Zombie*> zombieWave;
    Pilha<string> actionHistory;
    TabelaHash almanaque;
    int suns;

    void initAlmanaque();
    void fillZombieWave(int count);

public:
    Game();
    ~Game();

    int getSuns() const;
    void addSuns(int amount);
    bool spendSuns(int amount);

    void placePlant(Plant* plant, int row, int col);
    void spawnNextZombieFromQueue();
    
    void displayBoard(int turno);
    bool updateEntities();

    void sortZombiesBubble();
    void sortZombiesInsertion();
    Zombie* searchZombieByName(string name);
    void showHistory();
    void consultAlmanaque(string plantName);
};

#endif