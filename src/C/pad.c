
#include "../decomp_defs.h"

char High_shake_data[] = { 1, 0xFF, 0xFF, 0xC8, 0x50, 0x50, 0x50, 0x50, 0x50, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0 };

char Med_shake_data[] = { 1, 0xC8, 0xC8, 0x64, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0 };

char Low_shake_data[] = { 1, 0xA0, 0xA0, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0 };

char* shake_data[] = { High_shake_data, Med_shake_data, Low_shake_data };

/*
 * Offset 0x6B4E8
 * D:\driver2\game\C\PAD.C (line 75)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ InitControllers()
{ 
	int i; // $s3
	int j; // $a1

	DuplicatePadData.buffer = NULL;
	DuplicatePadData.length = 0;

	PadInitDirect(padbuffer[0], padbuffer[1]);
	PadStartCom();

	// [U]: UNDONE

	//Pads[0].mapnew
	//Pads[0].shakeptr
} 
/*
 * Offset 0x6B610
 * D:\driver2\game\C\PAD.C (line 132)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ReadControllers()
{ // line 2, address 0x6b610
	int i; // $s3
	int pad; // $s2
} // line 57, address 0x6b758
/*
 * Offset 0x6B758
 * D:\driver2\game\C\PAD.C (line 257)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MapPad(int pad /*$t2*/, struct PADRAW *pData /*$a3*/)
{ // line 1, address 0x6b758
	unsigned short i; // $a3
	unsigned short buttons; // $t0
	unsigned short mapped; // $t1
} // line 64, address 0x6b940
/*
 * Offset 0x6B948
 * D:\driver2\game\C\PAD.C (line 336)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleDualShock()
{ // line 2, address 0x6b948
	int state; // $v1
	int port; // $s3
	int pad; // $s5
	int dsload; // $s7
} // line 114, address 0x6bc2c
/*
 * Offset 0x6BC2C
 * D:\driver2\game\C\PAD.C (line 452)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ HandlePadVibration(int pad /*$t1*/)
{ // line 1, address 0x6bc2c
	int speed; // $a3
} // line 44, address 0x6be50
/*
 * Offset 0x6BE60
 * D:\driver2\game\C\PAD.C (line 113)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CloseControllers()
{ // line 2, address 0x6be60
	int i; // $v1
} // line 11, address 0x6bea0
/*
 * Offset 0x6BEA0
 * D:\driver2\game\C\PAD.C (line 191)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetPadVibration(int pad /*$a3*/, unsigned char type /*$a1*/)
{
}
/*
 * Offset 0x6BF1C
 * D:\driver2\game\C\PAD.C (line 209)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ StopPadVibration(int pad /*$a0*/)
{
}
/*
 * Offset 0x6BF54
 * D:\driver2\game\C\PAD.C (line 228)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ StopDualShockMotors()
{
}
/*
 * Offset 0x6BF5C
 * D:\driver2\game\C\PAD.C (line 232)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetDuplicatePadData(char *buffer /*$a0*/, int length /*$a1*/)
{
}
/*
 * Offset 0x6BF8C
 * D:\driver2\game\C\PAD.C (line 323)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ClearPad(int pad /*$a0*/)
{
}