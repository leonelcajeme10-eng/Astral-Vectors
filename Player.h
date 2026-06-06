#pragma once
#include "Entity.h"
#include "Proyectil.h"

class Player : public Entity
{
private:
	sf::CircleShape shape;
	sf::Texture textura;
	bool textura_cargada;
	int vida;
	int vida_max;
	float cooldown_disparo;
	float cooldown_actual;
	float cooldown_dash;
	float cooldown_actual_dash;
	float duracion_dash;
	bool dash;
	float tiempo_animacion;
	float inclinacion_sprite;

public:
	Player();

	void update(float dt) override;
	void render(sf::RenderWindow& ventana) override;
	bool canShoot(); //indica si ya puede disparar xd
	Proyectil disparar();
	float Dash(float dt);
	void recibir_danio(int danio);
	int getVida() const { return vida; };
	sf::Vector2f getPosicion() const { return posicion; }
	float getRadio() const { return radio; }
	int getVidaMax() const { return vida_max; }
	bool getDash() const { return dash; }
};
