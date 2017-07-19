#ifndef _COMMON_H_
#define _COMMON_H_

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

struct ColorRGBA {
	float R;
	float G;
	float B;
	float A;
	ColorRGBA(void):R(1.0),G(1.0),B(1.0),A(1.0){}
	ColorRGBA(float nR, float nG, float nB, float nA = 1.0):
				R(nR),G(nG),B(nB),A(nA){}
};

#endif