#ifndef _PLAYER_H_
#define _PLAYER_H_

//#include <windows.h>
//#include <glut.h>

#include "Vector.h"
#include "Camera.h"
#include "CoorMan.h"
#include "ThreadMan.h"
#include "Common.h"

class Player {
public:
	static Player* getInstance();
	~Player(){};

    Vector getPosition();
    Vector getDirection();
    Vector getUpVector();
	void moveByMouse();
	void moveByKeyboard(char d);

private:
	Player();
	Player(const Player&){}
	static Player* instance;

	int m_id;
	float speed;
	Vector pos;
    Vector dir;
    Vector up;
	Camera *MyCamera;
	CoorMan *MyCoorMan;
};

#endif