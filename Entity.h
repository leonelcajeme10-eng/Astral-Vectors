#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Vector2f posicion;
	float velocidad;
	float radio;


public:
	virtual ~Entity() = default; // declara el destructor para este y las clases hijas
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow& ventana) = 0;
};