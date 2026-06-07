#include "Pausa.h"
#include "Game.h"
#include <string>

namespace
{
	void centrarTexto(sf::Text& texto, float x, float y, float ancho, float alto)
	{
		sf::FloatRect bounds = texto.getLocalBounds();
		texto.setOrigin({
			bounds.position.x + bounds.size.x / 2.f,
			bounds.position.y + bounds.size.y / 2.f
			});
		texto.setPosition({ x + ancho / 2.f, y + alto / 2.f });
	}

	void dibujarTextoCentrado(sf::RenderTarget& window, const sf::Font& fuente, const std::string& textoValor,
		float x, float y, float ancho, float alto, unsigned int tamano, sf::Color color)
	{
		sf::Text texto(fuente);
		texto.setString(textoValor);
		texto.setCharacterSize(tamano);
		texto.setFillColor(color);
		texto.setOutlineColor(sf::Color(0, 0, 0, 190));
		texto.setOutlineThickness(1.2f);
		centrarTexto(texto, x, y, ancho, alto);
		window.draw(texto);
	}

	void dibujarBarra(sf::RenderTarget& window, const Assets& assets, float x, float y, float ancho, float alto, sf::Color color)
	{
		const sf::Texture& textura = assets.get_texture("barra_negra");
		sf::Sprite barra(textura);
		const sf::Vector2u tam = textura.getSize();

		barra.setPosition({ x, y });
		barra.setScale({
			ancho / static_cast<float>(tam.x),
			alto / static_cast<float>(tam.y)
			});
		barra.setColor(color);
		window.draw(barra);
	}
}

void Pausa::manejar_evento(const sf::Event& evento, GameState& estado)
{
	const auto* tecla = evento.getIf<sf::Event::KeyPressed>();

	if (tecla == nullptr)
	{
		return;
	}

	if (tecla->code == sf::Keyboard::Key::Up || tecla->code == sf::Keyboard::Key::W)
	{
		opcion--;

		if (opcion < 0)
		{
			opcion = static_cast<int>(opciones.size()) - 1;
		}
	}
	else if (tecla->code == sf::Keyboard::Key::Down || tecla->code == sf::Keyboard::Key::S)
	{
		opcion++;

		if (opcion >= static_cast<int>(opciones.size()))
		{
			opcion = 0;
		}
	}
	else if (tecla->code == sf::Keyboard::Key::Enter)
	{
		if (opcion == 0)
		{
			estado = GameState::Playing;
		}
		else if (opcion == 1)
		{
			estado = GameState::Menu_estado;
			opcion = 0;
		}
	}
	else if (tecla->code == sf::Keyboard::Key::P || tecla->code == sf::Keyboard::Key::Escape)
	{
		estado = GameState::Playing;
		opcion = 0;
	}
}

