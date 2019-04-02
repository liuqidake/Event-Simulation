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
    int minTime = 0;
    while(second < serviceLimitTime){
        if(timeToNextCustomerComing <= timeToNextCustomerServiceTimeOver){
            minTime = timeToNextCustomerComing;
            second += minTime;
            updateWaitingEventWithNewCustomer(second);
        } else{
            minTime = timeToNextCustomerServiceTimeOver;
            second+= minTime;
            updateWaitingEventWithNoCustomer(minTime);
        }

        updateServiceEvent(second, minTime);
    }
//    while(second < serviceLimitTime){
//        int minTime = std::min(timeToNextCustomerComing, timeToNextCustomerServiceTimeOver);
//        second += minTime;
//        updateWaitingEvent(second);
//        updateServiceEvent(second, minTime);
//    }
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
void BankSimulator::updateWaitingEventWithNewCustomer(int second){

    Customer customer = {second, -1, std::rand() % (maxServiceTime) + 1, -1};
    customer.remainingServiceTime = customer.serviceTime;
    waitingQueue.push(customer);

    //update the time towards a new customer coming to the bank
    timeToNextCustomerComing = std::rand() % (arrivalRate)+1 +
            (arrivalRate - (second%arrivalRate ==0?arrivalRate:second%arrivalRate));
}

void BankSimulator::updateWaitingEventWithNoCustomer(int minTime){
    timeToNextCustomerServiceTimeOver -= minTime;
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
    timeToNextCustomerServiceTimeOver = servingQueue.size() == 0?INT_MAX
            :servingQueue.top().remainingServiceTime;
}

/**
 * Decrease the remaining time of all customers being served right now
 */
void BankSimulator::decreaseServiceTime(int minTime){
    std::vector<Customer> temp;
    while(!servingQueue.empty()) {
        Customer customer = servingQueue.top();
        customer.remainingServiceTime = customer.remainingServiceTime- minTime;
        temp.push_back(customer);
        servingQueue.pop();
    }
    for(int i = 0; i< temp.size(); i++) servingQueue.push(temp[i]);
}

void BankSimulator::checkOutCustomers(){
    while((!servingQueue.empty()) && servingQueue.top().remainingServiceTime == 0) {
        Customer customer = servingQueue.top();
        totalServiceTimeQueue.push(customer);
        servingQueue.pop();
    }
}

void BankSimulator::serveNextCustomers(int second){
    int totalNumOfCheckers = 6;
    if(servingQueue.size() < totalNumOfCheckers){
        int remain = totalNumOfCheckers - servingQueue.size();
        int add = 0;
        while(add < remain && !waitingQueue.empty()){
            Customer curr = waitingQueue.front();
            waitingQueue.pop();
            curr.waitEndingTime = second;
            servingQueue.push(curr);
            add++;
        }
    }
}