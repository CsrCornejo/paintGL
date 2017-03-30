#include "cone_gl.h"
#include "object_gl.h"

ConeGL::ConeGL() : ObjectGL()
{


	GLfloat size = 1.f;

	this->r1 = size;
	this->r2 = size;
	this->sl = 10;
	this->st = 10;

}
ConeGL::~ConeGL()
{

}
void ConeGL::render()
{
	//glPolygonMode(GL_FRONT, this->FaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidCone(this->r1, this->r2, this-> sl, this->st);
	}
	else{
		glutWireCone(this->r1, this->r2, this->sl, this->st);
	}

	glPopMatrix();
}