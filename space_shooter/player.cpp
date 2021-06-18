#include "player.h"

                            // FUNKCJE PRYWATNE
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
    :      movementSpeed(10.f),
           attackCooldownMax(5.f),
           attackCooldown(attackCooldownMax),
           HP(HPMax),
           damage(1)
{
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

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x,y);
}

int Player::getHP()
{
    return HP;
}
int Player::getHPMax()
{
    return HPMax;
}

void Player::decreaseHP(int damage)
{
    this->HP -= damage;
}

int Player::Hit()
{
    return damage;
}


//animacje z kolizje ze scianami
void Player::animate(const float dirX, const float dirY)
{
//    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    sf::FloatRect sprite_bounds = sprite.getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and this->sprite.getGlobalBounds().top > 0) // wartosci stale
    {
        this->sprite.move(0,this->movementSpeed * dirY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sprite_bounds.top+sprite_bounds.height < 800) // dopoki prawda jest ze wysokosc okna < niz ustawiona
    {
        this->sprite.move(0,this->movementSpeed * dirY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and this->sprite.getGlobalBounds().left > 0)
    {
        this->sprite.move(this->movementSpeed * dirX,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and sprite_bounds.left+sprite_bounds.width < 500)
    {
        this->sprite.move(this->movementSpeed * dirX,0);
    }

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
