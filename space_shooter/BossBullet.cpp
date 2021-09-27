#include "BossBullet.h"

BossBullet::BossBullet()
{

}

const sf::FloatRect BossBullet::getBounds() const
{
    return getGlobalBounds();
}

const sf::Vector2f &BossBullet::getPos() const
{
    return getPosition();
}

BossBullet::BossBullet(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
    setTexture(*texture);
    setPosition(posX,posY);
    scale(0.5,0.5);

    direction.x = dirX;
    direction.y = dirY;
    movementSpeed = movement_speed;
}

BossBullet::~BossBullet()
{

}


void BossBullet::update()
{
    move(this->movementSpeed * this->direction);
}

void BossBullet::render(BossBullet* sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}
