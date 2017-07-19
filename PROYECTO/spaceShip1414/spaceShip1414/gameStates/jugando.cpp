#include "jugando.h"
#include "MaquinaEstadosJuego.h"
#include "..\Game\TGameEngine.h"
#include "..\graphicEngine\TGraphicEngine.h"
#include "..\movimentHandler\movimentHandler.h"
#include <iostream>
#include <string>
#include <SFML\OpenGL.hpp>
#include "../Game/player.h"

jugando::jugando(float w, float h) : estadosJuego("playingState"), arma{ -1 }, opciones{ false }, rec{ false }, pausa{ false }, victoria { false },
texto{ nullptr }, font{ nullptr }, tMenuPausa{ nullptr }, bMenuPausa{ nullptr }, bPulsetMenu{ nullptr }, tPulsetMenu{ nullptr }, bPausaPlay{ nullptr }, tPausa{ nullptr },
tPlay{ nullptr }, iArma{ nullptr }, iVida{ nullptr }, tVida{ nullptr }, rectangle{ nullptr }, reloj{ nullptr }, fFondo{ nullptr }, tFondo{ nullptr }, width{ w }, height{ h },
tecla{ -1 }, handlerApp{ nullptr }, graphicApp{ nullptr }, gameApp{ nullptr }, parcialReloj(sf::milliseconds(10)), fin{ false }, debugFisicas { true }
{
	tArma[0] = nullptr;
	tArma[1] = nullptr;
}

jugando::~jugando()
{
	if (graphicApp != nullptr) { limpiarEstado(); }
	std::cout << "Jugando Destroyed" << std::endl;
}

