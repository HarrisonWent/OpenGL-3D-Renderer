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
	void Draw(Shader* MyShader,Camera* MyCamera,LightBase* SceneLight, LightBase* SceneLight2);
private:
};

