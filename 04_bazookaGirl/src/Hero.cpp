#include "Hero.h"

// hero constructor
Hero::Hero()
{

}

// hero destructor
Hero::~Hero()
{

}

void Hero::init(std::string textureName, sf::Vector2f position, float mass, int frameCount, float animDuration)
{
	m_mass = mass;
	m_position = position;
	m_grounded = false;
	m_frameCount = frameCount;
	m_animDuration = animDuration;
	m_spriteSize = sf::Vector2i(92, 126);   // size of hero sprite, 92x126 pixels
	m_elapsedTime = 0;

	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_spriteSize.x, m_spriteSize.y));
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y / 2);
}

void Hero::jump(float velocity)
{
	if (jumpCount < 2 && m_grounded) {
		jumpCount++;
		m_velocity = velocity;
		m_grounded = false;
	}

}

void Hero::update(float dt)
{
	// animating sprite
	m_elapsedTime += dt;
	int animFrame = static_cast<int> ((m_elapsedTime / m_animDuration) * m_frameCount) % m_frameCount;
	m_sprite.setTextureRect(sf::IntRect(animFrame * m_spriteSize.x, 0, m_spriteSize.x, m_spriteSize.y));

	m_velocity -= m_mass * m_gravity * dt;
	m_position.y -= m_velocity * dt;
	m_sprite.setPosition(m_position);

	if (m_position.y > 768 * 0.75f) {
		m_position.y = 768 * 0.75f;
		m_velocity = 0;
		m_grounded = true;
		jumpCount = 0;
	}
}

sf::Sprite Hero::getSprite()
{
	return m_sprite;
}