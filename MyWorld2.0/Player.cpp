#include "Player.h"

Player::Player() {
	speed = 1.0;
	pos = Vector(-10.0, -10.0, 10.0);
	dir = Vector(1.0, 1.0, 0.0);
	up  = Vector(0.0, 0.0, 1.0);
	MyCamera = Camera::getInstance();
	MyCoorMan = CoorMan::getInstance();
	//MyCoorMan->addEntity(1,0,0,Vector(0,0,0),Vector(1,1,0));
}

Player* Player::instance = new Player();

Player* Player::getInstance() {
	
	return instance;
}

Vector Player::getPosition() {
	return pos;
}

Vector Player::getDirection() {
	return dir;
}

Vector Player::getUpVector() {
	return up;
}

void Player::moveByMouse() {
	POINT mousePos;
	long middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; //�õ���Ļ��ȵ�һ��
	long middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; //�õ���Ļ�߶ȵ�һ��
	
	//�õ���ǰ���λ��
    GetCursorPos(&mousePos);
    ShowCursor(FALSE);

	//������û���ƶ�,���ø���
    if ( abs(mousePos.x-middleX)<3 && abs(mousePos.y-middleY)<3 )
        return;

	//�����������ת�Ƕ�
	float angleX = (float)(mousePos.x-middleX)/middleX * 2.5;
	//�����������ת�Ƕ�
	float angleY = (float)(mousePos.y-middleY)/middleY * 3.0;

    //�������λ������Ļ����
    SetCursorPos(middleX, middleY);

	Vector tempH;
	tempH.setX(dir.getX()*cos(angleX) + dir.getY()*sin(angleX));
	tempH.setY(dir.getY()*cos(angleX) - dir.getX()*sin(angleX));

	/*Vector tempV;
	tempV.setZ(dir.getZ()*cos(angleY) - dir.getY()*sin(angleY));*/

	dir.setX(tempH.getX());
	dir.setY(tempH.getY());
	//dir.setZ(tempV.getZ());
	
	//�ı�up����
	/*Vector upVector(upinfo.getX(), upinfo.getY(), upinfo.getZ());
	tempH.setX(upVector.getX()*cos(angleX) + upVector.getY()*sin(angleX));
	tempH.setY(upVector.getY()*cos(angleX) - upVector.getX()*sin(angleX));
	tempV.setZ(upVector.getZ()*cos(angleY) - upVector.getY()*sin(angleY));
	upinfo.setX(tempH.getX());
	upinfo.setY(tempH.getY());
	upinfo.setZ(tempV.getZ());*/

	MyCamera->setCamera(pos.getX(),pos.getY(),pos.getZ(),pos.getX()+dir.getX(),pos.getY()+dir.getY(),pos.getZ()+dir.getZ(),up.getX(),up.getY(),up.getZ());
	MyMsg msg( MY_PLAYER, 1, pos.getX(), pos.getY(), pos.getZ(), dir.getX(), dir.getY(), dir.getZ());
	PostThreadMessage(ThreadMan::getInstance()->getThreadID("internet"), WM_USER+121, (WPARAM)&msg, 1);
	//printf("%f,%f,%f\n",pos.getX(),pos.getY(),pos.getZ());
}

void Player::moveByKeyboard(char d) {
	//���ӽ�ǰ���ƶ�
	if (d == 'w') {
		//��һ��
		dir = dir.normalize();
		//���������ͶӰ
		pos.setX(pos.getX() + dir.getX() * speed);
		pos.setY(pos.getY() + dir.getY() * speed);
	}
	//���ӽǺ��ƶ�
	else if (d == 's') {
		dir = dir.normalize();
		pos.setX(pos.getX() - dir.getX() * speed);
		pos.setY(pos.getY() - dir.getY() * speed);
	}
	//���ӽ����ƶ�
	else if (d == 'a') {
		//��˵���������
		Vector side = dir.crossProduct(up);
		side = side.normalize();
		pos.setX(pos.getX() - side.getX() * speed);
		pos.setY(pos.getY() - side.getY() * speed);
	}
	//���ӽ��ҷ��ƶ�
	else if (d == 'd') {
		Vector side = dir.crossProduct(up);
		//��˵���������
		side = side.normalize();
		pos.setX(pos.getX() + side.getX() * speed);
		pos.setY(pos.getY() + side.getY() * speed);
	}

	MyCamera->setCamera(pos.getX(),pos.getY(),pos.getZ(),pos.getX()+dir.getX(),pos.getY()+dir.getY(),pos.getZ()+dir.getZ(),up.getX(),up.getY(),up.getZ());
	MyMsg msg( MY_PLAYER, 1, pos.getX(), pos.getY(), pos.getZ(), dir.getX(), dir.getY(), dir.getZ());
	PostThreadMessage(ThreadMan::getInstance()->getThreadID("internet"), WM_USER+121, (WPARAM)&msg, 1);
	//printf("%f,%f,%f\n",pos.getX(),pos.getY(),pos.getZ());
}