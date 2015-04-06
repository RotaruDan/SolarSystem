//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Mesh.h"

	Mesh::Mesh(char* charname) {
		model = glmReadOBJ(charname);
	}

	Mesh::Mesh(char* charname, GLfloat scale) {
		model = glmReadOBJ(charname);
		glmUnitize(model);
		glmFacetNormals(model);
		
		glmScale(model, scale);
	}

	Mesh::~Mesh(){
		glmDelete(model);
	}

	void Mesh::draw(){		
		glmDraw(model, GL_SMOOTH);
	}