#include "StrongBrick.h"

StrongBrick::StrongBrick() {
    hitPoints_ = 3;
}

void StrongBrick::hit() {
    Block::hit();
    // Дополнительная логика при ударе
}

bool StrongBrick::shouldBallBounce() const {
    return true;
}