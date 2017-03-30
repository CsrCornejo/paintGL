#ifndef	TETRA_GL_H
#define TETRA_GL_H

#include "object_gl.h"

class TetraGL : public ObjectGL
{
public:
	int FaceMode;
public:
	TetraGL();
	~TetraGL();
	void render();
};

#endif
