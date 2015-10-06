#if !defined(LIGHT_H)
#define LIGHT_H

#include <GL\gl.h>

//Structure d'une lampe
typedef struct{
    float m_Ambient[4];
    float m_Diffuse[4];
    float m_Specular[4];
    float m_Position[4];
    GLenum m_Id;
}TLight;

TLight* CreateLight(float ambient[], float diffuse[], float specular[],
                    float position[],
                    GLenum id);
void DrawLight(TLight *plight);

#endif // !defined(LIGHT_H)
