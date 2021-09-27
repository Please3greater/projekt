#include "bonus2.h"

bonus2::bonus2()
{

}


const sf::FloatRect bonus2::getBounds() const
{
    return getGlobalBounds();
}

bonus2::bonus2(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
    setTexture(*texture);
    setScale(0.8,0.8);

    setPosition(posX,posY);
    direction.x = dirX;
    direction.y = dirY;
    movementSpeed = movement_speed;
}

bonus2::~bonus2()
{

}

void bonus2::update()
{
    move(this->movementSpeed * this->direction);
}

void bonus2::render(bonus2* sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}
