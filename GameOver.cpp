#include "GameOver.h"
#include "Assets.h"
#include "Game.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <sstream>

bool GameOver::manejar_eventos(GameState& estado, const sf::Event& evento)
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
			estado = GameState::Menu_estado;
			opcion = 0;
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

void GameOver::dibujar(sf::RenderWindow& window, const Assets& assets, const World& world)
{
	sf::View vistaAnterior = window.getView();

	const float ventanaAncho = 1920.f;
	const float ventanaAlto = 1080.f;

	sf::View vistaGameOver;
	vistaGameOver.setSize({ ventanaAncho, ventanaAlto });
	vistaGameOver.setCenter({ ventanaAncho / 2.f, ventanaAlto / 2.f });

	window.setView(vistaGameOver);

	const bool victoria = world.getVidaBoss() <= 0;
	const int puntuacion = world.getPuntuacion();
	const float tiempo = world.get_tiempo();

	const sf::Texture& texturaFondo = assets.get_texture("fondo");
	const sf::Vector2u tamFondo = texturaFondo.getSize();

	sf::Sprite fondo(texturaFondo);
	fondo.setScale({
		ventanaAncho / static_cast<float>(tamFondo.x),
		ventanaAlto / static_cast<float>(tamFondo.y)
		});
	fondo.setColor(sf::Color(118, 118, 118, 255));
	window.draw(fondo);

	sf::RectangleShape velo;
	velo.setSize({ ventanaAncho, ventanaAlto });
	velo.setFillColor(sf::Color(2, 3, 5, 158));
	window.draw(velo);

	sf::RectangleShape franja;
	franja.setPosition({ 0.f, ventanaAlto * 0.18f });
	franja.setSize({ ventanaAncho, 2.f });
	franja.setFillColor(victoria ? sf::Color(170, 224, 188, 52) : sf::Color(232, 188, 118, 48));
	window.draw(franja);

	franja.setPosition({ 0.f, ventanaAlto * 0.82f });
	window.draw(franja);

	const float panelAncho = 980.f;
	const float panelAlto = 600.f;

	const float panelX = ventanaAncho / 2.f - panelAncho / 2.f;
	const float panelY = ventanaAlto / 2.f - panelAlto / 2.f;

	sf::RectangleShape sombra;
	sombra.setPosition({ panelX - 18.f, panelY + 20.f });
	sombra.setSize({ panelAncho + 36.f, panelAlto });
	sombra.setFillColor(sf::Color(0, 0, 0, 118));
	window.draw(sombra);

	sf::RectangleShape panel;
	panel.setPosition({ panelX, panelY });
	panel.setSize({ panelAncho, panelAlto });
	panel.setFillColor(sf::Color(8, 10, 12, 218));
	panel.setOutlineColor(victoria ? sf::Color(170, 224, 188, 128) : sf::Color(232, 188, 118, 128));
	panel.setOutlineThickness(2.f);
	window.draw(panel);

	sf::RectangleShape bordeInterior;
	bordeInterior.setPosition({ panelX + 42.f, panelY + 42.f });
	bordeInterior.setSize({ panelAncho - 84.f, panelAlto - 84.f });
	bordeInterior.setFillColor(sf::Color::Transparent);
	bordeInterior.setOutlineColor(victoria ? sf::Color(170, 224, 188, 52) : sf::Color(232, 188, 118, 58));
	bordeInterior.setOutlineThickness(1.4f);
	window.draw(bordeInterior);

	sf::RectangleShape borde;
	borde.setPosition({ panelX + 46.f, panelY + 46.f });
	borde.setSize({ panelAncho - 92.f, panelAlto - 92.f });
	borde.setFillColor(sf::Color::Transparent);
	borde.setOutlineColor(victoria ? sf::Color(170, 224, 188, 110) : sf::Color(232, 188, 118, 110));
	borde.setOutlineThickness(2.f);
	window.draw(borde);

	const float centroX = panelX + panelAncho / 2.f;
	const float centroY = panelY + 300.f;

	const sf::Color colorPrincipal = victoria ? sf::Color(190, 230, 194, 92) : sf::Color(225, 95, 88, 76);
	const sf::Color colorSecundario = victoria ? sf::Color(244, 215, 146, 120) : sf::Color(244, 215, 146, 70);

	sf::CircleShape anillo(196.f, 128);
	anillo.setOrigin({ 196.f, 196.f });
	anillo.setPosition({ centroX, centroY });
	anillo.setFillColor(sf::Color::Transparent);
	anillo.setOutlineColor(colorPrincipal);
	anillo.setOutlineThickness(2.f);
	window.draw(anillo);

	sf::CircleShape anilloInterior(138.f, 96);
	anilloInterior.setOrigin({ 138.f, 138.f });
	anilloInterior.setPosition({ centroX, centroY });
	anilloInterior.setFillColor(sf::Color::Transparent);
	anilloInterior.setOutlineColor(colorSecundario);
	anilloInterior.setOutlineThickness(1.5f);
	window.draw(anilloInterior);

	for (int i = 0; i < 16; i++)
	{
		const float angulo = (static_cast<float>(i) / 16.f) * 6.2831853f;
		const float radioOrbita = victoria ? 218.f : 184.f;

		const float x = centroX + std::cos(angulo) * radioOrbita;
		const float y = centroY + std::sin(angulo) * radioOrbita;

		sf::CircleShape bala(victoria ? 7.f : 9.f, victoria ? 6 : 4);
		bala.setOrigin({ bala.getRadius(), bala.getRadius() });
		bala.setPosition({ x, y });
		bala.setRotation(sf::radians(angulo));
		bala.setFillColor(i % 2 == 0 ? colorSecundario : colorPrincipal);

		window.draw(bala);
	}

	sf::RectangleShape eje;
	eje.setSize({ 360.f, 1.4f });
	eje.setOrigin({ 180.f, 0.7f });
	eje.setPosition({ centroX, centroY });
	eje.setFillColor(colorSecundario);

	for (int i = 0; i < 4; i++)
	{
		eje.setRotation(sf::degrees(45.f * i));
		window.draw(eje);
	}

	const std::string titulo = victoria ? "VICTORIA" : "GAME OVER";
	const std::string subtitulo = victoria ? "EL VECTOR FINAL FUE RESTAURADO" : "LA SIMULACION COLAPSO";
	const sf::Color colorTitulo = victoria ? sf::Color(218, 255, 226, 255) : sf::Color(255, 225, 202, 255);

	sf::Text textoTitulo(assets.get_fuente("titulo"));
	textoTitulo.setString(titulo);
	textoTitulo.setCharacterSize(84);
	textoTitulo.setFillColor(colorTitulo);
	textoTitulo.setOutlineColor(sf::Color(0, 0, 0, 205));
	textoTitulo.setOutlineThickness(1.4f);

	sf::FloatRect boundsTitulo = textoTitulo.getLocalBounds();
	textoTitulo.setOrigin({
		boundsTitulo.position.x + boundsTitulo.size.x / 2.f,
		boundsTitulo.position.y + boundsTitulo.size.y / 2.f
		});
	textoTitulo.setPosition({
		panelX + panelAncho / 2.f,
		panelY + 72.f + 104.f / 2.f
		});
	window.draw(textoTitulo);

	sf::Text textoSubtitulo(assets.get_fuente("texto"));
	textoSubtitulo.setString(subtitulo);
	textoSubtitulo.setCharacterSize(24);
	textoSubtitulo.setFillColor(sf::Color(230, 214, 176, 218));
	textoSubtitulo.setOutlineColor(sf::Color(0, 0, 0, 205));
	textoSubtitulo.setOutlineThickness(1.4f);

	sf::FloatRect boundsSubtitulo = textoSubtitulo.getLocalBounds();
	textoSubtitulo.setOrigin({
		boundsSubtitulo.position.x + boundsSubtitulo.size.x / 2.f,
		boundsSubtitulo.position.y + boundsSubtitulo.size.y / 2.f
		});
	textoSubtitulo.setPosition({
		panelX + panelAncho / 2.f,
		panelY + 170.f + 44.f / 2.f
		});
	window.draw(textoSubtitulo);

	sf::RectangleShape linea;
	linea.setSize({ 258.f, 1.5f });
	linea.setFillColor(sf::Color(225, 178, 102, 132));

	linea.setPosition({ panelX + 178.f, panelY + 242.f });
	window.draw(linea);

	linea.setPosition({ panelX + panelAncho - 436.f, panelY + 242.f });
	window.draw(linea);

	sf::CircleShape sello(8.f, 4);
	sello.setOrigin({ 8.f, 8.f });
	sello.setPosition({ panelX + panelAncho / 2.f, panelY + 242.f });
	sello.setRotation(sf::degrees(45.f));
	sello.setFillColor(sf::Color(244, 215, 146, 205));
	window.draw(sello);

	std::ostringstream puntuacionTexto;
	puntuacionTexto << "PUNTUACION  " << puntuacion;

	sf::Text textoPuntuacion(assets.get_fuente("texto"));
	textoPuntuacion.setString(puntuacionTexto.str());
	textoPuntuacion.setCharacterSize(24);
	textoPuntuacion.setFillColor(sf::Color(245, 240, 224, 225));
	textoPuntuacion.setOutlineColor(sf::Color(0, 0, 0, 205));
	textoPuntuacion.setOutlineThickness(1.4f);

	sf::FloatRect boundsPuntuacion = textoPuntuacion.getLocalBounds();
	textoPuntuacion.setOrigin({
		boundsPuntuacion.position.x + boundsPuntuacion.size.x / 2.f,
		boundsPuntuacion.position.y + boundsPuntuacion.size.y / 2.f
		});
	textoPuntuacion.setPosition({
		panelX + panelAncho / 2.f,
		panelY + 282.f + 36.f / 2.f
		});
	window.draw(textoPuntuacion);

	const int tiempoTotal = static_cast<int>(tiempo);
	const int minutos = tiempoTotal / 60;
	const int segundos = tiempoTotal % 60;

	std::ostringstream tiempoTexto;
	tiempoTexto << "TIEMPO  "
		<< std::setfill('0') << std::setw(2) << minutos
		<< ":"
		<< std::setw(2) << segundos;

	sf::Text textoTiempo(assets.get_fuente("texto"));
	textoTiempo.setString(tiempoTexto.str());
	textoTiempo.setCharacterSize(24);
	textoTiempo.setFillColor(sf::Color(245, 240, 224, 205));
	textoTiempo.setOutlineColor(sf::Color(0, 0, 0, 205));
	textoTiempo.setOutlineThickness(1.4f);

	sf::FloatRect boundsTiempo = textoTiempo.getLocalBounds();
	textoTiempo.setOrigin({
		boundsTiempo.position.x + boundsTiempo.size.x / 2.f,
		boundsTiempo.position.y + boundsTiempo.size.y / 2.f
		});
	textoTiempo.setPosition({
		panelX + panelAncho / 2.f,
		panelY + 326.f + 36.f / 2.f
		});
	window.draw(textoTiempo);

	const float botonAncho = 524.f;
	const float botonAlto = 70.f;

	const float botonX = panelX + panelAncho / 2.f - botonAncho / 2.f;
	const float primerBotonY = panelY + 392.f;
	const float separacionBoton = 84.f;

	const sf::Texture& texturaBarra = assets.get_texture("barra_negra");
	const sf::Vector2u tamBarra = texturaBarra.getSize();

	for (int i = 0; i < static_cast<int>(opciones.size()); i++)
	{
		const float botonY = primerBotonY + separacionBoton * static_cast<float>(i);
		const bool seleccionado = i == opcion;

		sf::Sprite barra(texturaBarra);
		barra.setPosition({ botonX, botonY });
		barra.setScale({
			botonAncho / static_cast<float>(tamBarra.x),
			botonAlto / static_cast<float>(tamBarra.y)
			});
		barra.setColor(seleccionado ? sf::Color(255, 255, 255, 238) : sf::Color(196, 196, 196, 162));
		window.draw(barra);

		if (seleccionado)
		{
			sf::RectangleShape marca;
			marca.setPosition({ botonX + 28.f, botonY + botonAlto / 2.f - 5.f });
			marca.setSize({ 18.f, 10.f });
			marca.setFillColor(victoria ? sf::Color(170, 224, 188, 225) : sf::Color(244, 215, 146, 225));
			window.draw(marca);
		}

		sf::Text textoBoton(assets.get_fuente(i == 0 ? "titulo" : "texto"));
		textoBoton.setString(opciones[i]);
		textoBoton.setCharacterSize(i == 0 ? 31 : 24);
		textoBoton.setFillColor(seleccionado ? sf::Color(245, 240, 224, 255) : sf::Color(224, 205, 168, 205));
		textoBoton.setOutlineColor(sf::Color(0, 0, 0, 205));
		textoBoton.setOutlineThickness(1.4f);

		sf::FloatRect boundsBoton = textoBoton.getLocalBounds();
		textoBoton.setOrigin({
			boundsBoton.position.x + boundsBoton.size.x / 2.f,
			boundsBoton.position.y + boundsBoton.size.y / 2.f
			});
		textoBoton.setPosition({
			botonX + botonAncho / 2.f,
			botonY + 4.f + (botonAlto - 10.f) / 2.f
			});

		window.draw(textoBoton);
	}

	sf::Text textoAyuda(assets.get_fuente("texto"));
	textoAyuda.setString("W/S  O  FLECHAS  +  ENTER");
	textoAyuda.setCharacterSize(17);
	textoAyuda.setFillColor(sf::Color(224, 205, 168, 155));
	textoAyuda.setOutlineColor(sf::Color(0, 0, 0, 205));
	textoAyuda.setOutlineThickness(1.4f);

	sf::FloatRect boundsAyuda = textoAyuda.getLocalBounds();
	textoAyuda.setOrigin({
		boundsAyuda.position.x + boundsAyuda.size.x / 2.f,
		boundsAyuda.position.y + boundsAyuda.size.y / 2.f
		});
	textoAyuda.setPosition({
		panelX + panelAncho / 2.f,
		panelY + 556.f + 28.f / 2.f
		});
	window.draw(textoAyuda);

	window.setView(vistaAnterior);
}