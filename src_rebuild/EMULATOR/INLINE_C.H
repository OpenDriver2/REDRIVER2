#ifndef INLINE_C_H
#define INLINE_C_H

extern void gte_SetGeomScreen(int h);
extern int gte_ldlzc(int input);

// load IR1-IR3 (mtc2 regs 9,10,11)
#define gte_ldclmv( r0 ) \
	MTC2(*(ushort*)((char*)r0), 9);\
	MTC2(*(ushort*)((char*)r0+6), 10);\
	MTC2(*(ushort*)((char*)r0+12), 11);\

// store IR1-IR3 (mfc2 regs 9,10,11)
#define gte_stclmv( r0 ) \
	*(ushort*)((char*)r0) = IR1; \
	*(ushort*)((char*)r0 + 6) = IR2; \
	*(ushort*)((char*)r0 + 12) = IR3;

// load ctc2 8-11
#define gte_SetLightMatrix( r0 ) \
	CTC2(*(uint*)((char*)r0), 8);\
	CTC2(*(uint*)((char*)r0+4), 9);\
	CTC2(*(uint*)((char*)r0+8), 10);\
	CTC2(*(uint*)((char*)r0+12), 11);\
	CTC2(*(uint*)((char*)r0+16), 12);

// load ctc2 16-20
#define gte_SetColorMatrix( r0 ) \
	CTC2(*(uint*)((char*)r0), 16);\
	CTC2(*(uint*)((char*)r0+4), 17);\
	CTC2(*(uint*)((char*)r0+8), 18);\
	CTC2(*(uint*)((char*)r0+12), 19);\
	CTC2(*(uint*)((char*)r0+16), 20);

// load ctc2 0-4
#define gte_SetRotMatrix( r0 )	\
	CTC2(*(uint*)((char*)r0), 0);\
	CTC2(*(uint*)((char*)r0+4), 1);\
	CTC2(*(uint*)((char*)r0+8), 2);\
	CTC2(*(uint*)((char*)r0+12), 3);\
	CTC2(*(uint*)((char*)r0+16), 4);\

// load ctc2 5-7
#define gte_SetTransVector( r0 )\
	CTC2_S(*(int*)((char*)r0+0), 5);\
	CTC2_S(*(int*)((char*)r0+4), 6);\
	CTC2_S(*(int*)((char*)r0+8), 7);

// load ctc2 5-7
#define gte_SetTransMatrix( r0 ) \
	CTC2(*(uint*)((char*)r0+20), 5);\
	CTC2(*(uint*)((char*)r0+24), 6);\
	CTC2(*(uint*)((char*)r0+28), 7);

// store cfc2 0-7
#define gte_ReadRotMatrix( r0 ) \
	*(uint*)((char*)r0) = CFC2(0);		\
	*(uint*)((char*)r0 + 4) = CFC2(1);	\
	*(uint*)((char*)r0 + 8) = CFC2(2);	\
	*(uint*)((char*)r0 + 12) = CFC2(3);	\
	*(uint*)((char*)r0 + 16) = CFC2(4);	\
	*(uint*)((char*)r0 + 20) = CFC2(5);	\
	*(uint*)((char*)r0 + 24) = CFC2(6);	\
	*(uint*)((char*)r0 + 28) = CFC2(7);

// lwc2 9-11
#define gte_ldlvl( r0 ) \
	IR1 = *(ushort*)((char*)r0); \
	IR2 = *(ushort*)((char*)r0 + 4);\
	IR3 = *(ushort*)((char*)r0 + 8);

// swc2 9-11
#define gte_stlvl( r0 ) \
	*(ushort*)((char*)r0) = IR1; \
	*(ushort*)((char*)r0 + 4) = IR2;\
	*(ushort*)((char*)r0 + 8) = IR3;

// ctc2 21-23
#define gte_ldfc( r0 ) \
	CTC2(*(uint*)((char*)r0+0), 21);\
	CTC2(*(uint*)((char*)r0+4), 22);\
	CTC2(*(uint*)((char*)r0+8), 23);



#endif