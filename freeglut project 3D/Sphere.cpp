//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Sphere.h"

	Sphere::Sphere(){
		radius = 45.0;
		slices = 60;
		stacks = 60;
		init();
	}

	Sphere::Sphere(GLdouble radius, GLint slices, GLint stacks){
		Sphere::radius = radius;
		Sphere::slices = slices;
		Sphere::stacks = stacks;
		init();
	}

	void Sphere::init(){		
	    quadric=gluNewQuadric();
	    gluQuadricDrawStyle(quadric, GLU_FILL);			//  GLU_LINE
	    gluQuadricOrientation (quadric, GLU_OUTSIDE);	// GLU_INSIDE 
	    gluQuadricNormals(quadric, GLU_SMOOTH);			// GLU_FLAT
	}

	Sphere::~Sphere(){
		gluDeleteQuadric(quadric);
	}

	void Sphere::draw(){
		gluSphere(quadric, radius, slices, stacks);
	}