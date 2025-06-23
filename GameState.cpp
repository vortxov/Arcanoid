#include "GameState.h"
#include <iostream>
#include "GlassBrick.h"
#include "NormalBrick.h"
#include "Math.h"

TextureManager GameState::textureManager;

GameState::GameState(unsigned int width, unsigned int height)
	: window_(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid", sf::Style::Titlebar | sf::Style::Close))
	, platform_(std::make_unique<Platform>())
	, ball_(std::make_unique<Ball>())
	, currentBallSpeedMultiplier_(1.0f)
	, ballSpeedChangeTimer_(0.0f)
	, gameWon_(false)
	, gameLost_(false)
	, onMenu_(true)
{
	try
	{
		initialize();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Game initialization failed: " << e.what() << std::endl;
		throw;
	}
}

void GameState::initialize()
{
	setupWindow();
	loadResources();
	initGameObjects();
	setupText();
	setupScoreDisplay();
	scoreSystem_.addObserver([this](int score) {
		updateScoreDisplay(score);
	});
}

void GameState::loadResources()
{
	// Глобальный менеджер текстур
	textureManager.load("background", "resources/textures/background.png");
	textureManager.load("ball", "resources/textures/ball.png");
	textureManager.load("fireball", "resources/textures/fireball.png");
	textureManager.load("fireball_bonus", "resources/textures/fireball_bonus.png");
	textureManager.load("glass_blocks_bonus", "resources/textures/glass_blocks_bonus.png");
	textureManager.load("platform", "resources/textures/platform.png");
	textureManager.load("platform_bonus", "resources/textures/platform_bonus.png");
	textureManager.load("brick_normal", "resources/textures/brick_normal.png");
	textureManager.load("brick_strong", "resources/textures/brick_strong.png");
	textureManager.load("brick_glass", "resources/textures/brick_glass.png");

	// // Настроки для спрайтов
	// ball_->getSprite().setScale(2.0f, 2.0f);

	// Загрузка текстур
	if (!font_.loadFromFile("resources/fonts/arial.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}
}

void GameState::initGameObjects()
{
	// Установка текстуры заднего фона
	background_.setTexture(textureManager.get("background"));
	background_.setColor(sf::Color::White);	 // Белый цвет без затемнения

	// Установка текстуры заднего фона
	ball_->setPosition(400, 500);
	ball_->setVelocity(sf::Vector2f(180.f, -220.f));
	ball_->setTexture(textureManager.get("ball"));

	// Инициализация кирпичей
	platform_->setPosition(350, 550);
	platform_->setTexture(textureManager.get("platform"));

	initBricks();
}

void GameState::setupScoreDisplay()
{
	scoreText_.setFont(font_);
	scoreText_.setCharacterSize(24);
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setPosition(20, 440);

	highscoreText_.setFont(font_);
	highscoreText_.setCharacterSize(20);
	highscoreText_.setFillColor(sf::Color::Yellow);
	highscoreText_.setPosition(20, 460);

	scoreSystem_.readToHighscrores();
	updateScoreDisplay(0);
}

void GameState::updateScoreDisplay(int score)
{
	scoreText_.setString("Score: " + std::to_string(score));

	std::string highscoresStr = "Highscores:\n";
	for (int hs : scoreSystem_.getHighscores())
	{
		highscoresStr += std::to_string(hs) + "\n";
	}
	highscoreText_.setString(highscoresStr);
}

void GameState::setupWindow()
{
	window_->setFramerateLimit(60);
	window_->setVerticalSyncEnabled(true);
}

void GameState::setupText()
{
	// Настройка текста "Вы проиграли"
	loseText_.setFont(font_);
	loseText_.setCharacterSize(40);
	loseText_.setFillColor(sf::Color::White);
	loseText_.setString("Game Over!\nTry again?\n(Space - Yes, Esc - No)");
	centerText(loseText_);

	// Настройка текста победы
	winText_.setFont(font_);
	winText_.setCharacterSize(40);
	winText_.setFillColor(sf::Color::White);
	winText_.setString("Congratulations! You won!\nPlay again?\n(Space - Yes, Esc - No)");
	centerText(winText_);
}

void GameState::centerText(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
}

void GameState::run()
{
	sf::Clock clock;

	while (window_->isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		if (gameWon_)
		{
			handleWinScreenInput();
			showWinScreen();
		}
		else if (gameLost_)
		{
			handleLoseScreenInput();
			showLoseScreen();
		}
		else
		{
			handleEvents();
			update(deltaTime);
			render();
		}
	}
}

void GameState::handleEvents()
{
	sf::Event event;
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_->close();
		}
	}
}

void GameState::update(float deltaTime)
{
	handleInput();
	updateBall(deltaTime);
	// AccelerationBallSpeed(deltaTime); // Not used
	checkGameConditions();
	updateBonus(deltaTime);
}

void GameState::handleInput()
{
	float direction = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction += 1.f;
	}

	platform_->move(direction * platformSpeed_);
	clampPlatformPosition();
}

