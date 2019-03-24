
#include "../decomp_defs.h"

void IdentifyZone(struct __envsound *ep, struct __envsoundinfo *E, int pl);
void CalcEffPos(struct __envsound *ep, struct __envsoundinfo *E, int pl);
void CalcEffPos2(struct __envsound *ep, struct __envsoundinfo *E, int pl);
void UpdateEnvSnd(struct __envsound *ep, struct __envsoundinfo *E, int pl);

static envsoundfunc UpdateEnvSounds[] = {
	IdentifyZone,
	CalcEffPos,
	CalcEffPos2,
	UpdateEnvSnd
};

GEAR_DESC geard[2][4] =
{
	{
		{ 0, 0, 163, 144, 135 },
		{ 86, 133, 260, 90, 85 },
		{ 186, 233, 360, 60, 57 },
		{ 286, 326, 9999, 48, 45 }
	},
	{
		{ 0, 0, 50, 144, 135 },
		{ 43, 66, 100, 90, 85 },
		{ 93, 116, 150, 60, 57 },
		{ 143, 163, 9999, 48, 45 }
	}
};

// XM song position
int coptrackpos[8] = {
	0x10, 0xB, 7, 0x12, 0xC, 9, 8, 0xA,
};

/*
 * Offset 0x4D6F8
 * D:\driver2\game\C\GAMESND.C (line 171)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ ResidentModelsBodge()
{ // line 1, address 0x4d6f8
	int i; // $a1
	int j; // $a2
} // line 12, address 0x4d7ec
/*
 * Offset 0x4D7EC
 * D:\driver2\game\C\GAMESND.C (line 228)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ LoadLevelSFX(int missionNum /*$s1*/)
{ // line 1, address 0x4d7ec
	char city_night_fx; // $s2
	int i; // $s0
	{ // line 38, address 0x4db40
		int mission; // $a1
	} // line 41, address 0x4dcd8
} // line 67, address 0x4de98
/*
 * Offset 0x4DE98
 * D:\driver2\game\C\GAMESND.C (line 305)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ StartGameSounds()
{ // line 2, address 0x4de98
	struct VECTOR *cp; // $s2
	int i; // $s1
	{ // line 10, address 0x4defc
		int siren; // $a2
		int car_model; // $s0
	} // line 28, address 0x4e0e4
} // line 59, address 0x4e1f0
/*
 * Offset 0x4E1F0
 * D:\driver2\game\C\GAMESND.C (line 404)
 * Stack frame base $sp, length 0
 */
