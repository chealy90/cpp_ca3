//
// Created by favou on 27/04/2025.
//

#ifndef SUPERBUG_H
#define SUPERBUG_H
#include "Bug.h"
#include "Direction.h"
#include "Position.h"

class SuperBug : public Bug {
private:
    bool manualMoved = false;
public:
    SuperBug(int id, Position position, Direction direction, int size);
    void move() override;
    void move(Direction manualControl);

    // override methods so that superbug with identify as superbug
    bool isSuperBug() const override {
        return true;
    }

    bool wasManualMoved() const {
        return manualMoved;
    }
};



#endif //SUPERBUG_H
