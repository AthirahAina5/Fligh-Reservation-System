#include <iostream>
#include <chrono>
#include <thread>
#include <string.h>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "Flight.h"
#include "Passenger.h"
#include "Admin.h"
#include "FlightReservation.h"

void signalHandler(int signal);
void setInitialFonts();
bool adminLogin();
bool passengerLogin();
void printMenu();
void adminMenu();
void passengerMenu();
int loadData();
int saveData();
std::string generateTicketID();

void manageFlight();
void managePassenger();
void manageFlightReservation();
void manageAdmin();
void reserveTickets();
void cancelReservations();
void viewReservations();

AVLFlightTree avlFlightTree;
FlightNode* flightRoot = nullptr;

AVLPassengerTree avlPassengerTree;
PassengerNode* passengerRoot = nullptr;

AVLAdminTree avlAdminTree;
AdminNode* adminRoot = nullptr;

AVLFlightReservationTree avlFlightReservationTree;
FlightReservationNode* flightReservationRoot = nullptr;

unsigned int loggedInPassenderID;

int main()
{
    // Register signal handler
    std::signal(SIGINT, signalHandler);
    std::signal(SIGBREAK, signalHandler);

    // Set the color
    setInitialFonts();

    // Import data from files in the data folder
    std::cout << "Loading...\n\n";
    if (loadData() == 1) {
        std::cout << "All of the data has been loaded.\n";
    } else {
        std::cout << "Failed to open the files located in data folder.\n";
    }

    // std::this_thread::sleep_for(std::chrono::seconds(10));

    // Print the main menu
    printMenu();
    //adminMenu();


    return 0;
}

// Signal handler function
void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGBREAK) {
        saveData();
        exit(signal);
    }
}

void setInitialFonts() {
    // Change the color of terminal
    system("Color 03");
}

bool adminLogin() {
    system("CLS");

    unsigned int adminID;
    std::string adminPassword;

    std::cout << "\tAdmin Login";
    std::cout << "\n\nEnter Admin ID: ";
    std::cin >> adminID;

    while (true)
    {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have entered wrong input. Enter a valid Admin ID: ";
            std::cin >> adminID;
        }
        if (!std::cin.fail()) {
            break;
        }
    }

    std::cin.ignore();

    std::cout << "Enter Admin Password: ";
    getline(std::cin, adminPassword);

    AdminNode* foundAdmin = avlAdminTree.search(adminRoot, adminID);

    if (foundAdmin && foundAdmin->admin.getPassword() == adminPassword) {
        return true;
    }

    return false;
}

bool passengerLogin() {
    system("CLS");

    unsigned int passengerID;
    std::string passengerICNumber;

    std::cout << "\tPassenger Login";
    std::cout << "\n\nEnter Passenger ID: ";
    std::cin >> passengerID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true)
    {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
            std::cin >> passengerID;
        }

        if (!std::cin.fail()) {
            break;
        }
    }

    std::cout << "Enter Passenger IC Number: ";
    getline(std::cin, passengerICNumber);

    PassengerNode* foundPassenger = avlPassengerTree.search(passengerRoot, passengerID);

    if (foundPassenger && foundPassenger->passenger.getICNumber() == passengerICNumber) {
        loggedInPassenderID = passengerID;
        return true;
    }

    return false;
}

void printMenu() {
    system("CLS");
    int choice = -1, retry = 0;
    int maxRow = 15, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 15) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Flight Reservation System \t\t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Admin\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [2] Passenger\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {

        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        switch (choice) {//Perform action based on user input
        case 1: {
            do {
              if (adminLogin()) {
                    adminMenu();
                }
                else {

                    std::cout << "\n\n>> Do you want to try again? (1 - Yes, 2 - No): ";
                    std::cin >> retry;

                }

                while (true)
                {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Please enter (1 - Yes, 2 - No): ";
                        std::cin >> retry;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }
            } while (retry == 1);
        }
            break;
        case 2: {

            do {
              if (passengerLogin()) {
                    passengerMenu();
              }
              else {
                    std::cout << "\n\n>> Do you want to try again? (1 - Yes, 2 - No): ";
                    std::cin >> retry;
              }

              while (true)
              {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Please enter (1 - Yes, 2 - No): ";
                        std::cin >> retry;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
              }
            } while (retry == 1);

        }
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);
                flightReservationRoot = nullptr;
                avlFlightReservationTree.deleteTree(flightReservationRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }

        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2);
}

