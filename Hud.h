#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "SistemaPuntuacion.h"
#include <string>
struct DatosHUD
{
    SistemaPuntuacion sistema;
    int vidaJugador = 80;
    int vidaMaxJugador = 100;
    int vidaBoss = 90;
    int vidaMaxBoss = 100;
    int puntuacion =0;
    float tiempo = 0;
    int fase = 1;
};

class Hud
{
public:

    void dibujar(sf::RenderTarget& window, const DatosHUD& datos, const Assets& assets, float dt);
    Hud() = default;

private:
   
    const float hudX = 1440.f;
    const float hudY = 0.f;
    const float hudAncho = 480.f;
    const float hudAlto = 1080.f;
    const float margen = 40.f;
    float xTexto = hudX + margen; // 1480
    float anchoInterno = hudAncho - margen * 2; // 400
    float scroll_y = 0.f;
   

    void dibujarPanel(sf::RenderTarget& window, const Assets& asset);
    void dibujarBarraNegra(sf::RenderTarget& window, const Assets& asset, float x, float y, float ancho, float alto);
    void dibujarVidaJugador(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset);
    void dibujarVidaBoss(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset);
    void dibujarPuntuacion(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset);
    void dibujarTiempo(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset);
    void dibujarFase(sf::RenderTarget& window, const DatosHUD& datos, sf::Font& fuente);
    void dibujarDecoracionInferior(sf::RenderTarget& window, const Assets& asset);
    void dibujar_fondo(sf::RenderTarget& window, const Assets& asset,float dt);

    void dibujarBarra(sf::RenderTarget& window, float x, float y, float ancho, float alto, float porcentaje) const;
    void dibujarEtiqueta(sf::RenderTarget& window, const Assets& asset, const std::string& texto, float x, float y, unsigned int tamano) const;
    void dibujarNixieDigito(sf::RenderTarget& window, const Assets& asset, char digito, float x, float y, float escala) const;
    void dibujarSeparadorNixie(sf::RenderTarget& window, float x, float y) const;
    std::string formatearTiempo(float tiempo) const;
};


