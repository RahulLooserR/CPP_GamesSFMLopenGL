#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation();
	Animation(sf::Texture& texture, sf::IntRect rect, int count, float switchTime);
	~Animation();
	void update(float dt);
	sf::Sprite getSprite();
	void setSpritePos(sf::Vector2f position, float angle = 0.0f);
	bool isEnd = false;

protected:
	sf::IntRect m_rect;
	sf::Sprite m_sprite;

private:
	float m_switchTime;
	float m_totalTime;
	int m_imageCount;
	int m_currentImage;
};



