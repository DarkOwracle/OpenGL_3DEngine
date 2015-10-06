#include "MatrixTransform.h"

#include <math.h>
#include <stdio.h>

#include "Definition.h"

//Creation d'une matrice identitee
void MatrixTransformIdentity(float *m)
{
    m[0]=1.0f;  m[4]=0.0f;  m[8]=0.0f;  m[12]=0.0f;
    m[1]=0.0f;  m[5]=1.0f;  m[9]=0.0f;  m[13]=0.0f;
    m[2]=0.0f;  m[6]=0.0f;  m[10]=1.0f;  m[14]=0.0f;
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f;  m[15]=1.0f;
}

//Creation d'une matrice de translation
void MatrixTransformTranslate(float *m, float x, float y, float z)
{
    m[0]=1.0f;  m[4]=0.0f;  m[8]=0.0f;  m[12]=x;
    m[1]=0.0f;  m[5]=1.0f;  m[9]=0.0f;  m[13]=y;
    m[2]=0.0f;  m[6]=0.0f;  m[10]=1.0f; m[14]=z;
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f; m[15]=1.0f;
}

void MatrixTransformRotateX(float *m, float angle)
{
    float ra=angle/180.0*PI;
    float sin_t = sin(ra);
    float cos_t = cos(ra);
    m[0]=1.0f;  m[4]=0.0f;  m[8]=0.0f;  m[12]=0.0f;
    m[1]=0.0f;  m[5]=cos_t;  m[9]=-sin_t;  m[13]=0.0f;
    m[2]=0.0f;  m[6]=sin_t;  m[10]=cos_t;  m[14]=0.0f;
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f;  m[15]=1.0f;
}

void MatrixTransformRotateY(float *m, float angle)
{
    float ra=angle/180.0*PI;
    float sin_t = sin(ra);
    float cos_t = cos(ra);
    m[0]=cos_t;  m[4]=0.0f;  m[8]=sin_t;  m[12]=0.0f;
    m[1]=0.0f;   m[5]=1.0f;  m[9]=0.0f;   m[13]=0.0f;
    m[2]=-sin_t; m[6]=0.0f;  m[10]=cos_t; m[14]=0.0f;
    m[3]=0.0f;   m[7]=0.0f;  m[11]=0.0f;  m[15]=1.0f;
}

void MatrixTransformRotateZ(float *m, float angle)
{
    float ra=angle/180.0*PI;
    float sin_t = sin(ra);
    float cos_t = cos(ra);
    m[0]=cos_t;  m[4]=-sin_t;  m[8]=0.0;      m[12]=0.0f;
    m[1]=sin_t;  m[5]=cos_t;   m[9]=0.0f;     m[13]=0.0f;
    m[2]=0.0f;   m[6]=0.0f;    m[10]=1.0f;    m[14]=0.0f;
    m[3]=0.0f;   m[7]=0.0f;    m[11]=0.0f;    m[15]=1.0f;
}

void MatrixTransformScale(float *m, float sx, float sy, float sz)
{
    m[0]=1.0f/sx;  m[4]=0.0f;      m[8]=0.0;       m[12]=0.0f;
    m[1]=0.0f;     m[5]=1.0f/sy;   m[9]=0.0f;      m[13]=0.0f;
    m[2]=0.0f;     m[6]=0.0f;      m[10]=1.0f/sz;  m[14]=0.0f;
    m[3]=0.0f;     m[7]=0.0f;      m[11]=0.0f;     m[15]=1.0f;
}

void MatrixTransformMult(float *m, float *m1, float *m2)
{
    m[0] = m1[0]*m2[0]+m1[4]*m2[1]+m1[8]*m2[2]+m1[12]*m2[3];
    m[1] = m1[1]*m2[0]+m1[5]*m2[1]+m1[9]*m2[2]+m1[13]*m2[3];
    m[2] = m1[2]*m2[0]+m1[6]*m2[1]+m1[10]*m2[2]+m1[14]*m2[3];
    m[3] = m1[3]*m2[0]+m1[7]*m2[1]+m1[11]*m2[2]+m1[15]*m2[3];

    m[4] = m1[0]*m2[4]+m1[4]*m2[5]+m1[8]*m2[6]+m1[12]*m2[7];
    m[5] = m1[1]*m2[4]+m1[5]*m2[5]+m1[9]*m2[6]+m1[13]*m2[7];
    m[6] = m1[2]*m2[4]+m1[6]*m2[5]+m1[10]*m2[6]+m1[14]*m2[7];
    m[7] = m1[3]*m2[4]+m1[7]*m2[5]+m1[11]*m2[6]+m1[15]*m2[7];

    m[8] = m1[0]*m2[8]+m1[4]*m2[9]+m1[8]*m2[10]+m1[12]*m2[11];
    m[9] = m1[1]*m2[8]+m1[5]*m2[9]+m1[9]*m2[10]+m1[13]*m2[11];
    m[10] = m1[2]*m2[8]+m1[6]*m2[9]+m1[10]*m2[10]+m1[14]*m2[11];
    m[11] = m1[3]*m2[8]+m1[7]*m2[9]+m1[11]*m2[10]+m1[15]*m2[11];

    m[12] = m1[0]*m2[12]+m1[4]*m2[13]+m1[8]*m2[14]+m1[12]*m2[15];
    m[13] = m1[1]*m2[12]+m1[5]*m2[13]+m1[9]*m2[14]+m1[13]*m2[15];
    m[14] = m1[2]*m2[12]+m1[6]*m2[13]+m1[10]*m2[14]+m1[14]*m2[15];
    m[15] = m1[3]*m2[12]+m1[7]*m2[13]+m1[11]*m2[14]+m1[15]*m2[15];
}

void MatrixTransformCopy(float *mdest, float *msource)
{
    int i;
    for(i=0; i<16; i++)
        mdest[i] = msource[i];
}

void MatrixTransform_TransformPoint(float *m, float *p)
{
    float pm[4];
    pm[0] = m[0]*p[0]+m[4]*p[1]+m[8]*p[2]+m[12];
    pm[1] = m[1]*p[0]+m[5]*p[1]+m[9]*p[2]+m[13];
    pm[2] = m[2]*p[0]+m[6]*p[1]+m[10]*p[2]+m[14];
    pm[3] = m[3]*p[0]+m[7]*p[1]+m[11]*p[2]+m[15];
    if(pm[3]!=1.)
    {
        pm[0]/=pm[3];
        pm[1]/=pm[3];
        pm[2]/=pm[3];
    }
    p[0]=pm[0];
    p[1]=pm[1];
    p[2]=pm[2];
}

void PrintMatrixTransform(float *m)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            printf("%.2f  ", m[i*4+j]);
        printf("\n");
    }
}
