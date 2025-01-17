#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef FLIGHT_H
#define FLIGHT_H

class Flight
{
    public:
        Flight();
        Flight(unsigned int aFlightNumber, std::string aName, std::string aDepartureLocation, std::string aArrivalLocation, std::string aDepartureTime, std::string aArrivalTime, unsigned int aAvailableSeats);
        ~Flight();
        unsigned int getFlightNumber();
        void setFlightNumber(unsigned int aFlightNumber);
        std::string getName();
        void setName(std::string aName);
        std::string getDepartureLocation();
        void setDepartureLocation(std::string aDepartureLocation);
        std::string getArrivalLocation();
        void setArrivalLocation(std::string aArrivalLocation);
        std::string getDepartureTime();
        void setDepartureTime(std::string aDepartureTime);
        std::string getArrivalTime();
        void setArrivalTime(std::string aArrivalTime);
        unsigned int getAvailableSeats();
        void setAvailableSeats(unsigned int aAvailableSeats);
        bool hasSeats();

    private:
        unsigned int flightNumber;
        std::string name;
        std::string departureLocation;
        std::string arrivalLocation;
        std::string departureTime;
        std::string arrivalTime;
        unsigned int availableSeats;
};

#endif

#ifndef FLIGHTNODE_H
#define FLIGHTNODE_H
class FlightNode
{
    public:
        FlightNode();
        FlightNode(Flight f);
        ~FlightNode();

        Flight flight;
        FlightNode* left;
        FlightNode* right;
        int height;
};
#endif

#ifndef AVLFLIGHTTREE_H
#define AVLFLIGHTTREE_H
class AVLFlightTree {
    public:
        // Function to get the height of a FlightNode
        int getHeight(FlightNode* node);
        // Function to calculate the balance factor of a FlightNode
        int getBalanceFactor(FlightNode* node);
        // Function to update the height of a FlightNode
        void updateHeight(FlightNode* node);
        // Function to perform a right rotation for FlightNode
        FlightNode* rightRotate(FlightNode* y);
        // Function to perform a left rotation for FlightNode
        FlightNode* leftRotate(FlightNode* x);
        // Function to insert a FlightNode into the AVL tree
        FlightNode* insert(FlightNode* root, Flight flight);
        // Function to find the FlightNode with the minimum key in an AVL tree
        FlightNode* findMin(FlightNode* root);
        // Function to delete a FlightNode from the AVL tree
        FlightNode* deleteNode(FlightNode* root, int flightNumber);
        // Function to search for a FlightNode with a given flightNumber in the AVL tree
        FlightNode* search(FlightNode* root, int flightNumber);
        // Function to print the AVL tree of FlightNodes in inorder traversal
        void inorderTraversal(FlightNode* root);
        // Function to delete the entire AVL tree of FlightNodes
        void deleteTree(FlightNode* root);
        // Function to save the AVL tree to a text file
        void saveToFile(FlightNode* root, std::ofstream& outputFile);
        // Function to load the AVL tree from a text file
        FlightNode* loadFromFile(std::ifstream& inputFile);
};
#endif
