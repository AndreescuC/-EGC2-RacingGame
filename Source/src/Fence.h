struct fence {
	int relativeCurve;
	float leftX, leftY, rightX, rightY;
	int rotation;
	fence *next;
	fence *prev;
	fence(int d, struct fence *nextFence, struct fence *prevFence) {
		relativeCurve = d;
		next = nextFence;
		prev = prevFence;
		leftX = 0;
		leftY = 0;
		rightX = 0;
		rightY = 0;
	}
};

struct fenceSequence {
	int direction;
	int duration;
	fenceSequence(int d, int theD) {
		direction = d;
		duration = theD;
	}
};

class Fence
{
public:

	static void printFenceBuffer(struct fence *head)
	{
		struct fence *puppet;
		puppet = head;
		cout << "---------------------------------------------PRINTING FENCE BUFFER---------------------------------------------\n";
		while (puppet->next != nullptr) {
			cout << puppet->relativeCurve << " || Left:[" << puppet->leftX << ", " << puppet->leftY << "] || ";
			cout << "Right:[" << puppet->rightX << ", " << puppet->rightY << "] || Rotation: " << puppet->rotation << "\n |||\n";
			puppet = puppet->next;
		}
		cout << "---------------------------------------------END---------------------------------------------\n";
	}

	static void getNewFencePair(struct fence *puppet, float *leftX, float *leftY, float *rightX, float *rightY,
		float *rawLeftX, float *rawRightX, float *rawLeftY, float *rawRightY, int *rotation)
	{
		float fenceLength = 14;
		float roadWitdth = 15;
		float epsilon = 0.001;
		if (puppet->prev) {
			*rotation = puppet->prev->rotation + puppet->relativeCurve;
			if (*rotation == -1) {
				*rotation = 11;
			}
			*rotation = *rotation % 12;
			puppet->rotation = *rotation;
			if (puppet->relativeCurve == 1) {
				float correctedLeftX = *rightX - roadWitdth * cos(RADIANS(puppet->rotation * 30));
				float correctedLeftY = *rightY + roadWitdth * sin(RADIANS(puppet->rotation * 30));
				puppet->leftX = correctedLeftX;
				puppet->leftY = correctedLeftY;
			}

			if (puppet->relativeCurve == -1) {
				float correctedRightX = *leftX - roadWitdth * cos(RADIANS(abs(puppet->rotation * 30 - 180)));
				float correctedRightY = *leftY + roadWitdth * sin(RADIANS(abs(puppet->rotation * 30 - 180)));
				puppet->rightX = correctedRightX;
				puppet->rightY = correctedRightY;
			}

			*rawLeftX = *leftX;
			*rawLeftY = *leftY;
			*rawRightX = *rightX;
			*rawRightY = *rightY;

			float trigFactorY = cos(RADIANS(30 * *rotation));
			float trigFactorX = sin(RADIANS(30 * *rotation));
			trigFactorX = abs(trigFactorX) < epsilon ? 0 : round(trigFactorX * 1000) / 1000;
			trigFactorY = abs(trigFactorY) < epsilon ? 0 : round(trigFactorY * 1000) / 1000;

			*rightX = puppet->rightX + trigFactorX * fenceLength;
			*rightY = puppet->rightY + trigFactorY * fenceLength;

			*leftX = puppet->leftX + trigFactorX * fenceLength;
			*leftY = puppet->leftY + trigFactorY * fenceLength;

			
		} else {
			puppet->leftX = 0;
			puppet->leftY = 0;
			puppet->rightX = 15;
			puppet->rightY = 0;
			puppet->rotation = 0;
			*leftX = 0;
			*leftY = fenceLength;
			*rightX = roadWitdth;
			*rightY = fenceLength;
		}
	}
};
