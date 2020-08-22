#include "THISDUST.H"
#include "PATHFIND.H"
#include "SYSTEM.H"
#include "COP_AI.H"
#include "OBJCOLL.H"
#include "DR2ROADS.H"
#include "PLAYERS.H"
#include "CAMERA.H"

short distanceCache[16384];
char omap[128][16];
long dunyet[32][2];
int pathIterations;

int pathFrames;
int DoExtraWorkForNFrames;

VECTOR searchTarget;
int playerTargetDistanceSq;

int distanceReturnedLog[8];
int distLogIndex;
int lastDistanceFound;

tNode heap[201];
unsigned int numHeapEntries = 0;

PATHFIND_237fake ends[6][2];

// decompiled code
// original method signature: 
// struct tNode /*$ra*/ popNode()
 // line 314, offset 0x000e7000
	/* begin block 1 */
		// Start line: 315
		// Start offset: 0x000E7000
		// Variables:
	// 		unsigned int lNumHeapEntries; // $s0
	// 		struct tNode res; // stack offset -24
	// 		unsigned short f; // $t8
	// 		unsigned int child; // $a1
	// 		unsigned int here; // $t5

		/* begin block 1.1 */
			// Start line: 325                                                                  
			// Start offset: 0x000E7058
			// Variables:
		// 		unsigned int lastEntry; // $t4

			/* begin block 1.1.1 */
				// Start line: 329
				// Start offset: 0x000E7070
				// Variables:
			// 		int d; // $t3
			// 		int d2; // $t2
			// 		int d3; // $a3
			// 		int d4; // $t1
			/* end block 1.1.1 */
			// End offset: 0x000E70B8
			// End Line: 346
		/* end block 1.1 */
		// End offset: 0x000E7110
		// End Line: 347

		/* begin block 1.2 */
			// Start line: 349
			// Start offset: 0x000E7110
			// Variables:
		// 		int d; // $a2
		// 		int d2; // $a3
		// 		int d3; // $t1
		// 		int d4; // $t2
		/* end block 1.2 */
		// End offset: 0x000E715C
		// End Line: 358
	/* end block 1 */
	// End offset: 0x000E715C
	// End Line: 361

	/* begin block 2 */
		// Start line: 628
	/* end block 2 */
	// End Line: 629

	/* begin block 3 */
		// Start line: 630
	/* end block 3 */
	// End Line: 631

// [D]
tNode * popNode(tNode *__return_storage_ptr__)
{
	ushort uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int uVar5;
	ushort uVar6;
	uint uVar7;
	uint uVar8;
	int iVar9;
	int iVar10;
	ushort uVar11;
	uint uVar12;

	tNode res;

	uVar5 = heap[1].dist;
	iVar4 = heap[1].vz;
	iVar3 = heap[1].vy;
	iVar2 = heap[1].vx;

	if (numHeapEntries > 1) 
	{
		uVar1 = heap[numHeapEntries].dist;
		uVar12 = 1;

		while (true) 
		{
			uVar7 = uVar12 * 2;
			uVar11 = heap[uVar12 * 2].dist;
			uVar8 = uVar7;
			uVar6 = uVar11;

			if ((numHeapEntries - 2 <= uVar7) || (uVar8 = uVar7 + 1, uVar6 = heap[uVar7 + 1].dist, heap[uVar7 + 1].dist < uVar11)) 
			{
				uVar11 = uVar6;
				uVar7 = uVar8;
			}

			if ((numHeapEntries - 2 < uVar7) || (uVar1 <= uVar11)) 
				break;

			heap[uVar12].vx = heap[uVar7].vx;
			heap[uVar12].vy = heap[uVar7].vy;
			heap[uVar12].vz = heap[uVar7].vz;
			heap[uVar12].dist = uVar11;

			uVar12 = uVar7;
		}

		heap[uVar12].vx = heap[numHeapEntries].vx;
		heap[uVar12].vy = heap[numHeapEntries].vy;
		heap[uVar12].vz = heap[numHeapEntries].vz;;
		heap[uVar12].dist = heap[numHeapEntries].dist;
	}

	numHeapEntries--;

	__return_storage_ptr__->vx = iVar2;
	__return_storage_ptr__->vy = iVar3;
	__return_storage_ptr__->vz = iVar4;
	__return_storage_ptr__->dist = uVar5;

	return __return_storage_ptr__;
}



// decompiled code
// original method signature: 
// void /*$ra*/ WunCell(struct VECTOR *pbase /*$s0*/)
 // line 426, offset 0x000e7194
	/* begin block 1 */
		// Start line: 427
		// Start offset: 0x000E7194
		// Variables:
	// 		int i; // $s2
	// 		int j; // $s4
	// 		struct VECTOR v[2]; // stack offset -88
	// 		struct VECTOR pos; // stack offset -56

		/* begin block 1.1 */
			// Start line: 440
			// Start offset: 0x000E723C

			/* begin block 1.1.1 */
				// Start line: 440
				// Start offset: 0x000E723C
				// Variables:
			// 		int z; // $a1
			// 		int x; // $a2
			/* end block 1.1.1 */
			// End offset: 0x000E72C8
			// End Line: 446
		/* end block 1.1 */
		// End offset: 0x000E72C8
		// End Line: 446
	/* end block 1 */
	// End offset: 0x000E735C
	// End Line: 450

	/* begin block 2 */
		// Start line: 910
	/* end block 2 */
	// End Line: 911

