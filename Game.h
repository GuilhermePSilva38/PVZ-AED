#ifndef GAME_H
#define GAME_H

#include "Plant.h"
#include "Zombie.h"
#include "LDE.h"
#include <string>
using namespace std;

class Game {
    static const int ROWS = 5;
    static const int COLS = 9;

    Plant* board[ROWS][COLS];
    LDE<Zombie*> zombies;
    int suns;

public:
    Game();
    ~Game();

    int getSuns() const;
    void addSuns(int amount);
    bool spendSuns(int amount);

    void placePlant(Plant* plant, int row, int col);
    void spawnZombie(Zombie* zombie);
    
    void displayBoard();
    bool updateEntities();

    void sortZombiesByHp();
    Zombie* searchZombieByName(string name);
};

#endif