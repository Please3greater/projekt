#include "player.h"


void Player::initializeTexture()
{
    // wczytywanie tekstur
    if (!this->texture.loadFromFile("./../space_shooter/Tekstury/nasz.png"))
    {
        std::cout<<"Error occured in player texture loading"<<std::endl;
    }
}


void Player::initializeSprite()
{
    setTexture(texture);
    scale(0.5f,0.5f);
    setOrigin(112.0/2.0,75.0/2.0);
}

Player::Player()
    :      movementSpeed(10.f),
           attackCooldownMax(5.f),
           attackCooldown(attackCooldownMax),
           attackSpeed(0.6f),
           HP(HPMax),
           damage(1)

{
}

Player::~Player()
{

}


const sf::Vector2f &Player::getPos() const
{
    return getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return getGlobalBounds();
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
    HP -= damage;
}

void Player::increaseHP(int damage)
{
    HP = HP + damage;
}


//animacje z kolizje ze scianami
void Player::animate(const float dirX, const float dirY)
{
    sf::FloatRect sprite_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and getGlobalBounds().top > 0)
    {
        move(0,this->movementSpeed * dirY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sprite_bounds.top+sprite_bounds.height < 800) // dopoki prawda jest ze wysokosc okna < niz ustawiona
    {
        move(0,this->movementSpeed * dirY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and getGlobalBounds().left > 0)
    {
        move(this->movementSpeed * dirX,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and sprite_bounds.left+sprite_bounds.width < 500)
    {
        move(this->movementSpeed * dirX,0);
    }
}

//licznik do inicjalizacji wyrzutu pocisku
bool Player::canAttack()
{
    if(attackCooldown >= attackCooldownMax)
    {
        attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if(this->attackCooldown < this->attackCooldownMax)
    {
        this->attackCooldown += 0.5f * attackSpeed;
    }
}

void Player::speedUpAttack()
{
    attackSpeed *= 1.5;
}

void Player::render(Player* player, sf::RenderTarget &target)
{
    target.draw(*player);
}
