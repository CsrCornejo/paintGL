#ifndef LINE_GL_H
#define LINE_GL_H

#include "polygon_gl.h"

class LineGL : public PolygonGL
{
private:
	GLfloat x1, y1, z1, x2, y2, z2;
public:
	LineGL();
	~LineGL();
	void render();
};

#endif
