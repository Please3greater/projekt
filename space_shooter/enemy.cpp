#include "enemy.h"

Enemy::Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

//sf::Vector2i getRandomPosition(int &res_x, int &res_y)
//{
//    int x = 0;
//    int y = 0;

//    do
//    {
//        x = rand() % res_x;
//        y = rand() % res_y;
//    }
//    while ( (y > res_y/2) );

//    return sf::Vector2i(x,y);
//}

void Enemy::initializeVariables()
{
    this->type =0;
    this->HP =0;
    this->HPMax =2;
    this->damage =1;
    this->points = 5;
}



Enemy::Enemy(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
//    posX = getRandomPosition(500,800).first;
    this->initializeVariables();
    this->shape.setTexture(*texture);

    this->shape.setPosition(posX,posY);
    this->shape.scale(0.7,0.7);
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
    this->shape.setOrigin(93/2,84/2);
}

Enemy::~Enemy()
{

}



void Enemy::update()
{

        sf::FloatRect rectangle_bounds = this->shape.getGlobalBounds();




        if(rectangle_bounds.top+rectangle_bounds.height > 400) // wartosci stale
        {
            direction.y = -(direction.y);
        }
        if(rectangle_bounds.top < 0)
        {
            direction.y = -(direction.y);
        }
        if(rectangle_bounds.left+rectangle_bounds.width > 500) // wartosci stale
        {
            direction.x = -(direction.x);
        }
        if(rectangle_bounds.left  < 0)
        {
            direction.x = -(direction.x);
        }
        else {
            this->shape.move(this->movementSpeed * this->direction);
        }
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
