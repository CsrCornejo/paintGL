#ifndef	OCTA_GL_H
#define OCTA_GL_H

#include "object_gl.h"

class OctaGL : public ObjectGL
{
public:
	int FaceMode;
public:
	OctaGL();
	~OctaGL();
	void render();
};

#endif
