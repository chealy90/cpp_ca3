//
// Created by chris on 28/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
#include "Position.h"
#include "Direction.h"
#include <list>

#include "Bug.h"

class Crawler : public Bug
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

    void move() override;
    bool isWayBlocked();

    // getters
    int getId() const;
    Position getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    const std::list<Position>& getPath() const;

    // setters
    void setSize(int size);
    void setAlive(bool alive);

    ~Crawler() override;
};

#endif //CRAWLER_H
