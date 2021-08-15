#ifndef BOSS_H
#define BOSS_H

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>



class Boss : public sf::Sprite
{
private:
    sf::Vector2f direction;
    float movementSpeed;

public:
    Boss();
    Boss(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed, float rotation);
    virtual ~Boss();

    const sf::FloatRect getBounds() const;
    const sf::Vector2f &getPos() const;

    void updateAttack();
    void update();
    void render(Boss *sprite, sf::RenderTarget *target);
};

#endif // BOSS_H
