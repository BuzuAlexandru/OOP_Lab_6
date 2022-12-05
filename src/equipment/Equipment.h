#pragma once
#include <iostream>
using namespace std; 

class Equipment
{
    public:

    float integrity;

    Equipment()
    {
        integrity = 100;
    }

    void getDull()
    {
        integrity -= 0.5;
    }

    void repair()
    {
        integrity = 100;
    }

    virtual void instantiable() = 0;
};