int loadData() {
    // Load the AVL tree from the text file
    std::ifstream inputFlightFile("./data/flight_data.txt");
    std::ifstream inputPassengerFile("./data/passenger_data.txt");
    std::ifstream inputAdminFile("./data/admin_data.txt");
    std::ifstream inputFlightReservationFile("./data/flight_reservation_data.txt");
    int error = -1;

    if (inputFlightFile.is_open() && inputPassengerFile.is_open() && inputAdminFile.is_open() && inputFlightReservationFile.is_open()) {
        flightRoot = avlFlightTree.loadFromFile(inputFlightFile);
        inputFlightFile.close();

        avlFlightTree.inorderTraversal(flightRoot);

        passengerRoot = avlPassengerTree.loadFromFile(inputPassengerFile);
        inputPassengerFile.close();

        avlPassengerTree.inorderTraversal(passengerRoot);

        adminRoot = avlAdminTree.loadFromFile(inputAdminFile);
        inputAdminFile.close();

        avlAdminTree.inorderTraversal(adminRoot);

        flightReservationRoot = avlFlightReservationTree.loadFromFile(inputFlightReservationFile);
        inputFlightReservationFile.close();

        avlFlightReservationTree.inorderTraversal(flightReservationRoot, -1);

        error = 1;
    } else {
        error = -1;
    }

    return error;
}

int saveData() {
    // Save the AVL tree to a text file
    std::ofstream outputFlightFile("./data/flight_data.txt");
    std::ofstream outputPassengerFile("./data/passenger_data.txt");
    std::ofstream outputAdminFile("./data/admin_data.txt");
    std::ofstream outputFlightReservationFile("./data/flight_reservation_data.txt");
    int error = -1;

    if (outputFlightFile.is_open() && outputPassengerFile.is_open() && outputAdminFile.is_open() && outputFlightReservationFile.is_open()) {
        avlFlightTree.saveToFile(flightRoot, outputFlightFile);
        outputFlightFile.close();

        avlPassengerTree.saveToFile(passengerRoot, outputPassengerFile);
        outputPassengerFile.close();

        avlAdminTree.saveToFile(adminRoot, outputAdminFile);
        outputAdminFile.close();

        avlFlightReservationTree.saveToFile(flightReservationRoot, outputFlightReservationFile);
        outputFlightReservationFile.close();

        error = 1;
    } else {
        error = -1;
    }
    return error;
}

void adminMenu() {
    system("CLS");
    int choice = -1;
    int maxRow = 13, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 13) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Subject Registration System \t\t\t\t#\n";
            std::cout << "#\t\t\t  Admin Menu \t\t\t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Manage Flight Details\t\t\t\t#\n";
            std::cout << "#\t\t  [2] Manage Passenger Details\t\t\t\t#\n";
            std::cout << "#\t\t  [3] Manage Flight Reservation Details\t\t\t#\n";
            std::cout << "#\t\t  [4] Manage Admin Details\t\t\t\t#\n";
            std::cout << "#\t\t  [5] Admin Menu\t\t\t\t\t#\n";
            std::cout << "#\t\t  [6] Main Menu\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {
        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        switch (choice) {//Perform action based on user input
        case 1:
            manageFlight();
            break;
        case 2:
            managePassenger();
            break;
        case 3:
            manageFlightReservation();
            break;
        case 4:
            manageAdmin();
            break;
        case 5:
            adminMenu();
            break;
        case 6:
            printMenu();
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);
                flightReservationRoot = nullptr;
                avlFlightReservationTree.deleteTree(flightReservationRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }
        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10 && choice != 11);
}

