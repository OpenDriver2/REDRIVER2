#ifndef GAMESND_H
#define GAMESND_H

// Game loaded sound banks. DO NOT EDIT!
#define SOUND_BANK_SFX			1
#define SOUND_BANK_VOICES		2
#define SOUND_BANK_CARS			3
#define SOUND_BANK_ENVIRONMENT	4
#define SOUND_BANK_MISSION		5
#define SOUND_BANK_TANNER		6

extern int gDriver1Music;

extern int TimeSinceLastSpeech;

extern char phrase_top;

extern char force_idle[8];
extern char force_siren[8];

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
extern void DoPoliceLoudhailer(int cars, unsigned short *indexlist, uint* dist); // 0x0004F4A0

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
