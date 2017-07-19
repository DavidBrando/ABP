/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   MyContactFilter.cpp
* Author: David
*
* Created on 17 de diciembre de 2016, 18:13
*/
#include <Box2D\Box2D.h>
#include <iostream>
#include "Entity2D.h"
#include "MyContactFilter.h"
//#include "../Escenario/readJson.h"


MyContactFilter::MyContactFilter() {
}

MyContactFilter::MyContactFilter(const MyContactFilter& orig) {
}

MyContactFilter::~MyContactFilter() {
}

bool MyContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {


	/*#define FILTRO_PERSONAJE 1
	#define FILTRO_PARED 2
	#define FILTRO_PUERTA 3
	#define FILTRO_DISPAROPERS 4
	#define FILTRO_DISPAROENE 5
	#define FILTRO_ENEMIGO 6
	15 puerta abierta*/

	//    if(fixtureA != NULL && fixtureB != NULL){
	//    
	//    const b2Filter& f1 = fixtureA->GetFilterData();
	//    const b2Filter& f2 = fixtureB->GetFilterData();
	//    bool colision = false;
	// 
	//    //colisiones de player
	//    if(f1.groupIndex == 1 || f2.groupIndex == 1){
	//        if(f2.groupIndex == 2 || f2.groupIndex == 3 || f2.groupIndex == 5 ||f2.groupIndex == 6 ||
	//                f1.groupIndex == 2 || f1.groupIndex == 3 || f1.groupIndex == 5 ||f1.groupIndex == 6){
	//           // std::cout<<"ENTRO CON 1"<<std::endl;
	//           // colision = (f1.maskBits & f2.categoryBits) != 0 && (f1.categoryBits & f2.maskBits) != 0;
	//                    colision = true;
	//                    return colision;
	//            
	//        }
	//    }
	//    //colisiones de bala
	//    else if(f1.groupIndex == 4 || f2.groupIndex == 4){
	//        if(f1.groupIndex == 2 || f1.groupIndex == 3 || f1.groupIndex == 5 || f1.groupIndex == 6 
	//                || f2.groupIndex == 2 || f2.groupIndex == 3 || f2.groupIndex == 5 || f2.groupIndex == 6){
	//                       // std::cout<<"ENTRO CON 4"<<std::endl;
	//
	////             colision = (f1.maskBits & f2.categoryBits) != 0 && (f1.categoryBits & f2.maskBits) != 0;
	//                     colision = true;
	//                     
	//                    return colision;
	//
	//        }
	//       
	//    }
	//    //colisiones de enemigo
	//    else if(f1.groupIndex == 6 || f2.groupIndex == 6){
	//        if(f1.groupIndex == 2 || f1.groupIndex == 3 || f1.groupIndex == 4 ||  f1.groupIndex == 1
	//                || f2.groupIndex == 2 || f2.groupIndex == 3 || f2.groupIndex == 4 || f2.groupIndex == 1){
	//            colision = true;
	//            return colision;
	//        }
	//    }
	//    
	//    else if((f1.groupIndex == 1 && f2.groupIndex == 4) || (f1.groupIndex == 4 && f2.groupIndex == 1)){      
	//                    std::cout<<"BALA"<<std::endl;
	//
	//
	//        colision = false;
	//                            return colision;
	//
	////       colision = (f1.maskBits & f2.categoryBits) != 0 && (f1.categoryBits & f2.maskBits) != 0;
	//    } 
	//    
	//    return colision;
	//    
	//    }
	//    return false;

	/*#define FILTRO_PERSONAJE 1
	#define FILTRO_PARED 2
	#define FILTRO_PUERTA 3
	#define FILTRO_DISPAROPERS 4
	#define FILTRO_DISPAROENE 5
	#define FILTRO_ENEMIGO 6
	15 puerta abierta*/

	if (fixtureA != NULL && fixtureB != NULL) {

		const b2Filter& f1 = fixtureA->GetFilterData();
		const b2Filter& f2 = fixtureB->GetFilterData();

		//Entity2D *e1 = static_cast<Entity2D*>(fixtureA->GetUserData());
		//Entity2D *e2 = static_cast<Entity2D*>(fixtureB->GetUserData());


		//colision entre bala y personaje
		if ((f1.groupIndex == 1 && f2.groupIndex == 4) || (f1.groupIndex == 4 && f2.groupIndex == 1)) { return false; }
		if ((f1.groupIndex == 6 && f2.groupIndex == 5) || (f1.groupIndex == 5 && f2.groupIndex == 6)) { return false; }
	//	if (f1.groupIndex == f2.groupIndex ) { return false; }

		//colisiones de la puerta abierta
		if (f1.groupIndex == 15 || f2.groupIndex == 15) {

			if (f1.groupIndex == 1 || f2.groupIndex == 1) { return false; }
			else if (f1.groupIndex == 4 || f2.groupIndex == 4) { return false; }
			else if (f1.groupIndex == 6 || f2.groupIndex == 6) { return false; }


		}
		if ((f1.groupIndex == 1 && f2.groupIndex == 7) || (f1.groupIndex == 7 && f2.groupIndex == 1)) { return true; }
	

		//if (e1->getIDENSH() == 1 && e2->getIDENSH() == 1) { return false; }

		return true;

	}

	return false;
}