//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef EarthH
#define EarthH

#include "Sphere.h"

class Earth : public Sphere {

	private:
		void init();

	public:
		Earth();
		~Earth();
		void draw();
};

#endif