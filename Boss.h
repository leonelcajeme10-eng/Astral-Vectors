#pragma once
#include "Entity.h"
#include "Proyectil.h"
#include "PatronAtaque.h"
#include "PatronRecto.h"
#include "PatronAbanico.h"
#include "PatronCircular.h"
#include "PatronEspiral.h"
#include <vector>

class Boss : public Entity
{
private:
	sf::CircleShape shape;
	sf::Texture textura;
	bool textura_cargada;
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
	float tiempo_animacion;
	float tiempo_dash;

public:
	Boss();
	void update(float dt) override;
	void render(sf::RenderTarget& ventana) override;
	std::vector<Proyectil> atacar();
	void recibir_danio(int danio);
	void cambiar_fase();
	sf::Vector2f getPosicion() const { return posicion; }
	float getRadio() const { return radio; }
	int getVida() const { return vida; }
	int getVidaMax() const { return vida_max; }
	int getFase() const { return fase; }

};
