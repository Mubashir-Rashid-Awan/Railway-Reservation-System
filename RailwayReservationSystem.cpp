#include "RailwayReservationSystem.h"
#include <cctype>

RailwayReservationSystem::RailwayReservationSystem()
{
    trainListHead = NULL;
    passengerListHead = NULL;
    waitingListHead = NULL;
    cancelledStackTop = NULL;

    ticketCounter = 1000;

    adminUsername = "admin";
    adminPassword = "admin123";

    loadTrainsFromFile();
    loadPassengersFromFile();
}

void RailwayReservationSystem::addNewTrain()
{
    int number, acSeats, sleeperSeats;
    string name, source, destination;
    double acPrice, sleeperPrice;

    cout << "+========================================+\n";
    cout << "|               ADD NEW TRAIN            |\n";
    cout << "+========================================+\n";

    cout << "Train Number: ";
    cin >> number;
    cin.ignore();

    Train* temp = trainListHead;

    while (temp != NULL)
    {
        if (temp->trainNumber == number)
        {
            cout << "Train with this number already exists!\n";
            return;
        }

        temp = temp->nextTrain;
    }

    cout << "Train Name: ";
    getline(cin, name);

    cout << "Source Station: ";
    getline(cin, source);

    cout << "Destination Station: ";
    getline(cin, destination);

    cout << "Total AC Seats: ";
    cin >> acSeats;

    cout << "Total Sleeper Seats: ";
    cin >> sleeperSeats;

    cout << "AC Fare (Rs): ";
    cin >> acPrice;

    cout << "Sleeper Fare (Rs): ";
    cin >> sleeperPrice;

    Train* newTrain = new Train(
        number,
        name,
        source,
        destination,
        acSeats,
        sleeperSeats,
        acPrice,
        sleeperPrice
    );

    if (trainListHead == NULL)
    {
        trainListHead = newTrain;
    }
    else
    {
        Train* temp = trainListHead;

        while (temp->nextTrain != NULL)
        {
            temp = temp->nextTrain;
        }

        temp->nextTrain = newTrain;
        newTrain->prevTrain = temp;
    }

    saveTrainsToFile();

    cout << "\nTrain added successfully!\n";
}

void RailwayReservationSystem::displayAllTrains()
{
    if (trainListHead == NULL)
    {
        cout << "\nNo trains available!\n";
        return;
    }

    cout << "+========================================+\n";
    cout << "|             AVAILABLE TRAINS           |\n";
    cout << "+========================================+\n";

    Train* temp = trainListHead;

    while (temp != NULL)
    {
        cout << "\nTrain Number: " << temp->trainNumber;
        cout << "\nTrain Name: " << temp->trainName;
        cout << "\nRoute: "
             << temp->sourceStation
             << " -> "
             << temp->destinationStation;

        cout << "\nAC Seats: "
             << temp->availableACSeats
             << "/"
             << temp->totalACSeats
             << " (Rs "
             << temp->acFare
             << ")";

        cout << "\nSleeper Seats: "
             << temp->availableSleeperSeats
             << "/"
             << temp->totalSleeperSeats
             << " (Rs "
             << temp->sleeperFare
             << ")";

        cout << "\n" << string(40, '-') << "\n";

        temp = temp->nextTrain;
    }
}


	    
	    
Train* RailwayReservationSystem::findTrainByNumber(int number) 
{
    Train* temp = trainListHead;
    while (temp != NULL) 
    {
        if (temp->trainNumber == number) 
        {
            return temp;
        }
        temp = temp->nextTrain;
    }
    return NULL;
}
	    

