#pragma once
#include "WindowsProject5.h"
//#include "draw_figure.h"

class Torus
{
private:
	POINT3D pt_torus;
	double r_min_torus;
	double r_max_torus;
public:
	POINT3D get_pt_torus();
	double get_r_min_torus();
	double get_r_max_torus();
	void set_pt_torus(POINT3D pt);
	void set_pt_torus(double x, double y, double z);
	void set_r_min_torus(double r_min);
	void set_r_max_torus(double r_max);
	void Draw_torus();
	void CorrectValues();
};