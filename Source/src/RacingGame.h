#pragma once
#include <Component/SimpleScene.h>
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include "Transform3D.h"
#include "Camera.h"
#include "Fence.h"
#include "RoadBlock.h"

class RacingGame : public SimpleScene
{
	public:
		RacingGame();
		~RacingGame();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void initCourseSetup();
		void initFirstFenceSequence();
		void loadObjects();
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Camera *camera;
		glm::mat4 projectionMatrix;
		vector<struct fenceSequence *> fenceSequenceCollection;
		struct fence *head;
};
