//
// Created by Qi Liu on 2019-03-31.
//

#ifndef EVENTSIMULATIONS_BANKSIMULATOR_H
#define EVENTSIMULATIONS_BANKSIMULATOR_H

#include <iostream>
#include <queue>
#include <vector>
#include "math.h"
#include "Customer.h"
#include "PlaceInterface.hpp"

class BankSimulator:public Place{
private:
    //customers are added into this queue waiting for service
    std::queue<Customer> waitingQueue;
    //a priority queue for customers who are being served based on service time duration
    std::priority_queue<Customer, std::vector<Customer>, CustomerServiceDurationCompare> servingQueue;

public:
    BankSimulator(int arrivalRate, int maxServiceTime, int seed);
    void printResult();
    void simulation(int serviceLimitTime);
    void updateWaitingEventWithNewCustomer(int second);
    void updateWaitingEventWithNoCustomer(int minTime);
    void updateServiceEvent(int second, int minTime);
    void decreaseServiceTime(int minTime);
    void checkOutCustomers();
    void serveNextCustomers(int second);
    double getNintyPercent();
};



#endif //EVENTSIMULATIONS_BANKSIMULATOR_H
