#ifndef UTILS_HPP
#define UTILS_HPP
#include "Platform/Platform.hpp"

extern sf::RenderWindow window;
extern bool moveLeft, moveRight;
extern sf::Event event;

extern sf::Texture heroTexture;
extern sf::Sprite heroSprite;
//sf::Sprite heroSprite(heroTexture, sf::IntRect(0, 0, 90, 170));

extern sf::Texture backgroundTexture;
extern sf::Sprite backgroundSprite;

void init();
void init_window();
void updatePollEvents();
void updatePosition(float);
void draw();

#endif