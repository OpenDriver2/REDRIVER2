#include "driver2.h"
#include "cell.h"
#include "system.h"
#include "map.h"
#include "spool.h"

int cell_object_index = 0;
CELL_OBJECT cell_object_buffer[1024];

u_char cell_object_computed_values[2048];

extern u_char NumPlayers;

// [D] [T]
void ClearCopUsage(void)
{
	ClearMem((char *)cell_object_computed_values, sizeof_cell_object_computed_values);
}

// [D] [T]
PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, CELL_ITERATOR *pci, int use_computed, int level)
{
	PACKED_CELL_OBJECT *ppco;

	u_int value;
	u_short index;
	u_short num;
	int cbr;
	CELL_DATA* cell;
	ushort ptr;

	index = (cellx / MAP_REGION_SIZE & 1) + (cellz / MAP_REGION_SIZE & 1) * 2;

#ifdef PSX
	if (NumPlayers == 2)
#endif // else do this check always
	{
		// [A] don't draw loading region
		if (loading_region[index] != -1)
			return NULL;
		
		if (RoadMapRegions[index] != (cellx / MAP_REGION_SIZE) + (cellz / MAP_REGION_SIZE) * (cells_across / MAP_REGION_SIZE))
			return NULL;
	}

	cbr = (cellz % MAP_REGION_SIZE) * MAP_REGION_SIZE + index * (MAP_REGION_SIZE*MAP_REGION_SIZE) + (cellx % MAP_REGION_SIZE);
	
	ptr = cell_ptrs[cbr];
	
	if (ptr == 0xffff)
		return NULL;

	cell = &cells[ptr];

	if (level == -1) 
	{
		if (cell->num & 0x4000)
			return NULL;
	}
	else 
	{
		/*
			Data looks like this:

			45,34,773,456    - default list of cell objects
			0x4000 | 100     - list 1 header - type 100
			70,378,4557      - objects of list 1
			0x4000 | 14      - list 2 header - type 14
			8767,555,445,223 - objects of list 2
			0x8000           - end of cell objects
		*/

		level |= 0x4000;
		while (cell->num != level)	// skip until we reach the needed list header
		{
			cell++;
			if (cell->num & 0x8000)	// end of cell objects?
				return NULL;
		}
		cell++;
	}

	pci->nearCell.x = (cellx - (cells_across / 2)) * MAP_CELL_SIZE;
	pci->nearCell.z = (cellz - (cells_down / 2)) * MAP_CELL_SIZE;
	pci->use_computed = use_computed;

	pci->pcd = cell;

	num = cell->num & 16383;
	ppco = &cell_objects[num];

	if (ppco->value == 0xffff && (ppco->pos.vy & 1)) 
	{
		ppco = GetNextPackedCop(pci);
	}
	else if (use_computed)
	{
		value = 1 << (num & 7);

		if (cell_object_computed_values[num / 8] & value) // get cached value
		{
			ppco = GetNextPackedCop(pci);
			pci->ppco = ppco;

			return ppco;
		}

		cell_object_computed_values[num / 8] |= value;
	}

	pci->ppco = ppco;

	return ppco;
}


// [D] [T]
PACKED_CELL_OBJECT* GetNextPackedCop(CELL_ITERATOR* pci)
{
	ushort num;
	u_int value;
	PACKED_CELL_OBJECT* ppco;
	CELL_DATA* celld;

	celld = pci->pcd;
	
	do {
		do {
			if (celld->num & 0x8000)	// end of cell objects?
				return NULL;

			celld++;
			num = celld->num;

			if (num & 0x4000)			// end of list?
				return NULL;

			num &= 16383;
			ppco = &cell_objects[num];
		} while (ppco->value == 0xffff && (ppco->pos.vy & 1));
		
		if (!pci->use_computed)
			break;

		value = 1 << (num & 7);
		if ((cell_object_computed_values[num / 8] & value) == 0)
		{
			cell_object_computed_values[num / 8] |= value;
			break;
		}
	} while (true);

	pci->pcd = celld;
	pci->ppco = ppco;

	return ppco;
}


// [D] [T]
CELL_OBJECT* UnpackCellObject(PACKED_CELL_OBJECT* ppco, XZPAIR* near)
{
	int newIndex;
	CELL_OBJECT* pco;

	if (ppco == NULL)
		return NULL;

	pco = &cell_object_buffer[newIndex = cell_object_index];
	cell_object_index = newIndex + 1 & 1023;

	QuickUnpackCellObject(ppco, near, pco);

	return pco;
}