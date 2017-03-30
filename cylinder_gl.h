#ifndef	CYLINDER_GL_H
#define CYLINDER_GL_H

#include "object_gl.h"

class CylinderGL : public ObjectGL
{
private:
	GLfloat r, h;
	GLint slices, stacks;
public:
	int FaceMode;
public:
	CylinderGL();
	~CylinderGL();
	void render();
};

#endif
