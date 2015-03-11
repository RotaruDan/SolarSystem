//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef SateliteH
#define SateliteH

#include "Actor.h"

class Satelite : public Actor {

	private:
		GLdouble scale;

	public:
		Satelite();
		Satelite(GLdouble scale);
		~Satelite();
		void draw();
		void drawTriangle();
		void drawPiramid();
		void drawSquare();
};

#endif