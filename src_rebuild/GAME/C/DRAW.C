#include "DRIVER2.H"

#include "INLINE_C.H"

#include "DRAW.H"
#include "MAIN.H"
#include "MAP.H"
#include "MODELS.H"
#include "SYSTEM.H"
#include "CAMERA.H"
#include "MISSION.H"
#include "CELL.H"
#include "TILE.H"
#include "OBJANIM.H"
#include "TEXTURE.H"
#include "CARS.H"
#include "DEBRIS.H"
#include "../ASM/ASMTEST.H"

#include <string.h>

#include "PRES.H"

MATRIX aspect =
{
	{
		{ 6553, 0, 0 },
		{ 0, 4096, 0 },
		{ 0, 0, 4096 }
	},
	{ 0, 0, 0 }
};

MATRIX identity =
{
	{
		{ 4096, 0, 0 },
		{ 0, 4096, 0 },
		{ 0, 0, 4096 }
	},
	{ 0, 0, 0 }
};

int PolySizes[56] = {
	8,  12, 16, 24,
	20, 20, 28, 32,
	8,  12, 16, 16,
	0,  0,  0,  0,
	12, 12, 12, 16,
	20, 20, 24, 24,
	0,  0,  0,  0,
	0,  0,  0,  0,
	8,  12, 16, 24,
	20, 24, 28, 32,
	0,  0,  0,  0,
	0,  0,  0,  0,
	12, 12, 12, 16,
	20, 20, 24, 24,
};

SVECTOR day_vectors[4] =
{
  { 62404, 2520, 783, 0 },
  { 62404, 2520, 783, 0 },
  { 63172, 2364, 2364, 0 },
  { 62404, 2520, 783, 0 }
};

SVECTOR night_vectors[4] =
{
  { 3132, 2520, 783, 0 },
  { 3132, 2520, 783, 0 },
  { 63172, 2364, 63172, 0 },
  { 3132, 2520, 783, 0 }
};

SVECTOR day_colours[4] =
{
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 }
};

SVECTOR night_colours[4] =
{
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 }
};

void* model_object_ptrs[MAX_DRAWN_BUILDINGS];
void* model_tile_ptrs[MAX_DRAWN_TILES];
void* anim_obj_buffer[MAX_DRAWN_ANIMATING];
void* spriteList[MAX_DRAWN_SPRITES];

unsigned long planeColours[8];

MATRIX inv_camera_matrix;
MATRIX face_camera;
MATRIX2 CompoundMatrix[64];

uint farClip2Player = 36000;

int goFaster = 0;	// [A] was 1
int fasterToggle = 0;

//int current_object_computed_value = 0;

int combointensity;

#ifndef PSX
OUT_CELL_FILE_HEADER cell_header;
#endif // PSX

char CurrentPVS[444]; // 20*20+4
MATRIX2 matrixtable[64];
int setupYet = 0;

int gDrawDistance = 441;

// offset: 0x1f800020
_pct plotContext;

// decompiled code
// original method signature: 
// void /*$ra*/ addSubdivSpriteShadow(POLYFT4LIT *src /*$t3*/, SVECTOR *verts /*$t2*/, int z /*$a2*/)
 // line 651, offset 0x0003ed7c
	/* begin block 1 */
		// Start line: 652
		// Start offset: 0x0003ED7C
		// Variables:
	// 		unsigned long word0; // $a0
	// 		unsigned long vidx; // $t1
	// 		_pct *pc; // $t0
	// 		int w; // $s0
	/* end block 1 */
	// End offset: 0x0003EF64
	// End Line: 670

	/* begin block 2 */
		// Start line: 1302
	/* end block 2 */
	// End Line: 1303

	/* begin block 3 */
		// Start line: 1305
	/* end block 3 */
	// End Line: 1306

