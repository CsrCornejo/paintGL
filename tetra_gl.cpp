#include "tetra_gl.h"
#include "object_gl.h"

TetraGL::TetraGL() : ObjectGL()
{

}
TetraGL::~TetraGL()
{

}
void TetraGL::render()
{
	//glPolygonMode(GL_FRONT, this->FaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidTetrahedron();
	}
	else{
		glutWireTetrahedron();
	}

	glPopMatrix();
}