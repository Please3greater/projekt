#include "bullet.h"

Bullet::Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
    return getGlobalBounds();
}

const sf::Vector2f &Bullet::getPos() const
{
    return getPosition();
}

Bullet::Bullet(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed, float rotation)
{
    setTexture(*texture);
    setPosition(posX,posY);
    scale(0.5,0.5);
    setRotation(rotation);

    direction.x = dirX;
    direction.y = dirY;
    movementSpeed = movement_speed;
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    move(this->movementSpeed * this->direction);
}

void Bullet::render(Bullet* sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}
