#include "bonus3.h"

#include "bonus.h"

bonus3::bonus3()
{

}

const sf::FloatRect bonus3::getBounds() const
{
    return this->shape.getGlobalBounds();
}

bonus3::bonus3(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
    this->shape.setTexture(*texture);
    this->shape.setScale(2,2);

    this->shape.setPosition(posX,posY);
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
}

bonus3::~bonus3()
{

}

void bonus3::update()
{
    this->shape.move(this->movementSpeed * this->direction);
}

void bonus3::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}