// [D]
void WunCell(VECTOR *pbase)
{
	unsigned char bVar1;
	char cVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	unsigned char bVar7;
	int iVar8;
	PATHFIND_237fake* pPVar9;
	int iVar10;
	VECTOR v[2];
	VECTOR pos;

	pbase->vx = pbase->vx + 512;
	pbase->vz = pbase->vz + 512;

	v[0].vy = MapHeight(pbase) + 60;

	pbase->vx = pbase->vx - 512;
	pbase->vz = pbase->vz - 512;

	v[1].vy = v[0].vy;

	iVar10 = 0;
	do {
		iVar8 = 0;

		if (iVar10 != 0)
			pbase->vx += 512;

		do {
			v[0].vx = pbase->vx + ends[iVar8][0].dx;
			v[0].vz = pbase->vz + ends[iVar8][0].dz;
			v[1].vx = pbase->vx + ends[iVar8][1].dx;
			v[1].vz = pbase->vz + ends[iVar8][1].dz;

			iVar4 = v[0].vx + v[1].vx;
			iVar5 = v[0].vz + v[1].vz;

			cVar2 = lineClear(&v[0], &v[1]);

			bVar7 = 0;
			uVar6 = iVar5 >> 9;

			if (cVar2 == 0)
				bVar7 = 0xff;

			omap[(iVar4 >> 9 & 0x7fU)][((uVar6 & 0x7f) >> 3)] = omap[(iVar4 >> 9 & 0x7fU)][((uVar6 & 0x7f) >> 3)] ^ (1 << (uVar6 & 7)) & (bVar1 ^ bVar7);

			iVar8++;
		} while (iVar8 < 6);

		if (iVar10 != 0)
			pbase->vx -= 512;

		iVar10++;
	} while (iVar10 < 2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InvalidateMap()
 // line 453, offset 0x000e735c
	/* begin block 1 */
		// Start line: 455
		// Start offset: 0x000E735C
		// Variables:
	// 		struct VECTOR bPos; // stack offset -16
	// 		int count; // $t4
	// 		int dir; // $t1
	// 		int p; // $t2
	// 		int q; // $t3

		/* begin block 1.1 */
			// Start line: 465
			// Start offset: 0x000E73A8
			// Variables:
		// 		int tile; // $a0
		// 		int mask; // $a1
		// 		int diff; // $a1
		// 		int i; // $v0
		/* end block 1.1 */
		// End offset: 0x000E73A8
		// End Line: 468
	/* end block 1 */
	// End offset: 0x000E74B0
	// End Line: 487

	/* begin block 2 */
		// Start line: 1011
	/* end block 2 */
	// End Line: 1012

	/* begin block 3 */
		// Start line: 1015
	/* end block 3 */
	// End Line: 1016

	/* begin block 4 */
		// Start line: 1016
	/* end block 4 */
	// End Line: 1017

	/* begin block 5 */
		// Start line: 1023
	/* end block 5 */
	// End Line: 1024

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InvalidateMap(void)
{
	uint uVar1;
	int iVar2;
	uint uVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	VECTOR bPos;

	iVar6 = 0;
	iVar5 = 0;
	uVar4 = 0;
	iVar7 = 0x3ff;
	bPos.vx = player[0].pos[0] & 0xfffffc00;
	bPos.vz = player[0].pos[2] & 0xfffffc00;

	do {
		uVar3 = bPos.vz >> 10;

		uVar1 = dunyet[(bPos.vx >> 10 & 0x1fU)][(uVar3 & 1)];
		dunyet[(bPos.vx >> 10 & 0x1fU)][(uVar3 & 1)] = uVar1 ^ 3 << (uVar3 & 0x1e) & ((((bPos.vx >> 10 & 0x3fU) >> 5 | uVar3 >> 4 & 2) ^ 3) << (uVar3 & 0x1e) ^ uVar1);

		if (uVar4 == 1) 
		{
			iVar6++;
			bPos.vz += 1024;
			if (iVar5 == iVar6)
				uVar4 = 2;

		}
		else if (uVar4 < 2)
		{
			iVar2 = bPos.vx + 0x400;

			if (uVar4 == 0)
			{
				iVar5++;
				bPos.vx = iVar2;
				if (iVar5 + iVar6 == 1)
					uVar4 = 1;
			}
			else
			{
			LAB_PATH__000e7484:
				iVar6--;
				bPos.vz -= 1024;
				if (iVar5 == iVar6)
				{
					uVar4 = 0;
				}
			}
		}
		else
		{
			iVar2 = bPos.vx - 1024;

			if (uVar4 != 2)
				goto LAB_PATH__000e7484;

			iVar5--;
			bPos.vx = iVar2;

			if (iVar5 + iVar6 == 0)
				uVar4 = 3;
		}

		iVar7--;

		if (iVar7 < 0)
			return;

	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ BloodyHell()
 // line 495, offset 0x000e74b0
	/* begin block 1 */
		// Start line: 497
		// Start offset: 0x000E74B0
		// Variables:
	// 		struct VECTOR bPos; // stack offset -48
	// 		int count; // $s4
	// 		int dir; // $s0
	// 		int p; // $s1
	// 		int q; // $s2
	// 		unsigned int howMany; // $s3
		// Labels:
		//		0x0000069C	raa

		/* begin block 1.1 */
			// Start line: 517
			// Start offset: 0x000E755C
			// Variables:
		// 		int tile; // $a0
		// 		int mask; // $a1
		// 		int diff; // $v0
		// 		int i; // $v0
		/* end block 1.1 */
		// End offset: 0x000E75E4
		// End Line: 537
	/* end block 1 */
	// End offset: 0x000E76C4
	// End Line: 565

	/* begin block 2 */
		// Start line: 1125
	/* end block 2 */
	// End Line: 1126

	/* begin block 3 */
		// Start line: 1134
	/* end block 3 */
	// End Line: 1135

	/* begin block 4 */
		// Start line: 1135
	/* end block 4 */
	// End Line: 1136

	/* begin block 5 */
		// Start line: 1146
	/* end block 5 */
	// End Line: 1147

/* WARNING: Unknown calling convention yet parameter storage is locked */

unsigned int cellsThisFrame;
unsigned int cellsPerFrame = 4;

// [D]
void BloodyHell(void)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	int iVar8;
	VECTOR bPos;

	bPos.vy = 0x1fed;
	bPos.vx = player[0].pos[0] & 0xfffffc00;
	bPos.vz = player[0].pos[2] & 0xfffffc00;

	cellsThisFrame = 0;
	uVar7 = cellsPerFrame;

	if (CameraCnt < 4)
		uVar7 = cellsPerFrame + 0x14;

	iVar6 = 0;

	if (CameraCnt < 8)
		uVar7 = uVar7 + 4;

	iVar5 = 0;
	uVar4 = 0;
	iVar8 = 0;

	do {
		if (iVar8 == 200)
			uVar7 = uVar7 - 1;
	
		uVar2 = (int)bPos.vz >> 10;

		uVar3 = dunyet[((int)bPos.vx >> 10 & 0x1fU)][(uVar2 & 1)];
		uVar1 = 3 << (uVar2 & 0x1e) & ((((int)bPos.vx >> 10 & 0x3fU) >> 5 | uVar2 >> 4 & 2) << (uVar2 & 0x1e) ^ uVar3);

		if (uVar1 != 0) 
		{
			dunyet[((int)bPos.vx >> 10 & 0x1fU)][(uVar2 & 1)] = uVar3 ^ uVar1;
			WunCell(&bPos);

			cellsThisFrame++;

			if (uVar7 <= cellsThisFrame)
				return;

		}
		if (uVar4 == 1) 
		{
			iVar6 = iVar6 + 1;
			bPos.vz = bPos.vz + 0x400;
			if (iVar5 == iVar6)
				uVar4 = 2;
		}
		else if (uVar4 < 2)
		{
			if (uVar4 == 0)
			{
				iVar5 = iVar5 + 1;
				bPos.vx = bPos.vx + 0x400;
				if (iVar5 + iVar6 == 1)
				{
					uVar4 = 1;
				}
			}
			else
			{
			LAB_PATH__000e7674:
				iVar6 = iVar6 + -1;
				bPos.vz = bPos.vz - 0x400;

				if (iVar5 == iVar6)
					uVar4 = 0;
			}
		}
		else
		{
			if (uVar4 != 2)
				goto LAB_PATH__000e7674;

			iVar5 = iVar5 + -1;
			bPos.vx = bPos.vx - 0x400;

			if (iVar5 + iVar6 == 0)
				uVar4 = 3;
		}

		iVar8++;

		if (0x348 < iVar8)
			return;

	} while (true);
}



// decompiled code
// original method signature: 
// int /*$ra*/ blocked(struct tNode *v1 /*$a3*/, struct tNode *v2 /*$a2*/)
 // line 567, offset 0x000e76c4
	/* begin block 1 */
		// Start line: 568
		// Start offset: 0x000E76C4
		// Variables:
	// 		struct VECTOR pos; // stack offset -24
	// 		int res; // $a0

		/* begin block 1.1 */
			// Start line: 575
			// Start offset: 0x000E76E0

			/* begin block 1.1.1 */
				// Start line: 575
				// Start offset: 0x000E76E0
				// Variables:
			// 		int z; // $a2
			// 		int x; // $v1
			/* end block 1.1.1 */
			// End offset: 0x000E774C
			// End Line: 578
		/* end block 1.1 */
		// End offset: 0x000E774C
		// End Line: 578

		/* begin block 1.2 */
			// Start line: 585
			// Start offset: 0x000E7790

			/* begin block 1.2.1 */
				// Start line: 585
				// Start offset: 0x000E7790
				// Variables:
			// 		int z; // $v1
			// 		int x; // $a0
			/* end block 1.2.1 */
			// End offset: 0x000E7790
			// End Line: 585
		/* end block 1.2 */
		// End offset: 0x000E7790
		// End Line: 585
	/* end block 1 */
	// End offset: 0x000E7814
	// End Line: 590

	/* begin block 2 */
		// Start line: 1339
	/* end block 2 */
	// End Line: 1340

	/* begin block 3 */
		// Start line: 1342
	/* end block 3 */
	// End Line: 1343

int blocked(tNode *v1, tNode *v2)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	bool bVar2;
	char cVar3;
	int iVar4;
	int iVar5;
	undefined3 extraout_var;
	int iVar6;
	int iVar7;
	uint uVar8;
	uint uVar9;
	byte bVar10;

	if (DAT_PATH__000e913c == 0) {
		uVar8 = v1->vz + v2->vz >> 9;
		uVar8 = (int)(uint)(byte)(&DAT_PATH__000e91a8)
			[((int)(uVar8 & 0x7f) >> 3) + (v1->vx + v2->vx >> 5 & 0x7f0U)] >>
			(uVar8 & 7) & 1;
	}
	else {
		iVar4 = v1->vx;
		iVar6 = v2->vx;
		iVar5 = v1->vz;
		iVar7 = v2->vz;
		cVar3 = lineClear((VECTOR *)v1, (VECTOR *)v2);
		bVar10 = 0;
		bVar2 = CONCAT31(extraout_var, cVar3) == 0;
		uVar8 = (uint)bVar2;
		uVar9 = iVar5 + iVar7 >> 9;
		if (bVar2) {
			bVar10 = 0xff;
		}
		bVar1 = (&DAT_PATH__000e91a8)[((int)(uVar9 & 0x7f) >> 3) + (iVar4 + iVar6 >> 9 & 0x7fU) * 0x10];
		(&DAT_PATH__000e91a8)[((int)(uVar9 & 0x7f) >> 3) + (iVar4 + iVar6 >> 9 & 0x7fU) * 0x10] =
			bVar1 ^ (byte)(1 << (uVar9 & 7)) & (bVar1 ^ bVar10);
	}
	return uVar8;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ setDistance(struct tNode *n /*$a0*/, unsigned short dist /*$a1*/)
 // line 659, offset 0x000e90a4
	/* begin block 1 */
		// Start line: 1316
	/* end block 1 */
	// End Line: 1317

	/* begin block 2 */
		// Start line: 1318
	/* end block 2 */
	// End Line: 1319

void setDistance(tNode *n, ushort dist)
{
	UNIMPLEMENTED();
	/*
	n->dist = dist | 1;
	(&DAT_PATH__000e9b00)
		[(n->vx >> 2 & 0x3f80U | n->vz >> 9 & 0x7fU) ^ (n->vy & 1U) * 0x2040 ^ (n->vy & 2U) << 0xc] =
		dist | 1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ iterate()
 // line 712, offset 0x000e7814
	/* begin block 1 */
		// Start line: 714
		// Start offset: 0x000E7814
		// Variables:
	// 		int dir; // $s2
	// 		struct tNode itHere; // stack offset -48
	// 		struct tNode *nbr; // $s4

		/* begin block 1.1 */
			// Start line: 724
			// Start offset: 0x000E7870
			// Variables:
		// 		int nearBy; // $v1
		// 		int computed; // $s1

			/* begin block 1.1.1 */
				// Start line: 726
				// Start offset: 0x000E7870
				// Variables:
			// 		int dx; // $v0
			// 		int dz; // $a0
			/* end block 1.1.1 */
			// End offset: 0x000E7870
			// End Line: 727

			/* begin block 1.1.2 */
				// Start line: 727
				// Start offset: 0x000E7870

				/* begin block 1.1.2.1 */
					// Start line: 727
					// Start offset: 0x000E7870
					// Variables:
				// 		int res; // $a0
				/* end block 1.1.2.1 */
				// End offset: 0x000E7870
				// End Line: 727
			/* end block 1.1.2 */
			// End offset: 0x000E7870
			// End Line: 727
		/* end block 1.1 */
		// End offset: 0x000E797C
		// End Line: 763

		/* begin block 1.2 */
			// Start line: 768
			// Start offset: 0x000E79B4
			// Variables:
		// 		int nr; // $a0
		// 		int nl; // $v1

			/* begin block 1.2.1 */
				// Start line: 770
				// Start offset: 0x000E7A08
				// Variables:
			// 		unsigned int a; // $v1

				/* begin block 1.2.1.1 */
					// Start line: 770
					// Start offset: 0x000E7A08

					/* begin block 1.2.1.1.1 */
						// Start line: 713
						// Start offset: 0x000E7A44
						// Variables:
					// 		unsigned int r; // $v0
					/* end block 1.2.1.1.1 */
					// End offset: 0x000E7A68
					// End Line: 713
				/* end block 1.2.1.1 */
				// End offset: 0x000E7A68
				// End Line: 713
			/* end block 1.2.1 */
			// End offset: 0x000E7A68
			// End Line: 713

			/* begin block 1.2.2 */
				// Start line: 773
				// Start offset: 0x000E7AAC
				// Variables:
			// 		struct tNode *pnode; // $s0

				/* begin block 1.2.2.1 */
					// Start line: 773
					// Start offset: 0x000E7AAC
					// Variables:
				// 		unsigned int parent; // $a2
				// 		unsigned int i; // $a3
				/* end block 1.2.2.1 */
				// End offset: 0x000E7B98
				// End Line: 773
			/* end block 1.2.2 */
			// End offset: 0x000E7B98
			// End Line: 773
		/* end block 1.2 */
		// End offset: 0x000E7B98
		// End Line: 774
	/* end block 1 */
	// End offset: 0x000E7BA8
	// End Line: 776

	/* begin block 2 */
		// Start line: 1525
	/* end block 2 */
	// End Line: 1526

	/* begin block 3 */
		// Start line: 1648
	/* end block 3 */
	// End Line: 1649

	/* begin block 4 */
		// Start line: 1649
	/* end block 4 */
	// End Line: 1650

	/* begin block 5 */
		// Start line: 1651
	/* end block 5 */
	// End Line: 1652

/* WARNING: Unknown calling convention yet parameter storage is locked */

void iterate(void)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	ushort uVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	tNode *v2;
	int iVar8;
	tNode local_30;

	if (DAT_PATH__000f279c != 0) {
		popNode(&local_30);
		iVar8 = 0;
		v2 = (tNode *)&DAT_1f800020;
		do {
			iVar3 = (&DAT_PATH__000e9140)[iVar8];
			iVar4 = local_30.vx + (short)iVar3;
			v2->vx = iVar4;
			v2->vy = local_30.vy;
			iVar3 = local_30.vz + (iVar3 >> 0x10);
			v2->vz = iVar3;
			uVar1 = (&DAT_PATH__000e9b00)
				[(iVar4 >> 2 & 0x3f80U | iVar3 >> 9 & 0x7fU) ^ (local_30.vy & 1) * 0x2040 ^
				(local_30.vy & 2) << 0xc];
			v2->dist = uVar1;
			if ((uVar1 & 1) == 0) {
				iVar3 = blocked(&local_30, v2);
				if (iVar3 == 0) {
					iVar3 = v2->vy - local_30.vy;
					if (iVar3 < 0) {
						iVar3 = local_30.vy - v2->vy;
					}
					if (iVar3 < 0xc9) {
						if ((uVar1 & 1) == 0) {
							v2->dist = 0;
						}
						goto LAB_PATH__000e797c;
					}
				}
				v2->dist = 1;
			}
			else {
				if ((int)(uint)uVar1 <= (int)((uint)local_30.dist - 0x120)) {
					v2->dist = 1;
				}
			}
		LAB_PATH__000e797c:
			iVar8 = iVar8 + 1;
			v2 = v2 + 1;
		} while (iVar8 < 6);
		iVar3 = 0;
		iVar8 = 1;
		do {
			if (*(short *)(&DAT_1f80002c + iVar3 * 4) == 0) {
				uVar1 = (ushort)DAT_1f80002c;
				if (iVar3 != 5) {
					uVar1 = *(ushort *)(&DAT_1f80003c + iVar3 * 4);
				}
				uVar2 = DAT_1f80007c;
				if (iVar3 != 0) {
					uVar2 = *(ushort *)(&DAT_1f80001c + iVar3 * 4);
				}
				if (uVar2 < 2) {
					if (uVar1 >= 2) {
						iVar8 = (uint)uVar1 + (uint)local_30.dist;
						goto LAB_PATH__000e7a94;
					}
					uVar5 = (uint)local_30.dist + 0x100;
				}
				else {
					if (uVar1 < 2) {
						iVar8 = (uint)uVar2 + (uint)local_30.dist;
					LAB_PATH__000e7a94:
						uVar5 = (iVar8 >> 1) + 0xdd;
					}
					else {
						iVar8 = (uint)uVar1 - (uint)uVar2;
						uVar5 = 0x10000 - (iVar8 * iVar8) / 3;
						if ((int)uVar5 < 0) {
							uVar5 = 0;
						}
						else {
							uVar6 = (uVar5 >> 9) + 0x80;
							if (uVar6 == 0) {
								trap(7);
							}
							uVar5 = uVar5 / uVar6 + uVar6 >> 1;
						}
						uVar5 = local_30.dist + uVar5;
					}
				}
				uVar5 = uVar5 & 0xffff;
				iVar8 = iVar3 + 1;
				if (DAT_PATH__000f279c != 0xc6) {
					setDistance((tNode *)(&DAT_1f800020 + iVar3 * 4), (ushort)uVar5);
					uVar7 = DAT_PATH__000f279c + 1;
					uVar6 = uVar7 >> 1;
					iVar8 = uVar7 * 0x10;
					if ((uVar6 != 0) && (uVar5 < (ushort)(&DAT_PATH__000f1b14)[uVar6 * 8])) {
						iVar8 = uVar7 * 0x10;
						do {
							uVar7 = uVar6;
							*(undefined4 *)((int)&DAT_PATH__000f1b08 + iVar8) = (&DAT_PATH__000f1b08)[uVar7 * 4];
							*(undefined4 *)((int)&DAT_PATH__000f1b0c + iVar8) = (&DAT_PATH__000f1b0c)[uVar7 * 4];
							*(undefined4 *)((int)&DAT_PATH__000f1b10 + iVar8) = (&DAT_PATH__000f1b10)[uVar7 * 4];
							uVar6 = uVar7 >> 1;
							*(undefined4 *)((int)&DAT_PATH__000f1b14 + iVar8) =
								*(undefined4 *)(&DAT_PATH__000f1b14 + uVar7 * 8);
							if (uVar6 == 0) break;
							iVar8 = uVar7 << 4;
						} while (uVar5 < (ushort)(&DAT_PATH__000f1b14)[uVar6 * 8]);
						iVar8 = uVar7 << 4;
					}
					*(int *)((int)&DAT_PATH__000f1b08 + iVar8) = ((tNode *)(&DAT_1f800020 + iVar3 * 4))->vx;
					*(undefined4 *)((int)&DAT_PATH__000f1b0c + iVar8) = (&DAT_1f800024)[iVar3 * 4];
					*(undefined4 *)((int)&DAT_PATH__000f1b10 + iVar8) = (&DAT_1f800028)[iVar3 * 4];
					DAT_PATH__000f279c = DAT_PATH__000f279c + 1;
					*(undefined4 *)((int)&DAT_PATH__000f1b14 + iVar8) = (&DAT_1f80002c)[iVar3 * 4];
					iVar8 = iVar3 + 1;
				}
			}
			iVar3 = iVar8;
			iVar8 = iVar3 + 1;
		} while (iVar3 < 6);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitPathFinding()
 // line 801, offset 0x000e7bd0
	/* begin block 1 */
		// Start line: 803
		// Start offset: 0x000E7BD0
		// Variables:
	// 		int i; // $a0

		/* begin block 1.1 */
			// Start line: 802
			// Start offset: 0x000E7BD0
		/* end block 1.1 */
		// End offset: 0x000E7BD0
		// End Line: 802

		/* begin block 1.2 */
			// Start line: 802
			// Start offset: 0x000E7BD0
		/* end block 1.2 */
		// End offset: 0x000E7BD0
		// End Line: 802
	/* end block 1 */
	// End offset: 0x000E7CA8
	// End Line: 819

	/* begin block 2 */
		// Start line: 1602
	/* end block 2 */
	// End Line: 1603

	/* begin block 3 */
		// Start line: 1603
	/* end block 3 */
	// End Line: 1604

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitPathFinding(void)
{
	int i;

	setMem16((ushort*)distanceCache, 0xfffe, sizeof(distanceCache) / sizeof(short));
	ClearMem((char*)omap, sizeof(omap));
	ClearMem((char*)dunyet, sizeof(dunyet));
	InvalidateMap();

	lastDistanceFound = 18000;

	i = 0;
	do {
		distanceReturnedLog[i++] = 18000;
	} while (i < 8);

	pathFrames = 80;
	DoExtraWorkForNFrames = 6;
	distLogIndex = 0;
	searchTarget.vx = 0;
	searchTarget.vy = -12367;
	searchTarget.vz = 0;
	playerTargetDistanceSq = 0;
	pathFrames = 0;
	pathIterations = 129;
}



// decompiled code
// original method signature: 
// int /*$ra*/ getInterpolatedDistance(struct VECTOR *pos /*$s2*/)
 // line 821, offset 0x000e7ca8
	/* begin block 1 */
		// Start line: 822
		// Start offset: 0x000E7CA8
		// Variables:
	// 		struct tNode n; // stack offset -72
	// 		int fx; // $s4
	// 		int fz; // $s5
	// 		int a; // $s3
	// 		int b; // $s2
	// 		int c; // $v1
	// 		int min; // $s0
	// 		int flag; // $fp

		/* begin block 1.1 */
			// Start line: 822
			// Start offset: 0x000E7CA8
			// Variables:
		// 		struct VECTOR *where; // $s2
		// 		struct tNode *node; // $s0

			/* begin block 1.1.1 */
				// Start line: 822
				// Start offset: 0x000E7CA8
				// Variables:
			// 		int x; // $v1

				/* begin block 1.1.1.1 */
					// Start line: 822
					// Start offset: 0x000E7CA8
					// Variables:
				// 		struct tNode *pos; // $s0

					/* begin block 1.1.1.1.1 */
						// Start line: 822
						// Start offset: 0x000E7CA8
						// Variables:
					// 		struct VECTOR sp; // stack offset -56

						/* begin block 1.1.1.1.1.1 */
							// Start line: 822
							// Start offset: 0x000E7CA8

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 822
								// Start offset: 0x000E7CA8
								// Variables:
							// 		int z; // $v0
							// 		int x; // $a0
							/* end block 1.1.1.1.1.1.1 */
							// End offset: 0x000E7CA8
							// End Line: 822
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000E7CA8
						// End Line: 822

						/* begin block 1.1.1.1.1.2 */
							// Start line: 822
							// Start offset: 0x000E7D78
							// Variables:
						// 		int res; // $v0
						/* end block 1.1.1.1.1.2 */
						// End offset: 0x000E7D9C
						// End Line: 822
					/* end block 1.1.1.1.1 */
					// End offset: 0x000E7DA0
					// End Line: 822
				/* end block 1.1.1.1 */
				// End offset: 0x000E7DA0
				// End Line: 822
			/* end block 1.1.1 */
			// End offset: 0x000E7DA0
			// End Line: 822
		/* end block 1.1 */
		// End offset: 0x000E7DA0
		// End Line: 822

		/* begin block 1.2 */
			// Start line: 822
			// Start offset: 0x000E7DA0

			/* begin block 1.2.1 */
				// Start line: 822
				// Start offset: 0x000E7DA0
				// Variables:
			// 		int res; // $v0
			/* end block 1.2.1 */
			// End offset: 0x000E7DA0
			// End Line: 822
		/* end block 1.2 */
		// End offset: 0x000E7DA0
		// End Line: 822

		/* begin block 1.3 */
			// Start line: 822
			// Start offset: 0x000E7DA0

			/* begin block 1.3.1 */
				// Start line: 822
				// Start offset: 0x000E7DA0
				// Variables:
			// 		struct VECTOR sp; // stack offset -56

				/* begin block 1.3.1.1 */
					// Start line: 822
					// Start offset: 0x000E7DA0

					/* begin block 1.3.1.1.1 */
						// Start line: 822
						// Start offset: 0x000E7DA0
						// Variables:
					// 		int x; // $a3
					// 		int z; // $v0
					/* end block 1.3.1.1.1 */
					// End offset: 0x000E7DA0
					// End Line: 822
				/* end block 1.3.1.1 */
				// End offset: 0x000E7DA0
				// End Line: 822

				/* begin block 1.3.1.2 */
					// Start line: 822
					// Start offset: 0x000E7E84
					// Variables:
				// 		int res; // $v0
				/* end block 1.3.1.2 */
				// End offset: 0x000E7EA8
				// End Line: 822
			/* end block 1.3.1 */
			// End offset: 0x000E7EAC
			// End Line: 822
		/* end block 1.3 */
		// End offset: 0x000E7EAC
		// End Line: 822

		/* begin block 1.4 */
			// Start line: 839
			// Start offset: 0x000E7EAC

			/* begin block 1.4.1 */
				// Start line: 839
				// Start offset: 0x000E7EAC
				// Variables:
			// 		int res; // $a0
			/* end block 1.4.1 */
			// End offset: 0x000E7EAC
			// End Line: 839
		/* end block 1.4 */
		// End offset: 0x000E7EAC
		// End Line: 839

		/* begin block 1.5 */
			// Start line: 848
			// Start offset: 0x000E7F28

			/* begin block 1.5.1 */
				// Start line: 848
				// Start offset: 0x000E7F28
				// Variables:
			// 		struct VECTOR sp; // stack offset -56

				/* begin block 1.5.1.1 */
					// Start line: 848
					// Start offset: 0x000E7F28

					/* begin block 1.5.1.1.1 */
						// Start line: 848
						// Start offset: 0x000E7F28
						// Variables:
					// 		int x; // $v1
					// 		int z; // $v0
					/* end block 1.5.1.1.1 */
					// End offset: 0x000E7F28
					// End Line: 848
				/* end block 1.5.1.1 */
				// End offset: 0x000E7F28
				// End Line: 848

				/* begin block 1.5.1.2 */
					// Start line: 822
					// Start offset: 0x000E7F8C
					// Variables:
				// 		int res; // $v0
				/* end block 1.5.1.2 */
				// End offset: 0x000E7FB0
				// End Line: 822
			/* end block 1.5.1 */
			// End offset: 0x000E7FB4
			// End Line: 822
		/* end block 1.5 */
		// End offset: 0x000E7FB4
		// End Line: 822

		/* begin block 1.6 */
			// Start line: 850
			// Start offset: 0x000E7FB4

			/* begin block 1.6.1 */
				// Start line: 850
				// Start offset: 0x000E7FB4
				// Variables:
			// 		int res; // $a0
			/* end block 1.6.1 */
			// End offset: 0x000E7FB4
			// End Line: 850
		/* end block 1.6 */
		// End offset: 0x000E7FB4
		// End Line: 850

		/* begin block 1.7 */
			// Start line: 864
			// Start offset: 0x000E807C

			/* begin block 1.7.1 */
				// Start line: 864
				// Start offset: 0x000E807C
				// Variables:
			// 		struct VECTOR sp; // stack offset -56

				/* begin block 1.7.1.1 */
					// Start line: 864
					// Start offset: 0x000E807C

					/* begin block 1.7.1.1.1 */
						// Start line: 864
						// Start offset: 0x000E807C
						// Variables:
					// 		int x; // $v1
					// 		int z; // $v0
					/* end block 1.7.1.1.1 */
					// End offset: 0x000E807C
					// End Line: 864
				/* end block 1.7.1.1 */
				// End offset: 0x000E807C
				// End Line: 864

				/* begin block 1.7.1.2 */
					// Start line: 822
					// Start offset: 0x000E80D8
					// Variables:
				// 		int res; // $v0
				/* end block 1.7.1.2 */
				// End offset: 0x000E80FC
				// End Line: 822
			/* end block 1.7.1 */
			// End offset: 0x000E8100
			// End Line: 822
		/* end block 1.7 */
		// End offset: 0x000E8100
		// End Line: 822

		/* begin block 1.8 */
			// Start line: 865
			// Start offset: 0x000E8100

			/* begin block 1.8.1 */
				// Start line: 865
				// Start offset: 0x000E8100
				// Variables:
			// 		int res; // $a0
			/* end block 1.8.1 */
			// End offset: 0x000E8100
			// End Line: 865
		/* end block 1.8 */
		// End offset: 0x000E8100
		// End Line: 865
	/* end block 1 */
	// End offset: 0x000E822C
	// End Line: 880

	/* begin block 2 */
		// Start line: 1651
	/* end block 2 */
	// End Line: 1652

	/* begin block 3 */
		// Start line: 1654
	/* end block 3 */
	// End Line: 1655

int getInterpolatedDistance(VECTOR *pos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	bool bVar2;
	uint uVar3;
	uint uVar4;
	int iVar5;
	uint uVar6;
	uint uVar7;
	uint uVar8;
	int iVar9;
	int iVar10;
	uint local_48;
	uint local_44;
	uint local_40;
	ushort local_3c;
	uint local_38;
	uint local_30;

	uVar6 = pos->vz;
	local_48 = ((int)(pos->vx + ((int)uVar6 >> 1 & 0x1ffU)) >> 9) * 0x200 -
		((int)(uVar6 & 0x200) >> 1);
	local_44 = pos->vy;
	local_40 = ((int)uVar6 >> 9) << 9;
	local_38 = local_48 & 0xfffffc00;
	local_30 = local_40 & 0xfffffc00;
	if (((int)(uint)(byte)(&DAT_PATH__000e91a8)
		[((int)((int)local_30 >> 8 & 0x7fU) >> 3) + (local_38 >> 4 & 0x7c0)] >>
		((int)local_30 >> 8 & 7U) & 1U) == 0) {
		local_44 = 0;
	}
	else {
		local_44 = MapHeight((VECTOR *)&local_48);
		local_44 = local_44 ^ (local_44 ^ sdLevel) & 3;
	}
	iVar10 = pos->vz - local_40;
	iVar9 = (pos->vx - local_48) + (iVar10 >> 1);
	uVar7 = local_48 + 0x100;
	uVar3 = local_40 + 0x200;
	local_38 = uVar7 & 0xfffffc00;
	local_3c = (&DAT_PATH__000e9b00)
		[((int)local_48 >> 2 & 0x3f80U | (int)local_40 >> 9 & 0x7fU) ^ (local_44 & 1) * 0x2040
		^ (local_44 & 2) << 0xc];
	uVar6 = (uint)local_3c;
	local_30 = uVar3 & 0xfffffc00;
	local_48 = uVar7;
	local_40 = uVar3;
	if (((int)(uint)(byte)(&DAT_PATH__000e91a8)
		[((int)((int)local_30 >> 8 & 0x7fU) >> 3) + (local_38 >> 4 & 0x7c0)] >>
		((int)local_30 >> 8 & 7U) & 1U) == 0) {
		local_44 = 0;
	}
	else {
		local_44 = MapHeight((VECTOR *)&local_48);
		local_44 = local_44 ^ (local_44 ^ sdLevel) & 3;
	}
	local_3c = (&DAT_PATH__000e9b00)
		[((int)local_48 >> 2 & 0x3f80U | (int)local_40 >> 9 & 0x7fU) ^ (local_44 & 1) * 0x2040
		^ (local_44 & 2) << 0xc];
	uVar7 = (uint)local_3c;
	uVar3 = uVar7;
	if (uVar6 < uVar7) {
		uVar3 = uVar6;
	}
	if (iVar10 < iVar9) {
		local_48 = local_48 + 0x100;
		local_40 = local_40 - 0x200;
		local_38 = local_48 & 0xfffffc00;
		local_30 = local_40 & 0xfffffc00;
		if (((int)(uint)(byte)(&DAT_PATH__000e91a8)
			[((int)((int)local_30 >> 8 & 0x7fU) >> 3) + (local_38 >> 4 & 0x7c0)] >>
			((int)local_30 >> 8 & 7U) & 1U) == 0) {
			uVar4 = 0;
		}
		else {
			uVar4 = MapHeight((VECTOR *)&local_48);
			uVar4 = uVar4 ^ (uVar4 ^ sdLevel) & 3;
		}
		uVar4 = (uint)(ushort)(&DAT_PATH__000e9b00)
			[((int)local_48 >> 2 & 0x3f80U | (int)local_40 >> 9 & 0x7fU) ^
			(uVar4 & 1) * 0x2040 ^ (uVar4 & 2) << 0xc];
		uVar8 = uVar4;
		if (uVar3 < uVar4) {
			uVar8 = uVar3;
		}
		uVar8 = uVar8 + 0x155;
		bVar1 = 0xffff < uVar8;
		bVar2 = uVar8 < uVar6;
		if (bVar1) {
			uVar8 = 0xffff;
		}
		if (!bVar1 && bVar2) {
			uVar6 = uVar8;
		}
		if (uVar8 < uVar7) {
			uVar7 = uVar8;
		}
		iVar5 = uVar4 - uVar6;
		if (uVar8 < uVar4) {
			iVar5 = uVar8 - uVar6;
			uVar4 = uVar8;
		}
		iVar5 = iVar5 * iVar9;
		iVar10 = (uVar7 - uVar4) * iVar10;
	}
	else {
		local_48 = local_48 - 0x200;
		local_38 = local_48 & 0xfffffc00;
		local_30 = local_40 & 0xfffffc00;
		if (((int)(uint)(byte)(&DAT_PATH__000e91a8)
			[((int)((int)local_30 >> 8 & 0x7fU) >> 3) + (local_38 >> 4 & 0x7c0)] >>
			((int)local_30 >> 8 & 7U) & 1U) == 0) {
			uVar4 = 0;
		}
		else {
			uVar4 = MapHeight((VECTOR *)&local_48);
			uVar4 = uVar4 ^ (uVar4 ^ sdLevel) & 3;
		}
		uVar4 = (uint)(ushort)(&DAT_PATH__000e9b00)
			[((int)local_48 >> 2 & 0x3f80U | (int)local_40 >> 9 & 0x7fU) ^
			(uVar4 & 1) * 0x2040 ^ (uVar4 & 2) << 0xc];
		uVar8 = uVar4;
		if (uVar3 < uVar4) {
			uVar8 = uVar3;
		}
		uVar8 = uVar8 + 0x155;
		bVar1 = 0xffff < uVar8;
		bVar2 = uVar8 < uVar6;
		if (bVar1) {
			uVar8 = 0xffff;
		}
		if (!bVar1 && bVar2) {
			uVar6 = uVar8;
		}
		if (uVar8 < uVar7) {
			uVar7 = uVar8;
		}
		iVar5 = uVar4 - uVar6;
		if (uVar8 < uVar4) {
			iVar5 = uVar8 - uVar6;
			uVar4 = uVar8;
		}
		iVar5 = iVar5 * iVar10;
		iVar10 = (uVar7 - uVar4) * iVar9;
	}
	uVar6 = uVar6 + (iVar5 + iVar10 >> 9);
	DAT_PATH__000e9ac8 = uVar6 ^ (uVar6 & 1 ^ uVar6) & 1;
	return DAT_PATH__000e9ac8;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ addCivs()
 // line 891, offset 0x000e822c
	/* begin block 1 */
		// Start line: 893
		// Start offset: 0x000E822C
		// Variables:
	// 		struct _CAR_DATA *cp; // $t5

		/* begin block 1.1 */
			// Start line: 898
			// Start offset: 0x000E8260
			// Variables:
		// 		int where; // $a3

			/* begin block 1.1.1 */
				// Start line: 900
				// Start offset: 0x000E8260
				// Variables:
			// 		int vx; // $a3
			// 		int vz; // $a1
			// 		int x; // $a3
			// 		int z; // $t0
			/* end block 1.1.1 */
			// End offset: 0x000E8260
			// End Line: 900

			/* begin block 1.1.2 */
				// Start line: 900
				// Start offset: 0x000E8260
				// Variables:
			// 		int vx; // $t1
			// 		int vz; // $t2
			// 		int x; // $t1
			// 		int z; // $a1
			/* end block 1.1.2 */
			// End offset: 0x000E8354
			// End Line: 922
		/* end block 1.1 */
		// End offset: 0x000E8354
		// End Line: 923
	/* end block 1 */
	// End offset: 0x000E836C
	// End Line: 925

	/* begin block 2 */
		// Start line: 1793
	/* end block 2 */
	// End Line: 1794

	/* begin block 3 */
		// Start line: 1805
	/* end block 3 */
	// End Line: 1806

	/* begin block 4 */
		// Start line: 1806
	/* end block 4 */
	// End Line: 1807

	/* begin block 5 */
		// Start line: 1807
	/* end block 5 */
	// End Line: 1808

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void addCivs(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	uint uVar2;
	int iVar3;
	uint uVar4;
	uint uVar5;
	int iVar6;
	uint uVar7;
	int iVar8;
	uint uVar9;
	int iVar10;
	int iVar11;
	_CAR_DATA *p_Var12;

	p_Var12 = car_data;
	do {
		if (p_Var12->controlType == '\x02') {
			iVar11 = (int)(p_Var12->hd).oBox.radii[2].vx;
			iVar6 = (p_Var12->hd).oBox.location.vx;
			iVar10 = (int)(p_Var12->hd).oBox.radii[2].vz;
			iVar8 = (p_Var12->hd).oBox.location.vz;
			uVar4 = iVar6 + iVar11 >> 8 & 0x7e;
			uVar2 = iVar8 + iVar10 >> 8;
			uVar5 = uVar2 & 0x7e;
			iVar3 = (int)uVar5 >> 3;
			bVar1 = (byte)(3 << (uVar2 & 6));
			uVar7 = iVar6 - iVar11 >> 8 & 0x7e;
			(&DAT_PATH__000e91a8)[iVar3 + uVar4 * 0x10] =
				bVar1 ^ (&DAT_PATH__000e91a8)[iVar3 + uVar4 * 0x10];
			uVar9 = iVar8 - iVar10 >> 8;
			(&DAT_PATH__000e91a8)[iVar3 + (uVar4 + 1) * 0x10] =
				bVar1 ^ (&DAT_PATH__000e91a8)[iVar3 + (uVar4 + 1) * 0x10];
			uVar2 = uVar9 & 0x7e;
			if ((uVar4 ^ uVar5 << 8) == uVar7) {
				if (uVar2 != 0) goto LAB_PATH__000e8310;
			}
			else {
				if (uVar2 << 8 != 1) {
				LAB_PATH__000e8310:
					bVar1 = (byte)(3 << (uVar9 & 6));
					(&DAT_PATH__000e91a8)[((int)uVar2 >> 3) + uVar7 * 0x10] =
						bVar1 ^ (&DAT_PATH__000e91a8)[((int)uVar2 >> 3) + uVar7 * 0x10];
					(&DAT_PATH__000e91a8)[((int)uVar2 >> 3) + (uVar7 + 1) * 0x10] =
						bVar1 ^ (&DAT_PATH__000e91a8)[((int)uVar2 >> 3) + (uVar7 + 1) * 0x10];
				}
			}
		}
		p_Var12 = p_Var12 + 1;
		if ((_CAR_DATA *)0xd4697 < p_Var12) {
			return;
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateCopMap()
 // line 933, offset 0x000e836c
	/* begin block 1 */
		// Start line: 935
		// Start offset: 0x000E836C

		/* begin block 1.1 */
			// Start line: 939
			// Start offset: 0x000E83C0
		/* end block 1.1 */
		// End offset: 0x000E83C0
		// End Line: 939

		/* begin block 1.2 */
			// Start line: 946
			// Start offset: 0x000E83FC
			// Variables:
		// 		struct tNode startNode; // stack offset -72

			/* begin block 1.2.1 */
				// Start line: 952
				// Start offset: 0x000E843C
				// Variables:
			// 		struct _CAR_DATA *cp; // $a0
			/* end block 1.2.1 */
			// End offset: 0x000E843C
			// End Line: 952

			/* begin block 1.2.2 */
				// Start line: 934
				// Start offset: 0x000E8500

				/* begin block 1.2.2.1 */
					// Start line: 934
					// Start offset: 0x000E8500

					/* begin block 1.2.2.1.1 */
						// Start line: 934
						// Start offset: 0x000E8500

						/* begin block 1.2.2.1.1.1 */
							// Start line: 934
							// Start offset: 0x000E8500
							// Variables:
						// 		int i; // $a1

							/* begin block 1.2.2.1.1.1.1 */
								// Start line: 934
								// Start offset: 0x000E8524
								// Variables:
							// 		int d; // $v0
							/* end block 1.2.2.1.1.1.1 */
							// End offset: 0x000E8554
							// End Line: 934
						/* end block 1.2.2.1.1.1 */
						// End offset: 0x000E8564
						// End Line: 934
					/* end block 1.2.2.1.1 */
					// End offset: 0x000E8564
					// End Line: 934
				/* end block 1.2.2.1 */
				// End offset: 0x000E8564
				// End Line: 934
			/* end block 1.2.2 */
			// End offset: 0x000E8564
			// End Line: 934

			/* begin block 1.2.3 */
				// Start line: 934
				// Start offset: 0x000E8564

				/* begin block 1.2.3.1 */
					// Start line: 934
					// Start offset: 0x000E8564
					// Variables:
				// 		int x; // $v0

					/* begin block 1.2.3.1.1 */
						// Start line: 934
						// Start offset: 0x000E8564

						/* begin block 1.2.3.1.1.1 */
							// Start line: 934
							// Start offset: 0x000E8564
							// Variables:
						// 		struct VECTOR sp; // stack offset -56

							/* begin block 1.2.3.1.1.1.1 */
								// Start line: 934
								// Start offset: 0x000E8564

								/* begin block 1.2.3.1.1.1.1.1 */
									// Start line: 934
									// Start offset: 0x000E8564
									// Variables:
								// 		int z; // $v0
								// 		int x; // $v1
								/* end block 1.2.3.1.1.1.1.1 */
								// End offset: 0x000E8564
								// End Line: 934
							/* end block 1.2.3.1.1.1.1 */
							// End offset: 0x000E8564
							// End Line: 934

							/* begin block 1.2.3.1.1.1.2 */
								// Start line: 934
								// Start offset: 0x000E8604
								// Variables:
							// 		int res; // $v0
							/* end block 1.2.3.1.1.1.2 */
							// End offset: 0x000E8628
							// End Line: 934
						/* end block 1.2.3.1.1.1 */
						// End offset: 0x000E862C
						// End Line: 934
					/* end block 1.2.3.1.1 */
					// End offset: 0x000E862C
					// End Line: 934
				/* end block 1.2.3.1 */
				// End offset: 0x000E862C
				// End Line: 934
			/* end block 1.2.3 */
			// End offset: 0x000E862C
			// End Line: 934

			/* begin block 1.2.4 */
				// Start line: 934
				// Start offset: 0x000E862C
				// Variables:
			// 		struct tNode n; // stack offset -56
			// 		int fx; // $v1
			// 		int fz; // $v0

				/* begin block 1.2.4.1 */
					// Start line: 934
					// Start offset: 0x000E8660

					/* begin block 1.2.4.1.1 */
						// Start line: 934
						// Start offset: 0x000E8660
						// Variables:
					// 		int dz; // $a0
					// 		int dx; // $v0
					/* end block 1.2.4.1.1 */
					// End offset: 0x000E8660
					// End Line: 934
				/* end block 1.2.4.1 */
				// End offset: 0x000E8660
				// End Line: 934

				/* begin block 1.2.4.2 */
					// Start line: 934
					// Start offset: 0x000E8660

					/* begin block 1.2.4.2.1 */
						// Start line: 934
						// Start offset: 0x000E8660
						// Variables:
					// 		unsigned int parent; // $a2
					// 		unsigned int i; // $a3
					/* end block 1.2.4.2.1 */
					// End offset: 0x000E8774
					// End Line: 934
				/* end block 1.2.4.2 */
				// End offset: 0x000E8774
				// End Line: 934

				/* begin block 1.2.4.3 */
					// Start line: 986
					// Start offset: 0x000E8774

					/* begin block 1.2.4.3.1 */
						// Start line: 986
						// Start offset: 0x000E8774
						// Variables:
					// 		int dz; // $a0
					// 		int dx; // $v0
					/* end block 1.2.4.3.1 */
					// End offset: 0x000E8774
					// End Line: 986
				/* end block 1.2.4.3 */
				// End offset: 0x000E8774
				// End Line: 986

				/* begin block 1.2.4.4 */
					// Start line: 986
					// Start offset: 0x000E8774

					/* begin block 1.2.4.4.1 */
						// Start line: 986
						// Start offset: 0x000E8774
						// Variables:
					// 		unsigned int parent; // $a2
					// 		unsigned int i; // $a3
					/* end block 1.2.4.4.1 */
					// End offset: 0x000E88B4
					// End Line: 987
				/* end block 1.2.4.4 */
				// End offset: 0x000E88B4
				// End Line: 987

				/* begin block 1.2.4.5 */
					// Start line: 989
					// Start offset: 0x000E88B4

					/* begin block 1.2.4.5.1 */
						// Start line: 989
						// Start offset: 0x000E88B4
						// Variables:
					// 		int dz; // $a0
					// 		int dx; // $v0
					/* end block 1.2.4.5.1 */
					// End offset: 0x000E88B4
					// End Line: 989
				/* end block 1.2.4.5 */
				// End offset: 0x000E88B4
				// End Line: 989

				/* begin block 1.2.4.6 */
					// Start line: 989
					// Start offset: 0x000E88B4

					/* begin block 1.2.4.6.1 */
						// Start line: 989
						// Start offset: 0x000E88B4
						// Variables:
					// 		unsigned int parent; // $a2
					// 		unsigned int i; // $a3
					/* end block 1.2.4.6.1 */
					// End offset: 0x000E89BC
					// End Line: 990
				/* end block 1.2.4.6 */
				// End offset: 0x000E89BC
				// End Line: 990

				/* begin block 1.2.4.7 */
					// Start line: 934
					// Start offset: 0x000E89C4

					/* begin block 1.2.4.7.1 */
						// Start line: 934
						// Start offset: 0x000E89C4
						// Variables:
					// 		int dz; // $a0
					// 		int dx; // $v0
					/* end block 1.2.4.7.1 */
					// End offset: 0x000E89C4
					// End Line: 934
				/* end block 1.2.4.7 */
				// End offset: 0x000E89C4
				// End Line: 934

				/* begin block 1.2.4.8 */
					// Start line: 934
					// Start offset: 0x000E89C4

					/* begin block 1.2.4.8.1 */
						// Start line: 934
						// Start offset: 0x000E89C4
						// Variables:
					// 		unsigned int parent; // $a2
					// 		unsigned int i; // $a3
					/* end block 1.2.4.8.1 */
					// End offset: 0x000E8AD8
					// End Line: 934
				/* end block 1.2.4.8 */
				// End offset: 0x000E8AD8
				// End Line: 934

				/* begin block 1.2.4.9 */
					// Start line: 996
					// Start offset: 0x000E8AD8

					/* begin block 1.2.4.9.1 */
						// Start line: 996
						// Start offset: 0x000E8AD8
						// Variables:
					// 		int dz; // $a0
					// 		int dx; // $v0
					/* end block 1.2.4.9.1 */
					// End offset: 0x000E8AD8
					// End Line: 996
				/* end block 1.2.4.9 */
				// End offset: 0x000E8AD8
				// End Line: 996

				/* begin block 1.2.4.10 */
					// Start line: 996
					// Start offset: 0x000E8AD8

					/* begin block 1.2.4.10.1 */
						// Start line: 996
						// Start offset: 0x000E8AD8
						// Variables:
					// 		unsigned int parent; // $a2
					// 		unsigned int i; // $a3
					/* end block 1.2.4.10.1 */
					// End offset: 0x000E8C18
					// End Line: 997
				/* end block 1.2.4.10 */
				// End offset: 0x000E8C18
				// End Line: 997

				/* begin block 1.2.4.11 */
					// Start line: 999
					// Start offset: 0x000E8C18

					/* begin block 1.2.4.11.1 */
						// Start line: 999
						// Start offset: 0x000E8C18
						// Variables:
					// 		int dz; // $a0
					// 		int dx; // $v0
					/* end block 1.2.4.11.1 */
					// End offset: 0x000E8C18
					// End Line: 999
				/* end block 1.2.4.11 */
				// End offset: 0x000E8C18
				// End Line: 999

				/* begin block 1.2.4.12 */
					// Start line: 999
					// Start offset: 0x000E8C18

					/* begin block 1.2.4.12.1 */
						// Start line: 999
						// Start offset: 0x000E8C18
						// Variables:
					// 		unsigned int parent; // $a2
					// 		unsigned int i; // $a3
					/* end block 1.2.4.12.1 */
					// End offset: 0x000E8D18
					// End Line: 999
				/* end block 1.2.4.12 */
				// End offset: 0x000E8D18
				// End Line: 999
			/* end block 1.2.4 */
			// End offset: 0x000E8D18
			// End Line: 999
		/* end block 1.2 */
		// End offset: 0x000E8D18
		// End Line: 999

		/* begin block 1.3 */
			// Start line: 1010
			// Start offset: 0x000E8D54
			// Variables:
		// 		int i; // $s0

			/* begin block 1.3.1 */
				// Start line: 934
				// Start offset: 0x000E8DF4
			/* end block 1.3.1 */
			// End offset: 0x000E8DFC
			// End Line: 934
		/* end block 1.3 */
		// End offset: 0x000E8DFC
		// End Line: 1024

		/* begin block 1.4 */
			// Start line: 1027
			// Start offset: 0x000E8DFC
			// Variables:
		// 		int i; // $a1
		// 		int maxRet; // $a0
		/* end block 1.4 */
		// End offset: 0x000E8E70
		// End Line: 1038

		/* begin block 1.5 */
			// Start line: 1041
			// Start offset: 0x000E8E70
			// Variables:
		// 		int dx; // $a0
		// 		int dy; // $v1
		// 		int dz; // $v0
		/* end block 1.5 */
		// End offset: 0x000E8F00
		// End Line: 1045
	/* end block 1 */
	// End offset: 0x000E8F00
	// End Line: 1046

	/* begin block 2 */
		// Start line: 1938
	/* end block 2 */
	// End Line: 1939

	/* begin block 3 */
		// Start line: 1947
	/* end block 3 */
	// End Line: 1948

	/* begin block 4 */
		// Start line: 1948
	/* end block 4 */
	// End Line: 1949

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdateCopMap(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	uint uVar2;
	ushort uVar3;
	int *piVar4;
	ushort *puVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	uint uVar9;
	uint uVar10;
	uint local_48;
	uint local_44;
	uint local_40;
	undefined4 local_3c;
	uint local_38;
	uint local_30;

	BloodyHell();
	if ((player_position_known == 1) || (CameraCnt == 6)) {
		DAT_PATH__000f1b00 = 0;
		setMem16(&DAT_PATH__000e9b00, 0xfffe, 0x4000);
		DAT_PATH__000e99ac = 3;
	}
	if (DAT_PATH__000f1b00 == 0) {
		if ((player.playerType == '\x01') && ((CopsCanSeePlayer != 0 || (numActiveCops == 0)))) {
			iVar1 = (int)player.playerCarId;
			DAT_PATH__000e9ab8 =
				car_data[iVar1].hd.where.t[0] + (*(int *)(car_data[iVar1].st + 0x1c) + 0x800 >> 0xc) * 8;
			DAT_PATH__000e9abc =
				car_data[iVar1].hd.where.t[1] + (*(int *)(car_data[iVar1].st + 0x20) + 0x800 >> 0xc) * 4;
			DAT_PATH__000e9ac0 =
				car_data[iVar1].hd.where.t[2] + (*(int *)(car_data[iVar1].st + 0x24) + 0x800 >> 0xc) * 8;
		}
		else {
			if (DAT_PATH__000e9abc == -0x304f) {
				DAT_PATH__000e9ab8 = player.pos[0];
				DAT_PATH__000e9abc = player.pos[1];
				DAT_PATH__000e9ac0 = player.pos[2];
			}
		}
		puVar5 = &DAT_PATH__000e9b00;
		iVar1 = 0x3fff;
		do {
			uVar2 = (uint)*puVar5 + 0x2000;
			if ((uVar2 & 1) != 0) {
				uVar2 = uVar2 ^ 1;
			}
			uVar3 = (ushort)uVar2;
			if (0xfffe < uVar2) {
				uVar3 = 0xfffe;
			}
			*puVar5 = uVar3;
			iVar1 = iVar1 + -1;
			puVar5 = puVar5 + 1;
		} while (-1 < iVar1);
		local_48 = ((int)(DAT_PATH__000e9ab8 + ((int)DAT_PATH__000e9ac0 >> 1 & 0x1ffU)) >> 9) * 0x200 -
			((int)(DAT_PATH__000e9ac0 & 0x200) >> 1);
		local_40 = ((int)DAT_PATH__000e9ac0 >> 9) << 9;
		local_44 = DAT_PATH__000e9abc;
		local_38 = local_48 & 0xfffffc00;
		DAT_PATH__000f279c = 0;
		local_30 = local_40 & 0xfffffc00;
		if (((int)(uint)(byte)(&DAT_PATH__000e91a8)
			[((int)((int)local_30 >> 8 & 0x7fU) >> 3) + (local_38 >> 4 & 0x7c0)] >>
			((int)local_30 >> 8 & 7U) & 1U) == 0) {
			local_44 = 0;
		}
		else {
			local_44 = MapHeight((VECTOR *)(tNode *)&local_48);
			local_44 = local_44 ^ (local_44 ^ sdLevel) & 3;
		}
		iVar1 = local_48 - DAT_PATH__000e9ab8;
		if ((int)(DAT_PATH__000e9ac0 - local_40) <
			(int)((DAT_PATH__000e9ab8 - local_48) + ((int)(DAT_PATH__000e9ac0 - local_40) >> 1))) {
			iVar1 = SquareRoot0(iVar1 * iVar1 +
				(local_40 - DAT_PATH__000e9ac0) * (local_40 - DAT_PATH__000e9ac0));
			uVar2 = iVar1 / 2 & 0xffff;
			if (DAT_PATH__000f279c != 0xc6) {
				setDistance((tNode *)&local_48, (ushort)uVar2);
				uVar10 = DAT_PATH__000f279c + 1;
				uVar8 = uVar10 >> 1;
				if (uVar8 != 0) {
					uVar3 = (&DAT_PATH__000f1b14)[uVar8 * 8];
					while (uVar2 < uVar3) {
						(&DAT_PATH__000f1b08)[uVar10 * 4] = (&DAT_PATH__000f1b08)[uVar8 * 4];
						(&DAT_PATH__000f1b0c)[uVar10 * 4] = (&DAT_PATH__000f1b0c)[uVar8 * 4];
						(&DAT_PATH__000f1b10)[uVar10 * 4] = (&DAT_PATH__000f1b10)[uVar8 * 4];
						uVar9 = uVar8 >> 1;
						*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) =
							*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8);
						uVar10 = uVar8;
						if (uVar9 == 0) break;
						uVar3 = (&DAT_PATH__000f1b14)[uVar9 * 8];
						uVar8 = uVar9;
					}
				}
				DAT_PATH__000f279c = DAT_PATH__000f279c + 1;
				(&DAT_PATH__000f1b08)[uVar10 * 4] = local_48;
				(&DAT_PATH__000f1b0c)[uVar10 * 4] = local_44;
				(&DAT_PATH__000f1b10)[uVar10 * 4] = local_40;
				*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) = local_3c;
			}
			local_48 = local_48 + 0x100;
			local_40 = local_40 + 0x200;
			iVar1 = SquareRoot0((local_48 - DAT_PATH__000e9ab8) * (local_48 - DAT_PATH__000e9ab8) +
				(local_40 - DAT_PATH__000e9ac0) * (local_40 - DAT_PATH__000e9ac0));
			uVar2 = iVar1 / 2 & 0xffff;
			if (DAT_PATH__000f279c != 0xc6) {
				setDistance((tNode *)&local_48, (ushort)uVar2);
				uVar10 = DAT_PATH__000f279c + 1;
				uVar8 = uVar10 >> 1;
				if (uVar8 != 0) {
					uVar3 = (&DAT_PATH__000f1b14)[uVar8 * 8];
					while (uVar2 < uVar3) {
						(&DAT_PATH__000f1b08)[uVar10 * 4] = (&DAT_PATH__000f1b08)[uVar8 * 4];
						(&DAT_PATH__000f1b0c)[uVar10 * 4] = (&DAT_PATH__000f1b0c)[uVar8 * 4];
						(&DAT_PATH__000f1b10)[uVar10 * 4] = (&DAT_PATH__000f1b10)[uVar8 * 4];
						uVar9 = uVar8 >> 1;
						*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) =
							*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8);
						uVar10 = uVar8;
						if (uVar9 == 0) break;
						uVar3 = (&DAT_PATH__000f1b14)[uVar9 * 8];
						uVar8 = uVar9;
					}
				}
				DAT_PATH__000f279c = DAT_PATH__000f279c + 1;
				(&DAT_PATH__000f1b08)[uVar10 * 4] = local_48;
				(&DAT_PATH__000f1b0c)[uVar10 * 4] = local_44;
				(&DAT_PATH__000f1b10)[uVar10 * 4] = local_40;
				*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) = local_3c;
			}
			local_48 = local_48 + 0x100;
			local_40 = local_40 + -0x200;
			iVar1 = SquareRoot0((local_48 - DAT_PATH__000e9ab8) * (local_48 - DAT_PATH__000e9ab8) +
				(local_40 - DAT_PATH__000e9ac0) * (local_40 - DAT_PATH__000e9ac0));
			uVar2 = iVar1 / 2 & 0xffff;
			if (DAT_PATH__000f279c == 0xc6) goto LAB_PATH__000e8dfc;
			setDistance((tNode *)&local_48, (ushort)uVar2);
			uVar8 = DAT_PATH__000f279c + 1;
			uVar10 = uVar8 >> 1;
			if ((uVar10 != 0) && (uVar2 < (ushort)(&DAT_PATH__000f1b14)[uVar10 * 8])) {
				iVar1 = uVar8 * 0x10;
				do {
					uVar8 = uVar10;
					*(undefined4 *)((int)&DAT_PATH__000f1b08 + iVar1) = (&DAT_PATH__000f1b08)[uVar8 * 4];
					*(undefined4 *)((int)&DAT_PATH__000f1b0c + iVar1) = (&DAT_PATH__000f1b0c)[uVar8 * 4];
					*(undefined4 *)((int)&DAT_PATH__000f1b10 + iVar1) = (&DAT_PATH__000f1b10)[uVar8 * 4];
					uVar10 = uVar8 >> 1;
					*(undefined4 *)((int)&DAT_PATH__000f1b14 + iVar1) =
						*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8);
					if (uVar10 == 0) break;
					iVar1 = uVar8 << 4;
				} while (uVar2 < (ushort)(&DAT_PATH__000f1b14)[uVar10 * 8]);
			}
		}
		else {
			iVar1 = SquareRoot0(iVar1 * iVar1 +
				(local_40 - DAT_PATH__000e9ac0) * (local_40 - DAT_PATH__000e9ac0));
			uVar2 = iVar1 / 2 & 0xffff;
			if (DAT_PATH__000f279c != 0xc6) {
				setDistance((tNode *)&local_48, (ushort)uVar2);
				uVar10 = DAT_PATH__000f279c + 1;
				uVar8 = uVar10 >> 1;
				if (uVar8 != 0) {
					uVar3 = (&DAT_PATH__000f1b14)[uVar8 * 8];
					while (uVar2 < uVar3) {
						(&DAT_PATH__000f1b08)[uVar10 * 4] = (&DAT_PATH__000f1b08)[uVar8 * 4];
						(&DAT_PATH__000f1b0c)[uVar10 * 4] = (&DAT_PATH__000f1b0c)[uVar8 * 4];
						(&DAT_PATH__000f1b10)[uVar10 * 4] = (&DAT_PATH__000f1b10)[uVar8 * 4];
						uVar9 = uVar8 >> 1;
						*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) =
							*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8);
						uVar10 = uVar8;
						if (uVar9 == 0) break;
						uVar3 = (&DAT_PATH__000f1b14)[uVar9 * 8];
						uVar8 = uVar9;
					}
				}
				DAT_PATH__000f279c = DAT_PATH__000f279c + 1;
				(&DAT_PATH__000f1b08)[uVar10 * 4] = local_48;
				(&DAT_PATH__000f1b0c)[uVar10 * 4] = local_44;
				(&DAT_PATH__000f1b10)[uVar10 * 4] = local_40;
				*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) = local_3c;
			}
			local_48 = local_48 + 0x100;
			local_40 = local_40 + 0x200;
			iVar1 = SquareRoot0((local_48 - DAT_PATH__000e9ab8) * (local_48 - DAT_PATH__000e9ab8) +
				(local_40 - DAT_PATH__000e9ac0) * (local_40 - DAT_PATH__000e9ac0));
			uVar2 = iVar1 / 2 & 0xffff;
			if (DAT_PATH__000f279c != 0xc6) {
				setDistance((tNode *)&local_48, (ushort)uVar2);
				uVar10 = DAT_PATH__000f279c + 1;
				uVar8 = uVar10 >> 1;
				if (uVar8 != 0) {
					uVar3 = (&DAT_PATH__000f1b14)[uVar8 * 8];
					while (uVar2 < uVar3) {
						(&DAT_PATH__000f1b08)[uVar10 * 4] = (&DAT_PATH__000f1b08)[uVar8 * 4];
						(&DAT_PATH__000f1b0c)[uVar10 * 4] = (&DAT_PATH__000f1b0c)[uVar8 * 4];
						(&DAT_PATH__000f1b10)[uVar10 * 4] = (&DAT_PATH__000f1b10)[uVar8 * 4];
						uVar9 = uVar8 >> 1;
						*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) =
							*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8);
						uVar10 = uVar8;
						if (uVar9 == 0) break;
						uVar3 = (&DAT_PATH__000f1b14)[uVar9 * 8];
						uVar8 = uVar9;
					}
				}
				DAT_PATH__000f279c = DAT_PATH__000f279c + 1;
				(&DAT_PATH__000f1b08)[uVar10 * 4] = local_48;
				(&DAT_PATH__000f1b0c)[uVar10 * 4] = local_44;
				(&DAT_PATH__000f1b10)[uVar10 * 4] = local_40;
				*(undefined4 *)(&DAT_PATH__000f1b14 + uVar10 * 8) = local_3c;
			}
			local_48 = local_48 + -0x200;
			iVar1 = SquareRoot0((local_48 - DAT_PATH__000e9ab8) * (local_48 - DAT_PATH__000e9ab8) +
				(local_40 - DAT_PATH__000e9ac0) * (local_40 - DAT_PATH__000e9ac0));
			uVar2 = iVar1 / 2 & 0xffff;
			if (DAT_PATH__000f279c == 0xc6) goto LAB_PATH__000e8dfc;
			setDistance((tNode *)&local_48, (ushort)uVar2);
			uVar8 = DAT_PATH__000f279c + 1;
			uVar10 = uVar8 >> 1;
			if ((uVar10 != 0) && (uVar2 < (ushort)(&DAT_PATH__000f1b14)[uVar10 * 8])) {
				iVar1 = uVar8 * 0x10;
				do {
					uVar8 = uVar10;
					*(undefined4 *)((int)&DAT_PATH__000f1b08 + iVar1) = (&DAT_PATH__000f1b08)[uVar8 * 4];
					*(undefined4 *)((int)&DAT_PATH__000f1b0c + iVar1) = (&DAT_PATH__000f1b0c)[uVar8 * 4];
					*(undefined4 *)((int)&DAT_PATH__000f1b10 + iVar1) = (&DAT_PATH__000f1b10)[uVar8 * 4];
					uVar10 = uVar8 >> 1;
					*(undefined4 *)((int)&DAT_PATH__000f1b14 + iVar1) =
						*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8);
					if (uVar10 == 0) break;
					iVar1 = uVar8 << 4;
				} while (uVar2 < (ushort)(&DAT_PATH__000f1b14)[uVar10 * 8]);
			}
		}
		DAT_PATH__000f279c = DAT_PATH__000f279c + 1;
		(&DAT_PATH__000f1b08)[uVar8 * 4] = local_48;
		(&DAT_PATH__000f1b0c)[uVar8 * 4] = local_44;
		(&DAT_PATH__000f1b10)[uVar8 * 4] = local_40;
		*(undefined4 *)(&DAT_PATH__000f1b14 + uVar8 * 8) = local_3c;
	}
	else {
		addCivs();
		iVar1 = DAT_PATH__000f2798 << 2;
		uVar2 = DAT_PATH__000f2798;
		if (6 < DAT_PATH__000f2798) {
			uVar2 = 6;
			iVar1 = 0x18;
		}
		iVar1 = iRam000f27c0 + iVar1 * -4 + uVar2 * -5;
		if (DAT_PATH__000e99ac != 0) {
			DAT_PATH__000e99ac = DAT_PATH__000e99ac + -1;
			iVar1 = iVar1 + 0x3c;
		}
		iVar7 = iVar1 + -1;
		if (iVar1 < 0x24) {
			iVar7 = 0x23;
		}
		while (iVar7 != -1) {
			iVar7 = iVar7 + -1;
			iterate();
		}
		addCivs();
	}
