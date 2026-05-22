#ifndef WAITINGLISTNODE_H
#define WAITINGLISTNODE_H

#include <string>
using namespace std;

class WaitingListNode
{
public:
    string passengerName;
    int passengerAge;
    string passengerCNIC;
    string seatClass;
    int trainNumber;

    WaitingListNode* nextInWaitingList;
    WaitingListNode* prevInWaitingList;

    WaitingListNode(string name,
                    int age,
                    string cnic,
                    string seatType,
                    int trainNum);
};

#endif