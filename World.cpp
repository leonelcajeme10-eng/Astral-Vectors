#include "World.h"
#include "SistemaColisiones.h"
#include <iostream>

#include "assets.h"

World::World()
{
	cooldownInicialBoss = true;
	tiempoInicioBoss = 0.f;
	tiempoSonidoBoss = 0.2f;
}

void World::update(float dt,Assets& asset)
{
	jugador.update(dt); // actualiza jugador
	jefe.update(dt);
	sistema_puntuacion.update(dt);
	tiempoSonidoBoss += dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (jugador.canShoot()))
	{
		std::vector<Proyectil> proyectilesJugador = jugador.disparar();

		for (auto& proyectil :proyectilesJugador)
		{
			proyectiles.push_back(proyectil);
		}

		asset.reproducir_sfx("disparo");
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
		if (jefe.getVida() > 0)
		{
			std::vector<Proyectil> proyectilesJefe = jefe.atacar();

			if (!proyectilesJefe.empty() && tiempoSonidoBoss >= 0.2f)
			{
				asset.reproducir_sfx("disparo_boss");
				tiempoSonidoBoss = 0.f;
			}

			for (auto& proyectil : proyectilesJefe) // recorre los proyectiles jefe y los mete a los totales
			{
				proyectiles.push_back(proyectil);
			}
		}
	}

	for (int i = 0; i < proyectiles.size(); i++) // recorre el vector de proyectiles
	{
		proyectiles[i].update(dt); //actualiza todos los proyectiles del vector 

		if (proyectiles[i].getPosicionY() < -50.f || proyectiles[i].getPosicionY() > 1030.f || proyectiles[i].getPosicionX() < -50.f 
			|| proyectiles[i].getPosicionX() > 1440.f)
		{
			proyectiles.erase(proyectiles.begin() + i); // si el proyectil sale de la pantalla lo borra
			i--; // reajusta el vector pana
			sistema_puntuacion.agregar_bala_esquivada();
		}
	}

	sistema_colisiones.verificar_colisiones(jugador, jefe, proyectiles, dt, sistema_puntuacion);
}

Player& World::getJugador()
{
	return jugador;
}

Boss& World::getBoss()
{
	return jefe;
}

std::vector<Proyectil>& World::getProyectiles()
{
	return proyectiles;
}

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
