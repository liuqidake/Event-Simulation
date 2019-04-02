//
// Created by Qi Liu on 2019-04-01.
//

#include "SupermarketSimulator.h"


SupermarketSimulator::SupermarketSimulator(int arrivalRate, int maxServiceTime, int seed){
    std::srand(seed);
    this->waitingTimeMinIndex= 0;
    this->waitingTimeMinTime= 0;
    for(int i = 0; i< numOfCheckers; i++){
        CustomerLine line;
        this->lines.push_back(line);
    }
    this->timeToNextCustomerComing = std::rand()%60 +1;
    this->timeToNextCustomerServiceTimeOver = INT_MAX;
    this->arrivalRate = arrivalRate;
    this->maxServiceTime = maxServiceTime;
    this->numOfServingCheckers = 0;
};

void SupermarketSimulator::supermarketSimulation(int serviceLimitTime){
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
}

void SupermarketSimulator::updateWaitingEventWithNewCustomer(int second) {
    Customer customer = {second, -1, std::rand() % (maxServiceTime) + 1, -1,waitingTimeMinIndex};
    customer.remainingServiceTime = customer.serviceTime;
    lines[waitingTimeMinIndex].customers.push(customer);
    lines[waitingTimeMinIndex].totalTime += customer.serviceTime;
    getMinTime();
    timeToNextCustomerComing = std::rand() % (arrivalRate)+1 +
                               (arrivalRate - (second%arrivalRate ==0?arrivalRate:second%arrivalRate));
}

void SupermarketSimulator::updateWaitingEventWithNoCustomer(int minTime) {
    timeToNextCustomerServiceTimeOver -= minTime;
}

/**
 * update the status of the customers being served
 * @param second
 */
void SupermarketSimulator::updateServiceEvent(int second, int minTime){
    decreaseServiceTime(minTime);
    checkOutCustomers();
    serveNextCustomers(second);
    timeToNextCustomerServiceTimeOver = servingQueue.size() == 0?INT_MAX:servingQueue.top().remainingServiceTime;
}

/**
 * Decrease the remaining time of all customers being served right now
 */
void SupermarketSimulator::decreaseServiceTime(int minTime){
    std::vector<Customer> temp;
    while(!servingQueue.empty()) {
        Customer customer = servingQueue.top();
        customer.remainingServiceTime = customer.remainingServiceTime- minTime;
        temp.push_back(customer);
        servingQueue.pop();
    }
    for(int i = 0; i< temp.size(); i++) servingQueue.push(temp[i]);
}

void SupermarketSimulator::checkOutCustomers(){
    while((!servingQueue.empty()) && servingQueue.top().remainingServiceTime == 0) {
        Customer customer = servingQueue.top();
        int index = customer.indexOfCashier;
        lines[index].totalTime -= customer.serviceTime;
        lines[index].serving = false;
        getMinTime();
        totalServiceTimeQueue.push(customer);
        servingQueue.pop();
    }
}

void SupermarketSimulator::serveNextCustomers(int second) {
    for(int i = 0; i< numOfCheckers; i++){
        CustomerLine line= lines[i];
        if((!line.serving) && (!line.customers.empty())){
            Customer customer = line.customers.front();
            customer.waitEndingTime = second;
            servingQueue.push(customer);
            line.serving = true;
            line.customers.pop();
        }
    }
}

void SupermarketSimulator::getMinTime(){
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
    std::cout<<ten<<" "<<fifty<<" "<<ninty<<std::endl;
}