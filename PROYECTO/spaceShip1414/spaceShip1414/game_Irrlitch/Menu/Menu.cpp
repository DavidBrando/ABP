/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/



#include "Menu.h"
#include "../ManejadorEstadoGeneral.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Menu::Menu(std::string name) : EstadoGeneral(name) {
	control = false;
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {

}

Menu::Menu(IrrlichtDevice* iDevice, int i) {
	interfaz = iDevice->getGUIEnvironment();
	botonesMenu.push_back(interfaz->addButton(rect<int>(100, 120, 200, 160), NULL, 1, L"REANUDAR"));
	botonesMenu.push_back(interfaz->addButton(rect<int>(100, 160, 200, 200), NULL, 2, L"SALIR"));
}

void Menu::StarUP(IrrlichtDevice* iDevice) {
	interfaz = iDevice->getGUIEnvironment();
	ITexture* tex;
	tex = iDevice->getVideoDriver()->getTexture("textura/CARTEL.jpg");
	IGUIImage* img;
	estado = 0;
	tamanyo = vector2df(300, 300);
	botonesMenu.push_back(interfaz->addButton(rect<s32>(tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10, tamanyo.X / 3 + tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10), NULL, 1, L"JUGAR"));
	botonesMenu.push_back(interfaz->addButton(rect<s32>(tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10, tamanyo.X / 3 + tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10), NULL, 2, L"SALIR"));
	img = interfaz->addImage(core::rect<s32>(0, 0, 1366, 768));
	img->setImage(tex);
	img->setScaleImage(true);

}

void Menu::borrarMenu() {
	
	if (!botonesMenu.empty()) {
		for (std::vector<IGUIButton*>::iterator it = botonesMenu.begin(); it != botonesMenu.end(); ++it) {
			(*it)->remove();
		}
		botonesMenu.clear();
	}
}

void Menu::dibujarMenu() {
	
	botonesMenu.push_back(interfaz->addButton(rect<s32>(tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10, tamanyo.X / 3 + tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10), NULL, 1, L"JUGAR"));
	botonesMenu.push_back(interfaz->addButton(rect<s32>(tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10, tamanyo.X / 3 + tamanyo.X / 3, tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10 + tamanyo.Y / 10), NULL, 2, L"SALIR"));
}

s32 Menu::run() {

	
	if (!botonesMenu.empty()) {
		for (std::vector<IGUIButton*>::iterator it = botonesMenu.begin(); it != botonesMenu.end(); ++it) {

			if ((*it)->isPressed()) {
				std::cout << (*it)->getID() << std::endl;
				//borrarMenu();
				return (*it)->getID();
			}
		}
	}
	return -1;
}

void Menu::render(IrrlichtDevice* iDevice) {
	if (control == false) {
		this->StarUP(iDevice);
		control = true;
	}

	switch (estado) {
	case 0:
		s32 pulsado;
		pulsado = this->run();
		if (pulsado == 1) {
			estado = 1;
		}
		else if (pulsado == 2) {
			estado = 2;
		}
		break;
	case 1:

		//this->nombre="juego";
		borrarMenu();
		manager.CambiaEstado("juego");
		iDevice->getGUIEnvironment()->clear();
		control = false;
		break;

	case 2:
		iDevice->closeDevice();



		break;
	}

	if (control == true) {
		this->dibujarMenu();
		iDevice->getGUIEnvironment()->drawAll();
	}
}

void Menu::Dentro(void) {
	//set up gui
}

void Menu::Fuera(void) {
	//restore playerdata
}

bool Menu::OnEvent(const SEvent &event) {
	//handle user input
	return (false);
}
