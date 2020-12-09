#pragma once
#ifndef INTERS_H
#define INTERS_H
#include "WindowsProject5.h"
//#include "draw_figure.h"

void  inters_2_circle(POINT3D pt1, POINT3D pt2, double r1, double r2, POINT3D mas_pt[]);
void inters_line_circle(POINT3D pt1, POINT3D pt2, POINT3D pt3, double r, POINT3D mas_pt[]);
double distance(POINT3D pt1, POINT3D pt2);
void Polyr_poisk(POINT3D* pt_input, POINT3D* pt_output);
void intersection();
//int Draw_inters(POINT3D Mas_output[2], POINT3D krug_rez);
int get_spiral_center(GLfloat r_max, POINT3D SPIRAL_center[800]);

#endif