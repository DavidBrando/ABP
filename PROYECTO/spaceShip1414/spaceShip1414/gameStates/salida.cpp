#include "salida.h"
#include "MaquinaEstadosJuego.h"
#include <iostream>
#include <locale>
#include <string>
#include <SFML\System\Time.hpp>

salida::salida(float width, float height) : estadosJuego("exitState"), firtsUpdate{ false }
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
	titulo.setString("Gracias por haber jugado");
	titulo.setCharacterSize(60);
	titulo.setPosition(sf::Vector2f(300, 400));
	descuento = sf::milliseconds(500);
}

salida::~salida()
{
	std::cout << "Salida Destroyed" << std::endl;
}

void salida::render(void * window)
{
	static_cast<sf::RenderWindow *>(window)->pushGLStates();
	static_cast<sf::RenderWindow *>(window)->draw(fondo);
	/*titulo.setString("Gracias por haber jugado");
	titulo.setCharacterSize(60);
	titulo.setPosition(sf::Vector2f(300, 400));*/
	static_cast<sf::RenderWindow *>(window)->draw(titulo);
	/*int tempo = (descuento.asMilliseconds() - reloj.getElapsedTime().asMilliseconds()) / 1000;
	titulo.setString(std::to_string(tempo));
	titulo.setCharacterSize(30);
	titulo.setPosition(sf::Vector2f(1200, 700));
	static_cast<sf::RenderWindow *>(window)->draw(titulo);*/
	static_cast<sf::RenderWindow *>(window)->popGLStates();
}

void salida::resize(float width, float height)
{
	if (!imagen.loadFromFile("resourse/image/cartel" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}

	fondo.setTexture(imagen);
	titulo.setPosition(sf::Vector2f(300, 400));
}

void salida::update(double deltatime, void * window, void * manager)
{
	if (!firtsUpdate)
	{
		firtsUpdate = true;
		reloj.restart(); 
	}
	if (descuento.asMilliseconds() - reloj.getElapsedTime().asMilliseconds()<=0) { static_cast<sf::RenderWindow *>(window)->close(); }
}

void salida::handler(void * event, void * window, void * manager)
{
	switch (static_cast<sf::Event *>(event)->type)
	{
	case sf::Event::KeyReleased:
		switch (static_cast<sf::Event *>(event)->key.code)
		{
		case sf::Keyboard::Return:
			static_cast<sf::RenderWindow *>(window)->close();
			break;
		}
		break;
	}
}