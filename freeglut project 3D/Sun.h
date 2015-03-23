//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef SunH
#define SunH

#include "Sphere.h"

const GLfloat sunOn[]  = {1.0, 0.75, 0.0};
const GLfloat sunOff[] = {0.0, 0.0, 0.0};

class Sun : public Sphere {

	public:
		Sun();
		~Sun();
		void draw();
};

#endif