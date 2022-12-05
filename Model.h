#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <unistd.h>
using namespace std;

#include"src/character/Enemy.h"
#include "src/environment/Tower.h"
#include "src/environment/Quarry.h"
#include "src/environment/Map.h"
#include "src/environment/Trap.h"
#include "src/environment/Barracks.h"

 class Model
 {
    public:


    int n, difficulty, levelLimit, towNr, brkNr;
    Enemy* enemy;
    Tower* archerTower;
    Barracks* barrack;
    Map map=Map();
    Player player=Player();
    Quarry quarry[3];
    Trap mine = Trap();

    void setData(int tow, int brk, int n1, int level, int diff)
    {
        towNr = tow; 
        brkNr = brk; 
        n = n1; 
        levelLimit = level;
        difficulty = diff; 
    }

    void endGame()
    {
        free(enemy);
        free(archerTower);
        free(barrack);
        exit(0);
    }

    void init()
    {
        srand(time(NULL));

        enemy = (Enemy*)malloc(n*sizeof(Enemy));

        archerTower = (Tower*)malloc(towNr*sizeof(Tower));

        barrack = (Barracks*)malloc(brkNr*sizeof(Barracks));

        for(int i=0;i<n;i++)
                enemy[i] = Enemy();

        int towSpacing = map.width/towNr;
        for(int i=0;i<towNr;i++)
        {
            int y;
            if(i%2==0) y=22; else y = 28;
            archerTower[i] = Tower(i*towSpacing,y);
        }

        towSpacing = map.width/brkNr;
        for(int i=0;i<brkNr;i++)
        {
            int y;
            if(i%2==0) y=22; else y = 28;
            barrack[i] = Barracks(i*towSpacing,y);
        }

        mine= Trap();

        for (int i=0;i<3;i++)
            quarry[i]=Quarry();
    }

    void runSim(int t)
    {
        int state = 1;
        while(t > 0)
        {
            t--;

            for(int i=0;i<n;i++)
            {
                if(enemy[i].deployed)
                    continue;
                else
                {
                    enemy[i].deploy();
                    enemy[i].levelUp(difficulty);
                    break;
                }
            }

            for(int i=0;i<towNr;i++)
                for(int k=0;k<3;k++)
                    archerTower[i].ranger[k].hasShot=false;

            int tdmg;

            for(int i=0;i<towNr;i++)
                for(int k=0;k<3;k++)
                    for(int j=0;j<n;j++)
                        if(enemy[j].isAlive() && archerTower[i].inRange(enemy[j],k))
                            {
                                tdmg = archerTower[i].ranger[k].hit();
                                enemy[j].takeDmg(tdmg); 
                                player.TdefenseDmg+=tdmg;
                                archerTower[i].ranger[k].hasShot=true;
                                archerTower[i].ranger[k].weapon.getDull();
                                if(archerTower[i].ranger[k].weapon.integrity<50)
                                    archerTower[i].ranger[k].weapon.repair();
                                if(enemy[j].health<=0)
                                {    
                                    for(int p=0;p<brkNr;p++)
                                        for(int l=0;l<3;l++)
                                            if
                                            (
                                                enemy[j].inCombat 
                                                && barrack[p].fighter[l].inCombat && 
                                                barrack[p].fighter[l].isAlive() && 
                                                not barrack[p].fighter[l].healing
                                            )
                                            if(barrack[p].fighter[l].fighting == j && l == enemy[j].fighting)
                                            {
                                                barrack[p].fighter[l].disengage();
                                            }
                                    player.coinGet(enemy[j].goldValue);
                                    player.totalGold+=enemy[j].goldValue;
                                    enemy[j] = Enemy();
                                    player.killCount += 1;
                                }
                            }    
                                
            for(int i=0;i<brkNr;i++)
                for(int j=0;j<n;j++)
                    if(enemy[j].isAlive() && barrack[i].inRange(enemy[j]) && not enemy[j].inCombat)
                    {
                        for(int k=0;k<3;k++)
                            if(not enemy[j].inCombat && barrack[i].fighter[k].isAlive() && not barrack[i].fighter[k].inCombat && not barrack[i].fighter[k].healing)
                            {
                                barrack[i].fighter[k].engage(j);
                                enemy[j].engage(k);
                                break;
                            }
                    }
            

            for(int i=0;i<brkNr;i++)
                for(int k=0;k<3;k++)
                    for(int j=0;j<n;j++)
                        if
                        (
                            enemy[j].isAlive() && enemy[j].inCombat 
                            && barrack[i].fighter[k].inCombat && 
                            barrack[i].fighter[k].isAlive() && 
                            not barrack[i].fighter[k].healing 
                        )
                        {
                            if(barrack[i].fighter[k].fighting == j && k == enemy[j].fighting)
                            {
                                tdmg = barrack[i].fighter[k].hit();
                                enemy[j].takeDmg(tdmg);
                                player.TdefenseDmg+=tdmg;
                                barrack[i].fighter[k].weapon.getDull();
                                if(barrack[i].fighter[k].weapon.integrity<50)
                                    barrack[i].fighter[k].weapon.repair();
                                barrack[i].fighter[k].takeDmg(enemy[j].hit());
                                player.TenemyDmg+=enemy[j].hit();
                                enemy[j].weapon.getDull();
                                if(enemy[j].weapon.integrity<50)
                                    enemy[j].weapon.repair();

                                if(enemy[j].health<=0)
                                {
                                    barrack[i].fighter[k].disengage();
                                    barrack[i].knightResetPos(k);
                                    player.killCount += 1;
                                    player.coinGet(enemy[j].goldValue);
                                    player.totalGold+=enemy[j].goldValue;
                                    enemy[j] = Enemy();
                                }
                                    
                                if(barrack[i].fighter[k].health<=0)
                                {
                                    barrack[i].fighter[k].kill();
                                    barrack[i].fighter[k].healing = true;
                                    enemy[j].disengage();
                                    barrack[i].fighter[k].disengage();
                                    barrack[i].knightResetPos(k);
                                    player.knightDefeatCount += 1;
                                }
                            }
                        }

            for(int i=0;i<brkNr;i++)
                for(int k=0;k<3;k++)
                {
                    if(barrack[i].fighter[k].healing)
                    {
                        barrack[i].fighter[k].getHeal(10);
                        if(barrack[i].fighter[k].health >= barrack[i].fighter[k].maxHealth)
                            {
                                barrack[i].fighter[k].health = barrack[i].fighter[k].maxHealth;
                                barrack[i].fighter[k].healing = false;
                            }
                    }
                }

            for(int i=0;i<n;i++)
            {
                if(enemy[i].deployed && enemy[i].isAlive() && not enemy[i].inCombat)
                {
                    enemy[i].moveRight();
                    if(enemy[i].x==map.width)
                    {
                        player.breachCount += 1;
                        enemy[i] = Enemy();
                    }
                }
            } 

            if (mine.cooldown<=0)
            {
                for(int j=0;j<n;j++)
                {
                    if(mine.inRange(enemy[j])||rand()%100<n)
                    {
                        enemy[j].takeDmg(mine.damage);
                        if(enemy[j].health<=0)
                                {    
                                    for(int p=0;p<brkNr;p++)
                                        for(int l=0;l<3;l++)
                                            if
                                            (
                                                enemy[j].inCombat 
                                                && barrack[p].fighter[l].inCombat && 
                                                barrack[p].fighter[l].isAlive() && 
                                                not barrack[p].fighter[l].healing
                                            )
                                            if(barrack[p].fighter[l].fighting == j && l == enemy[j].fighting)
                                            {
                                                barrack[p].fighter[l].disengage();
                                            }
                                    player.coinGet(enemy[j].goldValue);
                                    player.totalGold+=enemy[j].goldValue;
                                    enemy[j] = Enemy();
                                    player.killCount += 1;
                                }
                        player.TdefenseDmg+=mine.damage;
                        mine.cooldown=10;
                        player.trapTriggered+=1;
                        break;
                    }
                }
            }
            else
            {
                mine.cooldown-=1;
                if (mine.cooldown==0)
                {
                    mine.placeTrap(25,rand()%3+24);
                    player.spentGold+=mine.price;
                    player.coinSpend(mine.price);
                }
                    
            }
            

            for(int i=0;i<towNr;i++)
            {
                if(state==1&&archerTower[i].price<=player.coins&&archerTower[i].level<levelLimit)
                {
                    int p = archerTower[i].price;
                    player.coinSpend(p);
                    player.spentGold+=p;
                    archerTower[i].levelUp();
                    state=-1;
                    break;
                }
            } 

            for(int i=0;i<brkNr;i++)
            {
                if(state==-1&&barrack[i].price<=player.coins&&barrack[i].level<levelLimit)
                {
                    int p = barrack[i].price;
                    player.coinSpend(p);
                    player.spentGold+=p;
                    barrack[i].levelUp();
                    state=1;
                    break;
                }
            }
            player.avgTowLvl=0;
            player.avgBrkLvl=0;

            for(int i=0;i<towNr;i++)
            {
                player.avgTowLvl+=archerTower[i].level;
            }
            player.avgTowLvl/=towNr;

            for(int i=0;i<brkNr;i++)
            {
                player.avgBrkLvl+=barrack[i].level;
            }
            player.avgBrkLvl/=brkNr;

            for (int i=0;i<3;i++)
            {
                int money = quarry[i].generateGold();
                player.coinGet(money);
                player.totalGold+= money;
            }
        }
    }
};