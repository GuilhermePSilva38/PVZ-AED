#include "Plant.h"
using namespace std;

Plant::Plant(string name, int hp, int x, int y, int cost)
    : Entity(name, hp, x, y), cost(cost){}

int Plant::getCost() const { return cost; }

void Plant::action(){
    cout << name << " faz alguma acao base.\n";
}

// --- Implementação das Plantas Base ---

Peashooter::Peashooter(int x, int y) 
    : Plant("Peashooter", 100, x, y, 100){}

void Peashooter::action(){
    cout << "Peashooter em (" << x << "," << y << ") atira uma ervilha!\n";
}

Sunflower::Sunflower(int x, int y) 
    : Plant("Sunflower", 100, x, y, 50){}

void Sunflower::action(){
    cout << "Sunflower em (" << x << "," << y << ") produz sol!\n";
}

BonkChoy::BonkChoy(int x, int y) 
    : Plant("Repolho Boxeador", 150, x, y, 150){}

void BonkChoy::action(){
    cout << "Repolho Boxeador em (" << x << "," << y << ") da uma sequencia de socos no zumbi proximo!\n";
}

IcebergLettuce::IcebergLettuce(int x, int y) 
    : Plant("Alfaceberg", 50, x, y, 0){}

void IcebergLettuce::action(){
    cout << "Alfaceberg em (" << x << "," << y << ") congela e paralisa o primeiro zumbi que pisar nela!\n";
}

TangledKelp::TangledKelp(int x, int y) 
    : Plant("Erva Trepadeira", 75, x, y, 25){}

void TangledKelp::action(){
    cout << "Erva Trepadeira em (" << x << "," << y << ") enrola e puxa o zumbi para baixo!\n";
}

// Nós (Wall-nut): Custo 50, alto HP (400) para funcionar como escudo
WallNut::WallNut(int x, int y) 
    : Plant("Nos", 400, x, y, 50){}

void WallNut::action(){
    cout << "Nos em (" << x << "," << y << ") esta a bloquear o caminho dos zumbis com o seu alto HP!\n";
}