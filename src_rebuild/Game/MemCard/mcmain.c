#include "driver2.h"
#include "main.h"


// decompiled code
// original method signature: 
// int /*$ra*/ CallMemoryCard(int flags /*stack 0*/, int ingame /*stack 4*/)
 // line 120, offset 0x000872f0
	/* begin block 1 */
		// Start line: 123
		// Start offset: 0x0008730C
		// Variables:
	// 		REPLAY_SAVE_HEADER *rheader; // stack offset -40
	// 		GAME_SAVE_HEADER *gheader; // stack offset -36
	// 		CONFIG_SAVE_HEADER *cheader; // stack offset -32
	// 		char *pt; // stack offset -28
	// 		int ret; // stack offset -24
	// 		int size; // stack offset -20

		/* begin block 1.1 */
			// Start line: 141
			// Start offset: 0x00087368
		/* end block 1.1 */
		// End offset: 0x0008737C
		// End Line: 143

		/* begin block 1.2 */
			// Start line: 249
			// Start offset: 0x0008783C
		/* end block 1.2 */
		// End offset: 0x00087868
		// End Line: 255
	/* end block 1 */
	// End offset: 0x000878B8
	// End Line: 268

	/* begin block 2 */
		// Start line: 240
	/* end block 2 */
	// End Line: 241

int CallMemoryCard(int flags, int ingame)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint uVar1;
	ushort local_res0;
	int local_18;
	uint local_14;

	DrawSync(0);
	EnableDisplay();
	if ((current->disp).disp.y == 0) {
		SwapDrawBuffers();
	}
	DrawSync(0);
	DisableDisplay();
	if (ingame == 0) {
		SetPleaseWait(&DAT_000f3000);
	}
	else {
		StorePermanentTPage();
		SetPleaseWait((char *)0x0);
	}
	MCbuffer128K = LoadMemCardOverlay();
	local_res0 = (ushort)flags;
	gMemCardMode = local_res0;
	MClanguageBuffer = MCbuffer128K + 0x20000;
	MCsaveBuffer = MCbuffer128K + 0x21000;
	if (flags == 0x20) {
		local_14 = SaveGameData(MCsaveBuffer);
		fileFormat.blockType = 'B';
		strcpy(fileFormat.asciiTitle, s_Driver_2_00012078);
		slice.sliceIconRefs[0] = '\x01';
		sprintf((char *)&slice, &DAT_000aaa08);
	}
	else {
		if (flags < 0x21) {
			if (flags == 0x10) {
				local_14 = SaveReplayData(MCsaveBuffer);
				fileFormat.blockType = 'A';
				strcpy(fileFormat.asciiTitle, s_Driver_2_00012078);
				sprintf((char *)&slice, &DAT_000aaa08);
				slice.sliceIconRefs[0] = '\x03';
			}
			else {
				if (flags != 0x11) goto LAB_00087634;
				local_14 = CalcReplayDataSize();
				fileFormat.blockType = 'A';
				strcpy(fileFormat.asciiTitle, s_Driver_2_00012078);
				slice.sliceIconRefs[0] = '\x03';
			}
		}
		else {
			if (flags == 0x80) {
				local_14 = SaveConfigData(MCsaveBuffer);
				fileFormat.blockType = 'C';
				strcpy(fileFormat.asciiTitle, s_Driver_2_00012078);
				slice.sliceIconRefs[0] = '\x02';
				sprintf((char *)&slice, &DAT_000aaa08);
			}
			else {
				if (flags < 0x81) {
					if (flags == 0x21) {
						local_14 = CalcGameDataSize();
						fileFormat.blockType = 'B';
						strcpy(fileFormat.asciiTitle, s_Driver_2_00012078);
						slice.sliceIconRefs[0] = '\x01';
					}
					else {
					LAB_00087634:
						printf(s_Erm____CallMemoryCard_passed_wit_00012084);
						while (FrameCnt != 0x78654321) {
							trap(0x400);
						}
					}
				}
				else {
					if (flags != 0x81) goto LAB_00087634;
					local_14 = CalcConfigDataSize();
					fileFormat.blockType = 'C';
					strcpy(fileFormat.asciiTitle, s_Driver_2_00012078);
					slice.sliceIconRefs[0] = '\x02';
				}
			}
		}
	}
	PutCorrectIcon((uint)(byte)slice.sliceIconRefs[0]);
	fileFormat.kanjiTitle[0] = 0;
	fileFormat.kanjiTitle[1] = 0;
	uVar1 = local_14;
	if ((int)local_14 < 0) {
		uVar1 = local_14 + 0x1fff;
	}
	fileFormat.blockSize = ((local_14 & 0x1fff) != 0) + (char)((int)uVar1 >> 0xd);
	fileFormat.sliceByteSize = local_14 + 0x7f & 0xffffff80;
	slice.sliceData = MCsaveBuffer;
	CloseControllers();
	local_18 = DoMemoryCard();
	if ((local_18 == 0) || (flags == 0x20)) goto LAB_00087824;
	if (flags < 0x21) {
		if (flags == 0x10) goto LAB_00087824;
		if (flags == 0x11) {
			local_18 = LoadReplayData(MCsaveBuffer);
			goto LAB_00087824;
		}
	}
	else {
		if (flags == 0x80) goto LAB_00087824;
		if (flags < 0x81) {
			if (flags == 0x21) {
				local_18 = LoadGameData(MCsaveBuffer);
				goto LAB_00087824;
			}
		}
		else {
			if (flags == 0x81) {
				local_18 = LoadConfigData(MCsaveBuffer);
				goto LAB_00087824;
			}
		}
	}
	printf(s_Erm____CallMemoryCard_passed_wit_00012084);
	while (FrameCnt != 0x78654321) {
		trap(0x400);
	}
