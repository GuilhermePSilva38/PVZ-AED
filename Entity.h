#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
protected:
    string name;
    int hp;
    int x;
    int y;

public:
    Entity(string name, int hp, int x, int y);
    virtual ~Entity() {}

    string getName() const;
    int getHp() const;
    int getX() const;
    int getY() const;

    void setHp(int hp);
    void setPosition(int x, int y);

    virtual void action() = 0;
};

#endif