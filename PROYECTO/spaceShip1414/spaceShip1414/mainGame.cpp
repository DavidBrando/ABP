#include "mainGame.h"
#include "gameStates\MaquinaEstadosJuego.h"
#include "gameStates\menu.h"
#include "gameStates\ajustes.h"
#include "gameStates\jugando.h"
#include "gameStates\salida.h"
#include "gameStates\perdido.h"
#include "gameStates\victoria.h"
#include <iostream>


mainGame::mainGame() : width{ 1366.f }, height{ 768.f }, fullScreen{ false }, redimencion{ false }
{
}

mainGame::~mainGame()
{
	delete gameConfig;
	gameConfig = nullptr;
	delete gameMenu;
	gameMenu = nullptr;
	delete gamePlaying;
	gamePlaying = nullptr;
	delete gameExit;
	gameExit = nullptr;
	delete manager;
	manager = nullptr;
	delete window;
	window = nullptr;
	delete gameOver;
	gameOver = nullptr;
	delete gamePass;
	gamePass = nullptr;
	std::cout << "Gracias por jugar a SpaceShip 1414" << std::endl;
}

bool mainGame::init(const std::string titulo)
{
	contextSettings = new sf::ContextSettings();
	contextSettings->depthBits = 24;

	if (fullScreen) { window = new sf::RenderWindow(sf::VideoMode(width, height), titulo, sf::Style::Fullscreen, *contextSettings); }
	else { window = new sf::RenderWindow(sf::VideoMode(width, height), titulo, sf::Style::Default, *contextSettings); }
	glewInit();
	window->setVerticalSyncEnabled(true);
	manager = new MaquinaEstadosJuego();
	gameMenu = new menu(width,height);
	manager->addEstado(gameMenu, true);
	gameConfig = new ajustes(width, height);
	manager->addEstado(gameConfig, false);
	gamePlaying = new jugando(width, height);
	manager->addEstado(gamePlaying, false);
	gameExit = new salida(width, height);
	manager->addEstado(gameExit, false);
	gameOver = new perdido(width, height);
	manager->addEstado(gameOver, false);
	gamePass = new victoria(width, height);
	manager->addEstado(gamePass, false);
	if (window != nullptr && gameMenu != nullptr && gameConfig != nullptr && gamePlaying != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void mainGame::run()
{
	while (window->isOpen())
	{
		//if (manager->reniciarEstado()) { reniciarJugando(); }
		sf::Event event;
		while (window->pollEvent(event))
		{
			manager->getEstadoActivo()->handler(&event, window, manager);
			if (event.type == sf::Event::Closed) { manager->cambiaEstado("exitState");	}
		}

		manager->getEstadoActivo()->update(0.1, window, manager);

		window->clear();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexArrayAttribEXT(0, 0);
	
		manager->getEstadoActivo()->render(window);
		window->display();
	}
}

void mainGame::resizeWindow(float w, float h)
{
	width = w;
	height = h;
	window->setSize(sf::Vector2u(width, height));
	gameConfig->resize(width, height);
	gameMenu->resize(width, height);
	gamePlaying->resize(width, height);
	gameExit->resize(width, height);
	gameOver->resize(width, height);
	gamePass->resize(width, height);
}

void mainGame::fullScreenWindow()
{
	if (fullScreen == true)	{ fullScreen = false; }
	else { fullScreen = true; }
}

void mainGame::reniciarJugando()
{
	manager->borrarEstado("playingState");
	delete gamePlaying;
	gamePlaying = new jugando(width, height);
	manager->addEstado(gamePlaying, false);
}
