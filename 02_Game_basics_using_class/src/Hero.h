#pragma once
#include "Platform/Platform.hpp"

class Hero
{
public:
	Hero();
	~Hero();
	void init(std::string textureName, sf::Vector2f position, float mass);
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
};
