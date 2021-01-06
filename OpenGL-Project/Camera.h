#pragma once
#include "Transform.hpp"
#include <SDL.h>
#include <string>
#include <iostream>
#include<glm\glm.hpp>
#include <glew.h>

//using namespace glm;

class Camera
{
private:

	float zNear = 0.1f;
	float zFar = 500.0f;
	float aspect = 0.0f;
	float fov = 75;

public:
	Camera(vec2 CameraSize,vec2 CameraPosition);

	//If set to true the getview function will get the viewtarget from mouse position
	bool MouseMotion = false;	

	vec2 Size;
	vec2 Position;

	glm::mat4 GetView() 
	{		
		//Positions!
		glm::vec3 cameraPos = m_transform->GetPosition();

		vec3 LookTarget = vec3(0);
		if (MouseMotion) 
		{
			LookTarget = GetLookTargetPosition();
		}	 

		//Directions!
		glm::vec3 cameraDirection = glm::normalize(LookTarget - cameraPos);

		//Rotations!
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 CamRight = normalize(cross(up,cameraDirection));
		glm::vec3 CamUp = cross(cameraDirection, CamRight);

		return glm::lookAt(cameraPos, LookTarget, up);
	}

	//current angles
	float xAngle = 0;
	float yAngle = 0;

	glm::vec3 GetLookTargetPosition()
	{
		//mouse position
		vec2 targetAngles = vec2(0);
		int Sensitivity = 2;

		//Get the mouse input
		SDL_Event eventssss;
		while (SDL_PollEvent(&eventssss))
		{
			if (eventssss.type == SDL_MOUSEMOTION)
			{
				targetAngles.x = -eventssss.motion.xrel;
				targetAngles.y = -eventssss.motion.yrel;
			}
		}

		//Add the mouse input into our current angle, wrapped to 360 degrees 
		xAngle = fmod(xAngle + (targetAngles.x * Sensitivity), 360.0f);
		yAngle = fmod(yAngle + (targetAngles.y * Sensitivity), 360.0f);
		
		vec2 Values = vec2(xAngle * (M_PI / 180.0f), yAngle * (M_PI / 180.0f));

		//Put the positions into a spherical value around the camera position
		vec3 TargetPosition;
		TargetPosition.x = sin(Values.x);
		TargetPosition.y = -cos(Values.y);
		TargetPosition.z = cos(Values.x) + sin(Values.y);
		TargetPosition += m_transform->GetPosition();

		//std::cout << "\nTarget position: " << TargetPosition.x<< " " << TargetPosition.y << " " << TargetPosition.z;

		//Return where we are looking
		return TargetPosition;
	}

	//spin the camera around world center
	void Spin(bool Direction) 
	{
		const float radius = 10.0f;
		float camX = sin(timer *radius);
		float camZ = cos(timer *radius);
		if (Direction) 
		{
			timer += 0.001f;
		}
		else 
		{
			timer -= 0.001f;
		}
		timer = fmod(timer, 360.0f);

		m_transform->SetPosition(vec3(camX * 5,m_transform->GetPosition().y, camZ * 5));
	}
	float timer = 0.00f;

	void WASDMove()
	{
		vec3 NewMove = vec3(0.0f, 0.0f, 0.0f);
		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_GetScancodeFromKey(SDLK_w)])
		{
			NewMove.b+=0.2f;
		}
		if (keyState[SDL_GetScancodeFromKey(SDLK_a)])
		{
			NewMove.r+= 0.2f;
		}
		if (keyState[SDL_GetScancodeFromKey(SDLK_s)])
		{
			NewMove.b-= 0.2f;
		}
		if (keyState[SDL_GetScancodeFromKey(SDLK_d)])
		{
			NewMove.r-= 0.2f;
		}

		//Directions!
		glm::vec3 cameraDirection = (glm::normalize(GetLookTargetPosition() - m_transform->GetPosition()));

		//Rotations!
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 CamRight = normalize(cross(up, cameraDirection));

		
		m_transform->SetPosition(m_transform->GetPosition()+ 
			(cameraDirection * NewMove.b) +	(CamRight * NewMove.r));
		

		//m_transform->SetPosition(m_transform->GetPosition() + NewMove);
	}

	glm::mat4 GetPerspective() 
	{
		return m_PerspectiveProjection;
	}

	
	glm::mat4 m_PerspectiveProjection;
	Transform* m_transform;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

};