void RailwayReservationSystem::bookTicket() 
{
    string name, cnic, seatClass;
    int age, trainNum;
    
    displayAllTrains();
    
    if (trainListHead == NULL) 
    {
        return;
    }
    
    cout << "+========================================+\n";
    cout << "|               BOOK TICKET              |\n";
    cout << "+========================================+\n";
    cout << "Enter Train Number: ";
    cin >> trainNum;
    
    Train* train = findTrainByNumber(trainNum);
    if (train == NULL) 
    {
        cout << "Train not found!\n";
        return;
    }
    
    cin.ignore();
    cout << "Passenger Name: ";
    getline(cin, name);
    cout << "Age: ";
    cin >> age;
    cin.ignore();
    cout << "CNIC: ";
    getline(cin, cnic);
    cout << "Seat Class (AC/Sleeper): ";
    getline(cin, seatClass);
    

    for (int i = 0; i < seatClass.length(); i++) 
    {
        seatClass[i] = toupper(seatClass[i]);
    }
    
    if (seatClass != "AC" && seatClass != "SLEEPER") 
    {
        cout << "Invalid seat class! Choose AC or Sleeper.\n";
        return;
    }
    

    if (seatClass == "AC" && train->availableACSeats > 0) 
    {
        train->availableACSeats--;
        int ticketId = ++ticketCounter;
        
        Passenger* newPassenger = new Passenger(name, age, cnic, seatClass, ticketId, trainNum);
        
        if (passengerListHead == NULL) 
        {
            passengerListHead = newPassenger;
        } 
        else 
        {
            Passenger* temp = passengerListHead;
            while (temp->nextPassenger != NULL) 
            {
                temp = temp->nextPassenger;
            }
            temp->nextPassenger = newPassenger;
            newPassenger->prevPassenger = temp;
        }
        
        savePassengersToFile();
        saveTrainsToFile();
        
        cout << "\n✓ Ticket Booked Successfully!\n";
        cout << "Ticket ID: " << ticketId << "\n";
        cout << "Fare: Rs " << train->acFare << "\n";
        
    } 
    else if (seatClass == "SLEEPER" && train->availableSleeperSeats > 0) 
    {
        train->availableSleeperSeats--;
        int ticketId = ++ticketCounter;
        
        Passenger* newPassenger = new Passenger(name, age, cnic, seatClass, ticketId, trainNum);
        
        if (passengerListHead == NULL) 
        {
            passengerListHead = newPassenger;
        } 
        else 
        {
            Passenger* temp = passengerListHead;
            while (temp->nextPassenger != NULL) 
            {
                temp = temp->nextPassenger;
            }
            temp->nextPassenger = newPassenger;
            newPassenger->prevPassenger = temp;
        }
        
        savePassengersToFile();
        saveTrainsToFile();
        
        cout << "\nTicket Booked Successfully!\n";
        cout << "Ticket ID: " << ticketId << "\n";
        cout << "Fare: Rs " << train->sleeperFare << "\n";
        
    } 
    else 
    {
        cout << "\nNo seats available! Adding to waiting list...\n";
        addToWaitingList(name, age, cnic, seatClass, trainNum);
    }
}

// ==================== WAITING LIST MANAGEMENT ====================
void RailwayReservationSystem::addToWaitingList(string name, int age, string cnic, string seatClass, int trainNum) 
{
    WaitingListNode* newNode = new WaitingListNode(name, age, cnic, seatClass, trainNum);
    
    if (waitingListHead == NULL) 
    {
        waitingListHead = newNode;
    } 
    else 
    {
        WaitingListNode* temp = waitingListHead;
        while (temp->nextInWaitingList != NULL) 
        {
            temp = temp->nextInWaitingList;
        }
        temp->nextInWaitingList = newNode;
        newNode->prevInWaitingList = temp;
    }
    
    cout << "Added to waiting list!\n";
}

void RailwayReservationSystem::displayWaitingList() 
{
    if (waitingListHead == NULL) 
    {
        cout << "\nWaiting list is empty!\n";
        return;
    }
    
    cout << "+========================================+\n";
    cout << "|              WAITING LIST              |\n";
    cout << "+========================================+\n";
    WaitingListNode* temp = waitingListHead;
    int count = 1;
    while (temp != NULL) 
    {
        cout << "\n[" << count++ << "]";
        cout << "\nName: " << temp->passengerName;
        cout << "\nAge: " << temp->passengerAge;
        cout << "\nCNIC: " << temp->passengerCNIC;
        cout << "\nSeat Class: " << temp->seatClass;
        cout << "\nTrain Number: " << temp->trainNumber;
        cout << "\n" << string(40, '-') << "\n";
        temp = temp->nextInWaitingList;
    }
}

