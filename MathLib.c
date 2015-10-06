#include "MathLib.h"

//La librairie pour les math (sin, cos, ...)
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Definition.h"

//La fonction calcul la position sur une sphere unitaire
void PointOnUnitSphere(const double azim, const double zeni, double *px, double *py, double *pz)
{
    (*px) = sin(azim)*cos(zeni);
    (*py) = sin(azim)*sin(zeni);
    (*pz) = cos(azim);
}

//Fonction pour generer un nombre aleatoire entre minV et maxV
int GetRand(int minV, int maxV)
{
  static int first = 0;
  if(first == 0)
  {
     srand(time(NULL));
     first = 1;
  }
  return minV+(int)((double)rand()*(double)(maxV-minV)/(double)RAND_MAX);
}
