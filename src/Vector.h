#ifndef __VECTOR__
#define __VECTOR__

class Vector{
private:
    float posX;
    float posY;
public:
	Vector(float x=0, float y=0);
    float getX();
    float getY();
    void sumar (Vector vector);
    void restar (Vector vector);
    float distancia (Vector vector);
	~Vector();
};

#endif
