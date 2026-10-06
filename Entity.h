#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

// TAD Entity (Classe Base)
class Entity {
protected:
    string name;
    int hp; // Health Points
    int x;  // Posição no grid X
    int y;  // Posição no grid Y

public:
    Entity(string name, int hp, int x, int y);
    virtual ~Entity() {}

    // Getters
    string getName() const;
    int getHp() const;
    int getX() const;
    int getY() const;

    // Setters
    void setHp(int hp);
    void setPosition(int x, int y);

    // Metodo Virtual Puro
    virtual void action() = 0; 
};

#endif
