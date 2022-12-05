#pragma once
#include "Unit.h"
#include <iostream>

class Soldier: public Unit
{
    public:

    Soldier():Unit()
    {}

    void levelUp(int lvlNr)
    {
        for(int i=0;i<lvlNr;i++)
        {
            level+=1;
            maxHealth *= 1.1;
            health = maxHealth;
            armor *=1.1;
            strength *= 1.1;
            dexterity *= 1.1;
        }
    }

    void getHeal(int heal)
    {
        health += heal;
    }
};
