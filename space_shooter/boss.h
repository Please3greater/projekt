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
    int HP;
    int HPMax;
    int damage;
    float attackCooldownMax;
    float attackCooldown;
    int rotation;
    float attackSpeed;

public:
    Boss();
    Boss(sf::Texture *texture, float posX, float posY, float dirX, float dirY,  // tekstura, pozycja x i y, kierunek ruchu x i y,
          float movement_speed,float scaleX, float scaleY, int hp);             //  predkosc skala x i y, HP, rotacja
    virtual ~Boss();

    //krawedzie
    const sf::FloatRect getBounds() const;
    const sf::Vector2f &getPos() const;

    // HP
    const int &getHP() const;
    void decreaseHP();
    int Hit();

    //walka
    bool canAttack();
    void speedUpAttack();

    // ruch
    void update(int rotation);

    //render
    void render(Boss *sprite, sf::RenderTarget *target);
};

#endif // BOSS_H
