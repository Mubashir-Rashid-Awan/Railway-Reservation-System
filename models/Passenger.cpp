#include "Passenger.h"

Passenger::Passenger(string name, int age, string cnic,
                     string seatType, int ticketId, int trainNum)
{
    passengerName = name;
    passengerAge = age;
    passengerCNIC = cnic;
    seatClass = seatType;
    ticketID = ticketId;
    trainNumber = trainNum;

    nextPassenger = NULL;
    prevPassenger = NULL;
}