// [D] [T] [A]
void addSubdivSpriteShadow(POLYFT4* src, SVECTOR* verts, int z)
{
	int m;

	m = 4;

	MVERTEX subdiVerts[5][5];

	plotContext.colour = 0x2e000000;
	plotContext.flags = 0x2;
	plotContext.clut = texture_cluts[src->texture_set][src->texture_id] << 0x10;
	plotContext.tpage = texture_pages[src->texture_set] << 0x10;

	if (z > 3200)
		m = 1; //2;

	plotContext.ot += 28;

	copyVector(&subdiVerts[0][0], &verts[src->v0]);
	subdiVerts[0][0].uv.val = *(ushort*)&src->uv0;

	copyVector(&subdiVerts[0][1], &verts[src->v1]);
	subdiVerts[0][1].uv.val = *(ushort*)&src->uv1;

	copyVector(&subdiVerts[0][2], &verts[src->v3]);
	subdiVerts[0][2].uv.val = *(ushort*)&src->uv3;

	copyVector(&subdiVerts[0][3], &verts[src->v2]);
	subdiVerts[0][3].uv.val = *(ushort*)&src->uv2;

	makeMesh((MVERTEX(*)[5][5])subdiVerts, m, m);
	drawMesh((MVERTEX(*)[5][5])subdiVerts, m, m, &plotContext);

	plotContext.ot -= 28;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSprites(int numFound /*$a2*/)
 // line 675, offset 0x0003ef64
	/* begin block 1 */
		// Start line: 676
		// Start offset: 0x0003EF64
		// Variables:
	// 		XZPAIR near; // stack offset -80
	// 		PACKED_CELL_OBJECT **list; // stack offset -64
	// 		unsigned long spriteColour; // stack offset -60
	// 		int numShadows; // stack offset -56

		/* begin block 1.1 */
			// Start line: 676
			// Start offset: 0x0003EF64
			// Variables:
		// 		SVECTOR result; // stack offset -72
		// 		unsigned char lightLevel; // $a1
		/* end block 1.1 */
		// End offset: 0x0003F0FC
		// End Line: 716

		/* begin block 1.2 */
			// Start line: 716
			// Start offset: 0x0003F0FC
			// Variables:
		// 		int i; // $t0
		/* end block 1.2 */
		// End offset: 0x0003F174
		// End Line: 729

		/* begin block 1.3 */
			// Start line: 743
			// Start offset: 0x0003F1F0
			// Variables:
		// 		PACKED_CELL_OBJECT *ppco; // $fp
		// 		MODEL *model; // $s4
		// 		int z; // stack offset -52
		// 		int yang; // $a0

			/* begin block 1.3.1 */
				// Start line: 770
				// Start offset: 0x0003F2A8
			/* end block 1.3.1 */
			// End offset: 0x0003F2A8
			// End Line: 770

			/* begin block 1.3.2 */
				// Start line: 776
				// Start offset: 0x0003F2F0
				// Variables:
			// 		POLYFT4LIT *src; // $s0
			// 		SVECTOR *verts; // $s3
			// 		int i; // $s1

				/* begin block 1.3.2.1 */
					// Start line: 781
					// Start offset: 0x0003F338
					// Variables:
				// 		unsigned long vidx; // $a3
				/* end block 1.3.2.1 */
				// End offset: 0x0003F338
				// End Line: 782
			/* end block 1.3.2 */
			// End offset: 0x0003F49C
			// End Line: 794
		/* end block 1.3 */
		// End offset: 0x0003F59C
		// End Line: 807
	/* end block 1 */
	// End offset: 0x0003F5F0
	// End Line: 809

	/* begin block 2 */
		// Start line: 1384
	/* end block 2 */
	// End Line: 1385

	/* begin block 3 */
		// Start line: 1390
	/* end block 3 */
	// End Line: 1391

	/* begin block 4 */
		// Start line: 1401
	/* end block 4 */
	// End Line: 1402

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

MATRIX shadowMatrix;

// [D] [T] [A]
void DrawSprites(PACKED_CELL_OBJECT** sprites, int numFound)
{
	int i;
	int z;
	uint spriteColour;
	uint lightdd;
	unsigned char lightLevel;
	MODEL* model;
	PACKED_CELL_OBJECT* pco;
	PACKED_CELL_OBJECT** list;
	int numShadows;
	int count;

	MVERTEX subdiVerts[5][5];

	lightdd = FIXEDH(camera_matrix.m[2][0] * day_vectors[GameLevel].vx) +
		FIXEDH(camera_matrix.m[2][1] * day_vectors[GameLevel].vy) +
		FIXEDH(camera_matrix.m[2][2] * day_vectors[GameLevel].vz) + 0x1000 * 0xc00;

	lightLevel = (lightdd >> 0x12) + 0x20U & 0xff;

	if (gWeather > 0 && gTimeOfDay == 1)
	{
		lightLevel = (lightLevel * 2 * NightAmbient) >> 8 & 0xff;
	}

	if (gTimeOfDay == 0)
	{
		lightLevel = (lightLevel * 2 * NightAmbient) >> 8;
	}
	else if (gTimeOfDay == 2)
	{
		lightLevel = (lightLevel * 2 * NightAmbient) >> 8;
	}
	else if (gTimeOfDay == 3)
	{
		if (GameLevel == 0)
			lightLevel *= 2;	// [A] level bug - Chicago trees lit wrong
		else
			lightLevel /= 3;
	}

	spriteColour = lightLevel << 0x10 | lightLevel << 8 | 0x2c000000 | lightLevel;

	i = 2;
	do {
		shadowMatrix.m[i][0] = inv_camera_matrix.m[i][2];
		shadowMatrix.m[i][1] = -inv_camera_matrix.m[i][0];
		shadowMatrix.m[i][2] = inv_camera_matrix.m[i][0];
		i--;
	} while (i >= 0);


	plotContext.primptr = current->primptr;
	plotContext.ptexture_pages = (ushort(*)[128])texture_pages;
	plotContext.ptexture_cluts = (ushort(*)[128][32])texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.ot = current->ot;

	list = sprites;

	plotContext.colour = spriteColour;
	plotContext.current = current;

	numShadows = 0;
	count = numFound - 1;

	while (count != -1)
	{
		pco = *list;
		list++;

		int modelnumber = (pco->value >> 6) | (pco->pos.vy & 1) << 10;

		model = modelpointers[modelnumber];
		plotContext.colour = spriteColour;

		if ((pco->value & 0x3f) == 63 || (gTimeOfDay == 3 && modelnumber == 945)) // [A] Vegas tree fix
			plotContext.colour = 0x2c808080;

		plotContext.scribble[0] = pco->pos.vx;
		plotContext.scribble[1] = (pco->pos.vy << 0x10) >> 0x11;
		plotContext.scribble[2] = pco->pos.vz;

		z = Apply_InvCameraMatrixAndSetMatrix((VECTOR_NOPAD*)plotContext.scribble, (MATRIX2*)&face_camera);

		if (z < 1000)
		{
			POLYFT4* src;
			SVECTOR* verts;
			int numPolys;

			numPolys = (uint)model->num_polys;
			src = (POLYFT4*)model->poly_block;
			verts = (SVECTOR*)model->vertices;

			plotContext.flags |= 4;

			while (numPolys--, numPolys >= 0)
			{
				plotContext.clut = texture_cluts[src->texture_set][src->texture_id] << 0x10;
				plotContext.tpage = texture_pages[src->texture_set] << 0x10;

				copyVector(&subdiVerts[0][0], &verts[src->v0]);
				subdiVerts[0][0].uv.val = *(ushort*)&src->uv0;

				copyVector(&subdiVerts[0][1], &verts[src->v1]);
				subdiVerts[0][1].uv.val = *(ushort*)&src->uv1;

				copyVector(&subdiVerts[0][2], &verts[src->v3]);
				subdiVerts[0][2].uv.val = *(ushort*)&src->uv3;

				copyVector(&subdiVerts[0][3], &verts[src->v2]);
				subdiVerts[0][3].uv.val = *(ushort*)&src->uv2;

				makeMesh((MVERTEX(*)[5][5])subdiVerts, 4, 4);
				drawMesh((MVERTEX(*)[5][5])subdiVerts, 4, 4, &plotContext);

				src++;
			}

			plotContext.flags &= ~4;
		}
		else
		{
			plotContext.ot -= 133;

			Tile1x1(model);

			plotContext.ot += 133;
		}

		count--;

		if (wetness == 0 && gTimeOfDay != 3 && (pco->value & 0x20) == 0 && z < 7000 && numShadows < 40)
		{
			gte_SetRotMatrix(&shadowMatrix);

			addSubdivSpriteShadow((POLYFT4*)model->poly_block, (SVECTOR*)model->vertices, z);

			if (model->num_polys == 2)
				addSubdivSpriteShadow((POLYFT4*)(model->poly_block + sizeof(POLYFT4)), (SVECTOR*)model->vertices, z);

			gte_SetRotMatrix(&face_camera);

			numShadows++;
		}
	}
	current->primptr = plotContext.primptr;
}

// decompiled code
// original method signature: 
// int /*$ra*/ DrawAllBuildings(unsigned long *objects /*$t3*/, int num_buildings /*$s5*/, DB *disp /*$a2*/)
// line 2053, offset 0x000411f4
/* begin block 1 */
// Start line: 2054
// Start offset: 0x000411F4
// Variables:
// 		int i; // $s3
// 		int model_number; // $v0
// 		int prev_mat; // $s4
// 		MODEL *model; // $a0
// 		CELL_OBJECT *building; // $s0

/* begin block 1.1 */
// Start line: 2091
// Start offset: 0x0004132C
// Variables:
// 		int spacefree; // $a0

/* begin block 1.1.1 */
// Start line: 2134
// Start offset: 0x0004135C
/* end block 1.1.1 */
// End offset: 0x00041364
// End Line: 2135

/* begin block 1.1.2 */
// Start line: 2138
// Start offset: 0x00041364
// Variables:
// 		int zBias; // $v0
// 		unsigned long *savedOT; // $s1
/* end block 1.1.2 */
// End offset: 0x00041398
// End Line: 2150
/* end block 1.1 */
// End offset: 0x00041398
// End Line: 2150
/* end block 1 */
// End offset: 0x0004143C
// End Line: 2179

/* begin block 2 */
// Start line: 5011
/* end block 2 */
// End Line: 5012

/* begin block 3 */
// Start line: 5025
/* end block 3 */
// End Line: 5026

// [D] [T]
int DrawAllBuildings(CELL_OBJECT** objects, int num_buildings)
{
	int mat;
	int zbias;
	int drawlimit;
	MODEL* model;
	OTTYPE* ot;
	CELL_OBJECT* cop;
	int i;
	int prev_mat;

	prev_mat = -1;

	for (i = 0; i < 8; i++)
	{
		plotContext.f4colourTable[i * 4 + 0] = planeColours[i] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 1] = planeColours[0] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 2] = planeColours[5] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 3] = planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	plotContext.current = current;
	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = 0;
	plotContext.primptr = plotContext.current->primptr;

	ot = plotContext.current->ot + 8;

	i = 0;

	while (i < num_buildings)
	{
		cop = (CELL_OBJECT*)*objects;
		mat = cop->yang;

		if (prev_mat == mat)
		{
			Apply_InvCameraMatrixSetTrans(&cop->pos);
		}
		else
		{
			Apply_InvCameraMatrixAndSetMatrix(&cop->pos, &CompoundMatrix[mat]);
			prev_mat = mat;
		}

		model = modelpointers[cop->type];

		zbias = model->zBias - 64;

		if (zbias < 0)
			zbias = 0;

		plotContext.ot = ot + zbias * 4;
		PlotBuildingModelSubdivNxN(model, cop->yang, &plotContext, 1);

		drawlimit = (int)current->primptr - (int)current->primtab;

		if (PRIMTAB_SIZE - drawlimit < 60000)
			break;

		i++;
		objects++;
	}

	// advance primitive buffer
	current->primptr = plotContext.primptr;

	return 0;
}

