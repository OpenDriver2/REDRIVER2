#include "THISDUST.H"
#include "TILE.H"
#include "MODELS.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "MODELS.H"
#include "DRAW.H"
#include "TEXTURE.H"
#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"

// decompiled code
// original method signature: 
// void /*$ra*/ Tile1x1(struct MODEL *model /*$a0*/)
 // line 79, offset 0x00041b10
	/* begin block 1 */
		// Start line: 80
		// Start offset: 0x00041B10
		// Variables:
	// 		int i; // $t3
	// 		unsigned char *polys; // $t0
	// 		struct SVECTOR *verts; // $t1
	// 		struct POLY_FT4 *prims; // $a2
	// 		unsigned long clut; // $t6
	// 		unsigned long tpage; // $a1

		/* begin block 1.1 */
			// Start line: 93
			// Start offset: 0x00041B4C
			// Variables:
		// 		unsigned long indices; // $a3
		// 		unsigned long texInfo; // $t2

			/* begin block 1.1.1 */
				// Start line: 93
				// Start offset: 0x00041B4C
				// Variables:
			// 		long *ot; // $t8

				/* begin block 1.1.1.1 */
					// Start line: 93
					// Start offset: 0x00041B4C
					// Variables:
				// 		int Z; // stack offset -16
				// 		unsigned long uv_01; // $t4
				// 		unsigned long uv_23; // $t5
					// Labels:
					//		0x000001B4	otherhalf

					/* begin block 1.1.1.1.1 */
						// Start line: 144
						// Start offset: 0x00041CC4
						// Variables:
					// 		int r2; // $a0
					/* end block 1.1.1.1.1 */
					// End offset: 0x00041CC4
					// End Line: 144
				/* end block 1.1.1.1 */
				// End offset: 0x00041D48
				// End Line: 161
			/* end block 1.1.1 */
			// End offset: 0x00041D48
			// End Line: 162
		/* end block 1.1 */
		// End offset: 0x00041D48
		// End Line: 163
	/* end block 1 */
	// End offset: 0x00041D7C
	// End Line: 166

	/* begin block 2 */
		// Start line: 158
	/* end block 2 */
	// End Line: 159

	/* begin block 3 */
		// Start line: 163
	/* end block 3 */
	// End Line: 164

extern _pct plotContext; // scratchpad addr: 0x1F8000C0

