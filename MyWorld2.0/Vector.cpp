#include "Vector.h"

Vector::Vector(float nx, float ny, float nz) : x(nx),y(ny),z(nz) {}

float Vector::length() {
	return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() {
	float len = length();
	if (len > -0.00001 && len < 0.00001)
		len = 1.0;
	x = x / len;
	y = y / len;
	z = z / len;
	return *this;
}

float Vector::dotProduct(const Vector& v) {
	return ( x * v.x + y * v.y + z * v.z );
}

Vector Vector::crossProduct(const Vector& v) {
	Vector vec;

    vec.x = y * v.z - z * v.y;
    vec.y = z * v.x - x * v.z;
    vec.z = x * v.y - y * v.x;

    return vec;
}