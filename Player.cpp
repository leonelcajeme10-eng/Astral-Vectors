#include "Player.h"
#include "Proyectil.h"

Player::Player()
{
	velocidad = 500.f;
	posicion = { 400.f, 300.f };
	radio = 40.f;
	cooldown_disparo = 0.4f;
	cooldown_actual = 0.4f;

	shape.setRadius(radio);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}
void Player::update(float dt)
{
	sf::Vector2f movimiento{ 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		movimiento.y -= 1.f; // resta a movimiento en y si presiona W (Arriba)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		movimiento.y += 1.f; // suma a movimiento en y si presiona S (Abajo)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		movimiento.x -= 1.f; // resta a movimiento en x si presiona A (Izquierda)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		movimiento.x += 1.f; // suma a movimiento en x si presiona D (Derecha)

	posicion += movimiento * velocidad * dt; //calcula la posicion actual con el movimiento nuevo
	shape.setPosition(posicion);

	cooldown_actual += dt; // actualiza el cooldown del pana disparo
};

void Player::render(sf::RenderWindow& ventana)
{
	ventana.draw(shape);
}

bool Player::canShoot()
{
	if (cooldown_actual < cooldown_disparo)
		return false;
	else
		return true;
}

Proyectil Player::disparar()
{
	cooldown_actual = 0.f; // reinicia el cooldown
	return Proyectil(posicion, ProjectileOwner::Player);
};
