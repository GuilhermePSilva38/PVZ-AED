#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"
#include <iostream>
using namespace std;

// Classe Base Plant
class Plant : public Entity{
protected:
    int cost;
public:
    Plant(string name, int hp, int x, int y, int cost);
    int getCost() const;
    void action() override;
};

// --- Tipos de Plantas Existentes ---

class Peashooter : public Plant{
public:
    Peashooter(int x, int y);
    void action() override;
};

class Sunflower : public Plant{
public:
    Sunflower(int x, int y);
    void action() override;
};

class BonkChoy : public Plant{
public:
    BonkChoy(int x, int y);
    void action() override;
};

class IcebergLettuce : public Plant{
public:
    IcebergLettuce(int x, int y);
    void action() override;
};

class TangledKelp : public Plant{
public:
    TangledKelp(int x, int y);
    void action() override;
};

class WallNut : public Plant{
public:
    WallNut(int x, int y);
    void action() override;
};

#endif