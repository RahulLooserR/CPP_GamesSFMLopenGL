#pragma once
#include "Hero.h"
#include "Rocket.h"
#include "Enemy.h"
#include "Platform/Platform.hpp"

extern sf::RenderWindow window;
extern sf::Event event;

extern Hero hero;


extern sf::Texture skyTexture;
extern sf::Sprite skySprite;

extern sf::Texture backgroundTexture;
extern sf::Sprite backgroundSprite;
extern std::vector<Rocket*> rockets;
extern std::vector<Enemy*> enemies;
extern float currentTime, prevTime;

void init();
void init_window();
void updatePollEvents();
void updatePosition(float);
void draw();
void shoot();
void spawnEnemy();
bool isCollided(sf::Sprite, sf::Sprite);