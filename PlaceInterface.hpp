//
//  PlaceInterface.hpp
//  Event-Simulation
//
//  Created by Gong Tia on 4/8/19.
//  Copyright © 2019 Gong Tia. All rights reserved.
//

#ifndef PlaceInterface_h
#define PlaceInterface_h
#include "Customer.h"

class Place{
protected:
    //a priority queue for customers who finish service based on the total service time
    std::priority_queue<Customer, std::vector<Customer>, CustomerTotalServiceTimeCompare> totalServiceTimeQueue;
    int timeToNextCustomerLeaving;
    int timeToNextCustomerComing;
    int arrivalRate;
    int maxServiceTime;
    
public:
    virtual void printResult() = 0;
    virtual void simulation(int serviceLimitTime) = 0;
    virtual void updateWaitingEventWithNewCustomer(int currentTime) = 0;
    virtual void updateWaitingEventWithNoCustomer(int timeToJumpForward) = 0;
    virtual void updateServiceEvent(int currentTime, int timeToJumpForward) = 0;
    virtual void decreaseServiceTime(int timeToJumpForward) = 0;
    virtual void checkOutCustomers() = 0;
    virtual void serveNextCustomers(int currentTime) = 0;
    virtual double getNintyPercent() = 0;
    Place(int arrivalRate, int maxServiceTime, int seed){
            std::srand(seed);
            this->timeToNextCustomerComing = std::rand()%60 +1;
            this->timeToNextCustomerLeaving = INT_MAX;
            this->arrivalRate = arrivalRate;
            this->maxServiceTime = maxServiceTime;
    }
};

#endif /* PlaceInterface_h */
