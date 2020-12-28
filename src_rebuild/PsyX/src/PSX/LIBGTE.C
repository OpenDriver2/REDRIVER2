#include "LIBGTE.H"
#include <stdio.h>
#include "PSYX_RENDER.H"

#include <assert.h>

#include "ABS.H"
#include "INLINE_C.H"
#include "GTEMAC.H"
#include "GTEREG.H"

#include "../GTE/PsyX_GTE.H"
#include "../GTE/rcossin_tbl.h"
#include "../GTE/ratan_tbl.h"
#include "../GTE/sqrt_tbl.h"

#define ONE_BITS			12
#define ONE					(1 << 12)
#define	FIXED(a)			((a) >> 12)

#ifndef MIN
#define MIN(a,b)	fst_min(a,b)
#endif

#ifndef MAX
#define MAX(a,b)	fst_max(a,b)
#endif

inline int fst_min(int a, int b)
{
	int diff = a - b;
	int dsgn = diff >> 31;
	return b + (diff & dsgn);
}

inline int fst_max(int a, int b)
{
	int diff = a - b;
	int dsgn = diff >> 31;
	return a - (diff & dsgn);
}

void InitGeom()
{
	C2_ZSF3 = 341;
	C2_ZSF4 = 256;
	C2_H = 1000;
	C2_DQA = -98;
	C2_DQB = 340;
	C2_OFX = 0;
	C2_OFY = 0;
}

void SetGeomOffset(int ofx, int ofy)
{
	C2_OFX = (ofx << 16);
	C2_OFY = (ofy << 16);
}

void SetGeomScreen(int h)
{
	C2_H = h;
}

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

void RotTrans(struct SVECTOR* v0, VECTOR* v1, long* flag)
{
	gte_RotTrans(v0, v1, flag);
}

void RotTransSV(SVECTOR* v0, SVECTOR* v1, long* flag)
{
	gte_ldv0(v0);
	gte_rt();
	gte_stsv(v1);
	gte_stflg(flag);
}

long RotTransPers(struct SVECTOR* v0, long* sxy, long* p, long* flag)
{
	int sz;
	gte_RotTransPers(v0, sxy, p, flag, &sz);

	return sz;
}

long RotTransPers3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0, long* sxy1, long* sxy2, long* p, long* flag)
{
	int sz;
	gte_RotTransPers3(v0, v1, v2, sxy0, sxy1, sxy2, p, flag, &sz);

	return sz;
}

long RotTransPers4(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0, long* sxy1, long* sxy2, long* sxy3, long* p, long* flag)
{
	long _flag;
	int sz;

	gte_ldv3(v0, v1, v2);
	gte_rtpt();

	gte_stsxy3(sxy0, sxy1, sxy2);

	gte_stflg(&_flag);

	gte_ldv0(v3);
	gte_rtps();

	gte_stsxy(sxy3);
	gte_stflg(flag);
	gte_stdp(p);

	*flag |= _flag;
	gte_stszotz(&sz);

	return sz;
}

void NormalColor(SVECTOR* v0, CVECTOR* v1)
{
	gte_NormalColor(v0, v1);
}

void NormalColor3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, CVECTOR* v3, CVECTOR* v4, CVECTOR* v5)
{
	gte_NormalColor3(v0, v1, v2, v3, v4, v5);
}

void NormalColorDpq(struct SVECTOR* v0, struct CVECTOR* v1, long p, struct CVECTOR* v2)
{
	gte_NormalColorDpq(v0, v1, p, v2);
}

void NormalColorCol(struct SVECTOR* v0, struct CVECTOR* v1, struct CVECTOR* v2)
{
	gte_NormalColorCol(v0, v1, v2);
}

void NormalColorCol3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, CVECTOR* v3, CVECTOR* v4, CVECTOR* v5, CVECTOR* v6)
{
	gte_NormalColorCol3(v0,v1,v2,v3,v4,v5,v6);
}

void DpqColor(CVECTOR* v0, long p, CVECTOR* v1)
{
	gte_DpqColor(v0, &p, v1);
}

void ColorDpq(VECTOR* v0, CVECTOR* v1, long p, CVECTOR* v2) 
{
	gte_ColorDpq(v0, v1, p, v2);
}

