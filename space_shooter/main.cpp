#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include<windows.h>


sf::Texture loadTexture(const std::string & filename_with_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;
}


std::pair<int,int> getRandomPosition(int &res_x, int &res_y)
{
    int x = 0;
    int y = 0;

    do
    {
        x = rand() % res_x;
        y = rand() % res_y;
    }
    while ( (y > res_y/2) );

    return std::pair<int,int>(x,y);
}






class Statek : public sf::Sprite                                                    // KLASA ABSTRAKCYJNA
{
public:
    Statek() : Sprite() {  };

    virtual ~Statek()=default; // tu dodac koniec gry, albo animacje wybuchu
    virtual void animate(const sf::Time &elapsed_time,const int &window_width, const int &window_heigh) = 0;

    void skala(float &skala_x, float &skala_y)
    {
        setScale(skala_x,skala_y);
    }

protected:
    sf::Texture texture;
    float vx_ = 200.0;
    float vy_ = 200.0;
    float skala_x_ = 1.0;
    float skala_y_ = 1.0;
    int HP_;
};






class Nasz : public Statek                                                              // NASZ STATEK
{
public:
    Nasz(sf::Texture &texture, const int &res_x, const int &res_y) : Statek() //const sf::Texture &texture,
    {
        setPosition(res_x/2,3*(res_y/4)); //res_x/2 - getGlobalBounds().width/2,res_y/2 - getGlobalBounds().height/2
        HP_ = 3;
        skala(skala_x,skala_y);
        setTexture(texture);
        setOrigin(112.0/2.0,75.0/2.0);
    }


