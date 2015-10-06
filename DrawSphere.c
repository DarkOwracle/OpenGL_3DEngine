#include "DrawSphere.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Definition.h"
#include "MathLib.h"

//La fonction dessine une sphere
//La sphere est un assemblage de carre
void DrawSphere(void *pT)
{
//Recupere les donnees de la sphere
    TShapeSphere *p = (TShapeSphere*)pT;
    float radius=p->m_Radius;
    int sector=p->m_Sector;

//Dessin
    double dt = PI/(double)sector;
    double dp = 2.0f*PI/(double)sector;
    double p1x,p1y,p1z;
    double p2x,p2y,p2z;
    double p3x,p3y,p3z;
    double p4x,p4y,p4z;


    //Pour tous les carres
    int i,j;
    for(i=0; i<sector; i++)
        for(j=0; j<sector; j++)
        {
            //Calcul la position des coins du carre
            PointOnUnitSphere((double)i*dt,(double)j*dp,&p1x,&p1y,&p1z);
            PointOnUnitSphere((double)(i+1)*dt,(double)j*dp,&p2x,&p2y,&p2z);
            PointOnUnitSphere((double)(i+1)*dt,(double)(j+1)*dp,&p3x,&p3y,&p3z);
            PointOnUnitSphere((double)(i)*dt,(double)(j+1)*dp,&p4x,&p4y,&p4z);
            //Dessin du carre en opengl
            glBegin(GL_POLYGON);
            glNormal3f(p1x,p1y,p1z);
            glVertex3f(p1x*radius,p1y*radius,p1z*radius);
            glNormal3f(p2x,p2y,p2z);
            glVertex3f(p2x*radius,p2y*radius,p2z*radius);
            glNormal3f(p3x,p3y,p3z);
            glVertex3f(p3x*radius,p3y*radius,p3z*radius);
            glNormal3f(p4x,p4y,p4z);
            glVertex3f(p4x*radius,p4y*radius,p4z*radius);
            glEnd();
        }
}
