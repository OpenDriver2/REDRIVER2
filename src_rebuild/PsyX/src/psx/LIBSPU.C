#define HAVE_M_PI

#include "psx/libspu.h"
#include "psx/libetc.h"
#include "psx/libmath.h"

#include <stdio.h>

#include "../PsyX_main.h"

#include <string.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>


// TODO: implement XA, implement ADSR

#define SPU_CENTERNOTE (-32768 / 2)

short _spu_voice_centerNote[24] ={ SPU_CENTERNOTE };

const char* getALCErrorString(int err)
{
	switch (err)
	{
	case ALC_NO_ERROR:
		return "AL_NO_ERROR";
	case ALC_INVALID_DEVICE:
		return "ALC_INVALID_DEVICE";
	case ALC_INVALID_CONTEXT:
		return "ALC_INVALID_CONTEXT";
	case ALC_INVALID_ENUM:
		return "ALC_INVALID_ENUM";
	case ALC_INVALID_VALUE:
		return "ALC_INVALID_VALUE";
	case ALC_OUT_OF_MEMORY:
		return "ALC_OUT_OF_MEMORY";
	default:
		return "AL_UNKNOWN";
	}
}

const char* getALErrorString(int err)
{
	switch (err)
	{
	case AL_NO_ERROR:
		return "AL_NO_ERROR";
	case AL_INVALID_NAME:
		return "AL_INVALID_NAME";
	case AL_INVALID_ENUM:
		return "AL_INVALID_ENUM";
	case AL_INVALID_VALUE:
		return "AL_INVALID_VALUE";
	case AL_INVALID_OPERATION:
		return "AL_INVALID_OPERATION";
	case AL_OUT_OF_MEMORY:
		return "AL_OUT_OF_MEMORY";
	default:
		return "AL_UNKNOWN";
	}
}

#define SPU_REALMEMSIZE			(512 * 1024)
#define SPU_MEMSIZE				(2048*1024)		// SPU_REALMEMSIZE
#define SPU_VOICES 24

typedef struct
{
	unsigned char	samplemem[SPU_MEMSIZE];
	unsigned char*	writeptr;
} SPUMemory;

static SPUMemory s_SpuMemory;
SDL_mutex* g_SpuMutex = NULL;
int g_spuInit = 0;

typedef struct
{
	SpuVoiceAttr attr;	// .voice is Id of this channel

	ALuint alBuffer;
	ALuint alSource;
	ushort sampledirty;
	ushort reverb;
} SPUVoice;

SPUVoice	g_SpuVoices[SPU_VOICES];
ALCdevice*	g_ALCdevice = NULL;
ALCcontext* g_ALCcontext = NULL;
int			g_SPUMuted = 0;
ALuint		g_ALEffectSlots[2];
int			g_currEffectSlotIdx = 0;
ALuint		g_nAlReverbEffect = 0;
int			g_enableSPUReverb = 0;
int			g_ALEffectsSupported = 0;

LPALGENEFFECTS alGenEffects = NULL;
LPALDELETEEFFECTS alDeleteEffects = NULL;
LPALEFFECTI alEffecti = NULL;
LPALEFFECTF alEffectf = NULL;
LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots = NULL;
LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots = NULL;
LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti = NULL;

