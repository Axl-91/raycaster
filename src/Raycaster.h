#ifndef __RAYCASTER__
#define __RAYCASTER__

#include <iostream>
#include "Map.h"
#include "Vector.h"

#define PI 3.14159265358979323846

class Raycaster{
private:
    Vector rayV;
    Vector rayH;
    Vector rayFinal;
    Vector &posPlayer;
    float distV = 10000;
    float distH = 10000;
    float &angPlayer;
    float angRay;
    Map &mapRay;
    float distT;
    void raycasterVertical();
    void raycasterHorizontal();
    void calcularRayFinal();
public:
    Raycaster(Vector &pos, float &anguloPlayer, Map &map);
    void crearRay(float &anguloRay);
    float getDistancia();
    void render(int &pos);
    ~Raycaster();
};

#endif