// decompiled code
// original method signature: 
// void /*$ra*/ DrawMapPSX(int *comp_val /*$t1*/)
 // line 883, offset 0x0003f6b0
	/* begin block 1 */
		// Start line: 884
		// Start offset: 0x0003F6B0
		// Variables:
	// 		CELL_ITERATOR ci; // stack offset -184
	// 		PACKED_CELL_OBJECT *ppco; // $s0
	// 		int i; // $s1
	// 		int dir; // $s7
	// 		int cellxpos; // $a0
	// 		int cellzpos; // $a1
	// 		int hloop; // $s4
	// 		int vloop; // $s5
	// 		int camx; // stack offset -112
	// 		int camz; // stack offset -108
	// 		char *PVS_ptr; // stack offset -104
	// 		int tiles_found; // stack offset -100
	// 		int other_models_found; // stack offset -96
	// 		int anim_objs_found; // $s6
	// 		MATRIX mRotStore; // stack offset -160
	// 		int rightcos; // stack offset -92
	// 		int rightsin; // stack offset -88
	// 		int leftcos; // stack offset -84
	// 		int leftsin; // stack offset -80
	// 		int backcos; // stack offset -76
	// 		int backsin; // stack offset -72
	// 		int rightPlane; // stack offset -68
	// 		int leftPlane; // stack offset -64
	// 		int backPlane; // $fp
	// 		unsigned int farClipLimit; // stack offset -60

		/* begin block 1.1 */
			// Start line: 967
			// Start offset: 0x0003F964
			// Variables:
		// 		MODEL *model; // $s2

			/* begin block 1.1.1 */
				// Start line: 975
				// Start offset: 0x0003F9B4
				// Variables:
			// 		int model_shape_flags; // $s1

				/* begin block 1.1.1.1 */
					// Start line: 986
					// Start offset: 0x0003FA10
					// Variables:
				// 		CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.1.1 */
						// Start line: 884
						// Start offset: 0x0003FA10
						// Variables:
					// 		PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.1.1.1 */
							// Start line: 884
							// Start offset: 0x0003FA10
							// Variables:
						// 		CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x0003FAB8
						// End Line: 884
					/* end block 1.1.1.1.1 */
					// End offset: 0x0003FAB8
					// End Line: 884
				/* end block 1.1.1.1 */
				// End offset: 0x0003FAC4
				// End Line: 988

				/* begin block 1.1.1.2 */
					// Start line: 993
					// Start offset: 0x0003FAF4
					// Variables:
				// 		CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.2.1 */
						// Start line: 884
						// Start offset: 0x0003FAF4
						// Variables:
					// 		PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.2.1.1 */
							// Start line: 884
							// Start offset: 0x0003FAF4
							// Variables:
						// 		CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.2.1.1 */
						// End offset: 0x0003FB9C
						// End Line: 884
					/* end block 1.1.1.2.1 */
					// End offset: 0x0003FB9C
					// End Line: 884
				/* end block 1.1.1.2 */
				// End offset: 0x0003FB9C
				// End Line: 994

				/* begin block 1.1.1.3 */
					// Start line: 1002
					// Start offset: 0x0003FBE8
					// Variables:
				// 		int yang; // $a1
				/* end block 1.1.1.3 */
				// End offset: 0x0003FCD0
				// End Line: 1010

				/* begin block 1.1.1.4 */
					// Start line: 1018
					// Start offset: 0x0003FD0C
					// Variables:
				// 		CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.4.1 */
						// Start line: 884
						// Start offset: 0x0003FD0C
						// Variables:
					// 		PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.4.1.1 */
							// Start line: 884
							// Start offset: 0x0003FD0C
							// Variables:
						// 		CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.4.1.1 */
						// End offset: 0x0003FDB4
						// End Line: 884
					/* end block 1.1.1.4.1 */
					// End offset: 0x0003FDB4
					// End Line: 884
				/* end block 1.1.1.4 */
				// End offset: 0x0003FE00
				// End Line: 1021

				/* begin block 1.1.1.5 */
					// Start line: 1032
					// Start offset: 0x0003FE34
					// Variables:
				// 		CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.5.1 */
						// Start line: 884
						// Start offset: 0x0003FE34
						// Variables:
					// 		PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.5.1.1 */
							// Start line: 884
							// Start offset: 0x0003FE34
							// Variables:
						// 		CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.5.1.1 */
						// End offset: 0x0003FEDC
						// End Line: 884
					/* end block 1.1.1.5.1 */
					// End offset: 0x0003FEDC
					// End Line: 884
				/* end block 1.1.1.5 */
				// End offset: 0x0003FF34
				// End Line: 1042
			/* end block 1.1.1 */
			// End offset: 0x0003FF34
			// End Line: 1045
		/* end block 1.1 */
		// End offset: 0x0003FF34
		// End Line: 1046

		/* begin block 1.2 */
			// Start line: 1071
			// Start offset: 0x000400CC
		/* end block 1.2 */
		// End offset: 0x000400D4
		// End Line: 1072

		/* begin block 1.3 */
			// Start line: 1081
			// Start offset: 0x000400E4
		/* end block 1.3 */
		// End offset: 0x0004010C
		// End Line: 1083

		/* begin block 1.4 */
			// Start line: 1089
			// Start offset: 0x00040138
			// Variables:
		// 		VECTOR newpos; // stack offset -128
		// 		CELL_OBJECT *cop; // $s0
		/* end block 1.4 */
		// End offset: 0x00040138
		// End Line: 1090
	/* end block 1 */
	// End offset: 0x00040218
	// End Line: 1123

	/* begin block 2 */
		// Start line: 1930
	/* end block 2 */
	// End Line: 1931

	/* begin block 3 */
		// Start line: 1961
	/* end block 3 */
	// End Line: 1962

	/* begin block 4 */
		// Start line: 1980
	/* end block 4 */
	// End Line: 1981

