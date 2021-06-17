#include "player.h"

                            // FUNKCJE PRYWATNE
void Player::initializeVariables()
{
    this->movementSpeed = 5.f;
    this->attackCooldownMax = 5.f;
    this->attackCooldown = this->attackCooldownMax;
}

void Player::initializeTexture()
{
    // wczytywanie tekstur
    if (!this->texture.loadFromFile("./../space_shooter/nasz.png"))
    {
        std::cout<<"Error occured in player texture loading"<<std::endl;
    }
}


void Player::initializeSprite()
{
    //wczytywanie tekstur do spritow
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.5f,0.5f);
    this->sprite.setPosition(250,640);
    this->sprite.setOrigin(112.0/2.0,75.0/2.0);
}

                            //KONSTRUKTOR I DESTRUKTOR
Player::Player()
{
    this->initializeVariables();
    this->initializeTexture();
    this->initializeSprite();
}

Player::~Player()
{

}
                            // FUNKCJE PUBLICZNE
const sf::Vector2f &Player::getPos() const
{
    return this->sprite.getPosition();
}



void Player::animate(const float dirX, const float dirY)
{

    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

//licznik do inicjalizacji wyrzutu pocisku
bool Player::canAttack()
{
    if(this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if(this->attackCooldown < this->attackCooldownMax)
    {
    this->attackCooldown += 0.5f;
    }
}

void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
