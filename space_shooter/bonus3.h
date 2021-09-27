#ifndef BONUS3_H
#define BONUS3_H
#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>


class bonus3
{
private:
    sf::Sprite shape;
    sf::Vector2f direction;
    float movementSpeed;
    int heal_;

public:
    bonus3();
    bonus3(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed);
    virtual ~bonus3();

    // krawedzie grafiki
    const sf::FloatRect getBounds() const;

    //uzdrawianie
    int heal(int heal_);
    int setHeal(int howMany);

    void update();
    void render(sf::RenderTarget *target);
};


#endif // BONUS3_H
