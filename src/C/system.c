
#include "../decomp_defs.h"

char* LevelFiles[] = {
	"LEVELS\\CHICAGO.LEV",
	"LEVELS\\HAVANA.LEV",
	"LEVELS\\VEGAS.LEV",
	"LEVELS\\RIO.LEV",
};

char* LoadingScreenNames[] = {
	"GFX\\LOADCHIC.TIM",
	"GFX\\LOADHAVA.TIM",
	"GFX\\LOADVEGA.TIM",
	"GFX\\LOADRIO.TIM",
};

char currentfilename[128] = { 0 };

/*
 * Offset 0x7EA38
 * D:\driver2\game\C\SYSTEM.C (line 759)
 * Stack frame base $sp, length 2208
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ LoadfileSeg(char *name /*$v0*/, char *addr /*$s1*/, int address /*$s5*/, int loadsize /*$fp*/)
{ // line 1, address 0x7ea38
	char namebuffer[64]; // stack address -2192
	unsigned char result[8]; // stack address -2128
	int sector; // $s2
	int nsectors; // $s5
	char sectorbuffer[2048]; // stack address -2120
	struct CdlFILE info; // stack address -72
	struct CdlLOC pos; // stack address -48
	int i; // $a2
	int toload; // $s4
	int first; // $a0
} // line 120, address 0x7ed58
/*
 * Offset 0x7ED58
 * D:\driver2\game\C\SYSTEM.C (line 1310)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SwapDrawBuffers2(int player /*$s0*/)
{ // line 1, address 0x7ed58
	int toggle; // $v1
} // line 30, address 0x7ee44
/*
 * Offset 0x7EE44
 * D:\driver2\game\C\SYSTEM.C (line 1364)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SetupDrawBuffers()
{ // line 2, address 0x7ee44
	struct RECT rect; // stack address -24
	int i; // $v1
} // line 47, address 0x7ef74
/*
 * Offset 0x7EF74
 * D:\driver2\game\C\SYSTEM.C (line 1429)
 * Stack frame base $sp, length 96
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetupDrawBufferData(int num_players /*stack 0*/)
{ // line 1, address 0x7ef74
	unsigned long *otpt; // $s2
	unsigned char *primpt; // $s1
	unsigned char *PRIMpt; // $fp
	int x[2]; // stack address -72
	int y[2]; // stack address -64
	int i; // $s3
	int j; // $s6
	int toggle; // $s7
	int height; // stack address -56
} // line 94, address 0x7f180
/*
 * Offset 0x7F180
 * D:\driver2\game\C\SYSTEM.C (line 1577)
 * Stack frame base $sp, length 136
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SetCityType(enum CITYTYPE type /*$a0*/)
{ // line 1, address 0x7f180
	struct CdlFILE cdfile; // stack address -120
	struct XYPAIR *info; // $s2
	char namebuffer[64]; // stack address -96
	unsigned char result[8]; // stack address -32
	int i; // $a2
	int sector; // $s0
} // line 78, address 0x7f3a0
/*
 * Offset 0x7F3BC
 * D:\driver2\game\C\SYSTEM.C (line 646)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ Loadfile(char *name /*$a2*/, char *addr /*$s2*/)
{ // line 1, address 0x7f3bc
	char namebuffer[64]; // stack address -88
	unsigned char result[8]; // stack address -24
	int nread; // $s0
} // line 24, address 0x7f450
/*
 * Offset 0x7F450
 * D:\driver2\game\C\SYSTEM.C (line 389)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ClearMem(char *mem /*$a0*/, int length /*$a1*/)
{ // line 1, address 0x7f450
	char *end; // $v1
} // line 27, address 0x7f4e4
/*
 * Offset 0x7F4E4
 * D:\driver2\game\C\SYSTEM.C (line 427)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ setMem8(unsigned char *mem /*$a0*/, unsigned char val /*$a1*/, int length /*$a2*/)
{ // line 1, address 0x7f4e4
	unsigned char *end; // $v1
	unsigned long lval; // $a3
} // line 32, address 0x7f58c
/*
 * Offset 0x7F58C
 * D:\driver2\game\C\SYSTEM.C (line 469)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ setMem16(unsigned short *mem /*$a0*/, unsigned short val /*$a1*/, int length /*$a2*/)
{ // line 1, address 0x7f58c
	unsigned short *end; // $a3
	unsigned long lval; // $a2
} // line 26, address 0x7f61c
/*
 * Offset 0x7F61C
 * D:\driver2\game\C\SYSTEM.C (line 1566)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ResetCityType()
{
}
/*
 * Offset 0x7F630
 * D:\driver2\game\C\SYSTEM.C (line 1682)
 * Stack frame base $sp, length 192
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ FileExists(char *filename /*$a2*/)
{ // line 1, address 0x7f630
	struct CdlFILE cdfile; // stack address -176
	char namebuffer[128]; // stack address -152
	unsigned char result[8]; // stack address -24
	int retries; // $s1
} // line 26, address 0x7f6a8
/*
 * Offset 0x7F6A8
 * D:\driver2\game\C\SYSTEM.C (line 1723)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 ra
 */
