#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>

class Vector {
public:
	Vector() { x = 1.0; y = 1.0; z = 1.0;}
	Vector(float xx, float yy, float zz);
	~Vector(){};
	Vector(const Vector& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	float length();
    Vector normalize();
    float dotProduct(const Vector& v);
    Vector crossProduct(const Vector& v);
	void setX(float nx) {x = nx;}
	void setY(float ny) {y = ny;}
	void setZ(float nz) {z = nz;}
	float getX() {return x;}
	float getY() {return y;}
	float getZ() {return z;}

private:
	float x;
	float y;
	float z;
};

#endif