// [D]
void Tile1x1(MODEL *model)
{
	ushort uVar1;
	int iVar2;
	uint uVar3;
	OTTYPE *ot;
	ulong uVar5;
	//undefined4 in_zero;
	//undefined4 in_at;
	SVECTOR *sv2;
	SVECTOR *sv3;
	SVECTOR *sv1;
	uint uVar8;
	SVECTOR *sv0;
	uint in_a1;
	uint uVar10;
	char *polys;
	SVECTOR *verts;
	uint uVar11;
	int i;
	uint uVar12;
	int local_10;
	POLY_FT4* prims;

	i = model->num_polys;
	polys = (char *)model->poly_block;
	verts = (SVECTOR *)model->vertices;

	ot = plotContext.ot;

	prims = (POLY_FT4*)plotContext.primptr;

	do {
		i--;
		if (i == -1) 
		{
			plotContext.ot = ot;
			return;
		}

		POLYFT4* poly = (POLYFT4*)polys;

		uVar10 = ((uint *)polys)[1]; // v0
		uVar11 = *(uint *)polys;

		//printf("v0: %d, v1: %d, v2: %d, v3: %d\n", (uVar10 & 0xff), (uVar10 >> 5 & 0x7f8), (uVar10 >> 0x18), (uVar10 >> 0xd & 0x7f8));

		sv0 = verts + (uVar10 & 0xff);
		sv1 = (SVECTOR*)((int)&verts->vx + (uVar10 >> 5 & 0x7f8));
		sv2 = verts + (uVar10 >> 0x18);

		gte_ldv3(sv0, sv1, sv2);
		docop2(0x280030);

		uVar8 = uVar11 >> 8 & 0xff;
		uVar1 = *(ushort *)((int)*plotContext.ptexture_cluts + (uVar11 >> 0xf & 0x1fe) + uVar8 * 0x40);
		in_a1 = (uint)(*plotContext.ptexture_pages)[uVar8] << 0x10;

		docop2(0x1400006);

		uVar8 = ((uint *)polys)[2]; // uv0
		uVar12 = ((uint *)polys)[3]; // uv2

		gte_stopz(&iVar2);
		docop2(0x158002d);

		plotContext.ot = ot;

		if (iVar2 < 0) 
		{
			gte_stsxy0(&prims->x0);
			sv3 = (SVECTOR *)((int)&verts->vx + (uVar10 >> 0xd & 0x7f8));

			gte_ldv0(sv3);

			docop2(0x180001);
			docop2(0x1400006);

			gte_stopz(&iVar2);

			gte_stotz(&local_10);

			if (iVar2 < 0 && 1 < local_10)
			{
			LAB_00041cc4:

				setPolyFT4(prims);
				addPrim(ot + (local_10 >> 1) + 0x85, prims);

				//uVar10 = ot[(local_10 >> 1) + 0x85];
				//ot[(local_10 >> 1) + 0x85] = (uint)plotContext.field_0x90 & 0xffffff;
				//(plotContext.field_0x90)->tag = uVar10 & 0xffffff | 0x9000000;

				gte_stsxy3(&prims->x1, &prims->x2, &prims->x3);
				*(uint *)&(prims->u0) = uVar8 & 0xffff | (uint)uVar1 << 0x10;
				*(uint *)&(prims->u1) = uVar8 >> 0x10 | in_a1;
				*(uint *)&(prims->u2) = uVar12 >> 0x10;
				*(uint *)&(prims->u3) = uVar12 & 0xffff;
				*(ulong *)&(prims->r0) = plotContext.colour;

				plotContext.primptr += sizeof(POLY_FT4);
				prims = (POLY_FT4*)plotContext.primptr;
			}
		}
		else 
		{
			gte_stotz(&local_10);

			if (1 < local_10)
			{
				gte_stsxy0(&prims->x0);
				sv3 = (SVECTOR *)((int)&verts->vx + (uVar10 >> 0xd & 0x7f8));

				gte_ldv0(sv3);
				docop2(0x180001);

				goto LAB_00041cc4;
			}
		}

		polys = (char *)(polys + PolySizes[poly->id]);
		ot = plotContext.ot;

	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTILES(int tile_amount /*$s2*/)
 // line 180, offset 0x00041d7c
	/* begin block 1 */
		// Start line: 181
		// Start offset: 0x00041D7C

		/* begin block 1.1 */
			// Start line: 201
			// Start offset: 0x00041E84
		/* end block 1.1 */
		// End offset: 0x00041EBC
		// End Line: 204

		/* begin block 1.2 */
			// Start line: 208
			// Start offset: 0x00041EBC
			// Variables:
		// 		struct PACKED_CELL_OBJECT **tilePointers; // $s3
		// 		int previous_matrix; // $s4

			/* begin block 1.2.1 */
				// Start line: 220
				// Start offset: 0x00041F34
				// Variables:
			// 		int model_number; // $s0
			// 		int z; // $a1

				/* begin block 1.2.1.1 */
					// Start line: 223
					// Start offset: 0x00041F34
					// Variables:
				// 		int yang; // $a1
				// 		struct PACKED_CELL_OBJECT *ppco; // $a0
				/* end block 1.2.1.1 */
				// End offset: 0x00041FB8
				// End Line: 241

				/* begin block 1.2.1.2 */
					// Start line: 270
					// Start offset: 0x0004202C
					// Variables:
				// 		struct MODEL *model; // $a0
				/* end block 1.2.1.2 */
				// End offset: 0x00042060
				// End Line: 279
			/* end block 1.2.1 */
			// End offset: 0x00042060
			// End Line: 282
		/* end block 1.2 */
		// End offset: 0x000420B0
		// End Line: 285
	/* end block 1 */
	// End offset: 0x000420B0
	// End Line: 287

	/* begin block 2 */
		// Start line: 445
	/* end block 2 */
	// End Line: 446

	/* begin block 3 */
		// Start line: 460
	/* end block 3 */
	// End Line: 461

	/* begin block 4 */
		// Start line: 463
	/* end block 4 */
	// End Line: 464

// [D]
void DrawTILES(int tile_amount)
{
	int iVar1;
	int iVar2;
	uint uVar3;
	ushort *puVar4;
	uint uVar5;
	ushort **ppuVar6;
	uint uVar7;

	if (-1 < gTimeOfDay) 
	{
		if (gTimeOfDay < 3)
		{
			plotContext.colour = combointensity & 0xffffffU | 0x2c000000;
		}
		else 
		{
			if (gTimeOfDay == 3) 
			{
				plotContext.colour = ((int)((uint)combointensity >> 0x10 & 0xff) / 3) * 0x10000 |
					((int)((uint)combointensity >> 8 & 0xff) / 3) * 0x100 |
					(int)(combointensity & 0xffU) / 3 | 0x2c000000U;
			}
		}
	}
	uVar7 = 0xffffffff;

	if (gWeather - 1U < 2)
	{
		uVar3 = plotContext.colour >> 2 & 0x3f;
		plotContext.colour = uVar3 * 0x30000 | uVar3 * 0x300 | uVar3 * 3 | 0x2c000000;
	}

	tile_amount = tile_amount + -1;
	plotContext.ot = current->ot;
	plotContext.primptr = current->primptr;
	plotContext.ptexture_pages = (ushort(*)[128])texture_pages;
	plotContext.ptexture_cluts = (ushort(*)[128][32])texture_cluts;
	plotContext.lastTexInfo = 0x18273472;
	ppuVar6 = (ushort **)tile_overflow_buffer;

	while (tile_amount != -1) 
	{
		puVar4 = *ppuVar6;
		plotContext.f4colourTable[6] = (*puVar4);
		plotContext.f4colourTable[7] = (int)((uint)puVar4[1] << 0x10) >> 0x11;
		plotContext.f4colourTable[8] = (puVar4[2]);
		ppuVar6 = ppuVar6 + 1;
		uVar5 = (uint)puVar4[3] & 0x3f;
		uVar3 = (uint)(puVar4[3] >> 6) | ((uint)puVar4[1] & 1) << 10;

		if (uVar7 == uVar5)
		{
			iVar1 = Apply_InvCameraMatrixSetTrans((VECTOR_NOPAD *)(plotContext.f4colourTable + 6));
		}
		else
		{
			iVar1 = Apply_InvCameraMatrixAndSetMatrix((VECTOR_NOPAD *)(plotContext.f4colourTable + 6), &CompoundMatrix[uVar5]);
			uVar7 = uVar5;
		}

		if (iVar1 < 7001)
		{
			if (Low2HighDetailTable[uVar3] != 0xffff)
				uVar3 = Low2HighDetailTable[uVar3];

#ifdef PSX
			if (iVar1 < 2000) 
				TileNxN(modelpointers[uVar3], 4, 0x4b);
			else 
				TileNxN(modelpointers[uVar3], 2, 0x23);
#else
			Tile1x1(modelpointers[uVar3]);	// [A] temporary draw it as it is
#endif
		}
		else
		{
			iVar2 = uVar3;// << 2;
			
			if (9000 < iVar1) 
			{
				iVar2 = uVar3;// << 2;
				if (Low2LowerDetailTable[uVar3] != 0xffff)
					iVar2 = Low2LowerDetailTable[uVar3];// << 2;
			}
			
			Tile1x1(modelpointers[iVar2]);
		}

		tile_amount--;
	}
	current->primptr = plotContext.primptr;
}



// decompiled code
// original method signature: 
// void /*$ra*/ makeMesh(struct MVERTEX (*VSP)[5][5] /*$t4*/, int m /*$t2*/, int n /*$a2*/)
 // line 292, offset 0x000420b0
	/* begin block 1 */
		// Start line: 293
		// Start offset: 0x000420B0

		/* begin block 1.1 */
			// Start line: 313
			// Start offset: 0x000420C8
			// Variables:
		// 		int a; // $t0
		// 		int b; // $t1
		/* end block 1.1 */
		// End offset: 0x000420C8
		// End Line: 313

		/* begin block 1.2 */
			// Start line: 313
			// Start offset: 0x000420C8
			// Variables:
		// 		int a; // $a3
		/* end block 1.2 */
		// End offset: 0x000420C8
		// End Line: 313

		/* begin block 1.3 */
			// Start line: 313
			// Start offset: 0x000420C8
			// Variables:
		// 		int a; // $a0
		// 		int b; // $a1
		/* end block 1.3 */
		// End offset: 0x000420C8
		// End Line: 313

		/* begin block 1.4 */
			// Start line: 320
			// Start offset: 0x000421B4
			// Variables:
		// 		int a; // $t0
		// 		int b; // $t1
		/* end block 1.4 */
		// End offset: 0x000421B4
		// End Line: 320

		/* begin block 1.5 */
			// Start line: 320
			// Start offset: 0x000421B4
			// Variables:
		// 		int a; // $a3
		/* end block 1.5 */
		// End offset: 0x000421B4
		// End Line: 320

		/* begin block 1.6 */
			// Start line: 320
			// Start offset: 0x000421B4
			// Variables:
		// 		int a; // $a0
		// 		int b; // $a1
		/* end block 1.6 */
		// End offset: 0x000421B4
		// End Line: 320

		/* begin block 1.7 */
			// Start line: 326
			// Start offset: 0x0004228C
			// Variables:
		// 		int k; // $s0

			/* begin block 1.7.1 */
				// Start line: 327
				// Start offset: 0x0004228C
				// Variables:
			// 		int a; // $t0
			// 		int b; // $t1
			/* end block 1.7.1 */
			// End offset: 0x0004228C
			// End Line: 327

			/* begin block 1.7.2 */
				// Start line: 327
				// Start offset: 0x0004228C
				// Variables:
			// 		int a; // $a3
			/* end block 1.7.2 */
			// End offset: 0x0004228C
			// End Line: 327

			/* begin block 1.7.3 */
				// Start line: 327
				// Start offset: 0x0004228C
				// Variables:
			// 		int a; // $a0
			// 		int b; // $a1
			/* end block 1.7.3 */
			// End offset: 0x0004228C
			// End Line: 327

			/* begin block 1.7.4 */
				// Start line: 332
				// Start offset: 0x00042378
				// Variables:
			// 		int a; // $t0
			// 		int b; // $t1
			/* end block 1.7.4 */
			// End offset: 0x00042378
			// End Line: 332

			/* begin block 1.7.5 */
				// Start line: 332
				// Start offset: 0x00042378
				// Variables:
			// 		int a; // $a3
			/* end block 1.7.5 */
			// End offset: 0x00042378
			// End Line: 332

			/* begin block 1.7.6 */
				// Start line: 332
				// Start offset: 0x00042378
				// Variables:
			// 		int a; // $a0
			// 		int b; // $a1
			/* end block 1.7.6 */
			// End offset: 0x00042378
			// End Line: 332
		/* end block 1.7 */
		// End offset: 0x00042458
		// End Line: 336

		/* begin block 1.8 */
			// Start line: 340
			// Start offset: 0x00042460
			// Variables:
		// 		int a; // $t1
		// 		int b; // $t5
		/* end block 1.8 */
		// End offset: 0x00042460
		// End Line: 340

		/* begin block 1.9 */
			// Start line: 343
			// Start offset: 0x000424D0
			// Variables:
		// 		int a; // $v0
		// 		int b; // $a1
		/* end block 1.9 */
		// End offset: 0x000424D0
		// End Line: 343

		/* begin block 1.10 */
			// Start line: 347
			// Start offset: 0x0004252C
			// Variables:
		// 		int a; // $t0
		// 		int b; // $t2
		/* end block 1.10 */
		// End offset: 0x0004252C
		// End Line: 347

		/* begin block 1.11 */
			// Start line: 347
			// Start offset: 0x0004252C
			// Variables:
		// 		int a; // $t3
		// 		int b; // $v0
		/* end block 1.11 */
		// End offset: 0x0004252C
		// End Line: 347

		/* begin block 1.12 */
			// Start line: 347
			// Start offset: 0x0004252C
			// Variables:
		// 		int a; // $a2
		/* end block 1.12 */
		// End offset: 0x0004252C
		// End Line: 347

		/* begin block 1.13 */
			// Start line: 347
			// Start offset: 0x0004252C
			// Variables:
		// 		int a; // $t8
		// 		int b; // $a1
		/* end block 1.13 */
		// End offset: 0x00042644
		// End Line: 350
	/* end block 1 */
	// End offset: 0x00042650
	// End Line: 353

	/* begin block 2 */
		// Start line: 700
	/* end block 2 */
	// End Line: 701

	/* begin block 3 */
		// Start line: 702
	/* end block 3 */
	// End Line: 703

	/* begin block 4 */
		// Start line: 708
	/* end block 4 */
	// End Line: 709

// [D] [A] - I don't expect this to work...
void makeMesh(MVERTEX(*VSP)[5][5], int m, int n)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	uint uVar8;
	uint uVar9;
	uint uVar10;
	uint uVar11;
	uint uVar12;
	int iVar13;

	//       N       0   1   2    3    4
	//
	//(*VSP)[n][0]   0   5   10   15   20
	//(*VSP)[n][1]   1   6   11   16   21
	//(*VSP)[n][2]   2   7   12   17   22
	//(*VSP)[n][3]   3   8   13   18   23
	//(*VSP)[n][4]   4   9   14   19   24

	if (n == 4) 
	{
		uVar3 = *(uint *)&(*VSP)[0][0].vx;
		uVar2 = *(uint *)&(*VSP)[0][0].vz;
		uVar5 = uVar3 ^ 0x8000;
		uVar9 = *(uint *)&(*VSP)[0][4].vx ^ 0x8000;
		uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
		
		uVar6 = uVar2 ^ 0x8000;
		uVar2 = uVar2 ^ 0x8000;
		uVar3 = uVar3 ^ 0x8000;

		uVar9 = *(uint *)&(*VSP)[0][4].vx ^ 0x8000;
		uVar10 = *(uint *)&(*VSP)[0][4].vz ^ 0x8000;
		uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);

		*(uint *)&(*VSP)[0][2].vx = uVar5 ^ 0x8000;
		*(uint *)&(*VSP)[0][1].vx = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
		*(uint *)&(*VSP)[0][3].vx = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
		*(uint *)&(*VSP)[0][2].vz = uVar6 ^ 0x8000;
		*(uint *)&(*VSP)[0][1].vz = (uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		*(uint *)&(*VSP)[0][3].vz = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;

		if (m == 1) 
		{
			uVar2 = *(uint *)&(*VSP)[1][0].vz;
			uVar5 = *(uint *)&(*VSP)[1][0].vx ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[1][4].vx ^ 0x8000;
			uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
			
			uVar6 = uVar2 ^ 0x8000;
			uVar2 = uVar2 ^ 0x8000;
			uVar3 = *(uint *)&(*VSP)[1][0].vx ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[1][4].vx ^ 0x8000;
			uVar10 = *(uint *)&(*VSP)[1][4].vz ^ 0x8000;
			uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);

			*(uint *)&(*VSP)[1][2].vx = uVar5 ^ 0x8000;
			*(uint *)&(*VSP)[1][1].vx = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][3].vx = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][2].vz = uVar6 ^ 0x8000;
			*(uint *)&(*VSP)[1][1].vz = (uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][3].vz = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		}
		else 
		{
			
			uVar2 = *(uint *)&(*VSP)[4][0].vz;
			uVar5 = *(uint *)&(*VSP)[4][0].vx ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[4][4].vx ^ 0x8000;
			uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
			
			uVar6 = uVar2 ^ 0x8000;
			uVar2 = uVar2 ^ 0x8000;

			uVar3 = *(uint *)&(*VSP)[4][0].vx ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[4][4].vx ^ 0x8000;
			uVar10 = *(uint *)&(*VSP)[4][4].vz ^ 0x8000;
			uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);

			*(uint *)&(*VSP)[4][2].vx = uVar5 ^ 0x8000;
			*(uint *)&(*VSP)[4][1].vx = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[4][3].vx = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[4][2].vz = uVar6 ^ 0x8000;
			*(uint *)&(*VSP)[4][1].vz = (uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[4][3].vz = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			
			iVar13 = 4;
			do {
				iVar13 = iVar13 + -1;
				uVar3 = *(uint *)&(*VSP)[0][0].vx;
				uVar2 = *(uint *)&(*VSP)[0][0].vz;
				uVar5 = uVar3 ^ 0x8000;
				uVar9 = *(uint *)&(*VSP)[4][0].vx ^ 0x8000;
				uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
				
				uVar6 = uVar2 ^ 0x8000;
				uVar2 = uVar2 ^ 0x8000;
				uVar3 = uVar3 ^ 0x8000;
				uVar9 = *(uint *)&(*VSP)[4][0].vx ^ 0x8000;
				uVar10 = *(uint *)&(*VSP)[4][0].vz ^ 0x8000;
				uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);

				*(uint *)&(*VSP)[2][0].vx = uVar5 ^ 0x8000;
				*(uint *)&(*VSP)[1][0].vx = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
				*(uint *)&(*VSP)[3][0].vx = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
				*(uint *)&(*VSP)[2][0].vz = uVar6 ^ 0x8000;
				*(uint *)&(*VSP)[1][0].vz = (uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
				*(uint *)&(*VSP)[3][0].vz = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;

				VSP++;// = (MVERTEX(*)[5][5])(*VSP + 1);

			} while (-1 < iVar13);
		}
	}
	else 
	{
		uVar2 = *(uint *)&(*VSP)[0][0].vx;
		uVar9 = *(uint *)&(*VSP)[0][2].vx;
		uVar6 = *(uint *)&(*VSP)[0][0].vz;

		uVar5 = uVar2 ^ 0x8000;
		uVar3 = uVar9 ^ 0x8000;
		uVar10 = (uVar5 | uVar3) - ((int)(uVar5 ^ uVar3) >> 1 & 0xffff7fffU);
		uVar5 = *(uint *)&(*VSP)[0][2].vz;
		
		uVar3 = uVar6 ^ 0x8000;
		uVar5 = uVar5 ^ 0x8000;
		uVar3 = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0x7f7f7fffU);

		*(uint *)&(*VSP)[0][1].vx = uVar10 ^ 0x8000;
		*(uint *)&(*VSP)[0][1].vz = uVar3 ^ 0x8000;

		if (m == 1) 
		{
			uVar5 = *(uint *)&(*VSP)[1][0].vx ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[1][2].vx ^ 0x8000;
			*(uint *)(*VSP + 6) = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;

			uVar5 = *(uint *)&(*VSP)[1][0].vz ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[1][2].vz ^ 0x8000;
			*(uint *)&(*VSP)[1][1].vz = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		}
		else 
		{
			uVar2 = uVar2 ^ 0x8000;
			uVar9 = uVar9 ^ 0x8000;
			uVar4 = *(uint *)&(*VSP)[2][0].vz;
			uVar7 = *(uint *)&(*VSP)[2][0].vx ^ 0x8000;
			uVar11 = *(uint *)&(*VSP)[2][2].vx ^ 0x8000;
			uVar11 = (uVar7 | uVar11) - ((int)(uVar7 ^ uVar11) >> 1 & 0xffff7fffU);
			
			uVar7 = uVar4 ^ 0x8000;
			uVar6 = uVar6 ^ 0x8000;
			uVar4 = uVar4 ^ 0x8000;
			uVar1 = *(uint *)&(*VSP)[2][2].vx ^ 0x8000;
			uVar12 = *(uint *)&(*VSP)[2][2].vz ^ 0x8000;
			uVar8 = (uVar7 | uVar12) - ((int)(uVar7 ^ uVar12) >> 1 & 0x7f7f7fffU);
			uVar7 = *(uint *)&(*VSP)[2][0].vx ^ 0x8000;

			*(uint *)&(*VSP)[2][1].vx = uVar11 ^ 0x8000;
			*(uint *)&(*VSP)[1][0].vx =(uVar2 | uVar7) - ((int)(uVar2 ^ uVar7) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][1].vx =(uVar10 | uVar11) - ((int)(uVar10 ^ uVar11) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][2].vx = (uVar9 | uVar1) - ((int)(uVar9 ^ uVar1) >> 1 & 0xffff7fffU) ^ 0x8000;

			*(uint *)&(*VSP)[2][1].vz = uVar8 ^ 0x8000;
			*(uint *)&(*VSP)[1][0].vz =(uVar6 | uVar4) - ((int)(uVar6 ^ uVar4) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][1].vz = (uVar3 | uVar8) - ((int)(uVar3 ^ uVar8) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[1][2].vz =(uVar5 | uVar12) - ((int)(uVar5 ^ uVar12) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ drawMesh(struct MVERTEX (*VSP)[5][5] /*$s2*/, int m /*$s3*/, int n /*$s1*/, struct _pct *pc /*$a3*/)
 // line 359, offset 0x00042650
	/* begin block 1 */
		// Start line: 360
		// Start offset: 0x00042650
		// Variables:
	// 		int j; // $t6
	// 		int k; // $t9
	// 		struct POLY_FT4 *prims; // $t1

		/* begin block 1.1 */
			// Start line: 370
			// Start offset: 0x000426B8
			// Variables:
		// 		int Z1; // stack offset -24
		// 		int Z2; // stack offset -20
		// 		struct MVERTEX (*VST)[5][5]; // $t2
		// 		long *ot; // $t7

			/* begin block 1.1.1 */
				// Start line: 382
				// Start offset: 0x00042714
				// Variables:
			// 		int r2; // $v0
			/* end block 1.1.1 */
			// End offset: 0x00042714
			// End Line: 382

			/* begin block 1.1.2 */
				// Start line: 462
				// Start offset: 0x00042A30
				// Variables:
			// 		int r2; // $v0
			/* end block 1.1.2 */
			// End offset: 0x00042AB4
			// End Line: 480
		/* end block 1.1 */
		// End offset: 0x00042AB4
		// End Line: 483
	/* end block 1 */
	// End offset: 0x00042AEC
	// End Line: 486

	/* begin block 2 */
		// Start line: 884
	/* end block 2 */
	// End Line: 885

	/* begin block 3 */
		// Start line: 891
	/* end block 3 */
	// End Line: 892

	/* begin block 4 */
		// Start line: 896
	/* end block 4 */
	// End Line: 897

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */


void drawMesh(MVERTEX(*VSP)[5][5], int m, int n, _pct *pc)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	uint uVar3;
	uint *puVar4;
	uint *local_a0_1124;
	int iVar5;
	POLY_FT4 *prim;
	MVERTEX *vertex;
	int iVar6;
	OTTYPE *ot;
	MVERTEX(*VST)[5][5];
	int iVar7;
	int Z1;
	int Z2;

	iVar7 = 0;
	prim = (POLY_FT4 *)pc->primptr;
	local_a0_1124 = (uint *)VSP;

	if (0 < n)
	{
		do {
			iVar6 = m-1;
			iVar5 = iVar7 + 2;

			if (iVar6 != -1) 
			{
				VST = (MVERTEX(*)[5][5])(*VSP + iVar6 * 5);
				do {
					vertex = (MVERTEX*)*VST + iVar7;
					ot = pc->ot;

					gte_ldv3(&vertex[0], &vertex[1], &vertex[2]);

					docop2(0x280030);
					docop2(0x158002d);

					gte_stotz(&iVar1);

					if (1 < iVar1) 
					{
						SXYPAIR DAT_1f800208 = *(SXYPAIR*)&SXY0;
						SXYPAIR DAT_1f80020c = *(SXYPAIR*)&SXY1;
						SXYPAIR DAT_1f800210 = *(SXYPAIR*)&SXY2;
						gte_stsxy3(&DAT_1f800208, &DAT_1f80020c, &DAT_1f800210);

						setPolyFT4(prim);
						addPrim(ot + (iVar1 >> 1), prim);

						*(uint *)&prim->x0 = *(uint *)&DAT_1f800208;
						*(uint *)&prim->x1 = *(uint *)&DAT_1f80020c;
						*(uint *)&prim->x2 = *(uint *)&DAT_1f800210;
						*(uint *)&prim[1].x2 = *(uint *)&DAT_1f80020c;

						gte_ldv3(&vertex[2], &vertex[7], &vertex[6]);

						docop2(0x280030);
						docop2(0x158002d);

						SXYPAIR DAT_1f80021c = *(SXYPAIR*)&SXY0;
						SXYPAIR DAT_1f800220 = *(SXYPAIR*)&SXY1;
						SXYPAIR DAT_1f800224 = *(SXYPAIR*)&SXY2;

						if ((((ushort)DAT_1f80020c.x < 0x140) ||
							((ushort)DAT_1f800208.x < 0x140)) ||
							((ushort)DAT_1f800210.x < 0x140))
						{
						LAB_00042824:
							if (((0x109 < (ushort)DAT_1f800208.y) &&
								(0x109 < (ushort)DAT_1f80020c.y)) &&
								((0x109 < (ushort)DAT_1f800210.y &&
								(((DAT_1f800224.y = (short)(DAT_1f800224.x >> 0x10), 0x109 < (ushort)DAT_1f800224.y &&	// PLS HELP
								(-1 < (int)((uint)(ushort)(DAT_1f80020c.y ^ DAT_1f800208.y) << 0x10))) &&
								(DAT_1f800210.x = DAT_1f800210.y, -1 < (int)((uint)(ushort)(DAT_1f80020c.y ^ DAT_1f800210.y)
								<< 0x10)))))))
								goto LAB_00042900;

							//*local_a0_1124 = (uint)prim & 0xffffff;

							setPolyFT4(prim);
							addPrim(ot + (iVar1 >> 1), prim);

							gte_stsxy(&prim->x3);

							*(uint *)&prim->r0 = pc->colour;
							*(uint *)&prim->u0 = (uint)vertex->uv | pc->clut;
							*(uint *)&prim->u1 = (uint)vertex[1].uv | pc->tpage;
							*(uint *)&prim->u2 = (uint)vertex[5].uv;
							*(uint *)&prim->u3 = (uint)vertex[6].uv;

							prim++;
							//pc->primptr = (char*)prim;
							return;
						}
						else 
						{
							if ((((ushort)DAT_1f800224.x < 0x140) ||
								((int)((uint)(ushort)(DAT_1f80020c.x ^ DAT_1f800208.x) << 0x10) < 0)) ||
								((int)((uint)(ushort)(DAT_1f80020c.x ^ DAT_1f800210.x) << 0x10) < 0))
								goto LAB_00042824;

						LAB_00042900:
							//local_a0_1124 = (uint *)(uint)(ushort)DAT_1f800210.x;
							*(SXYPAIR *)&prim->x2 = DAT_1f80020c;
						}

						gte_stotz(&iVar1);
						//puVar4 = ot + (iVar1 >> 1);

						if ((((ushort)DAT_1f80021c.y < 0x10a) ||
							((ushort)DAT_1f800220.y < 0x10a)) ||
							((((ushort)DAT_1f800224.y < 0x10a ||
							(((ushort)DAT_1f80020c.y < 0x10a ||
							((int)((uint)(ushort)(DAT_1f80020c.y ^ DAT_1f800208.y) << 0x10) < 0)))) ||
							((int)((uint)(ushort)(DAT_1f80020c.y ^ DAT_1f800210.y) << 0x10) < 0))))
						{
							if (((0x13f < (ushort)DAT_1f80020c.x) &&
								(0x13f < (ushort)DAT_1f800220.x)) &&
								(0x13f < (ushort)DAT_1f80021c.x))
							{
								if (((0x13f < (ushort)DAT_1f800224.x) &&
									(-1 < (int)((uint)(ushort)(DAT_1f800220.x ^ DAT_1f80021c.x) << 0x10))) &&
									(//local_a0_1124 = (uint *)(DAT_1f800224.x & 0xffff),
									-1 < (int)((uint)(ushort)(DAT_1f800220.x ^ DAT_1f800224.x) << 0x10)))
									goto LAB_00042ab4;
							}

							setPolyFT4(prim);

							*(uint *)&prim->r0 = pc->colour;

							gte_stsxy3(&prim->x0, &prim->x1, &prim->x3);

							*(uint *)&prim->u0 = (uint)vertex[2].uv | pc->clut;
							*(uint *)&prim->u1 = (uint)vertex[7].uv | pc->tpage;
							*(uint *)&prim->u2 = (uint)vertex[1].uv;
							*(uint *)&prim->u3 = (uint)vertex[6].uv;

							prim++;
							//local_a0_1124 = puVar4;

							//pc->primptr = (char*)prim;
							return;
						}
					}

				LAB_00042ab4:
					iVar6--;
					VST = (MVERTEX(*)[5][5])(VST-1 + 20);

				} while (iVar6 != -1);
			}

			iVar7 = iVar5;
		} while (iVar5 < n);
	}

	pc->primptr = (char*)prim;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SubdivNxM(char *polys /*$t4*/, unsigned long n /*$s1*/, unsigned long m /*$s0*/, int ofse /*$s2*/)
 // line 489, offset 0x00042aec
	/* begin block 1 */
		// Start line: 490
		// Start offset: 0x00042AEC
		// Variables:
	// 		struct MVERTEX (*VSP)[5][5]; // $t3
	// 		struct _pct *pc; // $t2

		/* begin block 1.1 */
			// Start line: 490
			// Start offset: 0x00042AEC
			// Variables:
		// 		unsigned long indices; // $a0
		// 		struct SVECTOR *v0; // $t1
		// 		struct SVECTOR *v1; // $a1
		// 		struct SVECTOR *v2; // $t0
		/* end block 1.1 */
		// End offset: 0x00042AEC
		// End Line: 490

		/* begin block 1.2 */
			// Start line: 490
			// Start offset: 0x00042AEC
			// Variables:
		// 		unsigned long uv_01; // $v1
		// 		unsigned long uv_23; // $a2
		/* end block 1.2 */
		// End offset: 0x00042AEC
		// End Line: 490

		/* begin block 1.3 */
			// Start line: 547
			// Start offset: 0x00042DEC
			// Variables:
		// 		int Z; // stack offset -24

			/* begin block 1.3.1 */
				// Start line: 562
				// Start offset: 0x00042E60
				// Variables:
			// 		unsigned long texInfo; // $a0
			/* end block 1.3.1 */
			// End offset: 0x00042ED4
			// End Line: 569
		/* end block 1.3 */
		// End offset: 0x00042F04
		// End Line: 575
	/* end block 1 */
	// End offset: 0x00042F34
	// End Line: 577

	/* begin block 2 */
		// Start line: 1283
	/* end block 2 */
	// End Line: 1284

	/* begin block 3 */
		// Start line: 1287
	/* end block 3 */
	// End Line: 1288

	/* begin block 4 */
		// Start line: 1288
	/* end block 4 */
	// End Line: 1289

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SubdivNxM(char *polys, ulong n, ulong m, int ofse)
{
	UNIMPLEMENTED_PRINTONCE();
	/*
	undefined4 in_zero;
	undefined4 in_at;
	undefined4 *puVar1;
	int iVar2;
	uint uVar3;
	undefined4 *ot;
	int iVar5;
	undefined4 *puVar6;
	uint uVar7;
	undefined4 *puVar8;
	undefined4 *puVar9;
	undefined4 uVar10;
	int local_18;

	iVar5 = DAT_1f8000c8;
	DAT_1f8000b4 = DAT_1f8000b4 + ofse * 4;
	uVar3 = *(uint *)(polys + 4);
	puVar9 = (undefined4 *)(DAT_1f8000c8 + (uVar3 & 0xff) * 8);
	puVar6 = (undefined4 *)(DAT_1f8000c8 + (uVar3 >> 5 & 0x7f8));
	DAT_1f800228 = *puVar9;
	DAT_1f80022c._0_2_ = (undefined2)puVar9[1];
	uVar10 = puVar6[1];
	(&DAT_1f800228)[n * 2] = *puVar6;
	(&DAT_1f80022c)[n * 2] = uVar10;
	iVar2 = (uVar3 >> 0x18) * 8;
	puVar8 = (undefined4 *)(iVar5 + iVar2);
	puVar1 = &DAT_1f800228 + m * 10;
	uVar10 = puVar8[1];
	*puVar1 = *puVar8;
	(&DAT_1f80022c)[m * 10] = uVar10;
	iVar5 = DAT_1f8000c8;
	ot = (undefined4 *)((uVar3 >> 0xd & 0x7f8) + DAT_1f8000c8);
	uVar10 = ot[1];
	puVar1[n * 2] = *ot;
	(puVar1 + n * 2)[1] = uVar10;
	setCopReg(2, in_zero, *puVar9);
	setCopReg(2, in_at, puVar9[1]);
	setCopReg(2, iVar5, *puVar6);
	setCopReg(2, iVar2, puVar6[1]);
	setCopReg(2, ot, *puVar8);
	setCopReg(2, puVar6, puVar8[1]);
	copFunction(2, 0x280030);
	uVar10 = *(undefined4 *)(polys + 0xc);
	DAT_1f80022c = CONCAT22((short)*(undefined4 *)(polys + 8), (undefined2)DAT_1f80022c);
	*(undefined2 *)((int)&DAT_1f80022c + n * 8 + 2) =
		(short)((uint)*(undefined4 *)(polys + 8) >> 0x10);
	*(undefined2 *)((int)&DAT_1f80022c + m * 0x28 + 2) = (short)((uint)uVar10 >> 0x10);
	*(undefined2 *)((int)&DAT_1f80022c + n * 8 + m * 0x28 + 2) = (short)uVar10;
	copFunction(2, 0x1400006);
	_DAT_1f800208 = getCopReg(2, 0xc);
	_DAT_1f80020c = getCopReg(2, 0xd);
	DAT_1f800210 = getCopReg(2, 0xe);
	if (((0x13f < DAT_1f800208) && (0x13f < DAT_1f80020c)) && (0x13f < (ushort)DAT_1f800210)) {
		if (_DAT_1f80020c << 0x10 < 0) {
			DAT_1f800208 = DAT_1f800208 ^ 1;
		}
		if (DAT_1f800208 == 0) {
			if (DAT_1f800210 << 0x10 < 0) {
				if (DAT_1f80020c == 1) goto LAB_00042f08;
			}
			else {
				if (DAT_1f80020c == 0) goto LAB_00042f08;
			}
		}
	}
	DAT_1f80020a = (ushort)((uint)_DAT_1f800208 >> 0x10);
	if (((0x109 < DAT_1f80020a) &&
		(DAT_1f80020e = (ushort)((uint)_DAT_1f80020c >> 0x10), 0x109 < DAT_1f80020e)) &&
		(DAT_1f800210._2_2_ = (ushort)((uint)DAT_1f800210 >> 0x10), 0x109 < DAT_1f800210._2_2_)) {
		iVar5 = (int)(short)DAT_1f80020a;
		if (0x10f < ((int)(short)DAT_1f80020e - iVar5) + (int)(short)DAT_1f800210._2_2_ + 8U) {
			if ((int)(short)DAT_1f80020e < 0) {
				if (iVar5 == 1) {
				LAB_00042db8:
					if ((int)((uint)DAT_1f800210._2_2_ << 0x10) < 0) {
						if (DAT_1f80020e == 1) goto LAB_00042f08;
					}
					else {
						if (DAT_1f80020e == 0) goto LAB_00042f08;
					}
				}
			}
			else {
				if (iVar5 == 0) goto LAB_00042db8;
			}
		}
	}
	local_18 = getCopReg(2, 0x18);
	if (local_18 < 0) {
		setCopReg(2, in_zero, (&DAT_1f800228)[m * 10 + n * 2]);
		setCopReg(2, in_at, (&DAT_1f800228 + m * 10 + n * 2)[1]);
		copFunction(2, 0x180001);
		copFunction(2, 0x1400006);
		local_18 = getCopReg(2, 0x18);
		local_18 = -local_18;
	}
	if (0 < local_18) {
		uVar3 = *(uint *)polys >> 8 & 0xffff;
		uVar7 = *(uint *)polys >> 8 & 0xff;
		if (DAT_1f8000cc != uVar3) {
			DAT_1f8000b8 = (uint)*(ushort *)((uVar3 >> 8) * 2 + uVar7 * 0x40 + DAT_1f800028) << 0x10;
			DAT_1f8000bc = (uint)*(ushort *)(uVar7 * 2 + DAT_1f800024) << 0x10;
			DAT_1f8000cc = uVar3;
		}
		makeMesh((MVERTEX(*)[5][5])&DAT_1f800228, m, n);
		drawMesh((MVERTEX(*)[5][5])&DAT_1f800228, m, n, (_pct *)&DAT_1f800020);
	}
LAB_00042f08:
	DAT_1f8000b4 = DAT_1f8000b4 + ofse * -4;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TileNxN(struct MODEL *model /*$s4*/, int levels /*$s2*/, int Dofse /*$s6*/)
 // line 581, offset 0x00042f40
	/* begin block 1 */
		// Start line: 582
		// Start offset: 0x00042F40
		// Variables:
	// 		int i; // $s3
	// 		char *polys; // $s0
	// 		char ttype; // $a3
	// 		unsigned long tiletypes; // $s1
	// 		int baseOffset; // $s5
	/* end block 1 */
	// End offset: 0x00043090
	// End Line: 631

	/* begin block 2 */
		// Start line: 1162
	/* end block 2 */
	// End Line: 1163

	/* begin block 3 */
		// Start line: 1570
	/* end block 3 */
	// End Line: 1571

// [D]
void TileNxN(MODEL *model, int levels, int Dofse)
{
	uint uVar1;
	unsigned char *polys;
	uint uVar2;
	int iVar3;
	int ofse;

	uVar1 = 0;
	ofse = 0x85;
	polys = (unsigned char *)model->poly_block;
	plotContext.verts = (SVECTOR *)model->vertices;
	uVar2 = *(uint *)(model + 1) >> 2;
	if ((*(uint *)model & 0x40000080) != 0) {
		ofse = 0xe5;
	}
	iVar3 = 0;
	if (model->num_polys != 0) {
		do {
			if (true) {
				switch (uVar1) {
				case 0:
				case 1:
					SubdivNxM((char *)polys, levels, levels, ofse);
					break;
				case 3:
					SubdivNxM((char *)polys, levels, 1, Dofse);
					break;
				case 4:
					SubdivNxM((char *)polys, levels, levels, 0x85);
				}
			}
			uVar1 = uVar2 & 7;
			uVar2 = uVar2 >> 3;
			iVar3 = iVar3 + 1;
			polys = polys + PolySizes[*polys];
		} while (iVar3 < (int)(uint)model->num_polys);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessSubDivisionLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
 // line 641, offset 0x00042f34
	/* begin block 1 */
		// Start line: 1553
	/* end block 1 */
	// End Line: 1554

	/* begin block 2 */
		// Start line: 1618
	/* end block 2 */
	// End Line: 1619

	/* begin block 3 */
		// Start line: 1619
	/* end block 3 */
	// End Line: 1620

void ProcessSubDivisionLump(char *lump_ptr, int lump_size)
{
	UNIMPLEMENTED();
	/*
	SubDivisionArrays = lump_ptr;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessLowDetailTable(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
 // line 651, offset 0x00043090
	/* begin block 1 */
		// Start line: 652
		// Start offset: 0x00043090
		// Variables:
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x0004310C
	// End Line: 674

	/* begin block 2 */
		// Start line: 1780
	/* end block 2 */
	// End Line: 1781

	/* begin block 3 */
		// Start line: 1801
	/* end block 3 */
	// End Line: 1802

	/* begin block 4 */
		// Start line: 1806
	/* end block 4 */
	// End Line: 1807

// [D]
void ProcessLowDetailTable(char *lump_ptr, int lump_size)
{
	int i;

	Low2HighDetailTable = (ushort *)lump_ptr;
	Low2LowerDetailTable = (ushort *)(lump_ptr + num_models_in_pack * 2);

	for (i = 0; i < num_models_in_pack; i++)
	{
		if (Low2LowerDetailTable[i] == 0xFFFF)
			pLodModels[i] = modelpointers[i];
		else
			pLodModels[i] = modelpointers[Low2LowerDetailTable[i]];
	}
}





