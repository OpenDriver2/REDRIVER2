#include "driver2.h"
#include "dr2roads.h"

#include "system.h"
#include "map.h"
#include "event.h"
#include "convert.h"
#include "cutscene.h"
#include "mission.h"
#include "handling.h"

sdPlane default_plane = { 0, 0, 0, 0, 2048 };

sdPlane sea_plane = { 9, 0, 16384, 0, 2048 }; // a default surface if FindSurfaceD2 fails

sdPlane* GetSeaPlane()
{
#ifdef DEBUG_OPTIONS
	return playerghost ? &default_plane : &sea_plane;
#else
	return &sea_plane;
#endif
}

ROAD_MAP_LUMP_DATA roadMapLumpData;
short* RoadMapDataRegions[4];

int NumTempJunctions = 0;
int NumDriver2Junctions = 0;
DRIVER2_JUNCTION *Driver2JunctionsPtr = NULL;
u_int* Driver2TempJunctionsPtr = NULL;

DRIVER2_CURVE *Driver2CurvesPtr = NULL;
int NumDriver2Curves = 0;

int NumDriver2Straights = 0;
DRIVER2_STRAIGHT *Driver2StraightsPtr = NULL;

int gDisableChicagoBridges = 0;

const short ChicagoBridgeRoads1[] = {
	434,
	433,
	65,
	64,
	63,
	62,
	61,
	457,
	458,
	488,
	-1,
};

const short ChicagoBridgeRoads2[] = {
	336,
	319,
	297,
	284,
	260,
	254,
	222,
	-1,
};

const short ChicagoBridgeRoads3[] = {
	562,
	570,
	582,
	586,
	597,
	600,
	622,
	623,
	-1,
};

// [A] Chicago roads
const short* ChicagoBridgeRoads[] = {
	// Goose island
	ChicagoBridgeRoads1,

	// Downtown
	ChicagoBridgeRoads2,

	// Downtown 2
	ChicagoBridgeRoads3,
};

// [A] custom function for working with roads in very optimized way
int GetSurfaceRoadInfo(DRIVER2_ROAD_INFO* outRoadInfo, int surfId)
{
	DRIVER2_CURVE* curve;
	DRIVER2_STRAIGHT* straight;

	ClearMem((char*)outRoadInfo, sizeof(DRIVER2_ROAD_INFO));
	outRoadInfo->surfId = surfId;

	if(IS_CURVED_SURFACE(surfId))
	{
		outRoadInfo->curve = curve = GET_CURVE(surfId);
		outRoadInfo->ConnectIdx = &curve->ConnectIdx;
		outRoadInfo->NumLanes = curve->NumLanes;
		outRoadInfo->LaneDirs = curve->LaneDirs;
		outRoadInfo->AILanes = curve->AILanes;
		return 1;
	}
	else if (IS_STRAIGHT_SURFACE(surfId))
	{
		outRoadInfo->straight = straight = GET_STRAIGHT(surfId);
		outRoadInfo->ConnectIdx = &straight->ConnectIdx;
		outRoadInfo->NumLanes = straight->NumLanes;
		outRoadInfo->LaneDirs = straight->LaneDirs;
		outRoadInfo->AILanes = straight->AILanes;
		return 1;
	}

	return 0;
}

// [A]
int GetLaneByPositionOnRoad(DRIVER2_ROAD_INFO* roadInfo, VECTOR* pos)
{
	int dx, dz, lane;
	int lane_count;

	lane_count = ROAD_WIDTH_IN_LANES(roadInfo);
	lane = -1;

	if (roadInfo->straight)
	{
		dx = pos->vx - roadInfo->straight->Midx;
		dz = pos->vz - roadInfo->straight->Midz;

		lane = ROAD_LANES_COUNT(roadInfo) - (FIXEDH(dx * rcossin_tbl[(roadInfo->straight->angle & 0xfff) * 2 + 1] -
													dz * rcossin_tbl[(roadInfo->straight->angle & 0xfff) * 2]) + 512 >> 9);

		if (lane < 0)
			lane = 0;

		if (lane_count <= lane)
			lane = lane_count - 1;
	}
	else if(roadInfo->curve)
	{
		dx = pos->vx - roadInfo->curve->Midx;
		dz = pos->vz - roadInfo->curve->Midz;

		lane = (SquareRoot0(dx * dx + dz * dz) >> 9) - roadInfo->curve->inside * 2;
	
		if (lane < 0)
			lane = 0;

		if (lane >= lane_count)
			lane = lane_count - 1;
	}

	return lane;
}

