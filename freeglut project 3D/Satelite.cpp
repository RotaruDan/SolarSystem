//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Satelite.h"

	Satelite::Satelite(){
		scale = 20;
	}

	Satelite::Satelite(GLdouble scale){
		Satelite::scale = scale;
	}

	Satelite::~Satelite(){

	}

	void Satelite::draw(){
		glRotated(90, 0, 0, 1);
		glTranslated(0, -scale, 0);
		drawPiramid();
		glTranslated(0, 2*scale, 0);
		glScaled(1, -1, 1);
		drawPiramid();
		glScaled(1, -1, 1);
		glTranslated(0, -scale, 0);  
		glRotated(0, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		GLdouble quarterScale = scale *.25f;
		glScaled(quarterScale, quarterScale, 0);
		drawSquare();
	}
	
	void Satelite::drawTriangle(){
		glScaled(scale, scale, scale);
		glBegin(GL_TRIANGLES); 
		glNormal3f(1.0, 1.0, 1.0);  // normal xyz
		glColor3f(1.0, 0.0, 0.0);   // red
		glVertex3f(0.5, 0.0, 0.0);  // vértice x
		glColor3f(0.0, 1.0, 0.0);   // green
		glVertex3f(0.0, 1.0, 0.0);  // vértice y
		glColor3f(0.0, 0.0, 1.0);   // blue
		glVertex3f(0.0, 0.0, 0.5);  // vértice z
		glEnd();
		GLdouble invScale = 1.0/scale;
		glScaled(invScale, invScale, invScale);
	}

	void Satelite::drawPiramid(){
		for(int i = 0; i < 4; ++i){
			glRotated(90, 0, 1, 0);
			drawTriangle();
		}
	}

	void Satelite::drawSquare(){
		glBegin(GL_QUADS);  // CUADRADO
		glNormal3f(0.5, 0.5, 0.5);  // normal xyz
		glColor3f(1.0, 0.0, 0.0);   // red
		glVertex3f(1, 1, 0.0);  // vértice x
		glColor3f(0.0, 1.0, 0.0);   // green
		glVertex3f(1, -1, 0.0);  // vértice y
		glColor3f(0.0, 0.0, 1.0);   // blue
		glVertex3f(-1, -1, 0);  // vértice z
		glColor3f(0.0, 0.0, 0.0);   // black
		glVertex3f(-1, 1, 0);  // vértice z
		glEnd();
	}