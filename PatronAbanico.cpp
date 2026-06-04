#include "PatronAbanico.h"

std::vector<Proyectil> PatronAbanico::generar(sf::Vector2f posicionBoss)
{
	std::vector<Proyectil> proyectiles;

	proyectiles.push_back(Proyectil({ posicionBoss.x - 200.f, posicionBoss.y + 50.f }, ProjectileOwner::Enemy, { -0.8f, 1.f }));
	proyectiles.push_back(Proyectil({ posicionBoss.x - 120.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy, { -0.45f, 1.f }));
	proyectiles.push_back(Proyectil({ posicionBoss.x - 40.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy, { -0.15f, 1.f }));
	proyectiles.push_back(Proyectil({ posicionBoss.x + 40.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy, { 0.15f, 1.f }));
	proyectiles.push_back(Proyectil({ posicionBoss.x + 120.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy, { 0.45f, 1.f }));
	proyectiles.push_back(Proyectil({ posicionBoss.x + 200.f, posicionBoss.y + 50.f }, ProjectileOwner::Enemy, { 0.8f, 1.f }));

	return proyectiles;
}
