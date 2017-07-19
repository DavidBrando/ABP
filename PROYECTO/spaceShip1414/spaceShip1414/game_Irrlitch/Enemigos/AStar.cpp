
#include "AStar.h"
#include "Nodo.h"
#include <math.h>


AStar::AStar(float** matrix, int tam)
{
	matriz = matrix;
	tamMatrix = tam;
	actualX, actualZ, anteriorX, anteriorZ = 0.0f;
}


AStar::~AStar()
{
	//for (int i = 0; i < tamMatrix; i++) {
	//	delete[] matriz[i];
	//}

	//delete[] matriz;
	matriz = nullptr;


}

int AStar::buscarWaypointCercano(const vector3df &posEne, const std::vector<Nodo*> &vecNodos)
{
	float min = 10000000;
	int pos = -1;
	for(int i = 0; i < vecNodos.size(); i++) {
		float xi, zi, xf, zf, peso;
		float pesoX, pesoZ;
		xi = posEne.X;
		zi = posEne.Z;
		xf = vecNodos.at(i)->getPosicion().X;
		zf = vecNodos.at(i)->getPosicion().Z;

		pesoX = powf((xf - xi), 2);
		pesoZ = powf((zf - zi), 2);
		peso = pesoX + pesoZ;
		peso = sqrtf(peso);

		if(peso < min) {
			min = peso;
			pos = i;
		}


	}
	//std::cout << "POS WAYPOINT INI: " <<pos<< std::endl;
	return pos;
}

int AStar::buscarWaypointMasCorto(const int &posNodoIni)
{
	float min = 10000000.0f;
	int pos = -1;

	for(int i = 0; i < tamMatrix ; i++) { 
		/*std::cout << "///////////////////////" << std::endl;
		std::cout << "MATRIZ: " << matriz[posNodoIni][i] << std::endl;*/
		if(matriz[posNodoIni][i] != 0 && matriz[posNodoIni][i] != -1 && matriz[posNodoIni][i] < min) {
			
			//std::cout << "MINIMO ANTES: " << min << std::endl;
			

			min = matriz[posNodoIni][i];
			pos = i;
			/*std::cout << "MINIMO DESPUES: " << min << std::endl;
			std::cout << "I: " << i << std::endl;
			std::cout << "///////////////////////" << std::endl;*/
		}

	}
	//std::cout << "POS WAYPOINT MAS CERCANO: " << pos << std::endl;

	return pos;
}

int AStar::buscarWaypointNoRepetido(const int & posWaypointRep, const int & posNodoActual)
{
	float min = 10000000;
	int pos = -1;
	for (int i = 0; i < tamMatrix; i++) {

		if (i != posWaypointRep && matriz[posNodoActual][i] != 0 && matriz[posNodoActual][i] != -1 && matriz[posNodoActual][i] < min) {

			min = matriz[posNodoActual][i];
			pos = i;

		}

	}

	if (pos == -1) {
		pos = posWaypointRep;
	}


	return pos;
}

//devuelve la direccion a donde se tiene que dirigir el enemigo
int AStar::getDireccion(const vector3df &posEne, const vector3df &posNodo)
{
	float xE, zE, xN, zN, vX, vZ;
	xE = posEne.X;	zE = posEne.Z;	xN = posNodo.X; zN = posNodo.Z;
	vX = xN - xE;	vZ = zN - zE;
	actualX = vX; actualZ = vZ;

	this->calcularAnguloDeRotacion();

	anteriorX = actualX;
	anteriorZ = actualZ;


	if (vX < 0) {

		if (vZ > 0) {
			return 7;
		}

		else if (vZ == 0) {
			return 1;
		}

		else if (vZ < 0) {
			return 6;
		}
	}

	else if (vX == 0) {
		
		if (vZ > 0) {
			return 2;
		}

		else if (vZ < 0) {
			return 3;
		}

	}

	else if (vX > 0) {

		if (vZ > 0) {
			return 4;
		}

		else if (vZ == 0) {
			return 0;
		}

		else if (vZ < 0) {
			return 5;
		}
	}


	

}

vector3df AStar::getVectorDeDireccion(const vector3df & posEne, const vector3df & posNodo)
{
	vector3df result = posNodo - posEne;
	
	return result.normalize();
}

bool AStar::estoyEnElNodo(const vector3df &posEne, const vector3df &posNodo)
{
	int xE, zE, xN, zN;
	xE = ceilf(posEne.X);	zE = ceilf(posEne.Z);	xN = ceilf(posNodo.X); zN = ceilf(posNodo.Z);
	/*float xE, zE, xN, zN;
	xE = posEne.X;	zE = posEne.Z;	xN = posNodo.X; zN = posNodo.Z;*/

	if (xE == xN && zE == zN) {
		return true;

	}
	

	return false;
}


float AStar::distanciaEntreElNodoYEne(const vector3df posEne, const vector3df posWaypoint) {


	float dis, x, y;

	x = posWaypoint.X - posEne.X;
	y = posWaypoint.Z - posEne.Z;

	x = powf(x, 2);
	y = powf(y, 2);

	dis = x + y;

	dis = sqrtf(dis);

	return dis;



}

void AStar::calcularAnguloDeRotacion()
{
	float elem1 = actualX * anteriorX + actualZ * anteriorZ;
	float mod1, mod2;
	mod1 = powf(actualX, 2) + powf(actualZ, 2);
	mod2 = powf(anteriorX, 2) + powf(anteriorZ, 2);
	mod1 = sqrtf(mod1);
	mod2 = sqrtf(mod2);

	angulo = elem1 / (mod1 * mod2);

	angulo = acosf(angulo);

	if (isnan(angulo) == 1) {
		angulo = 0.0f;
	}

	//std::cout << std::endl;
	//std::cout << "ANGULO: " << angulo << "º" << std::endl;
	//std::cout << std::endl;
	
}

float AStar::getAnguloDeRotacion()
{

	return angulo;
}









