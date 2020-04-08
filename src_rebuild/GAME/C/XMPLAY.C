#include "THISDUST.H"
#include "XMPLAY.H"


// TODO: replace this file with actual XMPLAY PS2
// or don't even decompile it?

int Song_ID = -0x1;


// decompiled code
// original method signature: 
// short /*$ra*/ Interpolate(short p /*$a0*/, short p1 /*$a1*/, short p2 /*$a2*/, short v1 /*$a3*/, int v2 /*stack 16*/)
 // line 237, offset 0x000869ec
	/* begin block 1 */
		// Start line: 238
		// Start offset: 0x000869EC
	/* end block 1 */
	// End offset: 0x00086A6C
	// End Line: 248

	/* begin block 2 */
		// Start line: 775
	/* end block 2 */
	// End Line: 776

	/* begin block 3 */
		// Start line: 474
	/* end block 3 */
	// End Line: 475

short Interpolate(short p, short p1, short p2, short v1, int v2)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;

	iVar1 = (int)p1;
	if (iVar1 != (int)p2) {
		iVar2 = ((int)p2 - iVar1) * 0x10000 >> 0x10;
		if (iVar2 == 0) {
			trap(7);
		}
		return (short)((uint)(((int)v1 +
			(((p - iVar1) * 0x10000 >> 0x10) *
			(((int)(short)v2 - (int)v1) * 0x10000 >> 0x10)) / iVar2) * 0x10000) >>
			0x10);
	}
	return v1;
	*/
}



// decompiled code
// original method signature: 
// unsigned short /*$ra*/ GetLogPeriod(unsigned char note /*$a0*/, unsigned short fine /*$a1*/)
 // line 256, offset 0x000863ec
	/* begin block 1 */
		// Start line: 257
		// Start offset: 0x000863EC
	/* end block 1 */
	// End offset: 0x00086484
	// End Line: 281

	/* begin block 2 */
		// Start line: 512
	/* end block 2 */
	// End Line: 513

ushort GetLogPeriod(unsigned char note, ushort fine)
{
	UNIMPLEMENTED();
	return 0;
	/*
	short sVar1;
	undefined2 extraout_var;
	int iVar2;

	iVar2 = (uint)(fine >> 4) + ((uint)note % 0xc) * 8;
	sVar1 = Interpolate(fine >> 4, 0, 0xf, logtab[iVar2], (int)(short)logtab[iVar2 + 1]);
	return (ushort)(CONCAT22(extraout_var, sVar1) >> (uint)note / 0xc);*/
}



// decompiled code
// original method signature: 
// unsigned short /*$ra*/ JPGetPeriod(unsigned char note /*$a0*/, short fine /*$a1*/)
 // line 288, offset 0x00086a6c
	/* begin block 1 */
		// Start line: 17009
	/* end block 1 */
	// End Line: 17010

	/* begin block 2 */
		// Start line: 17050
	/* end block 2 */
	// End Line: 17051

ushort JPGetPeriod(unsigned char note, short fine)
{
	UNIMPLEMENTED();
	return 0;
	/*
	return ((ushort)note * -0x40 -
		(short)(((int)((uint)(ushort)fine << 0x10) >> 0x10) -
		((int)((uint)(ushort)fine << 0x10) >> 0x1f) >> 1)) + 0x1e40;*/
}



// decompiled code
// original method signature: 
// unsigned short /*$ra*/ GetPeriod(unsigned char note /*$a2*/, unsigned short c2spd /*$a1*/)
 // line 299, offset 0x00086aa0
	/* begin block 1 */
		// Start line: 300
		// Start offset: 0x00086AA0
	/* end block 1 */
	// End offset: 0x00086AF0
	// End Line: 307

	/* begin block 2 */
		// Start line: 17072
	/* end block 2 */
	// End Line: 17073

