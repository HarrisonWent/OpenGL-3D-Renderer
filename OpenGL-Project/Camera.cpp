#include "Camera.h"

Camera::Camera(vec2 CameraSize, vec2 CameraPosition)
{
	Size = CameraSize;
	Position = CameraPosition;

	aspect = CameraSize.x / CameraSize.y;

	m_transform = new Transform(glm::vec3(0.0f,0.0f,-15.0f));
	m_PerspectiveProjection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}