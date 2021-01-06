#pragma once
#include <glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

#include "stb_image.h"

using namespace std;
class TextureLoader 
{
public:
	TextureLoader();

	 GLuint LoadTexture(string TextureLocation);
	
};