#pragma once
#include "Proyectil.h"
#include <vector>

class PatronAtaque
{
public:
	virtual ~PatronAtaque() = default;
	virtual std::vector <Proyectil> generar(sf::Vector2f) = 0;
};