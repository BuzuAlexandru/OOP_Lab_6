#pragma once
#include "Character.h"
#include <iostream>

class Worker: public Character
{
    public:

    float efficiency;
    Tool pickaxe;

    Worker():Character()
    {
        efficiency = 0.5;
        pickaxe = Tool();
    }

    void getHeal(int heal)
    {
        health += heal;
    }

    void instantiable(){}
};