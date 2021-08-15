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
    // jesli obiekty klasy Bullet dziedzicza po sf::Sprite, to zeby wywolac jakas metode klasy Bullet nie potrzeba nam odwolywac sie do obiektow
    // klasy Bullet w sposob sprite.funkcja(), tylko wystarczy sama funkcja()
    setTexture(*texture);

    setPosition(posX,posY);
    scale(0.5,0.5);
    direction.x = dirX;
    direction.y = dirY;
    movementSpeed = movement_speed;
    setRotation(rotation);
}

Bullet::~Bullet()
{

}

void Bullet::update()//, float rotation
{
    move(this->movementSpeed * this->direction);
}

void Bullet::render(Bullet* sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}
