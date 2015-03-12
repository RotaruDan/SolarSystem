//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Actor.h"

	Actor::Actor(){
		r = 0.0;
		g = 0.0;
		b = 0.0; 
		a = 1.0;
		x = 0.0;
		y = 0.0;
		z = 0.0;
		angle = 0;
		angleX = 0.0;
		angleY = 0.0;
		angleZ = 0.0;
	}

	Actor::~Actor(){

	}

	GLint Actor::getAngle(){
		return angle;
	}

	GLdouble Actor::getAngleX(){
		return angleX;
	}

	GLdouble Actor::getAngleY(){
		return angleY;
	}

	GLdouble Actor::getAngleZ(){
		return angleZ;
	}

	GLdouble Actor::getX(){
		return x;
	}

	GLdouble Actor::getY(){
		return y;
	}

	GLdouble Actor::getZ(){
		return z;
	}

	void Actor::setAngleVector(GLdouble angX, GLdouble angY, GLdouble angZ){
		angleX = angX;
		angleY = angY;
		angleZ = angZ;
	}

	void Actor::setAngle(GLint ang){
		angle = ang;
	}

	void Actor::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
		Actor::r = r;
		Actor::g = g;
		Actor::b = b;
		Actor::a = a;
	}

	void Actor::setX(GLdouble x){
		Actor::x = x;
	}

	void Actor::setY(GLdouble y){
		Actor::y = y;
	}

	void Actor::setZ(GLdouble z){
		Actor::z = z;
	}

	void Actor::render(){
		glPushMatrix();
		glColor4f(r, g, b, a);
		glRotated(angle, angleX, angleY, angleZ);
		glTranslated(x, y, z);
		draw();
		glPopMatrix();
	}

	void Actor::draw(){

	}