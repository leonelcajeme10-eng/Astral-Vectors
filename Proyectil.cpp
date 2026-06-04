#include "Proyectil.h"

Proyectil::Proyectil(sf::Vector2f posicionOrigen, ProjectileOwner propietarioOrigen)
{
	propietario = propietarioOrigen;

	if (propietario == ProjectileOwner::Player)
	{
		radio = 7;
		velocidad = 700.f;
		shape.setFillColor(sf::Color::Cyan);


	}
	else
	{
		radio = 10;
		velocidad = 500.f;
		shape.setFillColor(sf::Color::Red);

	}

	danio = 10;
	posicion = posicionOrigen;
	shape.setRadius(radio);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}

void Proyectil::update(float dt)
{
	if (propietario == ProjectileOwner::Player)
	{
		posicion.y -= velocidad * dt; // actualiza la posicion del proyectil al disparar el jugador;
	}
	else
	{
		posicion.y += velocidad * dt;
	}

	shape.setPosition(posicion);
}
void Proyectil::render(sf::RenderWindow& ventana)
{
	ventana.draw(shape);
};
