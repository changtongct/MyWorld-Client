#include "Camera.h"

Camera::Camera() {
	/*eyeinfo = Vector(0.0, 0.0, 20000.0);//宇宙
    centerinfo = Vector(0.0, 0.0, 0.0);
    upinfo = Vector(0.0, 1.0, 0.0);*/
	eyeinfo = Vector(0.0, -200.0, 10.0);//大门
	centerinfo = Vector(eyeinfo.getX(), eyeinfo.getY()+1.0, eyeinfo.getZ());
	upinfo = Vector(0.0, 0.0, 1.0);
	speed = 1.0;
	//eyeinfo = Vector(-450.0, -450.0, 100.0);//棋盘
	//centerinfo = Vector(-450.0, -450.0, 0.0);
	//upinfo = Vector(0.0, 1.0, 0.0);
    //speed = 10.0;
}

void Camera::setCamera( float eyeX, float eyeY, float eyeZ,
						float centerX, float centerY, float centerZ,
						float upX, float upY, float upZ) {
	eyeinfo = Vector(eyeX, eyeY, eyeZ);
	centerinfo = Vector(centerX, centerY, centerZ);
	upinfo = Vector(upX, upY, upZ);
	speed = 20.0;
}

void Camera::setViewByMouse() {
	POINT mousePos;
	long middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; //得到屏幕宽度的一半
	long middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; //得到屏幕高度的一半
	
	//得到当前鼠标位置
    GetCursorPos(&mousePos);
    ShowCursor(FALSE);

	//如果鼠标没有移动,则不用更新
    if ( abs(mousePos.x-middleX)<3 && abs(mousePos.y-middleY)<3 )
        return;

	//摄像机左右旋转角度
	float angleX = (float)(mousePos.x-middleX)/middleX * 1.5;
	//摄像机上下旋转角度
	float angleY = (float)(mousePos.y-middleY)/middleY * 2.0;

    //设置鼠标位置在屏幕中心
    SetCursorPos(middleX, middleY);

	Vector directionVector((centerinfo.getX()-eyeinfo.getX()), (centerinfo.getY()-eyeinfo.getY()), (centerinfo.getZ()-eyeinfo.getZ()));
	Vector tempH;
	tempH.setX(directionVector.getX()*cos(angleX) + directionVector.getY()*sin(angleX));
	tempH.setY(directionVector.getY()*cos(angleX) - directionVector.getX()*sin(angleX));

	Vector tempV;
	//tempV.setZ(directionVector.getZ()*cos(angleY) - directionVector.getY()*sin(angleY));

	centerinfo.setX(eyeinfo.getX() + tempH.getX());
	centerinfo.setY(eyeinfo.getY() + tempH.getY());
	//centerinfo.setZ(eyeinfo.getZ() + tempV.getZ());
	
	//改变up向量
	/*Vector upVector(upinfo.getX(), upinfo.getY(), upinfo.getZ());
	tempH.setX(upVector.getX()*cos(angleX) + upVector.getY()*sin(angleX));
	tempH.setY(upVector.getY()*cos(angleX) - upVector.getX()*sin(angleX));
	tempV.setZ(upVector.getZ()*cos(angleY) - upVector.getY()*sin(angleY));
	upinfo.setX(tempH.getX());
	upinfo.setY(tempH.getY());
	upinfo.setZ(tempV.getZ());*/

	MYMSG msg_camera(MY_PLAYER, 1, eyeinfo.getX(), eyeinfo.getY(), eyeinfo.getZ(), centerinfo.getX()-eyeinfo.getX(), centerinfo.getY()-eyeinfo.getY(), centerinfo.getZ()-eyeinfo.getZ());
	PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&msg_camera, 1);
}

