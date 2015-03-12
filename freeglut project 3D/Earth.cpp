//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Earth.h"
#include "TextureLoader.h"

	Earth::Earth() : Sphere(20, 25, 25){
		init();
	}

	void Earth::init(){		

		unsigned int width, height;
		unsigned char * data = loadBMPRaw("earth.bmp", width, height);
		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);
		
		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

		// Trilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		delete[] data;
	}

	void Earth::draw(){
		Sphere::draw();
	}