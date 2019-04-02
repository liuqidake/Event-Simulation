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

class BankSimulator{
private:
    //customers are added into this queue waiting for service
    std::queue<Customer> waitingQueue;
    //a priority queue for customers who are being served based on service time duration
    std::priority_queue<Customer, std::vector<Customer>, CustomerServiceDurationCompare> availableCheckersQueue;
    //a priority queue for customers who finish service based on the total service time
    std::priority_queue<Customer, std::vector<Customer>, CustomerTotalServiceTimeCompare> totalServiceTimeQueue;
    //the time length from the current time to the time that a customer coming to bank
    int timeToNextCustomerComing;
    //the time length from the current time to the time that the service of a customer finished
    int timeToNextCustomerServiceTimeOver;
    //number of seconds that between two customers coming to bank
    int arrivalRate;
    //the time that the bank should be closed
    int maxServiceTime;

public:
    BankSimulator(int arrivalRate, int maxServiceTime, int seed);
    void printResult();
    void bankSimulation(int serviceLimitTime);
    void updateWaitingEvent(int second);
    void updateServiceEvent(int second, int minTime);
    void decreaseServiceTime(int minTime);
    void checkOutCustomers();
    void serveNextCustomers(int second);
};



#endif //EVENTSIMULATIONS_BANKSIMULATOR_H
