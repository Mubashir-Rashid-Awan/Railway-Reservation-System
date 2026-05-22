#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger
{
public:
    string passengerName;
    int passengerAge;
    string passengerCNIC;
    string seatClass;
    int ticketID;
    int trainNumber;

    Passenger* nextPassenger;
    Passenger* prevPassenger;

    Passenger(string name, int age, string cnic,
              string seatType, int ticketId, int trainNum);
};

#endif