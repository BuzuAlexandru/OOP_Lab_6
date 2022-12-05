#pragma once
#include <iostream>
using namespace std; 
#include "Equipment.h"

class Tool: public Equipment
{
    public:

    float efficiency;
    Tool():Equipment()
    {
        efficiency=0.5;
    }

    void instantiable(){}
};