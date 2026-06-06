#include "Hud.h"
#include "Assets.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "SistemaPuntuacion.h"


void Hud::dibujar(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset)
{	

    this->dibujarPanel(window,asset);
    dibujarPuntuacion(window, datos, asset);
	dibujarVidaJugador(window,datos, asset);
    dibujarVidaBoss(window, datos, asset);
    dibujarTiempo(window, datos, asset);
    dibujarDecoracionInferior(window, asset);
}

void Hud::dibujarPanel(sf::RenderTarget& window, const Assets& asset)
{
    sf::Sprite fondo(asset.get_texture("barra_lateral"));
    
    fondo.setPosition({ this->hudX,this->hudY });
    
    sf::Vector2u tam = asset.get_texture("barra_lateral").getSize();

    fondo.setScale({
        hudAncho / static_cast<float>(tam.x),
        hudAlto / static_cast<float>(tam.y)
        });

    window.draw(fondo);

    sf::RectangleShape sombra;
    sombra.setPosition({ hudX, hudY });
    sombra.setSize({ hudAncho, hudAlto });
    sombra.setFillColor(sf::Color(3, 5, 8, 55));
    window.draw(sombra);

    sf::RectangleShape borde;
    borde.setPosition({ hudX, hudY });
    borde.setSize({ 2.f, hudAlto });
    borde.setFillColor(sf::Color(225, 170, 90, 80));
    window.draw(borde);
}

void Hud::dibujarBarraNegra(sf::RenderTarget& window, const Assets& asset, float x, float y, float ancho, float alto)
{
    const sf::Texture& textura = asset.get_texture("barra_negra");
    sf::Sprite barra(textura);
    sf::Vector2u tam = textura.getSize();

    barra.setPosition({ x, y });
    barra.setScale({
        ancho / static_cast<float>(tam.x),
        alto / static_cast<float>(tam.y)
        });        

    window.draw(barra);
}

void Hud::dibujarVidaJugador(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset)
{
    const sf::Texture& corazonsito = asset.get_texture("corazon");
    sf::Vector2u tamOriginal = corazonsito.getSize();

    const int cantidadCorazones = 5;
    const float anchoCorazon = 52.f;
    const float separacion = 66.f;
    const float escala = anchoCorazon / static_cast<float>(tamOriginal.x);
    const float anchoTotal = anchoCorazon + separacion * (cantidadCorazones - 1);
    const float xInicial = hudX + (hudAncho - anchoTotal) / 2.f;
    const float yInicial = 256.f;

    const float xFondo = 1480.f;
    const float yFondo = 200.f;
    const float anchoFondo = 400.f;
    const float altoFondo = 116.f;

    dibujarBarraNegra(window, asset, xFondo, yFondo, anchoFondo, altoFondo);
    dibujarEtiqueta(window, asset, "LIFE", xFondo + 24.f, yFondo + 16.f, 32);

    int corazonesActivos = 0;

    if (datos.vidaMaxJugador > 0)
    {
        const float porcentajeVida = static_cast<float>(datos.vidaJugador) / datos.vidaMaxJugador;
        corazonesActivos = static_cast<int>(std::ceil(porcentajeVida * cantidadCorazones));
    }

    for (int i = 0; i < cantidadCorazones; i++)
    {
        sf::Sprite sombra(corazonsito);
        sombra.setPosition({ xInicial + (i * separacion) - 2.f, yInicial - 2.f });
        sombra.setScale({ escala * 1.08f, escala * 1.08f });
        sombra.setColor(sf::Color(15, 4, 4, 175));
        window.draw(sombra);

        sf::Sprite corazon(corazonsito);

        corazon.setPosition({ xInicial + (i * separacion), yInicial });
        corazon.setScale({ escala, escala });

        if (i >= corazonesActivos)
        {
            corazon.setColor(sf::Color(255, 255, 255, 62));
        }

        window.draw(corazon);
    }
}

void Hud::dibujarVidaBoss(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset)
{
    const float x = 1480.f;
    const float y = 340.f;
    const float ancho = 400.f;
    const float alto = 126.f;

    dibujarBarraNegra(window, asset, x, y, ancho, alto);

    dibujarEtiqueta(window, asset, "BOSS", x + 24.f, y + 17.f, 32);

    sf::Text fase(asset.get_fuente("texto"));
    fase.setString("F" + std::to_string(datos.fase));
    fase.setCharacterSize(28);
    fase.setFillColor(sf::Color(245, 240, 225, 255));
    fase.setOutlineColor(sf::Color(0, 0, 0, 180));
    fase.setOutlineThickness(1.f);

    sf::FloatRect bounds = fase.getLocalBounds();
    fase.setOrigin({ bounds.position.x + bounds.size.x, bounds.position.y });
    fase.setPosition({ x + ancho - 24.f, y + 21.f });

    window.draw(fase);

    float porcentaje = 0.f;

    if (datos.vidaMaxBoss > 0)
    {
        porcentaje = static_cast<float>(datos.vidaBoss) / datos.vidaMaxBoss;
    }

    dibujarBarra(window, x + 24.f, y + 76.f, ancho - 48.f, 18.f, porcentaje);
}

