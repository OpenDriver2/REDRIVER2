#include "LIBGTE.H"
#include <stdio.h>
#include "EMULATOR.H"
#include "EMULATOR_PRIVATE.H"
#include <assert.h>

#include "LIBMATH.H"

#include "INLINE_C.H"
#include "GTEREG.H"

#include "GTE/rcossin_tbl.h"
#include "GTE/ratan_tbl.h"
#include "GTE/sqrt_tbl.h"

#define ONE 4096
#define	FIXED(a)			((a) / ONE)

#define WIDE_SCREEN (0)

#if !defined(GTE_EXTERNAL)

GTERegisters gteRegs;

#define GTE_SF(op) ((op >> 19) & 1)
#define GTE_MX(op) ((op >> 17) & 3)
#define GTE_V(op) ((op >> 15) & 3)
#define GTE_CV(op) ((op >> 13) & 3)
#define GTE_LM(op) ((op >> 10) & 1)
#define GTE_FUNCT(op) (op & 63)

#define gteop(code) (code & 0x1ffffff)

#define VX(n) (n < 3 ? gteRegs.CP2D.p[ n << 1 ].sw.l : IR1)
#define VY(n) (n < 3 ? gteRegs.CP2D.p[ n << 1 ].sw.h : IR2)
#define VZ(n) (n < 3 ? gteRegs.CP2D.p[ (n << 1) + 1 ].sw.l : IR3)
#define MX11(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) ].sw.l : -R << 4)
#define MX12(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) ].sw.h : R << 4)
#define MX13(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 1 ].sw.l : IR0)
#define MX21(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 1 ].sw.h : R13)
#define MX22(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 2 ].sw.l : R13)
#define MX23(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 2 ].sw.h : R13)
#define MX31(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 3 ].sw.l : R22)
#define MX32(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 3 ].sw.h : R22)
#define MX33(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 4 ].sw.l : R22)
#define CV1(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 5 ].sd : 0)
#define CV2(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 6 ].sd : 0)
#define CV3(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 7 ].sd : 0)

#ifndef max
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif

void InitGeom()
{
    //_patch_gte(); //Extern
#if 0
    mfc0    $v0, SR
        lui     $v1, 0x4000
        or $v0, $v1
        mtc0    $v0, SR
#endif
    ZSF3 = 341;
    ZSF4 = 256;
    H = 1000;
    DQA = -98;
    DQB = 340;
    OFX = 0;
    OFY = 0;
}

void SetGeomOffset(int ofx, int ofy)
{
    OFX = ofx << 16;
    OFY = ofy << 16;
}

void SetGeomScreen(int h)
{
    H = h;
}

static int m_sf;
static long long m_mac0;
static long long m_mac3;

unsigned int gte_leadingzerocount(unsigned int lzcs) {
    unsigned int lzcr = 0;

    if ((lzcs & 0x80000000) == 0)
        lzcs = ~lzcs;

    while ((lzcs & 0x80000000) != 0) {
        lzcr++;
        lzcs <<= 1;
    }

    return lzcr;
}

int LIM(int value, int max, int min, unsigned int flag) {
    if (value > max) {
        FLAG |= flag;
        return max;
    }
    else if (value < min) {
        FLAG |= flag;
        return min;
    }

    return value;
}

unsigned int MFC2(int reg) 
{
	switch (reg) {
	case 1:
	case 3:
	case 5:
	case 8:
	case 9:
	case 10:
	case 11:
		gteRegs.CP2D.p[reg].d = (int)gteRegs.CP2D.p[reg].sw.l;
		break;

	case 7:
	case 16:
	case 17:
	case 18:
	case 19:
		gteRegs.CP2D.p[reg].d = (unsigned int)gteRegs.CP2D.p[reg].w.l;
		break;

	case 15:
		gteRegs.CP2D.p[reg].d = SXY2;
		break;

	case 28:
	case 29:
		gteRegs.CP2D.p[reg].d = LIM(IR1 >> 7, 0x1f, 0, 0) | (LIM(IR2 >> 7, 0x1f, 0, 0) << 5) | (LIM(IR3 >> 7, 0x1f, 0, 0) << 10);
		break;
	}

	return gteRegs.CP2D.p[reg].d;
}

int MFC2_S(int reg)
{
	// FIXME: Is that modifiers should be signed too?
	switch (reg) {
	case 1:
	case 3:
	case 5:
	case 8:
	case 9:
	case 10:
	case 11:
		gteRegs.CP2D.p[reg].d = (int)gteRegs.CP2D.p[reg].sw.l;
		break;

	case 7:
	case 16:
	case 17:
	case 18:
	case 19:
		gteRegs.CP2D.p[reg].d = (unsigned int)gteRegs.CP2D.p[reg].w.l;
		break;

	case 15:
		gteRegs.CP2D.p[reg].d = SXY2;
		break;

	case 28:
	case 29:
		gteRegs.CP2D.p[reg].d = LIM(IR1 >> 7, 0x1f, 0, 0) | (LIM(IR2 >> 7, 0x1f, 0, 0) << 5) | (LIM(IR3 >> 7, 0x1f, 0, 0) << 10);
		break;
	}

	return gteRegs.CP2D.p[reg].sd;
}

void MTC2(unsigned int value, int reg) {
	switch (reg) {
	case 15:
		SXY0 = SXY1;
		SXY1 = SXY2;
		SXY2 = value;
		break;

	case 28:
		IR1 = (value & 0x1f) << 7;
		IR2 = (value & 0x3e0) << 2;
		IR3 = (value & 0x7c00) >> 3;
		break;

	case 30:
		LZCR = gte_leadingzerocount(value);
		break;

	case 31:
		return;
	}

	gteRegs.CP2D.p[reg].d = value;
}

void MTC2_S(int value, int reg) {
	switch (reg) {
	case 15:
		SXY0 = SXY1;
		SXY1 = SXY2;
		SXY2 = value;
		break;

	case 28:
		IR1 = (value & 0x1f) << 7;
		IR2 = (value & 0x3e0) << 2;
		IR3 = (value & 0x7c00) >> 3;
		break;

	case 30:
		LZCR = gte_leadingzerocount(value);
		break;

	case 31:
		return;
	}

	gteRegs.CP2D.p[reg].sd = value;
}

void CTC2(unsigned int value, int reg) {
	switch (reg) {
	case 4:
	case 12:
	case 20:
	case 26:
	case 27:
	case 29:
	case 30:
		value = (int)(short)value;
		break;

	case 31:
		value = value & 0x7ffff000;
		if ((value & 0x7f87e000) != 0)
			value |= 0x80000000;
		break;
	}

	gteRegs.CP2C.p[reg].d = value;
}