void RailwayReservationSystem::cancelTicket() 
{
    int ticketId;
    cout << "+========================================+\n";
    cout << "|              CANCEL TICKET             |\n";
    cout << "+========================================+\n";
    cout << "Enter Ticket ID: ";
    cin >> ticketId;
    
    Passenger* temp = passengerListHead;
    while (temp != NULL) 
    {
        if (temp->ticketID == ticketId) 
        {
            string reason;
            cin.ignore();
            cout << "Cancellation Reason: ";
            getline(cin, reason);
            
            CancelledTicket* cancelled = new CancelledTicket(ticketId, temp->passengerName, 
                                                                temp->trainNumber, reason);
            cancelled->nextCancelled = cancelledStackTop;
            cancelledStackTop = cancelled;
            

            Train* train = findTrainByNumber(temp->trainNumber);
            if (train != NULL) 
            {
                if (temp->seatClass == "AC") 
                {
                    train->availableACSeats++;
                } 
                else 
                {
                    train->availableSleeperSeats++;
                }
            }
            

            if (temp->prevPassenger != NULL) 
            {
                temp->prevPassenger->nextPassenger = temp->nextPassenger;
            } 
            else 
            {
                passengerListHead = temp->nextPassenger;
            }
            
            if (temp->nextPassenger != NULL) 
            {
                temp->nextPassenger->prevPassenger = temp->prevPassenger;
            }
            
            delete temp;
            

            assignFromWaitingList(train);
            
            savePassengersToFile();
            saveTrainsToFile();
            saveCancellationsToFile();
            
            cout << "\nTicket cancelled successfully!\n";
            return;
        }
        temp = temp->nextPassenger;
    }
    
    cout << "\nTicket not found!\n";
}

void RailwayReservationSystem::assignFromWaitingList(Train* train) 
{
    if (waitingListHead == NULL || train == NULL) 
    {
        return;
    }
    
    WaitingListNode* temp = waitingListHead;
    while (temp != NULL) 
    {
        if (temp->trainNumber == train->trainNumber) 
        {
            if (temp->seatClass == "AC" && train->availableACSeats > 0) 
            {
                train->availableACSeats--;
                int ticketId = ++ticketCounter;
                
                Passenger* newPassenger = new Passenger(temp->passengerName, temp->passengerAge, 
                                                            temp->passengerCNIC, temp->seatClass, 
                                                            ticketId, temp->trainNumber);
                
                if (passengerListHead == NULL) 
                {
                    passengerListHead = newPassenger;
                } 
                else 
                {
                    Passenger* pTemp = passengerListHead;
                    while (pTemp->nextPassenger != NULL) 
                    {
                        pTemp = pTemp->nextPassenger;
                    }
                    pTemp->nextPassenger = newPassenger;
                    newPassenger->prevPassenger = pTemp;
                }
                

                if (temp->prevInWaitingList != NULL) 
                {
                    temp->prevInWaitingList->nextInWaitingList = temp->nextInWaitingList;
                } 
                else 
                {
                    waitingListHead = temp->nextInWaitingList;
                }
                
                if (temp->nextInWaitingList != NULL) 
                {
                    temp->nextInWaitingList->prevInWaitingList = temp->prevInWaitingList;
                }
                
                cout << "Ticket assigned to " << temp->passengerName << " from waiting list!\n";
                cout << "New Ticket ID: " << ticketId << "\n";
                
                delete temp;
                return;
                
            } 
            else if (temp->seatClass == "SLEEPER" && train->availableSleeperSeats > 0) 
            {
                train->availableSleeperSeats--;
                int ticketId = ++ticketCounter;
                
                Passenger* newPassenger = new Passenger(temp->passengerName, temp->passengerAge, 
                                                            temp->passengerCNIC, temp->seatClass, 
                                                            ticketId, temp->trainNumber);
                
                if (passengerListHead == NULL) 
                {
                    passengerListHead = newPassenger;
                } 
                else 
                {
                    Passenger* pTemp = passengerListHead;
                    while (pTemp->nextPassenger != NULL) 
                    {
                        pTemp = pTemp->nextPassenger;
                    }
                    pTemp->nextPassenger = newPassenger;
                    newPassenger->prevPassenger = pTemp;
                }
                

                if (temp->prevInWaitingList != NULL) 
                {
                    temp->prevInWaitingList->nextInWaitingList = temp->nextInWaitingList;
                } 
                else 
                {
                    waitingListHead = temp->nextInWaitingList;
                }
                
                if (temp->nextInWaitingList != NULL) 
                {
                    temp->nextInWaitingList->prevInWaitingList = temp->prevInWaitingList;
                }
                
                cout << "Ticket assigned to " << temp->passengerName << " from waiting list!\n";
                cout << "New Ticket ID: " << ticketId << "\n";
                
                delete temp;
                return;
            }
        }
        temp = temp->nextInWaitingList;
    }
}

