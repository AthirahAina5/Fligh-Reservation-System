#include "FlightNode.h"

FlightNode::FlightNode(Flight f) {
    flight = f;
    left = nullptr;
    right = nullptr;
    height = 1;
}

FlightNode::~FlightNode() {    }
