//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef ActorH
#define ActorH

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Actor{

	private:
		GLint angle;
		GLdouble angleX, angleY, angleZ;
		GLdouble x, y, z;

	protected:
		GLfloat r, g, b, a;

	public:
		Actor();
		~Actor();

		GLint getAngle();
		GLdouble getAngleX();
		GLdouble getAngleY();
		GLdouble getAngleZ();

		GLdouble getX();
		GLdouble getY();
		GLdouble getZ();

		void setAngleVector(GLdouble angX, GLdouble angY, GLdouble angZ);
		void setAngle(GLint ang);
		
		void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		void setX(GLdouble x);
		void setY(GLdouble y);
		void setZ(GLdouble z);

		void render();

		virtual void draw();
};

#endif