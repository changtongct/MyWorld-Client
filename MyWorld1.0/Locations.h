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
	//��ʼ���ص���������Ķ�Ӧ��ϵ
	Location() {
		LocationCoor[shack] = Coordinate(80.0, -80.0, 10.5);
		LocationCoor[goldmine] = Coordinate(-80.0, 80.0, 10.5);
		LocationCoor[bank] = Coordinate(80.0, 80.0, 10.5);
		LocationCoor[saloon] = Coordinate(-80.0, -80.0, 10.5);
	};
	~Location(){};

	//���ݵص�����ѯ����
	Coordinate* locationCoor(enum location_type pName) {
		if (LocationCoor.find(pName) != LocationCoor.end())
			return &LocationCoor[pName];
		return NULL;
	}

private:
	unordered_map<enum location_type, Coordinate> LocationCoor;

};


#endif