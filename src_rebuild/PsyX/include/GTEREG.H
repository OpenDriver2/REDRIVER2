#ifndef GTEREG_H
#define GTEREG_H


typedef union
{
	struct { unsigned char l, h, h2, h3; } b;
	struct { unsigned short l, h; } w;
	struct { char l, h, h2, h3; } sb;
	struct { short l, h; } sw;

	unsigned int d;
	int sd;
} PAIR;

typedef struct {
	unsigned char r, g, b, c;
} CBGR;

typedef struct {
	short x, y, z, pad;
} SVector3D;

typedef struct {
	short x, y;
} SVector2D;

typedef struct {
	short z, pad;
} SVector2Dz;

typedef struct {
	short m11, m12, m13, m21, m22, m23, m31, m32, m33, pad;
} SMatrix3D;

typedef union
{
	struct
	{
		SVector3D		v0, v1, v2;
		CBGR			rgb;
		int				otz;
		int				ir0, ir1, ir2, ir3;
		SVector2D		sxy0, sxy1, sxy2, sxyp;
		SVector2Dz		sz0, sz1, sz2, sz3;
		CBGR			rgb0, rgb1, rgb2;
		int				reserved;
		int				mac0, mac1, mac2, mac3;
		unsigned int	irgb, orgb;
		int				lzcs, lzcr;
	} n;

	unsigned int r[32];
	PAIR p[32];

} psxCP2Data;

typedef union
{
	struct {
		SMatrix3D	rMatrix;
		int			trX, trY, trZ;
		SMatrix3D	lMatrix;
		int			rbk, gbk, bbk;
		SMatrix3D	cMatrix;
		int			rfc, gfc, bfc;
		int			ofx, ofy;
		int			h;
		int			dqa, dqb;
		int			zsf3, zsf4;
		int			flag;
	} n;
	unsigned int r[32];
	PAIR p[32];
} psxCP2Ctrl;

typedef union {
	struct {
		unsigned int	Index, Random, EntryLo0, BPC,
			Context, BDA, PIDMask, DCIC,
			BadVAddr, BDAM, EntryHi, BPCM,
			Status, Cause, EPC, PRid,
			Config, LLAddr, WatchLO, WatchHI,
			XContext, Reserved1, Reserved2, Reserved3,
			Reserved4, Reserved5, ECC, CacheErr,
			TagLo, TagHi, ErrorEPC, Reserved6;
	} n;
	unsigned int r[32];
} psxCP0Regs;

typedef struct
{
	psxCP0Regs CP0;  /* Coprocessor0 Registers */
	psxCP2Data CP2D; /* Cop2 data registers */
	psxCP2Ctrl CP2C; /* Cop2 control registers */
} GTERegisters;

extern GTERegisters gteRegs;

//Externals
extern int LIM(int value, int max, int min, unsigned int flag);

