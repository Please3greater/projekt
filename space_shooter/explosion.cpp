//#include "explosion.h"

//Explosion::Explosion()
//{

//}

//Explosion::Explosion(std::vector<sf::Texture> &textures, float posX, float posY, float switchTime)
//{
//    counter = switchTime*60;
//    maxCounter = counter;

////    this->textures["EXPL1"] = new sf::Texture();                                       // wybuch 1
////    this->textures["EXPL1"]->loadFromFile("./../space_shooter/Tekstury/expl1.png");
////    this->textures["EXPL2"] = new sf::Texture();                                       // wybuch 2
////    this->textures["EXPL2"]->loadFromFile("./../space_shooter/Tekstury/expl2.png");
////    this->textures["EXPL3"] = new sf::Texture();                                       // wybuch 3
////    this->textures["EXPL3"]->loadFromFile("./../space_shooter/Tekstury/expl3.png");
////    this->textures["EXPL4"] = new sf::Texture();                                       // wybuch 4
////    this->textures["EXPL4"]->loadFromFile("./../space_shooter/Tekstury/expl4.png");
////    this->textures["EXPL5"] = new sf::Texture();                                       // wybuch 5
////    this->textures["EXPL5"]->loadFromFile("./../space_shooter/Tekstury/expl5.png");
////    this->textures["EXPL6"] = new sf::Texture();                                       // wybuch 6
////    this->textures["EXPL6"]->loadFromFile("./../space_shooter/Tekstury/expl6.png");
////    this->textures["EXPL7"] = new sf::Texture();                                       // wybuch 7
////    this->textures["EXPL7"]->loadFromFile("./../space_shooter/Tekstury/expl7.png");
////    this->textures["EXPL8"] = new sf::Texture();                                       // wybuch 8
////    this->textures["EXPL8"]->loadFromFile("./../space_shooter/Tekstury/expl8.png");


//    for (auto & texture: textures)
//    {
//        sprite.setTexture(texture);
//        sprite.setPosition(posX,posY);
//        sprite.setScale(1,1);
//        sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
//        animacje.emplace_back(sprite);
//    }

//}

//Explosion::~Explosion()
//{

//}

//void Explosion::render(sf::RenderTarget *target)
//{
//    target->draw(animacje[static_cast<int>(animacje.size() - 0.99f * counter/maxCounter * animacje.size())]); //this->sprite
//}

//void Explosion::update()
//{
//    counter--;
//}

//int Explosion::getCounter()
//{
//    return counter;
//}
