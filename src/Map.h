#ifndef __MAP__
#define __MAP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Vector.h"
#include "Walls.h"
#include "Objects.h"

typedef struct Objeto {
	Vector posicion;
	int tipoObjecto;
} Objeto;

class Map{
private:
	int largoBloque = 64;
	int filas = 15;
	int columnas = 20;
    //El mapa deberia ser de dimensiones variables
	int map[15][20];
	Walls walls;
	Objects objects;
	std::vector<Objeto> vectObj;
public:
	Map();
	void load(int lvl[15][20]);
	void setRenderer(SDL_Renderer* renderer);
	int getLongBloques();
	bool hayCoordenadas(float &x, float &y);
	bool hayCoordenadas(Vector &posicion);
	int getBloque(float &x, float &y);
	int getBloque(Vector &posicion);
	void setWall(Vector &posicion, bool dark);
	void setColWall(float &pos);
	void renderWall(int &posX, int &posY, int &largo, int &alto);
	void addObject(Vector &posicion, int tipo);
	void ordenarObjects(Vector &pos);
	int getCantObjects();
	Vector getPosObj(int &pos);
	int getTipoObj(int &pos);
	void setObj(int &pos);
	void setColObject(int &pos);
	void renderObject(int &posX, int &posY, int &largo, int &alto);
	~Map();
};

#endif
