#include "PatronRecto.h"

std::vector<Proyectil> PatronRecto::generar(sf::Vector2f posicionBoss)
{
	std::vector<Proyectil> proyectiles;

	proyectiles.push_back(Proyectil({ posicionBoss.x - 200.f, posicionBoss.y + 50.f }, ProjectileOwner::Enemy));
	proyectiles.push_back(Proyectil({ posicionBoss.x - 120.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy));
	proyectiles.push_back(Proyectil({ posicionBoss.x - 40.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy));
	proyectiles.push_back(Proyectil({ posicionBoss.x + 40.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy));
	proyectiles.push_back(Proyectil({ posicionBoss.x + 120.f,  posicionBoss.y + 50.f }, ProjectileOwner::Enemy));
	proyectiles.push_back(Proyectil({ posicionBoss.x + 200.f, posicionBoss.y + 50.f }, ProjectileOwner::Enemy));



	return proyectiles;
}
