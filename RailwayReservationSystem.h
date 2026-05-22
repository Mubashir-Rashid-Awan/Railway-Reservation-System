#ifndef RAILWAYRESERVATIONSYSTEM_H
#define RAILWAYRESERVATIONSYSTEM_H

#include <iostream>
#include <fstream>

#include "models/Train.h"
#include "models/Passenger.h"
#include "models/WaitingListNode.h"
#include "models/CancelledTicket.h"

using namespace std;

class RailwayReservationSystem
{
private:
    Train* trainListHead;
    Passenger* passengerListHead;
    WaitingListNode* waitingListHead;
    CancelledTicket* cancelledStackTop;

    int ticketCounter;

    string adminUsername;
    string adminPassword;

public:
    RailwayReservationSystem();

    void addNewTrain();
    void displayAllTrains();
    Train* findTrainByNumber(int number);

    void bookTicket();

    void addToWaitingList(string name, int age,
                          string cnic,
                          string seatClass,
                          int trainNum);

    void displayWaitingList();

    void cancelTicket();

    void assignFromWaitingList(Train* train);

    void displayCancelledTickets();

    void displayAllPassengers();

    void loadTrainsFromFile();
    void loadPassengersFromFile();

    void saveTrainsToFile();
    void savePassengersToFile();
    void saveCancellationsToFile();

    void displayMainMenu();

    bool authenticateAdmin();
    void adminMenu();
};

#endif