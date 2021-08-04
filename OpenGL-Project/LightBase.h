#pragma once
#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include "Transform.hpp"
#include "Camera.h"
#include<glm\glm.hpp>

class LightBase
{
public:
	LightBase();
	~LightBase();

	/// <summary>
	/// Draw a gizmo where the light is and move the light using movestep
	/// </summary>
	/// <param name="Cam">Current camera</param>
	void Draw(Camera* Cam);

	//Colour of the light
	vec3 M_Color;
	Transform* m_Transform = new Transform();

	glm::vec3 moveStep = vec3(0.15f,0,0);
private:	
};

#endif // !LIGHTBASE_H
