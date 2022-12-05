#pragma once
#include <iostream>
using namespace std; 
#include "MapComponent.h"

class Quarry: public MapComponent
{
    public:

    int oreQuality;
    float accidentChance;
    Worker miner[3];

    Quarry():MapComponent()
    {
        oreQuality=1;
        for(int i; i<3;i++)
        {
            miner[i] = Worker();
        }
    }

    int generateGold()
    {
        int sum=0;
        for(int i = 0; i<3;i++)
        {
            sum += (int)(oreQuality + oreQuality*(miner[i].efficiency + miner[i].pickaxe.efficiency)); 
        }

        return sum;
    }

    void instantiable(){}
};