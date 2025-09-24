#ifndef GAMESND_H
#define GAMESND_H

// Game loaded sound banks. DO NOT EDIT!
#define SOUND_BANK_DUMMY		0
#define SOUND_BANK_SFX			1
#define SOUND_BANK_VOICES		2
#define SOUND_BANK_CARS			3
#define SOUND_BANK_ENVIRONMENT	4
#define SOUND_BANK_MISSION		5
#define SOUND_BANK_TANNER		6

enum SoundBankIds
{
	SBK_ID_MENU = 0,	// frontend, alpha 1.6 used it in ingame menu as well

	SBK_ID_SFX = 1,
	SBK_CAR_SOUNDS_START = 2,

	SBK_ID_JERICHO = 19,	// jericho_in_back
	SBK_ID_JONES = 20,

	SBK_CITY_EFFECTS_START = 21,

	SBK_COP_PHRASES_START = 29,

	SBK_ID_COUNTDOWN = 44,

	// Mission banks start
	// Jones banks
	SBK_ID_MISSION_2 = 45,	// Chase the witness
	SBK_ID_MISSION_3 = 46,	// Train pursuit
	SBK_ID_MISSION_4 = 47,
	SBK_ID_MISSION_10 = 48,

	SBK_ID_MISSION_11 = 49,	// Hijack the truck
	SBK_ID_MISSION_13 = 50,	// Steal the truck
	SBK_ID_FERRY = 51,	// Escape to ferry / To the docks
	SBK_ID_MISSION_18 = 52,	// Tail Jericho
	SBK_ID_MISSION_22 = 53,	// Beat the train
	SBK_ID_MISSION_23 = 54,	// Car bomb
	SBK_ID_MISSION_24 = 55,	// Stake out
	SBK_ID_MISSION_27 = 56,
	SBK_ID_MISSION_29 = 57,	// C4 deal
	SBK_ID_MISSION_30 = 58,	// Destroy the yard
	SBK_ID_MISSION_32 = 59,	// Steal the cop car
	SBK_ID_MISSION_33 = 60,	// Caine's cash - UNUSED
	SBK_ID_MISSION_35 = 61,	// Boat jump
	SBK_ID_MISSION_39 = 62,	// Lenny escaping - UNUSED
	SBK_ID_MISSION_40 = 63,	// Lenny gets caught

	SBK_ID_HAVANA_TAKEADRIVE = 64,
	SBK_ID_VEGAS_TAKEADRIVE = 65,

	SBK_ID_TANNER = 66,
	SBK_ID_SPECIAL_SIREN1 = 67,
	SBK_ID_SPECIAL_SIREN2 = 68,
	SBK_COP_SIREN_START = 69,
};

struct SPEECH_QUEUE
{
	char allowed;
	char chan;
	char is_playing;
	int count;
	char reverb;
	int slot[7];
};

extern int gDriver1Music;

extern int TimeSinceLastSpeech;

extern char phrase_top;

#ifndef PSX
extern char noisy_cars[MAX_CARS];

#define CARNOISE_FLAG_NONE 0
#define CARNOISE_FLAG_NOISY 1
#define CARNOISE_FLAG_FORCE_IDLE 2
#define CARNOISE_FLAG_FORCE_SIREN 4

#define CARNOISE_GET_FLAG(id,f) (noisy_cars[id] & f)
#define CARNOISE_SET_FLAG(id,f) (noisy_cars[id] |= f)
#define CARNOISE_CLEAR_FLAG(id,f) (noisy_cars[id] &= ~(f))

#define CARNOISE_IS_ACTIVE(id) CARNOISE_GET_FLAG(id,CARNOISE_FLAG_NOISY)
#define CARNOISE_ENABLE(id) CARNOISE_SET_FLAG(id,CARNOISE_FLAG_NOISY)
#define CARNOISE_DISABLE(id) CARNOISE_CLEAR_FLAG(id,CARNOISE_FLAG_NOISY)