void CTC2_S(int value, int reg) {
	switch (reg) {
	case 4:
	case 12:
	case 20:
	case 26:
	case 27:
	case 29:
	case 30:
		value = (int)(short)value;
		break;

	case 31:
		value = value & 0x7ffff000;
		if ((value & 0x7f87e000) != 0)
			value |= 0x80000000;
		break;
	}

	gteRegs.CP2C.p[reg].sd = value;
}

unsigned int CFC2(int reg)
{
	// TODO: correct functionality

	return gteRegs.CP2C.p[reg].d;
}

int CFC2_S(int reg)
{
	// TODO: correct functionality

	return gteRegs.CP2C.p[reg].sd;
}

#define _oB_ (gteRegs.GPR.r[_Rs_] + _Imm_)

inline long long gte_shift(long long a, int sf) {
    if (sf > 0)
        return a >> 12;
    else if (sf < 0)
        return a << 12;

    return a;
}

int BOUNDS(/*int44*/long long value, int max_flag, int min_flag) {
    if (value/*.positive_overflow()*/ > (long long)0x7ffffffffff)
        FLAG |= max_flag;

    if (value/*.negative_overflow()*/ < (long long)-0x8000000000)
        FLAG |= min_flag;

    return int(gte_shift(value/*.value()*/, m_sf));
}

unsigned int gte_divide(unsigned short numerator, unsigned short denominator)
{
    if (numerator < (denominator * 2))
    {
        static unsigned char table[] =
        {
            0xff, 0xfd, 0xfb, 0xf9, 0xf7, 0xf5, 0xf3, 0xf1, 0xef, 0xee, 0xec, 0xea, 0xe8, 0xe6, 0xe4, 0xe3,
            0xe1, 0xdf, 0xdd, 0xdc, 0xda, 0xd8, 0xd6, 0xd5, 0xd3, 0xd1, 0xd0, 0xce, 0xcd, 0xcb, 0xc9, 0xc8,
            0xc6, 0xc5, 0xc3, 0xc1, 0xc0, 0xbe, 0xbd, 0xbb, 0xba, 0xb8, 0xb7, 0xb5, 0xb4, 0xb2, 0xb1, 0xb0,
            0xae, 0xad, 0xab, 0xaa, 0xa9, 0xa7, 0xa6, 0xa4, 0xa3, 0xa2, 0xa0, 0x9f, 0x9e, 0x9c, 0x9b, 0x9a,
            0x99, 0x97, 0x96, 0x95, 0x94, 0x92, 0x91, 0x90, 0x8f, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x87, 0x86,
            0x85, 0x84, 0x83, 0x82, 0x81, 0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x77, 0x75, 0x74,
            0x73, 0x72, 0x71, 0x70, 0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64,
            0x63, 0x62, 0x61, 0x60, 0x5f, 0x5e, 0x5d, 0x5d, 0x5c, 0x5b, 0x5a, 0x59, 0x58, 0x57, 0x56, 0x55,
            0x54, 0x53, 0x53, 0x52, 0x51, 0x50, 0x4f, 0x4e, 0x4d, 0x4d, 0x4c, 0x4b, 0x4a, 0x49, 0x48, 0x48,
            0x47, 0x46, 0x45, 0x44, 0x43, 0x43, 0x42, 0x41, 0x40, 0x3f, 0x3f, 0x3e, 0x3d, 0x3c, 0x3c, 0x3b,
            0x3a, 0x39, 0x39, 0x38, 0x37, 0x36, 0x36, 0x35, 0x34, 0x33, 0x33, 0x32, 0x31, 0x31, 0x30, 0x2f,
            0x2e, 0x2e, 0x2d, 0x2c, 0x2c, 0x2b, 0x2a, 0x2a, 0x29, 0x28, 0x28, 0x27, 0x26, 0x26, 0x25, 0x24,
            0x24, 0x23, 0x22, 0x22, 0x21, 0x20, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a,
            0x19, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x12, 0x12, 0x11, 0x11,
            0x10, 0x0f, 0x0f, 0x0e, 0x0e, 0x0d, 0x0d, 0x0c, 0x0c, 0x0b, 0x0a, 0x0a, 0x09, 0x09, 0x08, 0x08,
            0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00,
            0x00
        };

        int shift = gte_leadingzerocount(denominator) - 16;

        int r1 = (denominator << shift) & 0x7fff;
        int r2 = table[((r1 + 0x40) >> 7)] + 0x101;
        int r3 = ((0x80 - (r2 * (r1 + 0x8000))) >> 8) & 0x1ffff;
        unsigned int reciprocal = ((r2 * r3) + 0x80) >> 8;

        return (unsigned int)((((unsigned long long)reciprocal * (numerator << shift)) + 0x8000) >> 16);
    }

    return 0xffffffff;
}

/* Setting bits 12 & 19-22 in FLAG does not set bit 31 */

int A1(/*int44*/long long a) { return BOUNDS(a, (1 << 31) | (1 << 30), (1 << 31) | (1 << 27)); }
int A2(/*int44*/long long a) { return BOUNDS(a, (1 << 31) | (1 << 29), (1 << 31) | (1 << 26)); }
int A3(/*int44*/long long a) { m_mac3 = a; return BOUNDS(a, (1 << 31) | (1 << 28), (1 << 31) | (1 << 25)); }
int Lm_B1(int a, int lm) { return LIM(a, 0x7fff, -0x8000 * !lm, (1 << 31) | (1 << 24)); }
int Lm_B2(int a, int lm) { return LIM(a, 0x7fff, -0x8000 * !lm, (1 << 31) | (1 << 23)); }
int Lm_B3(int a, int lm) { return LIM(a, 0x7fff, -0x8000 * !lm, (1 << 22)); }

int Lm_B3_sf(long long value, int sf, int lm) {
    int value_sf = int(gte_shift(value, sf));
    int value_12 = int(gte_shift(value, 1));
    int max = 0x7fff;
    int min = 0;
    if (lm == 0)
        min = -0x8000;

    if (value_12 < -0x8000 || value_12 > 0x7fff)
        FLAG |= (1 << 22);

    if (value_sf > max)
        return max;
    else if (value_sf < min)
        return min;

    return value_sf;
}

int Lm_C1(int a) { return LIM(a, 0x00ff, 0x0000, (1 << 21)); }
int Lm_C2(int a) { return LIM(a, 0x00ff, 0x0000, (1 << 20)); }
int Lm_C3(int a) { return LIM(a, 0x00ff, 0x0000, (1 << 19)); }
int Lm_D(long long a, int sf) { return LIM(int(gte_shift(a, sf)), 0xffff, 0x0000, (1 << 31) | (1 << 18)); }

unsigned int Lm_E(unsigned int result) {
    if (result == 0xffffffff) {
        FLAG |= (1 << 31) | (1 << 17);
        return 0x1ffff;
    }

    if (result > 0x1ffff)
        return 0x1ffff;

    return result;
}

