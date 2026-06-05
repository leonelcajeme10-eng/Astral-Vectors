#pragma once
#include "Entity.h"
#include "Player.h"
#include "World.h"
#include "Renderer.h"
#include "menu.h"
#include <SFML/Audio.hpp>

enum class  GameState {
	Menu_estado,
	Playing,
	Victory,
	GameOver,
};

class Game
{
private:
	sf::RenderWindow ventana;

	GameState estado = GameState::Menu_estado;
	World world;
	Assets assets;
	menu menu_principal;
	Hud hud;
	Renderer render;


public:
	Game();
	void run();
};