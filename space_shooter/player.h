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

    const int HPMax = 1000;
    int HP;

    int damage;



public:
    Player();
    virtual ~Player();

    //getter do pozycji gracza dla pocisku
    const sf::Vector2f &getPos(Player *sprite) const;
    const sf::FloatRect getBounds(Player *sprite) const;

//    void setPosition(const sf::Vector2f pos);
    void setPosition2(Player *sprite, const float x, const float y);

    //funkcje
    void animate(Player *sprite, const float dirX, const float dirY);
    int getHP(Player *sprite) ;
    int getHPMax(Player *sprite);
    void decreaseHP(Player *sprite, int damage);
    void increaseHP(Player *sprite, int damage);
//    int Hit(Player *sprite);
    bool canAttack(Player* player);
    void updateAttack();
    void update(Player* player);
    void render(Player* player, sf::RenderTarget &target);

    // funckje prywatne
    void initializeTexture();
    void initializeSprite(Player *sprite);
};

#endif // PLAYER_H
