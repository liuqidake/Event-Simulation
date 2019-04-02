//
// Created by Qi Liu on 2019-03-31.
//

#ifndef EVENTSIMULATIONS_BANKSIMULATOR_H
#define EVENTSIMULATIONS_BANKSIMULATOR_H

#include "Customer.h"
#include <queue>
#include <vector>
#include "math.h"

class BankSimulator{
private:
    std::queue<Customer&> waitingQueue;
    std::priority_queue<Customer&, std::vector<Customer&>, CustomerServiceDurationCompare> availableCheckersQueue;
    std::priority_queue<Customer&, std::vector<Customer&>, CustomerTotalServiceTimeCompare> totalServiceTimeQueue;
    bool isWaitingEvent;
    int timeToNextCustomerComing;
    int timeToNextCustomerServiceTimeOver;
    int arrivalRate;
    int maxServiceTime;

public:
    BankSimulator(int arrivalRate, int maxServiceTime, int seed);
    void bankSimulation(int serviceLimitTime);
    void updateWaitingEvent(int second);
    void updateServiceEvent(int second);
    void decreaseServiceTime();
    void checkOutCustomers();
    void serveNextCustomers(int second);
};



#endif //EVENTSIMULATIONS_BANKSIMULATOR_H
