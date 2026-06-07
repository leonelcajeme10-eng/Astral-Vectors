#pragma once
#include "Entity.h"
#include "Player.h"
#include "World.h"
#include "Renderer.h"
#include "menu.h"
#include "Pausa.h"
#include "BossIntroScene.h"
#include "Phase4DialogueScene.h"
#include <SFML/Audio.hpp>

enum class  GameState {
	Menu_estado,
	BossIntro,
	Playing,
	Phase4Dialogue,
	Pause,
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
	Pausa pantalla_pausa;
	BossIntroScene intro_boss;
	Phase4DialogueScene dialogo_fase_4;
	Hud hud;
	Renderer render;
	bool fase4DialogoMostrado = false;

	void actualizar_musica(int fase);


public:
	Game();
	void run();
};
