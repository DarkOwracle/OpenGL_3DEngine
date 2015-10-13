#include "DrawCone.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Definition.h"

void DrawCone(void* pT)
{
     glEnable(GL_NORMALIZE);
   //Recupere les donnees de la sphere
    TShapeCone *p = (TShapeCone*)pT;
    float radius=p->m_Radius;
    int sector=p->m_Sector;
    float height=p->m_Height;

    double dp = 2.0f*PI/(double)sector;
    float alpha = atan(radius/height);
    int i;
    for(i=0; i<sector; i++)
    {
        glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0); 
        glVertex3f(0,0,0);
        glVertex3f((radius*cos(i*dp)),0,(radius*sin(i*dp)));
        glVertex3f((radius*cos((i+1)*dp)),0,(radius*sin((i+1)*dp)));
        
        glNormal3f(cos(i*dp)*cos(alpha),sin(alpha),cos(alpha)*sin(i*dp));
        glVertex3f((radius*cos(i*dp)),0,(radius*sin(i*dp)));
        glNormal3f(cos((i+1)*dp)*cos(alpha),sin(alpha),cos(alpha)*sin((i+1)*dp));
        glVertex3f((radius*cos((i+1)*dp)),0,(radius*sin((i+1)*dp)));
        glNormal3f(0,1,0);
        glVertex3f(0,height,0);
        glEnd();
    }


}
