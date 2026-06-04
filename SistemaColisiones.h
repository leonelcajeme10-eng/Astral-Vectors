#pragma once
#include "Entity.h"
#include "Boss.h"
#include "Proyectil.h"
#include "Player.h"

class SistemaColisiones
{
public:
	void verificar_colisiones(Player& jugador, Boss& jefe, std::vector<Proyectil>& proyectiles);
	bool Colisiona(sf::Vector2f posA, float radioA, sf::Vector2f posB, float radioB);
};