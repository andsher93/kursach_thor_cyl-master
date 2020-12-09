#pragma once
//#include "WindowsProject5.h"
//#include "draw_figure.h"
#include "struct.h"
extern float   g_sceneWidth;
//extern GLUquadricObj* g_pGluQuadObj;
class Cylindr
{
private:
	POINT3D pt_cyl;
	double r_cyl;
	double height;		//height = g_sceneWidth - g_sceneWidth / 8
public:
	POINT3D get_pt_cyl();
	double get_r_cyl();
	void set_pt_cyl(POINT3D pt);
	void set_pt_cyl(double, double, double);
	void set_r_cyl(double radius);
	void set_height(double h);
	double get_height();
	//void Draw_cyl(GLUquadricObj* g_pGluQuadObj);
	void draw_cyl();
	Cylindr(POINT3D center, double rad, double height);
	Cylindr();
	void CorrectValues();
	//void draw_cyl();
};