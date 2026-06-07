#include "menu.h"
#include "Assets.h"
#include "Game.h"

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
}

bool menu::manejar_evento(const sf::Event& evento, GameState& estado)
{
	const auto* tecla = evento.getIf<sf::Event::KeyPressed>();

	if (tecla == nullptr)
	{
		return false;
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
			estado = GameState::BossIntro;
		}
		else if (opcion == 1)
		{
			return true;
		}
	}
	else if (tecla->code == sf::Keyboard::Key::Escape)
	{
		return true;
	}

	return false;
}

void menu::dibujar(sf::RenderWindow& window, Assets& assets)
{
	sf::Sprite fondo(assets.get_texture("menu"));
	sf::Vector2u tamFondo = assets.get_texture("menu").getSize();
	sf::Vector2u tamVentana = window.getSize();

	fondo.setScale({
		static_cast<float>(tamVentana.x) / static_cast<float>(tamFondo.x),
		static_cast<float>(tamVentana.y) / static_cast<float>(tamFondo.y)
		});

	window.draw(fondo);

	const sf::Texture& texturaBarra = assets.get_texture("barra_negra");
	sf::Vector2u tamBarra = texturaBarra.getSize();

	const float anchoBoton = 560.f;
	const float altoBoton = 105.f;
	const float xBoton = 165.f;
	const float yInicial = 520.f;
	const float separacion = 132.f;

	for (int i = 0; i < static_cast<int>(opciones.size()); i++)
	{
		const float yBoton = yInicial + separacion * i;

		sf::Sprite barra(texturaBarra);
		barra.setPosition({ xBoton, yBoton });
		barra.setScale({
			anchoBoton / static_cast<float>(tamBarra.x),
			altoBoton / static_cast<float>(tamBarra.y)
			});

		if (i == opcion)
		{
			barra.setColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			barra.setColor(sf::Color(210, 210, 210, 210));
		}

		window.draw(barra);

		sf::Text texto(assets.get_fuente("titulo"));
		texto.setString(opciones[i]);
		texto.setCharacterSize(42);
		texto.setFillColor(i == opcion ? sf::Color(245, 240, 225, 255) : sf::Color(190, 185, 170, 230));
		texto.setOutlineColor(sf::Color(0, 0, 0, 190));
		texto.setOutlineThickness(1.5f);
		texto.setLetterSpacing(1.4f);

		centrarTexto(texto, xBoton, yBoton, anchoBoton, altoBoton);
		window.draw(texto);
	}

}
