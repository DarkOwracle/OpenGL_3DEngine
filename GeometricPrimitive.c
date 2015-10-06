#include "GeometricPrimitive.h"

#include <stdio.h>
#include <stdlib.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

TGeometricPrimitive* CreateGeometricPrimitive(void (*pF_Draw)(void*),
                                              void *pShape,
                                              TMaterial *pMaterial,
                                              TMatrixTransform OtoW)
{
    //Verification des parametres
    if(pShape==NULL)
        return NULL;

    TGeometricPrimitive *pprim = malloc(sizeof(TGeometricPrimitive));
    if(pprim==NULL)
    {
        printf("Erreur pour creer une primitive (pprim=NULL)\n");
        return NULL;
    }
    pprim->m_pF_Draw = pF_Draw;
    pprim->m_pShape = pShape;
    pprim->m_pMaterial = pMaterial;
    MatrixTransformCopy(pprim->m_OtoW,OtoW);
    return pprim;
}

void SetMatrixTransformGeometricPrimitive(TGeometricPrimitive* pprim, TMatrixTransform OtoW)
{
    MatrixTransformCopy(pprim->m_OtoW,OtoW);
}

void DrawGeometricPrimitive(TGeometricPrimitive* pprim)
{
//Sauve l'etat d'opengl
    glPushMatrix();
//Choix du mode de dessin (ici en fil de fer)
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//Choix du mode de dessin (ici en plein)
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//Position dans la scene
    glMultMatrixf(pprim->m_OtoW);
//Choix de la couleur (sans lumiere !)
    //glColor3fv(pprim->m_Color);
//Fixe le materiau (avec lumiere !)
    DrawMaterial(pprim->m_pMaterial);
    //Dessine la forme
    if(pprim->m_pShape!=NULL)
        pprim->m_pF_Draw(pprim->m_pShape);
//Recharge l'etat d'opengl
    glPopMatrix();
}
