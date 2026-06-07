#include "Phase4DialogueScene.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <set>
#include <sstream>

namespace
{
	constexpr float VELOCIDAD_TEXTO = 48.f;
	constexpr float ANCHO_BASE = 1920.f;
	constexpr float ALTO_BASE = 1080.f;
	constexpr float MARGEN_CAJA_X = 115.f;
	constexpr float ALTO_CAJA_DIALOGO = 214.f;
	constexpr float MARGEN_CAJA_INFERIOR = 35.f;

	const Phase4CharacterLayout LAYOUT_BERNKASTEL = { { 560.f, 1045.f }, 930.f };
	const Phase4CharacterLayout LAYOUT_ANGE = { { 1320.f, 1045.f }, 960.f };
}

Phase4DialogueScene::Phase4DialogueScene()
{
	lineas = {
	{ "Bernkastel", "ha... asi que lograste llegar hasta la cuarta capa.", "ange_vn_enojo", "bernkastel_vn_sonrisa", false, true },
	{ "Ange", "Lo dices como si ya supieras que iba a llegar.", "ange_vn_enojo", "bernkastel_vn_sonrisa", true, false },
	{ "Bernkastel", "Por supuesto. Un tablero solo es interesante cuando la pieza cree que eligio el camino.", "ange_vn_seria", "bernkastel_vn_cruel", false, true },
	{ "Ange", "Ya me canse de que me traten como una pieza.", "ange_vn_desafio", "bernkastel_vn_cruel", true, false },
	{ "Bernkastel", "Que terca. Incluso ahora sigues creyendo que resistirte te hace libre.", "ange_vn_desafio", "bernkastel_vn_fria", false, true },
	{ "Ange", "No. Creo que elegir volver a levantarme si lo hace.", "ange_vn_enojo", "bernkastel_vn_fria", true, false },
	{ "Bernkastel", "Bien. Ese rostro te queda mejor que la desesperacion.", "ange_vn_enojo", "bernkastel_vn_sonrisa", false, true },
	{ "Ange", "Tu no decides lo que significa mi desesperacion.", "ange_vn_desafio", "bernkastel_vn_sonrisa", true, false },
	{ "Bernkastel", "Entonces demuestramelo, Ange.", "ange_vn_desafio", "bernkastel_vn_cruel", false, true },
	{ "Bernkastel", "Muestrame si tu milagro es real... o solo otro hermoso error.", "ange_vn_desafio", "bernkastel_vn_cruel", false, true }
	};
}

bool Phase4DialogueScene::load(const Assets& assets)
{
	assets_manager = &assets;

	try
	{
		assets.get_fuente("texto");
		assets.get_fuente("titulo");

		std::set<std::string> ids_texturas;

		for (const Phase4DialogueLine& linea : lineas)
		{
			ids_texturas.insert(linea.leftSpriteId);
			ids_texturas.insert(linea.rightSpriteId);
		}

		for (const std::string& id : ids_texturas)
		{
			assets.get_texture(id);
		}
	}
	catch (const std::exception& error)
	{
		std::cout << "No se pudo validar Phase4DialogueScene: " << error.what() << "\n";
		assets_manager = nullptr;
		return false;
	}

	reset();
	return true;
}

void Phase4DialogueScene::reset()
{
	linea_actual = 0;
	caracteres_visibles = 0.f;
	tiempo_escena = 0.f;
	terminado = false;
}

void Phase4DialogueScene::handleEvent(const sf::Event& event)
{
	if (terminado)
	{
		return;
	}

	const auto* tecla = event.getIf<sf::Event::KeyPressed>();

	if (tecla == nullptr)
	{
		return;
	}

	if (tecla->code == sf::Keyboard::Key::Escape)
	{
		terminado = true;
		return;
	}

	if (tecla->code == sf::Keyboard::Key::Enter || tecla->code == sf::Keyboard::Key::Space)
	{
		if (linea_completa())
		{
			avanzar_linea();
		}
		else
		{
			revelar_linea();
		}
	}
}