void ColorCol(VECTOR* v0, CVECTOR* v1, CVECTOR* v2)
{
	gte_ColorCol(v0, v1, v2);
}

long NormalClip(long sxy0, long sxy1, long sxy2)
{
	long opz;

	gte_NormalClip(&sxy0, &sxy1, &sxy2, &opz);
	
	return opz;
}

void LocalLight(SVECTOR* v0, VECTOR* v1)
{
	gte_LocalLight(v0, v1);
}

long RotAverageNclip4(struct SVECTOR* v0, struct SVECTOR* v1, struct SVECTOR* v2, struct SVECTOR* v3, long* sxy0/*arg_10*/, long* sxy1/*arg_14*/, long* sxy2/*arg_18*/, long* sxy3/*arg_1C*/, long* p/*arg_20*/, long* otz/*arg_24*/, long* flag/*arg_28*/)
{
	gte_ldv3(v0, v1, v2);
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
#if 1
	/*
	// FIXME: might be wrong
	SVECTOR t1, t2, t3;

	gte_SetRotMatrix(m0);

	t1.vx = m1->m[0][0];
	t1.vy = m1->m[1][0];
	t1.vz = m1->m[2][0];

	gte_rtv0();
	gte_stsv(&t1);

	t2.vx = m1->m[0][1];
	t2.vy = m1->m[1][1];
	t2.vz = m1->m[2][1];
	gte_ldv0(&t2);
	gte_rtv0();
	gte_stsv(&t2);

	t3.vx = m1->m[0][2];
	t3.vy = m1->m[1][2];
	t3.vz = m1->m[2][2];
	gte_ldv0(&t3);
	gte_rtv0();
	gte_stsv(&t3);

	m2->m[0][0] = t1.vx;
	m2->m[1][0] = t1.vx;
	m2->m[2][0] = t1.vz;

	m2->m[0][1] = t2.vz;
	m2->m[1][1] = t2.vx;
	m2->m[2][1] = t2.vy;

	m2->m[0][2] = t3.vy;
	m2->m[1][2] = t3.vy;
	m2->m[2][2] = t3.vz;

	return m1;
	*/

	gte_MulMatrix0(m0, m1, m2);

	return m1;
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
	MATRIX tmp;
	gte_MulMatrix0(m0, m1, &tmp);

	*m0 = tmp;

	return m0;
}

MATRIX* MulMatrix2(MATRIX* m0, MATRIX* m1)
{
	// Same as MulMatrix but result goes to m1
	MATRIX tmp;
	gte_MulMatrix0(m0, m1, &tmp);

	*m1 = tmp;

	return m1;
}

MATRIX* MulRotMatrix(MATRIX* m0)
{
	// FIXME: might be wrong
	// as RTV0 can be insufficient
	gte_ldv0(&m0->m[0]);
	gte_rtv0();
	gte_stsv(&m0->m[0]);

	gte_ldv0(&m0->m[1]);
	gte_rtv0();
	gte_stsv(&m0->m[1]);

	gte_ldv0(&m0->m[2]);
	gte_rtv0();
	gte_stsv(&m0->m[2]);

	return m0;
}

void SetBackColor(long rbk, long gbk, long bbk)
{
	gte_SetBackColor(rbk,gbk,bbk);
}

void SetFarColor(long rfc, long gfc, long bfc)
{
	gte_SetFarColor(rfc, gfc, bfc);
}

#define	APPLYMATRIX(m,v0,v1)	{\
	int vx = v0->vx;\
	int vy = v0->vy;\
	int vz = v0->vz;\
	v1->vx = FIXED(m->m[0][0]*vx + m->m[0][1]*vy + m->m[0][2]*vz );\
	v1->vy = FIXED(m->m[1][0]*vx + m->m[1][1]*vy + m->m[1][2]*vz );\
	v1->vz = FIXED(m->m[2][0]*vx + m->m[2][1]*vy + m->m[2][2]*vz );\
}

