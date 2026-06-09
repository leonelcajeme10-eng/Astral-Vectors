#include "Game.h"
#include "World.h"
#include "Hud.h"
#include <iostream>
#include "menu.h"

Game::Game() : ventana(sf::VideoMode({ 1920, 1080 }), "Astral Vectors"), assets(), hud(), render(assets, hud) , menu_principal ()
{
	ventana.setFramerateLimit(60);
	ventana.setKeyRepeatEnabled(false);
}



void Game::actualizar_musica(int fase)
{
	if (estado == GameState::Menu_estado)
	{
		assets.musica_fase_1.stop();
		assets.musica_fase_4.stop();

		if (assets.musica_menu.getStatus() != sf::SoundSource::Status::Playing)
		{
			assets.musica_menu.play();
		}

		return;
	}

	assets.musica_menu.stop();

	if (estado == GameState::Pause || estado == GameState::Phase4Dialogue)
	{
		return;
	}

	if (estado != GameState::Playing)
	{
		assets.musica_fase_1.stop();
		assets.musica_fase_4.stop();
		return;
	}

	if (fase == 4)
	{
		assets.musica_fase_1.stop();

		if (assets.musica_fase_4.getStatus() != sf::SoundSource::Status::Playing)
		{
			assets.musica_fase_4.play();
		}

		return;
	}

	assets.musica_fase_4.stop();

	if (assets.musica_fase_1.getStatus() != sf::SoundSource::Status::Playing)
	{
		assets.musica_fase_1.play();
	}
}




void Game::reiniciar_partida()
{
	world = World();
	fase4DialogoMostrado = false;
	risaGameOverReproducida = false;
	dialogo_fase_4.reset();
}

void Game::registrar_fin_partida()
{
	risaGameOverReproducida = false;
	estado = GameState::GameOver;
}

void Game::run()
{
	sf::Clock clock;

	if (!assets.cargar())
	{
		cout << "\n error al cargar fonts";
		return;
	}

	if (!assets.cargar_texturas())
	{
		cout << "\n error al cargar texturas";
		return;
	}

	if (!intro_boss.load(assets))
	{
		cout << "\n error al cargar intro boss";
		return;
	}

	if (!dialogo_fase_4.load(assets))
	{
		cout << "\n error al cargar dialogo fase 4";
		return;
	}

	if (!assets.cargar_musica())
	{
		cout << "\n error al cargar musica";
		return;
	}

	if (!assets.cargar_sonido())
	{
		cout << "\n error al cargar sonidos";
		return;
	}

	sf::RenderTexture escena_pausa({ 480, 270 });
	escena_pausa.setSmooth(true);
	escena_pausa.setView(sf::View({ 960.f, 540.f }, { 1920.f, 1080.f }));

	while (ventana.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (auto evento = ventana.pollEvent())
		{
			GameState estado_anterior = estado;

			if (evento->is<sf::Event::Closed>())
			{
				ventana.close();
			}

			switch (estado)
			{
			case GameState::Menu_estado:
			{
				if (menu_principal.manejar_evento(*evento, estado))
				{
					ventana.close();
				}
				break;
			}

			case GameState::Playing:




				if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>())
				{
					if (estado == GameState::Playing && (tecla->code == sf::Keyboard::Key::P || tecla->code == sf::Keyboard::Key::Escape))
					{
						estado = GameState::Pause;
					}
				}
				break;
			case GameState::BossIntro:
				intro_boss.handleEvent(*evento);
				break;

			case GameState::Phase4Dialogue:
				dialogo_fase_4.handleEvent(*evento);
				break;

			case GameState::Pause:
				pantalla_pausa.manejar_evento(*evento, estado);
				break;

			case GameState::Victory:
			case GameState::GameOver:
			case GameState::Win:
				if (pantalla_game_over.manejar_eventos(estado, *evento))
				{
					ventana.close();
				}
				break;
			}

			if (estado_anterior != estado && estado == GameState::BossIntro)
			{
				reiniciar_partida();
				intro_boss.reset();
			}
			
		}

		bool intro_terminada_este_frame = false;
		bool dialogo_fase_4_terminado_este_frame = false;

		if (estado == GameState::BossIntro)
		{
			intro_boss.update(dt);

			if (intro_boss.isFinished())
			{
				estado = GameState::Playing;
				intro_terminada_este_frame = true;
			}
		}

		if (estado == GameState::Phase4Dialogue)
		{
			dialogo_fase_4.update(dt);

			if (dialogo_fase_4.isFinished())
			{
				estado = GameState::Playing;
				dialogo_fase_4_terminado_este_frame = true;
			}
		}

		if (estado == GameState::Playing && !intro_terminada_este_frame && !dialogo_fase_4_terminado_este_frame)
		{
			world.update(dt,assets);

			if (world.getVidaBoss() <= 0 || world.getVidaJugador() <= 0)
			{
				registrar_fin_partida();
			}
			else if (!fase4DialogoMostrado && world.getFaseBoss() == 4)
			{
				fase4DialogoMostrado = true;
				dialogo_fase_4.reset();
				estado = GameState::Phase4Dialogue;
			}
		}

		ventana.clear();

		if (this->estado == GameState::Menu_estado)
		{
			
			menu_principal.dibujar(ventana, assets);
		}
		else if (this->estado == GameState::BossIntro)
		{
			intro_boss.render(ventana);
		}
		else if (this->estado == GameState::Playing) 
		{
			this->render.dibujar(ventana,world,dt);
		}
		else if (this->estado == GameState::Phase4Dialogue)
		{
			this->render.dibujar(ventana, world, 0.f);
			dialogo_fase_4.render(ventana);
		}
		else if (this->estado == GameState::Pause)
		{
			escena_pausa.clear();
			this->render.dibujar(escena_pausa, world, 0.f);
			escena_pausa.display();

			pantalla_pausa.dibujar(ventana, assets, escena_pausa.getTexture());
		}
		else if (this->estado == GameState::GameOver)
		{

			if (world.getVidaJugador() <= 0 && !risaGameOverReproducida)
			{
				assets.reproducir_sfx("risa");
				risaGameOverReproducida = true;
			}


			pantalla_game_over.dibujar(ventana, assets, world);
		}

		actualizar_musica(world.getFaseBoss());

		ventana.display();
	}
}
