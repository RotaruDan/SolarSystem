//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef SphereH
#define SphereH

#include "Actor.h"

class Sphere : public Actor {

	private:
		GLdouble radius;
		GLint slices, stacks;
		void init();

	protected:	
		GLUquadric * quadric;

	public:
		Sphere();
		Sphere(GLdouble radius, GLint slices, GLint stacks);
		~Sphere();
		void draw();
};

#endif