LAB_PATH__000e8dfc:
	piVar4 = &DAT_PATH__000f27a0;
	iVar7 = 6;
	DAT_PATH__000f1b00 = DAT_PATH__000f1b00 + 1;
	iVar1 = DAT_PATH__000f27bc;
	do {
		if (iVar1 < *piVar4) {
			iVar1 = *piVar4;
		}
		iVar7 = iVar7 + -1;
		piVar4 = piVar4 + 1;
	} while (-1 < iVar7);
	if ((DAT_PATH__000e99a8 < DAT_PATH__000f1b00) ||
		(2000 < (int)((uint)(ushort)DAT_PATH__000f1b24 - iVar1))) {
		DAT_PATH__000f1b00 = 0;
	}
	iVar6 = DAT_PATH__000e9ab8 - player.pos[0] >> 4;
	iVar7 = DAT_PATH__000e9abc - player.pos[1] >> 4;
	iVar1 = (int)(DAT_PATH__000e9ac0 - player.pos[2]) >> 4;
	DAT_PATH__000e9acc = iVar6 * iVar6 + iVar7 * iVar7 + iVar1 * iVar1;
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ getHeadingToPlayer(int vx /*$s4*/, int vy /*$a1*/, int vz /*$s3*/)
 // line 1050, offset 0x000e8f00
	/* begin block 1 */
		// Start line: 1051
		// Start offset: 0x000E8F00
		// Variables:
	// 		int d1; // $s2
	// 		int d2; // $s1
	// 		int d3; // $s0
	// 		struct VECTOR pos; // stack offset -48

		/* begin block 1.1 */
			// Start line: 1051
			// Start offset: 0x000E8F00
			// Variables:
		// 		int dx; // $a3
		// 		int dy; // $v1
		// 		int dz; // $v0
		// 		int playerHereDistSq; // $a3

			/* begin block 1.1.1 */
				// Start line: 1071
				// Start offset: 0x000E8F98
			/* end block 1.1.1 */
			// End offset: 0x000E8F98
			// End Line: 1073
		/* end block 1.1 */
		// End offset: 0x000E8F98
		// End Line: 1074

		/* begin block 1.2 */
			// Start line: 1098
			// Start offset: 0x000E8FF8
		/* end block 1.2 */
		// End offset: 0x000E9024
		// End Line: 1100

		/* begin block 1.3 */
			// Start line: 1102
			// Start offset: 0x000E9030
		/* end block 1.3 */
		// End offset: 0x000E9058
		// End Line: 1110

		/* begin block 1.4 */
			// Start line: 1106
			// Start offset: 0x000E9058
		/* end block 1.4 */
		// End offset: 0x000E90A4
		// End Line: 1111
	/* end block 1 */
	// End offset: 0x000E90A4
	// End Line: 1112

	/* begin block 2 */
		// Start line: 2208
	/* end block 2 */
	// End Line: 2209

	/* begin block 3 */
		// Start line: 2209
	/* end block 3 */
	// End Line: 2210

	/* begin block 4 */
		// Start line: 2214
	/* end block 4 */
	// End Line: 2215

	/* begin block 5 */
		// Start line: 2228
	/* end block 5 */
	// End Line: 2229

