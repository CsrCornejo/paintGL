#ifndef	CONE_GL_H
#define CONE_GL_H

#include "object_gl.h"

class ConeGL : public ObjectGL
{
private:
	GLfloat r1, r2;
	GLint sl, st;
public:
	int FaceMode;
public:
	ConeGL();
	~ConeGL();
	void render();
};

#endif
