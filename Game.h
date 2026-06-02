#pragma once
#include "Entity.h"
#include "Player.h"
#include "World.h"

enum GameState {
	Menu,
	Playing,
	Victory,
	GameOver,
};

class Game
{
private:
	sf::RenderWindow ventana;
	Player jugador;
	GameState estado;
	World world;

public:
	Game();
	void run();
};