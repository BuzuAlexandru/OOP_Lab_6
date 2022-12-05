#pragma once
#include <iostream>
using namespace std; 
#include "MapComponent.h"

class Tower: public MapComponent
{
    public:

    float range;
    Archer ranger[3];

    Tower(int x1, int y1):MapComponent()
    {
        x = x1;
        y = y1;
        range = 3;
        price = 100;
        for(int i=0;i<3;i++)
            ranger[i] = Archer();
    }

    void levelUp()
    {
        level += 1;
        range *= 1.1;
        int p = price * 1.1;
        price = (int)p;
        for(int i=0;i<3;i++)
            ranger[i].levelUp(1);
    }

    bool inRange(Enemy target, int i)
    {
        int r = range + ranger[i].weapon.range;
        int xt = target.x, yt = target.y;

        if(((abs(xt-x)<=r && abs(yt-y)<=r)) && ranger[i].hasShot==false)
            return true;
        else
            return false;
    }

    void instantiable(){}
};