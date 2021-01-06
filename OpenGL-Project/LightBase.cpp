#include "LightBase.h"

LightBase::LightBase()
{
	M_Color = vec3(1,0,0);
	m_Transform->SetPosition(vec3(-3.5f, 2.5f, -3.50f));
}

LightBase::~LightBase()
{
}

void LightBase::Draw(Camera* Cam)
{
	if ((moveStep.x + moveStep.y + moveStep.z) > 0)
	{
		if ((m_Transform->GetPosition().x+ m_Transform->GetPosition().y+ m_Transform->GetPosition().z) > 15)
		{
			moveStep = -moveStep;
		}
	}
	else {
		if ((m_Transform->GetPosition().x + m_Transform->GetPosition().y + m_Transform->GetPosition().z) < -15)
		{
			moveStep = -moveStep;
		}
	}

	m_Transform->SetPosition(vec3(m_Transform->GetPosition().x+ moveStep.x, m_Transform->GetPosition().y + moveStep.y, m_Transform->GetPosition().z + moveStep.z));

	glUseProgram(0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat*)&Cam->GetPerspective());
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 MV = Cam->GetView() * m_Transform->GetModel();
	glLoadMatrixf((const GLfloat*)&MV[0]);

	glBegin(GL_LINES);
		glm::vec3 p1 = this->m_Transform->GetPosition();
		glm::vec3 p2 = p1;

		glColor3f(1, 0, 0);
		glVertex3fv(&p1.x);
		p2 = p1 + glm::vec3(1, 0, 0) * 0.5f;
		glColor3f(1, 0, 0);
		glVertex3fv(&p2.x);

		glColor3f(0, 1, 0);
		glVertex3fv(&p1.x);
		p2 = p1 + glm::vec3(0, 1, 0) * 0.5f;
		glColor3f(0, 1, 0);
		glVertex3fv(&p2.x);

		glColor3f(0, 0, 1);
		glVertex3fv(&p1.x);
		p2 = p1 + glm::vec3(0, 0, 1) * 0.5f;
		glColor3f(0, 0, 1);
		glVertex3fv(&p2.x);
	glEnd();

}
