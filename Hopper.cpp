//
// Created by favou on 26/04/2025.
//

#include "Hopper.h"
#include <cstdlib>

using namespace std;

Hopper::Hopper(int id, Position position, Direction direction, int size, int hopLength) : Bug(id, position, direction, size) {
    setId(id);
    setPosition(position);
    setDirection(direction);
    setSize(size);
    setAlive(true);
    this->hopLength = hopLength;
}

void Hopper::move() {
    // don't move if bug dead
    if (!this->isAlive()) {
        return;
    }

    while (this->isWayBlocked()) {
        //switch direction
        //referenced code from https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
        // srand(time(NULL));
        int randInt = std::rand() % 4 + 1; //generate a random number between 1 and 4
        switch (randInt) {
            case 1:
                this->setDirection(Direction::NORTH);
            break;
            case 2:
                this->setDirection(Direction::EAST);
            break;
            case 3:
                this->setDirection(Direction::SOUTH);
            break;
            case 4:
                this->setDirection(Direction::WEST);
            break;
        }

    }

    //determine new position
    Position newPos;
    switch (this->getDirection()) {
        case Direction::NORTH:
            newPos.x = this->getPosition().x;
            newPos.y = this->getPosition().y - hopLength;
            break;
        case Direction::EAST:
            newPos.x = this->getPosition().x + hopLength;
            newPos.y = this->getPosition().y;
            break;
        case Direction::SOUTH:
            newPos.x = this->getPosition().x;
            newPos.y = this->getPosition().y + hopLength;
            break;
        case Direction::WEST:
            newPos.x = this->getPosition().x - hopLength;
            newPos.y = this->getPosition().y;
            break;
    }

    // if out of bounds, do not move
    if (newPos.x < 0 || newPos.x > 9 || newPos.y < 0 || newPos.y > 9) {
        return;
    }

    // set the new position
    this->setPosition(newPos);
}