#include "Utils.h"

Animation::Animation()
{

}

Animation::Animation(sf::Texture& texture, sf::IntRect rect, int count, float switchTime)
{
	m_rect = rect;
	m_currentImage = 0;
	m_switchTime = switchTime;
	m_imageCount = count;
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(rect);
	m_sprite.setOrigin(sf::Vector2f(m_rect.width / 2, m_rect.height / 2));
	m_totalTime = 0;
}

Animation::~Animation()
{

}

sf::Sprite Animation::getSprite()
{
	return m_sprite;
}

void Animation::setSpritePos(sf::Vector2f position, float angle)
{
	m_sprite.setPosition(position);
	m_sprite.setRotation(angle + 90);
}



void Animation::update(float dt)
{
	m_totalTime += dt;

	if (m_totalTime >= m_switchTime) {
		m_totalTime -= m_switchTime;
		m_currentImage += 1;

		if (m_currentImage >= m_imageCount) {
			m_currentImage = 0;
			isEnd = true;
		}
	}
	m_rect.left = m_currentImage * m_rect.width;
	m_sprite.setTextureRect(m_rect);
}