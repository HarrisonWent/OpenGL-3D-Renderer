#include "Object.h"

Object::Object()
{
	TextureLoader* m_TextureLoader = new TextureLoader();

	//Texture locations
	string AmbientLoc;
	string DiffuseLoc;
	string SpecLoc;
	string NormalLoc;
	vector<uint> Indices;
	//Load obj file
	vector<Vertex> LoadedVerts = OBJLoader::LoadOBJ("../Resources/Objects", "blocks_01.obj", AmbientLoc, DiffuseLoc, SpecLoc, NormalLoc, Indices);

	//Load the textures using the locations
	GLuint Diff = m_TextureLoader->LoadTexture("../Resources/Objects/" + DiffuseLoc);
	GLuint Norm = m_TextureLoader->LoadTexture("../Resources/Objects/" + NormalLoc);

	//Make the mesh using the loaded verts
	Mesh* LoadedSquareMesh = new Mesh(&LoadedVerts[0], LoadedVerts.size(), &Indices[0], Indices.size());
	
	//Set its textures
	LoadedSquareMesh->DiffuseTextureID = Diff;
	LoadedSquareMesh->NormalTextureID = Norm;

	MyMesh = LoadedSquareMesh;

	LoadedSquareMesh->m_transform->SetScale(glm::vec3(0.2f,0.2f,0.2f));

	delete(m_TextureLoader);
	m_TextureLoader = nullptr;
}

void Object::Draw(Shader* MyShader, Camera* MyCamera, LightBase* SceneLight,LightBase* SceneLight2)
{
	MyShader->Bind();

	glActiveTexture(GL_TEXTURE0);

	//Get the diffuse texture in the shader
	GLuint TextureLoc = glGetUniformLocation(MyShader->GetProgram(), "texture_Diffuse");
	glUniform1i(TextureLoc, 0);
	//set the diffuse texture to the meshes diffuse texture
	glBindTexture(GL_TEXTURE_2D, MyMesh->DiffuseTextureID);

	glActiveTexture(GL_TEXTURE1);

	//Get the normal texture in the shader
	GLuint TextureLoc2 = glGetUniformLocation(MyShader->GetProgram(), "texture_Normal");
	glUniform1i(TextureLoc2, 1);
	//set the normal texture to the meshes normal texture
	glBindTexture(GL_TEXTURE_2D, MyMesh->NormalTextureID);

	//Update the shader with the mesh transform and camera
	MyShader->Update(MyMesh->m_transform,MyCamera,SceneLight, SceneLight2);

	MyMesh->Draw();
}