void PsyX_SPU_InitOpenAlEffects()
{
	g_ALEffectsSupported = 0;

	if (!alcIsExtensionPresent(g_ALCdevice, ALC_EXT_EFX_NAME))
	{
		eprintf("PSX SPU effects are NOT supported!\n");
		return;
	}

	alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
	alDeleteEffects = (LPALDELETEEFFECTS)alGetProcAddress("alDeleteEffects");
	alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
	alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");
	alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
	alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");
	alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");

	int max_sends = 0;
	alcGetIntegerv(g_ALCdevice, ALC_MAX_AUXILIARY_SENDS, 1, &max_sends);

	// make reverb effect slot
	g_currEffectSlotIdx = 0;
	alGenAuxiliaryEffectSlots(1, g_ALEffectSlots);

	// make reverb effect
	alGenEffects(1, &g_nAlReverbEffect);
	alEffecti(g_nAlReverbEffect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);

	// setup defaults of effect
	alEffectf(g_nAlReverbEffect, AL_REVERB_GAIN, 0.45f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_GAINHF, 0.25f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DECAY_TIME, 2.0f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DECAY_HFRATIO, 0.9f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_REFLECTIONS_DELAY, 0.08f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_REFLECTIONS_GAIN, 0.2f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DIFFUSION, 0.9f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DENSITY, 0.1f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_AIR_ABSORPTION_GAINHF, 0.1f);

	g_ALEffectsSupported = 1;

	eprintf("PSX SPU effects are supported and initialized\n");

	alAuxiliaryEffectSloti(g_ALEffectSlots[g_currEffectSlotIdx], AL_EFFECTSLOT_EFFECT, g_nAlReverbEffect);
}

int PsyX_SPU_InitSound()
{
	int numDevices, alErr, i;
	const char* devices;
	const char* devStrptr;

	// out_channel_formats snd_outputchannels
	static int al_context_params[] =
	{
		ALC_FREQUENCY, 44100,
		ALC_MAX_AUXILIARY_SENDS, 2,
		0
	};

	if (g_ALCdevice)
		return 1;

	numDevices = 0;

	// Init openAL
	// check devices list

	devStrptr = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	devices = devStrptr;

	// go through device list (each device terminated with a single NULL, list terminated with double NULL)
	while ((*devStrptr) != '\0')
	{
		eprintinfo("found sound device: %s\n", devStrptr);
		devStrptr += strlen(devStrptr) + 1;
		numDevices++;
	}

	if(numDevices == 0)
		return 0;
	
	g_ALCdevice = alcOpenDevice(NULL);

	alErr = AL_NO_ERROR;

	if (!g_ALCdevice)
	{
		alErr = alcGetError(NULL);
		eprinterr("alcOpenDevice: NULL DEVICE error: %s\n", getALCErrorString(alErr));
		return 0;
	}

#ifndef __EMSCRIPTEN__
	g_ALCcontext = alcCreateContext(g_ALCdevice, al_context_params);
#else
	g_ALCcontext = alcCreateContext(g_ALCdevice, NULL);
#endif

	alErr = alcGetError(g_ALCdevice);
	if (alErr != AL_NO_ERROR)
	{
		eprinterr("alcCreateContext error: %s\n", getALCErrorString(alErr));
		return 0;
	}

	alcMakeContextCurrent(g_ALCcontext);

	alErr = alcGetError(g_ALCdevice);
	if (alErr != AL_NO_ERROR)
	{
		eprinterr("alcMakeContextCurrent error: %s\n", getALCErrorString(alErr));
		return 0;
	}

	// Setup defaults
	alListenerf(AL_GAIN, 1.0f);
	alDistanceModel(AL_NONE);

	// create channels
	for (i = 0; i < SPU_VOICES; i++)
	{
		SPUVoice* voice = &g_SpuVoices[i];
		memset(voice, 0, sizeof(SPUVoice));

		alGenSources(1, &voice->alSource);
		alGenBuffers(1, &voice->alBuffer);

		alSourcei(voice->alSource, AL_SOURCE_RESAMPLER_SOFT, 2);	// Use cubic resampler
		alSourcei(voice->alSource, AL_SOURCE_RELATIVE, AL_TRUE);
	}

	memset(&s_SpuMemory, 0, sizeof(s_SpuMemory));

	PsyX_SPU_InitOpenAlEffects();

	g_SpuMutex = SDL_CreateMutex();

	return 1;
}

void PsyX_SPU_ShutdownSound()
{
	if (!g_ALCcontext)
		return;

	for (int i = 0; i < SPU_VOICES; i++)
	{
		SPUVoice* voice = &g_SpuVoices[i];
		alDeleteSources(1, &voice->alSource);
		alDeleteBuffers(1, &voice->alBuffer);
	}

	if (g_ALEffectsSupported)
	{
		alDeleteEffects(1, &g_nAlReverbEffect);
		g_ALEffectsSupported = AL_NONE;
	}

	alDeleteAuxiliaryEffectSlots(1, g_ALEffectSlots);

	alcDestroyContext(g_ALCcontext);
	alcCloseDevice(g_ALCdevice);

	g_ALCcontext = NULL;
	g_ALCdevice = NULL;
}

