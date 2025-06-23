#include "Bonus.h"
#include <assert.h>

#include "Constants.h"
#include "Platform.h"

void Bonus::SetRandomBonusType(int randomBonusType)
{
	if (randomBonusType < 0 || randomBonusType > 2)
	{
		return;
	}

	if (randomBonusType == 0)
	{
		bonusType = BonusType::BrittleBrick;
	}
	else if (randomBonusType == 1)
	{
		bonusType = BonusType::FireBall;
	}
	else if (randomBonusType == 2)
	{
		bonusType = BonusType::BoostPlatformSpeed;
	}
}

bool Bonus::checkBonusWithPlatformCollision(const std::unique_ptr<Platform>& platform) const
{
	return getSprite().getGlobalBounds().intersects(platform->getGlobalBounds());
}

void Bonus::update(float deltaTime)
{
	sf::Vector2f newPosition = sf::Vector2f(sprite_.getPosition().x, (sprite_.getPosition().y) + BONUS_FALLING_SPEED * deltaTime);

	sprite_.setPosition(newPosition);
}

void Bonus::draw(sf::RenderWindow window)
{
	window.draw(sprite_);
}

sf::FloatRect Bonus::getBounds() const
{
	return sprite_.getGlobalBounds();
}

void Bonus::initBonus(const sf::Vector2f& brickPosition)
{
	switch (bonusType)
	{
		case BonusType::BrittleBrick:
		{
			assert(texture.loadFromFile("resources/textures/glass_blocks_bonus.png"));
			break;
		}
		case BonusType::FireBall:
		{
			assert(texture.loadFromFile("resources/textures/fireball_bonus.png"));
			break;
		}
		case BonusType::BoostPlatformSpeed:
		{
			assert(texture.loadFromFile("resources/textures/platform_bonus.png"));	// TODO: Другую текстурку
			break;
		}
		default:
			break;
	}

	sprite_.setScale(sf::Vector2f(0.5f, 0.5f));
	sprite_.setOrigin(0.5f, 0.5f);	// TODO: Сделать текстуру по центру, чтобы при разрушение кирпича, она спавнилась по центру
	sprite_.setPosition(brickPosition.x + 15.f, brickPosition.y);
	sprite_.setTexture(texture);
}