    void animate(const sf::Time &elapsed_time, const int &window_width, const int &window_heigh) //
    {
        sf::FloatRect sprite_guy_bounds = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and getGlobalBounds().top > 0) // dopoki prawda jest ze globalna granica gorna > 0
        {
            move(0,-vy_ * elapsed_time.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sprite_guy_bounds.top+sprite_guy_bounds.height < window_heigh) // dopoki prawda jest ze wysokosc okna < niz ustawiona
        {
            move(0,vy_ * elapsed_time.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and getGlobalBounds().left > 0)
        {
            move(-vx_ * elapsed_time.asSeconds(),0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and sprite_guy_bounds.left+sprite_guy_bounds.width < window_width)
        {
            move(vx_ * elapsed_time.asSeconds(),0);
        }
    }

    void rotacja()
    {
//        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    }

    void reduce_lives()
    {
        HP_--;
    }


    bool is_alive() const
    {
        if(HP_ >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:

    float skala_x = 0.5, skala_y = 0.5;
};


class MalyWrog : public Statek                                                      // MALY STATEK WROGA
{
public:
    MalyWrog(sf:: Texture &texture, int &res_x, int &res_y) : Statek()
    {
        auto[x,y] = getRandomPosition(res_x,res_y);
        setPosition(x,y);
        skala(scale_x,scale_y);
        setTexture(texture);
   }

    void animate(const sf::Time &elapsed, const int &res_x, const int &res_y)
    {
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        move(speed_x_*elapsed.asSeconds(), speed_y_*elapsed.asSeconds());
//      rotate(angular_velocity*elapsed.asSeconds());

        if(rectangle_bounds.top+rectangle_bounds.height > res_y/2)
        {
            speed_y_ = -abs(speed_y_);
        }
        if(rectangle_bounds.top < 0)
        {
            speed_y_ = abs(speed_y_);
        }
        if(rectangle_bounds.left+rectangle_bounds.width > res_x)
        {
            speed_x_ = -abs(speed_x_);
        }
        if(rectangle_bounds.left < 0)
        {
            speed_x_ = abs(speed_x_);
        }
    }

protected:
    int speed_x_ = 100.0;
    int speed_y_ = 100.0;
    float scale_x = 0.5 , scale_y = 0.5;
//    int angular_velocity = 10;
};



class SredniWrog : public Statek                                                      // SREDNI STATEK WROGA
{
public:
    SredniWrog(sf:: Texture &texture, int &res_x, int &res_y)
    {
        auto[x,y] = getRandomPosition(res_x,res_y);
        setPosition(x,y);
        skala(scale_x,scale_y);
        setTexture(texture);
   }

    void animate(const sf::Time &elapsed, const int &res_x, const int &res_y)
    {
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        move(speed_x_*elapsed.asSeconds(), speed_y_*elapsed.asSeconds());
//      rotate(angular_velocity*elapsed.asSeconds());

        if(rectangle_bounds.top+rectangle_bounds.height > res_y/2)
        {
            speed_y_ = -abs(speed_y_);
        }
        if(rectangle_bounds.top < 0)
        {
            speed_y_ = abs(speed_y_);
        }
        if(rectangle_bounds.left+rectangle_bounds.width > res_x)
        {
            speed_x_ = -abs(speed_x_);
        }
        if(rectangle_bounds.left < 0)
        {
            speed_x_ = abs(speed_x_);
        }
    }

protected:
    int speed_x_ = 50.0;
    int speed_y_ = 50.0;
    float scale_x = 0.7 , scale_y = 0.7;
//    int angular_velocity = 10;
};




class DuzyWrog : public Statek                                                      // DUZY STATEK WROGA
{
public:
    DuzyWrog(sf:: Texture &texture, int &res_x, int &res_y)
    {
        auto[x,y] = getRandomPosition(res_x,res_y);
        setPosition(x,y);
        skala(scale_x,scale_y);
        setTexture(texture);
   }

    void animate(const sf::Time &elapsed, const int &res_x, const int &res_y)
    {
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        move(speed_x_*elapsed.asSeconds(), speed_y_*elapsed.asSeconds());
//      rotate(angular_velocity*elapsed.asSeconds());

        if(rectangle_bounds.top+rectangle_bounds.height > res_y/2)
        {
            speed_y_ = -abs(speed_y_);
        }
        if(rectangle_bounds.top < 0)
        {
            speed_y_ = abs(speed_y_);
        }
        if(rectangle_bounds.left+rectangle_bounds.width > res_x)
        {
            speed_x_ = -abs(speed_x_);
        }
        if(rectangle_bounds.left < 0)
        {
            speed_x_ = abs(speed_x_);
        }
    }

protected:
    int speed_x_ = 20.0;
    int speed_y_ = 20.0;
    float scale_x = 1.0 , scale_y = 1.0;
//    int angular_velocity = 10;
};



class Pocisk : public sf::Sprite                                                                    // KLASA POCISK
{
public:
    Pocisk(sf::Texture &texture, const int &res_x, const int &res_y) : Sprite()
    {
        setPosition(res_x/2,3*(res_y/4));
        skala(scale_x,scale_y);
        setTexture(texture);
    }
    void skala(float &skala_x, float &skala_y)
    {
        setScale(skala_x,skala_y);
    }
//    void animate(const sf::Time &elapsed, const int &res_x, const int &res_y)
//    {
//        sf::FloatRect rectangle_bounds = getGlobalBounds();

//        move(50.0*elapsed.asSeconds(),50.0*elapsed.asSeconds());
//    }

protected:
    sf::Texture texture;
    float scale_x = 0.5 , scale_y = 0.5;
};




class Bonus
{
public:
    Bonus() {};
};










void projekt()
{
    srand(time(NULL));
    int window_width = 500;
    int window_heigh = 800;


    /// wektor unique pointerow na obiekty

    std::vector<std::unique_ptr<Statek>> obiekty;
    std::vector<std::unique_ptr<sf::Sprite>> tla;
    std::vector<std::unique_ptr<Pocisk>> pociski;


    sf::Texture texture_nasz = loadTexture("./../space_shooter/nasz.png");
    sf::Texture texture_enemy1 = loadTexture("./../space_shooter/enemy1.png");
    sf::Texture texture_enemy2 = loadTexture("./../space_shooter/enemy2.png");
    sf::Texture texture_enemy3 = loadTexture("./../space_shooter/enemy3.png");
    sf::Texture texture_background = loadTexture("./../space_shooter/black.png");
    sf::Texture texture_pocisk1 = loadTexture("./../space_shooter/pocisk1.png");

    auto sprite_background = std::make_unique<sf::Sprite>();                                        // SET TŁA
    sprite_background->setTexture(texture_background);
    sprite_background->setPosition(0,0);
    sprite_background->setTextureRect(sf::IntRect(0,0,window_width,window_heigh));
    texture_background.setRepeated(true);    // textura nie moze byc const, zeby mozna bylo to zrobic
    tla.emplace_back(std::move(sprite_background));
                                                                                                    // POWOŁANIE KOLEJNYCH OBIEKTOW
    std::unique_ptr nasz = std::make_unique<Nasz>(texture_nasz, window_width, window_heigh);        // MY
    obiekty.emplace_back(std::move(nasz));

    for(int i=0; i<5; i++)                                                                          //MALY WROG
    {
        obiekty.emplace_back(std::make_unique<MalyWrog>(texture_enemy1, window_width, window_heigh));
    }
    for(int i=0; i<3; i++)                                                                          // SREDNI WROG
    {
        obiekty.emplace_back(std::make_unique<SredniWrog>(texture_enemy2, window_width, window_heigh));
    }
    for(int i=0; i<2; i++)                                                                          // DUZY WROG
    {
        obiekty.emplace_back(std::make_unique<DuzyWrog>(texture_enemy3, window_width, window_heigh));
    }










    /// PROGRAM
    sf::RenderWindow window(sf::VideoMode(window_width, window_heigh), "GalaxyShooter");
    window.setFramerateLimit(60);

    sf::Clock clock;


    /// GLOWNA PETLA PROGRAMU
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        ///zegar
        sf::Time elapsed = clock.restart();
        ///czyszczenie okna
        window.clear(sf::Color::Black);


        if (1)                                                                                      //FACE TO MOUSE
        {
            Nasz *nasz_ptr = dynamic_cast<Nasz *>(obiekty[0].get());
            sf::Vector2f curPos;                                                                    // POZYCJA OBIEKTU
            curPos.x = nasz_ptr->getPosition().x;
            curPos.y = nasz_ptr->getPosition().y;

            sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));  // POZYCJA MYSZY
            float dx = curPos.x - mouse_position.x;
            float dy = curPos.y - mouse_position.y;
            const float PI = 3.14159265;
            float rotation = std::atan2(dy,dx)*180.0/PI;

            nasz_ptr->setRotation(rotation-90);
        }

//        if (1)                                                                                      // POCISKI
//        {
//            pociski.emplace_back(std::make_unique<Pocisk>(texture_pocisk1, window_width, window_heigh));
//            Sleep(1000);
//        }                                                                                     //TU SKONCZYLEM
                                                                                                // DODAC TO ZEBY POCISKI LECIALY Z NASZEGO STATKU
                                                                                                // I ZEBY LECIALY W DOBRA STORNE (METODA KLASY)
                                                                                                // POTEM DODAC KOLIZJE Z WROGAMI





                                                                //ANIMACJE I RYSOWANIE
        for(const auto &o : tla) {                              //TLO
            window.draw(*o);
        }


        for(const auto &o : obiekty) {                          // ZLE STATKI
            o->animate(elapsed,window_width,window_heigh);
            window.draw(*o);
        }



//        for(int i=0; i<static_cast<int>(obiekty.size()); i++)                                                   // KOLIZJE
//        {
//            KamienNieskonczonosci * kamienNieskonczonosci = dynamic_cast<KamienNieskonczonosci *>(obiekty[i].get());
//            StworOutsider * stworOutsider = dynamic_cast<StworOutsider *>(obiekty[i].get());

//            if (!thor.getGlobalBounds().intersects(kamienNieskonczonosci->getGlobalBounds()) and !kamienNieskonczonosci->getGlobalBounds().intersects(thor.getGlobalBounds()))
//            {
//                thor.add_points(100);
//                delete kamienNieskonczonosci;
//            }
//            if (!thor.getGlobalBounds().intersects(stworOutsider->getGlobalBounds()) and !stworOutsider->getGlobalBounds().intersects(thor.getGlobalBounds()))
//            {
//                thor.reduce_lives();
//            }
//        }


//        if(!thor.is_alive())
//        {
//            window.close();
//            std::cout<< "Przegrana"<<std::endl;
//        }
//        if(thor.get_number_of_points()>500)
//        {
//            window.close();
//            std::cout<<"Wygrana" <<std::endl;
//        }

        window.display();
    }
}




















int main()
{
    projekt();
    return 0;
}

