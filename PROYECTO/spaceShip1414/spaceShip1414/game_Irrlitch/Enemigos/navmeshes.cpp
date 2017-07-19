/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   navmeshes.cpp
* Author: User
*
* Created on 6 de febrero de 2017, 17:11
*/

#include "navmeshes.h"
#include "../Escenario/Escenario.h"
#include "../Escenario/Pared.h"


navmeshes::navmeshes(int grid, Escenario* esce) {

	tamGrid = grid;
	tam = esce->getTam();

	matriz = new int*[tam];
	matriz2 = new float*[tam / grid];
	matriz3 = new char*[tam / grid];

	for (int i = 0; i < tam; i++) {
		matriz[i] = new int[tam];
	}

	for (int i = 0; i < tam / grid; i++) {
		matriz2[i] = new float[tam / grid];
	}

	for (int i = 0; i < tam / grid; i++) {
		matriz3[i] = new char[tam / grid];
	}

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {

			matriz[i][j] = 0;
		}
	}

	for (int i = 0; i < tam / grid; i++) {
		for (int j = 0; j < tam / grid; j++) {

			matriz2[i][j] = 0;
		}
	}

	for (int i = 0; i < tam / grid; i++) {
		for (int j = 0; j < tam / grid; j++) {

			matriz3[i][j] = 'o';
		}
	}

}

navmeshes::navmeshes(const navmeshes& orig) {
}

navmeshes::~navmeshes() {

	for (int i = 0; i < tam; i++) {
		delete[] matriz[i];
	}

	for (int i = 0; i < tam / tamGrid; i++) {
		delete[] matriz2[i];
	}

	//delete[] matriz;
	delete[] matriz2;
}

void navmeshes::muestraGrafo() {
	std::cout << "//////////////////" << std::endl;
	/*
	FILE* fp = fopen("matriz.txt", "wb");


	for (int i = 0; i < tam; i++) {
	for (int j = 0; j < tam; j++) {
	//            std::cout << matriz[i][j] << ", ";
	char Cadena[10];
	sprintf(Cadena, "%d", matriz[i][j]);
	fprintf(fp, Cadena);
	fprintf(fp, " ");

	}
	fprintf(fp, "\n");
	//        std::cout << ";" << std::endl;
	}
	*/

	for (int i = 0; i < tam / tamGrid; i++) {
		for (int j = 0; j < tam / tamGrid; j++) {
			std::cout << matriz2[i][j] << ", ";
			if (j == (tam / tamGrid) - 1)
			{
				std::cout << "" << std::endl;
			}
		}
		//fprintf(fp, "\n");
		//        std::cout << ";" << std::endl;
	}

	std::cout << "//////////////////" << std::endl;
}

