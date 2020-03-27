#include "THISDUST.H"
#include "XAPLAY.H"

char* XANames[] = {
	"\\DRIVER2\\XA\\XABNK01.XA;1",
	"\\DRIVER2\\XA\\XABNK02.XA;1",
	"\\DRIVER2\\XA\\XABNK03.XA;1",
	"\\DRIVER2\\XA\\XABNK04.XA;1",
};


// decompiled code
// original method signature: 
// void /*$ra*/ GetMissionXAData(int number /*$s0*/)
 // line 128, offset 0x00082ec0
	/* begin block 1 */
		// Start line: 129
		// Start offset: 0x00082EC0
		// Variables:
	// 		struct CdlFILE fp; // stack offset -32
	/* end block 1 */
	// End offset: 0x00082F18
	// End Line: 144

	/* begin block 2 */
		// Start line: 256
	/* end block 2 */
	// End Line: 257

void GetMissionXAData(int number)

{
  int iVar1;
  CdlFILE CStack32;
  
  CdSearchFile(&CStack32,XANames4[number]);
  iVar1 = CdPosToInt((CdlLOC *)&CStack32);
  XAMissionMessages[number].start = iVar1;
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetXAData(int number /*$a0*/)
 // line 155, offset 0x00082d60
	/* begin block 1 */
		// Start line: 156
		// Start offset: 0x00082D60
		// Variables:
	// 		int i; // $s0
	// 		struct CdlFILE fp; // stack offset -32
	/* end block 1 */
	// End offset: 0x00082DAC
	// End Line: 167

	/* begin block 2 */
		// Start line: 310
	/* end block 2 */
	// End Line: 311

	/* begin block 3 */
		// Start line: 470
	/* end block 3 */
	// End Line: 471

void GetXAData(int number)

{
  int number_00;
  
  if (number < 0) {
    number_00 = 0;
    do {
      GetMissionXAData(number_00);
      number_00 = number_00 + 1;
    } while (number_00 < 4);
  }
  else {
    GetMissionXAData(number);
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetXAVolume(int volume /*$a0*/)
 // line 185, offset 0x00082f18
	/* begin block 1 */
		// Start line: 186
		// Start offset: 0x00082F18
	/* end block 1 */
	// End offset: 0x00082F78
	// End Line: 197

	/* begin block 2 */
		// Start line: 701
	/* end block 2 */
	// End Line: 702

	/* begin block 3 */
		// Start line: 743
	/* end block 3 */
	// End Line: 744

	/* begin block 4 */
		// Start line: 746
	/* end block 4 */
	// End Line: 747

void SetXAVolume(int volume)

{
  short sVar1;
  
  _sVar1 = volume / 0x4e + 0x7f;
  sVar1 = (short)_sVar1;
  if (_sVar1 == -1) {
    sVar1 = 0;
  }
  SsSetSerialVol(0,(int)sVar1,(int)sVar1);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PrepareXA()
 // line 226, offset 0x00082dac
	/* begin block 1 */
		// Start line: 228
		// Start offset: 0x00082DAC
		// Variables:
	// 		unsigned char param[4]; // stack offset -16
	/* end block 1 */
	// End offset: 0x00082E58
	// End Line: 249

	/* begin block 2 */
		// Start line: 546
	/* end block 2 */
	// End Line: 547

	/* begin block 3 */
		// Start line: 606
	/* end block 3 */
	// End Line: 607

	/* begin block 4 */
		// Start line: 607
	/* end block 4 */
	// End Line: 608

	/* begin block 5 */
		// Start line: 611
	/* end block 5 */
	// End Line: 612

/* WARNING: Unknown calling convention yet parameter storage is locked */

void PrepareXA(void)

{
  undefined local_10 [8];
  
  finished_count = 0;
  gPlaying = 0;
  if (xa_prepared == 0) {
    if ((spoolactive != 0) && (chunk_complete != 0)) {
      spoolpos_reading = spoolpos_reading + -1;
    }
    CdInit();
    local_10[0] = 0xe8;
    CdControlB(0xe,local_10,0);
    oldreadycallback = CdReadyCallback(cbready);
    olddatacallback = CdDataCallback(0);
    xa_prepared = 1;
    AllocateReverb(3,0x4000);
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlayXA(int num /*$a3*/, int index /*$t0*/)
 // line 265, offset 0x00082c64
	/* begin block 1 */
		// Start line: 266
		// Start offset: 0x00082C64
		// Variables:
	// 		struct CdlFILTER filt; // stack offset -40
	// 		struct CdlLOC loc; // stack offset -32
	// 		unsigned char res[8]; // stack offset -24
	/* end block 1 */
	// End offset: 0x00082D48
	// End Line: 290

	/* begin block 2 */
		// Start line: 530
	/* end block 2 */
	// End Line: 531

void PlayXA(int num,int index)

{
  int iVar1;
  undefined local_28;
  undefined local_27;
  undefined auStack32 [8];
  undefined auStack24 [8];
  
  if ((xa_prepared != 0) && (gPlaying != 1)) {
    local_27 = (undefined)index;
    StartPos = XAMissionMessages[num].start;
    gChannel = (ushort)index & 0xff;
    local_28 = 1;
    iVar1 = ((int)(&DAT_00002710 + gMasterVolume) / 0x4f) * 0x10000 >> 0x10;
    SsSetSerialVol(0,iVar1,iVar1);
    CdControlB(0xd,&local_28,auStack24);
    CdIntToPos(StartPos,auStack32);
    CdControlB(0x1b,auStack32,auStack24);
    AllocateReverb(3,0x4000);
    gPlaying = 1;
    xa_prepared = 2;
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ XAPrepared()
 // line 310, offset 0x000830f0
	/* begin block 1 */
		// Start line: 620
	/* end block 1 */
	// End Line: 621

/* WARNING: Unknown calling convention yet parameter storage is locked */

int XAPrepared(void)

{
  return xa_prepared;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnprepareXA()
 // line 320, offset 0x00082e68
	/* begin block 1 */
		// Start line: 322
		// Start offset: 0x00082E68
		// Variables:
	// 		unsigned char param[4]; // stack offset -16
	/* end block 1 */
	// End offset: 0x00082EB0
	// End Line: 337

	/* begin block 2 */
		// Start line: 801
	/* end block 2 */
	// End Line: 802

	/* begin block 3 */
		// Start line: 802
	/* end block 3 */
	// End Line: 803

	/* begin block 4 */
		// Start line: 804
	/* end block 4 */
	// End Line: 805

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UnprepareXA(void)

{
  undefined local_10 [8];
  
  if (xa_prepared != 0) {
    CdReadyCallback(oldreadycallback);
    CdDataCallback(olddatacallback);
    local_10[0] = 0x80;
    CdControlB(0xe,local_10,0);
    gPlaying = 0;
    xa_prepared = 0;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ StopXA()
 // line 343, offset 0x00082f78
	/* begin block 1 */
		// Start line: 930
	/* end block 1 */
	// End Line: 931

	/* begin block 2 */
		// Start line: 1059
	/* end block 2 */
	// End Line: 1060

	/* begin block 3 */
		// Start line: 1060
	/* end block 3 */
	// End Line: 1061

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StopXA(void)

{
  if ((gPlaying != 0) && (xa_prepared != 0)) {
    SsSetSerialVol(0,0,0);
    CdControlF(9,0);
    gPlaying = 0;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ cbready(int intr /*$s1*/, unsigned char *result /*$a1*/)
 // line 355, offset 0x000830fc
	/* begin block 1 */
		// Start line: 1217
	/* end block 1 */
	// End Line: 1218

void cbready(int intr,uchar *result)

{
  uint uVar1;
  
  if (intr == 1) {
    CdGetSector(buffer,8);
    uVar1 = ((uint)ULONG_ARRAY_000e11b4[0]._2_2_ & 0x7c00) >> 10;
    ID = (ushort)ULONG_ARRAY_000e11b4[0];
    CurrentChannel = (ushort)uVar1;
    if ((ushort)ULONG_ARRAY_000e11b4[0] == 0x160) {
      finished_count = finished_count | 1 << (uVar1 + 1 & 0x1f);
      if ((uVar1 == (uint)gChannel) || (finished_count == 0xff)) {
        SsSetSerialVol(0,0,0);
        CdControlF(9,0);
        gPlaying = 0;
        finished_count = 0;
      }
    }
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResumeXA()
 // line 386, offset 0x00082fc4
	/* begin block 1 */
		// Start line: 388
		// Start offset: 0x00082FC4
		// Variables:
	// 		struct CdlFILTER filt; // stack offset -32
	// 		unsigned char res[8]; // stack offset -24
	/* end block 1 */
	// End offset: 0x00083064
	// End Line: 408

	/* begin block 2 */
		// Start line: 1145
	/* end block 2 */
	// End Line: 1146

	/* begin block 3 */
		// Start line: 1146
	/* end block 3 */
	// End Line: 1147

	/* begin block 4 */
		// Start line: 1151
	/* end block 4 */
	// End Line: 1152

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ResumeXA(void)

{
  int iVar1;
  undefined local_20;
  undefined local_1f;
  undefined auStack24 [8];
  
  if ((xa_prepared != 0) && (gPlaying != 1)) {
    local_20 = 1;
    local_1f = (undefined)gChannel;
    iVar1 = ((int)(&DAT_00002710 + gMasterVolume) / 0x4f) * 0x10000 >> 0x10;
    SsSetSerialVol(0,iVar1,iVar1);
    CdControlB(0xd,&local_20,auStack24);
    CdControlB(0x1b,&pause_loc,auStack24);
    AllocateReverb(3,0x4000);
    gPlaying = 1;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PauseXA()
 // line 418, offset 0x00083078
	/* begin block 1 */
		// Start line: 419
		// Start offset: 0x00083078
		// Variables:
	// 		unsigned char res[8]; // stack offset -16
	/* end block 1 */
	// End offset: 0x000830E0
	// End Line: 433

	/* begin block 2 */
		// Start line: 1216
	/* end block 2 */
	// End Line: 1217

	/* begin block 3 */
		// Start line: 1218
	/* end block 3 */
	// End Line: 1219

/* WARNING: Unknown calling convention yet parameter storage is locked */

void PauseXA(void)

{
  uchar local_10;
  uchar local_f;
  uchar local_e;
  
  if ((xa_prepared != 0) && (gPlaying != 0)) {
    SsSetSerialVol(0,0,0);
    CdControlB(0x10,0,&local_10);
    pause_loc.minute = local_10;
    pause_loc.second = local_f;
    pause_loc.sector = local_e;
    CdControlB(9,0,0);
    gPlaying = 0;
  }
  return;
}





