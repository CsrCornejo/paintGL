#ifndef	TEAPOT_GL_H
#define TEAPOT_GL_H

#include "object_gl.h"

class TeapotGL : public ObjectGL
{
private:
	GLfloat s;
public:
	int FaceMode;
public:
	TeapotGL();
	~TeapotGL();
	void render();
};

#endif
