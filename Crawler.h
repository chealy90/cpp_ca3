//
// Created by chris on 28/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
#include "Position.h"
#include "Direction.h"
#include <list>

class Crawler
{
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;

public:
    Crawler(int id, Position position, Direction direction, int size);

    void move();
    bool isWayBlocked();
    void toString();
};

#endif //CRAWLER_H
