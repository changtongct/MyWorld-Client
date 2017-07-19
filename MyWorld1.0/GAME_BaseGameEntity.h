#ifndef __GAME_BASEGAMEENTITY_H__
#define __GAME_BASEGAMEENTITY_H__

#include "CoorManagement.h"

class GAME_BaseGameEntity {
public:
	GAME_BaseGameEntity() {
		SetID();
	};
	virtual ~GAME_BaseGameEntity(){};
	int getID()const {return g_ID;}
	void setHeight(int h) {height = h;}
	void setWidth(int w) {width = w;}
	void setCoor(Coordinate c) {origin_point = c;}

	int getHeight() {return height;}
	int getWidth() {return width;}
	Coordinate getOriginCoor() {return origin_point;}

private:
	int g_ID;
	static int  g_NextValidID;
	int height;
	int width;
	Coordinate origin_point;
	void SetID();
};

#endif