void GameState::clampPlatformPosition()
{
	sf::FloatRect bounds = platform_->getGlobalBounds();
	sf::Vector2f position = platform_->getPosition();

	if (position.x < 0.f)
	{
		platform_->setPosition(0.f, position.y);
	}
	else if (position.x + bounds.width > SCREEN_WIDTH)
	{
		platform_->setPosition(SCREEN_WIDTH - bounds.width, position.y);
	}
}

void GameState::updateBall(float deltaTime)
{
	ball_->update(deltaTime);
	checkCollisions();
}

// Not used
// void GameState::AccelerationBallSpeed(float deltaTime)
// {
// 	ballSpeedChangeTimer_ += deltaTime;
//
// 	if (ballSpeedChangeTimer_ >= ballSpeedChangeInterval_)
// 	{
// 		ballSpeedChangeTimer_ = 0.f;
// 		currentBallSpeedMultiplier_ = std::min(maxBallSpeedMultiplier_, currentBallSpeedMultiplier_ * 1.05f);
//
// 		// Масштаб спрайта мяча пропорционален скорости
// 		float ratio = (currentBallSpeedMultiplier_ - minBallSpeedMultiplier_) / (maxBallSpeedMultiplier_ - minBallSpeedMultiplier_);
// 		float scale = 1.0f + ratio * 0.2f;
// 		const_cast<sf::Sprite&>(ball_->getSprite()).setScale(scale, scale);
//
// 		ball_->setSpeedMultiplier(currentBallSpeedMultiplier_);
// 	}
// }

void GameState::initBricks()
{
	bricks_.clear();
	bonuses_.clear();

	static constexpr int rows = 5;
	static constexpr int cols = 8;
	static constexpr float brickWidth = 90.f;
	static constexpr float brickHeight = 25.f;
	static constexpr float spacing = 5.f;
	static constexpr float startY = 50.f;

	const float totalWidth = cols * (brickWidth + spacing) - spacing;
	const float startX = (SCREEN_WIDTH - totalWidth) / 2.f;

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// 1. Создаём список всех возможных позиций
	std::vector<sf::Vector2f> positions;
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			float x = startX + col * (brickWidth + spacing);
			float y = startY + row * (brickHeight + spacing);
			positions.emplace_back(x, y);
		}
	}

	// 2. Перемешиваем позиции
	std::random_shuffle(positions.begin(), positions.end());

	// 3. Создаём кирпичи и ставим их на случайные позиции
	int totalBricks = rows * cols;
	for (int i = 0; i < totalBricks; ++i)
	{
		std::unique_ptr<Block> brick;

		// Рандомный тип кирпича
		int typeChance = std::rand() % 100;
		if (typeChance < SPAWN_BRICK_STRONG_PERCENT)  // 10% - Strong
		{
			brick = std::make_unique<StrongBrick>();
			brick->setTexture(textureManager.get("brick_strong"));
		}
		else if (typeChance < SPAWN_BRICK_GLASS_PERCENT)  // 25% - Glass
		{
			brick = std::make_unique<GlassBrick>();
			brick->setTexture(textureManager.get("brick_glass"));
		}
		else  // 65% - Normal
		{
			brick = std::make_unique<NormalBrick>();
			brick->setTexture(textureManager.get("brick_normal"));
		}

		// Шанс на бонус
		if (std::rand() % 100 < BONUS_DROP_CHANCE_PERCENT)
		{
			int bonusType = std::rand() % 3;
			brick->SetRandomBonus(bonusType);
		}

		brick->setPosition(positions[i].x, positions[i].y);
		bricks_.push_back(std::move(brick));
	}
}

