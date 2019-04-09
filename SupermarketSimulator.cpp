//
// Created by Qi Liu on 2019-04-01.
//

#include "SupermarketSimulator.h"

void SupermarketSimulator::simulation(int serviceLimitTime){
    int currentTime = 0;
    int timeToJumpForward = 0;
    
    while(currentTime < serviceLimitTime){
        if(timeToNextCustomerComing <= timeToNextCustomerLeaving){
            timeToJumpForward = timeToNextCustomerComing;
            currentTime += timeToJumpForward;
            if(currentTime >= serviceLimitTime) return;
            updateWaitingEventWithNewCustomer(currentTime);
        } else{
            timeToJumpForward = timeToNextCustomerLeaving;
            currentTime += timeToJumpForward;
            if(currentTime >= serviceLimitTime) return;
            //            decrement timeToNextCustomerToCome:
            updateWaitingEventWithNoCustomer(timeToJumpForward);
        }

        updateServiceEvent(currentTime, timeToJumpForward);
    }
}

void SupermarketSimulator::updateWaitingEventWithNewCustomer(int currentTime) {
    //create a new customer arrival and push the customer to the shortest line:
    int serviceDuration = std::rand() % (maxServiceTime) + 1;
    Customer customer = {currentTime, -1, serviceDuration, -1, shortestLineIndex};
    customer.remainingServiceTime = customer.serviceTime;
    lines[shortestLineIndex].customers.push(customer);
    lines[shortestLineIndex].totalTime += customer.serviceTime;
    
    //after adding new customer, find the current shortest line and update waittime:
    findAndUpdateShortestLine();
    
    timeToNextCustomerComing =
    std::rand() % (arrivalRate)+ 1 + (arrivalRate - (currentTime % arrivalRate == 0 ? arrivalRate : currentTime % arrivalRate));
}

void SupermarketSimulator::updateWaitingEventWithNoCustomer(int minTime) {
    timeToNextCustomerComing -= minTime;
}

/**
 * update the status of the customers being served
 * @param second
 */
void SupermarketSimulator::updateServiceEvent(int currentTime, int timeToJump){
    decreaseServiceTime(timeToJump);
    checkOutCustomers();
    serveNextCustomers(currentTime);
    timeToNextCustomerLeaving = getCurrCustomerRemainingTime();
}

/**
 * Decrease the remaining time of all customers being served right now
 */
void SupermarketSimulator::decreaseServiceTime(int timeToJumpForward){
    for(int i = 0; i< numOfCheckers; i++){
        if(lines[i].serving){
            lines[i].customers.front().remainingServiceTime -= timeToJumpForward;
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

void SupermarketSimulator::serveNextCustomers(int currentTime) {
    for(int i = 0; i< numOfCheckers; i++){
        if((!lines[i].serving) &&(!lines[i].customers.empty())){
            lines[i].serving = true;
            lines[i].customers.front().waitEndingTime = currentTime;
        }
    }
}

void SupermarketSimulator::findAndUpdateShortestLine(){
    int minTime = lines[0].totalTime;
    int minIndex = 0;
    for(int i = 1; i< numOfCheckers; i++){
        if(lines[i].totalTime < minTime){
            minTime = lines[i].totalTime;
            minIndex = i;
        }
    }
    this->shortestLineWaitTime = minTime;
    this->shortestLineIndex= minIndex;
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

int SupermarketSimulator::getCurrCustomerRemainingTime() {
    int minTime = INT_MAX;
    for(int i = 0; i< numOfCheckers; i++){
        if(lines[i].serving && lines[i].customers.front().remainingServiceTime < minTime){
            minTime = lines[i].customers.front().remainingServiceTime;
        }
    }
    return minTime;
}