unsigned short /*$ra*/ GetEngineRevs(struct _CAR_DATA *cp /*$t2*/)
{ // line 1, address 0x4e1f0
	int gear; // $a1
	int lastgear; // $a0
	int ws; // $a2
	int acc; // $t1
	int type; // $t0
} // line 35, address 0x4e350
/*
 * Offset 0x4E350
 * D:\driver2\game\C\GAMESND.C (line 458)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ControlCarRevs(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x4e350
	unsigned short oldRevs; // $s2
	unsigned short desiredRevs; // $v1
	unsigned short newRevs; // $a0
	int acc; // $s3
	char spin; // $s4
	char player_id; // $s1
	{ // line 40, address 0x4e47c
		int revsmax; // $a3
	} // line 46, address 0x4e53c
} // line 55, address 0x4e5c8
/*
 * Offset 0x4E5C8
 * D:\driver2\game\C\GAMESND.C (line 595)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ControlSpeech(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
{ // line 1, address 0x4e5c8
} // line 40, address 0x4e768
/*
 * Offset 0x4E778
 * D:\driver2\game\C\GAMESND.C (line 721)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitDopplerSFX()
{ // line 1, address 0x4e778
	int i; // $v1
} // line 5, address 0x4e7f8
/*
 * Offset 0x4E7F8
 * D:\driver2\game\C\GAMESND.C (line 734)
 * Stack frame base $sp, length 200
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DoDopplerSFX()
{ // line 1, address 0x4e7f8
	int i; // $s1
	int j; // $s0
	int num_noisy_cars; // $s5
	unsigned long car_dist[20]; // stack address -176
	unsigned short indexlist[20]; // stack address -96
	struct _CAR_DATA *car_ptr; // $s2
	struct VECTOR *pp; // $a1
	unsigned long car_flags; // $s4
	char sirens; // stack address -56
	{ // line 91, address 0x4ed20
		int siren; // $v0
	} // line 108, address 0x4ee30
	{ // line 156, address 0x4f104
		int model; // $v1
	} // line 158, address 0x4f19c
	{ // line 175, address 0x4f224
		char old_idle; // $a1
		{ // line 180, address 0x4f2a8
			int model; // $v1
		} // line 190, address 0x4f37c
	} // line 195, address 0x4f3d0
} // line 210, address 0x4f508
/*
 * Offset 0x4F508
 * D:\driver2\game\C\GAMESND.C (line 946)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DoPoliceLoudhailer(int cars /*$s1*/, unsigned short *indexlist /*$s2*/, unsigned long *dist /*$s3*/)
{ // line 1, address 0x4f508
	int i; // $t1
	int rnd; // $t0
	int time; // $s0
	{ // line 5, address 0x4f5c8
		struct _CAR_DATA *car_ptr; // $a3
	} // line 13, address 0x4f68c
} // line 16, address 0x4f6b4
/*
 * Offset 0x4F6D0
 * D:\driver2\game\C\GAMESND.C (line 975)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CollisionSound(char player_id /*$s0*/, struct _CAR_DATA *cp /*$s5*/, int impact /*$s2*/, int car_car /*$s7*/)
{ // line 1, address 0x4f6d0
	long *here; // $s3
	char chan; // $s1
	char crash; // $s6
	char length; // $s4
	{ // line 8, address 0x4f758
		unsigned long p0dst; // $a1
		unsigned long p1dst; // $a0
	} // line 9, address 0x4f758
	{ // line 18, address 0x4f7ec
		{ // line 25, address 0x4f900
		} // line 32, address 0x4f998
	} // line 36, address 0x4f9bc
} // line 37, address 0x4f9bc
/*
 * Offset 0x4F9EC
 * D:\driver2\game\C\GAMESND.C (line 1019)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ExplosionSound(struct VECTOR *pos /*$s4*/, int type /*$s0*/)
{ // line 1, address 0x4f9ec
	int bang; // $s5
	int pitch; // $t0
	int rnd; // $s3
	struct VECTOR P; // stack address -48
	int sc1; // $s2
	int sc2; // $s1
} // line 29, address 0x4fbd8
/*
 * Offset 0x4FBFC
 * D:\driver2\game\C\GAMESND.C (line 1052)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ JerichoSpeak()
{ // line 1, address 0x4fbfc
	static unsigned int j_said; // address 0x0
	int rnd; // $a1
} // line 8, address 0x4fcf8
/*
 * Offset 0x4FCF8
 * D:\driver2\game\C\GAMESND.C (line 1103)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ SoundTasks()
{ // line 1, address 0x4fcf8
	int i; // $s2
	struct _CAR_DATA *cp; // $s1
} // line 80, address 0x5014c
/*
 * Offset 0x5014C
 * D:\driver2\game\C\GAMESND.C (line 1195)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ InitMusic(int musicnum /*$s0*/)
{ // line 1, address 0x5014c
	static char *music_pt; // address 0xc
	static char *sample_pt; // address 0x10
	static char xm_samples; // address 0x4
	int musicpos[3]; // stack address -32
	char *name; // $s1
	int sample_len; // $s0
	int music_len; // $t0
	{ // line 45, address 0x5020c
	} // line 52, address 0x50270
} // line 61, address 0x502e4
/*
 * Offset 0x502E4
 * D:\driver2\game\C\GAMESND.C (line 1350)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ Tunnels(struct __tunnelinfo *T /*$a0*/)
{ // line 1, address 0x502e4
	int i; // $t2
	int verb; // $t4
} // line 14, address 0x50468
/*
 * Offset 0x50468
 * D:\driver2\game\C\GAMESND.C (line 1366)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ AddTunnels(int level /*$a0*/)
{
}
/*
 * Offset 0x50C70
 * D:\driver2\game\C\GAMESND.C (line 1577)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AddEnvSnd(int type /*$t4*/, char flags /*$a1*/, int bank /*$a2*/, int sample /*$a3*/, int vol /*stack 16*/, long px /*stack 20*/, long pz /*stack 24*/)
{ // line 1, address 0x50c70
	void *data; // $a1
	struct __envsound *ep; // $t1
	struct __envsoundtags *T; // $t0
	long s; // $a1
} // line 58, address 0x50e70
/*
 * Offset 0x50E70
 * D:\driver2\game\C\GAMESND.C (line 1646)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ IdentifyZone(struct __envsound *ep /*$a3*/, struct __envsoundinfo *E /*stack 4*/, int pl /*$a2*/)
{ // line 1, address 0x50e70
	int i; // $s7
	int j; // $fp
	int tmp[4]; // stack address -96
	float d; // $s0
	float _g[4]; // stack address -80
	struct __bitfield64 zones; // stack address -64
} // line 58, address 0x51524
/*
 * Offset 0x51524
 * D:\driver2\game\C\GAMESND.C (line 1706)
 * Stack frame base $sp, length 8
 * Saved registers at address -4: s0 s1
 */
