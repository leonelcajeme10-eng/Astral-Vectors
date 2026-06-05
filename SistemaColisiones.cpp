#include "SistemaColisiones.h"
#include <cmath>

SistemaColisiones::SistemaColisiones()
{
    cooldown_colision = 2.0f;
}

void SistemaColisiones::verificar_colisiones(Player& jugador, Boss& jefe, std::vector<Proyectil>& proyectiles, float dt, SistemaPuntuacion& puntuaciones)
{
    // Colision de proyectiles de jugador a jefe y viceversa
    for (int i = 0; i < proyectiles.size(); i++)
    {
        if (proyectiles[i].getPropietario() == ProjectileOwner::Player)
        {
            if (Colisiona(proyectiles[i].getPosicion(), proyectiles[i].getRadio(), jefe.getPosicion(), jefe.getRadio()))
            {
                jefe.recibir_danio(proyectiles[i].getDanio());
                puntuaciones.agregar_danio(proyectiles[i].getDanio());
                proyectiles.erase(proyectiles.begin() + i);
                i--;
            }
        }
        else
        {
            if (!jugador.getDash())
            {
                if (Colisiona(proyectiles[i].getPosicion(), proyectiles[i].getRadio(), jugador.getPosicion(), jugador.getRadio()))
                {
                    jugador.recibir_danio(proyectiles[i].getDanio());
                    proyectiles.erase(proyectiles.begin() + i);
                    i--;
                }
            }
        }
    }

    cooldown_colision += dt;

    //Colision de jugador con jefe
    if (Colisiona(jugador.getPosicion(), jugador.getRadio(), jefe.getPosicion(), jefe.getRadio()) && cooldown_colision >= 2.0f)
    {
        if (!jugador.getDash())
        {
            jugador.recibir_danio(10);
            cooldown_colision = 0.f;
        }
    }
}

bool SistemaColisiones::Colisiona(sf::Vector2f posA, float radioA, sf::Vector2f posB, float radioB)
{
    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;

    float distancia = sqrt(dx * dx + dy * dy);

    if (distancia <= (radioA + radioB))
    {
        return true;
    }
    else
    {
        return false;
    }
}
