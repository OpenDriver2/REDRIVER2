#include "LIBSPU.H"
#include "LIBETC.H"
#include <stdio.h>

#include "EMULATOR.H"
#include "LIBAPI.H"
#include "LIBMATH.H"

#include <string.h>

#define SPU_CENTERNOTE (-32768 / 2)

short _spu_voice_centerNote[24] =
{
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE,
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE,
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE
};

SpuCommonAttr dword_424;//Might be wrong struct, need to check
int _spu_isCalled = 0;
int _spu_FiDMA = 0;///@TODO decl as extern find initial value
int _spu_EVdma = 0;
int _spu_rev_flag = 0;
int _spu_rev_reserve_wa = 0;
int _spu_rev_offsetaddr = 0;
int _spu_rev_startaddr = 0;
int _spu_AllocBlockNum = 0;
int _spu_AllocLastNum = 0;
int _spu_memList = 0;
int _spu_trans_mode = 0;
int _spu_transMode = 0;
int _spu_keystat = 0;
int _spu_RQmask = 0;
int _spu_RQvoice = 0;
int _spu_env = 0;
char spu[440];//0x1F801C00 is base address
short* _spu_RXX = (short*)&spu[0];
int _spu_mem_mode_plus = 3;
void* _spu_transferCallback = NULL;///@TODO initial value check
int _spu_inTransfer = 0;///@TODO initial value check
unsigned short _spu_tsa = 0;

void _spu_t(int mode, int flag)
{
	UNIMPLEMENTED();
}

void _spu_Fw(unsigned char* addr, unsigned long size)
{
	//v0 = _spu_transMode
	//s1 = addr
	//s0 = size

	if (_spu_trans_mode == 0)
	{
		//v0 = _spu_tsa
		//a1 = _spu_mem_mode_plus
		//a0 = 2
		_spu_t(2, _spu_tsa << _spu_mem_mode_plus);
		///@TODO check if a1 is modified in spu_t
	}
	//loc_A84
#if 0
jal     _spu_t
sllv    $a1, $v0, $a1

jal     _spu_t
li      $a0, 1

li      $a0, 3
move    $a1, $s1
jal     _spu_t
move    $a2, $s0
j       loc_A94
move    $v0, $s0

loc_A84:
move    $a0, $s1
jal     sub_480
move    $a1, $s0
move    $v0, $s0

loc_A94:
lw      $ra, 0x20+var_8($sp)
lw      $s1, 0x20+var_C($sp)
lw      $s0, 0x20+var_10($sp)
jr      $ra
addiu   $sp, 0x20
 # End of function _spu_Fw
#endif
}

//--------------------------------------------------------------------------------

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

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

struct SPUMemory
{
	unsigned char	samplemem[SPU_MEMSIZE];
	unsigned char*	writeptr;
};

static SPUMemory s_SpuMemory;

struct SPUVoice
{
	SpuVoiceAttr attr;	// .voice is Id of this channel

	ALuint alBuffer;
	ALuint alSource;
	int sampledirty;
};

SPUVoice s_SpuVoices[SPU_VOICES];

ALCdevice* s_ALCdevice = NULL;
ALCcontext* s_ALCcontext = NULL;

