


#include "LogicaDifusa.h"

//funciones matematicas

float min2valores(float x, float y) {
	
	if (x > y) {
		return y;
	}

	else {
		return x;
	}
}



float max2valores(float x, float y) {

	if (x > y) {
		return x;
	}

	else {
		return y;
	}

}




LogicaDifusa::LogicaDifusa(const float &vidaM, const float moralM, const float resistM)
{
	vidaMax = vidaM;
	moralMax = moralM;
	resistMax = resistM;
	escapar = 0.0f;
	cqc = 0.0f;
	disparar = 0.0f;
	disMax = 0.0f;

}


LogicaDifusa::~LogicaDifusa()
{
}

void LogicaDifusa::fusificador(const float & vidaE, const glm::vec3 & posE, const glm::vec2 & posJ, const float n_moral, const float n_resist)
{
	//vidaJugador = vidaJ;
	vidaEnemigo = vidaE;
	posEnemigo = posE;
	posJugador = posJ;
	resist = n_resist;
	moral = n_moral;
	reiniciarArrays();

	//std::cout << "DATOS" << std::endl;

	//std::cout << "VIDAENEMIGO: " << vidaEnemigo << std::endl;
	//std::cout << "POS ENEMIGO" << std::endl;
	//std::cout << "X: " << posEnemigo.X << " Y: " << posEnemigo.Y << " Z: " << posEnemigo.Z << std::endl;
	//std::cout << "POS JUGADOR" << std::endl;
	//std::cout << "X: " << posJugador.X << " Y: " << posJugador.Y << std::endl;
	//std::cout << "RESIST: " << resist << std::endl;
	//std::cout << "MORAL: " << moral << std::endl;


	//fuzzyficacion de variables (?)
	condiccionesDeLaVidaEnemigo();
	condiccionesDeLaDistancia();
	condiccionesDeLaMoral();
	condiccionesDeLaResistencia();
	sistemaDeInferencia();

}

