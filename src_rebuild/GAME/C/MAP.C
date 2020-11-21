#include "DRIVER2.H"
#include "MAP.H"
#include "SYSTEM.H"
#include "SPOOL.H"
#include "CONVERT.H"
#include "TEXTURE.H"
#include "MISSION.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "GLAUNCH.H"
#include "MODELS.H"
#include "PLAYERS.H"
#include "MAIN.H"

#include "STRINGS.H"

char *map_lump = NULL;
int initarea = 0;
int LoadedArea;

int current_region = 0;
int old_region = 0;

int current_cell_x = 0;
int current_cell_z = 0;

int num_regions;
int view_dist;
int pvs_square;
int pvs_square_sq;

int units_across_halved;
int units_down_halved;

int regions_across;
int regions_down;

PACKED_CELL_OBJECT** pcoplist;
CELL_OBJECT** coplist;

// decompiled code
// original method signature: 
// void /*$ra*/ NewProcessRoadMapLump(ROAD_MAP_LUMP_DATA *pRoadMapLumpData /*$s0*/, char *pLumpFile /*$s1*/)
 // line 237, offset 0x0005d7bc
	/* begin block 1 */
		// Start line: 238
		// Start offset: 0x0005D7BC
	/* end block 1 */
	// End offset: 0x0005D814
	// End Line: 243

	/* begin block 2 */
		// Start line: 2217
	/* end block 2 */
	// End Line: 2218

	/* begin block 3 */
		// Start line: 474
	/* end block 3 */
	// End Line: 475

// [D] [T]
void NewProcessRoadMapLump(ROAD_MAP_LUMP_DATA *pRoadMapLumpData, char *pLumpFile)
{
	Getlong((char*)&pRoadMapLumpData->width, pLumpFile);
	Getlong((char*)&pRoadMapLumpData->height, pLumpFile + 4);

	pRoadMapLumpData->unitXMid = (pRoadMapLumpData->width + 1) * 512;
	pRoadMapLumpData->unitZMid = pRoadMapLumpData->height * 512;
}


// decompiled code
// original method signature: 
// void /*$ra*/ ProcessJunctionsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
 // line 247, offset 0x0005d6cc
	/* begin block 1 */
		// Start line: 494
	/* end block 1 */
	// End Line: 495

	/* begin block 2 */
		// Start line: 1664
	/* end block 2 */
	// End Line: 1665

// [D] [T]
void ProcessJunctionsLump(char *lump_file, int lump_size)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessRoadsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
 // line 252, offset 0x0005d6c4
	/* begin block 1 */
		// Start line: 1668
	/* end block 1 */
	// End Line: 1669

	/* begin block 2 */
		// Start line: 504
	/* end block 2 */
	// End Line: 505

// [D] [T]
void ProcessRoadsLump(char *lump_file, int lump_size)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessRoadBoundsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
 // line 253, offset 0x0005d6d4
	/* begin block 1 */
		// Start line: 1675
	/* end block 1 */
	// End Line: 1676

// [D] [T]
void ProcessRoadBoundsLump(char *lump_file, int lump_size)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessJuncBoundsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
 // line 254, offset 0x0005d6dc
	/* begin block 1 */
		// Start line: 1677
	/* end block 1 */
	// End Line: 1678

// [D] [T]
void ProcessJuncBoundsLump(char *lump_file, int lump_size)
{
	return;
}



// decompiled code
// original method signature: 
// MODEL * /*$ra*/ FindModelPtrWithName(char *name /*$s4*/)
 // line 289, offset 0x0005d40c
	/* begin block 1 */
		// Start line: 290
		// Start offset: 0x0005D40C
		// Variables:
	// 		int dummy; // stack offset -32

		/* begin block 1.1 */
			// Start line: 290
			// Start offset: 0x0005D40C
			// Variables:
		// 		char *name; // $s4
		// 		int *num; // $s2

			/* begin block 1.1.1 */
				// Start line: 290
				// Start offset: 0x0005D40C
				// Variables:
			// 		int count; // $s1
			// 		char *temp; // $s0
			/* end block 1.1.1 */
			// End offset: 0x0005D4A4
			// End Line: 290
		/* end block 1.1 */
		// End offset: 0x0005D4A4
		// End Line: 290
	/* end block 1 */
	// End offset: 0x0005D4C4
	// End Line: 293

	/* begin block 2 */
		// Start line: 1545
	/* end block 2 */
	// End Line: 1546

	/* begin block 3 */
		// Start line: 578
	/* end block 3 */
	// End Line: 579

