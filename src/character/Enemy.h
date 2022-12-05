#pragma once
#include "Unit.h"
#include <iostream>

class Enemy: public Unit
{
    public:

    int x,y,mvSpeed, goldValue, dmgValue, fighting;
    bool inCombat, deployed;

    Enemy():Unit()
    {
        x=0;
        y=rand()%3+24;
        maxHealth = rand()%201 + 100;
        health = maxHealth;
        strength = 2;
        mvSpeed=1;
        goldValue=10;
        dmgValue=1;
        inCombat = false;
        deployed = false;
        fighting = -1;
    }

    void levelUp(int lvlNr)
    {
        for(int i=0;i<lvlNr;i++)
        {
            level+=1;
            maxHealth *= 1.1;
            health = maxHealth;
            armor *=1.1;
            strength *= 1.1;
            goldValue *= 1.1;
            dexterity *= 1.1;
        }
    }

    void moveRight()
    {
        x += mvSpeed;
    }

    void deploy()
    {
        deployed = true;
    }

    void engage(int j)
    {
        fighting = j;
        inCombat = true;
    }

    void disengage()
    {
        fighting = -1;
        inCombat = false;
    }

    void instantiable(){}
};