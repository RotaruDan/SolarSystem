//---------------------------------------------------------------------------
// Dan Cristia, Rotaru
//---------------------------------------------------------------------------
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>

#include "Mesh.h"
#include "Sun.h"
#include "Axis.h" 
#include "Sphere.h" 
#include "Earth.h" 
#include "Disk.h" 
#include "Satelite.h" 
#include "Group.h"
//---------------------------------------------------------------------------

// Viewport size  (left=right=0)
struct viewPort{GLsizei w; GLsizei h;} Vp = {400, 400};
// Camera parameters
struct viewCamera{GLdouble eyeX, eyeY, eyeZ;
        GLdouble lookX, lookY, lookZ;
        GLdouble upX, upY, upZ;} 
			initial = {100, 100, 100, 0, 0, 0, 0, 1, 0}, 
			front = {0, 0, 100, 0,0,0, 0,1,0},
			topView = {0, 100, 0, 0,0,0, 1,0,1}, 
			lateral = {100, 0, 0, 0,0,0, 0,1,0};
// Viewing frustum parameters
struct viewVolume{GLdouble xRight, xLeft;
        GLdouble yTop, yBot;
        GLdouble zNear, zFar;} Pj = {200,-200, 200,-200, 1,1000};

GLdouble scale = 1;
bool tiling, ortho = true;
viewCamera * currentView = &initial;
GLfloat light_position1[] = {0, 0, 0, 1.0f};

// Scene
Mesh plane("f-16.obj", 2);
Group root;
Sun sun;
Group earthSystem;
Satelite satelite;
Sphere moon(4, 10, 10);

// prototipos
void updateProjection();
void updateCamera();
void initScene();
void initGL();
void resize(int wW, int wH);
void display();
void keyPres(unsigned char key, int mX, int mY);
void keySp(int key, int mX, int mY);
//---------------------------------------------------------------------------

// programa principal
int main(int argc, char* argv[]){ 
	// Initialization 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Doble buffer, rgba y profundidad.
	glutInitWindowSize(Vp.w, Vp.h); 
	glutInitWindowPosition(100,100);
	glutInit(&argc,argv);
	// Window construction
	int win=glutCreateWindow("Práctica 1 - Un sistema planetario");
	// Callback registration
  
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPres);
	glutSpecialFunc(keySp);
	// OpenGL basic setting
	initGL();

	// iniciar la escena desde la raiz

	// Axis for debugging
	Axis axis;
	root.addChildren(&axis);
	
	Group solarSystem;
	// Solar system
	root.addChildren(&solarSystem);
	solarSystem.setAngleVector(0, 1, 0);		// Rotating around Y axis

	sun.setAngleVector(0, 1, 0);
	sun.setColor(1.0, 1.0, 0.0, 1.0);
	solarSystem.addChildren(&sun);

	Disk earthOrbit;
	earthOrbit.setColor(1.0, 1.0, 0.0, 1.0);
	earthOrbit.setAngle(90);					
	earthOrbit.setAngleVector(1, 0, 0);
	solarSystem.addChildren(&earthOrbit);

	// Earth system
	solarSystem.addChildren(&earthSystem);
	earthSystem.setX(70);
	earthSystem.setAngleVector(0, 1, 0);

	Earth earth;
	earth.setColor(1, 1, 1, 1);
	earth.setAngle(-90);
	earth.setAngleVector(1, 0, 0);
	earthSystem.addChildren(&earth);

	Disk moonOrbit(26.5, 27.5, 30, 1);
	moonOrbit.setColor(1, 1, 1, 1);
	moonOrbit.setAngle(90);					
	moonOrbit.setAngleVector(1, 0, 0);
	earthSystem.addChildren(&moonOrbit);

	moon.setColor(1, 1, 1, 1);
	moon.setAngleVector(0, 1, 0);
	moon.setX(27);
	earthSystem.addChildren(&moon);

	Disk sateliteOrbit(26.5, 27.5, 30, 1);
	sateliteOrbit.setColor(0, 1, 0, 1);
	earthSystem.addChildren(&sateliteOrbit);

	satelite.setColor(0, 1, 0, 1);
	satelite.setAngleVector(0, 0, 1);
	satelite.setY(27);
	earthSystem.addChildren(&satelite);

	Disk planeOrbit(26.5, 27.5, 30, 1);
	planeOrbit.setColor(0, 1, 1, 1);
	planeOrbit.setAngle(90);
	planeOrbit.setAngleVector(0, 1, 0);
	earthSystem.addChildren(&planeOrbit);

	plane.setColor(0, 1, 1, 1);
	plane.setAngleVector(1, 0, 0);
	plane.setY(27);
	earthSystem.addChildren(&plane);
  
	initScene();
	// Classic glut's main loop can be stopped after X-closing the window, using freeglut's setting
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
	glutMainLoop();  //while (continue_in_main_loop) glutMainLoopEvent();
	// Window destruction (never reach this point using classic glut)
	glutDestroyWindow(win);
	// liberar la escena
	return 0;
}
//---------------------------------------------------------------------------

