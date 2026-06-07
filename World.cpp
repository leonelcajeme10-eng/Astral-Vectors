#include "World.h"
#include "SistemaColisiones.h"
#include <iostream>

World::World()
{
	cooldownInicialBoss = true;
	tiempoInicioBoss = 0.f;
}

void World::update(float dt)
{
	jugador.update(dt); // actualiza jugador
	jefe.update(dt);
	sistema_puntuacion.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (jugador.canShoot()))
	{
		std::vector<Proyectil> proyectilesJugador = jugador.disparar();

		for (auto& proyectil :proyectilesJugador)
		{
			proyectiles.push_back(proyectil);
		}
	}

	if (cooldownInicialBoss)
	{
		tiempoInicioBoss += dt;

		if (tiempoInicioBoss >= 1.0f)
		{
			cooldownInicialBoss = false;
		}
	}
	else
	{
		std::vector<Proyectil> proyectilesJefe = jefe.atacar();

		for (auto& proyectil : proyectilesJefe) // recorre los proyectiles jefe y los mete a los totales
		{
			proyectiles.push_back(proyectil);
		}
	}

	for (int i = 0; i < proyectiles.size(); i++) // recorre el vector de proyectiles
	{
		proyectiles[i].update(dt); //actualiza todos los proyectiles del vector 

		if (proyectiles[i].getPosicionY() < -50.f || proyectiles[i].getPosicionY() > 1030.f)
		{
			proyectiles.erase(proyectiles.begin() + i); // si el proyectil sale de la pantalla lo borra
			i--; // reajusta el vector pana
			sistema_puntuacion.agregar_bala_esquivada();
		}
	}

	sistema_colisiones.verificar_colisiones(jugador, jefe, proyectiles, dt, sistema_puntuacion);
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

int World::getVidaJugador() const
{
	return jugador.getVida();
}

int World::getVidaMaxJugador() const
{
	return jugador.getVidaMax();
}

int World::getVidaBoss() const
{
	return jefe.getVida();
}

int World::getVidaMaxBoss() const
{
	return jefe.getVidaMax();
}

int World::getFaseBoss() const
{
	return jefe.getFase();
}

int World::getPuntuacion() const
{
	return sistema_puntuacion.getPuntuacion();
}

float World::get_tiempo() const
{

	return sistema_puntuacion.getTiempo();
}
