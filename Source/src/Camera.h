#pragma once
#include <include/glm.h>
#include <include/math.h>

using namespace glm;

class Camera
{
	public:
		Camera()
		{
			position = vec3(0, 2, 5);
			forward = vec3(0, 0, -1);
			up		= vec3(0, 1, 0);
			right	= vec3(1, 0, 0);
			distanceToTarget = 3;
		}
		Camera(const vec3 &position, const vec3 &center, const vec3 &up)
		{
			Set(position, center, up);
		}
		~Camera(){ }
			
		void Set(const vec3 &position, const vec3 &center, const vec3 &up)
		{
			this->position = position;
			forward = normalize(center-position);
			right	= cross(forward, up);
			this->up = cross(right,forward);
		}

		void MoveForward(float distance)
		{
			vec3 dir = normalize(vec3(forward.x, 0, forward.z));
			this->TranslateForward(distance);
		}

		void TranslateForward(float distance)
		{
			position = position + glm::normalize(forward) * distance;
		}

		void RotateFirstPerson_OX(float angle)
		{
			vec4 newRightVector = rotate(mat4(1.0f), angle, vec3(0, 1, 0)) * vec4(right, 1);
			right = normalize(vec3(newRightVector));
			vec4 newFowardVector = rotate(mat4(1.0f), angle, vec3(0, 1, 0)) * vec4(forward, 1);
			forward = normalize(vec3(newFowardVector));
			up = cross(right, forward);
		}

		mat4 getViewMatrix()
		{
			return lookAt(position, position + forward, up);
		}

		vec3 getPosition()
		{
			return position;
		}

		vec3 getTargetPosition()
		{
			return position + forward * distanceToTarget - vec3(0, 1.2, 0);
		}

	public:
		float distanceToTarget;
		vec3 position;
		vec3 forward;
		vec3 right;
		vec3 up;
};