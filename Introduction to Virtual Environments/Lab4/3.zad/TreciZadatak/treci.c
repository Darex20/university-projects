#include <io.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include "GL/glut.h"

#define PI 3.14159

/* "referenciranjem" na pojedini od sljedecih naziva mogu se koristiti
 * svojstva materijala zute (Sunce), plave (Zemlja) i bijele (Mjesec)
 * boje
 */
#define YELLOWMAT 1
#define BLUEMAT 2
#define WHITEMAT 3

 /* varijable koje predstavljaju (kako slijedi) pomake: Zemlje oko
  * svoje osi i oko Sunca, te Mjeseca oko svoje osi i oko Zemlje
  */
static double earthDay = 0, earthYear = 0, moonDay = 0, moonYear = 0;

void init(void)
{
	// definiranje komponenti lokalnog osvjetljenja pojedinih materijala 
	GLfloat yellowAmbientComp[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat yellowDiffuseComp[] = { 0.7, 0.7, 0.0, 1.0 };
	GLfloat yellowSpecularComp[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat blueAmbientComp[] = { 0.2, 0.2, 0.6, 1.0 };
	GLfloat blueDiffuseComp[] = { 0.1, 0.1, 0.7, 1.0 };
	GLfloat blueSpecularComp[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat whiteAmbientComp[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat whiteDiffuseComp[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat whiteSpecularComp[] = { 1.0, 1.0, 1.0, 1.0 };

	// definiranje karakteristika izvora svjetlosti 
	GLfloat lightSourcePosition[] = { 1.0, 0.5, 2.0, 0.0 };
	GLfloat lightSourceDirection[] = { 0.0, 0.0, 0.0, 0.0 };

	/* pridjeljivanje svojstava materijalima (koristenjem imena YELLOWMAT
	 * moze se pojedinim objektima pridjeliti definirani materijal)
	 */
	glNewList(YELLOWMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, yellowAmbientComp);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuseComp);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellowSpecularComp);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();

	glNewList(BLUEMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blueAmbientComp);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blueDiffuseComp);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blueSpecularComp);
	glMaterialf(GL_FRONT, GL_SHININESS, 90.0);
	glEndList();

	glNewList(WHITEMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbientComp);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteDiffuseComp);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecularComp);
	glMaterialf(GL_FRONT, GL_SHININESS, 80.0);
	glEndList();

	// pridjeljivanje karakteristika izvoru svjetlosti 
	glLightfv(GL_LIGHT0, GL_POSITION, lightSourcePosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightSourceDirection);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// inicijalizacija projekcijskog volumena
	gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



void drawSphere(float R, float step)
{
	/* potrebno je nadopuniti funkciju drawSphere tako da iscrtava
	 * kuglu (naputak: koristiti kod iz drugog zadatka ove laboratorijske
	 * vjezbe)
	 */

	 // Setting up check, theta, fi and coordinates
	int i = 0;
	float theta, fi;
	float coordinates1[3] = { 0.0, 0.0, 0.0 };
	float coordinates2[3] = { 0.0, 0.0, 0.0 };
	float coordinates3[3] = { 0.0, 0.0, 0.0 };
	float coordinates4[3] = { 0.0, 0.0, 0.0 };

	// reusing drugi.c algortihm to draw spheres (Sun, Earth, Moon)
	for (fi = 0; fi < PI; fi = fi + step)
	{
		for (theta = 0; theta <= 2 * PI; theta = theta + 0.1, i = (i + 1) % 2)
		{
			if (i == 0)
			{
				coordinates1[0] = R * cos(theta) * sin(fi);
				coordinates1[1] = R * sin(theta) * sin(fi);
				coordinates1[2] = R * cos(fi);

				coordinates2[0] = R * cos(theta) * sin(fi + step);
				coordinates2[1] = R * sin(theta) * sin(fi + step);
				coordinates2[2] = R * cos(fi + step);

			}
			else if (i == 1)
			{
				coordinates3[0] = R * cos(theta) * sin(fi);
				coordinates3[1] = R * sin(theta) * sin(fi);
				coordinates3[2] = R * cos(fi);

				coordinates4[0] = R * cos(theta) * sin(fi + step);
				coordinates4[1] = R * sin(theta) * sin(fi + step);
				coordinates4[2] = R * cos(fi + step);
			}

			glBegin(GL_QUAD_STRIP);

			glVertex3fv(coordinates1);
			glNormal3fv(coordinates1);

			glVertex3fv(coordinates2);
			glNormal3fv(coordinates2);

			glVertex3fv(coordinates3);
			glNormal3fv(coordinates3);

			glVertex3fv(coordinates4);
			glNormal3fv(coordinates4);

			glEnd();

		}
	}
}

void drawSun(void)
{
	// set the color to yellow
	glCallList(YELLOWMAT);

	// draw Sun and set its radius
	drawSphere(7.0, 0.01);
	glPopMatrix();
}

void drawEarth(void)
{
	glPushMatrix();
	// set the color to blue
	glCallList(BLUEMAT);

	// set the rotation around Sun
	glRotated(earthYear, 0.0, 1.0, 0.0);

	// Earths distance from Sun
	glTranslated(0.0, 0.0, 15.0);
	glPushMatrix();

	// inverse rotation around axis
	glRotated(-earthDay, 0.0, 1.0, 0.0);

	// draw Earth and set its radius
	drawSphere(0.60, 0.1);
	glPopMatrix();
}