VECTOR* ApplyMatrix(MATRIX* m, SVECTOR* v0, VECTOR* v1)
{
#if 1
	// correct Psy-Q implementation
	gte_SetRotMatrix(m);
	gte_ldv0(v0);
	gte_rtv0();
	gte_stlvnl(v1);
#else
	APPLYMATRIX(m, v0, v1);
#endif
	return v1;
}

VECTOR* ApplyRotMatrix(SVECTOR* v0, VECTOR* v1)
{
#if 1
	// correct Psy-Q implementation
	gte_ldv0(v0);
	gte_rtv0();
	gte_stsv(v1);
#else
	MATRIX temp;
	gte_ReadRotMatrix(&temp);

	MATRIX* m = &temp;

	APPLYMATRIX(m, v0, v1);
#endif
	return v1;
}

VECTOR* ApplyRotMatrixLV(VECTOR* v0, VECTOR* v1)
{
#if 1
	// correct Psy-Q implementation
	VECTOR tmpHI;
	VECTOR tmpLO;

	tmpHI.vx = v0->vx;
	tmpHI.vy = v0->vy;
	tmpHI.vz = v0->vz;

	if (tmpHI.vx < 0)
	{
		tmpLO.vx = -(-tmpHI.vx >> 0xf);
		tmpHI.vx = -(-tmpHI.vx & 0x7fff);
	}
	else
	{
		tmpLO.vx = tmpHI.vx >> 0xf;
		tmpHI.vx = tmpHI.vx & 0x7fff;
	}

	if (tmpHI.vy < 0)
	{
		tmpLO.vy = -(-tmpHI.vy >> 0xf);
		tmpHI.vy = -(-tmpHI.vy & 0x7fff);
	}
	else
	{
		tmpLO.vy = tmpHI.vy >> 0xf;
		tmpHI.vy = tmpHI.vy & 0x7fff;
	}

	if (tmpHI.vz < 0)
	{
		tmpLO.vz = -(-tmpHI.vz >> 0xf);
		tmpHI.vz = -(-tmpHI.vz & 0x7fff);
	}
	else
	{
		tmpLO.vz = tmpHI.vz >> 0xf;
		tmpHI.vz = tmpHI.vz & 0x7fff;
	}

	gte_ldlvl(&tmpLO);
	docop2(0x41E012);	// gte_rtir_sf0 ?
	gte_stlvnl(&tmpLO);

	gte_ldlvl(&tmpHI);
	gte_rtir();

	if (tmpLO.vx < 0)
		tmpLO.vx *= 8;
	else
		tmpLO.vx <<= 3;

	if (tmpLO.vy < 0)
		tmpLO.vy *= 8;
	else
		tmpLO.vy <<= 3;

	if (tmpLO.vz < 0)
		tmpLO.vz *= 8;
	else
		tmpLO.vz <<= 3;

	gte_stlvnl(&tmpHI);

	v1->vx = tmpHI.vx + tmpLO.vx;
	v1->vy = tmpHI.vy + tmpLO.vy;
	v1->vz = tmpHI.vz + tmpLO.vz;
#else
	MATRIX temp;
	gte_ReadRotMatrix(&temp);

	MATRIX* m = &temp;

	APPLYMATRIX(m, v0, v1);
#endif
	return v1;
}

SVECTOR* ApplyMatrixSV(MATRIX* m, SVECTOR* v0, SVECTOR* v1)
{
#if 1
	// correct Psy-Q implementation
	gte_SetRotMatrix(m);
	gte_ldv0(v0);
	gte_rtv0();
	gte_stsv(v1);
#else
	APPLYMATRIX(m, v0, v1);
#endif
	return v1;
}

