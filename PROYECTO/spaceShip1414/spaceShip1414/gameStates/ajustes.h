#pragma once
#include "estadosJuego.h"
#include <SFML/Graphics.hpp>


class ajustes :
	public estadosJuego
{
public:
	ajustes(unsigned int, unsigned int);
	~ajustes();
	void handler(void*, void *, void *)override;
	void update(double, void *, void *) override;
	void render(void *) override;
	void resize(float width, float height) override;
	int GetPressedItem() { return opcionSelecionada; }
private:
	void checkMousePos(void *);
	void clickOpcion(void *, void*);
	bool opcionSelecionada;
	sf::Font font;
	sf::Text opciones;
	sf::Sprite sFondo;
	sf::Texture tFondo;
	sf::Sprite sHub;
	sf::Texture tHub;
	sf::Sprite sButtonSelec;
	sf::Texture tButtonSelec;
};

