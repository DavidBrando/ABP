

#include "TGraphicEngine.h"
#include <iostream>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "resourceManager\TGestorRecursos.h"
#include "entityTree\TEntidad.h"
#include "entityTree\TNodo.h"
#include "entityTree\TTransform.h"
#include "entityTree\TCamara.h"
#include "entityTree\TLuz.h"
#include "entityTree\TMalla.h"
#include "framework\movimentHandler.h"
#include "../Fisicas/Mundo.h"
#include "../Game/Escenario/Escenario.h"




TGraphicEngine::TGraphicEngine() : shader(), aspect_ratio{}, window{}, registroCamaras(), registroLuces(), lastTime{ 0 }
{
	escena = new TNodo(nullptr);
	gestorRecursos = new TGestorRecursos();
	move = new movimentHandler();
}

TGraphicEngine::~TGraphicEngine()
{
	delete escena;
	escena = nullptr;
	delete gestorRecursos;
	gestorRecursos = nullptr;
	std::cout << "Facade Destroted" << std::endl;
}

TNodo * TGraphicEngine::crearNodo(TNodo* padre, TEntidad* entidad)
{
	return new TNodo(padre, entidad);
}

TTransform * TGraphicEngine::crearTransform()
{
	return new TTransform();
}

TCamara * TGraphicEngine::crearCamara(bool pe, float xu, float yu, float zu, float xf, float yf, float zf, bool a)
{
	TCamara* c = new TCamara(pe, xu, yu, zu, xf, yf, zf);
	if (a) 
	{
		c->activar();
	}
	return c;
}

TCamara * TGraphicEngine::crearCamaraS(bool pe, float xu, float yu, float zu, float xf, float yf, float zf, bool a)
{
	TCamara* c = new TCamara(pe, xu, yu, zu, xf, yf, zf);
	if (a)
	{
		c->activar();
	}
	c->setTipo(2);
	return c;
}

TCamara * TGraphicEngine::crearCamara()
{
	return new TCamara();
}

TLuz * TGraphicEngine::crearLuz(float x, float y, float z, bool a)
{
	TLuz* l = new TLuz(x, y, z);
	if (a)
	{
		l->activar();
	}

	return l;
}

TMalla * TGraphicEngine::crearMalla(std::string fichero)
{
	return new TMalla(fichero, gestorRecursos);
}

TNodo * TGraphicEngine::nodoRaiz()
{
	return escena;
}

GLFWwindow * TGraphicEngine::getGLFWwindow()
{
	return window;
}

bool TGraphicEngine::init(std::string title, int width, int height, bool full_screen)
{
	aspect_ratio = static_cast<float>(width) / static_cast<float>(height);

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) return false;

	window = glfwCreateWindow(width, height, title.c_str(), full_screen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowCloseCallback(window, close_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetCursorPosCallback(window, mouse_callback);



	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	glfwSetWindowUserPointer(window, this);

	return true;
}


void TGraphicEngine::run(Mundo * world, Escenario* esce)
{
	onstart();
	glfwSetTime(0.0);
	lastTime = 0.0;
	double currentFrame = glfwGetTime();
	double last = currentFrame;
	wo = world;

	while (!glfwWindowShouldClose(window))
	{
		

		currentFrame = glfwGetTime();
		deltaTime = (currentFrame - last);
		last = currentFrame;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->stepBox2D(1.0/60.0, 6, 2);
		world->getWorldBox2D()->DrawDebugData();

		world->clearForcesBox2D();
		//drawBox(world, 5, 50, 2, 1);
		move->checkKeys(window);
		//drawGround(world);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		esce->actualizarEstadoPuerta();
		glfwPollEvents();
		draw(getLastTime());
		glfwSwapBuffers(window);
		
	
		

	}

	glfwDestroyWindow(window);
	glfwTerminate();
}


void  TGraphicEngine::drawBox(Mundo * world, double x, double y, int w, int h) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0.1, 0.1);
	myBodyDef.angle = 0;

	b2Body* dynamicBody = world->getWorldBox2D()->CreateBody(&myBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(0.1, 0.1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 0.5;
	dynamicBody->CreateFixture(&boxFixtureDef);
	//Pared * p = new Pared(this,glm::vec3(0,0,0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	//p->setFisicas(world);
}

void  TGraphicEngine::drawGround(Mundo * world) {
	//b2Body *groundBody;
	//b2Fixture *bottomFixture;
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0, 0);
	//groundBody = world->getWorldBox2D()->CreateBody(&groundBodyDef);

	//b2EdgeShape groundBox;
	//b2FixtureDef groundBoxDef;
	//groundBoxDef.shape = &groundBox;

	//groundBox.Set(b2Vec2(XMIN, YMIN), b2Vec2(XMAX, YMIN));
	//bottomFixture = groundBody->CreateFixture(&groundBoxDef);
}


void TGraphicEngine::info()
{
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;
}

void TGraphicEngine::addRegistroLuz(TNodo* l)
{
	if (l)
	{
		registroLuces.push_back(l);
	}
}

