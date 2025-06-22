#pragma once
#include <memory>
#include "GameState.h"

class Application {
public:
    Application();
    void run();

private:
    std::unique_ptr<GameState> gameState_;
};