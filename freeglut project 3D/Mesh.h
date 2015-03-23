//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef MeshH
#define MeshH

#include "Actor.h"
#include "glm.h"

class Mesh : public Actor {

	private:
		GLMmodel* model;

	public:
		Mesh(char* filename);
		Mesh(char* filename, GLfloat scale);
		~Mesh();
		void draw();
};

#endif