#include "driver2.h"
#include "tile.h"
#include "models.h"
#include "system.h"
#include "mission.h"
#include "draw.h"
#include "texture.h"

#include "ASM/rndrasm.h"

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
	if ((model->shape_flags & SHAPE_FLAG_WATER) || (model->flags2 & MODEL_FLAG_GRASS))
		ofse = 229;
	else
		ofse = 133;

#ifdef USE_PGXP
	PGXP_SetZOffsetScale(0.0f, ofse > 200 ? 1.005f : 0.995f);
#endif

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

#ifdef USE_PGXP
	PGXP_SetZOffsetScale(0.0f, 1.0f);
#endif

	// done
	plotContext.current->primptr = plotContext.primptr;
}

// [D] [T]
void DrawTILES(PACKED_CELL_OBJECT** tiles, int tile_amount)
{
	MODEL* pModel;
	PACKED_CELL_OBJECT *ppco;
	int yang, dofse;
	int model_number;
	PACKED_CELL_OBJECT **tilePointers;
	int previous_matrix;
	int Z;

	if (gTimeOfDay > -1) 
	{
		if (gTimeOfDay < 3)
		{
			plotContext.colour = combointensity & 0xffffffU | 0x2C000000;
		}
		else if (gTimeOfDay == 3) 
		{
			plotContext.colour = ((combointensity >> 16 & 255) / 3) << 16 | ((combointensity >> 8 & 255) / 3) << 8 | (combointensity & 255) / 3 | 0x2C000000U;
		}
	}

	previous_matrix = -1;

	if (gWeather - 1U < 2)
	{
		u_int col;
		col = plotContext.colour >> 2 & 0x3f;
		plotContext.colour = col * 0x30000 | col * 0x300 | col * 3 | 0x2C000000;
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

		if (Z <= DRAW_LOD_DIST_HIGH)
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
			pModel = Z > DRAW_LOD_DIST_LOW ? pLodModels[model_number] : modelpointers[model_number];
			
			Tile1x1(pModel);
		}

		tile_amount--;
	}
	current->primptr = plotContext.primptr;
}

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

#if 0
	// no need to subdivide!
	if (g_pgxpZBuffer)
		return;
#endif

	v1 = (*VSP)[0][0];
	v2 = (*VSP)[0][1];
	v3 = (*VSP)[0][3];
	v4 = (*VSP)[0][2];

	VecSubtract(&e1, &v2, &v1); // plane[1] - plane[0];
	e1.uv.s.u0 = (v2.uv.s.u0 - v1.uv.s.u0) / 2;
	e1.uv.s.v0 = (v2.uv.s.v0 - v1.uv.s.v0) / 2;

	VecSubtract(&e2, &v3, &v4); // plane[2] - plane[3];
	e2.uv.s.u0 = (v3.uv.s.u0 - v4.uv.s.u0) / 2;
	e2.uv.s.v0 = (v3.uv.s.v0 - v4.uv.s.v0) / 2;

	VecSubtract(&e3, &v4, &v1); // plane[3] - plane[0];
	e3.uv.s.u0 = (v4.uv.s.u0 - v1.uv.s.u0) / 2;
	e3.uv.s.v0 = (v4.uv.s.v0 - v1.uv.s.v0) / 2;

	VecSubtract(&e4, &v3, &v2); // plane[2] - plane[1];
	e4.uv.s.u0 = (v3.uv.s.u0 - v2.uv.s.u0) / 2;
	e4.uv.s.v0 = (v3.uv.s.v0 - v2.uv.s.v0) / 2;

	//-----------

	// half them all
	SetVec(&e1, e1.vx / 2, e1.vy / 2, e1.vz / 2);

	SetVec(&e2, e2.vx / 2, e2.vy / 2, e2.vz / 2);

	SetVec(&e3, e3.vx / 2, e3.vy / 2, e3.vz / 2);

	SetVec(&e4, e4.vx / 2, e4.vy / 2, e4.vz / 2);

	//-----------

	VecAdd(&p1, &e1, &v1); // e1 * 0.5f + plane[0];
	p1.uv.s.u0 = e1.uv.s.u0 + v1.uv.s.u0;
	p1.uv.s.v0 = e1.uv.s.v0 + v1.uv.s.v0;

	VecAdd(&p2, &e2, &v4); // e2 * 0.5f + plane[3];
	p2.uv.s.u0 = e2.uv.s.u0 + v4.uv.s.u0;
	p2.uv.s.v0 = e2.uv.s.v0 + v4.uv.s.v0;

	VecAdd(&p3, &e3, &v1); // e3 * 0.5f + plane[0];
	p3.uv.s.u0 = e3.uv.s.u0 + v1.uv.s.u0;
	p3.uv.s.v0 = e3.uv.s.v0 + v1.uv.s.v0;

	VecAdd(&p4, &e4, &v2); // e4 * 0.5f + plane[1];
	p4.uv.s.u0 = e4.uv.s.u0 + v2.uv.s.u0;
	p4.uv.s.v0 = e4.uv.s.v0 + v2.uv.s.v0;

	//-----------

	VecSubtract(&e5, &p2, &p1); // p2 - p1;
	e5.uv.s.u0 = (p2.uv.s.u0 - p1.uv.s.u0) / 2;
	e5.uv.s.v0 = (p2.uv.s.v0 - p1.uv.s.v0) / 2;

	SetVec(&e5, e5.vx / 2, e5.vy / 2, e5.vz / 2);


	VecAdd(&p5, &e5, &p1); // e5 * 0.5f + p1;
	p5.uv.s.u0 = e5.uv.s.u0 + p1.uv.s.u0;
	p5.uv.s.v0 = e5.uv.s.v0 + p1.uv.s.v0;

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

