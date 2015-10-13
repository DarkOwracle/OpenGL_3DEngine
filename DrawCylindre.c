#include "DrawCylindre.h"

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
void DrawCylindre(void *pT)
{
//Recupere les donnees du cylindre
    TShapeCylindre *p = (TShapeCylindre*)pT;
    float radius= p->m_Radius;
    int sector= p->m_Sector;
    int longueurCylindre= p->m_Size;
//Dessin
    double dp = 2.0f*PI/(double)sector; //On a l'angle: (le prériphérique d'un cercle 2PI disisé par le nombre de morceau choisi)

    //positions du points
    double p1x,p1y,p1z;
    double p2x,p2y,p2z;
    double p3x,p3y,p3z;
    double p4x,p4y,p4z;

    int j;

    //Pour les faces rectangulaires
    for(j=0; j<sector; j++)
    {
        //----------CYLINDRE EN POSITION HORIZONTALE-----------
        //calcule des positions x y z        >>>>Faut-il dédier une fonction ? (Si oui en entrée: "dp,j,longueurCylindre" / en sortie "x1,y1,z1; x2,y2,z2; x3,y3,z3; x4,y4,z4")
        p1x = cos(dp *j); p1y = sin(dp*j); p1z = 0;
        p2x = cos(dp *j); p2y = sin(dp*j); p2z = longueurCylindre;
        p3x = cos(dp+ dp*j); p3y = sin(dp+ dp*j); p3z = longueurCylindre;
        p4x = cos(dp+ dp*j); p4y = sin(dp+ dp*j); p4z = 0;

        //Création du triangle du dessus
        glBegin(GL_TRIANGLES);
            glNormal3f(0.0,0.0,-1.0f);
            glVertex3f(0,0,0);
            glVertex3f(p1x*radius,p1y*radius,0);
            glVertex3f(p4x*radius,p4y*radius,0);
        glEnd();

        //Création d'un rectangle
        glBegin(GL_QUADS);
            glNormal3f(p1x,p1y,p1z);
            glVertex3f(p1x*radius,p1y*radius,0);
            glNormal3f(p2x,p2y,0.0);
            glVertex3f(p2x*radius,p2y*radius,p2z);
            glNormal3f(p3x,p3y,0.0);
            glVertex3f(p3x*radius,p3y*radius,p3z);
            glNormal3f(p4x,p4y,p4z);
            glVertex3f(p4x*radius,p4y*radius,0);
        glEnd();

        //Création du triangle du dessous
        glBegin(GL_TRIANGLES);
            glNormal3f(0.0,0.0,1.0f);
            glVertex3f(0,0,p2z);
            glVertex3f(p2x*radius,p2y*radius,p2z);
            glVertex3f(p3x*radius,p3y*radius,p3z);
        glEnd();

        //----------CYLINDRE EN POSITION VERTICALE-----------
        /*//calcule des positions x y z
        p1x = cos(dp *j); p1y = 0; p1z = sin(dp*j);
        p2x = cos(dp *j); p2y = longueurCylindre; p2z = sin(dp*j);
        p3x = cos(dp+ dp*j); p3y = longueurCylindre; p3z = sin(dp+ dp*j);
        p4x = cos(dp+ dp*j); p4y = 0; p4z = sin(dp+ dp*j);

        //Création du triangle du dessus
        glBegin(GL_TRIANGLES);
            glVertex3f(0,p2y*radius,0);
            glVertex3f(p2x*radius,p2y*radius,p2z*radius);
            glVertex3f(p3x*radius,p3y*radius,p3z*radius);
        glEnd();

        //Création d'un rectangle
        glBegin(GL_QUADS);
            glVertex3f(p1x*radius,p1y*radius,p1z*radius);
            glVertex3f(p2x*radius,p2y*radius,p2z*radius);
            glVertex3f(p3x*radius,p3y*radius,p3z*radius);
            glVertex3f(p4x*radius,p4y*radius,p4z*radius);
        glEnd();

        //Création du triangle du dessous
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(p1x*radius,p1y*radius,p1z*radius);
            glVertex3f(p4x*radius,p4y*radius,p4z*radius);
        glEnd();*/

    }
}