MODEL * FindModelPtrWithName(char *name)
{
	char cVar1;
	int iVar2;
	int iVar3;
	char *__s1;
	int iVar4;

	iVar4 = 0;
	__s1 = modelname_buffer;
	if (0 < num_models_in_pack) {
		do {
			iVar2 = strcmp(__s1, name);
			iVar3 = iVar4 + 1;
			if (iVar2 == 0) {
				return modelpointers[iVar4];
			}
			do {
				cVar1 = *__s1;
				__s1 = __s1 + 1;
			} while (cVar1 != '\0');
			iVar4 = iVar3;
		} while (iVar3 < num_models_in_pack);
	}
	return NULL;
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindModelIdxWithName(char *name /*$s3*/)
 // line 295, offset 0x0005d4c4
	/* begin block 1 */
		// Start line: 296
		// Start offset: 0x0005D4C4
		// Variables:
	// 		int i; // stack offset -32

		/* begin block 1.1 */
			// Start line: 296
			// Start offset: 0x0005D4C4
			// Variables:
		// 		char *name; // $s3
		// 		int *num; // $s2

			/* begin block 1.1.1 */
				// Start line: 296
				// Start offset: 0x0005D4C4
				// Variables:
			// 		int count; // $s1
			// 		char *temp; // $s0
			/* end block 1.1.1 */
			// End offset: 0x0005D540
			// End Line: 296
		/* end block 1.1 */
		// End offset: 0x0005D540
		// End Line: 296
	/* end block 1 */
	// End offset: 0x0005D560
	// End Line: 300

	/* begin block 2 */
		// Start line: 1554
	/* end block 2 */
	// End Line: 1555

	/* begin block 3 */
		// Start line: 1557
	/* end block 3 */
	// End Line: 1558

// [D] [T]
int FindModelIdxWithName(char *name)
{
	char *str;
	int i;

	i = 0;
	str = modelname_buffer;

	while (i < num_models_in_pack)
	{
		if (!strcmp(str, name))
			return i;

		while (*str++) {} // go to next string

		i++;
	}

	return -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitCellData()
 // line 311, offset 0x0005d36c
	/* begin block 1 */
		// Start line: 313
		// Start offset: 0x0005D36C
		// Variables:
	// 		char *alloclist; // $a2
	// 		int loop; // $v1
	/* end block 1 */
	// End offset: 0x0005D40C
	// End Line: 360

	/* begin block 2 */
		// Start line: 622
	/* end block 2 */
	// End Line: 623

	/* begin block 3 */
		// Start line: 1465
	/* end block 3 */
	// End Line: 1466

	/* begin block 4 */
		// Start line: 1472
	/* end block 4 */
	// End Line: 1473

/* WARNING: Unknown calling convention yet parameter storage is locked */

int cells_across = 1000;
int cells_down = 1000;

unsigned short *cell_ptrs;
PACKED_CELL_OBJECT* cell_objects;
int sizeof_cell_object_computed_values;
CELL_DATA* cells;
int num_straddlers;		// objects between regions

// [D] [T]
void InitCellData(void)
{
	int loop;

	MALLOC_BEGIN();

	cell_ptrs = (ushort *)D_MALLOC(4096 * sizeof(short));

	// init cell pointers
	for (loop = 0; loop < 4096; loop++)
		cell_ptrs[loop] = 0xFF;

	// (mallocptr + 8192);
	cell_objects = (PACKED_CELL_OBJECT*)D_MALLOC((num_straddlers + cell_objects_add[4]) * sizeof(PACKED_CELL_OBJECT));
	cells = (CELL_DATA*)D_MALLOC(cell_slots_add[4] * sizeof(CELL_DATA));

	MALLOC_END();

	sizeof_cell_object_computed_values = (num_straddlers + cell_objects_add[4] + 7) / sizeof(PACKED_CELL_OBJECT);
}



// decompiled code
// original method signature: 
// int /*$ra*/ newPositionVisible(VECTOR *pos /*$a0*/, char *pvs /*$a1*/, int ccx /*$a2*/, int ccz /*$a3*/)
 // line 378, offset 0x0005d61c
	/* begin block 1 */
		// Start line: 379
		// Start offset: 0x0005D61C
		// Variables:
	// 		int dx; // $a2
	// 		int dz; // $a0
	// 		int cellx; // $v1
	// 		int cellz; // $v0
	/* end block 1 */
	// End offset: 0x0005D6C4
	// End Line: 398

	/* begin block 2 */
		// Start line: 1770
	/* end block 2 */
	// End Line: 1771

	/* begin block 3 */
		// Start line: 756
	/* end block 3 */
	// End Line: 757

	/* begin block 4 */
		// Start line: 1773
	/* end block 4 */
	// End Line: 1774

// [D] [T]
int newPositionVisible(VECTOR *pos, char *pvs, int ccx, int ccz)
{
 	int dx; // $a2
 	int dz; // $a0
 	int cellx; // $v1
 	int cellz; // $v0

	int ab;

	dx = pos->vx + units_across_halved;
	dz = pos->vz + units_down_halved;

	cellx = (dx / MAP_CELL_SIZE) - ccx;
	cellz = (dz / MAP_CELL_SIZE) - ccz;

	if (ABS(cellx) <= view_dist && ABS(cellz) <= view_dist)
	{
		return pvs[cellx + 10 + (cellz + 10) * pvs_square] != 0;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PositionVisible(VECTOR *pos /*$a0*/)
 // line 400, offset 0x0005d560
	/* begin block 1 */
		// Start line: 401
		// Start offset: 0x0005D560
		// Variables:
	// 		int dx; // $a1
	// 		int dz; // $a0
	// 		int cellx; // $v1
	// 		int cellz; // $v0
	/* end block 1 */
	// End offset: 0x0005D61C
	// End Line: 420

	/* begin block 2 */
		// Start line: 1666
	/* end block 2 */
	// End Line: 1667

	/* begin block 3 */
		// Start line: 1767
	/* end block 3 */
	// End Line: 1768

	/* begin block 4 */
		// Start line: 1770
	/* end block 4 */
	// End Line: 1771

// [D] [T]
int PositionVisible(VECTOR *pos)
{
 	int dx; // $a1
 	int dz; // $a0
 	int cellx; // $v1
 	int cellz; // $v0

	int ab;

	dx = pos->vx + units_across_halved;
	dz = pos->vz + units_down_halved;

	cellx = (dx / MAP_CELL_SIZE) - current_cell_x;
	cellz = (dz / MAP_CELL_SIZE) - current_cell_z;

	if (cellx < 0)
		ab = -cellx;
	else
		ab = cellx;

	if (ab <= view_dist)
	{
		if (cellz < 0)
			ab = -cellz;
		else
			ab = cellz;

		if (ab <= view_dist)
			return CurrentPVS[cellx + 10 + (cellz + 10) * pvs_square] != 0;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckUnpackNewRegions()
 // line 438, offset 0x0005c824
	/* begin block 1 */
		// Start line: 440
		// Start offset: 0x0005C824
		// Variables:
	// 		AREA_LOAD_INFO regions_to_unpack[3]; // stack offset -104
	// 		int leftright_unpack; // $a1
	// 		int topbottom_unpack; // $a2
	// 		int num_regions_to_unpack; // $s5
	// 		int x; // $a2
	// 		int z; // $v1
	// 		int loop; // $s6
	// 		int barrel_region; // $s1
	// 		int sortcount; // $s4
	// 		int i; // $v1
	// 		int j; // $a2
	// 		SVECTOR sortregions[4]; // stack offset -80
	// 		unsigned short sortorder[4]; // stack offset -48
	// 		int force_load_boundary; // $a0

		/* begin block 1.1 */
			// Start line: 539
			// Start offset: 0x0005C9F4
			// Variables:
		// 		int region_to_unpack; // $s0
		// 		Spool *spoolptr; // $a1

			/* begin block 1.1.1 */
				// Start line: 559
				// Start offset: 0x0005CA74
			/* end block 1.1.1 */
			// End offset: 0x0005CB00
			// End Line: 579
		/* end block 1.1 */
		// End offset: 0x0005CB00
		// End Line: 580

		/* begin block 1.2 */
			// Start line: 584
			// Start offset: 0x0005CB28
		/* end block 1.2 */
		// End offset: 0x0005CB94
		// End Line: 594
	/* end block 1 */
	// End offset: 0x0005CC00
	// End Line: 598

	/* begin block 2 */
		// Start line: 876
	/* end block 2 */
	// End Line: 877

	/* begin block 3 */
		// Start line: 877
	/* end block 3 */
	// End Line: 878

	/* begin block 4 */
		// Start line: 878
	/* end block 4 */
	// End Line: 879

/* WARNING: Unknown calling convention yet parameter storage is locked */

// FIXME: move it somewhere else
extern int saved_leadcar_pos;

int region_x = 0;
int region_z = 0;

int current_barrel_region_xcell = 0;
int current_barrel_region_zcell = 0;

// [D] [T]
int CheckUnpackNewRegions(void)
{
	ushort sort;
	ushort *destsort;
	ushort *srcsort;

	int x, z;
	int i, j;
	int sortcount;
	int leftright_unpack;
	int topbottom_unpack;
	int target_region;
	int region_to_unpack;
	int num_regions_to_unpack;
	int force_load_boundary;
	AREA_LOAD_INFO regions_to_unpack[3];
	SVECTOR sortregions[4];
	ushort sortorder[4];

	leftright_unpack = 0;
	topbottom_unpack = 0;
	num_regions_to_unpack = 0;

	if (saved_leadcar_pos != 0) 
		return 0;

	force_load_boundary = 13;

	if (lead_car == 0)
		force_load_boundary = 18;

	if (current_barrel_region_xcell < force_load_boundary)
	{
		if (region_x != 0) 
		{
			leftright_unpack = 1;
			num_regions_to_unpack = 1;
			regions_to_unpack[0].xoffset = -1;
			regions_to_unpack[0].zoffset = 0;
		}
	}
	else if (0x20 - force_load_boundary < current_barrel_region_xcell)
	{
		if (region_x < cells_across >> 5)
		{
			leftright_unpack = 2;
			num_regions_to_unpack = 1;
			regions_to_unpack[0].xoffset = 1;
			regions_to_unpack[0].zoffset = 0;
		}
	}

	if (current_barrel_region_zcell < force_load_boundary)
	{
		if (region_z != 0) 
		{
			topbottom_unpack = 1;
			regions_to_unpack[num_regions_to_unpack].xoffset = 0;
			regions_to_unpack[num_regions_to_unpack].zoffset = -1;
			num_regions_to_unpack++;
		}
	}
	else if (32 - force_load_boundary < current_barrel_region_zcell && region_z != 0)
	{
		topbottom_unpack = 2;
		regions_to_unpack[num_regions_to_unpack].xoffset = 0;
		regions_to_unpack[num_regions_to_unpack].zoffset = 1;
		num_regions_to_unpack++;
	}

	if (num_regions_to_unpack == 2)
	{
		if (topbottom_unpack == 1)
		{
			num_regions_to_unpack = 3;

			if (leftright_unpack == 1)
			{
				regions_to_unpack[2].xoffset = -1;
				regions_to_unpack[2].zoffset = -1;
			}
			else
			{
				regions_to_unpack[2].xoffset = 1;
				regions_to_unpack[2].zoffset = -1;
			}
		}
		else 
		{
			if (leftright_unpack == 1)
				regions_to_unpack[2].xoffset = -1;
			else 
				regions_to_unpack[2].xoffset = 1;

			regions_to_unpack[2].zoffset = 1;
		}
		num_regions_to_unpack = 3;
	}

	i = 0;
	sortcount = 0;

	// get next region a space
	while (i < num_regions_to_unpack)
	{
		x = regions_to_unpack[i].xoffset;
		z = regions_to_unpack[i].zoffset;

		target_region = (region_x + x & 1U) + (region_z + z & 1U) * 2;
		region_to_unpack = current_region + x + z * (cells_across / 32);

		if (region_to_unpack != regions_unpacked[target_region] && loading_region[target_region] == -1)
		{
			ClearRegion(target_region);

			if (spoolinfo_offsets[region_to_unpack] == 0xffff)
			{
				regions_unpacked[target_region] = region_to_unpack;
			}
			else 
			{
				Spool *spoolptr = (Spool*)(RegionSpoolInfo + spoolinfo_offsets[region_to_unpack]);

				if (old_region == -1 && spoolptr->super_region != 0xFF)
					initarea = spoolptr->super_region;

				sortregions[sortcount].vx = region_to_unpack;
				sortregions[sortcount].vy = target_region;
				sortregions[sortcount].vz = spoolptr->offset;

				sortorder[sortcount] = sortcount;
				sortcount++;
			}
		}
		i++;
	}

	i = 0;
	while (i < sortcount)
	{
		if (sortcount > (i + 1))
		{
			srcsort = sortorder + i;
			destsort = sortorder + (i + 1);

			j = sortcount - (i + 1);

			do {
				sort = *srcsort;
				if (sortregions[*destsort].vz < sortregions[*srcsort].vz)
				{
					*srcsort = *destsort;
					*destsort = sort;
				}

				j--;
				destsort++;
			} while (j > 0);
		}

		UnpackRegion(sortregions[sortorder[i]].vx, sortregions[sortorder[i]].vy);

		i++;
	}

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlMap()
 // line 612, offset 0x0005cc00
	/* begin block 1 */
		// Start line: 614
		// Start offset: 0x0005CC00
		// Variables:
	// 		int x; // $a2
	// 		int z; // $a1

		/* begin block 1.1 */
			// Start line: 639
			// Start offset: 0x0005CCE4
		/* end block 1.1 */
		// End offset: 0x0005CCEC
		// End Line: 640

		/* begin block 1.2 */
			// Start line: 648
			// Start offset: 0x0005CD10
		/* end block 1.2 */
		// End offset: 0x0005CD20
		// End Line: 649
	/* end block 1 */
	// End offset: 0x0005CD80
	// End Line: 654

	/* begin block 2 */
		// Start line: 1306
	/* end block 2 */
	// End Line: 1307

	/* begin block 3 */
		// Start line: 1321
	/* end block 3 */
	// End Line: 1322

	/* begin block 4 */
		// Start line: 1322
	/* end block 4 */
	// End Line: 1323

	/* begin block 5 */
		// Start line: 1327
	/* end block 5 */
	// End Line: 1328

/* WARNING: Unknown calling convention yet parameter storage is locked */

extern OUT_CELL_FILE_HEADER cell_header;

// [D] [T]
void ControlMap(void)
{
	int region_to_unpack;

	current_cell_x = (player[0].spoolXZ->vx + units_across_halved) / MAP_CELL_SIZE;
	current_cell_z = (player[0].spoolXZ->vz + units_down_halved) / MAP_CELL_SIZE;

	region_x = current_cell_x / MAP_REGION_SIZE;
	region_z = current_cell_z / MAP_REGION_SIZE;

	old_region = current_region;

	current_barrel_region_xcell = current_cell_x - region_x * MAP_REGION_SIZE;
	current_barrel_region_zcell = current_cell_z - region_z * MAP_REGION_SIZE;

	region_to_unpack = region_x + region_z * (cells_across / MAP_REGION_SIZE);

	if (current_region == -1)
		UnpackRegion(region_to_unpack, region_x & 1U | (region_z & 1U) * 2);		// is that ever valid for 'target_barrel_region'?

	current_region = region_to_unpack;
	
	CheckLoadAreaData(current_barrel_region_xcell, current_barrel_region_zcell);

	CheckUnpackNewRegions();

	current_cell_x = (camera_position.vx + units_across_halved) / MAP_CELL_SIZE;
	current_cell_z = (camera_position.vz + units_down_halved) / MAP_CELL_SIZE;

	StartSpooling();
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitMap()
 // line 677, offset 0x0005cd80
	/* begin block 1 */
		// Start line: 679
		// Start offset: 0x0005CD80
		// Variables:
	// 		int i; // $s0
	// 		int tpage; // $v0
	// 		char result[8]; // stack offset -24

		/* begin block 1.1 */
			// Start line: 707
			// Start offset: 0x0005CE30

			/* begin block 1.1.1 */
				// Start line: 716
				// Start offset: 0x0005CE88
				// Variables:
			// 		int region; // $a3
			// 		int barrel_region; // $a1
			// 		Spool *spoolptr; // $v1

				/* begin block 1.1.1.1 */
					// Start line: 726
					// Start offset: 0x0005CEF4
				/* end block 1.1.1.1 */
				// End offset: 0x0005CF20
				// End Line: 732
			/* end block 1.1.1 */
			// End offset: 0x0005CF20
			// End Line: 733
		/* end block 1.1 */
		// End offset: 0x0005CF90
		// End Line: 742

		/* begin block 1.2 */
			// Start line: 678
			// Start offset: 0x0005CF90
		/* end block 1.2 */
		// End offset: 0x0005CFA8
		// End Line: 678
	/* end block 1 */
	// End offset: 0x0005CFA8
	// End Line: 744

	/* begin block 2 */
		// Start line: 1451
	/* end block 2 */
	// End Line: 1452

	/* begin block 3 */
		// Start line: 1475
	/* end block 3 */
	// End Line: 1476

	/* begin block 4 */
		// Start line: 1476
	/* end block 4 */
	// End Line: 1477

	/* begin block 5 */
		// Start line: 1484
	/* end block 5 */
	// End Line: 1485

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitMap(void)
{
	int region_to_unpack;
	int barrel_region;
	int i;

	initarea = -1;
	LoadedArea = -1;
	current_region = -1;

	i = slotsused;

	while (i < 19)
	{
		int tpage = tpageslots[i];

		if (tpage != 0xff)
			tpageloaded[tpage] = 0;

		tpageslots[i] = 0xff;
		i++;
	}

	// load regions synchronously
	if (doSpooling == 0)
	{
		old_region = -1;

		if (multiplayerregions[1] == -1)
		{
			multiplayerregions[1] = multiplayerregions[0] + 1;
			multiplayerregions[2] = multiplayerregions[0] - (cells_across >> 5);
			multiplayerregions[3] = multiplayerregions[2] + 1;
		}

		i = 0;
		do {
			region_to_unpack = multiplayerregions[i];

			if (spoolinfo_offsets[region_to_unpack] != 0xffff)
			{
				Spool* spoolptr = (Spool*)(RegionSpoolInfo + spoolinfo_offsets[region_to_unpack]);

				if (spoolptr->super_region != 0xff)
					initarea = spoolptr->super_region;

				barrel_region = (region_to_unpack % (cells_across >> 5) & 1U) + (region_to_unpack / (cells_across >> 5) & 1U) * 2;

				UnpackRegion(region_to_unpack, barrel_region);
			}

			i++;
		} while (i < 4);

		LoadInAreaTSets(initarea);
		LoadInAreaModels(initarea);

		current_cell_x = (camera_position.vx + units_across_halved) / MAP_CELL_SIZE;
		current_cell_z = (camera_position.vz + units_down_halved) / MAP_CELL_SIZE;

		StartSpooling();
	}
	else
	{
		regions_unpacked[0] = -1;
		regions_unpacked[1] = -1;
		regions_unpacked[2] = -1;
		regions_unpacked[3] = -1;

		ControlMap();
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetVisSetAtPosition(VECTOR *pos /*$a0*/, char *tgt /*$t3*/, int *ccx /*$a1*/, int *ccz /*$a3*/)
 // line 756, offset 0x0005d6e4
	/* begin block 1 */
		// Start line: 757
		// Start offset: 0x0005D6E4
		// Variables:
	// 		int x; // $t2
	// 		int z; // $t1
	// 		int cx; // $t0
	// 		int cz; // $a2
	// 		int rx; // $a3
	// 		int rz; // $a0

		/* begin block 1.1 */
			// Start line: 767
			// Start offset: 0x0005D76C
			// Variables:
		// 		int barrel_region_x; // $v0
		// 		int barrel_region_z; // $a0
		/* end block 1.1 */
		// End offset: 0x0005D7BC
		// End Line: 778
	/* end block 1 */
	// End offset: 0x0005D7BC
	// End Line: 779

	/* begin block 2 */
		// Start line: 2681
	/* end block 2 */
	// End Line: 2682

	/* begin block 3 */
		// Start line: 2685
	/* end block 3 */
	// End Line: 2686

// [D] [T] [A]
void GetVisSetAtPosition(VECTOR *pos, char *tgt, int *ccx, int *ccz)
{
	int cz;
	int cx;

	int rz;
	int rx;

	cx = (pos->vx + units_across_halved) / MAP_CELL_SIZE;
	cz = (pos->vz + units_down_halved) / MAP_CELL_SIZE;

	*ccx = cx;
	*ccz = cz;

	rx = cx / MAP_REGION_SIZE;
	rz = cz / MAP_REGION_SIZE;

	int barrel_region_x = (rx & 1);
	int barrel_region_z = (rz & 1);

	GetPVSRegionCell2(
		barrel_region_x + barrel_region_z * 2,
		rx + rz * (cells_across / MAP_REGION_SIZE),
		(cz - rz * MAP_REGION_SIZE) * MAP_REGION_SIZE + cx - rx * MAP_REGION_SIZE,
		tgt);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PVSDecode(char *output /*$s2*/, char *celldata /*$s3*/, unsigned short sz /*$s0*/, int havanaCorruptCellBodge /*$s4*/)
 // line 824, offset 0x0005cfa8
	/* begin block 1 */
		// Start line: 825
		// Start offset: 0x0005CFA8
		// Variables:
	// 		char *decodeBuf; // $s1

		/* begin block 1.1 */
			// Start line: 825
			// Start offset: 0x0005CFA8
			// Variables:
		// 		int pixelIndex; // $t0
		// 		int i; // $a0
		// 		int ni; // $a3
			// Labels:
			//		0x000008EC	spod

			/* begin block 1.1.1 */
				// Start line: 835
				// Start offset: 0x0005CFF4
			/* end block 1.1.1 */
			// End offset: 0x0005CFF4
			// End Line: 835

			/* begin block 1.1.2 */
				// Start line: 842
				// Start offset: 0x0005D03C
				// Variables:
			// 		int symIndex; // $a2
			// 		int sym; // $a0

				/* begin block 1.1.2.1 */
					// Start line: 825
					// Start offset: 0x0005D0A8
					// Variables:
				// 		unsigned char *pt; // $v0
				/* end block 1.1.2.1 */
				// End offset: 0x0005D0A8
				// End Line: 825

				/* begin block 1.1.2.2 */
					// Start line: 825
					// Start offset: 0x0005D0BC
					// Variables:
				// 		unsigned char *pt; // $v0
				/* end block 1.1.2.2 */
				// End offset: 0x0005D0BC
				// End Line: 825
			/* end block 1.1.2 */
			// End offset: 0x0005D104
			// End Line: 869
		/* end block 1.1 */
		// End offset: 0x0005D110
		// End Line: 872

		/* begin block 1.2 */
			// Start line: 873
			// Start offset: 0x0005D110
			// Variables:
		// 		int i; // $a2
		// 		int j; // $v1
		// 		int sz; // $a3
		// 		char *op; // $a1
		/* end block 1.2 */
		// End offset: 0x0005D1E4
		// End Line: 904

		/* begin block 1.3 */
			// Start line: 906
			// Start offset: 0x0005D1E4
			// Variables:
		// 		int i; // $v1
		/* end block 1.3 */
		// End offset: 0x0005D224
		// End Line: 911
	/* end block 1 */
	// End offset: 0x0005D224
	// End Line: 913

	/* begin block 2 */
		// Start line: 1725
	/* end block 2 */
	// End Line: 1726

	/* begin block 3 */
		// Start line: 1806
	/* end block 3 */
	// End Line: 1807

unsigned char nybblearray[512] = { 0 };

char* PVS_Buffers[4] = { 0 };
int pvsSize[4] = { 0, 0, 0, 0 };
unsigned char *PVSEncodeTable = NULL;

// [D] [T]
void PVSDecode(char *output, char *celldata, ushort sz, int havanaCorruptCellBodge)
{
	unsigned char scratchPad[1024];

	int pixelIndex;
	unsigned char* decodebuf;
	unsigned char* op;
	int i, j;
	int symIndex;
	int size;

	decodebuf = scratchPad;
	ClearMem((char*)decodebuf,pvs_square_sq);

	// decode byte-swapped array
	i = 0;
	while (i < sz)
	{
		((ushort*)nybblearray)[i] = SW_SHORT((unsigned char)celldata[i], (unsigned char)celldata[i] >> 4) & 0xf0f;
		i++;
	}

	pixelIndex = 0;
	symIndex = 0;
	i = 0;

	// decompress image
	while (i < sz * 2)
	{
		int ni;
		int sym;

		ni = nybblearray[i];
		i++;

		if (ni < 12)
		{
			symIndex = ni * 2;
		spod:
			sym = SW_SHORT(PVSEncodeTable[symIndex], PVSEncodeTable[symIndex + 1]);
		}
		else
		{
			if (i == sz*2)
				break;

			sym = (ni & 3) * 16 + nybblearray[i];
			i++;

			if (sym < 60)
			{
				symIndex = sym * 2 + 24;
				goto spod;
			}

			sym = ((sym & 3) * 16 + nybblearray[i]) * 16 + nybblearray[i+1];
			i += 2;
		}

		pixelIndex += (sym >> 1);
		decodebuf[pixelIndex] = 1;
		pixelIndex++;

		if ((sym & 1) != 0)
		{
			decodebuf[pixelIndex] = 1;
			pixelIndex++;
		}
	}

	if (havanaCorruptCellBodge == 0) 
		decodebuf[pvs_square_sq-1] ^= 1;

	size = pvs_square - 2;
	
	op = (decodebuf - 1) + (size * pvs_square + pvs_square);
	i = size;
	while (i >= 0) 
	{
		i--;
		j = pvs_square;
		while (j > 0)
		{
			*op = *op ^ op[pvs_square];
			j--;
			op--;
		}
	}

	size = pvs_square - 1;
	op = (decodebuf - 2) + (size * pvs_square + pvs_square);
	i = size;

	while (i >= 0) 
	{
		j = pvs_square-2;
		while (j >= 0) 
		{
			*op = *op ^ op[1];
			j--;
			op--;
		}
		i--;
		op--;
	}

#if 0
	printf("=========================\n");
	for (i = 0; i < pvs_square; i++)
	{
		char line[64];
		memcpy(line, (char*)decodebuf + i * pvs_square, pvs_square);
		for (j = 0; j < pvs_square; j++)
		{
			if (line[j] == 0)
				line[j] = '.';
			else
				line[j] = 'O';
		}
		line[j] = 0;
		printf("%s\n", line);
	}
	printf("=========================\n");
#endif
	memcpy(output, decodebuf, pvs_square_sq-1);	// 110*4
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetPVSRegionCell2(int source_region /*$a0*/, int region /*$a1*/, int cell /*$t2*/, char *output /*$a3*/)
 // line 928, offset 0x0005d224
	/* begin block 1 */
		// Start line: 929
		// Start offset: 0x0005D224
		// Variables:
	// 		char *bp; // $a2
	// 		char *tbp; // $a1
	// 		int j; // $v1
	// 		unsigned short length; // $t0

		/* begin block 1.1 */
			// Start line: 945
			// Start offset: 0x0005D29C
			// Variables:
		// 		unsigned char *pt; // $a0
		/* end block 1.1 */
		// End offset: 0x0005D29C
		// End Line: 945

		/* begin block 1.2 */
			// Start line: 945
			// Start offset: 0x0005D29C
		/* end block 1.2 */
		// End offset: 0x0005D29C
		// End Line: 945

		/* begin block 1.3 */
			// Start line: 929
			// Start offset: 0x0005D32C
			// Variables:
		// 		char *output; // $a0

			/* begin block 1.3.1 */
				// Start line: 929
				// Start offset: 0x0005D32C
				// Variables:
			// 		int k; // $v1
			/* end block 1.3.1 */
			// End offset: 0x0005D35C
			// End Line: 929
		/* end block 1.3 */
		// End offset: 0x0005D35C
		// End Line: 929
	/* end block 1 */
	// End offset: 0x0005D35C
	// End Line: 963

	/* begin block 2 */
		// Start line: 2027
	/* end block 2 */
	// End Line: 2028

	/* begin block 3 */
		// Start line: 2029
	/* end block 3 */
	// End Line: 2030

	/* begin block 4 */
		// Start line: 2045
	/* end block 4 */
	// End Line: 2046

	/* begin block 5 */
		// Start line: 2054
	/* end block 5 */
	// End Line: 2055

// [D] [T]
void GetPVSRegionCell2(int source_region, int region, int cell, char *output)
{
	int k;
	uint havanaCorruptCellBodge;
	char *tbp;
	char *bp;
	ushort length;

	if (gDriver1Level)
	{
		// don't draw non-loaded regions
		for (k = 0; k < pvs_square_sq; k++)
			output[k] = 1;

		return;
	}

	if (regions_unpacked[source_region] == region && loading_region[source_region] == -1) 
	{
		bp = PVS_Buffers[source_region];
		PVSEncodeTable = (unsigned char *)(bp + 0x802);
		tbp = bp + cell * 2;

		length = SW_SHORT((unsigned char)tbp[2], (unsigned char)tbp[3]) - SW_SHORT((unsigned char)tbp[0], (unsigned char)tbp[1]) & 0xffff;

		if (length == 0) 
		{
			for (k = 0; k < pvs_square_sq; k++)
				output[k] = 1;
		}
		else 
		{
			havanaCorruptCellBodge = 0;
			if (regions_unpacked[source_region] == 158 && cell == 168) 
				havanaCorruptCellBodge = (GameLevel == 1);

			PVSDecode(output, bp + SW_SHORT((unsigned char)tbp[0], (unsigned char)tbp[1]), length, havanaCorruptCellBodge);
		}
	}
	else 
	{
		// don't draw non-loaded regions
		for (k = 0; k < pvs_square_sq; k++)
			output[k] = 0;
	}
}





