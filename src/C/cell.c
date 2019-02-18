#include "../decomp_defs.h"

/*
 * Offset 0x23C14
 * D:\driver2\game\C\CELL.C (line 67)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
struct PACKED_CELL_OBJECT * /*$ra*/ GetFirstPackedCop(int cellx /*$t3*/, int cellz /*$a1*/, struct CELL_ITERATOR *pci /*$a2*/, int use_computed /*$a3*/)
{ // line 1, address 0x23c14
	struct PACKED_CELL_OBJECT *ppco; // $a1
	unsigned short index; // $a0
	unsigned short num; // $t0
	int cbrx; // $t0
	int cbrz; // $t1
	int xoff; // $a0
	int yoff; // $v0
	int cbr; // $t2
	{ // line 34, address 0x23cec
		int event; // $t0
	} // line 43, address 0x23d30
} // line 75, address 0x23e28
/*
 * Offset 0x23E28
 * D:\driver2\game\C\CELL.C (line 57)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ ClearCopUsage()
{
}