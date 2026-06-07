#include "Boss.h"
#include <iostream>
#include <ctime>

Boss::Boss()
{
	vida_max = 800;
	vida = vida_max;
	tiempo_ataque = 0.8f;
	patron_actual = 1;
	fase = 1;
	velocidad = 250.f;
	direccion = 1;
	direccionY = 1;
	radio = 50.f;
	posicion = { 710.f, 100.f };
	tiempo_detencion = 0.f;
	detenido = false;
	tiempo_animacion = 0.f;
	textura_cargada = textura.loadFromFile("assets/images/boss_sprite.png");
	tiempo_dash = 0.f;

	if (textura_cargada)
	{
		textura.setSmooth(true);
	}
	else
	{
		std::cout << "No se pudo cargar assets/images/boss_sprite.png\n";
	}

	shape.setRadius(radio);
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}

void Boss::update(float dt)
{
	tiempo_ataque += dt;
	tiempo_animacion += dt;

	if (vida > 0)
	{
		if (fase == 1)
		{
			//se detiene
			if (detenido)
			{
				tiempo_detencion += dt;

				if (tiempo_detencion >= 0.30f)
				{
					detenido = false;
					tiempo_detencion = 0.f;
				}

				shape.setPosition(posicion);
				return;
			}

			posicion.x += velocidad * direccion * dt; //calcula la posicion

			//Esto hace que se mueva hacia la izquierda o la derecha
			if (posicion.x > 1220.f)
			{
				direccion = -1;
			}

			if (posicion.x < 200.f)
			{
				direccion = 1;
			}
		}

		if (fase == 2)
		{
			//se detiene
			if (detenido)
			{
				tiempo_detencion += dt;

				if (tiempo_detencion >= 0.25f)
				{
					detenido = false;
					tiempo_detencion = 0.f;
				}

				shape.setPosition(posicion);
				return;
			}

			if (tiempo_dash <= 0.f && std::rand() % 40 == 0)
			{
				tiempo_dash = 0.45f; 
			}

			float multiplicador_velocidad = 1.f;

			if (tiempo_dash > 0.f)
			{
				multiplicador_velocidad = 2.2f;
				tiempo_dash -= dt;
			}

			posicion.x += velocidad * multiplicador_velocidad * direccion * dt;

			//Esto hace que se mueva hacia la izquierda o la derecha
			if (posicion.x > 1220.f)
			{
				direccion = -1;
			}

			if (posicion.x < 200.f)
			{
				direccion = 1;
			}
		}

		if (fase == 3)
		{
			if (detenido)
			{
				tiempo_detencion += dt;

				if (tiempo_detencion >= 0.25f)
				{
					detenido = false;
					tiempo_detencion = 0.f;
				}

				shape.setPosition(posicion);
				return;
			}

			float velocidadX = 360.f;
			float velocidadY = 160.f;

			posicion.x += velocidadX * direccion * dt;
			posicion.y += velocidadY * direccionY * dt;

			if (posicion.x > 1220.f)
			{
				direccion = -1;
			}

			if (posicion.x < 200.f)
			{
				direccion = 1;
			}

			if (posicion.y > 260.f)
			{
				direccionY = -1;
			}

			if (posicion.y < 80.f)
			{
				direccionY = 1;
			}
		}

		if (fase == 4)
		{
			if (detenido)
			{
				tiempo_detencion += dt;

				if (tiempo_detencion >= 0.20f)
				{
					detenido = false;
					tiempo_detencion = 0.f;
				}

				shape.setPosition(posicion);
				return;
			}

			float velocidadX = 360.f;
			float velocidadY = 160.f;

			posicion.x += velocidadX * direccion * dt;
			posicion.y += velocidadY * direccionY * dt;

			if (posicion.x > 1220.f)
			{
				direccion = -1;
			}

			if (posicion.x < 200.f)
			{
				direccion = 1;
			}

			if (posicion.y > 260.f)
			{
				direccionY = -1;
			}

			if (posicion.y < 80.f)
			{
				direccionY = 1;
			}
		}
	}

	shape.setPosition(posicion);
}

void Boss::render(sf::RenderWindow& ventana)
{
	if (textura_cargada)
	{
		sf::Sprite sprite(textura);
		const sf::Vector2u tam = textura.getSize();
		const float altoObjetivo = 190.f;
		const float escalaBase = altoObjetivo / static_cast<float>(tam.y);
		const float pulso = 1.f + std::sin(tiempo_animacion * 2.5f) * 0.02f;
		const float flotacion = std::sin(tiempo_animacion * 2.f) * 7.f;
		const float balanceo = std::sin(tiempo_animacion * 1.4f) * 2.f;

		sprite.setOrigin({ tam.x / 2.f, tam.y / 2.f });
		sprite.setScale({ escalaBase * pulso, escalaBase * pulso });
		sprite.setRotation(sf::degrees(balanceo));
		sprite.setPosition({ posicion.x, posicion.y + flotacion });
		ventana.draw(sprite);
		return;
	}

	ventana.draw(shape);
}

std::vector<Proyectil> Boss::atacar()
{
	std::vector<Proyectil> proyectiles;

	if (fase == 1)
	{
		if (!detenido && tiempo_ataque >= 1.0f) // si no esta detenido y ya es tiempo de atacar, genera proyectiles
		{
			PatronRecto patron;
			proyectiles = patron.generar(posicion); // genera los 6 proyectiles del patron recto

			tiempo_ataque = 0.f;
			detenido = true;
			tiempo_detencion = 0.f;
		}
	}

	if (fase == 2)
	{
		if (!detenido && tiempo_ataque >= 0.70f) // si no esta detenido y ya es tiempo de atacar, genera proyectiles
		{
			PatronAbanico patron;
			proyectiles = patron.generar(posicion); // genera los 6 proyectiles del patron recto

			tiempo_ataque = 0.f;
			detenido = true;
			tiempo_detencion = 0.f;
		}
	}

	if (fase == 3)
	{
		if (!detenido && tiempo_ataque >= 0.60f) // si no esta detenido y ya es tiempo de atacar, genera proyectiles
		{
			static PatronCircular patron;
			proyectiles = patron.generar(posicion); // genera los proyectiles del patron circular

			tiempo_ataque = 0.f;
			detenido = true;
			tiempo_detencion = 0.f;
		}
	}

	if (fase == 4)
	{
		if (tiempo_ataque >= 0.07f)
		{
			static PatronEspiral patron;
			proyectiles = patron.generar(posicion);

			tiempo_ataque = 0.f;
		}
	}
	return proyectiles; 
}

void Boss::recibir_danio(int danio)
{
	vida -= danio;

	if (vida < 0)
		vida = 0;

	cambiar_fase();
}

void Boss::cambiar_fase()
{
	if (vida <= vida_max * 0.25f)
		fase = 4;
	else if (vida <= vida_max * 0.50f)
		fase = 3;
	else if (vida <= vida_max * 0.75f)
		fase = 2;
	else
		fase = 1;
}
