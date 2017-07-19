/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   MiContactListener.cpp
* Author: David
*
* Created on 7 de diciembre de 2016, 11:27
*/
#include <Box2D\Box2D.h>
#include <iostream>
#include <math.h>
#include "../Escenario/Puerta.h"
#include "MiContactListener.h"
#include "../Jugador/Personaje.h"
#include "../Enemigos/Enemigo.h"
#include "Entity2D.h"
#include "../Escenario/Terminal.h"
#include "../Jugador/Inventario.h"
#include "../Escenario/ObjConsumables/Botiquines.h"
#include "../Escenario/ObjConsumables/Llave.h"
#include "../Escenario/ObjConsumables/TiposDeMunicion/MunicionSubfusil.h"
#include "../Escenario/ObjConsumables/TiposDeMunicion/MunicionEscopeta.h"
#include "../Escenario/ObjConsumables/TiposDeMunicion/MunicionPistola.h"
#include "../Jugador/Bala.h"
#include "../Enemigos/Nodo.h"


MiContactListener::MiContactListener() {
	terActivado = false;
}

MiContactListener::MiContactListener(const MiContactListener& orig) {
}

MiContactListener::~MiContactListener() {
}

void MiContactListener::actualizarPuerta(Entity2D* entity, Entity2D *pers, int modo) {
	std::cout << "ACTUALIZO " << modo << std::endl; 

	Puerta *puerta = static_cast<Puerta*>(entity->getObjeto3D());

	std::cout << "ID PUERTA: " << entity->getId() << std::endl;
	/*if (pers->getIDEN() == 0)
		Personaje *p = static_cast<Personaje*>(pers->getObjeto3D());*/

	if (modo == 0 && puerta->getEstado() != "BLOQLLAVE" ) {
		//si tiene rotacion en Y van | sino van -
		puerta->setDetectado(true,entity->getId());
		puerta->UpdateEstado();
	}	


	else if (modo == 1 && puerta->getEstado() != "BLOQLLAVE") {
		std::cout << "cerrar123" << std::endl;
		puerta->setDetectado(false,entity->getId());
		puerta->UpdateEstado();
	}

	//se deberia hacer un if para ver si el jugador tiene o no la llave asociada a la puerta
	//con la que ha colisionado. Tambien se deberia pasar al jugador para gestionar las
	//llaves que ha cogido

	else if(puerta->getEstado() == "BLOQLLAVE" && pers->getIDEN() == 0){

		Personaje *p = static_cast<Personaje*>(pers->getObjeto3D());
		if(p->getTeclaE() == true) {
			std::cout << "-----NOMBRE LLAVE: " << puerta->getLlaveAsociada() << std::endl;
			Llave *llave = p->getInventario()->buscaLlave(puerta->getLlaveAsociada());

			if (llave == nullptr)
				std::cout << "CACOTA" << std::endl;

			if(llave != nullptr) {
				puerta->setDetectado(true, entity->getId());

				puerta->UpdateEstado();


			}
		}

	}

}

void MiContactListener::aplicarDamage(Entity2D* entity, Entity2D *bala) {

	Enemigo *ene = static_cast<Enemigo*>(entity->getObjeto3D()); //mirar el tema de hacer un cast dependiendo de la raza
	Bala *bullet = static_cast<Bala*>(bala->getObjeto3D());
	if (ene->getVida() > 0.0f) {
		ene->quitarVida(bullet->getDamage());
		if (ene->getVida() <= 0.0f) {
			entity->setLive(false);
		}
	}
}

void MiContactListener::activarTerminar(Entity2D * pers, Entity2D * terminal, bool actTer)
{
	
	Personaje *personaje = static_cast<Personaje*>(pers->getObjeto3D());
	Terminal *ter = static_cast<Terminal*>(terminal->getObjeto3D());
	if (actTer==true)
	{
		if (terActivado==false)
		{
			if (personaje->getTeclaE() == true) {

				if (ter->getEstado() == false) {
					ter->cambiarEstado(true);
					ter->cambiarColor();
					pers->setLive(false);
					terActivado=true;
					personaje->setTeclaE(false);
				}

			}
		}
		else
		{
			ter->cambiarColor();
			/* DESACTIVACIÓN POR DELTA TIME
			if (personaje->getTeclaE() == true) {

				ter->cambiarEstado(false);
				ter->cambiarColor();
				terActivado = false;

			}*/
		}
	}

}

