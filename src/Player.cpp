#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Raycaster.h"

int toGrados(float radiales){
	float anguloGrados = (radiales / PI) * 180;
	int anguloInt = round(anguloGrados);
	return anguloInt;
}

Player::Player(){}

void Player::setPos(float x, float y){
    posX = x;
    posY = y;
}

void Player::setMap(Map &map){
    mapPlayer = map;
}

void Player::setRenderer(SDL_Renderer* renderer){
    rendererPlayer = renderer;
}

void Player::avanzar(){
	posX += dx;
	posY += dy;

    /*Vector lado1(posX-dx, posY);
    Vector lado2(posX+dx, posY);
    Vector lado3(posX, posY-dy);
    Vector lado4(posX, posY+dy);

	if (mapPlayer.getBloque(lado1) != 0){

	} else if (mapPlayer.getBloque(lado2) != 0){

	} else if (mapPlayer.getBloque(lado3) != 0){

	} else if (mapPlayer.getBloque(lado4) != 0){

	} else {
		posX += dx;
		posY += dy;
	}*/
}

void Player::retroceder(){
	posX -= dx;
	posY -= dy;

    /*Vector lado1(posX-dx, posY);
    Vector lado2(posX+dx, posY);
    Vector lado3(posX, posY-dy);
    Vector lado4(posX, posY+dy);

	if (mapPlayer.getBloque(lado1) != 0){

	} else if (mapPlayer.getBloque(lado2) != 0){

	} else if (mapPlayer.getBloque(lado3) != 0){

	} else if (mapPlayer.getBloque(lado4) != 0){

	} else {
		posX -= dx;
		posY -= dy;
	}
	*/
}

void Player::pollEvent(SDL_Event &evento){
	if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
			case SDLK_UP:
				avanzar();
				break;
			case SDLK_DOWN:
				retroceder();
				break;
			case SDLK_RIGHT:
				angulo += PI/36;
				if (toGrados(angulo) >= 360){
					angulo -= 2*PI;
				}
				dx = 5*cos(angulo);
				dy = 5*sin(angulo);
				break;
			case SDLK_LEFT:
				angulo -= PI/36;
				if (toGrados(angulo) < 0){
					angulo += 2*PI;
				}
				dx = 5*cos(angulo);
				dy = 5*sin(angulo);
				break;
			break;
		}
	}
}

void Player::renderRaycaster(){
	Vector vectorPos(posX, posY);
	Raycaster raycaster(vectorPos, angulo, mapPlayer);
	float anguloRay = angulo-PI/6;

	for (int pos=0; pos < 320; ++pos){
		if (anguloRay < 0){
			anguloRay += 2*PI;
		} else if (anguloRay > 2*PI){
			anguloRay -=2*PI;
		}
		raycaster.crearRay(anguloRay);
		raycaster.render(pos);

		distBuffer[pos] = raycaster.getDistancia();

		anguloRay += PI/960;
	}
}

bool Player::objEsVisible(Vector &posObj){
	/*Visibilidad hacia izq y derecha en radiales
	serian 30 grados pero agrego 5 mas para que
	se vea mas el sprite del objeto */
	float gVis = 35.0/180.0;
	float visible = PI * gVis;

	float dx = posObj.getX() - posX;
	float dy = posObj.getY() - posY;

	float anguloObj = atan2(dy, dx);
	float difAng = angulo - anguloObj;

	if (difAng < -PI){
		difAng += 2*PI;
	}
	if (difAng > PI){
		difAng -= 2*PI;
	}
	bool res = (difAng < visible);
	res &= (difAng > -visible);

	return res;
}

void Player::renderObjects(){
	int uno = 1;
	Vector posJugador = Vector(posX, posY);
	mapPlayer.ordenarObjects(posJugador);
	
	for (int obj = 0; obj < mapPlayer.getCantObjects(); ++obj){
		Vector posObjeto = mapPlayer.getPosObj(obj);
		if (!objEsVisible(posObjeto)){
			continue;
		}
		int tipoObj = mapPlayer.getTipoObj(obj);
		float distanciaObj = posJugador.distancia(posObjeto);

		//Coordenadas en Y
		float sizeObj = (64 * 320) / distanciaObj;
		float yo = 100 - (sizeObj/2);
		//Coordenadas en X
		float dx = posX - posObjeto.getX();
		float dy = posY - posObjeto.getY();

		float anguloObj = atan2(dy, dx) - angulo;
		float xo = tan(anguloObj) * 277.1281;
		float x = round((320/2) + xo - (sizeObj/2));

		float anchura = sizeObj / 64;
		int yoInt = yo;
		int sizeObjInt = sizeObj;
		mapPlayer.setObj(tipoObj);

		for (int i = 0; i < 64; ++i){
			for (int j = 0; j < anchura; ++j){
				int z = round(x)+((i)*anchura)+j;
				if (z < 0 || z > 320){ continue; }

				if (distBuffer[z] > distanciaObj){
					mapPlayer.setColObject(i);
					mapPlayer.renderObject(z, yoInt, uno, sizeObjInt);
				}
			}
		}
	}
}

void Player::render(){
	renderRaycaster();
	renderObjects();
}

Player::~Player(){}