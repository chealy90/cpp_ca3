//
// Created by favou on 10/04/2025.
//

#ifndef BUG_H
#define BUG_H
#include "Position.h"
#include "Direction.h"
#include <list>
#include <SFML/Graphics.hpp>

class Bug {
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std:: list<Position> path;
public:
    Bug(int id, Position position, Direction direction, int size);
    bool isWayBlocked();
    virtual ~Bug();
    virtual void move() = 0;

    // must check which bug type
    virtual bool isHopper() const {
        return false;
    }
    virtual int getHopLength() const {
        return 0;
    }

    virtual bool isSuperBug() const {
         return false;
    }

    // getters
    int getId() const {
        return id;
    }
    Position getPosition() const {
        return position;
    }
    Direction getDirection() const {
        return direction;
    }
    int getSize() const {
        return size;
    }
    bool isAlive() const {
        return alive;
    }
    const std::list<Position>& getPath() const {
        return path;
    }

    // setters
    void setId(int newId) {
        id = newId;
    }
    void setPosition(Position newPosition) {
        position = newPosition;
        path.push_back(newPosition);
    }
    void setDirection(Direction newDirection) {
        direction = newDirection;
    }
    void setSize(int newSize) {
        size = newSize;
    }
    void setAlive(bool alive) {
        this->alive = alive;
    }
};



#endif //BUG_H