long long F(long long a) {
    m_mac0 = a;

    if (a > 0x7fffffffLL)
        FLAG |= (1 << 31) | (1 << 16);

    if (a < -0x80000000LL)
        FLAG |= (1 << 31) | (1 << 15);

    return a;
}

int Lm_G1(long long a) {
    if (a > 0x3ff) {
        FLAG |= (1 << 31) | (1 << 14);
        return 0x3ff;
    }
    if (a < -0x400) {
        FLAG |= (1 << 31) | (1 << 14);
        return -0x400;
    }

    return int(a);
}

int Lm_G2(long long a) {
    if (a > 0x3ff) {
        FLAG |= (1 << 31) | (1 << 13);
        return 0x3ff;
    }

    if (a < -0x400) {
        FLAG |= (1 << 31) | (1 << 13);
        return -0x400;
    }

    return int(a);
}

int Lm_G1_ia(long long a) {
    if (a > 0x3ffffff)
        return 0x3ffffff;

    if (a < -0x4000000)
        return -0x4000000;

    return int(a);
}

int Lm_G2_ia(long long a) {
    if (a > 0x3ffffff)
        return 0x3ffffff;

    if (a < -0x4000000)
        return -0x4000000;

    return int(a);
}

int Lm_H(long long value, int sf) {
    long long value_sf = gte_shift(value, sf);
    int value_12 = int(gte_shift(value, 1));
    int max = 0x1000;
    int min = 0x0000;

    if (value_sf < min || value_sf > max)
        FLAG |= (1 << 12);

    if (value_12 > max)
        return max;

    if (value_12 < min)
        return min;

    return value_12;
}

#ifdef PGXP
PGXPVector3D g_FP_SXYZ0; // direct access PGXP without table lookup
PGXPVector3D g_FP_SXYZ1;
PGXPVector3D g_FP_SXYZ2;

PGXPVData g_pgxpCache[65535];
int g_pgxpVertexIndex = 0;
bool g_pgxpTransformed = false;

void PGXP_ClearCache()
{
	g_pgxpVertexIndex = 0;
}

ushort PGXP_GetIndex()
{
	if (g_pgxpTransformed)
	{
		g_pgxpTransformed = false;
		return g_pgxpVertexIndex;
	}
	
	return 0xFFFF;
}

// sets copy of cached vertex data to out
bool PGXP_GetCacheData(PGXPVData& out, uint lookup, ushort indexhint)
{
	if (indexhint == 0xFFFF)
	{
		out.px = 0.0f;
		out.py = 0.0f;
		out.pz = 1.0f;
		return false;
	}

	int start = indexhint - 8; // index hint allows us to start from specific index

	for (int i = max(0, start); i < g_pgxpVertexIndex; i++)
	{
		if (g_pgxpCache[i].lookup == lookup)
		{
			out.px = g_pgxpCache[i].px;
			out.py = g_pgxpCache[i].py;
			out.pz = g_pgxpCache[i].pz;

			return true;
		}
	}

	out.px = 0.0f;
	out.py = 0.0f;
	out.pz = 1.0f;

	return false;
}

#endif // PGXP

int docop2(int op) {
    int v;
    int lm;
    int cv;
    int mx;
    int h_over_sz3 = 0;

    lm = GTE_LM(gteop(op));
    m_sf = GTE_SF(gteop(op));

    FLAG = 0;

    switch (GTE_FUNCT(gteop(op))) {
    case 0x00:
    case 0x01:
#ifdef GTE_LOG
        GTELOG("%08x RTPS", op);
#endif

        MAC1 = A1(/*int44*/(long long)((long long)TRX << 12) + (R11 * VX0) + (R12 * VY0) + (R13 * VZ0));
        MAC2 = A2(/*int44*/(long long)((long long)TRY << 12) + (R21 * VX0) + (R22 * VY0) + (R23 * VZ0));
        MAC3 = A3(/*int44*/(long long)((long long)TRZ << 12) + (R31 * VX0) + (R32 * VY0) + (R33 * VZ0));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3_sf(m_mac3, m_sf, lm);
        SZ0 = SZ1;
        SZ1 = SZ2;
        SZ2 = SZ3;
        SZ3 = Lm_D(m_mac3, 1);
        h_over_sz3 = Lm_E(gte_divide(H, SZ3));
        SXY0 = SXY1;
        SXY1 = SXY2;
        SX2 = int(Lm_G1(F((long long)OFX + ((long long)IR1 * h_over_sz3)) >> 16));
        SY2 = int(Lm_G2(F((long long)OFY + ((long long)IR2 * h_over_sz3)) >> 16));

#if defined(PGXP)
		{
			g_FP_SXYZ0 = g_FP_SXYZ1;
			g_FP_SXYZ1 = g_FP_SXYZ2;

			g_FP_SXYZ2.px = (double(OFX) + double(float(IR1) * float(h_over_sz3))) / float(1 << 16);
			g_FP_SXYZ2.py = (double(OFY) + double(float(IR2) * float(h_over_sz3))) / float(1 << 16);
			g_FP_SXYZ2.pz = float(max(SZ3, H / 2)) / float(1 << 16);

			// make half-float equivalents
			g_FP_SXYZ2.x = g_FP_SXYZ2.px;
			g_FP_SXYZ2.y = g_FP_SXYZ2.py;
			g_FP_SXYZ2.z = g_FP_SXYZ2.pz;

			PGXPVData vdata;
			vdata.lookup = PGXP_LOOKUP_VALUE(g_FP_SXYZ2.x, g_FP_SXYZ2.y);		// hash short values
			vdata.px = g_FP_SXYZ2.px;
			vdata.py = g_FP_SXYZ2.py;
			vdata.pz = g_FP_SXYZ2.pz;

			g_pgxpCache[g_pgxpVertexIndex++] = vdata;
			g_pgxpTransformed = true;
		}
#endif
        MAC0 = int(F((long long)DQB + ((long long)DQA * h_over_sz3)));
        IR0 = Lm_H(m_mac0, 1);
        return 1;

    case 0x06:
#ifdef GTE_LOG
        GTELOG("%08x NCLIP", op);
#endif

#ifdef PGXP
		{
			float fSX0 = g_FP_SXYZ0.px;
			float fSY0 = g_FP_SXYZ0.py;

			float fSX1 = g_FP_SXYZ1.px;
			float fSY1 = g_FP_SXYZ1.py;

			float fSX2 = g_FP_SXYZ2.px;
			float fSY2 = g_FP_SXYZ2.py;

			float nclip = (fSX0 * fSY1) + (fSX1 * fSY2) + (fSX2 * fSY0) - (fSX0 * fSY2) - (fSX1 * fSY0) - (fSX2 * fSY1);

			float absNclip = fabs(nclip);

			if ((0.1f < absNclip) && (absNclip < 1.0f))
				nclip += (nclip < 0.0f) ? -1.0f : 1.0f;

			MAC0 = nclip;
		}
#else
		MAC0 = int(F((long long)(SX0 * SY1) + (SX1 * SY2) + (SX2 * SY0) - (SX0 * SY2) - (SX1 * SY0) - (SX2 * SY1)));
#endif
		FLAG = 0;
        return 1;

    case 0x0c:
#ifdef GTE_LOG
        GTELOG("%08x OP", op);
#endif

        MAC1 = A1((long long)(R22 * IR3) - (R33 * IR2));
        MAC2 = A2((long long)(R33 * IR1) - (R11 * IR3));
        MAC3 = A3((long long)(R11 * IR2) - (R22 * IR1));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        return 1;

    case 0x10:
#ifdef GTE_LOG
        GTELOG("%08x DPCS", op);
#endif

        MAC1 = A1((R << 16) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - (R << 16)), 0)));
        MAC2 = A2((G << 16) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - (G << 16)), 0)));
        MAC3 = A3((B << 16) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - (B << 16)), 0)));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x11:
