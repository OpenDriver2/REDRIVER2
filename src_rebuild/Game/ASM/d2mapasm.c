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

	buffer = *(short**)((int)RoadMapDataRegions + (cellPos_x >> 0xe & 4U ^ cellPos_z >> 0xd & 8U ^ sdSelfModifyingCode));	// pointless, but i'll keep it there

	cell.x = cellPos_x & 1023;
	cell.y = cellPos_z & 1023;

	surface = (short*)((int)buffer + (cellPos_z >> 3 & 0x1f80U) + (cellPos_x >> 9 & 0x7eU) + 8);

	if ((int)*surface == 0xffffffff) 
	{
		plane = NULL;
	}
	else 
	{
		if (((int)*surface & 0x8000U) != 0)
		{
			HSurface = (short*)((int)buffer + ((ushort)*surface & 0x1fff) * 2 + (int)buffer[2]);
			iVar1 = (int)*HSurface;
			do {
				if (-256 - pos->vy <= iVar1)
					break;
				iVar1 = (int)HSurface[2];
				HSurface = HSurface + 2;
			} while (iVar1 != -0x8000);
			surface = HSurface + 1;
		}

		do {
			nextLevel = false;
			BSPSurface = surface;
			if ((*surface & 0x4000U) != 0) 
			{
				BSPSurface = sdGetBSP((_sdNode*)((int)buffer + ((ushort)*surface & 0x1fff) * 4 + (int)buffer[3]), &cell);
				if (*BSPSurface == 0x7fff) 
				{
					nextLevel = true;
					BSPSurface = (short*)((ushort*)surface + 2);
				}
			}
			surface = BSPSurface;
		} while (nextLevel);

		plane = (sdPlane*)((int)buffer + *BSPSurface * 0xc + (int)buffer[1]);
	}
	return plane;
}

// [D] [T]
int RoadInCell_alpha16(VECTOR *pos)
{
	ushort uVar1;
	sdPlane* psVar2;
	int cellPos_x;
	ushort* check;
	int cellPos_z;
	uint uVar3;
	int* piVar4;
	sdPlane* plane;
	short* buffer;
	sdPlane* base;
	bool moreLevels;

	cellPos_x = pos->vx + -0x200;
	cellPos_z = pos->vz + -0x200;
	buffer = RoadMapDataRegions
		[cellPos_x >> 0x10 & 1U ^ (cells_across >> 6 & 1U) + (cellPos_z >> 0xf & 2U) ^
		cells_down >> 5 & 2U];
	if (*buffer == 2) {
		check = (ushort*)
			(buffer + (cellPos_x >> 10 & 0x3fU) + (cellPos_z >> 10 & 0x3fU) * 0x40 + 4);
		uVar3 = (short)*check;
		uVar1 = *check;
		if (uVar3 == 0xffffffff) {
			return -1;
		}
		if ((uVar1 & 0xe000) == 0) {
			plane = (sdPlane*)((int)buffer + uVar3 * 0xc + (int)buffer[1]);
		}
		else {
			if ((uVar1 & 0x2000) == 0) {
				plane = NULL;
			}
			else {
				moreLevels = (uVar3 & 0x8000) != 0;
				base = (sdPlane*)((int)buffer + (int)buffer[1]);
				if (moreLevels) {
					check = (ushort*)((int)buffer + (uVar1 & 0x1fff) * 2 + (int)buffer[2] + 2);
					goto LAB_000621a4;
				}
			LAB_000621b8:
				uVar1 = *check;
				check = check + 2;
				if ((uVar1 & 0x4000) == 0) {
					plane = base + (short)uVar1;
				}
				else {
					piVar4 = (int*)((int)buffer + (uVar1 & 0x1fff) * 4 + (int)buffer[3]);
					while (*piVar4 < 0) {
						psVar2 = FindRoadInBSP((sdNode*)(piVar4 + 1), base);
						if (psVar2 != NULL) goto LAB_00062240;
						piVar4 = piVar4 + ((*piVar4 << 1) >> 0x18);
					}
					psVar2 = base + *piVar4;
					plane = NULL;
					if (0x1f < psVar2->surface) {
					LAB_00062240:
						plane = psVar2;
					}
				}
				if (moreLevels) {
				LAB_000621a4:
					if (check[-1] == 0x8000) {
						moreLevels = false;
					}
					goto LAB_000621b8;
				}
			}
		}
		if (plane == NULL) {
			return -1;
		}
		if (0x1f < plane->surface) {
			cellPos_x = sdHeightOnPlane((VECTOR*)pos, plane);
			pos->vy = cellPos_x + 0x100;
			return plane->surface + -0x20;
		}
	}
	return -1;
}