void GameState::checkCollisions()
{
	Math::checkWallCollisions(ball_);
	Math::checkPlatformCollision(platform_, ball_);
	checkBrickCollisions();
}

void GameState::checkBrickCollisions()
{
	for (auto& brick : bricks_)
	{
		if (Math::isBrickHitByBall(brick, ball_))
		{
			brick->hit();  // Удар по кирпичу

			if (brick->isDestroyed())
			{
				// Очки
				if (dynamic_cast<NormalBrick*>(brick.get()))
				{
					scoreSystem_.addScore(ScoreSystem::BrickType::Normal);
				}
				else if (dynamic_cast<StrongBrick*>(brick.get()))
				{
					scoreSystem_.addScore(ScoreSystem::BrickType::Strong);
				}
				else if (dynamic_cast<GlassBrick*>(brick.get()))
				{
					scoreSystem_.addScore(ScoreSystem::BrickType::Glass);
				}

				pushBonus(*brick);	// Бонус
			}

			if (brick->shouldBallBounce())
			{
				Math::handleBrickCollisionResponse(*brick, ball_);
			}

			break;	// Только одно столкновение за кадр
		}
	}
}

void GameState::pushBonus(Block& brick)
{
	if (brick.GetBonus().GetBonusType() == BonusType::None)
	{
		return;	 // Нет бонуса — ничего не делать
	}

	// Начальная позиция бонуса — центр кирпича
	sf::Vector2f brickPosition = sf::Vector2f(brick.getSprite().getPosition().x, brick.getSprite().getPosition().y);

	// Инициализация бонуса и добавление в список активных
	brick.GetBonus().initBonus(brickPosition);
	bonuses_.push_back(brick.GetBonus());
}

void GameState::updateBonus(float deltaTime)
{
	for (auto it = bonuses_.begin(); it != bonuses_.end();)
	{
		it->update(deltaTime);

		if (it->checkBonusWithPlatformCollision(platform_))
		{
			// Очищаем таймер, когда пересеклись с платформой
			bonusClockTimer_.restart();
			currentBonusActivity = it->GetBonusType();
			it = bonuses_.erase(it);
		}
		else
		{
			++it;
		}
	}

	// TODO: Создать метод, куда перенесём логику текущего активного бонуса
	if (currentBonusActivity != BonusType::None && bonusClockTimer_.getElapsedTime().asSeconds() >= BONUS_ACTIVITY_DURATION)
	{
		currentBonusActivity = BonusType::None;
		ball_->setTexture(textureManager.get("ball"));
		ball_->setSpeedMultiplier(BALL_SPEED);
		bonusClockTimer_.restart();
	}
	else if (currentBonusActivity == BonusType::FireBall)
	{
		ball_->setTexture(textureManager.get("fireball"));
		ball_->setSpeedMultiplier(FIREBALL_SPEED);
	}
	else if (currentBonusActivity == BonusType::BrittleBrick)
	{
		ball_->setTexture(textureManager.get("ball"));
		ball_->setSpeedMultiplier(BALL_SPEED);
	}
	else if (currentBonusActivity == BonusType::BoostPlatformSpeed)
	{
		ball_->setTexture(textureManager.get("ball"));
		ball_->setSpeedMultiplier(BALL_SPEED);
	}
}

