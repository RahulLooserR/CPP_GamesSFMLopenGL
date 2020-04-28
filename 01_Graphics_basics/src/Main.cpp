#include "utils.hpp"

int main()
{
	init_window();
	init();
	sf::Clock clock;

	while (window.isOpen())
	{
		updatePollEvents();

		sf::Time dt = clock.restart();
		updatePosition(dt.asSeconds());

		window.clear();
		draw();
		window.display();
	}

	return 0;
}
