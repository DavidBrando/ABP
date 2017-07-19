#pragma once
class readJson;
class Escenario;
class Mundo;
class b2GLDraw;
class player;
class Camara;
class TGraphicEngine;
class movimentHandler;

class TGameEngine
{
public:
	TGameEngine();
	~TGameEngine();
	bool iniciarGameEngine(TGraphicEngine *);
	void update(double deltaTime, movimentHandler * handler, TGraphicEngine * motorApp, int tecla);

	void cambiarLuzActiva(int);
	player * getPlayer();
	Camara * getCamara();
	void drawDebug();
	Mundo * getMundo();

	void actualizarTiempoDeDisparo();
	void victory();

private:
	unsigned int flags;
	Mundo * world;
	Escenario * scene;
	b2GLDraw * fooDrawInstance;
	player * jugador;
};