void jugando::inicializarEstadoOld()
{
	graphicApp = new TGraphicEngine(width,height);
	if (!graphicApp->iniciarGraphicEngine())
	{
		std::cout << "Error al inicializar el motor Grafrico" << std::endl;
	}
	gameApp = new TGameEngine();
	if (!gameApp->iniciarGameEngine(graphicApp))
	{
		std::cout << "Error al inicializar el motor del Juego" << std::endl;
	}
	handlerApp = new movimentHandler();
	rec = false;
	pausa = false;
	opciones = false;
	font = new sf::Font();
	texto = new sf::Text();
	bMenuPausa = new sf::Sprite();
	tMenuPausa = new sf::Texture();
	bPulsetMenu = new sf::Sprite();
	tPulsetMenu = new sf::Texture();
	bPausaPlay = new sf::Sprite();
	tPausa = new sf::Texture();
	tPlay = new sf::Texture();
	iArma = new sf::Sprite();
	tArma[0] = new sf::Texture();
	tArma[1] = new sf::Texture();
	iVida = new sf::Sprite();
	tVida = new sf::Texture();
	rectangle = new sf::RectangleShape();
	reloj = new sf::Clock();
	fFondo = new sf::Sprite();
	tFondo = new sf::Texture();
	tecla = -1;
	if (!tFondo->loadFromFile("resourse/image/espacio.jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}
	fFondo->setTexture(*tFondo);
	fFondo->setPosition(0, 0);

	if (!tPausa->loadFromFile("resourse/texture/bPause.png", sf::IntRect(0, 0, 111, 111)))
	{
		std::cerr << "Boton Pause no cargado" << std::endl;
	}
	tPausa->setSmooth(true);
	if (!tPlay->loadFromFile("resourse/texture/bPlay.png", sf::IntRect(0, 0, 111, 111)))
	{
		std::cerr << "Boton Play no cargado" << std::endl;
	}
	tPlay->setSmooth(true);
	bPausaPlay->setTexture(*tPausa);
	if (height > 768) { bPausaPlay->setPosition(80, 960); }
	else { bPausaPlay->setPosition(80, 668); }
	bPausaPlay->setScale(0.35f, 0.35f);

	if (!tArma[0]->loadFromFile("resourse/image/pistola.png", sf::IntRect(0, 0, 960, 540)))
	{
		std::cerr << "Icono Arma no cargado" << std::endl;
	}
	tArma[0]->setSmooth(true);
	if (!tArma[1]->loadFromFile("resourse/image/escopeta.png", sf::IntRect(0, 0, 960, 540)))
	{
		std::cerr << "Icono Arma no cargado" << std::endl;
	}
	tArma[1]->setSmooth(true);
	iArma->setTexture(*tArma[0]);
	if (height > 768) { iArma->setPosition(1750, 960); }
	else { iArma->setPosition(1210, 668); }
	iArma->setScale(0.075f, 0.075f);

	if (!tVida->loadFromFile("resourse/image/battery.png", sf::IntRect(0, 0, 360, 360)))
	{
		std::cerr << "Icono Vida no cargado" << std::endl;
	}
	tVida->setSmooth(true);
	iVida->setTexture(*tVida);
	if (height > 768) { iVida->setPosition(1770, 50); }
	else { iVida->setPosition(1215, 50); }
	iVida->setScale(0.25f, 0.25f);

	if (!tMenuPausa->loadFromFile("resourse/image/bMenu.png", sf::IntRect(0, 0, 181, 182)))
	{
		std::cerr << "Icono Menu no cargado" << std::endl;
	}
	tMenuPausa->setSmooth(true);
	bMenuPausa->setTexture(*tMenuPausa);
	if (height > 768) { bMenuPausa->setPosition(870, 449); }
	else { bMenuPausa->setPosition(593, 293); }

	if (!tPulsetMenu->loadFromFile("resourse/image/bPulsetMenu.png", sf::IntRect(0, 0, 131, 130)))
	{
		std::cerr << "Icono Menu no cargado" << std::endl;
	}
	tPulsetMenu->setSmooth(true);
	bPulsetMenu->setTexture(*tPulsetMenu);

	if (!font->loadFromFile("resourse/font/Radiof.ttf"))
	{
		std::cerr << "Fuente no cargada" << std::endl;
	}
	texto->setFont(*font);
}

void jugando::inicializarEstado()
{
	graphicApp = new TGraphicEngine(width, height);
	if (!graphicApp->iniciarGraphicEngine())
	{
		std::cout << "Error al inicializar el motor Grafrico" << std::endl;
	}
	gameApp = new TGameEngine();
	if (!gameApp->iniciarGameEngine(graphicApp))
	{
		std::cout << "Error al inicializar el motor del Juego" << std::endl;
	}
	handlerApp = new movimentHandler();
	rec = false;
	pausa = false;
	opciones = false;
	font = new sf::Font();
	texto = new sf::Text();
	bPausaPlay = new sf::Sprite();
	tPausa = new sf::Texture();
	bMenuPausa = new sf::Sprite();
	tMenuPausa = new sf::Texture();
	bPulsetMenu = new sf::Sprite();
	tPulsetMenu = new sf::Texture();
	tHub = new sf::Texture();
	bHub = new sf::Sprite();
	iArma = new sf::Sprite();
	tArma[0] = new sf::Texture();
	tArma[1] = new sf::Texture();
	rectangle = new sf::RectangleShape();
	reloj = new sf::Clock();
	fFondo = new sf::Sprite();
	tFondo = new sf::Texture();
	iVida = new sf::Sprite();
	tVida = new sf::Texture();
	tecla = -1;
	if (!tFondo->loadFromFile("resourse/image/espacio" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}
	fFondo->setTexture(*tFondo);
	fFondo->setPosition(0, 0);

	if (!tPausa->loadFromFile("resourse/image/botonPausa" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 58, 58)))
	{
		std::cerr << "Boton Pause no cargado" << std::endl;
	}
	tPausa->setSmooth(true);
	bPausaPlay->setTexture(*tPausa);
	if (height > 768) { bPausaPlay->setPosition(80, 960); }
	else { bPausaPlay->setPosition(76, 671); }

	if (!tHub->loadFromFile("resourse/image/hub" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, width, height)))
	{
		std::cerr << "Hub no cargado" << std::endl;
	}
	tHub->setSmooth(true);
	bHub->setTexture(*tHub);
	bHub->setPosition(0, 0);

	if (!tArma[0]->loadFromFile("resourse/image/pistola" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 64, 64)))
	{
		std::cerr << "Icono Arma no cargado" << std::endl;
	}
	tArma[0]->setSmooth(true);
	if (!tArma[1]->loadFromFile("resourse/image/escopeta" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 95, 20)))
	{
		std::cerr << "Icono Arma no cargado" << std::endl;
	}
	tArma[1]->setSmooth(true);
	iArma->setTexture(*tArma[0]);
	if (height > 768) { iArma->setPosition(1750, 960); }
	else { iArma->setPosition(1214, 564); }

	if (!tVida->loadFromFile("resourse/image/vida" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 196, 36)))
	{
		std::cerr << "Icono Vida no cargado" << std::endl;
	}
	tVida->setSmooth(true);
	iVida->setTexture(*tVida);
	if (height > 768) { iVida->setPosition(1770, 50); }
	else { iVida->setPosition(1312, 40); }
	iVida->setScale(-1,1);

	if (!tMenuPausa->loadFromFile("resourse/image/bMenu.png", sf::IntRect(0, 0, 181, 182)))
	{
		std::cerr << "Icono Menu no cargado" << std::endl;
	}
	tMenuPausa->setSmooth(true);
	bMenuPausa->setTexture(*tMenuPausa);
	if (height > 768) { bMenuPausa->setPosition(870, 449); }
	else { bMenuPausa->setPosition(593, 293); }

	if (!tPulsetMenu->loadFromFile("resourse/image/bPulsetMenu.png", sf::IntRect(0, 0, 131, 130)))
	{
		std::cerr << "Icono Menu no cargado" << std::endl;
	}
	tPulsetMenu->setSmooth(true);
	bPulsetMenu->setTexture(*tPulsetMenu);

	if (!font->loadFromFile("resourse/font/Radiof.ttf"))
	{
		std::cerr << "Fuente no cargada" << std::endl;
	}
	texto->setFont(*font);

	rectangleParcialRelojA = new sf::RectangleShape();
	rectangleParcialRelojA->setSize(sf::Vector2f(4, 10));
	rectangleParcialRelojA->setFillColor(sf::Color(255, 0, 0, 100));
	rectangleParcialRelojA->setPosition(330, 140);
	rectangleParcialRelojB = new sf::RectangleShape();
	rectangleParcialRelojB->setSize(sf::Vector2f(4, 6));
	rectangleParcialRelojB->setFillColor(sf::Color(255, 0, 0, 100));
	rectangleParcialRelojB->setPosition(330, 636);
}

