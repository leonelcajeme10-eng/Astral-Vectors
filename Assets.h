#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

using namespace std;

class Assets
{
private:
	map<string , sf::Texture > textures;
	map<string, sf::Font> fonts;


public:
	Assets() = default;

	void cargar_texturas(const string& nombre, const string& ruta_archivo);
	void cargar_fuentes(const string& nombre, const string& ruta_archivo);

	sf::Texture& get_texture(const string& nombre);
	sf::Font& get_fuente(const string& nombre);

};

