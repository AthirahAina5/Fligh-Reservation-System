#include "Admin.h"
#include <iostream>
#include <cstring>

Admin::Admin() {
    setAdminID(0);
    setPassword("");
    setName("");
    setAge(0);
    setAdminGender(MALE);
}

Admin::~Admin() {    }

Admin::Admin(unsigned int aAdminID, std::string aPassword, std::string aName, unsigned int aAge, Gender aAdminGender) {
    setAdminID(aAdminID);
    setPassword(aPassword);
    setName(aName);
    setAge(aAge);
    setAdminGender(aAdminGender);
}

unsigned int Admin::getAdminID() {
    return adminID;
}

void Admin::setAdminID(unsigned int aAdminID) {
    adminID = aAdminID;
}

std::string Admin::getPassword() {
    return password;
}

void Admin::setPassword(std::string aPassword) {
    password = aPassword;
}

std::string Admin::getName() {
    return name;
}

void Admin::setName(std::string aName) {
    name = aName;
}

unsigned int Admin::getAge() {
    return age;
}

void Admin::setAge(unsigned int aAge) {
    age = aAge;
}

Gender Admin::getAdminGender() {
    return adminGender;
}

void Admin::setAdminGender(Gender aAdminGender) {
    adminGender = aAdminGender;
}

AdminNode::AdminNode() {    }

AdminNode::~AdminNode() {
    delete left;
    delete right;
}

AdminNode::AdminNode(Admin a) {
    admin = a;
    left = nullptr;
    right = nullptr;
    height = 1;
}

int AVLAdminTree::getHeight(AdminNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLAdminTree::getBalanceFactor(AdminNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLAdminTree::updateHeight(AdminNode* node) {
    if (node == nullptr)
        return;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

AdminNode* AVLAdminTree::rightRotate(AdminNode* y) {
    AdminNode* x = y->left;
    AdminNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

AdminNode* AVLAdminTree::leftRotate(AdminNode* x) {
    AdminNode* y = x->right;
    AdminNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

AdminNode* AVLAdminTree::insert(AdminNode* root, Admin admin) {
    if (root == nullptr)
        return new AdminNode(admin);

    if (admin.getAdminID() < root->admin.getAdminID()) {
        std::cout << "\n\n>> Admin data has been inserted successfully" << std::endl;

        root->left = insert(root->left, admin);
    } else if (admin.getAdminID()> root->admin.getAdminID()) {
        std::cout << "\n\n>> Admin data has been inserted successfully" << std::endl;

        root->right = insert(root->right, admin);
    } else { // Duplicate keys not allowed
        return root;
    }


    updateHeight(root);

    int balance = getBalanceFactor(root);

    // Left-Left case
    if (balance > 1 && admin.getAdminID() < root->left->admin.getAdminID())
        return rightRotate(root);

    // Right-Right case
    if (balance < -1 && admin.getAdminID() > root->right->admin.getAdminID())
        return leftRotate(root);

    // Left-Right case
    if (balance > 1 && admin.getAdminID() > root->left->admin.getAdminID()) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Left case
    if (balance < -1 && admin.getAdminID() < root->right->admin.getAdminID()) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }


    return root;
}

AdminNode* AVLAdminTree::findMin(AdminNode* root) {
    if (root == nullptr)
        return nullptr;

    if (root->left == nullptr)
        return root;
    else
        return findMin(root->left);
}

AdminNode* AVLAdminTree::deleteNode(AdminNode* root, int adminID) {
    if (root == nullptr)
        return root;

    if (adminID < root->admin.getAdminID())
        root->left = deleteNode(root->left, adminID);
    else if (adminID > root->admin.getAdminID())
        root->right = deleteNode(root->right, adminID);
    else {
        // AdminNode found, perform deletion
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            AdminNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            AdminNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            AdminNode* minNode = findMin(root->right);
            root->admin = minNode->admin;
            root->right = deleteNode(root->right, minNode->admin.getAdminID());
        }

        std::cout << "\n\n>> Admin data has been deleted successfully" << std::endl;

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

AdminNode* AVLAdminTree::search(AdminNode* root, int adminID) {
    if (root == nullptr || root->admin.getAdminID() == adminID)
        return root;

    if (adminID < root->admin.getAdminID())
        return search(root->left, adminID);

    return search(root->right, adminID);
}

void AVLAdminTree::inorderTraversal(AdminNode* root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    std::cout << "Admin ID: " << root->admin.getAdminID() << ", Name: " << root->admin.getName() << ", Age: " << root->admin.getAge() << ", Gender: " << root->admin.getAdminGender() << std::endl;
    inorderTraversal(root->right);
}

void AVLAdminTree::deleteTree(AdminNode* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void AVLAdminTree::saveToFile(AdminNode* root, std::ofstream& outputFile) {
    if (root == nullptr)
        return;

    saveToFile(root->left, outputFile);
    outputFile << root->admin.getAdminID() << "|" << root->admin.getPassword() << "|" << root->admin.getName() << "|" << root->admin.getAge() << "|" << root->admin.getAdminGender() << std::endl;
    saveToFile(root->right, outputFile);
}

AdminNode* AVLAdminTree::loadFromFile(std::ifstream& inputFile) {
    AdminNode* root = nullptr;

    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string adminIDStr, passwordStr, nameStr, ageStr, genderStr;

        if (std::getline(ss, adminIDStr, '|') && std::getline(ss, passwordStr, '|') && std::getline(ss, nameStr, '|') && std::getline(ss, ageStr, '|') && std::getline(ss, genderStr, '|')) {
            unsigned int adminID = std::stoi(adminIDStr);
            unsigned int age = std::stoi(ageStr);
            int gender = std::stoi(genderStr);

            Admin admin(adminID, passwordStr, nameStr, age, Gender(gender));

            root = insert(root, admin);
        }
    }

    return root;
}
