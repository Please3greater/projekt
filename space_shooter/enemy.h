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
    int points;

    void initializeVariables();

public:
    Enemy();
    Enemy(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed);
    virtual ~Enemy();

    // krawedzie pocisku
    const sf::FloatRect getBounds() const;

//    sf::Vector2i getRandomPosition(int &res_x, int &res_y);
    void updateAttack();
    void update();
    void render(sf::RenderTarget *target);
};
