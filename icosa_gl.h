#ifndef	ICOSA_GL_H
#define ICOSA_GL_H

#include "object_gl.h"

class IcosaGL : public ObjectGL
{
public:
	int FaceMode;
public:
	IcosaGL();
	~IcosaGL();
	void render();
};

#endif
