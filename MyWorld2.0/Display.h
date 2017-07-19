#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <glut.h>
#include "CoorMan.h"
#include "Planet.h"
#include "Camera.h"
#include "Vector.h"
#include "Common.h"

#include <unordered_map>
using namespace std;

extern CRITICAL_SECTION C_COOR;

void OnTimer(int val);
void InitDisplay();
void myDisplay();
void drawGround(float length, float width);
void drawGrid(float x, float y);
void drawCoordinateAxis();
void drawBox(Vector npos, Vector ndir);
void drawPerson(Vector npos, Vector ndir);
void drawPlayer(Vector npos, Vector ndir);
void drawBullet(Vector npos, Vector ndir);

#endif
