#include "DrawCube.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Definition.h"

void DrawCube(void* pT)
{
    //Recupere les donnees du cube
    TShapeCube *p = (TShapeCube*)pT;
    float size=p->m_Size;
    glBegin(GL_QUADS);
    //Face1
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,size,0.0);
    glVertex3f(size,size,0.0);
    glVertex3f(size,0.0,0.0);

    //Face 2
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(size,0.0,0.0);
    glVertex3f(size,0.0,size);
    glVertex3f(0.0,0.0,size);

    //Face 3
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(0.0,size,0.0);
    glVertex3f(0.0,size,size);
    glVertex3f(0.0,0.0,size);
    glVertex3f(0.0,0.0,0.0);

    //Face 4
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,size);
    glVertex3f(0.0,size,size);
    glVertex3f(size,size,size);
    glVertex3f(size,0.0,size);

    //Face 5
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(0.0,size,0.0);
    glVertex3f(size,size,0.0);
    glVertex3f(size,size,size);
    glVertex3f(0.0,size,size);

    //Face 6
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(size,size,0.0);
    glVertex3f(size,size,size);
    glVertex3f(size,0.0,size);
    glVertex3f(size,0.0,0.0);
    glEnd();
}
