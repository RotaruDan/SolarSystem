//---------------------------------------------------------------------------
// Ana Gil Luezas
//---------------------------------------------------------------------------
#ifndef Scene1H
#define Scene1H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include <GL/freeglut.h>  // teapot de glut
//#include <GL/glut.h>
//---------------------------------------------------------------------------
class Scene{
protected:
  struct sphere{
    GLUquadricObj *pEsf;
    GLint ang;
    GLdouble dis;} 
  esfera;
  struct square {
	  GLint ang;
  } mSquare;
  void drawEsfera();
  void drawAxes();
  void drawTriangle();
  void drawPiramid();
  void drawSquare();
public:
  Scene();
  ~Scene();
  void init();
  void render();
};

#endif

