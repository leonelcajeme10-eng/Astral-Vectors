#include "Hud.h"
#include "Assets.h"
#include <SFML/Graphics.hpp>
#include <cmath>


void Hud::dibujar(sf::RenderWindow& window, const DatosHUD& datos, const Assets& asset)
{	

    this->dibujarPanel(window,asset);
	dibujarVidaJugador(window,datos, asset);
    dibujarPuntuacion(window, datos, asset);
	
	
}

void Hud::dibujarPanel(sf::RenderWindow& window, const Assets& asset)
{
    sf::Sprite fondo(asset.get_texture("barra_lateral"));
    
    fondo.setPosition({ this->hudX,this->hudY });
    
    sf::Vector2u tam = asset.get_texture("barra_lateral").getSize();

    fondo.setScale({
        hudAncho / static_cast<float>(tam.x),
        hudAlto / static_cast<float>(tam.y)
        });

    window.draw(fondo);
        
    
}

void Hud::dibujarBarraNegra(sf::RenderWindow& window, const Assets& asset, float x, float y, float ancho, float alto)
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

void Hud::dibujarVidaJugador(sf::RenderWindow& window, const DatosHUD& datos, const Assets& asset)
{
    const sf::Texture& corazonsito = asset.get_texture("corazon");
    sf::Vector2u tamOriginal = corazonsito.getSize();

    const int cantidadCorazones = 5;
    const float anchoCorazon = 54.f;
    const float separacion = 68.f;
    const float escala = anchoCorazon / static_cast<float>(tamOriginal.x);
    const float anchoTotal = anchoCorazon + separacion * (cantidadCorazones - 1);
    const float xInicial = hudX + (hudAncho - anchoTotal) / 2.f;
    const float yInicial = 315.f;

    const float xFondo = 1480.f;
    const float yFondo = 292.f;
    const float anchoFondo = 380.f;
    const float altoFondo = 95.f;

    dibujarBarraNegra(window, asset, xFondo, yFondo, anchoFondo, altoFondo);

    int corazonesActivos = 0;

    if (datos.vidaMaxJugador > 0)
    {
        const float porcentajeVida = static_cast<float>(datos.vidaJugador) / datos.vidaMaxJugador;
        corazonesActivos = static_cast<int>(std::ceil(porcentajeVida * cantidadCorazones));
    }

    for (int i = 0; i < cantidadCorazones; i++)
    {
        sf::Sprite corazon(corazonsito);

        corazon.setPosition({ xInicial + (i * separacion), yInicial });
        corazon.setScale({ escala, escala });

        if (i >= corazonesActivos)
        {
            corazon.setColor(sf::Color(255, 255, 255, 70));
        }

        window.draw(corazon);
    }
}

void Hud::dibujarVidaBoss(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
}

void Hud::dibujarPuntuacion(sf::RenderWindow& window, const DatosHUD& datos, const Assets& asset)
{
    const float x = 1480.f;
    const float y = 120.f;
    const float ancho = 380.f;
    const float alto = 90.f;
   
    dibujarBarraNegra(window, asset, x, y, ancho, alto);

    // Texto "PUNTAJE"
    sf::Text titulo(asset.get_fuente("titulo"));
    titulo.setString("PUNTAJE");
    titulo.setCharacterSize(34);
    titulo.setFillColor(sf::Color(240, 235, 220, 240));
    titulo.setOutlineColor(sf::Color(0, 0, 0, 180));
    titulo.setOutlineThickness(1.f);
    titulo.setPosition({ x + 25.f, y + 18.f });

    window.draw(titulo);

    // Número del puntaje
    sf::Text puntaje(asset.get_fuente("texto"));
    puntaje.setString(std::to_string(datos.puntuacion));
    puntaje.setCharacterSize(36);
    puntaje.setFillColor(sf::Color(245, 240, 225, 255));
    puntaje.setOutlineColor(sf::Color(0, 0, 0, 180));
    puntaje.setOutlineThickness(1.f);
    puntaje.setLetterSpacing(1.6f);

    // Alinear a la derecha
    sf::FloatRect bounds = puntaje.getLocalBounds();
    puntaje.setOrigin({ bounds.position.x + bounds.size.x, bounds.position.y });
    puntaje.setPosition({ x + ancho - 25.f, y + 23.f });


    window.draw(puntaje);
}

void Hud::dibujarTiempo(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
    // Implementación pendiente
}

void Hud::dibujarFase(sf::RenderWindow& window, const DatosHUD& datos, sf::Font& fuente)
{
    // Implementación pendiente
}

void Hud::dibujarBarra(sf::RenderWindow& window, float x, float y, float ancho, float alto, float porcentaje) const
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
    fondo.setFillColor(sf::Color(45, 45, 45));

    sf::RectangleShape barra;
    barra.setPosition({ x,y });
    barra.setSize({ ancho * porcentaje, alto });
    barra.setFillColor(sf::Color(170, 60, 60));

    window.draw(fondo);
    window.draw(barra);
}



