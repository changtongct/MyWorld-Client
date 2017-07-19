#ifndef _COMMON_H_
#define _COMMON_H_

#define SERVER_IP "123.207.84.70"
#define SERVER_PORT 9999

#define	CHECK_BYTE		123
#define	LOG_ALLOC_ID	1
#define	LOG_IN			2
#define	LOG_ONLINE		3
#define	LOG_OFF			4


#define MY_BOX 1
#define MY_SPHERE 2
#define MY_BULLET 555
#define MY_PLAYER 4

#define BULLET_NEW 30
#define BULLET_MOVE 31
#define BULLET_DEL 32

#define MY_FLOOR_HEIGHT 0.0

struct MyMsg {
	int EntityName;
	char state;
	float X;
	float Y;
	float Z;
	float toX;
	float toY;
	float toZ;
	MyMsg(int nEntityName, char nstate, float nx, float ny, float nz, float ntox, float ntoy, float ntoz): 
		EntityName(nEntityName), X(nx), Y(ny), Z(nz), toX(ntox), toY(ntoy), toZ(ntoz)
		{};
};

#endif