//--------------------------------------------------------------------------------

// PSX ADPCM coefficients
const float K0[5] = { 0, 0.9375, 1.796875, 1.53125, 1.90625 };
const float K1[5] = { 0, 0, -0.8125, -0.859375, -0.9375 };

// PSX ADPCM decoding routine - decodes a single sample
short vagToPcm(unsigned char soundParameter, int soundData, float* vagPrev1, float* vagPrev2)
{
	int resultInt = 0;

	float dTmp1 = 0.0;
	float dTmp2 = 0.0;
	float dTmp3 = 0.0;

	if (soundData > 7)
		soundData -= 16;

	dTmp1 = (float)soundData * pow(2, (float)(12 - (soundParameter & 0x0F)));

	dTmp2 = (*vagPrev1) * K0[(soundParameter >> 4) & 0x0F];
	dTmp3 = (*vagPrev2) * K1[(soundParameter >> 4) & 0x0F];

	(*vagPrev2) = (*vagPrev1);
	(*vagPrev1) = dTmp1 + dTmp2 + dTmp3;

	resultInt = (int)round((*vagPrev1));

	if (resultInt > 32767)
		resultInt = 32767;

	if (resultInt < -32768)
		resultInt = -32768;

	return (short)resultInt;
}

typedef enum 
{
	LoopEnd = 1 << 0,		// Jump to repeat address after this block
							// 1 - Copy repeatAddress to currentAddress AFTER this block
							//     set ENDX (TODO: Immediately or after this block?)
							// 0 - Nothing

	Repeat = 1 << 1,		// Takes an effect only with LoopEnd bit set.
							// 1 - Loop normally
							// 0 - Loop and force Release

	LoopStart = 1 << 2,		// Mark current address as the beginning of repeat
							// 1 - Load currentAddress to repeatAddress
							// 0 - Nothing
} ADPCM_FLAGS;


// Main decoding routine - Takes PSX ADPCM formatted audio data and converts it to PCM. It also extracts the looping information if used.
int decodeSound(unsigned char* iData, int soundSize, short* oData, int* loopStart, int* loopLength, int breakOnEnd /*= 0*/)
{
	unsigned char sp;
	unsigned char flag;
	int sd = 0;
	float vagPrev1 = 0.0;
	float vagPrev2 = 0.0;
	int k = 0;

	int loopStrt = 0, loopEnd = 0;
	int breakOn = -1;

	for (int i = 0; i < soundSize; i++)
	{
		if (i % 16 == 0)
		{
			sp = iData[i];
			flag = iData[i+1];
			i += 2;
		}

		sd = (int)iData[i] & 0xF;
		oData[k++] = vagToPcm(sp, sd, &vagPrev1, &vagPrev2);

		sd = ((int)iData[i] >> 4) & 0xF;
		oData[k++] = vagToPcm(sp, sd, &vagPrev1, &vagPrev2);

		if (breakOnEnd && k == breakOn)
			return k;

		if (breakOn == -1)
		{
			// flags parsed
			if (flag & LoopStart)
			{
				loopStrt = k + 26; // FIXME: is that correct?
			}

			if (flag & LoopEnd)
			{
				loopEnd = k + 26;

				if (flag & Repeat)
				{
					*loopStart = loopStrt;
					*loopLength = loopEnd - loopStrt;
				}

				if (breakOnEnd)
					breakOn = k + 26;
			}
		}
	}

	return soundSize;
}

#include <assert.h>