// [D] [T]
void DrawMapPSX(int* comp_val)
{
	int dir;
	PACKED_CELL_OBJECT* ppco;
	int distScale;
	int cellx;
	int cellz;
	CELL_OBJECT* cop;
	MODEL* model;
	int hloop;
	int vloop;
	int backPlane;
	CELL_ITERATOR ci;
	MATRIX mRotStore;
	int cellxpos;
	int cellzpos;
	char* PVS_ptr;

	int tiles_found;
	int other_models_found;
	int sprites_found;
	int anim_objs_found;

	static int treecount = 0;
	static int alleycount = 0;
	
	int rightcos;
	int rightsin;
	int leftcos;
	int leftsin;
	int backcos;
	int backsin;
	int rightPlane;
	int leftPlane;
	int farClipLimit;
	int backAng;
	int leftAng;
	int rightAng;
	int i;
	int current_object_computed_value;

	backPlane = 6144;
	rightPlane = -6144;
	leftPlane = 6144;

	farClipLimit = 80000;

	// setup planes
	rightAng = camera_angle.vy - FrAng & 0xfff;
	leftAng = camera_angle.vy + FrAng & 0xfff;
	backAng = camera_angle.vy + 0x400U & 0xfff;

	rightcos = rcossin_tbl[rightAng * 2 + 1];
	rightsin = rcossin_tbl[rightAng * 2];

	leftcos = rcossin_tbl[leftAng * 2 + 1];
	leftsin = rcossin_tbl[leftAng * 2];
	backcos = rcossin_tbl[backAng * 2 + 1];
	backsin = rcossin_tbl[backAng * 2];

	if (NumPlayers == 2)
	{
		farClipLimit = farClip2Player;
	}

	tiles_found = 0;
	sprites_found = 0;
	goFaster = goFaster ^ fasterToggle;
	current_object_computed_value = *comp_val;
	other_models_found = 0;

	anim_objs_found = 0;

	if (setupYet == 0)
	{
		SetupDrawMapPSX();
		setupYet = 0;
	}

	cellzpos = current_cell_z;
	cellxpos = current_cell_x;

	// clean cell cache
	ClearCopUsage();

	PVS_ptr = CurrentPVS + 220;
	
	vloop = 0;
	hloop = 0;
	dir = 0;

	if (NumPlayers == 2)
		distScale = goFaster & 31 | 1;
	else
		distScale = goFaster & 31;

	i = (gDrawDistance >> distScale) - 1;		// [A]

	// walk through all cells
	while (i >= 0)
	{
		if (ABS(hloop) + ABS(vloop) < 21)
		{
			// clamped vis values
			int vis_h = MIN(MAX(hloop, -9), 10);
			int vis_v = MIN(MAX(vloop, -9), 10);
			
			cellx = cellxpos + hloop;
			cellz = cellzpos + vloop;

			

			if (rightPlane < 0 &&
				leftPlane > 0 &&
				backPlane < farClipLimit &&  // check planes
				cellx > -1 && cellx < cells_across &&							// check cell ranges
				cellz > -1 && cellz < cells_down &&
				PVS_ptr[vis_v * pvs_square + vis_h]) // check PVS table
			{
				ppco = GetFirstPackedCop(cellx, cellz, &ci, 1);
				
				// walk each cell object in cell
				while (ppco != NULL)
				{
					model = modelpointers[(ppco->value >> 6) | ((ppco->pos).vy & 1) << 10];

					if (FrustrumCheck16(ppco, model->bounding_sphere) != -1)
					{
						// sprity type
						if (model->shape_flags & 0x4000)
						{
							if (sprites_found < MAX_DRAWN_SPRITES)
								spriteList[sprites_found++] = ppco;

							if ((model->flags2 & 1) && anim_objs_found < 20)
							{
								cop = UnpackCellObject(ppco, &ci.nearCell);
								anim_obj_buffer[anim_objs_found++] = cop;
							}

							if(model->flags2 & 0x2000)
							{
								if (treecount == 0)
								{
									cop = UnpackCellObject(ppco, &ci.nearCell);

									ground_debris[groundDebrisIndex] = *cop;
									if (groundDebrisIndex < MAX_GROUND_DEBRIS-1)
										groundDebrisIndex++;
									else
										groundDebrisIndex = 0;
								}

								if(treecount < 15)
									treecount++;
								else
									treecount = 0;
							}
						}
						else
						{
							int modelNumber;
							modelNumber = ppco->value & 0x3f;

							if (modelNumber > 0)
							{
								MATRIX2* cmat;
								cmat = &CompoundMatrix[modelNumber];
								
								if (cmat->computed != current_object_computed_value)
								{
									cmat->computed = current_object_computed_value;

									gte_ReadRotMatrix(&mRotStore);
									gte_sttr(mRotStore.t);

									MulMatrix0(&inv_camera_matrix, (MATRIX*)&matrixtable[modelNumber], (MATRIX*)cmat);

									gte_SetRotMatrix(&mRotStore);
								}
							}

							if ((model->shape_flags & 0x480) || (model->flags2 & 0xc000))
							{
								if(model->flags2 & 0x80)
								{
									alleycount++;
									
									if (alleycount == 13)
									{
										cop = UnpackCellObject(ppco, &ci.nearCell);
										ground_debris[groundDebrisIndex] = *cop;
										
										if (groundDebrisIndex < MAX_GROUND_DEBRIS-1)
											groundDebrisIndex++;
										else
											groundDebrisIndex = 0;

										alleycount = 0;
									}
								}
								
								if (tiles_found < MAX_DRAWN_TILES)
									model_tile_ptrs[tiles_found++] = ppco;
							}
							else
							{
								cop = UnpackCellObject(ppco, &ci.nearCell);

								if (other_models_found < MAX_DRAWN_BUILDINGS)
									model_object_ptrs[other_models_found++] = cop;
								
								if ((model->flags2 & 1) && anim_objs_found < MAX_DRAWN_ANIMATING)
									anim_obj_buffer[anim_objs_found++] = cop;
							}
						}
					}

					ppco = GetNextPackedCop(&ci);
				}
			}
		}

		if (dir == 0)
		{
			leftPlane += leftcos;
			backPlane += backcos;
			rightPlane += rightcos;

			hloop++;

			if (hloop + vloop == 1)
				dir = 1;
		}
		else if (dir == 1)
		{
			leftPlane += leftsin;
			backPlane += backsin;
			rightPlane += rightsin;
			vloop++;

			//PVS_ptr += pvs_square;

			if (hloop == vloop)
				dir = 2;
		}
		else if (dir == 2)
		{
			hloop--;
			leftPlane -= leftcos;
			backPlane -= backcos;
			rightPlane -= rightcos;

			if (hloop + vloop == 0)
				dir = 3;
		}
		else
		{
			leftPlane -= leftsin;
			backPlane -= backsin;
			rightPlane -= rightsin;
			vloop--;
			
			//PVS_ptr -= pvs_square;

			if (hloop == vloop)
				dir = 0;
		}

		i--;
	}

#if 0
	char tempBuf[512];

	SetTextColour(255, 255, 0);

	sprintf(tempBuf, "Buildings: %d", other_models_found);
	PrintString(tempBuf, 10, 60);

	sprintf(tempBuf, "Sprites: %d", sprites_found);
	PrintString(tempBuf, 10, 75);

	sprintf(tempBuf, "Tiles: %d", tiles_found);
	PrintString(tempBuf, 10, 90);

	sprintf(tempBuf, "Anims: %d", anim_objs_found);
	PrintString(tempBuf, 10, 105);

	sprintf(tempBuf, "TOTAL: %d", other_models_found + sprites_found + tiles_found + anim_objs_found );
	PrintString(tempBuf, 10, 120);
#endif

	SetupPlaneColours(combointensity);

	if (sprites_found)
		DrawSprites((PACKED_CELL_OBJECT**)spriteList, sprites_found);

	if (tiles_found)
		DrawTILES((PACKED_CELL_OBJECT**)model_tile_ptrs, tiles_found);

	if (other_models_found)
		DrawAllBuildings((CELL_OBJECT**)model_object_ptrs, other_models_found);

	if (anim_objs_found)
		DrawAllAnimatingObjects((CELL_OBJECT**)anim_obj_buffer, anim_objs_found);
}

