#include "bonus.h"

Bonus::Bonus()
{

}


const sf::FloatRect Bonus::getBounds() const
{
    return this->shape.getGlobalBounds();
}

Bonus::Bonus(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
    this->shape.setTexture(*texture);
    this->shape.setScale(0.3,0.3);

    this->shape.setPosition(posX,posY);
    this->shape.scale(0.5,0.5);
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
}

Bonus::~Bonus()
{

}

int Bonus::setHeal(int howMany)
{
    return howMany;
}

int Bonus::heal(int heal_)
{
    return heal_;
}

void Bonus::update()
{
    this->shape.move(this->movementSpeed * this->direction);
}

void Bonus::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
