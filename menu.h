# pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


enum class GameState;
class Assets;

using namespace std;

class menu
{
private:

	int opcion  = 0;

	vector<string> opciones = { "COMENZAR" , "SALIR" };

public: 
	bool manejar_evento(const sf::Event& evento, GameState& estado);
	void dibujar(sf::RenderWindow& window, Assets& assets);
};

