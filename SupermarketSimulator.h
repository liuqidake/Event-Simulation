//
// Created by Qi Liu on 2019-04-01.
//

#ifndef EVENTSIMULATIONS_SUPERMARKETSIMULATOR_H
#define EVENTSIMULATIONS_SUPERMARKETSIMULATOR_H

#include <iostream>
#include <queue>
#include <vector>
#include "math.h"
#include "Customer.h"
#include "PlaceInterface.hpp"
const int numOfCheckers = 6;

class SupermarketSimulator: public Place{
private:
    std::vector<CustomerLine> lines; //six lines
    int shortestLineIndex ; //The line index which has the shoertest time to wait
    int shortestLineWaitTime;//The line' waiting time which is the shortest
    
public:
    SupermarketSimulator(int arrivalRate, int maxServiceTime, int seed):Place(arrivalRate, maxServiceTime, seed){
        this->shortestLineIndex= 0;
        this->shortestLineWaitTime= 0;
        //    lines vector of six customer lines
        for(int i = 0; i< numOfCheckers; i++){
            CustomerLine customerLine;
            this->lines.push_back(customerLine);
        }
    };
    
    void printResult();
    void simulation(int serviceLimitTime);
    void updateWaitingEventWithNewCustomer(int currentTime);
    void updateWaitingEventWithNoCustomer(int timeToJumpForward);
    void updateServiceEvent(int currentTime, int timeToJumpForward);
    void decreaseServiceTime(int timeToJumpForward);
    void checkOutCustomers();
    void serveNextCustomers(int currentTime);
//    getMinTotalTime is actually updating the shortest lines' wait time
    void findAndUpdateShortestLine();
//    get the customer being process's shortest remaining process time
    int getCurrCustomerRemainingTime();
    double getNintyPercent();
};
#endif //EVENTSIMULATIONS_SUPERMARKETSIMULATOR_H
