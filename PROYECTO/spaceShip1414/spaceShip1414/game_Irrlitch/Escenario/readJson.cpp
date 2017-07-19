/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   readJson.cpp
* Author: Hector
*
* Created on 30 de noviembre de 2016, 0:21
*/

#include "readJson.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/document.h"
#include "../rapidjson/pointer.h"
#include "../rapidjson/istreamwrapper.h"
#include <fstream>
#include <cstdio>
#include <string>
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

using namespace rapidjson;
using namespace std;


readJson::readJson(Escenario *e) {

	leerArchivo("../Puente.json");
	esce = e;
	crearPared();
}
readJson::readJson(const readJson& orig) {
}

readJson::~readJson() {
}

void readJson::leerArchivo(const char* rutaArchivo)
{
	FILE* fp = fopen(rutaArchivo, "rb"); // non-Windows use "r"
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	d.ParseStream(is);
	fclose(fp);
}

void readJson::crearPared()
{
	assert(d.HasMember("name"));
	assert(d["name"].IsString());
	const Value& a = d["hierarchy"];
	assert(a.IsArray());
	for (SizeType i = 0; i < a.Size(); i++)
	{
		if (a[i].HasMember("name"))
		{
			/*Leemos nombre del Padre y creamos variables*/
			std::string padre = a[i]["name"].GetString();
			double posicion[3];
			double rotacion[3];
			double escala[3];

			const Value& b = a[i]["components"];
			assert(b.IsArray());

			for (SizeType j = 0; j < b.Size(); j++)
			{
				if (b[j].HasMember("localPosition"))
				{
					const Value& c = b[j]["localPosition"];
					assert(c.IsArray());
					posicion[0] = c[0].GetDouble();
					posicion[1] = c[1].GetDouble();
					posicion[2] = c[2].GetDouble();
				}
				if (b[j].HasMember("localRotation"))
				{
					const Value& c = b[j]["localRotation"];
					assert(c.IsArray());
					rotacion[0] = c[0].GetDouble();
					rotacion[1] = c[1].GetDouble();
					rotacion[2] = c[2].GetDouble();
				}
				if (b[j].HasMember("localScale"))
				{
					const Value& c = b[j]["localScale"];
					assert(c.IsArray());
					escala[0] = c[0].GetDouble();
					escala[1] = c[1].GetDouble();
					escala[2] = c[2].GetDouble();
				}

			}

			const Value& d = a[i]["children"];
			assert(d.IsArray());

			std::string hijo;
			for (SizeType t = 0; t < d.Size(); t++)
			{
				hijo = d[t]["name"].GetString();

				double posicionC[3];
				double rotacionC[3];
				double escalaC[3];

				const Value& e = d[t]["components"];
				for (SizeType r = 0; r < e.Size(); r++)
				{
					if (e[r].HasMember("localPosition"))
					{
						const Value& c = e[r]["localPosition"];
						assert(c.IsArray());
						posicionC[0] = c[0].GetDouble();
						posicionC[1] = c[1].GetDouble();
						posicionC[2] = c[2].GetDouble();

					}

					if (e[r].HasMember("localRotation"))
					{
						const Value& c = e[r]["localRotation"];
						assert(c.IsArray());
						rotacionC[0] = c[0].GetDouble();
						rotacionC[1] = c[1].GetDouble();
						rotacionC[2] = c[2].GetDouble();

					}
					if (e[r].HasMember("localScale"))
					{
						const Value& c = e[r]["localScale"];
						assert(c.IsArray());
						escalaC[0] = c[0].GetDouble();
						escalaC[1] = c[1].GetDouble();
						escalaC[2] = c[2].GetDouble();
					}

				}
				std::string SubHijo;
				const Value& z = d[t]["children"];
				if (z.IsArray())
				{
					for (SizeType n = 0; n < z.Size(); n++)
					{
						SubHijo = z[n]["name"].GetString();

						double posicionSC[3];
						double rotacionSC[3];
						double escalaSC[3];


						const Value& g = z[n]["components"];
						for (SizeType t = 0; t < g.Size(); t++)
						{
							if (g[t].HasMember("localPosition"))
							{
								const Value& c = g[t]["localPosition"];
								assert(c.IsArray());
								posicionSC[0] = c[0].GetDouble();
								posicionSC[1] = c[1].GetDouble();
								posicionSC[2] = c[2].GetDouble();
							}
							if (g[t].HasMember("localRotation"))
							{
								const Value& c = g[t]["localRotation"];
								assert(c.IsArray());
								rotacionSC[0] = c[0].GetDouble();
								rotacionSC[1] = c[1].GetDouble();
								rotacionSC[2] = c[2].GetDouble();
							}
							if (g[t].HasMember("localScale"))
							{
								const Value& c = g[t]["localScale"];
								assert(c.IsArray());
								escalaSC[0] = c[0].GetDouble();
								escalaSC[1] = c[1].GetDouble();
								escalaSC[2] = c[2].GetDouble();
							}

						}

						esce->setSubHijos(SubHijo, posicionSC, rotacionSC, escalaSC);
					}

					esce->setHijos(hijo, posicionC, rotacionC, escalaC, esce->getSubHijos());
					esce->removeListSubHijos();
				}

			}
			esce->setPadres(padre, posicion, rotacion, escala, esce->getHijos());
			esce->removeListHijos();
		}

	}

	esce->dibujarEscenario();
}

