#include "Utils.h"
#include <iostream>

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(W, H), "Space Ship", sf::Style::Default);
	window.setFramerateLimit(60);

	setup();
	
	sf::Clock clock;
	float dt = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		dt = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			gameOver = false;
			fire(dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			ship->thrust = true;
		}
		else {
			ship->thrust = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			ship->angle += 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			ship->angle -= 3;
		}
		
		if(!gameOver)
			update(dt);
		window.clear();
		window.draw(spaceSprite);
		draw(window);
		window.display();
	}
	
	return 0;
}