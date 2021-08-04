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
	/// <summary>
	/// Loads a .OBJ file
	/// </summary>
	/// <param name="FolderLoc"></param>
	/// <param name="Filename"></param>
	/// <param name="AmbientLoc"></param>
	/// <param name="DiffLoc"></param>
	/// <param name="specLoc"></param>
	/// <param name="NormalLoc"></param>
	/// <param name="indices"></param>
	/// <returns></returns>
	static vector<Vertex> LoadOBJ(const string& FolderLoc,
		const string& Filename, string& AmbientLoc, string& DiffLoc,
		string& specLoc, string& NormalLoc, vector<glm::uint>& indices);

	static void LoadMaterial(const string& MatLibLoc, string& AmbientLoc,
		string& DiffLoc, string& specLoc, string& NormalLoc);
};

#endif // !OBJLOADER_H

