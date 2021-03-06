#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>

class Vector {
public:
	Vector(void) { x = 0.0; y = 0.0; z = 0.0;}
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
	void setX(float xx) {x = xx;}
	void setY(float yy) {y = yy;}
	void setZ(float zz) {z = zz;}
	float getX() {return x;}
	float getY() {return y;}
	float getZ() {return z;}

private:
	float x;
	float y;
	float z;
};

#endif