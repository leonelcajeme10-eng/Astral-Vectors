#pragma once
#include "PatronAtaque.h"
#include <vector>

class PatronRecto : public PatronAtaque
{
public:
	std::vector <Proyectil> generar(sf::Vector2f) override;
};