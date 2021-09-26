#include "game.h"

//funkcje prywatne
void Game::initializeWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(window_width,window_height), "Galaxy shooter");
    this->window->setFramerateLimit(60);
}

void Game::initializeTextures()
{
    this->textures["BULLET"] = new sf::Texture();                                       // nasz pocisk
    this->textures["BULLET"]->loadFromFile("./../space_shooter/Tekstury/pocisk1.png");
    this->textures["BULLET2"] = new sf::Texture();                                      // pocisk wroga
    this->textures["BULLET2"]->loadFromFile("./../space_shooter/Tekstury/pocisk2.png");
    this->textures["ENEMY1"] = new sf::Texture();                                       // wrog 1
    this->textures["ENEMY1"]->loadFromFile("./../space_shooter/Tekstury/enemy1.png");
    this->textures["ENEMY2"] = new sf::Texture();                                       // wrog 2
    this->textures["ENEMY2"]->loadFromFile("./../space_shooter/Tekstury/enemy2.png");
    this->textures["ENEMY3"] = new sf::Texture();                                       // wrog 3
    this->textures["ENEMY3"]->loadFromFile("./../space_shooter/Tekstury/enemy3.png");
    this->textures["BONUS1"] = new sf::Texture();                                       // apteczka
    this->textures["BONUS1"]->loadFromFile("./../space_shooter/Tekstury/bonus1.png");
    this->textures["BONUS2"] = new sf::Texture();                                       // tarcza
    this->textures["BONUS2"]->loadFromFile("./../space_shooter/Tekstury/bonus2.png");
    this->textures["BONUS3"] = new sf::Texture();                                       // szybsze pociski
    this->textures["BONUS3"]->loadFromFile("./../space_shooter/Tekstury/bonus3.png");
}

