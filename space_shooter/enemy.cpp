#include "enemy.h"
//#include "explosion.h"

Enemy::Enemy()
{

}

sf::FloatRect Enemy::getBounds() // tu musi byc kopia bo bedzie sie bugowac
{
    return getGlobalBounds();
}

const sf::Vector2f &Enemy::getPos() const
{
    return getPosition();
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
    setTexture(*texture);
    setPosition(posX,posY);
    scale(scaleX,scaleY);
    setOrigin(93/2,84/2);
    this->HP = hp;

    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
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

// zmienianie kierunku ruchu statku wroga
void Enemy::update()
{
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top+rectangle_bounds.height > 400)
        {
            direction.y = -(direction.y);
        }
        if(rectangle_bounds.top < 0)
        {
            direction.y = -(direction.y);
        }
        if(rectangle_bounds.left+rectangle_bounds.width > 500)
        {
            direction.x = -(direction.x);
        }
        if(rectangle_bounds.left < 0)
        {
            direction.x = -(direction.x);
        }
        move(this->movementSpeed * this->direction);
}

void Enemy::render(Enemy *sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}
