#include "Hud.h"



void Hud::dibujar(sf::RenderWindow& window, const DatosHUD& datos)
{
	this->dibujarPanel(window);
}

void Hud::dibujarPanel(sf::RenderWindow& window)
{
	sf::RectangleShape panel;

	panel.setPosition({ hudX,hudY });
	panel.setSize({ hudAncho,hudAlto });
	panel.setFillColor(sf::Color(18, 18, 18, 230));

	window.draw(panel);

}

void Hud::dibujarVidaJugador(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
}

void Hud::dibujarVidaBoss(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
}

void Hud::dibujarPuntuacion(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
}

void Hud::dibujarTiempo(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
}

void Hud::dibujarFase(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
}

void Hud::dibujarBarra(sf::RenderWindow& window, float x, float y, float ancho, float alto, float porcentaje)
{
}


