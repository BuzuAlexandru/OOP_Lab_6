#pragma once
#include "Soldier.h"
#include <iostream>

class Knight: public Soldier
{
    public:

    int x,y, fighting;

    bool inCombat, healing;

    Knight():Soldier()
    {
        x = -1;
        y = -1;
        strength = 3;
        inCombat = false;
        healing = false;
        fighting = -1;
    }

    void engage(int j)
    {
        fighting = j;
        inCombat = true;
    }

    void disengage()
    {
        fighting = -1;
        inCombat = false;
    }

    void instantiable(){}
};