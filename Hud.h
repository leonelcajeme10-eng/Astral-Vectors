#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
struct DatosHUD
{
    int vidaJugador = 80;
    int vidaMaxJugador = 100;
    int vidaBoss = 90;
    int vidaMaxBoss = 100;
    int puntuacion = 1;
    float tiempo = 100.f;
    int fase = 1;
};

class Hud
{
public:

    void dibujar(sf::RenderWindow& window, const DatosHUD& datos, const Assets& assets);
    Hud() = default;

private:
   
    const float hudX = 1440.f;
    const float hudY = 0.f;
    const float hudAncho = 480.f;
    const float hudAlto = 1080.f;
    const float margen = 40.f;
    float xTexto = hudX + margen; // 1480
    float anchoInterno = hudAncho - margen * 2; // 400
   

    void dibujarPanel(sf::RenderWindow& window, const Assets& asset);
    void dibujarBarraNegra(sf::RenderWindow& window, const Assets& asset, float x, float y, float ancho, float alto);
    void dibujarVidaJugador(sf::RenderWindow& window, const DatosHUD& datos, const Assets& asset);
    void dibujarVidaBoss(sf::RenderWindow& window, const DatosHUD& datos, const Assets& asset);
    void dibujarPuntuacion(sf::RenderWindow& window, const DatosHUD& datos, const Assets& asset);
    void dibujarTiempo(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente);
    void dibujarFase(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente);

    void dibujarBarra(sf::RenderWindow& window, float x, float y, float ancho, float alto, float porcentaje) const;
};


