#pragma once
#include <glm\vec3.hpp>

class TGraphicEngine;
class TGameEngine;
class movimentHandler
{
public:
	movimentHandler();
	~movimentHandler();
	void update(int, TGraphicEngine *, TGameEngine *);
private:
	//false = camara : true = player
	bool activo;
	bool moverJugador;
	float mouseSensitive;
};

