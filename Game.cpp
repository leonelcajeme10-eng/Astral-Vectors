#include "Game.h"
#include "World.h"
#include "Hud.h"
#include <iostream>
#include "menu.h"

Game::Game() : ventana(sf::VideoMode({ 1920, 1080 }), "Astral Vectors"), assets(), hud(), render(assets, hud) , menu_principal ()
{
	ventana.setFramerateLimit(60);
}

void Game::run()
{
	sf::Clock clock;

	if (!assets.cargar())
	{
		cout << "\n error al cargar fonts";
		return;
	}

	if (!assets.cargar_texturas())
	{
		cout << "\n error al cargar texturas";
		return;
	}

	if (!assets.cargar_musica())
	{
		cout << "\n error al cargar musica";
		return;
	}

	while (ventana.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (auto evento = ventana.pollEvent())
		{
			GameState estado_anterior = estado;

			if (evento->is<sf::Event::Closed>())
			{
				ventana.close();
			}

			if (this->estado == GameState::Menu_estado && menu_principal.manejar_evento(*evento, estado))
			{
				ventana.close();
			}

			if (estado_anterior == GameState::Menu_estado && estado == GameState::Playing)
			{
				assets.musica_menu.stop();
			}
		}

		ventana.clear();

		if (this->estado == GameState::Menu_estado)
		{
			menu_principal.dibujar(ventana, assets);
		}
		else if (this->estado == GameState::Playing) 
		{
			world.update(dt);
			world.render(ventana);
			this->render.dibujar(ventana, world);
		}
		ventana.display();
	}
};
