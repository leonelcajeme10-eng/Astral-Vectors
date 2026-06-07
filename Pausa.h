#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include <string>
#include <vector>

enum class GameState;

class Pausa
{
private:
	int opcion = 0;
	std::vector<std::string> opciones = { "CONTINUAR", "REGRESAR AL MENU" };

public:
	void manejar_evento(const sf::Event& evento, GameState& estado);
	void dibujar(sf::RenderWindow& window, const Assets& assets, const sf::Texture& escena_blur);
};