void GameState::clearBonus()
{
	bonuses_.clear();
}

// void GameState::handleBrickCollisionResponse(const Block& brick)
// {
// 	sf::FloatRect ballBounds = ball_->getGlobalBounds();
// 	sf::FloatRect brickBounds = brick.getGlobalBounds();
//
// 	// Вычисляем степень перекрытия с каждой стороны
// 	float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
// 	float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
// 	float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
// 	float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;
//
// 	// Определение стороны удара
// 	bool fromLeft = overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom;
// 	bool fromRight = overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom;
// 	bool fromTop = overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom;
// 	bool fromBottom = overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop;
//
// 	// Инвертируем соответствующую компоненту вектора скорости
// 	if (fromLeft || fromRight)
// 		ball_->reverseX();
// 	if (fromTop || fromBottom)
// 		ball_->reverseY();
// }

// void GameState::checkBonusWithPlatformCollision()
// {
// 	// bonuses_.erase(std::remove_if(bonuses_.begin(), bonuses_.end(), [&](const Bonus& bonus) {
// 	// 	return bonus.getSprite().getGlobalBounds().intersects(platform_->getGlobalBounds());
// 	// }),
// 	// 	bonuses_.end());
// }

void GameState::checkGameConditions()
{
	checkLoseCondition();
	checkWinCondition();
}

void GameState::checkLoseCondition()
{
	// Если мяч улетел ниже экрана — поражение
	if (ball_->getPosition().y - ball_->getRadius() > SCREEN_HEIGHT)
	{
		gameLost_ = true;
		scoreSystem_.saveToHighscores();
	}
}

void GameState::checkWinCondition()
{
	// Победа, если все кирпичи уничтожены
	bool allDestroyed = std::all_of(bricks_.begin(), bricks_.end(),
		[](const auto& brick) { return brick->isDestroyed(); });

	if (allDestroyed)
	{
		gameWon_ = true;
		scoreSystem_.saveToHighscores();
	}
}

void GameState::render()
{
	window_->clear();

	// Отрисовка фона
	window_->draw(background_);

	// Отрисовка счёта
	window_->draw(scoreText_);
	window_->draw(highscoreText_);

	// Отрисовка всех кирпичей
	for (const auto& brick : bricks_)
	{
		brick->draw(*window_);
	}

	// Отрисовка бонусов
	for (const Bonus& bonus : bonuses_)
	{
		window_->draw(bonus.getSprite());
	}

	// Отрисовка платформы и мяча
	window_->draw(platform_->getSprite());
	window_->draw(ball_->getSprite());

	// Отрисовка текста победы/поражения, если нужно
	if (gameWon_)
		window_->draw(winText_);
	if (gameLost_)
		window_->draw(loseText_);

	window_->display();
}

void GameState::showWinScreen()
{
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
			if (event.key.code == sf::Keyboard::Space)
			{
				resetGame();  // Перезапустить игру
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				window_->close();  // Выйти из игры
			}
		}
	}
}

void GameState::showLoseScreen()
{
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
			if (event.key.code == sf::Keyboard::Space)
			{
				resetGame();  // Перезапустить игру
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				window_->close();  // Закрыть окно
			}
		}
	}
}

void GameState::resetGame()
{
	// Сброс флагов
	gameWon_ = false;
	gameLost_ = false;
	currentBallSpeedMultiplier_ = 1.0f;
	ballSpeedChangeTimer_ = 0.0f;

	// Переинициализация мяча
	ball_->reset(400, 500);
	ball_->setVelocity(sf::Vector2f(180.f, -220.f));

	// Сброс позиции платформы
	platform_->setPosition(350, 550);

	// Пересоздание кирпичей
	initBricks();
	updateScoreDisplay(scoreSystem_.getCurrentScore());
}