#ifndef __COORMAN_H__
#define __COORMAN_H__

#include <Windows.h>
#include <unordered_map>
using namespace std;

#include "Vector.h"
#include "Display.h"

extern CRITICAL_SECTION C_COOR;

struct EntityInfo {
	char type;
	char state;
	Vector pos;
	Vector dir;
	EntityInfo(void){}
	EntityInfo(char t, char s, Vector p, Vector d):
				type(t), state(s), pos(p), dir(d){}
};

class CoorMan {
public:
	static CoorMan* getInstance();
	~CoorMan(){};
	
	bool addEntity(int nid, char ntype, char nstate, Vector npos, Vector ndir);
	bool delEntity(int id);
	Vector getPosition(int id);
	Vector getDirection(int id);
	bool changePosDirect(int id, Vector npos);
	//bool changePosSmooth(int id, Vector npos);
	bool changeDirDirect(int id, Vector ndir);
	int totalNumOfEntities();

	void friend myDisplay();

private:
	CoorMan();
	CoorMan(const CoorMan&){}
	static CoorMan* instance;
	CRITICAL_SECTION C_COOR;
	unordered_map<int, EntityInfo> Entities;
};

#endif