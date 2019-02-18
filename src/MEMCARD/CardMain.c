
#include "../decomp_defs.h"

/*
 * Offset 0x87358
 * D:\driver2\game\MEMCARD\MAIN.C (line 120)
 * Stack frame base $fp, length 56
 * Saved registers at address -8: s0 fp ra
 */
int /*$ra*/ CallMemoryCard(int flags /*stack 0*/, int ingame /*stack 4*/)
{ // line 3, address 0x87374
	struct REPLAY_SAVE_HEADER *rheader; // stack address -40
	struct GAME_SAVE_HEADER *gheader; // stack address -36
	struct CONFIG_SAVE_HEADER *cheader; // stack address -32
	char *pt; // stack address -28
	int ret; // stack address -24
	int length; // stack address -20
	{ // line 21, address 0x873d0
	} // line 23, address 0x873e4
	{ // line 129, address 0x878a4
	} // line 135, address 0x878d0
} // line 148, address 0x87920
/*
 * Offset 0x8793C
 * D:\driver2\game\MEMCARD\MAIN.C (line 270)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_SelectSound()
{
}
/*
 * Offset 0x87970
 * D:\driver2\game\MEMCARD\MAIN.C (line 275)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_ConfirmSound()
{
}
/*
 * Offset 0x879A4
 * D:\driver2\game\MEMCARD\MAIN.C (line 280)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_CancelSound()
{
}
/*
 * Offset 0x879D8
 * D:\driver2\game\MEMCARD\MAIN.C (line 285)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_ErrorSound()
{
}
/*
 * Offset 0x87A0C
 * D:\driver2\game\MEMCARD\MAIN.C (line 290)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_InitControllerLibrary(char *a /*stack 0*/, int b /*stack 4*/, char *c /*stack 8*/, int d /*stack 12*/)
{
}
/*
 * Offset 0x87A5C
 * D:\driver2\game\MEMCARD\MAIN.C (line 296)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_DeInitControllerLibrary()
{
}
/*
 * Offset 0x87A9C
 * D:\driver2\game\MEMCARD\MAIN.C (line 302)
 * Stack frame base $fp, length 24
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ libcman_ReadControllers()
{
}
/*
 * Offset 0x87ACC
 * D:\driver2\game\MEMCARD\MAIN.C (line 371)
 * Stack frame base $fp, length 88
 * Saved registers at address -4: fp ra
 */
int /*$ra*/ DoMemoryCard()
{ // line 2, address 0x87adc
	struct RECT rect; // stack address -56
	char filename[32]; // stack address -48
	char l; // stack address -16
	int options; // stack address -12
	static int ret; // address 0x0
} // line 71, address 0x87d34
/*
 * Offset 0x87D4C
 * D:\driver2\game\MEMCARD\MAIN.C (line 444)
 * Stack frame base $fp, length 32
 * Saved registers at address -4: fp ra
 */
char * /*$ra*/ LoadMemCardOverlay()
{ // line 2, address 0x87d5c
	char *pt; // stack address -16
	int ovsize; // stack address -12
} // line 16, address 0x87db8
/*
 * Offset 0x87DD0
 * D:\driver2\game\MEMCARD\MAIN.C (line 462)
 * Stack frame base $fp, length 40
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ StorePermanentTPage()
{ // line 2, address 0x87de0
	struct RECT rect; // stack address -24
	unsigned long *buffer; // stack address -16
} // line 8, address 0x87e2c
/*
 * Offset 0x87E44
 * D:\driver2\game\MEMCARD\MAIN.C (line 472)
 * Stack frame base $fp, length 40
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ RestorePermanentTPage()
{ // line 2, address 0x87e54
	struct RECT rect; // stack address -24
	unsigned long *buffer; // stack address -16
} // line 8, address 0x87ea0
/*
 * Offset 0x87EB8
 * D:\driver2\game\MEMCARD\MAIN.C (line 482)
 * Stack frame base $fp, length 32
 * Saved registers at address -4: fp ra
 */
void /*$ra*/ PutCorrectIcon(int which /*stack 0*/)
{ // line 2, address 0x87ecc
	unsigned char *clut; // stack address -16
	unsigned char *icon; // stack address -12
} // line 24, address 0x87fa0