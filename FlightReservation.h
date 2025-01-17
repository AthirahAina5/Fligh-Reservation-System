#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef FLIGHTRESERVATION_H
#define FLIGHTRESERVATION_H

class FlightReservation
{
    public:
        FlightReservation();
        ~FlightReservation();
        FlightReservation(unsigned int ticketID, unsigned int passengerID, unsigned int flightNumber, unsigned int seatID);

        unsigned int getTicketID();
        void setTicketID(unsigned int aTicketID);
        unsigned int getPassengerID();
        void setPassengerID(unsigned int aPassengerID);
        unsigned int getFlightNumber();
        void setFlightNumber(unsigned int aFlightNumber);
        unsigned int getSeatID();
        void setSeatID(unsigned int aSeatID);

    private:
        unsigned int ticketID;
        unsigned int passengerID;
        unsigned int flightNumber;
        unsigned int seatID;
};

#endif

#ifndef FLIGHTRESERVATIONNODE_H
#define FLIGHTRESERVATIONNODE_H

class FlightReservationNode {
    public:
        FlightReservationNode();
        FlightReservationNode(FlightReservation fr);
        ~FlightReservationNode();

        FlightReservation flightReservation;
        FlightReservationNode* left;
        FlightReservationNode* right;
        int height;
};
#endif

#ifndef AVLFLIGHTRESERVATIONTREE_H
#define AVLFLIGHTRESERVATIONTREE_H
class AVLFlightReservationTree {
    public:
        // Function to get the height of a FlightReservationNode
        int getHeight(FlightReservationNode* node);
        // Function to calculate the balance factor of a FlightReservationNode
        int getBalanceFactor(FlightReservationNode* node);
        // Function to update the height of a FlightReservationNode
        void updateHeight(FlightReservationNode* node);
        // Function to perform a right rotation for FlightReservationNode
        FlightReservationNode* rightRotate(FlightReservationNode* y);
        // Function to perform a left rotation for FlightReservationNode
        FlightReservationNode* leftRotate(FlightReservationNode* x);
        // Function to insert a FlightReservationNode into the AVL tree
        FlightReservationNode* insert(FlightReservationNode* root, FlightReservation flightReservation);
        // Function to find the FlightReservationNode with the minimum key in an AVL tree
        FlightReservationNode* findMin(FlightReservationNode* root);
        // Function to delete a FlightReservationNode from the AVL tree
        FlightReservationNode* deleteNode(FlightReservationNode* root, int ticketID);
        // Function to search for a FlightReservationNode with a given passengerID in the AVL tree
        FlightReservationNode* search(FlightReservationNode* root, int ticketID);
        // Function to print the AVL tree of FlightReservationNodes in inorder traversal
        void inorderTraversal(FlightReservationNode* root, int ticketID);
        // Function to delete the entire AVL tree of FlightReservationNodes
        void deleteTree(FlightReservationNode* root);
        // Function to save the AVL tree to a text file
        void saveToFile(FlightReservationNode* root, std::ofstream& outputFile);
        // Function to load the AVL tree from a text file
        FlightReservationNode* loadFromFile(std::ifstream& inputFile);
};

#endif