void MiContactListener::gestionarObjeto(Entity2D * pers, Entity2D * objeto, int tipo)
{

	switch (tipo)
	{
		//para copiar el objeto
		/*A *temClass = new A(10);
A *myClass01 = new A(*temClass);
A *myclass02 = new A(*temClass);
*/


	case 2:

		aumentarMunicionPistola(pers, objeto);

		break;

	case 3:
		aumentarMunicionSubfusil(pers, objeto);

		break;

	case 4:
		aumentarMunicionEscopeta(pers, objeto);

		break;


	default:
		addObjetoAlInventario(pers, objeto, tipo);
		break;
	}
	objeto->setLive(false);
}

void MiContactListener::aumentarMunicionPistola(Entity2D * pers, Entity2D * munPistola)
{
	std::cout << "" << std::endl;

	std::cout << "////////////////////////" << std::endl;
	std::cout << "AUMENTAR MUNICION DE PISTOLA" << std::endl;

	std::cout << "////////////////////////" << std::endl;
	std::cout << "" << std::endl;

	Personaje *personaje = static_cast<Personaje*>(pers->getObjeto3D());
	MunicionPistola *mun = static_cast<MunicionPistola*>(munPistola->getObjeto3D());

	personaje->cogerMunicion(mun->getMunicion(), 0);
//	munPistola->setLive(false);

}

void MiContactListener::aumentarMunicionSubfusil(Entity2D * pers, Entity2D * munSubfisul)
{
	std::cout << "" << std::endl;

	std::cout << "////////////////////////" << std::endl;
	std::cout << "AUMENTAR MUNICION DE SUBFUSIL" << std::endl;

	std::cout << "////////////////////////" << std::endl;
	std::cout << "" << std::endl;

	Personaje *personaje = static_cast<Personaje*>(pers->getObjeto3D());
	MunicionSubfusil *mun = static_cast<MunicionSubfusil*>(munSubfisul->getObjeto3D());

	personaje->cogerMunicion(mun->getMunicion(), 1);
	//munSubfisul->setLive(false);
}

void MiContactListener::aumentarMunicionEscopeta(Entity2D * pers, Entity2D * munEscopeta)
{
	std::cout << "" << std::endl;

	std::cout << "////////////////////////" << std::endl;
	std::cout << "AUMENTAR MUNICION DE ESCOPETA" << std::endl;

	std::cout << "////////////////////////" << std::endl;
	std::cout << "" << std::endl;

	Personaje *personaje = static_cast<Personaje*>(pers->getObjeto3D());
	MunicionEscopeta *mun = static_cast<MunicionEscopeta*>(munEscopeta->getObjeto3D());

	personaje->cogerMunicion(mun->getMunicion(), 2);
//	munEscopeta->setLive(false);
}

void MiContactListener::addObjetoAlInventario(Entity2D * pers, Entity2D * objeto, int tipo)
{
	Personaje *personaje = static_cast<Personaje*>(pers->getObjeto3D());

	if(tipo == 0) {

		Botiquines *bot = new Botiquines(*static_cast<Botiquines*>(objeto->getObjeto3D()));
		//bot->setFisica(objeto->getCuerpo2D()->GetWorld());
		personaje->getInventario()->addObjeto(bot);
	}

	else {
		Llave *llave = new Llave(*static_cast<Llave*>(objeto->getObjeto3D()));
		//llave->setFisica(objeto->getCuerpo2D()->GetWorld());

		personaje->getInventario()->addObjeto(llave);
	}

}


