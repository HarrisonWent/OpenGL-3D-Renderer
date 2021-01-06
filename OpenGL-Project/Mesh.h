#pragma once
#ifndef MESH_H
#define MESH_H

#include<glm\glm.hpp>
#include<glm/gtx/normal.hpp>
#include <glew.h>
#include "Transform.hpp"
#include <vector>
#include "Vertex.h"
#include "TextureLoader.h"

using namespace std;

class Mesh
{
public:
	Transform* m_transform = new Transform();

	Mesh(Vertex* verts, unsigned int vertCount, unsigned int* indices, unsigned int numIndices);
	
	void Draw();
	void CalculateTangentsBitangent(Vertex* verticies, unsigned int vertCount, unsigned int* indices, unsigned int numIndices);

	~Mesh();

	GLuint DiffuseTextureID;
	GLuint NormalTextureID;

private: 

	enum VertexBuffers
	{
		POSITION_VB,
		TEXCOORD_VB,		
		NORMAL_VB,
		TANGENT_VB,
		BITANGENT_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexBufferObjects[NUM_BUFFERS];
	GLuint m_vertexArrayObject = 0;

	unsigned int m_DrawCount = 0;

};

#endif // !MESH_H

