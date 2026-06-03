#include "Renderer.h"
#include "Hud.h"

void Renderer::dibujar(sf::RenderWindow& window, World& mundo)
{
	DatosHUD datos;
	
	hud.dibujar(window,datos);
	
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
