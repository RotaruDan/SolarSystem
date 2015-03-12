//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Disk.h"

using namespace std;

	Disk::Disk(){
		innerRadius = 68.5;
		outerRadius = 71.5;
		slices = 80;
		loops = 1;
		init();
	}

	Disk::Disk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops){
		Disk::innerRadius = innerRadius;
		Disk::outerRadius = outerRadius;
		Disk::slices = slices;
		Disk::loops = loops;
		init();
	}

	void Disk::init(){		
	    quadric = gluNewQuadric();
	    gluQuadricDrawStyle(quadric, GLU_FILL);			// GLU_LINE
	    gluQuadricOrientation (quadric, GLU_INSIDE);	// GLU_INSIDE 
		gluQuadricNormals(quadric, GLU_FLAT);			// GLU_FLAT
	}

	Disk::~Disk(){
		gluDeleteQuadric(quadric);
	}

	void Disk::draw(){
		gluDisk(quadric, innerRadius, outerRadius, slices, loops);
	}