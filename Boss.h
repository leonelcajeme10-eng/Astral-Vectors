#pragma once
#include "Entity.h"
#include "Proyectil.h"
#include "PatronAtaque.h"
#include "PatronRecto.h"
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
	int vidas;
	float velocidad;
	int direccion; // 1 derecha, -1 izquierda
	bool detenido;
	float tiempo_detencion;

public:
	Boss();
	void update(float dt) override;
	void render(sf::RenderWindow& ventana) override;
	std::vector<Proyectil> atacar();
	void recibir_danio(int danio);
	void cambiar_fase();
	sf::Vector2f getPosicion() { return posicion; }
	float getRadio() { return radio; }
	int getVida() { return vida; }
	int getFase() { return fase; }

};