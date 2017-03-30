#include "teapot_gl.h"
#include "object_gl.h"

TeapotGL::TeapotGL() : ObjectGL()
{


	GLfloat size = .5f;

	this->s = size;
}
TeapotGL::~TeapotGL()
{

}
void TeapotGL::render()
{
	//glPolygonMode(GL_FRONT, this->FaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidTeapot(this->s);
	}
	else{
		glutWireTeapot(this->s);
	}

	glPopMatrix();
}