void aplicarKnockBack(Entity2D *pers, Entity2D *enemigo, b2Body *bodyPers) {

	Personaje *p = static_cast<Personaje*>(pers->getObjeto3D());
	Enemigo *e = static_cast<Enemigo*>(enemigo->getObjeto3D());
	int dir = p->getDireccion();
	float vel = 50000.0f;
	//std::cout << "VELOSIDAD X: " << vel.x << "VELOSIDAD Y: " << vel.y << std::endl;

/*	std::cout << "//////////////////////////////////////////" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "POS PERS ANTES" << std::endl;
	std::cout << "Pos 3D X: " << p->getPos().X << "Pos 3D Z: " << p->getPos().Z << std::endl;
	std::cout << "Pos 2D X: " << bodyPers->GetPosition().x << "Pos 2D Z: " << bodyPers->GetPosition().y << std::endl;
	*/

	std::cout << "//////////////////////////////////////////" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "VIDA: " <<p->getVida()<< std::endl;
	std::cout << "" << std::endl;
	std::cout << "//////////////////////////////////////////" << std::endl;

	p->setImpulso(true);
	p->iniciarTiempoImpulso();
	p->quitarVida(e->getDamageChoque());

	switch (dir) {

	case 0:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(-vel, 0.0f), true);

	break;

	case 1:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(vel, 0.0f), true);


	break;

	case 2:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -vel), true);


	break;

	case 3:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(0.0f, vel), true);

	break;

	case 4:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(-vel, -vel), true);


	break;

	case 5:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(-vel, vel), true);


	break;

	case 6:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(vel, vel), true);


	break;

	case 7:

		bodyPers->ApplyLinearImpulseToCenter(b2Vec2(vel, -vel), true);


	break;




	}


	//p->actualizarPosicion();

	/*    std::cout<<"//////////////////////////////////////////"<<std::endl;
	            std::cout<<""<<std::endl;
	            std::cout<<"POS PERS DESPUES"<<std::endl;
	                 std::cout<<"Pos 3D X: "<<p->getPos().X<<"Pos 3D Z: "<< p->getPos().Z<<std::endl;
	                 std::cout<<"Pos 2D X: "<<bodyPers->GetPosition().x<<"Pos 2D Z: "<< bodyPers->GetPosition().y<<std::endl;
*/
	if(p->getVida() <= 0.0f && pers->getLive() != false) {
		//p->pasarMensaje();
	}

}


void atacarJugador(Entity2D *pers, Entity2D *enemigo) {

	Personaje *p = static_cast<Personaje*>(pers->getObjeto3D());
	Enemigo *e = static_cast<Enemigo*>(enemigo->getObjeto3D());

	//if (e->getVista() == false) {
		float pesoX = powf(p->getPos().X - e->getPos().X, 2);
		float pesoZ = powf(p->getPos().Z - e->getPos().Z, 2);
		float peso = sqrtf((pesoX + pesoZ));

		p->getPos();
		e->setPesoMaximoLogicaDifusa(peso);
		e->setPosJugador(p->getPos().X, p->getPos().Z);
		//e->setEstado(3);
		e->iniLogicaDifusa();
		//std::cout << std::endl;
		//std::cout <<"CALLBACK"<< std::endl;

		//std::cout << "POS X: " << p->getPos().X<<"POS Z: " << p->getPos().Z<< std::endl;
		//std::cout << std::endl;



		std::cout << std::endl;
		std::cout << "DISTANCIA ENTRE ENEMIGO Y JUGADOR" << std::endl;

		std::cout << "DISTANCIA: " << peso << std::endl;
		std::cout << std::endl;

	//}

}

void gestionarCambioDeEstadoEnemigo(Entity2D *enemigo) {
	Enemigo *e = static_cast<Enemigo*>(enemigo->getObjeto3D());

	//if (e->getVista() == false) {
		if (e->getNodoInicio() == nullptr || e->getNodoFin() == nullptr || e->getEstado() == 8) {
			e->setEstado(0);
		}

		else if (e->getNodoFin() != nullptr && e->getEstado() != 5) {
			e->setEstado(1);
		}

		else if (e->getEstado() == 5) {
			e->setEstado(5);
		}

		else if (e->getEstado() == 8) {
			if (e->getNodoInicio() != nullptr) {
				e->setEstado(1);
			}
		}

		
	//}

	e->setTime(0.0f);
}


