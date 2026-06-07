#pragma once
#include "Entity.h"
#include "Player.h"
#include "Proyectil.h"
#include "Boss.h"
#include <vector>
#include "SistemaColisiones.h"
#include "SistemaPuntuacion.h"

class World
{
private:
	Player jugador;
	Boss jefe;
	std::vector<Proyectil> proyectiles;
	std::vector<Proyectil> proyectilesJefe;
	SistemaColisiones sistema_colisiones;
	SistemaPuntuacion sistema_puntuacion;
	bool cooldownInicialBoss;
	float tiempoInicioBoss;

public:
	World();
	void update(float dt);
	Player& getJugador();
	Boss& getBoss();
	std::vector<Proyectil>& getProyectiles();
	int getVidaJugador() const;
	int getVidaMaxJugador() const;
	int getVidaBoss() const;
	int getVidaMaxBoss() const;
	int getFaseBoss() const;
	int getPuntuacion() const;
	float get_tiempo() const;
};
