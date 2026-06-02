#pragma once
#include "Entity.h"
#include "Player.h"
#include "Proyectil.h"
#include <vector>

class World
{
private:
	Player jugador;
	std::vector<Proyectil> proyectiles;

public:
	void update(float dt);
	void render(sf::RenderWindow& ventana); // renderiza todo lo que hay en el juego (jugador, boss, proyectiles)
};