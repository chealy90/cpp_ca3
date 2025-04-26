//
// Created by favou on 26/04/2025.
//

#ifndef HOPPER_H
#define HOPPER_H
#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength;
public:
    Hopper(int id, Position position, Direction direction, int size, int hopLength);
    void move() override;

    // getters
    int getHopLength() const {
        return hopLength;
    }
};



#endif //HOPPER_H
