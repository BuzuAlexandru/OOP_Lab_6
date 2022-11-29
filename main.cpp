#include<iostream>
#include<cstdlib>
#include<ctime>
#include <unistd.h>
using namespace std;

#include"src/equipment.h"
#include"src/character.h"
#include"src/environment.h"

Map map=Map();

Player player=Player();
int n = 10, difficulty = 20, levelLimit = 100;
Enemy* enemy;
int towNr = 5;
Tower* archerTower;
int brkNr = 5;
Barracks* barrack;
Quarry quarry[3];
Trap mine = Trap();


void endGame()
{
    free(enemy);
    free(archerTower);
    free(barrack);
    for(int i=0;i<map.height;i++)
        free(map.tile[i]);
    free(map.tile);
    exit(0);
}

void turn(int t)
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



int main()
{
    system("clear");

    srand(time(NULL));

    cout<<"Nr of archer towers(50 max): ";
    cin>>towNr;
    if(towNr>50) towNr=50;
    cout<<"\nNr of barracks(50 max): ";
    cin>>brkNr;
    if(brkNr>50) brkNr=50;
    cout<<"\nNr of enemies allowed(50 max): ";
    cin>>n;
    if(n>50) n=50;
    cout<<"\nLevel limit of the towers: ";
    cin>>levelLimit;
    cout<<"\nEnemy level: ";
    cin>>difficulty;
    
    map.tile=(int**)malloc(map.height*sizeof(int*));
    for(int i=0;i<map.height;i++)
        map.tile[i]=(int*)malloc(map.width*sizeof(int));

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
    
    for(int i=0;i<100;i++)
    {
        turn(50);
        system("clear");
        cout<<"Nr of archer towers: "<<towNr;
        cout<<"\nNr of barracks: "<<brkNr;
        cout<<"\nAmount of enemies: "<<n;
        cout<<"\nLevel limit of the towers: "<<levelLimit;
        cout<<"\nEnemy level: "<<difficulty;

        cout<<"\n\nNr of turns: "<<(i+1)*50<<endl;
        cout<<"Nr of defeated enemies: "<<player.killCount<<endl;
        cout<<"Nr of times knights where defeated: "<<player.knightDefeatCount<<endl;
        cout<<"Nr of escaped enemies: "<<player.breachCount<<endl;
        cout<<"Total dmg dealt by the enemies : "<<player.TenemyDmg<<endl;
        cout<<"Total dmg dealt by the defense : "<<player.TdefenseDmg<<endl;
        cout<<"Total nr of earned coins: "<<player.totalGold<<endl;
        cout<<"Total nr of spent coins: "<<player.spentGold<<endl;
        cout<<"Average level of archer towers : "<<player.avgTowLvl<<endl;
        cout<<"Average level of barracks : "<<player.avgBrkLvl<<endl;
        //cout<<"Nr of times traps were triggered: "<<player.trapTriggered<<endl;
        usleep(250000);
    }
    endGame();

    return 0;
}