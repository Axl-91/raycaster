#include "Vector.h"
#include <math.h>

Vector::Vector(float x, float y) : x(x), y(y) {}

float Vector::getX() const { return this->x; }

float Vector::getY() const { return this->y; }

void Vector::set(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vector::sum(const Vector &vector) {
    this->x += vector.getX();
    this->y += vector.getY();
}

void Vector::sub(const Vector &vector) {
    this->x -= vector.getX();
    this->y -= vector.getY();
}

float Vector::distance(const Vector &vector) const {
    float x = vector.getX() - this->x;
    float y = vector.getY() - this->y;

    return (sqrt((x * x) + (y * y)));
}
