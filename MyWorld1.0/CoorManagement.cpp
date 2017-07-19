#include "CoorManagement.h"

bool CoorManagement::addEntity(int newid, int newtype, Coordinate newdir, Coordinate newcoor) {
	if (Entities.find(newid) != Entities.end())
		return false;
	Entities[newid].type = newtype;
	Entities[newid].direction = newdir;
	Entities[newid].coordinate = newcoor;
	return true;
}


bool  CoorManagement::delEntity(int id) {
	if (Entities.find(id) == Entities.end())
		return false;
	Entities.erase(id);
	return true;
}


Coordinate CoorManagement::getCoordinate(int id) {
	return Entities[id].coordinate;
}

Coordinate CoorManagement::getDirection(int id) {
	return Entities[id].direction;
}


bool CoorManagement::changeCoorDirect(int id, Coordinate newdir, Coordinate newcoor) {
	if (Entities.find(id) == Entities.end())
		return false;
	Entities[id].direction = newdir;
	Entities[id].coordinate = newcoor;
	return true;
}


bool CoorManagement::changeCoorSmooth(int id, Coordinate newdir, Coordinate newcoor) {
	if (Entities.find(id) == Entities.end())
		return false;
	float stepX = (newcoor.x - Entities[id].coordinate.x)/30;
	float stepY = (newcoor.y - Entities[id].coordinate.y)/30;
	for (unsigned int i=0;i<30;++i) {
		Entities[id].coordinate.x = Entities[id].coordinate.x + stepX;
		Entities[id].coordinate.y = Entities[id].coordinate.y + stepY;
		Sleep(20 * static_cast<int>(SPEED));
	}
	return true;
}


int CoorManagement::totalNumOfEntities() {
	return Entities.size();
}