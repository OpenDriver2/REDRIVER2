#ifndef INLINE_C_H
#define INLINE_C_H

extern void gte_SetGeomScreen(int h);
extern int gte_ldlzc(int input);

extern int docop2(int op);

/*
 * Type 1 functions
 */

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
	MTC2(*(uint*)((char*)r0+0), 2);\
	MTC2(*(uint*)((char*)r0+4), 3);

// mtc2 4-5
#define gte_ldv2( r0 )\
	MTC2(*(uint*)((char*)r0+0), 4);\
	MTC2(*(uint*)((char*)r0+4), 5);

// mtc2 0-5
#define gte_ldv3( r0, r1, r2 ) \
	MTC2(*(uint*)((char*)r0+0), 0);\
	MTC2(*(uint*)((char*)r0+4), 1);\
	MTC2(*(uint*)((char*)r1+0), 2);\
	MTC2(*(uint*)((char*)r1+4), 3);\
	MTC2(*(uint*)((char*)r2+0), 4);\
	MTC2(*(uint*)((char*)r2+4), 5);

// load mtc2 9,10,11
#define gte_ldclmv( r0 ) \
	MTC2(*(ushort*)((char*)r0), 9); \
	MTC2(*(ushort*)((char*)r0+6), 10); \
	MTC2(*(ushort*)((char*)r0+12), 11);\

// lwc2 9-11
#define gte_ldlvl( r0 ) \
	MTC2(*(uint*)((char*)r0), 9); \
	MTC2(*(uint*)((char*)r0 + 4), 10);\
	MTC2(*(uint*)((char*)r0 + 8), 11);

#define gte_ldrgb( r0 ) \
	MTC2(*(uint*)((char*)r0), 6);

// mtc2 8
#define gte_lddp( r0 )	\
	MTC2(*(uint*)r0, 8);

// ctc2 13 14 15
#define gte_ldbkdir( r0, r1, r2 ) \
	CTC2(r0, 13); \
	CTC2(r1, 14); \
	CTC2(r2, 15);

// ctc2 24,25
#define gte_SetGeomOffset( r0, r1 )\
	CTC2(r0 << 16, 24); \
	CTC2(r1 << 16, 25); \

// ctc2 13,14,15
#define gte_SetBackColor( r0, r1, r2 ) \
				{	CTC2(r1 << 4, 13); \
					CTC2(r2 << 4, 14); \
					CTC2(r3 << 4, 15); }


// ctc2 21, 22, 23
#define gte_SetFarColor( r0, r1, r2 ) \
				{	CTC2(r1 << 4, 21); \
					CTC2(r2 << 4, 22); \
					CTC2(r3 << 4, 23); }

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

/*
 * Type 2 functions
 */

 // FIXME: there is lack of some macros
 // please refer to official Psy-Q PSX SDK headers
 // and this: https://github.com/ogamespec/pops-gte/blob/master/docs/gte.txt

#define gte_rtv0tr()		docop2(0x480012);
#define gte_rtv0()			docop2(0x486012);
#define gte_lcir()			docop2(0x4DE012);
#define gte_llir()			docop2(0x4BE012);

#define gte_rtir()			docop2(0x49E012)
#define gte_rtps()			docop2(0x180001)
#define gte_rtpt()			docop2(0x280030)
#define gte_nclip()			docop2(0x1400006)
#define gte_avsz3()			docop2(0x158002D)
#define gte_avsz4()			docop2(0x168002E)
#define gte_sqr0()			docop2(0xA00428)
#define gte_sqr12()			docop2(0xA80428)
#define gte_op0()			docop2(0x170000C)
#define gte_op12()			docop2(0x178000C)
#define gte_ncs()			docop2(0xC8041E)
#define gte_nct()			docop2(0xD80420)
#define gte_nccs()			docop2(0x108041B)
#define gte_ncct()			docop2(0x118043F)
#define gte_ncds()			docop2(0xE80413)
#define gte_ncdt()			docop2(0xF80416)
#define gte_cc()			docop2(0x138041C)
#define gte_cdp()			docop2(0x1280414)
#define gte_dcpl()			docop2(0x680029)
#define gte_dpcs()			docop2(0x780010)
#define gte_dpct()			docop2(0x180001)
#define gte_intpl()			docop2(0x980011)
#define gte_gpf0()			docop2(0x190003D)
#define gte_gpf12()			docop2(0x198003D)
#define gte_gpl0()			docop2(0x1A0003E)
#define gte_gpl12()			docop2(0x1A8003E)

#define gte_mvmva(sf, mx, v, cv, lm) docop2( 0x0400012 | \
	((sf)<<19) | ((mx)<<17) | ((v)<<15) | ((cv)<<13) | ((lm)<<10) )

 /*
  * Type 3 functions
  */

// store mfc2 9,10,11
#define gte_stclmv( r0 ) \
	*(ushort*)((char*)r0) = MFC2(9) & 0xFFFF; \
	*(ushort*)((char*)r0 + 6) = MFC2(10) & 0xFFFF; \
	*(ushort*)((char*)r0 + 12) = MFC2(11) & 0xFFFF;

