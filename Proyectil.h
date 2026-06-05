#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

enum class ProjectileOwner
{
	Player,
	Enemy
};

class Proyectil : public Entity
{
private:
	sf::CircleShape shape;
	int danio;
	ProjectileOwner propietario;
	sf::Vector2f direccion;

public:
	Proyectil(sf::Vector2f posicionOrigen, ProjectileOwner propietarioOrigen);
	Proyectil(sf::Vector2f posicionOrigen, ProjectileOwner propietarioOrigen, sf::Vector2f direccionOrigen);
	void update(float dt);
	int getDanio() { return danio; };
	ProjectileOwner getPropietario() { return propietario; };
	void render(sf::RenderWindow& ventana) override;
	float getPosicionY() { return posicion.y; };
	float getPosicionX() { return posicion.x; };
	sf::Vector2f getPosicion() { return posicion; }
	float getRadio() { return radio; }
};