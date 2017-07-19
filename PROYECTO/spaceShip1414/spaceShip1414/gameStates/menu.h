#pragma once
#include "estadosJuego.h"
#include <SFML/Graphics.hpp>

#define MAX_OPCIONES 4
class menu :
	public estadosJuego
{
public:
	menu(unsigned int, unsigned int);
	~menu();
	void handler(void*, void *, void *)override;
	void update(double, void *, void *) override;
	void render(void *) override;
	void resize(float width, float height) override;
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return opcionSelecionada; }
private:
	void checkMousePos(void *);
	void checkOpcionSelecionada();
	void clickOpcion(void *, void*);
	int opcionSelecionada;
	sf::Font font;
	sf::Text opciones[MAX_OPCIONES];
	sf::Sprite sFondo;
	sf::Texture tFondo;
	sf::Sprite sHub;
	sf::Texture tHub;
	sf::Sprite sButtonSelec;
	sf::Texture tButtonSelec;
};