#ifdef GTE_LOG
        GTELOG("%08x INTPL", op);
#endif

        MAC1 = A1((IR1 << 12) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - (IR1 << 12)), 0)));
        MAC2 = A2((IR2 << 12) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - (IR2 << 12)), 0)));
        MAC3 = A3((IR3 << 12) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - (IR3 << 12)), 0)));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x12:
#ifdef GTE_LOG
        GTELOG("%08x MVMVA", op);
#endif

        mx = GTE_MX(gteop(op));
        v = GTE_V(gteop(op));
        cv = GTE_CV(gteop(op));

        switch (cv) {
        case 2:
            MAC1 = A1((long long)(MX12(mx) * VY(v)) + (MX13(mx) * VZ(v)));
            MAC2 = A2((long long)(MX22(mx) * VY(v)) + (MX23(mx) * VZ(v)));
            MAC3 = A3((long long)(MX32(mx) * VY(v)) + (MX33(mx) * VZ(v)));
            Lm_B1(A1(((long long)CV1(cv) << 12) + (MX11(mx) * VX(v))), 0);
            Lm_B2(A2(((long long)CV2(cv) << 12) + (MX21(mx) * VX(v))), 0);
            Lm_B3(A3(((long long)CV3(cv) << 12) + (MX31(mx) * VX(v))), 0);
            break;

        default:
            MAC1 = A1(/*int44*/(long long)((long long)CV1(cv) << 12) + (MX11(mx) * VX(v)) + (MX12(mx) * VY(v)) + (MX13(mx) * VZ(v)));
            MAC2 = A2(/*int44*/(long long)((long long)CV2(cv) << 12) + (MX21(mx) * VX(v)) + (MX22(mx) * VY(v)) + (MX23(mx) * VZ(v)));
            MAC3 = A3(/*int44*/(long long)((long long)CV3(cv) << 12) + (MX31(mx) * VX(v)) + (MX32(mx) * VY(v)) + (MX33(mx) * VZ(v)));
            break;
        }

        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        return 1;

    case 0x13:
#ifdef GTE_LOG
        GTELOG("%08x NCDS", op);
#endif

        MAC1 = A1((long long)(L11 * VX0) + (L12 * VY0) + (L13 * VZ0));
        MAC2 = A2((long long)(L21 * VX0) + (L22 * VY0) + (L23 * VZ0));
        MAC3 = A3((long long)(L31 * VX0) + (L32 * VY0) + (L33 * VZ0));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
        MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
        MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
        MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
        MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x14:
#ifdef GTE_LOG
        GTELOG("%08x CDP", op);
#endif

        MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
        MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
        MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
        MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
        MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x16:
#ifdef GTE_LOG
        GTELOG("%08x NCDT", op);
#endif

        for (v = 0; v < 3; v++) {
            MAC1 = A1((long long)(L11 * VX(v)) + (L12 * VY(v)) + (L13 * VZ(v)));
            MAC2 = A2((long long)(L21 * VX(v)) + (L22 * VY(v)) + (L23 * VZ(v)));
            MAC3 = A3((long long)(L31 * VX(v)) + (L32 * VY(v)) + (L33 * VZ(v)));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
            MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
            MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
            MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
            MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            RGB0 = RGB1;
            RGB1 = RGB2;
            CD2 = CODE;
            R2 = Lm_C1(MAC1 >> 4);
            G2 = Lm_C2(MAC2 >> 4);
            B2 = Lm_C3(MAC3 >> 4);
        }
        return 1;

    case 0x1b:
#ifdef GTE_LOG
        GTELOG("%08x NCCS", op);
#endif

        MAC1 = A1((long long)(L11 * VX0) + (L12 * VY0) + (L13 * VZ0));
        MAC2 = A2((long long)(L21 * VX0) + (L22 * VY0) + (L23 * VZ0));
        MAC3 = A3((long long)(L31 * VX0) + (L32 * VY0) + (L33 * VZ0));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
        MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
        MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1((R << 4) * IR1);
        MAC2 = A2((G << 4) * IR2);
        MAC3 = A3((B << 4) * IR3);
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x1c:
#ifdef GTE_LOG
        GTELOG("%08x CC", op);
#endif

        MAC1 = A1(/*int44*/(long long)(((long long)RBK) << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
        MAC2 = A2(/*int44*/(long long)(((long long)GBK) << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
        MAC3 = A3(/*int44*/(long long)(((long long)BBK) << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1((R << 4) * IR1);
        MAC2 = A2((G << 4) * IR2);
        MAC3 = A3((B << 4) * IR3);
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x1e:
#ifdef GTE_LOG
        GTELOG("%08x NCS", op);
#endif

        MAC1 = A1((long long)(L11 * VX0) + (L12 * VY0) + (L13 * VZ0));
        MAC2 = A2((long long)(L21 * VX0) + (L22 * VY0) + (L23 * VZ0));
        MAC3 = A3((long long)(L31 * VX0) + (L32 * VY0) + (L33 * VZ0));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
        MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
        MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x20:
#ifdef GTE_LOG
        GTELOG("%08x NCT", op);
#endif

        for (v = 0; v < 3; v++) {
            MAC1 = A1((long long)(L11 * VX(v)) + (L12 * VY(v)) + (L13 * VZ(v)));
            MAC2 = A2((long long)(L21 * VX(v)) + (L22 * VY(v)) + (L23 * VZ(v)));
            MAC3 = A3((long long)(L31 * VX(v)) + (L32 * VY(v)) + (L33 * VZ(v)));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
            MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
            MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            RGB0 = RGB1;
            RGB1 = RGB2;
            CD2 = CODE;
            R2 = Lm_C1(MAC1 >> 4);
            G2 = Lm_C2(MAC2 >> 4);
            B2 = Lm_C3(MAC3 >> 4);
        }
        return 1;

    case 0x28:
#ifdef GTE_LOG
        GTELOG("%08x SQR", op);
#endif

        MAC1 = A1(IR1 * IR1);
        MAC2 = A2(IR2 * IR2);
        MAC3 = A3(IR3 * IR3);
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        return 1;

    case 0x29:
#ifdef GTE_LOG
        GTELOG("%08x DPCL", op);
#endif

        MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
        MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
        MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x2a:
#ifdef GTE_LOG
        GTELOG("%08x DPCT", op);
#endif

        for (v = 0; v < 3; v++) {
            MAC1 = A1((R0 << 16) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - (R0 << 16)), 0)));
            MAC2 = A2((G0 << 16) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - (G0 << 16)), 0)));
            MAC3 = A3((B0 << 16) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - (B0 << 16)), 0)));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            RGB0 = RGB1;
            RGB1 = RGB2;
            CD2 = CODE;
            R2 = Lm_C1(MAC1 >> 4);
            G2 = Lm_C2(MAC2 >> 4);
            B2 = Lm_C3(MAC3 >> 4);
        }
        return 1;

    case 0x2d:
