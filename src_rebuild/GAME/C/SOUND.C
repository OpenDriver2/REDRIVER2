#include "DRIVER2.H"
#include "SOUND.H"

#include "LIBSPU.H"
#include "LIBETC.H"
#include "LIBGTE.H"

#include "INLINE_C.H"

#include "CAMERA.H"
#include "XMPLAY.H"
#include "MISSION.H"
#include "GLAUNCH.H"
#include "GAMESND.H"
#include "XAPLAY.H"
#include "PLAYERS.H"

#include "RAND.H"
#include "STRINGS.H"

#define SPU_CHANNEL_COUNT 24

LONGVECTOR dummylong = { 0, 0, 0, 0 };

long bankaddr[2] = { 0 };
long banksize[2] = { 88064, 412672 };

char banks[24] = { 0 };

SAMPLE_DATA samples[7][35];
CHANNEL_DATA channels[MAX_SFX_CHANNELS]; // offset 0xDE480

int master_volume = 0;	// why need two?

int gMasterVolume = 0;
int gMusicVolume = -4000;

int Song_ID = -1;
int VABID = -1;

// decompiled code
// original method signature: 
// void /*$ra*/ InitSound()
 // line 114, offset 0x000790e4
	/* begin block 1 */
		// Start line: 116
		// Start offset: 0x000790E4
		// Variables:
	// 		int ct; // $s0
	/* end block 1 */
	// End offset: 0x000791D4
	// End Line: 161

	/* begin block 2 */
		// Start line: 228
	/* end block 2 */
	// End Line: 229

	/* begin block 3 */
		// Start line: 229
	/* end block 3 */
	// End Line: 230

	/* begin block 4 */
		// Start line: 231
	/* end block 4 */
	// End Line: 232

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitSound(void)
{
	int i;

	SpuInit();
	SpuInitMalloc(7, banks);
	SpuSetMute(1);

	AllocateReverb(3, 16384);

	i = 1;
	do {
		bankaddr[i] = SpuMalloc(banksize[i]);

		if (bankaddr[i] == -1)
		{
			eprintf("Failed to SpuMalloc! Exiting...\n");
			exit(-1);
		}

		i--;
	} while (i >= 0);

	ResetSound();

	XM_OnceOffInit(GetVideoMode());	// [A] PAL or NTSC here

	SetMasterVolume(gMasterVolume);
	VSyncCallback(VsyncProc);

	SpuSetMute(0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ClearChannelFields(int channel /*$a0*/)
 // line 163, offset 0x000791d4
	/* begin block 1 */
		// Start line: 331
	/* end block 1 */
	// End Line: 332

	/* begin block 2 */
		// Start line: 334
	/* end block 2 */
	// End Line: 335

	/* begin block 3 */
		// Start line: 335
	/* end block 3 */
	// End Line: 336

// [D] [T]
void ClearChannelFields(int channel)
{
	channels[channel].loop = 0;
	channels[channel].locked = 0;
	channels[channel].time = 0;
	channels[channel].samplerate = 0;
	channels[channel].srcvolume = -10000;
	channels[channel].srcpitch = 4096;
	channels[channel].volumeScale = 4096;
	channels[channel].dopplerScale = 4096;
	channels[channel].srcposition = NULL;
	channels[channel].position.vx = 0;
	channels[channel].position.vy = 0;
	channels[channel].position.vz = 0;
	channels[channel].srcvelocity = dummylong;
	channels[channel].player = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResetSound()
 // line 187, offset 0x00079250
	/* begin block 1 */
		// Start line: 189
		// Start offset: 0x00079250
		// Variables:
	// 		int ct; // $s0
	/* end block 1 */
	// End offset: 0x00079330
	// End Line: 222

	/* begin block 2 */
		// Start line: 393
	/* end block 2 */
	// End Line: 394

	/* begin block 3 */
		// Start line: 394
	/* end block 3 */
	// End Line: 395

	/* begin block 4 */
		// Start line: 401
	/* end block 4 */
	// End Line: 402

/* WARNING: Unknown calling convention yet parameter storage is locked */

int gSoundMode = 1;		// mono or stereo

int stop_sound_handler = 0;
int sound_paused = 0;
int music_paused = 0;

SpuCommonAttr sound_attr;

// [D] [T]
void ResetSound(void)
{
	int ct;

	stop_sound_handler = 1;
	sound_paused = 0;
	music_paused = 0;

	sound_attr.mvol.left = 16383;
	sound_attr.mvol.right = 16383;
	sound_attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;

	SpuSetCommonAttr(&sound_attr);

	ct = 0;
	do {
		memset(&channels[ct], 0, sizeof(CHANNEL_DATA));

		channels[ct].attr.volmode.left = 0;
		channels[ct].attr.volmode.right = 0;
		channels[ct].attr.voice = SPU_KEYCH(ct);

		ClearChannelFields(ct);
		ct++;
	} while (ct < MAX_SFX_CHANNELS);

	ct = 0;
	do {
		SpuSetVoiceRR(ct, 6);
		SpuSetVoiceAR(ct, 35);
	
		ct++;
	} while (ct < MAX_SFX_CHANNELS);

	stop_sound_handler = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetReverbState(int on /*$a0*/)
 // line 233, offset 0x0007a6c0
	/* begin block 1 */
		// Start line: 1777
	/* end block 1 */
	// End Line: 1778

	/* begin block 2 */
		// Start line: 466
	/* end block 2 */
	// End Line: 467

	/* begin block 3 */
		// Start line: 1778
	/* end block 3 */
	// End Line: 1779

// [D] [T]
void SetReverbState(int on)
{
	if (on == 0)
		SpuSetReverbVoice(0, SPU_ALLCH);
	else
		SpuSetReverbVoice(1, SPU_ALLCH);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetReverbInGameState(int on /*$a0*/)
 // line 253, offset 0x0007a704
	/* begin block 1 */
		// Start line: 254
		// Start offset: 0x0007A704
		// Variables:
	// 		long cl; // $a1
	/* end block 1 */
	// End offset: 0x0007A75C
	// End Line: 264

	/* begin block 2 */
		// Start line: 1817
	/* end block 2 */
	// End Line: 1818

	/* begin block 3 */
		// Start line: 1820
	/* end block 3 */
	// End Line: 1821

// [D] [T]
void SetReverbInGameState(int on)
{
	long cl;

	cl = 0xffff;

	gSpeechQueue.reverb = on;

	if (on && gSpeechQueue.is_playing)
		cl &= ~SPU_KEYCH(gSpeechQueue.chan);

	SpuSetReverbVoice(on, cl);
}



// decompiled code
// original method signature: 
// int /*$ra*/ SetReverbChannelState(int ch /*$a0*/, int on /*$s0*/)
 // line 274, offset 0x0007a75c
	/* begin block 1 */
		// Start line: 275
		// Start offset: 0x0007A75C
		// Variables:
	// 		long cl; // $s1
	// 		int prev; // $s2
	/* end block 1 */
	// End offset: 0x0007A7B0
	// End Line: 281

	/* begin block 2 */
		// Start line: 1849
	/* end block 2 */
	// End Line: 1850

	/* begin block 3 */
		// Start line: 1860
	/* end block 3 */
	// End Line: 1861

// [D] [T]
int SetReverbChannelState(int ch, int on)
{
	long cl;
	int prev;

	cl = SPU_KEYCH(ch);

	prev = SpuGetReverbVoice();

	SpuSetReverbVoice(on, cl);

	return (prev & cl) != 0;
}



// decompiled code
// original method signature: 
// void SetMasterVolume(int vol /*$a0*/)
 // line 288, offset 0x0007a7b0
	/* begin block 1 */
		// Start line: 1882
	/* end block 1 */
	// End Line: 1883

	/* begin block 2 */
		// Start line: 1890
	/* end block 2 */
	// End Line: 1891

	/* begin block 3 */
		// Start line: 1891
	/* end block 3 */
	// End Line: 1892

// [D] [T]
void SetMasterVolume(int vol)
{
	int vl = MAX(0, 10000 + vol);

	master_volume = vl + vl / 2 + vl / 8 + vl / 128;
	gMasterVolume = vol;
}



// decompiled code
// original method signature: 
// char /*$ra*/ SetPlayerOwnsChannel(int chan /*$a0*/, char player /*$a1*/)
 // line 307, offset 0x0007aba8
	/* begin block 1 */
		// Start line: 308
		// Start offset: 0x0007ABA8
	/* end block 1 */
	// End offset: 0x0007ABCC
	// End Line: 312

	/* begin block 2 */
		// Start line: 614
	/* end block 2 */
	// End Line: 615

	/* begin block 3 */
		// Start line: 3016
	/* end block 3 */
	// End Line: 3017

// [D] [T]
char SetPlayerOwnsChannel(int chan, char player)
{
	char oldPlayer;

	oldPlayer = channels[chan].player;
	channels[chan].player = player;

	return oldPlayer;
}



// decompiled code
// original method signature: 
// int /*$ra*/ StartSound(int channel /*$a0*/, int bank /*$s1*/, int sample /*$s2*/, int volume /*$s0*/, int pitch /*stack 16*/)
 // line 323, offset 0x0007a7f8
	/* begin block 1 */
		// Start line: 1960
	/* end block 1 */
	// End Line: 1961

	/* begin block 2 */
		// Start line: 1961
	/* end block 2 */
	// End Line: 1962

// [D] [T]
int StartSound(int channel, int bank, int sample, int volume, int pitch)
{
	if (channel < 0)
		channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = NULL;
	channels[channel].srcvolume = volume;

	return CompleteSoundSetup(channel, bank, sample, pitch, 0);
}



// decompiled code
// original method signature: 
// int /*$ra*/ Start3DTrackingSound(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s3*/, VECTOR *position /*$s2*/, long *velocity /*stack 16*/)
 // line 342, offset 0x0007a994
	/* begin block 1 */
		// Start line: 684
	/* end block 1 */
	// End Line: 685

// [D] [T]
int Start3DTrackingSound(int channel, int bank, int sample, VECTOR *position, long *velocity)
{
	if (channel < 0)
		channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = position;
	channels[channel].srcvelocity = velocity ? velocity : dummylong;
	channels[channel].srcpitch = 4096;
	channels[channel].srcvolume = 0;

	channel = CompleteSoundSetup(channel, bank, sample, 4096, 0);

	ComputeDoppler(&channels[channel]);
	SetChannelPitch(channel, 4096);

	return channel;
}



// decompiled code
// original method signature: 
// int /*$ra*/ Start3DSoundVolPitch(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s4*/, int x /*$s3*/, int y /*stack 16*/, int z /*stack 20*/, int volume /*stack 24*/, int pitch /*stack 28*/)
 // line 357, offset 0x0007a894
	/* begin block 1 */
		// Start line: 2034
	/* end block 1 */
	// End Line: 2035

// [D]
int Start3DSoundVolPitch(int channel, int bank, int sample, int x, int y, int z, int volume, int pitch)
{
	if (channel < 0)
		channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = &channels[channel].position;
	channels[channel].srcvelocity = dummylong;
	channels[channel].position.vx = x;
	channels[channel].position.vy = y;
	channels[channel].position.vz = z;
	channels[channel].srcvolume = volume;
	channels[channel].srcpitch = pitch;

	channel = CompleteSoundSetup(channel, bank, sample, pitch, 0);

	ComputeDoppler(&channels[channel]);
	SetChannelPitch(channel, pitch);

	return channel;
	
}



// decompiled code
// original method signature: 
// int /*$ra*/ CompleteSoundSetup(int channel /*$s2*/, int bank /*$s0*/, int sample /*$s5*/, int pitch /*$s1*/, int proximity /*stack 16*/)
 // line 399, offset 0x00079330
	/* begin block 1 */
		// Start line: 400
		// Start offset: 0x00079330
		// Variables:
	// 		long bpf; // $a1
	// 		long rate; // $a1
	/* end block 1 */
	// End offset: 0x00079504
	// End Line: 443

	/* begin block 2 */
		// Start line: 669
	/* end block 2 */
	// End Line: 670

	/* begin block 3 */
		// Start line: 847
	/* end block 3 */
	// End Line: 848

// [D] [T]
int CompleteSoundSetup(int channel, int bank, int sample, int pitch, int proximity)
{
	int bpf;
	int rate;

	rate = samples[bank][sample].samplerate * pitch;
	bpf = (rate / 4096) / 50;

	if (bpf == 0) 
	{
		channel = -1;
	}
	else
	{
		if (gSoundMode == 1 && proximity != -1) 
			UpdateVolumeAttributesS(channel, proximity);
		else
			UpdateVolumeAttributesM(channel);

		stop_sound_handler = 1;

		channels[channel].attr.mask =  SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER | SPU_VOICE_PITCH | SPU_VOICE_WDSA;
		channels[channel].attr.addr = samples[bank][sample].address;
		channels[channel].attr.pitch = MIN(rate / 44100, 16383);
		channels[channel].time = (samples[bank][sample].length / bpf) * 2 + 2;
		channels[channel].loop = samples[bank][sample].loop;

		channels[channel].samplerate = samples[bank][sample].samplerate;

		if (sound_paused != 0)
		{
			channels[channel].attr.volume.left = 0;
			channels[channel].attr.volume.right = 0;
		}

		SpuSetVoiceAttr(&channels[channel].attr);
		SpuSetKey(1, channels[channel].attr.voice);

		stop_sound_handler = 0;
	}

	return channel;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetChannelPitch(int channel /*$a0*/, int pitch /*$a1*/)
 // line 450, offset 0x00079504
	/* begin block 1 */
		// Start line: 451
		// Start offset: 0x00079504
		// Variables:
	// 		long rate; // $a0
	/* end block 1 */
	// End offset: 0x000795B4
	// End Line: 470

	/* begin block 2 */
		// Start line: 963
	/* end block 2 */
	// End Line: 964

	/* begin block 3 */
		// Start line: 971
	/* end block 3 */
	// End Line: 972

	/* begin block 4 */
		// Start line: 973
	/* end block 4 */
	// End Line: 974

// [D] [T]
void SetChannelPitch(int channel, int pitch)
{
	long rate;

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return;

	if (sound_paused)
		return;

	if (channels[channel].time != 0 && pitch > 128) 
	{
		channels[channel].srcpitch = pitch;

		rate = (channels[channel].samplerate * ((channels[channel].dopplerScale * pitch) / 4096)) / 44100;

		channels[channel].attr.mask = SPU_VOICE_PITCH;
		channels[channel].attr.pitch = MIN(rate, 16383);

		SpuSetVoiceAttr(&channels[channel].attr);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetChannelVolume(int channel /*$s0*/, int volume /*$t1*/, int proximity /*$a2*/)
 // line 477, offset 0x0007aa78
	/* begin block 1 */
		// Start line: 478
		// Start offset: 0x0007AA78
	/* end block 1 */
	// End offset: 0x0007AB24
	// End Line: 495

	/* begin block 2 */
		// Start line: 2333
	/* end block 2 */
	// End Line: 2334

// [D] [T]
void SetChannelVolume(int channel, int volume, int proximity)
{
	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return;

	if (sound_paused == 0 && channels[channel].time != 0) 
	{
		channels[channel].srcvolume = volume;

		if (gSoundMode == 1)
			UpdateVolumeAttributesS(channel, proximity);
		else
			UpdateVolumeAttributesM(channel);

		channels[channel].attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER;
		SpuSetVoiceAttr(&channels[channel].attr);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ComputeDoppler(CHANNEL_DATA *ch /*$s1*/)
 // line 501, offset 0x000795c4
	/* begin block 1 */
		// Start line: 502
		// Start offset: 0x000795C4
		// Variables:
	// 		int dist; // $s0
	// 		int seperationrate; // $v0
	// 		PLAYER *pl; // $s0
	/* end block 1 */
	// End offset: 0x00079720
	// End Line: 527

	/* begin block 2 */
		// Start line: 1078
	/* end block 2 */
	// End Line: 1079

// [D] [T]
void ComputeDoppler(CHANNEL_DATA *ch)
{
	long dist;
	long seperationrate;

	VECTOR *srcPos;
	long *srcVel;

	PLAYER *pl;
	int dx, dy, dz;

	srcPos = ch->srcposition;
	
	if (srcPos == NULL) 
	{
		ch->dopplerScale = ONE;
		return;
	}

	srcVel = ch->srcvelocity;

	pl = &player[ch->player];

	dx = srcPos->vx - pl->cameraPos.vx;
	dy = srcPos->vy + pl->cameraPos.vy;
	dz = srcPos->vz - pl->cameraPos.vz;
	
	dist = jsqrt(dx * dx + dy * dy + dz * dz);

	dx = (srcPos->vx - pl->cameraPos.vx) + FIXEDH(srcVel[0] - pl->camera_vel[0]);
	dy = (srcPos->vy + pl->cameraPos.vy) + FIXEDH(srcVel[1] - pl->camera_vel[1]);
	dz = (srcPos->vz - pl->cameraPos.vz) + FIXEDH(srcVel[2] - pl->camera_vel[2]);

	seperationrate = jsqrt(dx * dx + dy * dy + dz * dz);
	
	ch->dopplerScale = (seperationrate - dist) * -3 + ONE;
	ch->cameradist = dist;

	if (ch->dopplerScale << 16 < 0) 
		ch->dopplerScale = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetChannelPosition3(int channel /*$s1*/, VECTOR *position /*$a0*/, long *velocity /*$t0*/, int volume /*$t2*/, int pitch /*stack 16*/, int proximity /*stack 20*/)
 // line 588, offset 0x0007abcc
	/* begin block 1 */
		// Start line: 589
		// Start offset: 0x0007ABCC
	/* end block 1 */
	// End offset: 0x0007ACC0
	// End Line: 612

	/* begin block 2 */
		// Start line: 3300
	/* end block 2 */
	// End Line: 3301

	/* begin block 3 */
		// Start line: 3577
	/* end block 3 */
	// End Line: 3578

// [D] [T]
void SetChannelPosition3(int channel, VECTOR *position, long *velocity, int volume, int pitch, int proximity)
{
	if (channel < 0 || channel >= MAX_SFX_CHANNELS)
		return;

	if (camera_change != 1 && old_camera_change != 1 && sound_paused == 0)
	{
		channels[channel].srcposition = position;
		channels[channel].srcvelocity = velocity ? velocity : dummylong;
		channels[channel].srcvolume = volume;

		if (gSoundMode == 1)
			UpdateVolumeAttributesS(channel, proximity);
		else 
			UpdateVolumeAttributesM(channel);

		channels[channel].attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER;

		SpuSetVoiceAttr(&channels[channel].attr);

		ComputeDoppler(&channels[channel]);

		SetChannelPitch(channel, pitch);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PauseXM()
 // line 635, offset 0x00079734
	/* begin block 1 */
		// Start line: 636
		// Start offset: 0x00079734
		// Variables:
	// 		int fade; // $v1
	/* end block 1 */
	// End offset: 0x00079794
	// End Line: 655

	/* begin block 2 */
		// Start line: 1356
	/* end block 2 */
	// End Line: 1357

	/* begin block 3 */
		// Start line: 1358
	/* end block 3 */
	// End Line: 1359

/* WARNING: Unknown calling convention yet parameter storage is locked */

static int music_pause_max;

// [D] [T]
void PauseXM(void)
{
	int fade;

	if (music_paused != 0)
		return;

	music_pause_max = 0;
	fade = 96;

	while (fade < music_pause_max)	// [A] WTF?
		fade += 96;

	if (Song_ID != -1)	// [A] bug fix
		XM_Pause(Song_ID);

	music_paused = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PauseSFX()
 // line 657, offset 0x00079794
	/* begin block 1 */
		// Start line: 658
		// Start offset: 0x00079794
		// Variables:
	// 		int i; // $s1
	// 		int fade; // $s3
	/* end block 1 */
	// End offset: 0x00079958
	// End Line: 681

	/* begin block 2 */
		// Start line: 1399
	/* end block 2 */
	// End Line: 1400

	/* begin block 3 */
		// Start line: 1402
	/* end block 3 */
	// End Line: 1403

	/* begin block 4 */
		// Start line: 1404
	/* end block 4 */
	// End Line: 1405

/* WARNING: Unknown calling convention yet parameter storage is locked */

static __pauseinfo pause;

// [D] [T]
void PauseSFX(void)
{
	int i, fade;

	if (sound_paused)
		return;

	pause.max = 0;

	// set the faded volume
	for (i = 0; i < MAX_SFX_CHANNELS; i++)
	{
		int vl;
		SpuGetVoiceVolume(i, (short*)&pause.voll[i], (short*)&pause.volr[i]);

		vl = MAX(pause.voll[i], pause.volr[i]);

		if (pause.max < vl) 
			pause.max = vl;

		pause.lev = gMasterVolume + 10000;
	}

	fade = 0;

	// fade out each voice
	while (fade < pause.max)
	{
		for (i = 0; i < MAX_SFX_CHANNELS; i++)
		{
			SpuSetVoiceVolume(i, MAX(0, pause.voll[i] - fade), MAX(0, pause.volr[i] - fade));
		}

		fade += 96;
	}

	// pause by zeroing pitch
	for (i = 0; i < MAX_SFX_CHANNELS; i++)
	{
		SpuGetVoicePitch(i, &pause.pitch[i]);
		SpuSetVoicePitch(i, 0);
	}

	sound_paused = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PauseSound()
 // line 683, offset 0x0007acd8
	/* begin block 1 */
		// Start line: 3774
	/* end block 1 */
	// End Line: 3775

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void PauseSound(void)
{
	SetReverbInGameState(0);
	PauseXM();
	PauseSFX();
	PauseXA();
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnPauseXM()
 // line 698, offset 0x00079958
	/* begin block 1 */
		// Start line: 699
		// Start offset: 0x00079958
		// Variables:
	// 		int fade; // $a1
	/* end block 1 */
	// End offset: 0x000799B0
	// End Line: 717

	/* begin block 2 */
		// Start line: 1479
	/* end block 2 */
	// End Line: 1480

	/* begin block 3 */
		// Start line: 1497
	/* end block 3 */
	// End Line: 1498

	/* begin block 4 */
		// Start line: 1499
	/* end block 4 */
	// End Line: 1500

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void UnPauseXM(void)
{
	if (Song_ID == -1)
		return;

	int fade;

	if (music_paused != 0)
	{
		fade = 0;

		do {
			fade += 96;
		} while (fade < music_pause_max);	// [A] WTF?

		XM_Restart(Song_ID);
		music_paused = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnPauseSFX()
 // line 720, offset 0x000799b0
	/* begin block 1 */
		// Start line: 721
		// Start offset: 0x000799B0
		// Variables:
	// 		int i; // $s1
	// 		int fade; // $s2
	/* end block 1 */
	// End offset: 0x00079B38
	// End Line: 742

	/* begin block 2 */
		// Start line: 1539
	/* end block 2 */
	// End Line: 1540

	/* begin block 3 */
		// Start line: 1543
	/* end block 3 */
	// End Line: 1544

	/* begin block 4 */
		// Start line: 1545
	/* end block 4 */
	// End Line: 1546

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void UnPauseSFX(void)
{
	int i, fade, vol;

	if (!sound_paused)
		return;

	// restore pitch
	for (i = 0; i < MAX_SFX_CHANNELS; i++)
	{
		SpuSetVoicePitch(i, pause.pitch[i]);
	}

	vol = 10000 + gMasterVolume;

	// restore volume levels
	if (pause.lev != 0 && pause.lev != vol)
	{
		for (i = 0; i < MAX_SFX_CHANNELS; i++)
		{
			pause.voll[i] = pause.voll[i] * vol / pause.lev;
			pause.volr[i] = pause.volr[i] * vol / pause.lev;
		}
	}

	fade = 0;

	// fade out each voice
	while (fade < pause.max)
	{
		for (i = 0; i < MAX_SFX_CHANNELS; i++)
		{
			SpuSetVoiceVolume(i, MIN(fade, pause.voll[i]), MIN(fade, pause.volr[i]));
		}

		fade += 96;
	}
	
	sound_paused = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnPauseSound()
 // line 744, offset 0x0007ad10
	/* begin block 1 */
		// Start line: 745
		// Start offset: 0x0007AD10
	/* end block 1 */
	// End offset: 0x0007AD40
	// End Line: 753

	/* begin block 2 */
		// Start line: 3896
	/* end block 2 */
	// End Line: 3897

	/* begin block 3 */
		// Start line: 3900
	/* end block 3 */
	// End Line: 3901

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void UnPauseSound(void)
{
	UnPauseXM();
	UnPauseSFX();
	ResumeXA();
}



// decompiled code
// original method signature: 
// void /*$ra*/ StopChannel(int channel /*$s2*/)
 // line 760, offset 0x0007ad40
	/* begin block 1 */
		// Start line: 761
		// Start offset: 0x0007AD40

		/* begin block 1.1 */
			// Start line: 763
			// Start offset: 0x0007AD64
			// Variables:
		// 		unsigned char l; // $s3
		// 		int vsync; // $s0
		/* end block 1.1 */
		// End offset: 0x0007ADD8
		// End Line: 771
	/* end block 1 */
	// End offset: 0x0007ADF4
	// End Line: 773

	/* begin block 2 */
		// Start line: 3920
	/* end block 2 */
	// End Line: 3921

	/* begin block 3 */
		// Start line: 3928
	/* end block 3 */
	// End Line: 3929

//  [D] [T]
void StopChannel(int channel)
{
	unsigned char lock;
	int vsync;

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	
		return;

	lock = channels[channel].locked;
	vsync = VSync(-1);

	SpuSetKey(0, channels[channel].attr.voice);

	// PSX SPU keyoff sometimes does not work for first time due to it's nature
	do {
		if (SpuGetKeyStatus(channels[channel].attr.voice) == 0)
			break;
	} while (VSync(-1) - vsync < 8);

	ClearChannelFields(channel);
	
	channels[channel].locked = lock;
}



// decompiled code
// original method signature: 
// void /*$ra*/ StopAllChannels()
 // line 780, offset 0x0007adf4
	/* begin block 1 */
		// Start line: 782
		// Start offset: 0x0007ADF4
		// Variables:
	// 		int ct; // $s0
	/* end block 1 */
	// End offset: 0x0007AE34
	// End Line: 790

	/* begin block 2 */
		// Start line: 3962
	/* end block 2 */
	// End Line: 3963

	/* begin block 3 */
		// Start line: 3970
	/* end block 3 */
	// End Line: 3971

	/* begin block 4 */
		// Start line: 3971
	/* end block 4 */
	// End Line: 3972

	/* begin block 5 */
		// Start line: 3973
	/* end block 5 */
	// End Line: 3974

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void StopAllChannels(void)
{
	int ct;

	ct = 0;
	do {
		StopChannel(ct);
		VSync(0);
		ct++;
	} while (ct < MAX_SFX_CHANNELS);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LockChannel(int channel /*$a0*/)
 // line 797, offset 0x0007ae34
	/* begin block 1 */
		// Start line: 3999
	/* end block 1 */
	// End Line: 4000

	/* begin block 2 */
		// Start line: 4007
	/* end block 2 */
	// End Line: 4008

	/* begin block 3 */
		// Start line: 4008
	/* end block 3 */
	// End Line: 4009

// [D] [T]
void LockChannel(int channel)
{
	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return;

	channels[channel].locked = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnlockChannel(int c /*$a0*/)
 // line 811, offset 0x0007ae64
	/* begin block 1 */
		// Start line: 4035
	/* end block 1 */
	// End Line: 4036

// [D] [T]
void UnlockChannel(int c)
{
	if (c < 0 || c >= MAX_SFX_CHANNELS)	// [A]
		return;

	channels[c].locked = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SoundHandler()
 // line 822, offset 0x00079b38
	/* begin block 1 */
		// Start line: 824
		// Start offset: 0x00079B38
		// Variables:
	// 		int ct; // $a0
	// 		long off; // $a1
	/* end block 1 */
	// End offset: 0x00079BBC
	// End Line: 838

	/* begin block 2 */
		// Start line: 1674
	/* end block 2 */
	// End Line: 1675

	/* begin block 3 */
		// Start line: 1755
	/* end block 3 */
	// End Line: 1756

	/* begin block 4 */
		// Start line: 1756
	/* end block 4 */
	// End Line: 1757

	/* begin block 5 */
		// Start line: 1759
	/* end block 5 */
	// End Line: 1760

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void SoundHandler(void)
{
	int ct;
	long off;

	off = 0;

	if (stop_sound_handler || sound_paused)
		return;

	for (ct = 0; ct < MAX_SFX_CHANNELS; ct++)
	{
		if (channels[ct].loop || channels[ct].time == 0)
			continue;
	
		if (--channels[ct].time == 0) 
			off |= SPU_KEYCH(ct);
	}

	if (off) 
		SpuSetKey(0, off);
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadSoundBank(char *address /*$s3*/, int length /*$s2*/, int bank /*$s1*/)
 // line 845, offset 0x0007ae90
	/* begin block 1 */
		// Start line: 846
		// Start offset: 0x0007AE90
		// Variables:
	// 		int num_samples; // $s4
	// 		int slength; // $s2
	// 		int spuaddress; // $s1
	// 		int ct; // $v1
	/* end block 1 */
	// End offset: 0x0007AF84
	// End Line: 876

	/* begin block 2 */
		// Start line: 4103
	/* end block 2 */
	// End Line: 4104

// [D] [T]
int LoadSoundBank(char *address, int length, int bank)
{
	int slength;
	int spuaddress;
	int num_samples;
	int ct;

	spuaddress = bankaddr[bank];

	num_samples = *(int *)address;
	slength = num_samples * sizeof(SAMPLE_DATA) + sizeof(int);

	// copy sample info
	memcpy(samples[bank], address + sizeof(int), num_samples * sizeof(SAMPLE_DATA));

	// transfer sample data
	SpuSetTransferMode(SPU_TRANSFER_BY_DMA);

	SpuSetTransferStartAddr(spuaddress);
	SpuWrite((unsigned char*)address + slength, length - slength);
	
	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

	for(ct = 0; ct < num_samples; ct++)
	{
		samples[bank][ct].address += spuaddress;
	}

	return num_samples;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateXMSamples(int num_samps /*$s2*/)
 // line 882, offset 0x0007b1c4
	/* begin block 1 */
		// Start line: 883
		// Start offset: 0x0007B1C4
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x0007B228
	// End Line: 888

	/* begin block 2 */
		// Start line: 1764
	/* end block 2 */
	// End Line: 1765

	/* begin block 3 */
		// Start line: 4724
	/* end block 3 */
	// End Line: 4725

// [D] [T]
void UpdateXMSamples(int num_samps)
{
	int i;
	for (i = 0; i < num_samps; i++)
		XM_SetVAGAddress(VABID, i, samples[0][i].address);
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadSoundBankDynamic(char *address /*$s2*/, int length /*$s6*/, int dbank /*$a2*/)
 // line 904, offset 0x00079bcc
	/* begin block 1 */
		// Start line: 905
		// Start offset: 0x00079BCC
		// Variables:
	// 		static __LSBDinfo tabs; // offset 0x0
	// 		int i; // $a3
	// 		int num_samples; // $s1
	// 		int slength; // $s0
	/* end block 1 */
	// End offset: 0x00079E04
	// End Line: 977

	/* begin block 2 */
		// Start line: 1926
	/* end block 2 */
	// End Line: 1927

// [D] [T]
int LoadSoundBankDynamic(char *address, int length, int dbank)
{
	static __LSBDinfo lsbTabs;
	
	int i;
	int slength;
	int num_samples;

	if (address == NULL) 
	{
		switch (length)
		{
			case 0:
				if (dbank == 0)
				{
					lsbTabs.append = 0;
					puts("*---LSBD(): successful init---*\n");
				}
				break;
			case 1:
				lsbTabs.memtop = lsbTabs.addr;
				puts("*---LSBD(): saved memtop---*\n");
				break;
			case 2:
				lsbTabs.addr = lsbTabs.memtop;
				puts("*---LSBD(): goneto memtop---*\n");
				break;
			case 3:
				lsbTabs.bnktop[dbank] = lsbTabs.count[dbank];
				printf("*---LSBD(): saved banktop %d---*\n", lsbTabs.bnktop[dbank]);
				break;
			case 4:
				lsbTabs.count[dbank] = lsbTabs.bnktop[dbank];
				printf("*---LSBD(): goneto banktop %d---*\n", lsbTabs.count[dbank]);
				break;
		}

		return 0;
	}

	// init bank samples
	if (lsbTabs.append == 0) 
	{
		lsbTabs.addr = bankaddr[1];
		
		for(i = 0; i < 7; i++)
			lsbTabs.count[i] = 0;
		
		lsbTabs.append = 1;
	}

	num_samples = *(int *)address;
	slength = num_samples * sizeof(SAMPLE_DATA) + sizeof(int);

	memcpy(samples[dbank] + lsbTabs.count[dbank], address + sizeof(int), num_samples * sizeof(SAMPLE_DATA));

	SpuSetTransferMode(SPU_TRANSFER_BY_DMA);

	SpuSetTransferStartAddr(lsbTabs.addr);
	SpuWrite((unsigned char*)address + slength, length - slength);

	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

	// set proper address for samples
	for(i = 0; i < num_samples; i++)
	{
		samples[dbank][lsbTabs.count[dbank]].address += lsbTabs.addr;
		lsbTabs.count[dbank]++;
	}
	
	lsbTabs.addr += length - slength;

	return num_samples;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FreeXM()
 // line 993, offset 0x0007af84
	/* begin block 1 */
		// Start line: 4304
	/* end block 1 */
	// End Line: 4305

	/* begin block 2 */
		// Start line: 4422
	/* end block 2 */
	// End Line: 4423

	/* begin block 3 */
		// Start line: 4424
	/* end block 3 */
	// End Line: 4425

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void FreeXM(void)
{
	if (Song_ID == -1)
		return;

	XM_Exit();
	XM_FreeAllSongIDs();
	XM_CloseVAB2(VABID);

	Song_ID = -1;
	VABID = -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ StartXM(int reverb /*$s2*/)
 // line 1012, offset 0x0007afd0
	/* begin block 1 */
		// Start line: 1013
		// Start offset: 0x0007AFD0
		// Variables:
	// 		int ct; // $s0
	/* end block 1 */
	// End offset: 0x0007B050
	// End Line: 1028

	/* begin block 2 */
		// Start line: 4460
	/* end block 2 */
	// End Line: 4461

// [D] [T]
void StartXM(int reverb)
{
	int ct;

	if (Song_ID == -1)
		return;
	
	XM_PlayStart(Song_ID, -1);
	SpuSetReverb(1);

	for(ct = MAX_SFX_CHANNELS; ct < SPU_CHANNEL_COUNT; ct++)
	{
		SpuSetReverbVoice(reverb, SPU_VOICECH(ct));
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ StopXM()
 // line 1035, offset 0x0007b050
	/* begin block 1 */
		// Start line: 4514
	/* end block 1 */
	// End Line: 4515

	/* begin block 2 */
		// Start line: 4522
	/* end block 2 */
	// End Line: 4523

	/* begin block 3 */
		// Start line: 4524
	/* end block 3 */
	// End Line: 4525

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void StopXM(void)
{
	XM_PlayStop(Song_ID);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetXMVolume(int volume /*$a0*/)
 // line 1073, offset 0x0007b074
	/* begin block 1 */
		// Start line: 1074
		// Start offset: 0x0007B074
		// Variables:
	// 		int vol; // $a1
	/* end block 1 */
	// End offset: 0x0007B0C4
	// End Line: 1085

	/* begin block 2 */
		// Start line: 4598
	/* end block 2 */
	// End Line: 4599

	/* begin block 3 */
		// Start line: 4602
	/* end block 3 */
	// End Line: 4603

// [D] [T]
void SetXMVolume(int volume)
{
	int vol;

	vol = MIN(10000, MAX(0, 10000 + volume));

	gMusicVolume = volume;

	if (Song_ID == -1)
		return;

	XM_SetMasterVol(Song_ID, (vol >> 7) + (vol >> 8));
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetFreeChannel()
 // line 1124, offset 0x00079e04
	/* begin block 1 */
		// Start line: 1125
		// Start offset: 0x00079E04
		// Variables:
	// 		int ct; // $a0
	// 		int least; // $s1
	// 		int il; // $s0
	// 		char status[24]; // stack offset -40
	/* end block 1 */
	// End offset: 0x00079F38
	// End Line: 1156

	/* begin block 2 */
		// Start line: 2232
	/* end block 2 */
	// End Line: 2233

	/* begin block 3 */
		// Start line: 2380
	/* end block 3 */
	// End Line: 2381

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int GetFreeChannel(int force)
{
	int channel;
	int it;
	int least;

	char status[SPU_CHANNEL_COUNT];
	
	SpuGetAllKeysStatus(status);

	channel = 0;

	// find free channel
	while (channel < MAX_SFX_CHANNELS && (channels[channel].locked || status[channel] != SPU_OFF && status[channel] != SPU_RESET))
	{
		channel++;
	}

	if (channel < MAX_SFX_CHANNELS)
		return channel;

	if (!force)
		return -1;
	
	// if not found free channels - free already playing one
	channel = -1;
	least = 0;
	
	for (it = 0; it < MAX_SFX_CHANNELS; it++)
	{
		if (channels[it].locked || channels[it].loop)
			continue;
		
		if (channel == -1 || channels[it].time < least)
		{
			channel = it;
			least = channels[it].time;
		}
	}

	if (channel != -1) 
		StopChannel(channel);

	return channel;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateVolumeAttributesS(int channel /*$s2*/, int proximity /*$s5*/)
 // line 1163, offset 0x00079f38
	/* begin block 1 */
		// Start line: 1164
		// Start offset: 0x00079F38
		// Variables:
	// 		int volume; // $s1
	// 		int vol; // $a2
	// 		long ang; // $s0
	// 		long dist; // $s6
	// 		int player_id; // $a3
	// 		VECTOR *pos; // $s3
	// 		VECTOR *cam_pos; // $s4
	// 		int cam_ang; // $fp
	// 		long damp; // $v1

		/* begin block 1.1 */
			// Start line: 1215
			// Start offset: 0x0007A1B4
		/* end block 1.1 */
		// End offset: 0x0007A200
		// End Line: 1217
	/* end block 1 */
	// End offset: 0x0007A330
	// End Line: 1230

	/* begin block 2 */
		// Start line: 2464
	/* end block 2 */
	// End Line: 2465

	/* begin block 3 */
		// Start line: 2472
	/* end block 3 */
	// End Line: 2473

int gSurround = 0;

// [D]
void UpdateVolumeAttributesS(int channel, int proximity)
{
	int volume;
	int vol;
	int player_id;
	VECTOR *pos;
	VECTOR *cam_pos;
	long dist;
	int cam_ang, ang;
	long damp;
	

	player_id = channels[channel].player;
	pos = channels[channel].srcposition;
	cam_pos = &player[player_id].cameraPos;
	cam_ang = player[player_id].snd_cam_ang;

	volume = CalculateVolume(channel);

	vol = MAX(0, 10000 + volume);
	
	if (camera_change == 1 || old_camera_change == 1)
		vol = 0;

	vol = (vol + vol / 2 + vol / 8 + vol / 128) * master_volume / 16384;

	channels[channel].attr.volume.left = vol;
	channels[channel].attr.volume.right = gSurround ? -vol : vol;	// HMM: why like that?

	if (vol == 0)
		return;

	if (pos == NULL)
		return;

	if (pos->vz == cam_pos->vz && cam_pos->vx == pos->vx)
		return;

	// HACK: player car sounds are not affected with stereo
	if (player[player_id].cameraView == 2) 
	{
		if (channel == player[player_id].skidding.chan || channel == player[player_id].wheelnoise.chan)
			return;

		if (player_id == 0)
		{
			if (channel == 0 || channel == 1 || channel == 2)
				return;
		}
		else if (player_id == 1)
		{
			if (channel == 3 || channel == 4 || channel == 5) 
				return;
		}
	}

	// calc angle relative to camera angle and source position
	ang = 2048 - (((-ratan2(pos->vz - cam_pos->vz, cam_pos->vx - pos->vx) + 4096 + 3072) % 4096 - (cam_ang - 4096)) % 4096);

	// wtf?
	if(ABS(ang) >= 1024)
	{
		int tmp;
		tmp = 2048 - ABS(ang);

		if (ang < 1)
			ang = -tmp;
		else
			ang = tmp;
	}

	if (proximity > 0)
	{
		int dx, dz;
		
		dx = cam_pos->vx - pos->vx;
		dz = cam_pos->vz - pos->vz;

		dist = jsqrt(dx * dx + dz * dz);

		if(dist >= 12000)
			proximity = 0;
	}

	// calculate spatial damp for specific side
	if (ang > 0) 
	{
		damp = ((vol * 9 / 10) * ang) / 1024;

		if (proximity > 0)
			damp = damp * dist / 12000;

		channels[channel].attr.volume.left = MAX(0, vol - damp);
	}
	else if (ang < 0) 
	{
		damp = ((vol * 9 / 10) * -ang) / 1024;

		if (proximity > 0)
			damp = damp * dist / 12000;

		channels[channel].attr.volume.right = gSurround ? -MAX(0, vol - damp) : MAX(0, vol - damp);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateVolumeAttributesM(int channel /*$s0*/)
 // line 1232, offset 0x0007b0c4
	/* begin block 1 */
		// Start line: 1233
		// Start offset: 0x0007B0C4
		// Variables:
	// 		int volume; // $a1
	// 		int vol; // $a0
	/* end block 1 */
	// End offset: 0x0007B178
	// End Line: 1249

	/* begin block 2 */
		// Start line: 4797
	/* end block 2 */
	// End Line: 4798

	/* begin block 3 */
		// Start line: 4916
	/* end block 3 */
	// End Line: 4917

// [D] [T]
void UpdateVolumeAttributesM(int channel)
{
	int volume;
	int vol;

	volume = CalculateVolume(channel);

	vol = MAX(0, 10000 + volume);
	
	if (camera_change == 1 || old_camera_change == 1)
		vol = 0;
	
	vol = (vol + vol / 2 + vol / 8 + vol / 128) * master_volume / 16384;
	
	channels[channel].attr.volume.left = vol;
	channels[channel].attr.volume.right = vol;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalculateVolume(int channel /*$a2*/)
 // line 1257, offset 0x0007a360
	/* begin block 1 */
		// Start line: 1258
		// Start offset: 0x0007A360
		// Variables:
	// 		int volume; // $s0
	// 		VECTOR *pp; // $a3

		/* begin block 1.1 */
			// Start line: 1266
			// Start offset: 0x0007A3F4
			// Variables:
		// 		int distance; // $v1

			/* begin block 1.1.1 */
				// Start line: 1271
				// Start offset: 0x0007A3F4
				// Variables:
			// 		VECTOR ofse; // stack offset -24
			/* end block 1.1.1 */
			// End offset: 0x0007A3F4
			// End Line: 1274

			/* begin block 1.1.2 */
				// Start line: 1286
				// Start offset: 0x0007A4AC
				// Variables:
			// 		int fade; // $a0
			/* end block 1.1.2 */
			// End offset: 0x0007A504
			// End Line: 1291
		/* end block 1.1 */
		// End offset: 0x0007A520
		// End Line: 1293
	/* end block 1 */
	// End offset: 0x0007A534
	// End Line: 1295

	/* begin block 2 */
		// Start line: 2673
	/* end block 2 */
	// End Line: 2674

// [D] [T]
int CalculateVolume(int channel)
{
	int distance;
	int fade;
	int volume;

	VECTOR *srcPos;
	VECTOR *plPos;
	VECTOR ofse;

	volume = 10000 + channels[channel].srcvolume;

	if (NumPlayers > 1 && NoPlayerControl == 0) 
	{
		volume = (volume * 3 / 4);
	}

	srcPos = channels[channel].srcposition;

	if (srcPos != NULL)
	{
		plPos = &player[channels[channel].player].cameraPos;
		
		ofse.vx = srcPos->vx - plPos->vx;
		ofse.vy = srcPos->vy + plPos->vy;
		ofse.vz = srcPos->vz - plPos->vz;

		gte_ldlvl(&ofse);
		gte_sqr0();
		gte_stlvnl(&ofse);

		distance = SquareRoot0(ofse.vx + ofse.vy + ofse.vz);

		if (distance < 1024)
			distance = 1024;
		
		fade = 0xbd0000 / (distance + 2000);

		distance = MAX(0, MIN(4096, distance - 16000));
		
		if (distance != 0)
			fade *= (4096 - distance) / 4096;
		
		volume = (fade * volume) / 4096;
	}

	return volume - 10000;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AllocateReverb(long mode /*$s1*/, long depth /*$s0*/)
 // line 1303, offset 0x0007ab3c
	/* begin block 1 */
		// Start line: 1304
		// Start offset: 0x0007AB3C
		// Variables:
	// 		SpuReverbAttr r_attr; // stack offset -40
	/* end block 1 */
	// End offset: 0x0007AB94
	// End Line: 1319

	/* begin block 2 */
		// Start line: 3989
	/* end block 2 */
	// End Line: 3990

// [D] [T]
void AllocateReverb(long mode, long depth)
{
	SpuReverbAttr r_attr;

	if (SpuReserveReverbWorkArea(1) == 1)
	{
		r_attr.mode = mode | SPU_REV_MODE_CLEAR_WA;
		r_attr.mask = SPU_REV_MODE | SPU_REV_DEPTHL | SPU_REV_DEPTHR;
		r_attr.depth.left = depth;
		r_attr.depth.right = r_attr.depth.left;

		SpuSetReverbModeParam(&r_attr);
		SpuSetReverbDepth(&r_attr);
		SpuSetReverb(1);
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ FESound(int sample /*$s0*/)
 // line 1326, offset 0x0007a534
	/* begin block 1 */
		// Start line: 1327
		// Start offset: 0x0007A534
		// Variables:
	// 		long bpf; // $a1
	// 		long rate; // $a1
	// 		long pitch; // $s5
	// 		int channel; // $s6
	/* end block 1 */
	// End offset: 0x0007A6C0
	// End Line: 1358

	/* begin block 2 */
		// Start line: 2783
	/* end block 2 */
	// End Line: 2784

	/* begin block 3 */
		// Start line: 2815
	/* end block 3 */
	// End Line: 2816

// [D] [T]
int FESound(int sample)
{
	int channel;
	channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = NULL;
	channels[channel].srcvelocity = dummylong;
	channels[channel].srcvolume = 4096;

	return CompleteSoundSetup(channel, 1, sample, 2048, -1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ VsyncProc()
 // line 1371, offset 0x0007b178
	/* begin block 1 */
		// Start line: 5076
	/* end block 1 */
	// End Line: 5077

	/* begin block 2 */
		// Start line: 5199
	/* end block 2 */
	// End Line: 5200

	/* begin block 3 */
		// Start line: 5200
	/* end block 3 */
	// End Line: 5201

/* WARNING: Unknown calling convention yet parameter storage is locked */

int vblcounter = 0; // vblank counter

// [D] [T]
void VsyncProc(void)
{
	vblcounter++;

	if (Song_ID != -1)
		XM_Update();

	SoundHandler();
}





