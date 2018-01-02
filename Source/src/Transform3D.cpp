#include "Transform3D.h"

using namespace glm;
using namespace std;


mat4 Transform3D::RotateOZ3D(double angle)
{
	angle = RADIANS(angle);
	return transpose(mat4(
		cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1)
	);
}

mat4 Transform3D::Scale3D(double sx, double sy, double sz)
{
	return transpose(mat4(
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1)
	);
}

mat4 Transform3D::Translate3D(double tx, double ty, double tz)
{
	return transpose(mat4(
		1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1)
	);
}