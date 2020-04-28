#include "utils.hpp"

// global variables
sf::RenderWindow window;
sf::Event event;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Texture skyTexture;
sf::Sprite skySprite;
sf::Vector2f viewSize(1024, 768);
Hero hero;
std::vector<Rocket*> rockets;
std::vector<Enemy*> enemies;
float currentTime, prevTime = 0.0f;

// initialising sprites(background and heros)
void init()
{
	skyTexture.loadFromFile("content/sky.png");
	skySprite.setTexture(skyTexture);
	backgroundTexture.loadFromFile("content/bg.png");
	backgroundSprite.setTexture(backgroundTexture);
	hero.init("content/hero.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);

	srand((int)time(0));
}
// initialise game window
void init_window()
{
	sf::VideoMode vm(viewSize.x, viewSize.y);

	util::Platform platform;
	window.create(vm, "testing first game", sf::Style::Default);
	platform.setIcon(window.getSystemHandle());
}

// polling inputs
void updatePollEvents()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{

				hero.jump(750.0f);
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				shoot();
			}
		}
	}
}

// u
void updatePosition(float dt)
{
	// spawn enemy after every 1.25 seconds
	currentTime += dt;
	if(currentTime >= prevTime + 1.25f){
		spawnEnemy();
		prevTime = currentTime;
	}

	// update hero
	hero.update(dt);

	// update rockets
	for (unsigned int i = 0; i < rockets.size(); i++) {
        Rocket* rocket = rockets[i];
        rocket->update(dt);
		// checking if rocket crosses the view size and deleting rocket from list
        if (rocket->getSprite().getPosition().x > viewSize.x) {
            rockets.erase(rockets.begin() + i);
            delete(rocket);
        }
    }

	// updating enemies
	for (unsigned int i = 0; i < enemies.size(); i++) {
        Enemy* enemy = enemies[i];
        enemy->update(dt);
        if (enemy->getSprite().getPosition().x < 0) {
            enemies.erase(enemies.begin() + i);
            delete(enemy);
        }
    }

	// collision detection between enemies and rockets
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies[i];
		for (unsigned int j = 0; j < rockets.size(); j++)
		{
			Rocket* rocket = rockets[j];
			if (isCollided(enemy->getSprite(), rocket->getSprite()))
			{
				enemies.erase(enemies.begin() + i);
				rockets.erase(rockets.begin() + j);
				delete enemy;
				delete rocket;
			}
		}
	}

	// collision detection between hero and enemies
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies[i];
		if(isCollided(enemy->getSprite(), hero.getSprite()))
		{
			enemies.erase(enemies.begin() + i);
		}
	}
}

void draw()
{
	window.draw(skySprite);
	window.draw(backgroundSprite);
	window.draw(hero.getSprite());
	for (auto rocket : rockets)
	{
		window.draw(rocket->getSprite());
	}

	for(auto enemy : enemies){
		window.draw(enemy->getSprite());
	}
}

void shoot()
{
	Rocket* rocket = new Rocket;
	rocket->init("content/rocket.png", hero.getSprite().getPosition(), 500.0f);
	rockets.push_back(rocket);
}

void spawnEnemy()
{
	int randPos = rand() % 3;
	sf::Vector2f enemyPos;
	float speed;

	switch (randPos)
	{
		case 0:
			enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
			speed = -400;
			break;
		case 1:
			enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.65f);
			speed = -300;
			break;

		default:
			enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.55f);
			speed = -250;
			break;
	}

	Enemy* enemy = new Enemy;
	enemy->init("content/enemy.png", enemyPos, speed);
	enemies.push_back(enemy);
}

bool isCollided(sf::Sprite sprite1, sf::Sprite sprite2)
{
	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if(shape1.intersects(shape2)){
		return true;
	}
	return false;
}