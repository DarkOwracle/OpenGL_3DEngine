#include "Material.h"

#include <GL\gl.h>
#include <stdlib.h>

TMaterial* CreateMaterial(float Kd[], float Ke[])
{
    TMaterial *pmat = malloc(sizeof(TMaterial));
    int i;
    for(i=0; i<4; i++)
    {
        if(Kd!=NULL)
            pmat->m_Kd[i] = Kd[i];
        else
            pmat->m_Kd[i] = 0.0f;
        if(Ke!=NULL)
            pmat->m_Ke[i] = Ke[i];
        else
            pmat->m_Ke[i] = 0.0f;
    }
    return pmat;
}


void DrawMaterial(TMaterial *pmat)
{
    //glDisable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pmat->m_Kd);
    glMaterialfv(GL_FRONT, GL_EMISSION, pmat->m_Ke);
}