void manageFlight() {
    system("CLS");
    int choice = -1;
    int maxRow = 15, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 15) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Flight Reservation System \t\t\t\t#\n";
            std::cout << "#\t\t   Admin Menu (Manage Flight)\t\t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Add Flight Details\t\t\t\t#\n";
            std::cout << "#\t\t  [2] Edit Flight Details\t\t\t\t#\n";
            std::cout << "#\t\t  [3] Search Flight Details\t\t\t\t#\n";
            std::cout << "#\t\t  [4] Delete Flight Details\t\t\t\t#\n";
            std::cout << "#\t\t  [5] Admin Menu\t\t\t\t\t#\n";
            std::cout << "#\t\t  [6] Main Menu\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {
        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        unsigned int flightNumber, availableSeats;
        std::string flightName, departureLocation, arrivalLocation, departureTime, arrivalTime;
        Flight flight1;

        switch (choice) {//Perform action based on user input
        case 1: {

            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tAdd Flight Details\n" << std::endl;

            std::cout << "Enter Flight Number: ";
            std::cin >> flightNumber;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
                    std::cin >> flightNumber;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            std::cout << "Enter Flight Name: ";
            getline(std::cin, flightName);//Input choice

            std::cout << "Enter Departure Location: ";
            getline(std::cin, departureLocation);//Input choice

            std::cout << "Enter Arrival Location: ";
            getline(std::cin, arrivalLocation);

            std::cout << "Enter Departure Time (Example: 2023-02-03,21:30:00): ";
            getline(std::cin, departureTime);

            std::cout << "Enter Arrival Time (Example: 2023-02-03,21:30:00): ";
            getline(std::cin, arrivalTime);

            std::cout << "Enter Available Seats: ";
            std::cin >> availableSeats;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Available Seats: ";
                    std::cin >> availableSeats;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            flight1.setFlightNumber(flightNumber);
            flight1.setName(flightName);
            flight1.setDepartureLocation(departureLocation);
            flight1.setArrivalLocation(arrivalLocation);
            flight1.setDepartureTime(departureTime);
            flight1.setArrivalTime(arrivalTime);
            flight1.setAvailableSeats(availableSeats);

            // std::cout << "Arrival Time: " << flight1.getArrivalTime() << "\n";

            flightRoot = avlFlightTree.insert(flightRoot, flight1);
        }
              break;
        case 2: {
            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tUpdate Flight Details\n" << std::endl;

            std::cout << "Enter Flight Number To Update: ";
            std::cin >> flightNumber;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
                    std::cin >> flightNumber;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            FlightNode* foundFlight = avlFlightTree.search(flightRoot, flightNumber);

            if (foundFlight) {
                std::cout << "Enter Flight Name: ";
                getline(std::cin, flightName);

                std::cout << "Enter Departure Location: ";
                getline(std::cin, departureLocation);

                std::cout << "Enter Arrival Location: ";
                getline(std::cin, arrivalLocation);

                std::cout << "Enter Departure Time (Example: 2023-02-03 21:30:00): ";
                getline(std::cin, departureTime);

                std::cout << "Enter Arrival Time (Example: 2023-02-03 21:30:00): ";
                getline(std::cin, arrivalTime);

                std::cout << "Enter Available Seats: ";
                std::cin >> availableSeats;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true)
                {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Enter a valid Available Seats: ";
                        std::cin >> availableSeats;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }

                foundFlight->flight.setName(flightName);
                foundFlight->flight.setDepartureLocation(departureLocation);
                foundFlight->flight.setArrivalLocation(arrivalLocation);
                foundFlight->flight.setDepartureTime(departureTime);
                foundFlight->flight.setArrivalTime(arrivalTime);
                foundFlight->flight.setAvailableSeats(availableSeats);

                std::cout << "\n\n>> Flight data has been updated successfully" << std::endl;
            } else {
                std::cout << "\n\n>> Flight with number " << flightNumber << " not found!\n";
            }

        }
              break;
        case 3: {
            system("CLS");
            std::cout << "\tSearch Flight Details" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nEnter Flight Number: ";
            std::cin >> flightNumber;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
                    std::cin >> flightNumber;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            FlightNode* foundFlight = avlFlightTree.search(flightRoot, flightNumber);

            if (foundFlight) {
                std::cout << "\n\n\t\t\t**Flight Data**";
                std::cout << "\n#################################################################################################\n";
                std::cout << "\nFlight Number Flight Name Departure Location Arrival Location Departure Time\tArrival Time\tAvailable Seats\n";
                std::cout << foundFlight->flight.getFlightNumber() << "\t" << foundFlight->flight.getName() << "  " << foundFlight->flight.getDepartureLocation() << "" << foundFlight->flight.getArrivalLocation() << " " << foundFlight->flight.getDepartureTime() << "\t\t" << foundFlight->flight.getArrivalTime() << " " << foundFlight->flight.getAvailableSeats();
                std::cout << "\n#################################################################################################\n";
            } else {
                std::cout << "\n>> Error: Flight with number " << flightNumber << " not found!\n";
            }
        }
              break;
        case 4: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            system("CLS");
            std::cout << "\tDelete Flight Details" << std::endl;

            std::cout << "\nEnter Flight Number To Delete: ";
            std::cin >> flightNumber;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
                    std::cin >> flightNumber;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            flightRoot = avlFlightTree.deleteNode(flightRoot, flightNumber);
        }
              break;
        case 5:
            adminMenu();
            break;
        case 6:
            printMenu();
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);
                flightReservationRoot = nullptr;
                avlFlightReservationTree.deleteTree(flightReservationRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }
        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);

    std::cout << "\n\n";
    system("PAUSE");
    adminMenu();
}

