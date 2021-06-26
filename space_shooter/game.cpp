#include "game.h"

//funkcje prywatne
void Game::initializeWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(500,800), "Galaxy shooter");
    this->window->setFramerateLimit(60);
}

void Game::initializeTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("./../space_shooter/Tekstury/pocisk1.png");
    this->textures["BULLET2"] = new sf::Texture();
    this->textures["BULLET2"]->loadFromFile("./../space_shooter/Tekstury/pocisk2.png");
    this->textures["ENEMY1"] = new sf::Texture();
    this->textures["ENEMY1"]->loadFromFile("./../space_shooter/Tekstury/enemy1.png");
    this->textures["ENEMY2"] = new sf::Texture();
    this->textures["ENEMY2"]->loadFromFile("./../space_shooter/Tekstury/enemy2.png");
    this->textures["ENEMY3"] = new sf::Texture();
    this->textures["ENEMY3"]->loadFromFile("./../space_shooter/Tekstury/enemy3.png");
    this->textures["BONUS1"] = new sf::Texture();
    this->textures["BONUS1"]->loadFromFile("./../space_shooter/Tekstury/bonus1.png");
}

void Game::initializeBackground()
{
    if(!this->texture_background.loadFromFile("./../space_shooter/Tekstury/tlo.jpg"))
    {
        std::cout<<"Blad wczytywanie tekstury tla"<<std::endl;
    }
    background.setTexture(texture_background);
    background.setPosition(0,0);
    background.setOrigin(78,0);
    background.setScale(1,1);
}


void Game::initializeGUI()
{
    //zaladowanie fontow
    if(!this->font.loadFromFile("./../space_shooter/Fonty/font.ttf"))
    {
        std::cout<<"Blad wczytywanie fontu"<<std::endl;
    }
    //text
    this->myText.setFont(this->font);
    this->myText.setCharacterSize(50);
    this->myText.setFillColor(sf::Color::White);

    this->GameOver_text.setFont(this->font);
    this->GameOver_text.setCharacterSize(70);
    this->GameOver_text.setFillColor(sf::Color::White);
    this->GameOver_text.setString("GAME OVER");
    this->GameOver_text.setPosition(window_width/2 - GameOver_text.getGlobalBounds().width/2,window_height/2 - GameOver_text.getGlobalBounds().height/2);

    this->YouWin_text.setFont(this->font);
    this->YouWin_text.setCharacterSize(70);
    this->YouWin_text.setFillColor(sf::Color::White);
    this->YouWin_text.setString("YOU WIN!");
    this->YouWin_text.setPosition(window_width/2 - YouWin_text.getGlobalBounds().width/2,window_height/2 - YouWin_text.getGlobalBounds().height/2);


}

void Game::initializePlayer()
{
    this->player = new Player();

    this->player->setPosition2(player, 250, 640);
    this->player->initializeTexture();
    this->player->initializeSprite(player);
    this->HPMax = this->player->getHPMax(player);
}

void Game::initializeEnemies()
{
    this->spawnRule = 20.0f;
}


// KONSTRUKTOR
Game::Game()
{
    this->initializeWindow();
    this->initializeBackground();
    this->initializeTextures();
    this->initializePlayer();
    this->initializeEnemies();
    this->initializeGUI();
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
    for (auto &bull : enemy_bullets)
    {
        delete bull;
    }
    //usuwanie bonusow
    for (auto &bon : bonuses)
    {
        delete bon;
    }

    //usuwanie wrogow
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
        this->updateEvents();
        if(player->getHP(player) >0)
        {
            this->update();
        }
        this->render();
    }
}

