/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CriaAlien.cpp
 * Author: Hector
 *
 * Created on 16 de enero de 2017, 18:00
 */

#include "CriaAlien.h"
#include "Nodo.h"
#include "navmeshes.h"
#include "AStar.h"
#include "../Escenario/Escenario.h"
#include "../Fisicas/Entity2D.h"
#include "Waypoints.h"
#include "BehaviorTree\BehaivorTree.h"
#include "LogicaDifusa.h"
#include "Flocking\Flocking.h"

#define RESISTMAX 50
#define VELMAX 55



CriaAlien::CriaAlien(ISceneManager* smgr, IVideoDriver* driver, b2World *world, vector3df posicion, Escenario* esce, Waypoints* puntos) : Enemigo(smgr, driver, world, posicion, puntos) {
    
	//seria mejor que se le pasara las cosas necesarias del escenario que todo el escenario entero
	//para hacer el tema de los navmesehses y los waypoints
	maya = smgr -> addCubeSceneNode(5); //preguntar a Miguel Angel
    if (maya) {
        maya -> setPosition(posicion); //vector3df(0, 10, 40)
        maya->getMaterial(0).EmissiveColor.set(0, 0, 0, 20);
    }

    vel = VELMAX;
    pos = maya->getPosition();
	rot = maya->getRotation();
	vida = 100.0f;

	st.posicion = posicion;
	st.orientacion = 0;
	st.rotacion = 0;
	st.velocidad = vector3df(0, 0, 0);

	sto.angular = 0;
	sto.linear = vector3df(0, 0, 0);

	irr::core::stringw wideString(vida);
	GVida = smgr->addTextSceneNode(smgr->getGUIEnvironment()->getBuiltInFont(), wideString.c_str(), video::SColor(255, 255, 0, 0), 0);
	RVida = smgr->addTextSceneNode(smgr->getGUIEnvironment()->getBuiltInFont(), L"Vida: ", video::SColor(255, 255, 0, 0), 0);
	//napis a lo mejor estaria bien que estuviese en el .h de enemigo
	//tambien se tiene que borrar con el destructor
	GVida->setPosition(posicion);
	RVida->setPosition(vector3df(posicion.X - 64, posicion.Y, posicion.Z));

	smgr->getGUIEnvironment()->clear();
    
    estadoActual = BUSCARPUNTO;
    raza = CRIA;
    blindaje = 0.0f;
	damageChoque = 10.0f;
	moral = 50.0f;
	resistencia = RESISTMAX;
	
	entity = new Entity2D(world, pos, true, this, smgr, raza);
   // nav = new navmeshes(10, esce);
	//Botiquines *bot = new Botiquines(*static_cast<Botiquines*>(objeto->getObjeto3D()));
	
	waypoints = puntos;
	logica = new LogicaDifusa(vida, moral, resistencia);
   // waypoints->creaPesos(entity);
	//waypoints->mostrarPesos();
	tree = new BehaivorTree();
	disparado = false;

	damageBala = 10.0f;



//    std::cout << "GRAFO CON 0" << std::endl;
//    std::cout << "" << std::endl;
    //    nav->muestraGrafo();
  //  std::cout << "COLISIONES" << std::endl;
   // std::cout << "" << std::endl;
   // nav->setColisiones(esce->getParedes());
    //nav->muestraGrafo();
	path = new AStar(waypoints->getMatriz(), waypoints->getNodos().size());
	floc = new Flocking(false);
    // dibujaGrid(smgr);
	//crearArbol();
	time = 0.0f;

}

//CriaAlien::CriaAlien(const CriaAlien& orig) {
//}

CriaAlien::~CriaAlien() {

	delete(tree);
	//delete(nav);

}