#ifdef GTE_LOG
        GTELOG("%08x AVSZ3", op);
#endif

        MAC0 = int(F((long long)(ZSF3 * SZ1) + (ZSF3 * SZ2) + (ZSF3 * SZ3)));
        OTZ = Lm_D(m_mac0, 1);
        return 1;

    case 0x2e:
#ifdef GTE_LOG
        GTELOG("%08x AVSZ4", op);
#endif

        MAC0 = int(F((long long)(ZSF4 * SZ0) + (ZSF4 * SZ1) + (ZSF4 * SZ2) + (ZSF4 * SZ3)));
        OTZ = Lm_D(m_mac0, 1);
        return 1;

    case 0x30:
#ifdef GTE_LOG
        GTELOG("%08x RTPT", op);
#endif

        for (v = 0; v < 3; v++) 
		{
            MAC1 = A1(/*int44*/(long long)((long long)TRX << 12) + (R11 * VX(v)) + (R12 * VY(v)) + (R13 * VZ(v)));
            MAC2 = A2(/*int44*/(long long)((long long)TRY << 12) + (R21 * VX(v)) + (R22 * VY(v)) + (R23 * VZ(v)));
            MAC3 = A3(/*int44*/(long long)((long long)TRZ << 12) + (R31 * VX(v)) + (R32 * VY(v)) + (R33 * VZ(v)));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3_sf(m_mac3, m_sf, lm);
            SZ0 = SZ1;
            SZ1 = SZ2;
            SZ2 = SZ3;
            SZ3 = Lm_D(m_mac3, 1);
            h_over_sz3 = Lm_E(gte_divide(H, SZ3));
            SXY0 = SXY1;
            SXY1 = SXY2;
            SX2 = Lm_G1(F((long long)OFX + ((long long)IR1 * h_over_sz3)) >> 16);
            SY2 = Lm_G2(F((long long)OFY + ((long long)IR2 * h_over_sz3)) >> 16);

#if defined(PGXP)
			g_FP_SXYZ0 = g_FP_SXYZ1;
			g_FP_SXYZ1 = g_FP_SXYZ2;

			g_FP_SXYZ2.px = (double(OFX) + double(float(IR1) * float(h_over_sz3))) / float(1 << 16);
			g_FP_SXYZ2.py = (double(OFY) + double(float(IR2) * float(h_over_sz3))) / float(1 << 16);
			g_FP_SXYZ2.pz = float(max(SZ3, H / 2)) / float(1 << 16);

			// make half-float equivalents
			g_FP_SXYZ2.x = g_FP_SXYZ2.px;
			g_FP_SXYZ2.y = g_FP_SXYZ2.py;
			g_FP_SXYZ2.z = g_FP_SXYZ2.pz;

			PGXPVData vdata;
			vdata.lookup = PGXP_LOOKUP_VALUE(g_FP_SXYZ2.x, g_FP_SXYZ2.y);		// hash short values
			vdata.px = g_FP_SXYZ2.px;
			vdata.py = g_FP_SXYZ2.py;
			vdata.pz = g_FP_SXYZ2.pz;

			g_pgxpCache[g_pgxpVertexIndex++] = vdata;
			g_pgxpTransformed = true;
#endif
        }

        MAC0 = int(F((long long)DQB + ((long long)DQA * h_over_sz3)));
        IR0 = Lm_H(m_mac0, 1);
        return 1;

    case 0x3d:
#ifdef GTE_LOG
        GTELOG("%08x GPF", op);
#endif

        MAC1 = A1(IR0 * IR1);
        MAC2 = A2(IR0 * IR2);
        MAC3 = A3(IR0 * IR3);
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x3e:
#ifdef GTE_LOG
        GTELOG("%08x GPL", op);
#endif

        MAC1 = A1(gte_shift(MAC1, -m_sf) + (IR0 * IR1));
        MAC2 = A2(gte_shift(MAC2, -m_sf) + (IR0 * IR2));
        MAC3 = A3(gte_shift(MAC3, -m_sf) + (IR0 * IR3));
        IR1 = Lm_B1(MAC1, lm);
        IR2 = Lm_B2(MAC2, lm);
        IR3 = Lm_B3(MAC3, lm);
        RGB0 = RGB1;
        RGB1 = RGB2;
        CD2 = CODE;
        R2 = Lm_C1(MAC1 >> 4);
        G2 = Lm_C2(MAC2 >> 4);
        B2 = Lm_C3(MAC3 >> 4);
        return 1;

    case 0x3f:
#ifdef GTE_LOG
        GTELOG("%08x NCCT", op);
#endif

        for (v = 0; v < 3; v++) {
            MAC1 = A1((long long)(L11 * VX(v)) + (L12 * VY(v)) + (L13 * VZ(v)));
            MAC2 = A2((long long)(L21 * VX(v)) + (L22 * VY(v)) + (L23 * VZ(v)));
            MAC3 = A3((long long)(L31 * VX(v)) + (L32 * VY(v)) + (L33 * VZ(v)));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
            MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
            MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            MAC1 = A1((R << 4) * IR1);
            MAC2 = A2((G << 4) * IR2);
            MAC3 = A3((B << 4) * IR3);
            IR1 = Lm_B1(MAC1, lm);
            IR2 = Lm_B2(MAC2, lm);
            IR3 = Lm_B3(MAC3, lm);
            RGB0 = RGB1;
            RGB1 = RGB2;
            CD2 = CODE;
            R2 = Lm_C1(MAC1 >> 4);
            G2 = Lm_C2(MAC2 >> 4);
            B2 = Lm_C3(MAC3 >> 4);
        }
        return 1;
    }

    return 0;
}

#else

// Mednafen/BeetlePSX GTE
#include "GTE/gte.h"
#include "GTE/pgxp/pgxp_main.h"

