#if !defined(SCENE_H)
#define SCENE_H

#include "GeometricPrimitive.h"
#include "Light.h"

//Structure d'une scene
typedef struct{
    int m_NumberPrimitive;      //Le nombre actuel de primitives
    int m_NumberMaxPrimitive;   //Le nombre maximum de primitives
    TGeometricPrimitive **m_pPrimitive;  //Les primitives(table mémoire)
    int m_NumberLight;          //Le nombre actuel de lampes;
    TLight **m_pLight;          //Les lampes
}TScene;

TScene* CreateScene(int maxprimitive);

void DestroyScene(TScene *ps);

int AddPrimitiveScene(TScene *ps, TGeometricPrimitive* pp);
int AddLightScene(TScene *ps, TLight *pl);

int RemovePrimitiveScene(TScene *ps, int index);

void DrawScene(TScene *ps);

void DrawScenePicking(TScene *ps);

#endif // !defined(SCENE_H)