void managePassenger() {
    system("CLS");
    int choice = -1;
    int maxRow = 15, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 15) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Flight Reservation System \t\t\t\t#\n";
            std::cout << "#\t\t   Admin Menu (Manage Passenger)\t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Add Passenger Details\t\t\t\t#\n";
            std::cout << "#\t\t  [2] Edit Passenger Details\t\t\t\t#\n";
            std::cout << "#\t\t  [3] Search Passenger Details\t\t\t\t#\n";
            std::cout << "#\t\t  [4] Delete Passenger Details\t\t\t\t#\n";
            std::cout << "#\t\t  [5] Admin Menu\t\t\t\t\t#\n";
            std::cout << "#\t\t  [6] Main Menu\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {
        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        unsigned int passengerID;
        std::string name, icNumber, phoneNumber, email;
        Passenger passenger1;

        switch (choice) {//Perform action based on user input
        case 1: {

            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tAdd Passenger Details\n" << std::endl;

            std::cout << "Enter Passenger ID: ";
            std::cin >> passengerID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
                    std::cin >> passengerID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            std::cout << "Enter Name: ";
            getline(std::cin, name);//Input choice

            std::cout << "Enter IC Number: ";
            getline(std::cin, icNumber);//Input choice

            std::cout << "Enter Phone Number: ";
            getline(std::cin, phoneNumber);

            std::cout << "Enter Email: ";
            getline(std::cin, email);

            passenger1.setPassengerID(passengerID);
            passenger1.setName(name);
            passenger1.setICNumber(icNumber);
            passenger1.setPhoneNumber(phoneNumber);
            passenger1.setEmail(email);

            passengerRoot = avlPassengerTree.insert(passengerRoot, passenger1);
        }
              break;
        case 2: {
            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tUpdate Passenger Details\n" << std::endl;

            std::cout << "Enter Passenger ID To Update: ";
            std::cin >> passengerID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
                    std::cin >> passengerID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            PassengerNode* foundPassenger = avlPassengerTree.search(passengerRoot, passengerID);

            if (foundPassenger) {
                std::cout << "Enter Name: ";
                getline(std::cin, name);

                std::cout << "Enter IC Number: ";
                getline(std::cin, icNumber);

                std::cout << "Enter Phone Number: ";
                getline(std::cin, phoneNumber);

                std::cout << "Enter Email: ";
                getline(std::cin, email);

                foundPassenger->passenger.setName(name);
                foundPassenger->passenger.setICNumber(icNumber);
                foundPassenger->passenger.setPhoneNumber(phoneNumber);
                foundPassenger->passenger.setEmail(email);

                std::cout << "\n\n>> Passenger data has been updated successfully" << std::endl;
            } else {
                std::cout << "\n\n>> Passenger with ID " << passengerID << " not found!\n";
            }

        }
              break;
        case 3: {
            system("CLS");
            std::cout << "\tSearch Passenger Details" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nEnter Passenger ID: ";
            std::cin >> passengerID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
                    std::cin >> passengerID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            PassengerNode* foundPassenger = avlPassengerTree.search(passengerRoot, passengerID);

            if (foundPassenger) {
                std::cout << "\n\n\t\t\t**Passenger Data**";
                std::cout << "\n#################################################################################################\n";
                std::cout << "\nPassenger ID\tName\tIC Number\tPhone Number\tEmail\n";
                std::cout << foundPassenger->passenger.getPassengerID() << "\t" << foundPassenger->passenger.getName() << "  " << foundPassenger->passenger.getICNumber() << " " << foundPassenger->passenger.getPhoneNumber() << " " << foundPassenger->passenger.getEmail();
                std::cout << "\n#################################################################################################\n";
            } else {
                std::cout << "\n>> Error: Passenger with ID " << passengerID << " not found!\n";
            }
        }
              break;
        case 4: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            system("CLS");
            std::cout << "\tDelete Passenger Details" << std::endl;

            std::cout << "\nEnter Passenger ID To Delete: ";
            std::cin >> passengerID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
                    std::cin >> passengerID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            passengerRoot = avlPassengerTree.deleteNode(passengerRoot, passengerID);
        }
              break;
        case 5:
            adminMenu();
            break;
        case 6:
            printMenu();
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }
        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);

    std::cout << "\n\n";
    system("PAUSE");
    adminMenu();
}

