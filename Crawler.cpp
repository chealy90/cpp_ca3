//
// Created by chris on 28/03/2025.
//
#include "Crawler.h"
#include "Position.h"
#include <list>
#include <cstdlib>
#include <ctime>
#include <iostream>

Crawler::Crawler(int id, Position position, Direction direction, int size): Bug(id, position, direction, size) {
    this->setAlive(true); //assume all bugs are alive at creation
    this->setPosition(position); //start of paths list with the initial position
}

void Crawler::move() {
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

    this->setPosition(newPos);

}