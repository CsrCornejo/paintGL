#include "disk_gl.h"
#include "object_gl.h"

DiskGL::DiskGL() : ObjectGL()
{
	this->myQuad = gluNewQuadric();
	this->slices = this->loops = 20.0f;
	this->r1 = .25f;
	this->r2 = .5f;
	this->FaceMode = GL_LINE;
}
DiskGL::~DiskGL()
{

}
void DiskGL::render()
{


	glPushMatrix();

	glPolygonMode(GL_FRONT, this->FaceMode);
	glColor3f(this->color[0], this->color[1], this->color[2]);
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	gluDisk(this->myQuad, this->r1, this->r2, this->slices, this->loops);

	glPopMatrix();
}