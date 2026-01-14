#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#include "Raycaster.h"
#define LARGO_PANTALLA 320
#define ALTO_PANTALLA 200

int toGradosRay(float radiales){
	float angulo = (radiales / PI) * 180;
	int anguloInt = round(angulo);
	return anguloInt;
}

Raycaster::Raycaster(Vector &pos, float &anguloPlayer, Map &map):
    mapRay(map), posPlayer(pos), angPlayer(anguloPlayer){
}

void Raycaster::crearRay(float &angulo){
	angRay = angulo;
	raycasterHorizontal();
    raycasterVertical();
    calcularRayFinal();
}

void Raycaster::raycasterHorizontal(){
    float rx, ry, xo, yo;
    Vector raySuma;
	bool noHayColision = true;
	int grados = toGradosRay(angRay);
	float tangH = -1/tan(angRay);
	int largoBloque = mapRay.getLongBloques();

	if (grados > 180){
		int bloqPasados = posPlayer.getY() / largoBloque;
		ry = bloqPasados*largoBloque - 0.0001;
		rx = (posPlayer.getY() - ry)*tangH + posPlayer.getX();
        rayH = Vector(rx,ry);

		yo = -largoBloque;
		xo = -yo*tangH;
        raySuma = Vector(xo,yo);
	}
	if (grados < 180){
		int bloqPasados = posPlayer.getY() / largoBloque;
		ry = bloqPasados*largoBloque + largoBloque;
		rx = (posPlayer.getY() - ry)*tangH + posPlayer.getX();
        rayH = Vector(rx,ry);

		yo = largoBloque;
		xo = -yo*tangH;
        raySuma = Vector(xo,yo);
	}
	if (grados == 0 || grados == 360 || grados == 180){
		noHayColision = false;
	}

	while (noHayColision){
		distH = posPlayer.distancia(rayH);

		if (!mapRay.hayCoordenadas(rayH)){
			break;
		}
		if (mapRay.getBloque(rayH) == 0){
			rayH.sumar(raySuma);
		} else {
			noHayColision = false;
		}
	}
}

void Raycaster::raycasterVertical(){
    float rx, ry, xo, yo;
    Vector raySuma;
	bool noHayColision = true;
	int grados = toGradosRay(angRay);
	float tangV = -tan(angRay);
	int largoBloque = mapRay.getLongBloques();

	if (grados < 270 && grados > 90){
		int bloqPasados = posPlayer.getX() / largoBloque;
		rx = bloqPasados*largoBloque - 0.0001;
		ry = (posPlayer.getX() - rx)*tangV + posPlayer.getY();
        rayV = Vector(rx, ry);

		xo = -largoBloque;
		yo = -xo*tangV;
        raySuma = Vector(xo, yo);
	}
	if (grados > 270 || grados < 90){
		int bloqPasados = posPlayer.getX() / largoBloque;
		rx = bloqPasados*largoBloque + largoBloque;
		ry = (posPlayer.getX() - rx)*tangV + posPlayer.getY();
        rayV = Vector(rx, ry);

		xo = largoBloque;
		yo = -xo*tangV;
        raySuma = Vector(xo, yo);
	}
	if (grados == 270 || grados == 90){
		noHayColision=false;
	}

	while (noHayColision){
		distV = posPlayer.distancia(rayV);

		if (!mapRay.hayCoordenadas(rayV)){
			break;
		}
		if (mapRay.getBloque(rayV) == 0){
			rayV.sumar(raySuma);
		} else {
			noHayColision = false;
		}
	}
}

void Raycaster::calcularRayFinal(){
    if (distH < distV){
        distT = distH;
        rayFinal = rayH;
		mapRay.setWall(rayFinal, false);
		float rayX = rayFinal.getX();
		mapRay.setColWall(rayX);
    } else{
        distT = distV;
        rayFinal = rayV;
		mapRay.setWall(rayFinal, true);
		float rayY = rayFinal.getY();
		mapRay.setColWall(rayY);
    }

	/* Para evitar efecto fisheye */
	float angNuevo = angPlayer - angRay;
	if (angNuevo < 0) {angNuevo +=2*PI;}
	if (angNuevo > 2*PI) {angNuevo -= 2*PI;}
	distT = distT * cos(angNuevo);
}

float Raycaster::getDistancia(){
    return distT;
}

void Raycaster::render(int &pos){
	int largoCol = 1;
	int largoBloque = mapRay.getLongBloques();
	float largoPared = (largoBloque * LARGO_PANTALLA) / distT;
	//Desde donde voy a empezar a dibujar la pared
	float offset = (ALTO_PANTALLA/2) - (largoPared/2);

	int largoParedInt = largoPared;
	int offsetInt = offset;
	
	mapRay.renderWall(pos, offsetInt, largoCol, largoParedInt);
}

Raycaster::~Raycaster(){}
