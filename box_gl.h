#ifndef BOX_GL_H
#define BOX_GL_H

#include "object_gl.h"
#include "quad_gl.h"

class BoxGL : public ObjectGL
{
private:
	QuadGL *q1, *q2, *q3, *q4, *q5;
public:
	int FaceMode;
public:
	BoxGL();
	~BoxGL();
	void render();
};

#endif
