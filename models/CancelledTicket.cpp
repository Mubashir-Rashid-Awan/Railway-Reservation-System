#include "CancelledTicket.h"

CancelledTicket::CancelledTicket(int id,
                                 string name,
                                 int trainNum,
                                 string reason)
{
    ticketID = id;
    passengerName = name;
    trainNumber = trainNum;
    cancellationReason = reason;

    nextCancelled = NULL;
}