unsigned long SpuWrite(unsigned char* addr, unsigned long size)
{
	//if (0x7EFF0 < size)
	//	size = 0x7EFF0;

	int wptr_ofs = s_SpuMemory.writeptr - s_SpuMemory.samplemem;

	if (wptr_ofs+size > SPU_REALMEMSIZE)
	{
		eprintf("SPU WARNING: SpuWrite exceeded SPU_REALMEMSIZE (%d > 512k)!\n", wptr_ofs+size);
	}
	assert(size > 0 && wptr_ofs+size < SPU_MEMSIZE);

	// simply copy to the writeptr
	memcpy(s_SpuMemory.writeptr, addr, size);

#if 0 // BANK TEST
	{
		static short waveBuffer[SPU_MEMSIZE];

		ALuint alSource;
		ALuint alBuffer;

		alGenSources(1, &alSource);
		alGenBuffers(1, &alBuffer);

		int loopStart = 0, loopLen = 0;
		int count = decodeSound(addr, size, waveBuffer, &loopStart, &loopLen);

		// update AL buffer
		alBufferData(alBuffer, AL_FORMAT_MONO16, waveBuffer, count * sizeof(short), 11000);

		// set the buffer
		alSourcei(alSource, AL_BUFFER, alBuffer);
		alSourcef(alSource, AL_GAIN, 1.0f);// TODO: panning
		alSourcef(alSource, AL_PITCH, 1);

		alSourcePlay(alSource);
		int status;
		do
		{
			alGetSourcei(alSource, AL_SOURCE_STATE, &status);
		} while (status == AL_PLAYING);

		alSourceStop(alSource);

		alDeleteSources(1, &alSource);
		alDeleteBuffers(1, &alBuffer);
	}
#endif

	return size;
}

long SpuSetTransferMode(long mode)
{
	// TODO: handle different transfer modes?

	long mode_fix = mode == 0 ? 0 : 1;

	//trans_mode = mode;
	//transMode = mode_fix;

	return mode_fix;
}

unsigned long SpuSetTransferStartAddr(unsigned long addr)
{
	s_SpuMemory.writeptr = s_SpuMemory.samplemem + addr;

	if(addr > SPU_MEMSIZE)
		return 0;

	if (addr < 0x1010)
		return 0;

	return 1;
}

long SpuIsTransferCompleted(long flag)
{
	return 1;
}

void SpuStart()
{
	PsyX_SPU_InitSound();
}

void _SpuInit(int a0)
{
	ResetCallback();

	if (a0 == 0)
	{
		for (int i = 0; i < sizeof(_spu_voice_centerNote) / sizeof(short); i++)
			_spu_voice_centerNote[i] = SPU_CENTERNOTE;
	}

	SpuStart();
	g_spuInit = 1;
}

void SpuInit(void)
{
	_SpuInit(0);
}

void SpuQuit(void)
{
	g_spuInit = 0;
	PsyX_SPU_ShutdownSound();
}

void UpdateVoiceSample(SPUVoice* voice)
{
	static short waveBuffer[SPU_REALMEMSIZE];
	int loopStart, loopLen, count;
	ALuint alSource, alBuffer;

	//if (!voice->sampledirty)
	//	return;

	voice->sampledirty = 0;

	alSource = voice->alSource;
	alBuffer = voice->alBuffer;

	if (alSource == AL_NONE)
		return;

	loopStart = 0;
	loopLen = 0;
	
	count = decodeSound(s_SpuMemory.samplemem + voice->attr.addr, SPU_REALMEMSIZE - voice->attr.addr, waveBuffer, &loopStart, &loopLen, 1);

	if (count == 0)
		return;

#if 0	// sample test
	{
		ALuint aalSource;
		ALuint aalBuffer;

		alGenSources(1, &aalSource);
		alGenBuffers(1, &aalBuffer);

		// update AL buffer
		alBufferData(aalBuffer, AL_FORMAT_MONO16, waveBuffer, count * sizeof(short), 11000);

		// set the buffer
		alSourcei(aalSource, AL_BUFFER, aalBuffer);
		alSourcef(aalSource, AL_GAIN, 1.0f);// TODO: panning
		alSourcef(aalSource, AL_PITCH, 1);

		alSourcePlay(aalSource);
		int status;
		do
		{
			alGetSourcei(aalSource, AL_SOURCE_STATE, &status);
		} while (status == AL_PLAYING);

		alSourceStop(aalSource);

		alDeleteSources(1, &aalSource);
		alDeleteBuffers(1, &aalBuffer);
	}
#endif

	alSourcei(alSource, AL_BUFFER, 0);
	alBufferData(alBuffer, AL_FORMAT_MONO16, waveBuffer, count * sizeof(short), 44100);

	if (loopLen > 0)
	{
		loopStart += voice->attr.loop_addr - voice->attr.addr;

		if (loopStart-54 > 0 && loopStart + loopLen <= count)
		{
			int sampleOffs[] = { loopStart, loopStart + loopLen };
			alBufferiv(alBuffer, AL_LOOP_POINTS_SOFT, sampleOffs);
		}

		alSourcei(alSource, AL_LOOPING, AL_TRUE);
	}
	else
	{
		//int sampleOffs[] = { 0, 0 };
		//alBufferiv(alBuffer, AL_LOOP_POINTS_SOFT, sampleOffs);
		alSourcei(alSource, AL_LOOPING, AL_FALSE);
	}

	// set the buffer
	alSourcei(alSource, AL_BUFFER, alBuffer);
}

