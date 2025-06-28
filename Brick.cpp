#include "Brick.h"

Brick::Brick(int blowsToDestroy, bool shouldBallBounce)
{
	hitPoints_ = blowsToDestroy;
	destroyed_ = false;
	shouldBallBounce_ = shouldBallBounce;
	currentBrickType_ = EBT_BrickType::EBT_None;
	pastBrickType_ = currentBrickType_;
}

void Brick::SetRandomBonus(int random_bonus)
{
	bonus.SetRandomBonusType(random_bonus);
}

void Brick::hit()
{
	if (--hitPoints_ <= 0)
	{
		destroyed_ = true;
	}
}

void Brick::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

void Brick::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

void Brick::setCurrentBrickType(EBT_BrickType brickType, bool savePastBrickType)
{
	if (savePastBrickType)
	{
		pastBrickType_ = currentBrickType_;
	}
	currentBrickType_ = brickType;
}

void Brick::setPastBrickType(EBT_BrickType brickType)
{
	pastBrickType_ = brickType;
}


void Brick::applyBrittle()
{
	// Сохраняем только если ещё не был стеклянным
	if (currentBrickType_ != EBT_BrickType::EBT_Glass)
	{
		pastBrickType_ = currentBrickType_;
		currentBrickType_ = EBT_BrickType::EBT_Glass;
	}
}

void Brick::updateState(TextureManager& textureManager)
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

void Brick::draw(sf::RenderWindow& window) const
{
	if (!destroyed_)
	{
		window.draw(sprite_);
	}
}