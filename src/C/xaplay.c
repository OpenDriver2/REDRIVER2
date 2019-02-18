
#include "../decomp_defs.h"

char* XANames[] = {
	"\\DRIVER2\\XA\\XABNK01.XA;1",
	"\\DRIVER2\\XA\\XABNK02.XA;1",
	"\\DRIVER2\\XA\\XABNK03.XA;1",
	"\\DRIVER2\\XA\\XABNK04.XA;1",
};


/*
 * Offset 0x82CCC
 * D:\driver2\game\C\XAPLAY.C (line 265)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ PlayXA(int num /*$a3*/, int index /*$t0*/)
{ // line 1, address 0x82ccc
	struct CdlFILTER filt; // stack address -40
	struct CdlLOC loc; // stack address -32
	unsigned char res[8]; // stack address -24
} // line 25, address 0x82db0
/*
 * Offset 0x82DC8
 * D:\driver2\game\C\XAPLAY.C (line 155)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ GetXAData(int number /*$a0*/)
{ // line 1, address 0x82dc8
	int i; // $s0
	struct CdlFILE fp; // stack address -32
} // line 12, address 0x82e14
/*
 * Offset 0x82E14
 * D:\driver2\game\C\XAPLAY.C (line 226)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ PrepareXA()
{ // line 2, address 0x82e14
	unsigned char param[4]; // stack address -16
} // line 23, address 0x82ec0
/*
 * Offset 0x82ED0
 * D:\driver2\game\C\XAPLAY.C (line 320)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ UnprepareXA()
{ // line 2, address 0x82ed0
	unsigned char param[4]; // stack address -16
} // line 17, address 0x82f18
/*
 * Offset 0x82F28
 * D:\driver2\game\C\XAPLAY.C (line 128)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ GetMissionXAData(int number /*$s0*/)
{ // line 1, address 0x82f28
	struct CdlFILE fp; // stack address -32
} // line 16, address 0x82f80
/*
 * Offset 0x82F80
 * D:\driver2\game\C\XAPLAY.C (line 185)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetXAVolume(int volume /*$a0*/)
{ // line 1, address 0x82f80
} // line 12, address 0x82fe0
/*
 * Offset 0x82FE0
 * D:\driver2\game\C\XAPLAY.C (line 343)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ StopXA()
{
}
/*
 * Offset 0x8302C
 * D:\driver2\game\C\XAPLAY.C (line 386)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ResumeXA()
{ // line 2, address 0x8302c
	struct CdlFILTER filt; // stack address -32
	unsigned char res[8]; // stack address -24
} // line 22, address 0x830cc
/*
 * Offset 0x830E0
 * D:\driver2\game\C\XAPLAY.C (line 418)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ PauseXA()
{ // line 1, address 0x830e0
	unsigned char res[8]; // stack address -16
} // line 15, address 0x83148
/*
 * Offset 0x83158
 * D:\driver2\game\C\XAPLAY.C (line 310)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ XAPrepared()
{
}
/*
 * Offset 0x83164
 * D:\driver2\game\C\XAPLAY.C (line 355)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ cbready(int intr /*$s1*/, unsigned char *result /*$a1*/)
{
}