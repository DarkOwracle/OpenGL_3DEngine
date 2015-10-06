#include <stdio.h>
#include <stdlib.h>

//Les librairies pour openGL + glut
#include <glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

//Les fonctions avancées
#include "MatrixTransform.h"
#include "GeometricPrimitive.h"
#include "Scene.h"
#include "MathLib.h"
//Les fonctions Draw
#include "DrawSphere.h"
#include "DrawCube.h"
#include "DrawCone.h"
#include "DrawCylindre.h"
#include "DrawTorus.h"

//Gestion de la résolution de la fenetre au démarrage
#define W_SCREEN 853
#define H_SCREEN  480
#define RATIO_SCREEN  1.77

//Les variables globales
//La fenetre principale
static int g_window;

//La position et rotation de la camera
static float g_camera_angleX = 0;   //L'angle de rotation suivant X (en °)
static float g_camera_angleY = 0;   //L'angle de rotaion suivant Y (en °)
static float g_camera_transX = 0;   //La translation suivant X
static float g_camera_transY = 0;   //La translation suivant Y
static float g_camera_transZ = 20;  //La translation suivant Z

//Les variagles pour la gestion de la souris
//La position de depart d'un mouvement
static int g_mouse_startX;
static int g_mouse_startY;
//Le type d'action active
static int g_mouse_rotation=0;
static int g_mouse_translateXY=0;
static int g_mouse_translateZ=0;

//Un pointeur sur la scene
TScene *g_pScene=NULL;

//Les types de formes
enum{
    TYPE_SHAPE_SPHERE = 0,
    TYPE_SHAPE_CUBE,
    TYPE_SHAPE_CONE,
    TYPE_SHAPE_CYLINDRE,
    TYPE_SHAPE_TORUS,
    TYPE_SHAPE_UNKNOWN
};

//Test des erreurs avec openGL
#define OPENGL_CHECK_ERROR(str)                                    \
{                                                                  \
    GLenum error;                                                  \
    if((error = glGetError()) != GL_NO_ERROR)                      \
       printf("GL Error: %s (%s)\n", gluErrorString(error), str);  \
}

//Fonction pour detruire les allocations
void DestroyEnd()
{
    if(g_pScene)
        DestroyScene(g_pScene);
}

// ========================================================
// Gestion fenetrage windows
// ========================================================
#if defined (WIN32)
#include <windows.h>
static WNDPROC currentWndProc;
static HWND handle  = NULL;

static LRESULT CALLBACK winProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_CLOSE:
            DestroyEnd();
            exit(0);
            break;
        case WM_DESTROY:
            DestroyEnd();
            exit(0);
            break;
        default:
            return CallWindowProc(currentWndProc, handle, Msg, wParam, lParam);
            break;
    }
    return 0;
}

static void fixCloseWindowOnWin32()
{
    handle = WindowFromDC(wglGetCurrentDC());
    DragAcceptFiles (handle, TRUE);
    currentWndProc = (WNDPROC)GetWindowLongPtr(handle, GWL_WNDPROC);
    SetWindowLongPtr(handle, GWL_WNDPROC, (long)winProc);
}
#endif //WIN32
// ========================================================
// Gestion fenetrage windows
// ========================================================