#define CARNOISE_HAS_FORCED_IDLE(id) CARNOISE_GET_FLAG(id,CARNOISE_FLAG_FORCE_IDLE)
#define CARNOISE_SET_FORCED_IDLE(id) CARNOISE_SET_FLAG(id,CARNOISE_FLAG_FORCE_IDLE)
#define CARNOISE_CLEAR_FORCED_IDLE(id) CARNOISE_CLEAR_FLAG(id,CARNOISE_FLAG_FORCE_IDLE)

#define CARNOISE_HAS_FORCED_SIREN(id) CARNOISE_GET_FLAG(id,CARNOISE_FLAG_FORCE_SIREN)
#define CARNOISE_SET_FORCED_SIREN(id) CARNOISE_SET_FLAG(id,CARNOISE_FLAG_FORCE_SIREN)
#define CARNOISE_CLEAR_FORCED_SIREN(id) CARNOISE_CLEAR_FLAG(id,CARNOISE_FLAG_FORCE_SIREN)
#else
extern char force_idle[8];
extern char force_siren[8];

#define CARNOISE_HAS_FORCED_IDLE(id) (force_idle[id] > -1)
#define CARNOISE_SET_FORCED_IDLE(id) (force_idle[id] = 0)
#define CARNOISE_CLEAR_FORCED_IDLE(id) (force_idle[id] = -1)

#define CARNOISE_HAS_FORCED_SIREN(id) (force_siren[id] != 0)
#define CARNOISE_SET_FORCED_SIREN(id) (force_siren[id] = 1)
#define CARNOISE_CLEAR_FORCED_SIREN(id) (force_siren[id] = 0)
#endif
extern SPEECH_QUEUE gSpeechQueue;

extern void LoadBankFromLump(int bank, int lump); // 0x00052460

extern int CarHasSiren(int index); // 0x000522EC
extern int ResidentModelsBodge(); // 0x0004D690

extern void LoadLevelSFX(int missionNum); // 0x0004D784

extern void StartGameSounds(); // 0x0004DE30
extern void StartPlayerCarSounds(int playerId, int model, VECTOR* pos);
extern void SoundTasks(); // 0x0004FC90

extern void ControlCarRevs(CAR_DATA *cp); // 0x0004E2E8

extern void DoSpeech(int chan, int sound); // 0x000525F8
extern char PlaySpeech(SPEECH_QUEUE *pSpeechQueue, int sound); // 0x0005228C
extern void InitSpeechQueue(SPEECH_QUEUE *pSpeechQueue); // 0x00052654
extern void ControlSpeech(SPEECH_QUEUE *pSpeechQueue); // 0x0004E560

extern void CopSay(int phrase, int direction); // 0x00052190
extern void BodSay(int phrase); // 0x00052694

extern void MissionSay(int phrase); // 0x000526D0

extern void InitDopplerSFX(); // 0x0004E710
extern void DoDopplerSFX(); // 0x0004E790
extern void DoPoliceLoudhailer(int cars, unsigned short *indexlist, u_int* dist); // 0x0004F4A0

extern void CollisionSound(char player_id, CAR_DATA *cp, int impact, int car_car); // 0x0004F668
extern void ExplosionSound(VECTOR *pos, int type); // 0x0004F984

extern void JerichoSpeak(); // 0x0004FB94

extern void InitMusic(int musicnum); // 0x000500E4
extern void FunkUpDaBGMTunez(int funk); // 0x000527C0

extern void InitTunnels(char n); // 0x0005243C
extern int AddTunnel(int x1, int y1, int z1, int x2, int y2, int z2); // 0x00052848
extern void Tunnels(tunnelinfo *T); // 0x0005027C
extern void AddTunnels(int level); // 0x00050400

extern void InitEnvSnd(int num_envsnds); // 0x00052388
extern int SetEnvSndVol(int snd, int vol); // 0x00052168
extern void SetEnvSndPos(int snd, int px, int pz); // 0x00052904

extern int AddEnvSnd(int type, char flags, int bank, int sample, int vol, int px, int pz, int px2, int pz2); // 0x00050C08

extern void InitLeadHorn(); // 0x00052948
extern void LeadHorn(CAR_DATA *cp); // 0x00052954


#endif
