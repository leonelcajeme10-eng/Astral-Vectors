#include "PatronCircular.h"

PatronCircular::PatronCircular()
{
    num_proyectiles = 16;
    angulo_offset = 0.f;
}

std::vector<Proyectil> PatronCircular::generar(sf::Vector2f posicionBoss)
{
    std::vector<Proyectil> proyectiles;
    float pi = 3.14159265f;

    for (int i = 0; i < num_proyectiles; i++)
    {
        float angulo = angulo_offset + (2 * pi / num_proyectiles) * i; //calcula el angulo de direccion del proyectil

        sf::Vector2f direccion;
        direccion.x = std::cos(angulo);
        direccion.y = std::sin(angulo);

        proyectiles.push_back(Proyectil(posicionBoss, ProjectileOwner::Enemy, direccion)); // almacena el proyectil en el vector ya con la nueva direccion
    }

    angulo_offset += 0.2f; // hace que el siguiente círculo salga rotado

    return proyectiles;
}