// [D] [T]
void ProcessStraightsDriver2Lump(char *lump_file, int lump_size)
{
	Getlong((char *)&NumDriver2Straights, lump_file);
	Driver2StraightsPtr = (DRIVER2_STRAIGHT *)(lump_file + 4);

	// [A] patch chicago roads
	if (GameLevel == 0 && gDisableChicagoBridges)
	{
		DRIVER2_STRAIGHT* str;
		int grp, i, j;
		int numLanes;

		for (grp = 0; grp < 3; grp++)
		{
			// don't activate those roads in Caine's Compound
			if(grp == 0 && gCurrentMissionNumber == 7)
				continue;

			i = 0;
			while (ChicagoBridgeRoads[grp][i] >= 0)
			{
				str = GET_STRAIGHT(ChicagoBridgeRoads[grp][i]);
				numLanes = ROAD_LANES_COUNT(str);

				for (j = 0; j < numLanes; j++)
				{
					if ((numLanes & 1) && j == numLanes / 2)
						continue;

					str->AILanes |= 1 << j;
				}
				i++;
			}
		}
	}
}

// [D] [T]
void ProcessCurvesDriver2Lump(char *lump_file, int lump_size)
{
	Getlong((char *)&NumDriver2Curves, lump_file);
	Driver2CurvesPtr = (DRIVER2_CURVE *)(lump_file + 4);
}

// [D] [T]
void ProcessJunctionsDriver2Lump(char *lump_file, int lump_size, int fix)
{
	int loop;
	DRIVER2_JUNCTION *p;
	OLD_DRIVER2_JUNCTION *old;
	int i;

	Getlong((char *)&NumDriver2Junctions, lump_file);

	p = (DRIVER2_JUNCTION *)(lump_file + 4);
	Driver2JunctionsPtr = p;

	if (fix)	// this allows to load Alpha 1.6 LEV found in D2 demo
	{
		loop = 0;
		old = (OLD_DRIVER2_JUNCTION *)(lump_file + 4);

		for (loop = 0; loop < NumDriver2Junctions; loop++)
		{
			p->flags = old->flags;
			for (i = 0; i < 4; i++)
				p->ExitIdx[i] = old->ExitIdx[i];

			p++;
			old++;
		}
	}
}

// [D] [T]
int sdHeightOnPlane(VECTOR *pos, sdPlane *plane)
{
	int angle;
	int i, d;
	DRIVER2_CURVE *curve;
	int lx;
	int ly;

	if (plane != NULL)
	{
		d = plane->d;

		if ((d >> 1 ^ d) & 0x40000000) 
			return d ^ 0x40000000;

		if ((plane->surface & 0xe000U) == 0x4000 && plane->b == 0)
		{
			// calculate curve point
			curve = Driver2CurvesPtr + ((plane->surface & 0x1fff) - 32);
			angle = ratan2(curve->Midz - pos->vz, curve->Midx - pos->vx);

			return ((curve->gradient * (angle + 2048 & 0xfff)) / ONE) - curve->height;
		}

		i = plane->b;

		if (i != 0)
		{
			if (i == 0x4000)
				return -d;

			lx = (int)plane->a * ((pos->vx - 512 & 0xffff) + 512);
			ly = (int)plane->c * ((pos->vz - 512 & 0xffff) + 512);

			return -d - (lx + ly) / i;
		}
	}

	return 0;
}

