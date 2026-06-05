#pragma once
#include "PatronAtaque.h"
#include <vector>

class PatronCircular : public PatronAtaque
{
private:
	int num_proyectiles;
	float angulo_offset;

public:
	PatronCircular();
	std::vector <Proyectil> generar(sf::Vector2f posicionBoss) override;
};
