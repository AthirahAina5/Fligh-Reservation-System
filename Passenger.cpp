#include "Passenger.h"

Passenger::Passenger() {
    setPassengerID(0);
    setName("");
    setICNumber("");
    setPhoneNumber("");
    setEmail("");
}

Passenger::~Passenger() {    }

Passenger::Passenger(unsigned int aPassengerID, std::string aName, std::string aICNumber, std::string aPhoneNumber, std::string aEmail) {
    setPassengerID(aPassengerID);
    setName(aName);
    setICNumber(aICNumber);
    setPhoneNumber(aPhoneNumber);
    setEmail(aEmail);
}

unsigned int Passenger::getPassengerID() {
    return passengerID;
}

void Passenger::setPassengerID(unsigned int aPassengerID) {
    passengerID = aPassengerID;
}

std::string Passenger::getName() {
    return name;
}

void Passenger::setName(std::string aName) {
    name = aName;
}

std::string Passenger::getICNumber() {
    return icNumber;
}

void Passenger::setICNumber(std::string aICNumber) {
    icNumber = aICNumber;
}

std::string Passenger::getPhoneNumber() {
    return phoneNumber;
}

void Passenger::setPhoneNumber(std::string aPhoneNumber) {
    phoneNumber = aPhoneNumber;
}

std::string Passenger::getEmail() {
    return email;
}

void Passenger::setEmail(std::string aEmail) {
    email = aEmail;
}

PassengerNode::PassengerNode() {    }

PassengerNode::~PassengerNode() {
    delete left;
    delete right;
}

PassengerNode::PassengerNode(Passenger p) {
    passenger = p;
    left = nullptr;
    right = nullptr;
    height = 1;
}

int AVLPassengerTree::getHeight(PassengerNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLPassengerTree::getBalanceFactor(PassengerNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLPassengerTree::updateHeight(PassengerNode* node) {
    if (node == nullptr)
        return;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

PassengerNode* AVLPassengerTree::rightRotate(PassengerNode* y) {
    PassengerNode* x = y->left;
    PassengerNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

PassengerNode* AVLPassengerTree::leftRotate(PassengerNode* x) {
    PassengerNode* y = x->right;
    PassengerNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

PassengerNode* AVLPassengerTree::insert(PassengerNode* root, Passenger passenger) {
    if (root == nullptr)
        return new PassengerNode(passenger);

    if (passenger.getPassengerID() < root->passenger.getPassengerID()) {
        std::cout << "\n\n>> Passenger data has been inserted successfully" << std::endl;

        root->left = insert(root->left, passenger);
    } else if (passenger.getPassengerID()> root->passenger.getPassengerID()) {
        std::cout << "\n\n>> Passenger data has been inserted successfully" << std::endl;

        root->right = insert(root->right, passenger);
    } else { // Duplicate keys not allowed
        return root;
    }


    updateHeight(root);

    int balance = getBalanceFactor(root);

    // Left-Left case
    if (balance > 1 && passenger.getPassengerID() < root->left->passenger.getPassengerID())
        return rightRotate(root);

    // Right-Right case
    if (balance < -1 && passenger.getPassengerID() > root->right->passenger.getPassengerID())
        return leftRotate(root);

    // Left-Right case
    if (balance > 1 && passenger.getPassengerID() > root->left->passenger.getPassengerID()) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left case
    if (balance < -1 && passenger.getPassengerID() < root->right->passenger.getPassengerID()) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }


    return root;
}

PassengerNode* AVLPassengerTree::findMin(PassengerNode* root) {
    if (root == nullptr)
        return nullptr;

    if (root->left == nullptr)
        return root;
    else
        return findMin(root->left);
}

PassengerNode* AVLPassengerTree::deleteNode(PassengerNode* root, int passengerID) {
    if (root == nullptr)
        return root;

    if (passengerID < root->passenger.getPassengerID())
        root->left = deleteNode(root->left, passengerID);
    else if (passengerID > root->passenger.getPassengerID())
        root->right = deleteNode(root->right, passengerID);
    else {
        // PassengerNode found, perform deletion
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            PassengerNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            PassengerNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            PassengerNode* minNode = findMin(root->right);
            root->passenger = minNode->passenger;
            root->right = deleteNode(root->right, minNode->passenger.getPassengerID());
        }

        std::cout << "\n\n>> Passenger data has been deleted successfully" << std::endl;

    }

    if (root == nullptr)
        return root;

    updateHeight(root);

    int balance = getBalanceFactor(root);

    // Left-Left case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Right-Right case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Left-Right case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }


    return root;
}

PassengerNode* AVLPassengerTree::search(PassengerNode* root, int passengerID) {
    if (root == nullptr || root->passenger.getPassengerID() == passengerID)
        return root;

    if (passengerID < root->passenger.getPassengerID())
        return search(root->left, passengerID);

    return search(root->right, passengerID);
}

void AVLPassengerTree::inorderTraversal(PassengerNode* root) {
    if (root == nullptr)
        return;

    std::cout << root->passenger.getPassengerID() << "\t\t" << root->passenger.getName() << " " << root->passenger.getICNumber() << " " << root->passenger.getPhoneNumber() << " " << root->passenger.getEmail() << std::endl;

    inorderTraversal(root->left);
    inorderTraversal(root->right);
}

void AVLPassengerTree::deleteTree(PassengerNode* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void AVLPassengerTree::saveToFile(PassengerNode* root, std::ofstream& outputFile) {
    if (root == nullptr)
        return;

    saveToFile(root->left, outputFile);
    outputFile << root->passenger.getPassengerID() << "|" << root->passenger.getName() << "|" << root->passenger.getICNumber() << "|" << root->passenger.getPhoneNumber() << "|" << root->passenger.getEmail() << std::endl;
    saveToFile(root->right, outputFile);
}

PassengerNode* AVLPassengerTree::loadFromFile(std::ifstream& inputFile) {
    PassengerNode* root = nullptr;

    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string passengerIDStr, nameStr, icNumberStr, phoneNumberStr, emailStr;

        if (std::getline(ss, passengerIDStr, '|') && std::getline(ss, nameStr, '|') && std::getline(ss, icNumberStr, '|') && std::getline(ss, phoneNumberStr, '|') && std::getline(ss, emailStr, '|')) {
            unsigned int passengerID = std::stoi(passengerIDStr);
            Passenger passenger(passengerID, nameStr, icNumberStr, phoneNumberStr, emailStr);
            root = insert(root, passenger);
        }
    }

    return root;
}

