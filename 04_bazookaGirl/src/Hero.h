#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>

class Hero
{
public:
	Hero();
	~Hero();
	void init(std::string textureName, sf::Vector2f position, float mass, int frameCount, float animDuration);
	void jump(float velocity);
	void update(float dt);
	sf::Sprite getSprite();

private:
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	float m_mass;
	float m_velocity;
	const float m_gravity = 9.80f;
	int jumpCount = 0;
	bool m_grounded;

	// animation properties
	int m_frameCount;
	float m_animDuration;
	float m_elapsedTime;
	sf::Vector2i m_spriteSize;  // store sprite size
};

