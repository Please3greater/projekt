#include "bullet.h"

Bullet::Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

Bullet::Bullet(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
    this->shape.setTexture(*texture);

    this->shape.setPosition(posX,posY);
    this->shape.scale(0.5,0.5);
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