enum CDTYPE /*$ra*/ DiscSwapped(char *filename /*$s1*/)
{ // line 1, address 0x7f6a8
	struct CdlFILE cdfile; // stack address -40
	int ret; // $v1
} // line 39, address 0x7f764
/*
 * Offset 0x7F764
 * D:\driver2\game\C\SYSTEM.C (line 1253)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SwapDrawBuffers()
{ // line 2, address 0x7f764
} // line 50, address 0x7f828
/*
 * Offset 0x7F828
 * D:\driver2\game\C\SYSTEM.C (line 1535)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ InitaliseDrawEnv(struct DB *pBuff /*$s0*/, int x /*$s4*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/)
{
}
/*
 * Offset 0x7F8B0
 * D:\driver2\game\C\SYSTEM.C (line 580)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ Init_FileSystem()
{
	CdInit();

	VSync(3);
}
/*
 * Offset 0x7F8D8
 * D:\driver2\game\C\SYSTEM.C (line 622)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ DoCDRetry()
{ // line 2, address 0x7f8d8
	static int retries; // address 0xc
	unsigned char result[8]; // stack address -16
} // line 11, address 0x7f920
/*
 * Offset 0x7F920
 * D:\driver2\game\C\SYSTEM.C (line 952)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ReportMode(int on /*$s0*/)
{ // line 1, address 0x7f920
	static unsigned char param[8]; // address 0x0
} // line 15, address 0x7f95c
/*
 * Offset 0x7F96C
 * D:\driver2\game\C\SYSTEM.C (line 1017)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ loadsectors(char *addr /*$a0*/, int sector /*$v0*/, int nsectors /*$a2*/)
{ // line 1, address 0x7f96c
	struct CdlLOC pos; // stack address -16
} // line 18, address 0x7f9ec
/*
 * Offset 0x7F9EC
 * D:\driver2\game\C\SYSTEM.C (line 1221)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ EnableDisplay()
{ // line 2, address 0x7f9ec
	int i; // $s1
} // line 9, address 0x7fa58
/*
 * Offset 0x7FA58
 * D:\driver2\game\C\SYSTEM.C (line 1239)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DisableDisplay()
{
}
/*
 * Offset 0x7FA78
 * D:\driver2\game\C\SYSTEM.C (line 1349)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ UpdatePadData()
{
}
/*
 * Offset 0x7FAAC
 * D:\driver2\game\C\SYSTEM.C (line 978)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ data_ready()
{
}
/*
 * Offset 0x7FADC
 * D:\driver2\game\C\SYSTEM.C (line 987)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ sector_ready(unsigned char intr /*$a0*/, unsigned char *result /*$a1*/)
{ // line 1, address 0x7fadc
	{ // line 17, address 0x7fb4c
		struct CdlLOC p; // stack address -16
	} // line 27, address 0x7fb9c
} // line 28, address 0x7fbac