std::string generateTicketID() {
    const std::string digits = "123456789";
    const int length = 7;
    std::string ticketID;

    // Seed the random number generator
    std::srand(std::time(nullptr));

    for (int i = 0; i < length; ++i) {
        int randomIndex = std::rand() % digits.length();
        ticketID += digits[randomIndex];
    }

    return ticketID;
}

void manageFlightReservation() {
    system("CLS");
    int choice = -1;
    int maxRow = 15, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 15) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Flight Reservation System \t\t\t\t#\n";
            std::cout << "#\t\tAdmin Menu (Manage Flight Reservation) \t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Add Flight Reservation Details\t\t\t#\n";
            std::cout << "#\t\t  [2] Edit Flight Reservation Details\t\t\t#\n";
            std::cout << "#\t\t  [3] Search Flight Reservation Details\t\t\t#\n";
            std::cout << "#\t\t  [4] Delete Flight Reservation Details\t\t\t#\n";
            std::cout << "#\t\t  [5] Admin Menu\t\t\t\t\t#\n";
            std::cout << "#\t\t  [6] Main Menu\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {
        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        unsigned int ticketID, passengerID, flightNumber, seatID;
        FlightReservation flightReservation1;

        switch (choice) {//Perform action based on user input
        case 1: {

            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tAdd Flight Reservation Details\n" << std::endl;

            std::cout << "\n\t\t\t**Passenger Data**";
            std::cout << "\n#################################################################################################\n";
            std::cout << "\nPassenger ID\tName\tIC Number\tPhone Number\tEmail\n";
            avlPassengerTree.inorderTraversal(passengerRoot);
            std::cout << "\n#################################################################################################\n\n";

            std::cout << "\n\n\t\t\t\t\t**Flight Data**";
            std::cout << "\n##################################################################################################################\n";
            std::cout << "\nFlight Number   Flight Name   Departure Location   Arrival Location   Departure Time\tArrival Time\tAvailable Seats\n";
            avlFlightTree.inorderTraversal(flightRoot);
            std::cout << "\n##################################################################################################################\n";

            ticketID = std::stoi(generateTicketID());

            std::cout << "\nYour Ticket ID: " << ticketID << "\n";

            std::cout << "Enter Passenger ID: ";
            std::cin >> passengerID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
                    std::cin >> passengerID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            std::cout << "Enter Flight Number: ";
            std::cin >> flightNumber;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
                    std::cin >> flightNumber;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            std::cout << "Enter Seat ID: ";
            std::cin >> seatID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Seat ID: ";
                    std::cin >> seatID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            FlightNode* foundFlight = avlFlightTree.search(flightRoot, flightNumber);

            if (foundFlight) {
                if (foundFlight->flight.hasSeats()) {
                    flightReservation1.setTicketID(ticketID);
                    flightReservation1.setPassengerID(passengerID);
                    flightReservation1.setFlightNumber(flightNumber);
                    flightReservation1.setSeatID(seatID);

                    flightReservationRoot = avlFlightReservationTree.insert(flightReservationRoot, flightReservation1);
                    foundFlight->flight.setAvailableSeats(foundFlight->flight.getAvailableSeats() - 1);
                } else {
                    std::cout << "\n>> Error: Seats in this flight are full!\n";
                }
            } else {
                std::cout << "\n>> Error: Flight with Flight ID " << flightNumber << " not found!\n";
            }
        }
              break;
        case 2: {
            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tUpdate Flight Reservation Details\n" << std::endl;

            std::cout << "Enter Flight Reservation ID To Update: ";
            std::cin >> ticketID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Ticket ID: ";
                    std::cin >> ticketID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            FlightReservationNode* foundFlightReservation = avlFlightReservationTree.search(flightReservationRoot, ticketID);

            if (foundFlightReservation) {
                std::cout << "Enter Passenger ID: ";
                std::cin >> passengerID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true)
                {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Enter a valid Passenger ID: ";
                        std::cin >> passengerID;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }

                std::cout << "Enter Flight Number: ";
                std::cin >> flightNumber;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true)
                {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
                        std::cin >> flightNumber;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }

                std::cout << "Enter Seat ID: ";
                std::cin >> seatID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true)
                {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Enter a valid Seat ID: ";
                        std::cin >> seatID;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }

                foundFlightReservation->flightReservation.setPassengerID(passengerID);
                foundFlightReservation->flightReservation.setFlightNumber(flightNumber);
                foundFlightReservation->flightReservation.setSeatID(seatID);

                std::cout << "\n\n>> Flight Reservation data has been updated successfully" << std::endl;
            } else {
                std::cout << "\n\n>> Flight Reservation with Ticket ID " << passengerID << " not found!\n";
            }

        }
              break;
        case 3: {
            system("CLS");
            std::cout << "\tSearch Flight Reservation Details" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nEnter Ticket ID: ";
            std::cin >> ticketID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Ticket ID: ";
                    std::cin >> ticketID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            FlightReservationNode* foundFlightReservation = avlFlightReservationTree.search(flightReservationRoot, ticketID);

            if (foundFlightReservation) {
                std::cout << "\n\n\t\t\t**Flight Reservation Data**";
                std::cout << "\n#################################################################################################\n";
                std::cout << "\nTicket ID\tPassenger ID\tFlight Number\tSeat ID\n";
                std::cout << foundFlightReservation->flightReservation.getTicketID() << " " << foundFlightReservation->flightReservation.getPassengerID() << "  " << foundFlightReservation->flightReservation.getFlightNumber() << " " << foundFlightReservation->flightReservation.getSeatID();
                std::cout << "\n#################################################################################################\n";
            } else {
                std::cout << "\n>> Error: Flight Reservation with Ticket ID " << ticketID << " not found!\n";
            }
        }
              break;
        case 4: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            system("CLS");
            std::cout << "\tDelete Flight Reservation Details" << std::endl;

            std::cout << "\nEnter Ticket ID To Delete: ";
            std::cin >> ticketID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Ticket ID: ";
                    std::cin >> ticketID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            flightReservationRoot = avlFlightReservationTree.deleteNode(flightReservationRoot, ticketID);
        }
              break;
        case 5:
            adminMenu();
            break;
        case 6:
            printMenu();
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);
                flightReservationRoot = nullptr;
                avlFlightReservationTree.deleteTree(flightReservationRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }
        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);

    std::cout << "\n\n";
    system("PAUSE");
    adminMenu();
}

