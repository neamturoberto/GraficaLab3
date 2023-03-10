#include "glos.h"
#include "math.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0;
static GLfloat y = 0;

static float pi = 3.14159265359;
int nr_puncte = 360;
float interval = (2 * pi) / nr_puncte;
int raza = 50;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);

}

void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(x, 0, 0.0);

    glBegin(GL_POLYGON);
    {
        glColor3f(1.0, 0.0, 0.0);
        for (int i = 0; i <= 360; i++)
        {
            float x = cos(i + interval) * raza;
            float y = sin(i + interval) * raza;
            glVertex2d(x, y);
        }
    }
    glEnd();

    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Un patrat");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
