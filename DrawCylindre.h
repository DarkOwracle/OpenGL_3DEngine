#if !defined(DRAWCYLINDRE_H)
#define CYLINDRE_H

typedef struct{
    float m_Radius;
    int m_Sector;
    int m_Size;
}TShapeCylindre;

void DrawCylindre(void* pT);

#endif // !defined(DRAWCYLINDRE_H)
