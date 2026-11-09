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
    virtual ~Zombie() {}

    int getDamage() const;
    void action() override;
};

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

class BucketheadZombie : public Zombie {
public:
    BucketheadZombie(int x, int y);
    void action() override;
};

class NewspaperZombie : public Zombie {
public:
    NewspaperZombie(int x, int y);
    void action() override;
};

#endif