//---------------------------------------------------------------------------
#include "scene1.h"
//---------------------------------------------------------------------------

scene::scene(){
  esfera.pEsf=gluNewQuadric();
  iniciar();
}

scene::~scene(){
  gluDeleteQuadric(esfera.pEsf);
}

void scene::iniciar(){
  esfera.ang=0;
  esfera.dis=0;
  gluQuadricDrawStyle(esfera.pEsf, GLU_FILL);  //  GLU_LINE
  gluQuadricOrientation (esfera.pEsf,GLU_OUTSIDE); // GLU_INSIDE 
  gluQuadricNormals(esfera.pEsf,GLU_SMOOTH);  // GLU_FLAT
}

void scene::dibujar(){
  glMatrixMode(GL_MODELVIEW);
  drawAxes();
  //drawEsfera();
  glPushMatrix();
 
  glPopMatrix();
}

void scene::drawEsfera(){
  glPushMatrix();
    glColor4f(1.0,1.0,0.0,1.0);
    //glRotated(esfera.ang,0,1,0);   // Y-roll
	glScaled(2, 2, 2);
    glTranslated(esfera.dis,0,0);  // en el eje X
    glRotated(esfera.ang,0,1,0);   // Y-roll
    gluSphere(esfera.pEsf,50,24,24);
  glPopMatrix();
}

void scene::drawAxes(){
	// Drawing axes
  glBegin( GL_LINES );
    glColor3f(1.0, 0.0, 0.0); // red
    glVertex3f(0, 0, 0);      // origin
    glVertex3f(200, 0, 0);	  // x   
 
    glColor3f(0.0, 1.0, 0.0); // green
    glVertex3f(0, 0, 0);      // center
    glVertex3f(0, 200, 0);	  // y

    glColor3f(0.0, 0.0, 1.0); // blue
    glVertex3f(0, 0, 0);      // origin
    glVertex3f(0, 0, 200);	  // z   
  glEnd();
}


void scene::incAng(GLint a){
  esfera.ang = (esfera.ang + a) % 360;
}

void scene::setDis(GLdouble d){
  esfera.dis = d;  
}

void scene::incSquareAngle(GLint amount){
  mSquare.ang = (mSquare.ang + amount) % 360;
}

