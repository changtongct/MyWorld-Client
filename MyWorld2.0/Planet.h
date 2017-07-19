#ifndef __PLANET_H__
#define __PLANET_H__

#include <windows.h>
#include <math.h>
#include <glut.h>

struct plant_info {
	float pla_radius;	//千米
	float rev_radius;	//万千米
	float rev_period;	//天
};

const struct plant_info Suninfo		= {0.0,		0.,		0.}; //{696000, 0, 0};
const struct plant_info Mooninfo	= {33.98,	108,	30.};//{3398, 38, 30};
const struct plant_info Mecrucyinfo = {24.39,	779.,	88.};//{2439, 5790, 88};
const struct plant_info Venusinfo	= {60.52,	882.,	225.};//{6052, 10820, 225};
const struct plant_info Earthinfo	= {63.78,	1250.,	365.};//{6378, 14960, 365};
const struct plant_info Marsinfo	= {33.98,	1479.,	687.};//{3398, 22790, 687};
const struct plant_info Jupiterinfo = {713.98,	3783.,	4329.};//{71398, 77830, 4329};
const struct plant_info Saturninfo	= {603.3,	6270.,	10768.};//{60330, 142700, 10768};
const struct plant_info Uranusinfo	= {254.0,	8123.,	30660.};//{25400, 288230, 30660};
const struct plant_info Neptuneinfo = {246.0,	9239.,	60152.};//{24600, 452390, 60152};

void planetInit();
void drawGlobalLight();
void drawSunLight();

void drawPlants();
void drawSun();
void drawMecrucy();
void drawVenus();
void drawEarth();
void drawMoon();
void drawMars();
void drawJupiter();
void drawSaturn();
void drawUranus();
void drawNeptune();

#endif