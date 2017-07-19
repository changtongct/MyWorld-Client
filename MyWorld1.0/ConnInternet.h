#ifndef _CONNINTERNET_H_
#define _CONNINTERNET_H_

#include <windows.h>
//#include <WINSOCK2.H>

#include <STDIO.H>
#include "Common.h"
#include "CoorManagement.h"

#pragma  comment(lib,"ws2_32.lib")

extern CoorManagement AllEntity;

struct InternetPackage {
	char check;	//校验位，判断包的合法性
	char ptype;	//包类型
	char state;
	char reserve;
	int id;
	float X;
	float Y;
	float Z;
	float toX;
	float toY;
	float toZ;
	InternetPackage(void){}
	InternetPackage(char c, char t, char s, char r, int i, float x, float y, float z, float tox, float toy, float toz):
				check(c), ptype(t), state(s), reserve(r), id(i), X(x), Y(y), Z(z), toX(tox), toY(toy), toZ(toz){}
};

class ConnInternet {
public:
	static ConnInternet* Instance();
	~ConnInternet(){};

	void sendMsg(InternetPackage package);
	void receiveMsg(void);
	void closeSocket(void);
	int getID(void);

private:
	ConnInternet(void);
	ConnInternet(const ConnInternet&){}
	SOCKET sclient;
	sockaddr_in serAddr;
	int m_id;
	static bool logIn;
};

#endif