/* Data Registers mtc2 mfc2 */
#define C2_VX0		(gteRegs.CP2D.p[ 0 ].sw.l)
#define C2_VY0		(gteRegs.CP2D.p[ 0 ].sw.h)
#define C2_VZ0		(gteRegs.CP2D.p[ 1 ].sw.l)
#define C2_VX1		(gteRegs.CP2D.p[ 2 ].w.l)
#define C2_VY1		(gteRegs.CP2D.p[ 2 ].w.h)
#define C2_VZ1		(gteRegs.CP2D.p[ 3 ].w.l)
#define C2_VX2		(gteRegs.CP2D.p[ 4 ].w.l)
#define C2_VY2		(gteRegs.CP2D.p[ 4 ].w.h)
#define C2_VZ2		(gteRegs.CP2D.p[ 5 ].w.l)
#define C2_R		(gteRegs.CP2D.p[ 6 ].b.l)
#define C2_G		(gteRegs.CP2D.p[ 6 ].b.h)
#define C2_B		(gteRegs.CP2D.p[ 6 ].b.h2)
#define C2_CODE		(gteRegs.CP2D.p[ 6 ].b.h3)
#define C2_OTZ		(gteRegs.CP2D.p[ 7 ].w.l)
#define C2_IR0		(gteRegs.CP2D.p[ 8 ].sw.l)
#define C2_IR1		(gteRegs.CP2D.p[ 9 ].sw.l)
#define C2_IR2		(gteRegs.CP2D.p[ 10 ].sw.l)
#define C2_IR3		(gteRegs.CP2D.p[ 11 ].sw.l)
#define C2_SXY0		(gteRegs.CP2D.p[ 12 ].d)
#define C2_SX0		(gteRegs.CP2D.p[ 12 ].sw.l)
#define C2_SY0		(gteRegs.CP2D.p[ 12 ].sw.h)
#define C2_SXY1		(gteRegs.CP2D.p[ 13 ].d)
#define C2_SX1		(gteRegs.CP2D.p[ 13 ].sw.l)
#define C2_SY1		(gteRegs.CP2D.p[ 13 ].sw.h)
#define C2_SXY2		(gteRegs.CP2D.p[ 14 ].d)
#define C2_SX2		(gteRegs.CP2D.p[ 14 ].sw.l)
#define C2_SY2		(gteRegs.CP2D.p[ 14 ].sw.h)
#define C2_SXYP		(gteRegs.CP2D.p[ 15 ].d)
#define C2_SXP		(gteRegs.CP2D.p[ 15 ].sw.l)
#define C2_SYP		(gteRegs.CP2D.p[ 15 ].sw.h)
#define C2_SZ0		(gteRegs.CP2D.p[ 16 ].w.l)
#define C2_SZ1		(gteRegs.CP2D.p[ 17 ].w.l)
#define C2_SZ2		(gteRegs.CP2D.p[ 18 ].w.l)
#define C2_SZ3		(gteRegs.CP2D.p[ 19 ].w.l)
#define C2_RGB0		(gteRegs.CP2D.p[ 20 ].d)
#define C2_R0		(gteRegs.CP2D.p[ 20 ].b.l)
#define C2_G0		(gteRegs.CP2D.p[ 20 ].b.h)
#define C2_B0		(gteRegs.CP2D.p[ 20 ].b.h2)
#define C2_CD0		(gteRegs.CP2D.p[ 20 ].b.h3)
#define C2_RGB1		(gteRegs.CP2D.p[ 21 ].d)
#define C2_R1		(gteRegs.CP2D.p[ 21 ].b.l)
#define C2_G1		(gteRegs.CP2D.p[ 21 ].b.h)
#define C2_B1		(gteRegs.CP2D.p[ 21 ].b.h2)
#define C2_CD1		(gteRegs.CP2D.p[ 21 ].b.h3)
#define C2_RGB2		(gteRegs.CP2D.p[ 22 ].d)
#define C2_R2		(gteRegs.CP2D.p[ 22 ].b.l)
#define C2_G2		(gteRegs.CP2D.p[ 22 ].b.h)
#define C2_B2		(gteRegs.CP2D.p[ 22 ].b.h2)
#define C2_CD2		(gteRegs.CP2D.p[ 22 ].b.h3)
#define C2_RES1		(gteRegs.CP2D.p[ 23 ].d)
#define C2_MAC0		(gteRegs.CP2D.p[ 24 ].sd)
#define C2_MAC1		(gteRegs.CP2D.p[ 25 ].sd)
#define C2_MAC2		(gteRegs.CP2D.p[ 26 ].sd)
#define C2_MAC3		(gteRegs.CP2D.p[ 27 ].sd)
#define C2_IRGB		(gteRegs.CP2D.p[ 28 ].d)
#define C2_ORGB		(gteRegs.CP2D.p[ 29 ].d)
#define C2_LZCS		(gteRegs.CP2D.p[ 30 ].d)
#define C2_LZCR		(gteRegs.CP2D.p[ 31 ].d)

