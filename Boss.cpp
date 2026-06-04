#include "Boss.h"

Boss::Boss()
{
	vida_max = 500;
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

	shape.setRadius(radio);
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin({ radio, radio });	// centra el origen del circulo 
	shape.setPosition(posicion);
}

void Boss::update(float dt)
{
	tiempo_ataque += dt;

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

	if (fase == 3)
	{
		if (detenido)
		{
			tiempo_detencion += dt;

			if (tiempo_detencion >= 0.15f)
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

	shape.setPosition(posicion);
}

void Boss::render(sf::RenderWindow& ventana)
{
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
		if (!detenido && tiempo_ataque >= 0.75f) // si no esta detenido y ya es tiempo de atacar, genera proyectiles
		{
			PatronAbanico patron;
			proyectiles = patron.generar(posicion); // genera los 6 proyectiles del patron recto

			tiempo_ataque = 0.f;
			detenido = true;
			tiempo_detencion = 0.f;
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
	if (vida <= vida_max * 0.35f)
		fase = 3;
	else if (vida <= vida_max * 0.70f)
		fase = 2;
	else
		fase = 1;
}
