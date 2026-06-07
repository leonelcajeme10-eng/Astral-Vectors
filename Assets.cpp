#include "Assets.h"
#include <SFML/Graphics.hpp>
#include <iostream>




bool Assets::cargar_texturas()
{
    if (!this->textura_fondo.loadFromFile("assets/images/fondo.png"))
    {
        std::cout << "No se pudo cargar assets/images/fondo.png\n";
        return false;
    }
    this->textura_fondo.setSmooth(true);
    textura_fondo.setRepeated(true);

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
    this->textura_barra_negra.setSmooth(true);

    if (!this->textura_menu.loadFromFile("assets/images/menu_final.png"))
    {
        std::cout << "No se pudo cargar assets/images/menu_final.png\n";
        return false;
    }
    this->textura_menu.setSmooth(true);

    if (!this->textura_nixie_tube.loadFromFile("assets/images/nixie_tube.png"))
    {
        std::cout << "No se pudo cargar assets/images/nixie_tube.png\n";
        return false;
    }
    this->textura_nixie_tube.setSmooth(true);

   



    textures["barra_lateral"] = barra_lateral;
    textures["corazon"] = textura_corazones;
    textures["barra_negra"] = textura_barra_negra;
    textures["menu"] = textura_menu;
    textures["nixie_tube"] = textura_nixie_tube;
    textures["fondo"] = textura_fondo;
    
    return true;
}

bool Assets::cargar_musica()
{
    if (!musica_menu.openFromFile("assets/Music/cancion_menu_vorbis.ogg"))
    {
        std::cout << "No se pudo cargar assets/Music/cancion_menu_vorbis.ogg\n";
        return false;
    }

    musica_menu.setLooping(true);
    musica_menu.setVolume(40.f);
    musica_menu.play();

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