bool jugando::limpiarEstado()
{
	delete texto;
	delete font;
	delete tMenuPausa;
	delete bMenuPausa;
	delete bPulsetMenu;
	delete tPulsetMenu;
	delete bPausaPlay;
	delete tPausa;
	delete tPlay;
	delete iArma;
	delete tArma[0];
	delete tArma[1];
	delete iVida;
	delete tVida;
	delete rectangle;
	delete reloj;
	delete fFondo;
	delete tFondo;
	delete handlerApp;
	delete gameApp;
	delete graphicApp;
	texto = nullptr;
	font = nullptr;
	tMenuPausa = nullptr;
	bMenuPausa = nullptr;
	bPulsetMenu = nullptr;
	tPulsetMenu = nullptr;
	bPausaPlay = nullptr;
	tPausa = nullptr;
	tPlay = nullptr;
	iArma = nullptr;
	tArma[0] = nullptr;
	tArma[1] = nullptr;
	iVida = nullptr;
	tVida = nullptr;
	rectangle = nullptr;
	reloj = nullptr;
	fFondo = nullptr;
	tFondo = nullptr;
	handlerApp = nullptr;
	graphicApp = nullptr;
	gameApp = nullptr;
	return 1;
}

void jugando::handler(void * event, void * window, void * manager)
{
	if (gameApp != nullptr && gameApp->getPlayer()->getVida() > 0) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			!sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			tecla = -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !pausa)
		{
			std::cout << "W" << std::endl;
			tecla = 3;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !pausa)
		{
			std::cout << "A" << std::endl;
			tecla = 1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !pausa)
		{
			std::cout << "S" << std::endl;
			tecla = 2;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !pausa)
		{
			std::cout << "D" << std::endl;
			tecla = 0;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			std::cout << "1" << std::endl;
			tecla = 4;
			if (gameApp->getPlayer()->getArmaActual() != -1)
				gameApp->getPlayer()->setArmaActual(-1);
			changeWeapon(-1);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			//pistola
			std::cout << "2" << std::endl;
			tecla = 5;
			if (gameApp->getPlayer()->getArmaActual() != 0)
				gameApp->getPlayer()->setArmaActual(0);
			changeWeapon(0);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			//escopeta
			std::cout << "3" << std::endl;
			tecla = 6;

			if (gameApp->getPlayer()->getArmaActual() != 1)
				gameApp->getPlayer()->setArmaActual(1);

			changeWeapon(1);
		}

		//comprobar que si no tienes balas no puedes recargar mas
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) {
			if (!debugFisicas) { debugFisicas = true; }
			else { debugFisicas = false; }
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)
			&& gameApp->getPlayer()->getMunicionActual() > 0) {
			gameApp->getPlayer()->recargar();

			if (gameApp->getPlayer()->getMunicionActual() < 0) {
				std::cout << "No puedes recagar, no te quedan balas" << std::endl;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)
			&& gameApp->getPlayer()->getTeclaE() == false) {
			std::cout << "CAMBIO ESTADO TRUE" << std::endl;
			gameApp->getPlayer()->setTeclaE(true);
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E)
			&& gameApp->getPlayer()->getTeclaE() == true) {
			std::cout << "CAMBIO ESTADO FALSE" << std::endl;
			gameApp->getPlayer()->setTeclaE(false);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& gameApp->getPlayer()->getTeclaQ() == false) {
			std::cout << "CAMBIO ESTADO TRUE" << std::endl;
			gameApp->getPlayer()->setTeclaQ(true);
			gameApp->getPlayer()->usarBotiquin();
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& gameApp->getPlayer()->getTeclaQ() == true) {
			std::cout << "CAMBIO ESTADO FALSE" << std::endl;
			gameApp->getPlayer()->setTeclaQ(false);
		}

		if (static_cast<sf::Event *>(event)->type == sf::Event::MouseButtonPressed)
		{
			if (static_cast<sf::Event *>(event)->key.code == sf::Mouse::Left)
			{
				if (pausa) { if (opciones) { clickAjustes(window); } else { clickPauseMenu(window, manager); } }
				else { clickPlayPause(window); }
				if (gameApp && gameApp->getPlayer()->getDisparo() == false && !pausa) {

					if (gameApp->getPlayer()->getCargador() >= 0) {
						gameApp->getPlayer()->Disparar(gameApp->getMundo(), 0.016);
					}

				}

				//if (gameApp->getPlayer()->getDisparo() == true) {
				//	gameApp->getPlayer()->setTiempoDisparo(gameApp->getPlayer()->getTiempoDisparo() + 0.016);
				//	if (gameApp->getPlayer()->getTiempoDisparo() >= 0.5f/*pers->getTiempoArma()*/) {
				//		gameApp->getPlayer()->setDisparo(false);
				//		gameApp->getPlayer()->setTiempoDisparo(0);
				//	}
				//}
			}
		}

		if (static_cast<sf::Event *>(event)->type == sf::Event::KeyReleased)
		{
			if (static_cast<sf::Event *>(event)->key.code == sf::Keyboard::Escape) { if (!pausa) { if (pausa) { play(); } else { pause(); } } }
		}
	}
}

