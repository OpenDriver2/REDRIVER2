#include "../decomp_defs.h"

/*
 * Offset 0x60014
 * D:\driver2\game\C\MGENERIC.C (line 109)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ StorePlayerPosition(struct SAVED_PLAYER_POS *data /*$a2*/)
{ // line 1, address 0x60014
	unsigned short type; // $a0
} // line 39, address 0x602b0
/*
 * Offset 0x602B0
 * D:\driver2\game\C\MGENERIC.C (line 150)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RestorePlayerPosition(struct SAVED_PLAYER_POS *data /*$a2*/)
{ // line 1, address 0x602b0
} // line 28, address 0x60418
/*
 * Offset 0x60418
 * D:\driver2\game\C\MGENERIC.C (line 180)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ StoreCarPosition(struct _TARGET *target /*$t1*/, struct SAVED_CAR_POS *data /*$t0*/)
{ // line 1, address 0x60418
	int slot; // $v1
} // line 32, address 0x60544
/*
 * Offset 0x6054C
 * D:\driver2\game\C\MGENERIC.C (line 214)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RestoreCarPosition(struct SAVED_CAR_POS *data /*$a3*/)
{
}
/*
 * Offset 0x607A8
 * D:\driver2\game\C\MGENERIC.C (line 62)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ StoreEndData()
{ // line 2, address 0x607a8
	struct _TARGET *target; // $s0
	struct SAVED_CAR_POS *carpos; // $s2
	int i; // $s1
} // line 22, address 0x6084c
/*
 * Offset 0x6084C
 * D:\driver2\game\C\MGENERIC.C (line 86)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ RestoreStartData()
{ // line 2, address 0x6084c
	struct SAVED_CAR_POS *carpos; // $s0
	int i; // $s1
} // line 18, address 0x608a0