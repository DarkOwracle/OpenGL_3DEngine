#include "Scene.h"

#include <stdio.h>
#include <stdlib.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

TScene* CreateScene(int maxprimitive)
{
    //Allocation de la scene
    TScene *pS = malloc(sizeof(TScene));
    if(pS==NULL)
    {
        printf("Erreur pour creer la scene (pS=NULL)\n");
        return NULL;
    }
    //Fixe le nombre de primitive et le nombre maximum de primitive
    pS->m_NumberPrimitive=0;
    pS->m_NumberMaxPrimitive=maxprimitive;
    //Allocation de la liste des primitives
    pS->m_pPrimitive = malloc(maxprimitive*sizeof(TGeometricPrimitive));
    if(pS->m_pPrimitive==NULL)
    {
        printf("Erreur pour creer la liste des primitives (m_pPrimitive=NULL)\n");
        return pS;
    }
    //Fixe le nombre de lampes
    pS->m_NumberLight = 0;
    //Allocation de la liste des lampes
    pS->m_pLight = malloc(8*sizeof(TLight));
    if(pS->m_pLight==NULL)
    {
        printf("Erreur pour creer la liste des lampes (m_pLight=NULL)\n");
        return pS;
    }
    return pS;
}

void DestroyScene(TScene *ps)
{
    if(ps==NULL)
    {
        printf("Erreur DestroyScene (pS=NULL)\n");
        return;
    }
    //Supprime toutes les formes et primitives
    int i;
    TGeometricPrimitive *pP;
    for(i=0; i<ps->m_NumberPrimitive; i++)
    {
        pP=ps->m_pPrimitive[i];
        free(pP->m_pShape);
        free(pP->m_pMaterial);
        free(pP);
    }
    //Supprime toutes les lampes
    for(i=0; i<ps->m_NumberLight; i++)
    {
        free(ps->m_pLight[i]);
    }
    //Supprime la liste des primitives
    free(ps->m_pPrimitive);
    //Supprime la liste des lampes
    free(ps->m_pLight);
    //Supprime la scene
    free(ps);
}

int AddPrimitiveScene(TScene *ps, TGeometricPrimitive *pp)
{
    if(ps==NULL)
    {
        printf("Erreur AddPrimitiveScene (pS=NULL)\n");
        return 0;
    }
    if(ps->m_NumberPrimitive==ps->m_NumberMaxPrimitive)
    {
        printf("Erreur AddPrimitiveScene (max primitive)\n");
        return 0;
    }
    if(pp==NULL)
    {
        printf("Erreur AddPrimitiveScene (pP=NULL)\n");
        return 0;
    }
    ps->m_pPrimitive[ps->m_NumberPrimitive++] = pp;
    return 1;
}

int AddLightScene(TScene *ps, TLight *pl)
{
    if(ps==NULL)
    {
        printf("Erreur AddLightScene (ps=NULL)\n");
        return 0;
    }
    if(ps->m_NumberLight==8)
    {
        printf("Erreur AddLightScene (max light)\n");
        return 0;
    }
    if(pl==NULL)
    {
        printf("Erreur AddLightScene (pl=NULL)\n");
        return 0;
    }
    ps->m_pLight[ps->m_NumberLight++] = pl;
    return 1;
}


int RemovePrimitiveScene(TScene *ps, int index)
{
    if(ps==NULL)
    {
        printf("Erreur RemovePrimitiveScene (pS=NULL)\n");
        return 0;
    }
    if(index>=ps->m_NumberPrimitive)
    {
        printf("Erreur RemovePrimitiveScene (index)\n");
        return 0;
    }
//Cherche si la forme et le materiau sont encore utilises
    TGeometricPrimitive *pP=ps->m_pPrimitive[index];
    int i,j=0,k=0;
    for(i=0; i<index; i++)
    {
        if(ps->m_pPrimitive[i]->m_pShape == pP->m_pShape)
            j++;
        if(ps->m_pPrimitive[i]->m_pMaterial == pP->m_pMaterial)
            k++;
    }
    //Mettre a jour la scene
    for(i=index+1; i<ps->m_NumberPrimitive; i++)
    {
        if(ps->m_pPrimitive[i]->m_pShape == pP->m_pShape)
            j++;
        if(ps->m_pPrimitive[i]->m_pMaterial == pP->m_pMaterial)
            k++;
        ps->m_pPrimitive[i-1] = ps->m_pPrimitive[i];
    }
    ps->m_NumberPrimitive--;
    //Supprime la forme si non reutilisee.
    if(j==0)
        free(pP->m_pShape);
    //Supprime le materiau si non reutilise.
    if(k==0)
        free(pP->m_pMaterial);
    //Supprime la primitive
    free(pP);

    return 1;
}

void DrawScene(TScene *ps)
{
    if(ps==NULL)
    {
        printf("Erreur DrawScene (pS=NULL)\n");
        return;
    }
    //Pas de lumiere ambiante
    GLfloat ambientColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    //Active les lampes
    glEnable(GL_LIGHTING);
    //Place les lampes
    int i;
    for(i=0; i<ps->m_NumberLight; i++)
        DrawLight(ps->m_pLight[i]);
    //Place les primitives
    for(i=0; i<ps->m_NumberPrimitive; i++)
        DrawGeometricPrimitive(ps->m_pPrimitive[i]);
    //Desactive les effets de lumiere
    glDisable(GL_LIGHTING);
}