void SpuSetVoiceAttr(SpuVoiceAttr *arg)
{
	const float STEREO_FACTOR = 3.0f;
	SPUVoice* voice;
	ALuint alSource;
	float pitch, left_gain, right_gain, pan;

	if (!g_spuInit)
	{
		return;
	}
	
	SDL_LockMutex(g_SpuMutex);

	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (!(arg->voice & SPU_VOICECH(i)))
			continue;

		voice = &g_SpuVoices[i];

		ALuint alSource = voice->alSource;

		if (alSource == AL_NONE)
			continue;
		
		// update sample
		if ((arg->mask & SPU_VOICE_WDSA) || (arg->mask & SPU_VOICE_LSAX))
		{
			//ALuint tmp = voice->alSource[1];
			//voice->alSource[1] = voice->alSource[0];
			//voice->alSource[1] = tmp;
			//alSource = voice->alSource[0];

			if (arg->mask & SPU_VOICE_WDSA)
			{
				if (voice->attr.addr != arg->addr)
					voice->sampledirty++;

				voice->attr.addr = arg->addr;
			}
			
			if (arg->mask & SPU_VOICE_LSAX)
			{
				if(voice->attr.loop_addr != arg->loop_addr)
					voice->sampledirty++;

				voice->attr.loop_addr = arg->loop_addr;
			}			
		}

		// update volume
		if ((arg->mask & SPU_VOICE_VOLL) || (arg->mask & SPU_VOICE_VOLR))
		{
			if (arg->mask & SPU_VOICE_VOLL)
				voice->attr.volume.left = arg->volume.left;

			if (arg->mask & SPU_VOICE_VOLR)
				voice->attr.volume.right = arg->volume.right;

			left_gain = (float)(voice->attr.volume.left) / (float)(16384);
			right_gain = (float)(voice->attr.volume.right) / (float)(16384);

			if(left_gain > 1.0f)
				left_gain = 1.0f;

			if(right_gain > 1.0f)
				right_gain = 1.0f;

			pan = (acosf(left_gain) + asinf(right_gain)) / ((float)(M_PI)); // average angle in [0,1]
			pan = 2.0f * pan - 1.0f; // convert to [-1, 1]
			pan = pan * 0.5f; // 0.5 = sin(30') for a +/- 30 degree arc
			alSource3f(alSource, AL_POSITION, pan * STEREO_FACTOR, 0, -sqrtf(1.0f - pan * pan));

			alSourcef(alSource, AL_GAIN, (left_gain+right_gain)*0.5f);
		}

		// update pitch
		if (arg->mask & SPU_VOICE_PITCH)
		{
			voice->attr.pitch = arg->pitch;

			pitch = (float)(voice->attr.pitch) / 4096.0f;

			alSourcef(alSource, AL_PITCH, pitch);
		}
		
		// TODO: ADSR and other stuff
	}
	SDL_UnlockMutex(g_SpuMutex);
}