void Pausa::dibujar(sf::RenderWindow& window, const Assets& assets, const sf::Texture& escena_blur)
{
	const sf::Vector2u tamVentana = window.getSize();

	sf::Sprite fondoBlur(escena_blur);
	const sf::Vector2u tamBlur = escena_blur.getSize();
	fondoBlur.setScale({
		static_cast<float>(tamVentana.x) / static_cast<float>(tamBlur.x),
		static_cast<float>(tamVentana.y) / static_cast<float>(tamBlur.y)
		});
	fondoBlur.setColor(sf::Color(210, 210, 210, 255));
	window.draw(fondoBlur);

	sf::RectangleShape velo;
	velo.setSize({ static_cast<float>(tamVentana.x), static_cast<float>(tamVentana.y) });
	velo.setFillColor(sf::Color(2, 3, 5, 122));
	window.draw(velo);

	const float panelX = 492.f;
	const float panelY = 260.f;
	const float panelAncho = 924.f;
	const float panelAlto = 505.f;

	dibujarBarra(window, assets, panelX - 12.f, panelY + 16.f, panelAncho + 24.f, panelAlto, sf::Color(0, 0, 0, 145));
	dibujarBarra(window, assets, panelX, panelY, panelAncho, panelAlto, sf::Color(255, 255, 255, 235));

	sf::RectangleShape borde;
	borde.setPosition({ panelX + 42.f, panelY + 44.f });
	borde.setSize({ panelAncho - 84.f, panelAlto - 88.f });
	borde.setFillColor(sf::Color::Transparent);
	borde.setOutlineColor(sf::Color(232, 188, 118, 96));
	borde.setOutlineThickness(2.f);
	window.draw(borde);

	dibujarTextoCentrado(window, assets.get_fuente("titulo"), "PAUSA", panelX, panelY + 75.f, panelAncho, 96.f, 86, sf::Color(245, 239, 218, 255));
	dibujarTextoCentrado(window, assets.get_fuente("texto"), "SIMULACION SUSPENDIDA", panelX, panelY + 170.f, panelAncho, 46.f, 24, sf::Color(230, 214, 176, 210));

	sf::RectangleShape linea;
	linea.setSize({ 238.f, 1.5f });
	linea.setFillColor(sf::Color(225, 178, 102, 120));
	linea.setPosition({ panelX + 188.f, panelY + 238.f });
	window.draw(linea);
	linea.setPosition({ panelX + panelAncho - 426.f, panelY + 238.f });
	window.draw(linea);

	sf::CircleShape sello(7.f, 4);
	sello.setOrigin({ 7.f, 7.f });
	sello.setPosition({ panelX + panelAncho / 2.f, panelY + 238.f });
	sello.setRotation(sf::degrees(45.f));
	sello.setFillColor(sf::Color(244, 215, 146, 195));
	window.draw(sello);

	const float botonX = panelX + 220.f;
	const float botonAncho = 484.f;
	const float botonAlto = 72.f;
	const float primerBotonY = panelY + 282.f;
	const float separacionBoton = 88.f;

	for (int i = 0; i < static_cast<int>(opciones.size()); i++)
	{
		const float botonY = primerBotonY + separacionBoton * i;
		const bool seleccionado = i == opcion;

		dibujarBarra(window, assets, botonX, botonY, botonAncho, botonAlto,
			seleccionado ? sf::Color(255, 255, 255, 238) : sf::Color(196, 196, 196, 168));

		if (seleccionado)
		{
			sf::RectangleShape marca;
			marca.setPosition({ botonX + 28.f, botonY + botonAlto / 2.f - 5.f });
			marca.setSize({ 18.f, 10.f });
			marca.setFillColor(sf::Color(244, 215, 146, 220));
			window.draw(marca);
		}

		dibujarTextoCentrado(window, assets.get_fuente(i == 0 ? "titulo" : "texto"), opciones[i],
			botonX, botonY + 4.f, botonAncho, botonAlto - 10.f,
			i == 0 ? 34 : 24,
			seleccionado ? sf::Color(245, 240, 224, 255) : sf::Color(224, 205, 168, 205));
	}

	dibujarTextoCentrado(window, assets.get_fuente("texto"), "W/S  O  FLECHAS  +  ENTER", panelX, panelY + 448.f, panelAncho, 34.f, 17, sf::Color(224, 205, 168, 155));

	const sf::Texture& tuboTexture = assets.get_texture("nixie_tube");
	for (int i = 0; i < 2; i++)
	{
		sf::Sprite tubo(tuboTexture);
		tubo.setScale({ 0.34f, 0.34f });
		tubo.setColor(sf::Color(255, 205, 124, 120));
		tubo.setPosition({ panelX + 98.f + i * 676.f, panelY + 310.f });
		window.draw(tubo);
	}

	const sf::Texture& corazonTexture = assets.get_texture("corazon");
	for (int i = 0; i < 3; i++)
	{
		sf::Sprite corazon(corazonTexture);
		corazon.setScale({ 0.115f, 0.115f });
		corazon.setColor(sf::Color(255, 90, 80, 82));
		corazon.setPosition({ panelX + 384.f + i * 72.f, panelY + 472.f });
		window.draw(corazon);
	}
}
