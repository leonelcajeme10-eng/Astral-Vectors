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

public:
	Player();

	void update(float dt) override;
	void render(sf::RenderWindow& ventana) override;
	bool canShoot(); //indica si ya puede disparar xd
	Proyectil disparar();
	int getVida() { return vida; };
};