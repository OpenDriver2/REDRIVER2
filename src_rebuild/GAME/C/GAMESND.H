#ifndef GAMESND_H
#define GAMESND_H

extern int gDriver1Music;

extern int TimeSinceLastSpeech;

extern char phrase_top;

extern char force_idle[8];
extern char force_siren[8];

extern SPEECH_QUEUE gSpeechQueue;

extern void LoadBankFromLump(int bank, int lump); // 0x00052460

extern int CarHasSiren(int index); // 0x000522EC

extern int SpecialVehicleKludge(char vehicle2); // 0x00052510

extern int ResidentModelsBodge(); // 0x0004D690

extern int MapCarIndexToBank(int index); // 0x00052540

extern void LoadLevelSFX(int missionNum); // 0x0004D784

extern void StartGameSounds(); // 0x0004DE30

extern ushort GetEngineRevs(CAR_DATA *cp); // 0x0004E188

extern void ControlCarRevs(CAR_DATA *cp); // 0x0004E2E8

extern void DoSpeech(int chan, int sound); // 0x000525F8

extern char PlaySpeech(SPEECH_QUEUE *pSpeechQueue, int sound); // 0x0005228C

extern void InitSpeechQueue(SPEECH_QUEUE *pSpeechQueue); // 0x00052654

extern void ControlSpeech(SPEECH_QUEUE *pSpeechQueue); // 0x0004E560

extern void CopSay(int phrase, int direction); // 0x00052190

extern void BodSay(int phrase); // 0x00052694

extern void MissionSay(int phrase); // 0x000526D0

extern long jsqrt(unsigned long a); // 0x0005270C

extern void InitDopplerSFX(); // 0x0004E710

extern void DoDopplerSFX(); // 0x0004E790

extern void DoPoliceLoudhailer(int cars, unsigned short *indexlist, unsigned long *dist); // 0x0004F4A0

extern void CollisionSound(char player_id, CAR_DATA *cp, int impact, int car_car); // 0x0004F668

extern void ExplosionSound(VECTOR *pos, int type); // 0x0004F984

extern void JerichoSpeak(); // 0x0004FB94

extern void FunkUpDaBGMTunez(int funk); // 0x000527C0

extern void SoundTasks(); // 0x0004FC90

extern void InitMusic(int musicnum); // 0x000500E4

extern void InitTunnels(char n); // 0x0005243C

extern int AddTunnel(long x1, long y1, long z1, long x2, long y2, long z2); // 0x00052848

extern void Tunnels(tunnelinfo *T); // 0x0005027C

extern void AddTunnels(int level); // 0x00050400

extern void InitEnvSnd(int num_envsnds); // 0x00052388

extern int SetEnvSndVol(int snd, int vol); // 0x00052168

extern void SetEnvSndPos(int snd, long px, long pz); // 0x00052904

extern int AddEnvSnd(int type, char flags, int bank, int sample, int vol, long px, long pz, long px2, long pz2); // 0x00050C08

extern void IdentifyZone(envsound *ep, envsoundinfo *E, int pl); // 0x00050E08

extern void CalcEffPos(envsound *ep, envsoundinfo *E, int pl); // 0x000514BC

extern void CalcEffPos2(envsound *ep, envsoundinfo *E, int pl); // 0x000517D0

extern void UpdateEnvSnd(envsound *ep, envsoundinfo *E, int pl); // 0x00051F0C

extern void InitLeadHorn(); // 0x00052948

extern void LeadHorn(CAR_DATA *cp); // 0x00052954


#endif
