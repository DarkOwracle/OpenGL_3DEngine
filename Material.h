#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "Texture.h"

//Structure d'un materiau
typedef struct{
    float m_Kd[4];  //Diffusion
    float m_Ke[4];  //Emissivite
    TTexture *m_Texture;
}TMaterial;

TMaterial* CreateMaterial(float Kd[], float Ke[], char* texturename);
void DrawMaterial(TMaterial *pmat);

#endif // !defined(MATERIAL_H)