void drawMoon(void)
{
	glPushMatrix();
	// set the color to white
	glCallList(WHITEMAT);

	// set the rotation around Earth
	glRotated(moonYear, 0.0, 1.0, 0.0);

	// Moons distance from Earth
	glTranslated(0.0, 0.0, 1.0);
	glPushMatrix();

	// inverse rotation around axis
	glRotated(-moonDay, 0.0, 1.0, 0.0);

	// draw Moon and set its radius
	drawSphere(0.15, 0.1);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	/* Potrebno je dodati kod za iscrtavanje (dijela) Suncevog sustava
	 * prema trecem zadatku uputa za ove laboratorijske vjezbe. U uputama
	 * je objasnjena "modelview" matrica (transformacija) pomocu koje bi,
	 * kombinirajuci razlicite operacije, trebalo implementirati rotacije
	 * potrebne za izvodjenje simulacije. Obavezno pogledati napomenu za
	 * funkciju mouse()!
	 *
	 * Koristite sljedece parametre (zadane u VRML laboratorijskoj vjezbi):
	 * radijus Sunca = 6.96, Zemlje = 0.63, Mjeseca = 0.17
	 * preporuceni step: za Sunce 0.01, za Zemlju i Mjesec 0.1
	 * radijus kruzne putanje Zemlje oko Sunca = 14.96
	 * radijus kruzne putanje Mjeseca oko Zemlje = 1.0
	 *
	 * Neposredno prije poziva naredbe za iscrtavanje pojedinih tijela
	 * navedite naredbu glCallList () gdje su paramteri te funkcije
	 * YELLOWMAT, BLUEMAT ili WHITEMAT, kako bi npr. Suncu sa
	 * glCallList (YELLOWMAT) pridodali zutu boju i svojstva doticnog
	 * materijala
	 */

	 // draw Sun
	drawSun();

	// draw Earth
	drawEarth();

	// draw Moon
	drawMoon();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// swap buffers after you are done
	glutSwapBuffers();
}

// funkcija koja vraca trenutno vrijeme u milisekundama
long getCurrentTimeMs()
{
	struct _timeb timebuffer;

	_ftime64_s(&timebuffer);

	return(1000 * timebuffer.time + timebuffer.millitm);
}

/* funkcija koja iz relativnog vremena (razlike izmedju trenutnog
 * sistemskog vremena i sistemskog vremena na pocetku simulacije)
 * izracunava kuteve rotacije Zemlje i Mjeseca oko vlastitih osi,
 * te oko Sunca/Zemlje u svakom trenutku
 */
void spinDisplay(void)
{
	double seconds;

	/* varijabla koja biljezi vrijeme na samom pocetku izvodjenja
	 * simulacije
	 */
	static long startTime = -1;

	// varijabla koja biljezi trenutno vrijeme
	long currentTime;

	if (startTime == -1)
		startTime = getCurrentTimeMs();

	currentTime = getCurrentTimeMs();

	// racunanje relativnog vremena proteklog od pocetka simulacije	
	seconds = (double)(currentTime - startTime) / (double)1000;

	/* Funkcija koja iz relativnog vremena (razlike izmedju trenutnog
	 * sistemskog vremena i sistemskog vremena na pocetku simulacije)
	 * izracunava kuteve rotacije (brzine pomaka) Zemlje i Mjeseca oko
	 * vlastitih osi, te oko Sunca/Zemlje u svakom trenutku. Trajanje
	 * jednog "mjesecevog dana" jednako je 29.5 zemaljskih dana, a jedne
	 * "mjeseceve godine" 27.3 zemaljskih dana. Primjetite da se kutevi
	 * rotacije mogu izracunati i bez upotrebe varijable seconds ali ce
	 * tada animacija ovisiti o brzini kojom racunalo izvodi program.
	 * Znaci u tom slucaju ne dobivamo ispravno vrijeme obilaska planeta
	 * oko Sunca/svoje osi.
	 */

	// Earth day = 0.164 seconds, 360 / 0.164 = 2195.12
	earthDay = seconds * 2195.12;

	// Earth year = 1 minute, 360 / 60 = 6
	earthYear = seconds * 6;

	// Moon day = 4.828 seconds, 360 / 4.828 = 74.57
	moonDay = seconds * 74.57;

	// Moon year = 4.61 seconds, 360 / 4.61 = 78.09
	moonYear = seconds * 78.09;

	// "oznaka" koja kaze da je prozor potrebno ponovno iscrtati
	glutPostRedisplay();
}

/* Callback funkcija koja se poziva kad se pritisne ili otpusti tipka
 * misa. U ovom se konkretno slucaju pritiskom na lijevu tipku misa
 * pokrece izvodjenje simulacije, a na desnu tipku zaustavlja njeno
 * izvodjenje. Vazno je primjetiti kako se
 * funkcija spinDisplay() definira kao funkcija koja ce se stalno
 * pozivati (ukoliko nema drugih dogadjaja, npr. mijenjanja velicine
 * prozora), i to u svakom "frame-u" (cime cemo postici da se za svaki
 * "frame" mogu izracunati novi kutevi rotacije Zemlje i Mjeseca)
 */
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// koristenje dvostrukog spremnika
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// registracija callback funkcije mouse 
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

