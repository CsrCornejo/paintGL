#include <GL\glew.h>
#include <GL\freeglut.h>
#include <cmath>

#include "line_gl.h"

LineGL::LineGL() : PolygonGL()
{
	GLfloat size = 1.f;
	this->x1 = -size / 2.f;
	this->y1 = 0.f;
	this->z1 = 0.f;
	this->x2 = size / 2.f;
	this->y2 = 0.f;
	this->z2 = 0.f;

}
LineGL::~LineGL()
{

}
void LineGL::render()
{
	glPolygonMode(GL_FRONT, this->frontFaceMode);
	glPolygonMode(GL_BACK, this->backFaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	glBegin(GL_LINES);
	glVertex3f(this->x1, this->y1, this->z1);
	glVertex3f(this->x2, this->y2, this->z2);
	glEnd();
	glPopMatrix();
}