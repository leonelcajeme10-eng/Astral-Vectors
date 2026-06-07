#include "Renderer.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>
#include "SistemaPuntuacion.h"

void Renderer::dibujar(sf::RenderWindow& window, World& mundo, float dt)
{
	

	DatosHUD datos;
	datos.puntuacion = mundo.getPuntuacion();
	datos.vidaJugador = mundo.getVidaJugador();
	datos.vidaMaxJugador = mundo.getVidaMaxJugador();
	datos.vidaBoss = mundo.getVidaBoss();
	datos.vidaMaxBoss = mundo.getVidaMaxBoss();
	datos.fase = mundo.getFaseBoss();
	datos.tiempo = mundo.get_tiempo();

	hud.dibujar(window, datos, assets_manager, dt);
	dibujar_jugador(window, mundo);
	dibujar_boss(window, mundo);
	dibujar_proyectiles(window, mundo);
}

void Renderer::dibujar_jugador(sf::RenderWindow& window, World& mundo)
{
	mundo.getJugador().render(window);
}

void Renderer::dibujar_boss(sf::RenderWindow& window, World& mundo)
{
	mundo.getBoss().render(window);
}

void Renderer::dibujar_proyectiles(sf::RenderWindow& window, World& mundo)
{
	for (auto& proyectil : mundo.getProyectiles())
	{
		proyectil.render(window);
	}
}
