#include "BossIntroScene.h"
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
	
	const CharacterLayout LAYOUT_BERNKASTEL = { { 560.f, 1045.f }, 930.f };
	const CharacterLayout LAYOUT_ANGE = { { 1320.f, 1045.f }, 960.f };

	void dibujar_cubriendo(sf::RenderWindow& window, const sf::Texture& textura)
	{
		sf::Sprite sprite(textura);
		const sf::Vector2u tam_textura = textura.getSize();

		const float escala_x = ANCHO_BASE / static_cast<float>(tam_textura.x);
		const float escala_y = ALTO_BASE / static_cast<float>(tam_textura.y);
		const float escala = std::max(escala_x, escala_y);

		sprite.setScale({ escala, escala });
		sprite.setPosition({
			(ANCHO_BASE - static_cast<float>(tam_textura.x) * escala) * 0.5f,
			(ALTO_BASE - static_cast<float>(tam_textura.y) * escala) * 0.5f
			});

		window.draw(sprite);
	}
}

BossIntroScene::BossIntroScene()
{
	lineas = {
		{ "Ange", "Asi que este es el tablero donde querias encerrarme.", "ange_vn_seria", "bernkastel_vn_fria", true, false },
		{ "Bernkastel", "Encerrarte? No. Solo deje abierta la puerta que ibas a escoger.", "ange_vn_seria", "bernkastel_vn_sonrisa", false, true },
		{ "Ange", "Ya no voy a moverme como una pieza muda.", "ange_vn_enojo", "bernkastel_vn_sonrisa", true, false },
		{ "Bernkastel", "Que ternura. Una pieza que confunde voz con libertad.", "ange_vn_enojo", "bernkastel_vn_cruel", false, true },
		{ "Ange", "Entonces mira bien. Todavia puedo romper una jugada.", "ange_vn_desafio", "bernkastel_vn_cruel", true, false },
		{ "Bernkastel", "Romper? Solo estas llegando al final que ya habia leido.", "ange_vn_desafio", "bernkastel_vn_sonrisa", false, true },
		{ "Ange", "No necesito ganar tu historia. Solo necesito negarla.", "ange_vn_enojo", "bernkastel_vn_fria", true, false },
		{ "Bernkastel", "Bien, Ange. Resiste. Los milagros se ven mejor justo antes de romperse.", "ange_vn_enojo", "bernkastel_vn_cruel", false, true }
	};
}

bool BossIntroScene::load(const Assets& assets)
{
	assets_manager = &assets;

	try
	{
		assets.get_fuente("texto");
		assets.get_fuente("titulo");
		assets.get_texture("vn_background");

		std::set<std::string> ids_texturas;

		for (const DialogueLine& linea : lineas)
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
		std::cout << "No se pudo validar BossIntroScene: " << error.what() << "\n";
		assets_manager = nullptr;
		return false;
	}

	reset();
	return true;
}

void BossIntroScene::reset()
{
	linea_actual = 0;
	caracteres_visibles = 0.f;
	tiempo_escena = 0.f;
	terminado = false;
}

void BossIntroScene::handleEvent(const sf::Event& event)
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

void BossIntroScene::update(float dt)
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

void BossIntroScene::render(sf::RenderWindow& window)
{
	if (assets_manager == nullptr || lineas.empty())
	{
		return;
	}

	const sf::View vista_anterior = window.getView();


	sf::View vista_vn(sf::FloatRect({ 0.f, 0.f }, { ANCHO_BASE, ALTO_BASE }));
	window.setView(vista_vn);

	const DialogueLine& linea = lineas[std::min(linea_actual, lineas.size() - 1)];

	dibujar_cubriendo(window, assets_manager->get_texture("vn_background"));

	sf::RectangleShape velo({ ANCHO_BASE, ALTO_BASE });
	velo.setFillColor(sf::Color(0, 0, 18, 34));
	window.draw(velo);

	
	dibujar_personaje(window, linea.rightSpriteId, linea.rightActive, LAYOUT_BERNKASTEL);
	dibujar_personaje(window, linea.leftSpriteId, linea.leftActive, LAYOUT_ANGE);

	const float caja_x = MARGEN_CAJA_X;
	const float caja_y = ALTO_BASE - ALTO_CAJA_DIALOGO - MARGEN_CAJA_INFERIOR;
	const float caja_ancho = ANCHO_BASE - MARGEN_CAJA_X * 2.f;
	const float caja_alto = ALTO_CAJA_DIALOGO;

	sf::RectangleShape caja({ caja_ancho, caja_alto });
	caja.setPosition({ caja_x, caja_y });
	caja.setFillColor(sf::Color(9, 8, 18, 214));
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

	const std::string texto_envuelto = envolver_texto(
		linea.text,
		fuente_texto,
		tam_texto,
		caja_ancho - 110.f
	);

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
		indicador.setFillColor(sf::Color(
			235,
			225,
			190,
			static_cast<std::uint8_t>(150 + pulso * 80)
		));
		indicador.setPosition({ caja_x + caja_ancho - 70.f, caja_y + caja_alto - 48.f });
		window.draw(indicador);
	}

	const float fade_alpha = std::max(0.f, 255.f - tiempo_escena * 540.f);

	if (fade_alpha > 0.f)
	{
		sf::RectangleShape fade({ ANCHO_BASE, ALTO_BASE });
		fade.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(fade_alpha)));
		window.draw(fade);
	}

	window.setView(vista_anterior);
}

bool BossIntroScene::isFinished() const
{
	return terminado;
}

void BossIntroScene::avanzar_linea()
{
	linea_actual++;
	caracteres_visibles = 0.f;

	if (linea_actual >= lineas.size())
	{
		terminado = true;
	}
}

void BossIntroScene::revelar_linea()
{
	if (linea_actual < lineas.size())
	{
		caracteres_visibles = static_cast<float>(lineas[linea_actual].text.size());
	}
}

bool BossIntroScene::linea_completa() const
{
	if (linea_actual >= lineas.size())
	{
		return true;
	}

	return caracteres_visibles >= static_cast<float>(lineas[linea_actual].text.size());
}

std::string BossIntroScene::texto_visible() const
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

std::string BossIntroScene::texto_envuelto_visible(const std::string& texto_envuelto) const
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

std::string BossIntroScene::envolver_texto(
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

void BossIntroScene::dibujar_personaje(
	sf::RenderWindow& window,
	const std::string& textura_id,
	bool activo,
	const CharacterLayout& layout
) const
{
	const sf::Texture& textura = assets_manager->get_texture(textura_id);
	sf::Sprite sprite(textura);

	const sf::Vector2u tam_textura = textura.getSize();

	const float alto_objetivo = layout.altoBase;
	const float escala = alto_objetivo / static_cast<float>(tam_textura.y);

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