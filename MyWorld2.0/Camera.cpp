#include "Camera.h"

Camera::Camera() {
	pos = Vector(-100.0, -100.0, 10.0);
	dir = Vector(1.0, 1.0, 0.0);
	up  = Vector(0.0, 0.0, 1.0);
}

Camera* Camera::instance = new Camera();

Camera* Camera::getInstance() {
	
	return instance;
}

Vector Camera::getPosition() {
	return pos;
}

Vector Camera::getDirection() {
	return dir;
}

Vector Camera::getUpVector() {
	return up;
}

void Camera::setCamera( float posX, float posY, float posZ,
						float dirX, float dirY, float dirZ,
						float upX, float upY, float upZ) {
	pos = Vector(posX, posY, posZ);
	dir = Vector(dirX, dirY, dirZ);
	up  = Vector(upX, upY, upZ);
}

void Camera::setCameraPosition(	float posX, float posY, float posZ) {
	pos = Vector(posX, posY, posZ);
	dir.setX(dir.getX() + posX);
	dir.setY(dir.getY() + posY);
	dir.setZ(dir.getZ() + posZ);
}

void Camera::setLook() {
	gluLookAt(	pos.getX(), pos.getY(), pos.getZ(),
				dir.getX(), dir.getY(), dir.getZ(),
				up.getX(), up.getY(), up.getZ());
}
