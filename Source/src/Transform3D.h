#pragma once
#include <Core/Engine.h>

using namespace glm;
using namespace std;


class Transform3D
{
	public:
		Transform3D();
		~Transform3D();

		static mat4 Translate3D(double tx, double ty, double tz);
		static mat4 RotateOZ3D(double angle);
		static mat4 Scale3D(double sx, double sy, double sz);

	private:


	protected:

};
