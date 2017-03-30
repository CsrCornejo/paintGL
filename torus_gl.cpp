#include "torus_gl.h"
#include "object_gl.h"

TorusGL::TorusGL() : ObjectGL()
{


	GLfloat size = 1.f;

	this->r1 = size;
	this->r2 = size;
	this->sl = 10;
	this->st = 10;

}
TorusGL::~TorusGL()
{

}
void TorusGL::render()
{
	//glPolygonMode(GL_FRONT, this->FaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidTorus(this->r1, this->r2, this->sl, this->st);
	}
	else{
		glutWireTorus(this->r1, this->r2, this->sl, this->st);
	}

	glPopMatrix();
}