void jugando::update(double deltatime, void * window, void * manager)
{
	if (pausa)
	{
		if (fin == true) { static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("gameOverState"); }
		if (victoria == true) { static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("gameVictoryState"); }
	}
	else
	{
		if (gameApp != nullptr && gameApp->getPlayer()->getVida() <= 0.0f)
		{
			fin = true;
			pausa = true;
		}
		else if (gameApp != nullptr && gameApp->getPlayer()->getVictory())
		{
			victoria = true;
			pausa = true;
		}
		else
		{
			if (parcialReloj.asMilliseconds() - reloj->getElapsedTime().asMilliseconds() <= 0)
			{
				if (!rec)
				{
					rectangleParcialRelojA->setPosition(rectangleParcialRelojA->getPosition().x + 8, 140);
					rectangleParcialRelojB->setPosition(rectangleParcialRelojB->getPosition().x + 8, 636);
					if (rectangleParcialRelojA->getPosition().x >= 1034) { rec = true; }
				}
				else
				{
					rectangleParcialRelojA->setPosition(rectangleParcialRelojA->getPosition().x - 8, 140);
					rectangleParcialRelojB->setPosition(rectangleParcialRelojB->getPosition().x - 8, 636);
					if (rectangleParcialRelojA->getPosition().x <= 326) { rec = false; }
				}
				reloj->restart();
			}
			iVida->setTextureRect(sf::IntRect(0, 0, 196 * gameApp->getPlayer()->getPorcentajeVida(), 36));

			gameApp->update(0.1, handlerApp, graphicApp, tecla);
		}
	}
}

