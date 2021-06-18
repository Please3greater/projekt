#include <iostream>
#include<SFML/Graphics.hpp>



class Enemy
{
private:
    sf::Sprite shape;

    sf::Vector2f direction;
    float movementSpeed;
    int type;
    int HP;
    int HPMax;
    int damage;
    float attackCooldownMax;
    float attackCooldown;

    void initializeVariables();

public:
    Enemy();
    Enemy(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed, float scaleX, float scaleY, int hp);
    virtual ~Enemy();

    // krawedzie statku
    sf::FloatRect getBounds();
    const sf::Vector2f &getPos() const;

    // HP
    const int &getHP() const;
    void decreaseHP(); //int damage
    int Hit();

    bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget *target);
};
