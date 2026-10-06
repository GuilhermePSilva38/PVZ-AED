#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"
#include <iostream>
using namespace std;

class Zombie : public Entity {
protected:
    int damage;
    int speed;
public:
    Zombie(string name, int hp, int x, int y, int damage, int speed);
    int getDamage() const;
    void action() override;
};

// Tipos de Zumbi
class BasicZombie : public Zombie {
public:
    BasicZombie(int x, int y);
    void action() override;
};

class ConeheadZombie : public Zombie {
public:
    ConeheadZombie(int x, int y);
    void action() override;
};

#endif
