#ifndef RNDRASM_H
#define RNDRASM_H


extern void SetCameraVector(); // 0x0001BCD4

extern void Apply_Inv_CameraMatrix(VECTOR* v); // 0x0001BCFC
extern int Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD* pos);
extern int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD* pos, MATRIX2* mtx);

extern int FrustrumCheck16(PACKED_CELL_OBJECT* pcop, int bounding_sphere); // 0x0001BD30

extern int FrustrumCheck(VECTOR* pos, int bounding_sphere); // 0x0001BDEC



#endif
