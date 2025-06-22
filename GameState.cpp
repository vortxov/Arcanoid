#include "GameState.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <ctime>

// Инициализация статического члена
TextureManager GameState::textureManager;

GameState::GameState(unsigned int width, unsigned int height) :
    window_(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(800, 600),
        "Arkanoid",
        sf::Style::Titlebar | sf::Style::Close)),
    platform_(std::make_unique<Platform>()),
    ball_(std::make_unique<Ball>()),
    currentBallSpeedMultiplier_(1.0f),
    ballSpeedChangeTimer_(0.0f),
    gameWon_(false),
    gameLost_(false),
    onMenu_(true)
{
    try {
        initialize();
    }
    catch (const std::exception& e) {
        std::cerr << "Game initialization failed: " << e.what() << std::endl;
        throw;
    }
}

void GameState::initialize() {
    setupWindow();
    loadResources();
    initGameObjects();
    setupText();
    setupScoreDisplay();
    scoreSystem_.addObserver([this](int score) 
    {
        updateScoreDisplay(score);
    });
}

void GameState::loadResources() {
    // Загрузка текстур
    textureManager.load("background", "resources/textures/background.png");
    textureManager.load("ball", "resources/textures/ball.png");
    textureManager.load("platform", "resources/textures/platform.png");
    textureManager.load("brick_normal", "resources/textures/brick_normal.png");
    textureManager.load("brick_strong", "resources/textures/brick_strong.png");
    textureManager.load("brick_glass", "resources/textures/brick_glass.png");

    // Загрузка шрифта
    if (!font_.loadFromFile("resources/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void GameState::initGameObjects() {
    // Настройка фона
    background_.setTexture(textureManager.get("background"));
    background_.setColor(sf::Color::White); // Убедимся, что фон не затемнен

    // Настройка мяча
    ball_->setPosition(400, 500);
    ball_->setVelocity(sf::Vector2f(180.f, -220.f));
    ball_->setTexture(textureManager.get("ball"));
    ball_->setColor(sf::Color::White); // Убираем красный цвет

    // Настройка платформы
    platform_->setPosition(350, 550);
    platform_->setTexture(textureManager.get("platform"));

    initBricks();
}


void GameState::setupScoreDisplay() {
    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(24);
    scoreText_.setFillColor(sf::Color::White);
    scoreText_.setPosition(20, 440);

    highscoreText_.setFont(font_);
    highscoreText_.setCharacterSize(20);
    highscoreText_.setFillColor(sf::Color::Yellow);
    highscoreText_.setPosition(20, 460);

    updateScoreDisplay(0);
}

void GameState::updateScoreDisplay(int score) {
    scoreText_.setString("Score: " + std::to_string(score));

    std::string highscoresStr = "Highscores:\n";
    for (int hs : scoreSystem_.getHighscores()) {
        highscoresStr += std::to_string(hs) + "\n";
    }
    highscoreText_.setString(highscoresStr);
}


void GameState::setupWindow() {
    window_->setFramerateLimit(60);
    window_->setVerticalSyncEnabled(true);
}


void GameState::setupText() {
    // Текст проигрыша
    loseText_.setFont(font_);
    loseText_.setCharacterSize(40);
    loseText_.setFillColor(sf::Color::White);
    loseText_.setString("Game Over!\nTry again?\n(Y - Yes, N - No)");
    centerText(loseText_);

    // Текст победы
    winText_.setFont(font_);
    winText_.setCharacterSize(40);
    winText_.setFillColor(sf::Color::White);
    winText_.setString("Congratulations! You won!\nPlay again?\n(Y - Yes, N - No)");
    centerText(winText_);
}

void GameState::centerText(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, bounds.height / 2);
    text.setPosition(400, 300);
}

void GameState::run() {
    sf::Clock clock;

    while (window_->isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        if (gameWon_) {
            handleWinScreenInput();
            showWinScreen();
        }
        else if (gameLost_) {
            handleLoseScreenInput();
            showLoseScreen();
        }
        else {
            handleEvents();
            update(deltaTime);
            render();
        }
    }
}

void GameState::handleEvents() {
    sf::Event event;
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_->close();
        }
    }
}

void GameState::update(float deltaTime) {
    handleInput();
    updateBall(deltaTime);
    updateBallSpeed(deltaTime);
    checkGameConditions();
}

