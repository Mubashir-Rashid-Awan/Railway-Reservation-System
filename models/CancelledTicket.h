#ifndef CANCELLEDTICKET_H
#define CANCELLEDTICKET_H

#include <string>
using namespace std;

class CancelledTicket
{
public:
    int ticketID;
    string passengerName;
    int trainNumber;
    string cancellationReason;

    CancelledTicket* nextCancelled;

    CancelledTicket(int id,
                    string name,
                    int trainNum,
                    string reason);
};

#endif