VECTOR* ApplyMatrixLV(MATRIX* m, VECTOR* v0, VECTOR* v1)
{
#if 1
	// correct Psy-Q implementation
	VECTOR tmpHI;
	VECTOR tmpLO;

	gte_SetRotMatrix(m);

	tmpHI.vx = v0->vx;
	tmpHI.vy = v0->vy;
	tmpHI.vz = v0->vz;

	if (tmpHI.vx < 0)
	{
		tmpLO.vx = -(-tmpHI.vx >> 0xf);
		tmpHI.vx = -(-tmpHI.vx & 0x7fff);
	}
	else
	{
		tmpLO.vx = tmpHI.vx >> 0xf;
		tmpHI.vx = tmpHI.vx & 0x7fff;
	}

	if (tmpHI.vy < 0)
	{
		tmpLO.vy = -(-tmpHI.vy >> 0xf);
		tmpHI.vy = -(-tmpHI.vy & 0x7fff);
	}
	else
	{
		tmpLO.vy = tmpHI.vy >> 0xf;
		tmpHI.vy = tmpHI.vy & 0x7fff;
	}

	if (tmpHI.vz < 0)
	{
		tmpLO.vz = -(-tmpHI.vz >> 0xf);
		tmpHI.vz = -(-tmpHI.vz & 0x7fff);
	}
	else
	{
		tmpLO.vz = tmpHI.vz >> 0xf;
		tmpHI.vz = tmpHI.vz & 0x7fff;
	}

	gte_ldlvl(&tmpLO);
	docop2(0x41E012);	// gte_rtir_sf0 ?
	gte_stlvnl(&tmpLO);

	gte_ldlvl(&tmpHI);
	gte_rtir();

	if (tmpLO.vx < 0)
		tmpLO.vx *= 8;
	else
		tmpLO.vx <<= 3;

	if (tmpLO.vy < 0)
		tmpLO.vy *= 8;
	else
		tmpLO.vy <<= 3;

	if (tmpLO.vz < 0)
		tmpLO.vz *= 8;
	else
		tmpLO.vz <<= 3;

	gte_stlvnl(&tmpHI);

	v1->vx = tmpHI.vx + tmpLO.vx;
	v1->vy = tmpHI.vy + tmpLO.vy;
	v1->vz = tmpHI.vz + tmpLO.vz;
#else
	APPLYMATRIX(m, v0, v1);
#endif
	return v1;
}

MATRIX* RotMatrix(struct SVECTOR* r, MATRIX* m)
{
	// correct Psy-Q implementation
	int c0, c1, c2;
	int s0, s1, s2;
	int s2p0, s2m0, c2p0, c2m0;
	int	s2c0, s2s0, c2c0, c2s0;

	c0 = rcos(r->vx);
	c1 = rcos(r->vy);
	c2 = rcos(r->vz);
	s0 = rsin(r->vx);
	s1 = rsin(r->vy);
	s2 = rsin(r->vz);
	s2p0 = rsin(r->vz + r->vx);
	s2m0 = rsin(r->vz - r->vx);
	c2p0 = rcos(r->vz + r->vx);
	c2m0 = rcos(r->vz - r->vx);
	s2c0 = (s2p0 + s2m0) / 2;
	c2s0 = (s2p0 - s2m0) / 2;
	s2s0 = (c2m0 - c2p0) / 2;
	c2c0 = (c2m0 + c2p0) / 2;

	m->m[0][0] = FIXED(c2 * c1);
	m->m[1][0] = s2c0 + FIXED(c2s0 * s1);
	m->m[2][0] = s2s0 - FIXED(c2c0 * s1);
	m->m[0][1] = -FIXED(s2 * c1);
	m->m[1][1] = c2c0 - FIXED(s2s0 * s1);
	m->m[2][1] = c2s0 + FIXED(s2c0 * s1);
	m->m[0][2] = s1;
	m->m[1][2] = -FIXED(c1 * s0);
	m->m[2][2] = FIXED(c1 * c0);

	return m;
}

MATRIX* RotMatrixYXZ(struct SVECTOR* r, MATRIX* m)
{
	// correct Psy-Q implementation
	int c0, c1, c2;
	int s0, s1, s2;

	c0 = rcos(r->vx);
	c1 = rcos(r->vy);
	c2 = rcos(r->vz);
	s0 = rsin(r->vx);
	s1 = rsin(r->vy);
	s2 = rsin(r->vz);

	// Y-axis
	m->m[1][0] = FIXED(s2 * c0);
	m->m[1][1] = FIXED(c2 * c0);
	m->m[1][2] = -s0;

	// X-axis
	int x0 = FIXED(s1 * s0);
	m->m[0][0] = FIXED(c1 * c2) + FIXED(x0 * s2);
	m->m[0][1] = FIXED(x0 * c2) - FIXED(c1 * s2);
	m->m[0][2] = FIXED(s1 * c0);

	// Z-axis
	int z0 = FIXED(c1 * s0);
	m->m[2][1] = FIXED(s1 * s2) + FIXED(z0 * c2);
	m->m[2][0] = FIXED(z0 * s2) - FIXED(s1 * c2);
	m->m[2][2] = FIXED(c1 * c0);

	return m;
}