void GameState::handleInput() {
    float direction = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction += 1.f;
    }

    platform_->move(direction * platformSpeed_);
    clampPlatformPosition();
}

void GameState::clampPlatformPosition() {
    sf::FloatRect bounds = platform_->getGlobalBounds();
    sf::Vector2f position = platform_->getPosition();

    if (position.x < 0.f) {
        platform_->setPosition(0.f, position.y);
    }
    else if (position.x + bounds.width > 800.f) {
        platform_->setPosition(800.f - bounds.width, position.y);
    }
}

void GameState::updateBall(float deltaTime) {
    ball_->update(deltaTime);
    checkCollisions();
}

void GameState::updateBallSpeed(float deltaTime) {
    ballSpeedChangeTimer_ += deltaTime;

    if (ballSpeedChangeTimer_ >= ballSpeedChangeInterval_) {
        ballSpeedChangeTimer_ = 0.f;
        currentBallSpeedMultiplier_ = std::min(
            maxBallSpeedMultiplier_,
            currentBallSpeedMultiplier_ * 1.05f
        );

        // Визуальная индикация ускорения через scale вместо цвета
        float ratio = (currentBallSpeedMultiplier_ - minBallSpeedMultiplier_) /
            (maxBallSpeedMultiplier_ - minBallSpeedMultiplier_);
        float scale = 1.0f + ratio * 0.2f; // Увеличиваем на 20% при максимальном ускорении
        const_cast<sf::Sprite&>(ball_->getSprite()).setScale(scale, scale);

        ball_->setSpeedMultiplier(currentBallSpeedMultiplier_);
    }
}

void GameState::initBricks() {
    bricks_.clear();

    const int rows = 5;
    const int cols = 8;
    const float width = 90.f;
    const float height = 25.f;
    const float startX = (800 - (cols * (width + 5.f))) / 2.f;  //TODO: константа расширения
    const float startY = 50.f;
    srand(time(0));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::unique_ptr<Block> brick;

            if (row == 0 && col % 3 == 0) {
                brick = std::make_unique<StrongBrick>();
                brick->setTexture(textureManager.get("brick_strong"));
            }
            else if (row == 2 && col % 4 == 0) {
                brick = std::make_unique<GlassBrick>();
                brick->setTexture(textureManager.get("brick_glass"));
            }
            else {
                brick = std::make_unique<NormalBrick>();
                brick->setTexture(textureManager.get("brick_normal"));
            }
             // Seed для генерации случайных чисел
            int random_brickbonuschange = std::rand() % 1 + 1; // Случайное число от 1 до 10

            if (random_brickbonuschange == 1) {
                int random_bonus = std::rand() % 3;
                std::cout << random_bonus;
                brick->SetRandomBonus(random_bonus);
            }

            brick->setPosition(startX + col * (width + 5.f),
                startY + row * (height + 5.f));
            bricks_.push_back(std::move(brick));
        }
    }
}



void GameState::checkCollisions() {
    checkWallCollisions();
    checkPlatformCollision();
    checkBrickCollisions();
}

void GameState::checkWallCollisions() {
    sf::Vector2f ballPos = ball_->getPosition();
    float radius = ball_->getRadius();

    if (ballPos.x - radius <= 0 || ballPos.x + radius >= 800) {  //TODO: замена на константу разширения
        ball_->reverseX();
    }
    if (ballPos.y - radius <= 0) {
        ball_->reverseY();
    }
}

void GameState::checkPlatformCollision() { //TODO: дебаг соприкосновения 
    if (ball_->getGlobalBounds().intersects(platform_->getGlobalBounds())) {
        sf::Vector2f platformPos = platform_->getPosition();
        float platformCenter = platformPos.x + platform_->getGlobalBounds().width / 2;
        float hitPos = (ball_->getPosition().x - platformCenter) / (platform_->getGlobalBounds().width / 2);

        sf::Vector2f newVel;
        newVel.x = hitPos * 300.f;
        newVel.y = -sqrt(300.f * 300.f - newVel.x * newVel.x);
        ball_->setVelocity(newVel);
    }
}

