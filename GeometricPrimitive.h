#if !defined(GEOMETRICPRIMITIVE_H)
#define GEOMETRICPRIMITIVE_H

#include "MatrixTransform.h"
#include "Material.h"

//Structure d'une primitive
typedef struct{
    void (*m_pF_Draw)(void*);       //La fonction pour dessiner la primitive
    void *m_pShape;                 //La forme de la primitive
    //float m_Color[3];               //La couleur de la primitive
    TMaterial *m_pMaterial;         //Le materiau de la primitive
    TMatrixTransform m_OtoW;        //La matrice de transformation de l'objet dans le monde
}TGeometricPrimitive;

TGeometricPrimitive* CreateGeometricPrimitive(void (*pF_Draw)(void*),
                                              void *pShape,
                                              TMaterial *pMaterial,
                                              TMatrixTransform OtoW);



void SetMatrixTransformGeometricPrimitive(TGeometricPrimitive* pprim, TMatrixTransform OtoW);

void DrawGeometricPrimitive(TGeometricPrimitive* pprim);

#endif // !defined(GEOMETRICPRIMITIVE_H)