int getHeadingToPlayer(int vx, int vy, int vz)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	int iVar3;
	int val;
	int iVar4;
	VECTOR local_30;

	iVar4 = vx - player.pos[0] >> 4;
	iVar3 = vy - player.pos[1] >> 4;
	iVar1 = vz - player.pos[2] >> 4;
	val = 0xfa4;
	if (DAT_PATH__000e9acc << 1 <= (iVar4 * iVar4 + iVar3 * iVar3 + iVar1 * iVar1) * 3) {
		local_30.vx = vx + -0x80;
		local_30.vy = vy;
		local_30.vz = vz + -0x80;
		iVar1 = getInterpolatedDistance(&local_30);
		local_30.vx = vx + 0x80;
		local_30.vz = vz + -0x80;
		iVar3 = getInterpolatedDistance(&local_30);
		local_30.vz = vz + 0x80;
		local_30.vx = vx;
		iVar4 = getInterpolatedDistance(&local_30);
		if (0xf000 < iVar4) {
			ReplayLog_Fnarr_He_Said_Log(0x3e9);
			vx = lastKnownPosition.vx - local_30.vx;
			vz = lastKnownPosition.vz - local_30.vz;
			goto LAB_PATH__000e9048;
		}
		val = 0xbbb;
		if (0x600 < iVar4) {
			ReplayLog_Fnarr_He_Said_Log(0x7d2);
			uVar2 = ratan2((iVar1 - iVar3) * 2, iVar1 + iVar3 + iVar4 * -2);
			return uVar2 & 0xfff;
		}
	}
	ReplayLog_Fnarr_He_Said_Log(val);
	vx = player.pos[0] - vx;
	vz = player.pos[2] - vz;
LAB_PATH__000e9048:
	uVar2 = ratan2(vx, vz);
	return uVar2 | 0x1000;
	*/
}





