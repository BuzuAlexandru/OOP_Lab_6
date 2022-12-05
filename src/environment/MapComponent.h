#pragma once
#include <iostream>
using namespace std;  
#include"../equipment/Equipment.h"
#include"../character/Archer.h"
#include"../character/Knight.h"
#include"../character/Enemy.h"
#include"../character/Player.h"
#include"../character/Worker.h"


class MapComponent
{
    public:

    int x, y, level, price;
    
    MapComponent()
    {
        x = 0;
        y = 0;
        level = 0;
        price = 10;
    }

    virtual void instantiable()=0;

};