void SpuSetKey(long on_off, unsigned long voice_bit)
{
	SPUVoice* voice;
	ALuint alSource;

	if (!g_spuInit)
	{
		return;
	}

	SDL_LockMutex(g_SpuMutex);
	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (voice_bit & SPU_VOICECH(i))
		{
			voice = &g_SpuVoices[i];

			alSource = voice->alSource;

			if (alSource == AL_NONE)
				continue;

			if (on_off && !g_SPUMuted)
			{
				alSourceStop(alSource);
				UpdateVoiceSample(voice);

				alSourcePlay(alSource);
			}
			else
			{
				alSourceStop(alSource);
			}
		}
	}
	SDL_UnlockMutex(g_SpuMutex);
}

long SpuGetKeyStatus(unsigned long voice_bit)
{
	SPUVoice* voice;
	ALuint alSource;
	int state = AL_STOPPED;

	SDL_LockMutex(g_SpuMutex);

	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (voice_bit != SPU_VOICECH(i))
			continue;

		voice = &g_SpuVoices[i];

		alSource = voice->alSource;

		if (alSource == AL_NONE)
			break; // SpuOff?

		alGetSourcei(alSource, AL_SOURCE_STATE, &state);
		break;
	}

	SDL_UnlockMutex(g_SpuMutex);

	return (state == AL_PLAYING);	// simple as this?
}

void SpuGetAllKeysStatus(char* status)
{
	SPUVoice* voice;
	ALuint alSource;

	SDL_LockMutex(g_SpuMutex);

	for (int i = 0; i < SPU_VOICES; i++)
	{
		voice = &g_SpuVoices[i];

		alSource = voice->alSource;

		if (alSource == AL_NONE)
		{
			status[i] = 0; // SpuOff?
			continue;
		}
		
		int state;
		alGetSourcei(alSource, AL_SOURCE_STATE, &state);

		status[i] = (state == AL_PLAYING);
	}
	SDL_UnlockMutex(g_SpuMutex);
}

void SpuSetKeyOnWithAttr(SpuVoiceAttr* attr)
{
	SpuSetVoiceAttr(attr);
	SpuSetKey(1, attr->voice);
}

long SpuSetMute(long on_off)
{
	long old_state = g_SPUMuted;
	g_SPUMuted = on_off;
	return old_state;
}

long SpuSetReverb(long on_off)
{
	long old_state = g_enableSPUReverb;
	g_enableSPUReverb = on_off;

	if (!g_spuInit)
	{
		return;
	}

	// switch if needed
	if (g_ALEffectsSupported && old_state != g_enableSPUReverb)
	{
		if (g_enableSPUReverb)
		{
			alAuxiliaryEffectSloti(g_ALEffectSlots[g_currEffectSlotIdx], AL_EFFECTSLOT_EFFECT, g_nAlReverbEffect);
		}
		else
		{
			g_currEffectSlotIdx = 0;
			alAuxiliaryEffectSloti(g_ALEffectSlots[0], AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
			alAuxiliaryEffectSloti(g_ALEffectSlots[1], AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
		}
	}

	return old_state;
}

long SpuGetReverb(void)
{
	return g_enableSPUReverb;
}

long SpuSetReverbModeParam(SpuReverbAttr* attr)
{
	// TODO: setup next params
	/*
	alEffectf(g_nAlReverbEffect, AL_REVERB_GAIN, 0.45f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_GAINHF, 0.25f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DECAY_TIME, 2.0f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DECAY_HFRATIO, 0.9f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_REFLECTIONS_DELAY, 0.08f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_REFLECTIONS_GAIN, 0.2f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DIFFUSION, 0.9f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_DENSITY, 0.1f);
	alEffectf(g_nAlReverbEffect, AL_REVERB_AIR_ABSORPTION_GAINHF, 0.1f);
	*/

	PSYX_UNIMPLEMENTED();
	return 0;
}

void SpuGetReverbModeParam(SpuReverbAttr* attr)
{
	PSYX_UNIMPLEMENTED();
}

long SpuSetReverbDepth(SpuReverbAttr* attr)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long SpuReserveReverbWorkArea(long on_off)
{
	return 1;
}

long SpuIsReverbWorkAreaReserved(long on_off)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

unsigned long SpuSetReverbVoice(long on_off, unsigned long voice_bit)
{
	SPUVoice* voice;
	ALuint alSource;

	if (!g_spuInit)
	{
		return;
	}
	
	if(!g_ALEffectsSupported)
		return 0;

	SDL_LockMutex(g_SpuMutex);

	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (voice_bit & SPU_VOICECH(i))
		{
			voice = &g_SpuVoices[i];

			alSource = voice->alSource;

			if (alSource == AL_NONE)
				continue;

			voice->reverb = on_off > 0;

			if (on_off)
			{
				alSource3i(alSource, AL_AUXILIARY_SEND_FILTER, g_ALEffectSlots[g_currEffectSlotIdx], 0, AL_FILTER_NULL);
			}
			else
			{
				alSource3i(alSource, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL);
			}
		}
	}

	SDL_UnlockMutex(g_SpuMutex);

	return 0;
}

unsigned long SpuGetReverbVoice(void)
{
	SPUVoice* voice;

	unsigned long bits = 0;

	for (int i = 0; i < SPU_VOICES; i++)
	{
		voice = &g_SpuVoices[i];
		if (voice->reverb)
			bits |= SPU_KEYCH(i);
	}

	return bits;
}

long SpuClearReverbWorkArea(long mode)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}


