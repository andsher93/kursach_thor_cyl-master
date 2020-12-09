#pragma once

struct POINT3D
{
	double x, y, z;
};


struct C3dVector
{
	double x, y, z;
};

C3dVector operator ^ (const C3dVector& u_, const C3dVector& v_);

C3dVector operator - (const C3dVector& u_, const C3dVector& v_);