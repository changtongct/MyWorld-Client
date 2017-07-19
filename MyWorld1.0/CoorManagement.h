#ifndef __COORMANAGE_H__
#define __COORMANAGE_H__

#include <unordered_map>
#include <windows.h>
#include "Common.h"

using namespace std;

extern const float SPEED;

struct Coordinate {
	float x;
	float y;
	float z;
	Coordinate(void){x = 0.0; y = 0.0; z = 0.0;}
	Coordinate(float nx, float ny, float nz=50.0):x(nx),y(ny),z(nz){}
};

struct MYMSG {
	int EntityName;
	char state;
	float X;
	float Y;
	float Z;
	float toX;
	float toY;
	float toZ;
	MYMSG(int nEntityName, char nstate, float nx, float ny, float nz, float ntox, float ntoy, float ntoz): 
		EntityName(nEntityName), X(nx), Y(ny), Z(nz), toX(ntox), toY(ntoy), toZ(ntoz)
		{};
};

struct EntityInfo {
	int type;
	Coordinate direction;
	Coordinate coordinate;
	EntityInfo(void){}
	EntityInfo(int t, Coordinate c, Coordinate co):
				type(t), direction(c), coordinate(co){}
};

class CoorManagement {
public:
	CoorManagement(){};
	~CoorManagement(){};
	
	bool addEntity(int newid, int newtype, Coordinate newdir, Coordinate newcoor);
	bool delEntity(int id);
	Coordinate getCoordinate(int id);
	Coordinate getDirection(int id);
	bool changeCoorDirect(int id, Coordinate newdir, Coordinate newcoor);
	bool changeCoorSmooth(int id, Coordinate newdir, Coordinate newcoor);
	int totalNumOfEntities();

	void friend myDisplay();

private:
	unordered_map<int, EntityInfo> Entities;
};

#endif