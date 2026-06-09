#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Assets;
class World;
enum class GameState;

class GameOver
{
private:
	int opcion = 0;
	std::vector<std::string> opciones = { "REGRESAR AL MENU", "SALIR" };

public:
	bool manejar_eventos(GameState& estado, const sf::Event& evento);
	void dibujar(sf::RenderWindow& window, const Assets& assets, const World& world);
};