#if defined(USE_PGXP)

// swc2 14
#define gte_stsxy( r0 ) \
	*(uint*)((char*)r0) = *(uint*)&g_FP_SXYZ2.x;

// mfc2 12-14
#define gte_stsxy3( r0, r1, r2 )	\
	*(uint*)((char*)r0) = *(uint*)&g_FP_SXYZ0.x;\
	*(uint*)((char*)r1) = *(uint*)&g_FP_SXYZ1.x;\
	*(uint*)((char*)r2) = *(uint*)&g_FP_SXYZ2.x;

// swc2 14
#define gte_stsxy2( r0 ) gte_stsxy(r0)

// swc2 13
#define gte_stsxy1( r0 ) \
	*(uint*)((char*)r0) = *(uint*)&g_FP_SXYZ1.x;

// swc2 12
#define gte_stsxy0( r0 ) \
	*(uint*)((char*)r0) = *(uint*)&g_FP_SXYZ0.x;

#else

// swc2 14
#define gte_stsxy( r0 ) \
	*(uint*)((char*)r0) = MFC2(14);

// mfc2 12-14
#define gte_stsxy3( r0, r1, r2 )	\
	*(uint*)((char*)r0) = MFC2(12);\
	*(uint*)((char*)r1) = MFC2(13);\
	*(uint*)((char*)r2) = MFC2(14);

// swc2 14
#define gte_stsxy2( r0 ) gte_stsxy(r0)

// swc2 13
#define gte_stsxy1( r0 ) \
	*(uint*)((char*)r0) = MFC2(13);

// swc2 12
#define gte_stsxy0( r0 ) \
	*(uint*)((char*)r0) = MFC2(12);

#endif

// swc2 8
#define gte_stdp( r0 ) \
	*(uint*)((char*)r0) = MFC2(8); \

// cfc2 31
#define gte_stflg( r0 ) \
	*(uint*)((char*)r0) = CFC2(31);

// swc2 7
#define gte_stotz( r0 ) \
	*(uint*)((char*)r0) = MFC2(7);

// mfc2 19 
#define gte_stszotz( r0 ) \
	*(uint*)((char*)r0) = MFC2(19) >> 2;

// swc2 24
#define gte_stopz( r0 ) \
	*(uint*)((char*)r0) = MFC2(24);

// swc2 19
#define gte_stsz( r0 ) \
	*(uint*)((char*)r0) = MFC2(19);

// swc2 9-11
#define gte_stlvl( r0 ) \
	*(uint*)((char*)r0) = MFC2(9); \
	*(uint*)((char*)r0 + 4) = MFC2(10);\
	*(uint*)((char*)r0 + 8) = MFC2(11);

// mfc2 9, 10, 11
#define gte_stsv( r0 ) \
	*(ushort*)((char*)r0) = MFC2(9) & 0xFFFF; \
	*(ushort*)((char*)r0 + 2) = MFC2(10) & 0xFFFF;\
	*(ushort*)((char*)r0 + 4) = MFC2(11) & 0xFFFF;

// swc2 17,18,19
#define gte_stsz3( r0, r1, r2 ) \
	*(uint*)((char*)r0) = MFC2(17);\
	*(uint*)((char*)r1) = MFC2(18);\
	*(uint*)((char*)r2) = MFC2(19);

// swc2 25,26,27
#define gte_stlvnl( r0 ) \
	*(uint*)((char*)r0 + 0) = MFC2(25);\
	*(uint*)((char*)r0 + 4) = MFC2(26);\
	*(uint*)((char*)r0 + 8) = MFC2(27);

// ctc2 5,6,7
#define gte_ldtr( r0, r1, r2 ) \
	CTC2(*(uint*)((char*)r0), 5);\
	CTC2(*(uint*)((char*)r1), 6);\
	CTC2(*(uint*)((char*)r2), 7);\

// cfc2 5,6,7
#define gte_sttr( r0 ) \
	*(uint*)((char*)r0 + 0) = CFC2(5);\
	*(uint*)((char*)r0 + 4) = CFC2(6);\
	*(uint*)((char*)r0 + 8) = CFC2(7);

// swc2 22
#define gte_strgb( r0 )\
	*(uint*)((char*)r0) = MFC2(22);

// swc2 20 21 22
#define gte_strgb3( r0, r1, r2 )\
	*(uint*)((char*)r0) = MFC2(20);\
	*(uint*)((char*)r1) = MFC2(21);\
	*(uint*)((char*)r2) = MFC2(22);


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

// cfc2 21,22,23
#define gte_stfc( r0 )\
	*(uint*)((char*)r0 + 0) = CFC2(21);\
	*(uint*)((char*)r0 + 4) = CFC2(22);\
	*(uint*)((char*)r0 + 8) = CFC2(23);

#endif