#include "game.h"

//funkcje prywatne
void Game::initializeWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(500,800), "Projekt");
    this->window->setFramerateLimit(60);
}

void Game::initializeTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("./../space_shooter/pocisk1.png");
    this->textures["ENEMY1"] = new sf::Texture();
    this->textures["ENEMY1"]->loadFromFile("./../space_shooter/enemy1.png");
}

void Game::initializePlayer()
{
    this->player = new Player();
}

void Game::initializeEnemies()
{
    this->spawnTimerMax = 50.0f;
    this->spawnTimer = this->spawnTimerMax;
}


// KONSTRUKTOR
Game::Game()
{
    this->initializeWindow();
    this->initializeTextures();
    this->initializePlayer();
    this->initializeEnemies();
}
// DESTRUKTOR
Game::~Game()
{
    delete this->window;
    delete this->player;

    // usuwanie tekstur
    for (auto &tex : textures)
    {
        delete tex.second; //
//        delete tex.first;
    }
    // usuwanie pociskow
    for (auto &bull : bullets)
    {
        delete bull;
    }

    for (auto &enemy : enemies)
    {
        delete enemy;
    }

}






//funkcje publiczne

// funkcja glowna
void Game::run()
{
    while(this->window->isOpen())
    {
        this->update();
        this->render();
    }
}

/// obsluga eventow
void Game::updatePollEvents()
{
    sf::Event event;
    while(this->window->pollEvent(event))
    {
        if(event.Event::type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::updateInput()
{
    // Ruszanie sie naszego statku
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->player->animate(0.f,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->player->animate(0.f,1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player->animate(-1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player->animate(1.f,0.f);
    }
    if( player->canAttack()) //sf::Mouse::isButtonPressed(sf::Mouse::Left) and
    {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x,this->player->getPos().y,0.f,-10.f,1.f));
//        this->enemies.push_back(new Enemy(this->textures["ENEMY1"], this->player->getPos().x,this->player->getPos().y,0.f,-10.f,1.f));
        //    }
    }


//    for (int i=0; i<2; i++)
//    {
//    auto[x,y] = getRandomPosition(window_width,window_height);
//    this->enemies.setPos(x,y);

//        this->enemies.push_back(new Enemy(this->textures["ENEMY1"], this->player->getRandomPosition().x,this->player->getRandomPosition().y,0.f,-10.f,1.f));
//    }
}

void Game::updateBullets()
{
    int counter = 0;
    for (auto *bull : bullets)
    {
        bull->update();

        //usuwanie pociskow
        if(bull->getBounds().top + bull->getBounds().height < 0.f)
        {
            //usuwanie konkretnego wskaznika
            delete this->bullets.at(counter);
            //usuwanie go z wektora
            this->bullets.erase(this->bullets.begin()+counter);
            --counter;


        }
        std::cout<< this->bullets.size() << std::endl;
        ++counter;
    }
}

void Game::updateEnemies()
{
    this->spawnTimer +=0.5f;
    if(this->spawnTimer >= this->spawnTimerMax)
    {
//        for (int i =0; i<10;i++)
//        {
            this->enemies.push_back(new Enemy(this->textures["ENEMY1"], rand()%this->window->getSize().x,rand()%this->window->getSize().y/2,2.f,2.f,1.f));
            this->spawnTimer = 0.f;
//        }
    }
    for (auto *enemy : enemies)
    {
        enemy->update();
    }

//    int counter = 0;
//    for (auto *bull : bullets)
//    {
//        bull->update();

//        //usuwanie pociskow
//        if(bull->getBounds().top + bull->getBounds().height < 0.f)
//        {
//            //usuwanie konkretnego wskaznika
//            delete this->bullets.at(counter);
//            //usuwanie go z wektora
//            this->bullets.erase(this->bullets.begin()+counter);
//            --counter;


//        }
//        std::cout<< this->bullets.size() << std::endl;
//        ++counter;
//    }
}


void Game::update()
{
    this->updatePollEvents();
    this->updateInput();
    this->player->update();
    this->updateBullets();
    this->updateEnemies();

}


/// rysowanie
void Game::render()
{
    this->window->clear();

    // rysowanie wszystkiego
    this->player->render(*this->window);

    for (auto *bull : bullets)
    {
        bull->render(this->window);
    }
    for (auto *enemy : enemies)
    {
        enemy->render(this->window);
    }
    this->window->display();
}