void quitarVidaJugador(Entity2D *jugador, Entity2D *bala) {

	Personaje *j = static_cast<Personaje*>(jugador->getObjeto3D()); //mirar el tema de hacer un cast dependiendo de la raza
	Bala *bullet = static_cast<Bala*>(bala->getObjeto3D());
	if (j->getVida() > 0.0f) {
		j->quitarVida(bullet->getDamage());
		if (j->getVida() <= 0.0f && jugador->getLive() != false) {
		/*	jugador->setLive(false);
			j->pasarMensaje();*/
		}
	}

}


void paredDetectada(Entity2D *ene, bool x) {

	Enemigo *e = static_cast<Enemigo*>(ene->getObjeto3D());

	//e->setVista(x);
	e->setEsquivarPared(x);
	//e->obstacleAvoidance();

}


void empezarFlocking(Entity2D *e1, Entity2D *e2) {

	Enemigo *ene1 = static_cast<Enemigo*>(e1->getObjeto3D());
	Enemigo *ene2 = static_cast<Enemigo*>(e2->getObjeto3D());

	if (ene1->getLider()) {
		//ene2->iniLogicaDifusa();
		//hay que hacer un metodo que me diga su estado de la moral
		//para ver si tiene que activar el flocking o no

	}

	else if(ene2->getLider()) {
		//ene1->iniLogicaDifusa();
	
	}

		ene1->setGrupoFlocking(e1);
		ene1->setGrupoFlocking(e2);

		ene2->setGrupoFlocking(e2);
		ene2->setGrupoFlocking(e1);

		ene1->setVista(true);
		ene2->setVista(true);


}


void eliminarEntityDelVecindario(Entity2D *e1, Entity2D *e2) {

	Enemigo *ene1 = static_cast<Enemigo*>(e1->getObjeto3D());
	Enemigo *ene2 = static_cast<Enemigo*>(e2->getObjeto3D());

	std::cout << "ME MARCHO" << std::endl;

	ene1->deleteEntity(e1);
	ene1->deleteEntity(e2);
	
	ene2->deleteEntity(e2);
	ene2->deleteEntity(e1);

	ene1->setVista(false);
	ene2->setVista(false);

}


void evitarColisionEntreEnemigos(Entity2D *e1, Entity2D *e2) {

	Enemigo *ene1 = static_cast<Enemigo*>(e1->getObjeto3D());
	Enemigo *ene2 = static_cast<Enemigo*>(e2->getObjeto3D());

	//ene1->collisionAvoidance(ene2);
	//ene1->Mover();
}


