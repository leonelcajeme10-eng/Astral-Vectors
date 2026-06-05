#include "menu.h"
#include "Assets.h"

void menu::manejar_evento(sf::Event& evento, GameState& estado)
{
}

void menu::dibujar(sf::RenderWindow& window, Assets& assets)
{
	sf::Sprite fondo(assets.get_texture("menu"));


	window.draw(fondo);


}
