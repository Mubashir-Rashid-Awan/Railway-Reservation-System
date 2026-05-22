#include "Train.h"

Train::Train(int number, string name,
             string source,
             string destination,
             int acSeats,
             int sleeperSeats,
             double acPrice,
             double sleeperPrice)
{
    trainNumber = number;
    trainName = name;
    sourceStation = source;
    destinationStation = destination;

    totalACSeats = acSeats;
    totalSleeperSeats = sleeperSeats;

    availableACSeats = acSeats;
    availableSleeperSeats = sleeperSeats;

    acFare = acPrice;
    sleeperFare = sleeperPrice;

    nextTrain = NULL;
    prevTrain = NULL;
}