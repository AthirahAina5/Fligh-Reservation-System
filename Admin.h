#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef ADMIN_H
#define ADMIN_H

enum Gender {
  MALE,
  FEMALE
};

class Admin
{
    public:
        Admin();
        ~Admin();
        Admin(unsigned int aAdminID, std::string aPassword, std::string aName, unsigned int aAge, Gender aAdminGender);

        unsigned int getAdminID();
        void setAdminID(unsigned int aAdminID);
        std::string getPassword();
        void setPassword(std::string aPassword);
        std::string getName();
        void setName(std::string aName);
        unsigned int getAge();
        void setAge(unsigned int aAge);
        Gender getAdminGender();
        void setAdminGender(Gender aAdminGender);

    private:
        unsigned int adminID;
        std::string password;
        std::string name;
        unsigned int age;
        Gender adminGender;
};

#endif

#ifndef ADMINNODE_H
#define ADMINNODE_H
class AdminNode
{
    public:
        AdminNode();
        AdminNode(Admin a);
        ~AdminNode();

        Admin admin;
        AdminNode* left;
        AdminNode* right;
        int height;
};
#endif

#ifndef AVLADMINTREE_H
#define AVLADMINTREE_H
class AVLAdminTree {
    public:
        // Function to get the height of a AdminNode
        int getHeight(AdminNode* node);
        // Function to calculate the balance factor of a AdminNode
        int getBalanceFactor(AdminNode* node);
        // Function to update the height of a AdminNode
        void updateHeight(AdminNode* node);
        // Function to perform a right rotation for AdminNode
        AdminNode* rightRotate(AdminNode* y);
        // Function to perform a left rotation for AdminNode
        AdminNode* leftRotate(AdminNode* x);
        // Function to insert a AdminNode into the AVL tree
        AdminNode* insert(AdminNode* root, Admin admin);
        // Function to find the AdminNode with the minimum key in an AVL tree
        AdminNode* findMin(AdminNode* root);
        // Function to delete a AdminNode from the AVL tree
        AdminNode* deleteNode(AdminNode* root, int passengerID);
        // Function to search for a AdminNode with a given passengerID in the AVL tree
        AdminNode* search(AdminNode* root, int passengerID);
        // Function to print the AVL tree of AdminNodes in inorder traversal
        void inorderTraversal(AdminNode* root);
        // Function to delete the entire AVL tree of AdminNodes
        void deleteTree(AdminNode* root);
        // Function to save the AVL tree to a text file
        void saveToFile(AdminNode* root, std::ofstream& outputFile);
        // Function to load the AVL tree from a text file
        AdminNode* loadFromFile(std::ifstream& inputFile);
};

#endif


