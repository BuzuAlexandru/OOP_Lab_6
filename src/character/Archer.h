#pragma once
#include "Soldier.h"
#include <iostream>

class Archer: public Soldier
{
    public:

    bool hasShot;

    Archer():Soldier()
    {
        weapon.range = 3;
        hasShot = false;
    }

    void instantiable(){}
};
