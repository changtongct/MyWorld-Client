#include <windows.h>
#include <glut.h>

#include "ThreadMan.h"
#include "Display.h"
#include "Camera.h"
#include "Player.h"
#include "Internet.h"

DWORD WINAPI displayThread(LPVOID pM);
DWORD WINAPI inputThread(LPVOID pM);
DWORD WINAPI internetThread(LPVOID pM);
DWORD WINAPI internetThread1(LPVOID pM);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	//绘图线程
	HANDLE handle_Dispaly = CreateThread(NULL, 0, displayThread, NULL, 0, NULL);	//NULL/栈大小/函数/参数结构体指针/标志0:立即激活/ID
	HANDLE handle_Input = CreateThread(NULL, 0, inputThread, NULL, 0, NULL);
	HANDLE handle_Internet = CreateThread(NULL, 0, internetThread, NULL, 0, NULL);
	HANDLE handle_Internet1 = CreateThread(NULL, 0, internetThread1, NULL, 0, NULL);

	WaitForSingleObject(handle_Dispaly, INFINITE);
	WaitForSingleObject(handle_Input, INFINITE);
	WaitForSingleObject(handle_Internet, INFINITE);
	WaitForSingleObject(handle_Internet1, INFINITE);

	return 0;
}

DWORD WINAPI displayThread(LPVOID pM) {
	//glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);  //RGB模式|双缓冲
    glutInitWindowPosition(600, 200);
    glutInitWindowSize(800, 800);
	glutCreateWindow("SecondWorld");
	glutReshapeFunc(reshape);
	glutDisplayFunc(myDisplay);
	glutPassiveMotionFunc(motion);
	//glutMouseFunc(processMouse);
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(&SpecialKey);
	glutTimerFunc(16, &OnTimer, 1);
	glutMainLoop();

	return 0;
}
void reshape(int width, int height) {
	Camera *myCamera = Camera::getInstance();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / height, 0.1, 10000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	myCamera->setLook();
	//gluLookAt(0, -1000, 1000, centerinfo[0], centerinfo[1], centerinfo[2], 0, 0, 1);
	//printf("%f,%f,%f\n",centerinfo[0],centerinfo[1],centerinfo[2]);
}

DWORD WINAPI inputThread(LPVOID pM) {
	//glutPassiveMotionFunc(motion);
	//glutMouseFunc(processMouse);
	//glutKeyboardFunc(keyboard);
	//glutSpecialFunc(&SpecialKey);

	return 0;
}

void keyboard(unsigned char key, int x, int y) {
	Player *myPlayer = Player::getInstance();
	switch (key) {
		case 'w': myPlayer->moveByKeyboard('w');
			break;
		case 's': myPlayer->moveByKeyboard('s');
			break;
		case 'a': myPlayer->moveByKeyboard('a');
			break;
		case 'd': myPlayer->moveByKeyboard('d');
			break;
		/*case 'e': drawMaze();
			break;*/
		case 27:/*printf("\n程序将在3秒后关闭...");
				Sleep(1000);*/
				printf("\n程序将在2秒后关闭...");
				Sleep(1000);
				printf("\n程序将在1秒后关闭...");
				Sleep(1000);
				ExitProcess(0);
			break;
    }
}

void motion(int x, int y) {
	Player *myPlayer = Player::getInstance();
	myPlayer->moveByMouse();
}

DWORD WINAPI internetThread(LPVOID pM) {
	ThreadMan::getInstance()->addThreadID("internet", GetCurrentThreadId());
	
	CoorMan* myCoorMan = CoorMan::getInstance();
	ConnInternet *myInternet = ConnInternet::getInstance();

	MSG msg;
	int bRet;
	while ( (bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
			ExitThread(0);
		//来自camera，发送PLAYER坐标变换
		if (((MyMsg*)msg.wParam)->EntityName == MY_PLAYER) {
			myInternet->sendMsg(InternetPackage(CHECK_BYTE, 1, LOG_ONLINE, 0, myInternet->getID(),\
				((MyMsg*)msg.wParam)->X,((MyMsg*)msg.wParam)->Y,((MyMsg*)msg.wParam)->Z,\
				((MyMsg*)msg.wParam)->toX,((MyMsg*)msg.wParam)->toY,((MyMsg*)msg.wParam)->toZ));
		}
		if (((MyMsg*)msg.wParam)->EntityName == MY_BULLET) {
			printf("呵呵\n");
			myInternet->sendMsg(InternetPackage(CHECK_BYTE, 2, BULLET_NEW, 0, 0,\
				myCoorMan->getPosition(myInternet->getID()).getX(),  myCoorMan->getPosition(myInternet->getID()).getY(),\
				myCoorMan->getPosition(myInternet->getID()).getZ(),  myCoorMan->getDirection(myInternet->getID()).getX(),\
				myCoorMan->getDirection(myInternet->getID()).getY(),  myCoorMan->getDirection(myInternet->getID()).getZ()));
		}
	}

	return 0;
}

DWORD WINAPI internetThread1(LPVOID pM) {
	ConnInternet *myInternet = ConnInternet::getInstance();
	myInternet->receiveMsg();

	return 0;
}