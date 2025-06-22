#pragma once
#include "Block.h"

class StrongBrick : public Block {
public:
    StrongBrick();
    void hit() override;
    bool shouldBallBounce() const override;
};