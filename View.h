#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <unistd.h>
#include <tuple>
using namespace std;

class View
{
    public:

    tuple<int, int, int, int, int> getInput()
    {
        int towNr, brkNr, n, levelLimit, difficulty;

        system("clear");

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

        return {towNr, brkNr, n, levelLimit, difficulty};
    }

    void renderResult(int towNr, int brkNr, int n, int levelLimit, int difficulty, 
                        int killCount, int knightDefeatCount, int breachCount, 
                        float TenemyDmg, float TdefenseDmg, int totalGold, 
                        int spentGold, int avgTowLvl, int avgBrkLvl)
    {
        system("clear");
        cout<<"Nr of archer towers: "<<towNr;
        cout<<"\nNr of barracks: "<<brkNr;
        cout<<"\nAmount of enemies: "<<n;
        cout<<"\nLevel limit of the towers: "<<levelLimit;
        cout<<"\nEnemy level: "<<difficulty;
        cout<<"\n\nNr of defeated enemies: "<<killCount<<endl;
        cout<<"Nr of times knights where defeated: "<<knightDefeatCount<<endl;
        cout<<"Nr of escaped enemies: "<<breachCount<<endl;
        cout<<"Total dmg dealt by the enemies : "<<TenemyDmg<<endl;
        cout<<"Total dmg dealt by the defense : "<<TdefenseDmg<<endl;
        cout<<"Total nr of earned coins: "<<totalGold<<endl;
        cout<<"Total nr of spent coins: "<<spentGold<<endl;
        cout<<"Average level of archer towers : "<<avgTowLvl<<endl;
        cout<<"Average level of barracks : "<<avgBrkLvl<<endl;
    }
};