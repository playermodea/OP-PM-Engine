#include "OGRenderUtil.h"
#include "WindowManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "OGShader.h"
#include "glew/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

void OGRenderUtil::Init()
{
	SetDefaultShader<OGShader>();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void OGRenderUtil::InitLight()
{
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void OGRenderUtil::StartScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//PerspectiveProjection();
}

void OGRenderUtil::EndScreen()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP);
	glFlush();
}

void OGRenderUtil::ObjectRenderStart(TransformComponent* transform)
{
	glPushMatrix();
	//MainCamView();
	//glTranslatef(objPos.x, objPos.y, objPos.z);
	//glRotatef(objRot.x, 1.0f, 0.0f, 0.0f);
	//glRotatef(objRot.y, 0.0f, 1.0f, 0.0f);
	//glRotatef(objRot.z, 0.0f, 0.0f, 1.0f);
	//glScalef(objScale.x, objScale.y, objScale.z);
	glm::vec3 objPos = transform->GetWorldPos();
	GLfloat lightPos[] = { objPos.x,objPos.y,objPos.z,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	UpdateMatrix(transform);
}

void OGRenderUtil::ObjectRenderEnd()
{
	glPopMatrix();
}

void OGRenderUtil::MainCamView()
{
	glm::vec3 camPos = GetMainCamera()->GetTransform()->GetWorldPos();
	glm::vec3 camRot = GetMainCamera()->GetTransform()->GetWorldRot();

	glRotatef(camRot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(camRot.y, 0.0f, 1.0f, 0.0f);
	gluLookAt(camPos.x, camPos.y, camPos.z, camPos.x, camPos.y, - 1.0f + camPos.z, 0.0f, 1.0f, 0.0f);
}

void OGRenderUtil::Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void OGRenderUtil::PerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, WindowManager::Instance()->GetAspect(), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OGRenderUtil::OrthoProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(float)WindowManager::Instance()->GetWidth()/2.0f
			, (float)WindowManager::Instance()->GetWidth() / 2.0f
			, -(float)WindowManager::Instance()->GetHeight() / 2.0f
			, (float)WindowManager::Instance()->GetHeight() / 2.0f
			, 0.1f
			, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OGRenderUtil::UpdateMatrix(TransformComponent* transform)
{
	glm::vec3 objPos = transform->GetWorldPos();
	glm::vec3 objRot = transform->GetWorldRot();
	glm::vec3 objScale = transform->GetWorldScale();

	glm::mat4 objMat = glm::translate(glm::mat4(1.0f), objPos);
	objMat = glm::rotate(objMat, glm::radians(objRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	objMat = glm::rotate(objMat, glm::radians(objRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	objMat = glm::rotate(objMat, glm::radians(objRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	objMat = glm::scale(objMat, objScale);

	glm::vec3 camPos = GetMainCamera()->GetTransform()->GetWorldPos();
	glm::vec3 camRot = GetMainCamera()->GetTransform()->GetWorldRot();

	glm::mat4 viewMat;
	viewMat = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMat = glm::rotate(viewMat, glm::radians(camRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	viewMat *= glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(camPos.x, camPos.y, -1.0f + camPos.z), glm::vec3(0, 1, 0));

	glm::mat4 projMat = glm::perspective(glm::radians(90.0f), WindowManager::Instance()->GetAspect(), 0.1f, 100.0f);
	glm::mat4 MVP = projMat * viewMat * objMat;

	GetDefaultShader()->Use();
	GetDefaultShader()->SetMat4("MVP", MVP);
	GetDefaultShader()->SetInt("MyTexture", 0);
}