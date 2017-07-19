#include "perdido.h"
#include "MaquinaEstadosJuego.h"
#include <iostream>
#include <locale>
#include <string>
#include <SFML\System\Time.hpp>

perdido::perdido(float width, float height) : estadosJuego("gameOverState")
{
	if (!imagen.loadFromFile("resourse/image/cartel" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}

	fondo.setTexture(imagen);

	if (!font.loadFromFile("resourse/font/Radiof.ttf"))
	{
		std::cerr << "Fuente no cargada" << std::endl;
	}

	titulo.setFont(font);
	titulo.setColor(sf::Color::Yellow);
	titulo.setString("Has Muerto");
	titulo.setCharacterSize(40);
	titulo.setPosition(sf::Vector2f(503, 364));
	descuento = sf::milliseconds(2000);
}

perdido::~perdido()
{
	std::cout << "Perdido Destroyed" << std::endl;
}

void perdido::render(void * window)
{
	static_cast<sf::RenderWindow *>(window)->pushGLStates();
	static_cast<sf::RenderWindow *>(window)->draw(fondo);
	static_cast<sf::RenderWindow *>(window)->draw(titulo);
	static_cast<sf::RenderWindow *>(window)->popGLStates();
}

void perdido::resize(float width, float height)
{
	if (!imagen.loadFromFile("resourse/image/cartel" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}
	fondo.setTexture(imagen);
	titulo.setPosition(sf::Vector2f(300, 400));
}

void perdido::update(double deltatime, void * window, void * manager)
{
	if (!firtsUpdate)
	{
		firtsUpdate = true;
		reloj.restart();
	}
	if (descuento.asMilliseconds() - reloj.getElapsedTime().asMilliseconds() <= 0) { static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("menuState"); }
}

void perdido::handler(void * event, void * window, void * manager)
{
	switch (static_cast<sf::Event *>(event)->type)
	{
	case sf::Event::KeyReleased:
		switch (static_cast<sf::Event *>(event)->key.code)
		{
		case sf::Keyboard::Return:
			static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("menuState");
			break;
		}
		break;
	}
}