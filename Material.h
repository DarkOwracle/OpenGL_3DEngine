#if !defined(MATERIAL_H)
#define MATERIAL_H

//Structure d'un materiau
typedef struct{
    float m_Kd[4];  //Diffusion
    float m_Ke[4];  //Emissivite

}TMaterial;

TMaterial* CreateMaterial(float Kd[], float Ke[]);
void DrawMaterial(TMaterial *pmat);

#endif // !defined(MATERIAL_H)
