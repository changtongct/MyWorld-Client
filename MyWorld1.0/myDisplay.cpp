#include "myDisplay.h"

void InitDisplay() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//开启后reshape不起作用
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(60, 1, 10.0, 1000000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	myCamera.setLook();
	//gluLookAt(100, 100, 15.0, centerinfo[0], centerinfo[1], centerinfo[2], 0, 0, 1);
}

void myDisplay() {
	Sleep(1000);
	InitDisplay();

	//drawGlobalLight();
	drawSunLight();
	drawPlants();

	drawGround(500.5, 500.5);
	drawGrid(500.0, 500.0);
	//drawCoordinateAxis();

	unordered_map<int, EntityInfo>::iterator all_c_iter;
	for (all_c_iter=AllEntity.Entities.begin();all_c_iter!=AllEntity.Entities.end();++all_c_iter) {
		switch (all_c_iter->second.type) {
			case MY_BOX : drawBox(all_c_iter->second.coordinate, all_c_iter->second.direction);
				break;
			case MY_SPHERE : drawPerson(all_c_iter->second.coordinate, all_c_iter->second.direction);
				break;
			case MY_PLAYER : drawPlayer(all_c_iter->second.coordinate, all_c_iter->second.direction);
				break;
			case MY_BULLET : {printf("%f,%f,%f,%f\n",AllEntity.getCoordinate(all_c_iter->first).x,AllEntity.getCoordinate(all_c_iter->first).y,AllEntity.getCoordinate(all_c_iter->first).z);
								drawBullet(all_c_iter->second.coordinate, all_c_iter->second.direction);
								Coordinate tempc = AllEntity.getCoordinate(all_c_iter->first);
								Coordinate tempd = AllEntity.getDirection(all_c_iter->first);
								if (tempc.x < -500 || tempc.x > 500 || tempc.y < -500 || tempc.y > 500 || tempc.z < 0 || tempc.z > 100 ) {
									if (all_c_iter == AllEntity.Entities.begin()) {
										AllEntity.changeCoorDirect(all_c_iter->first,tempd,Coordinate(0,0,-1));
									}
									else {
										unordered_map<int, EntityInfo>::iterator temp_iter = all_c_iter;
										--all_c_iter;
										AllEntity.Entities.erase(temp_iter);
									}
								}
								else
									AllEntity.changeCoorDirect(all_c_iter->first,tempd,Coordinate(tempc.x+tempd.x*0.5,tempc.y+tempd.y*0.5,tempc.z+tempd.z*0.05));
							 }
				break;
			default:
				break;
		}
	}

	glFlush();
	glutSwapBuffers();
	Sleep(10);
}

