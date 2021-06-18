#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    float attackCooldownMax;
    float attackCooldown;

    const int HPMax = 1000;
    int HP;

    int damage;

    // funckje prywatne
    void initializeTexture();
    void initializeSprite();

public:
    Player();
    virtual ~Player();

    //getter do pozycji gracza dla pocisku
    const sf::Vector2f &getPos() const;
    const sf::FloatRect getBounds() const;

    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);

    //funkcje
    void animate(const float dirX, const float dirY);
    int getHP() ;
    int getHPMax();
    void decreaseHP(int damage);
    int Hit();
    bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget &target);
};

#endif // PLAYER_H
