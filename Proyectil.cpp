#include "Proyectil.h"

Proyectil::Proyectil(sf::Vector2f posicionOrigen, ProjectileOwner propietarioOrigen)
{
	propietario = propietarioOrigen;

	if (propietario == ProjectileOwner::Player)
	{
		radio = 8;
	}

	posicion = posicionOrigen;
	velocidad = 700.f;
	shape.setRadius(radio);
	shape.setFillColor(sf::Color::Cyan);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}

void Proyectil::update(float dt)
{
	if (propietario == ProjectileOwner::Player)
	{
		posicion.y -= velocidad * dt; // actualiza la posicion del proyectil al disparar el jugador;
	}

	shape.setPosition(posicion);
}
void Proyectil::render(sf::RenderWindow& ventana)
{
	ventana.draw(shape);
};
