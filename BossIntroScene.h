#pragma once

#include "Assets.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct CharacterLayout
{
	sf::Vector2f posicionBase;
	float altoBase;
};

struct DialogueLine
{
	std::string speaker;
	std::string text;
	std::string leftSpriteId;
	std::string rightSpriteId;
	bool leftActive;
	bool rightActive;
};

class BossIntroScene
{
private:
	const Assets* assets_manager = nullptr;
	std::vector<DialogueLine> lineas;
	std::size_t linea_actual = 0;
	float caracteres_visibles = 0.f;
	float tiempo_escena = 0.f;
	bool terminado = false;

	void avanzar_linea();
	void revelar_linea();
	bool linea_completa() const;
	std::string texto_visible() const;
	std::string envolver_texto(const std::string& texto, const sf::Font& fuente, unsigned int tamano, float ancho_maximo) const;
	std::string texto_envuelto_visible(const std::string& texto_envuelto) const;
	void dibujar_personaje(sf::RenderWindow& window, const std::string& textura_id, bool activo, const CharacterLayout& layout) const;

public:
	BossIntroScene();
	bool load(const Assets& assets);
	void reset();
	void handleEvent(const sf::Event& event);
	void update(float dt);
	void render(sf::RenderWindow& window);
	bool isFinished() const;
};