/* Control Registers ctc2 cfc2*/

#define C2_R11		(gteRegs.CP2C.p[ 0 ].sw.l)
#define C2_R12		(gteRegs.CP2C.p[ 0 ].sw.h)
#define C2_R13		(gteRegs.CP2C.p[ 1 ].sw.l)
#define C2_R21		(gteRegs.CP2C.p[ 1 ].sw.h)
#define C2_R22		(gteRegs.CP2C.p[ 2 ].sw.l)
#define C2_R23		(gteRegs.CP2C.p[ 2 ].sw.h)
#define C2_R31		(gteRegs.CP2C.p[ 3 ].sw.l)
#define C2_R32		(gteRegs.CP2C.p[ 3 ].sw.h)
#define C2_R33		(gteRegs.CP2C.p[ 4 ].sw.l)
#define C2_TRX		(gteRegs.CP2C.p[ 5 ].sd)
#define C2_TRY		(gteRegs.CP2C.p[ 6 ].sd)
#define C2_TRZ		(gteRegs.CP2C.p[ 7 ].sd)
#define C2_L11		(gteRegs.CP2C.p[ 8 ].sw.l)
#define C2_L12		(gteRegs.CP2C.p[ 8 ].sw.h)
#define C2_L13		(gteRegs.CP2C.p[ 9 ].sw.l)
#define C2_L21		(gteRegs.CP2C.p[ 9 ].sw.h)
#define C2_L22		(gteRegs.CP2C.p[ 10 ].sw.l)
#define C2_L23		(gteRegs.CP2C.p[ 10 ].sw.h)
#define C2_L31		(gteRegs.CP2C.p[ 11 ].sw.l)
#define C2_L32		(gteRegs.CP2C.p[ 11 ].sw.h)
#define C2_L33		(gteRegs.CP2C.p[ 12 ].sw.l)
#define C2_RBK		(gteRegs.CP2C.p[ 13 ].sd)
#define C2_GBK		(gteRegs.CP2C.p[ 14 ].sd)
#define C2_BBK		(gteRegs.CP2C.p[ 15 ].sd)
#define C2_LR1		(gteRegs.CP2C.p[ 16 ].sw.l)
#define C2_LR2		(gteRegs.CP2C.p[ 16 ].sw.h)
#define C2_LR3		(gteRegs.CP2C.p[ 17 ].sw.l)
#define C2_LG1		(gteRegs.CP2C.p[ 17 ].sw.h)
#define C2_LG2		(gteRegs.CP2C.p[ 18 ].sw.l)
#define C2_LG3		(gteRegs.CP2C.p[ 18 ].sw.h)
#define C2_LB1		(gteRegs.CP2C.p[ 19 ].sw.l)
#define C2_LB2		(gteRegs.CP2C.p[ 19 ].sw.h)
#define C2_LB3		(gteRegs.CP2C.p[ 20 ].sw.l)
#define C2_RFC		(gteRegs.CP2C.p[ 21 ].sd)
#define C2_GFC		(gteRegs.CP2C.p[ 22 ].sd)
#define C2_BFC		(gteRegs.CP2C.p[ 23 ].sd)
#define C2_OFX		(gteRegs.CP2C.p[ 24 ].sd)
#define C2_OFY		(gteRegs.CP2C.p[ 25 ].sd)
#define C2_H		(gteRegs.CP2C.p[ 26 ].sw.l)
#define C2_DQA		(gteRegs.CP2C.p[ 27 ].sw.l)
#define C2_DQB		(gteRegs.CP2C.p[ 28 ].sd)
#define C2_ZSF3		(gteRegs.CP2C.p[ 29 ].sw.l)
#define C2_ZSF4		(gteRegs.CP2C.p[ 30 ].sw.l)
#define C2_FLAG		(gteRegs.CP2C.p[ 31 ].d)

#endif