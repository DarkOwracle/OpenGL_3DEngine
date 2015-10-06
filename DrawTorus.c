#include "DrawTorus.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Definition.h"

void DrawTorus(void* pT)
{
    //Recupere les donnees du tore
    TShapeTorus *p = (TShapeTorus*)pT;
    float RadiusMax=p->m_RadiusMax;
    float RadiusMin=p->m_RadiusMin;
    int SectorRing=p->m_SectorRing;
    int SectorSide=p->m_SectorSide;

    float ringdelta=2.0f*PI/SectorRing;
    float sidedelta=2.0f*PI/SectorSide;
    float theta=0.0f;
    float ctheta=1.0f;
    float stheta=0.0f;
    int i,j;
    for(i=SectorRing;i>=0; i--)
    {
        float theta1=theta+ringdelta;
        float ctheta1=cos(theta1);
        float stheta1=sin(theta1);
        glBegin(GL_QUAD_STRIP);
        float phi=0.0f;
        for(j=SectorSide; j>=0; j--)
        {
            phi+=sidedelta;
            float cphi=cos(phi);
            float sphi=sin(phi);
            float dist=RadiusMax+RadiusMin*cphi;
            glNormal3f(ctheta1*cphi,sphi,-stheta1*cphi);
            glVertex3f(ctheta1*dist,RadiusMin*sphi,-stheta1*dist);
            glNormal3f(ctheta*cphi,sphi,-stheta*cphi);
            glVertex3f(ctheta*dist,RadiusMin*sphi,-stheta*dist);
        }
        glEnd();
        theta=theta1;
        ctheta=ctheta1;
        stheta=stheta1;
    }
}