void jugando::render(void * window)
{
	if (gameApp != nullptr && gameApp->getPlayer()->getVida() > 0.0f) {
		if (opciones)
		{
			static_cast<sf::RenderWindow *>(window)->pushGLStates();
			drawConfiguracion(window);
			static_cast<sf::RenderWindow *>(window)->popGLStates();
		}
		else
		{
			if (graphicApp) { graphicApp->draw(0.1); }
			if (debugFisicas) { gameApp->drawDebug(); }
			static_cast<sf::RenderWindow *>(window)->pushGLStates();
			drawHub(window);
			
			if (pausa)
			{
				drawPause(window);
			}
			static_cast<sf::RenderWindow *>(window)->popGLStates();
		}
	}
}

void jugando::resize(float width, float height)
{
	graphicApp->onresize(static_cast<int>(width), static_cast<int>(height));
	if (!tFondo->loadFromFile("resourse/image/espacio" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".jpg", sf::IntRect(1, 1, width, height)))
	{
		std::cerr << "Fondo no cargado" << std::endl;
	}
	fFondo->setTexture(*tFondo);
	fFondo->setPosition(0, 0);

	if (!tPausa->loadFromFile("resourse/image/botonPausa" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 58, 58)))
	{
		std::cerr << "Boton Pause no cargado" << std::endl;
	}
	tPausa->setSmooth(true);
	bPausaPlay->setTexture(*tPausa);
	if (height > 768) { bPausaPlay->setPosition(80, 960); }
	else { bPausaPlay->setPosition(76, 671); }

	if (!tHub->loadFromFile("resourse/image/hub" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, width, height)))
	{
		std::cerr << "Hub no cargado" << std::endl;
	}
	tHub->setSmooth(true);
	bHub->setTexture(*tHub);
	bHub->setPosition(0, 0);

	if (!tArma[0]->loadFromFile("resourse/image/pistola" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 64, 64)))
	{
		std::cerr << "Icono Arma no cargado" << std::endl;
	}
	tArma[0]->setSmooth(true);
	if (!tArma[1]->loadFromFile("resourse/image/escopeta" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 95, 20)))
	{
		std::cerr << "Icono Arma no cargado" << std::endl;
	}
	tArma[1]->setSmooth(true);
	iArma->setTexture(*tArma[0]);
	if (height > 768) { iArma->setPosition(1750, 960); }
	else { iArma->setPosition(1214, 564); }

	if (!tVida->loadFromFile("resourse/image/vida" + std::to_string(static_cast<int>(width)) + "x" + std::to_string(static_cast<int>(height)) + ".png", sf::IntRect(0, 0, 196, 36)))
	{
		std::cerr << "Icono Vida no cargado" << std::endl;
	}
	tVida->setSmooth(true);
	iVida->setTexture(*tVida);
	if (height > 768) { iVida->setPosition(1770, 50); }
	else { iVida->setPosition(1312, 40); }
	iVida->setScale(-1, 1);

	if (!tMenuPausa->loadFromFile("resourse/image/bMenu.png", sf::IntRect(0, 0, 181, 182)))
	{
		std::cerr << "Icono Menu no cargado" << std::endl;
	}
	tMenuPausa->setSmooth(true);
	bMenuPausa->setTexture(*tMenuPausa);
	if (height > 768) { bMenuPausa->setPosition(870, 449); }
	else { bMenuPausa->setPosition(593, 293); }

	if (!tPulsetMenu->loadFromFile("resourse/image/bPulsetMenu.png", sf::IntRect(0, 0, 131, 130)))
	{
		std::cerr << "Icono Menu no cargado" << std::endl;
	}
	tPulsetMenu->setSmooth(true);
	bPulsetMenu->setTexture(*tPulsetMenu);

	if (!font->loadFromFile("resourse/font/Radiof.ttf"))
	{
		std::cerr << "Fuente no cargada" << std::endl;
	}
	texto->setFont(*font);

	rectangleParcialRelojA = new sf::RectangleShape();
	rectangleParcialRelojA->setSize(sf::Vector2f(4, 10));
	rectangleParcialRelojA->setFillColor(sf::Color(255, 0, 0, 100));
	rectangleParcialRelojA->setPosition(330, 140);
	rectangleParcialRelojB = new sf::RectangleShape();
	rectangleParcialRelojB->setSize(sf::Vector2f(4, 6));
	rectangleParcialRelojB->setFillColor(sf::Color(255, 0, 0, 100));
	rectangleParcialRelojB->setPosition(330, 636);
}

