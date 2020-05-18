#include "Utils.h"
#include <iostream>


float DEGTORAD = 0.0174533f;
int W = 1024;
int H = 640;

sf::Texture spaceTexture, shipTexture, bulletTexture, asteroidTexture, explosionTexture;
sf::Sprite spaceSprite;
Animation bulletAnimation;
Animation asteroidsAnimation;
Animation explosionAnim;
std::vector<Entity*> entities;

ShipAnimation shipAnim;
Ship* ship = new Ship;
float currentTime = 0.0f, prevTime = 0.0f;
int count = 0;
bool gameOver = true;

void setup()
{
	
	spaceTexture.loadFromFile("Assets/graphics/background.jpg");
	shipTexture.loadFromFile("Assets/graphics/spaceship.png");
	asteroidTexture.loadFromFile("Assets/graphics/rock.png");
	shipTexture.setSmooth(true);

	bulletTexture.loadFromFile("Assets/graphics/fire_red.png");
	explosionTexture.loadFromFile("Assets/graphics/expAsteroid.png");

	bulletAnimation = Animation(bulletTexture, sf::IntRect(0, 0, 32, 64), 16, 2.0f);
	asteroidsAnimation = Animation(asteroidTexture, sf::IntRect(0, 0, 64, 64), 16, 0.1f);
	shipAnim = ShipAnimation(shipTexture, sf::IntRect(38, 0, 39, 42));
	explosionAnim = Animation(explosionTexture, sf::IntRect(0, 0, 50, 51), 20, 0.06f);
	spaceSprite.setTexture(spaceTexture);
	spaceSprite.scale(sf::Vector2f(0.65f, 0.60f));

	ship->setAnimation("ship", shipAnim, sf::Vector2f(400, 400), -90.0f, 20);
	entities.push_back(ship);


	for (auto i = 0; i < 10; i++) {
		Asteroid* asteroid = new Asteroid;
		asteroid->setAnimation("asteroid", asteroidsAnimation, sf::Vector2f(rand() % W, 
			rand() % H), rand() % (int)360, 40);
		entities.push_back(asteroid);
		count++;
	}
}

void fire(float dt)
{
	currentTime += dt;
	if (currentTime >= prevTime + 0.15f)
	{
		Bullet* bullet = new Bullet();
		bullet->setAnimation("bullet", bulletAnimation, ship->m_position, ship->angle, 20);
		entities.push_back(bullet);
		prevTime = currentTime;
	}
}

void update(float dt)
{

	for (auto entity : entities) {
		entity->update(dt);
	}

	for (auto a : entities) {
		for (auto b : entities) {
			if (a->name == "bullet" && b->name == "asteroid" && isCollided(a, b)) {
				a->life = false;
				b->life = false;

				Entity* astExp = new Entity();
				astExp->setAnimation("explosion", explosionAnim, a->m_position);
				entities.push_back(astExp);
				
				count--;
			}
			

			if (a->name == "ship" && b->name == "asteroid" && isCollided(a, b)) {
				a->life = false;
				b->life = false;

				Entity* astExp = new Entity();
				astExp->setAnimation("shipExplosion", explosionAnim, a->m_position);
				entities.push_back(astExp);
				gameOver = true;
			}
			
		}
	}
	if (count < 15) {
		Asteroid* asteroid = new Asteroid;
		asteroid->setAnimation("asteroid", asteroidsAnimation, sf::Vector2f(rand() % W,
			rand() % H), rand() % (int)360, 40);
		entities.push_back(asteroid);
		count++;
	}

	for (auto i = entities.begin();i != entities.end();)
	{
		Entity* entity = *i;

		if (entity->life == false) {
			i = entities.erase(i); 
			delete entity;
		}
		else i++;
	}
}

bool isCollided(Entity* a, Entity* b)
{
	return (a->m_position.x - b->m_position.x) * (a->m_position.x - b->m_position.x) +
		(a->m_position.y - b->m_position.y) * (a->m_position.y - b->m_position.y) <
		a->radius * b->radius;
}

void draw(sf::RenderWindow& window)
{
	for (auto entity : entities)
		entity->draw(window);
}