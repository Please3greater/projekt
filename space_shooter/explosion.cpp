#include "explosion.h"

Explosion::Explosion()
{

}

Explosion::Explosion(float posX, float posY)
    : maxCounter(20.f), counter(maxCounter)
{
        setPosition(posX,posY);
        setScale(1,1);
        setOrigin(getGlobalBounds().width/2,getGlobalBounds().height/2);
}

bool Explosion::timer()
{
    if(this->counter >= this->maxCounter)
    {
        this->counter = 0.f;
        return true;
    }
    if(this->counter < this->maxCounter)
    {
        this->counter++;
    }
    return false;
}

void Explosion::updateTextures(std::vector<std::pair<std::string,sf::Texture*>> explosion_textures)
{
    for(int i =0; i<8; i++)
    {
        if(timer())
        {
            setTexture(*explosion_textures[i].second);
        }

    }
}

Explosion::~Explosion()
{

}

void Explosion::render(Explosion *sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}

void Explosion::update()
{
    counter--;
}

int Explosion::getCounter()
{
    return counter;
}