unsigned int gte_leadingzerocount(unsigned int lzcs) {
	unsigned int lzcr = 0;

	if ((lzcs & 0x80000000) == 0)
		lzcs = ~lzcs;

	while ((lzcs & 0x80000000) != 0) {
		lzcr++;
		lzcs <<= 1;
	}

	return lzcr;
}

bool g_Initialized = false;

void InitGeom()
{
	if (!g_Initialized)
	{
		GTE_Init();
		GTE_Power();

		g_Initialized = true;
		PGXP_Init();

		PGXP_EnableModes(PGXP_MODE_MEMORY | PGXP_VERTEX_CACHE | PGXP_TEXTURE_CORRECTION);
	}

	GTE_WriteCR(29, 341);		// ZSF3, ZSF4
	GTE_WriteCR(30, 256);
	GTE_WriteCR(26, 1000);		// H

	CTC2_S(-98, 27);	// DQA
	CTC2_S(340, 28);	// DQB

	CTC2(24, 0);		// OFX, OFY
	CTC2(25, 0);
}

void SetGeomOffset(int ofx, int ofy)
{
	CTC2(*(uint*)&ofx, 24);
	CTC2(*(uint*)&ofy, 25);
}

void SetGeomScreen(int h)
{
	CTC2(*(uint*)&h, 26);
}

int docop2(int op)
{
	return GTE_Instruction(*(uint*)&op);
}

void MTC2(unsigned int value, int reg)
{
	GTE_WriteDR(reg, value);
}

void MTC2_S(int value, int reg)
{
	GTE_WriteDR(reg, *(uint*)&value);
}

uint MFC2(int reg)
{
	return GTE_ReadDR(reg);
}

void CTC2(unsigned int value, int reg)
{
	GTE_WriteCR(reg, value);
}

void CTC2_S(int value, int reg)
{
	GTE_WriteCR(reg, *(uint*)&value);
}

uint CFC2(int reg)
{
	return GTE_ReadCR(reg);
}

int CFC2_S(int reg)
{
	uint value = CFC2(reg);
	return *(int*)&value;
}

#endif // OLD_GTE

void SetRotMatrix(MATRIX* m)
{
	gte_SetRotMatrix(m);
}

void SetLightMatrix(MATRIX* m)
{
	gte_SetLightMatrix(m);
}

void SetColorMatrix(MATRIX* m)
{
	gte_SetColorMatrix(m);
}

void SetTransMatrix(MATRIX* m)
{
	gte_SetTransMatrix(m);
}

#define MAX_NUM_MATRICES 20
int matrixLevel = 0;
MATRIX stack[MAX_NUM_MATRICES];//unk_410
MATRIX* currentMatrix = &stack[0];//unk_40C

void PushMatrix()
{
    if (matrixLevel < 20)
    {
        MATRIX* m = &stack[matrixLevel];//$t7

		gte_ReadRotMatrix(m);
		gte_sttr(m->t);

        currentMatrix++;
        matrixLevel++;
    }
    else
    {
        printf("Error: Can't push matrix,stack(max 20) is full!\n");
    }
}

void PopMatrix()
{
    if (matrixLevel > 0)
    {
        currentMatrix--;
        matrixLevel--;
        MATRIX* m = &stack[matrixLevel];//$t7

		gte_SetRotMatrix(m);
		gte_SetTransMatrix(m);
    }
    else
    {
        printf("Error: Can't pop matrix,stack is empty!\n");
    }
}

long RotTransPers(struct SVECTOR* v0, long* sxy, long* p, long* flag)
{
	gte_ldv0(v0);

    gte_rtps();

	gte_stsxy(sxy);
	gte_stdp(p);
	gte_stflg(flag);

	int z;
	gte_stsz(&z);

    return z >> 2;
}

void RotTrans(struct SVECTOR* v0, VECTOR* v1, long* flag)
{
	long lVar1;

	gte_ldv0(v0);

	docop2(0x480012);

	gte_stlvnl(v1);
	gte_stflg(flag);

	return;
}

void NormalColorDpq(struct SVECTOR* v0, struct CVECTOR* v1, long p, struct CVECTOR* v2)
{
    UNIMPLEMENTED();
}

void NormalColorCol(struct SVECTOR* v0, struct CVECTOR* v1, struct CVECTOR* v2)
{
    UNIMPLEMENTED();
}

long RotAverageNclip4(struct SVECTOR* v0, struct SVECTOR* v1, struct SVECTOR* v2, struct SVECTOR* v3, long* sxy0/*arg_10*/, long* sxy1/*arg_14*/, long* sxy2/*arg_18*/, long* sxy3/*arg_1C*/, long* p/*arg_20*/, long* otz/*arg_24*/, long* flag/*arg_28*/)
{
	gte_ldv3(v0,v1,v2);
    gte_rtpt();
	gte_stflg(flag);

    gte_nclip();

	int opz;
	gte_stopz(&opz);

    if (opz > 0)
    {
		gte_stsxy3(sxy0, sxy1, sxy2);

		gte_ldv0(v3);

        gte_rtps();

		gte_stsxy(sxy3);
		gte_stdp(p);
		gte_stflg(flag);

        gte_avsz4();

		gte_stotz(otz);
    }

    return opz;
}

// TODO: to INLINE_C EMULATOR macros

MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2)
{
#if 0
	gte_MulMatrix0(m0, m1, m2);
#else
	/* これでもm0==m2の時ヤバイ */
	int vx, vy, vz;
	MATRIX tmp;
	/* のでm0をtmpにコピー */
	if (m0 == m2) {
		tmp = *m0; m0 = &tmp;
	}

	vx = m1->m[0][0];
	vy = m1->m[1][0];
	vz = m1->m[2][0];
	m2->m[0][0] = FIXED(m0->m[0][0] * vx + m0->m[0][1] * vy + m0->m[0][2] * vz);
	m2->m[1][0] = FIXED(m0->m[1][0] * vx + m0->m[1][1] * vy + m0->m[1][2] * vz);
	m2->m[2][0] = FIXED(m0->m[2][0] * vx + m0->m[2][1] * vy + m0->m[2][2] * vz);
	vx = m1->m[0][1];
	vy = m1->m[1][1];
	vz = m1->m[2][1];
	m2->m[0][1] = FIXED(m0->m[0][0] * vx + m0->m[0][1] * vy + m0->m[0][2] * vz);
	m2->m[1][1] = FIXED(m0->m[1][0] * vx + m0->m[1][1] * vy + m0->m[1][2] * vz);
	m2->m[2][1] = FIXED(m0->m[2][0] * vx + m0->m[2][1] * vy + m0->m[2][2] * vz);
	vx = m1->m[0][2];
	vy = m1->m[1][2];
	vz = m1->m[2][2];
	m2->m[0][2] = FIXED(m0->m[0][0] * vx + m0->m[0][1] * vy + m0->m[0][2] * vz);
	m2->m[1][2] = FIXED(m0->m[1][0] * vx + m0->m[1][1] * vy + m0->m[1][2] * vz);
	m2->m[2][2] = FIXED(m0->m[2][0] * vx + m0->m[2][1] * vy + m0->m[2][2] * vz);
#endif

	return m2;
}

