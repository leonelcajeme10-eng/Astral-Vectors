#pragma once
#include "Entity.h"
#include "Player.h"
#include "World.h"

#include "Renderer.h"

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
	Assets assets; 
	Hud hud;      
	Renderer render;

public:
	Game();
	void run();
};