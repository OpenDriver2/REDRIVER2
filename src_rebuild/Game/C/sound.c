#include "driver2.h"
#include "sound.h"

#include "camera.h"
#include "xmplay.h"
#include "mission.h"
#include "glaunch.h"
#include "gamesnd.h"
#include "xaplay.h"
#include "players.h"

#include "LIBSPU.H"
#include "LIBETC.H"
#include "LIBGTE.H"

#include "INLINE_C.H"

#include "RAND.H"
#include "STRINGS.H"

#define SPU_CHANNEL_COUNT 24
#define LSB_BANK_COUNT 7

typedef struct __LSBDinfo
{
	int addr;
	int memtop;
	int count[LSB_BANK_COUNT];
	int bnktop[LSB_BANK_COUNT];
	int append;
} LSBDinfo;

typedef struct __pauseinfo
{
	u_short pitch[MAX_SFX_CHANNELS];
	u_short voll[MAX_SFX_CHANNELS];
	u_short volr[MAX_SFX_CHANNELS];
	u_short max;
	u_short lev;
} pauseinfo;

static pauseinfo pause;
static LSBDinfo lsbTabs;

LONGVECTOR3 dummylong = { 0, 0, 0 };

int bankaddr[2] = { 0 };
int banksize[2] = { 88064, 412672 };

char banks[24] = { 0 };

SAMPLE_DATA samples[LSB_BANK_COUNT][35];
CHANNEL_DATA channels[MAX_SFX_CHANNELS]; // offset 0xDE480

int master_volume = 0;	// why need two?

int gMasterVolume = 0;
int gMusicVolume = -4000;

int Song_ID = -1;
int VABID = -1;

int gSoundMode = 1;		// mono or stereo

int stop_sound_handler = 0;
int sound_paused = 0;
int music_paused = 0;

SpuCommonAttr sound_attr;

int vblcounter = 0; // vblank counter

