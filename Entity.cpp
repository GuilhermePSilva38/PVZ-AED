#include "Entity.h"
using namespace std;

Entity::Entity(string name, int hp, int x, int y) 
    : name(name), hp(hp), x(x), y(y) {}

string Entity::getName() const { return name; }
int Entity::getHp() const { return hp; }
int Entity::getX() const { return x; }
int Entity::getY() const { return y; }

void Entity::setHp(int hp) { this->hp = hp; }
void Entity::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