void initScene(){
	sun.setAngle(0);
	earthSystem.setAngle(0);
	satelite.setAngle(0);
	moon.setAngle(0);
	tiling = false;
	currentView = &initial;

	initial.eyeX = 100;
	initial.eyeY = 100;
	initial.eyeZ = 100;

	front.eyeX = 0;
	front.eyeY = 0;
	front.eyeZ = 100;

	topView.eyeX = 0;
	topView.eyeY = 100;
	topView.eyeZ = 0;

	lateral.eyeX = 100;
	lateral.eyeY = 0;
	lateral.eyeZ = 0;

	updateCamera();
	ortho = true;
	updateProjection();
}

void initGL(){

	// Activar características de OpenGL
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);		// z buffer enable
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);   
	glEnable(GL_TEXTURE_2D); 

	GLfloat mat_diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat mat_ambient[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat mat_shininess[] = {100.0f};

	GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat light_position[] = {0, 0, 0, 1.0f};
	
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHT1);	
	GLfloat light_specular1[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat light_diffuse1[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	

	// set material property
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// SOL --> glMaterialfv(GL_FRONT, GL_EMISSION, mat_shininess);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// Viewport set up
	glViewport(0,0, Vp.w, Vp.h);  // Vp
	// Camera set up
	updateCamera();
	// Frustum set up
	updateProjection();
}

void updateCamera(){
	glMatrixMode(GL_MODELVIEW);   // VIEW
	glLoadIdentity();
	gluLookAt((*currentView).eyeX, (*currentView).eyeY, (*currentView).eyeZ,
		(*currentView).lookX,	(*currentView).lookY,	(*currentView).lookZ, 
		(*currentView).upX, (*currentView).upY, (*currentView).upZ);

}
//---------------------------------------------------------------------------

void resize(int wW, int wH){
	// Viewport set up     
	Vp.w = wW; Vp.h = wH; 
	glViewport(0,0, Vp.w, Vp.h); 

	// Frustum set up
	updateProjection();

	glutPostRedisplay();
}

void updateProjection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(ortho){
		Pj.xRight = Vp.w/ 2.0 / scale; Pj.xLeft = -Pj.xRight; 
		Pj.yTop = Vp.h/2.0 / scale;  Pj.yBot = -Pj.yTop; 
		glOrtho(Pj.xLeft,Pj.xRight, Pj.yBot,Pj.yTop, Pj.zNear, Pj.zFar);
	} else {
		gluPerspective(80, Vp.w / Vp.h, Pj.zNear, Pj.zFar );
	}
}
//---------------------------------------------------------------------------

void display(void) {
	
	light_position1[0] = static_cast<GLfloat>((*currentView).eyeX);
	light_position1[1] = static_cast<GLfloat>((*currentView).eyeY);
	light_position1[2] = static_cast<GLfloat>((*currentView).eyeZ);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glMatrixMode(GL_MODELVIEW);
	if(!tiling){
		glViewport(0,0, Vp.w, Vp.h); 
		root.render();
	} else {
		int columns = 4;
		int rows = 4;
		GLsizei vpW = Vp.w / columns;
		GLsizei vpH = Vp.h / rows;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				glViewport(i * vpW, j * vpH, vpW, vpH); 
				root.render();
			}
		}
	}

	glutSwapBuffers(); // Hay dos buffers que se van intercambiando para ir pinando en ellos
}
//---------------------------------------------------------------------------

