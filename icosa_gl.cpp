#include "icosa_gl.h"
#include "object_gl.h"

IcosaGL::IcosaGL() : ObjectGL()
{

}
IcosaGL::~IcosaGL()
{

}
void IcosaGL::render()
{
	//glPolygonMode(GL_FRONT, this->FaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidIcosahedron();
	}
	else{
		glutWireIcosahedron();
	}

	glPopMatrix();
}