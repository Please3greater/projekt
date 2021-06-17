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
    float attackCooldown;
    float attackCooldownMax;


    // funckje prywatne
    void initializeVariables();
    void initializeTexture();
    void initializeSprite();

public:
    Player();
    virtual ~Player();

    //getter do pozycji gracza dla pocisku
    const sf::Vector2f &getPos() const;

    //funkcje
//    std::pair<int,int> getRandomPosition(int &res_x, int &res_y);
    void animate(const float dirX, const float dirY);
    bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget &target);
};

#endif // PLAYER_H