void /*$ra*/ CalcEffPos(struct __envsound *ep /*$s1*/, struct __envsoundinfo *E /*$a1*/, int pl /*$a2*/)
{ // line 1, address 0x51524
	int j; // $t5
	int me; // $t2
} // line 36, address 0x51838
/*
 * Offset 0x51838
 * D:\driver2\game\C\GAMESND.C (line 1744)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CalcEffPos2(struct __envsound *ep /*stack 0*/, struct __envsoundinfo *E /*$s7*/, int pl /*$a2*/)
{ // line 1, address 0x51838
	int j; // stack address -56
	int me; // $s5
	{ // line 12, address 0x51940
	} // line 12, address 0x51940
} // line 66, address 0x51f74
/*
 * Offset 0x51F74
 * D:\driver2\game\C\GAMESND.C (line 1812)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateEnvSnd(struct __envsound *ep /*stack 0*/, struct __envsoundinfo *E /*$s4*/, int pl /*stack 8*/)
{ // line 1, address 0x51f74
	int i; // stack address -48
} // line 29, address 0x521d0
/*
 * Offset 0x521D0
 * D:\driver2\game\C\GAMESND.C (line 1545)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ SetEnvSndVol(int snd /*$a0*/, int vol /*$a1*/)
{ // line 1, address 0x521d0
	int was; // $v0
} // line 5, address 0x521f8
/*
 * Offset 0x521F8
 * D:\driver2\game\C\GAMESND.C (line 665)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ CopSay(int phrase /*$s1*/, int direction /*$s2*/)
{
}
/*
 * Offset 0x522F4
 * D:\driver2\game\C\GAMESND.C (line 562)
 * Stack frame base $sp, length 0
 */
