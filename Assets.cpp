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

    auto cargar_textura_vn = [this](const string& nombre, const string& ruta)
        {
            sf::Texture textura;

            if (!textura.loadFromFile(ruta))
            {
                std::cout << "No se pudo cargar " << ruta << "\n";
                return false;
            }

            textura.setSmooth(true);
            textures[nombre] = textura;
            return true;
        };

    if (!cargar_textura_vn("vn_background", "assets/images/vn_background.png") ||
        !cargar_textura_vn("ange_vn_seria", "assets/images/ange_vn_seria.png") ||
        !cargar_textura_vn("ange_vn_enojo", "assets/images/ange_vn_enojo.png") ||
        !cargar_textura_vn("ange_vn_desafio", "assets/images/ange_vn_desafio.png") ||
        !cargar_textura_vn("bernkastel_vn_fria", "assets/images/bernkastel_vn_fria.png") ||
        !cargar_textura_vn("bernkastel_vn_sonrisa", "assets/images/bernkastel_vn_sonrisa.png") ||
        !cargar_textura_vn("bernkastel_vn_cruel", "assets/images/bernkastel_vn_cruel.png"))
    {
        return false;
    }
    
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

    if (!musica_fase_1.openFromFile("assets/Music/fase_1.ogg"))
    {
        std::cout << "No se pudo cargar assets/Music/fase_1.ogg\n";
        return false;
    }
    musica_fase_1.setLooping(true);
    musica_fase_1.setVolume(40.f);
  


    if (!musica_fase_4.openFromFile("assets/Music/fase_4.ogg"))
    {
        std::cout << "No se pudo cargar assets/Music/fase_4.ogg\n";
        return false;
    }

    musica_fase_4.setLooping(true);
    musica_fase_4.setVolume(68.f);
    

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

