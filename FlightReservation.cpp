#include "FlightReservation.h"

FlightReservation::FlightReservation() {
    setTicketID(0);
    setPassengerID(0);
    setFlightNumber(0);
    setSeatID(0);
}

FlightReservation::~FlightReservation() {    }

FlightReservation::FlightReservation(unsigned int aTicketID, unsigned int aPassengerID, unsigned int aFlightNumber, unsigned int aSeatID) {
    setTicketID(aTicketID);
    setPassengerID(aPassengerID);
    setFlightNumber(aFlightNumber);
    setSeatID(aSeatID);
}

unsigned int FlightReservation::getTicketID() {
    return ticketID;
}

void FlightReservation::setTicketID(unsigned int aTicketID) {
    ticketID = aTicketID;
}

unsigned int FlightReservation::getPassengerID() {
    return passengerID;
}

void FlightReservation::setPassengerID(unsigned int aPassengerID) {
    passengerID = aPassengerID;
}

unsigned int FlightReservation::getFlightNumber() {
    return flightNumber;
}

void FlightReservation::setFlightNumber(unsigned int aFlightNumber) {
    flightNumber = aFlightNumber;
}

unsigned int FlightReservation::getSeatID() {
    return seatID;
}

void FlightReservation::setSeatID(unsigned int aSeatID) {
    seatID = aSeatID;
}

FlightReservationNode::FlightReservationNode() {    }

FlightReservationNode::~FlightReservationNode() {
    delete left;
    delete right;
}

FlightReservationNode::FlightReservationNode(FlightReservation fr) {
    flightReservation = fr;
    left = nullptr;
    right = nullptr;
    height = 1;
}

int AVLFlightReservationTree::getHeight(FlightReservationNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLFlightReservationTree::getBalanceFactor(FlightReservationNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLFlightReservationTree::updateHeight(FlightReservationNode* node) {
    if (node == nullptr)
        return;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

FlightReservationNode* AVLFlightReservationTree::rightRotate(FlightReservationNode* y) {
    FlightReservationNode* x = y->left;
    FlightReservationNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

FlightReservationNode* AVLFlightReservationTree::leftRotate(FlightReservationNode* x) {
    FlightReservationNode* y = x->right;
    FlightReservationNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

FlightReservationNode* AVLFlightReservationTree::insert(FlightReservationNode* root, FlightReservation flightReservation) {
    if (root == nullptr)
        return new FlightReservationNode(flightReservation);

    if (flightReservation.getTicketID() < root->flightReservation.getTicketID()) {
        std::cout << "\n\n>> Flight Reservation data has been inserted successfully" << std::endl;

        root->left = insert(root->left, flightReservation);
    } else if (flightReservation.getTicketID()> root->flightReservation.getTicketID()) {
        std::cout << "\n\n>> Flight Reservation data has been inserted successfully" << std::endl;

        root->right = insert(root->right, flightReservation);
    } else { // Duplicate keys not allowed
        return root;
    }

    updateHeight(root);

    int balance = getBalanceFactor(root);

    // Left-Left case
    if (balance > 1 && flightReservation.getTicketID() < root->left->flightReservation.getTicketID())
        return rightRotate(root);

    // Right-Right case
    if (balance < -1 && flightReservation.getTicketID() > root->right->flightReservation.getTicketID())
        return leftRotate(root);

    // Left-Right case
    if (balance > 1 && flightReservation.getTicketID() > root->left->flightReservation.getTicketID()) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left case
    if (balance < -1 && flightReservation.getTicketID() < root->right->flightReservation.getTicketID()) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

FlightReservationNode* AVLFlightReservationTree::findMin(FlightReservationNode* root) {
    if (root == nullptr)
        return nullptr;

    if (root->left == nullptr)
        return root;
    else
        return findMin(root->left);
}

FlightReservationNode* AVLFlightReservationTree::deleteNode(FlightReservationNode* root, int ticketID) {
    if (root == nullptr)
        return root;

    if (ticketID < root->flightReservation.getTicketID())
        root->left = deleteNode(root->left, ticketID);
    else if (ticketID > root->flightReservation.getTicketID())
        root->right = deleteNode(root->right, ticketID);
    else {
        // FlightReservationNode found, perform deletion
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            FlightReservationNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            FlightReservationNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            FlightReservationNode* minNode = findMin(root->right);
            root->flightReservation = minNode->flightReservation;
            root->right = deleteNode(root->right, minNode->flightReservation.getTicketID());
        }

        std::cout << "\n\n>> Flight Reservation data has been deleted successfully" << std::endl;

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

FlightReservationNode* AVLFlightReservationTree::search(FlightReservationNode* root, int ticketID) {
    if (root == nullptr || root->flightReservation.getTicketID() == ticketID)
        return root;

    if (ticketID < root->flightReservation.getPassengerID())
        return search(root->left, ticketID);

    return search(root->right, ticketID);
}

void AVLFlightReservationTree::inorderTraversal(FlightReservationNode* root, int passengerID = -1) {
    if (root == nullptr)
        return;

    if (passengerID == -1) {
        inorderTraversal(root->left);
        std::cout << root->flightReservation.getTicketID() << " " << root->flightReservation.getPassengerID() << " " << root->flightReservation.getFlightNumber() << " " << root->flightReservation.getSeatID() << std::endl;
        inorderTraversal(root->right);
    } else {
        inorderTraversal(root->left);
        std::cout << root->flightReservation.getTicketID() << "\t" << root->flightReservation.getFlightNumber() << "\t" << root->flightReservation.getSeatID() << std::endl;
        inorderTraversal(root->right);
    }

}

void AVLFlightReservationTree::deleteTree(FlightReservationNode* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void AVLFlightReservationTree::saveToFile(FlightReservationNode* root, std::ofstream& outputFile) {
    if (root == nullptr)
        return;

    saveToFile(root->left, outputFile);
    outputFile << root->flightReservation.getTicketID() << "|" << root->flightReservation.getPassengerID() << "|" << root->flightReservation.getFlightNumber() << "|" << root->flightReservation.getSeatID() << std::endl;
    saveToFile(root->right, outputFile);
}

FlightReservationNode* AVLFlightReservationTree::loadFromFile(std::ifstream& inputFile) {
    FlightReservationNode* root = nullptr;

    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string ticketIDStr, passengerIDStr, flightNumberStr, seatIDStr;

        if (std::getline(ss, ticketIDStr, '|') && std::getline(ss, passengerIDStr, '|') && std::getline(ss, flightNumberStr, '|') && std::getline(ss, seatIDStr, '|')) {
            unsigned int ticketID = std::stoi(ticketIDStr);
            unsigned int passengerID = std::stoi(passengerIDStr);
            unsigned int flightNumber = std::stoi(flightNumberStr);
            unsigned int seatID = std::stoi(seatIDStr);
            FlightReservation flightReservation(ticketID, passengerID, flightNumber, seatID);
            root = insert(root, flightReservation);
        }
    }

    return root;
}

