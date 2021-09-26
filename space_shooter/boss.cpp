#include "boss.h"


const sf::FloatRect Boss::getBounds() const
{
    return getGlobalBounds();
}

const sf::Vector2f &Boss::getPos() const
{
    return getPosition();
}

bool Boss::canAttack()
{
    if(attackCooldown >= attackCooldownMax)
    {
        attackCooldown = 0.f;
        return true;
    }
    if(this->attackCooldown < this->attackCooldownMax)
    {
//        this->attackCooldown++;
        this->attackCooldown += 0.5f * attackSpeed;
        return false;
    }
    return false;
}


void Boss::updateAttack()
{
//    if(this->attackCooldown < this->attackCooldownMax)
//    {
//    this->attackCooldown += 0.5f * attackSpeed;
//    }
}


Boss::Boss(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movement_speed,
           float scaleX, float scaleY, int hp)
    : damage(1), attackCooldownMax(5.f), attackCooldown(attackCooldownMax), attackSpeed(5.0f)
{
    setTexture(*texture);
    setPosition(posX,posY);
    scale(scaleX,scaleY);
    direction.x = dirX;
    direction.y = dirY;
    movementSpeed = movement_speed;
    setOrigin(102/2,84/2);
    this->HP = hp;
}

Boss::~Boss()
{

}

const int &Boss::getHP() const
{
    return this->HP;
}

void Boss::decreaseHP()
{
    this->HP--;
}

int Boss::Hit()
{
    return damage;
}

void Boss::speedUpAttack()
{
    attackSpeed *= 1.5;
}

void Boss::update(int rotation)
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();

    if(rectangle_bounds.top+rectangle_bounds.height > 750)
    {
        direction.y = -(direction.y);
    }
    if(rectangle_bounds.top < 50)
    {
        direction.y = -(direction.y);
    }
    move(this->movementSpeed * this->direction);
    rotate(rotation);
}

int Boss::getRotation2(Boss* sprite)
{
    int zm = sprite->getRotation();
    return zm;
}

void Boss::render(Boss* sprite, sf::RenderTarget *target)
{
    target->draw(*sprite);
}

