#pragma once
#include <iostream>
using namespace std; 
#include "Equipment.h"

class Weapon: public Equipment
{
    public:

    int power, range, accuracy;

    Weapon():Equipment()
    {
        power=1;
        range=0;
        accuracy=75;
    }

    void instantiable(){}
};