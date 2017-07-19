#include <windows.h>
#include "Common.h"
#include "Locations.h"
#include "Miner.h"
#include "EntityNames.h"
#include "myDisplay.h"
#include "CoorManagement.h"
#include "Statemachine.h"
#include "Camera.h"
#include "CoorManagement.h"
#include "ConnInternet.h"
#include "GAME_Maze.h"

//全局运行速度
const float SPEED = 0.5;
DWORD CoorMan_ThreadId;
DWORD Internet_ThreadId;
//坐标管理类
CoorManagement AllEntity;
//地点名转坐标类
Location AllLocation;
Miner miner(ent_Miner_Bob);
Camera myCamera;

int v;

DWORD WINAPI displayThread(LPVOID pM);
DWORD WINAPI FSMThread(LPVOID pM);
DWORD WINAPI CoorManThread(LPVOID pM);
DWORD WINAPI ConnInternetThread(LPVOID pM);
DWORD WINAPI ConnInternetThreadR(LPVOID pM);

void keyboard(unsigned char key, int x, int y);
void reshape(int width, int height);


int main(int argc, char *argv[]) {
	AllEntity.addEntity(1, MY_SPHERE, Coordinate(1,1,1), Coordinate(-20.0, -20.0, 10.5));
	glutInit(&argc, argv);

	//绘图线程
	HANDLE handle_Dispaly = CreateThread(NULL, 0, displayThread, NULL, 0, NULL);
	//世界逻辑线程
	HANDLE handle_FSM = CreateThread(NULL, 0, FSMThread, NULL, 0, NULL);
	//坐标管理线程
	HANDLE handle_CoorMan = CreateThread(NULL, 0, CoorManThread, NULL, 0, NULL);
	//网络服务线程
	HANDLE handle_Internet = CreateThread(NULL, 0, ConnInternetThread, NULL, 0, NULL);
	HANDLE handle_InternetR = CreateThread(NULL, 0, ConnInternetThreadR, NULL, 0, NULL);

	WaitForSingleObject(handle_Dispaly, INFINITE);
	WaitForSingleObject(handle_FSM, INFINITE);
	WaitForSingleObject(handle_CoorMan, INFINITE); 
	WaitForSingleObject(handle_Internet, INFINITE); 
	WaitForSingleObject(handle_InternetR, INFINITE); 

	system("pause");
	return 0;
}

void drawMaze() {
	GAME_Maze my_GAME_Maze(100, 100, Coordinate(-500,-500,0.5));
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': myCamera.moveCamera('w');
			break;
		case 's': myCamera.moveCamera('s');
			break;
		case 'a': myCamera.moveCamera('a');
			break;
		case 'd': myCamera.moveCamera('d');
			break;
		case 'e': drawMaze();
			break;
		case 27:/*printf("\n程序将在3秒后关闭...");
				Sleep(1000);*/
				printf("\n程序将在2秒后关闭...");
				Sleep(1000);
				printf("\n程序将在1秒后关闭...");
				Sleep(1000);
				ExitProcess(0);
			break;
    }
	//glutPostRedisplay();
}

void SpecialKey(GLint key, GLint x, GLint y) {
	switch (key) {
		case GLUT_KEY_UP : v=1;PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&v, 1);
						//AllEntity.changeCoorDirect( 1, Coordinate(AllEntity.getCoordinate(1).x, AllEntity.getCoordinate(1).y+10));
			break; 
		case GLUT_KEY_DOWN :  v=2;PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&v, 1);
						//AllEntity.changeCoorDirect( 1, Coordinate(AllEntity.getCoordinate(1).x, AllEntity.getCoordinate(1).y-10));
			break;
		case GLUT_KEY_LEFT : v=3;PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&v, 1);
						//AllEntity.changeCoorDirect( 1, Coordinate(AllEntity.getCoordinate(1).x-10, AllEntity.getCoordinate(1).y));
			break;
		case GLUT_KEY_RIGHT : v=4;PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&v, 1);
						//AllEntity.changeCoorDirect( 1, Coordinate(AllEntity.getCoordinate(1).x+10, AllEntity.getCoordinate(1).y));
			break;
	}
}

void motion(int x, int y) {
	myCamera.setViewByMouse();
	//glutPostRedisplay();
}

void processMouse(int button, int state,int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		MYMSG msg_bullet(MY_BULLET, BULLET_NEW, 0, 0, 0, 0, 0, 0);
		PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&msg_bullet, 1);
	}
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / height, 0.1, 10000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	myCamera.setLook();
	//gluLookAt(0, -1000, 1000, centerinfo[0], centerinfo[1], centerinfo[2], 0, 0, 1);
	//printf("%f,%f,%f\n",centerinfo[0],centerinfo[1],centerinfo[2]);
}

