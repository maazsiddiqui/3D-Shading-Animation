// Maaz Siddiqui
// Project 3

#include <math.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

// GLOBALS
GLfloat pos[] = { -2,4,5,1 }, amb[] = { 0.3,0.3,0.3,1.0 };
GLfloat front_amb_diff[] = { 0.7,0.5,0.1,1.0 };
GLfloat back_amb_diff[] = { 0.4,0.7,0.1,1.0 };
GLfloat spe[] = { 0.25,0.25,0.25,1.0 };
GLfloat theta = 0, dt = 0.3, axes[3][3] = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 } };
int axis = 0;
GLfloat y = -0.7;
bool fly = false;

void flyRocket() {
	dt = 0.0;
	y += 0.001 * 25;
}

void reset() {
	fly = false;
	dt = 0.3;
	y = -0.7;
}

// keyboard input

void SpecialInput(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		fly = true;
		break;
	case GLUT_KEY_DOWN:
		reset();
		break;
	case GLUT_KEY_LEFT:
		dt = 0.0;
		break;
	case GLUT_KEY_RIGHT:
		dt = 0.3;
		break;
	}

	glutPostRedisplay();
}

void rocket() {

	glColor3f(1, 0, 0);

	glPushMatrix();

	glTranslatef(0.0, 0.68, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutSolidCone(0.15, 0.4, 50, 30);

	glColor3f(0, 1, 0);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.02, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj *quadobj;
	quadobj = gluNewQuadric();
	gluCylinder(quadobj, 0.15, 0.15, 0.7, 50, 30);
	
	glColor3f(1.0, 0.5, 0.0);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -0.02, 0.0);
	glScalef(1.0, 0.1, 1.0);
	glutSolidSphere(0.15, 50, 30);
	
	glColor3f(1, 0, 0);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.0, 0.08, 0.0);
	glScalef(0.9, 0.4, 0.06);
	glutSolidCube(0.5);

	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 5, 0);
	glTranslatef(-0.0, 0.08, -0.0);
	glScalef(0.9, 0.4, 0.06);
	glutSolidCube(0.5);

	glPopMatrix();

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotated(theta, 0, 1, 0);

	glTranslatef(0, y, 0);

	rocket();

	glutSwapBuffers();
}


void idle(void) {
	if (theta >= 360) axis = (axis + 1) % 3;
	theta = (theta < 360) ? theta + dt : dt;
	if (fly) flyRocket();
	glutPostRedisplay();
}


void main(int argc, char** argv) {

	cout << "Fly Rocket: Up Arrow" << endl;
	cout << "Reset: Down Arrow" << endl;
	cout << "Stop Rotation: Left Arrow" << endl;
	cout << "Resume Rotation: Right Arrow" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Rocket");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(SpecialInput);
	glutMainLoop();
}

