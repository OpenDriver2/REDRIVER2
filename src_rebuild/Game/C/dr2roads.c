#include "driver2.h"
#include "dr2roads.h"

#include "system.h"
#include "map.h"
#include "event.h"
#include "convert.h"
#include "mission.h"
#include "handling.h"
#include "main.h"
#include "ASM/d2mapasm.h"

sdPlane default_plane = { SURF_CONCRETE, 0, 0, 0, 2048 };

sdPlane sea_plane = { SURF_DEEPWATER, 0, 16384, 0, 2048 }; // a default surface if FindSurfaceD2 fails

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
	DRIVER2_JUNCTION* junction;

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
	else if (IS_JUNCTION_SURFACE(surfId))
	{
		junction = GET_JUNCTION(surfId);
		outRoadInfo->ConnectIdx = &junction->ExitIdx;
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

		lane = ROAD_LANES_COUNT(roadInfo) - (FIXEDH(dx * RCOS(roadInfo->straight->angle) -
													dz * RSIN(roadInfo->straight->angle)) + 512 >> 9);

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

	// [A] patch Chicago & Vegas roads
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
	else if (GameLevel == 2)
	{
#if ENABLE_GAME_FIXES
		int i;
		DRIVER2_STRAIGHT* str;

		Driver2StraightsPtr[348].ConnectIdx[2] = 8244;
		Driver2StraightsPtr[348].ConnectIdx[3] = 351;
#endif
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

	// [A] patch Vegas roads
	if (GameLevel == 2)
	{
		Driver2JunctionsPtr[8244 & 0x1fff].ExitIdx[1] = 348;
		Driver2JunctionsPtr[8244 & 0x1fff].ExitIdx[3] = 347;
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

	if (plane)
	{
		d = plane->d;

		if ((d >> 1 ^ d) & 0x40000000) 
			return d ^ 0x40000000;

		if ((plane->surface & 0xE000) == 0x4000 && plane->b == 0)
		{
			// calculate curve point
			curve = &Driver2CurvesPtr[(plane->surface & 0x1fff) - 32];
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
	int dot;

	while (node->value < 0) // & 0x80000000U)
	{
		dot = pos->y * RCOS(node->n.angle) - pos->x * RSIN(node->n.angle);

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

#ifndef PSX
	if (gDemoLevel)
		return sdGetCell_alpha16(pos);
#endif

	sdLevel = 0;

	cellPos.x = pos->vx - 512;
	cellPos.y = pos->vz - 512;

	cell.x = cellPos.x & 1023;
	cell.y = cellPos.y & 1023;

	buffer = RoadMapDataRegions[(cellPos.x >> 16 & 1) ^ (regions_across / 2 & 1) + 
								(cellPos.y >> 15 & 2) ^ (regions_down & 2)];

	// Alpha 1.6 code, works too; not widely tested yet
	//buffer = *(short**)((int)RoadMapDataRegions + (cellPos.x >> 14 & 4 ^ cellPos.y >> 13 & 8 ^ sdSelfModifyingCode));

	plane = GetSeaPlane();
	
	if (*buffer != 2)
		return &default_plane;
	
	sdPlane* planeData = (sdPlane*)((char*)buffer + buffer[1]);
	short* bspData = (short*)((char*)buffer + buffer[2]);
	sdNode* nodeData = (sdNode*)((char*)buffer + buffer[3]);
		
	surface = &buffer[(cellPos.x >> 10 & 63) + 
						(cellPos.y >> 10 & 63) * 64 + 4];

	// initial surface
	if (*surface == -1)
		return plane;

	// check surface has overlapping planes flag (aka multiple levels)
	if ((*surface & 0x6000) == 0x2000)
	{
		surface = &bspData[*surface & 0x1fff];
		do {
			if(-256 - pos->vy > *surface)
			{
				surface += 2;
				sdLevel++;
			}
			else
				break;
		} while (*surface != -0x8000); // end flag
			
		surface += 1;
	}

	// iterate surfaces if BSP
	do {
		nextLevel = 0;

		// check if it's has BSP properties
		// basically it determines surface bounds
		if (*surface & 0x4000)
		{				
			// get closest surface by BSP lookup
			BSPSurface = sdGetBSP(&nodeData[*surface & 0x3fff], &cell);

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

	do
	{
		if (node->value > -1)
		{
			base += node->value;
			return (base->surface < 32) ? NULL : base;
		}

		plane = FindRoadInBSP(node + 1, base);
		node += node->n.offset;
	} while (plane == NULL);

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

#ifndef PSX
	if (gDemoLevel)
	{
		return RoadInCell_alpha16(pos);
	}
#endif

	cellPos.x = pos->vx - 512;
	cellPos.y = pos->vz - 512;

	buffer = RoadMapDataRegions[(cellPos.x >> 16 & 1) ^ (regions_across / 2 & 1) + 
								(cellPos.y >> 15 & 2) ^ (regions_down & 2)];

	if (*buffer == 2)
	{
		sdPlane* planeData = (sdPlane*)((char*)buffer + buffer[1]);
		short* bspData = (short*)((char*)buffer + buffer[2]);
		sdNode* nodeData = (sdNode*)((char*)buffer + buffer[3]);

		check = &buffer[(cellPos.x >> 10 & 63) +
						(cellPos.y >> 10 & 63) * 64 + 4];

		if (*check == -1)
			return -1;

		if (*check & 0x8000)
		{
			moreLevels = (*check & 0x6000) == 0x2000;

			if (moreLevels)
				check = &bspData[(*check & 0x1fff) + 1];

			do
			{
				if (moreLevels && check[-1] == 0x8000)
					moreLevels = 0;

				if (*check & 0x4000)
				{
					plane = FindRoadInBSP(&nodeData[*check & 0x3fff], planeData);

					if (plane != NULL)
						break;
				}
				else
				{
					plane = &planeData[*check];

					if (plane->surface >= 32)
						break;
				}

				check += 2;
			} while (true);
		}
		else if (!(*check & 0xE000))
		{
			plane = &planeData[*check];
		}
		else
			plane = NULL;

		if (plane == NULL)
			return -1;

		if (plane->surface >= 32)
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
void FindSurfaceD2(VECTOR *pos, VECTOR *normal, VECTOR *out, sdPlane **plane)
{
	sdPlane* pl;
	pl = sdGetCell(pos);

	*plane = pl;
	out->vx = pos->vx;
	out->vz = pos->vz;
	out->vy = sdHeightOnPlane(pos, pl);

	if (pl == NULL || pl->b == 0)
	{
		normal->vx = 0;
		normal->vy = 4096;
		normal->vz = 0;
	}
	else
	{
		normal->vx = (int)pl->a >> 2;
		normal->vy = (int)pl->b >> 2;
		normal->vz = (int)pl->c >> 2;
	}
}