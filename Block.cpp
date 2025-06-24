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

void Block::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

void Block::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

void Block::setCurrentBrickType(EBT_BrickType brickType)
{
	if (currentBrickType_ == brickType)
	{
		return;
	}

	pastBrickType_ = currentBrickType_;
	currentBrickType_ = brickType;
}

void Block::updateState(TextureManager& textureManager)
{
	switch (currentBrickType_)
	{
		case EBT_BrickType::EBT_Normal:
		{
			shouldBallBounce_ = true;
			setTexture(textureManager.get("brick_normal"));
			break;
		}
		case EBT_BrickType::EBT_Glass:
		{
			shouldBallBounce_ = false;
			setTexture(textureManager.get("brick_glass"));
			break;
		}
		case EBT_BrickType::EBT_Strong:
		{
			shouldBallBounce_ = true;
			setTexture(textureManager.get("brick_strong"));
			break;
		}
		case EBT_BrickType::EBT_None:
		{
			break;
		}
	}
}

void Block::draw(sf::RenderWindow& window) const
{
	if (!destroyed_)
	{
		window.draw(sprite_);
	}
}