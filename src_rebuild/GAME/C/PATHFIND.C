#include "DRIVER2.H"
#include "PATHFIND.H"
#include "SYSTEM.H"
#include "COP_AI.H"
#include "OBJCOLL.H"
#include "DR2ROADS.H"
#include "PLAYERS.H"
#include "CARS.H"
#include "CAMERA.H"

#include "SDL.h"

short distanceCache[16384];
char omap[128][16];				// obstacle map
long dunyet[32][2];				// scanned cell map
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


PATHFIND_237fake ends[6][2] = {
	{
		{0, 0},
		{512, 0}
	},

	{
		{0, 0},
		{256, 512 }
	},

	{
		{256, 512},
		{512, 0}
	},

	{
		{256, 512},
		{-256, 512}
	},

	{
		{256, 512},
		{0, 1024}
	},
	{
		{256, 512 },
		{512, 1024}
	}
};

PATHFIND_238fake dirs[6] = {
	{
		512,0
	},
	{
		256,-512
	},
	{
		-256,-512
	},
	{
		-512,0
	},
	{
		-256,512
	},
	{
		256,512
	},
};

// cx, cz in range of 0..128
#define OMAP_V(cx, cz)						omap[((cx) & 0x7f)][((cz) & 0x7f) >> 3]
#define OMAP_GETVALUE(cx, cz)				(OMAP_V(cx,cz) >> ((cz) & 7) & 1)

// cx, cz in range of 0...128
// FIXME: really bad
#define DONEMAP_V(cx, cz)					dunyet[(cx & 0x1fU)][(cz & 1)]
#define DONEMAP_GETVALUE(cx, cz, x, i)		(3 << (cz & 0x1e) & ((((cx & 0x3fU) >> 5 | cz & 2) ^ i) << (cz & 0x1e) ^ x))


// [A] sets obstacle map bit
inline void OMapSet(int cellX, int cellZ, int val)
{
	unsigned char prev = OMAP_V(cellX, cellZ);
	int bit = (1 << (cellZ & 7));
	OMAP_V(cellX, cellZ) = prev ^ bit & (prev ^ (val ? 0xFF : 0));
}

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
tNode* popNode(tNode* __return_storage_ptr__)
{
	ushort uVar1;
	ushort uVar6;
	uint uVar7;
	uint child;
	int d3;
	int d4;
	ushort d;
	uint here;
	tNode res;

	res = heap[1];

	if (numHeapEntries > 1)
	{
		uVar1 = heap[numHeapEntries].dist;

		here = 1;

		while (true)
		{
			// [A] I don't know what fuckery happening here
			uVar7 = here + 1;
			d = heap[uVar7].dist;

			child = uVar7 + 1;
			uVar6 = heap[uVar7 + 1].dist;

			if (numHeapEntries - 2 <= uVar7 || heap[uVar7 + 1].dist < d)
			{
				d = uVar6;
				uVar7 = child;
			}

			if ((numHeapEntries - 2 < uVar7) || (uVar1 <= d))
				break;

			heap[here] = heap[uVar7];

			here = uVar7;
		}

		heap[here] = heap[numHeapEntries];
	}

	numHeapEntries--;

	*__return_storage_ptr__ = res;
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

// [D] [T]
void WunCell(VECTOR* pbase)
{
	VECTOR v[2];
	int height1;
	int i, j;

	// [A] hack with height map (fixes some bits in Havana)
	height1 = MapHeight(pbase) + 60;
	
	pbase->vx += 512;
	pbase->vz += 512;

	v[0].vy = MapHeight(pbase) + 60;

	pbase->vx -= 512;
	pbase->vz -= 512;

	if (height1 - v[0].vy > 100)
		v[0].vy = height1;

	v[1].vy = v[0].vy;

	// [A] definitely better code
	// new 16 vs old 12 passes but map is not leaky at all#
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			v[0].vx = pbase->vx + i * 256 + 128;
			v[0].vz = pbase->vz + j * 256 + 128;

			OMapSet(v[0].vx >> 8, v[0].vz >> 8, CellAtPositionEmpty(&v[0], 128) == 0);
		}
	}

#if 0
	iVar10 = 0;
	do {
		iVar8 = 0;

		if (iVar10 != 0)
			pbase->vx += 512;

		v[0].vx = pbase->vx;
		v[0].vz = pbase->vz;

		do {

			v[0].vx = pbase->vx + ends[iVar8][0].dx;
			v[0].vz = pbase->vz + ends[iVar8][0].dz;

			v[1].vx = pbase->vx + ends[iVar8][1].dx;
			v[1].vz = pbase->vz + ends[iVar8][1].dz;

			iVar4 = v[0].vx + v[1].vx >> 1;
			iVar5 = v[0].vz + v[1].vz >> 1;

			OMapSet(iVar4 >> 8, iVar5 >> 8, lineClear(&v[0], &v[1]) == 0);

			iVar8++;
		} while (iVar8 < 6);

		if (iVar10 != 0)
			pbase->vx -= 512;

		iVar10++;
	} while (iVar10 < 2);