void drawGround(float length, float width) {
	glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

	glTranslatef(0.0, 0.0, 0.0);
	GLfloat sun_mat_ambient[]  = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat sun_mat_diffuse[]  = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat sun_mat_emission[] = {0.1f, 0.1f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glRectf(-length, -width, length, width);

	glPopMatrix();
    glPopAttrib();
}

void drawGrid(float x, float y) {
	glDisable(GL_LIGHTING);
	//保存当前属性
    glPushAttrib(GL_CURRENT_BIT);
	//压入堆栈
    glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
    glColor3f(1.0, 0.0, 0.0);
    //在X,Z平面上绘制网格
    for (float i = -x; i <= x; i += x/5.0)
    {
		glLineWidth(1.0f);
        glBegin(GL_LINES);

        glVertex3f(-y, i, 0);
        glVertex3f(y, i, 0);

        glVertex3f(i, -y, 0);
        glVertex3f(i, y, 0);

        glEnd();
    }
    glPopMatrix();
    glPopAttrib();
	glEnable(GL_LIGHTING);
}

void drawCoordinateAxis() {
	glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	gluCylinder(quadratic, 5.0, 1.0, 100.0, 10,10);
	//glRotatef();
	gluCylinder(quadratic, 5.0, 1.0, 100.0, 10,10);
	//glRotatef();
	gluCylinder(quadratic, 5.0, 1.0, 100.0, 10,10);

	glPopMatrix();
    glPopAttrib();
}

void drawBox(Coordinate coor, Coordinate newdir) {
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	float dSize = 0.5;
	glTranslatef(coor.x, coor.y, coor.z);
	
	GLfloat mat_ambient[]  = {0.5f, 0.3f, 0.3f, 1.0f};
	GLfloat mat_diffuse[]  = {0.5f, 0.3f, 0.3f, 1.0f};
	GLfloat mat_emission[] = {0.2f, 0.1f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	////////////////////////
	glBegin(GL_QUADS);
	//上
	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d(dSize, dSize, dSize);
	glVertex3d(-dSize, dSize, dSize);
	glVertex3d(-dSize, -dSize, dSize);
	glVertex3d(dSize, -dSize, dSize);
	//下
	glNormal3d(0.0, 0.0, -1.0);
	glVertex3d(dSize, dSize, -dSize);
	glVertex3d(-dSize, dSize, -dSize);
	glVertex3d(-dSize, -dSize, -dSize);
	glVertex3d(dSize, -dSize, -dSize);
	//前
	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d(dSize, dSize, dSize);
	glVertex3d(dSize, -dSize, dSize);
	glVertex3d(dSize, -dSize, -dSize);
	glVertex3d(dSize, dSize, -dSize);
	//后
	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(-dSize, dSize, dSize);
	glVertex3d(-dSize, dSize, -dSize);
	glVertex3d(-dSize, -dSize, -dSize);
	glVertex3d(-dSize, -dSize, dSize);
	//左
	glNormal3d(0.0, -1.0, 0.0);
	glVertex3d(dSize, -dSize, dSize);
	glVertex3d(dSize, -dSize, -dSize);
	glVertex3d(-dSize, -dSize, -dSize);
	glVertex3d(-dSize, -dSize, dSize);
	//右
	glNormal3d(0.0, 1.0, 0.0);
	glVertex3d(dSize, dSize,dSize);
	glVertex3d(dSize, dSize, -dSize);
	glVertex3d(-dSize, dSize, -dSize);
	glVertex3d(-dSize, dSize, dSize);
	glEnd();  
	///////////////////////
	glPopMatrix();
    glPopAttrib();
}

void drawPerson(Coordinate coor, Coordinate newdir) {
	/*glDisable(GL_LIGHTING);*/
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	
	GLfloat mat_ambient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat mat_diffuse[]  = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glTranslatef(coor.x, coor.y, 15.0);
	glutSolidSphere(10.0, 20, 20);

	glPopMatrix();
    glPopAttrib();
	/*glEnable(GL_LIGHTING);*/
}

void drawPlayer(Coordinate coor, Coordinate newdir) {
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	
	GLfloat mat_ambient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat mat_diffuse[]  = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat mat_emission[] = {1.0f, 0.0f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glTranslatef(coor.x, coor.y, coor.z - 5);/////////////////////////////////////////
	glutSolidSphere(3.0, 20, 20);
	glTranslatef(newdir.x*3, newdir.y*3, newdir.z*3);
	glutSolidSphere(2.0, 20, 20);
	glTranslatef(newdir.x*3, newdir.y*2, newdir.z*2);
	glutSolidSphere(1.0, 20, 20);

	glPopMatrix();
    glPopAttrib();
}

void drawBullet(Coordinate coor, Coordinate newdir) {
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	
	GLfloat mat_ambient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat mat_diffuse[]  = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat mat_emission[] = {1.0f, 0.0f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glTranslatef(coor.x, coor.y, coor.z);
	//glRotatef(newdir.x*3, newdir.y*2, newdir.z*2, -1.0f);
	GLUquadricObj *g; 
	g = gluNewQuadric();
	gluCylinder(g,0.1,0.1,0.5,8,3);

	glPopMatrix();
    glPopAttrib();
}