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

class SupermarketSimulator{
private:
    //the priority queue of customers who are being served
    std::priority_queue<Customer, std::vector<Customer>,CustomerServiceDurationCompare> servingQueue;
    std::vector<CustomerLine> lines; //six lines
    int waitingTimeMinIndex = 0; //The line index which has the shoertest time to wait
    int waitingTimeMinTime = 0;//The line' waiting time which is the shortest
    //a priority queue for customers who finish service based on the total service time
    std::priority_queue<Customer, std::vector<Customer>, CustomerTotalServiceTimeCompare> totalServiceTimeQueue;
    int numOfServingCheckers; //the number of checkers who are no idle
    int timeToNextCustomerComing;
    //the time length from the current time to the time that the service of a customer finished
    int timeToNextCustomerServiceTimeOver;
    //number of seconds that between two customers coming to bank
    int arrivalRate;
    //the time that the bank should be closed
    int maxServiceTime;

    const int numOfCheckers = 6;
public:
    SupermarketSimulator(int arrivalRate, int maxServiceTime, int seed);
    void printResult();
    void supermarketSimulation(int serviceLimitTime);
    void updateWaitingEventWithNewCustomer(int second);
    void updateWaitingEventWithNoCustomer(int minTime);
    void updateServiceEvent(int second, int minTime);
    void decreaseServiceTime(int minTime);
    void checkOutCustomers();
    void serveNextCustomers(int second);
    void getMinTime();
};
#endif //EVENTSIMULATIONS_SUPERMARKETSIMULATOR_H
