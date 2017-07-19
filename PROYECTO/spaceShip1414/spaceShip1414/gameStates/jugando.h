#pragma once
#include "estadosJuego.h"
#include <SFML/Graphics.hpp>

class TGameEngine;
class TGraphicEngine;
class movimentHandler;
class jugando :
	public estadosJuego
{
public:
	jugando(float, float);
	~jugando();
	void inicializarEstadoOld();
	void inicializarEstado() override;
	bool limpiarEstado() override;
	void handler(void*, void *, void *) override;
	void update(double, void *, void *) override;
	void render(void * window) override;
	void resize(float, float) override;
private:
	void drawConfiguracion(void *);
	void drawPause(void *);
	void drawNoClickHubOld(void * window);
	void drawHub(void *);
	void changeWeapon(int);
	void pause();
	void play();
	void clickPauseMenu(void *, void *);
	void clickPlayPause(void *);
	void checkMousePos(void *);
	void clickAjustes(void *);
	
	sf::Font * font;
	sf::Text * texto;
	sf::Texture * tHub;
	sf::Sprite * bHub;
	sf::Sprite * bMenuPausa;
	sf::Texture * tMenuPausa;
	sf::Sprite * bPulsetMenu;
	sf::Texture * tPulsetMenu;
	sf::Sprite * bPausaPlay;
	sf::Texture * tPausa;
	sf::Texture * tPlay;
	sf::Sprite * iArma;
	sf::Texture * tArma[2];
	sf::Sprite * iVida;
	sf::Texture * tVida;
	sf::RectangleShape * rectangle;
	sf::Clock * reloj;
	sf::Time parcialReloj;
	sf::RectangleShape * rectangleParcialRelojA;
	sf::RectangleShape * rectangleParcialRelojB;
	sf::Sprite * fFondo;
	sf::Texture * tFondo;

	TGameEngine * gameApp;
	TGraphicEngine * graphicApp;
	movimentHandler * handlerApp;

	int arma;
	unsigned int balas;
	bool rec;
	bool fin, debugFisicas, victoria;
	bool pausa, opciones;
	float width, height;
	int tecla;
};

