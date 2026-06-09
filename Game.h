#pragma once
#include "Entity.h"
#include "Player.h"
#include "World.h"
#include "Renderer.h"
#include "menu.h"
#include "Pausa.h"
#include "BossIntroScene.h"
#include "Phase4DialogueScene.h"
#include "GameOver.h"
#include <SFML/Audio.hpp>

enum class  GameState {
	Menu_estado,
	BossIntro,
	Playing,
	Phase4Dialogue,
	Pause,
	Victory,
	GameOver,
	Win,
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
	GameOver pantalla_game_over;
	BossIntroScene intro_boss;
	Phase4DialogueScene dialogo_fase_4;
	Hud hud;
	Renderer render;
	bool fase4DialogoMostrado = false;
	bool risaGameOverReproducida = false;

	void actualizar_musica(int fase);
	void actualizar_sonidos();
	void reiniciar_partida();
	void registrar_fin_partida();


public:
	Game();
	void run();
};