char /*$ra*/ PlaySpeech(struct SPEECH_QUEUE *pSpeechQueue /*$a0*/, int sound /*$a1*/)
{ // line 1, address 0x522f4
	char result; // $v0
	int i; // $a2
} // line 21, address 0x52354
/*
 * Offset 0x52354
 * D:\driver2\game\C\GAMESND.C (line 127)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CarHasSiren(int index /*$a0*/)
{
}
/*
 * Offset 0x523F0
 * D:\driver2\game\C\GAMESND.C (line 1510)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitEnvSnd(int num_envsnds /*$a0*/)
{ // line 1, address 0x523f0
	int i; // $v1
	int p; // $a1
	struct __envsoundtags *T; // $t1
} // line 28, address 0x524a4
/*
 * Offset 0x524A4
 * D:\driver2\game\C\GAMESND.C (line 1317)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitTunnels(char n /*$a0*/)
{ // line 1, address 0x524a4
	struct __tunnelinfo *T; // $a1
} // line 8, address 0x524c8
/*
 * Offset 0x524C8
 * D:\driver2\game\C\GAMESND.C (line 98)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ LoadBankFromLump(int bank /*$s3*/, int lump /*$s2*/)
{ // line 1, address 0x524c8
	static unsigned int blockLimit[73] = {0}; // address 0x10
	int length; // $s0
	char *name; // $s1

	name = "SOUND\\VOICES2.BLK";

	if (blockLimit[1] == 0)
	{
		LoadFileSeg(name, blockLimit[0], 0, 292);
	}

	//LoadFileSeg(name, 0x8018, 0, 292);
	//LoadSoundBankDynamic(0x8018, );

} // line 21, address 0x52578
/*
 * Offset 0x52578
 * D:\driver2\game\C\GAMESND.C (line 161)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ SpecialVehicleKludge(char vehicle2 /*$a0*/)
{ // line 1, address 0x52578
	static char kludge_bank[4][3] = {
		{ 2, 18, 10 },
		{ 2, 17, 4 },
		{ 9, 11, 13 },
		{ 17, 11, 15 }
	}; // address 0x134
} // line 8, address 0x525a8
/*
 * Offset 0x525A8
 * D:\driver2\game\C\GAMESND.C (line 197)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ MapCarIndexToBank(int index /*$a1*/)
{ // line 1, address 0x525a8
	int *RM; // $a2
	static char car_banks[4][9] = {
		{12, 4, 13, 5, 16, 9, 2, 16, 10},
		{10, 11, 7, 6, 17, 17, 2, 5, 4},
		{14, 3, 4, 6, 11, 9, 2, 17, 10},
		{8, 7, 13, 9, 2, 17, 17, 11, 16},
	};
} // line 22, address 0x52660
/*
 * Offset 0x52660
 * D:\driver2\game\C\GAMESND.C (line 515)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ DoSpeech(int chan /*$a0*/, int sound /*$a2*/)
{
}
/*
 * Offset 0x526BC
 * D:\driver2\game\C\GAMESND.C (line 587)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitSpeechQueue(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
{
}
/*
 * Offset 0x526FC
 * D:\driver2\game\C\GAMESND.C (line 677)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ BodSay(int phrase /*$a1*/)
{
}
/*
 * Offset 0x52738
 * D:\driver2\game\C\GAMESND.C (line 686)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ MissionSay(int phrase /*$a0*/)
{ // line 1, address 0x52738
} // line 5, address 0x52764
/*
 * Offset 0x52774
 * D:\driver2\game\C\GAMESND.C (line 700)
 * Stack frame base $sp, length 16
 */
long /*$ra*/ jsqrt(unsigned long a /*$a0*/)
{ // line 1, address 0x52774
	long b1; // $a1
	long b0; // $v1
} // line 13, address 0x52828
/*
 * Offset 0x52828
 * D:\driver2\game\C\GAMESND.C (line 1085)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ FunkUpDaBGMTunez(int funk /*$a0*/)
{
}
/*
 * Offset 0x528B0
 * D:\driver2\game\C\GAMESND.C (line 1331)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AddTunnel(long x1 /*$t1*/, long y1 /*$a1*/, long z1 /*$a2*/, long x2 /*$a3*/, long y2 /*stack 16*/, long z2 /*stack 20*/)
{ // line 1, address 0x528b0
	struct __tunnelinfo *T; // $t0
} // line 13, address 0x52964
/*
 * Offset 0x5296C
 * D:\driver2\game\C\GAMESND.C (line 1555)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetEnvSndPos(int snd /*$a0*/, long px /*$a1*/, long pz /*$a2*/)
{
}
/*
 * Offset 0x529B0
 * D:\driver2\game\C\GAMESND.C (line 1852)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitLeadHorn()
{
}
/*
 * Offset 0x529BC
 * D:\driver2\game\C\GAMESND.C (line 1855)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ LeadHorn(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x529bc
	static unsigned int rnd; // address 0x8
} // line 12, address 0x52a90