MATRIX* MulMatrix(MATRIX* m0, MATRIX* m1)
{
    UNIMPLEMENTED();
    return NULL;
}

MATRIX* MulMatrix2(MATRIX* m0, MATRIX* m1)
{
    UNIMPLEMENTED();
    return NULL;
}

void SetBackColor(long rbk, long gbk, long bbk)
{
    UNIMPLEMENTED();
}

void SetFarColor(long rfc, long gfc, long bfc)
{
    UNIMPLEMENTED();
}

#define	APPLYMATRIX(m,v0,v1)	{\
	int vx = v0->vx;\
	int vy = v0->vy;\
	int vz = v0->vz;\
	v1->vx = FIXED(m->m[0][0]*vx + m->m[0][1]*vy + m->m[0][2]*vz );\
	v1->vy = FIXED(m->m[1][0]*vx + m->m[1][1]*vy + m->m[1][2]*vz );\
	v1->vz = FIXED(m->m[2][0]*vx + m->m[2][1]*vy + m->m[2][2]*vz );\
}

VECTOR *ApplyMatrix(MATRIX *m, SVECTOR *v0, VECTOR *v1)
{
	APPLYMATRIX(m, v0, v1)
	return v1;
}

VECTOR *ApplyRotMatrix(SVECTOR *v0, VECTOR *v1)
{
	MATRIX temp;
	gte_ReadRotMatrix(&temp);

	MATRIX* m = &temp;

	APPLYMATRIX(m, v0, v1);
	return v1;
}

VECTOR *ApplyRotMatrixLV(VECTOR *v0, VECTOR *v1)
{
	MATRIX temp;
	gte_ReadRotMatrix(&temp);

	MATRIX* m = &temp;

	APPLYMATRIX(m, v0, v1);
	return v1;
}

SVECTOR *ApplyMatrixSV(MATRIX *m, SVECTOR *v0, SVECTOR *v1)
{
	APPLYMATRIX(m, v0, v1)
	return v1;
}

VECTOR *ApplyMatrixLV(MATRIX *m, VECTOR *v0, VECTOR *v1)
{
	APPLYMATRIX(m, v0, v1)
	return v1;
}

MATRIX* RotMatrix(struct SVECTOR* r, MATRIX* m)
{
	int c0,c1,c2;
	int s0,s1,s2;
	int s2p0,s2m0,c2p0,c2m0;
	int	s2c0,s2s0,c2c0,c2s0;

	c0=rcos(r->vx);
	c1=rcos(r->vy);
	c2=rcos(r->vz);
	s0=rsin(r->vx);
	s1=rsin(r->vy);
	s2=rsin(r->vz);
	s2p0=rsin( r->vz + r->vx );
	s2m0=rsin( r->vz - r->vx );
	c2p0=rcos( r->vz + r->vx );
	c2m0=rcos( r->vz - r->vx );
	s2c0 =	(s2p0+s2m0)/2;
	c2s0 =	(s2p0-s2m0)/2;
	s2s0 =	(c2m0-c2p0)/2;
	c2c0 =	(c2m0+c2p0)/2;

	m->m[0][0]=  FIXED(c2*c1);
	m->m[1][0]=  s2c0 + FIXED(c2s0*s1);
	m->m[2][0]=  s2s0 - FIXED(c2c0*s1);
	m->m[0][1]= -FIXED(s2*c1);
	m->m[1][1]=  c2c0 - FIXED(s2s0*s1);
	m->m[2][1]=  c2s0 + FIXED(s2c0*s1);
	m->m[0][2]=  s1;
	m->m[1][2]= -FIXED(c1*s0);
	m->m[2][2]=  FIXED(c1*c0);

	return m;
}

MATRIX* RotMatrixYXZ(struct SVECTOR* r, MATRIX* m)
{
	int iVar1;
	int iVar2;
	short sVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	uVar4 = (r->vx);

	if ((int)uVar4 < 0) 
	{
		iVar6 = *(int *)(rcossin_tbl + (-uVar4 & 0xfff) * 2);
		sVar3 = (short)iVar6;
		iVar5 = -(int)sVar3;
	}
	else 
	{
		iVar6 = *(int *)(rcossin_tbl + (uVar4 & 0xfff) * 2);
		iVar5 = (int)(short)iVar6;
		sVar3 = -(short)iVar6;
	}

	iVar6 = iVar6 >> 0x10;
	uVar4 = (r->vy);

	if ((int)uVar4 < 0) 
	{
		iVar7 = *(int *)(rcossin_tbl + (-uVar4 & 0xfff) * 2);
		iVar1 = -(int)(short)iVar7;
	}
	else
	{
		iVar7 = *(int *)(rcossin_tbl + (uVar4 & 0xfff) * 2);
		iVar1 = (int)(short)iVar7;
	}

	iVar7 = iVar7 >> 0x10;
	uVar4 = (r->vz);

	m->m[1][2] = sVar3;
	m->m[0][2] = FIXED(iVar1 * iVar6);
	sVar3 = FIXED(iVar7 * iVar6);

	if ((int)uVar4 < 0)
	{
		m->m[2][2] = sVar3;
		iVar8 = *(int *)(rcossin_tbl + (-uVar4 & 0xfff) * 2);
		iVar2 = -(int)(short)iVar8;
	}
	else
	{
		m->m[2][2] = sVar3;
		iVar8 = *(int *)(rcossin_tbl + (uVar4 & 0xfff) * 2);
		iVar2 = (int)(short)iVar8;
	}

	iVar8 = iVar8 >> 0x10;

	m->m[1][0] = FIXED(iVar2 * iVar6);
	m->m[1][1] = FIXED(iVar8 * iVar6);
	iVar6 = FIXED(iVar1 * iVar5);
	m->m[0][0] = FIXED(iVar7 * iVar8) + FIXED(iVar6 * iVar2);
	m->m[0][1] = FIXED(iVar6 * iVar8) - FIXED(iVar7 * iVar2);
	iVar5 = FIXED(iVar7 * iVar5);
	m->m[2][1] = FIXED(iVar1 * iVar2) + FIXED(iVar5 * iVar8);
	m->m[2][0] = FIXED(iVar5 * iVar2) - FIXED(iVar1 * iVar8);

	return m;
}

MATRIX* RotMatrixX(long r, MATRIX *m)
{
	int s0 = rsin(r);
	int c0 = rcos(r);
	int t1, t2;
	t1 = m->m[1][0];
	t2 = m->m[2][0];
	m->m[1][0] = FIXED(t1*c0 - t2 * s0);
	m->m[2][0] = FIXED(t1*s0 + t2 * c0);
	t1 = m->m[1][1];
	t2 = m->m[2][1];
	m->m[1][1] = FIXED(t1*c0 - t2 * s0);
	m->m[2][1] = FIXED(t1*s0 + t2 * c0);
	t1 = m->m[1][2];
	t2 = m->m[2][2];
	m->m[1][2] = FIXED(t1*c0 - t2 * s0);
	m->m[2][2] = FIXED(t1*s0 + t2 * c0);

	return m;
}

