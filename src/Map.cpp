#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Walls.h"
#include "Objects.h"

int lvl1[15][20] = {
	{34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34},
	{34,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,34},
	{34,35,49,35,35,49,35,35,00,00,00,00,00,36,36,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,00,00,00,00,00,36,36,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,34},
	{34,34,34,34,34,34,00,00,34,34,34,34,00,00,00,00,00,34,34,34},
	{34,00,00,00,00,00,00,00,34,34,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,34,34,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,34,34,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,34,34,00,00,00,00,00,00,00,00,00,34},
	{34,00,00,00,00,00,00,00,34,34,00,00,00,00,00,00,00,00,00,34},
	{34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34},
};

Map::Map(){
	load(lvl1);
	Objeto luz1 = {Vector(640,192), 6};
	vectObj.push_back(luz1);
	//Objeto luz2 = {Vector(), 9};
	//Objeto luz3 = {Vector(), 9};
	Objeto col1 = {Vector(192,384), 9};
	vectObj.push_back(col1);
	Objeto col2 = {Vector(192,448), 9};
	vectObj.push_back(col2);
	Objeto col3 = {Vector(192,320), 9};
	vectObj.push_back(col3);
	Objeto col4 = {Vector(705,192), 9};
	vectObj.push_back(col4);
}

void Map::load(int lvl[15][20]){
	for (int i = 0; i < filas; ++i){
		for (int j = 0; j < columnas; ++j){
			map[i][j] = lvl[i][j];
		}
	}
}

void Map::setRenderer(SDL_Renderer* renderer){
	walls.setRenderer(renderer);
	objects.setRenderer(renderer);
}

int Map::getLongBloques(){
	return largoBloque;
}

bool Map::hayCoordenadas(float &x, float &y){
	int posX = x/largoBloque;
	int posY = y/largoBloque;

	if (posX > columnas || posX < 0){
		return false;
	}
	if (posY > filas || posY < 0){
		return false;
	}
	
	return true;
}

bool Map::hayCoordenadas(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();
	return hayCoordenadas(x, y);
}

int Map::getBloque(float &x, float &y){
	int posX = x/largoBloque;
	int posY = y/largoBloque;

	return map[posY][posX];
}

int Map::getBloque(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();
	return getBloque(x, y);
}

void Map::setWall(Vector &vector, bool dark){
	int tipoWall = getBloque(vector) - 1;
	walls.setWall(tipoWall);
	if (dark){
		walls.setDark();
	}
}

void Map::setColWall(float &pos){
	int y = 0;
	int largoCol = 1;
	int rayInt = floor(pos);
	int posWall = rayInt % largoBloque;
	walls.recortar(posWall, y, largoCol, largoBloque);
}

void Map::renderWall(int &posX, int &posY, int &largo, int &alto){
	walls.render(posX, posY, largo, alto);
}

void Map::addObject(Vector &posicion, int tipo){
	Objeto obj = {posicion, tipo};
	vectObj.push_back(obj);
}

int Map::getCantObjects(){
	return vectObj.size();
}

void agregarVectDist(std::vector<Objeto> &v, Objeto &obj, Vector &pos){
	float dist = pos.distancia(obj.posicion);
	for (auto i = v.begin(); i != v.end(); ++i){
		Objeto objVec = *i;
		float distV = pos.distancia(objVec.posicion);
		if (dist > distV){
			v.insert(i, obj);
			return;
		}
	}
	v.push_back(obj);
}

void Map::ordenarObjects(Vector &pos){
	std::vector<Objeto> vectorAux;

	for (Objeto obj : vectObj){
		agregarVectDist(vectorAux, obj, pos);
	}
	vectObj.swap(vectorAux);
}

Vector Map::getPosObj(int &pos){
	Objeto objPedido = vectObj.at(pos);
	return objPedido.posicion;
}

int Map::getTipoObj(int &pos){
	Objeto objPedido = vectObj.at(pos);
	return objPedido.tipoObjecto;	
}

void Map::setObj(int &tipo){
	objects.setObject(tipo);
}

void Map::setColObject(int &pos){
	objects.recortar(pos, 0, 1, 64);
}

void Map::renderObject(int &posX, int &posY, int &largo, int &alto){
	objects.render(posX, posY, largo, alto);
}

Map::~Map(){}
