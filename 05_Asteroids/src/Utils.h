#pragma once

#include <vector>
#include<list>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ShipAnimation.h"
#include "Entity.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"


extern float DEGTORAD;
extern int W, H;   // width and height of window


extern sf::Texture spaceTexture, shipTexture, bulletTexture, asteroidTexture, explosionTexture;
extern sf::Sprite spaceSprite;

extern Animation explosionAnim;
extern Animation bulletAnimation;
extern Animation asteroidsAnimation;
extern ShipAnimation shipAnim;

extern std::vector<Entity*> entities;
extern Ship* ship;
extern bool gameOver;

void fire(float dt);
void setup();
void update(float dt);
void draw(sf::RenderWindow& window);
bool isCollided(Entity* entity1, Entity* entity2);