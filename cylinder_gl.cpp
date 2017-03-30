#include "cylinder_gl.h"
#include "object_gl.h"

CylinderGL::CylinderGL() : ObjectGL()
{
	this->r = .5f;
	this->h = .5f;
	this->slices = this->stacks = 20.0f;

}
CylinderGL::~CylinderGL()
{

}
void CylinderGL::render()
{


	glPushMatrix();

	glPolygonMode(GL_FRONT, this->FaceMode);
	glColor3f(this->color[0], this->color[1], this->color[2]);
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidCylinder(this->r, this->h, this->slices, this->stacks);
	}
	else{
		glutWireCylinder(this->r, this->h, this->slices, this->stacks);
	}


	glPopMatrix();
}