MATRIX* RotMatrixY(long r, MATRIX *m)
{
	int s0 = rsin(r);
	int c0 = rcos(r);
	int t1, t2;
	t1 = m->m[0][0];
	t2 = m->m[2][0];
	m->m[0][0] = FIXED(t1*c0 + t2 * s0);
	m->m[2][0] = FIXED(-t1 * s0 + t2 * c0);
	t1 = m->m[0][1];
	t2 = m->m[2][1];
	m->m[0][1] = FIXED(t1*c0 + t2 * s0);
	m->m[2][1] = FIXED(-t1 * s0 + t2 * c0);
	t1 = m->m[0][2];
	t2 = m->m[2][2];
	m->m[0][2] = FIXED(t1*c0 + t2 * s0);
	m->m[2][2] = FIXED(-t1 * s0 + t2 * c0);

	return m;
}

MATRIX* RotMatrixZ(long r, MATRIX *m)
{
	int s0 = rsin(r);
	int c0 = rcos(r);
	int t1,t2;
	t1 = m->m[0][0];
	t2 = m->m[1][0];
	m->m[0][0] = FIXED(t1*c0 - t2*s0);
	m->m[1][0] = FIXED(t1*s0 + t2*c0);
	t1 = m->m[0][1];
	t2 = m->m[1][1];
	m->m[0][1] = FIXED(t1*c0 - t2*s0);
	m->m[1][1] = FIXED(t1*s0 + t2*c0);
	t1 = m->m[0][2];
	t2 = m->m[1][2];
	m->m[0][2] = FIXED(t1*c0 - t2*s0);
	m->m[1][2] = FIXED(t1*s0 + t2*c0);

	return m;
}

MATRIX* RotMatrixZYX_gte(SVECTOR* r, MATRIX *m)
{
	// FIXME: make a proper function
	m->m[0][0] = 0x1000;
	m->m[0][1] = 0;
	m->m[0][2] = 0;

	m->m[1][0] = 0;
	m->m[1][1] = 0x1000;
	m->m[1][2] = 0;

	m->m[2][0] = 0;
	m->m[2][1] = 0;
	m->m[2][2] = 0x1000;

	RotMatrixX(r->vx, m);
	RotMatrixY(r->vy, m);
	RotMatrixZ(r->vz, m);
	return m;
}

MATRIX* TransMatrix(MATRIX* m, VECTOR* v)
{
	m->t[0] = v->vx;
	m->t[1] = v->vy;
	m->t[2] = v->vz;
    return m;
}

MATRIX* ScaleMatrix(MATRIX* m, VECTOR* v)
{
	m->m[0][0] = FIXED(m->m[0][0] * v->vx);
	m->m[0][1] = FIXED(m->m[0][1] * v->vx);
	m->m[0][2] = FIXED(m->m[0][2] * v->vx);
	m->m[1][0] = FIXED(m->m[1][0] * v->vy);
	m->m[1][1] = FIXED(m->m[1][1] * v->vy);
	m->m[1][2] = FIXED(m->m[1][2] * v->vy);
	m->m[2][0] = FIXED(m->m[2][0] * v->vz);
	m->m[2][1] = FIXED(m->m[2][1] * v->vz);
	m->m[2][2] = FIXED(m->m[2][2] * v->vz);
	return m;
}

void SetDQA(int iDQA)
{
	CTC2(*(uint*)&iDQA, 27);
}

void SetDQB(int iDQB)
{
	CTC2(*(uint*)&iDQB, 28);
}

void SetFogNear(long a, long h)
{
    //Error division by 0
    assert(h != 0);
    int depthQ = -(((a << 2) + a) << 6);
    assert(h != -1 && depthQ != 0x8000);
    SetDQA(depthQ / h);
    SetDQB(20971520);
}

int isin(int x)
{

#define qN	10
#define qA	12
#define B	19900
#define	C	3516

	int c, x2, y;

	c = x << (30 - qN);				// Semi-circle info into carry.
	x -= 1 << qN;					// sine -> cosine calc

	x = x << (31 - qN);				// Mask with PI
	x = x >> (31 - qN);				// Note: SIGNED shift! (to qN)

	x = x * x >> (2 * qN - 14);		// x=x^2 To Q14

	y = B - (x*C >> 14);			// B - x^2*C
	y = (1 << qA) - (x*y >> 16);	// A - x^2*(B-x^2*C)

	return c >= 0 ? y : -y;
}

int rsin(int a)
{
#if 0
	return isin(a);
#else
	if (a < 0)
		return -rcossin_tbl[(-a & 0xfffU) * 2];

	return rcossin_tbl[(a & 0xfffU) * 2];
#endif
}

int rcos(int a)
{
#if 0
	return isin(a + 1024);
#else
	if (a < 0) 
		return rcossin_tbl[(-a & 0xfffU) * 2 + 1];

	return rcossin_tbl[(a & 0xfffU) * 2 + 1];
#endif
}

long ratan2(long y, long x)
{
#if 0 // don't use it
	const double ONE_BY_2048 = 1.0 / 2048;
	const double CONV = 2048.0 / M_PI;

	float real = atan2(double(y) * ONE_BY_2048, double(x) * ONE_BY_2048);
	return real * CONV;
#else
	long v;
	ulong ang;

	bool xlt0 = x < 0;
	bool ylt0 = y < 0;

	if (x == 0 && y == 0)
		return 0;

	if (x < 0)
		x = -x;

	if (y < 0)
		y = -y;

	if (y < x)
	{
		if (((ulong)y & 0x7fe00000U) == 0)
			ang = (y * 1024) / x;
		else 
			ang = y / (x / 1024);

		v = ratan_tbl[ang];
	}
	else 
	{
		if(((ulong)x & 0x7fe00000U) == 0)
			ang = (x * 1024) / y;
		else 
			ang = x / (y / 1024);

		v = 1024 - ratan_tbl[ang];
	}

	if (xlt0)
		v = 2048 - v;
		
	if (ylt0)
		v = -v;

	return v;
#endif
}

long SquareRoot0(long a)
{
#if 1
	return sqrtl(a);
#else
	// working but bugged
	int idx;
	int lzcs;
	lzcs = gte_leadingzerocount(a);

	if (lzcs == 32)
		return 0;

	lzcs &= 0xfffffffe;

	if ((lzcs - 24) < 0)
		idx = a >> (24 - lzcs);
	else
		idx = a << (lzcs - 24);

	return (SQRT[idx-64] << ((31 - lzcs) >> 1)) >> 12;
#endif
}