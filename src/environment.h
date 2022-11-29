#pragma once
#include "entity.h"
#include "character.h"
#include <iostream>
using namespace std; 

class Environment: public Entity
{
    public:
    Environment():Entity()
    {}
};

class Map: public Environment
{
    public:

    int width, height, **tile;

    Map():Environment()
    {
        width=50;
        height=50;
    }

    int getID()
    {
        return id;
    }
};

class MapComponent: public Environment
{
    public:

    int x, y, level, price;
    
    MapComponent():Environment()
    {
        x = 0;
        y = 0;
        level = 0;
        price = 10;
    }

    void levelUp()
    {}
};

class Trap: public MapComponent
{
    public:

    int damage, AOE, cooldown;

    Trap():MapComponent()
    {
        cooldown=0;
        damage = 100;
        AOE = 0;
    }

    void placeTrap(int posx, int posy)
    {
        x = posx;
        y = posy;
    }

    int getID()
    {
        return id;
    }

    bool inRange(Enemy target)
    {
        if(target.x>=x-10 && target.x<=x+10 && target.y>=y-10 && target.y<=y+10)
            return true;
        else
            return false;
    }
};

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

    int getID()
    {
        return id;
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
};

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

    int getID()
    {
        return id;
    }

    bool inRange(Enemy target)
    {
        int xt = target.x, yt = target.y;

        if((abs(xt-x)<=range && abs(yt-y)<=range))
            return true;
        else
            return false;
    }
};

class Quarry: public MapComponent
{
    public:

    int oreQuality;
    float accidentChance;
    Worker miner[3];

    Quarry():MapComponent()
    {
        oreQuality=1;
        accidentChance = 0.5;
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

    int getID()
    {
        return id;
    }
};