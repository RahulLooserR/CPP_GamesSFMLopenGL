#include "utils.hpp"

// global variables
sf::RenderWindow window;
bool moveLeft = false, moveRight = false;
sf::Event event;
sf::Texture heroTexture;
sf::Sprite heroSprite = sf::Sprite(heroTexture, sf::IntRect(0, 0, 90, 170));
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

// initialising sprites(background and heros)
void init()
{
	heroTexture.loadFromFile("content/heroSprite.png");
	heroSprite.scale(sf::Vector2f(0.5, 0.5));
	heroSprite.setPosition(sf::Vector2f(50, 350));
	backgroundTexture.loadFromFile("content/background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.scale(sf::Vector2f(0.4, 0.5));
}
// initialise game window
void init_window()
{
	sf::Vector2f viewSize(640, 480);
	sf::VideoMode vm(viewSize.x, viewSize.y);

	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(640.0f * screenScalingFactor, 480.0f * screenScalingFactor), "SFML works!", sf::Style::Default);
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
			if (event.key.code == sf::Keyboard::Left)
			{
				moveLeft = true;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				moveRight = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				moveLeft = false;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				moveRight = false;
			}
		}
	}
}

// u
void updatePosition(float dt)
{
	if (moveRight)
	{
		heroSprite.move(50 * dt, 0);
	}
	if (moveLeft)
	{
		heroSprite.move(-50 * dt, 0);
	}
}

void draw()
{
	window.draw(backgroundSprite);
	window.draw(heroSprite);
}