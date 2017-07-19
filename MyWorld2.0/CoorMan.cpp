#include "CoorMan.h"


CoorMan::CoorMan() {
	InitializeCriticalSection(&C_COOR);
}

CoorMan* CoorMan::instance = new CoorMan();

CoorMan* CoorMan::getInstance() {
	return instance;
}

bool CoorMan::addEntity(int nid, char ntype, char nstate, Vector npos, Vector ndir) {
	if (Entities.find(nid) != Entities.end())
		return false;
	EnterCriticalSection(&C_COOR);
	Entities[nid].type = ntype;
	Entities[nid].state = nstate;
	Entities[nid].pos = npos;
	Entities[nid].dir = ndir;
	LeaveCriticalSection(&C_COOR);
	return true;
}

bool  CoorMan::delEntity(int id) {
	if (Entities.find(id) == Entities.end())
		return false;
	EnterCriticalSection(&C_COOR);
	Entities.erase(id);
	LeaveCriticalSection(&C_COOR);
	return true;
}

Vector CoorMan::getPosition(int id) {
	return Entities[id].pos;
}

Vector CoorMan::getDirection(int id) {
	return Entities[id].dir;
}

bool CoorMan::changePosDirect(int id, Vector npos) {
	if (Entities.find(id) == Entities.end())
		return false;
	EnterCriticalSection(&C_COOR);
	Entities[id].pos = npos;
	LeaveCriticalSection(&C_COOR);
	return true;
}

//bool CoorMan::changeCoorSmooth(int id, Coordinate newdir, Coordinate newcoor) {
//	if (Entities.find(id) == Entities.end())
//		return false;
//	float stepX = (newcoor.x - Entities[id].coordinate.x)/30;
//	float stepY = (newcoor.y - Entities[id].coordinate.y)/30;
//	for (unsigned int i=0;i<30;++i) {
//		Entities[id].coordinate.x = Entities[id].coordinate.x + stepX;
//		Entities[id].coordinate.y = Entities[id].coordinate.y + stepY;
//		Sleep(20 * static_cast<int>(SPEED));
//	}
//	return true;
//}

bool CoorMan::changeDirDirect(int id, Vector ndir) {
	if (Entities.find(id) == Entities.end())
		return false;
	EnterCriticalSection(&C_COOR);
	Entities[id].dir = ndir;
	LeaveCriticalSection(&C_COOR);
	return true;
}

int CoorMan::totalNumOfEntities() {
	return Entities.size();
}