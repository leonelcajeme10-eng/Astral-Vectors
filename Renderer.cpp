#include "Renderer.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>

void Renderer::dibujar(sf::RenderWindow& window, World& mundo)
{
	DatosHUD datos;

	
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
