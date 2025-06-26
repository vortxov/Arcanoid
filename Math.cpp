#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics/Rect.hpp>
#include "Ball.h"
#include "Brick.h"
#include "Platform.h"

void Math::checkWallCollisions(const std::unique_ptr<Ball>& ball)
{
	sf::Vector2f ballPos = ball->getPosition();
	float radius = ball->getRadius();

	if (ballPos.x - radius <= 0)
	{
		ball->reverseX();
		ball->setPosition(radius, ballPos.y);
	}
	else if (ballPos.x + radius >= SCREEN_WIDTH)
	{
		ball->reverseX();
		ball->setPosition(SCREEN_WIDTH - radius, ballPos.y);
	}

	if (ballPos.y - radius <= 0)
	{
		ball->reverseY();
		ball->setPosition(ballPos.x, radius);
	}
}

void Math::checkPlatformCollision(const std::unique_ptr<Platform>& platform, const std::unique_ptr<Ball>& ball)
{
	// Проверка на пересечение мяча и платформы
	if (ball->getGlobalBounds().intersects(platform->getGlobalBounds()))
	{
		sf::Vector2f platformPos = platform->getPosition();

		// Центр платформы
		float platformCenter = platformPos.x + platform->getGlobalBounds().width / 2;

		// Насколько далеко точка удара от центра платформы (-1 ... 1)
		float hitPos = (ball->getPosition().x - platformCenter) / (platform->getGlobalBounds().width / 2);

		// Ограничиваем hitPos, чтобы избежать ошибок
		hitPos = Math::clamp(hitPos, -1.f, 1.f);

		float speed = BALL_SPEED;
		sf::Vector2f newVel;
		newVel.x = hitPos * speed;

		float xSquared = newVel.x * newVel.x;
		float ySquared = speed * speed - xSquared;

		// Безопасный расчёт y — избегаем sqrt(отрицательного)
		newVel.y = (ySquared > 0.f) ? -std::sqrt(ySquared) : -1.f;

		ball->setVelocity(newVel);
	}
}

bool Math::isBrickHitByBall(const std::unique_ptr<Brick>& brick, const std::unique_ptr<Ball>& ball)
{
	// Проверка столкновения
	// Если кирпич ещё не разрушен и есть столкновение с мячом
	return !brick->isDestroyed() && ball->getGlobalBounds().intersects(brick->getGlobalBounds());
}

void Math::handleBrickCollisionResponse(const Brick& brick, const std::unique_ptr<Ball>& ball)
{
	sf::FloatRect ballBounds = ball->getGlobalBounds();
	sf::FloatRect brickBounds = brick.getGlobalBounds();

	// Вычисляем степень перекрытия с каждой стороны
	float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
	float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
	float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
	float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

	// Определение стороны удара
	bool fromLeft = overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom;
	bool fromRight = overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom;
	bool fromTop = overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom;
	bool fromBottom = overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop;

	// Инвертируем соответствующую компоненту вектора скорости
	if (fromLeft || fromRight)
		ball->reverseX();
	if (fromTop || fromBottom)
		ball->reverseY();
}