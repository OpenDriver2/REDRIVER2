#include "DRIVER2.H"
#include "XAPLAY.H"
#include "MAIN.H"
#include "SOUND.H"
#include "SPOOL.H"

#ifndef PSX

#include "../utils/riff.h"
#include "../utils/audio_source/snd_al_source.h"
#include "../utils/audio_source/snd_wav_cache.h"

#include "AL/al.h"

const char* XANameFormat = "DRIVER2\\XA\\XABNK0%d.XA[%d].wav";
ALuint g_XASource = AL_NONE;
CSoundSource_OpenALCache* g_XAWave = NULL;

#else

char* XANames[] = {
	"\\DRIVER2\\XA\\XABNK01.XA;1",
	"\\DRIVER2\\XA\\XABNK02.XA;1",
	"\\DRIVER2\\XA\\XABNK03.XA;1",
	"\\DRIVER2\\XA\\XABNK04.XA;1",
};

#endif

static unsigned long finished_count = 0;
static int gPlaying = 0;
unsigned short gChannel = 0;
static int xa_prepared = 0;

static unsigned short CurrentChannel;
static unsigned short ID;
static int StartPos;
static CdlLOC pause_loc;
static unsigned long buffer[8];
XA_TRACK XAMissionMessages[4];

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

// [D] [T]
void GetMissionXAData(int number)
{
#ifdef PSX
	CdlFILE fp;

	CdSearchFile(&fp, XANames[number]);
	XAMissionMessages[number].start = CdPosToInt((CdlLOC *)&fp);
#endif
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

// [D] [T]
void GetXAData(int number)
{
	int i;

	if (number < 0)
	{
		i = 0;
		do {
			GetMissionXAData(i++);
		} while (i < 4);
	}
	else 
	{
		GetMissionXAData(number);
	}
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

// [D] [T]
void SetXAVolume(int volume)
{
	short vol;

	vol = volume / 78 + 127;
	if (vol == -1)
		vol = 0;

#ifdef PSX
	SsSetSerialVol(0, vol, vol);
#endif
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

CdlCB oldreadycallback;
void* olddatacallback;

// [D] [T]
void PrepareXA(void)
{
#ifdef PSX
	u_char param[4];

	finished_count = 0;
	gPlaying = 0;

	if (xa_prepared == 0)
	{
		if (spoolactive && chunk_complete)
			spoolpos_reading--;

		CdInit();

		param[0] = 0xE8;
		CdControlB(CdlSetmode, param, 0);

		oldreadycallback = CdReadyCallback((CdlCB)cbready);
		olddatacallback = CdDataCallback(0);

		xa_prepared = 1;
		AllocateReverb(3, 0x4000);
	}
#else
	finished_count = 0;
	gPlaying = 0;

	if (xa_prepared == 0)
	{
		alGenSources(1, &g_XASource);
		alSourcei(g_XASource, AL_LOOPING, 0);

		if (g_XAWave)
		{
			delete g_XAWave;
			g_XAWave = NULL;
		}

		xa_prepared = 1;
	}
#endif
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

// [D] [T]
void PlayXA(int num, int index)
{
	short vol;

#ifdef PSX
	CdlFILTER filt;
	CdlLOC loc;
	u_char res[8];

	if (xa_prepared && gPlaying != 1) 
	{
		filt.chan = index;
		StartPos = XAMissionMessages[num].start;
		gChannel = index;
		filt.file = 1;

		vol = (10000 + gMasterVolume) / 79;
		SsSetSerialVol(0, vol, vol);

		CdControlB(0xd, (u_char*)&filt, res);

		CdIntToPos(StartPos, &loc);
		CdControlB(0x1b, (u_char*)&loc, res);

		AllocateReverb(3, 0x4000);

		gPlaying = 1;
		xa_prepared = 2;
	}
#else
	if (xa_prepared && gPlaying != 1)
	{
		char fileName[250];
		sprintf(fileName, XANameFormat, num+1, index);

		CSoundSource_WaveCache wavData;
		if (wavData.Load(fileName))
		{
			g_XAWave = new CSoundSource_OpenALCache(&wavData);

			alSourcei(g_XASource, AL_BUFFER, g_XAWave->m_alBuffer);

			vol = (10000 + gMasterVolume) / 79;
			alSourcef(g_XASource, AL_GAIN, float(vol) / 128.0f);

			alSourcePlay(g_XASource);
		}

		gPlaying = 1;
		xa_prepared = 2;
	}
#endif
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

// [D] [T]
int XAPrepared(void)
{
#ifndef PSX
	ALint sourceState;
	alGetSourcei(g_XASource, AL_SOURCE_STATE, &sourceState);

	if (sourceState == AL_STOPPED)
		UnprepareXA();

#endif
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

// [D] [T]
void UnprepareXA(void)
{
#ifdef PSX
	u_char param[4];

	if (xa_prepared != 0)
	{
		CdReadyCallback(oldreadycallback);
		CdDataCallback((void (*)())olddatacallback);

		param[0] = 0x80;
		CdControlB(CdlSetmode, param, 0);

		gPlaying = 0;
		xa_prepared = 0;
	}
#else
	if (xa_prepared)
	{
		alSourceStop(g_XASource);
		alDeleteSources(1, &g_XASource);

		if (g_XAWave)
		{
			delete g_XAWave;
			g_XAWave = NULL;
		}

		gPlaying = 0;
		xa_prepared = 0;
	}
#endif
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

// [D] [T]
void StopXA(void)
{
	if (gPlaying && xa_prepared)
	{
#ifdef PSX
		SsSetSerialVol(0, 0, 0);
		CdControlF(9, 0);
#else
		alSourcePause(g_XASource);
#endif
		gPlaying = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ cbready(int intr /*$s1*/, unsigned char *result /*$a1*/)
 // line 355, offset 0x000830fc
	/* begin block 1 */
		// Start line: 1217
	/* end block 1 */
	// End Line: 1218

// [D]
void cbready(int intr, unsigned char *result)
{
	UNIMPLEMENTED();
#if 0
	if (intr == 1) 
	{
		CdGetSector(buffer, 8);
		ID = buffer[3];

		CurrentChannel = ((uint)buffer[3] & 0x7c00) >> 10; // there is buffer[3]+2 bytes

		if (buffer[3] == 0x160) 
		{
			finished_count = finished_count | 1 << (CurrentChannel + 1 & 0x1f);

			if (CurrentChannel == gChannel || finished_count == 0xff)
			{
				SsSetSerialVol(0, 0, 0);
				CdControlF(9, 0);
				gPlaying = 0;
				finished_count = 0;
			}
		}
	}
#endif
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

// [D] [T]
void ResumeXA(void)
{
	short vol;

#ifdef PSX
	CdlFILTER filt;
	u_char res[8];

	if (xa_prepared && gPlaying != 1)
	{
		filt.file = 1;
		filt.chan = gChannel;

		vol = (10000 + gMasterVolume) / 79;
		SsSetSerialVol(0, vol, vol);

		CdControlB(0xd, (u_char*)&filt, res);
		CdControlB(0x1b, (u_char*)&pause_loc, res);
		AllocateReverb(3, 0x4000);

		gPlaying = 1;
	}
#else
	if (xa_prepared && gPlaying)
	{
		vol = (10000 + gMasterVolume) / 79;
		alSourcef(g_XASource, AL_GAIN, float(vol) / 128.0f);

		alSourcePlay(g_XASource);
	}
#endif
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

// [D] [T]
void PauseXA(void)
{
#ifdef PSX
	u_char res[8];

	if (xa_prepared && gPlaying)
	{
		SsSetSerialVol(0, 0, 0);
		CdControlB(0x10, 0, res);

		pause_loc.minute = res[0];
		pause_loc.second = res[1];
		pause_loc.sector = res[2];

		CdControlB(9, 0, 0);
		gPlaying = 0;
	}
#else
	if (xa_prepared && gPlaying)
	{
		alSourcePause(g_XASource);
	}
#endif
}





