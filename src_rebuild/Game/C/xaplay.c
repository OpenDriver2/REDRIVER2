#include "driver2.h"
#include "xaplay.h"


#include "camera.h"
#include "fmvplay.h"
#include "pause.h"
#include "platform.h"
#include "sound.h"
#include "pres.h"
#include "system.h"
#include "spool.h"

#ifndef PSX
#include "STRINGS.H"

#include "../utils/riff.h"
#include "../utils/audio_source/snd_al_source.h"
#include "../utils/audio_source/snd_wav_cache.h"

#include "AL/al.h"
#include "AL/alext.h"

#include "LIBETC.H"

const char* XANameFormat = "%sXA\\XABNK0%d.XA[%d].wav";
ALuint g_XASource = AL_NONE;
CSoundSource_WaveCache* g_wavData = NULL;
CSoundSource_OpenALCache* g_XAWave = NULL;

#else

#include "LIBSND.H"

char* XANames[] = {
	"%sXA\\XABNK01.XA;1",
	"%sXA\\XABNK02.XA;1",
	"%sXA\\XABNK03.XA;1",
	"%sXA\\XABNK04.XA;1",
};

#endif

struct XA_TRACK
{
	int start;
	int end;
};

XA_TRACK XAMissionMessages[4];

static unsigned long finished_count = 0;
static int gPlaying = 0;
unsigned short gChannel = 0;
static int xa_prepared = 0;

static unsigned short CurrentChannel;
static unsigned short ID;
static int StartPos;
static CdlLOC pause_loc;
static uint buffer[8];


#ifndef PSX
struct XA_SUBTITLE
{
	char text[48];
	int startframe;
	int endframe;
};

void StoreXASubtitles()
{
	int i, j;
	char fileName[250];

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			sprintf(fileName, XANameFormat, gDataFolder, i+1, j);
			FixPathSlashes(fileName);

			CSoundSource_WaveCache tmpWav;
			if (tmpWav.Load(fileName))
			{
				// Save subtitles file
				sprintf(fileName, "%sXA\\XABNK0%d.XA[%d].SBN", gDataFolder, i+1, j);
				FixPathSlashes(fileName);

				FILE* fp = fopen(fileName, "wb");

				if (fp)
				{
					int numSubtitles = tmpWav.m_numSubtitles;
					XA_SUBTITLE subtitles[30];

					// save subtitle count
					fwrite(&numSubtitles, sizeof(int), 1, fp);

					for (int i = 0; i < numSubtitles; i++)
					{
						CUESubtitle_t* sub = &tmpWav.m_subtitles[i];
						
						strcpy(subtitles[i].text, sub->text);
						subtitles[i].startframe = sub->sampleStart;
						subtitles[i].endframe = sub->sampleStart + sub->sampleLength;
					}

					// write all subtitles
					fwrite(subtitles, sizeof(XA_SUBTITLE), numSubtitles, fp);
					fclose(fp);
				}
			}
		}
	}
}

XA_SUBTITLE gXASubtitles[30];
int gNumXASubtitles = 0;

int gXASubtitleTime = 0;
int gXASubtitlePauseTime = 0;

void PrintXASubtitles()
{
	if (gSubtitles == 0 || pauseflag)
		return;
	
	if (gPlaying == 0 || g_wavData == NULL)
		return;

	int curTime = (VSync(-1) - gXASubtitleTime) * 17;

	// find subtitles
	for(int i = 0; i < gNumXASubtitles; i++)
	{
		XA_SUBTITLE* sub = &gXASubtitles[i];

		int subStartFrame = sub->startframe;
		int subEndFrame = sub->endframe;

		if(curTime >= subStartFrame && curTime <= subEndFrame)
		{
			SetTextColour(120, 120, 120);
			PrintStringCentred(sub->text, 200);
		}
	}
}
#endif

// [D] [T]
void GetMissionXAData(int number)
{
#ifdef PSX
	CdlFILE fp;
	char filename[64];

	sprintf(filename, XANames[number], gDataFolder);
	
	CdSearchFile(&fp, XANames[number]);
	XAMissionMessages[number].start = CdPosToInt((CdlLOC *)&fp);
#endif
}

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


CdlCB oldreadycallback;
void* olddatacallback;

void cbready(int intr, unsigned char *result);

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
		alSourcei(g_XASource, AL_SOURCE_RESAMPLER_SOFT, 2);	// Use cubic resampler
		alSourcei(g_XASource, AL_SOURCE_RELATIVE, AL_TRUE);

		if (g_XAWave)
		{
			delete g_XAWave;
			g_XAWave = NULL;
		}

		xa_prepared = 1;
	}
#endif
}

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
		sprintf(fileName, XANameFormat, gDataFolder, num+1, index);
		FixPathSlashes(fileName);

		g_wavData = new CSoundSource_WaveCache();

		if (g_wavData->Load(fileName))
		{
			// Load subtitles for XA
			sprintf(fileName, "%sXA\\XABNK0%d.XA[%d].SBN", gDataFolder, num + 1, index);
			FixPathSlashes(fileName);

			FILE* fp = fopen(fileName, "rb");

			if (fp)
			{
				fread(&gNumXASubtitles, sizeof(int), 1, fp);
				fread(gXASubtitles, sizeof(XA_SUBTITLE), gNumXASubtitles, fp);
				fclose(fp);
			}

			// make OpenAL buffer
			g_XAWave = new CSoundSource_OpenALCache(g_wavData);

			alSourcei(g_XASource, AL_BUFFER, g_XAWave->m_alBuffer);

			vol = (10000 + gMasterVolume) / 79;
			alSourcef(g_XASource, AL_GAIN, float(vol) / 128.0f);

			alSourcePlay(g_XASource);
		}

		gPlaying = 1;
		xa_prepared = 2;

		gXASubtitleTime = VSync(-1);
	}
#endif
}

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
			delete g_wavData;
			g_wavData = NULL;
			
			delete g_XAWave;
			g_XAWave = NULL;
		}

		gPlaying = 0;
		xa_prepared = 0;
	}
#endif
}

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

		gXASubtitleTime += VSync(-1) - gXASubtitlePauseTime;
	}
#endif
}

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
		gXASubtitlePauseTime = VSync(-1);
	}
#endif
}





