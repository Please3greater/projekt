#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include<SFML/Graphics.hpp>



class Bullet : public sf::Sprite
{
private:
//    sf::Sprite shape;
    sf::Vector2f direction;
    float movementSpeed;

public:
    Bullet();
    Bullet(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed, float rotation);
    virtual ~Bullet();

    // krawedzie pocisku
    const sf::FloatRect getBounds(Bullet *sprite) const;
    const sf::Vector2f &getPos(Bullet *sprite) const;

    void updateAttack();
    void update(Bullet *sprite); //, float rotation
    void render(Bullet *sprite, sf::RenderTarget *target);
};

#endif // BULLET_H
