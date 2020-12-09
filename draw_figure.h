#pragma once
#ifndef DRAW_FIGURE_H
#define DRAW_FIGURE_H


#include "WindowsProject5.h"

extern GLUquadricObj* g_pGluQuadObj;
extern float g_sceneWidth;

void SetMaterialAndLight0(int type_material)
{
	float r = 1.0,
		g = 0.5,
		b = 0.5;

	float diffuse[] = { r, g, b, 1.f },
		specular[] = { 0.0f, 1.0f, 1.0f, 1.f },

		sphere_mat[] = { .0f, 0.f, 1.1f, 1.f },
		cone_mat[] = { 1.f, 1.3f, .0f, 1.f },
		point_mat[] = { 0.0f, 1.0f, 0.f, 1.f };


	//glMaterialfv (GL_FRONT, GL_DIFFUSE, diffuse);

	switch (type_material)
	{
	case CYLINDER:  glMaterialfv(GL_FRONT, GL_AMBIENT, cone_mat); break;
	case SPIRAL:    glMaterialfv(GL_FRONT, GL_AMBIENT, sphere_mat); break;
	case POINT:     glMaterialfv(GL_FRONT, GL_DIFFUSE, point_mat); break;
	default: break;
	}

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0);

	GLfloat ambient[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat lightPos[] = { 10.0, 10.0, 10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void DrawSphere(double r)
{
	GLfloat m_ambient[] = { 0.24725, 0.1995, 0.0745, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);

	glColor3d(0, 0, 1);
	gluSphere(g_pGluQuadObj, r, 32, 32);
}

void DrawCylinder()
{
	SetMaterialAndLight0(POINT);
	gluCylinder(g_pGluQuadObj, g_sceneWidth / 4, g_sceneWidth / 4, g_sceneWidth - g_sceneWidth / 8, 32, 1);
}

void DrawCylindre(Cylindr cyl)
{
	SetMaterialAndLight0(POINT);
	gluCylinder(g_pGluQuadObj, cyl.get_r_cyl(), cyl.get_r_cyl(), cyl.get_height(), 32, 1);
}

int Draw_inters(POINT3D Mas_output[2], POINT3D krug_rez)
{
	if (Mas_output[1].x != 0 && Mas_output[1].y != 0)
	{
		glPushMatrix();
		glTranslatef(Mas_output[0].x, krug_rez.y, Mas_output[0].y);
		DrawSphere(0.5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(Mas_output[1].x, krug_rez.y, Mas_output[1].y);
		DrawSphere(0.5);
		glPopMatrix();
		return 1;
	}
	else
		return 0;
}


#endif // !DRAW_FIGURE_H