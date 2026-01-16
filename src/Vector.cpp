#include "Vector.h"
#include <math.h>

Vector::Vector(float posX, float posY) : x(posX), y(posY) {}

float Vector::getX() { return this->x; }

float Vector::getY() { return this->y; }

void Vector::set(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vector::sum(Vector vector) {
    this->x += vector.getX();
    this->y += vector.getY();
}

void Vector::sub(Vector vector) {
    this->x -= vector.getX();
    this->y -= vector.getY();
}

float Vector::distance(Vector vector) {
    float x = vector.getX() - this->x;
    float y = vector.getY() - this->y;

    return (sqrt((x * x) + (y * y)));
}

Vector::~Vector() {}