// [D] [T]
short* sdGetBSP(sdNode *node, XYPAIR *pos)
{
	int ang, dot;

	while (node->value < 0) // & 0x80000000U)
	{
		ang = (node->n.angle & 0xfff) * 2;
		dot = pos->y * rcossin_tbl[ang + 1] - pos->x * rcossin_tbl[ang];

		if (dot < node->n.dist * 4096)
			node++;
		else
			node += node->n.offset;
	} 

	return (short *)node;
}

int sdLevel = 0; // pathfinding value

// [D] [T]
sdPlane* sdGetCell(VECTOR *pos)
{
	int nextLevel;
	sdPlane *plane;
	short *surface;
	short *BSPSurface;
	short *buffer;
	XYPAIR cell;
	XYPAIR cellPos;

	sdLevel = 0;

	cellPos.x = pos->vx - 512;
	cellPos.y = pos->vz - 512;

	// [A] WARNING!
	// retail version of game with exe dated before 20th October 2000 (so called 1.0) is only supported
	// the later version of the game do have problem with height or BSP, so Havana's secret base ground is not solid

	// Oct 17 2000:			RoadMapDataRegions[(v4 >> 16) & 1 ^ (((cells_across >> 6) & 1) + (((v3 - 512) >> 15) & 2)) ^ (cells_down >> 5) & 2];
	// Oct 29 2000:			RoadMapDataRegions[(cellPos.x >> 16) & 1 ^ (((cellPos.y >> 15) & 2) + 1) ^ 2];

	buffer = RoadMapDataRegions[(cellPos.x >> 16 & 1U) ^ (cells_across / (MAP_REGION_SIZE*2) & 1U) + (cellPos.y >> 15 & 2U) ^ (cells_down / MAP_REGION_SIZE) & 2U];
	//buffer = RoadMapDataRegions[(cellPos.x >> 16) & 1 ^ (((cellPos.y >> 15) & 2) + 1) ^ 2];

	plane = NULL;
	
	if (*buffer == 2) 
	{
		short* bspData = (short*)((char*)buffer + buffer[2]);
		sdNode* nodeData = (sdNode*)((char*)buffer + buffer[3]);
		sdPlane* planeData = (sdPlane*)((char*)buffer + buffer[1]);
		
		surface = &buffer[(cellPos.x >> 10 & 0x3fU) + 
						  (cellPos.y >> 10 & 0x3fU) * MAP_REGION_SIZE*2 + 4];

		// no surface poitners
		if (*surface == -1)
			return GetSeaPlane();

		// check surface has overlapping planes flag (aka multiple levels)
		if ((*surface & 0x6000) == 0x2000)
		{
			surface = &bspData[(*surface & 0x1fff)];
			do {
				if(-256 - pos->vy > *surface)
				{
					surface += 2;
					sdLevel++;
				}
				else
					break;
			} while (*surface != -0x8000);
			
			surface += 1;
		}

		// iterate surfaces if BSP
		do {
			nextLevel = 0;

			// check if it's has BSP properties
			if (*surface & 0x4000)
			{
				cell.x = cellPos.x & 0x3ff;
				cell.y = cellPos.y & 0x3ff;
				
				// get closest surface by BSP lookup
				BSPSurface = sdGetBSP(&nodeData[(*surface & 0x3fff)], &cell);

				if (*BSPSurface == 0x7fff)
				{
					sdLevel++;
					nextLevel = 1;
					
					BSPSurface = surface + 2; // get to the next node
				}

				surface = BSPSurface;
			}
		} while (nextLevel);

		plane = &planeData[*surface];

		if (((int)plane & 3) == 0 && *(int *)plane != -1) 
		{
			if (plane->surface - 16U < 16)
				plane = EventSurface(pos, plane);
		}
		else 
			plane = GetSeaPlane();
	}

	return plane;
}

// [D] [T]
int GetSurfaceIndex(VECTOR *pos)
{
	sdPlane *plane = sdGetCell(pos);

	if (plane == NULL)
		return -32;

	return plane->surface - 32;
}

