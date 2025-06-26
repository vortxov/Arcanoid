#include "Ball.h"
#include "Constants.h"
#include <random>

Ball::Ball(float radius)
	: radius_(radius)
	, speedMultiplier_(1.0f)
	, position_(0, 0)
	, velocity_(0, 0)
{
	sprite_.setOrigin(radius / 2.f, radius / 2.f);
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
}

void Ball::reverseX()
{
	velocity_.x = -velocity_.x;
}

void Ball::reverseY()
{
	velocity_.y = -velocity_.y;
}

sf::Sprite& Ball::getSprite()
{
	return sprite_;
}

sf::FloatRect Ball::getGlobalBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const
{
	return position_;
}

sf::Vector2f Ball::getRandomBallDirection()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(45.f, 180.f);

	float vx = dist(gen);

	// Случайный знак
	if (std::uniform_int_distribution<int>(0, 1)(gen) == 0)
	{
		vx = -vx;
	}

	return sf::Vector2f(vx, -BALL_SPEED);
}

// sf::Vector2f Ball::getVelocity() const
// {
// 	return velocity_ * speedMultiplier_;
// }

float Ball::getRadius() const
{
	return radius_;
}

// float Ball::getSpeedMultiplier() const
// {
// 	return speedMultiplier_;
// }
