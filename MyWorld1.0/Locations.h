#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "CoorManagement.h"
#include <unordered_map>

using namespace std;

enum location_type {
	shack,
	goldmine,
	bank,
	saloon
};

class Location {

public:
	//初始化地点名和坐标的对应关系
	Location() {
		LocationCoor[shack] = Coordinate(80.0, -80.0, 10.5);
		LocationCoor[goldmine] = Coordinate(-80.0, 80.0, 10.5);
		LocationCoor[bank] = Coordinate(80.0, 80.0, 10.5);
		LocationCoor[saloon] = Coordinate(-80.0, -80.0, 10.5);
	};
	~Location(){};

	//根据地点名查询坐标
	Coordinate* locationCoor(enum location_type pName) {
		if (LocationCoor.find(pName) != LocationCoor.end())
			return &LocationCoor[pName];
		return NULL;
	}

private:
	unordered_map<enum location_type, Coordinate> LocationCoor;

};


#endif