void Hud::dibujarPuntuacion(sf::RenderTarget& window, const DatosHUD& datos, const Assets& asset)
{
    const float x = 1480.f;
    const float y = 70.f;
    const float ancho = 400.f;
    const float alto = 82.f;

    
    dibujarBarraNegra(window, asset, x, y, ancho, alto);

    dibujarEtiqueta(window, asset, "SCORE", x + 24.f, y + 17.f, 30);

    // Número del puntaje
    sf::Text puntaje(asset.get_fuente("texto"));
    puntaje.setString(std::to_string(datos.puntuacion));
    puntaje.setCharacterSize(34);
    

    // Alinear a la derecha
    sf::FloatRect bounds = puntaje.getLocalBounds();
    puntaje.setOrigin({ bounds.position.x + bounds.size.x, bounds.position.y });
    puntaje.setPosition({ x + ancho - 24.f, y + 22.f });


    window.draw(puntaje);
}

void Hud::dibujarTiempo(sf::RenderTarget& window, const DatosHUD& datos,const Assets& asset)
{
    const float x = 1480.f;
    const float y = 540.f;
    const float ancho = 400.f;
    const float alto = 176.f;

    dibujarBarraNegra(window, asset, x, y, ancho, alto);
    dibujarEtiqueta(window, asset, "TIME", x + 24.f, y + 16.f, 28);

    const std::string tiempoTexto = formatearTiempo(datos.tiempo);
    const float escala = 0.54f;
    const float tuboAncho = asset.get_texture("nixie_tube").getSize().x * escala;
    const float separadorAncho = 20.f;
    const float anchoTotal = tuboAncho * 4.f + separadorAncho;
    const float xInicio = x + (ancho - anchoTotal) / 2.f;
    const float yTubos = y + 62.f;

    dibujarNixieDigito(window, asset, tiempoTexto[0], xInicio, yTubos, escala);
    dibujarNixieDigito(window, asset, tiempoTexto[1], xInicio + tuboAncho, yTubos, escala);
    dibujarSeparadorNixie(window, xInicio + tuboAncho * 2.f + separadorAncho / 2.f, yTubos + 36.f);
    dibujarNixieDigito(window, asset, tiempoTexto[3], xInicio + tuboAncho * 2.f + separadorAncho, yTubos, escala);
    dibujarNixieDigito(window, asset, tiempoTexto[4], xInicio + tuboAncho * 3.f + separadorAncho, yTubos, escala);
}

void Hud::dibujarFase(sf::RenderTarget& window, const DatosHUD& datos, sf::Font& fuente)
{
    
}

void Hud::dibujarDecoracionInferior(sf::RenderTarget& window, const Assets& asset)
{
    const float x = 1480.f;
    const float y = 790.f;
    const float ancho = 400.f;
    const float alto = 190.f;

    dibujarBarraNegra(window, asset, x, y, ancho, alto);

    sf::Text codigo(asset.get_fuente("texto"));
    codigo.setString("LAB-CTRL / FIELD LOG");
    codigo.setCharacterSize(16);
    codigo.setFillColor(sf::Color(235, 225, 200, 130));
    codigo.setOutlineColor(sf::Color(0, 0, 0, 120));
    codigo.setOutlineThickness(1.f);
    codigo.setPosition({ x + 24.f, y + 24.f });
    window.draw(codigo);

    sf::RectangleShape linea;
    linea.setPosition({ x + 24.f, y + 64.f });
    linea.setSize({ ancho - 48.f, 1.f });
    linea.setFillColor(sf::Color(230, 185, 120, 70));
    window.draw(linea);

    for (int i = 0; i < 9; i++)
    {
        const float altoMarca = (i % 3 == 0) ? 28.f : 16.f;
        sf::RectangleShape marca;
        marca.setPosition({ x + 34.f + i * 37.f, y + 88.f });
        marca.setSize({ 2.f, altoMarca });
        marca.setFillColor(sf::Color(235, 225, 200, 75));
        window.draw(marca);
    }

    sf::CircleShape punto(3.f);
    punto.setFillColor(sf::Color(255, 126, 42, 155));
    for (int i = 0; i < 5; i++)
    {
        punto.setPosition({ x + 264.f + i * 18.f, y + 134.f });
        window.draw(punto);
    }

    sf::Text estado(asset.get_fuente("texto"));
    estado.setString("DIVERGENCE TRACE");
    estado.setCharacterSize(14);
    estado.setFillColor(sf::Color(235, 225, 200, 90));
    estado.setPosition({ x + 24.f, y + 132.f });
    window.draw(estado);
}