MATRIX* RotMatrixX(long r, MATRIX* m)
{
	// correct Psy-Q implementation
	int s0 = rsin(r);
	int c0 = rcos(r);
	int t1, t2;
	t1 = m->m[1][0];
	t2 = m->m[2][0];
	m->m[1][0] = FIXED(t1 * c0 - t2 * s0);
	m->m[2][0] = FIXED(t1 * s0 + t2 * c0);
	t1 = m->m[1][1];
	t2 = m->m[2][1];
	m->m[1][1] = FIXED(t1 * c0 - t2 * s0);
	m->m[2][1] = FIXED(t1 * s0 + t2 * c0);
	t1 = m->m[1][2];
	t2 = m->m[2][2];
	m->m[1][2] = FIXED(t1 * c0 - t2 * s0);
	m->m[2][2] = FIXED(t1 * s0 + t2 * c0);

	return m;
}

MATRIX* RotMatrixY(long r, MATRIX* m)
{
	// correct Psy-Q implementation
	int s0 = rsin(r);
	int c0 = rcos(r);
	int t1, t2;
	t1 = m->m[0][0];
	t2 = m->m[2][0];
	m->m[0][0] = FIXED(t1 * c0 + t2 * s0);
	m->m[2][0] = FIXED(-t1 * s0 + t2 * c0);
	t1 = m->m[0][1];
	t2 = m->m[2][1];
	m->m[0][1] = FIXED(t1 * c0 + t2 * s0);
	m->m[2][1] = FIXED(-t1 * s0 + t2 * c0);
	t1 = m->m[0][2];
	t2 = m->m[2][2];
	m->m[0][2] = FIXED(t1 * c0 + t2 * s0);
	m->m[2][2] = FIXED(-t1 * s0 + t2 * c0);

	return m;
}

MATRIX* RotMatrixZ(long r, MATRIX* m)
{
	// correct Psy-Q implementation
	int s0 = rsin(r);
	int c0 = rcos(r);
	int t1, t2;
	t1 = m->m[0][0];
	t2 = m->m[1][0];
	m->m[0][0] = FIXED(t1 * c0 - t2 * s0);
	m->m[1][0] = FIXED(t1 * s0 + t2 * c0);
	t1 = m->m[0][1];
	t2 = m->m[1][1];
	m->m[0][1] = FIXED(t1 * c0 - t2 * s0);
	m->m[1][1] = FIXED(t1 * s0 + t2 * c0);
	t1 = m->m[0][2];
	t2 = m->m[1][2];
	m->m[0][2] = FIXED(t1 * c0 - t2 * s0);
	m->m[1][2] = FIXED(t1 * s0 + t2 * c0);

	return m;
}

MATRIX* RotMatrixZYX_gte(SVECTOR* r, MATRIX* m)
{
#if 0
	// TODO: correct Psy-Q implementation
#else
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
#endif
	return m;
}

MATRIX* CompMatrix(MATRIX* m0, MATRIX* m1, MATRIX* m2)
{
	// UNTESTED
	SVECTOR tmp;
	gte_MulMatrix0(m0, m1, m2);

	tmp.vx = m1->t[0];
	tmp.vy = m1->t[1];
	tmp.vz = m1->t[2];

	gte_ldv0(&tmp);
	gte_rtv0();
	gte_stlvnl(m2->t);

	m2->t[0] += m0->t[0];
	m2->t[1] += m0->t[1];
	m2->t[2] += m0->t[2];

	return m2;
}

