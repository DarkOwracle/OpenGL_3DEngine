#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <GL\gl.h>

//Structure d'une texture
typedef struct{
    GLuint m_Id;
}TTexture;

int LoadBmp(char *sname, char** image, int *sizeR, int *sizeC);
TTexture* CreateTexture(char *sname, int texsize);

#endif // !defined(TEXTURE_H)