void navmeshes::setColisiones(std::list<Pared*> paredes) {
	int cont = 0;
	std::cout << "MOSTRANDO POSICION Y ESCALA" << std::endl;
	std::cout << "//////////////////" << std::endl;
	for (std::list<Pared*>::iterator it = paredes.begin(); it != paredes.end(); it++) {
		cont++;
		std::cout << "---POSICION--- " << cont << std::endl;
		std::cout << "X: " << (*it)->getPosicion().X << std::endl;
		std::cout << "Y: " << (*it)->getPosicion().Y << std::endl;
		std::cout << "Z: " << (*it)->getPosicion().Z << std::endl;

		float diferencia = abs(250 + (*it)->getPosicion().X);
		std::cout << "Negativo X " << diferencia << std::endl;
		float posMatriz;
		if (diferencia != 0)
		{
			posMatriz = diferencia / tamGrid;
		}
		else
		{
			posMatriz = 0;
		}
		std::cout << "Pos Matriz " << posMatriz << std::endl;
		float diferencia2 = 250 + (*it)->getPosicion().Z;
		std::cout << "Negativo Z " << diferencia2 << std::endl;
		float posMatriz2;
		if (diferencia2 != 0)
		{
			posMatriz2 = diferencia2 / tamGrid;
		}
		else
		{
			posMatriz2 = 0;
		}
		std::cout << "Pos Matriz " << posMatriz2 - 1 << std::endl;
		std::cout << "Limite " << tam / tamGrid << std::endl;
		std::cout << "Escala X " << (*it)->getEscala().X << " Escala Y " << (*it)->getEscala().Y << " Escala Z " << (*it)->getEscala().Z << std::endl;
		int x;

		if (posMatriz == 0)
		{
			x = 0;
		}
		else
		{
			x = abs(posMatriz - 1);
		}

		int y;

		if (posMatriz2 == 0)
		{
			y = 0;
		}
		else
		{
			y = abs(posMatriz2 - 1);
		}


		matriz2[x][y] = 1;
		if ((*it)->getRotacion().Y == 90)
		{

			int escala = ((*it)->getEscala().X / 2);
			std::cout << "Escala1 " << escala << std::endl;
			escala = escala * 10;
			std::cout << "Escala2 " << escala << std::endl;
			escala = escala / tamGrid;
			std::cout << "Escala3 " << y + escala << std::endl;
			for (int i = y + 1; i<y + escala + 1; i++)
			{
				matriz2[x][i] = 1;
			}
			escala = escala - 1;
			for (int i = y; i>y - escala - 1; i--)
			{
				matriz2[x][i] = 1;
			}
			//this->muestraGrafo();
		}
		else if ((*it)->getRotacion().Y == 0)
		{

			int escala = ((*it)->getEscala().X / 2);
			std::cout << "Escala1 " << escala << std::endl;
			escala = escala * 10;
			std::cout << "Escala2 " << escala << std::endl;
			escala = escala / tamGrid;
			std::cout << "Escala3 " << y + escala << std::endl;
			for (int i = x + 1; i<x + escala + 1; i++)
			{
				matriz2[i][y] = 1;
			}
			escala = escala - 1;
			for (int i = x; i>x - escala ; i--)
			{
				matriz2[i][y] = 1;
			}
			//this->muestraGrafo();
		}
	/*	this->marchingSquare();
		this->dibujarSquare();*/
	}

	/*
	for (std::list<Pared*>::iterator it = paredes.begin(); it != paredes.end(); it++) {
	if ((*it) != NULL &&  (*it)->getEscala().Y == 2.0f) {
	std::cout<<"POSICION"<<std::endl;
	std::cout<<"X: "<<(*it)->getPosicion().X<<std::endl;
	std::cout<<"Y: "<<(*it)->getPosicion().Y<<std::endl;
	std::cout<<"Z: "<<(*it)->getPosicion().Z<<std::endl;
	//            std::cout<<"//////////////////"<<std::endl;
	//            std::cout<<"//////////////////"<<std::endl;
	//            std::cout<<"ROTACION"<<std::endl;
	//            std::cout<<"X: "<<(*it)->getRotacion().X<<std::endl;
	//            std::cout<<"Y: "<<(*it)->getRotacion().Y<<std::endl;
	//            std::cout<<"Z: "<<(*it)->getRotacion().Z<<std::endl;
	//            std::cout<<"//////////////////"<<std::endl;
	//            std::cout<<"//////////////////"<<std::endl;
	//            std::cout<<"ESCALA"<<std::endl;
	//            std::cout<<"X: "<<(*it)->getEscala().X<<std::endl;
	//            std::cout<<"Y: "<<(*it)->getEscala().Y<<std::endl;
	//            std::cout<<"Z: "<<(*it)->getEscala().Z<<std::endl;
	//            std::cout<<"//////////////////"<<std::endl;
	//            std::cout<<"//////////////////"<<std::endl;
	int x = (*it)->getPosicion().X + tam*0.5, z = (*it)->getPosicion().Z + tam*0.5;

	if(x == 500)
	x--;
	if(z == 500)
	z--;

	//            if (x < 0) {//SI LA X ES NEGATIVA
	//                x += tam;
	//            }
	//
	//            if (z < 0) {//SI LA Z ES NEGATIVA
	//                z += tam;}


	int escala = (*it)->getEscala().X;

	//SI EL OBJETO ESTA ROTADO
	if ((*it)->getRotacion().Y == 90) {//HAY QUE AUMENTAR LAS FILAS Z Y LAS COLUMNAS X SE MANTIENEN
	//                std::cout << " fila z " << z << std::endl;
	//                std::cout << " columna x " << x << std::endl;
	//                std::cout << "  " << std::endl;

	int inicioZ = z - escala * 5;

	int finZ = (z + escala * 5);

	for (inicioZ; inicioZ < finZ; inicioZ++) {
	// matriz[inicioZ][x] = 1;
	matriz2[inicioZ/tamGrid][x/tamGrid]=1;
	}

	} else {//SI EL OBJETO NO ESTA ROTADO, SE AUMENTAN LAS COLUMNAS Y SE MANTIENEN LAS FILAS

	int inicioX = x - escala * 5;

	int finX = (x + escala * 5);

	for (inicioX; inicioX < finX; inicioX++) {
	// matriz[z][inicioX] = 1;
	matriz2[z/tamGrid][inicioX/tamGrid]=1;

	}
	}
	}
	}*/

}

