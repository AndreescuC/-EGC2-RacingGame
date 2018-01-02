#include "RacingGame.h"
#include <math.h>

using namespace std;
using namespace glm;


float rAngle = 0;
float activeSteering = 0;
float prevActiveSteering = 0;
bool recoviringFromSteering = false;

RacingGame::RacingGame(){}
RacingGame::~RacingGame(){}

void RacingGame::Init()
{
	camera = new Camera();
	camera->Set(vec3(0, 1, 3.5f), vec3(0, 1, 3.0f), vec3(0, 1, 0));

	initCourseSetup();
	initFirstFenceSequence();
	loadObjects();

	projectionMatrix = perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void RacingGame::initCourseSetup()
{
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 4));
	fenceSequenceCollection.push_back(new struct fenceSequence(1, 4));
	fenceSequenceCollection.push_back(new struct fenceSequence(-1, 4));
	/*fenceSequenceCollection.push_back(new struct fenceSequence(0, 0, 3));
	fenceSequenceCollection.push_back(new struct fenceSequence(15, 0, 3));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 20, 3));
	fenceSequenceCollection.push_back(new struct fenceSequence(15, 20, 3));

	//dreapta sus
	fenceSequenceCollection.push_back(new struct fenceSequence(30, 20, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(50, 20, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(30, 35, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(50, 35, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(30, 50, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(50, 50, 0));
	//stanga
	fenceSequenceCollection.push_back(new struct fenceSequence(-15, 20, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 20, 0));

	fenceSequenceCollection.push_back(new struct fenceSequence(-15, 35, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 35, 0));

	fenceSequenceCollection.push_back(new struct fenceSequence(-15, 50, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 50, 0));

	fenceSequenceCollection.push_back(new struct fenceSequence(-15, 65, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 65, 0));

	fenceSequenceCollection.push_back(new struct fenceSequence(-15, 80, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 80, 0));

	fenceSequenceCollection.push_back(new struct fenceSequence(-15, 95, 0));
	fenceSequenceCollection.push_back(new struct fenceSequence(0, 95, 0));*/
}

void RacingGame::initFirstFenceSequence()
{
	head = new struct fence(0, nullptr, nullptr);
	struct fence *puppet = head;

	struct fence *newNode1 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode1;
	puppet = newNode1;
	
	struct fence *newNode2 = new struct fence(0, nullptr, puppet);
	puppet->next = newNode2;
	puppet = newNode2;
	
	struct fence *newNode3 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode3;
	puppet = newNode3;
	
	struct fence *newNode4 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode4;
	puppet = newNode4;

	struct fence *newNode5 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode5;
	puppet = newNode5;

	struct fence *newNode6 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode6;
	puppet = newNode6;
	
	struct fence *newNode7 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode7;
	puppet = newNode7;

	struct fence *newNode8 = new struct fence(0, nullptr, puppet);
	puppet->next = newNode8;
	puppet = newNode8;

	struct fence *newNode9 = new struct fence(1, nullptr, puppet);
	puppet->next = newNode9;
	puppet = newNode9;

	struct fence *newNode10 = new struct fence(1, nullptr, puppet);
	puppet->next = newNode10;
	puppet = newNode10;

	struct fence *newNode11 = new struct fence(-1, nullptr, puppet);
	puppet->next = newNode11;
	puppet = newNode11;

	struct fence *newNode12 = new struct fence(0, nullptr, puppet);
	puppet->next = newNode12;
	Fence::printFenceBuffer(head);
}

