#include "Plant.h"
#include <iostream>
using namespace std;

Plant::Plant(string name, int hp, int x, int y, int cost)
    : Entity(name, hp, x, y), cost(cost) {}

int Plant::getCost() const { return cost; }

void Plant::action() {
    cout << name << " faz uma acao base.\n";
}

Peashooter::Peashooter(int x, int y) 
    : Plant("Peashooter", 100, x, y, 100) {}

void Peashooter::action() {
    cout << "Peashooter em (" << x << "," << y << ") atira uma ervilha!\n";
}

Sunflower::Sunflower(int x, int y) 
    : Plant("Sunflower", 100, x, y, 50) {}

void Sunflower::action() {
    cout << "Sunflower em (" << x << "," << y << ") produz sois!\n";
}

BonkChoy::BonkChoy(int x, int y) 
    : Plant("Repolho Boxeador", 150, x, y, 150) {}

void BonkChoy::action() {
    cout << "Repolho Boxeador em (" << x << "," << y << ") da socos em sequencia!\n";
}

IcebergLettuce::IcebergLettuce(int x, int y) 
    : Plant("Alfaceberg", 50, x, y, 0) {}

void IcebergLettuce::action() {
    cout << "Alfaceberg em (" << x << "," << y << ") paralisa o zumbi!\n";
}

TangledKelp::TangledKelp(int x, int y) 
    : Plant("Erva Trepadeira", 75, x, y, 25) {}

void TangledKelp::action() {
    cout << "Erva Trepadeira em (" << x << "," << y << ") puxa o zumbi!\n";
}

WallNut::WallNut(int x, int y) 
    : Plant("Nos", 400, x, y, 50) {}

void WallNut::action() {
    cout << "Nos em (" << x << "," << y << ") bloqueia o caminho com seu alto HP!\n";
}

Repeater::Repeater(int x, int y) 
    : Plant("Repeater", 100, x, y, 200) {}

void Repeater::action() {
    cout << "Repeater em (" << x << "," << y << ") dispara DUAS ervilhas seguidas!\n";
}

FirePeashooter::FirePeashooter(int x, int y) 
    : Plant("Fire Peashooter", 100, x, y, 175) {}

void FirePeashooter::action() {
    cout << "Fire Peashooter em (" << x << "," << y << ") lanca uma ervilha FLAMANTE de alto dano!\n";
}

PotatoMine::PotatoMine(int x, int y) 
    : Plant("Potato Mine", 50, x, y, 25) {}

void PotatoMine::action() {
    cout << "Potato Mine em (" << x << "," << y << ") esta armada no chao aguardando zumbis!\n";
}