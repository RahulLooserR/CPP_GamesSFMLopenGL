#pragma once
#include "Hero.h"
#include "Rocket.h"
#include "Enemy.h"
#include "Platform/Platform.hpp"


extern sf::Music bgMusic;
extern sf::Sound fireSound;
extern sf::Sound hitSound;

extern sf::RenderWindow window;
extern sf::Event event;

// fonts
extern sf::Font headingFont;
extern sf::Font scoreFont;
extern sf::Font msgFont;
extern sf::Font rocketFont;

// hero class and sprites
extern Hero hero;
extern sf::Texture skyTexture;
extern sf::Sprite skySprite;

// background texture and sprte
extern sf::Texture backgroundTexture;
extern sf::Sprite backgroundSprite;

// list of enemies and rockets
extern std::vector<Rocket*> rockets;
extern std::vector<Enemy*> enemies;

extern float currentTime, prevTime;

extern bool gameOver;
extern int score;
extern int rocketLeft;

void reset();
void init();
void init_window();
void updatePollEvents();
void updatePosition(float);
void draw();
void shoot();
void spawnEnemy();
bool isCollided(sf::Sprite, sf::Sprite);