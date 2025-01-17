#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger
{
    public:
        Passenger();
        ~Passenger();
        Passenger(unsigned int passengerID, std::string name, std::string icNumber, std::string phoneNumber, std::string email);

        unsigned int getPassengerID();
        void setPassengerID(unsigned int aPassengerID);
        std::string getName();
        void setName(std::string aName);
        std::string getICNumber();
        void setICNumber(std::string aICNumber);
        std::string getPhoneNumber();
        void setPhoneNumber(std::string aPhoneNumber);
        std::string getEmail();
        void setEmail(std::string aEmail);

    private:
        unsigned int passengerID;
        std::string name;
        std::string icNumber;
        std::string phoneNumber;
        std::string email;
};

#endif

#ifndef PASSENGERNODE_H
#define PASSENGERNODE_H
class PassengerNode
{
    public:
        PassengerNode();
        PassengerNode(Passenger p);
        ~PassengerNode();

        Passenger passenger;
        PassengerNode* left;
        PassengerNode* right;
        int height;
};
#endif

#ifndef AVLPASSENGERTREE_H
#define AVLPASSENGERTREE_H
class AVLPassengerTree {
    public:
        // Function to get the height of a PassengerNode
        int getHeight(PassengerNode* node);
        // Function to calculate the balance factor of a PassengerNode
        int getBalanceFactor(PassengerNode* node);
        // Function to update the height of a PassengerNode
        void updateHeight(PassengerNode* node);
        // Function to perform a right rotation for PassengerNode
        PassengerNode* rightRotate(PassengerNode* y);
        // Function to perform a left rotation for PassengerNode
        PassengerNode* leftRotate(PassengerNode* x);
        // Function to insert a PassengerNode into the AVL tree
        PassengerNode* insert(PassengerNode* root, Passenger passenger);
        // Function to find the PassengerNode with the minimum key in an AVL tree
        PassengerNode* findMin(PassengerNode* root);
        // Function to delete a PassengerNode from the AVL tree
        PassengerNode* deleteNode(PassengerNode* root, int passengerID);
        // Function to search for a PassengerNode with a given passengerID in the AVL tree
        PassengerNode* search(PassengerNode* root, int passengerID);
        // Function to print the AVL tree of PassengerNodes in inorder traversal
        void inorderTraversal(PassengerNode* root);
        // Function to delete the entire AVL tree of PassengerNodes
        void deleteTree(PassengerNode* root);
        // Function to save the AVL tree to a text file
        void saveToFile(PassengerNode* root, std::ofstream& outputFile);
        // Function to load the AVL tree from a text file
        PassengerNode* loadFromFile(std::ifstream& inputFile);
};

#endif

