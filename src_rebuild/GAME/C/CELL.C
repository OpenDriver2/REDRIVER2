#include "THISDUST.H"
#include "CELL.H"
#include "SYSTEM.H"
#include "MAP.H"
#include "MISSION.H"
#include "EVENT.H"
#include "SPOOL.H"
#include "DRAW.H"

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

// [D]
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

// [D]
PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, CELL_ITERATOR *pci, int use_computed)
{
	char bVar1;
	ushort uVar2;
	PACKED_CELL_OBJECT *ppco;
	int iVar4;
	CELL_DATA *celld;
	uint uVar6;
	uint uVar7;
	unsigned short index;
	unsigned short num;

	index = (cellx >> 5 & 1) + (cellz >> 5 & 1) * 2;

	if (NumPlayers == 2)
	{
		iVar4 = cells_across;

		if (cells_across < 0)
			iVar4 = cells_across + 0x1f;

		if (RoadMapRegions[index] != ((uint)cellx >> 5) + ((uint)cellz >> 5) * (iVar4 >> 5))
			return NULL;
	}

	if (cell_ptrs[(cellz - (cellz & 0xffffffe0U)) * 0x20 + index * 0x400 + (cellx - (cellx & 0xffffffe0U))] == 0xffff)
	{
		return NULL;
	}

	pci->pcd = cells + cell_ptrs[(cellz - (cellz & 0xffffffe0U)) * 0x20 + index * 0x400 + (cellx - (cellx & 0xffffffe0U))];

	num = pci->pcd->num;

	if (events.camera == 0) 
	{
		if ((pci->pcd->num & 0x4000) != 0)
		{
			return NULL;
		}
	}
	else 
	{
		pci->pcd++;
		while (num != (events.draw | 0x4000))
		{
			if ((pci->pcd->num & 0x8000) != 0)
				return NULL;

			num = pci->pcd->num;
			pci->pcd++;
		}
	}

	pci->nearCell.x = (cellx - (cells_across >> 1)) * 0x800;
	pci->nearCell.z = (cellz - (cells_down >> 1)) * 0x800;
	pci->use_computed = use_computed;

	num = pci->pcd->num;
	
	uVar7 = num & 0x3fff;
	ppco = cell_objects + uVar7;

	if ((ppco->value == 0xffff) && (((ppco->pos).vy & 1) != 0)) 
	{
	LAB_00023d8c:
		ppco = GetNextPackedCop(pci);
	}
	else 
	{
		if (use_computed != 0) 
		{
			bVar1 = cell_object_computed_values[uVar7 >> 3];
			uVar6 = 1 << (num & 7) & 0xffff;

			if ((bVar1 & uVar6) != 0)
				goto LAB_00023d8c;

			cell_object_computed_values[uVar7 >> 3] = bVar1 | (char)uVar6;
		}

		pci->ppco = ppco;
	}

	return ppco;
}





