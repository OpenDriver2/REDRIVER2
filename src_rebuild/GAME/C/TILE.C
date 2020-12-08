#include "DRIVER2.H"
#include "TILE.H"
#include "MODELS.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "DRAW.H"
#include "TEXTURE.H"
#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"

// decompiled code
// original method signature: 
// void /*$ra*/ Tile1x1(MODEL *model /*$a0*/)
 // line 79, offset 0x00041b10
	/* begin block 1 */
		// Start line: 80
		// Start offset: 0x00041B10
		// Variables:
	// 		int i; // $t3
	// 		unsigned char *polys; // $t0
	// 		SVECTOR *verts; // $t1
	// 		POLY_FT4 *prims; // $a2
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

// [D] [T] [A]
void Tile1x1(MODEL *model)
{
	int opz;
	int Z;
	int ofse;
	PL_POLYFT4* polys;
	int i;
	u_char ptype;
	POLY_FT4* prims;
	SVECTOR* srcVerts;

	srcVerts = (SVECTOR*)model->vertices;
	polys = (PL_POLYFT4*)model->poly_block;

	// grass should be under pavements and other things
	if ((model->shape_flags & 0x80) || (model->flags2 & 0x4000))
		ofse = 229;
	else
		ofse = 133;

	i = model->num_polys;
	while (i > 0)
	{
		// iterate through polygons
		// with skipping
		ptype = polys->id & 0x1f;

		// perform transform
		gte_ldv3(&srcVerts[polys->v0], &srcVerts[polys->v1], &srcVerts[polys->v3]);
		gte_rtpt();

		// get culling value
		gte_nclip();
		gte_stopz(&opz);

		if (opz > 0)
		{
			prims = (POLY_FT4*)plotContext.primptr;

			setPolyFT4(prims);
			*(ulong*)&prims->r0 = plotContext.colour;

			// retrieve first three verts
			gte_stsxy3(&prims->x0, &prims->x1, &prims->x2);

			// translate 4th vert and get OT Z value
			gte_ldv0(&srcVerts[polys->v2]);
			gte_rtps();
			gte_avsz4();

			gte_stotz(&Z);

			gte_stsxy(&prims->x3);

			prims->tpage = (*plotContext.ptexture_pages)[polys->texture_set];
			prims->clut = (*plotContext.ptexture_cluts)[polys->texture_set][polys->texture_id];

			*(ushort*)&prims->u0 = *(ushort*)&polys->uv0;
			*(ushort*)&prims->u1 = *(ushort*)&polys->uv1;
			*(ushort*)&prims->u2 = *(ushort*)&polys->uv3;
			*(ushort*)&prims->u3 = *(ushort*)&polys->uv2;

			addPrim(plotContext.ot + (Z >> 1) + ofse, prims);

			plotContext.primptr += sizeof(POLY_FT4);
		}

		polys = (PL_POLYFT4*)((char*)polys + plotContext.polySizes[ptype]);
		i--;
	}

	// done
	plotContext.current->primptr = plotContext.primptr;
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
		// 		PACKED_CELL_OBJECT **tilePointers; // $s3
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
				// 		PACKED_CELL_OBJECT *ppco; // $a0
				/* end block 1.2.1.1 */
				// End offset: 0x00041FB8
				// End Line: 241

				/* begin block 1.2.1.2 */
					// Start line: 270
					// Start offset: 0x0004202C
					// Variables:
				// 		MODEL *model; // $a0
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

// [D] [T]
void DrawTILES(PACKED_CELL_OBJECT** tiles, int tile_amount)
{
	PACKED_CELL_OBJECT *ppco;
	int yang;
	int model_number;
	PACKED_CELL_OBJECT **tilePointers;
	int previous_matrix;
	int Z;

	if (gTimeOfDay > -1) 
	{
		if (gTimeOfDay < 3)
		{
			plotContext.colour = combointensity & 0xffffffU | 0x2c000000;
		}
		else if (gTimeOfDay == 3) 
		{
			plotContext.colour = ((combointensity >> 16 & 0xFF) / 3) << 16 | ((combointensity >> 8 & 0xFF) / 3) << 8 | (combointensity & 0xFF) / 3 | 0x2c000000U;
		}
	}

	previous_matrix = -1;

	if (gWeather - 1U < 2)
	{
		ulong col;
		col = plotContext.colour >> 2 & 0x3f;
		plotContext.colour = col * 0x30000 | col * 0x300 | col * 3 | 0x2c000000;
	}

	tile_amount--;

	plotContext.ot = current->ot;
	plotContext.current = current;
	plotContext.primptr = current->primptr;
	plotContext.ptexture_pages = (ushort(*)[128])texture_pages;
	plotContext.ptexture_cluts = (ushort(*)[128][32])texture_cluts;
	plotContext.lastTexInfo = 0x18273472;
	plotContext.flags = 0;
	plotContext.polySizes = PolySizes;

	tilePointers = (PACKED_CELL_OBJECT **)tiles;

	while (tile_amount != -1) 
	{
		ppco = *tilePointers;
		
		plotContext.f4colourTable[6] = ppco->pos.vx;
		plotContext.f4colourTable[7] = (ppco->pos.vy << 0x10) >> 0x11;
		plotContext.f4colourTable[8] = ppco->pos.vz;
	
		tilePointers++;
	
		yang = ppco->value & 0x3f;
		model_number = (ppco->value >> 6) | (ppco->pos.vy & 1) << 10;

		if (previous_matrix == yang)
		{
			Z = Apply_InvCameraMatrixSetTrans((VECTOR_NOPAD *)(plotContext.f4colourTable + 6));
		}
		else
		{
			Z = Apply_InvCameraMatrixAndSetMatrix((VECTOR_NOPAD *)(plotContext.f4colourTable + 6), &CompoundMatrix[yang]);
			previous_matrix = yang;
		}

		if (Z <= 7000)
		{
			if (Low2HighDetailTable[model_number] != 0xffff)
				model_number = Low2HighDetailTable[model_number];

			if (Z < 2000)
				TileNxN(modelpointers[model_number], 4, 75);
			else 
				TileNxN(modelpointers[model_number], 2, 35);
		}
		else
		{
			if (Z > 9000) 
			{
				if (Low2LowerDetailTable[model_number] != 0xffff)
					model_number = Low2LowerDetailTable[model_number];
			}
			
			Tile1x1(modelpointers[model_number]);
		}

		tile_amount--;
	}
	current->primptr = plotContext.primptr;
}



// decompiled code
// original method signature: 
// void /*$ra*/ makeMesh(MVERTEX (*VSP)[5][5] /*$t4*/, int m /*$t2*/, int n /*$a2*/)
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

// [A] custom implemented function
void makeMesh(MVERTEX(*VSP)[5][5], int m, int n)
{

	/* vertices by index in quad:
		3---------2
		|         |
		|         |
		|         |
		0---------1
	*/

	// 0 3 2 1

	// do subdivision
	MVERTEX v1, v2, v3, v4;
	MVERTEX e1, e2, e3, e4, e5;
	MVERTEX p1, p2, p3, p4, p5;

	if (n < 2)
		return;

	v1 = (*VSP)[0][0];
	v2 = (*VSP)[0][1];
	v3 = (*VSP)[0][3];
	v4 = (*VSP)[0][2];

	VecSubtract(&e1, &v2, &v1); // plane[1] - plane[0];
	e1.uv.u0 = (v2.uv.u0 - v1.uv.u0) / 2;
	e1.uv.v0 = (v2.uv.v0 - v1.uv.v0) / 2;

	VecSubtract(&e2, &v3, &v4); // plane[2] - plane[3];
	e2.uv.u0 = (v3.uv.u0 - v4.uv.u0) / 2;
	e2.uv.v0 = (v3.uv.v0 - v4.uv.v0) / 2;

	VecSubtract(&e3, &v4, &v1); // plane[3] - plane[0];
	e3.uv.u0 = (v4.uv.u0 - v1.uv.u0) / 2;
	e3.uv.v0 = (v4.uv.v0 - v1.uv.v0) / 2;

	VecSubtract(&e4, &v3, &v2); // plane[2] - plane[1];
	e4.uv.u0 = (v3.uv.u0 - v2.uv.u0) / 2;
	e4.uv.v0 = (v3.uv.v0 - v2.uv.v0) / 2;

	//-----------

	// half them all
	SetVec(&e1, e1.vx / 2, e1.vy / 2, e1.vz / 2);

	SetVec(&e2, e2.vx / 2, e2.vy / 2, e2.vz / 2);

	SetVec(&e3, e3.vx / 2, e3.vy / 2, e3.vz / 2);

	SetVec(&e4, e4.vx / 2, e4.vy / 2, e4.vz / 2);

	//-----------

	VecAdd(&p1, &e1, &v1); // e1 * 0.5f + plane[0];
	p1.uv.u0 = e1.uv.u0 + v1.uv.u0;
	p1.uv.v0 = e1.uv.v0 + v1.uv.v0;

	VecAdd(&p2, &e2, &v4); // e2 * 0.5f + plane[3];
	p2.uv.u0 = e2.uv.u0 + v4.uv.u0;
	p2.uv.v0 = e2.uv.v0 + v4.uv.v0;

	VecAdd(&p3, &e3, &v1); // e3 * 0.5f + plane[0];
	p3.uv.u0 = e3.uv.u0 + v1.uv.u0;
	p3.uv.v0 = e3.uv.v0 + v1.uv.v0;

	VecAdd(&p4, &e4, &v2); // e4 * 0.5f + plane[1];
	p4.uv.u0 = e4.uv.u0 + v2.uv.u0;
	p4.uv.v0 = e4.uv.v0 + v2.uv.v0;

	//-----------

	VecSubtract(&e5, &p2, &p1); // p2 - p1;
	e5.uv.u0 = (p2.uv.u0 - p1.uv.u0) / 2;
	e5.uv.v0 = (p2.uv.v0 - p1.uv.v0) / 2;

	SetVec(&e5, e5.vx / 2, e5.vy / 2, e5.vz / 2);


	VecAdd(&p5, &e5, &p1); // e5 * 0.5f + p1;
	p5.uv.u0 = e5.uv.u0 + p1.uv.u0;
	p5.uv.v0 = e5.uv.v0 + p1.uv.v0;

	//-----------

	(*VSP)[0][0] = v1; // { plane[0], p1, p5, p3 },
	(*VSP)[0][1] = p1;
	(*VSP)[0][2] = p3;
	(*VSP)[0][3] = p5;

	(*VSP)[1][0] = p1; // { p1, plane[1], p4, p5 },
	(*VSP)[1][1] = v2;
	(*VSP)[1][2] = p5;
	(*VSP)[1][3] = p4;

	(*VSP)[2][0] = p5; // { p5, p4, plane[2], p2 },
	(*VSP)[2][1] = p4;
	(*VSP)[2][2] = p2;
	(*VSP)[2][3] = v3;

	(*VSP)[3][0] = p3; // { p3, p5, p2, plane[3] }
	(*VSP)[3][1] = p5;
	(*VSP)[3][2] = v4;
	(*VSP)[3][3] = p2;
}



// decompiled code
// original method signature: 
// void /*$ra*/ drawMesh(MVERTEX (*VSP)[5][5] /*$s2*/, int m /*$s3*/, int n /*$s1*/, plotContext *pc /*$a3*/)
 // line 359, offset 0x00042650
	/* begin block 1 */
		// Start line: 360
		// Start offset: 0x00042650
		// Variables:
	// 		int j; // $t6
	// 		int k; // $t9
	// 		POLY_FT4 *prims; // $t1

		/* begin block 1.1 */
			// Start line: 370
			// Start offset: 0x000426B8
			// Variables:
		// 		int Z1; // stack offset -24
		// 		int Z2; // stack offset -20
		// 		MVERTEX (*VST)[5][5]; // $t2
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

// [A] custom implemented function
void drawMesh(MVERTEX(*VSP)[5][5], int m, int n, _pct *pc)
{
	POLY_FT4* prim;
	int z;
	int opz;

	prim = (POLY_FT4*)pc->primptr;

	int numPolys = 4;

	if (n < 2)
		numPolys = 1;

	for (int index = 0; index < numPolys; index++)
	{
		setPolyFT4(prim);
		*(ulong*)&prim->r0 = pc->colour; // FIXME: semiTransparency support

		// test
		gte_ldv3(&(*VSP)[index][0], &(*VSP)[index][1], &(*VSP)[index][2]);
		gte_rtpt();
		gte_nclip();
		gte_stopz(&opz);

		gte_avsz3();
		
		gte_stotz(&z);

		if (pc->flags & (PLOT_NO_CULL | PLOT_INV_CULL))
		{
			if (pc->flags & PLOT_NO_CULL)
				opz = 1;		// no culling
			else // PLOT_FRONT_CULL
				opz = -opz;		// front face
		}

		if (opz > 0 && z > 5)
		{
			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);

			gte_ldv0(&(*VSP)[index][3]);
			gte_rtps();


			gte_stsxy(&prim->x3);

			*(ushort*)&prim->u0 = (*VSP)[index][0].uv.val;
			*(ushort*)&prim->u1 = (*VSP)[index][1].uv.val;
			*(ushort*)&prim->u2 = (*VSP)[index][2].uv.val;
			*(ushort*)&prim->u3 = (*VSP)[index][3].uv.val;

			prim->clut = pc->clut >> 0x10;
			prim->tpage = pc->tpage >> 0x10;

			addPrim(pc->ot + (z >> 1), prim);

			prim++;
		}
	}

	pc->primptr = (char*)prim;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SubdivNxM(char *polys /*$t4*/, unsigned long n /*$s1*/, unsigned long m /*$s0*/, int ofse /*$s2*/)
 // line 489, offset 0x00042aec
	/* begin block 1 */
		// Start line: 490
		// Start offset: 0x00042AEC
		// Variables:
	// 		MVERTEX (*VSP)[5][5]; // $t3
	// 		plotContext *pc; // $t2

		/* begin block 1.1 */
			// Start line: 490
			// Start offset: 0x00042AEC
			// Variables:
		// 		unsigned long indices; // $a0
		// 		SVECTOR *v0; // $t1
		// 		SVECTOR *v1; // $a1
		// 		SVECTOR *v2; // $t0
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

// [A] custom implemented function
void SubdivNxM(char *polys, int n, int m, int ofse)
{
	MVERTEX subdivVerts[5][5];

	SVECTOR* verts = plotContext.verts;

	POLYFT4* pft4 = (POLYFT4*)polys;
	
	plotContext.clut = (uint)(*plotContext.ptexture_cluts)[pft4->texture_set][pft4->texture_id] << 0x10;
	plotContext.tpage = (uint)(*plotContext.ptexture_pages)[pft4->texture_set] << 0x10;

	copyVector(&subdivVerts[0][0], &verts[pft4->v0]);
	subdivVerts[0][0].uv.val = *(ushort*)&pft4->uv0;

	copyVector(&subdivVerts[0][1], &verts[pft4->v1]);
	subdivVerts[0][1].uv.val = *(ushort*)&pft4->uv1;

	copyVector(&subdivVerts[0][2], &verts[pft4->v3]);
	subdivVerts[0][2].uv.val = *(ushort*)&pft4->uv3;

	copyVector(&subdivVerts[0][3], &verts[pft4->v2]);
	subdivVerts[0][3].uv.val = *(ushort*)&pft4->uv2;

	plotContext.ot += ofse;

	makeMesh((MVERTEX(*)[5][5])subdivVerts, m, n);
	drawMesh((MVERTEX(*)[5][5])subdivVerts, m, n, &plotContext);

	plotContext.ot -= ofse;
}



// decompiled code
// original method signature: 
// void /*$ra*/ TileNxN(MODEL *model /*$s4*/, int levels /*$s2*/, int Dofse /*$s6*/)
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

// [D] [T]
void TileNxN(MODEL *model, int levels, int Dofse)
{
	uint ttype;
	unsigned char *polys;
	uint tileTypes;
	int i;
	int ofse;

	ttype = 0;

	polys = (unsigned char *)model->poly_block;
	plotContext.verts = (SVECTOR *)model->vertices;

	// tile types comes right after model header it seems
	tileTypes = *(uint *)(model + 1) >> 2;

	// grass should be under pavements and other things
	if((model->shape_flags & 0x80) || (model->flags2 & 0x4000))
		ofse = 229;
	else
		ofse = 133;

	i = 0;

	while (i < model->num_polys)
	{
		switch (ttype) 
		{
			case 0:
			case 1:
				SubdivNxM((char *)polys, levels, levels, ofse);
				break;
			case 3:
				SubdivNxM((char *)polys, levels, 1, Dofse);
				break;
			case 4:
				SubdivNxM((char *)polys, levels, levels, 133);
				break;
		}

		ttype = tileTypes & 7;
		tileTypes >>= 3;

		polys += plotContext.polySizes[*polys];
		i++;
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
	// Driver 1 leftover...
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

// [D] [T]
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