#endif
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

// [A] function that invalidates map at ends
// fixes bug with not being able to update navigation cells
void InvalidateMapEnds()
{
	int x, z;
	long tile;
	int i;
	XZPAIR pos;
	pos.x = (player[0].pos[0] & 0xfffffc00) >> 10;
	pos.z = (player[0].pos[2] & 0xfffffc00) >> 10;

	for(i = 0; i < 32; i++)
	{
		x = pos.x + 15 + i;
		z = pos.z + 16;
		
		tile = DONEMAP_V(x, z);
		DONEMAP_V(x, z) = tile ^ DONEMAP_GETVALUE(x, z, tile, 3);

		x = pos.x + 16;
		z = pos.z + 15 + i;

		tile = DONEMAP_V(x, z);
		DONEMAP_V(x, z) = tile ^ DONEMAP_GETVALUE(x, z, tile, 3);
	}
}

// [D] [T]
void InvalidateMap(void)
{
	int dir;
	int p;
	int q;
	int count;
	int px, pz;
	VECTOR bPos;
	long tile, i;

	q = 0;
	p = 0;
	dir = 0;

	bPos.vx = player[0].pos[0] & 0xfffffc00;
	bPos.vz = player[0].pos[2] & 0xfffffc00;

	count = 0;
	do
	{
		px = bPos.vx >> 10;
		pz = bPos.vz >> 10;
	
		tile = DONEMAP_V(px, pz);
		i = DONEMAP_GETVALUE(px, pz, tile, 3);

		DONEMAP_V(px, pz) = tile ^ i;
		
		if (dir == 0)
		{
			p++;
			bPos.vx += 1024;

			if (p + q == 1)
				dir = 1;
		}
		else if (dir == 1)
		{
			q++;
			bPos.vz += 1024;

			if (p == q)
				dir = 2;
		}
		else if (dir == 2)
		{
			p--;
			bPos.vx -= 1024;

			if (p + q == 0)
				dir = 3;
		}
		else
		{
			q--;
			bPos.vz -= 1024;
	
			if (p == q)
				dir = 0;
		}

		count++;
	}while (count < 1024);
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

// [D] [T]
void BloodyHell(void)
{
	int dir;
	int p;
	int q;
	int px, pz;
	uint howMany;
	int count;
	VECTOR bPos;
	long tile, i;

	cellsThisFrame = 0;
	
	bPos.vy = 8173;

	bPos.vx = player[0].pos[0] & 0xfffffc00;
	bPos.vz = player[0].pos[2] & 0xfffffc00;

	howMany = cellsPerFrame;

	if (CameraCnt < 4)
		howMany = cellsPerFrame + 20;

	q = 0;
	
	if (CameraCnt < 8)
		howMany += 4;

	p = 0;
	dir = 0;
	count = 0;

	do {
		if (count == 200)
			howMany--;

		px = bPos.vx >> 10;
		pz = bPos.vz >> 10;

		tile = DONEMAP_V(px, pz);
		i = DONEMAP_GETVALUE(px, pz, tile, 0);

		if (i != 0)
		{
			DONEMAP_V(px, pz) = tile ^ i;

			WunCell(&bPos);

			cellsThisFrame++;

			if (howMany <= cellsThisFrame)
				return;
		}

		if (dir == 0)
		{
			p++;
			bPos.vx += 1024;

			if (p + q == 1)
				dir = 1;
		}
		else if (dir == 1) 
		{
			q++;
			bPos.vz += 1024;
			
			if (p == q)
				dir = 2;
		}
		else if (dir == 2)
		{
			p--;

			bPos.vx -= 1024;

			if (p + q == 0)
				dir = 3;
		}
		else 
		{
			q--;
			bPos.vz -= 1024;

			if (p == q)
				dir = 0;
		}

		count++;
	} while( count < 840 );
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

int slowWallTests = 0;

// [D] [A] - might be bugged
int blocked(tNode* v1, tNode* v2)
{
	unsigned char bVar1;
	bool bVar2;
	char cVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int res;
	int uVar9;
	unsigned char bVar10;

	if (slowWallTests == 0)
	{
		int x = (v1->vx + v1->vx >> 9 & 0x7f);
		int z = (v1->vz + v2->vz >> 9 & 0x7f);

		return OMAP_GETVALUE(x, z); //  omap[x][z] >> (v1->vz + v2->vz >> 9 & 7) & 1;
	}

	int x = (v1->vx + v1->vx >> 9 & 0x7f);
	int z = (v1->vz + v2->vz >> 9 & 0x7f);

	res = lineClear((VECTOR*)v1, (VECTOR*)v2) == 0;

	//OMapSet(x,z, res);

	return res;
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

// [D]
void setDistance(tNode* n, ushort dist)
{
	n->dist = dist | 1;

	distanceCache[(n->vx >> 2 & 0x3f80U | n->vz >> 9 & 0x7fU) ^ (n->vy & 1U) * 0x2040 ^ (n->vy & 2U) << 0xc] = dist | 1;
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

// [D] [A] - might be bugged
void iterate(void)
{
	tNode pathNodes[250];

	ushort uVar1;
	ushort uVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	tNode* nbr;
	int iVar8;
	tNode itHere;

	if (numHeapEntries == 0)
		return;

	popNode(&itHere);
	iVar8 = 0;
	nbr = pathNodes;
	do
	{
		nbr = nbr + 1;
		iVar4 = itHere.vx + dirs[iVar8].dx;
		nbr->vx = iVar4;
		nbr->vy = itHere.vy;
		iVar3 = itHere.vz + dirs[iVar8].dz;
		nbr->vz = iVar3;
		uVar1 = distanceCache[(iVar4 >> 2 & 0x3f80U | iVar3 >> 9 & 0x7fU) ^ (itHere.vy & 1) * 0x2040 ^ (itHere.vy & 2) << 0xc];
	
		nbr->dist = uVar1;
		if ((uVar1 & 1) == 0)
		{
			iVar3 = blocked(&itHere, nbr);
			if (iVar3 == 0)
			{
				iVar3 = nbr->vy - itHere.vy;
				if (iVar3 < 0)
				{
					iVar3 = itHere.vy - nbr->vy;
				}
				if (iVar3 < 0xc9)
				{
					if ((uVar1 & 1) == 0)
					{
						nbr->dist = 0;
					}
					goto LAB_PATH__000e797c;
				}
			}
			nbr->dist = 1;
		}
		else
		{
			if ((int)(uint)uVar1 <= (int)((uint)itHere.dist - 0x120))
			{
				nbr->dist = 1;
			}
		}
	LAB_PATH__000e797c:
		iVar8 = iVar8 + 1;
	}
	while (iVar8 < 6);
	iVar3 = 0;
	iVar8 = 1;
	do
	{
		if (pathNodes[iVar3 + 1].dist == 0)
		{
			uVar1 = pathNodes[1].dist;
			if (iVar3 != 5)
			{
				uVar1 = pathNodes[iVar3 + 2].dist;
			}
			uVar2 = pathNodes[6].dist;
			if (iVar3 != 0)
			{
				uVar2 = pathNodes[iVar3].dist;
			}
			if (uVar2 < 2)
			{
				if (uVar1 >= 2)
				{
					iVar8 = (uint)uVar1 + (uint)itHere.dist;
					goto LAB_PATH__000e7a94;
				}
				uVar5 = (uint)itHere.dist + 0x100;
			}
			else
			{
				if (uVar1 < 2)
				{
					iVar8 = (uint)uVar2 + (uint)itHere.dist;
				LAB_PATH__000e7a94:
					uVar5 = (iVar8 >> 1) + 0xdd;
				}
				else
				{
					iVar8 = (uint)uVar1 - (uint)uVar2;
					uVar5 = 0x10000 - (iVar8 * iVar8) / 3;
					if ((int)uVar5 < 0)
					{
						uVar5 = 0;
					}
					else
					{
						uVar6 = (uVar5 >> 9) + 0x80;
						if (uVar6 == 0)
						{
							trap(7);
						}
						uVar5 = uVar5 / uVar6 + uVar6 >> 1;
					}
					uVar5 = itHere.dist + uVar5;
				}
			}
			uVar5 = uVar5 & 0xffff;
			iVar8 = iVar3 + 1;
			if (numHeapEntries != 0xc6)
			{
				setDistance(pathNodes + iVar3 + 1, (ushort)uVar5);
				uVar7 = numHeapEntries + 1;
				uVar6 = uVar7 >> 1;
				iVar8 = uVar7 * 0x10;
				if ((uVar6 != 0) && (uVar5 < heap[uVar6].dist))
				{
					iVar8 = uVar7 * 0x10;
					do
					{
						uVar7 = uVar6;
						*(int*)((int)&heap[0].vx + iVar8) = (&heap[0].vx)[uVar7 * 4];
						*(int*)((int)&heap[0].vy + iVar8) = (&heap[0].vy)[uVar7 * 4];
						*(int*)((int)&heap[0].vz + iVar8) = (&heap[0].vz)[uVar7 * 4];
						uVar6 = uVar7 >> 1;
						*(uint*)((int)&heap[0].dist + iVar8) = *(uint*)(&heap[0].dist + uVar7 * 8);
						if (uVar6 == 0) break;
						iVar8 = uVar7 << 4;
					}
					while (uVar5 < heap[uVar6].dist);
					iVar8 = uVar7 << 4;
				}
				*(int*)((int)&heap[0].vx + iVar8) = pathNodes[iVar3 + 1].vx;
				*(int*)((int)&heap[0].vy + iVar8) = pathNodes[iVar3 + 1].vy;
				*(int*)((int)&heap[0].vz + iVar8) = pathNodes[iVar3 + 1].vz;
				numHeapEntries = numHeapEntries + 1;
				*(uint*)((int)&heap[0].dist + iVar8) = *(uint*)&pathNodes[iVar3 + 1].dist;
				iVar8 = iVar3 + 1;
			}
		}
		iVar3 = iVar8;
		iVar8 = iVar3 + 1;
	}
	while (iVar3 < 6);
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

extern int sdLevel; // D2ROADS

// [D]
int getInterpolatedDistance(VECTOR* pos)
{
	bool bVar1;
	bool bVar2;
	int uVar3;
	int iVar4;
	int uVar5;
	int uVar6;
	int uVar7;
	int uVar8;
	int iVar9;
	int iVar10;
	tNode n;
	VECTOR sp;

	uVar6 = pos->vz;
	n.vx = ((pos->vx + (uVar6 >> 1 & 0x1ffU)) >> 9) * 0x200 - ((uVar6 & 0x200) >> 1);
	n.vy = pos->vy;
	n.vz = (uVar6 >> 9) << 9;
	uVar6 = (n.vz & 0xfffffc00U) >> 8;

	if ((((char*)omap)[((int)(uVar6 & 0x7f) >> 3) + ((n.vx & 0xfffffc00U) >> 4 & 0x7c0)] >> (uVar6 & 7) & 1U) == 0) {
		n.vy = 0;
	}
	else
	{
		uVar6 = MapHeight((VECTOR*)&n);
		n.vy = uVar6 ^ (uVar6 ^ sdLevel) & 3;
	}

	iVar10 = pos->vz - n.vz;
	iVar9 = (pos->vx - n.vx) + (iVar10 >> 1);
	uVar7 = n.vx + 0x100;
	uVar3 = n.vz + 0x200;

	n.dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (n.vy & 1U) * 0x2040 ^ (n.vy & 2U) << 0xc];

	uVar6 = n.dist;
	uVar5 = (uVar3 & 0xfffffc00) >> 8;
	n.vx = uVar7;
	n.vz = uVar3;

	if ((((char*)omap)[((uVar5 & 0x7f) >> 3) + ((uVar7 & 0xfffffc00) >> 4 & 0x7c0)] >> (uVar5 & 7) & 1U) == 0)
	{
		n.vy = 0;
	}
	else
	{
		uVar3 = MapHeight((VECTOR*)&n);
		n.vy = uVar3 ^ (uVar3 ^ sdLevel) & 3;
	}

	n.dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (n.vy & 1U) * 0x2040 ^ (n.vy & 2U) << 0xc];

	uVar5 = n.dist;
	uVar3 = uVar5;

	if (uVar6 < uVar5)
		uVar3 = uVar6;

	if (iVar10 < iVar9)
	{
		n.vx = n.vx + 0x100;
		n.vz = n.vz - 0x200;
		uVar7 = (int)(n.vz & 0xfffffc00U) >> 8;

		if ((((char*)omap)[((uVar7 & 0x7f) >> 3) + ((n.vx & 0xfffffc00U) >> 4 & 0x7c0)] >> (uVar7 & 7) & 1U) == 0)
		{
			uVar7 = 0;
		}
		else
		{
			uVar7 = MapHeight((VECTOR*)&n);
			uVar7 = uVar7 ^ (uVar7 ^ sdLevel) & 3;
		}

		uVar7 = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (uVar7 & 1) * 0x2040 ^ (uVar7 & 2) << 0xc];

		uVar8 = uVar7;

		if (uVar3 < uVar7)
			uVar8 = uVar3;

		uVar8 = uVar8 + 0x155;
		bVar1 = 0xffff < uVar8;
		bVar2 = uVar8 < uVar6;

		if (bVar1)
			uVar8 = 0xffff;

		if (!bVar1 && bVar2)
			uVar6 = uVar8;

		if (uVar8 < uVar5)
			uVar5 = uVar8;

		iVar4 = uVar7 - uVar6;

		if (uVar8 < uVar7)
		{
			iVar4 = uVar8 - uVar6;
			uVar7 = uVar8;
		}

		iVar4 = iVar4 * iVar9;
		iVar10 = (uVar5 - uVar7) * iVar10;
	}
	else
	{
		n.vx = n.vx - 0x200;
		uVar7 = (int)(n.vz & 0xfffffc00U) >> 8;

		if ((((char*)omap)[((uVar7 & 0x7f) >> 3) + ((n.vx & 0xfffffc00U) >> 4 & 0x7c0)] >> (uVar7 & 7) & 1U) == 0)
		{
			uVar7 = 0;
		}
		else
		{
			uVar7 = MapHeight((VECTOR*)&n);
			uVar7 = uVar7 ^ (uVar7 ^ sdLevel) & 3;
		}

		uVar7 = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (uVar7 & 1) * 0x2040 ^ (uVar7 & 2) << 0xc];

		uVar8 = uVar7;

		if (uVar3 < uVar7)
			uVar8 = uVar3;

		uVar8 = uVar8 + 0x155;
		bVar1 = 0xffff < uVar8;
		bVar2 = uVar8 < uVar6;
		if (bVar1)
			uVar8 = 0xffff;

		if (!bVar1 && bVar2)
			uVar6 = uVar8;

		if (uVar8 < uVar5)
			uVar5 = uVar8;

		iVar4 = uVar7 - uVar6;
		if (uVar8 < uVar7)
		{
			iVar4 = uVar8 - uVar6;
			uVar7 = uVar8;
		}
		iVar4 = iVar4 * iVar10;
		iVar10 = (uVar5 - uVar7) * iVar9;
	}

	uVar6 = uVar6 + (iVar4 + iVar10 >> 9);
	lastDistanceFound = uVar6 ^ (uVar6 & 1 ^ uVar6) & 1;

	return lastDistanceFound;
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

// [D]
void addCivs(void)
{
	unsigned char bits;
	int uVar2;
	int iVar3;
	int uVar4;
	int uVar5;
	int iVar7;
	int iVar6;
	int uVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	int iVar11;
	int x, z, vx, vz;
	_CAR_DATA* cp;

	cp = car_data;
	do {
		if (cp->controlType == CONTROL_TYPE_CIV_AI)
		{
			iVar7 = cp->hd.oBox.radii[2].vx;
			x = cp->hd.oBox.location.vx;
			iVar6 = cp->hd.oBox.radii[2].vz;
			z = cp->hd.oBox.location.vz;

			vx = x + iVar7 >> 8 & 0x7e;
			vz = z + iVar6 >> 8;

			iVar3 = (vz & 0x7e) >> 3;
			bits = (3 << (vz & 6));

			uVar4 = x - iVar7 >> 8 & 0x7e;
			omap[vx][iVar3] = bits ^ omap[vx][iVar3];
			uVar5 = z - iVar6 >> 8;
			omap[(vx + 1)][iVar3] = bits ^ omap[(vx + 1)][iVar3];
			uVar2 = uVar5 & 0x7e;

			if ((vx ^ (vz & 0x7e) << 8) == uVar4)
			{
				if (uVar2 != 0)
					goto LAB_PATH__000e8310;
			}
			else if (uVar2 << 8 != 1)
			{
			LAB_PATH__000e8310:
				bits = (3 << (uVar5 & 6));
				omap[uVar4][(uVar2 >> 3)] = bits ^ omap[uVar4][(uVar2 >> 3)];
				omap[(uVar4 + 1)][(uVar2 >> 3)] = bits ^ omap[(uVar4 + 1)][(uVar2 >> 3)];
			}
		}

		cp++;

		if (&car_data[MAX_CARS - 1] < cp)
			return;

	} while (true);
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

// [D] [A] - might be bugged
void UpdateCopMap(void)
{
	int iVar1;
	int uVar2;
	long lVar3;
	short uVar4;
	int* piVar5;
	short* psVar6;
	int iVar7;
	int iVar8;
	int uVar9;
	int uVar10;
	int uVar11;
	tNode startNode;
	tNode sp_n;

	InvalidateMapEnds();
	BloodyHell();

	if ((player_position_known == 1) || (CameraCnt == 6))
	{
		pathFrames = 0;
		setMem16((ushort*)distanceCache, 0xfffe, 0x4000);
		DoExtraWorkForNFrames = 3;
	}

	if (pathFrames == 0)
	{
		if ((player[0].playerType == 1) && ((CopsCanSeePlayer != 0 || (numActiveCops == 0))))
		{
			iVar1 = (int)player[0].playerCarId;

			searchTarget.vx = car_data[iVar1].hd.where.t[0] + FIXEDH(car_data[iVar1].st.n.linearVelocity[0]) * 8;
			searchTarget.vy = car_data[iVar1].hd.where.t[1] + FIXEDH(car_data[iVar1].st.n.linearVelocity[1]) * 4;
			searchTarget.vz = car_data[iVar1].hd.where.t[2] + FIXEDH(car_data[iVar1].st.n.linearVelocity[2]) * 8;
		}
		else if (searchTarget.vy == -0x304f)
		{
			searchTarget.vx = player[0].pos[0];
			searchTarget.vy = player[0].pos[1];
			searchTarget.vz = player[0].pos[2];
		}

		psVar6 = distanceCache;
		iVar1 = 0x3fff;

		do {
			uVar2 = (uint)(ushort)*psVar6 + 0x2000;
			if ((uVar2 & 1) != 0)
				uVar2 = uVar2 ^ 1;

			uVar4 = (ushort)uVar2;
			if (0xfffe < uVar2)
				uVar4 = 0xfffe;

			*psVar6 = uVar4;
			iVar1--;
			psVar6 = (short*)((ushort*)psVar6 + 1);
		} while (-1 < iVar1);

		startNode.vx = ((searchTarget.vx + (searchTarget.vz >> 1 & 0x1ffU)) >> 9) * 0x200 - ((searchTarget.vz & 0x200U) >> 1);
		startNode.vz = (searchTarget.vz >> 9) << 9;
		startNode.vy = searchTarget.vy;
		numHeapEntries = 0;

		uVar2 = (int)(startNode.vz & 0xfffffc00U) >> 8;

		if ((((char*)omap)[((uVar2 & 0x7f) >> 3) + ((startNode.vx & 0xfffffc00U) >> 4 & 0x7c0)] >> (uVar2 & 7) & 1U) == 0)
		{
			startNode.vy = 0;
		}
		else
		{
			uVar2 = MapHeight((VECTOR*)&startNode);
			startNode.vy = uVar2 ^ (uVar2 ^ sdLevel) & 3;
		}

		iVar1 = startNode.vx - searchTarget.vx;

		if (searchTarget.vz - startNode.vz < (searchTarget.vx - startNode.vx) + (searchTarget.vz - startNode.vz >> 1))
		{
			lVar3 = SquareRoot0(iVar1 * iVar1 + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			uVar2 = lVar3 / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, (ushort)uVar2);
				uVar11 = numHeapEntries + 1;
				uVar9 = uVar11 >> 1;

				if (uVar9 != 0)
				{
					uVar4 = heap[uVar9].dist;

					while (uVar2 < uVar4)
					{
						heap[uVar11].vx = heap[uVar9].vx;
						heap[uVar11].vy = heap[uVar9].vy;
						heap[uVar11].vz = heap[uVar9].vz;
						uVar10 = uVar9 >> 1;
						heap[uVar11].dist = heap[uVar9].dist;
						heap[uVar11].ptoey = heap[uVar9].ptoey;

						uVar11 = uVar9;

						if (uVar10 == 0)
							break;

						uVar4 = heap[uVar10].dist;
						uVar9 = uVar10;
					}
				}

				numHeapEntries = numHeapEntries + 1;
				heap[uVar11].vx = startNode.vx;
				heap[uVar11].vy = startNode.vy;
				heap[uVar11].vz = startNode.vz;
				heap[uVar11].dist = startNode.dist;
				heap[uVar11].ptoey = startNode.ptoey;
			}

			startNode.vx = startNode.vx + 0x100;
			startNode.vz = startNode.vz + 0x200;
			lVar3 = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) +
				(startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			uVar2 = lVar3 / 2 & 0xffff;

			if (numHeapEntries != 0xc6)
			{
				setDistance(&startNode, (ushort)uVar2);
				uVar11 = numHeapEntries + 1;
				uVar9 = uVar11 >> 1;
				if (uVar9 != 0)
				{
					uVar4 = heap[uVar9].dist;
					while (uVar2 < uVar4)
					{
						heap[uVar11].vx = heap[uVar9].vx;
						heap[uVar11].vy = heap[uVar9].vy;
						heap[uVar11].vz = heap[uVar9].vz;
						uVar10 = uVar9 >> 1;
						heap[uVar11].dist = heap[uVar9].dist;
						heap[uVar11].ptoey = heap[uVar9].ptoey;
						uVar11 = uVar9;

						if (uVar10 == 0)
							break;

						uVar4 = heap[uVar10].dist;
						uVar9 = uVar10;
					}
				}
				numHeapEntries = numHeapEntries + 1;
				heap[uVar11].vx = startNode.vx;
				heap[uVar11].vy = startNode.vy;
				heap[uVar11].vz = startNode.vz;
				heap[uVar11].dist = startNode.dist;
				heap[uVar11].ptoey = startNode.ptoey;
			}

			startNode.vx = startNode.vx + 0x100;
			startNode.vz = startNode.vz + -0x200;
			lVar3 = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			uVar2 = lVar3 / 2 & 0xffff;

			if (numHeapEntries == 0xc6)
				goto LAB_PATH__000e8dfc;

			setDistance(&startNode, (ushort)uVar2);

			uVar9 = numHeapEntries + 1;
			uVar11 = uVar9 >> 1;

			if ((uVar11 != 0) && (uVar2 < heap[uVar11].dist))
			{
				iVar1 = uVar9 * 0x10;
				do {
					uVar9 = uVar11;
					*(int*)((int)&heap[0].vx + iVar1) = (&heap[0].vx)[uVar9 * 4]; // [A] I cannot understand decompiler shit code
					*(int*)((int)&heap[0].vy + iVar1) = (&heap[0].vy)[uVar9 * 4];
					*(int*)((int)&heap[0].vz + iVar1) = (&heap[0].vz)[uVar9 * 4];

					uVar11 = uVar9 >> 1;
					*(uint*)((int)&heap[0].dist + iVar1) = *(uint*)(&heap[0].dist + uVar9 * 8);

					if (uVar11 == 0)
						break;

					iVar1 = uVar9 << 4; // * 16
				} while (uVar2 < heap[uVar11].dist);
			}
		}
		else
		{
			lVar3 = SquareRoot0(iVar1 * iVar1 + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			uVar2 = lVar3 / 2 & 0xffff;
			if (numHeapEntries != 0xc6)
			{
				setDistance(&startNode, (ushort)uVar2);
				uVar11 = numHeapEntries + 1;
				uVar9 = uVar11 >> 1;
				if (uVar9 != 0)
				{
					uVar4 = heap[uVar9].dist;
					while (uVar2 < uVar4)
					{
						heap[uVar11].vx = heap[uVar9].vx;
						heap[uVar11].vy = heap[uVar9].vy;
						heap[uVar11].vz = heap[uVar9].vz;
						uVar10 = uVar9 >> 1;
						heap[uVar11].dist = heap[uVar9].dist;
						heap[uVar11].ptoey = heap[uVar9].ptoey;
						uVar11 = uVar9;

						if (uVar10 == 0)
							break;

						uVar4 = heap[uVar10].dist;
						uVar9 = uVar10;
					}
				}
				numHeapEntries = numHeapEntries + 1;
				heap[uVar11].vx = startNode.vx;
				heap[uVar11].vy = startNode.vy;
				heap[uVar11].vz = startNode.vz;
				heap[uVar11].dist = startNode.dist;
				heap[uVar11].ptoey = startNode.ptoey;
			}

			startNode.vx = startNode.vx + 0x100;
			startNode.vz = startNode.vz + 0x200;
			lVar3 = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			uVar2 = lVar3 / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, (ushort)uVar2);

				uVar11 = numHeapEntries + 1;
				uVar9 = uVar11 >> 1;

				if (uVar9 != 0)
				{
					uVar4 = heap[uVar9].dist;
					while (uVar2 < uVar4) {
						heap[uVar11].vx = heap[uVar9].vx;
						heap[uVar11].vy = heap[uVar9].vy;
						heap[uVar11].vz = heap[uVar9].vz;
						uVar10 = uVar9 >> 1;
						heap[uVar11].dist = heap[uVar9].dist;
						heap[uVar11].ptoey = heap[uVar9].ptoey;
						uVar11 = uVar9;

						if (uVar10 == 0)
							break;

						uVar4 = heap[uVar10].dist;
						uVar9 = uVar10;
					}
				}

				numHeapEntries = numHeapEntries + 1;
				heap[uVar11].vx = startNode.vx;
				heap[uVar11].vy = startNode.vy;
				heap[uVar11].vz = startNode.vz;
				heap[uVar11].dist = startNode.dist;
				heap[uVar11].ptoey = startNode.ptoey;
			}
			startNode.vx = startNode.vx + -0x200;
			lVar3 = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			uVar2 = lVar3 / 2 & 0xffff;

			if (numHeapEntries == 0xc6)
				goto LAB_PATH__000e8dfc;

			setDistance(&startNode, (ushort)uVar2);
			uVar9 = numHeapEntries + 1;
			uVar11 = uVar9 >> 1;

			if ((uVar11 != 0) && (uVar2 < heap[uVar11].dist))
			{
				iVar1 = uVar9 * 16;
				do {
					uVar9 = uVar11;
					*(int*)((int)&heap[0].vx + iVar1) = (&heap[0].vx)[uVar9 * 4];
					*(int*)((int)&heap[0].vy + iVar1) = (&heap[0].vy)[uVar9 * 4];
					*(int*)((int)&heap[0].vz + iVar1) = (&heap[0].vz)[uVar9 * 4];
					*(uint*)((int)&heap[0].dist + iVar1) = *(uint*)(&heap[0].dist + uVar9 * 8);

					uVar11 = uVar9 >> 1;

					if (uVar11 == 0)
						break;

					iVar1 = uVar9 << 4; // * 16
				} while (uVar2 < heap[uVar11].dist);
			}
		}

		numHeapEntries++;

		heap[uVar9].vx = startNode.vx;
		heap[uVar9].vy = startNode.vy;
		heap[uVar9].vz = startNode.vz;
		heap[uVar9].dist = startNode.dist;
		heap[uVar9].ptoey = startNode.ptoey;
	}
	else
	{
		// add cars
		addCivs();

		iVar1 = cellsThisFrame << 2;
		uVar2 = cellsThisFrame;

		if (6 < cellsThisFrame)
		{
			uVar2 = 6;
			iVar1 = 24;
		}

		iVar1 = pathIterations - iVar1 * 4 - uVar2 * 5;
		if (DoExtraWorkForNFrames != 0)
		{
			DoExtraWorkForNFrames--;
			iVar1 += 60;
		}

		iVar8 = iVar1 - 1;

		if (iVar1 < 36)
			iVar8 = 35;

		while (iVar8 != -1)
		{
			iVar8--;
			iterate();
		}

		// remove cars
		addCivs();
	}

LAB_PATH__000e8dfc:
	piVar5 = distanceReturnedLog;
	iVar8 = 6;
	pathFrames++;
	iVar1 = distanceReturnedLog[7];

	do {
		if (iVar1 < *piVar5)
			iVar1 = *piVar5;

		iVar8--;
		piVar5++;
	} while (-1 < iVar8);

	if (pathFrames > 250 || heap[1].dist - iVar1 > 3000)  // [A] was (pathFrames < pathFrames)
	{
		pathFrames = 0;
	}

	iVar7 = searchTarget.vx - player[0].pos[0] >> 4;
	iVar8 = searchTarget.vy - player[0].pos[1] >> 4;
	iVar1 = searchTarget.vz - player[0].pos[2] >> 4;
	playerTargetDistanceSq = iVar7 * iVar7 + iVar8 * iVar8 + iVar1 * iVar1;

#if 0
	static SDL_Window* occlusionWindow;
	static SDL_Surface* occlSurface;
	static SDL_Texture* occlTexture;
	static SDL_Surface* windowSurf;

	if (!occlusionWindow)
	{
		occlusionWindow = SDL_CreateWindow("Data Graphics View", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_TOOLTIP);
		occlSurface = SDL_CreateRGBSurface(0, 128, 128, 24, 0xFF, 0xFF, 0xFF, 0);
	}

	SDL_LockSurface(occlSurface);

	int pos_x = player[0].pos[0] >> 8;
	int pos_z = player[0].pos[2] >> 8;
	int pos_y = player[0].pos[1];

	tNode n;
	n.vx = player[0].pos[0];
	n.vz = player[0].pos[2];
	n.vy = pos_y;
	n.vy = MapHeight((VECTOR*)&n);

	for (int i = 0; i < 128; i++)
	{
		unsigned char* rgbLine = (unsigned char*)occlSurface->pixels + 128 * i * 3;

		for (int j = 0; j < 128; j++)
		{
			int px = pos_x + i - 64;
			int pz = pos_z + j - 64;
			
			if (OMAP_GETVALUE(px,pz))
			{
				rgbLine[j * 3] = 128;
				rgbLine[j * 3 + 1] = 128;
				rgbLine[j * 3 + 2] = 32;
			}
			else
			{
				rgbLine[j * 3] = 0;
				rgbLine[j * 3 + 1] = 0;
				rgbLine[j * 3 + 2] = 0;
			}

			//local_v0_152 = dunyet[(bPos.vx >> 10 & 0x1fU)][((bPos.vz >> 10) & 1)];

			// NEW METHOD
			// long val = dunyet[px >> 2 & 0x1f][pz >> 6 & 1]; // dunyet[px >> 2 & 0x1f][pz >> 2 & 1];
			// val = val >> (pz >> 2 & 0x1f) & 1;
			
			n.vx = px << 8;
			n.vz = pz << 8;
			n.vy = MapHeight((VECTOR*)&n);

			int dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (n.vy & 1U) * 0x2040 ^ (n.vy & 2U) << 0xc];// distanceCache[((pos_x+i & 127) * 128) + (j + pos_z & 127)];

			long prev = DONEMAP_V(px >> 2, pz >> 2);
			int val = DONEMAP_GETVALUE(px >> 2, pz >> 2, prev, 0);
			
			if (val != 0)
				rgbLine[j * 3] = 128;
			
			//if (rgbLine[j * 3] == 0 && rgbLine[j * 3 + 2] == 0)
			//	rgbLine[j * 3 + 1] = dist / 64;
		}
	}

	SDL_UnlockSurface(occlSurface);

	windowSurf = SDL_GetWindowSurface(occlusionWindow);

	SDL_Rect rect;
	rect.x = 1;
	rect.y = 1;
	rect.w = 511;
	rect.h = 511;

	SDL_BlitScaled(occlSurface, NULL, windowSurf, &rect);
	SDL_UpdateWindowSurface(occlusionWindow);

	SDL_FreeSurface(windowSurf);
#endif
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

// [D] [T]
int getHeadingToPlayer(int vx, int vy, int vz)
{
	int d1, d2, d3;
	int playerHereDistSq;
	int dx, dy, dz;
	int val;
	VECTOR pos;

	dx = vx - player[0].pos[0] >> 4;
	dy = vy - player[0].pos[1] >> 4;
	dz = vz - player[0].pos[2] >> 4;

	val = 4004;

	playerHereDistSq = (dx * dx + dy * dy + dz * dz);

	if (playerTargetDistanceSq * 2 <= playerHereDistSq * 3)
	{
		pos.vy = vy;

		pos.vx = vx - 128;
		pos.vz = vz - 128;

		d1 = getInterpolatedDistance(&pos);

		pos.vx = vx + 128;
		pos.vz = vz - 128;
		d2 = getInterpolatedDistance(&pos);

		pos.vz = vz + 128;
		pos.vx = vx;
		d3 = getInterpolatedDistance(&pos);

		if (d3 > 61440)
		{
			ReplayLog_Fnarr_He_Said_Log(0x3e9);

			dx = lastKnownPosition.vx - pos.vx;
			dz = lastKnownPosition.vz - pos.vz;

			return ratan2(dx, dz) + 4096;
		}

		val = 0xbbb;

		if (d3 > 1536)
		{
			ReplayLog_Fnarr_He_Said_Log(0x7d2);

			return ratan2((d1 - d2) * 2, d1 + d2 - d3 * 2) & 0xfff;
		}
	}

	ReplayLog_Fnarr_He_Said_Log(val);

	dx = player[0].pos[0] - vx;
	dz = player[0].pos[2] - vz;

	return ratan2(dx, dz) + 4096;
}
