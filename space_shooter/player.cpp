#include "player.h"

                            // FUNKCJE PRYWATNE
void Player::initializeTexture()
{
    // wczytywanie tekstur
    if (!this->texture.loadFromFile("./../space_shooter/Tekstury/nasz.png"))
    {
        std::cout<<"Error occured in player texture loading"<<std::endl;
    }
}


void Player::initializeSprite(Player *sprite)
{
    //wczytywanie tekstur do spritow
    sprite->setTexture(this->texture);
    sprite->scale(0.5f,0.5f);
//    sprite->setPosition(250,640);
    sprite->setOrigin(112.0/2.0,75.0/2.0);
}

//KONSTRUKTOR I DESTRUKTOR
Player::Player()
    :      movementSpeed(10.f),
           attackCooldownMax(5.f),
           attackCooldown(attackCooldownMax),
           HP(HPMax),
           damage(1)
{
//    this->initializeTexture();
//    this->initializeSprite();
}

Player::~Player()
{

}


// FUNKCJE PUBLICZNE
const sf::Vector2f &Player::getPos(Player *sprite) const
{
    return sprite->getPosition();
}

const sf::FloatRect Player::getBounds(Player *sprite) const
{
    return sprite->getGlobalBounds();
}

void Player::setPosition2(Player *sprite, const float x, const float y)
{
    sprite->setPosition(x,y);
}

int Player::getHP(Player *sprite)
{
    return sprite->HP;
}
int Player::getHPMax(Player *sprite)
{
    return sprite->HPMax;
}

void Player::decreaseHP(Player *sprite, int damage)
{
    sprite->HP -= damage;
}

void Player::increaseHP(Player *sprite, int damage)
{
    sprite->HP = HP + damage;
}

//int Player::Hit(Player *sprite)
//{
//    return sprite->damage;
//}


//animacje z kolizje ze scianami
void Player::animate(Player *sprite, const float dirX, const float dirY)
{
//    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    sf::FloatRect sprite_bounds = sprite->getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and sprite->getGlobalBounds().top > 0) // wartosci stale
    {
        sprite->move(0,this->movementSpeed * dirY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sprite_bounds.top+sprite_bounds.height < 800) // dopoki prawda jest ze wysokosc okna < niz ustawiona
    {
        sprite->move(0,this->movementSpeed * dirY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and sprite->getGlobalBounds().left > 0)
    {
        sprite->move(this->movementSpeed * dirX,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and sprite_bounds.left+sprite_bounds.width < 500)
    {
        sprite->move(this->movementSpeed * dirX,0);
    }

}

//licznik do inicjalizacji wyrzutu pocisku
bool Player::canAttack(Player* player)
{
    if(player->attackCooldown >= player->attackCooldownMax)
    {
        player->attackCooldown = 0.f;
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

void Player::update(Player* player)
{
    player->updateAttack();
}

void Player::render(Player* player, sf::RenderTarget &target)
{
    target.draw(*player);
}
