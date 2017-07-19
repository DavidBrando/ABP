#pragma once
#include "estadosJuego.h"
#include <SFML/Graphics.hpp>
#include <SFML\System\Clock.hpp>
class salida :
	public estadosJuego
{
public:
	salida(float, float);
	~salida();
	void handler(void*, void *, void *) override;
	void update(double, void *, void *) override;
	void render(void *) override;
	void resize(float width, float height) override;
private:
	sf::Font font;
	sf::Text titulo;
	sf::Sprite fondo;
	sf::Texture imagen;
	sf::Clock reloj;
	sf::Time descuento;
	bool firtsUpdate;
};