void MiContactListener::BeginContact(b2Contact* contact) {
	//std::cout<<""<<std::endl;

	//std::cout<<"////////////////////////"<<std::endl;

	//std::cout<<"COLISION"<<std::endl;
	if (contact != NULL) {
		b2Fixture *f1 = contact->GetFixtureA();
		b2Fixture *f2 = contact->GetFixtureB();

		if (f1 != NULL && f2 != NULL) {
			b2Body *b1 = f1->GetBody();
			b2Body *b2 = f2->GetBody();

			void* bodyUserData1 = f1->GetBody()->GetUserData();
			void* bodyUserData2 = f2->GetBody()->GetUserData();

			Entity2D *entity1 = static_cast<Entity2D*>(bodyUserData1);
			Entity2D *entity2 = static_cast<Entity2D*>(bodyUserData2);

			//            Personaje *pers = static_cast<Personaje*>(entity1->getObjeto3D());

		/*	 std::cout<<"ENTIDAD 1: "<<entity1->getIDEN()<<std::endl;
			   std::cout<<"ENTIDAD 2: "<<entity2->getIDEN()<<std::endl;*/
		

			/* int a = *((int*)b1->GetUserData());
			int b = *((int*)b2->GetUserData());
			if(a == 1){
			std::cout<<"Personaje"<<std::endl;

			}*/
			
		/**	std::cout<<"///////////////////////////////////"<<std::endl;
			std::cout<<"POSICION DE LA ENTITY 2"<<std::endl;
			std::cout<<"POS X: "<<entity2->getCuerpo2D()->GetPosition().x<<" POS Y: "<<entity2->getCuerpo2D()->GetPosition().y<<std::endl;
			std::cout<<"///////////////////////////////////"<<std::endl;
			

			std::cout << "Sombra: " << entity1->getIDENSH() << " Elemento: " << entity2->getIDEN() << std::endl;**/


			//            if((entity2->getIDEN()==0 && entity2->getIDEN() == 4)&&(entity2->getIDEN()==4 && entity2->getIDEN() == 0))
			//            {
			//                if(entity1->getSombraE2D() != NULL){
			//                    std::cout<<"MEMORIA: "<<entity1->getSombraE2D()<<std::endl;
			//                    pers->setPos(vector3df(entity1->getSombraE2D()->GetPosition().x,10,entity1->getSombraE2D()->GetPosition().y));
			//                }
			//            }
			//   


			//tema flocking

			if (entity1->getIDEN() == 4 && f1->IsSensor() && entity2->getIDEN() == 4 && !f2->IsSensor() ) {
				empezarFlocking(entity1, entity2);
				//evitarColisionEntreEnemigos(entity1, entity2);
				
			}

			else if (entity2->getIDEN() == 4 && f2->IsSensor() && entity1->getIDEN() == 4 && !f1->IsSensor()) {
				empezarFlocking(entity2, entity1);
				//evitarColisionEntreEnemigos(entity2, entity1);


			}
			
			//cuando el sensor de vista detecta una pared o puerta
			if (entity1->getIDEN() == 4 && f1->IsSensor() && (entity2->getIDEN() == 1 || entity2->getIDEN() == 2)) {
				paredDetectada(entity1, true);
			}

			else if (entity2->getIDEN() == 4 && f2->IsSensor() && (entity1->getIDEN() == 1 || entity1->getIDEN() == 2)) {
				paredDetectada(entity2, true);
			}


			//colisiones con las distintas balas y las paredes = 1 y puertas = 2 de ID balaPlayer = 3 balaEne = 6
			if (entity1->getIDEN() == 3 && entity2->getIDEN() == 2 && f2->IsSensor() != true) {
				entity1->setLive(false);

			}

			else if (entity2->getIDEN() == 3 && entity1->getIDEN() == 2 && f1->IsSensor() != true) {
				entity2->setLive(false);
			}


			if (entity1->getIDEN() == 6 && entity2->getIDEN() == 2 && f2->IsSensor() != true) {
				entity1->setLive(false);

			}

			else if (entity2->getIDEN() == 6 && entity1->getIDEN() == 2 && f1->IsSensor() != true) {
				entity2->setLive(false);
			}


			if((entity1->getIDEN() == 3 || entity1->getIDEN() == 6) && entity2->getIDEN() == 1) {
				entity1->setLive(false);

			}


			else if ((entity2->getIDEN() == 3 || entity2->getIDEN() == 6) && entity1->getIDEN() == 1) {
				entity2->setLive(false);

			}


			//bala de enemigo = 6 choca contra el jugador = 0

			if (entity1->getIDEN() == 6 && entity2->getIDEN() == 0) {
				quitarVidaJugador(entity2, entity1);
				entity1->setLive(false);

			}

			else if (entity2->getIDEN() == 6 && entity1->getIDEN() == 0) {

				quitarVidaJugador(entity1, entity2);
				entity2->setLive(false);
			}

			//el enemigo = 4 detecta al jugador = 0

			if (entity1->getIDEN() == 0 && entity2->getIDEN() == 4 && f2->IsSensor() == true) {
				std::cout << "A DISPARAR!" << std::endl;
				atacarJugador(entity1, entity2);

			}

			else if (entity2->getIDEN() == 0 && entity1->getIDEN() == 4 && f1->IsSensor() == true) {
				std::cout << "A DISPARAR!" << std::endl;
				atacarJugador(entity2, entity1);

			}


			//colision de enemigo y bala
			//3: bala; 4: enemigo
			if (entity1->getIDEN() == 3 && entity2->getIDEN() == 4 && f2->IsSensor() == false) {
				//entity2->setLive(false);
				aplicarDamage(entity2, entity1);
				entity1->setLive(false);
			}

			else if (entity1->getIDEN() == 4 && entity2->getIDEN() == 3 && f1->IsSensor() == false) {
				//entity1->setLive(false);              
				aplicarDamage(entity1, entity2);
				entity2->setLive(false);
			}

			//cuando la bala de enemigo = 6 choca contra el jugador = 0
			if (entity1->getIDEN() == 0 && entity2->getIDEN() == 6) {
				//entity2->setLive(false);
				
				entity2->setLive(false);
			}

			else if (entity1->getIDEN() == 6 && entity2->getIDEN() == 0) {
				//entity1->setLive(false);              
				
				entity1->setLive(false);
			}

			

			if (entity1->getIDEN() == 2 && (entity2->getIDEN() == 0 || entity2->getIDEN() == 4) && f1->IsSensor() == true && f2->IsSensor() != true) {
				actualizarPuerta(entity1, entity2, 0);
			}

			else if (entity2->getIDEN() == 2 && (entity1->getIDEN() == 0 || entity1->getIDEN() == 4) && f2->IsSensor() == true && f1->IsSensor() != true) {
				actualizarPuerta(entity2, entity1, 0);
			}


			//if de los objetos consumables
			if (entity1->getIDEN() == 0 
				&& entity2->getIDEN() == 5 
				&& entity2->getId() != 5
				&& f2->IsSensor() == true) {
				
				gestionarObjeto(entity1, entity2, entity2->getId());
				
			}

		/*	else if (entity2->getIDEN() == 0 && entity1->getIDEN() == 5 && f1->IsSensor() == true) {
				std::cout << "HOLA PAPITO 2" << std::endl;
			}*/

		}
	}
}

