//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Axis.h"

	Axis::Axis(){

	}

	Axis::~Axis(){

	}

	void Axis::draw(){
		glBegin( GL_LINES );
		glVertex3f(0, 0, 0);      // origin
		glVertex3f(200, 0, 0);	  // x   
 
		glVertex3f(0, 0, 0);      // center
		glVertex3f(0, 200, 0);	  // y

		glVertex3f(0, 0, 0);      // origin
		glVertex3f(0, 0, 200);	  // z   
		glEnd();
	}