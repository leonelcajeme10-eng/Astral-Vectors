#pragma once
#include "Boss.h"
#include "Player.h"

class SistemaPuntuacion
{
private:
	int puntuacion;
	float tiempo;
	int balas_esquivadas;
	int danio_infligido;

public:
	SistemaPuntuacion();
	void update(float dt);
	void agregar_danio(int danio);
	void agregar_bala_esquivada();
	int getPuntuacion() const;
	float getTiempo() const { return tiempo; }
	int getBalasEsquivadas() { return balas_esquivadas; }
	int getDanioInfligido() { return danio_infligido; }

	void reiniciar();

};