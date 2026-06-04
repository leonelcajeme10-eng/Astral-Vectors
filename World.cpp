#include "World.h"
#include "SistemaColisiones.h"
#include <iostream>

void World::update(float dt)
{
	jugador.update(dt); // actualiza jugador
	jefe.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (jugador.canShoot()))
		proyectiles.push_back(Proyectil(jugador.disparar())); // el jugador dispara, devuelve un proyectil al vector de proyectiles

	proyectilesJefe = jefe.atacar(); // le devuelven los proyectiles de atacar

	for (auto& proyectil : proyectilesJefe) // recorre los proyectiles jefe y los mete a los totales
	{
		proyectiles.push_back(proyectil);
	}

	for (int i = 0; i < proyectiles.size(); i++) // recorre el vector de proyectiles
	{
		proyectiles[i].update(dt); //actualiza todos los proyectiles del vector 

		if (proyectiles[i].getPosicionY() < -50.f || proyectiles[i].getPosicionY() > 1030.f)
		{
			proyectiles.erase(proyectiles.begin() + i); // si el proyectil sale de la pantalla lo borra
			i--; // reajusta el vector pana
		}
	}

	sistema_colisiones.verificar_colisiones(jugador, jefe, proyectiles, dt);
}

void World::render(sf::RenderWindow& ventana)
{
	jugador.render(ventana); // renderiza al jugador
	jefe.render(ventana);

	for (auto& proyectil : proyectiles) //renderiza todos los proyectiles del vector 
	{
		proyectil.render(ventana);
	}
};
