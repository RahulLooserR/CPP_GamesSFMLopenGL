
#include "utils.h"

int main()
{
	init_window();
	init();
	sf::Clock clock;

	while (window.isOpen())
	{
		updatePollEvents();

		sf::Time dt = clock.restart();
		if (!gameOver)
		{
			updatePosition(dt.asSeconds());
		}
		window.clear();
		draw();
		window.display();
	}

	return 0;

}

