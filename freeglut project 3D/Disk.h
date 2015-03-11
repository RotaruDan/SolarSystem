//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef DiskH
#define DiskH

#include "Actor.h"

class Disk : public Actor {

	private:
	    GLUquadric * quadric;
	    GLdouble innerRadius, outerRadius;
	    GLint slices, loops;
	    void init();

	public:
		Disk();
		Disk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops);
		~Disk();
		void draw();
};

#endif