bool Emulator_InitSound()
{
	if (s_ALCdevice)
		return true;

	printf(" \n--------- InitOpenAL --------- \n");

	// Init openAL
	// check devices list
	char* devices = (char*)alcGetString(nullptr, ALC_DEVICE_SPECIFIER);

	// go through device list (each device terminated with a single NULL, list terminated with double NULL)
	while ((*devices) != '\0')
	{
		printf("found sound device: %s\n", devices);
		devices += strlen(devices) + 1;
	}

	s_ALCdevice = alcOpenDevice(NULL);

	int alErr = AL_NO_ERROR;

	if (!s_ALCdevice)
	{
		alErr = alcGetError(nullptr);
		printf("alcOpenDevice: NULL DEVICE error: %s\n", getALCErrorString(alErr));
		return false;
	}

	// out_channel_formats snd_outputchannels
	int al_context_params[] =
	{
		ALC_FREQUENCY, 44100,
		0
	};

	s_ALCcontext = alcCreateContext(s_ALCdevice, al_context_params);

	alErr = alcGetError(s_ALCdevice);
	if (alErr != AL_NO_ERROR)
	{
		printf("alcCreateContext error: %s\n", getALCErrorString(alErr));
		return false;
	}

	alcMakeContextCurrent(s_ALCcontext);

	alErr = alcGetError(s_ALCdevice);
	if (alErr != AL_NO_ERROR)
	{
		printf("alcMakeContextCurrent error: %s\n", getALCErrorString(alErr));
		return false;
	}

	// Setup defaults
	alListenerf(AL_GAIN, 1.0f);
	//alDistanceModel(AL_NONE);

	// create channels
	for (int i = 0; i < SPU_VOICES; i++)
	{
		SPUVoice& voice = s_SpuVoices[i];
		memset(&voice, 0, sizeof(SPUVoice));

		alGenSources(1, &voice.alSource);
		alGenBuffers(1, &voice.alBuffer);

		alSourcei(voice.alSource, AL_SOURCE_RELATIVE, AL_TRUE);
	}

	memset(&s_SpuMemory, 0, sizeof(s_SpuMemory));

	return true;
}

//--------------------------------------------------------------------------------

#include <math.h>


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

enum ADPCM_FLAGS 
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
};


