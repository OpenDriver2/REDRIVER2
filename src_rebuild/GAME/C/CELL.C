#include "THISDUST.H"
#include "CELL.H"
#include "SYSTEM.H"
#include "MAP.H"
#include "MISSION.H"
#include "EVENT.H"
#include "SPOOL.H"
#include "DRAW.H"

int cell_object_index = 0;
CELL_OBJECT cell_object_buffer[1024];

// decompiled code
// original method signature: 
// void /*$ra*/ ClearCopUsage()
 // line 57, offset 0x00023dc0
	/* begin block 1 */
		// Start line: 254
	/* end block 1 */
	// End Line: 255

	/* begin block 2 */
		// Start line: 114
	/* end block 2 */
	// End Line: 115

	/* begin block 3 */
		// Start line: 256
	/* end block 3 */
	// End Line: 257

/* WARNING: Unknown calling convention yet parameter storage is locked */

unsigned char cell_object_computed_values[2048];

// [D] [T]
void ClearCopUsage(void)
{
	ClearMem((char *)cell_object_computed_values, sizeof_cell_object_computed_values);
}

// decompiled code
// original method signature: 
// struct PACKED_CELL_OBJECT * /*$ra*/ GetFirstPackedCop(int cellx /*$t3*/, int cellz /*$a1*/, struct CELL_ITERATOR *pci /*$a2*/, int use_computed /*$a3*/)
 // line 67, offset 0x00023bac
	/* begin block 1 */
		// Start line: 68
		// Start offset: 0x00023BAC
		// Variables:
	// 		struct PACKED_CELL_OBJECT *ppco; // $a1
	// 		unsigned short index; // $a0
	// 		unsigned short num; // $t0
	// 		int cbrx; // $t0
	// 		int cbrz; // $t1
	// 		int xoff; // $a0
	// 		int yoff; // $v0
	// 		int cbr; // $t2

		/* begin block 1.1 */
			// Start line: 101
			// Start offset: 0x00023C84
			// Variables:
		// 		int event; // $t0
		/* end block 1.1 */
		// End offset: 0x00023CC8
		// End Line: 110
	/* end block 1 */
	// End offset: 0x00023DC0
	// End Line: 142

	/* begin block 2 */
		// Start line: 134
	/* end block 2 */
	// End Line: 135

// [D] [T]
PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, CELL_ITERATOR *pci, int use_computed)
{
	PACKED_CELL_OBJECT *ppco;
	CELL_DATA *celld;
	uint value;
	unsigned short index;
	unsigned short num;
	int cbr;

	index = (cellx >> 5 & 1) + (cellz >> 5 & 1) * 2;

	if (NumPlayers == 2)
	{
		if (RoadMapRegions[index] != (cellx >> 5) + (cellz >> 5) * (cells_across >> 5))
			return NULL;
	}

	cbr = (cellz - (cellz & 0xffffffe0U)) * 32 + index * 1024 + (cellx - (cellx & 0xffffffe0U));

	if (cell_ptrs[cbr] == 0xffff)
	{
		return NULL;
	}

	pci->pcd = cells + cell_ptrs[cbr];

	num = pci->pcd->num;

	if (events.camera == 0) 
	{
		if (pci->pcd->num & 0x4000)
		{
			return NULL;
		}
	}
	else 
	{
		pci->pcd++;
		while (num != (events.draw | 0x4000))
		{
			if (pci->pcd->num & 0x8000)
				return NULL;

			num = pci->pcd->num;
			pci->pcd++;
		}
	}

	pci->nearCell.x = (cellx - (cells_across >> 1)) * 0x800;
	pci->nearCell.z = (cellz - (cells_down >> 1)) * 0x800;
	pci->use_computed = use_computed;

	num = pci->pcd->num;
	
	ppco = cell_objects + (num & 0x3fff);

	if (ppco->value == 0xffff && (ppco->pos.vy & 1) != 0) 
	{
		ppco = GetNextPackedCop(pci);
	}
	else if (use_computed != 0)
	{
		value = 1 << (num & 7) & 0xffff;

		if (cell_object_computed_values[(num & 0x3fff) >> 3] & value) // get cached value
		{
			ppco = GetNextPackedCop(pci);
			pci->ppco = ppco;

			return ppco;
		}


		cell_object_computed_values[(num & 0x3fff) >> 3] |= value;
	}

	pci->ppco = ppco;

	return ppco;
}


// decompiled code
// original method signature: 
// struct PACKED_CELL_OBJECT * /*$ra*/ GetNextPackedCop(struct CELL_ITERATOR *pci /*$a0*/)
 // line 813, offset 0x0003f5f0
	/* begin block 1 */
		// Start line: 814
		// Start offset: 0x0003F5F0
		// Variables:
	// 		struct PACKED_CELL_OBJECT *ppco; // $a3
	// 		unsigned short num; // $a1
	/* end block 1 */
	// End offset: 0x0003F6B0
	// End Line: 853

	/* begin block 2 */
		// Start line: 1812
	/* end block 2 */
	// End Line: 1813

	/* begin block 3 */
		// Start line: 1817
	/* end block 3 */
	// End Line: 1818

	/* begin block 4 */
		// Start line: 1821
	/* end block 4 */
	// End Line: 1822

// [D] [T]
PACKED_CELL_OBJECT* GetNextPackedCop(CELL_ITERATOR* pci)
{
	ushort num;
	uint value;
	PACKED_CELL_OBJECT* ppco;

	do {
		do {
			if (pci->pcd->num & 0x8000)
				return NULL;

			pci->pcd++;
			num = pci->pcd->num;

			if ((num & 0x4000) != 0)
				return NULL;

			ppco = cell_objects + (num & 0x3fff);
		} while (ppco->value == 0xffff && (ppco->pos.vy & 1) != 0);


		if (!pci->use_computed)
			break;

		value = 1 << (num & 7) & 0xffff;

		if ((cell_object_computed_values[(num & 0x3fff) >> 3] & value) == 0)
		{
			cell_object_computed_values[(num & 0x3fff) >> 3] |= value;
			break;
		}

	} while (true);

	pci->ppco = ppco;
	return ppco;
}



// decompiled code
// original method signature: 
// struct CELL_OBJECT * /*$ra*/ UnpackCellObject(struct PACKED_CELL_OBJECT *ppco /*$a3*/, struct XZPAIR *near /*$t0*/)
 // line 854, offset 0x000418e8
	/* begin block 1 */
		// Start line: 855
		// Start offset: 0x000418E8
		// Variables:
	// 		struct CELL_OBJECT *pco; // $a2
	/* end block 1 */
	// End offset: 0x000419A8
	// End Line: 870

	/* begin block 2 */
		// Start line: 4699
	/* end block 2 */
	// End Line: 4700

	/* begin block 3 */
		// Start line: 1708
	/* end block 3 */
	// End Line: 1709

// [D] [T]
CELL_OBJECT* UnpackCellObject(PACKED_CELL_OBJECT* ppco, XZPAIR* near)
{
	CELL_OBJECT* pco;

	if (ppco == NULL)
		return NULL;

	pco = &cell_object_buffer[cell_object_index];
	cell_object_index = cell_object_index + 1U & 0x3ff;

	pco->pos.vx = near->x + (((ppco->pos.vx - near->x) << 0x10) >> 0x10);
	pco->pos.vz = near->z + (((ppco->pos.vz - near->z) << 0x10) >> 0x10);

	pco->pos.vy = (ppco->pos.vy << 0x10) >> 0x11;
	pco->yang = ppco->value & 0x3f;
	pco->type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);

	return pco;
}