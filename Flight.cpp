#include "Flight.h"

Flight::Flight() {
    setFlightNumber(0);
    setName("");
    setDepartureLocation("");
    setArrivalLocation("");
    setDepartureTime("");
    setArrivalTime("");
    setAvailableSeats(0);
}

Flight::Flight(unsigned int aFlightNumber, std::string aName, std::string aDepartureLocation, std::string aArrivalLocation, std::string aDepartureTime, std::string aArrivalTime, unsigned int aAvailableSeats) {
    setFlightNumber(aFlightNumber);
    setName(aName);
    setDepartureLocation(aDepartureLocation);
    setArrivalLocation(aArrivalLocation);
    setDepartureTime(aDepartureTime);
    setArrivalTime(aArrivalTime);
    setAvailableSeats(aAvailableSeats);
}

Flight::~Flight() {    }

unsigned int Flight::getFlightNumber() {
    return flightNumber;
}

void Flight::setFlightNumber(unsigned int aFlightNumber) {
    flightNumber = aFlightNumber;
}

std::string Flight::getName() {
    return name;
}

void Flight::setName(std::string aName) {
    name = aName;
}

std::string Flight::getDepartureLocation() {
    return departureLocation;
}

void Flight::setDepartureLocation(std::string aDepartureLocation) {
    departureLocation = aDepartureLocation;
}

std::string Flight::getArrivalLocation() {
    return arrivalLocation;
}

void Flight::setArrivalLocation(std::string aArrivalLocation) {
    arrivalLocation = aArrivalLocation;
}

std::string Flight::getDepartureTime() {
    return departureTime;
}

void Flight::setDepartureTime(std::string aDepartureTime) {
    departureTime = aDepartureTime;
}

std::string Flight::getArrivalTime() {
    return arrivalTime;
}

void Flight::setArrivalTime(std::string aArrivalTime) {
    arrivalTime = aArrivalTime;
}

unsigned int Flight::getAvailableSeats() {
    return availableSeats;
}

void Flight::setAvailableSeats(unsigned int aAvailableSeats) {
    availableSeats = aAvailableSeats;
}

bool Flight::hasSeats() {
    if (getAvailableSeats() > 0) {
        return true;
    } else {
        return false;
    }
}

FlightNode::FlightNode() {    }

FlightNode::~FlightNode() {
    delete left;
    delete right;
}

FlightNode::FlightNode(Flight f) {
    flight = f;
    left = nullptr;
    right = nullptr;
    height = 1;
}

int AVLFlightTree::getHeight(FlightNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLFlightTree::getBalanceFactor(FlightNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLFlightTree::updateHeight(FlightNode* node) {
    if (node == nullptr)
        return;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

FlightNode* AVLFlightTree::rightRotate(FlightNode* y) {
    FlightNode* x = y->left;
    FlightNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

FlightNode* AVLFlightTree::leftRotate(FlightNode* x) {
    FlightNode* y = x->right;
    FlightNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

FlightNode* AVLFlightTree::insert(FlightNode* root, Flight flight) {
    if (root == nullptr)
        return new FlightNode(flight);

    if (flight.getFlightNumber() < root->flight.getFlightNumber()) {
        std::cout << "\n\n>> Flight data has been inserted successfully" << std::endl;

        root->left = insert(root->left, flight);
    } else if (flight.getFlightNumber()> root->flight.getFlightNumber()) {
        std::cout << "\n\n>> Flight data has been inserted successfully" << std::endl;

        root->right = insert(root->right, flight);
    } else { // Duplicate keys not allowed
        return root;
    }

    updateHeight(root);

    int balance = getBalanceFactor(root);

    // Left-Left case
    if (balance > 1 && flight.getFlightNumber() < root->left->flight.getFlightNumber())
        return rightRotate(root);

    // Right-Right case
    if (balance < -1 && flight.getFlightNumber() > root->right->flight.getFlightNumber())
        return leftRotate(root);

    // Left-Right case
    if (balance > 1 && flight.getFlightNumber() > root->left->flight.getFlightNumber()) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left case
    if (balance < -1 && flight.getFlightNumber() < root->right->flight.getFlightNumber()) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

FlightNode* AVLFlightTree::findMin(FlightNode* root) {
    if (root == nullptr)
        return nullptr;

    if (root->left == nullptr)
        return root;
    else
        return findMin(root->left);
}

FlightNode* AVLFlightTree::deleteNode(FlightNode* root, int flightNumber) {
    if (root == nullptr)
        return root;

    if (flightNumber < root->flight.getFlightNumber())
        root->left = deleteNode(root->left, flightNumber);
    else if (flightNumber > root->flight.getFlightNumber())
        root->right = deleteNode(root->right, flightNumber);
    else {
        // FlightNode found, perform deletion
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            FlightNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            FlightNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            FlightNode* minNode = findMin(root->right);
            root->flight = minNode->flight;
            root->right = deleteNode(root->right, minNode->flight.getFlightNumber());
        }

        std::cout << "\n\n>> Flight data has been deleted successfully" << std::endl;

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

FlightNode* AVLFlightTree::search(FlightNode* root, int flightNumber) {
    if (root == nullptr || root->flight.getFlightNumber() == flightNumber)
        return root;

    if (flightNumber < root->flight.getFlightNumber())
        return search(root->left, flightNumber);

    return search(root->right, flightNumber);
}

void AVLFlightTree::inorderTraversal(FlightNode* root) {
    if (root == nullptr)
        return;

    std::cout << root->flight.getFlightNumber() << "\t" << root->flight.getName() << "  " << root->flight.getDepartureLocation() << " " << root->flight.getArrivalLocation() << " " << root->flight.getDepartureTime() << "\t\t" << root->flight.getArrivalTime() << " " << root->flight.getAvailableSeats() << std::endl;
    //std::cout << root->flight.getArrivalTime() << "\t" << root->flight.getAvailableSeats();
    inorderTraversal(root->left);
    inorderTraversal(root->right);
}

void AVLFlightTree::deleteTree(FlightNode* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void AVLFlightTree::saveToFile(FlightNode* root, std::ofstream& outputFile) {
    if (root == nullptr)
        return;

    saveToFile(root->left, outputFile);
    outputFile << root->flight.getFlightNumber() << "|" << root->flight.getName() << "|" << root->flight.getDepartureLocation() << "|" << root->flight.getArrivalLocation() << "|" << root->flight.getDepartureTime() << "|" << root->flight.getArrivalTime() << "|" << root->flight.getAvailableSeats() << std::endl;
    saveToFile(root->right, outputFile);
}

FlightNode* AVLFlightTree::loadFromFile(std::ifstream& inputFile) {
    FlightNode* root = nullptr;

    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string flightNumberStr, flightNameStr, departureLocationStr, arrivalLocationStr, departureTimeStr, arrivalTimeStr, availableSeatsStr;

        if (std::getline(ss, flightNumberStr, '|') && std::getline(ss, flightNameStr, '|') && std::getline(ss, departureLocationStr, '|') && std::getline(ss, arrivalLocationStr, '|') && std::getline(ss, departureTimeStr, '|') && std::getline(ss, arrivalTimeStr, '|') && std::getline(ss, availableSeatsStr, '|')) {
            unsigned int flightNumber = std::stoi(flightNumberStr);
            unsigned int availableSeats = std::stoi(availableSeatsStr);
            std::cout << "\n\nArrival Time: " << arrivalTimeStr;
            Flight flight(flightNumber, flightNameStr, departureLocationStr, arrivalLocationStr, departureTimeStr, arrivalTimeStr, availableSeats);
            root = insert(root, flight);
        }
    }

    return root;
}
