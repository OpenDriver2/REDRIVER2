#include "THISDUST.H"
#include "TILE.H"


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

void Tile1x1(MODEL *model)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	int iVar2;
	uint uVar3;
	undefined4 in_zero;
	undefined4 in_at;
	undefined4 *puVar4;
	uint *puVar5;
	undefined4 *puVar6;
	uint uVar7;
	undefined4 *puVar8;
	uint in_a1;
	uint uVar9;
	uint *puVar10;
	int iVar11;
	uint uVar12;
	uint uVar13;
	uint uVar14;
	int iVar15;
	int local_10;

	uVar13 = (uint)model->num_polys;
	puVar10 = (uint *)model->poly_block;
	iVar11 = model->vertices;
	do {
		uVar13 = uVar13 - 1;
		if (uVar13 == 0xffffffff) {
			return;
		}
		uVar9 = puVar10[1];
		uVar12 = *puVar10;
		iVar15 = DAT_1f8000b4 + 0x214;
		puVar8 = (undefined4 *)(iVar11 + (uVar9 & 0xff) * 8);
		puVar6 = (undefined4 *)(iVar11 + (uVar9 >> 5 & 0x7f8));
		puVar4 = (undefined4 *)(iVar11 + (uVar9 >> 0x18) * 8);
		setCopReg(2, in_zero, *puVar8);
		setCopReg(2, in_at, puVar8[1]);
		setCopReg(2, puVar4, *puVar6);
		setCopReg(2, puVar6, puVar6[1]);
		setCopReg(2, puVar8, *puVar4);
		setCopReg(2, in_a1, puVar4[1]);
		copFunction(2, 0x280030);
		uVar7 = uVar12 >> 8 & 0xff;
		uVar1 = *(ushort *)((uVar12 >> 0xf & 0x1fe) + uVar7 * 0x40 + DAT_1f800028);
		in_a1 = (uint)*(ushort *)(uVar7 * 2 + DAT_1f800024) << 0x10;
		copFunction(2, 0x1400006);
		uVar7 = puVar10[2];
		uVar14 = puVar10[3];
		iVar2 = getCopReg(2, 0x18);
		copFunction(2, 0x158002d);
		if (iVar2 < 0) {
			uVar3 = getCopReg(2, 0xc);
			DAT_1f8000b0[2] = uVar3;
			puVar4 = (undefined4 *)(iVar11 + (uVar9 >> 0xd & 0x7f8));
			setCopReg(2, in_zero, *puVar4);
			setCopReg(2, in_at, puVar4[1]);
			copFunction(2, 0x180001);
			copFunction(2, 0x1400006);
			iVar2 = getCopReg(2, 0x18);
			if ((iVar2 < 0) && (local_10 = getCopReg(2, 7), 1 < local_10)) {
			LAB_00041cc4:
				puVar5 = (uint *)(iVar15 + (local_10 >> 1) * 4);
				uVar9 = *puVar5;
				*puVar5 = (uint)DAT_1f8000b0 & 0xffffff;
				*DAT_1f8000b0 = uVar9 & 0xffffff | 0x9000000;
				uVar9 = getCopReg(2, 0xc);
				DAT_1f8000b0[4] = uVar9;
				uVar9 = getCopReg(2, 0xd);
				DAT_1f8000b0[6] = uVar9;
				uVar9 = getCopReg(2, 0xe);
				DAT_1f8000b0[8] = uVar9;
				uVar9 = DAT_1f8000c0;
				DAT_1f8000b0[3] = uVar7 & 0xffff | (uint)uVar1 << 0x10;
				DAT_1f8000b0[5] = uVar7 >> 0x10 | in_a1;
				DAT_1f8000b0[7] = uVar14 >> 0x10;
				DAT_1f8000b0[9] = uVar14 & 0xffff;
				DAT_1f8000b0[1] = uVar9;
				DAT_1f8000b0 = DAT_1f8000b0 + 10;
			}
		}
		else {
			local_10 = getCopReg(2, 7);
			if (1 < local_10) {
				uVar3 = getCopReg(2, 0xc);
				DAT_1f8000b0[2] = uVar3;
				puVar4 = (undefined4 *)(iVar11 + (uVar9 >> 0xd & 0x7f8));
				setCopReg(2, in_zero, *puVar4);
				setCopReg(2, in_at, puVar4[1]);
				copFunction(2, 0x180001);
				goto LAB_00041cc4;
			}
		}
		puVar10 = (uint *)((int)puVar10 + PolySizes[uVar12 & 0xff]);
	} while (true);
	*/
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

