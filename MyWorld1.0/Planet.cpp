#include "planet.h"

int Mecrucy_day = 0;
int Venus_day = 0;
int Earth_day = 0;
int Mars_day = 0;
int Jupiter_day = 0;
int Saturn_day = 0;
int Uranus_day = 0;
int Neptune_day = 0;
int Moon_day = 0;

float ratio1 = 1.0;//行星半径
float ratio2 = 1.0;//公转半径
float ratio3 = 0.3;//公转周期

void planetInit() {
	GLfloat sun_mat_ambient[]  = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat sun_mat_diffuse[]  = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat sun_mat_emission[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat sun_mat_shininess  = 10.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT,	 sun_mat_ambient  );
	glMaterialfv(GL_FRONT, GL_DIFFUSE,	 sun_mat_diffuse  );
	glMaterialfv(GL_FRONT, GL_EMISSION,	 sun_mat_emission );
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
}

void drawGlobalLight() {//定义全局光源，它是一种白色的光源
	GLfloat sun_light_position[] = {1.0f, 0.0f, 0.0f, 0.0f};
	GLfloat sun_light_ambient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat sun_light_diffuse[]  = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat sun_light_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient );
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void drawSunLight() {// 定义中心光源，它是一种白色的光源
	GLfloat sun_light_position[] = {0.0f, 0.0f, 1000.0f, 1.0f};	//如果第四个值W为零，则表示该光源位于无限远处，前三个值表示了它所在的方向
	GLfloat sun_light_ambient[]  = {0.8f, 0.8f, 0.8f, 1.0f};	//该光源所发出的光，经过非常多次的反射后，最终遗留在整个光照环境中的强度（颜色）
	GLfloat sun_light_diffuse[]  = {0.8f, 0.8f, 0.8f, 1.0f};	//该光源所发出的光，照射到粗糙表面时经过漫反射，所得到的光的强度（颜色）
	GLfloat sun_light_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};	//该光源所发出的光，照射到光滑表面时经过镜面反射，所得到的光的强度（颜色）

	glLightfv(GL_LIGHT1, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  sun_light_ambient );
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  sun_light_diffuse );
	glLightfv(GL_LIGHT1, GL_SPECULAR, sun_light_specular);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void drawPlants() {
	glPushAttrib(GL_CURRENT_BIT);
	planetInit();
	//drawSun();
	drawMecrucy();
	drawVenus();
	drawEarth();
	drawMoon();
	drawMars();
	drawJupiter();
	drawSaturn();
	drawUranus();
	drawNeptune();
	glPopAttrib();
}

void drawSun() {
	glutSolidSphere(Suninfo.pla_radius * ratio1, 50, 50);	//绘制：半径,经线精细度,纬线精细度
}

void drawMecrucy() {
	glPushMatrix();
	++Mecrucy_day;
	if (Mecrucy_day >= Mecrucyinfo.rev_period /ratio3)
		Mecrucy_day = 0;
	GLfloat sun_mat_emission[] = {0.5f, 0.5f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,	 sun_mat_emission );
	glRotatef(Mecrucy_day*360./Mecrucyinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Mecrucyinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Mecrucyinfo.pla_radius * ratio1, 50, 50);
	glPopMatrix();
}
void drawVenus() {
	glPushMatrix();
	++Venus_day;
	if (Venus_day >= Venusinfo.rev_period / ratio3)
		Venus_day = 0;
	GLfloat sun_mat_emission[] = {0.5f, 0.5f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,	 sun_mat_emission );
	glRotatef(Venus_day*360./Venusinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Venusinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Venusinfo.pla_radius * ratio1, 50, 50);
	glPopMatrix();
}

void drawEarth() {
	glPushMatrix();
	++Earth_day;
	if (Earth_day >= Earthinfo.rev_period / ratio3)
		Earth_day = 0;
	GLfloat sun_mat_emission[]	= {0.0f, 0.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Earth_day*360./Earthinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Earthinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Earthinfo.pla_radius * ratio1, 30, 30);
}

void drawMoon() {
	++Moon_day;
	if (Moon_day >= Mooninfo.rev_period / ratio3)
		Moon_day = 0;
	GLfloat sun_mat_specular[]	= {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat sun_mat_emission[]	= {0.5f, 0.0f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Moon_day*360./Mooninfo.rev_period * ratio3, 0.0f, 0.0f, 1.0f);
	glTranslatef(Mooninfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Mooninfo.pla_radius * ratio1, 30, 30);
	glPopMatrix();
}

void drawMars() {
	glPushMatrix();
	++Mars_day;
	if (Mars_day >= Marsinfo.rev_period / ratio3)
		Mars_day = 0;
	GLfloat sun_mat_emission[]	= {0.2f, 0.2f, 0.2f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Mars_day*360./Marsinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Marsinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Marsinfo.pla_radius * ratio1, 30, 30);
	glPopMatrix();
}

void drawJupiter() {
	glPushMatrix();
	++Jupiter_day;
	if (Jupiter_day >= Jupiterinfo.rev_period / ratio3)
		Jupiter_day = 0;
	GLfloat sun_mat_emission[]	= {0.2f, 0.2f, 0.2f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Jupiter_day*360./Jupiterinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Jupiterinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Jupiterinfo.pla_radius * ratio1, 30, 30);
	glPopMatrix();
}

void drawSaturn() {
	glPushMatrix();
	++Saturn_day;
	if (Saturn_day >= Saturninfo.rev_period / ratio3)
		Saturn_day = 0;
	GLfloat sun_mat_emission[]	= {0.2f, 0.2f, 0.2f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Saturn_day*360./Saturninfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Saturninfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Saturninfo.pla_radius * ratio1, 30, 30);
	glPopMatrix();
}

void drawUranus() {
	glPushMatrix();
	++Uranus_day;
	if (Uranus_day >= Uranusinfo.rev_period / ratio3)
		Uranus_day = 0;
	GLfloat sun_mat_emission[]	= {0.2f, 0.2f, 0.2f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Uranus_day*360./Uranusinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Uranusinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Uranusinfo.pla_radius * ratio1, 30, 30);
	glPopMatrix();
}

void drawNeptune() {
	glPushMatrix();
	++Neptune_day;
	if (Neptune_day >= Neptuneinfo.rev_period / ratio3)
		Neptune_day = 0;
	GLfloat sun_mat_emission[]	= {0.2f, 0.2f, 0.2f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
	glRotatef(Neptune_day*360./Neptuneinfo.rev_period * ratio3, 0.0f, 0.0f, -1.0f);
	glTranslatef(Neptuneinfo.rev_radius * ratio2, 0.0f, 0.0f);
	glutSolidSphere(Neptuneinfo.pla_radius * ratio1, 30, 30);
	glPopMatrix();
}
