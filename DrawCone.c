#include "DrawCone.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Definition.h"
#include "MathLib.h"


//La fonction dessine un cylindre
//Le cylindre est un assemblage de : triangle + rectangle + triangle
void DrawCone(void *pT)
{
//Recupere les donnees du cylindre
    TShapeCone *p = (TShapeCone*)pT;
    float radius= p->m_Radius;
    int sector= p->m_Sector;
    int height= p->m_Size;
//Dessin
    double dp = 2.0f*PI/(double)sector; //On a l'angle: (le prériphérique d'un cercle 2PI disisé par le nombre de morceau choisi)

    //positions du points
    double p1x,p1y,p1z;
    double p2x,p2y,p2z;
    double p3x,p3y,p3z;

    int j;

    //Pour les faces rectangulaires
    for(j=0; j<sector; j++)
    {
        //calcule des positions x y z
        p1x = cos(dp *j); p1y = atan(1/height); p1z = sin(dp*j);
        p2x = 0; p2y = 1; p2z = 0;
        p3x = cos(dp+ dp*j); p3y = 0; p3z = sin(dp+ dp*j);
        

        //Création d'un rectangle
        glBegin(GL_TRIANGLES);
            glNormal3f(p1x,p1y,p1z);
            glVertex3f(p1x*radius,0.0,p1z*radius);
            glNormal3f(p2x,p2y,p2z);
            glVertex3f(0.0,height,0.0);
            glNormal3f(p3x,p3y,p3z);
            glVertex3f(p3x*radius,0.0,p3z*radius);
        glEnd();

        //Création du triangle du dessous
        glBegin(GL_TRIANGLES);
            glNormal3f(0.0,-1.0f,0.0);
            glVertex3f(0,0,0);
            //glNormal3f(0.0,-1.0f,0.0);
            glVertex3f(p1x*radius,0.0,p1z*radius);
            //glNormal3f(0.0,-1.0f,0.0);
            glVertex3f(p3x*radius,0.0,p3z*radius);
        glEnd();
    }
}