void LogicaDifusa::baseDeConocimiento()
{
	float aux;
	int m_estado = getEstadoDeLaMoral(); //el estado de la moral se quedo por implementar




	//accion escapar
	if(resultadosDePos[0] > 0.0f && resultadosVidaEnemigo[0] > 0.0f) {

		if (escapar > 0.0f) {
			aux = min2valores(resultadosDePos[0], resultadosVidaEnemigo[0]);
			escapar = max2valores(escapar, aux);
		}

		else {
			escapar = min2valores(resultadosDePos[0], resultadosVidaEnemigo[0]);	
		}

	}


	if (resultadosDePos[1] > 0.0f && resultadosVidaEnemigo[0] > 0.0f) {
		if(escapar > 0.0f) {
			aux = min2valores(resultadosDePos[1], resultadosVidaEnemigo[0]);
			escapar = max2valores(escapar, aux);
		}
		else {
			escapar = min2valores(resultadosDePos[1], resultadosVidaEnemigo[0]);

		}

	}

	if (resultadosDePos[0] > 0.0f && resultadosVidaEnemigo[1] > 0.0f) {

		if (escapar > 0.0f) {
			aux = min2valores(resultadosDePos[0], resultadosVidaEnemigo[1]);
			escapar = max2valores(escapar, aux);
		}

		else {
			escapar = min2valores(resultadosDePos[0], resultadosVidaEnemigo[1]);

		}
	}

	//accion disparar

	if (resultadosDePos[2] > 0.0f && resultadosVidaEnemigo[0] > 0.0f) {
		
		if (disparar > 0.0f) {
			aux = min2valores(resultadosDePos[2], resultadosVidaEnemigo[0]);
			disparar = max2valores(disparar, aux);
		}

		else {
			disparar = min2valores(resultadosDePos[2], resultadosVidaEnemigo[0]);
		}
	}



	if (resultadosDePos[1] > 0.0f && resultadosVidaEnemigo[1] > 0.0f) {

		if (disparar > 0.0f) {
			aux = min2valores(resultadosDePos[1], resultadosVidaEnemigo[1]);
			disparar = max2valores(disparar, aux);
		}

		else {
			disparar = min2valores(resultadosDePos[1], resultadosVidaEnemigo[1]);

		}

	}

	if (resultadosDePos[2] > 0.0f && resultadosVidaEnemigo[1] > 0.0f) {

		if (disparar > 0.0f) {
			aux = min2valores(resultadosDePos[2], resultadosVidaEnemigo[1]);
			disparar = max2valores(disparar, aux);
		}

		else {
			disparar = min2valores(resultadosDePos[2], resultadosVidaEnemigo[1]);

		}

	}


	if (resultadosDePos[1] > 0.0f && resultadosVidaEnemigo[2] > 0.0f) {

		if (disparar > 0.0f) {
			aux = min2valores(resultadosDePos[1], resultadosVidaEnemigo[2]);
			disparar = max2valores(disparar, aux);
		}

		else {
			disparar = min2valores(resultadosDePos[1], resultadosVidaEnemigo[2]);

		}

	}

	if (resultadosDePos[2] > 0.0f && resultadosVidaEnemigo[2] > 0.0f) {

		if (disparar > 0.0f) {
			aux = min2valores(resultadosDePos[2], resultadosVidaEnemigo[2]);
			disparar = max2valores(disparar, aux);
		}

		else {
			disparar = min2valores(resultadosDePos[2], resultadosVidaEnemigo[2]);

		}

	}



	//accion cuerpo a cuerpo

	if (resultadosDePos[0] > 0.0f && resultadosVidaEnemigo[3] > 0.0f) {

		if (cqc > 0.0f) {
			aux = min2valores(resultadosDePos[0], resultadosVidaEnemigo[3]);
			cqc = max2valores(cqc, aux);
		}

		else {
			cqc = min2valores(resultadosDePos[0], resultadosVidaEnemigo[3]);
		}
	}

	if (resultadosDePos[0] > 0.0f && resultadosVidaEnemigo[2] > 0.0f) {

		if (cqc > 0.0f) {
			aux = min2valores(resultadosDePos[0], resultadosVidaEnemigo[2]);
			cqc = max2valores(cqc, aux);
		}

		else {
			cqc = min2valores(resultadosDePos[0], resultadosVidaEnemigo[2]);

		}

	}



	if (resultadosDePos[1] > 0.0f && resultadosVidaEnemigo[3] > 0.0f) {

		if (cqc > 0.0f) {
			aux = min2valores(resultadosDePos[1], resultadosVidaEnemigo[3]);
			cqc = max2valores(cqc, aux);
		}

		else {
			cqc = min2valores(resultadosDePos[1], resultadosVidaEnemigo[3]);

		}

	}

	if (resultadosDePos[2] > 0.0f && resultadosVidaEnemigo[3] > 0.0f) {

		if (cqc > 0.0f) {
			aux = min2valores(resultadosDePos[2], resultadosVidaEnemigo[3]);
			cqc = max2valores(cqc, aux);
		}

		else {
			cqc = min2valores(resultadosDePos[2], resultadosVidaEnemigo[3]);

		}

	}


	//std::cout << "VALORES" << std::endl;
	//std::cout << "ESCAPAR: " << escapar << std::endl;
	//std::cout << "DISPARAR: " << disparar << std::endl;
	//std::cout << "CQC: " << cqc << std::endl;
	//std::cout << "/////////////////////" << std::endl;
}

void LogicaDifusa::desfusificador()
{
	int rAux = 0;
	int mAux = 0;
	rAux = getEstadoDelCansancio();
	mAux = getEstadoDeLaMoral();
	//std::cout << "ESTADO: " << rAux << std::endl;
	//mostrarArrays();

	if(rAux > 0) {

		if (escapar > disparar && escapar > cqc ) {
			estadoDecidido = 6;
		}

		else if (disparar > escapar && disparar > cqc) {
			estadoDecidido = 3;
		}

		else if(cqc > disparar && cqc > escapar) {
			estadoDecidido = 7;
		}
	}


	else if(mAux > 1){
		estadoDecidido = 5; //tiene que decirle al enemigo que  huya para buscar al lider y active el flocking
	}

	//se decide el estado que sera


}

void LogicaDifusa::sistemaDeInferencia()
{
	baseDeConocimiento();
	desfusificador();
}

