#pragma once

#include "Assets.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct Phase4CharacterLayout
{
	sf::Vector2f posicionBase;
	float altoBase;
};

struct Phase4DialogueLine
{
	std::string speaker;
	std::string text;
	std::string leftSpriteId;
	std::string rightSpriteId;
	bool leftActive;
	bool rightActive;
};

class Phase4DialogueScene
{
private:
	const Assets* assets_manager = nullptr;
	std::vector<Phase4DialogueLine> lineas;
	std::size_t linea_actual = 0;
	float caracteres_visibles = 0.f;
	float tiempo_escena = 0.f;
	bool terminado = false;

	void avanzar_linea();
	void revelar_linea();
	bool linea_completa() const;
	std::string texto_visible() const;
	std::string texto_envuelto_visible(const std::string& texto_envuelto) const;
	std::string envolver_texto(const std::string& texto, const sf::Font& fuente, unsigned int tamano, float ancho_maximo) const;
	void dibujar_personaje(sf::RenderWindow& window, const std::string& textura_id, bool activo, const Phase4CharacterLayout& layout) const;

public:
	Phase4DialogueScene();
	bool load(const Assets& assets);
	void reset();
	void handleEvent(const sf::Event& event);
	void update(float dt);
	void render(sf::RenderWindow& window);
	bool isFinished() const;
};
