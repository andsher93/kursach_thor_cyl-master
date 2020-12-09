#include "Torus.h"

POINT3D Torus::get_pt_torus()
{
    return this->pt_torus;
}

double Torus::get_r_min_torus()
{
    return this->r_min_torus;
}

double Torus::get_r_max_torus()
{
    return this->r_max_torus;
}

void Torus::set_pt_torus(POINT3D pt)
{
    this->pt_torus = pt;
}

void Torus::set_pt_torus(double x, double y, double z)
{
    this->pt_torus.x = x;
    this->pt_torus.y = y;
    this->pt_torus.z = z;
}

void Torus::set_r_min_torus(double r_min)
{
    this->r_min_torus = r_min;
}

void Torus::set_r_max_torus(double r_max)
{
    this->r_max_torus = r_max;
}

void Torus::Draw_torus()
{	// рисование тора
		/*----------------------*/
		/* нарисовать тор       */
		/*----------------------*/
		GLfloat         x1, x2, x3, x4,
			y1, y2, y3, y4,
			z1, z2, z3, z4,
			fi, fi_max, dr, dr1, d_z = 0.2;
		C3dVector  v1, v2, v3, vn, v12, v13;

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);

		glFrontFace(GL_CCW);

		glBegin(GL_TRIANGLES);
		double D_fi = 0.1;
		for (fi_max = -PI; fi_max < PI * 4; fi_max += D_fi)
		{
			for (fi = -PI; fi < PI; fi += D_fi)
			{
				dr = this->r_min_torus * cos(fi);
				dr1 = this->r_min_torus * cos(fi + D_fi);

				x1 = (this->r_max_torus + dr) * cos(fi_max);      x2 = (this->r_max_torus + dr1) * cos(fi_max);
				x3 = (this->r_max_torus + dr1) * cos(fi_max + D_fi);  x4 = (this->r_max_torus + dr) * cos(fi_max + D_fi);

				y1 = (this->r_max_torus + dr) * sin(fi_max);      y2 = (this->r_max_torus + dr1) * sin(fi_max);
				y3 = (this->r_max_torus + dr1) * sin(fi_max + D_fi);  y4 = (this->r_max_torus + dr) * sin(fi_max + D_fi);

				z1 = this->r_min_torus * sin(fi);					z2 = this->r_min_torus * sin(fi + D_fi);
				z3 = this->r_min_torus * sin(fi + D_fi);     z4 = this->r_min_torus * sin(fi);

				v1.x = x1;   v1.y = y1; v1.z = z1;
				v2.x = x2;   v2.y = y2; v2.z = z2;
				v3.x = x3;   v3.y = y3; v3.z = z3;

				v13 = v1 - v3;
				v12 = v1 - v2;
				vn = v12 ^ v13;

				glNormal3f(vn.x, vn.y, vn.z);
				glVertex3f(x1, y1, z1);
				glVertex3f(x3, y3, z3);
				glVertex3f(x2, y2, z2);

				glVertex3f(x1, y1, z1);
				glVertex3f(x4, y4, z4);
				glVertex3f(x3, y3, z3);

			}

		}
		glEnd();
		//Kol_center_spiral = get_spiral_center(r_max, SPIRAL_center);

		glFrontFace(GL_CW);
}

void Torus::CorrectValues()
{
	if (this->r_min_torus <= 0 || this->r_max_torus <= 0)
	{
		set_r_min_torus(5.);
		set_r_min_torus(10);
	}
}