void LogicaDifusa::condiccionesDeLaVidaEnemigo()
{
	//vida alta

	float limt1 = vidaMax * 0.75f;

	float limt2 = vidaMax * 0.45f;
	float limt3 = vidaMax * 0.85f;
	float ptoM = vidaMax * 0.65f;

	float limt4 = vidaMax * 0.25f;
	float limt5 = vidaMax * 0.55f;
	float ptoB = vidaMax * 0.40f;
	
	float limt6 = vidaMax * 0.35f;
	float limt7 = vidaMax * 0.10f;

	//aqui esta el fallo
	//se cambia aqui el orden de los arrays o en la base de conocimiento

	if (vidaEnemigo > limt1) {

		if (vidaEnemigo < vidaMax) {
			resultadosVidaEnemigo[3] = (vidaEnemigo - limt1) / (vidaMax - limt1); //100 - 75
		}

		else {
			resultadosVidaEnemigo[3] = 1.0f;
		}
	}


	//vida media
	if (vidaEnemigo > limt2 && vidaEnemigo < limt3) {

		if (vidaEnemigo <= ptoM) {
			resultadosVidaEnemigo[2] = (vidaEnemigo - limt2) / (ptoM - limt2); //65 - 45
		}

		else {
			resultadosVidaEnemigo[2] = 2.0f - (vidaEnemigo - limt2) / (ptoM - limt2);
		}
	}

	//vida baja
	if (vidaEnemigo > limt4 && vidaEnemigo < limt5) {

		if (vidaEnemigo <= ptoB) {
			resultadosVidaEnemigo[1] = (vidaEnemigo - limt4) / (ptoB - limt4);//40 - 25
		}

		else {
			resultadosVidaEnemigo[1] = 2.0f - (vidaEnemigo - limt4) / (ptoB - limt4);

		}
	}

	//huir
	if (vidaEnemigo < limt6) {

		if (vidaEnemigo > limt7) {
			resultadosVidaEnemigo[0] = -(vidaEnemigo - limt7) / (limt7 - limt6); //10 - 35
		}

		else {

			resultadosVidaEnemigo[0] = 1.0f;
		}
	}
}


void LogicaDifusa::condiccionesDeLaDistancia()
{
	
	float pesoX = powf(posJugador.x - posEnemigo.x, 2);
	float pesoZ = powf(posJugador.y - posEnemigo.z, 2);
	float peso = sqrtf((pesoX + pesoZ));

	float limt1 = disMax * 0.7f;

	float limt2 = disMax * 0.8f;
	float limt3 = disMax * 0.15f;
	float ptoM = disMax * 0.5f;

	float limt4 = disMax * 0.35f;


		//distancia alta
		if (peso > limt1) {
	
			if (peso < disMax) {
				resultadosDePos[2] = (peso - limt1) / (disMax - limt1); //100 - 75
			}
	
			else {
				resultadosDePos[2] = 1.0f;
			}
		}
	
	
		//distancia media
		if (peso > limt3 && peso < limt2) {
	
			if (disMax <= ptoM) {
				resultadosDePos[1] = (peso - limt3) / (ptoM - limt3); //65 - 45
			}
	
			else {
				resultadosDePos[1] = 2.0f - (peso - limt3) / (ptoM - limt3);
			}
		}
	
	
		//distancia baja
		if (peso < limt4) {
	
			if (peso > 0.0f) {
				resultadosDePos[0] = - (peso) / (-limt4); //no se si se deberia poner un menos ?
			}
	
			else {
				resultadosDePos[0] = 1.0f;
			}
		}
}

void LogicaDifusa::condiccionesDeLaMoral()
{

	float limt1 = moralMax * 0.7f;

	float limt2 = moralMax * 0.8f;
	float limt3 = moralMax * 0.15f;
	float ptoM = moralMax * 0.5f;

	float limt4 = moralMax * 0.35f;


	//distancia alta
	if (moral > limt1) {

		if (moral < moralMax) {
			resultadosDeMoral[2] = (moral - limt1) / (moralMax - limt1); //100 - 75
		}

		else {
			resultadosDeMoral[2] = 1.0f;
		}
	}


	//distancia media
	if (moral > limt3 && moral < limt2) {

		if (disMax <= ptoM) {
			resultadosDeMoral[1] = (moral - limt3) / (ptoM - limt3); //65 - 45
		}

		else {
			resultadosDeMoral[1] = 2.0f - (moral - limt3) / (ptoM - limt3);
		}
	}


	//distancia baja
	if (moral < limt4) {

		if (moral > 0.0f) {
			resultadosDeMoral[0] = -(moral) / (-limt4); //no se si se deberia poner un menos ?
		}

		else {
			resultadosDeMoral[0] = 1.0f;
		}
	}

}

