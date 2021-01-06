#pragma once
#include <glm\gtc\type_ptr.hpp>

#include <glew.h>
#include <string>
#include <fstream>

#include "Transform.hpp"
#include "Camera.h"
#include "LightBase.h"

using namespace std;

class Shader
{
public:
	Shader(const string FileLocation);
	~Shader();

	void Update(Transform* transform, Camera* camera, LightBase* light, LightBase* light2);
	void Bind();

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (success == GL_FALSE)
		{
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			std::cerr << errorMessage << ": " << error << "" << std::endl;
		}
	}

	static GLuint CreateShader(const string& ShaderSource, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		if (shader == 0)
		{
			cerr << "Error: Shader creation failed!" << endl;
		}

		const char* tempSourceCode = ShaderSource.c_str();

		glShaderSource(shader, 1, &tempSourceCode, NULL);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed: ");
		return shader;
	}

	static std::string LoadShader(const std::string fileName)
	{
		std::ifstream  file;
		const char* fileNameChar = fileName.c_str();
		file.open(fileNameChar, std::ifstream::in);

		std::string output;
		std::string line;

		if (file.is_open())
		{
			while (file.good())
			{
				std::getline(file, line);
				output.append(line + "\n");
			}
		}
		else
		{
			std::cout << "Unable to load shader";
		}
		return output;
	}

	GLuint GetProgram() { return m_Program; }
private:
	string Name;
	GLuint m_Program;

	enum ShaderTypes
	{
		VERTEX,
		FRAGMENT,
		NUM_SHADER_TYPES
	};
	GLuint m_Shaders[NUM_SHADER_TYPES];

	enum UniformNames
	{
		MODEL_U,
		PROJECTION_U,
		VIEW_U,
		FRAG_LIGHTCOLOR_U,
		FRAG_LIGHTPOS_U,
		FRAG_CAMERAPOS_U,
		NUM_UNIFORMS
	};
	GLuint m_Uniforms[NUM_UNIFORMS];



};

