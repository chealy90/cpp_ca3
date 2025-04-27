//
// Created by favou on 27/04/2025.
//

#include "SuperBug.h"
#include <iostream>
#include <cstdlib>

SuperBug::SuperBug(int id, Position position, Direction direction, int size)
    : Bug(id, position, direction, size) {
    setAlive(true);
    setPosition(position);
}

void SuperBug::move() {
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
            newPos.y = this->getPosition().y - 1;
        break;
        case Direction::EAST:
            newPos.x = this->getPosition().x + 1;
            newPos.y = this->getPosition().y;
        break;
        case Direction::SOUTH:
            newPos.x = this->getPosition().x;
            newPos.y = this->getPosition().y + 1;
        break;
        case Direction::WEST:
            newPos.x = this->getPosition().x - 1;
            newPos.y = this->getPosition().y;
        break;
    }

    // if not out of bounds , set new position
    if (newPos.x >= 0 && newPos.x <= 9 && newPos.y >= 0 && newPos.y <= 9) {
        this->setPosition(newPos);
    }

}

void SuperBug::move(Direction manualControl) {
    // don't move if bug dead
    if (!this->isAlive()) {
        return;
    }

    //determine new position
    Position newPos;
    this->setDirection(manualControl);

    switch (manualControl) {
        case Direction::NORTH:
            newPos.x = this->getPosition().x;
            newPos.y = this->getPosition().y - 1;
        break;
        case Direction::EAST:
            newPos.x = this->getPosition().x + 1;
            newPos.y = this->getPosition().y;
        break;
        case Direction::SOUTH:
            newPos.x = this->getPosition().x;
            newPos.y = this->getPosition().y + 1;
        break;
        case Direction::WEST:
            newPos.x = this->getPosition().x - 1;
            newPos.y = this->getPosition().y;
        break;
    }

    // if not out of bounds , set new position
    if (newPos.x >= 0 && newPos.x <= 9 && newPos.y >= 0 && newPos.y <= 9) {
        this->setPosition(newPos);
        std::cout << "SuperBug moved manually to (" << newPos.x << "," << newPos.y << ")" << std::endl;
    }
}