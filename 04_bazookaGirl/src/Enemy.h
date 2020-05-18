#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void init(std::string textureName, sf::Vector2f position, float mass);
	void jump(float velocity);
	void update(float dt);
	sf::Sprite getSprite();


private:
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	float m_mass;
	float m_speed;
	const float m_gravity = 9.80f;
};

