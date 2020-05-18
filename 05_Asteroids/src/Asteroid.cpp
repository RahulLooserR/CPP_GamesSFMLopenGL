#include "Utils.h"

Asteroid::Asteroid()
{
	dx = rand() % 4;
	dy = rand() % 4 + 1;
}

Asteroid::~Asteroid()
{
}

void Asteroid::update(float dt)
{
	m_position.x += dx * cos(angle * DEGTORAD);
	m_position.y += dy * sin(angle * DEGTORAD);

	if (m_position.x > W) m_position.x = 0; if (m_position.x < 0) m_position.x = W;
	if (m_position.y > H) m_position.y = 0; if (m_position.y < 0) m_position.y = H;

	animation->setSpritePos(m_position, angle);
	animation->update(dt);
}
