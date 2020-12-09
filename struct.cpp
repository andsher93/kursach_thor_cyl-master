#include "struct.h"

C3dVector operator ^ (const C3dVector& u_, const C3dVector& v_)
{
	C3dVector vrez = { u_.y * v_.z - u_.z * v_.y,
		u_.z * v_.x - u_.x * v_.z,
		u_.x * v_.y - u_.y * v_.x
	};

	return vrez;
}

C3dVector operator - (const C3dVector& u_, const C3dVector& v_)
{
	C3dVector vrez = { u_.x - v_.x,
		u_.y - v_.y,
		u_.z - v_.z
	};

	return vrez;
}