void DrawTILES(int tile_amount)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	uint uVar3;
	ushort *puVar4;
	uint uVar5;
	ushort **ppuVar6;
	uint uVar7;

	if (-1 < gTimeOfDay) {
		if (gTimeOfDay < 3) {
			DAT_1f8000c0 = combointensity & 0xffffffU | 0x2c000000;
		}
		else {
			if (gTimeOfDay == 3) {
				DAT_1f8000c0 = ((int)((uint)combointensity >> 0x10 & 0xff) / 3) * 0x10000 |
					((int)((uint)combointensity >> 8 & 0xff) / 3) * 0x100 |
					(int)(combointensity & 0xffU) / 3 | 0x2c000000U;
			}
		}
	}
	uVar7 = 0xffffffff;
	if (gWeather - 1U < 2) {
		uVar3 = DAT_1f8000c0 >> 2 & 0x3f;
		DAT_1f8000c0 = uVar3 * 0x30000 | uVar3 * 0x300 | uVar3 * 3 | 0x2c000000;
	}
	tile_amount = tile_amount + -1;
	DAT_1f8000b4 = current->ot;
	DAT_1f8000b0 = current->primptr;
	DAT_1f800024 = &texture_pages;
	DAT_1f800028 = &texture_cluts;
	DAT_1f8000cc = 0x18273472;
	ppuVar6 = (ushort **)tile_overflow_buffer;
	while (tile_amount != -1) {
		puVar4 = *ppuVar6;
		DAT_1f800044 = (uint)*puVar4;
		DAT_1f800048 = (int)((uint)puVar4[1] << 0x10) >> 0x11;
		DAT_1f80004c = (uint)puVar4[2];
		ppuVar6 = ppuVar6 + 1;
		uVar5 = (uint)puVar4[3] & 0x3f;
		uVar3 = (uint)(puVar4[3] >> 6) | ((uint)puVar4[1] & 1) << 10;
		if (uVar7 == uVar5) {
			iVar1 = Apply_InvCameraMatrixSetTrans(&DAT_1f800044);
		}
		else {
			iVar1 = Apply_InvCameraMatrixAndSetMatrix(&DAT_1f800044, CompoundMatrix + uVar5);
			uVar7 = uVar5;
		}
		if (iVar1 < 0x1b59) {
			if (Low2HighDetailTable[uVar3] != 0xffff) {
				uVar3 = (uint)Low2HighDetailTable[uVar3];
			}
			if (iVar1 < 2000) {
				TileNxN(modelpointers1536[uVar3], 4, 0x4b);
			}
			else {
				TileNxN(modelpointers1536[uVar3], 2, 0x23);
			}
		}
		else {
			iVar2 = uVar3 << 2;
			if (9000 < iVar1) {
				iVar2 = uVar3 << 2;
				if (Low2LowerDetailTable[uVar3] != 0xffff) {
					iVar2 = (uint)Low2LowerDetailTable[uVar3] << 2;
				}
			}
			Tile1x1(*(MODEL **)((int)modelpointers1536 + iVar2));
		}
		tile_amount = tile_amount + -1;
	}
	current->primptr = DAT_1f8000b0;
	return;*/
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

