#pragma once
#include "Character.h"
#include <iostream>

class Unit: public Character
{
    public:

    float armor, dexterity, strength;
    int level;
    Weapon weapon;

    Unit():Character()
    {
        level=0;
        armor=1;
        dexterity=75;
        strength=1;
        weapon = Weapon();
    }

    bool isAlive()
    {
        if(health>0)
            return true;
        else    
            return false;
    }

    void kill()
    {
        health = 0;
    }

    void takeDmg(int dmg)
    {
        health -= dmg-dmg*armor/50;
    }

    int hit()
    {
        if(rand()%100<(dexterity+weapon.accuracy)/2)
            return strength + weapon.power * weapon.integrity / 100;
        else
            return 0;
    }
};