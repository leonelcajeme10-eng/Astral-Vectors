#pragma once
#include "Entity.h"
#include "Proyectil.h"
#include "PatronAtaque.h"
#include "PatronRecto.h"
#include "PatronAbanico.h"
#include "PatronCircular.h"
#include <vector>

class Boss : public Entity
{
private:
	sf::CircleShape shape;
	int vida;
	int vida_max;
	float tiempo_ataque;
	int patron_actual;
	int fase;
	float velocidad;
	int direccion; // 1 derecha, -1 izquierda
	int direccionY;
	bool detenido;
	float tiempo_detencion;

public:
	Boss();
	void update(float dt) override;
	void render(sf::RenderWindow& ventana) override;
	std::vector<Proyectil> atacar();
	void recibir_danio(int danio);
	void cambiar_fase();
	sf::Vector2f getPosicion() const { return posicion; }
	float getRadio() const { return radio; }
	int getVida() const { return vida; }
	int getVidaMax() const { return vida_max; }
	int getFase() const { return fase; }

};
