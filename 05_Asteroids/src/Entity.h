#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Entity
{
public:
	float angle;
	sf::Vector2f m_position;
	float dx = 0, dy = 0, radius = 1;
	Animation* animation;
	std::string name;
	bool life;

	Entity();
	~Entity();
	virtual void update(float dt);
	virtual void setAnimation(std::string name, Animation& animation, sf::Vector2f position,
		float angle = -90.0f, float R = 1);
	virtual void draw(sf::RenderWindow& window);
	
};

