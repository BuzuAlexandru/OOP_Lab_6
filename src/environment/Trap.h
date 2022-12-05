#pragma once
#include <iostream>
using namespace std; 
#include "MapComponent.h"

class Trap: public MapComponent
{
    public:

    int damage, AOE, cooldown;

    Trap():MapComponent()
    {
        cooldown=0;
        damage = 100;
        AOE = 0;
    }

    void placeTrap(int posx, int posy)
    {
        x = posx;
        y = posy;
    }

    bool inRange(Enemy target)
    {
        if(target.x>=x-10 && target.x<=x+10 && target.y>=y-10 && target.y<=y+10)
            return true;
        else
            return false;
    }

    void instantiable(){}
};