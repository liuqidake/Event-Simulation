//
// Created by Qi Liu on 2019-04-01.
//

#include "SupermarketSimulator.h"


SupermarketSimulator::SupermarketSimulator(int arrivalRate, int maxServiceTime, int seed){
    std::srand(seed);
    this->waitingTimeMinIndex= 0;
    this->waitingTimeMinTime= 0;
    for(int i = 0; i< numOfCheckers; i++){
        CustomerLine customerLine;
        this->lines.push_back(customerLine);
    }
    this->timeToNextCustomerComing = std::rand()%60 +1;
    this->timeToNextCustomerServiceTimeOver = INT_MAX;
    this->arrivalRate = arrivalRate;
    this->maxServiceTime = maxServiceTime;
};

void SupermarketSimulator::supermarketSimulation(int serviceLimitTime){
    int second = 0;
    int minTime = 0;
    while(second < serviceLimitTime){
        if(timeToNextCustomerComing <= timeToNextCustomerServiceTimeOver){
            minTime = timeToNextCustomerComing;
            second += minTime;
            if(second >= serviceLimitTime) return;
            updateWaitingEventWithNewCustomer(second);
        } else{
            minTime = timeToNextCustomerServiceTimeOver;
            second+= minTime;
            if(second >= serviceLimitTime) return;
            updateWaitingEventWithNoCustomer(minTime);
        }

        updateServiceEvent(second, minTime);
    }
}

void SupermarketSimulator::updateWaitingEventWithNewCustomer(int second) {
    Customer customer = {second, -1, std::rand() % (maxServiceTime) + 1, -1,waitingTimeMinIndex};
    customer.remainingServiceTime = customer.serviceTime;
    lines[waitingTimeMinIndex].customers.push(customer);
    lines[waitingTimeMinIndex].totalTime += customer.serviceTime;
    getMinTotalTime();
    timeToNextCustomerComing = std::rand() % (arrivalRate)+1 +
                               (arrivalRate - (second%arrivalRate ==0?arrivalRate:second%arrivalRate));
}

void SupermarketSimulator::updateWaitingEventWithNoCustomer(int minTime) {
    timeToNextCustomerComing -= minTime;
}

/**
 * update the status of the customers being served
 * @param second
 */
void SupermarketSimulator::updateServiceEvent(int second, int minTime){
    decreaseServiceTime(minTime);
    checkOutCustomers();
    serveNextCustomers(second);
    timeToNextCustomerServiceTimeOver = getMinRemainingTime();
}

/**
 * Decrease the remaining time of all customers being served right now
 */
void SupermarketSimulator::decreaseServiceTime(int minTime){
    for(int i = 0; i< numOfCheckers; i++){
        if(lines[i].serving){
            lines[i].customers.front().remainingServiceTime -= minTime;
        }
    }
}

void SupermarketSimulator::checkOutCustomers(){
    for(int i = 0; i< numOfCheckers; i++){
        if(lines[i].serving){
            Customer& customer = lines[i].customers.front();
            if(customer.remainingServiceTime == 0){
               totalServiceTimeQueue.push(customer);
               lines[i].customers.pop();
               lines[i].serving = false;
               lines[i].totalTime -= customer.serviceTime;
            }
        }
    }
}

void SupermarketSimulator::serveNextCustomers(int second) {
    for(int i = 0; i< numOfCheckers; i++){
        if((!lines[i].serving) &&(!lines[i].customers.empty())){
            lines[i].serving = true;
            lines[i].customers.front().waitEndingTime = second;
        }
    }
}

void SupermarketSimulator::getMinTotalTime(){
    int minTime = lines[0].totalTime;
    int minIndex = 0;
    for(int i = 1; i< numOfCheckers; i++){
        if(lines[i].totalTime < minTime){
            minTime = lines[i].totalTime;
            minIndex = i;
        }
    }
    this->waitingTimeMinTime = minTime;
    this->waitingTimeMinIndex= minIndex;
}


void SupermarketSimulator::printResult() {

    double ten;
    double fifty;
    double ninty;
    int total = this->totalServiceTimeQueue.size();
    for(int i = 0; i < total; i++){
        Customer customer = totalServiceTimeQueue.top();
        if(i*100/ total == 10){
            ten = (customer.serviceTime+ customer.waitEndingTime - customer.waitStartingTime)/(double)60;
        }
        if(i*100/ total == 50){
            fifty = (customer.serviceTime+ customer.waitEndingTime - customer.waitStartingTime)/(double)60;
        }
        if(i*100/ total == 90){
            ninty = (customer.serviceTime+ customer.waitEndingTime - customer.waitStartingTime)/(double)60;
        }

        totalServiceTimeQueue.pop();
    }
}

double SupermarketSimulator::getNintyPercent() {
    int total = this->totalServiceTimeQueue.size();
    double ninty;
    for(int i = 0; i < total; i++){
        Customer customer = totalServiceTimeQueue.top();
        if(i*100/ total == 90){
            ninty = (customer.serviceTime+ customer.waitEndingTime - customer.waitStartingTime)/(double)60;
            break;
        }

        totalServiceTimeQueue.pop();
    }

    return ninty;
}

int SupermarketSimulator::getMinRemainingTime() {
    int minTime = INT_MAX;
    for(int i = 0; i< numOfCheckers; i++){
        if(lines[i].serving && lines[i].customers.front().remainingServiceTime< minTime){
            minTime = lines[i].customers.front().remainingServiceTime;
        }
    }
    return minTime;
}