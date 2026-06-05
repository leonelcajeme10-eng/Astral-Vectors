#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

class Assets
{
protected:
	map<string , sf::Texture > textures;
	map<string, sf::Font> fonts;
	sf::Font fontHUD;
	sf::Font fontTitulo;
	sf::Texture barra_lateral;
	sf::Font fontJP;
	sf::Texture textura_corazones;
	sf::Texture textura_barra_negra;
	sf::Texture textura_menu;

public:
	sf::Music musica_menu;
	Assets() = default;

	bool cargar_texturas(); 
	bool cargar_musica();

	const sf::Texture& get_texture(const string& nombre) const;
	const sf::Font& get_fuente(const string& nombre) const;

	bool cargar();
   

};