MATRIX* CompMatrixLV(MATRIX* m0, MATRIX* m1, MATRIX* m2)
{
	// UNTESTED
	// correct Psy-Q implementation
	VECTOR tmpHI;
	VECTOR tmpLO;

	gte_MulMatrix0(m0, m1, m2);

	// next... same as ApplyMatrixLV
	tmpHI.vx = m1->t[0];
	tmpHI.vy = m1->t[1];
	tmpHI.vz = m1->t[2];

	if (tmpHI.vx < 0)
	{
		tmpLO.vx = -(-tmpHI.vx >> 0xf);
		tmpHI.vx = -(-tmpHI.vx & 0x7fff);
	}
	else 
	{
		tmpLO.vx = tmpHI.vx >> 0xf;
		tmpHI.vx = tmpHI.vx & 0x7fff;
	}

	if (tmpHI.vy < 0)
	{
		tmpLO.vy = -(-tmpHI.vy >> 0xf);
		tmpHI.vy = -(-tmpHI.vy & 0x7fff);
	}
	else 
	{
		tmpLO.vy = tmpHI.vy >> 0xf;
		tmpHI.vy = tmpHI.vy & 0x7fff;
	}

	if (tmpHI.vz < 0)
	{
		tmpLO.vz = -(-tmpHI.vz >> 0xf);
		tmpHI.vz = -(-tmpHI.vz & 0x7fff);
	}
	else
	{
		tmpLO.vz = tmpHI.vz >> 0xf;
		tmpHI.vz = tmpHI.vz & 0x7fff;
	}

	gte_ldlvl(&tmpLO);
	docop2(0x41E012);	// gte_rtir_sf0 ?
	gte_stlvnl(&tmpLO);

	gte_ldlvl(&tmpHI);
	gte_rtir();

	if (tmpLO.vx < 0)
		tmpLO.vx = tmpLO.vx * 8;
	else
		tmpLO.vx = tmpLO.vx << 3;

	if (tmpLO.vy < 0)
		tmpLO.vy = tmpLO.vy * 8;
	else
		tmpLO.vy = tmpLO.vy << 3;

	if (tmpLO.vz < 0)
		tmpLO.vz = tmpLO.vz * 8;
	else
		tmpLO.vz = tmpLO.vz << 3;

	gte_stlvnl(&tmpHI);

	m2->t[0] = tmpHI.vx + tmpLO.vx + m0->t[0];
	m2->t[1] = tmpHI.vy + tmpLO.vy + m0->t[1];
	m2->t[2] = tmpHI.vz + tmpLO.vz + m0->t[2];

	return m2;
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

void SetFogNearFar(long a, long b, long h)
{
	if (b - a < 100)
		return;

	assert((b - a));
	assert((b - a) != -1 && (-a * b) != 32768);
	assert((b - a));
	assert((b - a) != -1 && (b << 12) != 32768);
	assert(h != 0);
	assert(h != -1 && (((-a * b) / (b - a)) << 8) != 32768);

	int dqa = (-a * b / (b - a) << 8) / h;

	SetDQA(MAX(MIN(dqa, 32767), -32767));
	SetDQB((b << 12) / (b - a) << 12);
}

int rsin(int a)
{
	//if (a < 0) // really not needed; bit mask does it all
	//	return -rcossin_tbl[(-a & 0xfffU) * 2];

	return rcossin_tbl[(a & 0xfffU) * 2];
}

int rcos(int a)
{
	//if (a < 0) // really not needed; bit mask does it all
	//	return rcossin_tbl[(-a & 0xfffU) * 2 + 1];

	return rcossin_tbl[(a & 0xfffU) * 2 + 1];
}

long ratan2(long y, long x)
{
	// correct Psy-Q implementation
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
			ang = (y << 10) / x;
		else
			ang = y / (x >> 10);

		v = ratan_tbl[ang];
	}
	else
	{
		if (((ulong)x & 0x7fe00000U) == 0)
			ang = (x << 10) / y;
		else
			ang = x / (y >> 10);

		v = 1024 - ratan_tbl[ang];
	}

	if (xlt0)
		v = 2048 - v;

	if (ylt0)
		v = -v;

	return v;
}

long SquareRoot0(long a)
{
	// correct Psy-Q implementation
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

	return SQRT[idx - 64] << (31 - lzcs >> 1) >> 12;
}