void makeMesh(MVERTEX(*VSP)[5][5], int m, int n)
{
	UNIMPLEMENTED();
	/*
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

	if (n == 4) {
		uVar3 = *(uint *)*VSP;
		uVar2 = *(uint *)&(*VSP)[0].vz;
		uVar5 = uVar3 ^ 0x8000;
		uVar9 = *(uint *)(*VSP + 4) ^ 0x8000;
		uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
		*(uint *)(*VSP + 2) = uVar5 ^ 0x8000;
		uVar6 = uVar2 ^ 0x8000;
		uVar3 = uVar3 ^ 0x8000;
		uVar9 = *(uint *)(*VSP + 4) ^ 0x8000;
		uVar10 = *(uint *)&(*VSP)[4].vz ^ 0x8000;
		uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);
		*(uint *)(*VSP + 1) = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
		uVar2 = uVar2 ^ 0x8000;
		*(uint *)(*VSP + 3) = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
		*(uint *)&(*VSP)[2].vz = uVar6 ^ 0x8000;
		*(uint *)&(*VSP)[1].vz = (uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		*(uint *)&(*VSP)[3].vz = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		if (m == 1) {
			uVar2 = *(uint *)&(*VSP)[5].vz;
			uVar5 = *(uint *)(*VSP + 5) ^ 0x8000;
			uVar9 = *(uint *)(*VSP + 9) ^ 0x8000;
			uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
			*(uint *)(*VSP + 7) = uVar5 ^ 0x8000;
			uVar6 = uVar2 ^ 0x8000;
			uVar3 = *(uint *)(*VSP + 5) ^ 0x8000;
			uVar9 = *(uint *)(*VSP + 9) ^ 0x8000;
			uVar10 = *(uint *)&(*VSP)[9].vz ^ 0x8000;
			uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);
			*(uint *)(*VSP + 6) = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
			uVar2 = uVar2 ^ 0x8000;
			*(uint *)(*VSP + 8) = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[7].vz = uVar6 ^ 0x8000;
			*(uint *)&(*VSP)[6].vz = (uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[8].vz =
				(uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		}
		else {
			iVar13 = 4;
			uVar2 = *(uint *)&(*VSP)[0x14].vz;
			uVar5 = *(uint *)(*VSP + 0x14) ^ 0x8000;
			uVar9 = *(uint *)(*VSP + 0x18) ^ 0x8000;
			uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
			*(uint *)(*VSP + 0x16) = uVar5 ^ 0x8000;
			uVar6 = uVar2 ^ 0x8000;
			uVar3 = *(uint *)(*VSP + 0x14) ^ 0x8000;
			uVar9 = *(uint *)(*VSP + 0x18) ^ 0x8000;
			uVar10 = *(uint *)&(*VSP)[0x18].vz ^ 0x8000;
			uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);
			*(uint *)(*VSP + 0x15) = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
			uVar2 = uVar2 ^ 0x8000;
			*(uint *)(*VSP + 0x17) = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[0x16].vz = uVar6 ^ 0x8000;
			*(uint *)&(*VSP)[0x15].vz =
				(uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[0x17].vz =
				(uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			do {
				iVar13 = iVar13 + -1;
				uVar3 = *(uint *)*VSP;
				uVar2 = *(uint *)&(*VSP)[0].vz;
				uVar5 = uVar3 ^ 0x8000;
				uVar9 = *(uint *)(*VSP + 0x14) ^ 0x8000;
				uVar5 = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU);
				*(uint *)(*VSP + 10) = uVar5 ^ 0x8000;
				uVar6 = uVar2 ^ 0x8000;
				uVar3 = uVar3 ^ 0x8000;
				uVar9 = *(uint *)(*VSP + 0x14) ^ 0x8000;
				uVar10 = *(uint *)&(*VSP)[0x14].vz ^ 0x8000;
				uVar6 = (uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU);
				*(uint *)(*VSP + 5) = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0xffff7fffU) ^ 0x8000;
				uVar2 = uVar2 ^ 0x8000;
				*(uint *)(*VSP + 0xf) = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000
					;
				*(uint *)&(*VSP)[10].vz = uVar6 ^ 0x8000;
				*(uint *)&(*VSP)[5].vz =
					(uVar2 | uVar6) - ((int)(uVar2 ^ uVar6) >> 1 & 0x7f7f7fffU) ^ 0x8000;
				*(uint *)&(*VSP)[0xf].vz =
					(uVar6 | uVar10) - ((int)(uVar6 ^ uVar10) >> 1 & 0x7f7f7fffU) ^ 0x8000;
				VSP = (MVERTEX(*)[5][5])(*VSP + 1);
			} while (-1 < iVar13);
		}
	}
	else {
		uVar2 = *(uint *)*VSP;
		uVar9 = *(uint *)(*VSP + 2);
		uVar6 = *(uint *)&(*VSP)[0].vz;
		uVar5 = uVar2 ^ 0x8000;
		uVar3 = uVar9 ^ 0x8000;
		uVar10 = (uVar5 | uVar3) - ((int)(uVar5 ^ uVar3) >> 1 & 0xffff7fffU);
		uVar5 = *(uint *)&(*VSP)[2].vz;
		*(uint *)(*VSP + 1) = uVar10 ^ 0x8000;
		uVar3 = uVar6 ^ 0x8000;
		uVar5 = uVar5 ^ 0x8000;
		uVar3 = (uVar3 | uVar5) - ((int)(uVar3 ^ uVar5) >> 1 & 0x7f7f7fffU);
		*(uint *)&(*VSP)[1].vz = uVar3 ^ 0x8000;
		if (m == 1) {
			uVar5 = *(uint *)(*VSP + 5) ^ 0x8000;
			uVar9 = *(uint *)(*VSP + 7) ^ 0x8000;
			*(uint *)(*VSP + 6) = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0xffff7fffU) ^ 0x8000;
			uVar5 = *(uint *)&(*VSP)[5].vz ^ 0x8000;
			uVar9 = *(uint *)&(*VSP)[7].vz ^ 0x8000;
			*(uint *)&(*VSP)[6].vz = (uVar5 | uVar9) - ((int)(uVar5 ^ uVar9) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		}
		else {
			uVar2 = uVar2 ^ 0x8000;
			uVar9 = uVar9 ^ 0x8000;
			uVar4 = *(uint *)&(*VSP)[10].vz;
			uVar7 = *(uint *)(*VSP + 10) ^ 0x8000;
			uVar11 = *(uint *)(*VSP + 0xc) ^ 0x8000;
			uVar11 = (uVar7 | uVar11) - ((int)(uVar7 ^ uVar11) >> 1 & 0xffff7fffU);
			*(uint *)(*VSP + 0xb) = uVar11 ^ 0x8000;
			uVar7 = uVar4 ^ 0x8000;
			uVar1 = *(uint *)(*VSP + 0xc) ^ 0x8000;
			uVar12 = *(uint *)&(*VSP)[0xc].vz ^ 0x8000;
			uVar8 = (uVar7 | uVar12) - ((int)(uVar7 ^ uVar12) >> 1 & 0x7f7f7fffU);
			uVar7 = *(uint *)(*VSP + 10) ^ 0x8000;
			*(uint *)(*VSP + 5) = (uVar2 | uVar7) - ((int)(uVar2 ^ uVar7) >> 1 & 0xffff7fffU) ^ 0x8000;
			uVar6 = uVar6 ^ 0x8000;
			uVar4 = uVar4 ^ 0x8000;
			*(uint *)(*VSP + 6) = (uVar10 | uVar11) - ((int)(uVar10 ^ uVar11) >> 1 & 0xffff7fffU) ^ 0x8000
				;
			*(uint *)(*VSP + 7) = (uVar9 | uVar1) - ((int)(uVar9 ^ uVar1) >> 1 & 0xffff7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[0xb].vz = uVar8 ^ 0x8000;
			*(uint *)&(*VSP)[5].vz = (uVar6 | uVar4) - ((int)(uVar6 ^ uVar4) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[6].vz = (uVar3 | uVar8) - ((int)(uVar3 ^ uVar8) >> 1 & 0x7f7f7fffU) ^ 0x8000;
			*(uint *)&(*VSP)[7].vz =
				(uVar5 | uVar12) - ((int)(uVar5 ^ uVar12) >> 1 & 0x7f7f7fffU) ^ 0x8000;
		}
	}
	return;*/
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
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar2;
	MVERTEX(*paaMVar3)[5][5];
	MVERTEX(*paaMVar4)[5][5];
	int iVar5;
	uint *puVar6;
	undefined4 *puVar7;
	int iVar8;
	int iVar9;
	MVERTEX *pMVar10;
	int iVar11;

	iVar11 = 0;
	puVar6 = *(uint **)(pc->ptexture_pages + 0x46);
	paaMVar4 = VSP;
	if (0 < n) {
		do {
			iVar8 = m + -1;
			iVar5 = iVar11 + 2;
			if (iVar8 != -1) {
				pMVar10 = *VSP + iVar8 * 5;
				do {
					puVar7 = (undefined4 *)(&pMVar10->vx + iVar11 * 4);
					iVar9 = *(int *)(pc->ptexture_pages + 0x48);
					setCopReg(2, in_zero, *puVar7);
					setCopReg(2, in_at, puVar7[1]);
					setCopReg(2, puVar7 + 10, puVar7[2]);
					setCopReg(2, puVar7 + 2, puVar7[3]);
					setCopReg(2, paaMVar4, puVar7[10]);
					setCopReg(2, 0x9000000, puVar7[0xb]);
					copFunction(2, 0x280030);
					copFunction(2, 0x158002d);
					iVar1 = getCopReg(2, 7);
					if (1 < iVar1) {
						_DAT_1f800208 = getCopReg(2, 0xc);
						_DAT_1f80020c = getCopReg(2, 0xd);
						DAT_1f800210 = getCopReg(2, 0xe);
						paaMVar4 = (MVERTEX(*)[5][5])(iVar9 + (iVar1 >> 1) * 4);
						*puVar6 = *(uint *)*paaMVar4 & 0xffffff | 0x9000000;
						uVar2 = getCopReg(2, 0xc);
						puVar6[2] = uVar2;
						uVar2 = getCopReg(2, 0xd);
						puVar6[4] = uVar2;
						uVar2 = getCopReg(2, 0xe);
						puVar6[6] = uVar2;
						uVar2 = getCopReg(2, 0xd);
						puVar6[0x10] = uVar2;
						setCopReg(2, in_zero, puVar7[4]);
						setCopReg(2, in_at, puVar7[5]);
						setCopReg(2, puVar7 + 0xc, puVar7[0xe]);
						setCopReg(2, puVar7 + 0xe, puVar7[0xf]);
						setCopReg(2, puVar7 + 4, puVar7[0xc]);
						setCopReg(2, 0x9000000, puVar7[0xd]);
						copFunction(2, 0x280030);
						copFunction(2, 0x158002d);
						DAT_1f80021c = getCopReg(2, 0xc);
						DAT_1f800220 = getCopReg(2, 0xd);
						DAT_1f800224 = getCopReg(2, 0xe);
						if (((DAT_1f80020c < 0x140) || (DAT_1f800208 < 0x140)) || ((ushort)DAT_1f800210 < 0x140)
							) {
						LAB_00042824:
							if (((0x109 < DAT_1f80020a) && (0x109 < DAT_1f80020e)) &&
								((0x109 < DAT_1f800210._2_2_ &&
								(((DAT_1f800224._2_2_ = (ushort)(DAT_1f800224 >> 0x10), 0x109 < DAT_1f800224._2_2_
									&& (-1 < (int)((uint)(DAT_1f80020e ^ DAT_1f80020a) << 0x10))) &&
									(DAT_1f800210._0_2_ = DAT_1f800210._2_2_,
										-1 < (int)((uint)(DAT_1f80020e ^ DAT_1f800210._2_2_) << 0x10)))))))
								goto LAB_00042900;
							*(uint *)*paaMVar4 = (uint)puVar6 & 0xffffff;
							uVar2 = getCopReg(2, 0xe);
							puVar6[8] = uVar2;
							puVar6[1] = *(uint *)(pc->ptexture_pages + 0x4e);
							puVar6[3] = (uint)*(ushort *)((int)puVar7 + 6) | *(uint *)(pc->ptexture_pages + 0x4a);
							puVar6[5] = (uint)*(ushort *)((int)puVar7 + 0xe) |
								*(uint *)(pc->ptexture_pages + 0x4c);
							puVar6[7] = (uint)*(ushort *)((int)puVar7 + 0x2e);
							puVar6[9] = (uint)*(ushort *)((int)puVar7 + 0x36);
							puVar6 = puVar6 + 10;
						}
						else {
							if ((((ushort)DAT_1f800224 < 0x140) ||
								((int)((uint)(DAT_1f80020c ^ DAT_1f800208) << 0x10) < 0)) ||
								((int)((uint)(DAT_1f80020c ^ (ushort)DAT_1f800210) << 0x10) < 0))
								goto LAB_00042824;
						LAB_00042900:
							paaMVar4 = (MVERTEX(*)[5][5])(uint)(ushort)DAT_1f800210;
							puVar6[6] = _DAT_1f80020c;
						}
						iVar1 = getCopReg(2, 7);
						paaMVar3 = (MVERTEX(*)[5][5])(iVar9 + (iVar1 >> 1) * 4);
						if (((DAT_1f80021c._2_2_ < 0x10a) || (DAT_1f800220._2_2_ < 0x10a)) ||
							(((DAT_1f800224._2_2_ < 0x10a ||
							((DAT_1f80020e < 0x10a || ((int)((uint)(DAT_1f80020e ^ DAT_1f80020a) << 0x10) < 0))
								)) || ((int)((uint)(DAT_1f80020e ^ DAT_1f800210._2_2_) << 0x10) < 0)))) {
							if (((0x13f < DAT_1f80020c) && (0x13f < (ushort)DAT_1f800220)) &&
								(0x13f < (ushort)DAT_1f80021c)) {
								if (((0x13f < (ushort)DAT_1f800224) &&
									(-1 < (int)((uint)((ushort)DAT_1f800220 ^ (ushort)DAT_1f80021c) << 0x10))) &&
									(paaMVar4 = (MVERTEX(*)[5][5])(DAT_1f800224 & 0xffff),
										-1 < (int)((uint)((ushort)DAT_1f800220 ^ (ushort)DAT_1f800224) << 0x10)))
									goto LAB_00042ab4;
							}
							uVar2 = *(uint *)*paaMVar3;
							*(uint *)*paaMVar3 = (uint)puVar6 & 0xffffff;
							*puVar6 = uVar2 & 0xffffff | 0x9000000;
							puVar6[1] = *(uint *)(pc->ptexture_pages + 0x4e);
							uVar2 = getCopReg(2, 0xc);
							puVar6[2] = uVar2;
							uVar2 = getCopReg(2, 0xd);
							puVar6[4] = uVar2;
							uVar2 = getCopReg(2, 0xe);
							puVar6[8] = uVar2;
							puVar6[3] = (uint)*(ushort *)((int)puVar7 + 0x16) |
								*(uint *)(pc->ptexture_pages + 0x4a);
							puVar6[5] = (uint)*(ushort *)((int)puVar7 + 0x3e) |
								*(uint *)(pc->ptexture_pages + 0x4c);
							puVar6[7] = (uint)*(ushort *)((int)puVar7 + 0xe);
							puVar6[9] = (uint)*(ushort *)((int)puVar7 + 0x36);
							puVar6 = puVar6 + 10;
							paaMVar4 = paaMVar3;
						}
					}
				LAB_00042ab4:
					iVar8 = iVar8 + -1;
					pMVar10 = (MVERTEX *)(&pMVar10[-0x19].vx + 0x50);
				} while (iVar8 != -1);
			}
			iVar11 = iVar5;
		} while (iVar5 < n);
	}
	*(uint **)(pc->ptexture_pages + 0x46) = puVar6;
	return;*/
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
	UNIMPLEMENTED();
	/*
	undefined4 in_zero;
	undefined4 in_at;
	undefined4 *puVar1;
	int iVar2;
	uint uVar3;
	undefined4 *puVar4;
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
	puVar4 = (undefined4 *)((uVar3 >> 0xd & 0x7f8) + DAT_1f8000c8);
	uVar10 = puVar4[1];
	puVar1[n * 2] = *puVar4;
	(puVar1 + n * 2)[1] = uVar10;
	setCopReg(2, in_zero, *puVar9);
	setCopReg(2, in_at, puVar9[1]);
	setCopReg(2, iVar5, *puVar6);
	setCopReg(2, iVar2, puVar6[1]);
	setCopReg(2, puVar4, *puVar8);
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

void TileNxN(MODEL *model, int levels, int Dofse)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	byte *polys;
	uint uVar2;
	int iVar3;
	int ofse;

	uVar1 = 0;
	ofse = 0x85;
	polys = (byte *)model->poly_block;
	DAT_1f8000c8 = model->vertices;
	uVar2 = *(uint *)(model + 1) >> 2;
	if ((*(uint *)model & 0x40000080) != 0) {
		ofse = 0xe5;
	}
	iVar3 = 0;
	if (model->num_polys != 0) {
		do {
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
			uVar1 = uVar2 & 7;
			uVar2 = uVar2 >> 3;
			iVar3 = iVar3 + 1;
			polys = polys + PolySizes[*polys];
		} while (iVar3 < (int)(uint)model->num_polys);
	}
	return;*/
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

void ProcessLowDetailTable(char *lump_ptr, int lump_size)
{
	UNIMPLEMENTED();
	/*
	ushort *puVar1;
	int iVar2;
	MODEL **ppMVar3;
	MODEL **ppMVar4;

	puVar1 = (ushort *)(lump_ptr + num_models_in_pack * 2);
	Low2HighDetailTable = (ushort *)lump_ptr;
	Low2LowerDetailTable = puVar1;
	if (0 < num_models_in_pack) {
		ppMVar3 = pLodModels1536;
		ppMVar4 = modelpointers1536;
		iVar2 = num_models_in_pack;
		do {
			if (*puVar1 == 0xffff) {
				*ppMVar3 = *ppMVar4;
			}
			else {
				*ppMVar3 = modelpointers1536[*puVar1];
			}
			ppMVar3 = ppMVar3 + 1;
			ppMVar4 = ppMVar4 + 1;
			iVar2 = iVar2 + -1;
			puVar1 = puVar1 + 1;
		} while (iVar2 != 0);
	}
	return;
	*/
}





