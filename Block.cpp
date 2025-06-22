#include "Block.h"

Block::Block()
	: hitPoints_(1)
	, destroyed_(false)
{
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
	sprite_.setColor(sf::Color::White);
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