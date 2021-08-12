#ifndef BONUS_H
#define BONUS_H

#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
// jakas zmiana test

class Bonus
{
private:
    sf::Sprite shape;
    sf::Vector2f direction;
    float movementSpeed;
    int heal_;

public:
    Bonus();
    Bonus(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed);
    virtual ~Bonus();

    // krawedzie grafiki
    const sf::FloatRect getBounds() const;
    //uzdrawianie
    int heal();

    void update();
    void render(sf::RenderTarget *target);


};


#endif // BONUS_H