void Camera::moveCamera(char d) {
	//向视角前方移动
	if (d == 'w') {
		//方向向量
		Vector direction((eyeinfo.getX()-centerinfo.getX()),(eyeinfo.getY()-centerinfo.getY()),(eyeinfo.getZ()-centerinfo.getZ()));
		//归一化
		Vector n_direction = direction.normalize();
		//计算各方向投影
		eyeinfo.setX(eyeinfo.getX() - n_direction.getX() * speed);
		eyeinfo.setY(eyeinfo.getY() - n_direction.getY() * speed);
		//eyeinfo.setZ(eyeinfo.getZ() - n_direction.getZ() * speed);
		centerinfo.setX(centerinfo.getX() - n_direction.getX() * speed);
		centerinfo.setY(centerinfo.getY() - n_direction.getY() * speed);
		//centerinfo.setZ(centerinfo.getZ() - n_direction.getZ() * speed);
	}
	//向视角后方移动
	else if (d == 's') {
		Vector direction((eyeinfo.getX()-centerinfo.getX()),(eyeinfo.getY()-centerinfo.getY()),(eyeinfo.getZ()-centerinfo.getZ()));
		Vector n_direction = direction.normalize();
		eyeinfo.setX(eyeinfo.getX() + n_direction.getX() * speed);
		eyeinfo.setY(eyeinfo.getY() + n_direction.getY() * speed);
		//eyeinfo.setZ(eyeinfo.getZ() + n_direction.getZ() * speed);
		centerinfo.setX(centerinfo.getX() + n_direction.getX() * speed);
		centerinfo.setY(centerinfo.getY() + n_direction.getY() * speed);
		//centerinfo.setZ(centerinfo.getZ() + n_direction.getZ() * speed);
	}
	//向视角左方移动
	else if (d == 'a') {
		Vector direction((eyeinfo.getX()-centerinfo.getX()),(eyeinfo.getY()-centerinfo.getY()),(eyeinfo.getZ()-centerinfo.getZ()));
		//叉乘得左右向量
		Vector direction1 = direction.crossProduct(upinfo);
		Vector n_direction = direction1.normalize();
		eyeinfo.setX(eyeinfo.getX() + n_direction.getX() * speed);
		eyeinfo.setY(eyeinfo.getY() + n_direction.getY() * speed);
		//eyeinfo.setZ(eyeinfo.getZ() + n_direction.getZ() * speed);
		centerinfo.setX(centerinfo.getX() + n_direction.getX() * speed);
		centerinfo.setY(centerinfo.getY() + n_direction.getY() * speed);
		//centerinfo.setZ(centerinfo.getZ() + n_direction.getZ() * speed);
	}
	//向视角右方移动
	else if (d == 'd') {
		Vector direction((eyeinfo.getX()-centerinfo.getX()),(eyeinfo.getY()-centerinfo.getY()),(eyeinfo.getZ()-centerinfo.getZ()));
		//叉乘得左右向量
		Vector direction1 = direction.crossProduct(upinfo);
		Vector n_direction = direction1.normalize();
		eyeinfo.setX(eyeinfo.getX() - n_direction.getX() * speed);
		eyeinfo.setY(eyeinfo.getY() - n_direction.getY() * speed);
		//eyeinfo.setZ(eyeinfo.getZ() - n_direction.getZ() * speed);
		centerinfo.setX(centerinfo.getX() - n_direction.getX() * speed);
		centerinfo.setY(centerinfo.getY() - n_direction.getY() * speed);
		//centerinfo.setZ(centerinfo.getZ() - n_direction.getZ() * speed);
	}
	
	MYMSG msg_camera(MY_PLAYER, 1, eyeinfo.getX(), eyeinfo.getY(), eyeinfo.getZ(), centerinfo.getX()-eyeinfo.getX(), centerinfo.getY()-eyeinfo.getY(), centerinfo.getZ()-eyeinfo.getZ());
	PostThreadMessage(Internet_ThreadId, WM_USER+121, (WPARAM)&msg_camera, 1);
}

void Camera::setLook() {
	gluLookAt(	eyeinfo.getX(), eyeinfo.getY(), eyeinfo.getZ(),
				centerinfo.getX(), centerinfo.getY(), centerinfo.getZ(),
				upinfo.getX(), upinfo.getY(), upinfo.getZ());
}
