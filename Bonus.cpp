#include "Bonus.h"

void Bonus::SetRandomBonusType(int randomBonusType)
{
    if (randomBonusType < 0 || randomBonusType > 2) {
        return;
    }

    if (randomBonusType == 0) {
        bonusType = BonusType::BrittleBrick;
    }
    else if (randomBonusType == 1) {
        bonusType = BonusType::FireBall;
    }
    else if (randomBonusType == 2) {
        bonusType = BonusType::BoostPlatformSpeed;
    }
}



void Bonus::draw(sf::RenderWindow window)
{
    window.draw(sprite_);
}

void Bonus::initBonus(const sf::Vector2f& brickPosition)
{
    switch (bonusType)
    {
    case BonusType::BrittleBrick:
        texture.loadFromFile("resources/textures/glassblocks_bonus.png");
        break;
    case BonusType::FireBall:
        texture.loadFromFile("resources/textures/fireball_bonus.png");
        break;
    case BonusType::BoostPlatformSpeed:
        texture.loadFromFile("resources/textures/random_bonus.png"); //TODO: ������ ���������
        break;
    default:
        break;
    }
    sprite_.setTexture(texture);

    sprite_.setPosition(brickPosition);

    
}
