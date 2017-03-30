#ifndef	DISK_GL_H
#define DISK_GL_H

#include "object_gl.h"

class DiskGL : public ObjectGL
{
private:
	GLUquadric *myQuad;
	GLfloat r1, r2;
	GLint slices, loops;
public:
	int FaceMode;
public:
	DiskGL();
	~DiskGL();
	void render();
};

#endif