// [D] [T]
void SoundHandler(void)
{
	int ct;
	int off;

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

// [D] [T]
void VsyncProc(void)
{
	vblcounter++;

	if (Song_ID != -1)
		XM_Update();

	SoundHandler();
}

// [D] [T]
void InitSound(void)
{
	int i;

	SpuInit();
	SpuInitMalloc(LSB_BANK_COUNT, banks);
	SpuSetMute(1);

	AllocateReverb(3, 16384);

	i = 1;
	do {
		bankaddr[i] = SpuMalloc(banksize[i]);

		if (bankaddr[i] == -1)
		{
			printError("Failed to SpuMalloc! Exiting...\n");
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
	channels[channel].srcvelocity = (LONGVECTOR3*)dummylong;
	channels[channel].player = 0;
}

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

// [D] [T]
void SetReverbState(int on)
{
	if (on == 0)
		SpuSetReverbVoice(0, SPU_ALLCH);
	else
		SpuSetReverbVoice(1, SPU_ALLCH);
}

// [D] [T]
void SetReverbInGameState(int on)
{
	int cl;

	cl = 0xffff;

	gSpeechQueue.reverb = on;

	if (on && gSpeechQueue.is_playing)
		cl &= ~SPU_KEYCH(gSpeechQueue.chan);

	SpuSetReverbVoice(on, cl);
}

// [D] [T]
int SetReverbChannelState(int ch, int on)
{
	int cl;
	int prev;

	cl = SPU_KEYCH(ch);

	prev = SpuGetReverbVoice();

	SpuSetReverbVoice(on, cl);

	return (prev & cl) != 0;
}

// [D] [T]
void SetMasterVolume(int vol)
{
	int vl = MAX(0, 10000 + vol);

	master_volume = vl + vl / 2 + vl / 8 + vl / 128;
	gMasterVolume = vol;
}

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

// [D] [T]
char SetPlayerOwnsChannel(int chan, char player)
{
	char oldPlayer;

	oldPlayer = channels[chan].player;
	channels[chan].player = player;

	return oldPlayer;
}

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


int gSurround = 0;

// [D]
void UpdateVolumeAttributesS(int channel, int proximity)
{
	int volume;
	int vol;
	int player_id;
	VECTOR *pos;
	VECTOR *cam_pos;
	int dist;
	int cam_ang, ang;
	int damp;


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
	if (ABS(ang) >= 1024)
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

		if (dist >= 12000)
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


// [D] [T]
void ComputeDoppler(CHANNEL_DATA *ch)
{
	int dist;
	int seperationrate;

	VECTOR *srcPos;
	long* srcVel; // LONGVECTOR3

	PLAYER *pl;
	int dx, dy, dz;

	srcPos = ch->srcposition;

	if (srcPos == NULL)
	{
		ch->dopplerScale = ONE;
		return;
	}

	srcVel = (long*)ch->srcvelocity;

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

// [D] [T]
int Start3DTrackingSound(int channel, int bank, int sample, VECTOR *position, LONGVECTOR3* velocity)
{
	if (channel < 0)
		channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = position;
	channels[channel].srcvelocity = velocity ? velocity : (LONGVECTOR3*)dummylong;
	channels[channel].srcpitch = 4096;
	channels[channel].srcvolume = 0;

	channel = CompleteSoundSetup(channel, bank, sample, 4096, 0);

	ComputeDoppler(&channels[channel]);
	SetChannelPitch(channel, 4096);

	return channel;
}

// [D]
int Start3DSoundVolPitch(int channel, int bank, int sample, int x, int y, int z, int volume, int pitch)
{
	if (channel < 0)
		channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = &channels[channel].position;
	channels[channel].srcvelocity = (LONGVECTOR3*)dummylong;
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

// [D] [T]
void SetChannelPitch(int channel, int pitch)
{
	int rate;

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

// [D] [T]
void SetChannelPosition3(int channel, VECTOR *position, LONGVECTOR3* velocity, int volume, int pitch, int proximity)
{
	if (channel < 0 || channel >= MAX_SFX_CHANNELS)
		return;

	if (camera_change != 1 && old_camera_change != 1 && sound_paused == 0)
	{
		channels[channel].srcposition = position;
		channels[channel].srcvelocity = velocity ? velocity : (LONGVECTOR3*)dummylong;
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

// [D] [T]
void PauseSound(void)
{
	SetReverbInGameState(0);
	PauseXM();
	PauseSFX();
	PauseXA();
}

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

// [D] [T]
void UnPauseSound(void)
{
	UnPauseXM();
	UnPauseSFX();
	ResumeXA();
}

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

// [D] [T]
void LockChannel(int channel)
{
	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return;

	channels[channel].locked = 1;
}

// [D] [T]
void UnlockChannel(int c)
{
	if (c < 0 || c >= MAX_SFX_CHANNELS)	// [A]
		return;

	channels[c].locked = 0;
}

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

// [D] [T]
void UpdateXMSamples(int num_samps)
{
	int i;
	for (i = 0; i < num_samps; i++)
		XM_SetVAGAddress(VABID, i, samples[0][i].address);
}

// [D] [T]
int LoadSoundBankDynamic(char *address, int length, int dbank)
{
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

// [D] [T]
void StopXM(void)
{
	XM_PlayStop(Song_ID);
}

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

// [D] [T]
int FESound(int sample)
{
	int channel;
	channel = GetFreeChannel();

	if (channel < 0 || channel >= MAX_SFX_CHANNELS)	// [A]
		return -1;

	channels[channel].srcposition = NULL;
	channels[channel].srcvelocity = (LONGVECTOR3*)dummylong;
	channels[channel].srcvolume = 4096;

	return CompleteSoundSetup(channel, 1, sample, 2048, -1);
}

// [D] [T]
int jsqrt(u_int a)
{
	int b0;
	int b1;

	if (a < 2)
		return a;

	b0 = a >> 1;

	if (a < 0x40000000)
	{
		if (b0 >= 0x8000)
			b0 = 0x7fff;
	}
	else
	{
		if (b0 >= 0x10000)
			b0 = 0xffff;
	}

	do
	{
		b1 = b0 + a / b0 >> 1;

		if (ABS(b0 - b1) <= 100)
			break;

		b0 = b1;
	} while (true);

	return b1;
}


