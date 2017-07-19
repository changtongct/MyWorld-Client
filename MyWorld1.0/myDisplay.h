#include <glut.h>
#include "CoorManagement.h"
#include "Planet.h"
#include "Camera.h"
#include "Common.h"

extern CoorManagement AllEntity;
extern Camera myCamera;

void InitDisplay();
void myDisplay();
void drawGround(float length, float width);
void drawGrid(float x, float y);
void drawCoordinateAxis();
void drawBox(Coordinate coor, Coordinate newdir);
void drawPerson(Coordinate coor, Coordinate newdir);
void drawPlayer(Coordinate coor, Coordinate newdir);
void drawBullet(Coordinate coor, Coordinate newdir);