#if 0
	// no need to subdivide!
	if (g_pgxpZBuffer)
		numPolys = 1;
#endif

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

// [A] custom implemented function
void SubdivNxM(char *polys, int n, int m, int ofse)
{
	MVERTEX subdivVerts[5][5];

	SVECTOR* verts = plotContext.verts;

	POLYFT4* pft4 = (POLYFT4*)polys;
	
	plotContext.clut = (u_int)(*plotContext.ptexture_cluts)[pft4->texture_set][pft4->texture_id] << 0x10;
	plotContext.tpage = (u_int)(*plotContext.ptexture_pages)[pft4->texture_set] << 0x10;

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

// [D] [T]
void TileNxN(MODEL *model, int levels, int Dofse)
{
	u_int ttype;
	u_char *polys;
	u_int tileTypes;
	int i;
	int ofse;

	ttype = 0;

	polys = (u_char *)model->poly_block;
	plotContext.verts = (SVECTOR *)model->vertices;

	// tile types comes right after model header it seems
	tileTypes = *(u_int *)(model + 1) >> 2;

	// grass should be under pavements and other things
	if((model->shape_flags & SHAPE_FLAG_WATER) || (model->flags2 & MODEL_FLAG_GRASS))
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
#ifdef USE_PGXP
				PGXP_SetZOffsetScale(0.0f, ofse > 200 ? 1.008f : 0.995f);
#endif
				SubdivNxM((char *)polys, levels, levels, ofse);
				break;
			case 3:
#ifdef USE_PGXP
				PGXP_SetZOffsetScale(0.0f, ofse < 40 ? 1.0f : 0.991f);
#endif
				SubdivNxM((char *)polys, levels, 1, Dofse);
				break;
			case 4:
#ifdef USE_PGXP
				PGXP_SetZOffsetScale(0.0f, 1.0f);
#endif
				SubdivNxM((char *)polys, levels, levels, 133);
				break;
		}

		ttype = tileTypes & 7;
		tileTypes >>= 3;

		polys += plotContext.polySizes[*polys];
		i++;
	}

#ifdef USE_PGXP
	PGXP_SetZOffsetScale(0.0f, 1.0f);
#endif
}

void ProcessSubDivisionLump(char *lump_ptr, int lump_size)
{
	// Driver 1 leftover...
	UNIMPLEMENTED();
	/*
	SubDivisionArrays = lump_ptr;
	return;*/
}

// [D] [T]
void ProcessLowDetailTable(char *lump_ptr, int lump_size)
{
	int i;

	Low2HighDetailTable = (ushort *)lump_ptr;
	Low2LowerDetailTable = Low2HighDetailTable + num_models_in_pack;

	for (i = 0; i < num_models_in_pack; i++)
	{
		if (Low2LowerDetailTable[i] != 0xFFFF)
			pLodModels[i] = modelpointers[Low2LowerDetailTable[i]];
		else
			pLodModels[i] = modelpointers[i];
	}
}





