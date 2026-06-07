#include "Proyectil.h"
#include <cmath>

Proyectil::Proyectil(sf::Vector2f posicionOrigen, ProjectileOwner propietarioOrigen)
{
	propietario = propietarioOrigen;

	if (propietario == ProjectileOwner::Player)
	{
		direccion = { 0.f, -1.f }; // va para arriba
		radio = 7;
		velocidad = 700.f;
		shape.setFillColor(sf::Color::Cyan);
		danio = 2;
	}
	else
	{
		direccion = { 0.f, 1.f }; // va para abajo
		radio = 10;
		velocidad = 500.f;
		shape.setFillColor(sf::Color::Red);
		danio = 5;
	}

	posicion = posicionOrigen;
	shape.setRadius(radio);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}

Proyectil::Proyectil(sf::Vector2f posicionOrigen, ProjectileOwner propietarioOrigen, sf::Vector2f direccionOrigen)
{
	propietario = propietarioOrigen;
	posicion = posicionOrigen;
	direccion = direccionOrigen;

	float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

	if (magnitud != 0.f)
	{
		direccion.x /= magnitud;
		direccion.y /= magnitud;
	}

	if (propietario == ProjectileOwner::Player)
	{
		radio = 7.f;
		velocidad = 700.f;
		shape.setFillColor(sf::Color::Cyan);
		danio = 10;
	}
	else
	{
		radio = 10.f;
		velocidad = 500.f;
		shape.setFillColor(sf::Color::Red);
		danio = 5;
	}

	shape.setRadius(radio);
	shape.setOrigin({ radio, radio });
	shape.setPosition(posicion);
}

void Proyectil::update(float dt)
{
	posicion += direccion * velocidad * dt;
	shape.setPosition(posicion);
}
void Proyectil::render(sf::RenderTarget& ventana)
{
	ventana.draw(shape);
};
