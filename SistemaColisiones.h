#pragma once
#include "Entity.h"
#include "Boss.h"
#include "Proyectil.h"
#include "Player.h"

class SistemaColisiones
{
private:
	float cooldown_colision;

public:
	SistemaColisiones();
	void verificar_colisiones(Player& jugador, Boss& jefe, std::vector<Proyectil>& proyectiles, float dt);
	bool Colisiona(sf::Vector2f posA, float radioA, sf::Vector2f posB, float radioB);
};