// [D] [T]
sdPlane * FindRoadInBSP(sdNode *node, sdPlane *base)
{
	sdPlane *plane;

	while (true)
	{
		if (node->value > -1)
		{
			base += node->value;
			return (base->surface < 32) ? NULL : base;
		}

		plane = FindRoadInBSP(node + 1, base);

		if (plane != NULL)
			break;

		node += node->n.offset;
	}

	return plane;
}

// [D] [T]
int RoadInCell(VECTOR *pos)
{
	int moreLevels;
	sdPlane *plane;
	short *check;
	short *buffer;
	XYPAIR cellPos;

	cellPos.x = pos->vx - 512;
	cellPos.y = pos->vz - 512;
	buffer = RoadMapDataRegions[cellPos.x >> 0x10 & 1U ^ (cells_across >> 6 & 1U) + (cellPos.y >> 0xf & 2U) ^ cells_down >> 5 & 2U];

	if (*buffer == 2)
	{
		check = (short *)(buffer + (cellPos.x >> 10 & 0x3fU) + (cellPos.y >> 10 & 0x3fU) * 64 + 4);

		if (*check == -1)
			return -1;

		if (*check & 0x8000)
		{
			moreLevels = (*check & 0x6000) == 0x2000;

			if (moreLevels)
				check = (short *)((int)buffer + (*check & 0x1fff) * sizeof(short) + buffer[2] + 2);

			do
			{
				if (moreLevels && check[-1] == 0x8000)
					moreLevels = 0;

				if (*check & 0x4000)
				{
					plane = FindRoadInBSP((_sdNode *)((int)buffer + (*check & 0x3fff) * sizeof(_sdNode) + buffer[3]), (sdPlane *)((int)buffer + buffer[1]));

					if (plane != NULL)
						break;
				}
				else
				{
					plane = (sdPlane *)((int)buffer + buffer[1]) + *check;

					if (plane->surface > 31)
						break;
				}

				check += 2;
			} while (true);
		}
		else if ((*check & 0xE000) == 0)
		{
			plane = (sdPlane *)((int)buffer + *check * sizeof(sdPlane) + buffer[1]);
		}
		else
			plane = NULL;

		if (plane == NULL)
			return -1;

		if (plane->surface > 31)
		{
			pos->vy = sdHeightOnPlane(pos, plane) + 256;
			return plane->surface - 32;
		}
	}

	return -1;
}

// [D] [T]
int MapHeight(VECTOR *pos)
{
	sdPlane *plane;

	plane = sdGetCell(pos);

	if (plane)
		return sdHeightOnPlane(pos, plane);

	return 0;
}

// [D] [T]
int FindSurfaceD2(VECTOR *pos, VECTOR *normal, VECTOR *out, sdPlane **plane)
{
	*plane = sdGetCell(pos);
	out->vx = pos->vx;
	out->vz = pos->vz;
	out->vy = sdHeightOnPlane(pos, *plane);

	if (*plane == NULL || (*plane)->b == 0)
	{
		normal->vx = 0;
		normal->vy = 4096;
		normal->vz = 0;
	}
	else
	{
		normal->vx = (int)(*plane)->a >> 2; // [A] was (int)((uint)(ushort)(*plane)->a << 0x10) >> 0x12;
		normal->vy = (int)(*plane)->b >> 2;
		normal->vz = (int)(*plane)->c >> 2;
	}

	if (*plane == NULL)
	{
		return 4096;
	}
	else if ((*plane)->surface == 4)
	{
		// [A] Rev 1.1 doesn't have this cutscene hack
		if (gInGameCutsceneActive && gCurrentMissionNumber == 23 && gInGameCutsceneID == 0)
			out->vy += rcossin_tbl[(pos->vx + pos->vz) * 4 & 0x1fff] >> 9;
		else
			out->vy += (rcossin_tbl[(pos->vx + pos->vz) * 4 & 0x1fff] >> 8) / 3;

		return 2048;
	}

	return 4096;
}