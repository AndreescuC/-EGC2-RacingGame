

struct point {
	float x;
	float y;
	point(float xCoord, float yCoord) {
		x = xCoord;
		y = yCoord;
	}
	point() {
		x = 0;
		y = 0;
	}
};

struct roadBlock {
	struct point A;
	struct point B;
	struct point C;
	struct point D;
	roadBlock(struct point Ap, struct point Bp, struct point Cp, struct point Dp) {
		A = Ap;
		B = Bp;
		C = Cp;
		D = Dp;
	}
};

class RoadBlock
{

public:

	static bool isPointInsideRectangle(struct roadBlock roadPortion, struct point car)
	{
		float areaByTriangles = computeTrigArea(roadPortion.A, roadPortion.B, car);
		areaByTriangles += computeTrigArea(roadPortion.A, roadPortion.D, car);
		areaByTriangles += computeTrigArea(roadPortion.C, roadPortion.D, car);
		areaByTriangles += computeTrigArea(roadPortion.C, roadPortion.B, car);
		float areaRect = computeRectArea(roadPortion.A, roadPortion.B, roadPortion.C);

		return areaByTriangles == areaRect;
	}

private:

	static float computeTrigArea(struct point A, struct point B, struct point C)
	{
		float a = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
		float b = sqrt(pow(A.x - C.x, 2) + pow(A.y - C.y, 2));
		float c = sqrt(pow(C.x - B.x, 2) + pow(C.y - B.y, 2));
		float hP = (a + b + c) / 2;

		return sqrt(hP * (hP - a) * (hP - b) * (hP - c));;
	}

	static float computeRectArea(struct point A, struct point B, struct point C)
	{
		float a = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
		float b = sqrt(pow(A.x - C.x, 2) + pow(A.y - C.y, 2));

		return a * b;
	}
};
