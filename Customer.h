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
    int indexOfCashier;
};

struct CustomerLine{
    std::queue<Customer> customers;
    bool serving;
    int totalTime;
};

struct CustomerTotalServiceTimeCompare{
    bool operator()(const Customer& lhs, const Customer& rhs) const
    {
        return (rhs.serviceTime+rhs.waitEndingTime - rhs.waitStartingTime)
            < (lhs.serviceTime+lhs.waitEndingTime - lhs.waitStartingTime);
    }
};

struct CustomerServiceDurationCompare{
    bool operator()(const Customer& lhs, const Customer& rhs) const
    {
        return rhs.remainingServiceTime < lhs.remainingServiceTime;
    }
};


#endif //EVENTSIMULATIONS_CUSTOMER_H