void Game::initializeBackground()
{
    if(!this->texture_background.loadFromFile("./../space_shooter/Tekstury/tlo.png"))
    {
        std::cout<<"Blad wczytywanie tekstury tla"<<std::endl;
    }
    texture_background.setRepeated(true);
    background.setTextureRect(sf::IntRect(0, 0, window_width, window_height));
    background.setTexture(texture_background);
    background.setPosition(0,0);
    background.setOrigin(0,0);
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

    this->player->setPosition2(window_width/2, 0.8*window_height); // na sztywno
    this->player->initializeTexture();
    this->player->initializeSprite();
    this->HPMax = this->player->getHPMax();
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
    for (auto &bon2 : bonuses2)
    {
        delete bon2;
    }
    for (auto &bon3 : bonuses3)
    {
        delete bon3;
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
        if(player->getHP() >0)
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
    curPos.x = player->getPos().x;
    curPos.y = player->getPos().y;

    //sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    sf::Vector2f mouse_position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));    // POZYCJA MYSZY
    float dx = curPos.x - mouse_position.x;
    float dy = curPos.y - mouse_position.y;
    const float PI = 3.14159265;
    float rotation = std::atan2(dy,dx)*180.0/PI;

    //debuger
//    std::cout<<mouse_position.x<<"\t"<<mouse_position.y<<std::endl;

    player->setRotation(rotation-90);

//    for(auto& bull : bullets)
//    {
//        bull->setRotation(rotation-90);
//    }


//    for(auto *bull : bullets)
//    {
//        sf::Vector2f curPos;                                                                        // POZYCJA OBIEKTU
//        curPos.x = bull->getPos().x;
//        curPos.y = bull->getPos().y;

//        bull->setRotation(roration-90);    // pociski tez trzeba dziedziczyc po sf::Sprite, tak samo jak playera, zeby mozna bylo uzyc setRotation
//    }



    // Ruszanie sie naszego statku                                                      // OBSLUGA KLAWISZY   ( RUCH )
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player->animate(0.f,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player->animate(0.f,1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->animate(-1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->animate(1.f,0.f);
    }


    if( player->canAttack())                                                        // NASZE POCISKI
    {
        aimDir = mouse_position - player->getPos();                                 // kierunek w ktorym maja leciec nasze pociski ( do kursora )
        aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

//        std::cout<<mouse_position.x<<"\t"<<mouse_position.y<<std::endl;
//        for(auto *bull : bullets)
//        {
            this->bullets.push_back(new Bullet(textures["BULLET"],
                                               player->getPos().x,
                                               player->getPos().y,
                                               aimDirNorm.x,
                                               aimDirNorm.y,
                                               10.f,
                                               rotation-90));
//        }
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
            //usuwanie pociskow                                                                             ( na sztywno )
            if(bull->getBounds().top + bull->getBounds().height < window_height - window_height     or
               bull->getBounds().top + bull->getBounds().height > window_height                     or
               bull->getBounds().width + bull->getBounds().left > window_width                      or
               bull->getBounds().width + bull->getBounds().left < window_width-window_width         )
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

void Game::updateEnemyBullets() // ( and enemies )
{                                                                                       //OBRACANIE SIE WROGOW DO NAS
    sf::Vector2f ourCurPos;                                         // nasza pozycja
    ourCurPos.x = player->getPos().x;
    ourCurPos.y = player->getPos().y;



    for (auto& e : enemies)                                                             // POCISKI WROGA
    {
        sf::Vector2f enemyCurPos;                                   // pozycja wroga
        enemyCurPos.x = e->getPos().x;
        enemyCurPos.y = e->getPos().y;

        float dx = ourCurPos.x - enemyCurPos.x;
        float dy = ourCurPos.y - enemyCurPos.y;
        const float PI = 3.14159265;
        float rotation = std::atan2(dy,dx)*180.0/PI;

        e->setRotation(rotation-90);

        aimDir = e->getPos() - player->getPos();                                 // kierunek w ktorym maja leciec pociski wroga ( do nas )
        aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

        if( e->canAttack())                                                         // teraz strzelaja wszystkie naraz w tym samym czasie
        {
            e->updateAttack();                                                      // dodanie do wektora

            this->enemy_bullets.push_back(new Bullet(textures["BULLET2"],
                                                     e->getPos().x,
                                                     e->getPos().y,
                                                     aimDirNorm.x, //0.f
                                                     aimDirNorm.y,//-10.f
                                                     -10.f,//-0.5f
                                                     rotation-270)); //static_cast<float>(setRotation(rotation-90))  bulletRotation()
//            std::cout<< "Liczba pociskow wroga na ekranie: ";
//            std::cout<< this->enemy_bullets.size() << std::endl;
        }
    }

    for (auto *bull : enemy_bullets)                                                // ruch
    {
        bull->update();
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
        if( player->getBounds().intersects( bon->getBounds() ) )
        {
            player->increaseHP(bon->heal(bon->setHeal(player->getHPMax()/10)));
            delete this->bonuses.at(counter);

            this->bonuses.erase(this->bonuses.begin()+counter);
            --counter;
        }
    }
}

void Game::updateBonuses2()//clock_t initTime
{
    int counter = 0;
    for (auto *bon2 : bonuses2)
    {
        bon2->update();

        if(bon2->getBounds().top + bon2->getBounds().height > window_height)    // kolizja z krawedzia ekranu
        {
            //usuwanie konkretnego wskaznika
            delete this->bonuses2.at(counter);

            //usuwanie go z wektora
            this->bonuses2.erase(this->bonuses2.begin()+counter);
            --counter;
        }

        if( player->getBounds().intersects( bon2->getBounds() ) )               // kolizja bonusu 2 z nami ( ma dzialac na 5 sekund )
        {
            if(!player->czyMaTarcze)
            {
                player->czyMaTarcze = true;
                clock.restart();
            }
            else
            {
                bon2->setPosition(player->getPosition().x-55, player->getPosition().y-50);

                for(auto *ebull : enemy_bullets)                                // kolizja pociskow wroga z nasza tarcza
                {
                    if(bon2->getBounds().intersects(ebull->getBounds()))
                    {
//                        delete ebull->at(counter);
                        this->enemy_bullets.erase(enemy_bullets.begin()+counter);
                        --counter;
                    }
                }

                if( clock.getElapsedTime().asSeconds() > 5.0f )
                {
//                    delete bonuses2.at(counter);
                    this->bonuses2.erase(bonuses2.begin()+counter);
                    player->czyMaTarcze = false;
                    --counter;
                }
            }
        }

    }
}

void Game::updateBonuses3()
{
    int counter = 0;
    for (auto *bon3 : bonuses3)
    {
        bon3->update();

        if(bon3->getBounds().top + bon3->getBounds().height > window_height)            // zderzenie bonusu z krawedzia
        {
            //usuwanie konkretnego wskaznika
            delete this->bonuses3.at(counter);

            //usuwanie go z wektora
            this->bonuses3.erase(this->bonuses3.begin()+counter);
            --counter;
        }
        if( player->getBounds().intersects( bon3->getBounds() ) )                       // zderzenie bonusu z nami
        {
            player->speedUpAttack();

            delete this->bonuses3.at(counter);
            this->bonuses3.erase(this->bonuses3.begin()+counter);
            --counter;
        }
    }
}

void Game::updateTimer()
{
    spawnRule++;
}

std::pair<int,int> Game::getRandomPosition(int res_x, int res_y, int deadzone)         // spawn w prostokacie ( antybug na blokowanie sie
{                                                                                       // przeciwnikow na krawedzi okienka aplikacji )
    int x = 0;
    int y = 0;
    do
    {
        x = rand() % res_x;
        y = rand() % res_y;

    }
//    Ustawianie przedzialu w jakim moga respic sie wrogowie. Granica:
//                       prawa                         lewa                                dol                             gora
    while(abs(x - res_x ) < deadzone or abs(x - res_x ) > deadzone+400 or (abs( y - res_y ) < deadzone ) or abs( y - res_y ) > deadzone+200);
    return std::pair<int,int>(x,y);
}


void Game::updateEnemies()                                                           // SPAWN WROGOW
{
    if(spawnRule == 20.0f and enemies.empty())                                     // 1 FALA
    {
        updateTimer();
        for (int i = 0; i<10; i++)
        {                   //rand()%this->window->getSize().x, rand()%this->window->getSize().y/2
            this->enemies.push_back(new Enemy(this->textures["ENEMY1"],
                                    // w 3 zmiennej przesuwamy przedzial ( obie granice prawo-lewo lub gora-dol )
                                    getRandomPosition(window_width,window_height,50).first,getRandomPosition(window_width,window_height,420).second,
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
            this->enemies.push_back(new Enemy(this->textures["ENEMY2"],
                                    getRandomPosition(window_width,window_height,100).first,getRandomPosition(window_width,window_height,450).second,//rand()%this->window->getSize().x, rand()%this->window->getSize().y/2
                                    2.f,2.f,
                                    1.2f,1.0,
                                    1.0,10));
        }
    }

    if(spawnRule == 22.f and enemies.empty())                                      // 3 FALA
    {
        updateTimer();
        for (int i = 0; i<5; i++)
        {
            this->enemies.push_back(new Enemy(this->textures["ENEMY3"],
                                    getRandomPosition(window_width,window_height,100).first,getRandomPosition(window_width,window_height,450).second,//rand()%this->window->getSize().x, rand()%this->window->getSize().y/2
                                    2.f,2.f,
                                    0.7f,1.2,
                                    1.2,20));
        }
    }
    if(spawnRule == 23.f and enemies.empty())                                      // BOSS tu trzeba stworzc calkiem nowy, osobny obiekt
    {
        updateTimer();
        for (int i = 0; i<1; i++)
        {
            this->enemies.push_back(new Enemy(this->textures["ENEMY3"],
                                    getRandomPosition(window_width,window_height,100).first,getRandomPosition(window_width,window_height,500).second,//rand()%this->window->getSize().x, rand()%this->window->getSize().y/2
                                    2.f,2.f,
                                    0.5f,2.0,
                                    2.0,50));
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

int Game::Hit(int howMany)
{
    return howMany;
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

                if (enemies[i]->getHP() <= 0)                           // likwidacja wroga ( tu dodac animacje )
                {
                    int x = 0;
                    x = rand()%10;
                    //usuwanie obiektu z wektora
                    this->enemies.erase(this->enemies.begin() +i);
                    ///
                    /// miejsce na wybuchy

                    ///

                    if (x < 2) // szansa na wypadniecie tego konretnego bonusu
                    {
                        this->bonuses.push_back(new Bonus(this->textures["BONUS1"],
                                                enemies[i]->getPos().x,//50
                                                enemies[i]->getPos().y, //100
                                                0.f,
                                                10.f,
                                                1.0f));
                    }
                    else if (x >= 4 and x < 7)
                    {
                        this->bonuses2.push_back(new bonus2(this->textures["BONUS2"],
                                                enemies[i]->getPos().x,
                                                enemies[i]->getPos().y,
                                                0.f,
                                                10.f,
                                                1.0f));
                    }
                    else if(x >= 5 and x < 8)
                    {
                        this->bonuses3.push_back(new bonus3(this->textures["BONUS3"],
                                                enemies[i]->getPos().x,
                                                enemies[i]->getPos().y,
                                                0.f,
                                                8.f,
                                                1.0f));
                    }
                }
            }
            // debugowanie
//            std::cout<< "Liczba wrogow na ekranie: ";
//            std::cout<< this->enemies.size() << std::endl;
        }


        //kolizje naszego statku ze statkami wroga
        if (player->getBounds().intersects(enemies[i]->getBounds()))
        {
            enemies[i]->decreaseHP();
            player->decreaseHP(this->enemies[i]->Hit());
//            std::cout<<player->getHP(player)<<std::endl;    //debugger ilosci hp
        }
    }


    // kolizje pociskow wroga z naszym statkiem // usuwanie pociskow wroga
    int counter = 0;
    for (auto *bull : enemy_bullets)
    {
        if(bull->getBounds().top > window_height)                       // pocisk poza ekranem aplikacji
        {
            //usuwanie konkretnego wskaznika
            delete this->enemy_bullets.at(counter);
            //usuwanie go z wektora
            this->enemy_bullets.erase(this->enemy_bullets.begin()+counter);
            --counter;
        }
        if(bull->getBounds().intersects(player->getBounds()))     // pocisk przy zderzeniu z naszym statkiem
        {
//            for(auto& enemy:enemies)
//            {                                                 // napisanie for enemy : enemies nie dziala, bo cos wykracza poza skale
                player->decreaseHP(Hit(1));//enemy->Hit()       // tu by sie przydalo zlinkowac jakos hit() obiektu enemy
                delete this->enemy_bullets.at(counter);
                //usuwanie go z wektora
                this->enemy_bullets.erase(this->enemy_bullets.begin()+counter);
                --counter;
//            }
        }

//        std::cout<< "Liczba pociskow na ekranie: ";
//        std::cout<< this->bullets.size() << std::endl;
//        std::cout<< "Liczba pociskow wroga na ekranie: ";
//        std::cout<< this->enemy_bullets.size() << std::endl;
        ++counter;
    }


}



void Game::updateGUI()
{
    std::stringstream ss;
    ss << player->getHP() << "/" << HPMax;
    this->myText.setString(ss.str());
}

void Game::update()
{
//    this->updateEvents();
    this->updateInput();
    this->player->update();
    this->updateBullets();
    this->updateEnemyBullets();
    this->updateEnemies();
    this->updateBonuses();
    this->updateBonuses3();
    this->updateBonuses2();
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
        bull->render(bull,window);
    }
    for (auto *bon : bonuses)
    {
        bon->render(this->window);
    }
    for (auto *bon2 : bonuses2)
    {
        bon2->render(bon2,window);
    }
    for (auto *bon3 : bonuses3)
    {
        bon3->render(this->window);
    }
    for (auto *bull : enemy_bullets)
    {
        bull->render(bull,window);
    }
    for (auto *enemy : enemies)
    {
        enemy->render(enemy,window);
    }
    this->renderGUI();

    //game over text
    if(player->getHP() <=0)
    {
        this->window->draw(this->GameOver_text);
    }

    if(enemies.empty())                 // tu trzeba dac warunek dla istnienia bossa, a nie dla pustego wektora, bo po kazdej fali wektor
    {                                   // jest pusty i to sie zalacza na chwile
        this->window->draw(this->YouWin_text);
    }

    this->window->display();
}














