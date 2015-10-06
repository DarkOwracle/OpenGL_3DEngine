#if !defined(DRAWCONE_H)
#define DRAWCONE_H

typedef struct{
    float m_Radius;
    int m_Sector;
    int m_Size;
}TShapeCone;

void DrawCone(void* pT);

#endif // !defined(DRAWCONE_H)
