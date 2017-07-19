#ifndef _INTERNET_H_
#define _INTERNET_H_

#include <windows.h>

#include <STDIO.H>
#include "Common.h"
#include "CoorMan.h"

#pragma  comment(lib,"ws2_32.lib")

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
	static ConnInternet* getInstance();
	~ConnInternet(){};

	void initConn(void);
	void inquireID(void);
	void sendMsg(InternetPackage package);
	void receiveMsg(void);
	void closeSocket(void);
	int getID(void);

private:
	ConnInternet(void);
	ConnInternet(const ConnInternet&){}
	static ConnInternet* instance;
	SOCKET sclient;
	sockaddr_in serAddr;
	int m_id;
	static bool logIn;
	CoorMan *MyCoorMan;
};

#endif