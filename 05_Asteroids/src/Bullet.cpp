#include "Utils.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{

	dx = cos(angle * DEGTORAD) * SPEED;
	dy = sin(angle * DEGTORAD) * SPEED;

	m_position.x += dx;
	m_position.y += dy;

	animation->setSpritePos(m_position, angle);
	animation->update(dt);

	if (m_position.x < 0 || m_position.x > W || m_position.y < 0 || m_position.y > H)
		life = false;
}
