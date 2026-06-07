#pragma once
#include "PatronAtaque.h"

class PatronEspiral : public PatronAtaque
{
private:
    float angulo_offset;

public:
    PatronEspiral();
    std::vector<Proyectil> generar(sf::Vector2f posicionBoss) override;
};