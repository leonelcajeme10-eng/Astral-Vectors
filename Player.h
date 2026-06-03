#pragma once
#include "Entity.h"
#include "Proyectil.h"

class Player : public Entity
{
private:
	sf::CircleShape shape;
	int vida;
	int vida_max;
	float cooldown_disparo;
	float cooldown_actual;
	float cooldown_dash;
	float cooldown_actual_dash;
	float duracion_dash;

public:
	Player();

	void update(float dt) override;
	void render(sf::RenderWindow& ventana) override;
	bool canShoot(); //indica si ya puede disparar xd
	Proyectil disparar();
	float Dash(float dt);
	int getVida() { return vida; };
	sf::Vector2f getPosicion() { return posicion; }
	float getRadio() { return radio; }
	int getVidaMax() { return vida_max; }
};