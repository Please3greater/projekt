#ifndef GAME_H
#define GAME_H

#pragma once
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <map>
#include <string>
#include <sstream>
#include <math.h>



class Game
{
private:
    sf::RenderWindow* window;
    int window_width = 500;
    int window_height = 800;

    sf::Vector2f mouse_position;

    // zycie w rogu ekranu
    sf::Font font;
    sf::Text myText;
    sf::Text GameOver_text;
    sf::Text YouWin_text;

    //licznik do spawnu wrogow
    float spawnRule;

    //Textures
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;            // nasze pociski
    std::vector<Bullet*> enemy_bullets;      // pociski wroga
    std::vector<Enemy *> enemies;

    //tlo
    sf::Texture texture_background;
    sf::Sprite background;

    // set postaci w grze
    Player* player;
    unsigned HP;
    unsigned HPMax;

    //inicjowanie wszystkiego
    void initializeBackground();
    void initializeWindow();
    void initializeTextures();
    void initializeGUI();
    void initializePlayer();
    void initializeEnemies();

public:
    Game();
    virtual ~Game();

   //funkcje publiczne
//   std::pair<int,int> getRandomPosition(int res_x, int res_y, int dead_zone);
   void run();
   void updateEvents();
   void updateInput();
   void updateGUI();
   void updateBullets();
   void updateEnemyBullets();
   void updateTimer();
   bool canAttack();
   void updateEnemies();
   void updateCombat();
   void update();
   void renderGUI();
   void renderBackground();
   void render();
};

#endif // GAME_H
