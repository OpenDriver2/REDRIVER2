#ifndef INLINE_C_H
#define INLINE_C_H

extern void gte_SetGeomScreen(int h);
extern int gte_ldlzc(int input);

// load mtc2 9,10,11
#define gte_ldclmv( r0 ) \
	IR1 = *(ushort*)((char*)r0);\
	IR2 = *(ushort*)((char*)r0+6);\
	IR3 = *(ushort*)((char*)r0+12);\

// store mfc2 9,10,11
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

// cfc2 16-23
#define gte_ReadColorMatrix( r0 ) \
	*(uint*)((char*)r0) = CFC2(16);		\
	*(uint*)((char*)r0 + 4) = CFC2(17);	\
	*(uint*)((char*)r0 + 8) = CFC2(18);	\
	*(uint*)((char*)r0 + 12) = CFC2(19);	\
	*(uint*)((char*)r0 + 16) = CFC2(20);	\
	*(uint*)((char*)r0 + 20) = CFC2(21);	\
	*(uint*)((char*)r0 + 24) = CFC2(22);	\
	*(uint*)((char*)r0 + 28) = CFC2(23);

// cfc2 8-15
#define gte_ReadLightMatrix( r0 ) \
	*(uint*)((char*)r0) = CFC2(8);		\
	*(uint*)((char*)r0 + 4) = CFC2(9);	\
	*(uint*)((char*)r0 + 8) = CFC2(10);	\
	*(uint*)((char*)r0 + 12) = CFC2(11);	\
	*(uint*)((char*)r0 + 16) = CFC2(12);	\
	*(uint*)((char*)r0 + 20) = CFC2(13);	\
	*(uint*)((char*)r0 + 24) = CFC2(14);	\
	*(uint*)((char*)r0 + 28) = CFC2(15);

// ctc2 8-12
#define gte_SetLightMatrix( r0 )\
	CTC2(*(uint*)((char*)r0), 8);\
	CTC2(*(uint*)((char*)r0+4), 9);\
	CTC2(*(uint*)((char*)r0+8), 10);\
	CTC2(*(uint*)((char*)r0+12), 11);\
	CTC2(*(uint*)((char*)r0+16), 12);

// ctc2 16-20
#define gte_SetColorMatrix( r0 )\
	CTC2(*(uint*)((char*)r0), 16);\
	CTC2(*(uint*)((char*)r0+4), 17);\
	CTC2(*(uint*)((char*)r0+8), 18);\
	CTC2(*(uint*)((char*)r0+12), 19);\
	CTC2(*(uint*)((char*)r0+16), 20);

// lwc2 9-11
#define gte_ldlvl( r0 ) \
	MTC2(*(uint*)((char*)r0), 9); \
	MTC2(*(uint*)((char*)r0 + 4), 10);\
	MTC2(*(uint*)((char*)r0 + 8), 11);

// swc2 9-11
#define gte_stlvl( r0 ) \
	*(uint*)((char*)r0) = MFC2(9); \
	*(uint*)((char*)r0 + 4) = MFC2(10);\
	*(uint*)((char*)r0 + 8) = MFC2(11);

// ctc2 21-23
#define gte_ldfc( r0 ) \
	CTC2(*(uint*)((char*)r0+0), 21);\
	CTC2(*(uint*)((char*)r0+4), 22);\
	CTC2(*(uint*)((char*)r0+8), 23);

// mtc2 0-1
#define gte_ldv0( r0 )\
	MTC2(*(uint*)((char*)r0+0), 0);\
	MTC2(*(uint*)((char*)r0+4), 1);

// mtc2 2-3
#define gte_ldv1( r0 )\
	MTC2(*(uint*)((char*)r1+0), 2);\
	MTC2(*(uint*)((char*)r1+4), 3);

// mtc2 4-5
#define gte_ldv2( r0 )\
	MTC2(*(uint*)((char*)r2+0), 4);\
	MTC2(*(uint*)((char*)r2+4), 5);

// mtc2 0-5
#define gte_ldv3( r0, r1, r2 ) \
	MTC2(*(uint*)((char*)r0+0), 0);\
	MTC2(*(uint*)((char*)r0+4), 1);\
	MTC2(*(uint*)((char*)r1+0), 2);\
	MTC2(*(uint*)((char*)r1+4), 3);\
	MTC2(*(uint*)((char*)r2+0), 4);\
	MTC2(*(uint*)((char*)r2+4), 5);

// mfc2 12-14
#define gte_stsxy3( r0, r1, r2 )	\
	*(uint*)((char*)r0+0) = SXY0;\
	*(uint*)((char*)r1+0) = SXY1;\
	*(uint*)((char*)r2+0) = SXY2;

#define gte_rtpt() docop2(0x280030);

#define gte_stdp( r0 ) \
	*(uint*)((char*)r0 + 0) = IR0; \

#define gte_stflg( r0 ) \
	*(uint*)((char*)r0+0) = FLAG;

#define gte_stszotz( r0 ) \
	*(uint*)((char*)r0+0) = SZ3 >> 2;

#define gte_rtir() docop2(0x49E012);

// TODO: GTEMAC
#define gte_RotTransPers3(r1,r2,r3,r4,r5,r6,r7,r8,r9)		\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
					gte_stsxy3(r4,r5,r6);	\
					gte_stdp(r7);		\
					gte_stflg(r8);		\
					gte_stszotz(r9);	}

#define gte_MulMatrix0(r1,r2,r3)				\
				{	gte_SetRotMatrix(r1);	\
					gte_ldclmv(r2);		\
					gte_rtir();		\
					gte_stclmv(r3);		\
					gte_ldclmv((char*)r2+2);\
					gte_rtir();		\
					gte_stclmv((char*)r3+2);\
					gte_ldclmv((char*)r2+4);\
					gte_rtir();		\
					gte_stclmv((char*)r3+4);	}

#endif