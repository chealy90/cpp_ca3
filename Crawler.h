//
// Created by chris on 28/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
#include "Position.h"
#include "Direction.h"
#include <list>

#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, Position position, Direction direction, int size);
    void move() override;
};

#endif //CRAWLER_H
