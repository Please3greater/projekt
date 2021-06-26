#include "enemy.h"

Enemy::Enemy()
:      damage(1),
       attackCooldownMax(100.f),
       attackCooldown(attackCooldownMax)
{
}


sf::FloatRect Enemy::getBounds() // tu musi byc kopia bo bedzie sie bugowac (pamiec dynamiczna)
{
    return this->shape.getGlobalBounds();
}
const sf::Vector2f &Enemy::getPos() const
{
    return this->shape.getPosition();
}

bool Enemy::canAttack()
{
    if(this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    if(this->attackCooldown < this->attackCooldownMax)
    {
        this->attackCooldown++;
    }
    return false;
}

void Enemy::updateAttack()
{
    if(this->attackCooldown < this->attackCooldownMax)
    {
    this->attackCooldown += 1.f;
    }
}

Enemy::Enemy(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed, float scaleX, float scaleY, int hp)
    :    damage(1),
         attackCooldownMax(100.f),
         attackCooldown(attackCooldownMax)
{
//    posX = getRandomPosition(500,800).first;
    this->shape.setTexture(*texture);

    this->shape.setPosition(posX,posY);
    this->shape.scale(scaleX,scaleY);
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
    this->shape.setOrigin(93/2,84/2);
    this->HP = hp;
}

Enemy::~Enemy()
{

}

const int &Enemy::getHP() const
{
    return this->HP;
}

void Enemy::decreaseHP()
{
    this->HP--;
}


int Enemy::Hit()
{
    return damage;
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
        if(rectangle_bounds.left < 0) //rectangle_bounds.left  < 0 dla tego przypadku dziwnie nie dziala
        {
            direction.x = -(direction.x);
        }
        this->shape.move(this->movementSpeed * this->direction);
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
