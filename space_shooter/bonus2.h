#ifndef BONUS2_H
#define BONUS2_H

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class bonus2 : public sf::Sprite
{
private:
    sf::Sprite shape;
    sf::Vector2f direction;
    float movementSpeed;

public:
    bonus2();
    bonus2(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed);
    virtual ~bonus2();

    // krawedzie grafiki
    const sf::FloatRect getBounds() const;

    void update();
    void render(bonus2* sprite, sf::RenderTarget *target);


};

#endif // BONUS2_H