//Fonction pour ajouter une primitive dans la scene
void AddPrimitiveToRender(unsigned char type)
{
//Des variables
    float r0,h0,rmax;
    int i0,i1;
//Cree la forme ...
    void *pShape = NULL;
    void (*pF_Draw)(void*) = NULL;
    switch(type) //... en fonction du type
    {
        case TYPE_SHAPE_SPHERE: //Une sphere
            pShape = malloc(sizeof(TShapeSphere));
            if(pShape==NULL)
            {
                printf("Erreur pour creer la forme sphere\n");
                return;
            }
            printf("Rayon de la sphere: ");
            scanf("%f",&r0);
            ((TShapeSphere*)pShape)->m_Radius = r0;
            printf("Nombre de secteur: ");
            scanf("%d",&i0);
            ((TShapeSphere*)pShape)->m_Sector = i0;
            pF_Draw = DrawSphere;
            break;
        case TYPE_SHAPE_CUBE: //Un cube
            pShape = malloc(sizeof(TShapeCube));
            if(pShape==NULL)
            {
                printf("Erreur pour creer la forme cube\n");
                return;
            }
            printf("Taille du cube: ");
            scanf("%f",&r0);
            ((TShapeCube*)pShape)->m_Size = r0;
            pF_Draw = DrawCube;
            break;

        case TYPE_SHAPE_CONE: //Une cône
            pShape = malloc(sizeof(TShapeCone));
            if(pShape==NULL)
            {
                printf("Erreur pour creer la forme sphere\n");
                return;
            }
            printf("Rayon du cone: ");
            scanf("%f",&r0);
            ((TShapeCone*)pShape)->m_Radius = r0;
            printf("Hauteur du cone: ");
            scanf("%f",&h0);
            ((TShapeCone*)pShape)->m_Height = h0;
            printf("Nombre de secteur: ");
            scanf("%d",&i0);
            ((TShapeCone*)pShape)->m_Sector = i0;
            pF_Draw = DrawCone;
            break;
            
        case TYPE_SHAPE_CYLINDRE: //Un cylindre
            pShape = malloc(sizeof(TShapeCylindre));
            if(pShape==NULL)
            {
                printf("Erreur pour creer la forme cylindre\n");
                return;
            }
            printf("Rayon du cylindre: ");
            scanf("%f",&r0);
            ((TShapeCylindre*)pShape)->m_Radius = r0;
            printf("Hauteur du cone: ");
            scanf("%f",&h0);
            ((TShapeCylindre*)pShape)->m_Size = h0;
            printf("Nombre de secteur: ");
            scanf("%d",&i0);
            ((TShapeCylindre*)pShape)->m_Sector = i0;
            pF_Draw = DrawCylindre;
            break;

         case TYPE_SHAPE_TORUS: //Une tore
            pShape = malloc(sizeof(TShapeTorus));
            if(pShape==NULL)
            {
                printf("Erreur pour creer la forme Tore\n");
                return;
            }
            printf("Rayon minimum: ");
            scanf("%f",&r0);
            ((TShapeTorus*)pShape)->m_RadiusMin = r0;
            printf("Rayon maximum: ");
            scanf("%f",&rmax);
            ((TShapeTorus*)pShape)->m_RadiusMax = rmax;
            printf("Nombre de secteurs de l'anneau: ");
            scanf("%d",&i0);
            ((TShapeTorus*)pShape)->m_SectorRing = i0;
            printf("Nombre de secteurs lateraux: ");
            scanf("%d",&i1);
            ((TShapeTorus*)pShape)->m_SectorSide = i1;
            pF_Draw = DrawTorus;
            break;
            

        default:
            printf("Erreur, le type de primitive n'existe pas!\n");
            return;
    }
//Les proprietes de la primitive
    //Cree une matrice de transformation
    TMatrixTransform mpos;
    //Translation
    MatrixTransformTranslate(mpos,
                             (float)GetRand(-10,10),
                             (float)GetRand(-10,10),
                             (float)GetRand(-10,10));

    //Cree une couleur
    float color[3]={(float)GetRand(0,100)/100.F,
                    (float)GetRand(0,100)/100.F,
                    (float)GetRand(0,100)/100.F};
    //Cree un materiau
    TMaterial *pMat = CreateMaterial(color,NULL);

//Cree la primitive
    TGeometricPrimitive *pPrim = CreateGeometricPrimitive(pF_Draw,
                                        pShape,
                                        pMat,
                                        mpos);
    if(pPrim==NULL)
    {
        free(pShape);
        free(pMat);
        printf("Erreur de creation de la primitive\n");
        return;
    }
//Ajoute a la scene
    if(AddPrimitiveScene(g_pScene,pPrim)==0)
    {
        printf("Erreur pour ajouter la primitive a la scene\n");
        free(pPrim);
        free(pShape);
        free(pMat);
    }
}

//Fonction pour supprimer une primitive a la scene
void RemovePrimitiveToRender()
{
//Verifie qu'il a des spheres
    if(g_pScene->m_NumberPrimitive==0)
    {
        printf("Pas de primitive a retirer\n");
        return;
    }
//Prend une primitive au hasard
    int index=GetRand(0,g_pScene->m_NumberPrimitive-1);
    RemovePrimitiveScene(g_pScene,index);
}

//Fonction pour gerer les boutons de la souris
void MouseButtonFunc(int button, int state, int x, int y)
{
  //Si bouton de gauche
  if(button == GLUT_LEFT_BUTTON)
  {
    //Si actif
    if(state == GLUT_DOWN)
    {
        //Sauvegarde de la position de depart
        g_mouse_startX = x;
        g_mouse_startY = y;
        //Active la rotation
        g_mouse_rotation = 1;
    }
    else //Si relache...
    {
        //Desactive la rotation
        g_mouse_rotation = 0;
    }
 }
 //Si bouton du milieu
 else if(button == GLUT_MIDDLE_BUTTON)
 {
     if(state == GLUT_DOWN)
     {
         g_mouse_startX = x;
         g_mouse_startY = y;
         g_mouse_translateZ=1;
     }
     else
     {
         g_mouse_translateZ=0;
     }
 }
 if(button == GLUT_RIGHT_BUTTON)
 {
     if(state == GLUT_DOWN)
     {
         g_mouse_startX = x;
         g_mouse_startY = y;
         g_mouse_translateXY=1;
     }
     else
     {
         g_mouse_translateXY=0;
     }
 }
}