void MiContactListener::EndContact(b2Contact* contact) {
	// std::cout<<"SALGO"<<std::endl;
	if (contact != NULL) {
		b2Fixture *f1 = contact->GetFixtureA();
		b2Fixture *f2 = contact->GetFixtureB();

		if (f1 != NULL && f2 != NULL) {
			b2Body *b1 = f1->GetBody();
			b2Body *b2 = f2->GetBody();

			void* bodyUserData1 = f1->GetBody()->GetUserData();
			void* bodyUserData2 = f2->GetBody()->GetUserData();

			Entity2D *entity1 = static_cast<Entity2D*>(bodyUserData1);
			Entity2D *entity2 = static_cast<Entity2D*>(bodyUserData2);
			/*
			std::cout<<"ENTIDAD 1: "<<entity1->getIDEN()<<std::endl;
			std::cout<<"ENTIDAD 2: "<<entity2->getIDEN()<<std::endl;

			int a = *((int*)b1->GetUserData());
			int b = *((int*)b2->GetUserData());
			if(a == 1){
			std::cout<<"Personaje"<<std::endl;

			}*/
			//            std::cout<<"///////////////////////////////////"<<std::endl;
			//            std::cout<<"POSICION DE LA ENTITY 2"<<std::endl;
			//            std::cout<<"POS X: "<<entity2->getCuerpo2D()->GetPosition().x<<" POS Y: "<<entity2->getCuerpo2D()->GetPosition().y<<std::endl;
			//            std::cout<<"///////////////////////////////////"<<std::endl;
		

			if (entity1->getIDEN() == 4 && f1->IsSensor() && (entity2->getIDEN() == 1 || entity2->getIDEN() == 2)) {
				paredDetectada(entity1, false);
			}

			else if (entity2->getIDEN() == 4 && f2->IsSensor() && (entity1->getIDEN() == 1 || entity1->getIDEN() == 2)) {
				paredDetectada(entity2, false);
			}


			if (entity1->getIDEN() == 2 && entity2->getIDEN() == 0 && f1->IsSensor() == true) {
				std::cout << "lalal 1" << std::endl;

				actualizarPuerta(entity1, entity2, 1);
			}

			else if (entity2->getIDEN() == 2 && entity1->getIDEN() == 0 && f2->IsSensor() == true) {
				std::cout << "lalal 2" << std::endl;
				actualizarPuerta(entity2, entity1, 1);
			}

			//if (entity1->getIDEN() == 0 && entity2->getIDEN() == 4) {
			//	//aplicarKnockBack(entity1, b1);
			//	Personaje *p = static_cast<Personaje*>(entity1->getObjeto3D());
			//	p->setImpulso(false);

			//}

			if ((entity1->getIDEN() == 4 && f1->IsSensor()) && entity2->getIDEN() == 4) {
				gestionarCambioDeEstadoEnemigo(entity1);
			}

			else if ((entity2->getIDEN() == 4 && f2->IsSensor()) && entity1->getIDEN() == 4) {
				gestionarCambioDeEstadoEnemigo(entity2);

			}


			if (entity1->getIDEN() == 0 && entity2->getIDEN() == 4 && f2->IsSensor() == true) {
				std::cout << "ADIOS 1" << std::endl;
				gestionarCambioDeEstadoEnemigo(entity2);

			}


			if (entity1->getIDEN() == 4 && f1->IsSensor() && entity2->getIDEN() == 4 && !f2->IsSensor()) {
				eliminarEntityDelVecindario(entity1, entity2);
			}

			else if (entity2->getIDEN() == 4 && f2->IsSensor() && entity1->getIDEN() == 4 && !f1->IsSensor()) {
				eliminarEntityDelVecindario(entity2, entity1);

			}

			

		}
	}
}

void MiContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	//std::cout<<""<<std::endl;

	//std::cout<<"////////////////////////"<<std::endl;

	//std::cout<<"COLISION"<<std::endl;
	if (contact != NULL) {

		b2Fixture *f1 = contact->GetFixtureA();
		b2Fixture *f2 = contact->GetFixtureB();

		if (f1 != NULL && f2 != NULL) {

			b2Body *b1 = f1->GetBody();
			b2Body *b2 = f2->GetBody();

			void* bodyUserData1 = f1->GetBody()->GetUserData();
			void* bodyUserData2 = f2->GetBody()->GetUserData();

			Entity2D *entity1 = static_cast<Entity2D*>(bodyUserData1);
			Entity2D *entity2 = static_cast<Entity2D*>(bodyUserData2);
			/*
			std::cout<<"ENTIDAD 1: "<<entity1->getIDEN()<<std::endl;
			std::cout<<"ENTIDAD 2: "<<entity2->getIDEN()<<std::endl;


			if(entity1->getIDEN() == 0){
			
			}

			else if(entity2->getIDEN() == 0){
		

			}*/


			if (entity1->getIDEN() == 0 && entity2->getIDEN() == 5)
			{
				this->activarTerminar(entity1, entity2, true);

			}

			if (entity1->getIDEN() == 2 && (entity2->getIDEN() == 0 || entity2->getIDEN() == 4)) {
				actualizarPuerta(entity1, entity2, 0);
			}

			else if (entity2->getIDEN() == 2 && (entity1->getIDEN() == 0 || entity1->getIDEN() == 4)) {
				actualizarPuerta(entity2, entity1, 0);
			}
	
			/*if (entity1->getIDEN() == 0 && entity2->getIDEN() == 5 && f2->IsSensor() == true) {
				
				this->activarTerminar(entity1, entity2);
			}*/

			//if (entity1->getIDEN() == 0 && entity2->getIDEN() == 4 ) {
			//	std::cout << "A DISPARAR!" << std::endl;
			//	dispararEnemigo(entity1, entity2);

			//}


		}

	}

}

void MiContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	if (contact != NULL) {

		b2Fixture *f1 = contact->GetFixtureA();
		b2Fixture *f2 = contact->GetFixtureB();

		if (f1 != NULL && f2 != NULL) {

			b2Body *b1 = f1->GetBody();
			b2Body *b2 = f2->GetBody();

			void* bodyUserData1 = f1->GetBody()->GetUserData();
			void* bodyUserData2 = f2->GetBody()->GetUserData();

			Entity2D *entity1 = static_cast<Entity2D*>(bodyUserData1);
			Entity2D *entity2 = static_cast<Entity2D*>(bodyUserData2);

			/*     std::cout<<"ENTIDAD 1: "<<entity1->getIDEN()<<std::endl;
			std::cout<<"ENTIDAD 2: "<<entity2->getIDEN()<<std::endl;


			if(entity1->getIDEN() == 0){
			
			}

			else if(entity2->getIDEN() == 0){
			

			}*/

			if (entity1->getIDEN() == 0 && entity2->getIDEN() == 4) {
				aplicarKnockBack(entity1, entity2, b1);

			}

		}

	}
}





