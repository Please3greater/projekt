#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <map>


class Game
{
private:
    sf::RenderWindow* window;
    int window_width = 500;
    int window_height = 800;

    float spawnTimer;
    float spawnTimerMax;

    //Textures
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    std::vector<Enemy *> enemies;

    // set postaci w grze
    Player* player;

    //inicjowanie wszystkiego
    void initializeWindow();
    void initializeTextures();
    void initializePlayer();
    void initializeEnemies();

public:
    Game();
    virtual ~Game();

   //funkcje
   void run();
   void updatePollEvents();
   void updateInput();
   void updateBullets();
   void updateEnemies();
   void update();
   void render();
};

#endif // GAME_H
