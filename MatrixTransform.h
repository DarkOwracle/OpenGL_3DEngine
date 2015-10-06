#if !defined(MATRIXTRANSFORM_H)
#define MATRIXTRANSFORM_H

//Definition d'une matrice de transformation
//  | a0    a4      a8      a12|
//  | a1    a5      a9      a13|
//  | a2    a6      a10     a14|
//  | a3    a7      a11     a15|
typedef float TMatrixTransform[16];

void MatrixTransformIdentity(float *m);

void MatrixTransformTranslate(float *m, float x, float y, float z);

void MatrixTransformRotateX(float *m, float angle);
void MatrixTransformRotateY(float *m, float angle);
void MatrixTransformRotateZ(float *m, float angle);

void MatrixTransformScale(float *m, float sx, float sy, float sz);

void MatrixTransformMult(float *m, float *m1, float *m2);

void MatrixTransformCopy(float *mdest, float *msource);

void MatrixTransform_TransformPoint(float *m, float *p);
void PrintMatrixTransform(float *m);

#endif // !defined(MATRIXTRANSFORM_H)
