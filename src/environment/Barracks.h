#pragma once
#include <iostream>
using namespace std; 
#include "MapComponent.h"

class Barracks: public MapComponent
{
    public:

    int range;
    Knight fighter[3];

    Barracks(int x1, int y1):MapComponent()
    {
        x = x1;
        y = y1;
        price = 100;
        range = 5;
        for(int i=0;i<3;i++)
        {   
            fighter[i] = Knight();
            fighter[i].x = x;
            fighter[i].y = y;
        }
    }

    void levelUp()
    {
        level += 1;
        range *= 1.1;
        range *= 1.1;
        int p = price * 1.1;
        for(int i=0;i<3;i++)
            fighter[i].levelUp(1);
    }

    void knightResetPos(int i)
    {
        fighter[i].x = x;
        fighter[i].y = y;
    }

    bool inRange(Enemy target)
    {
        int xt = target.x, yt = target.y;

        if((abs(xt-x)<=range && abs(yt-y)<=range))
            return true;
        else
            return false;
    }

    void instantiable(){}
};