void jugando::drawConfiguracion(void * window)
{
	static_cast<sf::RenderWindow *>(window)->draw(*fFondo);
	texto->setColor(sf::Color(255, 255, 255, 180));
	texto->setString("Ajustes del Juego");
	texto->setCharacterSize(20);

	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(621, 308); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
	texto->setColor(sf::Color(255, 255, 255, 180));
	texto->setString("Volver al juego");
	texto->setCharacterSize(20);

	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(621, 608); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
}

void jugando::drawPause(void * window)
{
	rectangle->setSize(sf::Vector2f(width, height));
	rectangle->setFillColor(sf::Color(0, 0, 0, 200));
	rectangle->setPosition(0, 0);
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);
	static_cast<sf::RenderWindow *>(window)->draw(*bMenuPausa);
	checkMousePos(window);
	texto->setColor(sf::Color(255, 255, 0, 230));
	texto->setString("Continuar");
	texto->setCharacterSize(20);

	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(621, 308); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
	texto->setColor(sf::Color(255, 255, 0, 230));
	texto->setString("Opciones");
	texto->setCharacterSize(20);

	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(627, 344); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
	texto->setColor(sf::Color(255, 255, 0, 230));
	texto->setString("Volver al Menu");
	texto->setCharacterSize(16);

	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(623, 386); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
	texto->setColor(sf::Color(255, 255, 0, 230));
	texto->setString("Salir a Windows");
	texto->setCharacterSize(16);

	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(622, 423); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
}

