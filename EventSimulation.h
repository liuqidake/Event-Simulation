//
// Created by Qi Liu on 2019-04-01.
//

#include <iostream>
#include <cstdlib>
#include <climits>

#include "BankSimulator.h"
#include "SupermarketSimulator.h"

#ifndef EVENTSIMULATIONS_EVENTSIMULATION_H
#define EVENTSIMULATIONS_EVENTSIMULATION_H

class EventSimulation{
private:
    int serviceLimitTime;
    BankSimulator *bank;
    //SupermarketSimulator supermarket;
public:
    EventSimulation(double rate, double maxInMinute, int seed);
    void eventSimulation();
    void bankSimulation();
    void superMarketSimulation();
};


#endif //EVENTSIMULATIONS_EVENTSIMULATION_H