void CriaAlien::crearArbol() {

	Node* n = new Node("root", "selector");
	tree->addNode(n, NULL);

	Node * a = new Node("relax", "selector");
	tree->addNode(a, n);
	Node *b = new Node("jugadorPercibido", "condicion");
	tree->addNode(b, a);
	b = new Node("estoyCansado", "condicion");
	tree->addNode(b, a);
	b = new Node("patrullar", "secuencia");
	tree->addNode(b, a);
	Node *c = new Node("buscarWaypoint", "accion");
	tree->addNode(c, b);
	c = new Node("moverWaypoint", "accion");
	tree->addNode(c, b);
	c = new Node("pararMirar", "accion");
	tree->addNode(c, b);

	a = new Node("alerta", "selector");
	tree->addNode(a, n);
	b = new Node("jugadorVisualizado", "condicion");
	tree->addNode(b, a);
	b = new Node("ultimo4Waypoints", "accion");
	tree->addNode(b, a);

	a = new Node("combate", "secuencia");
	tree->addNode(a, n);
	b = new Node("moral", "selector");
	tree->addNode(b, a);
	c = new Node("alta", "selector");
	tree->addNode(c, b);
	Node *d = new Node("vidaAlta", "secuencia");
	tree->addNode(d, c);
	Node *e = new Node("arañar", "accion");
	tree->addNode(e, d);
	d = new Node("vidaMedia", "selector");
	tree->addNode(d, c);
	e = new Node("cerca", "secuencia");
	tree->addNode(e, d);
	Node *f = new Node("arañar", "accion");
	tree->addNode(f, e);
	e = new Node("lejos", "secuencia");
	tree->addNode(e, d);
	f = new Node("cubrir", "accion");
	tree->addNode(f, e);
	c = new Node("baja", "selector");
	tree->addNode(c, b);
	d = new Node("vidaMedia", "secuencia");
	tree->addNode(d, c);
	e = new Node("cubrir", "accion");
	tree->addNode(e, d);
	d = new Node("vidaBaja", "secuencia");
	tree->addNode(d, c);
	e = new Node("huir", "accion");
	tree->addNode(e, d);


	std::cout << tree->Update() << std::endl;
	//	tree->imprimirArbol();

}

void CriaAlien::dibujaGrid(ISceneManager *grid) {
    float** matriz = nav->getMatriz();
    IMeshSceneNode *maya;
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (matriz[i][j] == 1) {
                maya = grid->addCubeSceneNode(10);
                maya->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
                maya->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
                maya->getMaterial(0).EmissiveColor.set(0, 255, 10, 20);
                maya->setPosition(vector3df(10*i-240, 5, 10 * j - 240));

            } else {
                maya = grid->addCubeSceneNode(10);
                maya->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
                maya->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
                maya->getMaterial(0).EmissiveColor.set(0, 255, 255, 255);
                maya->setPosition(vector3df(10 * i - 240, 10, 10 * j - 240));
            }

        }
    }
}

void CriaAlien::setLider(bool c) {
	floc->setLider(c);
}



void CriaAlien::Update(f32 dt) { //cambiar a que no se le pase nada y que en el estado 0 busque el waypoint mas cercano a su posicion
	
	//crear metodos para todos los estados

	if (vista == true && estadoActual != FLOCKING && floc->getLider() != true) {
		floc->colisionAvoidance(entity);

	}

	if (esquivarPared) {
		obstacleAvoidance();
	}

	st.update(sto, dt);
	

	switch (estadoActual) {

		

        case BUSCARPUNTO: 
          
			BuscarWaypoint();

			//st.update(sto, dt);

				
            break;

        case PATRULLAR: //patrullar
          
			Patrullar();
			//iniLogicaDifusa();
			if (vel < VELMAX * 0.5f) {
				setVelocidad();
				estadoActual = DESCANSAR;

			}
		//	st.update(sto, dt);
			if(floc->getLider()) {
				floc->cambiarEstadoSequito(entity, FLOCKING);
			}

            break;

        case ATACAR: //atacar
          
			Atacar(dt);

            break;


		case DESCANSAR:

			setVelocidad();
			recuperarResistencia();
			if (resistencia >= RESISTMAX * 0.75) {

				vel = VELMAX;
				estadoActual = PATRULLAR;
				

			}
				

			break;

		case ROTACION:
			maya->getMaterial(0).EmissiveColor.set(0, 255, 50, 150);


			break;

		case ESCAPAR:

			maya->getMaterial(0).EmissiveColor.set(0, 255, 50, 150);
			iniLogicaDifusa();

			break;

		case CUERPOACUERPO:

			CQC();
			//st.update(sto, dt);


			break;

		case FLOCKING:

			emepzarFlocking(dt);
			//st.update(sto, dt);


			break;

    }

	setPos(st.posicion);
	entity->getSombraE2D();
	this->actualizarLista();
	GVida->setPosition(st.posicion);
	RVida->setPosition(vector3df(st.posicion.X - 8, st.posicion.Y, st.posicion.Z));


}

