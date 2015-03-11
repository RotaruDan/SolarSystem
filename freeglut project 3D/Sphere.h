//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef SphereH
#define SphereH

#include "Actor.h"

class Sphere : public Actor {

	private:
		GLUquadric * quadric;
		GLdouble radius;
		GLint slices, stacks;
		void init();

	public:
		Sphere();
		Sphere(GLdouble radius, GLint slices, GLint stacks);
		~Sphere();
		void draw();
};

#endif