void Hud::dibujarBarra(sf::RenderTarget& window, float x, float y, float ancho, float alto, float porcentaje) const
{
    if (porcentaje < 0.f)
    {
        porcentaje = 0.f;
    }
    else if (porcentaje > 1.f)
    {
        porcentaje = 1.f;
    }

    sf::RectangleShape fondo;
    fondo.setPosition({ x,y });
    fondo.setSize({ ancho,alto });
    fondo.setFillColor(sf::Color(28, 26, 25, 220));
    fondo.setOutlineColor(sf::Color(220, 170, 95, 70));
    fondo.setOutlineThickness(1.f);

    sf::RectangleShape barra;
    barra.setPosition({ x,y });
    barra.setSize({ ancho * porcentaje, alto });
    barra.setFillColor(sf::Color(190, 66, 58));

    window.draw(fondo);
    window.draw(barra);
}

void Hud::dibujarEtiqueta(sf::RenderTarget& window, const Assets& asset, const std::string& texto, float x, float y, unsigned int tamano) const
{
    sf::Text etiqueta(asset.get_fuente("titulo"));
    etiqueta.setString(texto);
    etiqueta.setCharacterSize(tamano);
    etiqueta.setFillColor(sf::Color(240, 235, 220, 240));
    etiqueta.setOutlineColor(sf::Color(0, 0, 0, 180));
    etiqueta.setOutlineThickness(1.f);
    etiqueta.setPosition({ x, y });
    window.draw(etiqueta);
}

void Hud::dibujarNixieDigito(sf::RenderTarget& window, const Assets& asset, char digito, float x, float y, float escala) const
{
    sf::Sprite tubo(asset.get_texture("nixie_tube"));
    tubo.setPosition({ x, y });
    tubo.setScale({ escala, escala });
    window.draw(tubo);

    const float tuboAncho = asset.get_texture("nixie_tube").getSize().x * escala;
    const float tuboAlto = asset.get_texture("nixie_tube").getSize().y * escala;

    sf::Text filamento(asset.get_fuente("titulo"));
    filamento.setString("8");
    filamento.setCharacterSize(static_cast<unsigned int>(78.f * escala));
    filamento.setFillColor(sf::Color(255, 130, 35, 34));
    filamento.setOutlineColor(sf::Color(255, 92, 12, 28));
    filamento.setOutlineThickness(2.f);

    sf::FloatRect boundsFilamento = filamento.getLocalBounds();
    filamento.setOrigin({ boundsFilamento.position.x + boundsFilamento.size.x / 2.f, boundsFilamento.position.y + boundsFilamento.size.y / 2.f });
    filamento.setPosition({ x + tuboAncho / 2.f, y + tuboAlto * 0.48f });
    window.draw(filamento);

    sf::Text brillo(asset.get_fuente("titulo"));
    brillo.setString(std::string(1, digito));
    brillo.setCharacterSize(static_cast<unsigned int>(78.f * escala));
    brillo.setFillColor(sf::Color(255, 118, 25, 90));
    brillo.setOutlineColor(sf::Color(255, 70, 5, 90));
    brillo.setOutlineThickness(5.f);

    sf::FloatRect boundsBrillo = brillo.getLocalBounds();
    brillo.setOrigin({ boundsBrillo.position.x + boundsBrillo.size.x / 2.f, boundsBrillo.position.y + boundsBrillo.size.y / 2.f });
    brillo.setPosition({ x + tuboAncho / 2.f, y + tuboAlto * 0.48f });
    window.draw(brillo);

    sf::Text numero(asset.get_fuente("titulo"));
    numero.setString(std::string(1, digito));
    numero.setCharacterSize(static_cast<unsigned int>(78.f * escala));
    numero.setFillColor(sf::Color(255, 206, 92, 245));
    numero.setOutlineColor(sf::Color(255, 94, 18, 185));
    numero.setOutlineThickness(1.5f);

    sf::FloatRect boundsNumero = numero.getLocalBounds();
    numero.setOrigin({ boundsNumero.position.x + boundsNumero.size.x / 2.f, boundsNumero.position.y + boundsNumero.size.y / 2.f });
    numero.setPosition({ x + tuboAncho / 2.f, y + tuboAlto * 0.48f });
    window.draw(numero);
}

void Hud::dibujarSeparadorNixie(sf::RenderTarget& window, float x, float y) const
{
    for (float offset : { 0.f, 18.f })
    {
        sf::CircleShape aura(5.5f);
        aura.setOrigin({ 5.5f, 5.5f });
        aura.setPosition({ x, y + offset });
        aura.setFillColor(sf::Color(255, 94, 14, 62));
        window.draw(aura);

        sf::CircleShape punto(2.6f);
        punto.setOrigin({ 2.6f, 2.6f });
        punto.setPosition({ x, y + offset });
        punto.setFillColor(sf::Color(255, 209, 88, 230));
        window.draw(punto);
    }
}

std::string Hud::formatearTiempo(float tiempo) const
{
    const int segundosTotales = std::max(0, static_cast<int>(tiempo));
    const int minutos = std::min(segundosTotales / 60, 99);
    const int segundos = std::min(segundosTotales % 60, 59);

    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << minutos << ":" << std::setw(2) << segundos;
    return stream.str();
}