void manageAdmin() {
    system("CLS");
    int choice = -1;
    int maxRow = 15, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 15) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Flight Reservation System \t\t\t\t#\n";
            std::cout << "#\t\t  Admin Menu (Manage Admin)\t\t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Add Admin Details\t\t\t\t\t#\n";
            std::cout << "#\t\t  [2] Edit Admin Details\t\t\t\t#\n";
            std::cout << "#\t\t  [3] Search Admin Details\t\t\t\t#\n";
            std::cout << "#\t\t  [4] Delete Admin Details\t\t\t\t#\n";
            std::cout << "#\t\t  [5] Admin Menu\t\t\t\t\t#\n";
            std::cout << "#\t\t  [6] Main Menu\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {
        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        unsigned int adminID, age, gender;
        std::string password, name;
        Admin admin1;

        switch (choice) {//Perform action based on user input
        case 1: {

            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tAdd Admin Details\n" << std::endl;

            std::cout << "Enter Admin ID: ";
            std::cin >> adminID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Admin ID: ";
                    std::cin >> adminID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            std::cout << "Enter Name: ";
            getline(std::cin, name);//Input choice

            std::cout << "Enter Password: ";
            getline(std::cin, password);//Input choice

            std::cout << "Enter Age: ";
            std::cin >> age;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Age: ";
                    std::cin >> age;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            std::cout << "Enter Gender (1 - MALE, 2 - FEMALE): ";
            std::cin >> gender;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail() && gender != 1 && gender != 2) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Gender: ";
                    std::cin >> gender;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            admin1.setAdminID(adminID);
            admin1.setPassword(password);
            admin1.setName(name);

            if (gender == 1) {
                admin1.setAdminGender(MALE);
            } else {
                admin1.setAdminGender(FEMALE);
            }

            adminRoot = avlAdminTree.insert(adminRoot, admin1);
        }
              break;
        case 2: {
            system("CLS");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\tUpdate Admin Details\n" << std::endl;

            std::cout << "Enter Admin ID To Update: ";
            std::cin >> adminID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Admin ID: ";
                    std::cin >> adminID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            AdminNode* foundAdmin = avlAdminTree.search(adminRoot, adminID);

            if (foundAdmin) {
                std::cout << "Enter Password: ";
                getline(std::cin, password);

                std::cout << "Enter Name: ";
                getline(std::cin, name);

                std::cout << "Enter Age: ";
                std::cin >> age;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true)
                {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Enter a valid Age: ";
                        std::cin >> age;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }

                std::cout << "Enter Gender (1 - MALE, 2 - FEMALE): ";
                std::cin >> gender;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true)
                {
                    if (std::cin.fail() && gender != 1 && gender != 2) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "You have entered wrong input. Enter a valid Gender: ";
                        std::cin >> gender;
                    }
                    if (!std::cin.fail()) {
                        break;
                    }
                }

                foundAdmin->admin.setPassword(password);
                foundAdmin->admin.setName(name);
                foundAdmin->admin.setAge(age);

                if (gender == 1) {
                    foundAdmin->admin.setAdminGender(MALE);
                } else {
                    foundAdmin->admin.setAdminGender(FEMALE);
                }

                std::cout << "\n\n>> Admin data has been updated successfully" << std::endl;
            } else {
                std::cout << "\n\n>> Admin with ID " << adminID << " not found!\n";
            }

        }
              break;
        case 3: {
            system("CLS");
            std::cout << "\tSearch Admin Details" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nEnter Admin ID: ";
            std::cin >> adminID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Admin ID: ";
                    std::cin >> adminID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            AdminNode* foundAdmin = avlAdminTree.search(adminRoot, adminID);
            std::string genderDisplay;

            if (foundAdmin) {
                std::cout << "\n\n\t\t\t**Admin Data**";
                std::cout << "\n#################################################################################################\n";
                std::cout << "\nAdmin ID Name\tAge\tGender\n";

                if (foundAdmin->admin.getAdminGender() == 0) {
                    genderDisplay = "MALE";
                } else {
                    genderDisplay = "FEMALE";
                }

                std::cout << foundAdmin->admin.getAdminID() << "\t" << foundAdmin->admin.getName() << "\t" << foundAdmin->admin.getAge() << "\t" << genderDisplay;
                std::cout << "\n#################################################################################################\n";
            } else {
                std::cout << "\n>> Error: Admin with ID " << adminID << " not found!\n";
            }
        }
              break;
        case 4: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            system("CLS");
            std::cout << "\tDelete Admin Details" << std::endl;

            std::cout << "\nEnter Admin ID To Delete: ";
            std::cin >> adminID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true)
            {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You have entered wrong input. Enter a valid Admin ID: ";
                    std::cin >> adminID;
                }
                if (!std::cin.fail()) {
                    break;
                }
            }

            adminRoot = avlAdminTree.deleteNode(adminRoot, adminID);
        }
              break;
        case 5:
            adminMenu();
            break;
        case 6:
            printMenu();
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);
                flightReservationRoot = nullptr;
                avlFlightReservationTree.deleteTree(flightReservationRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }
        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);

    std::cout << "\n\n";
    system("PAUSE");
    adminMenu();
}

