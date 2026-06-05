#pragma once
#include "PatronAtaque.h"
#include <vector>

class PatronAbanico : public PatronAtaque
{
public:
	std::vector <Proyectil> generar(sf::Vector2f posicionBoss) override;
};
