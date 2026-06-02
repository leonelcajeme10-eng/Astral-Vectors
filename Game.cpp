#include "Game.h"
#include "World.h"

Game::Game() : ventana(sf::VideoMode({ 1920, 1080 }), "Astral Vectors")
{
}

void Game::run()
{
	sf::Clock clock;

	while (ventana.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (const std::optional event = ventana.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				ventana.close();
		}

		world.update(dt);

		ventana.clear();
		world.render(ventana);
		ventana.display();
	}
};
