#define GLEW_STATIC
#include <glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "Vertex.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "LightBase.h"
#include "Object.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//All the meshes in the scene wwe are rendering
std::vector<Object*> SceneObjects;
LightBase* SceneLight;
LightBase* SceneLight2;

void RenderCamera(Camera* CameraToRender, Shader* UsedShader, vec4 Colour)
{

	vec2 CameraPosition = CameraToRender->Position;
	vec2 CameraSize = CameraToRender->Size;

	//Set the viewport dimensions and location
	glViewport(CameraPosition.x, CameraPosition.y, CameraSize.x, CameraSize.y);
	glLoadIdentity();

	//Give the viewport the cameras unqiue colour
	glScissor(CameraPosition.x, CameraPosition.y, CameraSize.x, CameraSize.y);
	glEnable(GL_SCISSOR_TEST);
	glClearColor(Colour.r, Colour.g, Colour.b, Colour.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glUseProgram(UsedShader->GetProgram());

	//For each mesh in the scene draw it using the render camera
	for (Object* obj : SceneObjects)
	{
		obj->Draw(UsedShader,CameraToRender,SceneLight,SceneLight2);
	}

	SceneLight->Draw(CameraToRender);
	SceneLight2->Draw(CameraToRender);
}

int main(int argc, char *argv[]) 
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	
	//These are used for the window and making the camera sizes
	int width = 1600;
	int height = 768;

	//Create the window
	SDL_Window* window = SDL_CreateWindow("My window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext GLContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (status != GLEW_OK) 
	{
		std::cout << "GLEW failed to initlialize!" << std::endl;
	}

	//Lights
	SceneLight = new LightBase();
	SceneLight->M_Color = vec3(1, 1, 1);
	SceneLight2 = new LightBase();
	SceneLight2->moveStep = vec3(0.1f, 0.15f, 0.0f);

	//Create shader
	Shader* basicShader = new Shader("../Resources/Shaders/Basic");

	//Create scene objects
	Object* NewSceneObject = new Object();
	SceneObjects.push_back(NewSceneObject);

	NewSceneObject = new Object();
	SceneObjects.push_back(NewSceneObject);
	NewSceneObject->MyMesh->m_transform->SetPosition(glm::vec3(10, 5, 10));

	NewSceneObject = new Object();
	SceneObjects.push_back(NewSceneObject);
	NewSceneObject->MyMesh->m_transform->SetPosition(glm::vec3(-10,4, 10));

	//Make a vector for the camera sizes in pixels, As each camera will be a quarter
	int CamHeight = height / 2;
	int CamWidth = width / 2;
	vec2 CameraSize = vec2(CamWidth, CamHeight);

	//Setup camera
	Camera* MainCamera = new Camera(vec2(width,height), vec2(0, 0));
	MainCamera->m_transform->SetPosition(vec3(2,10,-15));
	MainCamera->xAngle = 25;
	MainCamera->yAngle = 45;

	//Enable mouse movement for camera
	MainCamera->MouseMotion = true;

	while (true)
	{		
		//This camera has mouse movement enabled (fps style look around)
		RenderCamera(MainCamera, basicShader, vec4(0.2f, 0.2f, 0.2f, 1.0f));

		//This camera will used the wasd keys to move around
		MainCamera->WASDMove();

		//Wait (60fps target)
		SDL_Delay(16);		

		//Display newly rendered frame
		SDL_GL_SwapWindow(window);
	}

	for (Object* m : SceneObjects) 
	{
		delete(&m);
	}

	delete(MainCamera);

	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;
}