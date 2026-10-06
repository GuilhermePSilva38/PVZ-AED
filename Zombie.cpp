#include "Zombie.h"
using namespace std;

Zombie::Zombie(string name, int hp, int x, int y, int damage, int speed)
    : Entity(name, hp, x, y), damage(damage), speed(speed) {}

int Zombie::getDamage() const { return damage; }

void Zombie::action() {
    cout << name << " anda e ataca.\n";
}

BasicZombie::BasicZombie(int x, int y) 
    : Zombie("Basic Zombie", 100, x, y, 10, 1) {}

void BasicZombie::action() {
    cout << "Basic Zombie em (" << x << "," << y << ") tenta morder as plantas!\n";
}

ConeheadZombie::ConeheadZombie(int x, int y) 
    : Zombie("Conehead Zombie", 250, x, y, 10, 1) {}

void ConeheadZombie::action() {
    cout << "Conehead Zombie em (" << x << "," << y << ") caminha com um cone na cabeca.\n";
}
