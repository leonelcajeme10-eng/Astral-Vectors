#include "World.h"

void World::update(float dt)
{
	jugador.update(dt); // actualiza jugador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (jugador.canShoot()))
		proyectiles.push_back(Proyectil(jugador.disparar())); // el jugador dispara, devuelve un proyectil al vector de proyectiles

	for (int i = 0; i < proyectiles.size(); i++) // recorre el vector de proyectiles
	{
		proyectiles[i].update(dt); //actualiza todos los proyectiles del vector

		if (proyectiles[i].getPosicionY() < -50.f) 
		{
			proyectiles.erase(proyectiles.begin() + i); // si el proyectil sale de la pantalla lo borra
			i--; // reajusta el vector pana
		}
	}
}
void World::render(sf::RenderWindow& ventana)
{
	jugador.render(ventana); // renderiza al jugador

	for (auto& proyectil : proyectiles) //renderiza todos los proyectiles del vector 
	{
		proyectil.render(ventana);
	}
};