void RacingGame::loadObjects()
{
	{
		Mesh* mesh = new Mesh("wall");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "wooden-wall.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("car");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "car.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("tree");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tree-toon.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void RacingGame::Update(float deltaTimeSeconds)
{
	struct fence *puppet = head;
	float leftX, leftY, rightX, rightY, rawLeftX, rawRightX, rawLeftY, rawRightY;
	float middleX, middleY;
	int rotation;
	while (puppet != nullptr) {
		Fence::getNewFencePair(puppet, &leftX, &leftY, &rightX, &rightY, &rawLeftX, &rawRightX, &rawLeftY, &rawRightY, &rotation);
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Scale3D(0.2, 0.1, 0.4);
			modelMatrix *= Transform3D::Translate3D(puppet->leftX, 0, puppet->leftY);
			modelMatrix *= Transform3D::RotateOZ3D(30 * puppet->rotation);
			modelMatrix *= Transform3D::Translate3D(0, 0, 0);
			RenderMesh(meshes["wall"], shaders["Simple"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Scale3D(0.2, 0.1, 0.4);
			modelMatrix *= Transform3D::Translate3D(puppet->rightX, 0, puppet->rightY);
			modelMatrix *= Transform3D::RotateOZ3D(30 * puppet->rotation);
			modelMatrix *= Transform3D::Translate3D(0, 0, 0);
			RenderMesh(meshes["wall"], shaders["Simple"], modelMatrix);
		}
		if (puppet->next == nullptr) {
			break;
		}
		if (puppet->relativeCurve == 1) {
			middleX = (puppet->leftX + rawLeftX) / 2;
			middleY = (puppet->leftY + rawLeftY) / 2;
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Scale3D(2, 1.5, 2);
			modelMatrix *= Transform3D::Translate3D(0.1 * middleX, 0, 0.2 * middleY);
			RenderMesh(meshes["tree"], shaders["Simple"], modelMatrix);
		}
		if (puppet->relativeCurve == -1) {
			middleX = (puppet->rightX + rawRightX) / 2;
			middleY = (puppet->rightY + rawRightY) / 2;
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Scale3D(2, 1.5, 2);
			modelMatrix *= Transform3D::Translate3D(0.1 * middleX, 0, 0.2 * middleY);
			RenderMesh(meshes["tree"], shaders["Simple"], modelMatrix);
		}

		struct point A = struct point(puppet->leftX, puppet->leftY);
		struct point B = struct point(puppet->rightX, puppet->rightY);
		struct point C = struct point(leftX, leftY);
		struct point D = struct point(rightX, rightY);
		struct point car = struct point();
		cout << RoadBlock::isPointInsideRectangle(struct roadBlock(A, B, C, D), car) + "\n";

		puppet = puppet->next;
		puppet->leftX = leftX;
		puppet->leftY = leftY;
		puppet->rightX = rightX;
		puppet->rightY = rightY;
	}
	//cout << "\n";
	{
		mat4 modelMatrix = mat4(1);
		modelMatrix = translate(modelMatrix, camera->getTargetPosition());
		modelMatrix *= Transform3D::RotateOZ3D(DEGREES(rAngle));
		modelMatrix *= Transform3D::Scale3D(0.15, 0.22, 0.15);
		modelMatrix *= Transform3D::RotateOZ3D(90);
		RenderMesh(meshes["car"], shaders["Simple"], modelMatrix);
	}

	//cout << "( " << camera->getTargetPosition()[0] << ", " << camera->getTargetPosition()[1] << ", " << camera->getTargetPosition()[2] << ")\n";
}

void RacingGame::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}
void RacingGame::FrameEnd()
{
	DrawCoordinatSystem(camera->getViewMatrix(), projectionMatrix);
}
void RacingGame::RenderMesh(Mesh * mesh, Shader * shader, const mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, value_ptr(modelMatrix));

	mesh->Render();
}
// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h
void RacingGame::OnInputUpdate(float deltaTime, int mods)
{
	float steeringSeinsitivity = 0.02;
	float speed = 0.05;
	float steeringRotationSensitivity = 0.001f;
	bool steering = false;

	if (window->KeyHold(GLFW_KEY_W)) {
		camera->TranslateForward(speed);

		if (window->KeyHold(GLFW_KEY_A)) {
			steering = true;
			//if (abs(activeSteering) < 0.5) {
				activeSteering -= 0.1;
			//}
			rAngle += steeringSeinsitivity;
			camera->RotateFirstPerson_OX(steeringSeinsitivity);
			//camera->RotateFirstPerson_OX(steeringRotationSensitivity * activeSteering);
			//modelMatrix *= Transform3D::RotateOZ3D(DEGREES(rAngle));
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			steering = true;
			//if (abs(activeSteering) < 0.5) {
				activeSteering += 0.1;
			//}
			rAngle -= steeringSeinsitivity;
			camera->RotateFirstPerson_OX(-steeringSeinsitivity);
			//camera->RotateFirstPerson_OX(steeringRotationSensitivity * activeSteering);
			//modelMatrix *= Transform3D::RotateOZ3D(DEGREES(rAngle));
		}

		/*if (!steering) {
			prevActiveSteering = activeSteering;
			activeSteering += (-activeSteering / abs(activeSteering)) * 0.01;
			if (prevActiveSteering / activeSteering < 0) {
				recoviringFromSteering = false;
			}
			camera->RotateFirstPerson_OX(activeSteering);
		}*/
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		camera->TranslateForward(-speed);
	}
	
}
void RacingGame::OnKeyPress(int key, int mods){}
void RacingGame::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			camera->RotateFirstPerson_OX(sensivityOX * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {		}

	}
}
void RacingGame::OnKeyRelease(int key, int mods) {}
void RacingGame::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}
void RacingGame::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}
void RacingGame::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
void RacingGame::OnWindowResize(int width, int height) {}
