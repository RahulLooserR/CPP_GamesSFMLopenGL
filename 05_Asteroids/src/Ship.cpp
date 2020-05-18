#include "Utils.h"

Ship::Ship()
{

}

Ship::~Ship()
{
}

void Ship::update(float dt)
{
        if (thrust)
        {
            dx += cos(angle * DEGTORAD) * 0.1;
            dy += sin(angle * DEGTORAD) * 0.1;
        }
        else
        {
            dx *= 0.99;
            dy *= 0.99;
        }

        float speed = sqrt(dx * dx + dy * dy);
        if (speed > MAXSPEED)
        {
            dx *= MAXSPEED / speed;
            dy *= MAXSPEED / speed;
        }

        m_position.x += dx;
        m_position.y += dy;

        if (m_position.x > W) m_position.x = 0; if (m_position.x < 0) m_position.x = W;
        if (m_position.y > H) m_position.y = 0; if (m_position.y < 0) m_position.y = H;
	
	shipAnim->setSpritePos(m_position, angle);
	shipAnim->update(dt);
}

void Ship::setAnimation(std::string name, ShipAnimation& anim, sf::Vector2f position, float angle, float R)
{
    radius = R;
    this->name = name;
    shipAnim = new ShipAnimation;
    *shipAnim = anim;
    m_position = position;
    this->angle = angle;
}

void Ship::draw(sf::RenderWindow& window)
{
    window.draw(shipAnim->getSprite());
}