// Main decoding routine - Takes PSX ADPCM formatted audio data and converts it to PCM. It also extracts the looping information if used.
int decodeSound(unsigned char* iData, int soundSize, short* oData, int* loopStart, int* loopLength, bool breakOnEnd = false)
{
	unsigned char sp;
	unsigned char flag;
	int sd = 0;
	float vagPrev1 = 0.0;
	float vagPrev2 = 0.0;
	int k = 0;

	int loopStrt = 0, loopEnd = 0;

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

		// flags parsed
		if (flag & ADPCM_FLAGS::LoopStart)
		{
			loopStrt = k;
		}

		if (flag & ADPCM_FLAGS::LoopEnd)
		{
			loopEnd = k;

			if (flag & ADPCM_FLAGS::Repeat)
			{
				*loopStart = loopStrt;
				*loopLength = loopEnd - loopStrt;
			}

			if (breakOnEnd)
				return loopEnd;
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
		eprintf("LIBSPU WARNING: SpuWrite exceeded SPU_REALMEMSIZE (%d > 512k)!\n", wptr_ofs+size);
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

	//loc_228
	_spu_Fw(addr, size);


	if (_spu_transferCallback == NULL)
	{
		_spu_inTransfer = 0;
	}

	return size;
}

long SpuSetTransferMode(long mode)
{
	// TODO: handle different transfer modes

	long mode_fix = mode == 0 ? 0 : 1;

	//trans_mode = mode;
	//transMode = mode_fix;

	return mode_fix;
}

unsigned long SpuSetTransferStartAddr(unsigned long addr)
{
	s_SpuMemory.writeptr = s_SpuMemory.samplemem + addr;
	return 0;
}

long SpuIsTransferCompleted(long flag)
{
	UNIMPLEMENTED();
	return 0;
}

void _SpuDataCallback(int a0)
{
	UNIMPLEMENTED();
}

void SpuStart()//(F)
{
	long event = 0;

	if (_spu_isCalled == 0)
	{
		_spu_isCalled = 1;
		EnterCriticalSection();
		_SpuDataCallback(_spu_FiDMA);
		//event = OpenEvent(HwSPU, EvSpCOMP, EvMdNOINTR, NULL);
		_spu_EVdma = event;
		EnableEvent(event);
		ExitCriticalSection();
	}
	//loc_348
}

void _spu_init(int a0)
{
	UNIMPLEMENTED();
}

void _spu_FsetRXX(int a0, int a1, int a2)//(F)
{
	if (a2 == 0)
	{
		_spu_RXX[a0] = a1;
	}
	else
	{
		_spu_RXX[a0] = a1 >> _spu_mem_mode_plus;
	}
}

void _SpuInit(int a0)
{
	ResetCallback();
	_spu_init(a0);

	if (a0 == 0)
	{
		for (int i = 0; i < sizeof(_spu_voice_centerNote) / sizeof(short); i++)
		{
			_spu_voice_centerNote[i] = SPU_CENTERNOTE;
		}
	}
	//loc_240
	SpuStart();

	_spu_rev_flag = 0;
	_spu_rev_reserve_wa = 0;
	dword_424.mask = 0;
	dword_424.mvol.left = 0;
	dword_424.mvol.right = 0;
	dword_424.mvolmode.left = 0;
	dword_424.mvolmode.right = 0;
	dword_424.mvolx.left = 0;
	dword_424.mvolx.right = 0;
	_spu_rev_offsetaddr = _spu_rev_startaddr;
	_spu_FsetRXX(209, _spu_rev_startaddr, 0);
	_spu_AllocBlockNum = 0;
	_spu_AllocLastNum = 0;
	_spu_memList = 0;
	_spu_trans_mode = 0;
	_spu_transMode = 0;
	_spu_keystat = 0;
	_spu_RQmask = 0;
	_spu_RQvoice = 0;
	_spu_env = 0;
}

void SpuInit(void)
{
	Emulator_InitSound();

	_SpuInit(0);
}

void UpdateVoiceSample(SPUVoice& voice)
{
	//if (!voice.sampledirty)
	//	return;

	voice.sampledirty = 0;

	static short waveBuffer[SPU_REALMEMSIZE];

	ALuint alSource = voice.alSource;
	ALuint alBuffer = voice.alBuffer;

	int loopStart = 0, loopLen = 0;
	int count = decodeSound(s_SpuMemory.samplemem + voice.attr.addr, SPU_REALMEMSIZE - voice.attr.addr, waveBuffer, &loopStart, &loopLen, true);

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

	if (loopLen > 0)
	{
		loopStart += voice.attr.loop_addr - voice.attr.addr;

		int sampleOffs[] = { loopStart, loopStart + loopLen };
		alBufferiv(alBuffer, AL_LOOP_POINTS_SOFT, sampleOffs);

		alSourcei(alSource, AL_LOOPING, AL_TRUE);
	}
	else
	{
		int sampleOffs[] = { 0, 0 };
		alBufferiv(alBuffer, AL_LOOP_POINTS_SOFT, sampleOffs);
		alSourcei(alSource, AL_LOOPING, AL_FALSE);
	}


	alBufferData(alBuffer, AL_FORMAT_MONO16, waveBuffer, count * sizeof(short), 44100);

	// set the buffer
	alSourcei(alSource, AL_BUFFER, alBuffer);
}

void SpuSetVoiceAttr(SpuVoiceAttr *arg)
{
	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (!(arg->voice & SPU_VOICECH(i)))
			continue;

		SPUVoice& voice = s_SpuVoices[i];

		ALuint alSource = voice.alSource;

		// update sample
		if ((arg->mask & SPU_VOICE_WDSA) || (arg->mask & SPU_VOICE_LSAX))
		{
			//ALuint tmp = voice.alSource[1];
			//voice.alSource[1] = voice.alSource[0];
			//voice.alSource[1] = tmp;
			//alSource = voice.alSource[0];

			if (arg->mask & SPU_VOICE_WDSA)
			{
				if (voice.attr.addr != arg->addr)
					voice.sampledirty++;

				voice.attr.addr = arg->addr;
			}
			
			if (arg->mask & SPU_VOICE_LSAX)
			{
				if(voice.attr.loop_addr != arg->loop_addr)
					voice.sampledirty++;

				voice.attr.loop_addr = arg->loop_addr;
			}			
		}

		// update volume
		if ((arg->mask & SPU_VOICE_VOLL) || (arg->mask & SPU_VOICE_VOLR))
		{
			if (arg->mask & SPU_VOICE_VOLL)
				voice.attr.volume.left = arg->volume.left;

			if (arg->mask & SPU_VOICE_VOLR)
				voice.attr.volume.right = arg->volume.right;

			float left_gain = float(voice.attr.volume.left) / float(16384);
			float right_gain = float(voice.attr.volume.right) / float(16384);

			float pan = (acosf(left_gain) + asinf(right_gain)) / ((float)M_PI); // average angle in [0,1]
			pan = 2 * pan - 1; // convert to [-1, 1]
			pan = pan * 0.5f; // 0.5 = sin(30') for a +/- 30 degree arc
			alSource3f(alSource, AL_POSITION, pan, 0, -sqrtf(1.0f - pan * pan));

			alSourcef(alSource, AL_GAIN, (left_gain+right_gain)*0.5f);
		}

		// update pitch
		if (arg->mask & SPU_VOICE_PITCH)
		{
			voice.attr.pitch = arg->pitch;

			float pitch = float(voice.attr.pitch) / 4096.0f;

			alSourcef(alSource, AL_PITCH, pitch);
		}
	}
}

