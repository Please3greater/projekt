#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player : public sf::Sprite
{
private:
    sf::Texture texture;
    float movementSpeed;
    float attackCooldownMax;
    float attackCooldown;
    float attackSpeed;

    const int HPMax = 100;
    int HP;

    int damage;

public:
    bool czyMaTarcze = false;
    Player();
    virtual ~Player();

    //getter do pozycji gracza dla pocisku
    const sf::Vector2f &getPos() const;
    const sf::FloatRect getBounds() const;

    void setPosition2(const float x, const float y);

    //funkcje
    void animate(const float dirX, const float dirY);
    int getHP() ;
    int getHPMax();
    void decreaseHP(int damage);
    void increaseHP(int damage);
    bool canAttack();
    void updateAttack();
    void speedUpAttack();
    void update();
    void render(Player* player, sf::RenderTarget &target);

    void initializeTexture();
    void initializeSprite();
};

#endif // PLAYER_H
