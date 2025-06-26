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

void Bonus::initBonus(const sf::Vector2f& brickPosition, TextureManager& textureManager)
{
	switch (bonusType)
	{
		case BonusType::BrittleBrick:
		{
			sprite_.setTexture(textureManager.get("glass_blocks_bonus"));
			break;
		}
		case BonusType::FireBall:
		{
			sprite_.setTexture(textureManager.get("fireball_bonus"));
			break;
		}
		case BonusType::BoostPlatformSpeed:
		{
			sprite_.setTexture(textureManager.get("platform_bonus"));
			break;
		}
		default:
			break;
	}

	sprite_.setScale(sf::Vector2f(0.5f, 0.5f));
	sprite_.setOrigin(0.5f, 0.5f);	// TODO: Сделать текстуру по центру, чтобы при разрушение кирпича, она спавнилась по центру
	sprite_.setPosition(brickPosition.x + 15.f, brickPosition.y);
	
}
