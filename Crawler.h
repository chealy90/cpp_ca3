//
// Created by chris on 28/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
#include "Position.h"
#include <list>
class Crawler
{
private:
    int id;
    Position position;
    int direction;
    int size;
    bool alive;
    list<Position> path;

public:
    Crawler();

    void move();
    bool isWayBlocked();
};

#endif //CRAWLER_H