/// obsluga eventow
void Game::updateEvents()
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
{                                                                                                // FACE TO MOUSE
    sf::Vector2f curPos;                                                                        // POZYCJA OBIEKTU
    curPos.x = player->getPos(player).x;
    curPos.y = player->getPos(player).y;

    //        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    sf::Vector2f mouse_position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));    // POZYCJA MYSZY
    float dx = curPos.x - mouse_position.x;
    float dy = curPos.y - mouse_position.y;
    const float PI = 3.14159265;
    float rotation = std::atan2(dy,dx)*180.0/PI;

    //debuger
    std::cout<<mouse_position.x<<"\t"<<mouse_position.y<<std::endl;

    player->setRotation(rotation-90);


//    for(auto *bull : bullets)
//    {
//        sf::Vector2f curPos;                                                                        // POZYCJA OBIEKTU
//        curPos.x = bull->getPos().x;
//        curPos.y = bull->getPos().y;

//        bull->setRotation(roration-90);    // pociski tez trzeba dziedziczyc po sf::Sprite, tak samo jak playera, zeby mozna bylo uzyc setRotation
//    }



    // Ruszanie sie naszego statku                                                      // OBSLUGA KLAWISZY   ( RUCH )
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player->animate(player,0.f,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player->animate(player,0.f,1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->animate(player,-1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->animate(player,1.f,0.f);
    }
    if( player->canAttack(player))                                                        // NASZE POCISKI
    {
        aimDir = mouse_position - player->getPos(player);
        aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

//        std::cout<<mouse_position.x<<"\t"<<mouse_position.y<<std::endl;
        this->bullets.push_back(new Bullet(this->textures["BULLET"],
                                player->getPos(player).x,
                                player->getPos(player).y,
                                aimDirNorm.x,
                                aimDirNorm.y,
                                10.f));
    }
}


void Game::updateBullets()
{
    int counter = 0;
    for (auto *bull : bullets)
    {
        bull->update();
//        for(auto enemy : enemies)
//        {
            //usuwanie pociskow
            if(bull->getBounds().top + bull->getBounds().height < 0.f) // or bull->getBounds().top + bull->getBounds().height < enemy->getBounds().height
            {
                //usuwanie konkretnego wskaznika
                delete this->bullets.at(counter);
                //usuwanie go z wektora
                this->bullets.erase(this->bullets.begin()+counter);
                --counter;


            }
//        }
//        std::cout<< "Liczba pociskow na ekranie: ";
//        std::cout<< this->bullets.size() << std::endl;
        ++counter;
    }
}


void Game::updateEnemyBullets()
{

    for (auto& e : enemies)                                                         // POCISKI WROGA
    {
        if( e->canAttack())
        {
            e->updateAttack();
            for (auto& enemy : enemies)
            {
                this->enemy_bullets.push_back(new Bullet(this->textures["BULLET2"], enemy->getPos().x,enemy->getPos().y,0.f,-10.f,-0.5f));
            }
        }
    }

    int counter = 0;
    for (auto *bull : enemy_bullets)
    {
        bull->update();

        //usuwanie pociskow
        if(bull->getBounds().top > window_height or player->getBounds(player).intersects(bull->getBounds()))
        {
            //usuwanie konkretnego wskaznika
            delete this->enemy_bullets.at(counter);
            //usuwanie go z wektora
            this->enemy_bullets.erase(this->enemy_bullets.begin()+counter);
            --counter;


        }
//        std::cout<< "Liczba pociskow na ekranie: ";
//        std::cout<< this->bullets.size() << std::endl;
        ++counter;
    }
}

void Game::updateBonuses()
{
    int counter = 0;
    for (auto *bon : bonuses)
    {
        bon->update();

        if(bon->getBounds().top + bon->getBounds().height > window_height)
        {
            //usuwanie konkretnego wskaznika
            delete this->bonuses.at(counter);

            //usuwanie go z wektora
            this->bonuses.erase(this->bonuses.begin()+counter);
            --counter;
        }
        if( player->getBounds(player).intersects( bon->getBounds() ) )
        {
            player->increaseHP(player,bon->heal());
            delete this->bonuses.at(counter);

            this->bonuses.erase(this->bonuses.begin()+counter);
            --counter;
        }
    }
}

void Game::updateTimer()
{
    spawnRule++;
}

std::pair<float,float> Game::getRandomPosition(int res_x, int res_y, int dead_zone)
{
    int x = 0;
    int y = 0;

    do {
        x = static_cast<float>(rand() % res_x);
        y = static_cast<float>(rand() % res_y);
    } while ( (abs(x-res_x/2) > dead_zone || abs(y-res_y/2) < dead_zone) );

    return std::pair<float,float>(x,y);
}


void Game::updateEnemies()                                                           // SPAWN WROGOW
{
    if(spawnRule == 20.0f and enemies.empty())                                     // 1 FALA
    {
        updateTimer();
        for (int i = 0; i<10; i++)
        {                                                           //getRandomPosition(500,800,100).first,getRandomPosition(500,800,100).second
            this->enemies.push_back(new Enemy(this->textures["ENEMY1"],
                                    rand()%this->window->getSize().x/2, rand()%this->window->getSize().y/2, //
                                    2.f, 2.f,
                                    2.f, 0.7,
                                    0.7, 5));
        }
    }

    if(spawnRule == 21.f and enemies.empty())                                      // 2 FALA
    {
        updateTimer();
        for (int i = 0; i<7; i++)
        {
            this->enemies.push_back(new Enemy(this->textures["ENEMY2"], rand()%this->window->getSize().x/2,rand()%this->window->getSize().y/2,2.f,2.f,1.2f,1.0,1.0,10));
        }
    }

    if(spawnRule == 22.f and enemies.empty())                                      // 3 FALA
    {
        updateTimer();
        for (int i = 0; i<5; i++)
        {
            this->enemies.push_back(new Enemy(this->textures["ENEMY3"], rand()%this->window->getSize().x/2,rand()%this->window->getSize().y/2,2.f,2.f,0.7f,1.2,1.2,20));
        }
    }
    if(spawnRule == 23.f and enemies.empty())                                      // BOSS tu trzeba stworzc calkiem nowy, osobny obiekt
    {
        updateTimer();
        for (int i = 0; i<1; i++)
        {
            this->enemies.push_back(new Enemy(this->textures["ENEMY3"], rand()%this->window->getSize().x/2,rand()%this->window->getSize().y/2,2.f,2.f,0.5f,2.0,2.0,50));
        }
    }
//    else
//    {

//    }



    for (auto *enemy : enemies)                // RUCH WROGOW
    {
        // movement and bounce
        enemy->update();
    }
}

void Game::updateCombat()                                               // KOLIZJE WALKA
{
    // kolizje naszych pociskow ze statkami wroga
    for (int i = 0; i < static_cast<int>(this->enemies.size()); i++)
    {
        for(int j=0; j< static_cast<int>(this->bullets.size()); j++)
        {
            if(this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds()))
            {
                enemies[i]->decreaseHP();
                //DEBUGER
//                std::cout<< "HP wroga: " << std::endl;
//                std::cout<< this->enemies[i]->getHP() << std::endl;
               this->bullets.erase(this->bullets.begin() +j);           // POCISK MUSI USUWAC SIE PRZY ZDERZENIU Z WROGIEM, ZEBY ODJAC MU TYLKO 1 HP
                if (enemies[i]->getHP() <= 0)
                {
                    //usuwanie obiektu z wektora
                    this->enemies.erase(this->enemies.begin() +i);

                    if (rand()%10 < 3) // szansa na wypadniecie tego konretnego bonusu
                    {
                        this->bonuses.push_back(new Bonus(this->textures["BONUS1"],
                                                enemies[i]->getPos().x,//50
                                                enemies[i]->getPos().y, //100
                                                0.f,
                                                10.f,
                                                1.0f));
                    }
                }
            }
            // debugowanie
//            std::cout<< "Liczba wrogow na ekranie: ";
//            std::cout<< this->enemies.size() << std::endl;
        }


        //kolizje naszego statku ze statkami wroga
        if (player->getBounds(player).intersects(enemies[i]->getBounds()))
        {
            enemies[i]->decreaseHP();
            player->decreaseHP(player,this->enemies[i]->Hit());
                std::cout<<player->getHP(player)<<std::endl;
        }
    }


    // kolizje pociskow wroga z naszym statkiem
    for (auto &e : enemies)
    {
        for(auto &b : enemy_bullets)
        {
            if(b->getBounds().intersects(player->getBounds(player)))
            {
                player->decreaseHP(player, e->Hit());
                //DEBUGER
                std::cout<< this->player->getHP(player) << std::endl;
            }
        }
    }
//    for (int i = 0; i < static_cast<int>(this->enemies.size()); i++)
//    {
//        for(int j=0; j< static_cast<int>(this->enemy_bullets.size()) ; j++)
//        {
//            if(this->enemy_bullets[j]->getBounds().intersects(this->player->getBounds()))
//            {
//                player->decreaseHP(enemies[i]->Hit());
//                //DEBUGER
////                std::cout<< this->enemies[i]->getHP() << std::endl;
//            }
//        }
//    }

}



void Game::updateGUI()
{
    std::stringstream ss;
    std::stringstream ss2;

    ss << player->getHP(player);
    ss << "/";
    ss << HPMax;
    this->myText.setString(ss.str());
}

void Game::update()
{
//    this->updateEvents();
    this->updateInput();
    this->player->update(player);
    this->updateBullets();
    this->updateEnemyBullets();
    this->updateEnemies();
    this->updateBonuses();
    this->updateCombat();
    this->updateGUI();
}




/// rysowanie

void Game::renderGUI()
{
    this->window->draw(this->myText);
}

void Game::renderBackground()
{
    window->draw(background);
}

void Game::render()
{
    this->window->clear();

    // rysowanie wszystkiego
    this->renderBackground();
    this->player->render(player,*this->window);

    for (auto *bull : bullets)
    {
        bull->render(this->window);
    }
    for (auto *bon : bonuses)
    {
        bon->render(this->window);
    }
    for (auto *bull : enemy_bullets)
    {
        bull->render(this->window);
    }
    for (auto *enemy : enemies)
    {
        enemy->render(this->window);
    }
    this->renderGUI();

    //gave over text
    if(player->getHP(player) <=0)
    {
        this->window->draw(this->GameOver_text);
    }

    if(enemies.empty())                 // tu trzeba dac warunek dla istnienia bossa, a nie dla pustego wektora, bo po kazdej fali wektor
    {                                   // jest pusty i to sie zalacza na chwile
        this->window->draw(this->YouWin_text);
    }

    this->window->display();
}














