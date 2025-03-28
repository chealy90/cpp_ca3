//
// Created by chris on 28/03/2025.
//
#include "Crawler.h"
#include "Position.h"
#include <list>
#include <cstdlib>
#include <ctime>

Crawler::Crawler(int id, Position position, Direction direction, int size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = true; //assume all bugs are alive at creation
    this->path.push_back(position); //start of paths list with the initial position
}

void Crawler::move() {
    if (this->isWayBlocked()) {
        //switch direction
        //referenced code from https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
        srand(time(0));
        int randInt = (std::rand() & 4) + 1; //generate a random number between 1 and 4
        switch (randInt) {
            case 1:
                this->direction=Direction::NORTH;
                break;
            case 2:
                this->direction=Direction::EAST;
                break;
            case 3:
                this->direction=Direction::SOUTH;
                break;
            case 4:
                this->direction=Direction::WEST;
                break;
        }
        //repeat function until able to move
        this->move();

    }
    else {
        Position newPos;
        //determine new position
        switch (this->direction) {
            case Direction::NORTH:
                newPos.x = this->position.x;
                newPos.y = this->position.y - 1;
                break;
            case Direction::EAST:
                newPos.x = this->position.x + 1;
                newPos.y = this->position.y;
                break;
            case Direction::SOUTH:
                newPos.x = this->position.x;
                newPos.y = this->position.y + 1;
                break;
            case Direction::WEST:
                newPos.x = this->position.x - 1;
                newPos.y = this->position.y;
            break;
        }

        this->path.push_back(newPos);
        this->position = newPos;
    }
}



bool Crawler::isWayBlocked() {
    //North boundary
    if (this->direction == Direction::NORTH && this->position.y == 0) {
        return true;
    }

    //east boundary
    if (this->direction == Direction::EAST && this->position.x == 10) { // FIX THIS
        return true;
    }

    //south boundary
    if (this->direction == Direction::SOUTH && this->position.y == 10) { //FIX THIS
        return true;
    }

    //west boundary
    if (this->direction == Direction::WEST && this->position.x == 0) {
        return true;
    }

    return false;
}


