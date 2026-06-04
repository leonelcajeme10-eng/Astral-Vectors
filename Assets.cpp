#include "Assets.h"
#include <SFML/Graphics.hpp>
#include <iostream>




bool Assets::cargar_texturas()
{
    if (!barra_lateral.loadFromFile("assets/images/panel_lateral.png"))
    {
        std::cout << "No se pudo cargar assets/images/panel_lateral.png\n";
        return false;
    }

    if (!this->textura_corazones.loadFromFile("assets/images/corazon.png"))
    {
        std::cout << "No se pudo cargar assets/images/corazon.png\n";
        return false;
    }

    if (!this->textura_barra_negra.loadFromFile("assets/images/barra_negra.png"))
    {
        std::cout << "No se pudo cargar assets/images/barra_negra.png\n";
        return false;
    }

    textures["barra_lateral"] = barra_lateral;
    textures["corazon"] = textura_corazones;
    textures["barra_negra"] = textura_barra_negra;
    
    return true;
}

const sf::Texture& Assets::get_texture(const string& nombre) const
{
	return this->textures.at(nombre);
}

const sf::Font& Assets::get_fuente(const string& nombre) const
{
	return fonts.at(nombre);
}

bool Assets::cargar()
{
    if (!fontHUD.openFromFile("assets/fonts/SpecialElite-Regular.ttf"))
    {
        std::cout << "No se pudo cargar SpecialElite-Regular.ttf\n";
        return false;
    }

    if (!fontTitulo.openFromFile("assets/fonts/CormorantGaramond-VariableFont_wght.ttf"))
    {
        std::cout << "No se pudo cargar CormorantGaramond-VariableFont_wght.ttf\n";
        return false;
    }

    fonts["texto"] = fontHUD;
    fonts["titulo"] = fontTitulo;

    return true;
}

