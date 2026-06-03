#include "Game.h"
#include "World.h"
#include "Hud.h"

Game::Game() : ventana(sf::VideoMode({ 1920, 1080 }), "Astral Vectors"), assets(), hud(), render(assets, hud)
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
		this->render.dibujar(ventana, world);
		ventana.display();
	}
};