void passengerMenu() {
    system("CLS");
    int choice = -1;
    int maxRow = 15, row = 1;//Declare variables
    for (row == 1; row <= maxRow; row++)//For loop to print the contents
    {
        if (row == 1 || row == 15) {
            std::cout << "#########################################################################\n";
        }
        else if (row == 3) {
            std::cout << "#\t\t  Subject Registration System \t\t\t\t#\n";
            std::cout << "#\t\t\t  Passenger Menu \t\t\t\t#\n";
        }
        else if (row == 7) {
            std::cout << "#\t\t  [1] Reserve Tickets\t\t\t\t\t#\n";
            std::cout << "#\t\t  [2] Cancel Reservations\t\t\t\t#\n";
            std::cout << "#\t\t  [3] View Reservations\t\t\t\t\t#\n";
            std::cout << "#\t\t  [4] Passenger Menu\t\t\t\t\t#\n";
            std::cout << "#\t\t  [5] Main Menu\t\t\t\t\t\t#\n";
            std::cout << "#\t\t  [0] Exit\t\t\t\t\t\t#\n";
        }
        else {
            std::cout << "#\t\t\t\t\t\t\t\t\t#\n";
        }
    }

    do {
        std::cout << "\nEnter your choice >>> ";
        std::cin >> choice;//Input choice

        while (true)
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You have entered wrong input. Enter a valid input: ";
                std::cin >> choice;
            }
            if (!std::cin.fail()) {
                break;
            }
        }

        switch (choice) {//Perform action based on user input
        case 1:
            reserveTickets();
            break;
        case 2:
            cancelReservations();
            break;
        case 3:
            viewReservations();
            break;
        case 4:
            passengerMenu();
            break;
        case 5:
            printMenu();
            break;
        case 0:
            if (saveData() == 1) {
                std::cout << "Data saved in files located in data folder.\n";

                flightRoot = nullptr;
                avlFlightTree.deleteTree(flightRoot);
                passengerRoot = nullptr;
                avlPassengerTree.deleteTree(passengerRoot);
                adminRoot = nullptr;
                avlAdminTree.deleteTree(adminRoot);
                flightReservationRoot = nullptr;
                avlFlightReservationTree.deleteTree(flightReservationRoot);

                exit(0);
                break;
            } else {
                std::cout << "Failed to open the files located in data folder.\n";
            }
        default:
            choice = -1;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
}