void Phase4DialogueScene::update(float dt)
{
	if (terminado || linea_actual >= lineas.size())
	{
		return;
	}

	tiempo_escena += dt;

	const std::string& texto = lineas[linea_actual].text;

	caracteres_visibles = std::min(
		caracteres_visibles + VELOCIDAD_TEXTO * dt,
		static_cast<float>(texto.size())
	);
}

void Phase4DialogueScene::render(sf::RenderWindow& window)
{
	if (assets_manager == nullptr || lineas.empty())
	{
		return;
	}

	const sf::View vista_anterior = window.getView();
	sf::View vista_vn(sf::FloatRect({ 0.f, 0.f }, { ANCHO_BASE, ALTO_BASE }));
	window.setView(vista_vn);

	const Phase4DialogueLine& linea = lineas[std::min(linea_actual, lineas.size() - 1)];

	sf::RectangleShape velo({ ANCHO_BASE, ALTO_BASE });
	velo.setFillColor(sf::Color(0, 0, 20, 148));
	window.draw(velo);

	
	dibujar_personaje(window, linea.rightSpriteId, linea.rightActive, LAYOUT_BERNKASTEL);
	dibujar_personaje(window, linea.leftSpriteId, linea.leftActive, LAYOUT_ANGE);

	const float caja_x = MARGEN_CAJA_X;
	const float caja_y = ALTO_BASE - ALTO_CAJA_DIALOGO - MARGEN_CAJA_INFERIOR;
	const float caja_ancho = ANCHO_BASE - MARGEN_CAJA_X * 2.f;
	const float caja_alto = ALTO_CAJA_DIALOGO;

	sf::RectangleShape caja({ caja_ancho, caja_alto });
	caja.setPosition({ caja_x, caja_y });
	caja.setFillColor(sf::Color(9, 8, 18, 224));
	caja.setOutlineColor(sf::Color(176, 166, 214, 225));
	caja.setOutlineThickness(2.f);
	window.draw(caja);

	sf::RectangleShape placa_nombre({ 285.f, 58.f });
	placa_nombre.setPosition({ caja_x + 42.f, caja_y - 32.f });
	placa_nombre.setFillColor(
		linea.speaker == "Ange"
		? sf::Color(54, 18, 28, 238)
		: sf::Color(28, 24, 72, 238)
	);
	placa_nombre.setOutlineColor(sf::Color(220, 205, 170, 220));
	placa_nombre.setOutlineThickness(1.5f);
	window.draw(placa_nombre);

	const sf::Font& fuente_titulo = assets_manager->get_fuente("titulo");
	const sf::Font& fuente_texto = assets_manager->get_fuente("texto");

	sf::Text nombre(fuente_titulo);
	nombre.setString(linea.speaker);
	nombre.setCharacterSize(40);
	nombre.setFillColor(sf::Color(245, 238, 220, 255));
	nombre.setPosition({ caja_x + 62.f, caja_y - 28.f });
	window.draw(nombre);

	const unsigned int tam_texto = 34;
	const std::string texto_envuelto = envolver_texto(linea.text, fuente_texto, tam_texto, caja_ancho - 110.f);
	const std::string texto = texto_envuelto_visible(texto_envuelto);

	sf::Text dialogo(fuente_texto);
	dialogo.setString(texto);
	dialogo.setCharacterSize(tam_texto);
	dialogo.setFillColor(sf::Color(238, 234, 224, 255));
	dialogo.setLineSpacing(1.18f);
	dialogo.setPosition({ caja_x + 55.f, caja_y + 62.f });
	window.draw(dialogo);

	if (linea_completa())
	{
		const float pulso = (std::sin(tiempo_escena * 6.f) + 1.f) * 0.5f;

		sf::ConvexShape indicador(3);
		indicador.setPoint(0, { 0.f, 0.f });
		indicador.setPoint(1, { 24.f, 0.f });
		indicador.setPoint(2, { 12.f, 18.f });
		indicador.setFillColor(sf::Color(235, 225, 190, static_cast<std::uint8_t>(150 + pulso * 80)));
		indicador.setPosition({ caja_x + caja_ancho - 70.f, caja_y + caja_alto - 48.f });
		window.draw(indicador);
	}

	window.setView(vista_anterior);
}

