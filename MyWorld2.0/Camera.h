#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <windows.h>
#include <glut.h>

#include "Vector.h"

class Camera {
public:
	static Camera* getInstance();
	~Camera(){};

    Vector getPosition();
    Vector getDirection();
    Vector getUpVector();

    void setCamera(	float posX, float posY, float posZ,
					float dirX, float dirY, float dirZ,
					float upX, float upY, float upZ);
	void setCameraPosition(	float posX, float posY, float posZ);
    void setLook();

private:
	Camera();
	Camera(const Camera&){}
	static Camera* instance;

	Vector pos;
    Vector dir;
    Vector up;
};

#endif