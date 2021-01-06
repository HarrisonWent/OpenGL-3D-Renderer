#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"
#include <map>

using namespace std;

class OBJLoader
{
public:
	static vector<Vertex> LoadOBJ(const string& FolderLoc,
		const string& Filename, string& AmbientLoc, string& DiffLoc,
		string& specLoc, string& NormalLoc, vector<glm::uint>& indices);

	static void LoadMaterial(const string& MatLibLoc, string& AmbientLoc,
		string& DiffLoc, string& specLoc, string& NormalLoc);
};

#endif // !OBJLOADER_H