void keyPres(unsigned char key, int mX, int mY){
	bool need_redisplay = true;
	if(key == 27) {  /* Escape key */  //continue_in_main_loop = false; (**)
		glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop 
	} else if(key == '+') { 
		if(scale < 10.) {
			scale +=0.25; resize(Vp.w, Vp.h);
		} 
	} else if(key == '-') { 
		if(scale > 0.3) {
			scale -=0.25; resize(Vp.w, Vp.h);
		} 
	} else if(key == 's') { 
		sun.setAngle(sun.getAngle() + 5); 
		earthSystem.setAngle(earthSystem.getAngle() + 4); 
		satelite.setAngle(satelite.getAngle() + 2); 
		plane.setAngle(plane.getAngle() + 2); 
		moon.setAngle(moon.getAngle() + 3); 
	} else if(key == 't') { 
		tiling = !tiling; 
	} else if(key == 'i') {
		initScene(); 
	} else if(key == 'x') {
		currentView = &lateral;
		updateCamera();
	} else if(key == 'y') {
		currentView = &front;
		updateCamera();
	} else if(key == 'z') {
		currentView = &topView;
		updateCamera();
	} else if(key == 'p') {
		ortho = !ortho;
		updateProjection();
	} else if(key == 'n') {
		if(currentView == &initial){
			currentView->eyeX -= 5;
			currentView->eyeY -= 5;
			currentView->eyeZ -= 5;	  
		} else if(currentView == &lateral){
			currentView->eyeX -= 5;	  
		} else if(currentView == &front){
			currentView->eyeZ -= 5;	  
		} else if(currentView == &topView){
			currentView->eyeY -= 5;
		}
		updateCamera();
	} else if(key == 'N') {
		if(currentView == &initial){
			currentView->eyeX += 5;
			currentView->eyeY += 5;
			currentView->eyeZ += 5;	 
		} else if(currentView == &lateral){
			currentView->eyeX += 5;	  
		} else if(currentView == &front){
			currentView->eyeZ += 5;	  
		} else if(currentView == &topView){
			currentView->eyeY += 5;
		}
		updateCamera();
	}  else if(key == 'u') {
		if(currentView == &initial){
			currentView->eyeX -= 5;
			currentView->eyeZ += 5;	  
		} else if(currentView == &lateral){
			currentView->eyeZ += 5;	  
		} else if(currentView == &front){
			currentView->eyeX -= 5;	  
		} else if(currentView == &topView){
			currentView->eyeZ -= 5;
			currentView->eyeX += 5;	  
		}
		updateCamera();
	} else if(key == 'U') {
		if(currentView == &initial){
			currentView->eyeX += 5;
			currentView->eyeZ -= 5;	  
		} else if(currentView == &lateral){
			currentView->eyeZ -= 5;	  
		} else if(currentView == &front){
			currentView->eyeX += 5;	  
		} else if(currentView == &topView){
			currentView->eyeZ += 5;
			currentView->eyeX -= 5;	  
		}
		updateCamera();
	}  else if(key == 'v') {
		if(currentView == &initial){
			currentView->eyeY -= 5;
		} else if(currentView == &lateral){
			currentView->eyeY -= 5;	  
		} else if(currentView == &front){
			currentView->eyeY -= 5;	  
		} else if(currentView == &topView){
			currentView->eyeX -= 5;
			currentView->eyeZ -= 5;
		}
		updateCamera();
	} else if(key == 'V') {
		if(currentView == &initial){
			currentView->eyeY += 5;
		} else if(currentView == &lateral){
			currentView->eyeY += 5;	  
		} else if(currentView == &front){
			currentView->eyeY += 5;	  
		} else if(currentView == &topView){
			currentView->eyeX += 5;
			currentView->eyeZ += 5;
		}
		updateCamera();
	} else {
		need_redisplay = false;
	}

	if (need_redisplay) { 
		glutPostRedisplay(); // Esto vuelve a invocar a "display"
	}
}
//---------------------------------------------------------------------------

void keySp(int key, int mX, int mY){
  bool need_redisplay = true;
  if(key == GLUT_KEY_UP) glRotatef(5.0, 1.0,0.0,0.0);   
  else if (key == GLUT_KEY_DOWN) glRotatef(-5.0, 1.0,0.0,0.0);  
  else if (key == GLUT_KEY_RIGHT) glTranslatef(5.0, 0.0,0.0); 
  else if(key == GLUT_KEY_LEFT) glTranslatef(-5.0, 0.0,0.0); 
  else need_redisplay = false;

  if (need_redisplay) glutPostRedisplay();
}
//---------------------------------------------------------------------------
