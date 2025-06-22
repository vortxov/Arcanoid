#include "NormalBrick.h"

NormalBrick::NormalBrick() {
    hitPoints_ = 1;
}

bool NormalBrick::shouldBallBounce() const {
    return true;
}