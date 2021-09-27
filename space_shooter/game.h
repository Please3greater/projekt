#ifndef GAME_H
#define GAME_H

#pragma once
#include "player.h"
#include "bullet.h"
#include "BossBullet.h"
#include "enemy.h"
#include "bonus.h"
#include "bonus2.h"
#include "bonus3.h"
#include "explosion.h"
#include "boss.h"
#include <map>
#include <string>
#include <sstream>
#include <math.h>
#include <time.h>
#include <SFML/Audio.hpp>


class Game
{
private:
    // wymiary okienka gry
    sf::RenderWindow* window;
    int window_width = 500;
    int window_height = 800;

    // licznik czasu do 2 bonusu
    sf::Clock clock;

    //muzyka
    sf::Music music;
    sf::Music music2;

    // strzelanie i obrot w kierunku myszy
    sf::Vector2f mouse_position;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    // zycie w rogu ekranu
    sf::Font font;
    sf::Text myText;
    sf::Text GameOver_text;
    sf::Text YouWin_text;

    //licznik do spawnu wrogow
    float spawnRule;

    // warunek konca gry
    int end = 0;

    //Textury
    std::map<std::string, sf::Texture*> textures;   //tekstury
//    std::vector<std::pair<std::string,sf::Texture*>> expl_textures; // tekstury wybuchow

    //wektory obiektow
    std::vector<Bullet*> bullets;            // nasze pociski
    std::vector<Bullet*> enemy_bullets;     // pociski wroga
    std::vector<BossBullet*> boss_bullets; // pociski bossa
    std::vector<Enemy*> enemies;          // wrogowie
    std::vector<Bonus*> bonuses;         // bonusy
    std::vector<bonus2*> bonuses2;      // bonusy2
    std::vector<bonus3*> bonuses3;     // bonusy3
    std::vector<Boss*> bossess;       // boss
//    std::vector<Explosion*> wybuchy; // wybuchy

    //tlo
    sf::Texture texture_background;
    sf::Sprite background;

    // set naszej postaci w grze
    Player* player;
    unsigned HP;
    unsigned HPMax;

    //inicjowanie wszystkiego
    void initializeBackground();
    void initializeMusic();
    void initializeWindow();
    void initializeTextures();
    void initializeGUI();
    void initializePlayer();
    void initializeEnemies();

public:
    Game();
    virtual ~Game();

    //funkcje publiczne
    bool canAttack();
    int Hit(int howMany);
    std::pair<int,int> getRandomPosition(int res_x, int res_y, int deadzone);
    void run();

    void updateEvents();
    void updateInput();
    void updateGUI();
    void updateEnemyBullets();
    void updateBossBullets();
    void updateBonuses();
    void updateBonuses2();
    void updateBonuses3();
    void updateTimer();
    void updateEnemies();
    void updateCombat();
    void update();

    void renderGUI();
    void renderBackground();
    void render();
};

#endif // GAME_H
