#include "ajustes.h"
#include "MaquinaEstadosJuego.h"
#include <iostream>

ajustes::ajustes(unsigned int width, unsigned int height) : estadosJuego("configState"), opcionSelecionada{ false }
{
	if (!tFondo.loadFromFile("resourse/image/espacio" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}

	sFondo.setTexture(tFondo);
	sFondo.setPosition(0, 0);

	if (!tHub.loadFromFile("resourse/image/menuAjustes" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Hub no cargado" << std::endl;
	}
	tHub.setSmooth(true);
	sHub.setTexture(tHub);
	sHub.setPosition(0, 0);

	if (!tButtonSelec.loadFromFile("resourse/image/menuPrinPulsado" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png"))
	{
		std::cerr << "Botton Seleccin no cargado" << std::endl;
	}
	tButtonSelec.setSmooth(true);
	sButtonSelec.setTexture(tButtonSelec);
	sButtonSelec.setPosition(581, 493);

	if (!font.loadFromFile("resourse/font/Radiof.ttf"))
	{
		std::cerr << "Fuente no cargada" << std::endl;
	}

	opciones.setFont(font);
	opciones.setColor(sf::Color::White);
	opciones.setString("Volver");
	opciones.setPosition(sf::Vector2f(628, 506));
	
}

ajustes::~ajustes()
{
	std::cout << "Ajustes Destroyed" << std::endl;
}

void ajustes::render(void * window)
{
	static_cast<sf::RenderWindow *>(window)->pushGLStates();
	static_cast<sf::RenderWindow *>(window)->draw(sFondo);
	static_cast<sf::RenderWindow *>(window)->draw(sHub);
	if (opcionSelecionada) { static_cast<sf::RenderWindow *>(window)->draw(sButtonSelec); }
	static_cast<sf::RenderWindow *>(window)->draw(opciones);
	static_cast<sf::RenderWindow *>(window)->popGLStates();
}

void ajustes::resize(float width, float height)
{
	if (!tFondo.loadFromFile("resourse/image/espacio" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}

	sFondo.setTexture(tFondo);
	sFondo.setPosition(0, 0);

	if (!tHub.loadFromFile("resourse/image/menuAjustes" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Hub no cargado" << std::endl;
	}
	tHub.setSmooth(true);
	sHub.setTexture(tHub);
	sHub.setPosition(0, 0);

	if (!tButtonSelec.loadFromFile("resourse/image/menuPrinPulsado" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png"))
	{
		std::cerr << "Botton Seleccin no cargado" << std::endl;
	}
	tButtonSelec.setSmooth(true);
	sButtonSelec.setTexture(tButtonSelec);
	sButtonSelec.setPosition(581, 493);

	opciones.setPosition(sf::Vector2f(628, 506));
}

void ajustes::update(double deltatime, void * window, void * manager)
{
	checkMousePos(window);
}

void ajustes::checkMousePos(void * window)
{
	sf::Vector2i posMouse = sf::Mouse::getPosition(*(static_cast<sf::RenderWindow *>(window)));
	if (posMouse.x > 581 && posMouse.x < 581 + 190)
	{
		if (posMouse.y > 493 && posMouse.y < 493 + 57) {
			opciones.setColor(sf::Color::White);
			opcionSelecionada = true;
			opciones.setColor(sf::Color::Red);
		}
		else { opcionSelecionada = false; }
	}
	else { opcionSelecionada = false; }
}

void ajustes::clickOpcion(void * window, void * manager)
{
	sf::Vector2i posMouse = sf::Mouse::getPosition(*(static_cast<sf::RenderWindow *>(window)));
	if (posMouse.x > 581 && posMouse.x < 581 + 190)
	{
		if (posMouse.y > 493 && posMouse.y < 493 + 57) {
			static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("menuState");
		}
	}
}

void ajustes::handler(void * event, void * window, void * manager)
{
	if (static_cast<sf::Event *>(event)->type == sf::Event::MouseButtonPressed)
	{
		if (static_cast<sf::Event *>(event)->key.code == sf::Mouse::Left)
		{
			clickOpcion(window, manager);
		}
	}
	switch (static_cast<sf::Event *>(event)->type)
	{
	case sf::Event::KeyReleased:
		switch (static_cast<sf::Event *>(event)->key.code)
		{
		case sf::Keyboard::Return:
			if( opcionSelecionada ){ static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("exitState"); }
			break;
		}
		break;
	}
}