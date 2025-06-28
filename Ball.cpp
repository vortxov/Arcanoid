#include "Ball.h"
#include "Constants.h"
#include <random>

Ball::Ball(float radius)
	: radius_(radius)
	, speedMultiplier_(1.0f)
	, wallCollisionCount_(0)
	, position_(0, 0)
	, velocity_(0, 0)
{
}

void Ball::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

void Ball::setVelocity(const sf::Vector2f& velocity)
{
	velocity_ = velocity;
}

void Ball::setSpeedMultiplier(float multiplier)
{
	speedMultiplier_ = multiplier;
}

void Ball::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
	sf::FloatRect bounds = sprite_.getLocalBounds();
	sprite_.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite_.setScale(2 * radius_ / bounds.width, 2 * radius_ / bounds.height);
}

void Ball::update(float deltaTime)
{
	position_ += velocity_ * deltaTime * speedMultiplier_;
	sprite_.setPosition(position_);
}

void Ball::reset(float x, float y)
{
	setPosition(x, y);
	velocity_ = sf::Vector2f(0, 0);
	speedMultiplier_ = 1.0f;
	wallCollisionCount_ = 0;
}

void Ball::reverseX()
{
	velocity_.x = -velocity_.x;
}

void Ball::reverseY()
{
	velocity_.y = -velocity_.y;
}

void Ball::adjustTrajectoryIfNeeded()
{
	// Если было 3 или больше столкновений со стенами
	if (wallCollisionCount_ >= 3)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());

		// Вычисляем текущий угол движения
		float currentAngle = std::atan2(velocity_.y, velocity_.x);

		// Генерируем угол коррекции в заданном диапазоне
		std::uniform_real_distribution<float> correctionDist(MIN_CORRECTION_ANGLE, MAX_CORRECTION_ANGLE);
		float correctionAngle = correctionDist(gen) * 3.14159f / 180.0f;

		float newAngle;

		if (velocity_.y < 0)  // Мяч летит вверх - подталкиваем еще больше вверх
		{
			// Уменьшаем угол (делаем более вертикально вверх)
			newAngle = currentAngle - correctionAngle;
		}
		else  // Мяч летит вниз - подталкиваем еще больше вниз
		{
			// Увеличиваем угол (делаем более вертикально вниз)
			newAngle = currentAngle + correctionAngle;
		}

		// Вычисляем новые компоненты скорости
		velocity_.x = std::cos(newAngle) * BALL_SPEED;
		velocity_.y = std::sin(newAngle) * BALL_SPEED;

		// Сбрасываем счетчик
		wallCollisionCount_ = 0;
	}
}

sf::Vector2f Ball::getRandomBallDirection()
{
	return getRandomBallDirection(35.0f, 145.0f, true);	 // true = может лететь вверх
}

sf::Vector2f Ball::getRandomBallDirection(float minAngle, float maxAngle, bool canGoUp)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	// Генерируем угол в заданном диапазоне (в градусах)
	std::uniform_real_distribution<float> angleDist(minAngle, maxAngle);
	float angle = angleDist(gen);

	// Конвертируем в радианы
	float angleRad = angle * 3.14159f / 180.0f;

	// Вычисляем компоненты скорости
	float vx = std::cos(angleRad) * BALL_SPEED;
	float vy = std::sin(angleRad) * BALL_SPEED;

	// Случайное направление по горизонтали
	if (std::uniform_int_distribution<int>(0, 1)(gen) == 0)
	{
		vx = -vx;
	}

	// Направление по вертикали
	if (!canGoUp)
	{
		vy = std::abs(vy);	// Всегда вниз (отрицательное значение)
	}
	else
	{
		vy = -std::abs(vy);	 // Всегда вверх для старта игры
	}

	return sf::Vector2f(vx, vy);
}

float Ball::getSpeedMultiplier() const
{
	return speedMultiplier_;
}
