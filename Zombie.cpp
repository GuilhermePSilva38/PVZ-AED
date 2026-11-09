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
    cout << "Basic Zombie em (" << x << "," << y << ") caminha faminto.\n";
}

ConeheadZombie::ConeheadZombie(int x, int y) 
    : Zombie("Conehead Zombie", 250, x, y, 10, 1) {}

void ConeheadZombie::action() {
    cout << "Conehead Zombie em (" << x << "," << y << ") avanca protegido por um cone.\n";
}

BucketheadZombie::BucketheadZombie(int x, int y) 
    : Zombie("Buckethead Zombie", 500, x, y, 15, 1) {}

void BucketheadZombie::action() {
    cout << "Buckethead Zombie em (" << x << "," << y << ") avanca com um BALDE DE FERRO!\n";
}

NewspaperZombie::NewspaperZombie(int x, int y) 
    : Zombie("Newspaper Zombie", 180, x, y, 20, 1) {}

void NewspaperZombie::action() {
    cout << "Newspaper Zombie em (" << x << "," << y << ") avanca furioso lendo jornal!\n";
}