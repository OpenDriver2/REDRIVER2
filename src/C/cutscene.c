#include "../decomp_defs.h"

/*
 * Offset 0x31400
 * D:\driver2\game\C\CUTSCENE.C (line 646)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawInGameCutscene()
{ // line 2, address 0x31400
	struct TILE *tile; // $s0
} // line 30, address 0x31550
/*
 * Offset 0x31550
 * D:\driver2\game\C\CUTSCENE.C (line 683)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ TriggerChase(int *car /*$s2*/, int cutscene /*$a1*/)
{ // line 1, address 0x31550
	void *inform; // $s3
	int i; // $a0
	int length; // $s1
	{ // line 12, address 0x315c0
	} // line 38, address 0x3170c
} // line 42, address 0x31754
/*
 * Offset 0x31754
 * D:\driver2\game\C\CUTSCENE.C (line 838)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ ReleaseInGameCutscene()
{ // line 2, address 0x31754
	{ // line 7, address 0x317b0
		struct STREAM_SOURCE *pinfo; // $a0
		int i; // $s0
	} // line 79, address 0x319e0
} // line 105, address 0x31a88
/*
 * Offset 0x31A88
 * D:\driver2\game\C\CUTSCENE.C (line 1040)
 * Stack frame base $sp, length 96
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ TriggerInGameCutsceneSystem(int cutscene /*$a0*/)
{ // line 1, address 0x31a88
	static char padid[8]; // address 0x0
	int bDamageOverride; // stack address -64
	int i; // $s2
	int id; // $v1
	{ // line 18, address 0x31acc
		{ // line 54, address 0x31c2c
			int car; // $v1
			int model; // $v1
			int palette; // $a1
		} // line 65, address 0x31c84
		{ // line 85, address 0x31d14
			{ // line 90, address 0x31d74
				int car; // $v1
			} // line 104, address 0x31df8
		} // line 112, address 0x31df8
	} // line 146, address 0x31f08
} // line 151, address 0x31f44
/*
 * Offset 0x31F44
 * D:\driver2\game\C\CUTSCENE.C (line 1199)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetNullPlayer(int plr /*$a0*/)
{ // line 1, address 0x31f44
} // line 14, address 0x31fc8
/*
 * Offset 0x31FC8
 * D:\driver2\game\C\CUTSCENE.C (line 1221)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetNullPlayerDontKill(int plr /*$a0*/)
{ // line 1, address 0x31fc8
} // line 14, address 0x32048
/*
 * Offset 0x32048
 * D:\driver2\game\C\CUTSCENE.C (line 1244)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DestroyPlayer(int plr /*$s0*/, int fully /*$a1*/)
{
}
/*
 * Offset 0x32180
 * D:\driver2\game\C\CUTSCENE.C (line 1299)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ LoadCutsceneToReplayBuffer(int residentCutscene /*$a0*/)
{ // line 2, address 0x32180
	struct REPLAY_SAVE_HEADER *rheader; // $a1
	struct REPLAY_STREAM_HEADER *sheader; // $t1
	char filename[64]; // stack address -88
	char *pt; // $s1
	int i; // $a0
	int length; // $s0
} // line 56, address 0x324a4
/*
 * Offset 0x324A4
 * D:\driver2\game\C\CUTSCENE.C (line 1362)
 * Stack frame base $sp, length 456
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ LoadCutsceneToBuffer(int subindex /*$s3*/)
{ // line 1, address 0x324a4
	struct CUTSCENE_HEADER header; // stack address -440
	struct REPLAY_SAVE_HEADER rheader; // stack address -376
	char filename[64]; // stack address -88
	int address; // $a2
	int length; // $s0
} // line 78, address 0x32628
/*
 * Offset 0x32628
 * D:\driver2\game\C\CUTSCENE.C (line 566)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitInGameCutsceneVariables()
{
}
/*
 * Offset 0x32694
 * D:\driver2\game\C\CUTSCENE.C (line 594)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ HandleInGameCutscene()
{ // line 2, address 0x32694
	{ // line 37, address 0x32774
	} // line 48, address 0x32798
} // line 50, address 0x327a8
/*
 * Offset 0x327A8
 * D:\driver2\game\C\CUTSCENE.C (line 732)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ TriggerInGameCutscene(int cutscene /*$s0*/)
{ // line 1, address 0x327a8
	{ // line 30, address 0x32858
	} // line 37, address 0x32894
} // line 38, address 0x32894
/*
 * Offset 0x328A4
 * D:\driver2\game\C\CUTSCENE.C (line 778)
 * Stack frame base $sp, length 152
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ CalcInGameCutsceneSize()
{ // line 39, address 0x328a4
	struct CUTSCENE_HEADER header; // stack address -136
	char filename[64]; // stack address -72
} // line 52, address 0x32930
/*
 * Offset 0x32930
 * D:\driver2\game\C\CUTSCENE.C (line 951)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ PreLoadInGameCutscene(int chase /*$a0*/)
{
}
/*
 * Offset 0x32950
 * D:\driver2\game\C\CUTSCENE.C (line 965)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ CutsceneCameraChange(int cameracnt /*$s0*/)
{
}
/*
 * Offset 0x32A1C
 * D:\driver2\game\C\CUTSCENE.C (line 1010)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ LoadInGameCutscene(int subindex /*$s1*/)
{ // line 1, address 0x32a1c
	int ret; // $s0
} // line 23, address 0x32a9c
/*
 * Offset 0x32A9C
 * D:\driver2\game\C\CUTSCENE.C (line 1274)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ FindNextCutChange(int cameracnt /*$a0*/)
{ // line 1, address 0x32a9c
	int found; // $t0
	int count; // $a3
	int nextframe; // $a2
} // line 17, address 0x32b00
/*
 * Offset 0x32B00
 * D:\driver2\game\C\CUTSCENE.C (line 1471)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ LoadCutsceneInformation(int cutscene /*$s2*/)
{ // line 1, address 0x32b00
	int i; // $s1
} // line 27, address 0x32bbc
/*
 * Offset 0x32BBC
 * D:\driver2\game\C\CUTSCENE.C (line 1505)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ FreeCutsceneBuffer()
{ // line 2, address 0x32bbc
	int i; // $v1
} // line 13, address 0x32c28
/*
 * Offset 0x32C28
 * D:\driver2\game\C\CUTSCENE.C (line 1520)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ IsCutsceneResident(int cutscene /*$a0*/)
{ // line 1, address 0x32c28
	int i; // $a1
} // line 13, address 0x32c70
/*
 * Offset 0x32C70
 * D:\driver2\game\C\CUTSCENE.C (line 1442)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ShowCutsceneError()
{
}