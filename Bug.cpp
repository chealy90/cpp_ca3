//
// Created by favou on 10/04/2025.
//

#include "Bug.h"
#include <iostream>

using namespace std;

Bug::Bug(int id, Position position, Direction direction, int size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = true;
}

Bug::~Bug() {
    // cout << "Destroying Bug ID: " << id << endl;
}

bool Bug::isWayBlocked() {
    bool blocked = false;
    if (this->isHopper()) {
        switch (this->getDirection()) {
            case Direction::NORTH: {
                if (this->getPosition().y <= 2) blocked = true;
                break;
            }
            case Direction::SOUTH: {
                if (this->getPosition().y >= 7) blocked = true;
                break;
            }
            case Direction::EAST: {
                if (this->getPosition().x >= 7) blocked = true;
                break;
            }
            case Direction::WEST: {
                if (this->getPosition().x <= 2) blocked = true;
                break;
            }
        }
    }

    else {
        if (direction == Direction::NORTH && position.y <= 0) {
            blocked = true;
        }
        if (direction == Direction::EAST && position.x >= 9) {
            blocked = true;
        }
        if (direction == Direction::SOUTH && position.y >= 9) {
            blocked = true;
        }
        if (direction == Direction::WEST && position.x <= 0) {
            blocked = true;
        }
    }

    return blocked;




}