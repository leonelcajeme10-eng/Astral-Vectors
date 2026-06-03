#pragma once
#include "Entity.h"
#include "Proyectil.h"
#include <vector>

class Boss : public Entity
{
private:
	int vida;
	int vida_max;
	float tiempo_ataque;
	int patron_actual;
	int fase;

public:
	void update(float dt) override;
	void render(sf::RenderWindow& ventana) override;
	std::vector<Proyectil> atacar();
	int recibir_danio(int danio);
	void cambiar_fase();
	sf::Vector2f getPosicion() { return posicion; }
	float getRadio() { return radio; }
	int getVidaMax() { return vida_max; }

};