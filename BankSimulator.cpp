//
// Created by Qi Liu on 2019-03-31.
//

#include "BankSimulator.h"

BankSimulator:: BankSimulator(int arrivalRate, int maxServiceTime, int seed){
    std::srand(seed);
    this->timeToNextCustomerComing = arrivalRate;
    this->timeToNextCustomerServiceTimeOver = INT_MAX;
    this->arrivalRate = arrivalRate;
    this->maxServiceTime = maxServiceTime;
};


void BankSimulator::bankSimulation(int serviceLimitTime){
    int second = 0;
    while(second < serviceLimitTime){
        int minTime = std::min(timeToNextCustomerComing, timeToNextCustomerServiceTimeOver);
        second += minTime;
        updateWaitingEvent(second);
        updateServiceEvent(second, minTime);
    }
}

void BankSimulator::printResult() {

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
    std::cout<<ten<<" "<<fifty<<" "<<ninty<<std::endl;
}

/**
* add new customer into waiting queue when the time is the time that a customer should come to bank
* @param second
*/
void BankSimulator::updateWaitingEvent(int second){
    //second % arrivalRate == 0 means the minimum time is the time before a new customer comes to a bank
    if(second % arrivalRate == 0){
        Customer customer = {second, -1, -1, -1};
        waitingQueue.push(customer);
        //std::cout<<waitingQueue.size()<<std::endl;
    }
    //update the time towards a new customer coming to the bank
    timeToNextCustomerComing = arrivalRate - (second%arrivalRate);
}

/**
 * update the status of the customers being served
 * @param second
 */
void BankSimulator::updateServiceEvent(int second, int minTime){
    int totalNumOfCheckers = 6;
    decreaseServiceTime(minTime);
    checkOutCustomers();
    serveNextCustomers(second);
    timeToNextCustomerServiceTimeOver = availableCheckersQueue.size() == 0?INT_MAX
            :availableCheckersQueue.top().remainingServiceTime;
}

/**
 * Decrease the remaining time of all customers being served right now
 */
void BankSimulator::decreaseServiceTime(int minTime){
    std::vector<Customer> temp;
    while(!availableCheckersQueue.empty()) {
        Customer customer = availableCheckersQueue.top();
        customer.remainingServiceTime = customer.remainingServiceTime- minTime;
        temp.push_back(customer);
        availableCheckersQueue.pop();
    }
    for(int i = 0; i< temp.size(); i++) availableCheckersQueue.push(temp[i]);
}

void BankSimulator::checkOutCustomers(){
    while((!availableCheckersQueue.empty()) && availableCheckersQueue.top().remainingServiceTime == 0) {
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
            availableCheckersQueue.push(curr);
            add++;
        }
    }
}