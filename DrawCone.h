#if !defined(DRAWCONE_H)
#define DRAWCONE_H

typedef struct{
    float m_Radius;
    int m_Sector;
    float m_Height;
}TShapeCone;

void DrawCone(void* pT);

#endif // !defined(DRAWCONE_H)
