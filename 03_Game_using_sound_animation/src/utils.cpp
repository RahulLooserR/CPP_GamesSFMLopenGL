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
float currentTime, prevTime;

sf::Font headingFont;
sf::Text headingText;
sf::Font scoreFont;
sf::Text scoreText;
sf::Font msgFont;
sf::Text msgText;
sf::Font rocketFont;
sf::Text rocketText;

sf::Music bgMusic;
sf::SoundBuffer fireBuffer;
sf::SoundBuffer hitBuffer;
sf::Sound fireSound(fireBuffer);
sf::Sound hitSound(hitBuffer);
bool gameOver = true;
int rocketLeft = 100;
int score;

// resetting game variables
void reset()
{
	score = 0;
	currentTime = 0.0f;
	prevTime = 0.0f;
	rocketLeft = 100;

	// clearing list of enemies and rockets
	for (Enemy* enemy : enemies)
	{
		delete (enemy);
	}
	for (Rocket* rocket : rockets)
	{
		delete (rocket);
	}
	enemies.clear();
	rockets.clear();
}

// initialising sprites(background and heros)
void init()
{
	skyTexture.loadFromFile("content/graphics/sky.png");
	skySprite.setTexture(skyTexture);
	backgroundTexture.loadFromFile("content/graphics/bg.png");
	backgroundSprite.setTexture(backgroundTexture);

	// heading text and properties
	headingFont.loadFromFile("content/fonts/SnackerComic.ttf");
	headingText.setFont(headingFont);
	headingText.setFillColor(sf::Color::Red);
	headingText.setString("Bazooka girl");
	headingText.setCharacterSize(80);

	// setting text position
	sf::FloatRect bounds = headingText.getLocalBounds();
	headingText.setOrigin(bounds.width / 2, bounds.height / 2);
	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.05f));

	// message text and properties
	msgFont.loadFromFile("content/fonts/arial.ttf");
	msgText.setFont(msgFont);
	msgText.setFillColor(sf::Color::Magenta);
	msgText.setString("Press space to start the game, press space to shoot and up arrow to jump");
	msgText.setCharacterSize(30);

	// setting message position
	sf::FloatRect msgbounds = msgText.getLocalBounds();
	msgText.setOrigin(msgbounds.width / 2, msgbounds.height / 2);
	msgText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.15f));

	// score and properties
	scoreFont.loadFromFile("content/fonts/waltographUI.ttf");
	scoreText.setString("Score: 0");
	scoreText.setFont(scoreFont);
	scoreText.setFillColor(sf::Color::Blue);
	scoreText.setCharacterSize(30);

	// setting score position
	sf::FloatRect scorebounds = scoreText.getLocalBounds();
	scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2);
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.25f));

	// rocket font
	rocketFont.loadFromFile("content/fonts/waltographUI.ttf");
	rocketText.setString("Rockets: 100");
	rocketText.setFont(rocketFont);
	rocketText.setCharacterSize(20);
	rocketText.setFillColor(sf::Color::Yellow);
	// rocket text position
	//sf::FloatRect rocketbounds = rocketText.getGlobalBounds();
	//rocketText.setOrigin(rocketbounds.width / 2, rocketbounds.height / 2);
	rocketText.setPosition(sf::Vector2f(viewSize.x * 0.02f, viewSize.y * 0.25f));

	hero.init("content/graphics/heroAnim.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200, 4, 1.0f);

	// loading background music
	bgMusic.openFromFile("content/audio/bgMusic.ogg");
	bgMusic.setLoop(true);
	bgMusic.play();


	hitBuffer.loadFromFile("content/audio/hit.ogg");
	fireBuffer.loadFromFile("content/audio/fire.ogg");

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
				if (gameOver)
				{
					gameOver = false;
					reset();
				}
				else
				{
					shoot();
				}
			}
		}
	}
}

// u
void updatePosition(float dt)
{
	static int counterRocket = 0;
	// spawn enemy after every 1.25 seconds
	currentTime += dt;
	if (currentTime >= prevTime + 1.25f)
	{
		spawnEnemy();
		prevTime = currentTime;
		counterRocket++;
	}

	if(counterRocket >= 8){
		rocketLeft += 5;
		counterRocket = 0;
	}

	// update hero
	hero.update(dt);

	// update rockets
	for (unsigned int i = 0; i < rockets.size(); i++)
	{
		Rocket* rocket = rockets[i];
		rocket->update(dt);
		// checking if rocket crosses the view size and deleting rocket from list
		if (rocket->getSprite().getPosition().x > viewSize.x)
		{
			rockets.erase(rockets.begin() + i);
			delete (rocket);
		}
	}

	// updating enemies
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies[i];
		enemy->update(dt);
		if (enemy->getSprite().getPosition().x < 0)
		{
			enemies.erase(enemies.begin() + i);
			delete (enemy);
			gameOver = true;
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
				score++;
				hitSound.play();
			}
		}
	}

	// collision detection between hero and enemies
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies[i];
		if (isCollided(enemy->getSprite(), hero.getSprite()))
		{
			// enemies.erase(enemies.begin() + i);
			gameOver = true;
			hitSound.play();
		}
	}
}

void draw()
{
	window.draw(skySprite);
	window.draw(backgroundSprite);
	window.draw(headingText);
	if (gameOver)
	{
		window.draw(msgText);
	}
	else
	{
		auto finalScore = "Score: " + std::to_string(score);
		scoreText.setString(finalScore);
		window.draw(scoreText);
		auto finalRocket = "Rockets: " + std::to_string(rocketLeft);
		rocketText.setString(finalRocket);
		window.draw(rocketText);
	}

	window.draw(hero.getSprite());
	for (auto rocket : rockets)
	{
		window.draw(rocket->getSprite());
	}

	for (auto enemy : enemies)
	{
		window.draw(enemy->getSprite());
	}
}

void shoot()
{
	if (rocketLeft > 0)
	{
		Rocket* rocket = new Rocket;
		rocket->init("content/graphics/rocket.png", hero.getSprite().getPosition(), 500.0f);
		rockets.push_back(rocket);
		fireSound.play();
		rocketLeft--;
	}
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
	enemy->init("content/graphics/enemy.png", enemyPos, speed);
	enemies.push_back(enemy);
}

bool isCollided(sf::Sprite sprite1, sf::Sprite sprite2)
{
	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2))
	{
		return true;
	}
	return false;
}