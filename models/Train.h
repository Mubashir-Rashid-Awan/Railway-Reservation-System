#ifndef TRAIN_H
#define TRAIN_H

#include <string>
using namespace std;

class Train
{
public:
    int trainNumber;
    string trainName;
    string sourceStation;
    string destinationStation;

    int totalACSeats;
    int totalSleeperSeats;

    int availableACSeats;
    int availableSleeperSeats;

    double acFare;
    double sleeperFare;

    Train* nextTrain;
    Train* prevTrain;

    Train(int number, string name,
          string source,
          string destination,
          int acSeats,
          int sleeperSeats,
          double acPrice,
          double sleeperPrice);
};

#endif