#include "GlassBrick.h"

GlassBrick::GlassBrick() {
    hitPoints_ = 1;
}

bool GlassBrick::shouldBallBounce() const {
    return false;
}