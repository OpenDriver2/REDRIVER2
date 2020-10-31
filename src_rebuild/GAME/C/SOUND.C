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

long dummylong[4] = { 0, 0, 0, 0 };

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
	channels[channel].srcpitch = 0x1000;
	channels[channel].volumeScale = 0x1000;
	channels[channel].dopplerScale = 0x1000;
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

// [D]
void ResetSound(void)
{
	int channel;
	CHANNEL_DATA *chan;
	ulong *puVar3;

	stop_sound_handler = 1;
	sound_paused = 0;
	music_paused = 0;

	sound_attr.mvol.left = 0x3fff;
	sound_attr.mvol.right = 0x3fff;
	sound_attr.mask = 3;

	SpuSetCommonAttr(&sound_attr);
	chan = channels;

	channel = 0;
	do {
		memset(chan, 0, sizeof(CHANNEL_DATA));

		chan->attr.volmode.left = 0;
		chan->attr.volmode.right = 0;
		chan->attr.voice = SPU_KEYCH(channel);

		ClearChannelFields(channel);

		chan++;
		channel++;
	} while (channel < MAX_SFX_CHANNELS);

	channel = 0;
	do {
		SpuSetVoiceRR(channel, 6);
		SpuSetVoiceAR(channel, 35);
		channel++;
	} while (channel < MAX_SFX_CHANNELS);

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

void SetReverbState(int on)
{
	if (on == 0)
		SpuSetReverbVoice(0, 0xffffff);
	else
		SpuSetReverbVoice(1, 0xffffff);
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

// [D]
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

// [D]
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

// [D]
void SetMasterVolume(int vol)
{
	int puVar1;
	int puVar2;
	int puVar3;

	puVar2 = 10000 + vol;
	puVar3 = puVar2;

	if (puVar2 < 0)
		puVar3 = 0;

	puVar1 = puVar3 / 2;

	if (10000 < (int)puVar2) 
	{
		puVar3 = 10000;
		puVar1 = 5000;
	}

	master_volume = puVar3 + puVar1 + (puVar3 / 8) + (puVar3 / 128);
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

// [D]
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

// [D]
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

// [D]
int Start3DTrackingSound(int channel, int bank, int sample, VECTOR *position, long *velocity)
{
	int channel_00;

	if (channel < 0)
		channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = position;
	channels[channel].srcvelocity = velocity ? velocity : dummylong;
	channels[channel].srcpitch = 0x1000;
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

// [D]
int CompleteSoundSetup(int channel, int bank, int sample, int pitch, int proximity)
{
	int iVar3;
	uint uVar4;
	int rate;
	uint uVar6;
	ushort uVar7;

	rate = samples[bank][sample].samplerate * pitch;

	iVar3 = rate / 44100;
	uVar7 = iVar3;

	if (16383 < iVar3)
		uVar7 = 16383;

	uVar4 = (rate / 4096) / 50;

	if (uVar4 == 0) 
	{
		channel = -1;
	}
	else
	{
		uVar6 = samples[bank][sample].length;

		if (uVar4 == 0) 
			trap(7);

		if (gSoundMode == 1) 
			UpdateVolumeAttributesS(channel, proximity);
		else
			UpdateVolumeAttributesM(channel);


		stop_sound_handler = 1;

		channels[channel].attr.mask = 0x9f;

		channels[channel].attr.addr = samples[bank][sample].address;
		channels[channel].attr.pitch = uVar7;
		channels[channel].time = (uVar6 / uVar4) * 2 + 2;
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

// [D]
void SetChannelPitch(int channel, int pitch)
{
	long rate;

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return;

	if (sound_paused)
		return;

	if (channels[channel].time != 0 && 0x80 < pitch) 
	{
		channels[channel].srcpitch = pitch;

		rate = (channels[channel].samplerate * ((channels[channel].dopplerScale * pitch) / 4096)) / 44100;

		if (16383 < rate)
			rate = 16383;

		channels[channel].attr.mask = 0x10;
		channels[channel].attr.pitch = rate;

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

// [D]
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

		channels[channel].attr.mask = 0xf;
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

// D
void ComputeDoppler(CHANNEL_DATA *ch)
{
	int iVar1;
	long lVar2;
	long lVar3;
	int iVar4;
	VECTOR *srcPos;
	int iVar6;
	int iVar7;
	long *srcVel;
	PLAYER *pl;

	srcPos = ch->srcposition;

	if (srcPos == NULL) 
	{
		ch->dopplerScale = ONE;
	}
	else 
	{
		pl = &player[ch->player];

		iVar4 = srcPos->vx - pl->cameraPos.vx;
		iVar7 = srcPos->vy + pl->cameraPos.vy;
		iVar6 = srcPos->vz - pl->cameraPos.vz;
		lVar2 = jsqrt(iVar4 * iVar4 + iVar7 * iVar7 + iVar6 * iVar6);

		srcPos = ch->srcposition;
		srcVel = ch->srcvelocity;

		iVar6 = (srcPos->vx - pl->cameraPos.vx) + FIXEDH(srcVel[0] - pl->camera_vel[0]);
		iVar4 = (srcPos->vy + pl->cameraPos.vy) + FIXEDH(srcVel[1] - pl->camera_vel[1]);
		iVar1 = (srcPos->vz - pl->cameraPos.vz) + FIXEDH(srcVel[2] - pl->camera_vel[2]);

		lVar3 = jsqrt(iVar6 * iVar6 + iVar4 * iVar4 + iVar1 * iVar1);

		iVar1 = (lVar3 - lVar2) * -3 + ONE;

		ch->dopplerScale = iVar1;
		ch->cameradist = lVar2;

		if (iVar1 * 0x10000 < 0) 
			ch->dopplerScale = 0;
	}
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

// [D]
void SetChannelPosition3(int channel, VECTOR *position, long *velocity, int volume, int pitch, int proximity)
{
	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
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

		channels[channel].attr.mask = 0xf;

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

// [D]
void PauseXM(void)
{
	bool bVar1;
	int fade;

	if (music_paused == 0) 
	{
		music_pause_max = 0;
		fade = 96;

		do {
			bVar1 = fade < 0;
			fade += 96;
		} while (bVar1);

		if (Song_ID != -1)	// [A] bug fix
			XM_Pause(Song_ID);

		music_paused = 1;
	}
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

// [D] [A] please refactor
void PauseSFX(void)
{
	ushort uVar1;
	bool bVar2;
	short sVar3;
	short sVar4;
	short *local_s0_76;
	short *local_s0_252;
	ushort *local_s0_364;
	int iVar5;
	int iVar6;
	short *local_s2_68;

	if (sound_paused == 0) 
	{
		pause.max = 0;
		iVar5 = 0;
		
		local_s0_76 = (short *)pause.voll;
		local_s2_68 = (short *)pause.volr;

		do {
			SpuGetVoiceVolume(iVar5, local_s0_76, local_s2_68);

			if (*local_s2_68 < *local_s0_76)
				uVar1 = *local_s0_76;
			else
				uVar1 = *local_s2_68;

			if (pause.max < uVar1) 
			{
				pause.max = *local_s2_68;

				if (*local_s2_68 < *local_s0_76)
					pause.max = *local_s0_76;
			}

			local_s2_68++;
			local_s0_76++;
			iVar5++;

			pause.lev = gMasterVolume + 10000;
		} while (iVar5 < MAX_SFX_CHANNELS);

		iVar5 = 96;

		// fade?
		do {
			iVar6 = 0;

			local_s0_76 = (short *)pause.voll;
			local_s0_252 = (short *)pause.volr;

			do {

				sVar4 = *local_s0_76 - iVar5;

				if (*local_s0_76 - iVar5 < 0)
					sVar4 = 0;

				sVar3 = *local_s0_252 - iVar5;

				if (*local_s0_252 - iVar5 < 0) 
					sVar3 = 0;

				SpuSetVoiceVolume(iVar6, sVar4, sVar3);

				iVar6++;
				local_s0_252++;
				local_s0_76++;
			} while (iVar6 < MAX_SFX_CHANNELS);

			bVar2 = iVar5 < pause.max;
			iVar5 = iVar5 + 96;
		} while (bVar2);

		iVar5 = 0;
		local_s0_364 = pause.pitch;

		do {
			SpuGetVoicePitch(iVar5, local_s0_364);
			SpuSetVoicePitch(iVar5, 0);

			iVar5 = iVar5 + 1;
			local_s0_364++;
		} while (iVar5 < MAX_SFX_CHANNELS);

		sound_paused = 1;
	}
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

// [D]
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

// [D]
void UnPauseXM(void)
{
	if (Song_ID == -1)
		return;

	bool bVar1;
	int fade;

	if (music_paused != 0)
	{
		fade = 96;

		do {
			bVar1 = fade < music_pause_max;
			fade += 96;
		} while (bVar1);

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

// [D] [A] please refactor
void UnPauseSFX(void)
{
	bool bVar1;
	ushort local_v0_108;
	ushort uVar2;
	ushort *puVar2;
	ushort *puVar3;
	ushort uVar4;
	ushort *local_s0_44;
	int iVar5;
	int iVar6;

	if (sound_paused != 0) {
		local_s0_44 = pause.pitch;
		iVar6 = 0;

		do {
			puVar3 = local_s0_44;
			local_s0_44++;// = (__pauseinfo *)(local_s0_44->pitch + 1);
			iVar5 = iVar6 + 1;

			SpuSetVoicePitch(iVar6, *puVar3);

			iVar6 = iVar5;
		} while (iVar5 < 0x10);

		local_v0_108 = 10000 + gMasterVolume;

		if (pause.lev != 0 && pause.lev != local_v0_108) 
		{
			puVar2 = pause.voll;
			puVar3 = pause.volr;
			iVar6 = 0xf;
			do {
				if (pause.lev == 0)
					trap(7);

				*puVar2 = ((*puVar2 * local_v0_108) / pause.lev);

				if (pause.lev == 0)
					trap(7);

				*puVar3 = ((*puVar3 * local_v0_108) / pause.lev);

				iVar6--;
				puVar3++;
				puVar2++;
			} while (-1 < iVar6); // MAX_SFX_CHANNELS
		}

		iVar6 = 0x60;

		do {
			iVar5 = 0;

			puVar2 = pause.voll;
			puVar3 = pause.volr;

			do {
				uVar2 = *puVar2;
				if (iVar6 < *puVar2)
					uVar2 = iVar6;

				uVar4 = *puVar3;
				if (iVar6 < *puVar3)
					uVar4 = iVar6;

				SpuSetVoiceVolume(iVar5, uVar2, uVar4);

				iVar5++;
				puVar3++;
				puVar2++;
			} while (iVar5 < MAX_SFX_CHANNELS);

			bVar1 = iVar6 < pause.max;
			iVar6 = iVar6 + 0x60;
		} while (bVar1);

		sound_paused = 0;
	}
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

// [D]
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

//  [D]
void StopChannel(int channel)
{
	unsigned char lock;
	int vsync;

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return;

	lock = channels[channel].locked;
	vsync = VSync(-1);

	SpuSetKey(0, channels[channel].attr.voice);

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

// [D]
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

// [D]
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

// [D]
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

// [D]
void SoundHandler(void)
{
	ushort uVar1;
	CHANNEL_DATA *pCVar2;
	uint uVar3;
	ulong voice_bit;

	voice_bit = 0;
	if ((stop_sound_handler == 0) && (sound_paused == 0)) 
	{
		uVar3 = 0;
		pCVar2 = channels;

		do {
			uVar1 = pCVar2->time;

			if (pCVar2->loop == '\0' && (uVar1 != 0)) 
			{
				pCVar2->time = uVar1 - 1;

				if (uVar1 == 1) {
					voice_bit = voice_bit | 1 << (uVar3 & 0x1f);
				}
			}
			uVar3 = uVar3 + 1;
			pCVar2 = pCVar2 + 1;
		} while ((int)uVar3 < MAX_SFX_CHANNELS);

		if (voice_bit != 0) 
		{
			SpuSetKey(0, voice_bit);
		}
	}
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

// [D]
int LoadSoundBank(char *address, int length, int bank)
{
	SAMPLE_DATA *dest;
	int slength;
	int spuaddress;
	int num_samples;

	dest = samples[bank];

	num_samples = *(int *)address;
	memcpy(dest, address + 4, num_samples * sizeof(SAMPLE_DATA));

	slength = num_samples * sizeof(SAMPLE_DATA) + 4;
	spuaddress = bankaddr[bank];

	SpuSetTransferMode(0);
	SpuSetTransferStartAddr(spuaddress);
	SpuWrite((unsigned char*)address + slength, length - slength);
	SpuIsTransferCompleted(1);

	int ct = num_samples;
	if (0 < num_samples) 
	{
		do {
			ct--;
			dest->address += spuaddress;
			dest++;;
		} while (ct != 0);
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

// [D]
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

// [D]
int LoadSoundBankDynamic(char *address, int length, int dbank)
{
	static __LSBDinfo lsbTabs;

	int iVar1;
	int *piVar2;
	ulong uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int num_samples;

	num_samples = 0;

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
			default:
				goto switchD_00079c20_caseD_5;
		}
	}
	else 
	{
	switchD_00079c20_caseD_5:

		if (lsbTabs.append == 0) 
		{
			iVar5 = 6;
			piVar2 = lsbTabs.count + 6;
			lsbTabs.addr = bankaddr[1];

			do {
				*piVar2 = 0;
				iVar5--;
				piVar2--;
			} while (-1 < iVar5);

			lsbTabs.append = 1;
		}

		piVar2 = lsbTabs.count + dbank;
		num_samples = *(int *)address;

		memcpy(&samples[dbank][*piVar2], address + 4, num_samples * sizeof(SAMPLE_DATA));

		iVar6 = num_samples * sizeof(SAMPLE_DATA) + 4;
		length = length - iVar6;

		SpuSetTransferMode(SPU_TRANSFER_BY_DMA);

		SpuSetTransferStartAddr(lsbTabs.addr);
		SpuWrite((unsigned char*)address + iVar6, length);

		SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

		iVar6 = num_samples;

		if (0 < num_samples) 
		{
			do {
				
				iVar4 = *piVar2;
				uVar3 = samples[dbank][iVar4].address;
				
				samples[dbank][iVar4].address = lsbTabs.addr + uVar3;

				*piVar2 = iVar4 + 1;
				iVar6--;
			} while (iVar6 != 0);
		}
		lsbTabs.addr += length;
	}

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

// [D]
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

// [D]
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

// [D]
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

// [D]
void SetXMVolume(int volume)
{
	int vol;

	vol = 10000 + volume;
	if (vol < 0)
		vol = 0;

	if (vol > 10000)
		vol = 10000;

	gMusicVolume = volume;

	if (Song_ID == -1)
		return;

	XM_SetMasterVol(Song_ID, (char)((int)vol >> 7) + (char)((uint)vol >> 8));
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

// [D]
int GetFreeChannel(void)
{
	int channel;
	int it;
	ushort least;

	char status[SPU_CHANNEL_COUNT];

	least = 0;
	SpuGetAllKeysStatus(status);

	channel = 0;

	while (channels[channel].locked != 0 || status[channel] != 0)
	{
		channel++;

		if (channel > MAX_SFX_CHANNELS-1)
		{
			channel = 0;

			while (channels[channel].locked != 0 || status[channel] != 3) // ADSR status?
			{
				channel++;

				if (channel > MAX_SFX_CHANNELS - 1)
				{
					channel = -1;

					it = 0;

					while (it < MAX_SFX_CHANNELS)
					{
						if (channels[it].locked == 0 && channels[it].loop == 0)
						{
							if (channel == -1 || channels[it].time < least)
							{
								channel = it;
								least = channels[it].time;
							}
						}

						it++;
					}

					if (channel != -1) 
						StopChannel(channel);

					return channel;
				}
			}
			return channel;
		}
	}

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
	bool bVar1;
	int local_v0_204;
	long lVar2;
	int iVar3;
	short sVar4;
	int local_a2_160;
	int local_a2_184;
	int iVar5;
	int iVar6;
	int iVar7;
	VECTOR *pVVar8;
	VECTOR *pVVar9;
	long unaff_s6;
	int iVar10;

	local_a2_160 = CalculateVolume(channel);
	iVar5 = gSurround;
	iVar6 = channels[channel].player;
	pVVar8 = channels[channel].srcposition;
	pVVar9 = &player[iVar6].cameraPos;
	iVar10 = player[iVar6].snd_cam_ang;

	if (camera_change == 1 || (local_a2_160 = (0x2710 + local_a2_160), old_camera_change == 1)) 
		local_a2_160 = 0;

	local_a2_184 = local_a2_160;
	if (local_a2_160 < 0)
	{
		local_a2_184 = 0;
	}

	local_v0_204 = local_a2_184 / 2;

	if (10000 < local_a2_160) 
	{
		local_a2_184 = 10000;
		local_v0_204 = 5000;
	}

	iVar7 = ((local_v0_204 + local_a2_184 + local_a2_184 / 8 + local_a2_184 / 128) * master_volume) / 16384;
	sVar4 = iVar7;
	channels[channel].attr.volume.left = sVar4;

	if (gSurround != 0) {
		sVar4 = -sVar4;
	}

	channels[channel].attr.volume.right = sVar4;

	if (iVar7 == 0)
		return;

	if (pVVar8 == NULL)
		return;

	iVar5 = player[iVar6].cameraPos.vz;
	if ((pVVar8->vz == iVar5) && (pVVar9->vx == pVVar8->vx))
		return;

	if (player[iVar6].cameraView == 2) 
	{
		if (channel == player[iVar6].skidding.chan)
			return;

		if (channel == player[iVar6].wheelnoise.chan)
			return;

		if (iVar6 == 0)
		{
			if (channel == 0)
				return;

			iVar3 = 1;

			if (channel == player[iVar6].cameraView) 
				return;
		}
		else 
		{
			if (iVar6 != 1) 
				goto LAB_0007a128;
			if (channel == 3) 
				return;
			iVar3 = 4;
			if (channel == 5)
				return;

		}
		if (channel == iVar3)
			return;
	}
LAB_0007a128:
	lVar2 = ratan2(pVVar8->vz - iVar5, pVVar9->vx - pVVar8->vx);

	iVar3 = -lVar2 + 0x1c00;
	iVar5 = iVar3;

	iVar10 = (iVar3 + (iVar5 / 4096) * -4096) - (iVar10 + -4096);
	iVar5 = iVar10;

	iVar10 = 0x800 - (iVar10 + (iVar5 / 4096) * -4096);

	iVar5 = iVar10;

	if (iVar10 < 0) 
		iVar5 = -iVar10;

	if ((0x3ff < iVar5) && (bVar1 = iVar10 < 1, iVar10 = 2048 - iVar5, bVar1)) {
		iVar10 = -iVar10;
	}

	if ((proximity != 0) &&
		(iVar5 = player[iVar6].cameraPos.vz - pVVar8->vz, iVar6 = pVVar9->vx - pVVar8->vx,
		unaff_s6 = jsqrt(iVar5 * iVar5 + iVar6 * iVar6), 11999 < unaff_s6))
	{
		proximity = 0;
	}

	if (iVar10 < 1) 
	{
		if (iVar10 < 0) 
		{
			iVar5 = ((iVar7 * 9) / 10) * -iVar10;

			//if (iVar5 < 0) 
			//	iVar5 = iVar5 + 0x3ff;

			iVar5 = iVar5 / 1024;

			if (proximity != 0)
				iVar5 = (iVar5 * unaff_s6) / 12000;

			sVar4 = (iVar7 - iVar5);

			if (iVar7 - iVar5 < 0)
				sVar4 = 0;
	
			if (gSurround != 0)
				sVar4 = -sVar4;

			channels[channel].attr.volume.right = sVar4;
		}
	}
	else
	{
		iVar10 = ((iVar7 * 9) / 10) * iVar10;

		//if (iVar10 < 0)
		//	iVar10 = iVar10 + 0x3ff;

		iVar10 = iVar10 / 1024;

		if (proximity != 0)
			iVar10 = (iVar10 * unaff_s6) / 12000;

		sVar4 = (iVar7 - iVar10);

		if (iVar7 - iVar10 < 0)
			sVar4 = 0;

		channels[channel].attr.volume.left = sVar4;
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

// [D]
void UpdateVolumeAttributesM(int channel)
{
	int iVar1;
	int puVar2;
	int puVar3;
	int puVar4;
	short sVar5;

	iVar1 = CalculateVolume(channel);

	if ((camera_change == 1) || (puVar3 = 10000 + iVar1, old_camera_change == 1))
		puVar3 = 0;

	puVar4 = puVar3;

	if ((int)puVar3 < 0)
		puVar4 = 0;

	puVar2 = puVar4 / 2;

	if (10000 < puVar3) 
	{
		puVar4 = 10000;
		puVar2 = 5000;
	}

	sVar5 = ((puVar4 + puVar2 + (puVar4 / 8) + (puVar4 / 128)) * master_volume) / 16384;

	channels[channel].attr.volume.left = sVar5;
	channels[channel].attr.volume.right = sVar5;
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

// [D]
int CalculateVolume(int channel)
{
	int iVar1;
	int iVar2;
	int iVar5;

	VECTOR *pp;
	VECTOR ofse = {0};

	int volume;

	volume = 10000 + channels[channel].srcvolume;

	if (1 < NumPlayers && NoPlayerControl == 0) 
	{
		iVar1 = volume * 3;
		volume = (iVar1 / 4);
	}

	pp = channels[channel].srcposition;

	if (pp != NULL) // [A]
	{
		iVar1 = channels[channel].player;
		
		ofse.vx = pp->vx - player[iVar1].cameraPos.vx;
		ofse.vy = pp->vy + player[iVar1].cameraPos.vy;
		ofse.vz = pp->vz - player[iVar1].cameraPos.vz;

		gte_ldlvl(&ofse);

		gte_sqr0();

		gte_stlvnl(&ofse);

		iVar1 = SquareRoot0(ofse.vx + ofse.vy + ofse.vz);

		iVar2 = iVar1-16000;

		if (iVar1 < 1024)
		{
			iVar1 = 1024;
			iVar2 = -0x3a80;
		}

		if (iVar2 < 0)
			iVar2 = 0;
		else if (0x1000 < iVar2) 
			iVar2 = 4069;

		iVar5 = 0xbd0000 / (iVar1 + 2000);

		if (iVar2 != 0)
			iVar5 = iVar5 * (4096 - iVar2) / 4096;

		iVar5 *= volume;
		volume = iVar5 / 4096;
	}

	return volume-10000;
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

// [D]
void AllocateReverb(long mode, long depth)
{
	SpuReverbAttr r_attr;

	if (SpuReserveReverbWorkArea(1) == 1)
	{
		r_attr.mode = mode | 0x100;
		r_attr.mask = 7;
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

// [D]
int FESound(int sample)
{
	int iVar2;
	uint uVar3;
	int channel;
	int iVar4;
	uint uVar5;
	ushort uVar6;

	channel = GetFreeChannel();

	iVar4 = samples[1][sample].samplerate * 2048;

	iVar2 = iVar4 / 44100;
	uVar6 = iVar2;

	if (0x3fff < iVar2)
	{
		uVar6 = 0x3fff;
	}

	uVar3 = (iVar4 / 4096) / 50;

	if (uVar3 == 0)
	{
		channel = -1;
	}
	else {
		uVar5 = samples[1][sample].length;

		if (uVar3 == 0)
			trap(7);

		channels[channel].srcvolume = 0;
		channels[channel].srcposition = (VECTOR *)0x0;
		UpdateVolumeAttributesM(channel);

		stop_sound_handler = 1;
		channels[channel].attr.mask = 0x9f;
		channels[channel].attr.addr = samples[1][sample].address;
		channels[channel].attr.pitch = uVar6;
		channels[channel].loop = samples[1][sample].loop;
		channels[channel].time = (uVar5 / uVar3) * 2 + 2;
		channels[channel].samplerate = samples[1][sample].samplerate;

		SpuSetVoiceAttr(&channels[channel].attr);
		SpuSetKey(1, channels[channel].attr.voice);

		stop_sound_handler = 0;
	}

	return channel;
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

// [D]
void VsyncProc(void)
{
	vblcounter = vblcounter + 1;

	if (Song_ID != -1)
		XM_Update();

	SoundHandler();
}





