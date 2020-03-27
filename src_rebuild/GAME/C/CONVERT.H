#ifndef CONVERT_H
#define CONVERT_H


extern void Calc_Object_MatrixYZX(struct MATRIX *mat, struct SVECTOR *angles); // 0x0002D3F8

extern void _RotMatrixX(struct MATRIX *m, short ang); // 0x0002D470

extern void _RotMatrixY(struct MATRIX *m, short ang); // 0x0002D49C

extern void _RotMatrixZ(struct MATRIX *m, short ang); // 0x0002D4C8

extern void RotMatrixXYZ(struct MATRIX *m, struct SVECTOR *r); // 0x0002D4F4

extern void _MatrixRotate(struct VECTOR *pos); // 0x0002D51C

extern void InvertMatrix(struct MATRIX *a, struct MATRIX *b); // 0x0002D55C

extern void BuildWorldMatrix(); // 0x0002D304

extern void ScaleCamera(); // 0x0002D5C8

extern void Getlong(char *dest, char *source); // 0x0002D678

extern void RandomInit(long i1, long i2); // 0x0002D6A8

extern long Random2(int step); // 0x0002D724


#endif
