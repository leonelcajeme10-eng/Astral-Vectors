#include "Player.h"
#include "Proyectil.h"
#include <cmath>
#include <iostream>
#include <vector>

Player::Player()
{
	vida = 100;
	vida_max = vida;
	velocidad = 500.f;
	posicion = { 740.f, 900.f };
	radio = 25.f;
	cooldown_disparo = 0.4f;
	cooldown_actual = 0.4f;
	cooldown_dash = 1.f;
	cooldown_actual_dash = cooldown_dash;
	duracion_dash = 0.15f;
	dash = false;
	tiempo_animacion = 0.f;
	inclinacion_sprite = 0.f;
	textura_cargada = textura.loadFromFile("assets/images/player_sprite.png");

	if (textura_cargada)
	{
		textura.setSmooth(true);
	}
	else
	{
		std::cout << "No se pudo cargar assets/images/player_sprite.png\n";
	}

	shape.setRadius(radio);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}
void Player::update(float dt)
{
	tiempo_animacion += dt;

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
	inclinacion_sprite = movimiento.x * 5.f;

	posicion += movimiento * velocidad * multiplicador_dash * dt; //calcula la posicion actual con el movimiento nuevo

	// No permite que el jugador salga de pantalla
	if (posicion.x < radio)
		posicion.x = radio;

	if (posicion.x > 1440 - radio)
		posicion.x = 1440 - radio;

	if (posicion.y < radio)
		posicion.y = radio;

	if (posicion.y > 1080 - radio)
		posicion.y = 1080 - radio;

	shape.setPosition(posicion);

	cooldown_actual += dt; // actualiza el cooldown del pana disparo
};

void Player::render(sf::RenderTarget& ventana)
{
	if (textura_cargada)
	{
		sf::Sprite sprite(textura);
		const sf::Vector2u tam = textura.getSize();
		const float altoObjetivo = 130.f;
		const float escalaBase = altoObjetivo / static_cast<float>(tam.y);
		const float escala = escalaBase * (dash ? 1.08f : 1.f);
		const float flotacion = std::sin(tiempo_animacion * 7.f) * 2.f;
		const float respiracion = 1.f + std::sin(tiempo_animacion * 5.f) * 0.015f;

		sprite.setOrigin({ tam.x / 2.f, tam.y / 2.f });
		sprite.setScale({ escala * respiracion, escala * respiracion });
		sprite.setRotation(sf::degrees(inclinacion_sprite + std::sin(tiempo_animacion * 6.f) * 1.2f));
		sprite.setPosition({ posicion.x, posicion.y + flotacion });
		ventana.draw(sprite);
		return;
	}

	ventana.draw(shape);
}

bool Player::canShoot()
{
	if (cooldown_actual < cooldown_disparo)
		return false;
	else
		return true;
}

std::vector<Proyectil> Player::disparar() 
{
	cooldown_actual = 0.f; // reinicia el cooldown
	std::vector<Proyectil> disparos;

	disparos.push_back(Proyectil({ posicion.x - 30.f, posicion.y }, ProjectileOwner::Player));
	disparos.push_back(Proyectil({ posicion.x, posicion.y }, ProjectileOwner::Player));
	disparos.push_back(Proyectil({ posicion.x + 30.f, posicion.y }, ProjectileOwner::Player));

	return disparos;
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
		dash = true;
		return 3.f;
	}
	
	dash = false;
	return 1.f;
}

void Player::recibir_danio(int danio)
{
	vida -= danio;

	if (vida < 0)
		vida = 0;
};
