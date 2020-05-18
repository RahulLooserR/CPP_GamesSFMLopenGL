#pragma once

#include "Entity.h"
#// include "Utils.h"

class Bullet :
	public Entity
{
public:
	Bullet();
	~Bullet();
	void update(float dt);

private:
	const float SPEED = 10.0f;
};