/*void CriaAlien::Mover(int modo) {


}*/
void CriaAlien::emepzarFlocking(f32 dt) {

	maya->getMaterial(0).EmissiveColor.set(0, 125, 50, 175);
	vector3df u;
	float maxAngularAcceleration = MULTIVEL * 2.5;

	//vector3df v(0, 0, 0);
	 if (time < 1.5f) {

		u = floc->cohesion(entity);
		sto.linear = u * maxAngularAcceleration;
		Mover();

	 }

	 else {

		u = floc->separacion(entity);
		sto.linear = u * maxAngularAcceleration;
		Mover();

		u = floc->alineacion(entity);
		sto.linear = u * maxAngularAcceleration;
		Mover();
	
	 }

	 

	 time += dt;

	//if (time > 5.0) {

		//u = floc->alineacion(entity);
		//vectorUnitario += u;
		//u = floc->cohesion(entity);
		//vectorUnitario = u;
		//u = floc->separacion(entity);
		//vectorUnitario += u;
		//time = 0.0f;
	//}
	//time += dt;
	//Mover(u);


}

void CriaAlien::CQC() {

	maya->getMaterial(0).EmissiveColor.set(0, 10, 250, 150);
	vector3df posPlayer;
	posPlayer.X = posJugador.X;
	posPlayer.Y = 0.0f;
	posPlayer.Z = posJugador.Y;
	//dir = path->getDireccion(pos, posPlayer);
	//this->Mover(dir);

	//vectorUnitario = path->getVectorDeDireccion(pos, posPlayer);
	seek(posPlayer);


	if (path->estoyEnElNodo(pos, posPlayer)) {
		dir = -1;
		this->setVelocidad();



		/*posNodo = path->buscarWaypointMasCorto(posNodo);
		puntoFin = waypoints->getNodoX(posNodo);*/

	}


	iniLogicaDifusa();

}

void CriaAlien::Patrullar() {

	maya->getMaterial(0).EmissiveColor.set(0, 15, 0, 200);



	if (puntoFin == nullptr) {
	
		posNodo = path->buscarWaypointMasCorto(posNodo);

		if (posNodo != -1) {
			puntoFin = waypoints->getNodoX(posNodo);


		}

		if(nodoAnterior == puntoFin) {

		
			posNodo = path->buscarWaypointNoRepetido(puntoFin->getLugarDelNodo(), puntoIni->getLugarDelNodo());
			puntoFin = waypoints->getNodoX(posNodo);


		}

		/*std::cout << std::endl;
		std::cout << "NOMBRE DEL DESTINO: " << this->puntoFin->getNombre() << std::endl;*/

	}

	else if (puntoFin != nullptr) {



		//vectorUnitario = path->getVectorDeDireccion(pos, puntoFin->getPosicion());


		//Mover(vectorUnitario);

		if (path->distanciaEntreElNodoYEne(st.posicion, puntoFin->getPosicion()) < 30.0f) {

			arrive(puntoFin->getPosicion());
			//Mover(vectorUnitario);
			if (path->distanciaEntreElNodoYEne(st.posicion, puntoFin->getPosicion()) < 10.0f
				|| path->distanciaEntreElNodoYEne(st.posicion, puntoFin->getPosicion()) < 20.0f)
			{

				dir = -1;
				//this->setVelocidad();

				nodoAnterior = puntoIni;
				puntoIni = puntoFin;
				puntoFin = nullptr;
			}
		}

		else {
			seek(puntoFin->getPosicion());
		}
	

		//if (path->estoyEnElNodo(pos, puntoFin->getPosicion())) {

		//	dir = -1;
		//	this->setVelocidad();
		//
		//	nodoAnterior = puntoIni;
		//	puntoIni = puntoFin;
		//	puntoFin = nullptr;

		//	/*posNodo = path->buscarWaypointMasCorto(posNodo);
		//	puntoFin = waypoints->getNodoX(posNodo);*/

		//}


	}

	/*std::cout << std::endl;
	std::cout << "PATRULLO PREMO!" << std::endl;
	std::cout << std::endl;*/


}