// decompiled code
// original method signature: 
// void /*$ra*/ SetupPlaneColours(unsigned long ambient /*$a3*/)
 // line 1125, offset 0x00040218
	/* begin block 1 */
		// Start line: 1126
		// Start offset: 0x00040218

		/* begin block 1.1 */
			// Start line: 1140
			// Start offset: 0x000402B4
			// Variables:
		// 		unsigned long r; // $t4
		// 		unsigned long g; // $t2
		// 		unsigned long b; // $a0
		/* end block 1.1 */
		// End offset: 0x000402B4
		// End Line: 1140
	/* end block 1 */
	// End offset: 0x00040408
	// End Line: 1159

	/* begin block 2 */
		// Start line: 2705
	/* end block 2 */
	// End Line: 2706

	/* begin block 3 */
		// Start line: 2708
	/* end block 3 */
	// End Line: 2709

	/* begin block 4 */
		// Start line: 2709
	/* end block 4 */
	// End Line: 2710

// [D] [T]
void SetupPlaneColours(ulong ambient)
{
	unsigned long r;
	unsigned long g;
	unsigned long b;

	if ((gWeather - 1U > 1) && gTimeOfDay != 0 && gTimeOfDay != 2)
	{
		if (gTimeOfDay == 1)
		{
			b = ambient & 0xff;
			g = ambient >> 8 & 0xff;
			r = ambient >> 0x10 & 0xff;

			planeColours[1] = (r * 0x78 >> 7) << 0x10 | (g * 0x78 >> 7) << 8 | b * 0x78 >> 7;
			planeColours[2] = (r * 0x67 >> 7) << 0x10 | (g * 0x67 >> 7) << 8 | b * 0x67 >> 7;
			planeColours[3] = (r * 0xd >> 5) << 0x10 | (g * 0xd >> 5) << 8 | b * 0xd >> 5;
			planeColours[0] = r << 0x10 | g << 8 | b;
			planeColours[4] = (r * 3 >> 3) << 0x10 | (g * 3 >> 3) << 8 | b * 3 >> 3;
			planeColours[5] = planeColours[3];
			planeColours[6] = planeColours[2];
			planeColours[7] = planeColours[1];
			return;
		}

		planeColours[0] = ambient;
		planeColours[1] = ambient;
		planeColours[2] = ambient;
		planeColours[3] = ambient;
		planeColours[4] = ambient;
		planeColours[5] = ambient;
		planeColours[6] = ambient;
		planeColours[7] = ambient;
		return;
	}

	planeColours[0] = ambient;
	planeColours[1] = ambient + 0x10101;
	planeColours[2] = ambient + 0x30303;
	planeColours[3] = ambient + 0x80808;
	planeColours[4] = ambient + 0xa0a0a;
	planeColours[5] = ambient + 0x80808;
	planeColours[6] = ambient + 0x30303;
	planeColours[7] = ambient + 0x10101;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDrawMapPSX()
 // line 1162, offset 0x00040408
	/* begin block 1 */
		// Start line: 1165
		// Start offset: 0x00040408

		/* begin block 1.1 */
			// Start line: 1166
			// Start offset: 0x00040468
			// Variables:
		// 		int region_x1; // $t0
		// 		int region_z1; // $a0
		// 		int current_barrel_region_x1; // $v0
		// 		int current_barrel_region_z1; // $a0
		/* end block 1.1 */
		// End offset: 0x0004048C
		// End Line: 1178

		/* begin block 1.2 */
			// Start line: 1178
			// Start offset: 0x0004048C
			// Variables:
		// 		int theta; // $s2
		/* end block 1.2 */
		// End offset: 0x00040500
		// End Line: 1196
	/* end block 1 */
	// End offset: 0x00040534
	// End Line: 1200

	/* begin block 2 */
		// Start line: 2788
	/* end block 2 */
	// End Line: 2789

	/* begin block 3 */
		// Start line: 2792
	/* end block 3 */
	// End Line: 2793

	/* begin block 4 */
		// Start line: 2794
	/* end block 4 */
	// End Line: 2795

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void SetupDrawMapPSX(void)
{
	int region_x1;
	int region_z1;
	int current_barrel_region_x1;
	int current_barrel_region_z1;

	int theta;

	current_cell_x = (camera_position.vx + units_across_halved) / MAP_CELL_SIZE;
	current_cell_z = (camera_position.vz + units_down_halved) / MAP_CELL_SIZE;

	region_x1 = current_cell_x / MAP_REGION_SIZE;
	region_z1 = current_cell_z / MAP_REGION_SIZE;

	current_barrel_region_x1 = (region_x1 & 1);
	current_barrel_region_z1 = (region_z1 & 1);

	GetPVSRegionCell2(
		current_barrel_region_x1 + current_barrel_region_z1 * 2,
		region_x1 + region_z1 * cells_across / MAP_REGION_SIZE,
		(current_cell_z % MAP_REGION_SIZE) * MAP_REGION_SIZE + (current_cell_x % MAP_REGION_SIZE),
		CurrentPVS);


	for (theta = 0; theta < 64; theta++)
		MulMatrix0(&inv_camera_matrix, (MATRIX*)&matrixtable[theta], (MATRIX*)&CompoundMatrix[theta]);

	InitFrustrumMatrix();
	SetFrustrumMatrix();

	setupYet = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitFrustrumMatrix()
 // line 1209, offset 0x00040534
	/* begin block 1 */
		// Start line: 2912
	/* end block 1 */
	// End Line: 2913

	/* begin block 2 */
		// Start line: 2922
	/* end block 2 */
	// End Line: 2923

	/* begin block 3 */
		// Start line: 2923
	/* end block 3 */
	// End Line: 2924

/* WARNING: Unknown calling convention yet parameter storage is locked */

MATRIX frustrum_matrix;

// [D] [T]
void InitFrustrumMatrix(void)
{
	int a;

	a = -camera_angle.vy;

	frustrum_matrix.m[0][1] = 0;
	frustrum_matrix.m[0][0] = rcossin_tbl[(a & 0xfffU) * 2];
	frustrum_matrix.m[0][2] = rcossin_tbl[(a & 0xfffU) * 2 + 1];

	a = (FrAng - 1024) - camera_angle.vy;

	frustrum_matrix.m[1][1] = 0;
	frustrum_matrix.m[1][0] = rcossin_tbl[(a & 0xfff) * 2];
	frustrum_matrix.m[1][2] = rcossin_tbl[(a & 0xfff) * 2 + 1];

	a = -(FrAng - 1024) - camera_angle.vy;

	frustrum_matrix.m[2][1] = 0;
	frustrum_matrix.m[2][0] = rcossin_tbl[(a & 0xfff) * 2];
	frustrum_matrix.m[2][2] = rcossin_tbl[(a & 0xfff) * 2 + 1];
	frustrum_matrix.t[0] = -80;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFrustrumMatrix()
 // line 1219, offset 0x000417a4
	/* begin block 1 */
		// Start line: 4751
	/* end block 1 */
	// End Line: 4752

	/* begin block 2 */
		// Start line: 2438
	/* end block 2 */
	// End Line: 2439

	/* begin block 3 */
		// Start line: 4752
	/* end block 3 */
	// End Line: 4753

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void SetFrustrumMatrix(void)
{
	gte_SetLightMatrix(&frustrum_matrix);
}

// decompiled code
// original method signature: 
// void /*$ra*/ Set_Inv_CameraMatrix()
 // line 1224, offset 0x000417dc
	/* begin block 1 */
		// Start line: 4761
	/* end block 1 */
	// End Line: 4762

	/* begin block 2 */
		// Start line: 4762
	/* end block 2 */
	// End Line: 4763

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void Set_Inv_CameraMatrix(void)
{
	gte_SetColorMatrix(&inv_camera_matrix);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalcObjectRotationMatrices()
 // line 1324, offset 0x00041814
	/* begin block 1 */
		// Start line: 1326
		// Start offset: 0x00041814
		// Variables:
	// 		int i; // $s1
	// 		int j; // $a0
	// 		SVECTOR ang; // stack offset -56
	// 		MATRIX mat; // stack offset -48
	/* end block 1 */
	// End offset: 0x000418BC
	// End Line: 1341

	/* begin block 2 */
		// Start line: 4961
	/* end block 2 */
	// End Line: 4962

	/* begin block 3 */
		// Start line: 4962
	/* end block 3 */
	// End Line: 4963

	/* begin block 4 */
		// Start line: 4968
	/* end block 4 */
	// End Line: 4969

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T] [A]
void CalcObjectRotationMatrices(void)
{
	int i;
	int angle;
	MATRIX* m;

	angle = 0;

	for (i = 0; i < 64; i++)
	{
		// simpler and faster method
		m = (MATRIX*)&matrixtable[i];

		m->m[0][0] = ONE; m->m[0][1] = 0;   m->m[0][2] = 0;
		m->m[1][0] = 0;   m->m[1][1] = ONE; m->m[1][2] = 0;
		m->m[2][0] = 0;   m->m[2][1] = 0;   m->m[2][2] = ONE;

		RotMatrixY(angle, m);

		angle += 64;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlotMDL_less_than_128(MODEL *model /*$a0*/)
 // line 1344, offset 0x000418bc
	/* begin block 1 */
		// Start line: 5018
	/* end block 1 */
	// End Line: 5019

	/* begin block 2 */
		// Start line: 5022
	/* end block 2 */
	// End Line: 5023

	/* begin block 3 */
		// Start line: 5023
	/* end block 3 */
	// End Line: 5024

// [D] [T]
void PlotMDL_less_than_128(MODEL* model)
{
	RenderModel(model, (MATRIX*)0x0, (VECTOR*)0x0, 0, 0, 0, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessMapLump(char *lump_ptr /*$v0*/, int lump_size /*$a1*/)
 // line 1425, offset 0x00040608
	/* begin block 1 */
		// Start line: 1426
		// Start offset: 0x00040608
		// Variables:
	// 		char *cellptr; // $s0
	// 		int cell_size; // $a3
	// 		int region_size; // $t0
	/* end block 1 */
	// End offset: 0x000407D8
	// End Line: 1478

	/* begin block 2 */
		// Start line: 3346
	/* end block 2 */
	// End Line: 3347

	/* begin block 3 */
		// Start line: 3357
	/* end block 3 */
	// End Line: 3358


// [D] [T]
void ProcessMapLump(char* lump_ptr, int lump_size)
{
#ifdef PSX
	cells_across = *(int*)lump_ptr;
	cells_down = *(int*)(lump_ptr + 4);
	num_regions = *(int*)(lump_ptr + 0xc);
	view_dist = 10;

	pvs_square = 21;
	pvs_square_sq = 21 * 21;

	units_across_halved = cells_across / 2 << 0xb;
	units_down_halved = cells_down / 2 << 0xb;
	regions_across = cells_across;

	if (cells_across < 0) {
		regions_across = cells_across + 0x1f;
	}
	regions_across = regions_across >> 5;
	regions_down = cells_down;
	if (cells_down < 0) {
		regions_down = cells_down + 0x1f;
	}
	regions_down = regions_down >> 5;
	if (0x400 < num_regions) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	num_straddlers = *(int*)(lump_ptr + 0x2c);
	if (*(int*)(lump_ptr + 8) != 0x800) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if (*(int*)(lump_ptr + 0x10) != 0x20) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	InitCellData();
	memcpy(cell_objects, lump_ptr + 0x30, num_straddlers << 3);

#else

	memcpy(&cell_header, lump_ptr, sizeof(OUT_CELL_FILE_HEADER));

	cells_across = cell_header.cells_across;
	cells_down = cell_header.cells_down;
	num_regions = cell_header.num_regions;

	view_dist = 10;
	pvs_square = 21;
	pvs_square_sq = 21 * 21;

	units_across_halved = cells_across / 2 * MAP_CELL_SIZE;
	units_down_halved = cells_down / 2 * MAP_CELL_SIZE;

	regions_across = cells_across / MAP_REGION_SIZE;
	regions_down = cells_down / MAP_REGION_SIZE;

	lump_ptr += sizeof(OUT_CELL_FILE_HEADER);

	num_straddlers = *(int*)lump_ptr;

	InitCellData();
	memcpy(cell_objects, lump_ptr + 4, num_straddlers * sizeof(PACKED_CELL_OBJECT));
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawAllTheCars(int view /*$s6*/)
 // line 1711, offset 0x000407d8
	/* begin block 1 */
		// Start line: 1712
		// Start offset: 0x000407D8
		// Variables:
	// 		int loop; // $s0
	// 		int x; // $s2
	// 		int z; // $s1
	// 		int xd; // $a0
	// 		int zd; // $v1
	// 		CAR_DATA (*cars_to_draw[20]); // stack offset -112
	// 		int num_cars_to_draw; // $s4
	// 		static int car_distance[20]; // offset 0x0
	// 		static int temp; // offset 0x0

		/* begin block 1.1 */
			// Start line: 1712
			// Start offset: 0x000407D8
			// Variables:
		// 		CAR_DATA *lcp; // $s0

			/* begin block 1.1.1 */
				// Start line: 1738
				// Start offset: 0x00040860
				// Variables:
			// 		int dist; // $v0
			/* end block 1.1.1 */
			// End offset: 0x000408E0
			// End Line: 1748
		/* end block 1.1 */
		// End offset: 0x000408F0
		// End Line: 1751

		/* begin block 1.2 */
			// Start line: 1757
			// Start offset: 0x000408F8
			// Variables:
		// 		int i; // $a0

			/* begin block 1.2.1 */
				// Start line: 1762
				// Start offset: 0x00040920
				// Variables:
			// 		CAR_DATA *car; // $t4
			// 		int dist; // $t0
			// 		int j; // $a3
			/* end block 1.2.1 */
			// End offset: 0x000409A0
			// End Line: 1771
		/* end block 1.2 */
		// End offset: 0x000409C0
		// End Line: 1774

		/* begin block 1.3 */
			// Start line: 1790
			// Start offset: 0x000409E4
			// Variables:
		// 		int spacefree; // $a1
		/* end block 1.3 */
		// End offset: 0x00040A2C
		// End Line: 1798
	/* end block 1 */
	// End offset: 0x00040A68
	// End Line: 1824

	/* begin block 2 */
		// Start line: 3945
	/* end block 2 */
	// End Line: 3946

	/* begin block 3 */
		// Start line: 3970
	/* end block 3 */
	// End Line: 3971

	/* begin block 4 */
		// Start line: 3974
	/* end block 4 */
	// End Line: 3975

int gForceLowDetailCars = 0;
int num_cars_drawn = 0;

// [D] [T]
void DrawAllTheCars(int view)
{
	static int car_distance[MAX_CARS]; // offset 0x0
	CAR_DATA* cars_to_draw[MAX_CARS];

	int dx, dz;
	int dist;
	int i, j;
	CAR_DATA* cp;
	int num_cars_to_draw;
	int spacefree;
	

	num_cars_drawn = 0;
	num_cars_to_draw = 0;

	cp = &car_data[MAX_CARS - 1];
	do {
		if (cp->controlType != CONTROL_TYPE_NONE && 
			PositionVisible((VECTOR*)cp->hd.where.t))
		{
			// XZ distance estimation
			dx = ABS(camera_position.vx - cp->hd.where.t[0]);
			dz = ABS(camera_position.vz - cp->hd.where.t[2]);

			if (dx < dz)
				dist = dz + dx / 2;
			else
				dist = dx + dz / 2;

			if (dist < 16000)
			{
				car_distance[num_cars_to_draw] = dx + dz;
				cars_to_draw[num_cars_to_draw] = cp;
				num_cars_to_draw++;
			}
		}

		cp--;
	} while (cp >= car_data);

	if (num_cars_to_draw != 0)
	{
		gForceLowDetailCars = 0;

		// sort cars by distance
		i = 1;
		while (i < num_cars_to_draw)
		{
			cp = cars_to_draw[i];
			dist = car_distance[i];

			j = i - 1;

			while (dist < car_distance[j])
			{
				car_distance[i] = car_distance[j];
				cars_to_draw[i] = cars_to_draw[j];

				if (j == 0)
					break;
				
				j--;
			}
			
			cars_to_draw[i] = cp;
			car_distance[i] = dist;

			i++;
		}

		i = 0;
		spacefree = (num_cars_to_draw - 1) * 2000;

		while (i < num_cars_to_draw)
		{
			// Don't exceed draw buffers
			if ((int)(current->primtab + (-3000 - (int)(current->primptr - PRIMTAB_SIZE))) < 5800)
				return;

			// make cars look uglier
			if ((int)(current->primtab + (-3000 - (int)(current->primptr - PRIMTAB_SIZE)) - spacefree) < 5800)
				gForceLowDetailCars = 1;

			if (cars_to_draw[i]->controlType == CONTROL_TYPE_PLAYER)
				gForceLowDetailCars = 0;

			DrawCar(cars_to_draw[i], view);
			
			spacefree -= 2000;
			i++;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlotBuildingModelSubdivNxN(MODEL *model /*$t0*/, int rot /*stack 4*/, _pct *pc /*$s2*/, int n /*stack 12*/)
 // line 1857, offset 0x00040a90
	/* begin block 1 */
		// Start line: 1858
		// Start offset: 0x00040A90
		// Variables:
	// 		SVECTOR *verts; // $s4
	// 		PL_POLYFT4 *polys; // $s1
	// 		int i; // $s7
	// 		int asdf; // $fp

		/* begin block 1.1 */
			// Start line: 1876
			// Start offset: 0x00040B40
			// Variables:
		// 		unsigned long word0; // $s0

			/* begin block 1.1.1 */
				// Start line: 1886
				// Start offset: 0x00040B9C
				// Variables:
			// 		int Z; // stack offset -48
			// 		unsigned int vidx; // $s3

				/* begin block 1.1.1.1 */
					// Start line: 1896
					// Start offset: 0x00040BD0
					// Variables:
				// 		unsigned long th; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x00040C10
				// End Line: 1902

				/* begin block 1.1.1.2 */
					// Start line: 1940
					// Start offset: 0x00040E30
					// Variables:
				// 		int diff; // $a1
				// 		int min; // $a2

					/* begin block 1.1.1.2.1 */
						// Start line: 1945
						// Start offset: 0x00040E30
						// Variables:
					// 		int max; // $v1
					/* end block 1.1.1.2.1 */
					// End offset: 0x00040EA4
					// End Line: 1949

					/* begin block 1.1.1.2.2 */
						// Start line: 1970
						// Start offset: 0x00040F10
						// Variables:
					// 		int w; // $s0
					/* end block 1.1.1.2.2 */
					// End offset: 0x00040F3C
					// End Line: 1973

					/* begin block 1.1.1.2.3 */
						// Start line: 1983
						// Start offset: 0x00041060
						// Variables:
					// 		POLY_FT4 *prims; // $t2
					// 		int uv0; // $v1
					// 		int uv1; // $a2
					// 		int uv2; // $t3
					// 		int uv3; // $t1

						/* begin block 1.1.1.2.3.1 */
							// Start line: 1994
							// Start offset: 0x000410A8
							// Variables:
						// 		unsigned int r; // $a2
						/* end block 1.1.1.2.3.1 */
						// End offset: 0x000410A8
						// End Line: 1994

						/* begin block 1.1.1.2.3.2 */
							// Start line: 1994
							// Start offset: 0x000410A8
							// Variables:
						// 		int r2; // $v1
						/* end block 1.1.1.2.3.2 */
						// End offset: 0x000410A8
						// End Line: 1994
					/* end block 1.1.1.2.3 */
					// End offset: 0x00041140
					// End Line: 2019
				/* end block 1.1.1.2 */
				// End offset: 0x00041140
				// End Line: 2021
			/* end block 1.1.1 */
			// End offset: 0x00041158
			// End Line: 2026
		/* end block 1.1 */
		// End offset: 0x00041178
		// End Line: 2033
	/* end block 1 */
	// End offset: 0x000411F4
	// End Line: 2040

	/* begin block 2 */
		// Start line: 4392
	/* end block 2 */
	// End Line: 4393

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

// [D] [T] [A] custom
void PlotBuildingModelSubdivNxN(MODEL* model, int rot, _pct* pc, int n)
{
	int opz;
	int diff, minZ, maxZ;
	int Z;
	PL_POLYFT4* polys;
	int i;
	int r;
	u_char temp;
	u_char ptype;
	POLY_FT4* prims;
	SVECTOR* srcVerts;
	MVERTEX subdiVerts[5][5];
	int combo;

	srcVerts = (SVECTOR*)model->vertices;
	polys = (PL_POLYFT4*)model->poly_block;

	combo = combointensity;

	// transparent object flag
	if (pc->flags & 1)
		combo |= 0x2000000;

	i = model->num_polys;
	while (i > 0)
	{
		// iterate through polygons
		// with skipping
		ptype = polys->id & 0x1f;

		if ((ptype & 1) == 0 && ptype != 8) // is FT3 triangle?
		{
			temp = polys->uv2.v;
			polys->uv3.u = polys->uv2.u;
			polys->uv3.v = temp;

			polys->v3 = polys->v2;

			polys->id |= 1;
			ptype |= 1;
		}

		if (ptype != 11 && ptype != 21)
		{
			polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
			i--;
			continue;
		}

		// perform transform
		gte_ldv3(&srcVerts[polys->v0], &srcVerts[polys->v1], &srcVerts[polys->v3]);
		gte_rtpt();

		// get culling value
		gte_nclip();
		gte_stopz(&opz);

		r = rot;

		if (pc->flags & 0x6)
		{
			if (opz < 0)
				r = rot + 32 & 63;

			if (pc->flags & 0x4)
				opz = 1;		// no culling
			else
				opz = -opz;		// front face
		}

		if (ptype == 21)
		{
			pc->colour = combo & 0x2ffffffU | 0x2c000000;
		}
		else
		{
			temp = polys->th;

			if ((polys->th & 0x80) == 0) // cache normal index if it were not
				temp = polys->th = normalIndex(srcVerts, *(uint*)&polys->v0);

			pc->colour = pc->f4colourTable[(r >> 3) * 4 - temp & 31];
		}

		if (opz > 0)
		{
			gte_stsz3(&pc->scribble[0], &pc->scribble[1], &pc->scribble[2]);

			pc->tpage = (*pc->ptexture_pages)[polys->texture_set] << 0x10;

			if ((pc->flags & 0x10) == 0) // [A] custom palette flag - for pedestrian heads
				pc->clut = (*pc->ptexture_cluts)[polys->texture_set][polys->texture_id] << 0x10;

			minZ = pc->scribble[2];
			if (pc->scribble[1] < minZ)
				minZ = pc->scribble[1];

			if (pc->scribble[0] < minZ)
				minZ = pc->scribble[0];

			maxZ = pc->scribble[2];
			if (maxZ < pc->scribble[1])
				maxZ = pc->scribble[1];

			diff = maxZ - minZ;
			if (maxZ < pc->scribble[0])
				diff = pc->scribble[0] - minZ;

			if ((n == 0) || ((diff << 2) <= minZ - 350))
			{
				prims = (POLY_FT4*)pc->primptr;

				setPolyFT4(prims);
				*(ulong*)&prims->r0 = pc->colour;

				// retrieve first three verts
				gte_stsxy3(&prims->x0, &prims->x1, &prims->x2);

				// translate 4th vert and get OT Z value
				gte_ldv0(&srcVerts[polys->v2]);
				gte_rtps();
				gte_avsz4();

				gte_stotz(&Z);

				gte_stsxy(&prims->x3);

				prims->tpage = pc->tpage >> 0x10;
				prims->clut = pc->clut >> 0x10;

				*(ushort*)&prims->u0 = *(ushort*)&polys->uv0;
				*(ushort*)&prims->u1 = *(ushort*)&polys->uv1;
				*(ushort*)&prims->u2 = *(ushort*)&polys->uv3;
				*(ushort*)&prims->u3 = *(ushort*)&polys->uv2;

				addPrim(pc->ot + (Z >> 1), prims);

				pc->primptr += sizeof(POLY_FT4);
			}
			else
			{
				r = n;
				if (n == 1)
				{
					if (minZ - 150 < (diff << 1))
						r = 4;
					else
						r = 2;
				}

				copyVector(&subdiVerts[0][0], &srcVerts[polys->v0]);
				subdiVerts[0][0].uv.val = *(ushort*)&polys->uv0;

				copyVector(&subdiVerts[0][1], &srcVerts[polys->v1]);
				subdiVerts[0][1].uv.val = *(ushort*)&polys->uv1;

				copyVector(&subdiVerts[0][2], &srcVerts[polys->v3]);
				subdiVerts[0][2].uv.val = *(ushort*)&polys->uv3;

				copyVector(&subdiVerts[0][3], &srcVerts[polys->v2]);
				subdiVerts[0][3].uv.val = *(ushort*)&polys->uv2;

				makeMesh((MVERTEX(*)[5][5])subdiVerts, r, r);
				drawMesh((MVERTEX(*)[5][5])subdiVerts, r, r, pc);
			}
		}

		polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
		i--;
	}
}


// decompiled code
// original method signature: 
// void /*$ra*/ RenderModel(MODEL *model /*$s2*/, MATRIX *matrix /*$a1*/, VECTOR *pos /*$a2*/, int zBias /*$s0*/, int flags /*stack 16*/)
 // line 2181, offset 0x0004143c
	/* begin block 1 */
		// Start line: 2182
		// Start offset: 0x0004143C
		// Variables:
	// 		int i; // $t0
	// 		unsigned long *savedOT; // $s1

		/* begin block 1.1 */
			// Start line: 2191
			// Start offset: 0x00041468
			// Variables:
		// 		MATRIX comb; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x00041498
		// End Line: 2196

		/* begin block 1.2 */
			// Start line: 2210
			// Start offset: 0x00041538
			// Variables:
		// 		int spacefree; // $a0
		/* end block 1.2 */
		// End offset: 0x000415C0
		// End Line: 2222
	/* end block 1 */
	// End offset: 0x000415E4
	// End Line: 2224

	/* begin block 2 */
		// Start line: 5547
	/* end block 2 */
	// End Line: 5548

	/* begin block 3 */
		// Start line: 5550
	/* end block 3 */
	// End Line: 5551

	/* begin block 4 */
		// Start line: 5555
	/* end block 4 */
	// End Line: 5556

// [D] [T]
void RenderModel(MODEL* model, MATRIX* matrix, VECTOR* pos, int zBias, int flags, int subdiv, int nrot)
{
	if (matrix != NULL)
	{
		MATRIX comb;
		gte_SetTransVector(pos);

		MulMatrix0(&inv_camera_matrix, matrix, &comb);
		SetRotMatrix(&comb);
	}

	zBias /= 8;
	zBias += (model->zBias - 64);

	plotContext.ot = current->ot;

	if (zBias > 0)
		plotContext.ot += (zBias * 4);

	for (int i = 0; i < 8; i++)
	{
		plotContext.f4colourTable[i * 4 + 0] = planeColours[i] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 1] = planeColours[0] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 2] = planeColours[5] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 3] = planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = flags;
	plotContext.current = current;
	
	plotContext.primptr = plotContext.current->primptr;

	if ((current->primtab - (current->primptr - PRIMTAB_SIZE)) > 56000)
		PlotBuildingModelSubdivNxN(model, nrot, &plotContext, subdiv);

	// advance primitive buffer
	current->primptr = plotContext.primptr;
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ normalIndex(SVECTOR *verts /*$a0*/, unsigned int vidx /*$a1*/)
 // line 2267, offset 0x000415e4
	/* begin block 1 */
		// Start line: 2268
		// Start offset: 0x000415E4
		// Variables:
	// 		int th23; // $a0
	// 		int nx; // $t4
	// 		int ny; // $v1
	// 		int nz; // $a2
	// 		SVECTOR p; // stack offset -16
	// 		SVECTOR q; // stack offset -8

		/* begin block 1.1 */
			// Start line: 2268
			// Start offset: 0x000415E4
			// Variables:
		// 		int x; // $a1
		// 		int y; // $a0
		/* end block 1.1 */
		// End offset: 0x00041724
		// End Line: 2275
	/* end block 1 */
	// End offset: 0x000417A4
	// End Line: 2286

	/* begin block 2 */
		// Start line: 5723
	/* end block 2 */
	// End Line: 5724

	/* begin block 3 */
		// Start line: 5767
	/* end block 3 */
	// End Line: 5768

	/* begin block 4 */
		// Start line: 5771
	/* end block 4 */
	// End Line: 5772

// [D] [T]
ulong normalIndex(SVECTOR* verts, uint vidx)
{
	SVECTOR* v0;
	SVECTOR* v1;
	SVECTOR* v2;
	int ny;
	int y;
	int th23;
	int x;
	
	int nz;
	int nx;
	SVECTOR p;
	SVECTOR q;

	v0 = verts + (vidx & 0xff);
	v1 = verts + (vidx >> 8 & 0xff);
	v2 = verts + (vidx >> 16 & 0xff);

	p.vz = v1->vz - v0->vz;
	q.vz = v2->vz - v0->vz;
	
	p.vy = v1->vy - v0->vy;
	q.vy = v2->vy - v0->vy;

	p.vx = v1->vx - v0->vx;
	q.vx = v2->vx - v0->vx;

	nx = p.vy * q.vz - p.vz * q.vy;
	nz = p.vx * q.vy - p.vy * q.vx;

	x = nx + (nz >> 3);
	y = nz - (x >> 2);

	x += (y >> 3);

	if (x < y)
	{
		if (x + y < 1) 
			th23 = y < 0 ? 5 : 4;
		else
			th23 = x < 0 ? 3 : 2;
	}
	else 
	{
		if (x + y < 1)
			th23 = x < 0 ? 6 : 7;
		else
			th23 = 0 < y ? 1 : 0;
	}
	
	th23 *= 4;

	ny = p.vz * q.vx - p.vx * q.vz;

	nx = ABS(nx);
	nz = ABS(nz);
	
	if (nx + nz < ny)
		th23 += 1;

	if (nx + nz < -ny)
		th23 = th23 & 0x1f | 2;
	else
		th23 = th23 & 0x1f;

	return th23 | 0x80;
}





