#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <windows.h>

#include "commdlg.h"

#include "triangle_gl.h"
#include "quad_gl.h"
#include "cube_gl.h"
#include "line_gl.h"
#include "point_gl.h"
#include "pyramid_gl.h"
#include "sphere_gl.h"
#include "cone_gl.h"
#include "tetra_gl.h"
#include "octa_gl.h"
#include "dodeca_gl.h"
#include "icosa_gl.h"
#include "teapot_gl.h"
#include "box_gl.h"
#include "torus_gl.h"
#include "cylinder_gl.h"
#include "disk_gl.h"

using namespace std;

int foi = 0;		//figure option index
int foi_size = 16;
string currentDrawFigure;

string figureOptions[] = { "Esfera", "Cono", "Cubo", "Caja", "Toroide", "Tetrahedro",
"Octahedro", "Dodecahedro", "Icosahedro", "Tetera", "Cilindro",
"Disco", "Punto", "Segmento", "Triangulo", "Cuadrado", "Piramide" };

int numDoneFigures[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

std::vector<ObjectGL *> scene;
string * drawnFigures = new string[60];

int fci = 0;
int fci_size = 0;

const int SPHERE = 0,
CONE = 1,
CUBE = 2,
BOX = 3,
TORO = 4,
TETRA = 5,
OCTAH = 6,
DODE = 7,
ICOSA = 8,
TEA = 9,
CILY = 10,
DISK = 11,
DOT = 12,
SEG = 13,
TRIA = 14,
QUAD = 15,
PYRA = 16;


// Referencias a las Ventanas
int mainwindow;
int subwindow_1;
int subwindow_2;	// Avaliable Figures
int subwindow_3;	// Figures on Canvas
int subwindow_4;	// Translate
int subwindow_5;	// Scalate
int subwindow_6;	// Rotate

GLint GAP = 12;

// Tamaño de la ventana
GLint main_window_w = 900 + 3 * GAP;
GLint main_window_h = 600 + 3 * GAP;

// Posicion Inicial Ventana (definidas en init)
GLint main_window_x;
GLint main_window_y;

// Tamaño de la subventana 1 - CANVAS
GLint subwindow1_w = main_window_w*.8 - GAP;
GLint subwindow1_h = main_window_h*.8 - GAP;

GLint subwindow1_x = GAP;
GLint subwindow1_y = GAP;

// Tamaño de las subventanas para SELECCIONAR (2)
GLint subwindow_figures_w = (main_window_w * .4) - (2 * GAP);
GLint subwindow_figures_h = (main_window_h * .2) - (2 * GAP);

GLint  subwindow_figures_x = GAP;
GLint  subwindow_figures_y = (2 * GAP) + subwindow1_h;

GLint subwindow_canvas_figures_w = (main_window_w * .4);
GLint subwindow_canvas_figures_h = (main_window_h * .2) - (2 * GAP);

GLint  subwindow_canvas_figures_x = (2 * GAP) + subwindow_figures_w;
GLint  subwindow_canvas_figures_y = (2 * GAP) + subwindow1_h;

// Tamaño de las subventanas para TRANSFORMATIONS (3)
GLint subwindow_translate_w = (main_window_w * .2) - (2 * GAP);
GLint subwindow_translate_h = (main_window_h * .25) - (2 * GAP);

GLint subwindow_translate_x = (2 * GAP) + subwindow1_w;
GLint subwindow_translate_y = GAP;

GLint subwindow_scale_w = (main_window_w * .2) - (2 * GAP);
GLint subwindow_scale_h = (main_window_h * .25) - (2 * GAP);

GLint subwindow_scale_x = (2 * GAP) + subwindow1_w;
GLint subwindow_scale_y = (2 * GAP) + subwindow_translate_h;

GLint subwindow_rotate_w = (main_window_w * .2) - (2 * GAP);
GLint subwindow_rotate_h = (main_window_h * .25) - (2 * GAP);

GLint subwindow_rotate_x = (2 * GAP) + subwindow1_w;
GLint subwindow_rotate_y = (3 * GAP) + (2 * subwindow_translate_h);






/**
====================================
AID METHODS
------------------------------------
**/
void clearScreen(GLfloat r, GLfloat g, GLfloat b){
	glClearColor(r, g, b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glutSwapBuffers();
}


void clearScreenFrom(int subwindow){
	glutSetWindow(subwindow);
	clearScreen(1, 1, 1);
}


void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

GLfloat middleCoordX(std::string to, GLfloat charSize){
	return -(to.length()*charSize / 2);
}






void subwindow1_reshape(int width, int height)
{
	//  Represents a side of the viewport. A viewport is intended to
	//  to take a square shape so that the aspect ratio is reserved
	int viewport_side = 0;

	//  Viewport x and y positions 
	int viewport_x = 0, viewport_y = 0;

	//  Calculate viewport side
	viewport_side = (width > height) ? height : width;

	//  Calculate viewport position (Center viewport)
	viewport_x = (width - viewport_side) / 2;
	viewport_y = (height - viewport_side) / 2;

	//  Preserve aspect ratio
	glViewport(0, 0, width, height);

	//  Set subwindow width and height
	subwindow1_w = width;
	subwindow1_h = height;

	//  Notify that we are reshaping subwindow 1
	printf("Subwindow 1: ");

	//  Print current width and height
	printf("Width: %d, Height: %d, Viewport Side: %d.\n", width,
		height, viewport_side);
}


void init()
{
	glutSetWindow(mainwindow);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glutSetWindow(subwindow_1);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutSetWindow(subwindow_2);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutSetWindow(subwindow_3);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutSetWindow(subwindow_4);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutSetWindow(subwindow_5);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutSetWindow(subwindow_6);
	glClearColor(1.f, 1.f, 1.f, 1.f);

}

/**
====================================
RENDER METHODS
------------------------------------
**/

BOOLEAN selectFig = false,
selectCanvasFig = false,
selectTranslate = false,
selectScale = false,
selectRotate = false;


void renderMainWindow()
{
	glutSetWindow(mainwindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Se limpian los buffers con el color activo definido por glClearColor
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}


void renderSubwindow1(){

	glutSetWindow(subwindow_1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0);

	for (int i = 0; i < fci_size; i++){
		if (i == fci){
			scene.at(i)->setColor(1.f, 0.f, 0.f);
			//cout << "Coloree de Rojo el: " << i << endl;

		}
		else{
			scene.at(i)->setColor(0.f, 0.f, 0.f);
		}

		scene.at(i)->render();
	}

	drawBitmapText("Osama Hosam's OpenGL Tutorials", 1, 1, 0);

	glutSwapBuffers();
}


void renderSubwindow2(){

	glutSetWindow(subwindow_2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0); //black


	string text = "Selecciona una Figura";
	GLfloat x = middleCoordX(text, .1);
	cout << x << endl;
	drawBitmapText(&text[0], x / 2, .4, 0);

	currentDrawFigure = figureOptions[foi];
	drawBitmapText(&currentDrawFigure[0], -.15, -.2, 0);

	glutSwapBuffers();
}


void renderSubwindow3(){

	glutSetWindow(subwindow_3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0); //black

	string text = "Seleccionar Figura Dentro del Canvas";
	GLfloat x = middleCoordX(text, .1);
	drawBitmapText(&text[0], x / 2, .4, 0);

	if (fci_size > 0){
		drawBitmapText(&(drawnFigures[fci])[0], -.15, -.2, 0);

	}

	glutSwapBuffers();
}



void renderSubwindow4(){

	glutSetWindow(subwindow_4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0);

	string text = "1. Trasladar";
	GLfloat x = middleCoordX(text, .1);
	drawBitmapText(&text[0], x, 0, 0);

	string text2 = "Eje X: G+ D-";
	GLfloat x1 = middleCoordX(text2, .1);
	drawBitmapText(&text2[0], x1, -.5, 0);

	string text3 = "Eje Y: R+ F-";
	drawBitmapText(&text3[0], x1, -1, 0);

	glutSwapBuffers();
}

void renderSubwindow5(){

	glutSetWindow(subwindow_5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0);

	string text = "2. Escalar";
	GLfloat x = middleCoordX(text, .1);
	drawBitmapText(&text[0], x, 0, 0);

	string text2 = "Uniforme: I+ K-";
	GLfloat x1 = middleCoordX(text2, .1);
	drawBitmapText(&text2[0], x1, -.5, 0);
	//drawBitmapText(&currentDrawFigure[0], 0, 0, 0);

	glutSwapBuffers();
}


void renderSubwindow6(){

	glutSetWindow(subwindow_6);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0);

	string text = "3. Rotar";
	GLfloat x = middleCoordX(text, .1);
	drawBitmapText(&text[0], x, .5, 0);

	string text2 = "Eje X: E+ D-";
	string text3 = "Eje Y: R+ F-";
	string text4 = "Eje Z: T+ G-";

	GLfloat x1 = middleCoordX(text2, .1);

	drawBitmapText(&text2[0], x1, 0, 0);
	drawBitmapText(&text3[0], x1, -.5, 0);
	drawBitmapText(&text4[0], x1, -1, 0);


	//drawBitmapText(&currentDrawFigure[0], 0, 0, 0);

	glutSwapBuffers();
}


void clearTranformationButtons(){

	clearScreenFrom(subwindow_4);
	clearScreenFrom(subwindow_5);
	clearScreenFrom(subwindow_6);

	renderSubwindow4();
	renderSubwindow5();
	renderSubwindow6();

}


void clearSelectControls(){
	clearScreenFrom(subwindow_2);
	clearScreenFrom(subwindow_3);

	renderSubwindow2();
	renderSubwindow3();
}


void storeFigureName(string name, int num){

	std::string numb = std::to_string(num);
	std::string myFigure = strcat(&name[0], &numb[0]);
	drawnFigures[fci_size] = myFigure;
	fci_size++;
}


/**
====================================
MOUSE LISTENERS
------------------------------------
**/

void subwindow1_mouse(int button, int state, int x, int y){
	//click al canvas
	if (state == 1){
		if (selectFig){
			switch (foi)
			{
			case SPHERE:{
							SphereGL *obj = new SphereGL();
							obj->scale(.5f, .5f, .5f);
							scene.push_back(obj);
							storeFigureName("SPHERE", ++numDoneFigures[SPHERE]);
							break;
			}
			case CONE:{
						  ConeGL *obj = new ConeGL();
						  obj->scale(.25f, .25f, .25f);
						  scene.push_back(obj);
						  storeFigureName("CONE", ++numDoneFigures[CONE]);
						  break;
			}
			case CUBE:{
						  //ObjectGL *obj = new CubeGL();
						  CubeGL *obj = new CubeGL();
						  obj->scale(0.5f, 0.5f, 0.5f);
						  scene.push_back(obj);
						  storeFigureName("CUBE", ++numDoneFigures[CUBE]);
						  break;
			}

			case BOX:{
						 BoxGL *obj = new BoxGL();
						 obj->scale(.25f, .25f, .25f);
						 scene.push_back(obj);
						 storeFigureName("BOX", ++numDoneFigures[BOX]);
						 break;
			}
			case TORO:{
						  TorusGL *obj = new TorusGL();
						  obj->scale(.5f, .5f, .5f);
						  obj->scale(.25f, .25f, .25f);
						  scene.push_back(obj);
						  storeFigureName("TORUS", ++numDoneFigures[TORO]);
						  break;
			}
			case TETRA:{
						   TetraGL *obj = new TetraGL();
						   obj->scale(.5f, .5f, .5f);
						   obj->scale(.5f, .5f, .5f);
						   scene.push_back(obj);
						   storeFigureName("TETRA", ++numDoneFigures[TETRA]);
						   break;
			}
			case OCTAH:{
						   OctaGL *obj = new OctaGL();
						   obj->scale(.5f, .5f, .5f);
						   obj->scale(.5f, .5f, .5f);
						   scene.push_back(obj);
						   storeFigureName("OCTA", ++numDoneFigures[OCTAH]);
						   break;
			}
			case DODE:{
						  DodecaGL *obj = new DodecaGL();
						  obj->scale(.5f, .5f, .5f);
						  obj->scale(.5f, .5f, .5f);
						  scene.push_back(obj);
						  storeFigureName("DODE", ++numDoneFigures[DODE]);
						  break;
			}
			case ICOSA:{
						   IcosaGL *obj = new IcosaGL();
						   obj->scale(.5f, .5f, .5f);
						   scene.push_back(obj);
						   storeFigureName("ICOSA", ++numDoneFigures[ICOSA]);
						   break;
			}
			case TEA:{
						 TeapotGL *obj = new TeapotGL();
						 scene.push_back(obj);
						 storeFigureName("TEA", ++numDoneFigures[TEA]);
						 break;
			}
			case CILY:{
						  CylinderGL *obj = new CylinderGL();
						  obj->setColor(.0f, .0f, .0f);
						  obj->translate(0.f, 0.f, -0.25f);
						  obj->scale(0.75f, 0.75f, 0.75f);
						  scene.push_back(obj);
						  storeFigureName("CYLI", ++numDoneFigures[CILY]);
						  break;
			}
			case DISK:{
						  DiskGL *obj = new DiskGL();
						  scene.push_back(obj);
						  storeFigureName("DISK", ++numDoneFigures[DISK]);
						  break;
			}
			case DOT:{
						 scene.push_back(new PointGL());
						 storeFigureName("DOT", ++numDoneFigures[DOT]);
						 break;
			}
			case SEG:{
						 scene.push_back(new LineGL());
						 storeFigureName("SEG", ++numDoneFigures[SEG]);
						 break;
			}
			case TRIA:{
						  TriangleGL *obj = new TriangleGL();
						  obj->scale(0.5f, 0.5f, 0.5f);
						  scene.push_back(obj);
						  storeFigureName("TRIA", ++numDoneFigures[TRIA]);
						  break;
			}
			case QUAD:{
						  QuadGL *obj = new QuadGL();
						  obj->scale(0.5f, 0.5f, 0.5f);
						  scene.push_back(obj);
						  storeFigureName("QUAD", ++numDoneFigures[QUAD]);
						  break;
			}
			case PYRA:{
						  PyramidGL *obj = new PyramidGL();
						  obj->scale(0.5f, 0.5f, 0.5f);
						  scene.push_back(obj);
						  storeFigureName("PYRA", ++numDoneFigures[PYRA]);
						  break;
			}
			default:
				break;
			}

			clearScreen(1.f, 1.f, 1.f);
			renderSubwindow1();
			clearSelectControls();
			selectFig = false;
		}
	}




}

void subwindow2_mouse(int button, int state, int x, int y) {
	if (state == 1){
		if (!selectFig){
			//activate!
			clearScreen(0, 1, 1); // cyan
			selectFig = true;
			selectCanvasFig = false;
			glutSetWindow(subwindow_3);
			clearScreen(1, 1, 1);
			renderSubwindow3();
			clearTranformationButtons();
		}
		else{
			clearScreen(1, 1, 1); // white
			selectFig = false;
		}
	}
}

void subwindow3_mouse(int button, int state, int x, int y) {
	if (state == 1){
		if (!selectCanvasFig){
			//activate!
			clearScreen(0, 1, 1); // cyan
			selectCanvasFig = true;
			selectFig = false;
			glutSetWindow(subwindow_2);
			clearScreen(1, 1, 1);
			renderSubwindow2();
		}
		else{
			//deactivate
			clearScreen(1, 1, 1); // white
			selectCanvasFig = false;
		}
	}
}


void subwindow4_mouse(int button, int state, int x, int y) {
	if (state == 1){
		if (!selectTranslate){

			if (selectFig == true){
				return;
			}

			clearScreen(1, 1, 0); // yellow

			selectTranslate = true;
			selectScale = false;
			selectRotate = false;

			clearScreenFrom(subwindow_5);
			clearScreenFrom(subwindow_6);

			renderSubwindow5();
			renderSubwindow6();

		}
		else{
			clearScreen(1, 1, 1); // white
			selectTranslate = false;
		}
	}

}

void subwindow5_mouse(int button, int state, int x, int y) {

	if (state == 1){
		if (!selectScale){

			if (selectFig == true){
				return;
			}

			clearScreen(1, 1, 0);

			selectTranslate = false;
			selectScale = true;
			selectRotate = false;

			clearScreenFrom(subwindow_4);
			clearScreenFrom(subwindow_6);

			renderSubwindow4();
			renderSubwindow6();

		}
		else{
			clearScreen(1, 1, 1);
			selectScale = false;
		}
	}

}

void subwindow6_mouse(int button, int state, int x, int y) {

	if (state == 1){
		if (!selectRotate){

			if (selectFig == true){
				return;
			}

			clearScreen(1, 1, 0);

			selectTranslate = false;
			selectScale = false;
			selectRotate = true;

			clearScreenFrom(subwindow_4);
			clearScreenFrom(subwindow_5);

			renderSubwindow4();
			renderSubwindow5();

		}
		else{
			clearScreen(1, 1, 1);
			selectRotate = false;
		}
	}

}


/**
====================================
KEYBOARD LISTENERS
------------------------------------
**/
void selectNewFigure(unsigned char key, int x, int y){

	cout << key << endl;
	if (key == GLUT_KEY_LEFT){
		if (foi == 0){
			foi = foi_size;
		}
		else{
			foi--;
		}
	}

	if (key == GLUT_KEY_RIGHT){
		if (foi == foi_size){
			foi = 0;
		}
		else{
			foi++;
		}
	}

	renderSubwindow2();
	cout << "Figure to draw" << foi << endl;
}


void selectFigureFromCanvas(unsigned char key, int x, int y){


	if (key == GLUT_KEY_LEFT){
		if (fci == 0){
			fci = fci_size - 1;
		}
		else{
			fci--;
		}
	}

	if (key == GLUT_KEY_RIGHT){
		if (fci == fci_size - 1){
			fci = 0;
		}
		else{
			fci++;
		}
	}

	renderSubwindow1();
	renderSubwindow3();

}

void translateFigure(unsigned char key, int x, int y){

	cout << "fci : " << fci << endl;
	cout << "Your key : " << key << endl;



	if (fci_size){

		switch (key){
		case 'd':{
					 cout << "GO LEFT" << endl;
					 scene.at(fci)->translate(-0.1f, 0.0f, 0.0f);
					 break;
		}
		case 'g':{
					 cout << "GO RIGHT" << endl;
					 scene.at(fci)->translate(0.1f, 0.0f, 0.0f);
					 break;
		}
		case 'r':{
					 cout << "GO UP" << endl;
					 scene.at(fci)->translate(0.0f, 0.1f, 0.0f);
					 break;
		}
		case 'f':{
					 cout << "GO DOWN" << endl;
					 scene.at(fci)->translate(0.0f, -0.1f, 0.0f);
					 break;
		}
		}
	}

	renderSubwindow1();
}

void scalateFigure(unsigned char key, int x, int y){

	cout << "fci : " << fci << endl;

	if (fci_size){

		switch (key){
		case 'd':{
					 cout << "Less X" << endl;
					 scene.at(fci)->scale(0.9f, 1.0f, 1.0f);
					 break;
		}
		case 'e':{
					 cout << "More X" << endl;
					 scene.at(fci)->scale(1.1f, 1.0f, 1.0f);
					 break;
		}
		case 'r':{
					 cout << "More Y" << endl;
					 scene.at(fci)->scale(1.0f, 1.1f, 1.0f);
					 break;
		}
		case 'f':{
					 cout << "Less Y" << endl;
					 scene.at(fci)->scale(1.0f, 0.9f, 1.0f);
					 break;
		}
		case 't':{
					 cout << "More Z" << endl;
					 scene.at(fci)->scale(1.0f, 1.0f, 1.1f);
					 break;
		}
		case 'g':{
					 cout << "Less Z" << endl;
					 scene.at(fci)->scale(1.0f, 1.0f, 0.9f);
					 break;
		}
		case 'i':{
					 cout << "Complete Scale Up" << endl;
					 scene.at(fci)->scale(1.1f, 1.1f, 1.1f);
					 break;
		}
		case 'k':{
					 cout << "Complete Scale Down" << endl;
					 scene.at(fci)->scale(0.9f, 0.9f, 0.9f);
					 break;
		}
		}
	}

	renderSubwindow1();
}

void rotateFigure(unsigned char key, int x, int y){

	cout << "fci : " << fci << endl;

	if (fci_size){

		switch (key){
		case 'd':{
					 cout << "Rotate -X" << endl;
					 scene.at(fci)->rotate(-1.f, 1.0f, 0.0f, 0.0f);
					 break;
		}
		case 'e':{
					 cout << "Rotate +X" << endl;
					 scene.at(fci)->rotate(1.f, 1.0f, 0.0f, 0.0f);
					 break;
		}
		case 'r':{
					 cout << "Rotate +Y" << endl;
					 scene.at(fci)->rotate(1.f, 0.0f, 1.0f, 0.0f);
					 break;
		}
		case 'f':{
					 cout << "Rotate -Y" << endl;
					 scene.at(fci)->rotate(-1.f, 0.0f, 1.0f, 0.0f);
					 break;
		}
		case 't':{
					 cout << "Rotate +Z" << endl;
					 scene.at(fci)->rotate(1.f, 0.0f, 0.0f, 1.0f);
					 break;
		}
		case 'g':{
					 cout << "Rotate -Z" << endl;
					 scene.at(fci)->rotate(-1.f, 0.0f, 0.0f, 1.0f);
					 break;
		}
		}
	}

	renderSubwindow1();
}


void onCanvas(unsigned char key, int x, int y){

	renderSubwindow1();

}


int main(GLint argc, GLchar **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	main_window_x = (glutGet(GLUT_SCREEN_WIDTH) / 2) - (main_window_w / 2);
	main_window_y = (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (main_window_h / 2);
	glutInitWindowPosition(main_window_x, main_window_y);
	glutInitWindowSize(main_window_w, main_window_h);
	mainwindow = glutCreateWindow("OpenGL Paint");
	glutSetWindow(mainwindow);
	glutDisplayFunc(renderMainWindow);

	subwindow_1 = glutCreateSubWindow(mainwindow, subwindow1_x, subwindow1_y, subwindow1_w, subwindow1_h);
	glutSetWindow(subwindow_1);
	glutMouseFunc(subwindow1_mouse);
	glutDisplayFunc(renderSubwindow1);
	glutKeyboardFunc(onCanvas);
	glutReshapeFunc(subwindow1_reshape);

	subwindow_2 = glutCreateSubWindow(mainwindow, subwindow_figures_x, subwindow_figures_y, subwindow_figures_w, subwindow_figures_h);
	glutSetWindow(subwindow_2);
	glutMouseFunc(subwindow2_mouse);
	glutDisplayFunc(renderSubwindow2);
	glutKeyboardFunc(selectNewFigure);
	glutIdleFunc(renderSubwindow2);

	subwindow_3 = glutCreateSubWindow(mainwindow, subwindow_canvas_figures_x, subwindow_canvas_figures_y, subwindow_canvas_figures_w, subwindow_canvas_figures_h);
	glutSetWindow(subwindow_3);
	glutMouseFunc(subwindow3_mouse);
	glutDisplayFunc(renderSubwindow3);
	glutKeyboardFunc(selectFigureFromCanvas);
	glutIdleFunc(renderSubwindow3);

	subwindow_4 = glutCreateSubWindow(mainwindow, subwindow_translate_x, subwindow_translate_y, subwindow_translate_w, subwindow_translate_h);
	glutSetWindow(subwindow_4);
	glutMouseFunc(subwindow4_mouse);
	glutDisplayFunc(renderSubwindow4);
	glutKeyboardFunc(translateFigure);
	glutIdleFunc(renderSubwindow4);

	subwindow_5 = glutCreateSubWindow(mainwindow, subwindow_scale_x, subwindow_scale_y, subwindow_scale_w, subwindow_scale_h);
	glutSetWindow(subwindow_5);
	glutMouseFunc(subwindow5_mouse);
	glutDisplayFunc(renderSubwindow5);
	glutKeyboardFunc(scalateFigure);
	glutIdleFunc(renderSubwindow5);

	subwindow_6 = glutCreateSubWindow(mainwindow, subwindow_rotate_x, subwindow_rotate_y, subwindow_rotate_w, subwindow_rotate_h);
	glutSetWindow(subwindow_6);
	glutMouseFunc(subwindow6_mouse);
	glutDisplayFunc(renderSubwindow6);
	glutKeyboardFunc(rotateFigure);
	glutIdleFunc(renderSubwindow6);



	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error");
		return false;
	}

	init();
	glutMainLoop();
	return 0;
}