#ifndef ASMTEST_H
#define ASMTEST_H


extern void SetCameraVector() ; // 0x0001BCD4

extern void date_date() ; // 0x0009BB6C

extern void date_time() ; // 0x0009BB70

extern void cd_icon() ; // 0x0009BB74

extern void Apply_Inv_CameraMatrix(VECTOR* v) ; // 0x0001BCFC
extern int Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD *pos);
extern int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD *pos, MATRIX2 *mtx);

extern int FrustrumCheck16(PACKED_CELL_OBJECT* pcop, int bounding_sphere) ; // 0x0001BD30

extern void FrustrumCheck() ; // 0x0001BDEC

extern void Asm_PlotSprite() ; // 0x0001BEE4


#endif