//Gestion du mouvement de la souris
void MouseMotionFunc(int x, int y)
{
    //Si c'est la rotation
    if(g_mouse_rotation)
    {
        //Calcul les nouveaux angles en fonction du mouvement de la souris
        g_camera_angleX = g_camera_angleX + (y - g_mouse_startY);
        g_camera_angleY = g_camera_angleY + (x - g_mouse_startX);
        //Sauvegarde la position pour le prochain mouvement
        g_mouse_startX = x;
        g_mouse_startY = y;
    }
    //Si c'est la translation
    else if(g_mouse_translateZ)
    {
        g_camera_transZ += (y-g_mouse_startY)/10.0;
        //Limite le deplacement
        if(g_camera_transZ>100)
           g_camera_transZ=100;
        if(g_camera_transZ<5)
           g_camera_transZ=5;
        g_mouse_startY = y;
    }
    else if(g_mouse_translateXY)
    {
        g_camera_transX += (x-g_mouse_startX)/10.0;
        g_camera_transY -= (y-g_mouse_startY)/10.0;
        g_mouse_startX = x;
        g_mouse_startY = y;
    }
    glutPostRedisplay();
}

//Fonction pour la gestion du clavier (hors touches speciales)
void KeyboardFunc(unsigned char key, int x, int y)
{
    int i0;
    switch(key)
    {
        case 'a':
            printf("%d: Sphere\n%d: Cube\n%d: Cone\n%d: Cylindre\n%d: Tore\n",TYPE_SHAPE_SPHERE,TYPE_SHAPE_CUBE,TYPE_SHAPE_CONE,TYPE_SHAPE_CYLINDRE,TYPE_SHAPE_TORUS);
            printf("Forme a ajouter: ");
            scanf("%i",&i0);
            AddPrimitiveToRender(i0);
            break;
        case 'A':
            RemovePrimitiveToRender();
            break;
    }
    glutPostRedisplay();
}

void DrawOrthonormal()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glEnd();
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1.0,0.0);
    glEnd();
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glEnd();
    glEnable(GL_LIGHTING);
}


//La fonction de dessin pour GLUT
void DisplayFunc()
{
//La couleur par defaut
    glClearColor(0.1,0.1,0.1,1.0);

//Efface le buffer de dessin
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//La position de visualisation
    //Charge une matrice identitee
    glLoadIdentity();
    //La position du regard
    gluLookAt(0.0,0.0,g_camera_transZ, //L'oeil
              0.0,0.0,0.0,  //Vers où
              0.0,1.0,0.0); //orientation de l'oeil

//Effectue des deplacement de la camera
  //Deplacement
  glTranslatef(g_camera_transX,g_camera_transY,0);
  //Rotation suivant X
  glRotatef(g_camera_angleX, 1.0, 0.0, 0.0);
  //Rotation suivant Y
  glRotatef(g_camera_angleY, 0.0, 1.0, 0.0);

//Affiche un repere
    DrawOrthonormal();

//Affiche la scene
    DrawScene(g_pScene);

//Charge le nouveau dessin
    glutSwapBuffers();

//Test si erreur
    OPENGL_CHECK_ERROR("Error DisplayFunc !");
}

void CreateSceneMoteur3D()
{
//Cree une scene
    g_pScene = CreateScene(10000);

//Cree et ajoute une lampe
    float lamb[4] = {0.0f,0.0f,0.0f,1.0f};
    float ldif[4] = {0.8f,0.8f,0.8f,1.0f};
    float lspec[4] = {0.0f,0.0f,0.0f,1.0f};
    float lpos[4] = {0.0f,0.0f,0.0f,1.0f};
    TLight *pl = CreateLight(lamb,ldif,lspec,lpos,GL_LIGHT0);

    if(AddLightScene(g_pScene,pl)==0)
    {
        printf("Erreur pour ajouter la lumiere a la scene\n");
        free(pl);
    }
}


int main(int argc, char *argv[])
{
//Initialisation de glut
    glutInit(&argc,argv);
//Initialise le mode de dessin
//                        2 buffers   RGB          profondeur
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//Creation de la fenetre
    glutInitWindowSize(W_SCREEN,H_SCREEN);
    g_window = glutCreateWindow("Moteur 3D");
//La fonction pour dessiner
    glutDisplayFunc(DisplayFunc);
//Les fonctions pour la souris
    glutMouseFunc(MouseButtonFunc);
    glutMotionFunc(MouseMotionFunc);
//Les fonctions pour le clavier
    glutKeyboardFunc(KeyboardFunc);

//Active le buffer de pronfondeur
  glEnable(GL_DEPTH_TEST);

//Initialise le mode de projetction (la camera)
   //Choix de la matrice a modifier
  glMatrixMode(GL_PROJECTION);
  //Les specifications de cette matrice
  gluPerspective( 45.0, //Angle d'ouverture
                  RATIO_SCREEN,  //Le ratio entre X et Y
                  0.1, //La limite min en Z
                  200.0); //La limite max en Z

//On ne touche plus que la matrice de visualisation dans le reste du programme
  glMatrixMode(GL_MODELVIEW);

//Gestion de la fenetre sous windows
    #if defined (WIN32)
    fixCloseWindowOnWin32();
    #endif //WIN32

//Creation de la scene
    CreateSceneMoteur3D();

//Test si erreur
    OPENGL_CHECK_ERROR("Main !");

//Une boucle infinie
    glutMainLoop();
    return 0;
}

