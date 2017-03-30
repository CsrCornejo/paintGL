#ifndef	DODECA_GL_H
#define DODECA_GL_H

#include "object_gl.h"

class DodecaGL : public ObjectGL
{
public:
	int FaceMode;
public:
	DodecaGL();
	~DodecaGL();
	void render();
};

#endif