void TGraphicEngine::addRegistroCamara(TNodo * c)
{
	if (c)
	{
		registroCamaras.push_back(c);
	}
}

movimentHandler* TGraphicEngine::getMovimentHandler()
{
	return move;
}

void TGraphicEngine::setPlayerMove(player * j)
{
	move->setPlayer(j);
}

void TGraphicEngine::setCameraMove(Camara * j)
{
	move->setCamara(j);
}

double TGraphicEngine::getLastTime()
{
	return lastTime;
}

double TGraphicEngine::getDT()
{
	return deltaTime;
}

void TGraphicEngine::setLastTime(double t)
{
	lastTime = t;
}

TCamara* TGraphicEngine::getCamaraActiva()
{
	return camaraActiva;
}

void TGraphicEngine::cambiarCamaraActiva(char m)
{
	if (camaraActiva) {
		camaraActiva->desactivar();
	}
	if (registroCamaras.size() > m) {
		static_cast<TCamara*>(registroCamaras.at(m)->getEntidad())->activar();
		camaraActiva = static_cast<TCamara*>(registroCamaras.at(m)->getEntidad());
	}
}

glm::vec3 TGraphicEngine::moverCamara()
{

	std::cout << "hle" << std::endl;
	camaraActiva->setWindow(window);
	return camaraActiva->mover();
}

glm::mat4 TGraphicEngine::getView()
{
	return camaraActiva->getView();
}



void TGraphicEngine::draw(double time)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.use();
	camaraActivada();
	luzActivada();
	wo->getWorldBox2D()->DrawDebugData();

	this->escena->draw(shader, camaraActiva->getView(), camaraActiva->getProjectionMatrix(),wo);
	shader.unUse();
}

void TGraphicEngine::onstart()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	shader.compile("graphicEngine/Shader/directional.vertex_shader", "graphicEngine/Shader/directional.fragment_shader");

	// ocultar el cursor y ubicarlo en el centro de la ventana
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(this->window, 1280 / 2, 720 / 2);
}

void TGraphicEngine::onstop()
{
}

void TGraphicEngine::onresize(int width, int height)
{
	aspect_ratio = std::max(0.0f, width / (float)height);
	glViewport(0, 0, width, height);
}

void TGraphicEngine::camaraActivada()
{
	for (size_t i = 0; i < registroCamaras.size(); i++)
	{
		if (static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->getActiva())
		{
			glm::mat4 t = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getEntidad())->getMatriz();
			glm::mat4 e = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getPadre()->getEntidad())->getMatriz();
			glm::mat4 r = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getPadre()->getPadre()->getEntidad())->getMatriz();
			if (static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->getTipo() == 2)
			{
				glm::mat4 tt = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getPadre()->getPadre()->getPadre()->getEntidad())->getMatriz();
				static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->setView(tt*r*e*t);
			}
			else
			{
				static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->setView((r*e)*t);
			}
			camaraActiva = static_cast<TCamara*>(registroCamaras.at(i)->getEntidad());
			camaraActiva->setWindow(this->window);
			break;
		}
	}
}

void TGraphicEngine::luzActivada()
{
	for (size_t i = 0; i < registroLuces.size(); i++) {
		if (static_cast<TLuz*>(registroLuces.at(i)->getEntidad())->getActiva())
		{
			glm::mat4 t = static_cast<TTransform*>(registroLuces.at(i)->getPadre()->getEntidad())->getMatriz();
			glm::mat4 e = static_cast<TTransform*>(registroLuces.at(i)->getPadre()->getPadre()->getEntidad())->getMatriz();
			glm::mat4 r = static_cast<TTransform*>(registroLuces.at(i)->getPadre()->getPadre()->getPadre()->getEntidad())->getMatriz();
			static_cast<TLuz*>(registroLuces.at(i)->getEntidad())->renderLuz((r*e)*t, shader, camaraActiva->getView(), camaraActiva->getProjectionMatrix());
		}
	}
}

void TGraphicEngine::error_callback(int error, const char * description)
{
	std::cerr << "Error: " << error << ", " << description << std::endl << std::endl;
}

void TGraphicEngine::close_callback(GLFWwindow *window)
{
	TGraphicEngine* win_app = getTGraphicEngineApp(window);
	win_app->onstop();
}

void TGraphicEngine::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	TGraphicEngine* win_app = getTGraphicEngineApp(window);
	double currentTime = glfwGetTime();
	win_app->getMovimentHandler()->onKey(window, key, scancode, action, mods, currentTime-win_app->getLastTime(), win_app);
	win_app->setLastTime(currentTime);
}

void TGraphicEngine::resize_callback(GLFWwindow * window, int width, int height)
{
	TGraphicEngine* win_app = getTGraphicEngineApp(window);
	win_app->onresize(width, height);
}

void TGraphicEngine::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	TGraphicEngine* win_app = getTGraphicEngineApp(window);
	win_app->getMovimentHandler()->onMouse(window, xpos, ypos);
}

inline TGraphicEngine * TGraphicEngine::getTGraphicEngineApp(GLFWwindow * window)
{
	return static_cast<TGraphicEngine*>(glfwGetWindowUserPointer(window));
}
