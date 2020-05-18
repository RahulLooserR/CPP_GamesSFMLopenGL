#include "ShipAnimation.h"

ShipAnimation::ShipAnimation()
{
}

ShipAnimation::ShipAnimation(sf::Texture& texture, sf::IntRect rect)
{
	m_sprite.setTexture(texture);
	m_rect = rect;
	m_sprite.setTextureRect(m_rect);
	m_sprite.setOrigin(m_rect.width / 2, m_rect.height / 2);
}

ShipAnimation::~ShipAnimation()
{
}

void ShipAnimation::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_sprite.setTextureRect(sf::IntRect(0, 38, 39, 42));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_sprite.setTextureRect(sf::IntRect(77, 38, 39, 42));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_sprite.setTextureRect(sf::IntRect(38, 38, 39, 42));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_sprite.setTextureRect(sf::IntRect(0, 0, 39, 42));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_sprite.setTextureRect(sf::IntRect(77, 0, 39, 42));
	}
	else {
		m_sprite.setTextureRect(sf::IntRect(38, 0, 39, 41));
	}
}
