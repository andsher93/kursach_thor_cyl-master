#include "inters.h"
//#include "draw_figure.h"
extern float   g_sceneWidth;

POINT3D pt1, pt2, pt_rez[4] = { 0 }, pt_rez_vnut[4] = { 0 };
POINT3D SPIRAL_center[800] = {};
POINT3D Krug[2], Krug_rez_left[50] = { 0 }, Krug_rez_right[50];
POINT3D	Start[2] = { 0, 0, 0 }, center = { 0, 0, 0 }, Mas_output[2] = { 0, 0, 0 };
extern GLfloat r_max;
int Kol_center_spiral = 0;
//*****************************************************************
//*                     inters_2_circle                           *
//*                     ===============                           *
//*            Пересечение двух окружностей                       * 
//*****************************************************************
void inters_2_circle(POINT3D pt1, POINT3D pt2, double r1, double r2, POINT3D mas_pt[])
{

	double   x1, y1, x2, y2, a, b, c, e, D, _b,
		xr1, yr1, xr2, yr2, sinu;

	x1 = 0.0;
	y1 = 0.0;
	x2 = pt2.x - pt1.x;
	y2 = pt2.y - pt1.y;

	c = (r2 * r2 - x2 * x2 - y2 * y2 - r1 * r1) / -2.0;

	a = y2 * y2 + x2 * x2;

	b = -2.0 * y2 * c;

	_b = -b;

	e = c * c - r1 * r1 * x2 * x2;

	D = fabs(b * b - 4.0 * a * e);

	yr1 = (_b + sqrt(D)) / (2.0 * a);
	yr2 = (_b - sqrt(D)) / (2.0 * a);


	if (fabs(x2) > 0.0001)
	{
		xr1 = (c - yr1 * y2) / x2;
		xr2 = (c - yr2 * y2) / x2;
	}
	else
	{
		xr1 = sqrt(r1 * r1 - yr1 * yr1);
		xr2 = -xr1;
	}

	mas_pt[0].x = pt1.x + xr1;
	mas_pt[0].y = pt1.y + yr1;

	mas_pt[1].x = pt1.x + xr2;
	mas_pt[1].y = pt1.y + yr2;

}


//********************************************************************
//*                     inters_line_circle                           *
//*                     ==================                           *
//*            Пересечение отрезка с окружностью                     * 
//*  Возвращает список точек пересечения, первым элементом которого  *
//*    является точка пересечения, находящаяся внутри отрезка        *
//********************************************************************
void inters_line_circle(POINT3D pt1, POINT3D pt2, POINT3D pt3, double r, POINT3D mas_pt[])
{
	mas_pt[0] = { 0 };
	mas_pt[1] = { 0 };
	double   x1, y1, x2, y2, x3, y3, a, b, _b, c, D,
		x21, y21, x13, y13, u1, u2,
		d1, d2;
	POINT3D   ptr1, ptr2;

	x1 = pt1.x;
	y1 = pt1.y;
	x2 = pt2.x;
	y2 = pt2.y;
	x3 = pt3.x;
	y3 = pt3.y;
	x21 = x2 - x1;
	y21 = y2 - y1;
	x13 = x1 - x3;
	y13 = y1 - y3;

	a = x21 * x21 + y21 * y21;

	b = 2.0 * (x21 * x13 + y21 * y13);

	_b = -b;

	c = (x3 * x3 + y3 * y3 + x1 * x1 + y1 * y1) - 2.0 * (x3 * x1 + y3 * y1) - r * r;

	D = sqrt(b * b - 4.0 * a * c);
	if (D >= 0) {
		u1 = (_b + D) / (2.0 * a);

		u2 = (_b - D) / (2.0 * a);

		ptr1.x = x1 + u1 * x21;
		ptr1.y = y1 + u1 * y21;

		ptr2.x = x1 + u2 * x21;
		ptr2.y = y1 + u2 * y21;

		d1 = distance(ptr1, pt1) + distance(ptr1, pt2);
		d2 = distance(ptr2, pt1) + distance(ptr2, pt2);

		if (d1 < d2)
		{
			mas_pt[0] = ptr1;
			mas_pt[1] = ptr2;
		}
		else
		{
			mas_pt[0] = ptr2;
			mas_pt[1] = ptr1;
		}
	}

}

