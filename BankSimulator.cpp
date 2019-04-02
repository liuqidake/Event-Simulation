//
// Created by Qi Liu on 2019-03-31.
//

#include "BankSimulator.h"

BankSimulator:: BankSimulator(int arrivalRate, int maxServiceTime, int seed){
    std::srand(seed);
    this->timeToNextCustomerComing = arrivalRate;
    this->timeToNextCustomerServiceTimeOver = ULLONG_MAX;
    this->arrivalRate = arrivalRate;
    this->maxServiceTime = maxServiceTime;
    this->isWaitingEvent = true;
};


void BankSimulator::bankSimulation(int serviceLimitTime){
    int second = 1;
    int totalNumOfCheckers = 6;
    while(second <= serviceLimitTime){
        second = std::min(timeToNextCustomerComing, timeToNextCustomerServiceTimeOver);
        updateWaitingEvent(second);
        updateServiceEvent(second);
    }
}
void BankSimulator::updateWaitingEvent(int second){
    if(second % arrivalRate == 0){
        Customer customer = {second, -1, -1, -1};
        waitingQueue.push(customer);
    }

    timeToNextCustomerComing = arrivalRate - (second%arrivalRate);
}
void BankSimulator::updateServiceEvent(int second){
    int totalNumOfCheckers = 6;
    if(availableCheckersQueue.size() > 0 ){
        decreaseServiceTime();
        checkOutCustomers();
        serveNextCustomers(second);
    }
    timeToNextCustomerServiceTimeOver = availableCheckersQueue.top();
}

void BankSimulator::decreaseServiceTime(){
    std::vector<Customer&> temp;
    while(!availableCheckersQueue.empty()) {
        temp.push_back(availableCheckersQueue.top().remainingServiceTime - timeToNextCustomerComing);
        availableCheckersQueue.pop();
    }
    for(int i = 0; i< temp.size(); i++) availableCheckersQueue.push(temp[i]);
}

void BankSimulator::checkOutCustomers(){
    while((!availableCheckersQueue.empty())&&availableCheckersQueue.top().remainingServiceTime == 0) {
        Customer customer = availableCheckersQueue.top();
        totalServiceTimeQueue.push(customer);
        availableCheckersQueue.pop();
    }
}

void BankSimulator::serveNextCustomers(int second){
    int totalNumOfCheckers = 6;
    if(availableCheckersQueue.size() < totalNumOfCheckers){
        int remain = totalNumOfCheckers - availableCheckersQueue.size();
        int add = 0;
        while(add < remain && !waitingQueue.empty()){
            Customer curr = waitingQueue.front();
            waitingQueue.pop();
            curr.waitEndingTime = second;
            curr.serviceTime = std::rand() % (maxServiceTime) + 1;
            curr.remainingServiceTime = curr.serviceTime;
        }
    }
}