#include "SistemaPuntuacion.h"

SistemaPuntuacion::SistemaPuntuacion()
{
	puntuacion = 0;
	tiempo = 0.f;
	balas_esquivadas = 0;
	danio_infligido = 0;
}

void SistemaPuntuacion::update(float dt)
{
	tiempo += dt;
}

void SistemaPuntuacion::agregar_danio(int danio)
{
	danio_infligido += danio;
	puntuacion += danio * 10;
}

void SistemaPuntuacion::agregar_bala_esquivada()
{
	balas_esquivadas++;
	puntuacion += 5;
}

int SistemaPuntuacion::getPuntuacion() const
{
	return puntuacion;
}

void SistemaPuntuacion::reiniciar()
{
	puntuacion = 0;
	tiempo = 0.f;
	balas_esquivadas = 0;
	danio_infligido = 0;
}