DWORD WINAPI displayThread(LPVOID pM) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);  //RGB模式|双缓冲
    glutInitWindowPosition(600, 200);
    glutInitWindowSize(800, 800);
	glutCreateWindow("MyWorld");
	glutReshapeFunc(reshape);
	glutDisplayFunc(&myDisplay);
	glutPassiveMotionFunc(motion);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(&SpecialKey);
	glutIdleFunc(&myDisplay);
	glutMainLoop();

	return 0;
}

DWORD WINAPI FSMThread(LPVOID pM) {
    Sleep(500 * SPEED);
	/*for (int i=0; i<20; ++i) {
		globalUpdate();
		miner.Update();
		Coordinate *temp = AllLocation.locationCoor(miner.Location());
		MYMSG mymsg(1,temp->x, temp->y, temp->z);
		PostThreadMessage(CoorMan_ThreadId, WM_USER+121, (WPARAM)&mymsg, 1);
		Sleep(1000 * SPEED);
	}*/

	return 0;
}

DWORD WINAPI CoorManThread(LPVOID pM) {
	//CoorMan_ThreadId = GetCurrentThreadId();
	//MSG msg;
	//int bRet;
	////阻塞式读取消息队列
	//while ( (bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
	//	if (bRet == -1)
	//		ExitThread(CoorMan_ThreadId);
	//	//读取消息内容，并操纵坐标平滑改变
	//	AllEntity.changeCoorSmooth( ((MYMSG*)msg.wParam)->EntityName,
	//								Coordinate(0,0,0),
	//								Coordinate(((MYMSG*)msg.wParam)->X,
	//								((MYMSG*)msg.wParam)->Y,0));
	//}
	
	return 0;
}

DWORD WINAPI ConnInternetThread(LPVOID pM) {
	ConnInternet *MyConnect = ConnInternet::Instance();

	Internet_ThreadId = GetCurrentThreadId();

	MSG msg;
	int bRet;
	while ( (bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
			ExitThread(Internet_ThreadId);
		//来自camera，发送PLAYER坐标变换
		if (((MYMSG*)msg.wParam)->EntityName == MY_PLAYER) {
			MyConnect->sendMsg(InternetPackage(CHECK_BYTE, 1, LOG_ONLINE, 0, MyConnect->getID(),\
				((MYMSG*)msg.wParam)->X,((MYMSG*)msg.wParam)->Y,((MYMSG*)msg.wParam)->Z,\
				((MYMSG*)msg.wParam)->toX,((MYMSG*)msg.wParam)->toY,((MYMSG*)msg.wParam)->toZ));
		}
		if (((MYMSG*)msg.wParam)->EntityName == MY_BULLET) {
			printf("呵呵\n");
			MyConnect->sendMsg(InternetPackage(CHECK_BYTE, 2, BULLET_NEW, 0, 0,\
				AllEntity.getCoordinate(MyConnect->getID()).x,  AllEntity.getCoordinate(MyConnect->getID()).y,\
				AllEntity.getCoordinate(MyConnect->getID()).z,  AllEntity.getDirection(MyConnect->getID()).x,\
				AllEntity.getDirection(MyConnect->getID()).y, AllEntity.getDirection(MyConnect->getID()).z));
		}
		
		//读取消息内容，并操纵坐标平滑改变
		/*if (*((int*)msg.wParam) == 1) {
			MyConnect->sendMsg(InternetPackage(CHECK_BYTE,1,LOG_ONLINE,4,1,AllEntity.getCoordinate(1).x,AllEntity.getCoordinate(1).y+10,AllEntity.getCoordinate(1).z,6,7,12.625));
		}
		if (*((int*)msg.wParam) == 2) {
			MyConnect->sendMsg(InternetPackage(CHECK_BYTE,1,LOG_ONLINE,4,1,AllEntity.getCoordinate(1).x,AllEntity.getCoordinate(1).y-10,AllEntity.getCoordinate(1).z,6,7,12.625));
		}
		if (*((int*)msg.wParam) == 3) {
			MyConnect->sendMsg(InternetPackage(CHECK_BYTE,1,LOG_ONLINE,4,1,AllEntity.getCoordinate(1).x-10,AllEntity.getCoordinate(1).y,AllEntity.getCoordinate(1).z,6,7,12.625));
		}
		if (*((int*)msg.wParam) == 4) {
			MyConnect->sendMsg(InternetPackage(CHECK_BYTE,1,LOG_ONLINE,4,1,AllEntity.getCoordinate(1).x+10,AllEntity.getCoordinate(1).y,AllEntity.getCoordinate(1).z,6,7,12.625));
		}*/
	}

	return 0;
}

DWORD WINAPI ConnInternetThreadR(LPVOID pM) {

	ConnInternet *MyConnect = ConnInternet::Instance();

	MyConnect->receiveMsg();

	return 0;
}