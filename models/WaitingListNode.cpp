#include "WaitingListNode.h"

WaitingListNode::WaitingListNode(string name,
                                 int age,
                                 string cnic,
                                 string seatType,
                                 int trainNum)
{
    passengerName = name;
    passengerAge = age;
    passengerCNIC = cnic;
    seatClass = seatType;
    trainNumber = trainNum;

    nextInWaitingList = NULL;
    prevInWaitingList = NULL;
}