bool Phase4DialogueScene::isFinished() const
{
	return terminado;
}

void Phase4DialogueScene::avanzar_linea()
{
	linea_actual++;
	caracteres_visibles = 0.f;

	if (linea_actual >= lineas.size())
	{
		terminado = true;
	}
}

void Phase4DialogueScene::revelar_linea()
{
	if (linea_actual < lineas.size())
	{
		caracteres_visibles = static_cast<float>(lineas[linea_actual].text.size());
	}
}

bool Phase4DialogueScene::linea_completa() const
{
	if (linea_actual >= lineas.size())
	{
		return true;
	}

	return caracteres_visibles >= static_cast<float>(lineas[linea_actual].text.size());
}

std::string Phase4DialogueScene::texto_visible() const
{
	if (linea_actual >= lineas.size())
	{
		return "";
	}

	const std::size_t visibles = std::min(
		static_cast<std::size_t>(caracteres_visibles),
		lineas[linea_actual].text.size()
	);

	return lineas[linea_actual].text.substr(0, visibles);
}

std::string Phase4DialogueScene::texto_envuelto_visible(const std::string& texto_envuelto) const
{
	const std::size_t visibles = texto_visible().size();
	std::size_t caracteres_contados = 0;
	std::string resultado;

	for (char caracter : texto_envuelto)
	{
		if (caracter != '\n')
		{
			if (caracteres_contados >= visibles)
			{
				break;
			}

			caracteres_contados++;
		}

		resultado += caracter;
	}

	return resultado;
}

std::string Phase4DialogueScene::envolver_texto(
	const std::string& texto,
	const sf::Font& fuente,
	unsigned int tamano,
	float ancho_maximo
) const
{
	std::stringstream entrada(texto);
	std::string palabra;
	std::string linea;
	std::string resultado;

	sf::Text medidor(fuente);
	medidor.setCharacterSize(tamano);

	while (entrada >> palabra)
	{
		const std::string prueba = linea.empty() ? palabra : linea + " " + palabra;
		medidor.setString(prueba);

		if (!linea.empty() && medidor.getLocalBounds().size.x > ancho_maximo)
		{
			resultado += linea + "\n";
			linea = palabra;
		}
		else
		{
			linea = prueba;
		}
	}

	resultado += linea;
	return resultado;
}

void Phase4DialogueScene::dibujar_personaje(
	sf::RenderWindow& window,
	const std::string& textura_id,
	bool activo,
	const Phase4CharacterLayout& layout
) const
{
	const sf::Texture& textura = assets_manager->get_texture(textura_id);
	sf::Sprite sprite(textura);

	const sf::Vector2u tam_textura = textura.getSize();

	const float escala = layout.altoBase / static_cast<float>(tam_textura.y);

	sprite.setOrigin({
		static_cast<float>(tam_textura.x) * 0.5f,
		static_cast<float>(tam_textura.y)
		});

	sprite.setScale({ escala, escala });
	sprite.setPosition(layout.posicionBase);

	const float margen_x = 35.f;
	const float margen_top = 20.f;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::Vector2f posicion = sprite.getPosition();

	if (bounds.position.x < margen_x)
	{
		posicion.x += margen_x - bounds.position.x;
	}

	if (bounds.position.x + bounds.size.x > ANCHO_BASE - margen_x)
	{
		posicion.x -= (bounds.position.x + bounds.size.x) - (ANCHO_BASE - margen_x);
	}

	sprite.setPosition(posicion);
	bounds = sprite.getGlobalBounds();

	if (bounds.position.y < margen_top)
	{
		posicion.y += margen_top - bounds.position.y;
	}

	sprite.setPosition(posicion);

	sprite.setColor(
		activo
		? sf::Color::White
		: sf::Color(185, 185, 205, 205)
	);

	window.draw(sprite);
}
