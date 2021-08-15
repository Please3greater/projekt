#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player : public sf::Sprite
{
private:
//    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    float attackCooldownMax;
    float attackCooldown;

    const int HPMax = 100;
    int HP;

    int damage;



public:
    Player();
    virtual ~Player();

    //getter do pozycji gracza dla pocisku
    const sf::Vector2f &getPos() const;
    const sf::FloatRect getBounds() const;

//    void setPosition(const sf::Vector2f pos);
    void setPosition2(const float x, const float y);

    //funkcje
    void animate(const float dirX, const float dirY);
    int getHP() ;
    int getHPMax();
    void decreaseHP(int damage);
    void increaseHP(int damage);
//    int Hit(Player *sprite);
    bool canAttack();
    void updateAttack();
    void update();
    void render(Player* player, sf::RenderTarget &target);

    // funckje prywatne
    void initializeTexture();
    void initializeSprite();
};

#endif // PLAYER_H