void GameState::checkBrickCollisions() {
    for (auto& brick : bricks_) {
        if (!brick->isDestroyed() && ball_->getGlobalBounds().intersects(brick->getBounds())) {
            brick->hit();

            if (brick->isDestroyed()) {
                if (dynamic_cast<NormalBrick*>(brick.get())) {
                    scoreSystem_.addScore(ScoreSystem::BrickType::Normal);
                }
                else if (dynamic_cast<StrongBrick*>(brick.get())) {
                    scoreSystem_.addScore(ScoreSystem::BrickType::Strong);
                }
                else if (dynamic_cast<GlassBrick*>(brick.get())) {
                    scoreSystem_.addScore(ScoreSystem::BrickType::Glass);
                }

                pushBonus(*brick);
            }

            if (brick->shouldBallBounce()) {
                handleBrickCollisionResponse(*brick);
            }
            break;
        }
    }
}


void GameState::pushBonus(Block& brick)
{
    if (brick.GetBonus().GetBonusType() == BonusType::None) {
        return;
    }

    sf::Vector2f brickPosition = sf::Vector2f(brick.getSprite().getPosition().x + 25.f, brick.getSprite().getPosition().y + 15.f);

    brick.GetBonus().initBonus(brickPosition);


    bonuses_.push_back(brick.GetBonus());
}


//
//void spawnBonus(BonusType bonusType)
//{
//    if (bonusType == BonusType::None) {
//        return;
//    }
//
//
//}

void GameState::handleBrickCollisionResponse(const Block& brick) 
{
    sf::FloatRect ballBounds = ball_->getGlobalBounds();
    sf::FloatRect brickBounds = brick.getBounds();

    float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
    float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
    float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
    float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

    bool fromLeft = overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom;
    bool fromRight = overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom;
    bool fromTop = overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom;
    bool fromBottom = overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop;

    if (fromLeft || fromRight) ball_->reverseX();
    if (fromTop || fromBottom) ball_->reverseY();
}

void GameState::checkGameConditions() 
{
    checkLoseCondition();
    checkWinCondition();
}

void GameState::checkLoseCondition() 
{
    if (ball_->getPosition().y - ball_->getRadius() > 600) 
    {
        gameLost_ = true;
    }
}

void GameState::checkWinCondition() {
    bool allDestroyed = std::all_of(bricks_.begin(), bricks_.end(),
        [](const auto& brick) { return brick->isDestroyed(); });

    if (allDestroyed) {
        gameWon_ = true;
    }
}

void GameState::render() 
{
    window_->clear();

    // Отрисовка фона
    window_->draw(background_);

    //Очки
    window_->draw(scoreText_);
    window_->draw(highscoreText_);

    for (const auto& brick : bricks_) 
    {
        brick->draw(*window_);
    }

    for (const Bonus &temp : bonuses_)
    {
        window_->draw(temp.sprite_);
        //temp.draw(window_);
    }

    // Отрисовка платформы и мяча
    window_->draw(platform_->getSprite());
    window_->draw(ball_->getSprite());

    // Отрисовка UI
    if (gameWon_) window_->draw(winText_);
    if (gameLost_) window_->draw(loseText_);

    window_->display();
}

void GameState::showWinScreen() 
{
    scoreSystem_.saveToHighscores();
    window_->clear();
    window_->draw(background_);
    window_->draw(winText_);
    window_->display();
}

void GameState::handleWinScreenInput() 
{
    sf::Event event;
    while (window_->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            window_->close();
        }
        else if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::Y) 
            {
                resetGame();
            }
            else if (event.key.code == sf::Keyboard::N) 
            {
                window_->close();
            }
        }
    }
}

void GameState::showLoseScreen() 
{
    scoreSystem_.saveToHighscores();
    window_->clear();
    window_->draw(background_);
    window_->draw(loseText_);
    window_->display();
}

void GameState::handleLoseScreenInput() 
{
    sf::Event event;
    while (window_->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            window_->close();
        }
        else if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::Y) 
            {
                resetGame();
            }
            else if (event.key.code == sf::Keyboard::N) 
            {
                window_->close();
            }
        }
    }
}

void GameState::resetGame() 
{
    // Сброс состояния
    gameWon_ = false;
    gameLost_ = false;
    currentBallSpeedMultiplier_ = 1.0f;
    ballSpeedChangeTimer_ = 0.0f;

    // Сброс объектов
    ball_->reset(400, 500);
    ball_->setVelocity(sf::Vector2f(180.f, -220.f));
    ball_->setColor(sf::Color::White);
    platform_->setPosition(350, 550);

    // Пересоздание блоков
    initBricks();

      
}