void RailwayReservationSystem::displayCancelledTickets() 
{
    if (cancelledStackTop == NULL) 
    {
        cout << "\nNo cancelled tickets!\n";
        return;
    }
    
    cout << "+========================================+\n";
    cout << "|             CANCELLED TICKETS          |\n";
    cout << "+========================================+\n";
    CancelledTicket* temp = cancelledStackTop;
    while (temp != NULL) 
    {
        cout << "\nTicket ID: " << temp->ticketID;
        cout << "\nPassenger: " << temp->passengerName;
        cout << "\nTrain Number: " << temp->trainNumber;
        cout << "\nReason: " << temp->cancellationReason;
        cout << "\n" << string(40, '-') << "\n";
        temp = temp->nextCancelled;
    }
}

void RailwayReservationSystem::displayAllPassengers() 
{
    if (passengerListHead == NULL) 
    {
        cout << "\nNo passengers found!\n";
        return;
    }
    
    cout << "+========================================+\n";
    cout << "|              PASSENGER LIST            |\n";
    cout << "+========================================+\n";
    Passenger* temp = passengerListHead;
    while (temp != NULL) 
    {
        cout << "\nTicket ID: " << temp->ticketID;
        cout << "\nName: " << temp->passengerName;
        cout << "\nAge: " << temp->passengerAge;
        cout << "\nCNIC: " << temp->passengerCNIC;
        cout << "\nSeat Class: " << temp->seatClass;
        cout << "\nTrain Number: " << temp->trainNumber;
        cout << "\n" << string(40, '-') << "\n";
        temp = temp->nextPassenger;
    }
}


void RailwayReservationSystem::loadTrainsFromFile() 
{
    ifstream file("trains.txt");
    if (!file) return;
    
    int number, totalAC, totalSleeper, availAC, availSleeper;
    string name, source, dest;
    double acPrice, sleeperPrice;
    string line;
    
    while (getline(file, line)) 
    {
        size_t pos = 0;
        string token;
        int field = 0;
        
        while ((pos = line.find("|")) != string::npos) 
        {
            token = line.substr(0, pos);
            if (field == 0) number = stoi(token);
            else if (field == 1) name = token;
            else if (field == 2) source = token;
            else if (field == 3) dest = token;
            else if (field == 4) totalAC = stoi(token);
            else if (field == 5) totalSleeper = stoi(token);
            else if (field == 6) availAC = stoi(token);
            else if (field == 7) availSleeper = stoi(token);
            else if (field == 8) acPrice = stod(token);
            line.erase(0, pos + 1);
            field++;
        }
        sleeperPrice = stod(line);
        
        Train* newTrain = new Train(number, name, source, dest, totalAC, totalSleeper, acPrice, sleeperPrice);
        newTrain->availableACSeats = availAC;
        newTrain->availableSleeperSeats = availSleeper;
        
        if (trainListHead == NULL) 
        {
            trainListHead = newTrain;
        } 
        else 
        {
            Train* temp = trainListHead;
            while (temp->nextTrain != NULL) 
            {
                temp = temp->nextTrain;
            }
            temp->nextTrain = newTrain;
            newTrain->prevTrain = temp;
        }
    }
    file.close();
}