void reserveTickets() {
    system("CLS");
    int choice = -1;

    unsigned int ticketID, passengerID, flightNumber, seatID;
    FlightReservation flightReservation1;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\tReserve Tickets\n" << std::endl;

    std::cout << "\n\n\t\t\t\t\t**Flight Data**";
    std::cout << "\n##################################################################################################################\n";
    std::cout << "\nFlight Number   Flight Name   Departure Location   Arrival Location   Departure Time\tArrival Time\tAvailable Seats\n";
    avlFlightTree.inorderTraversal(flightRoot);
    std::cout << "\n##################################################################################################################\n";

    ticketID = std::stoi(generateTicketID());
    passengerID = loggedInPassenderID;

    std::cout << "\nYour Ticket ID: " << ticketID << "\n";

    std::cout << "Enter Flight Number: ";
    std::cin >> flightNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true)
    {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have entered wrong input. Enter a valid Flight Number: ";
            std::cin >> flightNumber;
        }
        if (!std::cin.fail()) {
            break;
        }
    }

    std::cout << "Enter Seat ID: ";
    std::cin >> seatID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true)
    {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have entered wrong input. Enter a valid Seat ID: ";
            std::cin >> seatID;
        }
        if (!std::cin.fail()) {
            break;
        }
    }

    FlightNode* foundFlight = avlFlightTree.search(flightRoot, flightNumber);

    if (foundFlight) {
        if (foundFlight->flight.hasSeats()) {
            flightReservation1.setTicketID(ticketID);
            flightReservation1.setPassengerID(passengerID);
            flightReservation1.setFlightNumber(flightNumber);
            flightReservation1.setSeatID(seatID);

            flightReservationRoot = avlFlightReservationTree.insert(flightReservationRoot, flightReservation1);
            foundFlight->flight.setAvailableSeats(foundFlight->flight.getAvailableSeats() - 1);
        } else {
            std::cout << "\n>> Error: Seats in this flight are full!\n";
        }
    } else {
        std::cout << "\n>> Error: Flight with Flight ID " << flightNumber << " not found!\n";
    }

    std::cout << "\n\n";
    system("PAUSE");
    passengerMenu();
}

void cancelReservations() {
    system("CLS");
    int choice = -1;

    unsigned int ticketID, passengerID, flightNumber, seatID;
    FlightReservation flightReservation1;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\tCancel Reservations\n" << std::endl;

    std::cout << "\nEnter Ticket ID To Delete: ";
    std::cin >> ticketID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true)
    {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have entered wrong input. Enter a valid Ticket ID: ";
            std::cin >> ticketID;
        }
        if (!std::cin.fail()) {
            break;
        }
    }

    flightReservationRoot = avlFlightReservationTree.deleteNode(flightReservationRoot, ticketID);

    std::cout << "\n\n";
    system("PAUSE");
    passengerMenu();
}

void viewReservations() {
    system("CLS");
    int choice = -1;

    unsigned int ticketID, passengerID, flightNumber, seatID;
    FlightReservation flightReservation1;

    passengerID = loggedInPassenderID;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\tYour Bookings\n" << std::endl;

    std::cout << "\n\n\t\t\t**Flight Reservation Data**";
    std::cout << "\n################################################################################\n";
    std::cout << "\nTicket ID\tFlight Number\tSeat ID\n";
    avlFlightReservationTree.inorderTraversal(flightReservationRoot, 1);
    std::cout << "\n################################################################################\n";

    std::cout << "\n\n";
    system("PAUSE");
    passengerMenu();
}

