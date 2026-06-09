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
	sf::Texture textura_nixie_tube;
	sf::Texture textura_fondo;
	sf::Texture textura_bala_roja;
	sf::Texture textura_bala_morada;
	

public:
	sf::Music musica_menu;
	sf::Music musica_fase_1;
	sf::Music musica_fase_4;
	std::map<std::string, sf::SoundBuffer> sound_buffers;
	std::vector<sf::Sound> sonidos_activos;
	Assets() = default;

	bool cargar_texturas(); 
	bool cargar_musica();
	bool cargar_sonido();
	void reproducir_sfx(const string& nombre);

	const sf::Texture& get_texture(const string& nombre) const;
	const sf::Font& get_fuente(const string& nombre) const;

	bool cargar();
   

};

