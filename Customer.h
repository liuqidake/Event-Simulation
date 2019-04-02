//
// Created by Qi Liu on 2019-04-01.
//

#ifndef EVENTSIMULATIONS_CUSTOMER_H
#define EVENTSIMULATIONS_CUSTOMER_H

struct Customer{
    int waitStartingTime;
    int waitEndingTime;
    int serviceTime;
    int remainingServiceTime;
};


class CustomerTotalServiceTimeCompare{
public:
    bool operator() (Customer &lhs, Customer &rhs){
        return (rhs.serviceTime+rhs.waitEndingTime - rhs.waitStartingTime)
               - (lhs.serviceTime+lhs.waitEndingTime-lhs.waitStartingTime);
    }
};

class CustomerServiceDurationCompare{
public:
    bool operator() (Customer &lhs, Customer &rhs){
        return rhs.serviceTime - lhs.serviceTime;
    }
};
#endif //EVENTSIMULATIONS_CUSTOMER_H




// if available add people  check set if set is zero then skip; if not check if it is nullptr , if so, then  add a new customer
// if available and update set if its not nullptr then add this customer to pq
// add customer queue
// update cashier times   update cashier time, if it is nullptr, ignore , or update the Customer time if it is zero add it to set