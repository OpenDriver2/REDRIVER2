#include "../decomp_defs.h"

/*
 * Offset 0x5F364
 * D:\driver2\game\C\MDRAW.C (line 58)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawMission()
{ // line 2, address 0x5f364
	{ // line 10, address 0x5f3f8
		char *string; // $s1
	} // line 27, address 0x5f480
} // line 66, address 0x5f5bc
/*
 * Offset 0x5F5D4
 * D:\driver2\game\C\MDRAW.C (line 312)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DrawWorldTarget(struct _TARGET *target /*$s0*/)
{ // line 1, address 0x5f5d4
	struct VECTOR tv; // stack address -32
	int slot; // $v1
	int flags; // $s1
} // line 105, address 0x5f8b8
/*
 * Offset 0x5F8CC
 * D:\driver2\game\C\MDRAW.C (line 419)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawMultiplayerTarget(struct _TARGET *target /*$s0*/)
{ // line 1, address 0x5f8cc
	struct VECTOR tv; // stack address -40
	unsigned char r; // $s3
	unsigned char g; // $s2
	unsigned char b; // $s1
} // line 98, address 0x5fad4
/*
 * Offset 0x5FAF0
 * D:\driver2\game\C\MDRAW.C (line 126)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DrawTimer(struct MR_TIMER *timer /*$s1*/)
{ // line 1, address 0x5faf0
	char string[16]; // stack address -32
} // line 27, address 0x5fbd0
/*
 * Offset 0x5FBE4
 * D:\driver2\game\C\MDRAW.C (line 155)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: ra
 */
void /*$ra*/ DisplayPlayerPosition()
{ // line 2, address 0x5fbe4
	char string[32]; // stack address -40
} // line 6, address 0x5fc2c
/*
 * Offset 0x5FC2C
 * D:\driver2\game\C\MDRAW.C (line 163)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DrawMessage(int y /*$s1*/, char *string /*$s0*/)
{ // line 1, address 0x5fc2c
	{ // line 4, address 0x5fc48
	} // line 13, address 0x5fc90
} // line 14, address 0x5fca4
/*
 * Offset 0x5FCA4
 * D:\driver2\game\C\MDRAW.C (line 179)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawWorldTargets()
{ // line 2, address 0x5fca4
	int i; // $s0
} // line 9, address 0x5fce4
/*
 * Offset 0x5FCF4
 * D:\driver2\game\C\MDRAW.C (line 190)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawOverheadTargets()
{ // line 2, address 0x5fcf4
	int i; // $s0
} // line 9, address 0x5fd34
/*
 * Offset 0x5FD44
 * D:\driver2\game\C\MDRAW.C (line 201)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawFullscreenTargets()
{ // line 2, address 0x5fd44
	int i; // $s0
} // line 9, address 0x5fd84
/*
 * Offset 0x5FD94
 * D:\driver2\game\C\MDRAW.C (line 212)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawMultiplayerTargets()
{ // line 2, address 0x5fd94
	int i; // $s0
} // line 9, address 0x5fdd4
/*
 * Offset 0x5FDE4
 * D:\driver2\game\C\MDRAW.C (line 230)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawOverheadTarget(struct _TARGET *target /*$s0*/)
{ // line 1, address 0x5fde4
	struct VECTOR tv; // stack address -24
} // line 39, address 0x5feec
/*
 * Offset 0x5FEFC
 * D:\driver2\game\C\MDRAW.C (line 271)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawFullscreenTarget(struct _TARGET *target /*$s0*/)
{ // line 1, address 0x5fefc
	struct VECTOR tv; // stack address -24
} // line 39, address 0x60004