void RailwayReservationSystem::loadPassengersFromFile() 
{
    ifstream file("passengers.txt");
    if (!file) return;
    
    int ticketId, age, trainNum;
    string name, cnic, seatClass;
    string line;
    
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        int field = 0;
        
        while ((pos = line.find("|")) != string::npos) 
        {
            token = line.substr(0, pos);
            if (field == 0) {
                ticketId = stoi(token);
                if (ticketId > ticketCounter) ticketCounter = ticketId;
            }
            else if (field == 1) name = token;
            else if (field == 2) age = stoi(token);
            else if (field == 3) cnic = token;
            else if (field == 4) seatClass = token;
            line.erase(0, pos + 1);
            field++;
        }
        trainNum = stoi(line);
        
        Passenger* newPassenger = new Passenger(name, age, cnic, seatClass, ticketId, trainNum);
        
        if (passengerListHead == NULL) 
        {
            passengerListHead = newPassenger;
        } 
        else 
        {
            Passenger* temp = passengerListHead;
            while (temp->nextPassenger != NULL) 
            {
                temp = temp->nextPassenger;
            }
            temp->nextPassenger = newPassenger;
            newPassenger->prevPassenger = temp;
        }
    }
    file.close();
}

void RailwayReservationSystem::saveCancellationsToFile() 
{
    ofstream file("cancellations.txt", ios::app);
    if (cancelledStackTop != NULL) 
    {
        file << cancelledStackTop->ticketID << "|" << cancelledStackTop->passengerName << "|"
                << cancelledStackTop->trainNumber << "|" << cancelledStackTop->cancellationReason << "\n";
    }
    file.close();
}

void RailwayReservationSystem::savePassengersToFile() 
{
    ofstream file("passengers.txt");
    Passenger* temp = passengerListHead;
    while (temp != NULL) {
        file << temp->ticketID << "|" << temp->passengerName << "|" 
                << temp->passengerAge << "|" << temp->passengerCNIC << "|"
                << temp->seatClass << "|" << temp->trainNumber << "\n";
        temp = temp->nextPassenger;
    }
    file.close();
}

void RailwayReservationSystem::saveTrainsToFile() 
{
    ofstream file("trains.txt");
    Train* temp = trainListHead;
    while (temp != NULL) 
    {
        file << temp->trainNumber << "|" << temp->trainName << "|" 
                << temp->sourceStation << "|" << temp->destinationStation << "|"
                << temp->totalACSeats << "|" << temp->totalSleeperSeats << "|"
                << temp->availableACSeats << "|" << temp->availableSleeperSeats << "|"
                << temp->acFare << "|" << temp->sleeperFare << "\n";
        temp = temp->nextTrain;
    }
    file.close();
}

void RailwayReservationSystem::displayMainMenu() 
{
    int choice;
    
    while (true) 
    {
        cout << "\n";
        cout << "+========================================+\n";
        cout << "|        RAILWAY RESERVATION SYSTEM      |\n";
        cout << "+========================================+\n";
        cout << "1. View All Trains\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. View All Passengers\n";
        cout << "5. View Waiting List\n";
        cout << "6. View Cancelled Tickets\n";
        cout << "7. Admin Panel\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) 
        {
            case 1:
                displayAllTrains();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                displayAllPassengers();
                break;
            case 5:
                displayWaitingList();
                break;
            case 6:
                displayCancelledTickets();
                break;
            case 7:
                if (authenticateAdmin()) {
                    adminMenu();
                }
                break;
            case 8:
                cout << "\n Thank you for using Railway Reservation System!\n";
                return;
            default:
                cout << "\n Invalid choice! Please try again.\n";
        }
    }
}


bool RailwayReservationSystem::authenticateAdmin() 
{
    string username, password;
    cout << "+========================================+\n";
    cout << "|                ADMIN LOGIN             |\n";
    cout << "+========================================+\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    
    if (username == adminUsername && password == adminPassword) 
    {
        cout << "\nLogin Successful!\n";
        return true;
    } 
    else 
    {
        cout << "\nInvalid Credentials!\n";
        return false;
    }
}

void RailwayReservationSystem::adminMenu() 
{
    int choice;
    
    while (true) 
    {
        cout << "\n";
        cout << "+========================================+\n";
        cout << "|               ADMIN PANEL              |\n";
        cout << "+========================================+\n";
        cout << "1. Add New Train\n";
        cout << "2. View All Trains\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) 
        {
            case 1:
                addNewTrain();
                break;
            case 2:
                displayAllTrains();
                break;
            case 3:
                return;
            default:
                cout << "\n Invalid choice! Please try again.\n";
        }
    }
}