void SpuSetCommonAttr(SpuCommonAttr* attr)
{
	PSYX_UNIMPLEMENTED();
}

static long s_spuMallocVal = 0;

long SpuInitMalloc(long num, char* top)
{
	s_spuMallocVal = 0;
	return num;
}

long SpuMalloc(long size)
{
	int addr = s_spuMallocVal;
	s_spuMallocVal += size;

	if (s_spuMallocVal > SPU_MEMSIZE)
		return -1;

	return addr;
}

long SpuMallocWithStartAddr(unsigned long addr, long size)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void SpuFree(unsigned long addr)
{
	s_spuMallocVal = 0;
}

unsigned long SpuFlush(unsigned long ev)
{
	//PSYX_UNIMPLEMENTED();
	return 0;
}

void SpuSetCommonMasterVolume(short mvol_left, short mvol_right)// (F)
{
	//MasterVolume.VolumeLeft.Raw = mvol_left;
	//MasterVolume.VolumeRight.Raw = mvol_right;
}

long SpuSetReverbModeType(long mode)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void SpuSetReverbModeDepth(short depth_left, short depth_right)
{
	PSYX_UNIMPLEMENTED();
}

void SpuSetVoiceVolume(int vNum, short volL, short volR)
{
	SpuVoiceAttr attr;

	attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
	attr.voice = SPU_VOICECH(vNum);
	attr.volume.left = volL;
	attr.volume.right = volR;

	SpuSetVoiceAttr(&attr);
}

void SpuSetVoicePitch(int vNum, unsigned short pitch)
{
	SpuVoiceAttr attr;

	attr.mask = SPU_VOICE_PITCH;
	attr.voice = SPU_VOICECH(vNum);
	attr.pitch = pitch;

	SpuSetVoiceAttr(&attr);
}

void SpuGetVoiceVolume(int vNum, short *volL, short *volR)
{
	if(volL)
		*volL = g_SpuVoices[vNum].attr.volume.left;

	if(volR)
		*volR = g_SpuVoices[vNum].attr.volume.right;
}

void SpuGetVoicePitch(int vNum, unsigned short *pitch)
{
	*pitch = g_SpuVoices[vNum].attr.pitch;
}

void SpuSetVoiceAR(int vNum, unsigned short AR)
{
	SpuVoiceAttr attr;

	attr.mask = SPU_VOICE_ADSR_AR;
	attr.ar = AR;

	SpuSetVoiceAttr(&attr);
}

void SpuSetVoiceRR(int vNum, unsigned short RR)
{
	SpuVoiceAttr attr;

	attr.mask = SPU_VOICE_ADSR_RR;
	attr.rr = RR;

	SpuSetVoiceAttr(&attr);
}
