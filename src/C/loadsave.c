
#include "../decomp_defs.h"

/*
 * Offset 0x57C58
 * D:\driver2\game\C\LOADSAVE.C (line 109)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ SaveConfigData(char *buffer /*$a0*/)
{ // line 1, address 0x57c58
	struct CONFIG_SAVE_HEADER *header; // $s0
	int i; // $t0
} // line 29, address 0x57e58
/*
 * Offset 0x57E58
 * D:\driver2\game\C\LOADSAVE.C (line 140)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ LoadConfigData(char *buffer /*$a0*/)
{ // line 1, address 0x57e58
	struct CONFIG_SAVE_HEADER *header; // $t3
	int i; // $t4
} // line 28, address 0x5803c
/*
 * Offset 0x5803C
 * D:\driver2\game\C\LOADSAVE.C (line 37)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ CalcReplayDataSize()
{ // line 2, address 0x5803c
} // line 9, address 0x5805c
/*
 * Offset 0x5805C
 * D:\driver2\game\C\LOADSAVE.C (line 48)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ SaveReplayData(char *buffer /*$a0*/)
{ // line 2, address 0x5805c
} // line 6, address 0x5807c
/*
 * Offset 0x5807C
 * D:\driver2\game\C\LOADSAVE.C (line 56)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ LoadReplayData(char *buffer /*$a0*/)
{
}
/*
 * Offset 0x5809C
 * D:\driver2\game\C\LOADSAVE.C (line 62)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CalcGameDataSize()
{
}
/*
 * Offset 0x580A4
 * D:\driver2\game\C\LOADSAVE.C (line 69)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ SaveGameData(char *buffer /*$s0*/)
{ // line 1, address 0x580a4
} // line 14, address 0x58134
/*
 * Offset 0x58134
 * D:\driver2\game\C\LOADSAVE.C (line 85)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ LoadGameData(char *buffer /*$a0*/)
{ // line 1, address 0x58134
	struct GAME_SAVE_HEADER *header; // $a0
} // line 14, address 0x581cc
/*
 * Offset 0x581CC
 * D:\driver2\game\C\LOADSAVE.C (line 102)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CalcConfigDataSize()
{
}