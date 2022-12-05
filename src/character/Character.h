#pragma once
#include "../equipment/Tool.h"
#include "../equipment/Weapon.h"
#include <iostream>
using namespace std; 

class Character
{
    public:

    float maxHealth,health;

    Character()
    {
        maxHealth = 100;
        health = maxHealth;
    }

    void takeDmg(int dmg)
    {
        health -= dmg;
    }

    virtual void instantiable()=0;
};

