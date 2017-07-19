#include <string>
#include "BehaivorTree.h"


//==========BEHAVIOR TREE===========


BehaivorTree::BehaivorTree()
{
	root = nullptr;
	contNodos = 0;
}


BehaivorTree::~BehaivorTree()
{
}

Status BehaivorTree::Update()
{
	Status estadoNodo;
	bool salida = false;
//	std::cout << root->getListaHijos().size() << std::endl;
	
	for (int i=0; i<root->getListaHijos().size()&&salida==false; i++)
	{
		estadoNodo = root->getListaHijos()[i]->getEstado();
		std::cout << root->getListaHijos()[i]->getAccion()<<" "<<i << std::endl;
		if (estadoNodo== BH_INVALID || estadoNodo == BH_FAILURE || estadoNodo == BH_SUCCESS)
		{
			salida = true;
		}

		if (estadoNodo == BH_READY && !root->getListaHijos().empty())
		{
			estadoNodo = root->getListaHijos()[i]->Update();
		}

	}
	
	return estadoNodo;
}

void BehaivorTree::addNode(Node * hijo, Node *padre)
{
	if(padre == NULL) {
		
		//std::cout << "Entra root" << std::endl;
		root = hijo;
		hijo->setID(contNodos);
		contNodos++;

		//for (std::size_t i = 0; i < hijos; i++) {
		//	hijo->crearHijos(contNodos, hijo);
		//	contNodos++;
		//}
		
	}

	else {
		//std::cout << "Entra hijo" << std::endl;
		padre->addNodo(hijo);
		
	}

}
/*
void BehaivorTree::imprimirArbol()
{
	std::cout << "---------ROOT: " << root->getListaHijos().size() << std::endl;
	

	if (root != NULL) {

	for(std::size_t i = 0; i<root->getListaHijos().size(); i++) {
		
			std::cout <<"NOMBRE: "<< root->getListaHijos()[i]->getAccion() << std::endl;
			if(root->getListaHijos()[i]->getListaHijos().empty() == false) {
				//muestras sus hijos
				for (std::size_t j = 0; j<root->getListaHijos()[i]->getListaHijos().size(); j++) {
					std::cout << "NOMBRE HIJOS: " << root->getListaHijos()[i]->getListaHijos()[j]->getAccion()<< std::endl;

				}

			}

		}
	}

}*/


//=================== NODE =======================

Node::Node()
{
}

Node::Node(std::string n_accion, std::string n_task)
{
	ID = NULL;
	accion = n_accion;
	tipoTask = n_task;
	setEstado(BH_READY);
}

std::string Node::getAccion()
{
	return accion;
}

std::string Node::getTipoTask()
{
	return tipoTask;
}

Status Node::getEstado()
{
	return estado;
}

void Node::setID(int n_ID)
{
	ID = n_ID;
}

void Node::setEstado(Status s)
{
	estado = s;
}

void Node::addNodo(Node * n)
{

	nodosHijos.push_back(n);
}

Status Node::Update()
{
	Status estadoNodo=BH_SUCCESS;
	bool salida = false;

	//std::cout << this->getListaHijos().size() << std::endl;
	
	for (int i = 0; i<this->getListaHijos().size() && salida == false; i++)
	{
		estadoNodo = this->getListaHijos()[i]->getEstado();
		std::cout <<"--->"<< this->getListaHijos()[i]->getAccion()<<" "<< this->getListaHijos()[i]->getTipoTask() <<std::endl;
		if (estadoNodo == BH_INVALID || estadoNodo == BH_FAILURE || estadoNodo == BH_SUCCESS)
		{
			salida = true;
		
		}

		if (estadoNodo == BH_READY&&!this->getListaHijos().empty())
		{
			estadoNodo=this->getListaHijos()[i]->Update();
		}
		
	}

	return estadoNodo;
}

void Node::crearHijos(int cont, Node *p)
{
	//habria que ver alguna manera de distinguir que tipo de nodo queremos crear
	//si es alguno normal o de algun tipo en concreto

	//ver si traerse el bucle aqui para aumentar el contador del arbol
	//y que lo devuelva cuando acabe para que se guarde otra vez

	//Node *n = new Node();
	//n->setID(cont);
	//n->setPadre(p);
	//nodosHijos.push_back(n);
}

std::vector<Node*> Node::getListaHijos()
{
	return nodosHijos;
}




//==========SEQUENCE===========


//Node * Sequence::getNode()
//{
//	return  nullptr;
//}
//
//void Sequence::onInicializar()
//{
//	hijoActual = NULL;
//}
//
//Status Sequence::update()
//{
//	
//	while (true) {
//
//		Status s = hijo->tick();
//
//		if (s != BH_SUCCESS) {
//			return s;
//		}
//
//		if (++hijoActual == arbol.end()) {
//			return BH_SUCCESS;
//		}
//
//	}
//
//	//ASSERT_FAIL(BehaivorTree, "Se ha salido del bucle por un error");
//	return BH_INVALID;
//
//
//}


//==========SELECTOR===========


//void Selector::onInicializar()
//{
//	hijoActual = arbol.begin();
//
//}
//
//Status Selector::update()
//{
//	while (true) {
//
//		Status s = hijo->tick();
//
//		if (s != BH_FAILURE) {
//			return s;
//		}
//
//		if (++hijoActual == arbol.end()) {
//
//			return BH_FAILURE;
//
//		}
//
//	}
//
//	return BH_INVALID;
//}




//===========TASK=================

//Task::Task(Node * node)
//{
//	nodo = node;
//}
//
//Task::~Task()
//{
//}
//
//void Task::onInicializar()
//{
//}
//
//void Task::onTerminar(Status)
//{
//}


