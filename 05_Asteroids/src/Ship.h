#pragma once
#include "Entity.h"
#include "ShipAnimation.h"

class Ship
	: public Entity
{
public:
	bool thrust = false;
	ShipAnimation* shipAnim;
	const float MAXSPEED = 5.0f;

	Ship();
	~Ship();
	void update(float dt);
	void setAnimation(std::string name, ShipAnimation& animation, sf::Vector2f position,
		float angle = -90.0f, float R = 1);
	void draw(sf::RenderWindow& window);
};