void SpuSetKey(long on_off, unsigned long voice_bit)
{
	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (!(voice_bit & SPU_VOICECH(i)))
			continue;

		SPUVoice& voice = s_SpuVoices[i];

		//int state;
		//alGetSourcei(voice.alSource, AL_SOURCE_STATE, &state);

		ALuint alSource = voice.alSource;

		if (on_off)
		{
			UpdateVoiceSample(voice);
			alSourcePlay(alSource);
		}
		else
		{
			alSourceStop(alSource);
		}
	}
}

long SpuGetKeyStatus(unsigned long voice_bit)
{
	int state = AL_STOPPED;

	for (int i = 0; i < SPU_VOICES; i++)
	{
		if (voice_bit != SPU_VOICECH(i))
			continue;

		SPUVoice& voice = s_SpuVoices[i];

		ALuint alSource = voice.alSource;

		alGetSourcei(alSource, AL_SOURCE_STATE, &state);
		break;
	}

	return (state == AL_PLAYING);	// simple as this?
}

void SpuGetAllKeysStatus(char* status)
{
	for (int i = 0; i < SPU_VOICES; i++)
	{
		SPUVoice& voice = s_SpuVoices[i];

		ALuint alSource = voice.alSource;

		int state;
		alGetSourcei(alSource, AL_SOURCE_STATE, &state);

		status[i] = (state == AL_PLAYING);
	}
}

void SpuSetKeyOnWithAttr(SpuVoiceAttr* attr)
{
	SpuSetVoiceAttr(attr);
	SpuSetKey(1, attr->voice);
}

long SpuSetMute(long on_off)
{
	UNIMPLEMENTED();
	return 0;
}

long SpuSetReverb(long on_off)
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long SpuSetReverbVoice(long on_off, unsigned long voice_bit)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuSetCommonAttr(SpuCommonAttr* attr)
{
	UNIMPLEMENTED();
}

static long s_spuMallocVal = 0;

long SpuInitMalloc(long num, char* top)//(F)
{
	s_spuMallocVal = 0;

	if (num > 0)
	{
		//loc_214
		((int*)top)[0] = 0x40001010;
		_spu_memList = (uintptr_t)top;
		_spu_AllocLastNum = 0;
		_spu_AllocBlockNum = num;
		((int*)top)[1] = (0x10000000 << _spu_mem_mode_plus) - 0x1010;
	}

	return num;
}

long SpuMalloc(long size)
{
	int addr = s_spuMallocVal;
	s_spuMallocVal += size;

	return addr; /*(long)(uintptr_t)malloc(size)*/;
}

long SpuMallocWithStartAddr(unsigned long addr, long size)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuFree(unsigned long addr)
{
	/*free((void*)(uintptr_t)addr)*/;
}

unsigned long SpuFlush(unsigned long ev)
{
	//UNIMPLEMENTED();
	return 0;
}

void SpuSetCommonMasterVolume(short mvol_left, short mvol_right)// (F)
{
	//MasterVolume.VolumeLeft.Raw = mvol_left;
	//MasterVolume.VolumeRight.Raw = mvol_right;
}

long SpuSetReverbModeType(long mode)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuSetReverbModeDepth(short depth_left, short depth_right)
{
	UNIMPLEMENTED();
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
		*volL = s_SpuVoices[vNum].attr.volume.left;

	if(volR)
		*volR = s_SpuVoices[vNum].attr.volume.right;
}

void SpuGetVoicePitch(int vNum, unsigned short *pitch)
{
	*pitch = s_SpuVoices[vNum].attr.pitch;
}

void SpuSetVoiceAR(int vNum, unsigned short AR)
{
	UNIMPLEMENTED();
}

void SpuSetVoiceRR(int vNum, unsigned short RR)
{
	UNIMPLEMENTED();
}