void jugando::drawNoClickHubOld(void * window)
{
	rectangle->setSize(sf::Vector2f(100, 10));
	rectangle->setFillColor(sf::Color(255, 255, 255, 150));
	rectangle->setPosition(50, 50);
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);
	rectangle->setSize(sf::Vector2f(10, 90));
	rectangle->setFillColor(sf::Color(255, 255, 255, 150));
	rectangle->setPosition(50, 60);
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);

	if (rec) {
		sf::CircleShape circulo(10);
		circulo.setFillColor(sf::Color(255, 0, 0, 150));
		circulo.setPosition(70, 70);
		static_cast<sf::RenderWindow *>(window)->draw(circulo);
		rec = false;
	}
	else {
		sf::CircleShape circulo(9);
		circulo.setFillColor(sf::Color(255, 0, 0, 150));
		circulo.setPosition(71, 71);
		static_cast<sf::RenderWindow *>(window)->draw(circulo);
		rec = true;
	}

	texto->setColor(sf::Color(255, 255, 255, 150));
	texto->setString("REC");
	texto->setCharacterSize(20);

	texto->setPosition(92, 65);
	static_cast<sf::RenderWindow *>(window)->draw(*texto);

	rectangle->setSize(sf::Vector2f(100, 10));
	rectangle->setFillColor(sf::Color(255, 255, 255, 150));
	if (height > 768) {	rectangle->setPosition(50, 1030); }
	else { rectangle->setPosition(50, 718); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);
	rectangle->setSize(sf::Vector2f(10, 90));
	if (height > 768) { rectangle->setPosition(50, 930); }
	else { rectangle->setPosition(50, 628); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);

	rectangle->setSize(sf::Vector2f(100, 10));
	if (height > 768) {	rectangle->setPosition(1770, 50); }
	else { rectangle->setPosition(1216, 50); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);
	rectangle->setSize(sf::Vector2f(10, 90));
	if (height > 768) { rectangle->setPosition(1860, 60); }
	else { rectangle->setPosition(1306, 60); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);

	static_cast<sf::RenderWindow *>(window)->draw(*iVida);
	rectangle->setSize(sf::Vector2f(70*(gameApp->getPlayer()->getPorcentajeVida()), 28));
	rectangle->setFillColor(sf::Color(0, 255, 0, 170));
	if (height > 768) { rectangle->setPosition(1770, 81); }
	else { rectangle->setPosition(1221, 81); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);
		
	rectangle->setSize(sf::Vector2f(100, 10));
	rectangle->setFillColor(sf::Color(255, 255, 255, 150));
	if (height > 768) {	rectangle->setPosition(1770, 1030); }
	else { rectangle->setPosition(1216, 718); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);
	rectangle->setSize(sf::Vector2f(10, 90));
	if (height > 768) {	rectangle->setPosition(1860, 930);	}
	else { rectangle->setPosition(1306, 628); }
	static_cast<sf::RenderWindow *>(window)->draw(*rectangle);

	static_cast<sf::RenderWindow *>(window)->draw(*iArma);

	texto->setColor(sf::Color(255, 255, 255, 180));
	texto->setString(std::to_string(balas));
	texto->setCharacterSize(20);
	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(1262, 688); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);

	sf::Time tiempo;
	if (!pausa)
	{
		tiempo = reloj->getElapsedTime();
	}
	texto->setColor(sf::Color(255, 255, 255, 180));
	texto->setString(std::to_string(tiempo.asSeconds()));
	texto->setCharacterSize(30);

	if (height > 768) { texto->setPosition(900, 1015); }
	else { texto->setPosition(623, 680); }
	static_cast<sf::RenderWindow *>(window)->draw(*texto);
	static_cast<sf::RenderWindow *>(window)->draw(*bPausaPlay);
}

void jugando::drawHub(void * window)
{
	static_cast<sf::RenderWindow *>(window)->draw(*bHub);
	static_cast<sf::RenderWindow *>(window)->draw(*rectangleParcialRelojA);
	static_cast<sf::RenderWindow *>(window)->draw(*rectangleParcialRelojB);
	if(arma != -1) { static_cast<sf::RenderWindow *>(window)->draw(*iArma); }

	texto->setColor(sf::Color(255, 255, 255, 140));
	texto->setString(std::to_string(gameApp->getPlayer()->getCargador()));
	texto->setCharacterSize(20);
	if (height > 768) { texto->setPosition(1226, 980); }
	else { texto->setPosition(1258, 596); }
	if (arma != -1) {
		static_cast<sf::RenderWindow *>(window)->draw(*texto);
	}
	static_cast<sf::RenderWindow *>(window)->draw(*iVida);
	static_cast<sf::RenderWindow *>(window)->draw(*bPausaPlay);
}

