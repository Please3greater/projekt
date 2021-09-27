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

    int HPMax = 150;
    int HP;

    int damage;

public:
    bool czyMaTarcze = false;

    Player();
    virtual ~Player();

    //getter do pozycji gracza dla pocisku
    const sf::Vector2f &getPos() const;
    const sf::FloatRect getBounds() const;

    //ruch
    void animate(const float dirX, const float dirY);

    //HP
    int getHP() ;
    int getHPMax();
    void decreaseHP(int damage);
    void increaseHP(int damage);

    //attack
    bool canAttack();
    void updateAttack();
    void speedUpAttack();

    //rysowanie
    void initializeTexture();
    void initializeSprite();
    void render(Player* player, sf::RenderTarget &target);
};

#endif // PLAYER_H
