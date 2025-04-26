//
// Created by favou on 10/04/2025.
//

#include "Bug.h"

using namespace std;

Bug::Bug(int id, Position position, Direction direction, int size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = true;
    path.push_back(position);
}

Bug::~Bug() {
    cout << "Destroying Bug ID: " << id << endl;
}

bool Bug::isWayBlocked() const {
    if (direction == Direction::NORTH && position.y <= 0) {
        return true;
    }
    if (direction == Direction::EAST && position.x >= 9) {
        return true;
    }
    if (direction == Direction::SOUTH && position.y >= 9) {
        return true;
    }
    if (direction == Direction::WEST && position.x <= 0) {
        return true;
    }
    return false;
}