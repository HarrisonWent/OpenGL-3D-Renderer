#include "Shader.h"

Shader::Shader(const string FileLocation)
{
	Name = FileLocation;
	m_Program = glCreateProgram();

	//Shaders
	m_Shaders[VERTEX] = CreateShader(LoadShader(FileLocation + ".vert"), GL_VERTEX_SHADER);
	m_Shaders[FRAGMENT] = CreateShader(LoadShader(FileLocation + ".frag"), GL_FRAGMENT_SHADER);

	for (GLuint i = 0; i < NUM_SHADER_TYPES; i++)
	{
		glAttachShader(m_Program, m_Shaders[i]);
	}

	//Check for shader errors
	glLinkProgram(m_Program);
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: Program Linking failed: ");

	glValidateProgram(m_Program);
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	//Uniforms
	m_Uniforms[MODEL_U] = glGetUniformLocation(m_Program, "model");
	m_Uniforms[PROJECTION_U] = glGetUniformLocation(m_Program, "projection");
	m_Uniforms[VIEW_U] = glGetUniformLocation(m_Program, "view");

	m_Uniforms[FRAG_CAMERAPOS_U] = glGetUniformLocation(m_Program, "FragCamPos");
	m_Uniforms[FRAG_LIGHTCOLOR_U] = glGetUniformLocation(m_Program, "PointLight_Colours");
	m_Uniforms[FRAG_LIGHTPOS_U] = glGetUniformLocation(m_Program, "PointLight_Positions");

	for (GLuint i = 0; i < NUM_UNIFORMS; i++)
	{
		if (m_Uniforms[i] == GL_INVALID_INDEX)
		{
			cout << "Shader " << Name << " Uniform invalid index: " << static_cast<UniformNames>(i)
				<< " (Might be optimized out if not used)" << endl;
		}
	}
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADER_TYPES; i++)
	{
		glDetachShader(m_Program, m_Shaders[i]);
		glDeleteShader(m_Shaders[i]);
	}
	glDeleteProgram(m_Program);
}

void Shader::Update(Transform* transform, Camera* camera, LightBase* light,LightBase* light2)
{
	mat4 projection = camera->GetPerspective();
	mat4 view = camera->GetView();
	mat4 model = transform->GetModel();

	GLint modelLoc = glGetUniformLocation(GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform->GetModel()[0][0]);

	glUniformMatrix4fv(m_Uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_Uniforms[PROJECTION_U], 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(m_Uniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);

	glUniform3f(m_Uniforms[FRAG_CAMERAPOS_U], camera->m_transform->GetPosition().x,
		camera->m_transform->GetPosition().y,
		camera->m_transform->GetPosition().z);

	//glUniform3f(m_Uniforms[FRAG_LIGHTPOS_U], light->m_Transform->GetPosition().x,
	//	light->m_Transform->GetPosition().y,
	//	light->m_Transform->GetPosition().z);

	//glUniform3f(m_Uniforms[FRAG_LIGHTCOLOR_U], light->M_Color.x,
	//	light->M_Color.y,
	//	light->M_Color.z);

	vec3 pointPositions[2] = {
		light->m_Transform->GetPosition(),
		light2->m_Transform->GetPosition(),
		};

	vec3 pointColours[2] = {
		light->M_Color,
		light2->M_Color,
		};

	glUniform3fv(m_Uniforms[FRAG_LIGHTCOLOR_U],2,
		glm::value_ptr(pointColours[0]));

	glUniform3fv(m_Uniforms[FRAG_LIGHTPOS_U], 2,
		glm::value_ptr(pointPositions[0]));
}

void Shader::Bind()
{
	glUseProgram(m_Program);
}
