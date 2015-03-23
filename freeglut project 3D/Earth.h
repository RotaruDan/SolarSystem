//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef EarthH
#define EarthH

#include "Sphere.h"

class Earth : public Sphere {

	private:
		GLuint textureID;
		void init();

	public:
		Earth();
		~Earth();
		void draw();
};

#endif