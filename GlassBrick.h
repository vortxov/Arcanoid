#pragma once
#include "Block.h"

class GlassBrick : public Block {
public:
    GlassBrick();
    bool shouldBallBounce() const override;
};
