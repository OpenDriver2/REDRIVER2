#ifndef CONVERT_H
#define CONVERT_H


extern void Calc_Object_MatrixYZX(MATRIX *mat, SVECTOR *angles); // 0x0002D3F8

extern void _RotMatrixX(MATRIX *m, short ang); // 0x0002D470

extern void _RotMatrixY(MATRIX *m, short ang); // 0x0002D49C

extern void _RotMatrixZ(MATRIX *m, short ang); // 0x0002D4C8

extern void RotMatrixXYZ(MATRIX *m, SVECTOR *r); // 0x0002D4F4

extern void _MatrixRotate(VECTOR *pos); // 0x0002D51C

extern void InvertMatrix(MATRIX *a, MATRIX *b); // 0x0002D55C

extern void BuildWorldMatrix(); // 0x0002D304

extern void ScaleCamera(); // 0x0002D5C8

extern void Getlong(char *dest, char *source); // 0x0002D678

extern void RandomInit(long i1, long i2); // 0x0002D6A8

extern long Random2(int step); // 0x0002D724


#endif
