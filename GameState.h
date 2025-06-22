#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Platform.h"
#include "Ball.h"
#include "NormalBrick.h"
#include "StrongBrick.h"
#include "GlassBrick.h"
#include "ScoreSystem.h"
#include "TextureManager.h"
#include "Bonus.h"

class GameState {
public:
    GameState(unsigned int width, unsigned int height);
    void run();

private:
    // Инициализация
    void initialize();
    void setupWindow();
    void loadResources();
    void initGameObjects();
    void setupText();
    void centerText(sf::Text& text);
    void setupScoreDisplay();
    void updateScoreDisplay(int score);

    // Игровая логика
    std::vector<std::unique_ptr<Block>> bricks_;
    void handleEvents();
    void update(float deltaTime);
    void render();
    void handleInput();
    void clampPlatformPosition();
    void updateBall(float deltaTime);
    void updateBallSpeed(float deltaTime);
    void initBricks();
    void pushBonus(Block& brick);

    // Коллизии
    void checkCollisions();
    void checkWallCollisions();
    void checkPlatformCollision();
    void checkBrickCollisions();
    void handleBrickCollisionResponse(const Block& brick);

    // Состояния игры
    void checkGameConditions();
    void checkLoseCondition();
    void checkWinCondition();

    // Экраны окончания игры
    void showWinScreen();
    void handleWinScreenInput();
    void showLoseScreen();
    void handleLoseScreenInput();
    void resetGame();

    // Ресурсы
    static TextureManager textureManager;
    ScoreSystem scoreSystem_;
    sf::Text scoreText_;
    sf::Text highscoreText_;
    sf::Font font_;
    sf::Text winText_;
    sf::Text loseText_;
    sf::Sprite background_;

    // Игровые объекты
    std::unique_ptr<sf::RenderWindow> window_;
    std::unique_ptr<Platform> platform_;
    std::unique_ptr<Ball> ball_;
    std::vector<std::unique_ptr<Block>> blocks_;
    std::vector<Bonus> bonuses_;

    // Параметры игры
    bool gameWon_;
    bool gameLost_;
    bool onMenu_;
    const float platformSpeed_ = 5.0f;
    float currentBallSpeedMultiplier_;
    float ballSpeedChangeTimer_;
    const float ballSpeedChangeInterval_ = 1.0f;
    const float minBallSpeedMultiplier_ = 1.0f;
    const float maxBallSpeedMultiplier_ = 1.5f;
};