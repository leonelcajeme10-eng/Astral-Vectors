#include "Renderer.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>
#include "SistemaPuntuacion.h"

void Renderer::dibujar(sf::RenderWindow& window, World& mundo)
{
	DatosHUD datos;
	datos.puntuacion = mundo.getPuntuacion();
	datos.vidaJugador = mundo.getVidaJugador();
	datos.vidaMaxJugador = mundo.getVidaMaxJugador();
	datos.vidaBoss = mundo.getVidaBoss();
	datos.vidaMaxBoss = mundo.getVidaMaxBoss();
	datos.fase = mundo.getFaseBoss();
	datos.tiempo = mundo.get_tiempo();
	

	
	hud.dibujar(window,datos,assets_manager);

	
}

void Renderer::dibujar_jugador()
{

}

void Renderer::dibujar_boss()
{
}

void Renderer::dibujar_proyectiles()
{
}