ushort GetPeriod(unsigned char note, ushort c2spd)
{
	UNIMPLEMENTED();
	return 0;
	/*
	ushort uVar1;

	if (ms->NotAmiga == 1) {
		uVar1 = JPGetPeriod(note, c2spd);
	}
	else {
		uVar1 = GetLogPeriod(note, c2spd);
	}
	return uVar1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_Exit()
 // line 331, offset 0x00085d18
	/* begin block 1 */
		// Start line: 333
		// Start offset: 0x00085D18
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x00085D78
	// End Line: 342

	/* begin block 2 */
		// Start line: 662
	/* end block 2 */
	// End Line: 663

	/* begin block 3 */
		// Start line: 4182
	/* end block 3 */
	// End Line: 4183

	/* begin block 4 */
		// Start line: 4183
	/* end block 4 */
	// End Line: 4184

/* WARNING: Unknown calling convention yet parameter storage is locked */

void XM_Exit(void)
{
	UNIMPLEMENTED();
	/*
	int SongID;

	SongID = 0;
	if (0 < XM_NSA) {
		do {
			XM_Quit(SongID);
			SongID = SongID + 1;
		} while (SongID < XM_NSA);
		SongID = 0;
	}
	do {
		XM_CloseVAB(SongID);
		SongID = SongID + 1;
	} while (SongID < 8);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_CloseVAB(int VabID /*$a1*/)
 // line 345, offset 0x00085fb4
	/* begin block 1 */
		// Start line: 690
	/* end block 1 */
	// End Line: 691

void XM_CloseVAB(int VabID)
{
	UNIMPLEMENTED();
	/*
	if ((&iVABID)[VabID] != -1) {
		ClearSPU(VabID);
		(&iVABID)[VabID] = -1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_CloseVAB2(int VabID /*$a3*/)
 // line 354, offset 0x000862f0
	/* begin block 1 */
		// Start line: 355
		// Start offset: 0x000862F0
		// Variables:
	// 		int i; // $v0
	/* end block 1 */
	// End offset: 0x00086358
	// End Line: 367

	/* begin block 2 */
		// Start line: 11906
	/* end block 2 */
	// End Line: 11907

	/* begin block 3 */
		// Start line: 708
	/* end block 3 */
	// End Line: 709

void XM_CloseVAB2(int VabID)
{
	UNIMPLEMENTED();
	/*
	ulong *puVar1;
	int iVar2;

	iVar2 = (int)(&iVABID)[VabID];
	if (iVar2 != -1) {
		if (0 < iVar2) {
			puVar1 = &xm_l_vag_spu_addr + VabID * 0x80;
			do {
				*puVar1 = 0;
				iVar2 = iVar2 + -1;
				puVar1 = puVar1 + 1;
			} while (iVar2 != 0);
		}
		(&iVABID)[VabID] = -1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_Update()
 // line 374, offset 0x00085d78
	/* begin block 1 */
		// Start line: 376
		// Start offset: 0x00085D78
	/* end block 1 */
	// End offset: 0x00085DB8
	// End Line: 385

	/* begin block 2 */
		// Start line: 4238
	/* end block 2 */
	// End Line: 4239

	/* begin block 3 */
		// Start line: 4271
	/* end block 3 */
	// End Line: 4272

	/* begin block 4 */
		// Start line: 4272
	/* end block 4 */
	// End Line: 4273

/* WARNING: Unknown calling convention yet parameter storage is locked */

void XM_Update(void)
{
	UNIMPLEMENTED_PRINTONCE();
	/*
	int iVar1;

	XM_SCAN = VSync(1);
	if (JP_Do_Nothing == 0) {
		UpdateXMData();
		iVar1 = VSync(1);
		XM_SCAN = iVar1 - XM_SCAN;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_PlayStart(int Song_ID /*$a2*/, int PlayMask /*$a1*/)
 // line 409, offset 0x00085e38
	/* begin block 1 */
		// Start line: 818
	/* end block 1 */
	// End Line: 819

void XM_PlayStart(int Song_ID, int PlayMask)
{
	UNIMPLEMENTED();
	/*
	XMSONG *pXVar1;

	if (((&XMSongIDs)[Song_ID] != -1) && (PlayMask != 0)) {
		pXVar1 = (XMSONG *)(&XM_SngAddress24)[Song_ID];
		mu = pXVar1;
		pXVar1->PlayMask = PlayMask;
		pXVar1->XMPlay = '\x01';
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_PlayStop(int Song_ID /*$a1*/)
 // line 429, offset 0x00085dc8
	/* begin block 1 */
		// Start line: 4383
	/* end block 1 */
	// End Line: 4384

void XM_PlayStop(int Song_ID)
{
	UNIMPLEMENTED();
	/*
	if ((&XMSongIDs)[Song_ID] != -1) {
		mu = (XMSONG *)(&XM_SngAddress24)[Song_ID];
		if (mu->XMPlay != '\0') {
			mu->XMPlay = '\0';
			SilenceXM(Song_ID);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ InitXMData(unsigned char *mpp /*$s5*/, int XM_ID /*$a1*/, int S3MPan /*$a2*/)
 // line 454, offset 0x000831b0
	/* begin block 1 */
		// Start line: 455
		// Start offset: 0x000831B0
		// Variables:
	// 		int t; // $s2
	// 		int a; // $s4
	// 		int c; // $s3
	// 		unsigned long b; // $a2
	// 		unsigned short b2; // $v1
	/* end block 1 */
	// End offset: 0x0008344C
	// End Line: 521

	/* begin block 2 */
		// Start line: 908
	/* end block 2 */
	// End Line: 909

	/* begin block 3 */
		// Start line: 918
	/* end block 3 */
	// End Line: 919

int InitXMData(unsigned char *mpp, int XM_ID, int S3MPan)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	byte bVar2;
	ulong uVar3;
	ushort uVar4;
	uint uVar5;
	uchar *puVar6;
	XMHEADER *pXVar7;
	_func_12 *mpp_00;
	uchar *mpp_01;
	int iVar8;
	int iVar9;
	int iVar10;

	pXVar7 = (XMHEADER *)XM_HeaderAddress8[XM_ID];
	mhu = pXVar7;
	pXVar7->S3MPanning = S3MPan;
	pXVar7->version = (ushort)mpp[0x3a] + (ushort)mpp[0x3b] * 0x100;
	pXVar7->songlength = (ushort)mpp[0x40] + (ushort)mpp[0x41] * 0x100;
	pXVar7->restart = (ushort)mpp[0x42] + (ushort)mpp[0x43] * 0x100;
	uVar5 = (uint)mpp[0x44] + (uint)mpp[0x45] * 0x100;
	uVar4 = (ushort)uVar5;
	pXVar7->XMChannels = uVar4;
	pXVar7->numpat = (ushort)mpp[0x46] + (ushort)mpp[0x47] * 0x100;
	pXVar7->numins = (ushort)mpp[0x48] + (ushort)mpp[0x49] * 0x100;
	pXVar7->flags = (ushort)mpp[0x4a] + (ushort)mpp[0x4b] * 0x100;
	pXVar7->tempo = (ushort)mpp[0x4c] + (ushort)mpp[0x4d] * 0x100;
	bVar1 = mpp[0x4e];
	bVar2 = mpp[0x4f];
	pXVar7->XMPSXChannels = uVar4;
	pXVar7->bpm = (ushort)bVar1 + (ushort)bVar2 * 0x100;
	if (0x18 < (uVar5 & 0xffff)) {
		pXVar7->XMPSXChannels = 0x18;
	}
	iVar8 = 0;
	mpp_01 = mpp;
	if (mhu->songlength != 0) {
		do {
			mhu->jorders[iVar8] = mpp_01[0x50];
			iVar8 = iVar8 + 1;
			mpp_01 = mpp + iVar8;
		} while (iVar8 < (int)(uint)mhu->songlength);
	}
	iVar10 = 0x150;
	uVar4 = mhu->numpat;
	iVar8 = 0;
	if (uVar4 != 0) {
		do {
			mpp_00 = (_func_12 *)(mpp + iVar10);
			iVar9 = iVar8 + 1;
			mhu->JAP_PAT_ADDR[iVar8] = mpp_00;
			uVar3 = GetLong((uchar *)mpp_00);
			*(_func_12 **)(mhu->JAP_PAT_ADDR2 + iVar8) = mpp_00 + uVar3;
			iVar10 = iVar10 + uVar3 + *(ushort *)(mpp_00 + 7);
			iVar8 = iVar9;
		} while (iVar9 < (int)(uint)uVar4);
	}
	uVar5 = (uint)mhu->numins;
	iVar8 = 0;
	if (mhu->numins != 0) {
		do {
			mpp_01 = mpp + iVar10;
			uVar3 = GetLong(mpp_01);
			pXVar7 = mhu;
			uVar4 = *(ushort *)(mpp_01 + 0x1b);
			if (uVar4 == 0) {
				puVar6 = (uchar *)0x1234567;
				*(undefined4 *)((int)mhu->JAP_SampAddr + iVar8) = 0xcdcdcdcd;
			}
			else {
				puVar6 = mpp + iVar10 + uVar3;
				*(uchar **)((int)mhu->JAP_SampAddr + iVar8) = mpp + iVar10 + 0x1d;
				uVar3 = uVar3 + (uint)uVar4 * 0x28;
			}
			*(uchar **)((int)pXVar7->JAP_SampHdrAddr + iVar8) = puVar6;
			iVar10 = iVar10 + uVar3;
			uVar5 = uVar5 - 1;
			*(uchar **)((int)mhu->JAP_InstrumentOffset + iVar8) = mpp_01;
			iVar8 = iVar8 + 4;
		} while (uVar5 != 0);
	}
	return (uint)mhu->XMPSXChannels;
	*/
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ GetLong(unsigned char *mpp /*$a0*/)
 // line 568, offset 0x000869c0
	/* begin block 1 */
		// Start line: 569
		// Start offset: 0x000869C0
	/* end block 1 */
	// End offset: 0x000869EC
	// End Line: 584

	/* begin block 2 */
		// Start line: 1136
	/* end block 2 */
	// End Line: 1137

	/* begin block 3 */
		// Start line: 17264
	/* end block 3 */
	// End Line: 17265

ulong GetLong(unsigned char *mpp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	return (uint)*mpp + (uint)mpp[1] * 0x100 + (uint)mpp[2] * 0x10000 + (uint)mpp[3] * 0x1000000;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_OnceOffInit(int PAL /*$a0*/)
 // line 592, offset 0x00085f7c
	/* begin block 1 */
		// Start line: 913
	/* end block 1 */
	// End Line: 914

	/* begin block 2 */
		// Start line: 7171
	/* end block 2 */
	// End Line: 7172

	/* begin block 3 */
		// Start line: 7172
	/* end block 3 */
	// End Line: 7173

	/* begin block 4 */
		// Start line: 7179
	/* end block 4 */
	// End Line: 7180

void XM_OnceOffInit(int PAL)
{
	UNIMPLEMENTED();
	/*
	if (PAL == 0) {
		XM_NSA = 0;
		PALType = 0;
		BPMLimit = 0x96;
		JP_Do_Nothing = 0;
		return;
	}
	if (PAL == 1) {
		PALType = PAL;
	}
	XM_NSA = 0;
	BPMLimit = 0x96;
	JP_Do_Nothing = 0;
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ XM_Init(int VabID /*$s5*/, int XM_ID /*$s4*/, int SongID /*$s0*/, int FirstCh /*$s2*/, int Loop /*stack 16*/, int PlayMask /*stack 20*/, int PlayType /*stack 24*/, int SFXNum /*stack 28*/)
 // line 627, offset 0x0008344c
	/* begin block 1 */
		// Start line: 628
		// Start offset: 0x0008344C
		// Variables:
	// 		int i; // $s1
	// 		int pmsk; // $v1
	// 		int Chn; // $s0
	// 		int t; // $a2
	// 		int SngID; // $s3
	// 		int fr; // $a3
	/* end block 1 */
	// End offset: 0x0008392C
	// End Line: 778

	/* begin block 2 */
		// Start line: 1208
	/* end block 2 */
	// End Line: 1209

	/* begin block 3 */
		// Start line: 1315
	/* end block 3 */
	// End Line: 1316

int XM_Init(int VabID, int XM_ID, int SongID, int FirstCh, int Loop, int PlayMask, int PlayType, int SFXNum)
{
	UNIMPLEMENTED();
	return 0;
	/*
	ushort uVar1;
	bool bVar2;
	XMSONG *pXVar3;
	XMSONG *pXVar4;
	XMCHANNEL *pXVar5;
	uchar *puVar6;
	short *psVar7;
	XMHEADER *pXVar8;
	short *psVar9;
	int Channel;
	uint uVar10;
	int iVar11;

	if (SongID == -1) {
		SongID = GetFreeSongID();
		if (SongID == -1) {
			return -1;
		}
	}
	else {
		if (XM_NSA <= SongID) {
			return -1;
		}
		XM_Quit(SongID);
		(&XMSongIDs)[SongID] = 0;
	}
	mu = (XMSONG *)(&XM_SngAddress24)[SongID];
	mhu = (XMHEADER *)XM_HeaderAddress8[XM_ID];
	JP_Do_Nothing = 1;
	mu->XMPlay = '\0';
	pXVar3 = mu;
	mu->VabID = (uchar)VabID;
	pXVar4 = mu;
	pXVar3->JUp = 0;
	pXVar4->Status = (uchar)(PlayType & 0x7fU);
	pXVar3 = mu;
	pXVar4->SongLoop = Loop;
	pXVar4->PlayMask = PlayMask;
	pXVar8 = mhu;
	pXVar4->SFXNum = SFXNum;
	pXVar3->HeaderNum = XM_ID;
	pXVar3->JBPM = 0;
	pXVar3->PCounter = 3;
	uVar1 = pXVar8->restart;
	pXVar3->repcnt = 0;
	pXVar3->CurPos = 0;
	pXVar3->SongPos = 0;
	pXVar3->reppos = uVar1;
	if ((PlayType & 0x7fU) == 0) {
		pXVar3->SongPos = (short)SFXNum;
		pXVar3->CurrentStart = SFXNum;
	}
	pXVar8 = mhu;
	pXVar3 = mu;
	uVar1 = mhu->tempo;
	mu->SongSpeed = uVar1;
	pXVar3->vbtick = uVar1;
	pXVar3->SongBPM = pXVar8->bpm;
	uVar1 = pXVar8->flags;
	pXVar3->patdly = '\0';
	pXVar4 = mu;
	pXVar3->NotAmiga = (uint)uVar1;
	pXVar4->patdly2 = '\0';
	mu->SongVolume = -0x80;
	mu->MasterVolume = -0x80;
	pXVar3 = mu;
	mu->PlayNext = -1;
	pXVar3->BPlayNext = -1;
	pXVar3->FirstCh = FirstCh;
	pXVar3->PatternPos = 0;
	pXVar3->posjmp = 1;
	pXVar3->patbrk = 0;
	pXVar3->BPlayFlag = 0;
	pXVar3->UserPan = 0;
	pXVar3->MaxChans = '\0';
	pXVar8 = mhu;
	if (FirstCh == -1) {
		uVar10 = 0;
		if (mhu->XMPSXChannels != 0) {
			iVar11 = 0x58;
			do {
				pXVar5 = (XMCHANNEL *)(&mu->Status + iVar11);
				if ((mu->PlayMask & 1 << (uVar10 & 0x1f)) != 0) {
					bVar2 = false;
					Channel = 0;
					psVar7 = &XMSPU_SFX;
					psVar9 = psVar7;
					do {
						XMCU = pXVar5;
						if (*psVar7 == 0) {
							*psVar9 = (short)SongID + 1;
							pXVar5->SPUChannel = (uchar)Channel;
							mu->MaxChans = mu->MaxChans + '\x01';
							InitSPUChannel(Channel);
							bVar2 = true;
							break;
						}
						psVar7 = psVar7 + 1;
						Channel = Channel + 1;
						psVar9 = psVar9 + 1;
					} while (Channel < 0x18);
					if (!bVar2) {
						JPClearSPUFlags(SongID + 1);
						(&XMSongIDs)[SongID] = -1;
						JP_Do_Nothing = 0;
						return -2;
					}
				}
				iVar11 = iVar11 + 0x78;
				uVar10 = uVar10 + 1;
				pXVar8 = mhu;
			} while ((int)uVar10 < (int)(uint)mhu->XMPSXChannels);
		}
	}
	else {
		uVar10 = 0;
		if (mhu->XMPSXChannels != 0) {
			iVar11 = 0x58;
			do {
				if ((mu->PlayMask & 1 << (uVar10 & 0x1f)) != 0) {
					XMCU = (XMCHANNEL *)(&mu->Status + iVar11);
					((XMCHANNEL *)(&mu->Status + iVar11))->SPUChannel = (uchar)FirstCh;
					mu->MaxChans = mu->MaxChans + '\x01';
					if (FirstCh < 0x18) {
						InitSPUChannel(FirstCh);
					}
					FirstCh = FirstCh + 1;
					pXVar8 = mhu;
				}
				uVar10 = uVar10 + 1;
				iVar11 = iVar11 + 0x78;
			} while ((int)uVar10 < (int)(uint)pXVar8->XMPSXChannels);
		}
	}
	iVar11 = 0;
	if (pXVar8->XMChannels != 0) {
		Channel = 0;
		do {
			puVar6 = &mu->Status;
			(puVar6 + Channel)[0x99] = '\0';
			pXVar3 = mu;
			*(undefined2 *)(puVar6 + Channel + 0xb2) = 0;
			(&pXVar3->XM_Chnl[0].tmpvolume)[Channel] = '@';
			(&mu->XM_Chnl[0].retrig)[Channel] = '\0';
			(&mu->XM_Chnl[0].wavecontrol)[Channel] = '\0';
			(&mu->XM_Chnl[0].glissando)[Channel] = '\0';
			(&mu->XM_Chnl[0].panning)[Channel] = -0x80;
			(&mu->XM_Chnl[0].note)[Channel] = '\0';
			(&mu->XM_Chnl[0].vol)[Channel] = '\0';
			(&mu->XM_Chnl[0].eff)[Channel] = '\0';
			(&mu->XM_Chnl[0].dat)[Channel] = '\0';
			(&mu->XM_Chnl[0].ins)[Channel] = '\0';
			(&mu->XM_Chnl[0].ChDead)[Channel] = '\x01';
			(&mu->XM_Chnl[0].nothing)[Channel] = '\x01';
			puVar6 = &mu->Status + Channel;
			puVar6[0x9a] = -2;
			pXVar3 = mu;
			*(undefined2 *)(puVar6 + 0x5e) = 0xffff;
			*(undefined2 *)(puVar6 + 0x60) = 0xffff;
			*(undefined2 *)(puVar6 + 0x62) = 0;
			(&pXVar3->XM_Chnl[0].OldSample)[Channel] = -1;
			(&mu->XM_Chnl[0].Dolby)[Channel] = '\0';
			iVar11 = iVar11 + 1;
			Channel = Channel + 0x78;
		} while (iVar11 < (int)(uint)mhu->XMChannels);
	}
	if (PlayType < 0x80) {
		mu->XMPlay = '\x01';
	}
	JP_Do_Nothing = 0;
	return SongID;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ JPlayNote(unsigned char *j /*$s0*/, int pmsk /*$s3*/)
 // line 788, offset 0x0008392c
	/* begin block 1 */
		// Start line: 789
		// Start offset: 0x0008392C
		// Variables:
	// 		unsigned char b; // $s1
	// 		int ret; // $s2
	// 		unsigned char note; // $s4
	/* end block 1 */
	// End offset: 0x00083B64
	// End Line: 876

	/* begin block 2 */
		// Start line: 1754
	/* end block 2 */
	// End Line: 1755

	/* begin block 3 */
		// Start line: 1765
	/* end block 3 */
	// End Line: 1766

	/* begin block 4 */
		// Start line: 1772
	/* end block 4 */
	// End Line: 1773

int JPlayNote(unsigned char *j, int pmsk)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	uchar *puVar2;
	int iVar3;
	uchar uVar4;

	bVar1 = *j;
	iVar3 = 1;
	XMC->eff = '\0';
	uVar4 = '\0';
	XMC->vol = '\0';
	XMC->dat = '\0';
	if (bVar1 == 0x80) {
		iVar3 = 1;
		XMC->nothing = '\x01';
	}
	else {
		puVar2 = j + 1;
		if ((bVar1 & 0x80) == 0) {
			XMC->nothing = '\0';
			if (pmsk != 0) {
				SetNote(bVar1 - 1);
				XMC->ins = *puVar2;
				SetInstr(XMC->ins + -1);
				if (bVar1 != 0x61) {
					SetPer();
				}
				XMC->vol = j[2];
				XMC->eff = j[3];
				XMC->dat = j[4];
			}
			iVar3 = 5;
		}
		else {
			if ((bVar1 & 1) != 0) {
				if (pmsk != 0) {
					XMC->nothing = '\0';
					uVar4 = *puVar2;
					SetNote(uVar4 + -1);
				}
				puVar2 = j + 2;
				iVar3 = 2;
			}
			if ((bVar1 & 2) != 0) {
				if (pmsk != 0) {
					XMC->ins = *puVar2;
					SetInstr(XMC->ins + -1);
				}
				puVar2 = puVar2 + 1;
				iVar3 = iVar3 + 1;
			}
			if ((((bVar1 & 3) != 0) && (uVar4 != 'a')) && (pmsk != 0)) {
				SetPer();
			}
			if ((bVar1 & 4) != 0) {
				iVar3 = iVar3 + 1;
				XMC->nothing = '\0';
				uVar4 = *puVar2;
				puVar2 = puVar2 + 1;
				XMC->vol = uVar4;
			}
			if ((bVar1 & 8) != 0) {
				iVar3 = iVar3 + 1;
				XMC->nothing = '\0';
				uVar4 = *puVar2;
				puVar2 = puVar2 + 1;
				XMC->eff = uVar4;
			}
			if ((bVar1 & 0x10) != 0) {
				iVar3 = iVar3 + 1;
				XMC->dat = *puVar2;
			}
		}
	}
	return iVar3;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ JPlayEffects()
 // line 885, offset 0x00083b64
	/* begin block 1 */
		// Start line: 887
		// Start offset: 0x00083B64
		// Variables:
	// 		unsigned char vol; // $a1
	// 		unsigned char eff; // $s1
	// 		unsigned char dat; // $s0
	/* end block 1 */
	// End offset: 0x00083DA4
	// End Line: 1004

	/* begin block 2 */
		// Start line: 1982
	/* end block 2 */
	// End Line: 1983

	/* begin block 3 */
		// Start line: 1992
	/* end block 3 */
	// End Line: 1993

	/* begin block 4 */
		// Start line: 1993
	/* end block 4 */
	// End Line: 1994

	/* begin block 5 */
		// Start line: 1999
	/* end block 5 */
	// End Line: 2000

/* WARNING: Unknown calling convention yet parameter storage is locked */

void JPlayEffects(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte eff;
	uchar dat;
	XMCHANNEL *pXVar2;
	uchar eff_00;
	uint uVar3;

	pXVar2 = XMC;
	bVar1 = XMC->vol;
	uVar3 = (uint)bVar1;
	eff = XMC->eff;
	dat = XMC->dat;
	XMC->ownper = 0;
	pXVar2->ownvol = 0;
	switch (bVar1 >> 4) {
	case 6:
		if ((bVar1 & 0xf) != 0) {
			SPE('\n', bVar1 & 0xf);
		}
		break;
	case 7:
		if ((bVar1 & 0xf) == 0) break;
		eff_00 = '\n';
		goto LAB_00083c88;
	case 8:
		SPE('\x0e', bVar1 & 0xf | 0xb0);
		break;
	case 9:
		SPE('\x0e', bVar1 & 0xf | 0xa0);
		break;
	case 10:
		eff_00 = '\x04';
		goto LAB_00083c88;
	case 0xb:
		SPE('\x04', bVar1 & 0xf);
		break;
	case 0xc:
		XMC->panning = bVar1 << 4;
		break;
	case 0xd:
		if ((bVar1 & 0xf) != 0) {
			DoXMPanSlide(bVar1 & 0xf);
		}
		break;
	case 0xe:
		if ((bVar1 & 0xf) != 0) {
			DoXMPanSlide((uchar)((uVar3 & 0xf) << 4));
		}
		break;
	case 0xf:
		eff_00 = '\x03';
	LAB_00083c88:
		SPE(eff_00, (uchar)((uVar3 & 0xf) << 4));
		break;
	default:
		uVar3 = uVar3 - 0x10 & 0xff;
		if (uVar3 < 0x41) {
			SPE('\f', (uchar)uVar3);
		}
	}
	switch (eff) {
	case 0x10:
		ms->SongVolume = dat << 1;
		break;
	case 0x11:
	case 0x15:
	case 0x21:
		break;
	default:
		if (eff < 0x10) {
			SPE(eff, dat);
		}
		break;
	case 0x14:
		SetNote('`');
		break;
	case 0x19:
		XMC->panning = dat;
		break;
	case 0x1b:
		DoS3MRetrig(dat);
		break;
	case 0x1d:
		SPE('\x06', dat);
	}
	if (XMC->ownper == 0) {
		XMC->period = XMC->tmpperiod;
	}
	if (XMC->ownvol == 0) {
		XMC->volume = XMC->tmpvolume;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SPE(unsigned char eff /*$a0*/, unsigned char dat /*$s0*/)
 // line 1012, offset 0x00083da4
	/* begin block 1 */
		// Start line: 1013
		// Start offset: 0x00083DA4
		// Variables:
	// 		int hi; // $v1
	// 		int lo; // $a0
	/* end block 1 */
	// End offset: 0x000841B0
	// End Line: 1174

	/* begin block 2 */
		// Start line: 2237
	/* end block 2 */
	// End Line: 2238

	/* begin block 3 */
		// Start line: 2246
	/* end block 3 */
	// End Line: 2247

void SPE(unsigned char eff, unsigned char dat)
{
	UNIMPLEMENTED();
	/*
	ushort *puVar1;
	XMSONG *pXVar2;
	uint uVar3;
	uint uVar4;
	ushort uVar5;

	pXVar2 = ms;
	uVar3 = (uint)dat;
	if (0xf < eff) {
		return;
	}
	uVar5 = (ushort)dat;
	switch (eff) {
	case '\0':
		Arpeggio(dat);
		break;
	case '\x01':
		if (dat != '\0') {
			XMC->slidespeed = (ushort)dat << 2;
		}
		if (ms->vbtick != 0) {
			XMC->tmpperiod = XMC->tmpperiod - XMC->slidespeed;
		}
		break;
	case '\x02':
		if (dat != '\0') {
			XMC->slidespeed = (ushort)dat << 2;
		}
		if (ms->vbtick != 0) {
			XMC->tmpperiod = XMC->tmpperiod + XMC->slidespeed;
		}
		break;
	case '\x03':
		XMC->kick = '\0';
		if (dat != '\0') {
			XMC->portspeed = (ushort)dat << 2;
		}
		DoToneSlide();
		goto LAB_00083f30;
	case '\x04':
		if ((dat & 0xf) != 0) {
			XMC->vibdepth = dat & 0xf;
		}
		if ((dat & 0xf0) != 0) {
			XMC->vibspd = (uchar)((uVar3 & 0xf0) >> 2);
		}
		DoVibrato();
		goto LAB_00083f30;
	case '\x05':
		XMC->kick = '\0';
		DoToneSlide();
		goto LAB_00083f0c;
	case '\x06':
		DoVibrato();
	LAB_00083f0c:
		if (dat == '\0') {
			dat = XMC->oldvslide;
		}
		XMC->oldvslide = dat;
		DoVolSlide(dat);
	LAB_00083f30:
		XMC->ownper = 1;
		break;
	case '\a':
		if ((dat & 0xf) != 0) {
			XMC->trmdepth = dat & 0xf;
		}
		if ((dat & 0xf0) != 0) {
			XMC->trmspd = (uchar)((uVar3 & 0xf0) >> 2);
		}
		DoTremolo();
		XMC->ownvol = 1;
		break;
	case '\b':
		XMC->panning = dat;
		break;
	case '\t':
		if ((ms->vbtick == 0) && (dat != '\0')) {
			uVar4 = (uVar3 * 0x200) / 7;
			XMC->SOffset = (uVar4 + (uVar3 * 0x200 - uVar4 >> 1) >> 2 & 0x7ffffff0) << 1;
		}
		break;
	case '\n':
		if (dat == '\0') {
			dat = XMC->oldvslide;
		}
		XMC->oldvslide = dat;
		DoVolSlide(dat);
		break;
	case '\v':
		if (ms->patdly2 == '\0') {
			ms->patbrk = 0;
			pXVar2->SongPos = uVar5 - 1;
			pXVar2->posjmp = 2;
		}
		break;
	case '\f':
		if (ms->vbtick == 0) {
			if (dat == -1) {
				ms->BPlayFlag = 1;
			}
			else {
				if (dat == -2) {
					ms->BPlayFlag = 0;
				}
				else {
					if (dat == -3) {
						ms->BPlayFlag = 2;
					}
					else {
						if (dat == -4) {
							XMC->Dolby = '\0';
						}
						else {
							if (dat == -5) {
								XMC->Dolby = '\x01';
							}
							else {
								if (dat == -6) {
									XMC->Dolby = '\x02';
								}
								else {
									if (0x40 < dat) {
										dat = '@';
									}
									XMC->tmpvolume = dat + '@';
								}
							}
						}
					}
				}
			}
		}
		break;
	case '\r':
		if (ms->patdly2 == '\0') {
			puVar1 = &ms->numrow;
			uVar3 = (uint)(dat >> 4) * 10 + (uVar3 & 0xf) + 1;
			ms->patbrk = (ushort)uVar3;
			uVar4 = (uint)*puVar1 + 1;
			if (uVar4 < uVar3) {
				pXVar2->patbrk = (ushort)uVar4;
			}
			ms->posjmp = 2;
		}
		break;
	case '\x0e':
		DoEEffects(dat);
		break;
	case '\x0f':
		if ((ms->vbtick == 0) && (ms->patdly2 == '\0')) {
			if (dat < 0x20) {
				ms->SongSpeed = uVar5;
			}
			else {
				ms->SongBPM = uVar5;
			}
			pXVar2->vbtick = 0;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoEEffects(unsigned char dat /*$a0*/)
 // line 1182, offset 0x000841b0
	/* begin block 1 */
		// Start line: 1183
		// Start offset: 0x000841B0
		// Variables:
	// 		unsigned char nib; // $a1
	/* end block 1 */
	// End offset: 0x00084524
	// End Line: 1320

	/* begin block 2 */
		// Start line: 2585
	/* end block 2 */
	// End Line: 2586

	/* begin block 3 */
		// Start line: 2594
	/* end block 3 */
	// End Line: 2595

void DoEEffects(unsigned char dat)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;

	_bVar1 = (uint)dat & 0xf;
	bVar1 = (byte)_bVar1;
	_bVar1 = (ushort)_bVar1;
	switch (dat >> 4) {
	case '\x01':
		if (ms->vbtick == 0) {
			if ((dat & 0xf) == 0) {
				_bVar1 = (ushort)XMC->oldfslide;
			}
			XMC->oldfslide = (uchar)_bVar1;
			XMC->tmpperiod = XMC->tmpperiod + _bVar1 * 4;
			return;
		}
		break;
	case '\x02':
		if (ms->vbtick == 0) {
			if ((dat & 0xf) == 0) {
				_bVar1 = (ushort)XMC->oldfslide;
			}
			XMC->oldfslide = (uchar)_bVar1;
			XMC->tmpperiod = XMC->tmpperiod + _bVar1 * -4;
			return;
		}
		break;
	case '\x03':
		XMC->glissando = bVar1;
		return;
	case '\x04':
		XMC->wavecontrol = XMC->wavecontrol & 0xf0;
		XMC->wavecontrol = bVar1 | XMC->wavecontrol;
		return;
	case '\x06':
		if (ms->vbtick == 0) {
			if ((dat & 0xf) == 0) {
				ms->reppos = ms->PatternPos - 1;
				return;
			}
			if (ms->repcnt == 0) {
				ms->repcnt = _bVar1;
			}
			else {
				ms->repcnt = ms->repcnt - 1;
			}
			if (ms->repcnt != 0) {
				ms->PatternPos = ms->reppos;
				return;
			}
		}
		break;
	case '\a':
		XMC->wavecontrol = XMC->wavecontrol & 0xf;
		XMC->wavecontrol = XMC->wavecontrol | (byte)(_bVar1 << 4);
		return;
	case '\b':
		XMC->panning = (uchar)(_bVar1 << 4);
		return;
	case '\t':
		if ((dat & 0xf) != 0) {
			if (XMC->retrig == '\0') {
				XMC->kick = '\x01';
				XMC->retrig = bVar1;
			}
			XMC->retrig = XMC->retrig + -1;
			return;
		}
		break;
	case '\n':
		if (ms->vbtick == 0) {
			if ((dat & 0xf) == 0) {
				bVar1 = XMC->oldfvslide;
			}
			XMC->oldfvslide = bVar1;
			XMC->tmpvolume = bVar1 + XMC->tmpvolume;
			if (0x80 < (byte)XMC->tmpvolume) {
				XMC->tmpvolume = -0x80;
				return;
			}
		}
		break;
	case '\v':
		if (ms->vbtick == 0) {
			if ((dat & 0xf) == 0) {
				bVar1 = XMC->oldfvslide;
			}
			XMC->oldfvslide = bVar1;
			XMC->tmpvolume = XMC->tmpvolume - bVar1;
			if ((byte)XMC->tmpvolume < 0x40) goto LAB_00084490;
		}
		break;
	case '\f':
		if (_bVar1 <= ms->vbtick) {
		LAB_00084490:
			XMC->tmpvolume = '@';
			return;
		}
		break;
	case '\r':
		if ((uint)ms->vbtick == _bVar1) {
			XMC->kick = '\x01';
			return;
		}
		XMC->kick = '\0';
		return;
	case '\x0e':
		if ((ms->vbtick == 0) && (ms->patdly2 == '\0')) {
			ms->patdly = bVar1 + 1;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetNote(unsigned char note /*$a0*/)
 // line 1328, offset 0x000868e0
	/* begin block 1 */
		// Start line: 1329
		// Start offset: 0x000868E0
		// Variables:
	// 		unsigned char *j; // $a0
	/* end block 1 */
	// End offset: 0x000869B8
	// End Line: 1363

	/* begin block 2 */
		// Start line: 2656
	/* end block 2 */
	// End Line: 2657

	/* begin block 3 */
		// Start line: 17986
	/* end block 3 */
	// End Line: 17987

void SetNote(unsigned char note)
{
	UNIMPLEMENTED();
	/*
	if (CurrentCh < 0x18) {
		if (note == '`') {
			XMC->keyon = '\0';
			if ((XMC->sample == -2) || (((byte)mh->JAP_InstrumentOffset[XMC->sample][0xe9] & 1) == 0)) {
				XMC->tmpvolume = '@';
				return;
			}
		}
		else {
			XMC->note = note;
			XMC->kick = '\x01';
			if ((XMC->wavecontrol & 0x80) == 0) {
				XMC->trmpos = '\0';
			}
			if ((XMC->wavecontrol & 8) == 0) {
				XMC->vibpos = '\0';
			}
		}
	}
	return;*/
}



// autogenerated function stub: 
// void /*$ra*/ SetInstr(unsigned char inst /*$a0*/)
void SetInstr(unsigned char inst)
{
	UNIMPLEMENTED();
	/*
	// line 1372, offset 0x000867e4
	/* begin block 1 */
		// Start line: 1373
		// Start offset: 0x000867E4
		// Variables:
	//unsigned long *j; // $a2
/* end block 1 */
// End offset: 0x000868D8
// End Line: 1433

/* begin block 2 */
	// Start line: 17965
/* end block 2 */
// End Line: 17966

/* begin block 3 */
	// Start line: 2744
/* end block 3 */
// End Line: 2745

/* begin block 4 */
	// Start line: 17975
/* end block 4 */
// End Line: 17976

}


// decompiled code
// original method signature: 
// void /*$ra*/ SetPer()
 // line 1448, offset 0x00084524
	/* begin block 1 */
		// Start line: 1450
		// Start offset: 0x00084524
		// Variables:
	// 		unsigned long *j; // $a1
	/* end block 1 */
	// End offset: 0x000846C8
	// End Line: 1509

	/* begin block 2 */
		// Start line: 2997
	/* end block 2 */
	// End Line: 2998

	/* begin block 3 */
		// Start line: 3126
	/* end block 3 */
	// End Line: 3127

	/* begin block 4 */
		// Start line: 3127
	/* end block 4 */
	// End Line: 3128

	/* begin block 5 */
		// Start line: 3130
	/* end block 5 */
	// End Line: 3131

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetPer(void)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	uchar uVar2;
	XMCHANNEL *pXVar3;
	ushort uVar4;
	_func_14 *p_Var5;

	if (0x17 < CurrentCh) {
		return;
	}
	uVar4 = GetPeriod(XMC->note + XMC->transpose, XMC->c2spd);
	pXVar3 = XMC;
	uVar1 = XMC->sample;
	uVar2 = XMC->OldSample;
	XMC->wantedperiod = uVar4;
	pXVar3->tmpperiod = uVar4;
	pXVar3->OldPeriod = 0;
	pXVar3->SOffset = 0;
	if (uVar2 != uVar1) {
		pXVar3->OldSample = uVar1;
		pXVar3 = XMC;
		p_Var5 = mh->JAP_InstrumentOffset[XMC->sample];
		XMC->keyoffspd = (ushort)(byte)p_Var5[0xef];
		*(_func_14 *)&pXVar3->envflg = p_Var5[0xe9];
		if ((XMC->envflg & 1) != 0) {
			*(_func_14 *)&XMC->envpts = p_Var5[0xe1];
			*(_func_14 *)&XMC->envsus = p_Var5[0xe3];
			*(_func_14 *)&XMC->envbeg = p_Var5[0xe4];
			*(_func_14 *)&XMC->envend = p_Var5[0xe5];
		}
		*(_func_14 *)&XMC->panenvflg = p_Var5[0xea];
		if ((XMC->panenvflg & 1) == 0) goto code_r0x000846a8;
		*(_func_14 *)&XMC->panenvpts = p_Var5[0xe2];
		*(_func_14 *)&XMC->panenvsus = p_Var5[0xe6];
		*(_func_14 *)&XMC->panenvbeg = p_Var5[0xe7];
		*(_func_14 *)&XMC->panenvend = p_Var5[0xe8];
	}
	pXVar3 = XMC;
	if ((XMC->panenvflg & 1) != 0) {
		XMC->panenvp = 0;
		pXVar3->panenva = 0;
		pXVar3->panenvb = 1;
	}
code_r0x000846a8:
	pXVar3 = XMC;
	if ((XMC->envflg & 1) != 0) {
		XMC->envp = 0;
		pXVar3->enva = 0;
		pXVar3->envb = 1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ Arpeggio(unsigned char dat /*$a1*/)
 // line 1517, offset 0x00086738
	/* begin block 1 */
		// Start line: 1518
		// Start offset: 0x00086738
		// Variables:
	// 		unsigned char note; // $a2
	/* end block 1 */
	// End offset: 0x000867E4
	// End Line: 1537

	/* begin block 2 */
		// Start line: 3034
	/* end block 2 */
	// End Line: 3035

	/* begin block 3 */
		// Start line: 18091
	/* end block 3 */
	// End Line: 18092

void Arpeggio(unsigned char dat)
{
	UNIMPLEMENTED();
	/*
	XMCHANNEL *pXVar1;
	byte bVar2;
	ushort uVar3;
	uint uVar4;
	uchar uVar5;

	uVar5 = XMC->note;
	if (dat == '\0') {
		return;
	}
	uVar4 = (uint)ms->vbtick;
	uVar4 = uVar4 - (((uint)((ulonglong)uVar4 * 0xaaaaaaab >> 0x20) & 0xfffffffe) + uVar4 / 3) &
		0xffff;
	if (uVar4 == 1) {
		bVar2 = dat >> 4;
	}
	else {
		bVar2 = dat & 0xf;
		if (uVar4 != 2) goto LAB_000867ac;
	}
	uVar5 = uVar5 + bVar2;
LAB_000867ac:
	uVar3 = GetPeriod(uVar5 + XMC->transpose, XMC->c2spd);
	pXVar1 = XMC;
	XMC->period = uVar3;
	pXVar1->ownper = 1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoVolSlide(unsigned char dat /*$a1*/)
 // line 1545, offset 0x000865b4
	/* begin block 1 */
		// Start line: 3090
	/* end block 1 */
	// End Line: 3091

	/* begin block 2 */
		// Start line: 17935
	/* end block 2 */
	// End Line: 17936

void DoVolSlide(unsigned char dat)
{
	UNIMPLEMENTED();
	/*
	if (ms->vbtick != 0) {
		XMC->tmpvolume = XMC->tmpvolume + (dat >> 4);
		if (0x80 < (byte)XMC->tmpvolume) {
			XMC->tmpvolume = -0x80;
		}
		XMC->tmpvolume = XMC->tmpvolume - (dat & 0xf);
		if ((byte)XMC->tmpvolume < 0x40) {
			XMC->tmpvolume = '@';
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoXMPanSlide(unsigned char inf /*$a0*/)
 // line 1561, offset 0x000866ac
	/* begin block 1 */
		// Start line: 1562
		// Start offset: 0x000866AC
		// Variables:
	// 		unsigned char lo; // $v0
	// 		unsigned char hi; // $a0
	// 		short pan; // $v1
	/* end block 1 */
	// End offset: 0x00086730
	// End Line: 1588

	/* begin block 2 */
		// Start line: 18106
	/* end block 2 */
	// End Line: 18107

	/* begin block 3 */
		// Start line: 3122
	/* end block 3 */
	// End Line: 3123

void DoXMPanSlide(unsigned char inf)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	uchar uVar2;
	int iVar3;
	uint uVar4;

	uVar4 = (uint)inf;
	if (inf == '\0') {
		uVar4 = (uint)XMC->pansspd;
	}
	else {
		XMC->pansspd = inf;
	}
	uVar1 = uVar4 & 0xf;
	if (ms->vbtick != 0) {
		if (uVar4 >> 4 != 0) {
			uVar1 = 0;
		}
		iVar3 = (XMC->panning - uVar1) + (uVar4 >> 4);
		uVar2 = (uchar)iVar3;
		if (iVar3 < 0) {
			uVar2 = '\0';
		}
		if (0xff < iVar3) {
			uVar2 = -1;
		}
		XMC->panning = uVar2;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoS3MRetrig(unsigned char inf /*$a0*/)
 // line 1596, offset 0x000846d8
	/* begin block 1 */
		// Start line: 1597
		// Start offset: 0x000846D8
		// Variables:
	// 		unsigned char hi; // $a1
	/* end block 1 */
	// End offset: 0x000848F0
	// End Line: 1672

	/* begin block 2 */
		// Start line: 3434
	/* end block 2 */
	// End Line: 3435

void DoS3MRetrig(unsigned char inf)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;

	bVar1 = inf >> 4;
	if ((inf & 0xf) != 0) {
		XMC->s3mrtgslide = bVar1;
		XMC->s3mrtgspeed = inf & 0xf;
	}
	if (bVar1 != 0) {
		XMC->s3mrtgslide = bVar1;
	}
	if (XMC->s3mrtgspeed == '\0') {
		return;
	}
	if (XMC->retrig != '\0') goto code_r0x000848d8;
	XMC->kick = '\x01';
	XMC->retrig = XMC->s3mrtgspeed;
	if (ms->vbtick == 0) goto code_r0x000848d8;
	switch (XMC->s3mrtgslide) {
	case '\x01':
	case '\x02':
	case '\x03':
	case '\x04':
	case '\x05':
		XMC->tmpvolume = XMC->tmpvolume - (char)(1 << ((uint)XMC->s3mrtgslide - 1 & 0x1f));
		break;
	case '\x06':
		XMC->tmpvolume = (char)((int)((uint)(byte)XMC->tmpvolume << 1) / 3);
		break;
	case '\a':
		XMC->tmpvolume = (byte)XMC->tmpvolume >> 1;
		if ((byte)XMC->tmpvolume < 0x40) {
			XMC->tmpvolume = '@';
			break;
		}
		goto code_r0x000848b8;
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
		XMC->tmpvolume = XMC->tmpvolume + (char)(1 << ((uint)XMC->s3mrtgslide - 9 & 0x1f));
		break;
	case '\x0e':
		XMC->tmpvolume = (char)((int)((uint)(byte)XMC->tmpvolume * 3) >> 1);
		break;
	case '\x0f':
		XMC->tmpvolume = XMC->tmpvolume << 1;
	}
	if ((byte)XMC->tmpvolume < 0x40) {
		XMC->tmpvolume = '@';
	}
code_r0x000848b8:
	if (0x80 < (byte)XMC->tmpvolume) {
		XMC->tmpvolume = -0x80;
	}
code_r0x000848d8:
	XMC->retrig = XMC->retrig + -1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoToneSlide()
 // line 1680, offset 0x00086644
	/* begin block 1 */
		// Start line: 1682
		// Start offset: 0x00086644
		// Variables:
	// 		int dist; // $v1
	/* end block 1 */
	// End offset: 0x000866AC
	// End Line: 1702

	/* begin block 2 */
		// Start line: 18204
	/* end block 2 */
	// End Line: 18205

	/* begin block 3 */
		// Start line: 18205
	/* end block 3 */
	// End Line: 18206

	/* begin block 4 */
		// Start line: 18210
	/* end block 4 */
	// End Line: 18211

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DoToneSlide(void)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	ushort uVar2;
	int iVar3;
	int iVar4;

	iVar4 = (uint)XMC->period - (uint)XMC->wantedperiod;
	if (iVar4 != 0) {
		uVar1 = XMC->portspeed;
		iVar3 = iVar4;
		if (iVar4 < 0) {
			iVar3 = -iVar4;
		}
		if ((int)(uint)uVar1 <= iVar3) {
			uVar2 = -uVar1;
			if (iVar4 < 1) {
				uVar2 = uVar1;
			}
			XMC->period = XMC->period + uVar2;
			goto LAB_00086698;
		}
	}
	XMC->period = XMC->wantedperiod;
LAB_00086698:
	XMC->tmpperiod = XMC->period;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoVibrato()
 // line 1710, offset 0x000848f0
	/* begin block 1 */
		// Start line: 1712
		// Start offset: 0x000848F0
		// Variables:
	// 		unsigned char q; // $a1
	// 		unsigned short temp; // $a2
	/* end block 1 */
	// End offset: 0x000849F0
	// End Line: 1746

	/* begin block 2 */
		// Start line: 3623
	/* end block 2 */
	// End Line: 3624

	/* begin block 3 */
		// Start line: 3662
	/* end block 3 */
	// End Line: 3663

	/* begin block 4 */
		// Start line: 3663
	/* end block 4 */
	// End Line: 3664

	/* begin block 5 */
		// Start line: 3666
	/* end block 5 */
	// End Line: 3667

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DoVibrato(void)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	byte bVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = 0;
	uVar3 = (uint)((byte)XMC->vibpos >> 2) & 0x1f;
	bVar2 = XMC->wavecontrol & 3;
	if (bVar2 == 1) {
		uVar4 = uVar3 << 3;
		if ((int)((uint)(byte)XMC->vibpos << 0x18) < 0) {
			uVar4 = uVar4 ^ 0xff;
		}
	}
	else {
		if (bVar2 < 2) {
			if ((XMC->wavecontrol & 3) == 0) {
				uVar4 = (uint)VibratoTable[uVar3];
			}
		}
		else {
			if (bVar2 == 2) {
				uVar4 = 0xff;
			}
		}
	}
	uVar1 = (ushort)(uVar4 * XMC->vibdepth >> 5) & 0x7fc;
	if (XMC->vibpos < '\0') {
		uVar1 = XMC->tmpperiod - uVar1;
	}
	else {
		uVar1 = uVar1 + XMC->tmpperiod;
	}
	XMC->period = uVar1;
	if (ms->vbtick != 0) {
		XMC->vibpos = XMC->vibpos + XMC->vibspd;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoTremolo()
 // line 1754, offset 0x000849f0
	/* begin block 1 */
		// Start line: 1756
		// Start offset: 0x000849F0
		// Variables:
	// 		unsigned char q; // $a2
	// 		unsigned short temp; // $a3
	/* end block 1 */
	// End offset: 0x00084B3C
	// End Line: 1794

	/* begin block 2 */
		// Start line: 3749
	/* end block 2 */
	// End Line: 3750

	/* begin block 3 */
		// Start line: 3758
	/* end block 3 */
	// End Line: 3759

	/* begin block 4 */
		// Start line: 3759
	/* end block 4 */
	// End Line: 3760

	/* begin block 5 */
		// Start line: 3762
	/* end block 5 */
	// End Line: 3763

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DoTremolo(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	char cVar2;
	byte bVar3;
	uint uVar4;
	uint uVar5;

	uVar4 = (uint)((byte)XMC->trmpos >> 2) & 0x1f;
	bVar1 = XMC->wavecontrol >> 4;
	bVar3 = bVar1 & 3;
	uVar5 = 0;
	if (bVar3 == 1) {
		uVar5 = uVar4 << 3;
		if ((int)((uint)(byte)XMC->trmpos << 0x18) < 0) {
			uVar5 = uVar5 ^ 0xff;
		}
	}
	else {
		if (bVar3 < 2) {
			if ((bVar1 & 3) == 0) {
				uVar5 = (uint)VibratoTable[uVar4];
			}
		}
		else {
			if (bVar3 == 2) {
				uVar5 = 0xff;
			}
		}
	}
	cVar2 = (char)(uVar5 * XMC->trmdepth >> 6);
	if (XMC->trmpos < '\0') {
		XMC->volume = XMC->tmpvolume - cVar2;
		if ((byte)XMC->volume < 0x40) {
			XMC->volume = '@';
		}
	}
	else {
		XMC->volume = XMC->tmpvolume + cVar2;
		if (0x80 < (byte)XMC->volume) {
			XMC->volume = -0x80;
		}
	}
	if (ms->vbtick != 0) {
		XMC->trmpos = XMC->trmpos + XMC->trmspd;
	}
	return;*/
}



// decompiled code
// original method signature: 
// short /*$ra*/ DoPan(short envpan /*$a0*/, short pan /*$a1*/)
 // line 1802, offset 0x00086560
	/* begin block 1 */
		// Start line: 3604
	/* end block 1 */
	// End Line: 3605

short DoPan(short envpan, short pan)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	iVar1 = (int)pan + -0x80;
	if (iVar1 < 0) {
		iVar1 = -iVar1;
	}
	iVar1 = ((int)envpan + -0x80) * (0x80 - iVar1);
	if (iVar1 < 0) {
		iVar1 = iVar1 + 0x7f;
	}
	return (short)((uint)(((int)pan + (iVar1 >> 7)) * 0x10000) >> 0x10);*/
}



// decompiled code
// original method signature: 
// short /*$ra*/ DoVol(unsigned long a /*$v0*/, short b /*$a1*/, short c /*$a2*/)
 // line 1817, offset 0x00086538
	/* begin block 1 */
		// Start line: 3634
	/* end block 1 */
	// End Line: 3635

short DoVol(ulong a, short b, short c)
{
	return (short)(a * (int)b * (int)c >> 0x17);
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateXMData()
 // line 1831, offset 0x00086484
	/* begin block 1 */
		// Start line: 1833
		// Start offset: 0x00086484
		// Variables:
	// 		int SC; // $s0
	/* end block 1 */
	// End offset: 0x00086520
	// End Line: 1851

	/* begin block 2 */
		// Start line: 16634
	/* end block 2 */
	// End Line: 16635

	/* begin block 3 */
		// Start line: 18185
	/* end block 3 */
	// End Line: 18186

	/* begin block 4 */
		// Start line: 18186
	/* end block 4 */
	// End Line: 18187

	/* begin block 5 */
		// Start line: 18190
	/* end block 5 */
	// End Line: 18191

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdateXMData(void)
{
	UNIMPLEMENTED();
	/*
	int SC;
	uchar **ppuVar1;

	XMTime3 = 0;
	XMTime2 = 0;
	XMTime1 = 0;
	if ((JP_Do_Nothing == 0) && (SC = 0, 0 < XM_NSA)) {
		ppuVar1 = &XM_SngAddress24;
		do {
			ms = (XMSONG *)*ppuVar1;
			UpdateWithTimer(SC);
			if (ms->PCounter == 5) {
				UpdateWithTimer(SC);
				ms->PCounter = 0;
			}
			SC = SC + 1;
			ppuVar1 = (uchar **)((XMSONG **)ppuVar1 + 1);
		} while (SC < XM_NSA);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateWithTimer(int SC /*$a3*/)
 // line 1855, offset 0x0008607c
	/* begin block 1 */
		// Start line: 3710
	/* end block 1 */
	// End Line: 3711

void UpdateWithTimer(int SC)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	bool bVar2;
	XMSONG *pXVar3;
	int iVar4;
	int iVar5;

	ms = (XMSONG *)(&XM_SngAddress24)[SC];
	aa = aa + 1;
	bVar1 = ms->XMPlay;
	if (bVar1 == 1) {
		if (PALType == (uint)bVar1) {
			ms->PCounter = ms->PCounter + 1;
		}
		iVar4 = BPMLimit;
		pXVar3 = ms;
		mh = (XMHEADER *)XM_HeaderAddress8[ms->HeaderNum];
		iVar5 = ms->JBPM + (uint)ms->SongBPM;
		bVar2 = iVar5 < BPMLimit;
		ms->JBPM = iVar5;
		if (bVar2) {
			if ((pXVar3->JUp == 0) && (PALType != 0)) {
				pXVar3->JUp = (uint)bVar1;
				UpdateEffs();
				ApplyEffs();
				UpdateHardware();
			}
		}
		else {
			pXVar3->JBPM = iVar5 - iVar4;
			XM_DoFullUpdate(SC);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_DoFullUpdate(int SC /*$s1*/)
 // line 1887, offset 0x00086178
	/* begin block 1 */
		// Start line: 11819
	/* end block 1 */
	// End Line: 11820

void XM_DoFullUpdate(int SC)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;

	ms = (XMSONG *)(&XM_SngAddress24)[SC];
	bVar1 = ms->XMPlay;
	if (bVar1 == 1) {
		mh = (XMHEADER *)XM_HeaderAddress8[ms->HeaderNum];
		if (ms->JUp == 0) {
			UpdateEffs();
			ApplyEffs();
		}
		ms->JUp = 0;
		UpdateHardware();
		if ((uint)ms->vbtick == (uint)bVar1) {
			CurrentKeyStat();
		}
		UpdatePatternData(SC);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdatePatternData(int SC /*$a0*/)
 // line 1921, offset 0x00084b3c
	/* begin block 1 */
		// Start line: 1922
		// Start offset: 0x00084B3C
		// Variables:
	// 		int SP; // $s1
	// 		int t; // $s0
	// 		int pmsk; // $a2
	// 		int FindOffset; // $t0
	// 		unsigned char *pataddr; // $a0
	// 		unsigned char patdat; // $a1
	/* end block 1 */
	// End offset: 0x00085018
	// End Line: 2095

	/* begin block 2 */
		// Start line: 3969
	/* end block 2 */
	// End Line: 3970

	/* begin block 3 */
		// Start line: 4097
	/* end block 3 */
	// End Line: 4098

	/* begin block 4 */
		// Start line: 4103
	/* end block 4 */
	// End Line: 4104

void UpdatePatternData(int SC)
{
	UNIMPLEMENTED();
	/*
	ushort *puVar1;
	short *psVar2;
	bool bVar3;
	uchar uVar4;
	byte bVar5;
	short sVar6;
	XMHEADER *pXVar7;
	XMSONG *pXVar8;
	XMSONG *pXVar9;
	ushort uVar10;
	int iVar11;
	int iVar12;
	ulong *puVar13;
	int iVar14;
	uint uVar15;
	uint uVar16;

	pXVar8 = ms;
	puVar1 = &ms->SongSpeed;
	uVar10 = ms->vbtick + 1;
	ms->vbtick = uVar10;
	if (uVar10 < *puVar1) {
		return;
	}
	pXVar8->vbtick = 0;
	pXVar8->PatternPos = pXVar8->PatternPos + 1;
	if (pXVar8->patdly != '\0') {
		pXVar8->patdly2 = pXVar8->patdly;
		ms->patdly = '\0';
	}
	uVar4 = ms->patdly2;
	if ((uVar4 != '\0') && (ms->patdly2 = uVar4 + -1, uVar4 != '\x01')) {
		ms->PatternPos = ms->PatternPos - 1;
	}
	bVar3 = false;
	if (ms->PatternPos == ms->numrow) {
		ms->posjmp = 2;
	}
	if (ms->BPlayFlag == 2) {
	LAB_00084c54:
		XM_Quit(SC);
		return;
	}
	if (ms->posjmp == 0) goto LAB_00084e30;
	if ((ms->posjmp == 2) && (ms->Status == '\x01')) {
		if (ms->patbrk == 0) goto LAB_00084c54;
	LAB_00084c74:
		ms->PatternPos = ms->patbrk - 1;
	}
	else {
		if (ms->patbrk != 0) goto LAB_00084c74;
		ms->PatternPos = 0;
	}
	pXVar8 = ms;
	bVar3 = ms->PatternPos != 0;
	ms->CurPos = (uint)ms->PatternPos;
	pXVar9 = ms;
	if (((int)pXVar8->BPlayNext == -1) || (pXVar8->BPlayFlag == 0)) {
		psVar2 = &ms->PlayNext;
		if ((int)*psVar2 == -1) {
			ms->SongPos = ms->posjmp + ms->SongPos + -1;
		}
		else {
			ms->SongPos = ms->PlayNext;
			pXVar9->CurrentStart = (int)*psVar2;
			pXVar9->PlayNext = -1;
		}
	}
	else {
		pXVar8->BPlayFlag = 0;
		pXVar8->SongPos = pXVar8->BPlayNext;
		pXVar8->CurrentStart = (int)pXVar8->BPlayNext;
		pXVar8->BPlayNext = -1;
	}
	pXVar8 = ms;
	pXVar7 = mh;
	sVar6 = ms->SongPos;
	ms->posjmp = 0;
	pXVar8->patbrk = 0;
	if ((int)(uint)pXVar7->songlength <= (int)sVar6) {
		if (pXVar8->SongLoop == 0) {
			pXVar8->XMPlay = '\0';
			return;
		}
		pXVar8->SongPos = pXVar8->reppos;
	}
	if (ms->SongPos < 0) {
		ms->SongPos = mh->songlength - 1;
	}
	pXVar8 = ms;
	if (ms->Status == '\0') {
		uVar16 = (uint)mh->jorders[ms->SongPos];
	}
	else {
		uVar16 = ms->SFXNum;
	}
	puVar1 = &mh->version;
	ms->CurrentPattern = (ushort)uVar16;
	puVar13 = *(ulong **)(puVar1 + uVar16 * 2 + 0xc);
	pXVar8->PatAdr = puVar13;
	pXVar8->PatAdr2 = *(ulong **)(puVar1 + uVar16 * 2 + 0x20c);
	pXVar8->numrow = (ushort)*(byte *)((int)puVar13 + 5) + (ushort)*(byte *)((int)puVar13 + 6) * 0x100
		;
	pXVar8->PatSize = (ushort)*(byte *)((int)puVar13 + 7) + (ushort)*(byte *)(puVar13 + 2) * 0x100;
LAB_00084e30:
	if ((ms->patdly2 == '\0') && (ms->PatSize != 0)) {
		if (mh->version == 0xddba) {
			if (bVar3) {
				iVar11 = PACKEDCalcPlayPos(ms->CurPos);
				ms->CurPos = iVar11;
			}
			iVar11 = ms->CurPos;
			iVar14 = 0;
			if (mh->XMPSXChannels != 0) {
				iVar12 = 0x58;
				do {
					XMC = (XMCHANNEL *)(&ms->Status + iVar12);
					XMC->eff = '\0';
					XMC->vol = '\0';
					XMC->dat = '\0';
					iVar14 = iVar14 + 1;
					iVar12 = iVar12 + 0x78;
				} while (iVar14 < (int)(uint)mh->XMPSXChannels);
			}
			bVar5 = *(byte *)((int)ms->PatAdr2 + iVar11);
			while (iVar11 = iVar11 + 1, bVar5 != 0xff) {
				CurrentCh = ZEXT14(bVar5);
				XMC = ms->XM_Chnl + CurrentCh;
				iVar14 = JPlayNote((uchar *)((int)ms->PatAdr2 + iVar11),
					ms->PlayMask & 1 << (CurrentCh & 0x1fU));
				iVar11 = iVar11 + iVar14;
				bVar5 = *(byte *)((int)ms->PatAdr2 + iVar11);
			}
		}
		else {
			if (bVar3) {
				iVar11 = CalcPlayPos(ms->CurPos);
				ms->CurPos = iVar11;
			}
			iVar11 = ms->CurPos;
			if (mh->XMChannels != 0) {
				iVar14 = 0x58;
				uVar16 = 0;
				do {
					uVar15 = uVar16 + 1;
					XMC = (XMCHANNEL *)(&ms->Status + iVar14);
					CurrentCh = uVar16;
					iVar12 = JPlayNote((uchar *)((int)ms->PatAdr2 + iVar11),
						ms->PlayMask & 1 << (uVar16 & 0x1f));
					iVar14 = iVar14 + 0x78;
					iVar11 = iVar11 + iVar12;
					uVar16 = uVar15;
				} while ((int)uVar15 < (int)(uint)mh->XMChannels);
			}
		}
		ms->CurPos = iVar11;
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcPlayPos(int StartPos /*$s4*/)
 // line 2099, offset 0x00087024
	/* begin block 1 */
		// Start line: 2100
		// Start offset: 0x00087024
		// Variables:
	// 		int SP; // $s1
	// 		int t; // $s0
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x000870DC
	// End Line: 2114

	/* begin block 2 */
		// Start line: 23323
	/* end block 2 */
	// End Line: 23324

	/* begin block 3 */
		// Start line: 4198
	/* end block 3 */
	// End Line: 4199

	/* begin block 4 */
		// Start line: 23327
	/* end block 4 */
	// End Line: 23328

int CalcPlayPos(int StartPos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar2 = 0;
	iVar4 = 0;
	if (0 < StartPos) {
		do {
			iVar2 = iVar2 + 1;
			if (mh->XMChannels != 0) {
				iVar5 = 0x58;
				iVar1 = 0;
				do {
					iVar3 = iVar1 + 1;
					XMC = (XMCHANNEL *)(&ms->Status + iVar5);
					CurrentCh = iVar1;
					iVar1 = JCalcPat((uchar *)((int)ms->PatAdr2 + iVar4));
					iVar5 = iVar5 + 0x78;
					iVar4 = iVar4 + iVar1;
					iVar1 = iVar3;
				} while (iVar3 < (int)(uint)mh->XMChannels);
			}
		} while (iVar2 < StartPos);
	}
	return iVar4;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ PACKEDCalcPlayPos(int StartPos /*$s3*/)
 // line 2116, offset 0x0008714c
	/* begin block 1 */
		// Start line: 2117
		// Start offset: 0x0008714C
		// Variables:
	// 		int SP; // $s0
	// 		int i; // $a1
	// 		unsigned char *pataddr; // $a0
	// 		unsigned char patdat; // $v1
	/* end block 1 */
	// End offset: 0x00087228
	// End Line: 2139

	/* begin block 2 */
		// Start line: 23441
	/* end block 2 */
	// End Line: 23442

	/* begin block 3 */
		// Start line: 4232
	/* end block 3 */
	// End Line: 4233

	/* begin block 4 */
		// Start line: 23447
	/* end block 4 */
	// End Line: 23448

int PACKEDCalcPlayPos(int StartPos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar3 = 0;
	iVar4 = 0;
	if (0 < StartPos) {
		do {
			iVar3 = iVar3 + 1;
			bVar1 = *(byte *)((int)ms->PatAdr2 + iVar4);
			while (iVar4 = iVar4 + 1, bVar1 != 0xff) {
				CurrentCh = ZEXT14(bVar1);
				XMC = ms->XM_Chnl + CurrentCh;
				iVar2 = JCalcPat((uchar *)((int)ms->PatAdr2 + iVar4));
				iVar4 = iVar4 + iVar2;
				bVar1 = *(byte *)((int)ms->PatAdr2 + iVar4);
			}
		} while (iVar3 < StartPos);
	}
	return iVar4;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ JCalcPat(unsigned char *j /*$a0*/)
 // line 2143, offset 0x000870dc
	/* begin block 1 */
		// Start line: 2145
		// Start offset: 0x000870DC
		// Variables:
	// 		unsigned char b; // $v1
	// 		int ret; // $a1
	/* end block 1 */
	// End offset: 0x0008714C
	// End Line: 2187

	/* begin block 2 */
		// Start line: 23395
	/* end block 2 */
	// End Line: 23396

	/* begin block 3 */
		// Start line: 23425
	/* end block 3 */
	// End Line: 23426

	/* begin block 4 */
		// Start line: 23426
	/* end block 4 */
	// End Line: 23427

	/* begin block 5 */
		// Start line: 23429
	/* end block 5 */
	// End Line: 23430

int JCalcPat(unsigned char *j)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	int iVar2;

	bVar1 = *j;
	iVar2 = 1;
	if (bVar1 == 0x80) {
		return 1;
	}
	if ((bVar1 & 0x80) == 0) {
		iVar2 = 5;
	}
	else {
		if ((bVar1 & 1) != 0) {
			iVar2 = 2;
		}
		if ((bVar1 & 2) != 0) {
			iVar2 = iVar2 + 1;
		}
		if ((bVar1 & 4) != 0) {
			iVar2 = iVar2 + 1;
		}
		if ((bVar1 & 8) != 0) {
			iVar2 = iVar2 + 1;
		}
		if ((bVar1 & 0x10) != 0) {
			iVar2 = iVar2 + 1;
		}
	}
	return iVar2;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ApplyEffs()
 // line 2195, offset 0x00085034
	/* begin block 1 */
		// Start line: 2197
		// Start offset: 0x00085034
		// Variables:
	// 		short envpan; // $s2
	// 		short envvol; // $s1
	// 		int t; // $s3
	// 		int pmsk; // $v1
	// 		short vlm; // $s0
	// 		short Pn; // $a1
	// 		unsigned char MaxChans; // $s4
	/* end block 1 */
	// End offset: 0x00085350
	// End Line: 2281

	/* begin block 2 */
		// Start line: 4703
	/* end block 2 */
	// End Line: 4704

	/* begin block 3 */
		// Start line: 4704
	/* end block 3 */
	// End Line: 4705

	/* begin block 4 */
		// Start line: 4711
	/* end block 4 */
	// End Line: 4712

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ApplyEffs(void)
{
	UNIMPLEMENTED();
	/*
	XMHEADER *pXVar1;
	XMSONG *pXVar2;
	short b;
	short envpan;
	undefined2 extraout_var;
	int iVar3;
	XMCHANNEL *pXVar4;
	int iVar5;
	uint uVar6;
	uchar uVar7;
	int iVar8;
	int iVar9;

	pXVar2 = ms;
	pXVar1 = mh;
	ms->XMActiveVoices = 0;
	uVar7 = pXVar2->MaxChans;
	uVar6 = 0;
	if (pXVar1->XMPSXChannels != 0) {
		iVar8 = 0x58;
		do {
			if (uVar7 == '\0') {
				return;
			}
			pXVar4 = (XMCHANNEL *)(&ms->Status + iVar8);
			if ((ms->PlayMask & 1 << (uVar6 & 0x1f)) != 0) {
				uVar7 = uVar7 + -1;
				XMC = pXVar4;
				if (pXVar4->kick != '\0') {
					pXVar4->keyon = '\x01';
					pXVar4 = XMC;
					XMC->fadevol = 0x7fff;
					pXVar4->ChDead = '\0';
				}
				pXVar4 = XMC;
				if (XMC->ChDead == '\0') {
					ms->XMActiveVoices = ms->XMActiveVoices + 1;
					if (pXVar4->period == 0) {
						pXVar4->period = 1;
					}
					else {
						if (0x8000 < pXVar4->period) {
							pXVar4->period = 0x8000;
						}
					}
					b = 0x100;
					if ((XMC->envflg & 1) != 0) {
						b = ProcessEnvelope(0x100, XMC->keyon, (uint)XMC->sample);
					}
					envpan = 0x80;
					if ((XMC->panenvflg & 1) != 0) {
						envpan = ProcessPanEnvelope(0x80, XMC->keyon, (uint)XMC->sample);
					}
					pXVar4 = XMC;
					iVar9 = ((uint)(byte)XMC->volume - 0x40) * (0x40 - (int)XMC->UserVol);
					if (iVar9 < 0) {
						iVar9 = iVar9 + 0x3f;
					}
					iVar9 = (((iVar9 << 10) >> 0x10) + 0x40) * 0x10000 >> 0x10;
					if (iVar9 < 0x41) {
						XMC->RVol = 0;
						pXVar4->LVol = 0;
					}
					else {
						b = DoVol((int)XMC->fadevol, b, (short)((uint)((iVar9 + -0x40) * 0x10000) >> 0x10));
						iVar9 = CONCAT22(extraout_var, b) * (uint)ms->SongVolume;
						if (iVar9 < 0) {
							iVar9 = iVar9 + 0x7f;
						}
						iVar9 = (int)(short)((short)((uint)(iVar9 * 0x200) >> 0x10) * (ushort)ms->MasterVolume);
						if (iVar9 < 0) {
							iVar9 = iVar9 + 0x7f;
						}
						iVar3 = ((uint)XMC->panning + (uint)(ushort)ms->UserPan) * 0x10000;
						iVar5 = iVar3 >> 0x10;
						b = (short)((uint)iVar3 >> 0x10);
						if (iVar5 < 0) {
							b = 0;
						}
						else {
							if (0xff < iVar5) {
								b = 0xff;
							}
						}
						envpan = DoPan(envpan, b);
						pXVar4 = XMC;
						b = (short)(iVar9 >> 7);
						XMC->LVol = b * (0xff - envpan);
						pXVar4->RVol = b * envpan;
					}
					pXVar4 = XMC;
					if ((XMC->LVol == 0) && (XMC->RVol == 0)) {
						if (XMC->keyon == '\0') {
							StpCh((uint)XMC->SPUChannel);
							XMC->ChDead = '\x01';
						}
					}
					else {
						if ((XMC->keyon == '\0') &&
							(iVar9 = (uint)(ushort)XMC->fadevol - (uint)XMC->keyoffspd,
								XMC->fadevol = (short)iVar9, iVar9 * 0x10000 < 0)) {
							pXVar4->fadevol = 0;
						}
					}
				}
			}
			uVar6 = uVar6 + 1;
			iVar8 = iVar8 + 0x78;
		} while ((int)uVar6 < (int)(uint)mh->XMPSXChannels);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateEffs()
 // line 2289, offset 0x00086ebc
	/* begin block 1 */
		// Start line: 2291
		// Start offset: 0x00086EBC
		// Variables:
	// 		int t; // $s0
	// 		int pmsk; // $v1
	// 		unsigned char MaxChans; // $s1
	/* end block 1 */
	// End offset: 0x00086F54
	// End Line: 2313

	/* begin block 2 */
		// Start line: 22408
	/* end block 2 */
	// End Line: 22409

	/* begin block 3 */
		// Start line: 4578
	/* end block 3 */
	// End Line: 4579

	/* begin block 4 */
		// Start line: 22409
	/* end block 4 */
	// End Line: 22410

	/* begin block 5 */
		// Start line: 22414
	/* end block 5 */
	// End Line: 22415

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdateEffs(void)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	uint uVar2;
	uchar uVar3;
	int iVar4;

	uVar3 = ms->MaxChans;
	uVar2 = 0;
	if (mh->XMPSXChannels != 0) {
		iVar4 = 0x58;
		do {
			if (uVar3 == '\0') {
				return;
			}
			XMC = (XMCHANNEL *)(&ms->Status + iVar4);
			uVar1 = uVar3 + -1;
			if (((ms->PlayMask & 1 << (uVar2 & 0x1f)) != 0) && (uVar3 = uVar1, XMC->nothing == '\0')) {
				JPlayEffects();
			}
			uVar2 = uVar2 + 1;
			iVar4 = iVar4 + 0x78;
		} while ((int)uVar2 < (int)(uint)mh->XMPSXChannels);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoDolbySS()
 // line 2322, offset 0x00085374
	/* begin block 1 */
		// Start line: 5038
	/* end block 1 */
	// End Line: 5039

	/* begin block 2 */
		// Start line: 5039
	/* end block 2 */
	// End Line: 5040

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DoDolbySS(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	if (MonoMode == '\0') {
		DVL = ((int)XMC->OldLVol + (int)XMC->OldRVol) / 2;
		DVR = DVL;
		return;
	}
	if (XMC->Dolby == '\x01') {
		iVar1 = (int)XMC->OldRVol;
		if ((int)XMC->OldLVol < iVar1) {
			DVL = iVar1;
			DVR = -iVar1;
			return;
		}
		DVL = (int)XMC->OldLVol;
		DVR = -iVar1;
		return;
	}
	if (XMC->Dolby == '\x02') {
		DVR = (int)XMC->OldRVol;
		DVL = -DVR;
		if (DVR <= (int)XMC->OldLVol) {
			DVR = (int)XMC->OldLVol;
			return;
		}
	}
	else {
		DVL = (int)XMC->OldLVol;
		DVR = (int)XMC->OldRVol;
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetEmpty(int old /*$t1*/)
 // line 2368, offset 0x00087228
	/* begin block 1 */
		// Start line: 2369
		// Start offset: 0x00087228
		// Variables:
	// 		int i; // $a3
	// 		struct XMCHANNEL *j; // $a0
	/* end block 1 */
	// End offset: 0x000872F0
	// End Line: 2396

	/* begin block 2 */
		// Start line: 23979
	/* end block 2 */
	// End Line: 23980

	/* begin block 3 */
		// Start line: 23984
	/* end block 3 */
	// End Line: 23985

int GetEmpty(int old)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	XMCHANNEL *pXVar2;
	int iVar3;
	int iVar4;

	de = de + 1;
	if ((int)(uint)mh->XMPSXChannels <= de) {
		de = 0;
	}
	dd = de;
	iVar4 = 0;
	if (mh->XMPSXChannels != 0) {
		do {
			iVar3 = dd + 1;
			pXVar2 = ms->XM_Chnl + dd;
			dd = iVar3;
			if ((int)(uint)mh->XMPSXChannels <= iVar3) {
				dd = 0;
			}
			if ((pXVar2->kick == '\0') && (pXVar2->ChDead == '\x01')) {
				bVar1 = pXVar2->SPUChannel;
				pXVar2->SPUChannel = (uchar)old;
				return (uint)bVar1;
			}
			iVar4 = iVar4 + 1;
		} while (iVar4 < (int)(uint)mh->XMPSXChannels);
	}
	return -1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateHardware()
 // line 2398, offset 0x00085448
	/* begin block 1 */
		// Start line: 2400
		// Start offset: 0x00085448
		// Variables:
	// 		int t; // $s2
	// 		int prd; // $s0
	// 		int SPUKeyOn; // $s6
	// 		int pmsk; // $v1
	// 		int Chnl; // $s1
	// 		unsigned char MaxChans; // $s3
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x0008577C
	// End Line: 2503

	/* begin block 2 */
		// Start line: 5193
	/* end block 2 */
	// End Line: 5194

	/* begin block 3 */
		// Start line: 5194
	/* end block 3 */
	// End Line: 5195

	/* begin block 4 */
		// Start line: 5196
	/* end block 4 */
	// End Line: 5197

	/* begin block 5 */
		// Start line: 5203
	/* end block 5 */
	// End Line: 5204

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdateHardware(void)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	ushort *puVar2;
	byte bVar3;
	ushort uVar4;
	XMSONG *pXVar5;
	uint uVar6;
	XMCHANNEL *pXVar7;
	int Vol1;
	int Vol2;
	long Pitch;
	uint old;
	uint uVar8;
	uchar uVar9;
	int iVar10;
	uint uVar11;

	uVar11 = 0;
	uVar9 = ms->MaxChans;
	uVar8 = 0;
	if ((mh->XMPSXChannels != 0) && (uVar9 != '\0')) {
		iVar10 = 0x58;
		do {
			pXVar7 = (XMCHANNEL *)(&ms->Status + iVar10);
			if (((ms->PlayMask & 1 << (uVar8 & 0x1f)) != 0) &&
				(uVar9 = uVar9 + -1, XMC = pXVar7, pXVar7->kick != '\0')) {
				old = (uint)pXVar7->SPUChannel;
				SpuSetKey(0, 1 << (old & 0x1f));
				uVar6 = GetEmpty(old);
				if (uVar6 != 0xffffffff) {
					old = uVar6;
				}
				XMC->SPUChannel = (uchar)old;
				uVar4 = XMC->period;
				if (ms->NotAmiga == 0) {
					if (uVar4 == 0) {
						trap(7);
					}
					Pitch = 0xa3ba68 / (int)(uint)uVar4 >> 3;
				}
				else {
					Pitch = GetFreq2((uint)uVar4);
				}
				pXVar7 = XMC;
				psVar1 = &XMC->RVol;
				XMC->OldLVol = XMC->LVol;
				pXVar7->OldRVol = *psVar1;
				DoDolbySS();
				pXVar7 = XMC;
				pXVar5 = ms;
				uVar11 = uVar11 | 1 << (old & 0x1f);
				puVar2 = &XMC->period;
				bVar3 = XMC->sample;
				XMC->SPUPitch = (ushort)Pitch;
				pXVar7->OldPeriod = *puVar2;
				PlaySFX((uint)pXVar5->VabID, old, (uint)bVar3, Pitch, DVL, DVR);
			}
			uVar8 = uVar8 + 1;
			iVar10 = iVar10 + 0x78;
		} while (((int)uVar8 < (int)(uint)mh->XMPSXChannels) && (uVar9 != '\0'));
	}
	if (uVar11 != 0) {
		XMTime1 = 1;
		SpuSetKey(1, uVar11);
		SpuFlush(0);
		aa = 0;
	}
	uVar9 = ms->MaxChans;
	uVar8 = 0;
	if (mh->XMPSXChannels != 0) {
		iVar10 = 0x58;
		do {
			if (uVar9 == '\0') {
				return;
			}
			pXVar7 = (XMCHANNEL *)(&ms->Status + iVar10);
			if (((ms->PlayMask & 1 << (uVar8 & 0x1f)) != 0) &&
				(uVar9 = uVar9 + -1, XMC = pXVar7, pXVar7->ChDead == '\0')) {
				bVar3 = pXVar7->SPUChannel;
				if (pXVar7->kick == '\0') {
					Vol1 = (int)pXVar7->LVol;
					Vol2 = (int)pXVar7->OldLVol;
					if ((Vol1 != Vol2) || (pXVar7->RVol != pXVar7->OldRVol)) {
						if (Vol2 != Vol1) {
							Vol1 = IntVols(Vol1, Vol2);
							XMC->OldLVol = (short)Vol1;
						}
						if ((int)XMC->OldRVol != (int)XMC->RVol) {
							Vol1 = IntVols((int)XMC->RVol, (int)XMC->OldRVol);
							XMC->OldRVol = (short)Vol1;
						}
						DoDolbySS();
						SetVol((uint)bVar3, DVL, DVR);
					}
					pXVar7 = XMC;
					pXVar5 = ms;
					if (XMC->period != XMC->OldPeriod) {
						XMC->OldPeriod = XMC->period;
						uVar4 = pXVar7->period;
						if (pXVar5->NotAmiga == 0) {
							if (uVar4 == 0) {
								trap(7);
							}
							Pitch = 0xa3ba68 / (int)(uint)uVar4 >> 3;
						}
						else {
							Pitch = GetFreq2((uint)uVar4);
						}
						XMC->SPUPitch = (ushort)Pitch;
						SetFrq((uint)bVar3, Pitch);
					}
				}
				else {
					pXVar7->kick = '\0';
				}
			}
			uVar8 = uVar8 + 1;
			iVar10 = iVar10 + 0x78;
		} while ((int)uVar8 < (int)(uint)mh->XMPSXChannels);
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ IntVols(int Vol1 /*$a0*/, int Vol2 /*$a1*/)
 // line 2516, offset 0x00086f70
	/* begin block 1 */
		// Start line: 2517
		// Start offset: 0x00086F70
		// Variables:
	// 		int a; // $v1
	/* end block 1 */
	// End offset: 0x00086FA0
	// End Line: 2527

	/* begin block 2 */
		// Start line: 22879
	/* end block 2 */
	// End Line: 22880

	/* begin block 3 */
		// Start line: 22881
	/* end block 3 */
	// End Line: 22882

int IntVols(int Vol1, int Vol2)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	iVar1 = Vol2 - Vol1;
	if (iVar1 < 0) {
		iVar1 = -iVar1;
	}
	iVar1 = (iVar1 >> 2) + 1;
	if (Vol2 <= Vol1) {
		return Vol2 + iVar1;
	}
	return Vol1 + iVar1;*/
}



// decompiled code
// original method signature: 
// long /*$ra*/ GetFreq2(long period /*$v1*/)
 // line 2540, offset 0x00086af0
	/* begin block 1 */
		// Start line: 2542
		// Start offset: 0x00086AF0
		// Variables:
	// 		int okt; // $a1
	// 		long frequency; // $a0
	/* end block 1 */
	// End offset: 0x00086B48
	// End Line: 2556

	/* begin block 2 */
		// Start line: 19325
	/* end block 2 */
	// End Line: 19326

	/* begin block 3 */
		// Start line: 21559
	/* end block 3 */
	// End Line: 21560

	/* begin block 4 */
		// Start line: 21560
	/* end block 4 */
	// End Line: 21561

	/* begin block 5 */
		// Start line: 21565
	/* end block 5 */
	// End Line: 21566

long GetFreq2(long period)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;

	iVar1 = JPPer - period;
	iVar2 = (iVar1 / 6 + (iVar1 >> 0x1f) >> 7) - (iVar1 >> 0x1f);
	return (int)(uint)lintab[iVar1 + iVar2 * -0x300] >> (8U - iVar2 & 0x1f);*/
}



// decompiled code
// original method signature: 
// short /*$ra*/ ProcessEnvelope(short v /*$a2*/, unsigned char keyon /*$a1*/, int JSmp /*$a2*/)
 // line 2564, offset 0x000857a4
	/* begin block 1 */
		// Start line: 2565
		// Start offset: 0x000857A4
		// Variables:
	// 		unsigned char a2; // $s2
	// 		unsigned char b; // $s0
	// 		unsigned short p; // $s1
	// 		unsigned long *j; // $s5
	// 		short bpos; // $s3
	/* end block 1 */
	// End offset: 0x00085974
	// End Line: 2627

	/* begin block 2 */
		// Start line: 5630
	/* end block 2 */
	// End Line: 5631

	/* begin block 3 */
		// Start line: 5641
	/* end block 3 */
	// End Line: 5642

short ProcessEnvelope(short v, unsigned char keyon, int JSmp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	byte bVar2;
	XMCHANNEL *pXVar3;
	short sVar4;
	int iVar5;
	_func_14 *p_Var6;
	_func_14 *p_Var7;
	int iVar8;
	ushort uVar9;
	ushort uVar10;
	ushort uVar11;
	ushort uVar12;
	_func_14 *p_Var13;

	bVar1 = *(byte *)&XMC->enva;
	bVar2 = *(byte *)&XMC->envb;
	uVar9 = (ushort)bVar2;
	uVar11 = XMC->envp;
	p_Var13 = mh->JAP_InstrumentOffset[JSmp];
	p_Var6 = p_Var13 + (uint)bVar1 * 4;
	p_Var7 = p_Var13 + (uint)bVar2 * 4;
	iVar8 = ((uint)(byte)p_Var7[0x81] + (uint)(byte)p_Var7[0x82] * 0x100) * 0x10000;
	iVar5 = ((uint)(byte)p_Var6[0x81] + (uint)(byte)p_Var6[0x82] * 0x100) * 0x10000;
	sVar4 = Interpolate(XMC->envp, (short)((uint)iVar5 >> 0x10), (short)((uint)iVar8 >> 0x10),
		(short)(((uint)(byte)p_Var6[0x83] + (uint)(byte)p_Var6[0x84] * 0x100) *
			0x40000 >> 0x10),
			(int)(((uint)(byte)p_Var7[0x83] + (uint)(byte)p_Var7[0x84] * 0x100) * 0x40000)
		>> 0x10);
	pXVar3 = XMC;
	uVar12 = (ushort)bVar1;
	uVar10 = uVar9;
	if (((((XMC->envflg & 2) == 0) || (keyon == '\0')) || ((uint)bVar1 != (uint)XMC->envsus)) ||
		((uint)uVar11 != iVar5 >> 0x10)) {
		_uVar11 = (uint)uVar11 + 1 & 0xffff;
		uVar11 = (ushort)_uVar11;
		if (iVar8 >> 0x10 <= (int)_uVar11) {
			uVar12 = (ushort)bVar2;
			_uVar11 = (uint)bVar2 + 1 & 0xff;
			uVar10 = (ushort)_uVar11;
			if ((XMC->envflg & 4) == 0) {
				if (XMC->envpts <= _uVar11) {
					uVar10 = uVar10 - 1 & 0xff;
					uVar11 = uVar11 - 1;
				}
			}
			else {
				uVar12 = uVar9;
				if (XMC->envend < _uVar11) {
					bVar1 = XMC->envbeg;
					uVar12 = (ushort)bVar1;
					uVar10 = (ushort)bVar1 + 1 & 0xff;
					uVar11 = *(ushort *)(p_Var13 + (uint)bVar1 * 4 + 0x81);
				}
			}
		}
	}
	XMC->enva = uVar12;
	pXVar3->envp = uVar11;
	pXVar3->envb = uVar10;
	return sVar4;*/
}



// decompiled code
// original method signature: 
// short /*$ra*/ ProcessPanEnvelope(short v /*$a2*/, unsigned char keyon /*$a1*/, int JSmp /*$a2*/)
 // line 2635, offset 0x00085974
	/* begin block 1 */
		// Start line: 2636
		// Start offset: 0x00085974
		// Variables:
	// 		unsigned char a2; // $s2
	// 		unsigned char b; // $s0
	// 		unsigned short p; // $s1
	// 		unsigned long *j; // $s5
	// 		short bpos; // $s3
	/* end block 1 */
	// End offset: 0x00085B44
	// End Line: 2699

	/* begin block 2 */
		// Start line: 5807
	/* end block 2 */
	// End Line: 5808

	/* begin block 3 */
		// Start line: 5816
	/* end block 3 */
	// End Line: 5817

	/* begin block 4 */
		// Start line: 5828
	/* end block 4 */
	// End Line: 5829

short ProcessPanEnvelope(short v, unsigned char keyon, int JSmp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	byte bVar2;
	XMCHANNEL *pXVar3;
	short sVar4;
	int iVar5;
	_func_14 *p_Var6;
	_func_14 *p_Var7;
	int iVar8;
	ushort uVar9;
	ushort uVar10;
	ushort uVar11;
	ushort uVar12;
	_func_14 *p_Var13;

	bVar1 = *(byte *)&XMC->panenva;
	bVar2 = *(byte *)&XMC->panenvb;
	uVar9 = (ushort)bVar2;
	uVar11 = XMC->panenvp;
	p_Var13 = mh->JAP_InstrumentOffset[JSmp];
	p_Var6 = p_Var13 + (uint)bVar1 * 4;
	p_Var7 = p_Var13 + (uint)bVar2 * 4;
	iVar8 = ((uint)(byte)p_Var7[0xb1] + (uint)(byte)p_Var7[0xb2] * 0x100) * 0x10000;
	iVar5 = ((uint)(byte)p_Var6[0xb1] + (uint)(byte)p_Var6[0xb2] * 0x100) * 0x10000;
	sVar4 = Interpolate(XMC->panenvp, (short)((uint)iVar5 >> 0x10), (short)((uint)iVar8 >> 0x10),
		(short)(((uint)(byte)p_Var6[0xb3] + (uint)(byte)p_Var6[0xb4] * 0x100) *
			0x40000 >> 0x10),
			(int)(((uint)(byte)p_Var7[0xb3] + (uint)(byte)p_Var7[0xb4] * 0x100) * 0x40000)
		>> 0x10);
	pXVar3 = XMC;
	uVar12 = (ushort)bVar1;
	uVar10 = uVar9;
	if (((((XMC->panenvflg & 2) == 0) || (keyon == '\0')) || ((uint)bVar1 != (uint)XMC->panenvsus)) ||
		((uint)uVar11 != iVar5 >> 0x10)) {
		_uVar11 = (uint)uVar11 + 1 & 0xffff;
		uVar11 = (ushort)_uVar11;
		if (iVar8 >> 0x10 <= (int)_uVar11) {
			uVar12 = (ushort)bVar2;
			_uVar11 = (uint)bVar2 + 1 & 0xff;
			uVar10 = (ushort)_uVar11;
			if ((XMC->panenvflg & 4) == 0) {
				if (XMC->panenvpts <= _uVar11) {
					uVar10 = uVar10 - 1 & 0xff;
					uVar11 = uVar11 - 1;
				}
			}
			else {
				uVar12 = uVar9;
				if (XMC->panenvend < _uVar11) {
					bVar1 = XMC->panenvbeg;
					uVar12 = (ushort)bVar1;
					uVar10 = (ushort)bVar1 + 1 & 0xff;
					uVar11 = *(ushort *)(p_Var13 + (uint)bVar1 * 4 + 0xb1);
				}
			}
		}
	}
	XMC->panenva = uVar12;
	pXVar3->panenvp = uVar11;
	pXVar3->panenvb = uVar10;
	return sVar4;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_SetSongPos(int Song_ID /*$a2*/, unsigned short pos /*$a1*/)
 // line 2707, offset 0x00085e8c
	/* begin block 1 */
		// Start line: 2708
		// Start offset: 0x00085E8C
		// Variables:
	// 		int t; // $a2
	/* end block 1 */
	// End offset: 0x00085F74
	// End Line: 2736

	/* begin block 2 */
		// Start line: 8973
	/* end block 2 */
	// End Line: 8974

void XM_SetSongPos(int Song_ID, ushort pos)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	XMSONG *pXVar2;
	int iVar3;
	int iVar4;

	if ((&XMSongIDs)[Song_ID] != -1) {
		mu = (XMSONG *)(&XM_SngAddress24)[Song_ID];
		mhu = (XMHEADER *)XM_HeaderAddress8[mu->HeaderNum];
		if (pos < mhu->songlength) {
			iVar3 = 0;
			if (mhu->XMChannels != 0) {
				iVar4 = 0x58;
				do {
					XMCU = (XMCHANNEL *)(&mu->Status + iVar4);
					XMCU->keyon = '\0';
					XMCU->tmpvolume = '@';
					iVar3 = iVar3 + 1;
					iVar4 = iVar4 + 0x78;
				} while (iVar3 < (int)(uint)mhu->XMChannels);
			}
			pXVar2 = mu;
			uVar1 = mu->SongSpeed;
			mu->posjmp = 1;
			pXVar2->patbrk = 0;
			pXVar2->SongPos = pos;
			pXVar2->vbtick = uVar1;
			JP_Do_Nothing = 0;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaySFX(int VBID /*$a0*/, int Channel /*$a1*/, int Inst /*$a2*/, int Pitch /*$a3*/, int LV /*stack 16*/, int RV /*stack 20*/)
 // line 3003, offset 0x00086c64
	/* begin block 1 */
		// Start line: 3004
		// Start offset: 0x00086C64
	/* end block 1 */
	// End offset: 0x00086CF8
	// End Line: 3026

	/* begin block 2 */
		// Start line: 6006
	/* end block 2 */
	// End Line: 6007

	/* begin block 3 */
		// Start line: 22619
	/* end block 3 */
	// End Line: 22620

void PlaySFX(int VBID, int Channel, int Inst, int Pitch, int LV, int RV)
{
	UNIMPLEMENTED();
	/*
	xm_g_s_attr.voice = 1 << (Channel & 0x1fU);
	xm_g_s_attr.mask = 0x10093;
	xm_g_s_attr.pitch = (ushort)Pitch;
	xm_g_s_attr.volume.left = (short)LV;
	xm_g_s_attr.volume.right = (short)RV;
	xm_g_s_attr.addr = (&xm_l_vag_spu_addr)[VBID * 0x80 + Inst] + XMC->SOffset;
	xm_g_s_attr.loop_addr = (&xm_l_vag_spu_addr)[VBID * 0x80 + Inst] + XMC->SOffset;
	SpuSetVoiceAttr(&xm_g_s_attr);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSPUChannel(int Channel /*$a0*/)
 // line 3035, offset 0x00086d74
	/* begin block 1 */
		// Start line: 6070
	/* end block 1 */
	// End Line: 6071

	/* begin block 2 */
		// Start line: 22998
	/* end block 2 */
	// End Line: 22999

void InitSPUChannel(int Channel)
{
	UNIMPLEMENTED();
	/*
	xm_g_s_attr.voice = 1 << (Channel & 0x1fU);
	xm_g_s_attr.mask = 0xff80;
	xm_g_s_attr.r_mode = 3;
	xm_g_s_attr.a_mode = 1;
	xm_g_s_attr.s_mode = 1;
	xm_g_s_attr.ar = 4;
	xm_g_s_attr.dr = 0;
	xm_g_s_attr.sr = 0;
	xm_g_s_attr.rr = 1;
	xm_g_s_attr.sl = 0xf;
	SpuSetVoiceAttr(&xm_g_s_attr);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CurrentKeyStat()
 // line 3068, offset 0x00086b48
	/* begin block 1 */
		// Start line: 3070
		// Start offset: 0x00086B48
		// Variables:
	// 		int t; // $a1
	// 		char KeyStat[24]; // stack offset -32
	/* end block 1 */
	// End offset: 0x00086BF4
	// End Line: 3083

	/* begin block 2 */
		// Start line: 22112
	/* end block 2 */
	// End Line: 22113

	/* begin block 3 */
		// Start line: 22625
	/* end block 3 */
	// End Line: 22626

	/* begin block 4 */
		// Start line: 22626
	/* end block 4 */
	// End Line: 22627

	/* begin block 5 */
		// Start line: 22629
	/* end block 5 */
	// End Line: 22630

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CurrentKeyStat(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	char acStack32[24];

	SpuGetAllKeysStatus(acStack32);
	iVar1 = 0;
	if (mh->XMPSXChannels != 0) {
		iVar2 = 0x58;
		do {
			XMC = (XMCHANNEL *)(&ms->Status + iVar2);
			if ((acStack32[XMC->SPUChannel] != '\x01') && (XMC->ChDead == '\0')) {
				XMC->ChDead = '\x01';
				XMC->nothing = '\x01';
			}
			iVar1 = iVar1 + 1;
			iVar2 = iVar2 + 0x78;
		} while (iVar1 < (int)(uint)mh->XMPSXChannels);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StpCh(int Channel /*$a0*/)
 // line 3091, offset 0x00086bf4
	/* begin block 1 */
		// Start line: 22668
	/* end block 1 */
	// End Line: 22669

	/* begin block 2 */
		// Start line: 22677
	/* end block 2 */
	// End Line: 22678

	/* begin block 3 */
		// Start line: 22680
	/* end block 3 */
	// End Line: 22681

void StpCh(int Channel)
{
	SpuSetVoiceVolume(Channel, 0, 0);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetVol(int Channel /*$a0*/, int LVol /*$a1*/, int RVol /*$a2*/)
 // line 3104, offset 0x00086c38
	/* begin block 1 */
		// Start line: 6208
	/* end block 1 */
	// End Line: 6209

	/* begin block 2 */
		// Start line: 22716
	/* end block 2 */
	// End Line: 22717

void SetVol(int Channel, int LVol, int RVol)
{
	SpuSetVoiceVolume(Channel, (int)(short)LVol, (int)(short)RVol);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFrq(int Channel /*$a0*/, int Pitch /*$a1*/)
 // line 3115, offset 0x00086c18
	/* begin block 1 */
		// Start line: 22725
	/* end block 1 */
	// End Line: 22726

	/* begin block 2 */
		// Start line: 22726
	/* end block 2 */
	// End Line: 22727

void SetFrq(int Channel, int Pitch)
{
	SpuSetVoicePitch(Channel, Pitch & 0xffff);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SilenceXM(int Song_ID /*$a0*/)
 // line 3126, offset 0x00086ddc
	/* begin block 1 */
		// Start line: 3128
		// Start offset: 0x00086DDC
		// Variables:
	// 		int t; // $s0
	// 		int i; // $s1
	// 		int c; // $a0
	// 		int pmsk; // $v0
	/* end block 1 */
	// End offset: 0x00086EBC
	// End Line: 3151

	/* begin block 2 */
		// Start line: 23203
	/* end block 2 */
	// End Line: 23204

	/* begin block 3 */
		// Start line: 23204
	/* end block 3 */
	// End Line: 23205

	/* begin block 4 */
		// Start line: 23209
	/* end block 4 */
	// End Line: 23210

void SilenceXM(int Song_ID)
{
	UNIMPLEMENTED();
	/*
	uint Channel;
	uint uVar1;
	uint uVar2;
	int iVar3;

	mu = (XMSONG *)(&XM_SngAddress24)[Song_ID];
	mhu = (XMHEADER *)XM_HeaderAddress8[mu->HeaderNum];
	uVar1 = 0;
	uVar2 = 0;
	if (mhu->XMPSXChannels != 0) {
		iVar3 = 0x58;
		do {
			if ((mu->PlayMask & 1 << (uVar1 & 0x1f)) != 0) {
				Channel = (uint)((XMCHANNEL *)(&mu->Status + iVar3))->SPUChannel;
				uVar2 = uVar2 | 1 << (Channel & 0x1f);
				XMC = (XMCHANNEL *)(&mu->Status + iVar3);
				SetVol(Channel, 0, 0);
			}
			uVar1 = uVar1 + 1;
			iVar3 = iVar3 + 0x78;
		} while ((int)uVar1 < (int)(uint)mhu->XMPSXChannels);
	}
	SpuSetKey(0, uVar2);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_Pause(int Song_ID /*$a1*/)
 // line 3160, offset 0x00085c38
	/* begin block 1 */
		// Start line: 3161
		// Start offset: 0x00085C38
		// Variables:
	// 		int t; // $s0
	/* end block 1 */
	// End offset: 0x00085D04
	// End Line: 3179

	/* begin block 2 */
		// Start line: 6320
	/* end block 2 */
	// End Line: 6321

void XM_Pause(int Song_ID)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;

	if ((&XMSongIDs)[Song_ID] != -1) {
		mu = (XMSONG *)(&XM_SngAddress24)[Song_ID];
		mhu = (XMHEADER *)XM_HeaderAddress8[mu->HeaderNum];
		if (mu->XMPlay == '\x01') {
			mu->XMPlay = '\x02';
			iVar1 = 0;
			if (mhu->XMPSXChannels != 0) {
				iVar2 = 0x58;
				do {
					XMCU = (XMCHANNEL *)(&mu->Status + iVar2);
					SetFrq((uint)XMCU->SPUChannel, 0);
					iVar1 = iVar1 + 1;
					iVar2 = iVar2 + 0x78;
				} while (iVar1 < (int)(uint)mhu->XMPSXChannels);
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_Restart(int Song_ID /*$a1*/)
 // line 3206, offset 0x00085b44
	/* begin block 1 */
		// Start line: 3207
		// Start offset: 0x00085B44
		// Variables:
	// 		int t; // $s0
	/* end block 1 */
	// End offset: 0x00085C24
	// End Line: 3226

	/* begin block 2 */
		// Start line: 7002
	/* end block 2 */
	// End Line: 7003

void XM_Restart(int Song_ID)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;

	if ((&XMSongIDs)[Song_ID] != -1) {
		mu = (XMSONG *)(&XM_SngAddress24)[Song_ID];
		mhu = (XMHEADER *)XM_HeaderAddress8[mu->HeaderNum];
		if (mu->XMPlay == '\x02') {
			mu->XMPlay = '\x01';
			iVar1 = 0;
			if (mhu->XMPSXChannels != 0) {
				iVar2 = 0x58;
				do {
					XMCU = (XMCHANNEL *)(&mu->Status + iVar2);
					if (XMCU->ChDead == '\0') {
						SetFrq((uint)XMCU->SPUChannel, (uint)XMCU->SPUPitch);
					}
					iVar1 = iVar1 + 1;
					iVar2 = iVar2 + 0x78;
				} while (iVar1 < (int)(uint)mhu->XMPSXChannels);
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_SetMasterVol(int Song_ID /*$a2*/, unsigned char Vol /*$a1*/)
 // line 3273, offset 0x00086008
	/* begin block 1 */
		// Start line: 12805
	/* end block 1 */
	// End Line: 12806

void XM_SetMasterVol(int Song_ID, unsigned char Vol)
{
	UNIMPLEMENTED();
	/*
	if (((&XMSongIDs)[Song_ID] != -1) && (Vol < 0x81)) {
		mu = (XMSONG *)(&XM_SngAddress24)[Song_ID];
		mu->MasterVolume = Vol;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ClearSPU(int VBID /*$a0*/)
 // line 3308, offset 0x00086cf8
	/* begin block 1 */
		// Start line: 3309
		// Start offset: 0x00086CF8
		// Variables:
	// 		int i; // $s1
	// 		int Amount; // $a1
	/* end block 1 */
	// End offset: 0x00086D74
	// End Line: 3323

	/* begin block 2 */
		// Start line: 22976
	/* end block 2 */
	// End Line: 22977

	/* begin block 3 */
		// Start line: 23259
	/* end block 3 */
	// End Line: 23260

	/* begin block 4 */
		// Start line: 23263
	/* end block 4 */
	// End Line: 23264

void ClearSPU(int VBID)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	ulong *puVar2;

	iVar1 = (int)(&iVABID)[VBID];
	if (0 < iVar1) {
		puVar2 = &xm_l_vag_spu_addr + VBID * 0x80;
		do {
			if (*puVar2 != 0) {
				XM_FreeVAG(*puVar2);
				*puVar2 = 0;
			}
			iVar1 = iVar1 + -1;
			puVar2 = puVar2 + 1;
		} while (iVar1 != 0);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_FreeVAG(int addr /*$a0*/)
 // line 3331, offset 0x0008605c
	/* begin block 1 */
		// Start line: 6317
	/* end block 1 */
	// End Line: 6318

	/* begin block 2 */
		// Start line: 13218
	/* end block 2 */
	// End Line: 13219

	/* begin block 3 */
		// Start line: 13219
	/* end block 3 */
	// End Line: 13220

void XM_FreeVAG(int addr)
{
	SpuFree(addr);
	return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetFreeSongID()
 // line 3337, offset 0x00086fa0
	/* begin block 1 */
		// Start line: 3339
		// Start offset: 0x00086FA0
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x00086FF0
	// End Line: 3349

	/* begin block 2 */
		// Start line: 23712
	/* end block 2 */
	// End Line: 23713

	/* begin block 3 */
		// Start line: 24523
	/* end block 3 */
	// End Line: 24524

	/* begin block 4 */
		// Start line: 24524
	/* end block 4 */
	// End Line: 24525

	/* begin block 5 */
		// Start line: 24525
	/* end block 5 */
	// End Line: 24526

/* WARNING: Unknown calling convention yet parameter storage is locked */

int GetFreeSongID(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	short *psVar2;

	iVar1 = 0;
	if (0 < XM_NSA) {
		psVar2 = &XMSongIDs;
		do {
			if (*psVar2 == -1) {
				*psVar2 = 0;
				return iVar1;
			}
			iVar1 = iVar1 + 1;
			psVar2 = psVar2 + 1;
		} while (iVar1 < XM_NSA);
	}
	return -1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_Quit(int SongID /*$s0*/)
 // line 3351, offset 0x00086234
	/* begin block 1 */
		// Start line: 14750
	/* end block 1 */
	// End Line: 14751

void XM_Quit(int SongID)
{
	UNIMPLEMENTED();
	/*
	XM_PlayStop(SongID);
	(&XMSongIDs)[SongID] = -1;
	JPClearSPUFlags(SongID + 1);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ JPClearSPUFlags(int SongID /*$a0*/)
 // line 3359, offset 0x00086ff0
	/* begin block 1 */
		// Start line: 3360
		// Start offset: 0x00086FF0
		// Variables:
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x00087024
	// End Line: 3368

	/* begin block 2 */
		// Start line: 24561
	/* end block 2 */
	// End Line: 24562

	/* begin block 3 */
		// Start line: 24572
	/* end block 3 */
	// End Line: 24573

	/* begin block 4 */
		// Start line: 24575
	/* end block 4 */
	// End Line: 24576

void JPClearSPUFlags(int SongID)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	int iVar2;

	psVar1 = &XMSPU_SFX;
	iVar2 = 0x17;
	do {
		if ((int)*psVar1 == SongID) {
			*psVar1 = 0;
		}
		iVar2 = iVar2 + -1;
		psVar1 = psVar1 + 1;
	} while (-1 < iVar2);
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ XM_GetFreeVAB()
 // line 3449, offset 0x00086278
	/* begin block 1 */
		// Start line: 3451
		// Start offset: 0x00086278
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x000862B0
	// End Line: 3459

	/* begin block 2 */
		// Start line: 14898
	/* end block 2 */
	// End Line: 14899

	/* begin block 3 */
		// Start line: 14946
	/* end block 3 */
	// End Line: 14947

	/* begin block 4 */
		// Start line: 14947
	/* end block 4 */
	// End Line: 14948

	/* begin block 5 */
		// Start line: 14949
	/* end block 5 */
	// End Line: 14950

/* WARNING: Unknown calling convention yet parameter storage is locked */

int XM_GetFreeVAB(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	short *psVar2;

	iVar1 = 0;
	psVar2 = &iVABID;
	do {
		if (*psVar2 == -1) {
			return iVar1;
		}
		iVar1 = iVar1 + 1;
		psVar2 = psVar2 + 1;
	} while (iVar1 < 8);
	return -1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_SetVAGAddress(int VabID /*$a0*/, int slot /*$a1*/, int addr /*$a2*/)
 // line 3461, offset 0x000862b8
	/* begin block 1 */
		// Start line: 14972
	/* end block 1 */
	// End Line: 14973

	/* begin block 2 */
		// Start line: 14973
	/* end block 2 */
	// End Line: 14974

void XM_SetVAGAddress(int VabID, int slot, int addr)
{
	UNIMPLEMENTED();
	/*
	(&xm_l_vag_spu_addr)[VabID * 0x80 + slot] = addr;
	(&iVABID)[VabID] = (short)slot + 1;
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ XM_GetSongSize()
 // line 3506, offset 0x0008639c
	/* begin block 1 */
		// Start line: 7012
	/* end block 1 */
	// End Line: 7013

	/* begin block 2 */
		// Start line: 18224
	/* end block 2 */
	// End Line: 18225

/* WARNING: Unknown calling convention yet parameter storage is locked */

int XM_GetSongSize(void)
{
	return 0xbb0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_SetSongAddress(unsigned char *Address /*$a0*/)
 // line 3511, offset 0x00086358
	/* begin block 1 */
		// Start line: 17908
	/* end block 1 */
	// End Line: 17909

	/* begin block 2 */
		// Start line: 18222
	/* end block 2 */
	// End Line: 18223

	/* begin block 3 */
		// Start line: 18223
	/* end block 3 */
	// End Line: 18224

void XM_SetSongAddress(unsigned char *Address)
{
	UNIMPLEMENTED();
	/*
	mu = (XMSONG *)Address;
	(&XM_SngAddress24)[XM_NSA] = Address;
	*Address = '\0';
	mu->XMPlay = '\0';
	XM_NSA = XM_NSA + 1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_FreeAllSongIDs()
 // line 3527, offset 0x000863a4
	/* begin block 1 */
		// Start line: 18265
	/* end block 1 */
	// End Line: 18266

	/* begin block 2 */
		// Start line: 18266
	/* end block 2 */
	// End Line: 18267

/* WARNING: Unknown calling convention yet parameter storage is locked */

void XM_FreeAllSongIDs(void)
{
	UNIMPLEMENTED();
	//XM_NSA = 0;
	//return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ XM_GetFileHeaderSize()
 // line 3532, offset 0x000863e4
	/* begin block 1 */
		// Start line: 7064
	/* end block 1 */
	// End Line: 7065

	/* begin block 2 */
		// Start line: 18287
	/* end block 2 */
	// End Line: 18288

/* WARNING: Unknown calling convention yet parameter storage is locked */

int XM_GetFileHeaderSize(void)
{
	return 0xf1c;
}



// decompiled code
// original method signature: 
// void /*$ra*/ XM_SetFileHeaderAddress(unsigned char *Address /*$a0*/)
 // line 3537, offset 0x000863b0
	/* begin block 1 */
		// Start line: 18285
	/* end block 1 */
	// End Line: 18286

	/* begin block 2 */
		// Start line: 18286
	/* end block 2 */
	// End Line: 18287

void XM_SetFileHeaderAddress(unsigned char *Address)
{
	UNIMPLEMENTED();
	/*
	uchar **ppuVar1;

	if (XM_HA < 8) {
		ppuVar1 = XM_HeaderAddress8 + XM_HA;
		XM_HA = XM_HA + 1;
		*ppuVar1 = Address;
	}
	return;*/
}





