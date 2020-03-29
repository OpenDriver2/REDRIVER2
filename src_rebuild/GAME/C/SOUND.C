#include "THISDUST.H"
#include "SOUND.H"

#include "LIBSPU.H"
#include "LIBETC.H"

#include <string.h>

long dummylong[3] = { 0, 0, 0 };

void* bankaddr = NULL;
char banks[24] = { 0 };
long banksize[2] = { 88064, 412672 };

SAMPLE_DATA samples[35][7];
int VABID = -1;

unsigned long channel_lookup[16]; // offset 0xDD3D8
struct CHANNEL_DATA channels[16]; // offset 0xDE480

int gMasterVolume = 0;
int gMusicVolume = 0;

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





void InitSound(void)
{
	UNIMPLEMENTED();

	/*
	int iVar1;
	ulong *puVar2;
	int iVar3;
	uint uVar4;
	long *plVar5;
	long *plVar6;

	SpuInit();
	SpuInitMalloc(7, banks);
	SpuSetMute(1);
	AllocateReverb(3, 0x4000);
	plVar6 = &bankaddr;
	plVar5 = &banksize;
	iVar3 = 1;
	do {
		iVar1 = SpuMalloc(*plVar5);
		*plVar6 = iVar1;
		if (iVar1 == -1) {
			exit(-1);
		}
		plVar6 = plVar6 + 1;
		iVar3 = iVar3 + -1;
		plVar5 = plVar5 + 1;
	} while (-1 < iVar3);
	uVar4 = 0;
	puVar2 = &channel_lookup;
	do {
		*puVar2 = 1 << (uVar4 & 0x1f);
		uVar4 = uVar4 + 1;
		puVar2 = puVar2 + 1;
	} while ((int)uVar4 < 0x10);
	ResetSound();
	XM_OnceOffInit(1);
	SetMasterVolume(gMasterVolume);
	VSyncCallback(VsyncProc);
	SpuSetMute(0);
	return;
	*/
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

void ClearChannelFields(int channel)
{
	UNIMPLEMENTED();

	channels[channel].loop = '\0';
	channels[channel].locked = '\0';
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
	channels[channel].srcvelocity = (long *)0xa1a5c;
	channels[channel].player = 0;
	return;
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

void ResetSound(void)
{
	UNIMPLEMENTED();
	/*
	ulong uVar1;
	int iVar2;
	int channel;
	CHANNEL_DATA *__s;
	ulong *puVar3;

	stop_sound_handler = 1;
	sound_paused = 0;
	music_paused = 0;
	sound_attr.mvol.left = 0x3fff;
	sound_attr.mvol.right = 0x3fff;
	sound_attr.mask = 3;
	SpuSetCommonAttr(&sound_attr);
	puVar3 = &channel_lookup;
	__s = &channels;
	channel = 0;
	do {
		memset(__s, 0, 0x78);
		uVar1 = *puVar3;
		puVar3 = puVar3 + 1;
		iVar2 = channel + 1;
		(__s->attr).volmode.left = 0;
		(__s->attr).volmode.right = 0;
		(__s->attr).voice = uVar1;
		ClearChannelFields(channel);
		__s = __s + 1;
		channel = iVar2;
	} while (iVar2 < 0x10);
	channel = 0;
	do {
		SpuSetVoiceRR(channel, 6);
		SpuSetVoiceAR(channel, 0x23);
		channel = channel + 1;
	} while (channel < 0x10);
	stop_sound_handler = 0;
	return;
	*/
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
	if (on == 0) {
		SpuSetReverbVoice(0, 0xffffff);
	}
	else {
		SpuSetReverbVoice(1, 0xffffff);
	}
	return;
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

void SetReverbInGameState(int on)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;

	uVar1 = 0xffff;
	gSpeechQueue.reverb = (char)on;
	if ((on != 0) && (gSpeechQueue.is_playing != '\0')) {
		uVar1 = ~(1 << ((uint)(byte)gSpeechQueue.chan & 0x1f)) & 0xffff;
	}
	SpuSetReverbVoice(on, uVar1);
	return;
	*/
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

int SetReverbChannelState(int ch, int on)
{
	UNIMPLEMENTED();
	return 0;

	/*
	uint uVar1;
	uint uVar2;

	uVar2 = 1 << (ch & 0x1fU);
	uVar1 = SpuGetReverbVoice();
	SpuSetReverbVoice(on, uVar2);
	return (uint)((uVar1 & uVar2) != 0);*/
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

void SetMasterVolume(int vol)
{
	UNIMPLEMENTED();
	/*
	undefined *puVar1;
	undefined *puVar2;
	undefined *puVar3;

	puVar2 = &DAT_00002710 + vol;
	puVar3 = puVar2;
	if ((int)puVar2 < 0) {
		puVar3 = (undefined *)0x0;
	}
	puVar1 = (undefined *)((int)puVar3 >> 1);
	if (10000 < (int)puVar2) {
		puVar3 = &DAT_00002710;
		puVar1 = &DAT_00001388;
	}
	master_volume = (int)puVar3 + (int)puVar1 + ((int)puVar3 >> 3) + ((int)puVar3 >> 7);
	gMasterVolume = vol;
	return;
	*/
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

char SetPlayerOwnsChannel(int chan, char player)
{
	UNIMPLEMENTED();
	return 0;
	/*
	char cVar1;

	cVar1 = (&channels)[chan].player;
	(&channels)[chan].player = player;
	return cVar1;
	*/
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

int StartSound(int channel, int bank, int sample, int volume, int pitch)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	if (channel < 0) {
		channel = GetFreeChannel();
	}
	if ((uint)channel < 0x10) {
		(&channels)[channel].srcposition = (VECTOR *)0x0;
		(&channels)[channel].srcvolume = volume;
		iVar1 = CompleteSoundSetup(channel, bank, sample, pitch, 0);
	}
	else {
		iVar1 = -1;
	}
	return iVar1;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ Start3DTrackingSound(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s3*/, struct VECTOR *position /*$s2*/, long *velocity /*stack 16*/)
 // line 342, offset 0x0007a994
	/* begin block 1 */
		// Start line: 684
	/* end block 1 */
	// End Line: 685

int Start3DTrackingSound(int channel, int bank, int sample, VECTOR *position, long *velocity)
{
	UNIMPLEMENTED();
	return 0;

	/*
	int channel_00;

	if (channel < 0) {
		channel = GetFreeChannel();
	}
	if ((uint)channel < 0x10) {
		(&channels)[channel].srcposition = position;
		(&channels)[channel].srcvelocity = velocity;
		(&channels)[channel].srcpitch = 0x1000;
		(&channels)[channel].srcvolume = 0;
		channel_00 = CompleteSoundSetup(channel, bank, sample, 0x1000, 0);
		ComputeDoppler(&channels + channel_00);
		SetChannelPitch(channel_00, 0x1000);
	}
	else {
		channel_00 = -1;
	}
	return channel_00;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ Start3DSoundVolPitch(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s4*/, int x /*$s3*/, int y /*stack 16*/, int z /*stack 20*/, int volume /*stack 24*/, int pitch /*stack 28*/)
 // line 357, offset 0x0007a894
	/* begin block 1 */
		// Start line: 2034
	/* end block 1 */
	// End Line: 2035

int Start3DSoundVolPitch(int channel, int bank, int sample, int x, int y, int z, int volume, int pitch)
{
	UNIMPLEMENTED();

	int channel_00;

	if (channel < 0) {
		channel = GetFreeChannel();
	}
	if ((uint)channel < 0x10) {
		channels[channel].srcposition = &channels[channel].position;
		channels[channel].position.vx = x;
		channels[channel].position.vy = y;
		channels[channel].position.vz = z;
		channels[channel].srcvolume = volume;
		channels[channel].srcpitch = (ushort)pitch;
		channel_00 = CompleteSoundSetup(channel, bank, sample, pitch, 0);
		ComputeDoppler(&channels[channel_00]);
		SetChannelPitch(channel_00, pitch);
	}
	else {
		channel_00 = -1;
	}
	return channel_00;
	
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

int CompleteSoundSetup(int channel, int bank, int sample, int pitch, int proximity)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	uchar uVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	uint uVar6;
	ushort uVar7;

	iVar5 = bank * 0x23 + sample;
	pitch = samples[iVar5].samplerate * pitch;
	iVar3 = pitch / 0xac44;
	uVar7 = (ushort)iVar3;
	if (0x3fff < iVar3) {
		uVar7 = 0x3fff;
	}
	uVar4 = (pitch >> 0xc) / 0x32;
	if (uVar4 == 0) {
		channel = -1;
	}
	else {
		uVar6 = samples[iVar5].length;
		if (uVar4 == 0) {
			trap(7);
		}
		if (gSoundMode == 1) {
			UpdateVolumeAttributesS(channel, proximity);
		}
		else {
			UpdateVolumeAttributesM(channel);
		}
		stop_sound_handler = 1;
		(&channels)[channel].attr.mask = 0x9f;
		sample = bank * 0x23 + sample;
		(&channels)[channel].attr.addr = samples[sample].address;
		uVar2 = *(uchar *)&samples[sample].loop;
		(&channels)[channel].attr.pitch = uVar7;
		(&channels)[channel].time = (short)(uVar6 / uVar4) * 2 + 2;
		(&channels)[channel].loop = uVar2;
		bVar1 = sound_paused != 0;
		(&channels)[channel].samplerate = samples[sample].samplerate;
		if (bVar1) {
			(&channels)[channel].attr.volume.left = 0;
			(&channels)[channel].attr.volume.right = 0;
		}
		SpuSetVoiceAttr(&channels + channel);
		SpuSetKey(1, (&channels)[channel].attr.voice);
		stop_sound_handler = 0;
	}
	return channel;
	*/
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

void SetChannelPitch(int channel, int pitch)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	ushort uVar2;

	if (((uint)channel < 0x10) && (sound_paused == 0)) {
		if (((&channels)[channel].time != 0) && (0x80 < pitch)) {
			uVar2 = (&channels)[channel].dopplerScale;
			(&channels)[channel].srcpitch = (ushort)pitch;
			iVar1 = ((&channels)[channel].samplerate * ((int)((uint)uVar2 * pitch) >> 0xc)) / 0xac44;
			uVar2 = (ushort)iVar1;
			if (0x3fff < iVar1) {
				uVar2 = 0x3fff;
			}
			(&channels)[channel].attr.mask = 0x10;
			(&channels)[channel].attr.pitch = uVar2;
			SpuSetVoiceAttr(&channels + channel);
		}
	}
	return;
	*/
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

void SetChannelVolume(int channel, int volume, int proximity)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = gSoundMode;
	if ((((uint)channel < 0x10) && (sound_paused == 0)) && ((&channels)[channel].time != 0)) {
		(&channels)[channel].srcvolume = volume;
		if (iVar1 == 1) {
			UpdateVolumeAttributesS(channel, proximity);
		}
		else {
			UpdateVolumeAttributesM(channel);
		}
		(&channels)[channel].attr.mask = 0xf;
		SpuSetVoiceAttr(&channels + channel);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ComputeDoppler(struct CHANNEL_DATA *ch /*$s1*/)
 // line 501, offset 0x000795c4
	/* begin block 1 */
		// Start line: 502
		// Start offset: 0x000795C4
		// Variables:
	// 		int dist; // $s0
	// 		int seperationrate; // $v0
	// 		struct _PLAYER *pl; // $s0
	/* end block 1 */
	// End offset: 0x00079720
	// End Line: 527

	/* begin block 2 */
		// Start line: 1078
	/* end block 2 */
	// End Line: 1079

void ComputeDoppler(CHANNEL_DATA *ch)
{
	UNIMPLEMENTED();

	/*
	int iVar1;
	long lVar2;
	long lVar3;
	int iVar4;
	VECTOR *pVVar5;
	int iVar6;
	int iVar7;
	int *piVar8;

	pVVar5 = ch->srcposition;
	if (pVVar5 == (VECTOR *)0x0) {
		ch->dopplerScale = 0x1000;
	}
	else {
		iVar1 = (int)ch->player;
		iVar4 = pVVar5->vx - (&player)[iVar1].cameraPos.vx;
		iVar7 = pVVar5->vy + (&player)[iVar1].cameraPos.vy;
		iVar6 = pVVar5->vz - (&player)[iVar1].cameraPos.vz;
		lVar2 = jsqrt(iVar4 * iVar4 + iVar7 * iVar7 + iVar6 * iVar6);
		pVVar5 = ch->srcposition;
		piVar8 = ch->srcvelocity;
		iVar6 = (pVVar5->vx - (&player)[iVar1].cameraPos.vx) +
			(*piVar8 - (&player)[iVar1].camera_vel[0] >> 0xc);
		iVar4 = pVVar5->vy + (&player)[iVar1].cameraPos.vy +
			(piVar8[1] - (&player)[iVar1].camera_vel[1] >> 0xc);
		iVar1 = (pVVar5->vz - (&player)[iVar1].cameraPos.vz) +
			(piVar8[2] - (&player)[iVar1].camera_vel[2] >> 0xc);
		lVar3 = jsqrt(iVar6 * iVar6 + iVar4 * iVar4 + iVar1 * iVar1);
		iVar1 = (lVar3 - lVar2) * -3 + 0x1000;
		ch->dopplerScale = (ushort)iVar1;
		ch->cameradist = lVar2;
		if (iVar1 * 0x10000 < 0) {
			ch->dopplerScale = 0;
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetChannelPosition3(int channel /*$s1*/, struct VECTOR *position /*$a0*/, long *velocity /*$t0*/, int volume /*$t2*/, int pitch /*stack 16*/, int proximity /*stack 20*/)
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

void SetChannelPosition3(int channel, VECTOR *position, long *velocity, int volume, int pitch, int proximity)
{
	UNIMPLEMENTED();

	/*
	int iVar1;

	if ((((camera_change != '\x01') && (old_camera_change != '\x01')) && ((uint)channel < 0x10)) &&
		(sound_paused == 0)) {
		if (velocity == (long *)0x0) {
			velocity = dummylong;
		}
		(&channels)[channel].srcposition = position;
		iVar1 = gSoundMode;
		(&channels)[channel].srcvelocity = velocity;
		(&channels)[channel].srcvolume = volume;
		if (iVar1 == 1) {
			UpdateVolumeAttributesS(channel, proximity);
		}
		else {
			UpdateVolumeAttributesM(channel);
		}
		(&channels)[channel].attr.mask = 0xf;
		SpuSetVoiceAttr(&channels + channel);
		ComputeDoppler(&channels + channel);
		SetChannelPitch(channel, pitch);
	}
	return;
	*/
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

void PauseXM(void)
{
	UNIMPLEMENTED();

	/*
	bool bVar1;
	int iVar2;

	if (music_paused == 0) {
		musps.max = 0;
		iVar2 = 0x60;
		do {
			bVar1 = iVar2 < 0;
			iVar2 = iVar2 + 0x60;
		} while (bVar1);
		XM_Pause(Song_ID);
		music_paused = 1;
	}
	return;
	*/
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

void PauseSFX(void)
{
	UNIMPLEMENTED();

	/*
	ushort uVar1;
	bool bVar2;
	short sVar3;
	short sVar4;
	ushort *puVar5;
	__pauseinfo *p_Var6;
	int iVar7;
	int iVar8;

	if (sound_paused == 0) {
		pause.max = 0;
		iVar7 = 0;
		iVar8 = 0xdd488;
		puVar5 = pause.voll;
		do {
			SpuGetVoiceVolume(iVar7, puVar5, iVar8);
			if (puVar5[0x10] < *puVar5) {
				uVar1 = *puVar5;
			}
			else {
				uVar1 = puVar5[0x10];
			}
			if (pause.max < uVar1) {
				pause.max = puVar5[0x10];
				if (puVar5[0x10] < *puVar5) {
					pause.max = *puVar5;
				}
			}
			iVar8 = iVar8 + 2;
			puVar5 = puVar5 + 1;
			iVar7 = iVar7 + 1;
			pause.lev = (short)gMasterVolume + 10000;
		} while (iVar7 < 0x10);
		iVar7 = 0x60;
		do {
			iVar8 = 0;
			puVar5 = pause.volr;
			do {
				sVar4 = (short)((uint)puVar5[-0x10] - iVar7);
				if ((int)((uint)puVar5[-0x10] - iVar7) < 0) {
					sVar4 = 0;
				}
				sVar3 = (short)((uint)*puVar5 - iVar7);
				if ((int)((uint)*puVar5 - iVar7) < 0) {
					sVar3 = 0;
				}
				SpuSetVoiceVolume(iVar8, (int)sVar4, (int)sVar3);
				iVar8 = iVar8 + 1;
				puVar5 = puVar5 + 1;
			} while (iVar8 < 0x10);
			bVar2 = iVar7 < (int)(uint)pause.max;
			iVar7 = iVar7 + 0x60;
		} while (bVar2);
		iVar7 = 0;
		p_Var6 = &pause;
		do {
			SpuGetVoicePitch(iVar7, p_Var6);
			SpuSetVoicePitch(iVar7, 0);
			iVar7 = iVar7 + 1;
			p_Var6 = (__pauseinfo *)(p_Var6->pitch + 1);
		} while (iVar7 < 0x10);
		sound_paused = 1;
	}
	return;
	*/
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

void PauseSound(void)
{
	UNIMPLEMENTED();
	/*
	SetReverbInGameState(0);
	PauseXM();
	PauseSFX();
	PauseXA();
	return;*/
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

void UnPauseXM(void)
{
	UNIMPLEMENTED();

	/*
	bool bVar1;
	int iVar2;

	if (music_paused != 0) {
		iVar2 = 0x60;
		do {
			bVar1 = iVar2 < (int)(uint)musps.max;
			iVar2 = iVar2 + 0x60;
		} while (bVar1);
		XM_Restart(Song_ID);
		music_paused = 0;
	}
	return;
	*/
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

void UnPauseSFX(void)
{
	UNIMPLEMENTED();

	/*
	bool bVar1;
	undefined *puVar2;
	ushort uVar3;
	ushort *puVar4;
	ushort uVar5;
	__pauseinfo *p_Var6;
	int iVar7;
	int iVar8;

	if (sound_paused != 0) {
		p_Var6 = &pause;
		iVar8 = 0;
		do {
			puVar4 = p_Var6->pitch;
			p_Var6 = (__pauseinfo *)(p_Var6->pitch + 1);
			iVar7 = iVar8 + 1;
			SpuSetVoicePitch(iVar8, (uint)*puVar4);
			iVar8 = iVar7;
		} while (iVar7 < 0x10);
		if ((pause.lev != 0) &&
			(puVar2 = &DAT_00002710 + gMasterVolume, (undefined *)(uint)pause.lev != puVar2)) {
			puVar4 = pause.volr;
			iVar8 = 0xf;
			do {
				if (pause.lev == 0) {
					trap(7);
				}
				puVar4[-0x10] = (ushort)((int)((uint)puVar4[-0x10] * (int)puVar2) / (int)(uint)pause.lev);
				if (pause.lev == 0) {
					trap(7);
				}
				*puVar4 = (ushort)((int)((uint)*puVar4 * (int)puVar2) / (int)(uint)pause.lev);
				iVar8 = iVar8 + -1;
				puVar4 = puVar4 + 1;
			} while (-1 < iVar8);
		}
		iVar8 = 0x60;
		do {
			iVar7 = 0;
			puVar4 = pause.volr;
			do {
				uVar3 = puVar4[-0x10];
				if (iVar8 < (int)(uint)puVar4[-0x10]) {
					uVar3 = (ushort)iVar8;
				}
				uVar5 = *puVar4;
				if (iVar8 < (int)(uint)*puVar4) {
					uVar5 = (ushort)iVar8;
				}
				SpuSetVoiceVolume(iVar7, (int)(short)uVar3, (int)(short)uVar5);
				iVar7 = iVar7 + 1;
				puVar4 = puVar4 + 1;
			} while (iVar7 < 0x10);
			bVar1 = iVar8 < (int)(uint)pause.max;
			iVar8 = iVar8 + 0x60;
		} while (bVar1);
		sound_paused = 0;
	}
	return;
	*/
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

void UnPauseSound(void)
{
	UNIMPLEMENTED();
	/*
	UnPauseXM();
	UnPauseSFX();
	ResumeXA();
	return;
	*/
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

void StopChannel(int channel)
{
	UNIMPLEMENTED();

	/*
	uchar uVar1;
	int iVar2;
	uint uVar3;
	int iVar4;

	if ((uint)channel < 0x10) {
		uVar1 = (&channels)[channel].locked;
		iVar2 = VSync(0xffffffff);
		SpuSetKey(0, (&channels)[channel].attr.voice);
		do {
			uVar3 = SpuGetKeyStatus((&channels)[channel].attr.voice);
			if ((uVar3 & 0xff) == 0) break;
			iVar4 = VSync(0xffffffff);
		} while (iVar4 - iVar2 < 8);
		ClearChannelFields(channel);
		(&channels)[channel].locked = uVar1;
	}
	return;
	*/
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

void StopAllChannels(void)
{
	int channel;

	channel = 0;
	do {
		StopChannel(channel);
		VSync(0);
		channel = channel + 1;
	} while (channel < 0x10);
	return;
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

void LockChannel(int channel)
{
	if ((uint)channel < 0x10) {
		channels[channel].locked = 1;
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnlockChannel(int c /*$a0*/)
 // line 811, offset 0x0007ae64
	/* begin block 1 */
		// Start line: 4035
	/* end block 1 */
	// End Line: 4036

void UnlockChannel(int c)
{
	if ((uint)c < 0x10) {
		channels[c].locked = 0;
	}
	return;
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

void SoundHandler(void)
{
	UNIMPLEMENTED();

	/*
	ushort uVar1;
	CHANNEL_DATA *pCVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = 0;
	if ((stop_sound_handler == 0) && (sound_paused == 0)) {
		uVar3 = 0;
		pCVar2 = &channels;
		do {
			if ((pCVar2->loop == '\0') && (uVar1 = pCVar2->time, uVar1 != 0)) {
				pCVar2->time = uVar1 - 1;
				if (uVar1 == 1) {
					uVar4 = uVar4 | 1 << (uVar3 & 0x1f);
				}
			}
			uVar3 = uVar3 + 1;
			pCVar2 = pCVar2 + 1;
		} while ((int)uVar3 < 0x10);
		if (uVar4 != 0) {
			SpuSetKey(0);
		}
	}
	return;
	*/
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

int LoadSoundBank(char *address, int length, int bank)
{
	UNIMPLEMENTED();
	return 0;

	/*
	SAMPLE_DATA *__dest;
	int iVar1;
	int iVar2;
	int iVar3;

	__dest = samples[bank * 0x23];
	iVar3 = *(int *)address;
	memcpy(__dest, address + 4, iVar3 * 0x10);
	iVar1 = iVar3 * 0x10 + 4;
	iVar2 = bankaddr[bank];
	SpuSetTransferMode(0);
	SpuSetTransferStartAddr(iVar2);
	SpuWrite(address + iVar1, length - iVar1);
	SpuIsTransferCompleted(1);
	iVar1 = iVar3;
	if (0 < iVar3) {
		do {
			iVar1 = iVar1 + -1;
			__dest->address = __dest->address + iVar2;
			__dest = __dest + 1;
		} while (iVar1 != 0);
	}
	return iVar3;
	*/
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

void UpdateXMSamples(int num_samps)
{
	UNIMPLEMENTED();
	/*
	ulong *puVar1;
	int slot;
	int iVar2;
	SAMPLE_DATA *pSVar3;

	if (0 < num_samps) {
		pSVar3 = samples;
		slot = 0;
		do {
			puVar1 = &pSVar3->address;
			pSVar3 = pSVar3 + 1;
			iVar2 = slot + 1;
			XM_SetVAGAddress(VABID, slot, *puVar1);
			slot = iVar2;
		} while (iVar2 < num_samps);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadSoundBankDynamic(char *address /*$s2*/, int length /*$s6*/, int dbank /*$a2*/)
 // line 904, offset 0x00079bcc
	/* begin block 1 */
		// Start line: 905
		// Start offset: 0x00079BCC
		// Variables:
	// 		static struct __LSBDinfo tabs; // offset 0x0
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

int LoadSoundBankDynamic(char *address, int length, int dbank)
{
	UNIMPLEMENTED();
	return 0;

	/*
	int iVar1;
	undefined4 *puVar2;
	ulong uVar3;
	int iVar4;
	int iVar5;
	long lVar6;
	int *piVar7;

	if (address == (char *)0x0) {
		switch (length) {
		case 0:
			if (dbank == 0) {
				tabs_93[16] = 0;
			}
			lVar6 = 0;
			break;
		case 1:
			tabs_93[1] = tabs_93[0];
			lVar6 = tabs_93[0];
			break;
		case 2:
			tabs_93[0] = tabs_93[1];
			lVar6 = tabs_93[1];
			break;
		case 3:
			tabs_93[dbank + 9] = tabs_93[dbank + 2];
			lVar6 = tabs_93[dbank + 2];
			break;
		case 4:
			tabs_93[dbank + 2] = tabs_93[dbank + 9];
			lVar6 = tabs_93[dbank + 9];
			break;
		default:
			goto switchD_00079c20_caseD_5;
		}
	}
	else {
	switchD_00079c20_caseD_5:
		if (tabs_93[16] == 0) {
			iVar5 = 6;
			puVar2 = tabs_93 + 8;
			tabs_93[0] = LONG_000ab14c;
			do {
				*puVar2 = 0;
				iVar5 = iVar5 + -1;
				puVar2 = puVar2 + -1;
			} while (-1 < iVar5);
			tabs_93[16] = 1;
		}
		piVar7 = tabs_93 + dbank + 2;
		lVar6 = *(long *)address;
		memcpy(samples + *piVar7 + dbank * 0x23, address + 4, lVar6 * 0x10);
		iVar5 = lVar6 * 0x10 + 4;
		length = length - iVar5;
		SpuSetTransferMode(0);
		SpuSetTransferStartAddr(tabs_93[0]);
		SpuWrite(address + iVar5, length);
		SpuIsTransferCompleted(1);
		iVar5 = lVar6;
		if (0 < lVar6) {
			do {
				iVar1 = tabs_93[0];
				iVar5 = iVar5 + -1;
				iVar4 = *piVar7;
				uVar3 = samples[dbank * 0x23 + iVar4].address;
				*piVar7 = iVar4 + 1;
				samples[dbank * 0x23 + iVar4].address = uVar3 + iVar1;
			} while (iVar5 != 0);
		}
		tabs_93[0] = tabs_93[0] + length;
	}
	return lVar6;
	*/
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

void FreeXM(void)
{
	UNIMPLEMENTED();

	/*
	if (Song_ID != -1) {
		XM_Exit();
		XM_FreeAllSongIDs();
		XM_CloseVAB2(VABID);
		Song_ID = -1;
		VABID = -1;
	}
	return;
	*/
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

void StartXM(int reverb)
{
	UNIMPLEMENTED();

	/*
	uint uVar1;

	uVar1 = 0x10;
	XM_PlayStart(Song_ID, -1);
	SpuSetReverb(1);
	do {
		if (reverb == 0) {
			SpuSetReverbVoice(0, 1 << (uVar1 & 0x1f));
		}
		else {
			SpuSetReverbVoice(1, 1 << (uVar1 & 0x1f));
		}
		uVar1 = uVar1 + 1;
	} while ((int)uVar1 < 0x18);
	return;
	*/
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

void StopXM(void)
{
	UNIMPLEMENTED();

	//XM_PlayStop(Song_ID);
	return;
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

void SetXMVolume(int volume)
{
	UNIMPLEMENTED();

	/*
	undefined *puVar1;

	puVar1 = &DAT_00002710 + volume;
	if ((int)puVar1 < 0) {
		puVar1 = (undefined *)0x0;
	}
	if (10000 < (int)puVar1) {
		puVar1 = &DAT_00002710;
	}
	gMusicVolume = volume;
	XM_SetMasterVol(Song_ID, (char)((int)puVar1 >> 7) + (char)((uint)puVar1 >> 8));
	return;
	*/
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

int GetFreeChannel(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int channel;
	int iVar1;
	uchar *puVar2;
	CHANNEL_DATA *pCVar3;
	ushort uVar4;
	char local_28[24];

	uVar4 = 0;
	SpuGetAllKeysStatus(local_28);
	channel = 0;
	puVar2 = &channels.locked;
	while ((*puVar2 != '\0' || (local_28[channel] != '\0'))) {
		channel = channel + 1;
		puVar2 = puVar2 + 0x78;
		if (0xf < channel) {
			channel = 0;
			puVar2 = &channels.locked;
			while ((*puVar2 != '\0' || (local_28[channel] != '\x03'))) {
				channel = channel + 1;
				puVar2 = puVar2 + 0x78;
				if (0xf < channel) {
					channel = -1;
					iVar1 = 0;
					pCVar3 = &channels;
					do {
						if ((pCVar3->locked == '\0') && (pCVar3->loop == '\0')) {
							if ((channel == -1) || (pCVar3->time < uVar4)) {
								channel = iVar1;
								uVar4 = pCVar3->time;
							}
						}
						iVar1 = iVar1 + 1;
						pCVar3 = pCVar3 + 1;
					} while (iVar1 < 0x10);
					if (channel != -1) {
						StopChannel(channel);
					}
					return channel;
				}
			}
			return channel;
		}
	}
	return channel;
	*/
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
	// 		struct VECTOR *pos; // $s3
	// 		struct VECTOR *cam_pos; // $s4
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

void UpdateVolumeAttributesS(int channel, int proximity)
{
	UNIMPLEMENTED();

	/*
	bool bVar1;
	int iVar2;
	undefined *puVar3;
	int iVar4;
	int iVar5;
	short sVar6;
	undefined *puVar7;
	undefined *puVar8;
	int iVar9;
	int iVar10;
	VECTOR *pVVar11;
	VECTOR *pVVar12;
	long unaff_s6;
	int iVar13;

	iVar2 = CalculateVolume(channel);
	iVar9 = gSurround;
	iVar10 = (int)(&channels)[channel].player;
	pVVar11 = (&channels)[channel].srcposition;
	pVVar12 = &(&player)[iVar10].cameraPos;
	iVar13 = (&player)[iVar10].snd_cam_ang;
	if ((camera_change == '\x01') || (puVar7 = &DAT_00002710 + iVar2, old_camera_change == '\x01')) {
		puVar7 = (undefined *)0x0;
	}
	puVar8 = puVar7;
	if ((int)puVar7 < 0) {
		puVar8 = (undefined *)0x0;
	}
	puVar3 = (undefined *)((int)puVar8 >> 1);
	if (10000 < (int)puVar7) {
		puVar8 = &DAT_00002710;
		puVar3 = &DAT_00001388;
	}
	iVar2 = ((int)puVar3 + (int)puVar8 + ((int)puVar8 >> 3) + ((int)puVar8 >> 7)) * master_volume >>
		0xe;
	sVar6 = (short)iVar2;
	(&channels)[channel].attr.volume.left = sVar6;
	if (iVar9 != 0) {
		sVar6 = -sVar6;
	}
	(&channels)[channel].attr.volume.right = sVar6;
	if (iVar2 == 0) {
		return;
	}
	if (pVVar11 == (VECTOR *)0x0) {
		return;
	}
	iVar9 = (&player)[iVar10].cameraPos.vz;
	if ((pVVar11->vz == iVar9) && (pVVar12->vx == pVVar11->vx)) {
		return;
	}
	if ((&player)[iVar10].cameraView == 2) {
		if (channel == (int)(&player)[iVar10].skidding.chan) {
			return;
		}
		if (channel == (int)(&player)[iVar10].wheelnoise.chan) {
			return;
		}
		if (iVar10 == 0) {
			if (channel == 0) {
				return;
			}
			iVar4 = 1;
			if (channel == (uint)(byte)(&player)[iVar10].cameraView) {
				return;
			}
		}
		else {
			if (iVar10 != 1) goto LAB_0007a128;
			if (channel == 3) {
				return;
			}
			iVar4 = 4;
			if (channel == 5) {
				return;
			}
		}
		if (channel == iVar4) {
			return;
		}
	}
LAB_0007a128:
	iVar4 = ratan2(pVVar11->vz - iVar9, pVVar12->vx - pVVar11->vx);
	iVar5 = -iVar4 + 0x1c00;
	iVar9 = iVar5;
	if (iVar5 < 0) {
		iVar9 = -iVar4 + 0x2bff;
	}
	iVar13 = (iVar5 + (iVar9 >> 0xc) * -0x1000) - (iVar13 + -0x1000);
	iVar9 = iVar13;
	if (iVar13 < 0) {
		iVar9 = iVar13 + 0xfff;
	}
	iVar13 = 0x800 - (iVar13 + (iVar9 >> 0xc) * -0x1000);
	iVar9 = iVar13;
	if (iVar13 < 0) {
		iVar9 = -iVar13;
	}
	if ((0x3ff < iVar9) && (bVar1 = iVar13 < 1, iVar13 = 0x800 - iVar9, bVar1)) {
		iVar13 = -iVar13;
	}
	if ((proximity != 0) &&
		(iVar9 = (&player)[iVar10].cameraPos.vz - pVVar11->vz, iVar10 = pVVar12->vx - pVVar11->vx,
			unaff_s6 = jsqrt(iVar9 * iVar9 + iVar10 * iVar10), 11999 < unaff_s6)) {
		proximity = 0;
	}
	if (iVar13 < 1) {
		if (iVar13 < 0) {
			iVar9 = ((iVar2 * 9) / 10) * -iVar13;
			if (iVar9 < 0) {
				iVar9 = iVar9 + 0x3ff;
			}
			iVar9 = iVar9 >> 10;
			if (proximity != 0) {
				iVar9 = (iVar9 * unaff_s6) / 12000;
			}
			sVar6 = (short)(iVar2 - iVar9);
			if (iVar2 - iVar9 < 0) {
				sVar6 = 0;
			}
			if (gSurround != 0) {
				sVar6 = -sVar6;
			}
			(&channels)[channel].attr.volume.right = sVar6;
		}
	}
	else {
		iVar13 = ((iVar2 * 9) / 10) * iVar13;
		if (iVar13 < 0) {
			iVar13 = iVar13 + 0x3ff;
		}
		iVar13 = iVar13 >> 10;
		if (proximity != 0) {
			iVar13 = (iVar13 * unaff_s6) / 12000;
		}
		sVar6 = (short)(iVar2 - iVar13);
		if (iVar2 - iVar13 < 0) {
			sVar6 = 0;
		}
		(&channels)[channel].attr.volume.left = sVar6;
	}
	return;
	*/
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

void UpdateVolumeAttributesM(int channel)
{
	UNIMPLEMENTED();

	/*
	int iVar1;
	undefined *puVar2;
	undefined *puVar3;
	undefined *puVar4;
	short sVar5;

	iVar1 = CalculateVolume(channel);
	if ((camera_change == '\x01') || (puVar3 = &DAT_00002710 + iVar1, old_camera_change == '\x01')) {
		puVar3 = (undefined *)0x0;
	}
	puVar4 = puVar3;
	if ((int)puVar3 < 0) {
		puVar4 = (undefined *)0x0;
	}
	puVar2 = (undefined *)((int)puVar4 >> 1);
	if (10000 < (int)puVar3) {
		puVar4 = &DAT_00002710;
		puVar2 = &DAT_00001388;
	}
	sVar5 = (short)(((int)puVar4 + (int)puVar2 + ((int)puVar4 >> 3) + ((int)puVar4 >> 7)) *
		master_volume >> 0xe);
	(&channels)[channel].attr.volume.left = sVar5;
	(&channels)[channel].attr.volume.right = sVar5;
	return;
	*/
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
	// 		struct VECTOR *pp; // $a3

		/* begin block 1.1 */
			// Start line: 1266
			// Start offset: 0x0007A3F4
			// Variables:
		// 		int distance; // $v1

			/* begin block 1.1.1 */
				// Start line: 1271
				// Start offset: 0x0007A3F4
				// Variables:
			// 		struct VECTOR ofse; // stack offset -24
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

int CalculateVolume(int channel)
{
	UNIMPLEMENTED();
	return 0;

	/*
	int iVar1;
	int iVar2;
	VECTOR *pVVar3;
	undefined4 in_t1;
	undefined4 in_t2;
	undefined4 in_t3;
	undefined *puVar4;
	int iVar5;

	puVar4 = &DAT_00002710 + (&channels)[channel].srcvolume;
	if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
		iVar1 = (int)puVar4 * 3;
		puVar4 = (undefined *)(iVar1 >> 2);
		if (iVar1 < 0) {
			puVar4 = (undefined *)(iVar1 + 3 >> 2);
		}
	}
	pVVar3 = (&channels)[channel].srcposition;
	if (pVVar3 != (VECTOR *)0x0) {
		iVar1 = (int)(&channels)[channel].player;
		setCopReg(2, in_t1, pVVar3->vx - (&player)[iVar1].cameraPos.vx);
		setCopReg(2, in_t2, pVVar3->vy + (&player)[iVar1].cameraPos.vy);
		setCopReg(2, in_t3, pVVar3->vz - (&player)[iVar1].cameraPos.vz);
		copFunction(2, 0xa00428);
		iVar1 = getCopReg(2, 0x19);
		iVar2 = getCopReg(2, 0x1a);
		iVar5 = getCopReg(2, 0x1b);
		iVar1 = SquareRoot0(iVar1 + iVar2 + iVar5);
		iVar2 = iVar1 + -16000;
		if (iVar1 < 0x400) {
			iVar1 = 0x400;
			iVar2 = -0x3a80;
		}
		if (iVar2 < 0) {
			iVar2 = 0;
		}
		else {
			if (0x1000 < iVar2) {
				iVar2 = 0x1000;
			}
		}
		iVar5 = 0xbd0000 / (iVar1 + 2000);
		if (iVar1 + 2000 == 0) {
			trap(7);
		}
		if (iVar2 != 0) {
			iVar5 = iVar5 * (0x1000 - iVar2) >> 0xc;
		}
		iVar5 = iVar5 * (int)puVar4;
		puVar4 = (undefined *)(iVar5 >> 0xc);
		if (iVar5 < 0) {
			puVar4 = (undefined *)(iVar5 + 0xfff >> 0xc);
		}
	}
	return (int)(puVar4 + -10000);
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ AllocateReverb(long mode /*$s1*/, long depth /*$s0*/)
 // line 1303, offset 0x0007ab3c
	/* begin block 1 */
		// Start line: 1304
		// Start offset: 0x0007AB3C
		// Variables:
	// 		struct SpuReverbAttr r_attr; // stack offset -40
	/* end block 1 */
	// End offset: 0x0007AB94
	// End Line: 1319

	/* begin block 2 */
		// Start line: 3989
	/* end block 2 */
	// End Line: 3990

void AllocateReverb(long mode, long depth)
{
	UNIMPLEMENTED();

	/*
	int iVar1;
	undefined4 local_28;
	uint local_24;
	undefined2 local_20;
	undefined2 local_1e;

	iVar1 = SpuReserveReverbWorkArea(1);
	if (iVar1 == 1) {
		local_24 = mode | 0x100;
		local_28 = 7;
		local_20 = (undefined2)depth;
		local_1e = local_20;
		SpuSetReverbModeParam(&local_28);
		SpuSetReverbDepth(&local_28);
		SpuSetReverb(1);
	}
	return;
	*/
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

int FESound(int sample)
{
	UNIMPLEMENTED();
	return 0;

	/*
	uchar uVar1;
	int iVar2;
	uint uVar3;
	int channel;
	int iVar4;
	uint uVar5;
	ushort uVar6;

	channel = GetFreeChannel();
	iVar4 = samples[sample + 0x23].samplerate << 0xb;
	iVar2 = iVar4 / 0xac44;
	uVar6 = (ushort)iVar2;
	if (0x3fff < iVar2) {
		uVar6 = 0x3fff;
	}
	uVar3 = (iVar4 >> 0xc) / 0x32;
	if (uVar3 == 0) {
		channel = -1;
	}
	else {
		uVar5 = samples[sample + 0x23].length;
		if (uVar3 == 0) {
			trap(7);
		}
		(&channels)[channel].srcvolume = 0;
		(&channels)[channel].srcposition = (VECTOR *)0x0;
		UpdateVolumeAttributesM(channel);
		stop_sound_handler = 1;
		(&channels)[channel].attr.mask = 0x9f;
		uVar1 = *(uchar *)&samples[sample + 0x23].loop;
		(&channels)[channel].attr.addr = samples[sample + 0x23].address;
		(&channels)[channel].attr.pitch = uVar6;
		(&channels)[channel].loop = uVar1;
		(&channels)[channel].time = (short)(uVar5 / uVar3) * 2 + 2;
		(&channels)[channel].samplerate = samples[sample + 0x23].samplerate;
		SpuSetVoiceAttr(&channels + channel);
		SpuSetKey(1, (&channels)[channel].attr.voice);
		stop_sound_handler = 0;
	}
	return channel;
	*/
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

void VsyncProc(void)
{
	UNIMPLEMENTED();

	/*
	vblcounter = vblcounter + 1;
	if (Song_ID != -1) {
		XM_Update();
	}
	SoundHandler();
	return;
	*/
}





