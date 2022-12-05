#pragma once
#include<iostream>

#include "View.h"
#include "Model.h"

class Controller
{
    public:

    View* v;
    Model* m;

    Controller(View* _v, Model* _m)
    {
        v = _v;
        m = _m;

        onLoad();
    }

    void onLoad()
    {
        auto [towNr, brkNr, n, levelLimit, difficulty] = v->getInput();

        m->setData(towNr, brkNr, n, levelLimit, difficulty);

        m->init();

        for(int i=0;i<100;i++)
        {
            m->runSim(50);

            v->renderResult(m->towNr, m->brkNr, m->n, m->levelLimit, m->difficulty,
                        m->player.killCount,m->player.knightDefeatCount,
                        m->player.breachCount,m->player.TenemyDmg,m->player.TdefenseDmg, 
                        m->player.totalGold,m->player.spentGold,m->player.avgTowLvl,m->player.avgBrkLvl);

            usleep(250000);
        }

        m->endGame();
    }
};