double distance(POINT3D pt1, POINT3D pt2)
{
	double x21, y21;

	x21 = pt2.x - pt1.x;
	y21 = pt2.y - pt1.y;

	return (sqrt(x21 * x21 + y21 * y21));
}


void Polyr_poisk(POINT3D* pt_input, POINT3D* pt_output) {
	double F_first = 0, Fi, F_last = 0, D_fi;
	double R = g_sceneWidth / 4;
	glTranslatef(0, -g_sceneWidth / 4, 0);
	double dz = 5 / 2;

	int  i = 0, j = 0;
	F_first = atan((pt_input[0].y + R) / pt_input[0].x);
	F_last = atan((pt_input[1].y + R) / pt_input[1].x);
	D_fi = (F_last - F_first) / N_delta;


	for (Fi = F_first, i = 0, j = 0; Fi < F_last + D_fi; i++, j++, Fi += D_fi) {

		pt_output[i].x = R * cos(Fi);
		pt_output[i].y = (R * sin(Fi)) - R;
		pt_output[i].z = 0;
	}

	for (Fi = F_first, i = 0, j = 0; F_last + D_fi < Fi; i++, j++, Fi += D_fi) {

		pt_output[i].x = -R * cos(Fi);
		pt_output[i].y = -(R * sin(Fi)) - R;
		pt_output[i].z = 0;
	}

	glTranslatef(0, g_sceneWidth / 4, 0);

}

void intersection()
{

	int Kol_center_spiral = get_spiral_center(r_max, SPIRAL_center);
	pt1 = { 0, 0, 0 };
	pt2 = { 0, -g_sceneWidth / 4, 0 };
	inters_2_circle(pt1, pt2, 15, g_sceneWidth / 4, pt_rez);
	inters_2_circle(pt1, pt2, 5, g_sceneWidth / 4, pt_rez_vnut);

	//поиск крайних точек слева от НК
	Krug[0] = pt_rez[0];
	Krug[1] = pt_rez_vnut[0];
	Polyr_poisk(Krug, Krug_rez_left);

	//поиск крайних точек справа от НК
	Krug[0] = pt_rez[1];
	Krug[1] = pt_rez_vnut[1];
	Polyr_poisk(Krug, Krug_rez_right);




	// Поиск точек пересечения слева от начала координат и их отрисовка
	Start[1].y = g_sceneWidth;
	for (int j = 0, i = 0; j < Kol_center_spiral; j += 1)
	{
		Start[0].x = Krug_rez_left[i].x;
		Start[0].y = 0;
		Start[1].x = Krug_rez_left[i].x;
		center.x = SPIRAL_center[j].x;
		center.y = SPIRAL_center[j].z;



		inters_line_circle(Start[0], Start[1], center, 5.0, Mas_output);

		if (Draw_inters(Mas_output, Krug_rez_left[i]))
			i++;

		if (i == N_delta + 1) {
			j += 80;
			i = 0;
		}
	}


	// Поиск точек пересечения справа от начала координат и их отрисовка
	Start[1].y = g_sceneWidth;
	for (int j = 0, i = N_delta; j < Kol_center_spiral; j += 1)
	{
		Start[0].x = Krug_rez_right[i].x;
		Start[0].y = 0;
		Start[1].x = Krug_rez_right[i].x;
		center.x = SPIRAL_center[j].x;
		center.y = SPIRAL_center[j].z;

		inters_line_circle(Start[0], Start[1], center, 5.0, Mas_output);

		if (Draw_inters(Mas_output, Krug_rez_right[i]))
		{
			i--;
		}
		if (i == -1) {
			i = N_delta;
			j += 280;
		}
	}
}


int get_spiral_center(GLfloat r_max, POINT3D SPIRAL_center[800])
{
	int Kol = 0;
	double D_fi = 0.020;
	GLfloat d_z = 0.04, fi, fi_max;
	for (fi_max = -PI; fi_max < PI * 4; fi_max += D_fi)
	{
		for (fi = -PI; fi < PI; fi += D_fi)
		{



		}

		SPIRAL_center[Kol].x = r_max * cos(fi_max);
		SPIRAL_center[Kol].y = r_max * sin(fi_max);
		SPIRAL_center[Kol].z = g_sceneWidth / 4;

		Kol++;



	}
	return Kol;
}
