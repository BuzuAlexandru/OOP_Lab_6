#pragma once
#include <iostream>
#include "Character.h"

class Player: public Character
{
    public:

    int coins, killCount, breachCount, knightDefeatCount, totalGold, spentGold, avgTowLvl, avgBrkLvl, trapTriggered;
    float TdefenseDmg, TenemyDmg;

    Player():Character()
    {
        killCount = 0;
        breachCount = 0;
        knightDefeatCount = 0; 
        TdefenseDmg = 0;
        TenemyDmg = 0;
        totalGold = 0;
        spentGold = 0;
        avgTowLvl = 0;
        avgBrkLvl = 0;
        trapTriggered = 0;

        maxHealth = 0;
        health = maxHealth;
        coins = 100;
    }

    void coinSpend(int cost)
    {
        coins -= cost;
    }

    void coinGet(int gold)
    {
        coins += gold;
    }

    void instantiable(){}
};