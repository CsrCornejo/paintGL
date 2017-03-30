#ifndef	TORUS_GL_H
#define TORUS_GL_H

#include "object_gl.h"

class TorusGL : public ObjectGL
{
private:
	GLfloat r1, r2;
	GLint sl, st;
public:
	int FaceMode;
public:
	TorusGL();
	~TorusGL();
	void render();
};

#endif
