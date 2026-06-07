#include "PatronEspiral.h"
#include <cmath>


PatronEspiral::PatronEspiral()
{
	angulo_offset = 0.f;
}

std::vector<Proyectil> PatronEspiral::generar(sf::Vector2f posicionBoss)
{
    std::vector<Proyectil> proyectiles;
    float pi = 3.14159265f;

    int brazos = 4; // cantidad de lineas de la espiral

    for (int i = 0; i < brazos; i++)
    {
        float angulo = angulo_offset + (2 * pi / brazos) * i;

        sf::Vector2f direccion;
        direccion.x = std::cos(angulo);
        direccion.y = std::sin(angulo);

        proyectiles.push_back(Proyectil(posicionBoss, ProjectileOwner::Enemy, direccion));
    }

    angulo_offset += 0.15f; // velocidad de rotacion de la espiral

    if (angulo_offset >= 2 * pi)
        angulo_offset -= 2 * pi;

    return proyectiles;

}