LAB_00087824:
	InitControllers();
	if (ingame != 0) {
		SetPleaseWait((char *)0x0);
		RestorePermanentTPage();
		LoadSky();
		InitMap();
		SpoolSYNC();
	}
	SetupDrawBuffers();
	EnableDisplay();
	SwapDrawBuffers();
	DrawSync(0);
	VSync(0);
	SetDispMask(1);
	return local_18;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_SelectSound()
 // line 270, offset 0x000878d4
	/* begin block 1 */
		// Start line: 540
	/* end block 1 */
	// End Line: 541

/* WARNING: Unknown calling convention yet parameter storage is locked */

void libcman_SelectSound(void)
{
	UNIMPLEMENTED();
	return;
	/*
	FESound(3);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_ConfirmSound()
 // line 275, offset 0x00087908
	/* begin block 1 */
		// Start line: 550
	/* end block 1 */
	// End Line: 551

/* WARNING: Unknown calling convention yet parameter storage is locked */

void libcman_ConfirmSound(void)
{
	UNIMPLEMENTED();
	return;
	/*
	FESound(2);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_CancelSound()
 // line 280, offset 0x0008793c
	/* begin block 1 */
		// Start line: 560
	/* end block 1 */
	// End Line: 561

/* WARNING: Unknown calling convention yet parameter storage is locked */

void libcman_CancelSound(void)
{
	UNIMPLEMENTED();
	/*
	FESound(0);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_ErrorSound()
 // line 285, offset 0x00087970
	/* begin block 1 */
		// Start line: 570
	/* end block 1 */
	// End Line: 571

/* WARNING: Unknown calling convention yet parameter storage is locked */

void libcman_ErrorSound(void)
{
	UNIMPLEMENTED();
	/*
	FESound(1);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_InitControllerLibrary(char *a /*stack 0*/, int b /*stack 4*/, char *c /*stack 8*/, int d /*stack 12*/)
 // line 290, offset 0x000879a4
	/* begin block 1 */
		// Start line: 580
	/* end block 1 */
	// End Line: 581

void libcman_InitControllerLibrary(char *a, int b, char *c, int d)
{
	UNIMPLEMENTED();
	/*
	InitControllers();
	SetDuplicatePadData(a, b);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_DeInitControllerLibrary()
 // line 296, offset 0x000879f4
	/* begin block 1 */
		// Start line: 592
	/* end block 1 */
	// End Line: 593

/* WARNING: Unknown calling convention yet parameter storage is locked */

void libcman_DeInitControllerLibrary(void)
{
	UNIMPLEMENTED();
	/*
	CloseControllers();
	SetDuplicatePadData((char *)0x0, 0);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ libcman_ReadControllers()
 // line 302, offset 0x00087a34
	/* begin block 1 */
		// Start line: 604
	/* end block 1 */
	// End Line: 605

/* WARNING: Unknown calling convention yet parameter storage is locked */

void libcman_ReadControllers(void)
{
	UNIMPLEMENTED();
	/*
	ReadControllers();
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ DoMemoryCard()
 // line 371, offset 0x00087a64
	/* begin block 1 */
		// Start line: 373
		// Start offset: 0x00087A74
		// Variables:
	// 		RECT rect; // stack offset -56
	// 		char filename[32]; // stack offset -48
	// 		char l; // stack offset -16
	// 		int options; // stack offset -12
	// 		static int ret; // offset 0x0
	/* end block 1 */
	// End offset: 0x00087CCC
	// End Line: 442

	/* begin block 2 */
		// Start line: 742
	/* end block 2 */
	// End Line: 743

/* WARNING: Unknown calling convention yet parameter storage is locked */

int DoMemoryCard(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	undefined2 local_38;
	undefined2 local_36;
	undefined2 local_34;
	undefined2 local_32;
	char acStack48[32];
	undefined local_10;
	int local_c;

	local_c = 0x254;
	local_10 = 0x49;
	sprintf(acStack48, s_DATA_MCTEXT__cTEXT_LNG_000120e0, 0x49);
	Loadfile(acStack48, MClanguageBuffer);
	fileFormat.sliceIconTimPtrs[1] = (_func_17 *)&icon_1;
	fileFormat.sliceIconTimPtrs[2] = (_func_17 *)&icon_2;
	fileFormat.sliceIconTimPtrs[3] = (_func_17 *)&icon_0;
	SpuSetMute(0);
	MCoptions = local_c;
	MCfilename = s_GFX_MCBACK_RAW_000120f8;
	MCsp = SetSp(MCbuffer128K + 0x1fc00);
	if ((gMemCardMode & 1) == 0) {
		ret_30 = card_manager(1, MCoptions, MClanguageBuffer, &fileFormat, &slice, MCfilename, MCbuffer128K);
	}
	else {
		ret_30 = card_manager(0, MCoptions, MClanguageBuffer, &fileFormat, &slice, MCfilename, MCbuffer128K);
	}
	SetSp(MCsp);
	DrawSync(0);
	SetDispMask(0);
	local_38 = 0;
	local_36 = 0;
	local_34 = 0x140;
	local_32 = 0x200;
	ClearImage(&local_38, 0, 0, 0);
	DrawSync(0);
	return (uint)(ret_30 == 2);*/
}



// decompiled code
// original method signature: 
// char * /*$ra*/ LoadMemCardOverlay()
 // line 444, offset 0x00087ce4
	/* begin block 1 */
		// Start line: 446
		// Start offset: 0x00087CF4
		// Variables:
	// 		char *pt; // stack offset -16
	// 		int ovsize; // stack offset -12
	/* end block 1 */
	// End offset: 0x00087D50
	// End Line: 460

	/* begin block 2 */
		// Start line: 888
	/* end block 2 */
	// End Line: 889

/* WARNING: Unknown calling convention yet parameter storage is locked */

char * LoadMemCardOverlay(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	iVar1 = Loadfile(s_MCARD_BIN_000120d4, &DAT_000f3000);
	return &DAT_000f3000 + (iVar1 + 3U & 0xfffffffc);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StorePermanentTPage()
 // line 462, offset 0x00087d68
	/* begin block 1 */
		// Start line: 464
		// Start offset: 0x00087D78
		// Variables:
	// 		RECT rect; // stack offset -24
	// 		unsigned long *buffer; // stack offset -16
	/* end block 1 */
	// End offset: 0x00087DC4
	// End Line: 470

	/* begin block 2 */
		// Start line: 924
	/* end block 2 */
	// End Line: 925

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StorePermanentTPage(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 local_18;
	undefined2 local_16;
	undefined2 local_14;
	undefined2 local_12;
	char *local_10;

	local_10 = model_spool_buffer + 0xa000;
	local_18 = 0x1c0;
	local_16 = 0;
	local_14 = 0x40;
	local_12 = 0x100;
	StoreImage(&local_18, local_10);
	DrawSync(0);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RestorePermanentTPage()
 // line 472, offset 0x00087ddc
	/* begin block 1 */
		// Start line: 474
		// Start offset: 0x00087DEC
		// Variables:
	// 		RECT rect; // stack offset -24
	// 		unsigned long *buffer; // stack offset -16
	/* end block 1 */
	// End offset: 0x00087E38
	// End Line: 480

	/* begin block 2 */
		// Start line: 944
	/* end block 2 */
	// End Line: 945

/* WARNING: Unknown calling convention yet parameter storage is locked */

void RestorePermanentTPage(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 local_18;
	undefined2 local_16;
	undefined2 local_14;
	undefined2 local_12;
	char *local_10;

	local_10 = model_spool_buffer + 0xa000;
	local_18 = 0x1c0;
	local_16 = 0;
	local_14 = 0x40;
	local_12 = 0x100;
	LoadImage(&local_18, local_10);
	DrawSync(0);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PutCorrectIcon(int which /*stack 0*/)
 // line 482, offset 0x00087e50
	/* begin block 1 */
		// Start line: 484
		// Start offset: 0x00087E64
		// Variables:
	// 		unsigned char *clut; // stack offset -16
	// 		unsigned char *icon; // stack offset -12
	/* end block 1 */
	// End offset: 0x00087F38
	// End Line: 506

	/* begin block 2 */
		// Start line: 964
	/* end block 2 */
	// End Line: 965

void PutCorrectIcon(int which)
{
	UNIMPLEMENTED();
	/*
	undefined *local_10;
	undefined *local_c;

	if (which == 2) {
		local_10 = &DAT_000a2994;
		local_c = &DAT_000a29c0;
	}
	else {
		if ((which < 3) || (which != 3)) {
			local_10 = &DAT_000a28d4;
			local_c = &DAT_000a2900;
		}
		else {
			local_10 = &DAT_000a2814;
			local_c = &DAT_000a2840;
		}
	}
	memcpy(fileFormat.blockIconClut, local_10, 0x20);
	memcpy(fileFormat.blockIconData, local_c, 0x80);
	return;
	*/
}





