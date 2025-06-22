#pragma once
#include "Block.h"

class NormalBrick : public Block {
public:
    NormalBrick();
    bool shouldBallBounce() const override;
};