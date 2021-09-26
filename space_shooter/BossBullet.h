#ifndef BOSSBULLET_H
#define BOSSBULLET_H
#include <iostream>
#include<SFML/Graphics.hpp>


class BossBullet : public sf::Sprite
{
private:
    sf::Vector2f direction;
    float movementSpeed;

public:
    BossBullet();
    BossBullet(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed);
    virtual ~BossBullet();

    // krawedzie pocisku
    const sf::FloatRect getBounds() const;
    const sf::Vector2f &getPos() const;

    void updateAttack();
    void update();
    void render(BossBullet *sprite, sf::RenderTarget *target);
};

#endif // BOSSBULLET_H
