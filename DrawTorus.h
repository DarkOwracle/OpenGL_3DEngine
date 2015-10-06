#if !defined(DRAWTORUS_H)
#define DRAWTORUS_H

typedef struct{
    float m_RadiusMin;
    float m_RadiusMax;
    int m_SectorRing;
    int m_SectorSide;
}TShapeTorus;

void DrawTorus(void* pT);

#endif // !defined(DRAWTORUS_H)
