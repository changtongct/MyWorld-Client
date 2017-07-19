#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <windows.h>
#include <glut.h>
#include "Vector.h"
#include "CoorManagement.h"
#include "Common.h"

extern DWORD Internet_ThreadId;
extern CoorManagement AllEntity;

class Camera {
public:
	Camera();
	~Camera(){};

    Vector getPosition() {return eyeinfo;}
    Vector getView() {return centerinfo;}
    Vector getUpVector() {return upinfo;}
    float getSpeed() {return speed;}

    void setSpeed(float s) { 
        speed  = s;
    }

    void setCamera(	float eyeX, float eyeY, float eyeZ,
					float centerX, float centerY, float centerZ,
					float upX, float upY, float upZ);

    void setViewByMouse();

    void moveCamera(char d);

    void setLook();
private:
	int m_id;
	Vector eyeinfo;
    Vector centerinfo;
    Vector upinfo;
    float speed;
};

#endif