#include "DrawBite.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "Definition.h"
#include "MathLib.h"

void DrawBite(void *pT)
{
     TShapeBite *p = (TShapeBite*)pT;
     float radius=p->m_Radius;
     int sector=p->m_Sector;
     float height=p->m_Height;
     
     double dt = PI/(double)sector;
     double dp = 2.0f*PI/(double)sector;
     double p1x,p1y,p1z;
     double p2x,p2y,p2z;
     double p3x,p3y,p3z;
     double p4x,p4y,p4z;
     
     //Première sphère
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
            glVertex3f(p1x*radius-radius,p1y*radius,p1z*radius);
            glNormal3f(p2x,p2y,p2z);
            glVertex3f(p2x*radius-radius,p2y*radius,p2z*radius);
            glNormal3f(p3x,p3y,p3z);
            glVertex3f(p3x*radius-radius,p3y*radius,p3z*radius);
            glNormal3f(p4x,p4y,p4z);
            glVertex3f(p4x*radius-radius,p4y*radius,p4z*radius);
            glEnd();
        }
        
         //Deuxième Sphère
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
            glVertex3f(p1x*radius+radius,p1y*radius,p1z*radius);
            glNormal3f(p2x,p2y,p2z);
            glVertex3f(p2x*radius+radius,p2y*radius,p2z*radius);
            glNormal3f(p3x,p3y,p3z);
            glVertex3f(p3x*radius+radius,p3y*radius,p3z*radius);
            glNormal3f(p4x,p4y,p4z);
            glVertex3f(p4x*radius+radius,p4y*radius,p4z*radius);
            glEnd();
        }
    
        //Sphere du haut
        dp=dp/2;
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
            glVertex3f(p1x*radius,(p1y*radius)+ height,p1z*radius);
            glNormal3f(p2x,p2y,p2z);
            glVertex3f(p2x*radius,(p2y*radius)+ height,p2z*radius);
            glNormal3f(p3x,p3y,p3z);
            glVertex3f(p3x*radius,(p3y*radius)+ height,p3z*radius);
            glNormal3f(p4x,p4y,p4z);
            glVertex3f(p4x*radius,(p4y*radius)+ height,p4z*radius);
            glEnd();
        }
    
        //Cyclindre
        float radius_old = radius;
        radius = radius*0.7;
        dp = dp*2;
     for(j=0; j<2*sector; j++)
    {
        p1x = cos(dp *j); p1y = 0; p1z = sin(dp*j);
        p2x = cos(dp *j); p2y = height; p2z = sin(dp*j);
        p3x = cos(dp+ dp*j); p3y = height; p3z = sin(dp+ dp*j);
        p4x = cos(dp+ dp*j); p4y = 0; p4z = sin(dp+ dp*j);

        //CrÃ©ation du triangle du dessus
         glBegin(GL_TRIANGLES);
            glNormal3f(0.0,1.0f,0);
            glVertex3f(0,p2y,0);
            glVertex3f(p2x*radius,p2y,p2z*radius);
            glVertex3f(p3x*radius,p3y,p3z*radius);
            glEnd();

        //CrÃ©ation d'un rectangle
        glBegin(GL_QUADS);
            glNormal3f(p1x,p1y,p1z);
            glVertex3f(p1x*radius,p1y,p1z*radius);
            glNormal3f(p2x,p2y,0.0);
            glVertex3f(p2x*radius,p2y,p2z*radius);
            glNormal3f(p3x,p3y,0.0);
            glVertex3f(p3x*radius,p3y,p3z*radius);
            glNormal3f(p4x,p4y,p4z);
            glVertex3f(p4x*radius,p4y,p4z*radius);
        glEnd();

        //CrÃ©ation du triangle du dessous
        glBegin(GL_TRIANGLES);
            glNormal3f(0.0,-1.0f,0.0f);
            glVertex3f(0,0,0);
            glVertex3f(p1x*radius,p1y,p1z*radius);
            glVertex3f(p4x*radius,p4y,p4z*radius);
        glEnd();
}


}
     

