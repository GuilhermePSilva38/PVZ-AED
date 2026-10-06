#include <iostream>
#include "Game.h"
#include "Plant.h"
#include "Zombie.h"
using namespace std;

int main() {
    cout << "=== Plants vs Zombies - Previa ===\n";

    Game pvz;

    // Colocando plantas no tabuleiro (Matriz)
    pvz.placePlant(new Sunflower(0, 0), 0, 0);
    pvz.placePlant(new Peashooter(0, 1), 0, 1);
    pvz.placePlant(new Peashooter(2, 2), 2, 2);
    pvz.placePlant(new BonkChoy(1, 0), 1, 0);
    pvz.placePlant(new WallNut(1, 1), 1, 1);
    pvz.placePlant(new IcebergLettuce(2, 0), 2, 0);
    pvz.placePlant(new TangledKelp(3, 0), 3, 0);

    // Mostra a Matriz
    pvz.displayBoard();

    // Spawnando Zumbis (Adicionados na LDE)
    pvz.spawnZombie(new BasicZombie(0, 8));
    pvz.spawnZombie(new ConeheadZombie(2, 8));
    pvz.spawnZombie(new BasicZombie(4, 8));

    // Executa ações (Polimorfismo)
    pvz.updateEntities();

    // Ordenação (LDE)
    pvz.sortZombiesByHp();

    // Busca
    cout << "\nRealizando busca por 'Conehead Zombie':\n";
    pvz.searchZombieByName("Conehead Zombie");

    cout << "\nRealizando busca por 'Buckethead Zombie':\n";
    pvz.searchZombieByName("Buckethead Zombie");

    return 0;
}