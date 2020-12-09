#include "Cylindr.h"

POINT3D Cylindr::get_pt_cyl()
{
    return this->pt_cyl;
}

double Cylindr::get_r_cyl()
{
    return this->r_cyl;
}

void Cylindr::set_pt_cyl(POINT3D pt)
{
    this->pt_cyl = pt;
}

void Cylindr::set_pt_cyl(double x, double y, double z)
{
    this->pt_cyl.x = x;
    this->pt_cyl.y = y;
    this->pt_cyl.z = z;
}


void Cylindr::set_r_cyl(double radius)
{
    this->r_cyl = radius;
}

void Cylindr::set_height(double h)
{
    this->height = h;
}

double Cylindr::get_height()
{
    return this->height;
}
/*
void Cylindr::Draw_cyl(GLUquadricObj* g_pGluQuadObj)
{
    SetMaterialAndLight0(POINT);
    gluCylinder(g_pGluQuadObj, r_cyl, r_cyl, height, 32, 1);
}
*/
Cylindr::Cylindr()
{
    set_pt_cyl(0, 0, 0);
    set_r_cyl(g_sceneWidth / 4);
    set_height(g_sceneWidth - g_sceneWidth / 8);
}

Cylindr::Cylindr (POINT3D center, double rad, double height)
{
    set_pt_cyl(center);
    set_r_cyl(rad);
    set_height(height);
}

void Cylindr::CorrectValues()
{
    if (this->r_cyl <= 0)
        set_r_cyl(g_sceneWidth/4.);
    if (this->height <= 0)
        set_height(g_sceneWidth - g_sceneWidth / 8.);
}
