#include "Light.h"

#include <stdlib.h>

TLight* CreateLight(float ambient[], float diffuse[], float specular[],
                    float position[],
                    GLenum id)
{
    TLight *pl = malloc(sizeof(TLight));
    int i;
    for(i=0; i<4; i++)
    {
        if(ambient!=NULL)
            pl->m_Ambient[i] = ambient[i];
        else
            pl->m_Ambient[i] = 0.0f;
        if(diffuse!=NULL)
            pl->m_Diffuse[i] = diffuse[i];
        else
            pl->m_Diffuse[i] = 0.0f;
        if(specular!=NULL)
            pl->m_Specular[i] = specular[i];
        else
            pl->m_Specular[i] = 0.0f;
        if(position!=NULL)
            pl->m_Position[i] = position[i];
        else
            pl->m_Position[i] = 0.0f;
    }
    pl->m_Id = id;
    return pl;
}

void DrawLight(TLight *plight)
{
    glEnable(plight->m_Id);
    glLightfv(plight->m_Id, GL_POSITION, plight->m_Position);
    glLightfv(plight->m_Id, GL_AMBIENT, plight->m_Ambient);

    glLightfv(plight->m_Id, GL_DIFFUSE, plight->m_Diffuse);
    glLightfv(plight->m_Id, GL_SPECULAR, plight->m_Specular);

    //Pas d'attenuation, pas d'effet de direction
	glLightf( plight->m_Id, GL_CONSTANT_ATTENUATION,  1.0f );
	glLightf( plight->m_Id, GL_LINEAR_ATTENUATION,  0.0f );
	glLightf( plight->m_Id, GL_QUADRATIC_ATTENUATION, 0.0f );
}
