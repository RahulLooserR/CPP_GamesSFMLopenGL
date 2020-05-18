#pragma once
#include "Animation.h"

class ShipAnimation : public Animation
{
public:
	ShipAnimation();
	ShipAnimation(sf::Texture& texture, sf::IntRect rect);
	~ShipAnimation();
	void update(float dt);
};