void jugando::changeWeapon(int a)
{
	arma = a;
	if(arma != -1)
	{
		iArma->setTexture(*tArma[a]);
		if (width > 1366)
		{
		}
		else
		{
			switch (a)
			{
			case 0:
				iArma->setPosition(1214, 564);
				iArma->setTextureRect(sf::IntRect(0, 0, 64, 64));
				break;
			case 1:
				iArma->setPosition(1198, 590);
				iArma->setTextureRect(sf::IntRect(0, 0, 95, 20));
				break;
			}
		}
	}

}

void jugando::pause()
{
	pausa = true;
	//bPausaPlay->setTexture(*tPlay);
}

void jugando::play()
{
	pausa = false;
	//bPausaPlay->setTexture(*tPausa);
}

void jugando::clickPauseMenu(void * window, void * manager)
{
	sf::Vector2i posMouse = sf::Mouse::getPosition(*(static_cast<sf::RenderWindow *>(window)));
	if (posMouse.x > 23 + 593 && posMouse.x < 593 + 157)
	{
		if (posMouse.y > 13 + 293 && posMouse.y < 293 + 46) {
			pausa = false;
		}
		if (posMouse.y > 50 + 293 && posMouse.y < 293 + 83) {
			opciones = true;
		}
		if (posMouse.y > 88 + 293 && posMouse.y < 293 + 121) {
			static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("menuState");
		}
		if (posMouse.y > 125 + 293 && posMouse.y < 293 + 159) {
			static_cast<MaquinaEstadosJuego *>(manager)->cambiaEstado("exitState");
		}
	}
}

void jugando::clickPlayPause(void * window)
{
	sf::Vector2i posMouse = sf::Mouse::getPosition(*(static_cast<sf::RenderWindow *>(window)));
	if (posMouse.x > bPausaPlay->getGlobalBounds().left 
		&& posMouse.x < (bPausaPlay->getGlobalBounds().width + bPausaPlay->getGlobalBounds().left)
		&& posMouse.y > bPausaPlay->getGlobalBounds().top 
		&& posMouse.y < (bPausaPlay->getGlobalBounds().height + bPausaPlay->getGlobalBounds().top))
	{
		pause();
	}
}

void jugando::checkMousePos(void * window)
{
	sf::Vector2i posMouse = sf::Mouse::getPosition(*(static_cast<sf::RenderWindow *>(window)));
	if (posMouse.x > 23 + 593 && posMouse.x < 593 + 157)
	{
		if (posMouse.y > 13 + 293 && posMouse.y < 293 + 46) {
			bPulsetMenu->setPosition(25 + 593, 293+14);
			static_cast<sf::RenderWindow *>(window)->draw(*bPulsetMenu);
		}
		if (posMouse.y > 50 + 293 && posMouse.y < 293 + 83) {
			bPulsetMenu->setPosition(25 + 593, 293 + 51);
			static_cast<sf::RenderWindow *>(window)->draw(*bPulsetMenu);
		}
		if (posMouse.y > 88 + 293 && posMouse.y < 293 + 121) {
			bPulsetMenu->setPosition(25 + 593, 293 + 89);
			static_cast<sf::RenderWindow *>(window)->draw(*bPulsetMenu);
		}
		if (posMouse.y > 125 + 293 && posMouse.y < 293 + 159) {
			bPulsetMenu->setPosition(25 + 593, 293 + 127);
			static_cast<sf::RenderWindow *>(window)->draw(*bPulsetMenu);
		}
	}
}

void jugando::clickAjustes(void * window)
{
	sf::Vector2i posMouse = sf::Mouse::getPosition(*(static_cast<sf::RenderWindow *>(window)));
	if (posMouse.x > 621 && posMouse.x < 750)
	{
		if (posMouse.y > 608 && posMouse.y < 628) {
			opciones = false;
		}
	}
}
