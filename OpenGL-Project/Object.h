#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "LightBase.h"
#include "OBJLoader.h"
#include "TextureLoader.h"
class Object
{
public:
	Object();
	Mesh* MyMesh;

	/// <summary>
	/// Draws the objects mesh with its textures
	/// </summary>
	/// <param name="MyShader"></param>
	/// <param name="MyCamera"></param>
	/// <param name="SceneLight"></param>
	/// <param name="SceneLight2"></param>
	void Draw(Shader* MyShader,Camera* MyCamera,LightBase* SceneLight, LightBase* SceneLight2);
private:
};

