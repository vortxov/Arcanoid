#include "Block.h"

Block::Block(int blowsToDestroy, bool shouldBallBounce)
{
	hitPoints_ = blowsToDestroy;
	destroyed_ = false;
	shouldBallBounce_ = shouldBallBounce;
}

void Block::SetRandomBonus(int random_bonus)
{
	bonus.SetRandomBonusType(random_bonus);
}

void Block::hit()
{
	if (--hitPoints_ <= 0)
	{
		destroyed_ = true;
	}
}

bool Block::isDestroyed() const
{
	return destroyed_;
}

void Block::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

void Block::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

void Block::draw(sf::RenderWindow& window) const
{
	if (!destroyed_)
	{
		window.draw(sprite_);
	}
}

sf::FloatRect Block::getGlobalBounds() const
{
	return sprite_.getGlobalBounds();
}