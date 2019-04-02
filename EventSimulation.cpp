//
// Created by Qi Liu on 2019-04-01.
//

#include "EventSimulation.h"

EventSimulation::EventSimulation(double rate, double maxInMinute, int seed){
    int arrivalRate = (int)60/rate;
    int maxServiceTime =  (int)60 * maxInMinute;
    this->serviceLimitTime = 12*60*60;
    this->bank = new BankSimulator(arrivalRate, maxServiceTime, seed);
    this->supermarket = new SupermarketSimulator(arrivalRate, maxServiceTime, seed);
}
void EventSimulation::eventSimulation(){
    bank->bankSimulation(serviceLimitTime);
    supermarket->supermarketSimulation(serviceLimitTime);
}
