#include "driver2.h"
#include "d2mapasm.h"
#include "C/map.h"
#include "C/dr2roads.h"

uint region_buffer_xor = 0;
uint sdSelfModifyingCode = 8;

extern int sdLevel;
extern short* RoadMapDataRegions[4];

extern short* sdGetBSP(sdNode* node, XYPAIR* pos);
extern sdPlane* FindRoadInBSP(sdNode* node, sdPlane* base);
extern int sdHeightOnPlane(VECTOR* pos, sdPlane* plane);

// [D]
// DO NOT USE IT!
sdPlane* sdGetCell_asm(int param_1, short** roadMapData, int pos_x, int pos_z, int pos_y, int _sdLevel)
{
	sdPlane* plane;
	int surfHeight;
	ushort* BSPSurface;
	XYPAIR cell;
	ushort* surface;
	short* HSurface;
	short* buffer;
	bool nextLevel;

	buffer = *(short**)((param_1 ^ sdSelfModifyingCode) + (int)roadMapData);

	cell.x = pos_x & 1023;
	cell.y = pos_z & 1023;

	surface = (ushort*)((int)buffer + (pos_z >> 3 & 0x1f80U) + (pos_x >> 9 & 0x7eU) + 8);

	if (*surface == 0xffff)
	{
		plane = NULL;
	}
	else
	{
		if ((*surface & 0x6000) == 0x2000)
		{
			HSurface = (short*)((int)buffer + (*surface & 0x1fff) * 2 + (int)buffer[2]);
			surfHeight = (int)*HSurface;
			do {
				if (-256 - pos_y <= surfHeight)
					break;

				surfHeight = (int)HSurface[2];
				HSurface = HSurface + 2;
				_sdLevel = _sdLevel + 1;
			} while (surfHeight != -0x8000);

			surface = (ushort*)(HSurface + 1);
		}
		do
		{
			nextLevel = false;
			BSPSurface = surface;

			if ((*surface & 0x4000) != 0)
			{
				BSPSurface = (ushort*)sdGetBSP((_sdNode*)((int)buffer + (*surface & 0x1fff) * 4 + (int)buffer[3]), &cell);
				if (*BSPSurface == 0x7fff)
				{
					_sdLevel = _sdLevel + 1;
					nextLevel = true;
					BSPSurface = surface + 2;
				}
			}
			surface = BSPSurface;
		} while (nextLevel);

		plane = (sdPlane*)((int)buffer + (short)*BSPSurface * sizeof(sdPlane) + (int)buffer[1]);
	}

	sdLevel = _sdLevel;

	return plane;
}

// [D] [T]
sdPlane* sdGetCell_alpha16(VECTOR* pos)
{
	sdPlane* plane;
	int iVar1;
	short* BSPSurface;
	int cellPos_x;
	int cellPos_z;
	XYPAIR cell;
	short* surface;
	short* HSurface;
	short* buffer;
	bool nextLevel;

	cellPos_x = pos->vx - 512;
	cellPos_z = pos->vz - 512;

	buffer = *(short**)((int)RoadMapDataRegions + (cellPos_x >> 14 & 4U ^ cellPos_z >> 13 & 8U ^ sdSelfModifyingCode));	// pointless, but i'll keep it there
	
	cell.x = cellPos_x & 1023;
	cell.y = cellPos_z & 1023;

	surface = &buffer[(cellPos_x >> 10 & 0x3fU) + (cellPos_z >> 10 & 0x3fU) * MAP_REGION_SIZE * 2 + 4];

	if (*surface == -1) 
	{
		plane = NULL;
	}
	else 
	{
		sdPlane* planeData = (sdPlane*)((char*)buffer + buffer[1]);
		short* bspData = (short*)((char*)buffer + buffer[2]);
		sdNode* nodeData = (sdNode*)((char*)buffer + buffer[3]);

		// check surface has overlapping planes flag (aka multiple levels)
		if (*surface & 0x8000)
		{
			surface = &bspData[*surface & 0x1fff];
			do {
				if (-256 - pos->vy > *surface)
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
			nextLevel = false;
			BSPSurface = surface;

			// check if it's has BSP properties
			// basically it determines surface bounds
			if (*surface & 0x4000) 
			{
				BSPSurface = sdGetBSP(&nodeData[*surface & 0x1fff], &cell);
				if (*BSPSurface == 0x7fff) 
				{
					nextLevel = true;
					BSPSurface = surface + 2;
				}
			}
			surface = BSPSurface;
		} while (nextLevel);

		plane = &planeData[*BSPSurface];
	}
	return plane;
}

// [D] [T]
int RoadInCell_alpha16(VECTOR *pos)
{
	int cellPos_x;
	int cellPos_z;
	
	short* check;
	
	sdPlane* plane;
	short* buffer;
	bool moreLevels;

	cellPos_x = pos->vx - 512;
	cellPos_z = pos->vz - 512;
	
	buffer = RoadMapDataRegions[(cellPos_x >> 16 & 1U) ^ (regions_across / 2 & 1) +
								(cellPos_z >> 15 & 2U) ^ (regions_down & 2)];
	
	if (*buffer == 2) 
	{
		sdPlane* planeData = (sdPlane*)((char*)buffer + buffer[1]);
		short* bspData = (short*)((char*)buffer + buffer[2]);
		sdNode* nodeData = (sdNode*)((char*)buffer + buffer[3]);
		
		check = &buffer[(cellPos_x >> 10 & 0x3fU) + 
						(cellPos_z >> 10 & 0x3fU) * MAP_REGION_SIZE * 2 + 4];

		if (*check == -1)
			return -1;
		
		if (*check & 0xE000)
		{
			if (*check & 0x2000)
			{
				// check surface has overlapping planes flag (aka multiple levels)
				moreLevels = (*check & 0x8000) != 0;

				if (moreLevels)
					check = &bspData[(*check & 0x1fff) + 1];

				do
				{
					if (moreLevels && check[-1] == -0x8000)
						moreLevels = 0;

					// check if it's has BSP properties
					// basically it determines surface bounds
					if (*check & 0x4000)
					{
						sdNode* search = &nodeData[*check & 0x1fff];

						while (search->value < 0)
						{
							plane = FindRoadInBSP(search + 1, planeData);

							if (plane != NULL)
								break;

							search += search->n.offset;
						}

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
			else
			{
				plane = NULL;
			}
		}
		else 
		{
			plane = &planeData[*check];
		}
	
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