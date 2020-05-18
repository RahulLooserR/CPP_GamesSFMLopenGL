#include "Entity.h"
#include <iostream>

Entity::Entity()
{
	life = true;
}

Entity::~Entity()
{
}

void Entity::update(float dt)
{
	if (animation->isEnd) {
		life = false;
	}
	animation->update(dt);
	animation->setSpritePos(m_position);
}

void Entity::setAnimation(std::string name, Animation& anim, sf::Vector2f position, float angle, float r)
{
	this->radius = r;
	this->name = name;
	animation = new Animation;
	*animation = anim;
	m_position = position;
	this->angle = angle;
	
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(animation->getSprite());
}
