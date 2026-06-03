#include "Player.h"
#include "Proyectil.h"
#include <cmath>

Player::Player()
{
	vida = 100;
	vida_max = vida;
	velocidad = 500.f;
	posicion = { 400.f, 300.f };
	radio = 30.f;
	cooldown_disparo = 0.4f;
	cooldown_actual = 0.4f;
	cooldown_dash = 1.f;
	cooldown_actual_dash = cooldown_dash;
	duracion_dash = 0.15f;

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

	float magnitud = std::sqrt(movimiento.x * movimiento.x + movimiento.y * movimiento.y);

	if (magnitud != 0.f)
	{
		movimiento.x /= magnitud;
		movimiento.y /= magnitud;
	}

	float multiplicador_dash = Dash(dt); // devuelve 1 o 3 si esta en dashito o no

	posicion += movimiento * velocidad * multiplicador_dash * dt; //calcula la posicion actual con el movimiento nuevo

	// No permite que el jugador salga de pantalla
	if (posicion.x < radio)
		posicion.x = radio;

	if (posicion.x > 1920 - radio)
		posicion.x = 1920 - radio;

	if (posicion.y < radio)
		posicion.y = radio;

	if (posicion.y > 1080 - radio)
		posicion.y = 1080 - radio;

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
}

float Player::Dash(float dt)
{
	cooldown_actual_dash += dt;
	bool shift_presionado = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
	
	if (cooldown_actual_dash >= cooldown_dash)
	{
		if (shift_presionado)
		{
			cooldown_actual_dash = 0;
		}
	}

	if (cooldown_actual_dash < duracion_dash)
	{
		return 3.f;
	}

	return 1.f;
};