float** navmeshes::getMatriz()
{
	return matriz2;
}

void navmeshes::marchingSquare()
{
	for(int i = 0; i<tam/tamGrid; i++)
	{
		for (int j=0; j<tam/tamGrid; j++)
		{
			if (matriz2[i][j]==1)
			{
				if (i==0 && j==0) //EsquinaSupIzq
				{ 
				
					if (matriz2[i][j]==1&&matriz2[i][j+1]==1&&matriz2[i+1][j]==1&& matriz2[i + 1][j+1] == 0) //caso 13
					{
						matriz3[i][j] = '<';
					}
				}
				
				else if (i==tam/tamGrid-1&&j==tam/tamGrid-1)//EsquinaInfDer
				{
					if (matriz2[i][j] == 1 && matriz2[i][j - 1] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j - 1] == 0) //caso 14
					{
						matriz3[i][j] = '>';
					}
				}

				else if (i==0&&j==tam/tamGrid-1)//EsquinaSupDer
				{
					//std::cout << "entra" << std::endl;
					
					if (matriz2[i][j] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 1 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						
						matriz3[i][j] = '>';
					}
				}	

				else if (i == tam / tamGrid - 1 && j == 0)//EsquinaInfIzq
				{

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j + 1] == 0) //caso 13
					{

						matriz3[i][j] = '<';
					}
				}
				
				else if (i==0)//primera fila
				{
					if (matriz2[i][j] == 1 && matriz2[i][j+1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i+1][j] == 0 && matriz2[i + 1][j+1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i + 1][j - 1] == 1) //caso 13
					{
						matriz3[i][j] = '-';
					}
				}

				else if (j==0)//primera columna
				{
					if (matriz2[i][j] == 1 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j + 1] == 0 && matriz2[i][j + 1] == 0 && matriz2[i + 1][j + 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j + 1] == 1 && matriz2[i][j + 1] == 0 && matriz2[i + 1][j + 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j + 1] == 0 && matriz2[i][j + 1] == 0 && matriz2[i + 1][j + 1] == 1) //caso 13
					{
						matriz3[i][j] = '|';
					}
				}
				else if (j == tam / tamGrid - 1) //ultima columna Der
				{
					if (matriz2[i][j] == 1 && matriz2[i + 1][j] == 1 && matriz2[i-1][j] == 1 && matriz2[i - 1][j-1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j - 1] == 1 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i - 1][j - 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j - 1] == 1) //caso 13
					{
						matriz3[i][j] = '|';
					}
				}
				
				
				else if (i == tam / tamGrid - 1)//ultima fila
				{
					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i - 1][j] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i - 1][j] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 1) //caso 13
					{
						matriz3[i][j] = '-';
					}
				}

				else
				{

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						
						matriz3[i][j] = '>';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{

						matriz3[i][j] = '>';
					}
				
					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{

						matriz3[i][j] = '<';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j+1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i+1][j] == 1 && matriz2[i-1][j] == 1 && matriz2[i+1][j + 1] == 0 && matriz2[i-1][j + 1] == 0 && matriz2[i-1][j - 1] == 0 && matriz2[i+1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 1) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 1 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}
					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 1 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}
					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 1 && matriz2[i - 1][j - 1] == 1 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 1 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 1 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '|';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 1 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 1 && matriz2[i + 1][j - 1] == 1) //caso 13
					{

						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 1 && matriz2[i + 1][j - 1] == 1) //caso 13
					{
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 1 && matriz2[i - 1][j + 1] == 1 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 0 && matriz2[i][j - 1] == 1 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '-';
					}

					if (matriz2[i][j] == 1 && matriz2[i][j + 1] == 1 && matriz2[i][j - 1] == 0 && matriz2[i + 1][j] == 0 && matriz2[i - 1][j] == 0 && matriz2[i + 1][j + 1] == 0 && matriz2[i - 1][j + 1] == 0 && matriz2[i - 1][j - 1] == 0 && matriz2[i + 1][j - 1] == 0) //caso 13
					{
						matriz3[i][j] = '-';
					}
					


					

				}


			}
		}
	}
}


void navmeshes::dibujarSquare()
{
	for (int i = 0; i < tam / tamGrid; i++) {
		for (int j = 0; j < tam / tamGrid; j++) {
			std::cout << matriz3[i][j];
			if (j == (tam / tamGrid) - 1)
			{
				std::cout << "" << std::endl;
			}
		}
	}
}