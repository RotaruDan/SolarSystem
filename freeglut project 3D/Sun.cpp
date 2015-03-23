//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Sun.h"

	Sun::Sun() : Sphere() {
	}

	Sun::~Sun(){
		Sphere::~Sphere();
	}

	void Sun::draw(){		
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sunOn);
		Sphere::draw();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sunOff);
	}