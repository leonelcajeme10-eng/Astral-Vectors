#pragma once
#include "Entity.h"
#include "Player.h"
#include "Proyectil.h"
#include "Boss.h"
#include <vector>
#include "SistemaColisiones.h"

class World
{
private:
	Player jugador;
	Boss jefe;
	std::vector<Proyectil> proyectiles;
	std::vector<Proyectil> proyectilesJefe;
	SistemaColisiones sistema_colisiones;

public:
	void update(float dt);
	void render(sf::RenderWindow& ventana); // renderiza todo lo que hay en el juego (jugador, boss, proyectiles)
	int getVidaJugador() const;
	int getVidaMaxJugador() const;
	int getVidaBoss() const;
	int getVidaMaxBoss() const;
	int getFaseBoss() const;
};