void LogicaDifusa::condiccionesDeLaResistencia()
{

	float limt1 = resistMax * 0.7f;

	float limt2 = resistMax * 0.8f;
	float limt3 = resistMax * 0.4f;
	float ptoM = resistMax * 0.6f;

	float limt4 = resistMax * 0.55f;


	//distancia alta
	if (resist > limt1) {
		if (resist < resistMax) {
			resultadosDeResistencia[2] = (resist - limt1) / (resistMax - limt1); //100 - 75
		}

		else {
			resultadosDeResistencia[2] = 1.0f;
		}
	}


	//distancia media
	if (resist > limt3 && resist < limt2) {

		if (disMax <= ptoM) {
			resultadosDeResistencia[1] = (resist - limt3) / (ptoM - limt3); //65 - 45
		}

		else {
			resultadosDeResistencia[1] = 2.0f - (resist - limt3) / (ptoM - limt3);
		}
	}


	//distancia baja
	if (resist < limt4) {

		if (resist > 0.0f) {
			resultadosDeResistencia[0] = -(resist) / (-limt4); //no se si se deberia poner un menos ?
		}

		else {
			resultadosDeResistencia[0] = 1.0f;
		}
	}

}

void LogicaDifusa::setPesoMaximo(float x)
{
	disMax = x;
}

void LogicaDifusa::reiniciarArrays() {

	for (std::size_t i = 0; i < 4; i++) {

		resultadosVidaEnemigo[i] = 0.0f;
	
	}

	for (std::size_t i = 0; i < 3; i++) {

		//resultadosVidaJugador[i] = 0.0f;
		resultadosDePos[i] = 0.0f;
		resultadosDeMoral[i] = 0.0f;
		resultadosDeResistencia[i] = 0.0f;

	}

	escapar = 0.0f;
	cqc = 0.0f;
	disparar = 0.0f;
	nResist = 0.0f;
	nMoral = 0.0f;


}

void LogicaDifusa::mostrarArrays() {

	for (std::size_t i = 0; i < 4; i++) {

		std::cout << "VIDA ENE:" << " " << i << " " << resultadosVidaEnemigo[i] << std::endl;

	}

	for (std::size_t i = 0; i < 3; i++) {

		//resultadosVidaJugador[i] = 0.0f;
		std::cout << "POS ENE:" << " " << i << " " << resultadosDePos[i] << std::endl;
		std::cout << "MORAL ENE:" << " " << i << " " << resultadosDeMoral[i] << std::endl;
		std::cout << "RESIST ENE:" << " " << i << " " << resultadosDeResistencia[i] << std::endl;

	}

}

int LogicaDifusa::getEstadoDecidido()
{
	return estadoDecidido;
}

int LogicaDifusa::getEstadoDelCansancio()
{
	int estado = -1;

	if (resultadosDeResistencia[0] > resultadosDeResistencia[1]
		&& resultadosDeResistencia[0] > resultadosDeResistencia[2]) {

		nResist = resultadosDeResistencia[0];
		//estadoDecidido = descansar;
		estado = 0;

	}

	else if (resultadosDeResistencia[1] > resultadosDeResistencia[0]
		&& resultadosDeResistencia[1] > resultadosDeResistencia[2]) {

		nResist = resultadosDeResistencia[1];
		//estadoDecidido = descansar;
		estado = 1;

	}


	else if (resultadosDeResistencia[2] > resultadosDeResistencia[1]
		&& resultadosDeResistencia[2] > resultadosDeResistencia[0]) {

		nResist = resultadosDeResistencia[2];
		//estadoDecidido = descansar;
		estado = 2;

	}

	return estado;
}

int LogicaDifusa::getEstadoDeLaMoral()
{
	int estado = -1;

	if (resultadosDeMoral[0] > resultadosDeMoral[1]
		&& resultadosDeMoral[0] > resultadosDeMoral[2]) {

		nMoral = resultadosDeMoral[0];
		//estadoDecidido = descansar;
		estado = 0;

	}

	else if (resultadosDeMoral[1] > resultadosDeMoral[0]
		&& resultadosDeMoral[1] > resultadosDeMoral[2]) {

		nMoral = resultadosDeMoral[1];
		//estadoDecidido = descansar;
		estado = 1;

	}


	else if (resultadosDeMoral[2] > resultadosDeMoral[1]
		&& resultadosDeMoral[2] > resultadosDeMoral[0]) {

		nMoral = resultadosDeMoral[2];
		//estadoDecidido = descansar;
		estado = 2;

	}

	return estado;
}
