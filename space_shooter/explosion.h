#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <iostream>
#include<SFML/Graphics.hpp>

class Explosion : sf::Sprite
{
private:
//    sf::Sprite sprite;

    int maxCounter;
    int counter;

public:
    Explosion();
    Explosion(float posX, float posY);
    virtual ~Explosion();

    bool timer();
    void updateTextures(std::vector<std::pair<std::string,sf::Texture*>> explosion_textures);
    void update();
    int getCounter();
    void render(Explosion* sprite, sf::RenderTarget *target);
};



#endif // EXPLOSION_H