void CriaAlien::Atacar(f32 dt)
{
	maya->getMaterial(0).EmissiveColor.set(0, 255, 50, 0);
	/*		std::cout << std::endl;
	std::cout << "CRIA ALIEN" << std::endl;
	std::cout << "POS X: " << posJugador.X << "POS Y(Z): " << posJugador.Y << std::endl;
	std::cout << std::endl;*/

	if (disparado == false) {

		this->disparar(dt); //donde crea la bala

	}


	if (disparado == true) {
		this->aumentarTiempoDisparo(dt);
		if (this->getTiempoDisparo() >= 0.7f) {
			this->setDisparo(false);
			this->resetTiempoDisparo();
		}
	}

	this->setVelocidad();
	iniLogicaDifusa();

}

void CriaAlien::BuscarWaypoint()
{
	maya->getMaterial(0).EmissiveColor.set(0, 0, 200, 10);

	if (puntoIni == nullptr) {
		posNodo = path->buscarWaypointCercano(st.posicion, waypoints->getNodos());

		if(posNodo != -1) {
			puntoIni = waypoints->getNodoX(posNodo);
		}

		//	std::cout << std::endl;
		//std::cout << "NOMBRE: " << this->puntoIni->getNombre() << std::endl;
		//std::cout << "POS NODO: " << posNodo << std::endl;
	}



	if (puntoIni != nullptr) {

		//vectorUnitario = path->getVectorDeDireccion(pos, puntoIni->getPosicion());

	//	std::cout << "DISTANSIA QUE ME FUMO PARA LLEGAR AL NODO: " << path->distanciaEntreElNodoYEne(pos, puntoIni->getPosicion()) << std::endl;

		if (path->distanciaEntreElNodoYEne(st.posicion, puntoIni->getPosicion()) < 50.0f) {

			arrive(puntoIni->getPosicion());
		//std::cout << "DISTANSIA QUE ME FUMO PARA LLEGAR AL NODO: " << path->distanciaEntreElNodoYEne(pos, puntoIni->getPosicion()) << std::endl;

			//Mover(vectorUnitario);
			if (path->distanciaEntreElNodoYEne(st.posicion, puntoIni->getPosicion()) < 10.0f
				|| path->distanciaEntreElNodoYEne(st.posicion, puntoIni->getPosicion()) < 20.0f
				|| path->estoyEnElNodo(st.posicion, puntoIni->getPosicion()))
			{
		
					estadoActual = PATRULLAR;

					dir = -1;
					//this->setVelocidad();
	
			}
		}

		else {
			seek(puntoIni->getPosicion());
		}
		//if (path->estoyEnElNodo(pos, puntoIni->getPosicion())) {
		//	estadoActual = PATRULLAR;

		//	dir = -1;
		//	this->setVelocidad();

		//}
	}
}

void CriaAlien::quitarVida(float damage) {

    std::cout << "CRIA ALIEN" << std::endl;

    vida = vida - (damage - blindaje);
	moral = moral - (damage * 0.35 - blindaje);
	if (moral < 0.0f)
		moral = 0.0f;

	resistencia = resistencia - damage * 0.35;

	vel = vel - resistencia * 0.15f;

	if (resistencia < 0.0f)
		resistencia = 0.0f;

    irr::core::stringw wideString(vida);
    GVida->setText(wideString.c_str());

    std::cout << vida << std::endl;
}

void CriaAlien::recuperarResistencia()
{
	maya->getMaterial(0).EmissiveColor.set(0, 250, 200, 10);

	vida += 0.001f;
	resistencia += 0.001f;
	irr::core::stringw wideString(vida);
	GVida->setText(wideString.c_str());
	
}
