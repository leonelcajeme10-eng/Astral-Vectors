#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "World.h"
#include "Hud.h"

class Renderer
{

private:
	Hud& hud;
	Assets& assets_manager;


public:
	Renderer() = default;

	Renderer(Assets& manager, Hud& h) : assets_manager(manager), hud(h)
	{
	}

	void dibujar(sf::RenderWindow& window, World& mundo, float dt);
	void dibujar_jugador(sf::RenderWindow& window, World& mundo);
	void dibujar_boss(sf::RenderWindow& window, World& mundo);
	void dibujar_proyectiles(sf::RenderWindow& window, World& mundo);
	



};
