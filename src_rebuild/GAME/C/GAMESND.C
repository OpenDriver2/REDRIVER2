

#include "DRIVER2.H"
#include "GAMESND.H"

#include "LIBSPU.H"

#include "SOUND.H"
#include "SYSTEM.H"
#include "HANDLING.H"
#include "MISSION.H"
#include "MC_SND.H"
#include "GLAUNCH.H"
#include "LOADVIEW.H"
#include "CUTSCENE.H"
#include "CAMERA.H"
#include "COP_AI.H"
#include "CARS.H"
#include "WHEELFORCES.H"
#include "ENVSOUND.H"
#include "CONVERT.H"
#include "XMPLAY.H"
#include "PLAYERS.H"
#include "MAIN.H"
#include "SKY.H"
#include "DEBRIS.H"

#include <math.h>

#include "FELONY.H"

typedef void(*envsoundfunc)(struct __envsound* ep /*$s1*/, struct __envsoundinfo* E /*$a1*/, int pl /*$a2*/);

void IdentifyZone(struct __envsound* ep, struct __envsoundinfo* E, int pl);
void CalcEffPos(struct __envsound* ep, struct __envsoundinfo* E, int pl);
void CalcEffPos2(struct __envsound* ep, struct __envsoundinfo* E, int pl);
void UpdateEnvSnd(struct __envsound* ep, struct __envsoundinfo* E, int pl);

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
int xm_coptrackpos_d2[8] = {
	0x10, 0xB, 7, 0x12, 0xC, 9, 8, 0xA,
};

int xm_coptrackpos_d1[8] = {
	0xC, 0xC, 0xB, 0xB, 8, 0xB, 0xF, 0xC,
};

int* xm_coptrackpos;
int gDriver1Music = 0;

// TODO: AI.C?
SPEECH_QUEUE gSpeechQueue;
static char cop_bank = 0;
char phrase_top = 0;

static struct __othercarsound siren_noise[2];
static struct __othercarsound car_noise[4];
static int loudhail_time = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ LoadBankFromLump(int bank /*$s3*/, int lump /*$s2*/)
 // line 98, offset 0x00052460
	/* begin block 1 */
		// Start line: 99
		// Start offset: 0x00052460
		// Variables:
	// 		static unsigned int blockLimit[73]; // offset 0x10
	// 		int size; // $s0
	// 		char *name; // $s1
	/* end block 1 */
	// End offset: 0x00052510
	// End Line: 119

	/* begin block 2 */
		// Start line: 4241
	/* end block 2 */
	// End Line: 4242

	/* begin block 3 */
		// Start line: 196
	/* end block 3 */
	// End Line: 197

char _sbank_buffer[0x80000];		// 0x180000

// [D] [T]
void LoadBankFromLump(int bank, int lump)
{
	static unsigned int blockLimit[73] = { 0 };

	int size;
	char* name;

	name = "SOUND\\VOICES2.BLK";

	if (blockLimit[1] == 0)
		LoadfileSeg(name, (char*)blockLimit, 0, sizeof(blockLimit));

	size = blockLimit[lump + 1] - blockLimit[lump];
	LoadfileSeg(name, _sbank_buffer, blockLimit[lump], size);

	if (size > 0 && blockLimit[lump] && blockLimit[lump + 1]) // [A]
		LoadSoundBankDynamic(_sbank_buffer, size, bank);
	else
		printf("WARNING: sound bank lump %d is not valid!\n", lump);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarHasSiren(int index /*$a0*/)
 // line 127, offset 0x000522ec
	/* begin block 1 */
		// Start line: 254
	/* end block 1 */
	// End Line: 255

	/* begin block 2 */
		// Start line: 2853
	/* end block 2 */
	// End Line: 2854

// [D] [T]
int CarHasSiren(int index)
{
	if (index == 4)
	{
		if (GameLevel == 0)
		{
			if (MissionHeader->residentModels[4] == 8)
				return 0x110;
		}
		else if (GameLevel == 2)
		{
			if (MissionHeader->residentModels[4] == 9)
				return 0x110;
		}
		else if (GameLevel == 3)
		{
			if (MissionHeader->residentModels[4] == 10)
				return 0x110;
		}
	}

	return (MissionHeader->residentModels[index] == 0) << 9;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SpecialVehicleKludge(char vehicle2 /*$a0*/)
 // line 161, offset 0x00052510
	/* begin block 1 */
		// Start line: 162
		// Start offset: 0x00052510
		// Variables:
	// 		static char kludge_bank[4][3]; // offset 0x134
	/* end block 1 */
	// End offset: 0x00052540
	// End Line: 169

	/* begin block 2 */
		// Start line: 4346
	/* end block 2 */
	// End Line: 4347

	/* begin block 3 */
		// Start line: 4389
	/* end block 3 */
	// End Line: 4390

// [D] [T]
int SpecialVehicleKludge(char vehicle2)
{
	static char kludge_bank[4][3] = {
		{ 2, 18, 10 },
		{ 2, 17, 4 },
		{ 9, 11, 13 },
		{ 17, 11, 15 }
	};

	return kludge_bank[GameLevel][vehicle2];
}



// decompiled code
// original method signature: 
// int /*$ra*/ ResidentModelsBodge()
 // line 171, offset 0x0004d690
	/* begin block 1 */
		// Start line: 172
		// Start offset: 0x0004D690
		// Variables:
	// 		int i; // $a1
	// 		int j; // $a2
	/* end block 1 */
	// End offset: 0x0004D784
	// End Line: 183

	/* begin block 2 */
		// Start line: 342
	/* end block 2 */
	// End Line: 343

	/* begin block 3 */
		// Start line: 344
	/* end block 3 */
	// End Line: 345

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int ResidentModelsBodge(void)
{
	int i;
	int j;

	j = MissionHeader->residentModels[4];

	if (gCurrentMissionNumber == 24 || gCurrentMissionNumber == 27 ||
		gCurrentMissionNumber == 29 ||
		(gCurrentMissionNumber == 30 || gCurrentMissionNumber == 35))
	{
		return 3;
	}

	if (gCurrentMissionNumber - 50U < 16 && j == 12)
	{
		return 5;
	}

	if (GameLevel == 0)
	{
		i = 11;

		if (j == 9)
			return 4;
	}
	else if (GameLevel == 1)
	{
		if (j - 8U > 1)
			return 3;
	}
	else if (GameLevel == 2)
		i = 8;
	else if (GameLevel == 3)
		i = 11;
	else
		return 3;

	if (j != i)
		return 3;

	return 4;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MapCarIndexToBank(int index /*$a1*/)
 // line 197, offset 0x00052540
	/* begin block 1 */
		// Start line: 198
		// Start offset: 0x00052540
		// Variables:
	// 		int *RM; // $a2
	// 		static char car_banks[4][9]; // offset 0x140
	/* end block 1 */
	// End offset: 0x000525F8
	// End Line: 219

	/* begin block 2 */
		// Start line: 4432
	/* end block 2 */
	// End Line: 4433

	/* begin block 3 */
		// Start line: 4461
	/* end block 3 */
	// End Line: 4462

	/* begin block 4 */
		// Start line: 4472
	/* end block 4 */
	// End Line: 4473

// [D] [T]
int MapCarIndexToBank(int index)
{
	static char car_banks[4][9] =
	{
		{12, 4, 13, 5, 16, 9, 2, 15, 10},
		{10, 11, 7, 6, 17, 17, 2, 5, 4},
		{14, 3, 4, 6, 11, 9, 2, 17, 10},
		{8, 7, 13, 9, 2, 17, 17, 11, 16},
	};

	int* RM;
	int model;
	int ret;

	RM = MissionHeader->residentModels;

	model = RM[index];

	if (gCurrentMissionNumber - 39U < 2 && RM[index] == 13)
	{
		model = 10 - (RM[0] + RM[1] + RM[2]);

		if (model < 1)
			model = 1;

		if (model > 4)
			model = 4;
	}

	ret = model - 1;

	if (model == 0)
		ret = 1;

	if (ret > 6)
		ret -= 3;

	return car_banks[GameLevel][ret];
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadLevelSFX(int missionNum /*$s1*/)
 // line 228, offset 0x0004d784
	/* begin block 1 */
		// Start line: 229
		// Start offset: 0x0004D784
		// Variables:
	// 		char city_night_fx; // $s2
	// 		int i; // $s0

		/* begin block 1.1 */
			// Start line: 266
			// Start offset: 0x0004DAD8
			// Variables:
		// 		int mission; // $a1
		/* end block 1.1 */
		// End offset: 0x0004DC70
		// End Line: 269
	/* end block 1 */
	// End offset: 0x0004DE30
	// End Line: 295

	/* begin block 2 */
		// Start line: 414
	/* end block 2 */
	// End Line: 415

	/* begin block 3 */
		// Start line: 460
	/* end block 3 */
	// End Line: 461

static char cop_model = 0;

// [D] [T]
void LoadLevelSFX(int missionNum)
{
	int index;
	int i;
	uint city_night_fx;

	city_night_fx = (gTimeOfDay == 3);

	cop_bank = missionNum % 4 + 1;
	cop_model = 3;

	// init sound bank memory
	LoadSoundBankDynamic(NULL, 0, 0);
	i = 0;

	// load car banks
	do {
		LoadBankFromLump(3, MapCarIndexToBank(i));
		i++;
	} while (i < 3);

	ShowLoading();

	// load footsteps, car effects etc
	LoadBankFromLump(1, 0);
	LoadBankFromLump(1, 1);
	LoadBankFromLump(6, 66);

	if (GameLevel & 2)
		LoadBankFromLump(2, (GameLevel & 1) * 2 + 69);
	else
		LoadBankFromLump(2, (GameLevel & 3) + 69);

	// Load cop voices except those missions
	if (missionNum - 1U > 3 && missionNum != 6 && missionNum != 7 &&
		missionNum != 9 && missionNum != 10 && missionNum != 11 &&
		missionNum != 13 && missionNum != 14 && missionNum != 18 &&
		missionNum != 19 && missionNum != 20 && missionNum != 22 &&
		missionNum != 26 && missionNum != 28 && missionNum != 31 &&
		missionNum != 33 && missionNum != 34 && missionNum != 38 &&
		missionNum != 40)
	{
		if (GameLevel & 2)
		{
			LoadBankFromLump(2, (GameLevel & 1) * 8 + (GameLevel & 1) * 2 + 29);
			LoadBankFromLump(2, (GameLevel & 1) * 10 + cop_bank + 29);
		}
		else
		{
			LoadBankFromLump(2, (GameLevel & 3) * 4 + (GameLevel & 3) + 29);
			LoadBankFromLump(2, (GameLevel & 3) * 5 + cop_bank + 29);
		}
	}

	ShowLoading();

	// load ambient effects
	if (NumPlayers < 2 || NoPlayerControl != 0)
	{
		if (GameLevel == 0)
			LoadBankFromLump(4, city_night_fx + 21);
		else if (GameLevel == 1)
			LoadBankFromLump(4, city_night_fx + 23);
		else if (GameLevel == 2)
			LoadBankFromLump(4, city_night_fx + 25);
		else if (GameLevel == 3)
			LoadBankFromLump(4, city_night_fx + 27);
	}

	phrase_top = 0;

	if (missionNum - 2U < 3 || missionNum == 9 || missionNum == 10 || missionNum == 27)
	{
		LoadBankFromLump(5, 20);
		phrase_top = 7;
	}
	else if (missionNum - 20U < 2 || missionNum == 25 || missionNum == 39)
	{
		LoadBankFromLump(5, 19);
		phrase_top = 3;
	}

	switch (missionNum)
	{
		case 2:
			index = 45;
			break;
		case 3:
			index = 46;
			break;
		case 4:
			index = 47;
			break;
		case 10:
			index = 48;
			break;
		case 13:
			index = 50;
			break;
		case 15:
			index = 51;
			break;
		case 16:
			index = 51;
			break;
		case 18:
			index = 52;
			break;
		case 22:
			index = 53;
			break;
		case 23:
			index = 54;
			break;
		case 24:
			index = 55;
			break;
		case 27:
			index = 56;
			break;
		case 29:
			index = 57;
			break;
		case 30:
			index = 58;
			break;
		case 25:
		case 32:
			index = 59;
			break;
		case 33:
			index = 60;
			break;
		case 35:
			index = 61;
			break;
		case 39:
			index = 62;
			break;
		case 40:
			index = 63;
			break;
		case 54:
			index = 65;
			break;
		case 55:
			index = 65;
			break;
		case 11:
		case 20:
		case 21:
		case 52:
		case 53:
		case 56:
		case 57:
			index = 49;
			break;
		default:
			index = 0;
	}

	if (index != 0)
		LoadBankFromLump(5, index);

	if (GameLevel == 0 || GameLevel == 3)
		LoadBankFromLump(1, 67);
	else if (GameLevel == 2)
		LoadBankFromLump(1, 68);

	LoadSoundBankDynamic(NULL, 1, 0);
	LoadSoundBankDynamic(NULL, 3, 3);

	if (gCurrentMissionNumber - 39 < 2)
		LoadBankFromLump(3, MapCarIndexToBank(4));
	else
		LoadBankFromLump(3, SpecialVehicleKludge(0));

	if (missionNum != 24 && missionNum != 27 &&
		missionNum != 29 && missionNum != 30 &&
		missionNum != 35)
	{
		LoadBankFromLump(3, SpecialVehicleKludge(1));
	}

	if (missionNum - 50U < 16)
	{
		LoadBankFromLump(3, SpecialVehicleKludge(2));
	}

	if (gCurrentMissionNumber == 7 || gCurrentMissionNumber == 9 ||
		gCurrentMissionNumber == 11 || gCurrentMissionNumber == 20 ||
		gCurrentMissionNumber == 26 || gCurrentMissionNumber == 31 ||
		gCurrentMissionNumber == 33 || gCurrentMissionNumber == 40)
	{
		i = 0;

		do {
			if (MissionHeader->residentModels[i] == MissionHeader->residentModels[3])
				cop_model = i;

			i++;
		} while (i < 3);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ StartGameSounds()
 // line 305, offset 0x0004de30
	/* begin block 1 */
		// Start line: 307
		// Start offset: 0x0004DE30
		// Variables:
	// 		struct VECTOR *cp; // $s2
	// 		int i; // $s1

		/* begin block 1.1 */
			// Start line: 315
			// Start offset: 0x0004DE94
			// Variables:
		// 		int siren; // $a2
		// 		int car_model; // $s0
		/* end block 1.1 */
		// End offset: 0x0004E07C
		// End Line: 333
	/* end block 1 */
	// End offset: 0x0004E188
	// End Line: 364

	/* begin block 2 */
		// Start line: 614
	/* end block 2 */
	// End Line: 615

	/* begin block 3 */
		// Start line: 625
	/* end block 3 */
	// End Line: 626

	/* begin block 4 */
		// Start line: 626
	/* end block 4 */
	// End Line: 627

	/* begin block 5 */
		// Start line: 633
	/* end block 5 */
	// End Line: 634

/* WARNING: Unknown calling convention yet parameter storage is locked */

int TimeSinceLastSpeech = 0;

// [D] [T]
void StartGameSounds(void)
{
	int channel;
	int i;
	_PLAYER* lcp;
	_CAR_DATA* cp;
	int sample;
	int pitch;
	int car_model;
	int siren;

	TimeSinceLastSpeech = 0;

	lcp = player;

	i = 0;
	
	while (i < NumPlayers)
	{
		if(lcp->playerType == 1)
		{
			cp = &car_data[lcp->playerCarId];
			car_model = cp->ap.model;

			if (car_model == 4)
				sample = ResidentModelsBodge();
			else if (car_model > 2)
				sample = car_model - 1;
			else
				sample = car_model;

			if (i == 0) 
			{
				channel = 1;
				pitch = 16383;
			}
			else 
			{
				channel = 4;
				pitch = 129;
			}

			Start3DSoundVolPitch(channel, 3, sample * 3 + 1, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -10000, pitch);

			if (car_model == 4)
				sample = ResidentModelsBodge() * 3;
			else if (car_model < 3)
				sample = car_model * 3;
			else
				sample = (car_model - 1) * 3;

			if (i == 0)
			{
				channel = 0;
				pitch = 16383;
			}
			else 
			{
				channel = 3;
				pitch = 129;
			}

			Start3DSoundVolPitch(channel, 3, sample, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -10000, pitch);

			siren = CarHasSiren(car_model);

			if (siren != 0)
			{
				if (i != 0)
					channel = 5;
				else
					channel = 2;

				Start3DSoundVolPitch(channel, (siren & 0xff00) >> 8, siren & 0xff, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -10000, 129);
			}

			if (NumPlayers > 1 && NoPlayerControl == 0)
			{
				if (i != 0)
					channel = 3;
				else
					channel = 0;

				SetPlayerOwnsChannel(channel, i);
				
				if (i != 0)
					channel = 4;
				else
					channel = 1;

				SetPlayerOwnsChannel(channel, i);
				
				if (i != 0)
					channel = 5;
				else
					channel = 2;

				SetPlayerOwnsChannel(channel, i);
			}
		}
	
		lcp->crash_timer = 0;

		lcp->revsvol = -10000;
		lcp->idlevol = -8000;
		lcp++;
		i++;
	}
	
	if (NumPlayers == 1)
	{
		SpuSetVoiceAR(2, 27);
		SpuSetVoiceAR(5, 27);
	}

	if (NumPlayers < 2 || NoPlayerControl != 0)
	{
		InitEnvSnd(32);
		AddEnvSounds(GameLevel, gTimeOfDay);
	}

	InitDopplerSFX();
	InitSkidding();

	AddTunnels(GameLevel);
	
	first_offence = 1;

	InitializeMissionSound();
}

// decompiled code
// original method signature: 
// unsigned short /*$ra*/ GetEngineRevs(struct _CAR_DATA *cp /*$t2*/)
 // line 404, offset 0x0004e188
	/* begin block 1 */
		// Start line: 405
		// Start offset: 0x0004E188
		// Variables:
	// 		int gear; // $a1
	// 		int lastgear; // $a0
	// 		int ws; // $a2
	// 		int acc; // $t1
	// 		int type; // $t0
	/* end block 1 */
	// End offset: 0x0004E2E8
	// End Line: 439

	/* begin block 2 */
		// Start line: 820
	/* end block 2 */
	// End Line: 821

	/* begin block 3 */
		// Start line: 861
	/* end block 3 */
	// End Line: 862

/* WARNING: Removing unreachable block (ram,0x0004e1b0) */

// [D] [T]
ushort GetEngineRevs(_CAR_DATA* cp)
{
	int acc;
	GEAR_DESC* gd;
	int gear;
	int lastgear;
	int ws, lws;
	int type;

	gear = cp->hd.gear;
	ws = cp->hd.wheel_speed;
	acc = cp->thrust;
	type = (cp->controlType == CONTROL_TYPE_CIV_AI);

	if (ws < 1)
	{
		ws = -ws / 2048;
		lastgear = 0;

		cp->hd.gear = 0;
	}
	else
	{
		ws >>= 11;

		if (gear > 3)
			gear = 3;

		gd = &geard[type][gear];

		do {
			if (acc < 1)
				lws = gd->lowidl_ws;
			else
				lws = gd->low_ws;

			lastgear = gear;
	
			if (ws < lws)
			{
				gd--;
				lastgear = gear - 1;
			}

			if (gd->hi_ws < ws)
			{
				gd++;
				lastgear++;
			}

			if (gear == lastgear)
				break;
	
			gear = lastgear;
			
		} while (true);

		cp->hd.gear = lastgear;
	}

	if (acc != 0)
		return ws * geard[type][lastgear].ratio_ac;

	return ws * geard[type][lastgear].ratio_id;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlCarRevs(struct _CAR_DATA *cp /*$s0*/)
 // line 458, offset 0x0004e2e8
	/* begin block 1 */
		// Start line: 459
		// Start offset: 0x0004E2E8
		// Variables:
	// 		unsigned short oldRevs; // $s2
	// 		unsigned short desiredRevs; // $v1
	// 		unsigned short newRevs; // $a0
	// 		int acc; // $s3
	// 		char spin; // $s4
	// 		char player_id; // $s1

		/* begin block 1.1 */
			// Start line: 498
			// Start offset: 0x0004E414
			// Variables:
		// 		int revsmax; // $a3
		/* end block 1.1 */
		// End offset: 0x0004E4D4
		// End Line: 504
	/* end block 1 */
	// End offset: 0x0004E560
	// End Line: 513

	/* begin block 2 */
		// Start line: 954
	/* end block 2 */
	// End Line: 955

	/* begin block 3 */
		// Start line: 974
	/* end block 3 */
	// End Line: 975

const int maxrevdrop = 1440;
const int maxrevrise = 1600;

// [D] [T]
void ControlCarRevs(_CAR_DATA* cp)
{
	char spin;
	int player_id, acc, oldvol;
	short oldRevs, newRevs, desiredRevs;

	acc = cp->thrust;
	spin = cp->wheelspin;
	oldRevs = cp->hd.revs;
	player_id = GetPlayerId(cp);

	cp->hd.changingGear = 0;

	if (spin == 0 && (cp->hd.wheel[1].susCompression || cp->hd.wheel[3].susCompression || acc == 0))
	{
		desiredRevs = GetEngineRevs(cp);
	}
	else
	{
		desiredRevs = 20160;

		if (cp->hd.wheel[1].susCompression == 0 && cp->hd.wheel[3].susCompression == 0)
		{
			desiredRevs = 30719;
			spin = 1;
		}

		if (oldRevs < 8000)
			oldRevs = 8000;

		cp->hd.gear = 0;
	}

	newRevs = desiredRevs;
	desiredRevs = (oldRevs - newRevs);

	if (maxrevdrop < desiredRevs)
	{
		acc = 0;
		cp->hd.changingGear = 1;
		newRevs = oldRevs - maxrevdrop;
	}

	desiredRevs = newRevs - oldRevs;

	if (maxrevrise < desiredRevs)
		newRevs = oldRevs + maxrevrise;

	cp->hd.revs = newRevs;
	if (player_id != -1)
	{
		if (acc == 0 && newRevs < 7001)
		{
			acc = player[player_id].revsvol;

			player[player_id].idlevol += 200;
			player[player_id].revsvol = acc - 200;

			if (player[player_id].idlevol > -6000)
				player[player_id].idlevol = -6000;

			if (player[player_id].revsvol < -10000)
				player[player_id].revsvol = -10000;
		}
		else
		{
			int revsmax;
	
			if (acc != 0)
				revsmax = -5500;
			else
				revsmax = -6750;

			if (spin == 0)
				acc = -64;
			else
				acc = -256;

			player[player_id].idlevol += acc;

			if (spin == 0)
				acc = 175;
			else
				acc = 700;

			player[player_id].revsvol = player[player_id].revsvol + acc;

			if (player[player_id].idlevol < -10000)
				player[player_id].idlevol = -10000;

			if (player[player_id].revsvol > revsmax)
				player[player_id].revsvol = revsmax;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoSpeech(int chan /*$a0*/, int sound /*$a2*/)
 // line 515, offset 0x000525f8
	/* begin block 1 */
		// Start line: 4824
	/* end block 1 */
	// End Line: 4825

	/* begin block 2 */
		// Start line: 5121
	/* end block 2 */
	// End Line: 5122

// [D] [T]
void DoSpeech(int chan, int sound)
{
	if (sound >= 100)
		StartSound(chan, 5, sound - 100, 0, 4096);
	else if (sound != 0)
		StartSound(chan, 2, sound, - 1500, 4096);
}



// decompiled code
// original method signature: 
// char /*$ra*/ PlaySpeech(struct SPEECH_QUEUE *pSpeechQueue /*$a0*/, int sound /*$a1*/)
 // line 562, offset 0x0005228c
	/* begin block 1 */
		// Start line: 563
		// Start offset: 0x0005228C
		// Variables:
	// 		char result; // $v0
	// 		int i; // $a2
	/* end block 1 */
	// End offset: 0x000522EC
	// End Line: 583

	/* begin block 2 */
		// Start line: 1124
	/* end block 2 */
	// End Line: 1125

	/* begin block 3 */
		// Start line: 3271
	/* end block 3 */
	// End Line: 3272

// [D] [T]
char PlaySpeech(SPEECH_QUEUE* pSpeechQueue, int sound)
{
	int i;

	if (pSpeechQueue->count >= 7)
		return 0;

	i = pSpeechQueue->count - 1;

	while (i >= 0)
	{
		pSpeechQueue->slot[i+1] = pSpeechQueue->slot[i];
		i--;
	}

	pSpeechQueue->slot[0] = sound;
	pSpeechQueue->count++;

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSpeechQueue(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
 // line 587, offset 0x00052654
	/* begin block 1 */
		// Start line: 5265
	/* end block 1 */
	// End Line: 5266

// [D] [T]
void InitSpeechQueue(SPEECH_QUEUE* pSpeechQueue)
{
	ClearMem((char*)pSpeechQueue, sizeof(SPEECH_QUEUE));

	if (GameType != GAME_MISSION)
		pSpeechQueue->allowed = 2;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlSpeech(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
 // line 595, offset 0x0004e560
	/* begin block 1 */
		// Start line: 596
		// Start offset: 0x0004E560
	/* end block 1 */
	// End offset: 0x0004E700
	// End Line: 635

	/* begin block 2 */
		// Start line: 1169
	/* end block 2 */
	// End Line: 1170

	/* begin block 3 */
		// Start line: 1252
	/* end block 3 */
	// End Line: 1253

	/* begin block 4 */
		// Start line: 1257
	/* end block 4 */
	// End Line: 1258

// [D] [T]
void ControlSpeech(SPEECH_QUEUE* pSpeechQueue)
{
	if (GameType == GAME_MISSION)
	{		
		if (bMissionTitleFade == 0)
		{
			if (pSpeechQueue->allowed == 1)
				pSpeechQueue->allowed = 2;
		}
		else
			pSpeechQueue->allowed = 1;

		if (pSpeechQueue->allowed != 2)
			return;
	}

	if (pSpeechQueue->count < 1)
	{
		TimeSinceLastSpeech++;

		if (pSpeechQueue->is_playing != 0 && SpuGetKeyStatus(SPU_VOICECH(pSpeechQueue->chan)) == 0)
		{
			SetReverbChannelState(pSpeechQueue->chan, pSpeechQueue->reverb);
			UnlockChannel(pSpeechQueue->chan);

			pSpeechQueue->is_playing = 0;
		}
	}
	else if (pSpeechQueue->is_playing == 0)
	{
		pSpeechQueue->chan = GetFreeChannel();

		LockChannel(pSpeechQueue->chan);

		pSpeechQueue->reverb = SetReverbChannelState(pSpeechQueue->chan, 0);
		pSpeechQueue->is_playing = 1;

		channels[pSpeechQueue->chan].time = 0;

		pSpeechQueue->count--;

		DoSpeech(pSpeechQueue->chan, pSpeechQueue->slot[pSpeechQueue->count]);
	}
	else if (SpuGetKeyStatus(SPU_VOICECH(pSpeechQueue->chan)) == 0)
	{
		pSpeechQueue->count--;

		DoSpeech(pSpeechQueue->chan, pSpeechQueue->slot[pSpeechQueue->count]);
	}

	TimeSinceLastSpeech = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CopSay(int phrase /*$s1*/, int direction /*$s2*/)
 // line 665, offset 0x00052190
	/* begin block 1 */
		// Start line: 3366
	/* end block 1 */
	// End Line: 3367

	/* begin block 2 */
		// Start line: 1330
	/* end block 2 */
	// End Line: 1331

// [D]
void CopSay(int phrase, int direction)
{
	if (gCurrentMissionNumber == 7 || gCurrentMissionNumber == 9 || gCurrentMissionNumber == 11 || 
		gCurrentMissionNumber == 20 || gCurrentMissionNumber == 26 || gCurrentMissionNumber == 31 || 
		gCurrentMissionNumber == 33 || gCurrentMissionNumber == 40)
		return;

	PlaySpeech(&gSpeechQueue, phrase);

	if (phrase == 10)
	{
		if (cop_bank == 1)
			return;

		if (cop_bank != 2 && cop_bank != 3)
			return;
	}
	else
	{
		if (phrase != 15)
			return;

		if (cop_bank != 4)
			return;
	}

	PlaySpeech(&gSpeechQueue, direction + 1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ BodSay(int phrase /*$a1*/)
 // line 677, offset 0x00052694
	/* begin block 1 */
		// Start line: 5445
	/* end block 1 */
	// End Line: 5446

// [D] [T]
void BodSay(int phrase)
{
	if (phrase_top != 0 && phrase < phrase_top)
		PlaySpeech(&gSpeechQueue, phrase + 100);
}



// decompiled code
// original method signature: 
// void /*$ra*/ MissionSay(int phrase /*$a0*/)
 // line 686, offset 0x000526d0
	/* begin block 1 */
		// Start line: 687
		// Start offset: 0x000526D0
	/* end block 1 */
	// End offset: 0x000526FC
	// End Line: 691

	/* begin block 2 */
		// Start line: 5463
	/* end block 2 */
	// End Line: 5464

// [D] [T]
void MissionSay(int phrase)
{
	phrase = GetMissionSound(phrase);

	if (phrase != -1)
		PlaySpeech(&gSpeechQueue, phrase + 100);
}



// decompiled code
// original method signature: 
// long /*$ra*/ jsqrt(unsigned long a /*$a0*/)
 // line 700, offset 0x0005270c
	/* begin block 1 */
		// Start line: 701
		// Start offset: 0x0005270C
		// Variables:
	// 		long b1; // $a1
	// 		long b0; // $v1
	/* end block 1 */
	// End offset: 0x000527C0
	// End Line: 713

	/* begin block 2 */
		// Start line: 5491
	/* end block 2 */
	// End Line: 5492

	/* begin block 3 */
		// Start line: 5494
	/* end block 3 */
	// End Line: 5495

// [D] [T]
long jsqrt(ulong a)
{
	long b0;
	long b1;

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
	}
	while (true);

	return b1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitDopplerSFX()
 // line 721, offset 0x0004e710
	/* begin block 1 */
		// Start line: 722
		// Start offset: 0x0004E710
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x0004E790
	// End Line: 726

	/* begin block 2 */
		// Start line: 1510
	/* end block 2 */
	// End Line: 1511

	/* begin block 3 */
		// Start line: 1511
	/* end block 3 */
	// End Line: 1512

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitDopplerSFX(void)
{
	int i;

	i = 0;
	do {
		siren_noise[i].chan = -1;
		siren_noise[i].car = 20;
		siren_noise[i].in_use = 0;
		i++;
	} while (i < 2);

	i = 0;
	do {
		car_noise[i].chan = -1;
		car_noise[i].chan = -1;
		car_noise[i].car = 20;
		car_noise[i].in_use = 0;
		i++;
	} while (i < 4);

	if (GameType == GAME_GETAWAY)
		loudhail_time = 245;
	else
		loudhail_time = 75;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoDopplerSFX()
 // line 734, offset 0x0004e790
	/* begin block 1 */
		// Start line: 735
		// Start offset: 0x0004E790
		// Variables:
	// 		int i; // $s1
	// 		int j; // $s0
	// 		int num_noisy_cars; // $s5
	// 		unsigned long car_dist[20]; // stack offset -176
	// 		unsigned short indexlist[20]; // stack offset -96
	// 		struct _CAR_DATA *car_ptr; // $s2
	// 		struct VECTOR *pp; // $a1
	// 		unsigned long car_flags; // $s4
	// 		char sirens; // stack offset -56

		/* begin block 1.1 */
			// Start line: 825
			// Start offset: 0x0004ECB8
			// Variables:
		// 		int siren; // $v0
		/* end block 1.1 */
		// End offset: 0x0004EDC8
		// End Line: 842

		/* begin block 1.2 */
			// Start line: 890
			// Start offset: 0x0004F09C
			// Variables:
		// 		int model; // $v1
		/* end block 1.2 */
		// End offset: 0x0004F134
		// End Line: 892

		/* begin block 1.3 */
			// Start line: 909
			// Start offset: 0x0004F1BC
			// Variables:
		// 		char old_idle; // $a1

			/* begin block 1.3.1 */
				// Start line: 914
				// Start offset: 0x0004F240
				// Variables:
			// 		int model; // $v1
			/* end block 1.3.1 */
			// End offset: 0x0004F314
			// End Line: 924
		/* end block 1.3 */
		// End offset: 0x0004F368
		// End Line: 929
	/* end block 1 */
	// End offset: 0x0004F4A0
	// End Line: 944

	/* begin block 2 */
		// Start line: 1527
	/* end block 2 */
	// End Line: 1528

	/* begin block 3 */
		// Start line: 1536
	/* end block 3 */
	// End Line: 1537

/* WARNING: Unknown calling convention yet parameter storage is locked */

char force_idle[8] = { 0 };
char force_siren[8] = { 0 };

// [D]
void DoDopplerSFX(void)
{
	int pitch, volume, sample;
	short* playerFelony;
	ushort* puVar7;
	int vvar3;
	int vvar4;
	int i, j, count;
	int car;
	uint car_flags;
	uint _car_flags;
	int num_noisy_cars;
	int sirens;

	ulong car_dist[MAX_CARS];
	ushort indexlist[MAX_CARS];
	
	_CAR_DATA* car_ptr;
	int dx, dz;
	ulong dist;

	num_noisy_cars = 0;

	// collect sounding cars and estimate their distance to camera
	for (i = 0; i < MAX_CARS; i++)
	{
		car_ptr = &car_data[i];

		dx = car_ptr->hd.where.t[0] - camera_position.vx;
		dz = car_ptr->hd.where.t[2] - camera_position.vz;
	
		if (ABS(dx) < 16384 && ABS(dz) < 16384)
		{
			if (car_ptr->controlType == CONTROL_TYPE_CIV_AI && car_ptr->ai.c.ctrlState != 5 && car_ptr->ai.c.ctrlState != 7)
			{
				dist = jsqrt(dx * dx + dz * dz) + 0x6000;
			}
			else if (car_ptr->controlType == CONTROL_TYPE_PURSUER_AI ||
				car_ptr->controlType == CONTROL_TYPE_LEAD_AI ||
				car_ptr->controlType == CONTROL_TYPE_CUTSCENE && SilenceThisCar(i) == 0)
			{
				dist = jsqrt(dx * dx + dz * dz);
			}
			else
				continue;

			indexlist[num_noisy_cars] = i;
			car_dist[i] = dist;
			num_noisy_cars++;
		}
	}

	// sort cars by distance distance
	i = 0;
	while (i < num_noisy_cars-1)
	{
		j = i + 1;
		while (j < num_noisy_cars)
		{
			int tmpi;
			tmpi = indexlist[i];
			
			if (car_dist[indexlist[j]] < car_dist[tmpi])
			{
				indexlist[i] = indexlist[j];
				indexlist[j] = tmpi;
			}

			j++;
		}

		i++;
	}

	car_flags = 0;
	sirens = 0;

	// collect cop cars for siren sound
	for(i = 0; i < num_noisy_cars && sirens < 2; i++)
	{
		int siren;
		car_ptr = &car_data[indexlist[i]];

		siren = 0;
		
		if (handlingType[car_ptr->hndType].fourWheelDrive == 1 &&
			car_ptr->controlType == CONTROL_TYPE_PURSUER_AI && car_ptr->ai.p.dying < 75 &&
			CarHasSiren(car_ptr->ap.model) != 0)
		{
			siren = 1;
		}

		// vegas ambulance
		if (gCurrentMissionNumber == 26)
		{
			if (car_ptr->ap.model == 4 && car_ptr->controlType == CONTROL_TYPE_CUTSCENE)
			{
				siren = 1;
			}
		}

		// any cutscene cop car or car with forced siren
		if (gInGameCutsceneActive != 0 && car_ptr->controlType == CONTROL_TYPE_CUTSCENE && force_siren[indexlist[i]] != 0)
		{
			siren = 1;
		}

		// play car music
		if (gCurrentMissionNumber != 7 && car_ptr->controlType == CONTROL_TYPE_CIV_AI && car_ptr->ap.model <= 2 && indexlist[i] == 1)
		{
			siren = 1;
		}

		if (!siren)
			continue;

		car_flags |= 1 << indexlist[i];

		if (gInGameCutsceneActive == 0)
			sirens++;
	}

	// stop old siren noises
	for (i = 0; i < 2; i++)
	{
		int siren;
		siren = (car_flags & 1 << siren_noise[i].car) != 0;
		
		siren_noise[i].in_use = siren;
		car_flags &= ~(siren << siren_noise[i].car);

		if (siren == 0 && siren_noise[i].stopped == 0)
		{
			StopChannel(siren_noise[i].chan);
			UnlockChannel(siren_noise[i].chan);

			siren_noise[i].chan = -1;
			siren_noise[i].car = 20;
			siren_noise[i].stopped = 1;
		}
	}

#if 0
	for(i = 0; i < num_noisy_cars; i++)
	{
		if(car_flags & 1 << indexlist[i])
		{
			car = indexlist[i];
					
			// dispatch siren sounds
			for (j = 0; j < 2; j++)
			{
				if (siren_noise[j].in_use != 0)
					continue;
				
				siren_noise[j].in_use = 1;
				siren_noise[j].stopped = 0;
				siren_noise[j].car = car;

				if (gCurrentMissionNumber == 26 || car_data[car].controlType != CONTROL_TYPE_CIV_AI)
				{
					int siren;
					siren = CarHasSiren(car_data[car].ap.model);

					siren_noise[j].chan = Start3DTrackingSound(-1, (siren & 0xff00) >> 8, siren & 0xff, 
					                                           (VECTOR*)car_data[car].hd.where.t, 
					                                           car_data[car].st.n.linearVelocity);
				}
				else
				{
					// play music
					siren_noise[j].chan = Start3DTrackingSound(-1, 4, 5, 
					                                           (VECTOR*)car_data[car].hd.where.t, 
					                                           car_data[car].st.n.linearVelocity);
				}

				LockChannel(siren_noise[j].chan);
			}
		}
	}

	// update siren positions
	for (j = 0; j < 2; j++)
	{
		if (siren_noise[j].in_use == 0)
			continue;

		car = siren_noise[j].car;

		if (car_data[car].controlType == CONTROL_TYPE_PURSUER_AI)
			pitch = car_data[car].ai.p.dying;
		else
			pitch = 0;

		SetChannelPosition3(siren_noise[j].chan, 
		                    (VECTOR*)car_data[car].hd.where.t, 
		                    car_data[car].st.n.linearVelocity, 
		                    pitch * -30 - 3000, j * 4 - (pitch * 48 - 4096), 0);
	}
	
	
	{
		if (num_noisy_cars > (4 - sirens))
			num_noisy_cars = 4 - sirens;
		else
			num_noisy_cars = num_noisy_cars;

		car_flags = 0;

		for (j = 0; j < num_noisy_cars; j++)
		{
			car = indexlist[j];

			if (car_data[car].controlType != CONTROL_TYPE_PURSUER_AI || car_data[car].ai.p.dying == 0)
				car_flags |= 1 << car;
		}

		for (j = 0; j < 4; j++)
		{
			int noise;

			noise = (car_flags & (1 << car_noise[j].car)) != 0;
			car_noise[j].in_use = noise;

			car_flags &= ~(noise << car_noise[j].car);
		}

		for (j = 0; j < 4; j++)
		{
			if (car_noise[j].in_use == 0 && car_noise[j].stopped == 0)
			{
				StopChannel(car_noise[j].chan);
				UnlockChannel(car_noise[j].chan);

				car_noise[j].chan = -1;
				car_noise[j].car = 20;
				car_noise[j].stopped = 1;
			}
		}

		// start new sound
		// pick free car noise slot and play
		for(i = 0; i < num_noisy_cars; i++)
		{
			if (car_flags & 1 << indexlist[i])
			{
				car = indexlist[i];
				for (j = 0; j < 4; j++)
				{
					int bank, model;

					if (car_noise[j].in_use)
						continue;

					car_noise[j].in_use = 1;
					car_noise[j].stopped = 0;
					car_noise[j].car = car;

					// determine which sound type it has to play
					if (gInGameCutsceneActive != 0 && force_idle[car] > -1)
						car_noise[j].idle = force_idle[car];
					else
						car_noise[j].idle = (car_data[car].hd.speed < 17);

					model = car_data[car].ap.model;

					if (model == 3)
						model = cop_model;

					// get bank id
					if (model == 4)
						bank = ResidentModelsBodge();
					else if (model < 3)
						bank = model;
					else
						bank = model - 1;

					if (car_noise[j].idle)
						sample = bank * 3 + 1;
					else
						sample = bank * 3;

					car_noise[j].chan = Start3DTrackingSound(-1, 3, sample, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity);

					LockChannel(car_noise[j].chan);
				}
			}
		}
	}

	for (j = 0; j < 4; j++)
	{
		char old_idle;

		if (car_noise[j].in_use == 0)
			continue;

		car = car_noise[j].car;
		old_idle = car_noise[j].idle;

		// determine which sound type it has to play
		if (gInGameCutsceneActive != 0 && force_idle[car] > -1)
			car_noise[j].idle = force_idle[car];
		else
			car_noise[j].idle = (car_data[car].hd.speed < 17);

		// restart sound if it's changed
		if (old_idle != car_noise[j].idle)
		{
			int bank, model;

			StopChannel(car_noise[j].chan);
			UnlockChannel(car_noise[j].chan);

			model = car_data[car].ap.model;

			if (model == 3)
				model = cop_model;

			// get bank id
			if (model == 4)
				bank = ResidentModelsBodge();
			else if (model < 3)
				bank = model;
			else
				bank = model - 1;

			if (car_noise[j].idle)
				sample = bank * 3 + 1;
			else
				sample = bank * 3;

			car_noise[j].chan = Start3DTrackingSound(-1, 3, sample, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity);
			LockChannel(car_noise[j].chan);
		}

		if (car_data[car].controlType == CONTROL_TYPE_CIV_AI)
			volume = -7000;
		else
			volume = -6250;

		pitch = (car_data[car].hd.revs << 0x10) >> 0x12;

		if (car_noise[j].idle != 0)
			pitch += 4096;
		else
			pitch += 1500;

		car_noise[j].in_use = 1;

		SetChannelPosition3(car_noise[j].chan, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity, volume, pitch, 0);
	}

	// bark on player
	if (CopsCanSeePlayer != 0)
	{
		if (player[0].playerCarId < 0)
			playerFelony = &pedestrianFelony;
		else
			playerFelony = &car_data[player[0].playerCarId].felonyRating;
		
		if (*playerFelony > FELONY_MIN_VALUE)
			DoPoliceLoudhailer(num_noisy_cars, indexlist, car_dist);
	}

	// update each sound channel with new info
	for (j = 0; j < 16; j++)
	{
		if (channels[j].loop == 0 && channels[j].time != 0 && channels[j].srcposition != NULL)
		{
			SetChannelPosition3(j,
				channels[j].srcposition, channels[j].srcvelocity,
				channels[j].srcvolume, channels[j].srcpitch, 0);
		}
	}
	
#else
	// PLS HELP ME this is even more confusing than GetNextRoadInfo...
	vvar4 = 0;
	do {
		do {

			if (num_noisy_cars < 3)
				vvar3 = num_noisy_cars;
			else
				vvar3 = 2;

			if (vvar4 < vvar3)
			{
				puVar7 = indexlist + vvar4;
				vvar4++;
				continue;
			}
	
			{
				for (j = 0; j < 2; j++)
				{
					if (siren_noise[j].in_use != 0)
					{
						car = siren_noise[j].car;
	
						if (car_data[car].controlType == CONTROL_TYPE_PURSUER_AI)
							pitch = (uint)car_data[car].ai.p.dying;
						else
							pitch = 0;

						SetChannelPosition3(siren_noise[j].chan, 
                                            (VECTOR*)car_data[car].hd.where.t, 
                                            car_data[car].st.n.linearVelocity, 
                                            pitch * -30 - 3000, j * 4 - (pitch * 48 - 4096), 0);
					}
				}
				
				if (num_noisy_cars > (4 - sirens))
					count = 4 - sirens;
				else
					count = num_noisy_cars;

				_car_flags = 0;
				
				for (j = 0; j < count; j++)
				{
					car = indexlist[j];

					if (car_data[car].controlType != CONTROL_TYPE_PURSUER_AI || car_data[car].ai.p.dying == 0)
						_car_flags |= 1 << car;
				}

				for (j = 0; j < 4; j++)
				{
					int noise;
					
					noise = (_car_flags & (1 << car_noise[j].car)) != 0;
					car_noise[j].in_use = noise;

					_car_flags &= ~(noise << car_noise[j].car);
				}

				for (j = 0; j < 4; j++)
				{
					if (car_noise[j].in_use == 0 && car_noise[j].stopped == 0)
					{
						StopChannel(car_noise[j].chan);
						UnlockChannel(car_noise[j].chan);

						car_noise[j].chan = -1;
						car_noise[j].car = 20;
						car_noise[j].stopped = 1;
					}
				}
			}

			vvar4 = 0;
			do {
				{
					do {
						
						if (num_noisy_cars < 5)
							vvar3 = num_noisy_cars;
						else
							vvar3 = 4;

						if (vvar4 < vvar3)
						{
							puVar7 = indexlist + vvar4;
							vvar4++;
							continue;
						}
					
						{
							for (j = 0; j < 4; j++)
							{
								char old_idle;
								
								if (car_noise[j].in_use == 0)
									continue;
									
								car = car_noise[j].car;
								old_idle = car_noise[j].idle;

								// determine which sound type it has to play
								if (gInGameCutsceneActive != 0 && force_idle[car] > -1)
									car_noise[j].idle = force_idle[car];
								else
									car_noise[j].idle = (car_data[car].hd.speed < 17);

								// restart sound if it's changed
								if (old_idle != car_noise[j].idle)
								{
									int bank, model;

									StopChannel(car_noise[j].chan);
									UnlockChannel(car_noise[j].chan);

									model = car_data[car].ap.model;

									if (model == 3)
										model = cop_model;

									// get bank id
									if (model == 4)
										bank = ResidentModelsBodge();
									else if (model < 3)
										bank = model;
									else
										bank = model - 1;

									if (car_noise[j].idle)
										sample = bank * 3 + 1;
									else
										sample = bank * 3;

									car_noise[j].chan = Start3DTrackingSound(-1, 3, sample, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity);
									LockChannel(car_noise[j].chan);
								}

								if (car_data[car].controlType == CONTROL_TYPE_CIV_AI)
									volume = -7000;
								else
									volume = -6250;

								pitch = (car_data[car].hd.revs << 0x10) >> 0x12;

								if (car_noise[j].idle != 0)
									pitch += 4096;
								else
									pitch += 1500;

								car_noise[j].in_use = 1;
								
								SetChannelPosition3(car_noise[j].chan, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity, volume, pitch, 0);
							}

							// bark on player
							if (CopsCanSeePlayer != 0)
							{
								if (player[0].playerCarId < 0)
									playerFelony = &pedestrianFelony;
								else
									playerFelony = &car_data[player[0].playerCarId].felonyRating;
								
								if (*playerFelony > FELONY_MIN_VALUE)
									DoPoliceLoudhailer(num_noisy_cars, indexlist, car_dist);
							}

							// update each sound channel with new info
							for (j = 0; j < 16; j++)
							{
								if (channels[j].loop == 0 && channels[j].time != 0 && channels[j].srcposition != NULL)
								{
									SetChannelPosition3(j,
                                                        channels[j].srcposition, channels[j].srcvelocity,
                                                        channels[j].srcvolume, channels[j].srcpitch, 0);
								}
							}
						}

						return;
					} while ((_car_flags & 1 << ((uint)*puVar7 & 0x1f)) == 0);

					car = *puVar7;

					// start new sound
					// pick free car noise slot and play
					for (j = 0; j < 4; j++)
					{
						int bank, model;
						
						if (car_noise[j].in_use)
							continue;

						car_noise[j].in_use = 1;
						car_noise[j].stopped = 0;
						car_noise[j].car = car;

						// determine which sound type it has to play
						if (gInGameCutsceneActive != 0 && force_idle[car] > -1)
							car_noise[j].idle = force_idle[car];
						else
							car_noise[j].idle = (car_data[car].hd.speed < 17);

						model = car_data[car].ap.model;

						if (model == 3)
							model = cop_model;

						// get bank id
						if (model == 4)
							bank = ResidentModelsBodge();
						else if (model < 3)
							bank = model;
						else
							bank = model - 1;

						if (car_noise[j].idle)
							sample = bank * 3 + 1;
						else
							sample = bank * 3;

						car_noise[j].chan = Start3DTrackingSound(-1, 3, sample, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity);
						
						LockChannel(car_noise[j].chan);
						
						break;
					}
				}

			} while (true);
		} while ((car_flags & 1 << ((uint)*puVar7 & 0x1f)) == 0);

		// dispatch siren sounds
		j = 0;
		do {
			if (siren_noise[j].in_use == 0)
			{
				siren_noise[j].in_use = 1;
				siren_noise[j].stopped = 0;
				siren_noise[j].car = *puVar7;

				if (gCurrentMissionNumber == 26 || car_data[siren_noise[j].car].controlType != CONTROL_TYPE_CIV_AI)
				{
					int siren;
					siren = CarHasSiren(car_data[siren_noise[j].car].ap.model);
					
					siren_noise[j].chan = Start3DTrackingSound(-1, (siren & 0xff00) >> 8, siren & 0xff, 
																(VECTOR*)car_data[siren_noise[j].car].hd.where.t, 
																car_data[siren_noise[j].car].st.n.linearVelocity);
				}
				else
				{
					// play music
					siren_noise[j].chan = Start3DTrackingSound(-1, 4, 5, 
																(VECTOR*)car_data[siren_noise[j].car].hd.where.t, 
																car_data[siren_noise[j].car].st.n.linearVelocity);
				}

				LockChannel(siren_noise[j].chan);
				break;
			}

			j++;
		} while (j < 2);

	} while (true);
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoPoliceLoudhailer(int cars /*$s1*/, unsigned short *indexlist /*$s2*/, unsigned long *dist /*$s3*/)
 // line 946, offset 0x0004f4a0
	/* begin block 1 */
		// Start line: 947
		// Start offset: 0x0004F4A0
		// Variables:
	// 		int i; // $t1
	// 		int rnd; // $t0
	// 		int time; // $s0

		/* begin block 1.1 */
			// Start line: 951
			// Start offset: 0x0004F560
			// Variables:
		// 		struct _CAR_DATA *car_ptr; // $a3
		/* end block 1.1 */
		// End offset: 0x0004F624
		// End Line: 959
	/* end block 1 */
	// End offset: 0x0004F64C
	// End Line: 962

	/* begin block 2 */
		// Start line: 2215
	/* end block 2 */
	// End Line: 2216

	/* begin block 3 */
		// Start line: 2218
	/* end block 3 */
	// End Line: 2219

// [D]
void DoPoliceLoudhailer(int cars, ushort* indexlist, ulong* dist)
{
	long lVar1;
	uint uVar2;
	uint uVar3;
	int iVar4;
	int iVar5;

	lVar1 = Random2(0x4e);
	iVar5 = 275;

	if (GameType == GAME_GETAWAY)
		iVar5 = 475;

	if (gCurrentMissionNumber != 7 && gCurrentMissionNumber != 9 &&
		gCurrentMissionNumber != 11 && gCurrentMissionNumber != 20 &&
		gCurrentMissionNumber != 26 && gCurrentMissionNumber != 31 &&
		gCurrentMissionNumber != 33 && gCurrentMissionNumber != 0x28)
	{
		iVar4 = 0;

		if (0 < cars)
		{
			do {
				uVar2 = (uint)*indexlist;
				uVar3 = dist[uVar2];

				if (0x6000 < uVar3)
					dist[uVar2] = uVar3 - 0x6000;

				if (car_data[uVar2].controlType == CONTROL_TYPE_PURSUER_AI && car_data[uVar2].ai.p.dying == 0 && iVar5 < loudhail_time && lVar1 == (lVar1 / 31) * 31)
				{
					Start3DTrackingSound(-1, 2, lVar1 % 2 + 13, (VECTOR*)car_data[uVar2].hd.where.t, car_data[uVar2].st.n.linearVelocity);
					loudhail_time = 0;
					break;
				}

				iVar4++;
				indexlist++;
			} while (iVar4 < cars);
		}

		if (loudhail_time <= iVar5)
			loudhail_time++;

	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CollisionSound(char player_id /*$s0*/, struct _CAR_DATA *cp /*$s5*/, int impact /*$s2*/, int car_car /*$s7*/)
 // line 975, offset 0x0004f668
	/* begin block 1 */
		// Start line: 976
		// Start offset: 0x0004F668
		// Variables:
	// 		long *here; // $s3
	// 		char chan; // $s1
	// 		char crash; // $s6
	// 		char size; // $s4

		/* begin block 1.1 */
			// Start line: 983
			// Start offset: 0x0004F6F0
			// Variables:
		// 		unsigned long p0dst; // $a1
		// 		unsigned long p1dst; // $a0
		/* end block 1.1 */
		// End offset: 0x0004F6F0
		// End Line: 984

		/* begin block 1.2 */
			// Start line: 993
			// Start offset: 0x0004F784

			/* begin block 1.2.1 */
				// Start line: 1000
				// Start offset: 0x0004F898
			/* end block 1.2.1 */
			// End offset: 0x0004F930
			// End Line: 1007
		/* end block 1.2 */
		// End offset: 0x0004F954
		// End Line: 1011
	/* end block 1 */
	// End offset: 0x0004F954
	// End Line: 1012

	/* begin block 2 */
		// Start line: 2285
	/* end block 2 */
	// End Line: 2286

// [D]
void CollisionSound(char player_id, _CAR_DATA* cp, int impact, int car_car)
{
	int iVar1;
	int chan;
	long lVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int playerid;
	int phrase;
	int sample;

	playerid = player_id < 0 ? 0 : player_id;

	if (impact < 25)
		return;

	if (NumPlayers > 1 && NoPlayerControl == 0)
	{
		iVar5 = cp->hd.where.t[0] - player[0].pos[0];
		iVar6 = cp->hd.where.t[2] - player[0].pos[2];

		iVar4 = cp->hd.where.t[0] - player[1].pos[0];
		iVar1 = cp->hd.where.t[2] - player[1].pos[2];

		playerid = (iVar4 * iVar4 + iVar1 * iVar1) < (iVar5 * iVar5 + iVar6 * iVar6);
	}

	if (player[playerid].crash_timer != 0)
		return;

	sample = 8;
	phrase = 0;

	if (car_car == 0)
	{
		if (impact > 780)
		{
			sample = 10;
			phrase = 1;
		}
		else if (impact > 350)
		{
			sample = 9;
			phrase = 2;
		}
	}
	else
	{
		if (impact > 900)
		{
			sample = 10;
			phrase = 1;
		}
		else if (impact > 380)
		{
			sample = 9;
			phrase = 2;
		}
	}

	chan = GetFreeChannel();

	SetPlayerOwnsChannel(chan, playerid);
	Start3DSoundVolPitch(chan, 1, sample, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2750, impact - (impact / 1024) * 1024 + 3584);

	player[playerid].crash_timer = 2;

	if (GetPlayerId(cp) != 0 ||
		(gCurrentMissionNumber - 2 > 2 && gCurrentMissionNumber != 9 && gCurrentMissionNumber != 10 && gCurrentMissionNumber != 27 || (impact & 5) == 0))
		return;

	lVar3 = Random2(1);

	if (lVar3 == (lVar3 / 3) * 3)
	{
		phrase |= 4;
	}
	else
	{
		if (car_car != 2)
		{
			if (phrase != 0)
			{
				phrase = Random2(1);
				sample = 0;

				if ((phrase & 1) == 0)
					sample = 3;

				BodSay(sample);
			}

			return;
		}

		if (phrase == 0)
			return;

		phrase = 2;

		if ((Random2(1) & 1) != 0)
			phrase = 1;
	}

	BodSay(phrase);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ExplosionSound(struct VECTOR *pos /*$s4*/, int type /*$s0*/)
 // line 1019, offset 0x0004f984
	/* begin block 1 */
		// Start line: 1020
		// Start offset: 0x0004F984
		// Variables:
	// 		int bang; // $s5
	// 		int pitch; // $t0
	// 		int rnd; // $s3
	// 		struct VECTOR P; // stack offset -48
	// 		int sc1; // $s2
	// 		int sc2; // $s1
	/* end block 1 */
	// End offset: 0x0004FB70
	// End Line: 1048

	/* begin block 2 */
		// Start line: 2380
	/* end block 2 */
	// End Line: 2381

// [D]
void ExplosionSound(VECTOR* pos, int type)
{
	char id;
	long lVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int unaff_s1;
	int unaff_s2;
	int sample;
	int iVar5;

	sample = 0xff;
	lVar1 = Random2(4);

	if (gCurrentMissionNumber == 23)
	{
	LAB_0004fa04:
		id = 12;
	LAB_0004fa10:
		id = GetMissionSound(id);
		sample = id;
	}
	else if (gCurrentMissionNumber == 13)
	{
		goto LAB_0004fa04;
	}
	else if (gCurrentMissionNumber == 30 || gCurrentMissionNumber == 35)
	{
		id = 29;
		goto LAB_0004fa10;
	}

	if (sample == 0xff)
		return;

	iVar3 = pos->vx;
	if (type == 1)
	{
		unaff_s2 = 3;
		unaff_s1 = 1;
	}
	else if (type < 2)
	{
		unaff_s2 = 2;
		unaff_s1 = 2;

		iVar5 = iVar3 * unaff_s2;
		if (type != 0)
			goto LAB_0004fab8;

	}
	else
	{
		unaff_s2 = 1;
		unaff_s1 = 3;

		iVar5 = iVar3 * unaff_s2;

		if (type != 0x29a)
			goto LAB_0004fab8;
	}

	iVar5 = iVar3 * unaff_s2;
LAB_0004fab8:
	iVar5 = iVar5 + player[0].cameraPos.vx * unaff_s1;

	iVar4 = pos->vy * unaff_s2 + player[0].cameraPos.vy * unaff_s1;

	iVar2 = pos->vz * unaff_s2 + player[0].cameraPos.vz * unaff_s1;

	Start3DSoundVolPitch(-1, 5, sample, iVar5 >> 2, iVar4 >> 2, iVar2 >> 2, 0, ((FrameCnt * iVar3 ^ lVar1 * pos->vz) & 0x3ffU) + 0xe00);
}



// decompiled code
// original method signature: 
// void /*$ra*/ JerichoSpeak()
 // line 1052, offset 0x0004fb94
	/* begin block 1 */
		// Start line: 1053
		// Start offset: 0x0004FB94
		// Variables:
	// 		static unsigned int j_said; // offset 0x0
	// 		int rnd; // $a1
	/* end block 1 */
	// End offset: 0x0004FC90
	// End Line: 1060

	/* begin block 2 */
		// Start line: 2452
	/* end block 2 */
	// End Line: 2453

	/* begin block 3 */
		// Start line: 2453
	/* end block 3 */
	// End Line: 2454

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [A] - might be incorrect
void JerichoSpeak(void)
{
	static unsigned int j_said = 0;
	uint uVar1;
	long rnd;
	short* psVar3;

	rnd = Random2(3);

	if (CopsCanSeePlayer != 0)
	{
		if (player[0].playerCarId < 0)
			psVar3 = &pedestrianFelony;
		else
			psVar3 = &car_data[player[0].playerCarId].felonyRating;

		if (((*psVar3 > FELONY_MIN_VALUE) && (rnd == (rnd / 5) * 5)))
		{
			if (j_said > 60)
			{
				BodSay(rnd % 3);
				j_said = 0;
			}
			else
				j_said++;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ FunkUpDaBGMTunez(int funk /*$a0*/)
 // line 1085, offset 0x000527c0
	/* begin block 1 */
		// Start line: 5888
	/* end block 1 */
	// End Line: 5889

	/* begin block 2 */
		// Start line: 6261
	/* end block 2 */
	// End Line: 6262

	/* begin block 3 */
		// Start line: 6263
	/* end block 3 */
	// End Line: 6264

static int copmusic = 0;
int current_music_id;

static char header_pt[sizeof(XMHEADER)];
static char song_pt[sizeof(XMSONG)];

// [D]
void FunkUpDaBGMTunez(int funk)
{
	if (funk == 0) {
		if (copmusic != 0)
		{
			copmusic = 0;
			XM_SetSongPos(Song_ID, 0);
		}
	}
	else
	{
		if (copmusic == 0)
		{
			copmusic = 1;
			XM_SetSongPos(Song_ID, xm_coptrackpos[current_music_id]);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SoundTasks()
 // line 1103, offset 0x0004fc90
	/* begin block 1 */
		// Start line: 1104
		// Start offset: 0x0004FC90
		// Variables:
	// 		int i; // $s2
	// 		struct _CAR_DATA *cp; // $s1
	/* end block 1 */
	// End offset: 0x000500E4
	// End Line: 1183

	/* begin block 2 */
		// Start line: 2510
	/* end block 2 */
	// End Line: 2511

	/* begin block 3 */
		// Start line: 2554
	/* end block 3 */
	// End Line: 2555

	/* begin block 4 */
		// Start line: 2558
	/* end block 4 */
	// End Line: 2559

/* WARNING: Unknown calling convention yet parameter storage is locked */

static struct __envsound envsnd[32];
static struct __envsoundinfo ESdata[2];
__tunnelinfo tunnels;

// [D]
void SoundTasks(void)
{
	static struct __envsoundtags EStags;

	int channel;
	int channel_00;
	int uVar1;
	VECTOR* position;
	long* velocity;
	int volume;
	int* piVar2;
	int iVar3;
	int iVar4;
	_PLAYER* pPVar5;

	iVar3 = 0;
	if (NumPlayers != 0)
	{
		pPVar5 = player;

		do {
			channel_00 = pPVar5->playerCarId;

			if (channel_00 != -1 && (pPVar5->cameraView == 2 || pPVar5->cameraView == 0))
			{
				pPVar5->camera_vel[0] = car_data[channel_00].st.n.linearVelocity[0];
				pPVar5->camera_vel[1] = car_data[channel_00].st.n.linearVelocity[1];
				pPVar5->camera_vel[2] = car_data[channel_00].st.n.linearVelocity[2];
			}
			else
			{
				pPVar5->camera_vel[0] = 0;
				pPVar5->camera_vel[1] = 0;
				pPVar5->camera_vel[2] = 0;
			}

			if (pPVar5->car_sound_timer > -1)
				pPVar5->car_sound_timer--;

			if (pPVar5->car_sound_timer == 4 && channel_00 != -1)
			{
				Start3DSoundVolPitch(-1, 6, 4, car_data[channel_00].hd.where.t[0], -car_data[channel_00].hd.where.t[1], car_data[channel_00].hd.where.t[2], -2500, 3072);
			}

			if (pPVar5->car_sound_timer == 0)
				pPVar5->car_is_sounding = 0;

			if (pPVar5->crash_timer > 0)
				pPVar5->crash_timer--;

			if (pPVar5->playerCarId < 0)
			{
				channel_00 = 1;
				if (iVar3 != 0)
					channel_00 = 4;

				SetChannelVolume(channel_00, -10000, 0);
				channel_00 = 0;
				if (iVar3 != 0)
					channel_00 = 3;

				SetChannelVolume(channel_00, -10000, 0);
				channel_00 = 2;
				if (iVar3 != 0)
					channel_00 = 5;

				SetChannelVolume(channel_00, -10000, 0);
			}
			else
			{
				channel = 1;
				if (iVar3 != 0)
					channel = 4;

				position = (VECTOR*)car_data[channel_00].hd.where.t;
				velocity = car_data[channel_00].st.n.linearVelocity;

				if (pPVar5->car_is_sounding == 0)
				{
					volume = pPVar5->idlevol;
				}
				else
				{
					volume = -10000;
				}

				SetChannelPosition3(channel, position, velocity, volume, car_data[channel_00].hd.revs / 4 + 4096, 0);
				channel = 0;

				if (iVar3 != 0) {
					channel = 3;
				}

				volume = -10000;

				if (pPVar5->car_is_sounding < 2)
					volume = pPVar5->revsvol;


				SetChannelPosition3(channel, position, velocity, volume, car_data[channel_00].hd.revs / 4 + pPVar5->revsvol / 64 + 1500, 0);

				channel_00 = CarHasSiren(car_data[channel_00].ap.model);

				if (channel_00 != 0)
				{
					if (pPVar5->horn.on == 0)
					{
						uVar1 = 2;
						if (iVar3 != 0)
							uVar1 = 5;

						SpuSetVoicePitch(uVar1, 0);
					}
					else
					{
						channel_00 = 2;

						if (iVar3 != 0)
							channel_00 = 5;

						SetChannelPosition3(channel_00, position, velocity, 0, 0x1000, 0);
					}
				}
			}

			pPVar5 = pPVar5 + 1;
			iVar3 = iVar3 + 1;
		} while (iVar3 < NumPlayers);
	}

	if (NumPlayers < 2 || NoPlayerControl != 0)
	{
		UpdateEnvSounds[EStags.func_cnt](envsnd, ESdata, 0);

		iVar4 = EStags.func_cnt + 1;
		iVar3 = iVar4;
		EStags.func_cnt = iVar4 + (iVar3 >> 2) * -4;

		DoDopplerSFX();
		Tunnels(&tunnels);
	}

	ControlSpeech(&gSpeechQueue);
	if (gInGameCutsceneActive == 0)
	{
		DoMissionSound();
	}
	else
	{
		HandleRequestedXA();
		DoCutsceneSound();
	}

	if (gInGameChaseActive != 0)
		LeadHorn(&car_data[player[0].targetCarId]); //LeadHorn(&car_data[1]);

	if (jericho_in_back != 0 && (gCurrentMissionNumber == 20 || gCurrentMissionNumber == 25 || gCurrentMissionNumber == 39))
	{
		JerichoSpeak();
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitMusic(int musicnum /*$s0*/)
 // line 1195, offset 0x000500e4
	/* begin block 1 */
		// Start line: 1196
		// Start offset: 0x000500E4
		// Variables:
	// 		static char *music_pt; // offset 0xc
	// 		static char *sample_pt; // offset 0x10
	// 		static char xm_samples; // offset 0x4
	// 		int musicpos[3]; // stack offset -32
	// 		char *name; // $s1
	// 		int sample_len; // $s0
	// 		int music_len; // $t0

		/* begin block 1.1 */
			// Start line: 1240
			// Start offset: 0x000501A4
		/* end block 1.1 */
		// End offset: 0x00050208
		// End Line: 1247
	/* end block 1 */
	// End offset: 0x0005027C
	// End Line: 1256

	/* begin block 2 */
		// Start line: 2760
	/* end block 2 */
	// End Line: 2761

	/* begin block 3 */
		// Start line: 2773
	/* end block 3 */
	// End Line: 2774

// [D] [T]
void InitMusic(int musicnum)
{
	static char* music_pt; // offset 0xc
	static char* sample_pt; // offset 0x10
	static char xm_samples; // offset 0x4
	int sample_len;
	int music_len;
	char* name;

	char* d1musicName = "SOUND\\D1MUSIC.BIN";
	char* musicname = "SOUND\\MUSIC.BIN";

	if (FileExists(d1musicName) && gDriver1Music)
	{
		name = d1musicName;
		xm_coptrackpos = xm_coptrackpos_d1;
	}
	else
	{
		name = musicname;
		xm_coptrackpos = xm_coptrackpos_d2;
		gDriver1Music = 0;
	}

	char* addr;
	int musicpos[3];

	copmusic = 0;
	puts("NewLevel in InitMusic()\n");
	AllocateReverb(3, 16384);

	current_music_id = musicnum;
	LoadfileSeg(name, (char*)musicpos, musicnum * 8, sizeof(musicpos));

	MALLOC_BEGIN()

		addr = mallocptr;

	sample_len = musicpos[2] - musicpos[1];
	music_len = musicpos[1] - musicpos[0];

	if (NewLevel != 0)
	{
		music_pt = mallocptr;
		sample_pt = mallocptr + music_len; // (sample_len + 3U & 0xfffffffc);

		mallocptr = sample_pt;
		LoadfileSeg(name, addr, musicpos[0], music_len + sample_len);
	}

	MALLOC_END();

	if (Song_ID == -1)
	{
		VABID = XM_GetFreeVAB();

		if (NewLevel != 0)
			xm_samples = LoadSoundBank(sample_pt, sample_len, 0);

		UpdateXMSamples(xm_samples);

		XM_GetFileHeaderSize();
		XM_SetFileHeaderAddress((unsigned char*)header_pt);
		XM_GetSongSize();
		XM_SetSongAddress((unsigned char*)song_pt);
	}

	InitXMData((unsigned char*)music_pt, 0, 0);

	Song_ID = XM_Init(VABID, 0, 0, 16, 1, -1, 0, 0);

	if (music_paused != 0)
		XM_Pause(Song_ID);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitTunnels(char n /*$a0*/)
 // line 1317, offset 0x0005243c
	/* begin block 1 */
		// Start line: 1318
		// Start offset: 0x0005243C
		// Variables:
	// 		struct __tunnelinfo *T; // $a1
	/* end block 1 */
	// End offset: 0x00052460
	// End Line: 1325

	/* begin block 2 */
		// Start line: 5453
	/* end block 2 */
	// End Line: 5454

	/* begin block 3 */
		// Start line: 2634
	/* end block 3 */
	// End Line: 2635

// [D]
void InitTunnels(char n)
{
	if (n > 29)
		n = 29;

	tunnels.num_tunnels = n;
	tunnels.tunnel_cnt = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AddTunnel(long x1 /*$t1*/, long y1 /*$a1*/, long z1 /*$a2*/, long x2 /*$a3*/, long y2 /*stack 16*/, long z2 /*stack 20*/)
 // line 1331, offset 0x00052848
	/* begin block 1 */
		// Start line: 1332
		// Start offset: 0x00052848
		// Variables:
	// 		struct __tunnelinfo *T; // $t0
	/* end block 1 */
	// End offset: 0x000528FC
	// End Line: 1344

	/* begin block 2 */
		// Start line: 6755
	/* end block 2 */
	// End Line: 6756

// [D]
int AddTunnel(long x1, long y1, long z1, long x2, long y2, long z2)
{
	if (tunnels.tunnel_cnt < tunnels.num_tunnels)
	{
		tunnels.coords[tunnels.tunnel_cnt].p1.vx = x1;
		tunnels.coords[tunnels.tunnel_cnt].p1.vy = y1;
		tunnels.coords[tunnels.tunnel_cnt].p1.vz = z1;
		tunnels.coords[tunnels.tunnel_cnt].p2.vx = x2;
		tunnels.coords[tunnels.tunnel_cnt].p2.vy = y2;
		tunnels.coords[tunnels.tunnel_cnt].p2.vz = z2;

		return tunnels.tunnel_cnt++;
	}

	return -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ Tunnels(struct __tunnelinfo *T /*$a0*/)
 // line 1350, offset 0x0005027c
	/* begin block 1 */
		// Start line: 1351
		// Start offset: 0x0005027C
		// Variables:
	// 		int i; // $t2
	// 		int verb; // $t4
	/* end block 1 */
	// End offset: 0x00050400
	// End Line: 1364

	/* begin block 2 */
		// Start line: 3075
	/* end block 2 */
	// End Line: 3076

	/* begin block 3 */
		// Start line: 3115
	/* end block 3 */
	// End Line: 3116

	/* begin block 4 */
		// Start line: 3119
	/* end block 4 */
	// End Line: 3120

// [D]
void Tunnels(__tunnelinfo* T)
{
	int iVar1;
	int iVar2;
	int iVar4;
	int iVar5;
	int on;

	iVar5 = 0;
	gTunnelNum = -1;
	NoRainIndoors = 0;
	on = 0;

	if (T->tunnel_cnt != 0)
	{
		iVar4 = 0;
		do {
			iVar1 = T->coords[iVar5].p2.vx;
			iVar2 = T->coords[iVar5].p1.vx;

			if (iVar2 < iVar1)
				iVar1 = iVar2;

			if (iVar1 < camera_position.vx)
			{
				iVar1 = T->coords[iVar5].p2.vx;

				if (iVar1 < iVar2)
					iVar1 = iVar2;

				if (camera_position.vx < iVar1)
				{
					iVar1 = T->coords[iVar5].p2.vy;
					iVar2 = T->coords[iVar5].p1.vy;
					if (iVar2 < iVar1)
						iVar1 = iVar2;

					if (iVar1 < camera_position.vy)
					{
						iVar1 = T->coords[iVar5].p2.vy;
						if (iVar1 < iVar2)
							iVar1 = iVar2;

						if (camera_position.vy < iVar1)
						{
							iVar1 = T->coords[iVar5].p2.vz;
							iVar4 = T->coords[iVar5].p1.vz;

							if (iVar4 < iVar1)
								iVar1 = iVar4;

							if (iVar1 < camera_position.vz)
							{
								iVar1 = T->coords[iVar5].p2.vz;
								if (iVar1 < iVar4)
									iVar1 = iVar4;

								if (camera_position.vz < iVar1)
								{
									on = 1;
									gTunnelNum = iVar5;
									NoRainIndoors = 1;
									break;
								}
							}
						}
					}
				}
			}
			iVar5 = iVar5 + 1;
			iVar4 = iVar5 * 0x20;
		} while (iVar5 < T->tunnel_cnt);
	}
	SetReverbInGameState(on);
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddTunnels(int level /*$a0*/)
 // line 1366, offset 0x00050400
	/* begin block 1 */
		// Start line: 3152
	/* end block 1 */
	// End Line: 3153

	/* begin block 2 */
		// Start line: 3155
	/* end block 2 */
	// End Line: 3156

// [D]
void AddTunnels(int level)
{
	if (level == 0)
	{
		InitTunnels(29);

		AddTunnel(-0x13178, 0, -0x1e848, -0xab18, -500, -0x26f0c);
		AddTunnel(-65000, 0, -0x1df4c, -68000, -500, -0x1e848);
		AddTunnel(-0xbdd8, 0, -0x39dc8, -0xc4ae, -500, -0x3997c);
		AddTunnel(-0x35af7, 0, 0xa4cfb, -0x32f07, -2000, 0xa3507);
		AddTunnel(-0x47ef4, 0, 0x4e1e5, -0x466fc, -500, 0x4d5f5);
		AddTunnel(-0x44df9, 0, 0x4e8ee, -0x43611, -500, 0x4d0f6);
		AddTunnel(-0x418f6, 0, 0x4e2f4, -0x4010a, -500, 0x4cb40);
		AddTunnel(-0x47bfe, 0, 0x4b5f8, -0x46c0e, -500, 0x4a9f8);
		AddTunnel(-0x43f02, 0, 0x4b5f8, -0x43afe, -500, 0x4aa00);
		AddTunnel(-0x48cfe, 0, 0x49a00, -0x468fa, -500, 0x48e00);
		AddTunnel(-0x47506, 0, 0x48e00, -0x468fa, -500, 0x481f8);
		AddTunnel(-0x452fa, 0, 0x489f4, -0x446fa, -500, 0x47dfc);
		AddTunnel(-0x452fe, 0, 0x47dfc, -0x42f06, -500, 0x47200);
		AddTunnel(-0x46e8b, 0, 0x43eec, -0x44e7f, -500, 0x432f8);
		AddTunnel(-0x44afa, 0, 0x439f0, -0x43ede, -500, 0x42e00);
		AddTunnel(-0x466f6, 0, 0x41af8, -0x45afa, -500, 0x40f00);
		AddTunnel(-0x46a83, 0, 0x3f6e6, -0x4668b, -500, 0x3eafa);
		AddTunnel(-0x488fa, 0, 0x3dafa, -0x47112, -500, 0x3cef6);
		AddTunnel(-0x456fe, 0, 0x3dafa, -0x43f0e, -500, 0x3cef6);
		AddTunnel(-0x418fa, 0, 0x3dafa, -0x400fe, -500, 0x3cef6);
		AddTunnel(-0x48e02, 0, 0x3acf9, -0x46e06, -500, 0x3a101);
		AddTunnel(-0x410fa, 0, 0x3b5f5, -0x3f906, -500, 0x3aa05);
		AddTunnel(-0x44cf6, 0, 0x390f7, -0x448fe, -500, 0x384ff);
		AddTunnel(-0x448fe, 0, 0x384ff, -0x43102, -500, 0x37903);
		AddTunnel(-0x45afe, 0, 0x329f9, -0x45706, -500, 0x31dfd);
		AddTunnel(-0x47701, 0, 0x30df8, -0x42f05, -500, 0x2f604);
		AddTunnel(-0x41501, 0, 0x305f8, -0x40905, -500, 0x2ee00);
		AddTunnel(-0x418fe, 0, 0x2ee00, -0x40d05, -500, 0x2d608);
		AddTunnel(-0x351f1, 0, -0x55f12, -0x30a1d, -500, -0x57702);
	}
	else if (level == 1)
	{
		InitTunnels(4);

		AddTunnel(-0x6153a, 0, -0x274e8, -0x5314c, 2000, -0x19258);
		AddTunnel(0x429a0, 0, 0xa0f0, 0x3e418, 2000, 0x29298);
		AddTunnel(-0x749a0, 0, -0x1b83c, -0x60ec8, 0x1f40, -0x206c0);
		AddTunnel(-0x2d613, 0, -0xa1ea, -0x2bdc2, -1000, -0xae38);
	}
	else if (level == 2)
	{
		InitTunnels(2);

		AddTunnel(0x2678a, 0, 0xb4b9a, 0x2918a, -2000, 0xb139b);
		AddTunnel(0x28550, 0, 0xb139b, 0x2918a, -2000, 0xb06da);
	}
	else if (level == 3)
	{
		InitTunnels(5);

		AddTunnel(0x24f68, 0, -0x3d374, 0x25cb0, -400, -0x398e6);
		AddTunnel(-0x1c19c, 0, -0x2f2b0, -0x1ba94, -400, -0x20594);
		AddTunnel(-0x118dc, 0, -0x3f7a, -0x11fb2, -400, -0x6f54);
		AddTunnel(0x131dc, 0, -0x28fdc, 0x14212, -500, -0x297de);
		AddTunnel(0x2a5ee, 0, 0x3c668, 0x2b624, -500, 0x3be34);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitEnvSnd(int num_envsnds /*$a0*/)
 // line 1510, offset 0x00052388
	/* begin block 1 */
		// Start line: 1511
		// Start offset: 0x00052388
		// Variables:
	// 		int i; // $v1
	// 		int p; // $a1
	// 		struct __envsoundtags *T; // $t1
	/* end block 1 */
	// End offset: 0x0005243C
	// End Line: 1538

	/* begin block 2 */
		// Start line: 5618
	/* end block 2 */
	// End Line: 5619

	/* begin block 3 */
		// Start line: 5622
	/* end block 3 */
	// End Line: 5623

static struct __envsoundtags EStags;

// [D]
void InitEnvSnd(int num_envsnds)
{
	bool bVar1;
	__envsound* p_Var2;
	uint uVar3;
	int* piVar4;
	int iVar5;
	int iVar6;
	int iVar7;

	if (num_envsnds > 32)
		num_envsnds = 0x20;

	if (0 < num_envsnds)
	{
		p_Var2 = envsnd;
		iVar5 = num_envsnds;
		do {
			p_Var2->type = 0;
			iVar5--;
			p_Var2++;
		} while (iVar5 != 0);
	}

	if (NumPlayers != 0)
	{
		iVar5 = 0;
		iVar7 = 1;

		do {
			iVar6 = 3;
			piVar4 = ESdata[iVar5].playing_sound + 3;
			do {
				*piVar4 = -1;
				iVar6--;
				piVar4--;
			} while (-1 < iVar6);

			bVar1 = iVar7 < NumPlayers;
			iVar5 = iVar7;
			iVar7 = iVar7 + 1;
		} while (bVar1);
	}

	EStags.frame_cnt = 0;
	EStags.func_cnt = 0;
	EStags.num_envsnds = num_envsnds;
	EStags.envsnd_cnt = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SetEnvSndVol(int snd /*$a0*/, int vol /*$a1*/)
 // line 1545, offset 0x00052168
	/* begin block 1 */
		// Start line: 1546
		// Start offset: 0x00052168
		// Variables:
	// 		int was; // $v0
	/* end block 1 */
	// End offset: 0x00052190
	// End Line: 1550

	/* begin block 2 */
		// Start line: 4242
	/* end block 2 */
	// End Line: 4243

	/* begin block 3 */
		// Start line: 3090
	/* end block 3 */
	// End Line: 3091

	/* begin block 4 */
		// Start line: 4244
	/* end block 4 */
	// End Line: 4245

// [D]
int SetEnvSndVol(int snd, int vol)
{
	int was;

	was = envsnd[snd].vol;
	envsnd[snd].vol = vol;

	return was;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetEnvSndPos(int snd /*$a0*/, long px /*$a1*/, long pz /*$a2*/)
 // line 1555, offset 0x00052904
	/* begin block 1 */
		// Start line: 7203
	/* end block 1 */
	// End Line: 7204

	/* begin block 2 */
		// Start line: 7205
	/* end block 2 */
	// End Line: 7206

// [D]
void SetEnvSndPos(int snd, long px, long pz)
{
	if (envsnd[snd].type == 3)
	{
		envsnd[snd].pos2.vx = px;
		envsnd[snd].pos.vx = px;
		envsnd[snd].pos2.vz = pz;
		envsnd[snd].pos.vz = pz;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ AddEnvSnd(int type /*$t4*/, char flags /*$a1*/, int bank /*$a2*/, int sample /*$a3*/, int vol /*stack 16*/, long px /*stack 20*/, long pz /*stack 24*/)
 // line 1577, offset 0x00050c08
	/* begin block 1 */
		// Start line: 1578
		// Start offset: 0x00050C08
		// Variables:
	// 		void *data; // $a1
	// 		struct __envsound *ep; // $t1
	// 		struct __envsoundtags *T; // $t0
	// 		long s; // $a1
	/* end block 1 */
	// End offset: 0x00050E08
	// End Line: 1635

	/* begin block 2 */
		// Start line: 3577
	/* end block 2 */
	// End Line: 3578

// [D]
int AddEnvSnd(int type, char flags, int bank, int sample, int vol, long px, long pz, long px2, long pz2)
{
	__envsound* ep;

	if (EStags.envsnd_cnt >= EStags.num_envsnds)
		return -1;

	ep = &envsnd[EStags.envsnd_cnt];

	ep->type = type;
	ep->bank = bank;
	ep->sample = sample;
	ep->flags = flags;
	ep->vol = vol;

	switch (type)
	{
		case 1:
		case 2:
		case 4:
			ep->pos.vx = px;
			ep->pos2.vx = px2;
			ep->pos2.vz = pz2;
			ep->pos.vz = pz;
			break;
		case 3:
			ep->pos2.vx = px;
			ep->pos.vx = px;
			ep->pos2.vz = pz;
			ep->pos.vz = pz;
			break;
		case 5:
			ep->type = 1;
			ep->pos.vx = px - px2;
			ep->pos.vz = pz - px2;
			ep->pos2.vx = px + px2;
			ep->pos2.vz = pz + px2;
	}

	if (ep->pos.vx == ep->pos2.vx)
		ep->flags = ep->flags | 1;

	if (ep->pos.vz == ep->pos2.vz)
		ep->flags = ep->flags | 2;

	if (type != 3)
		ep->flags = ep->flags | 0x20;

	return EStags.envsnd_cnt++;
}



// decompiled code
// original method signature: 
// void /*$ra*/ IdentifyZone(struct __envsound *ep /*$a3*/, struct __envsoundinfo *E /*stack 4*/, int pl /*$a2*/)
 // line 1646, offset 0x00050e08
	/* begin block 1 */
		// Start line: 1647
		// Start offset: 0x00050E08
		// Variables:
	// 		int i; // $s7
	// 		int j; // $fp
	// 		int tmp[4]; // stack offset -96
	// 		float d; // $s0
	// 		float _g[4]; // stack offset -80
	// 		struct __bitfield64 zones; // stack offset -64
	/* end block 1 */
	// End offset: 0x000514BC
	// End Line: 1704

	/* begin block 2 */
		// Start line: 3727
	/* end block 2 */
	// End Line: 3728

	/* begin block 3 */
		// Start line: 3739
	/* end block 3 */
	// End Line: 3740

// [D] [A] unprocessed arrays
void IdentifyZone(__envsound* ep, __envsoundinfo* E, int pl)
{
	bool bVar1;
	int* piVar2;
	int local_v0_412;
	int local_v0_576;
	float uVar3;
	float uVar4;
	double uVar16;
	double uVar17;
	float fVar5;
	int local_v1_320;
	int iVar6;
	int local_v1_468;
	int iVar7;
	int uVar8;
	int iVar9;
	long lVar10;
	int local_a0_1016;
	int local_a0_1044;
	int* local_a0_1248;
	int* local_a0_1304;
	int iVar11;
	int local_a2_308;
	int iVar12;
	float* pfVar13;
	int iVar14;
	int iVar15;

	int tmp[4];
	float _g[4];
	__bitfield64 zones;
	int* _tmp;
	int* piStack48;

	_tmp = tmp;
	iVar14 = 3;
	piVar2 = tmp + 3;
	zones.l = 0;
	zones.h = 0;

	do {
		*piVar2 = -1;
		iVar14 = iVar14 + -1;
		piVar2 = piVar2 + -1;
	} while (-1 < iVar14);

	(E->cam_pos).vx = player[pl].cameraPos.vx;
	(E->cam_pos).vy = player[pl].cameraPos.vy;
	(E->cam_pos).vz = player[pl].cameraPos.vz;

	iVar14 = 0;
	iVar15 = 0;

	piStack48 = _tmp;
	if (0 < EStags.envsnd_cnt)
	{
		do {
			if (-1 < tmp[3])
				break;

			if ((ep->type != 0) && (-7500 < ep->vol))
			{
				iVar9 = (ep->pos2).vx;
				iVar11 = (ep->pos).vx;
				iVar6 = iVar9;
				if (iVar11 < iVar9) {
					iVar6 = iVar11;
				}
				local_a2_308 = (ep->vol + 7500) * 4;
				local_v1_320 = local_a2_308;
				if (local_a2_308 < 0)
					local_v1_320 = 0;

				if (22000 < local_v1_320)
					local_v1_320 = 22000;

				iVar12 = (E->cam_pos).vx;
				if (iVar6 - local_v1_320 < iVar12)
				{
					if (iVar9 < iVar11)
						iVar9 = iVar11;

					iVar6 = local_a2_308;
					if (local_a2_308 < 0)
						iVar6 = 0;

					local_v0_412 = iVar9 + iVar6;
					if (22000 < iVar6)
						local_v0_412 = (22000 + iVar9);

					if (iVar12 < local_v0_412)
					{
						iVar6 = (ep->pos2).vz;
						iVar11 = (ep->pos).vz;
						iVar9 = iVar6;
						if (iVar11 < iVar6)
							iVar9 = iVar11;

						local_v1_468 = local_a2_308;
						if (local_a2_308 < 0)
							local_v1_468 = 0;

						if (22000 < local_a2_308)
							local_v1_468 = 22000;

						iVar12 = (E->cam_pos).vz;
						if (iVar9 - local_v1_468 < iVar12)
						{
							iVar9 = iVar6;
							if (iVar6 < iVar11)
								iVar9 = iVar11;

							iVar7 = (ep->vol + 7500) * 4;

							local_v0_576 = iVar7;
							if (iVar7 < 0)
								local_v0_576 = 0;

							local_v0_576 = iVar9 + local_v0_576;
							if (22000 < iVar7)
								local_v0_576 = (22000 + iVar9);

							if (iVar12 < local_v0_576)
							{
								if (((ep->type == 2) || (ep->type == 4)) && ((ep->flags & 3) == 0))
								{
									pfVar13 = _g + iVar14;
									uVar3 = iVar6 - iVar11;// __floatsisf(iVar6 - iVar11);
									iVar9 = (ep->pos).vx;
									uVar4 = ep->pos2.vx - iVar9;//__floatsisf(ep->pos2.vx - iVar9);
									fVar5 = uVar3 / uVar4;// (float)__divsf3(uVar3, uVar4);
									lVar10 = (E->cam_pos).vx;
									*pfVar13 = fVar5;
									uVar3 = lVar10; //  __floatsisf(lVar10);
									uVar3 = fVar5 * uVar3;//__mulsf3(fVar5, uVar3);
									uVar4 = iVar9; // __floatsisf(iVar9);
									uVar4 = fVar5 * uVar4;// __mulsf3(fVar5, uVar4);
									uVar3 = uVar3 - uVar4;// __subsf3(uVar3, uVar4);
									uVar4 = iVar12; // __floatsisf(iVar12);
									uVar3 = uVar3 - uVar4;// __subsf3(uVar3, uVar4);
									uVar4 = iVar11; // __floatsisf(iVar11);
									uVar3 = uVar3 + uVar4; // __addsf3(uVar3, uVar4);
									uVar16 = uVar3; // __extendsfdf2(uVar3);
									iVar9 = *pfVar13; // __fixunssfsi(*pfVar13); // might be incorrectly working
									iVar6 = *pfVar13; // __fixunssfsi(*pfVar13);
									iVar9 = iVar9 * iVar6 + 1;
									uVar17 = iVar9; // __floatsidf(iVar9);

									if (iVar9 < 0)
										uVar17 = uVar17 + 30.0f;// __adddf3((int)((ulonglong)uVar17 >> 0x20), (int)uVar17, 0, 0x41f00000);

									uVar17 = sqrt(uVar17);

									uVar17 = uVar16 / uVar17; // __divdf3((int)((ulonglong)uVar16 >> 0x20), (int)uVar16, (int)((ulonglong)uVar17 >> 0x20), (int)uVar17);
									uVar3 = uVar17;// __truncdfsf2((int)((ulonglong)uVar17 >> 0x20), (int)uVar17);

									if (ep->type == 2)
									{
										//iVar9 = __gesf2(uVar3, 0);
										//if (iVar9 < 0) 
										if (uVar3 < 0)
										{
										LAB_000511e8:
											uVar3 = -uVar3;
										}
									}
									else
									{
										if ((ep->flags & 8) != 0)
											goto LAB_000511e8;
									}

									local_a0_1016 = (ep->vol + 7500) * 4;
									local_a0_1044 = local_a0_1016;

									if (local_a0_1016 < 0)
										local_a0_1044 = 0;

									if (22000 < local_a0_1016)
										local_a0_1044 = 22000;

									uVar4 = (local_a0_1044);
									//iVar9 = __ltsf2(uVar3, uVar4);
									//if (iVar9 < 0)
									if (uVar3 < uVar4)
									{
										iVar14 = iVar14 + 1;
										*piStack48 = iVar15;
										piStack48 = piStack48 + 1;
									}
								}
								else
								{
									iVar14 = iVar14 + 1;
									*piStack48 = iVar15;
									piStack48 = piStack48 + 1;
								}
							}
						}
					}
				}
			}
			iVar15 = iVar15 + 1;
			ep = ep + 1;
		} while (iVar15 < EStags.envsnd_cnt);
	}

	iVar14 = 0;
	local_a0_1248 = _tmp;

	while (true)
	{
		bVar1 = iVar14 < EStags.envsnd_cnt;

		if (4 < EStags.envsnd_cnt)
			bVar1 = iVar14 < 4;

		if (!bVar1)
			break;
		uVar8 = *local_a0_1248;

		if (-1 < uVar8)
		{
			if (uVar8 < 0x20)
				zones.l = zones.l | 1 << (uVar8 & 0x1f);
			else
				zones.h = zones.h | 1 << (uVar8 - 0x20 & 0x1f);
		}
		local_a0_1248 = local_a0_1248 + 1;
		iVar14 = iVar14 + 1;
	}

	iVar14 = 3;
	local_a0_1304 = E->thisS;

	do {
		uVar8 = *local_a0_1304;
		if (-1 < uVar8)
		{
			if (uVar8 < 0x20)
			{
				if ((zones.l & 1 << (uVar8 & 0x1f)) != 0)
					goto LAB_00051370;

				*local_a0_1304 = -1;
			}
			else
			{
				if ((zones.h & 1 << (uVar8 - 0x20 & 0x1f)) == 0)
				{
					*local_a0_1304 = -1;
				}
				else
				{
				LAB_00051370:
					uVar8 = *local_a0_1304;

					if (uVar8 < 0x20)
						zones.l = zones.l & ~(1 << (uVar8 & 0x1f));
					else
						zones.h = zones.h & ~(1 << (uVar8 - 0x20 & 0x1f));
				}
			}
		}

		iVar14 = iVar14 + -1;
		local_a0_1304 = local_a0_1304 + 1;

		if (iVar14 < 0)
		{
			iVar15 = 1;
			iVar14 = 0;

			do {
				uVar8 = _tmp[iVar14];
				iVar9 = iVar15;

				if (-1 < uVar8)
				{

					if (uVar8 < 0x20)
						uVar8 = zones.l & 1 << (uVar8 & 0x1f);
					else
						uVar8 = zones.h & 1 << (uVar8 - 0x20 & 0x1f);

					if (uVar8 != 0)
					{
						iVar15 = 0;
						while (iVar9 = iVar14 + 1, iVar15 < 4)
						{
							if (E->thisS[iVar15] < 0)
							{
								E->thisS[iVar15] = _tmp[iVar14];
								E->g[iVar15] = _g[iVar14];
								break;
							}

							iVar15 = iVar15 + 1;
						}
					}
				}

				iVar15 = iVar9 + 1;
				iVar14 = iVar9;

				if (3 < iVar9)
					return;

			} while (true);
		}
	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalcEffPos(struct __envsound *ep /*$s1*/, struct __envsoundinfo *E /*$a1*/, int pl /*$a2*/)
 // line 1706, offset 0x000514bc
	/* begin block 1 */
		// Start line: 1707
		// Start offset: 0x000514BC
		// Variables:
	// 		int j; // $t5
	// 		int me; // $t2
	/* end block 1 */
	// End offset: 0x000517D0
	// End Line: 1742

	/* begin block 2 */
		// Start line: 3903
	/* end block 2 */
	// End Line: 3904

	/* begin block 3 */
		// Start line: 3906
	/* end block 3 */
	// End Line: 3907

// [D] [A] unprocessed arrays
void CalcEffPos(__envsound* ep, __envsoundinfo* E, int pl)
{
	bool bVar1;
	long* local_a0_52;
	int iVar2;
	__envsound* p_Var3;
	int iVar4;
	int* piVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	long* local_t3_52;
	int iVar9;
	uint uVar10;
	long* local_t6_52;
	long* local_t7_28;
	long* plVar11;
	long* local_t9_52;
	long* temp_79f679ea1b7;
	long* temp_79f9c232453;

	uVar10 = 0;
	iVar9 = 0;
	local_t7_28 = &E->eff_pos[0].vz;
	local_a0_52 = (long*)E;
	local_t3_52 = (long*)E;
	local_t6_52 = local_t7_28;
	plVar11 = local_t7_28;
	local_t9_52 = (long*)E;

	do {
		E->flags = E->flags & ~(1 << (uVar10 & 0x1f));
		iVar8 = E->thisS[uVar10];

		if (-1 < iVar8)
		{
			p_Var3 = ep + iVar8;
			if (p_Var3->type == 1)
			{
				iVar2 = (p_Var3->pos2).vx;
				iVar4 = (p_Var3->pos).vx;
				iVar7 = iVar2;

				if (iVar4 < iVar2)
					iVar7 = iVar4;

				iVar6 = (E->cam_pos).vx;
				if (iVar6 < iVar7)
				{
					if (iVar4 < iVar2)
						iVar2 = iVar4;

					*local_t9_52 = iVar2;
				}
				else
				{
					iVar7 = iVar2;

					if (iVar2 < iVar4)
						iVar7 = iVar4;

					if (iVar7 < iVar6)
					{
						if (iVar2 < iVar4)
							iVar2 = iVar4;

						*local_a0_52 = iVar2;
					}
					else
					{
						*local_t3_52 = iVar6;
					}
				}
				p_Var3 = ep + iVar8;
				iVar8 = (p_Var3->pos2).vz;
				iVar2 = (p_Var3->pos).vz;

				if (iVar2 < iVar8)
					iVar8 = iVar2;

				iVar7 = (E->cam_pos).vz;

				if (iVar7 < iVar8)
				{
					iVar8 = (p_Var3->pos2).vz;
					if (iVar2 < iVar8)
						iVar8 = iVar2;

					*local_t6_52 = iVar8;
				}
				else
				{
					iVar8 = (p_Var3->pos2).vz;

					iVar4 = iVar8;
					if (iVar8 < iVar2)
						iVar4 = iVar2;

					if (iVar4 < iVar7)
					{
						if (iVar8 < iVar2)
							iVar8 = iVar2;

						*plVar11 = iVar8;
					}
					else
					{
						local_t3_52[2] = iVar7;
					}
				}
			}
			else
			{
				if (p_Var3->type != 2)
					goto LAB_0005179c;

				if ((p_Var3->flags & 1) == 0)
				{
					if ((p_Var3->flags & 2) == 0)
						goto LAB_0005179c;

					local_t3_52[2] = (p_Var3->pos).vz;
					iVar8 = (p_Var3->pos2).vx;
					iVar2 = (p_Var3->pos).vx;

					if (iVar2 < iVar8)
						iVar8 = iVar2;

					iVar7 = (E->cam_pos).vx;
					if (iVar8 <= iVar7)
					{
						iVar4 = (p_Var3->pos2).vx;
						iVar8 = iVar4;
						if (iVar4 < iVar2)
							iVar8 = iVar2;

						if (iVar7 <= iVar8)
						{
							temp_79f9c232453 = (long*)E->eff_pos;
							goto LAB_00051788;
						}

						temp_79f679ea1b7 = (long*)E->eff_pos;
						goto LAB_0005176c;
					}

					iVar4 = (p_Var3->pos2).vx;
					piVar5 = (int*)((int)&E->eff_pos[0].vx + iVar9);
					bVar1 = iVar2 < iVar4;
				}
				else
				{
					*local_t3_52 = (p_Var3->pos).vx;
					iVar8 = (p_Var3->pos2).vz;
					iVar2 = (p_Var3->pos).vz;

					if (iVar2 < iVar8)
						iVar8 = iVar2;

					iVar7 = (E->cam_pos).vz;

					if (iVar7 < iVar8)
					{
						iVar4 = (p_Var3->pos2).vz;
						piVar5 = (int*)((int)local_t7_28 + iVar9);
						bVar1 = iVar2 < iVar4;
					}
					else
					{
						iVar4 = (p_Var3->pos2).vz;
						iVar8 = iVar4;

						if (iVar4 < iVar2)
							iVar8 = iVar2;

						temp_79f679ea1b7 = local_t7_28;
						temp_79f9c232453 = local_t7_28;

						if (iVar7 <= iVar8)
						{
						LAB_00051788:
							*(int*)((int)temp_79f9c232453 + iVar9) = iVar7;
							goto LAB_0005178c;
						}
					LAB_0005176c:
						piVar5 = (int*)((int)temp_79f679ea1b7 + iVar9);
						bVar1 = iVar4 < iVar2;
					}
				}
				if (bVar1) {
					iVar4 = iVar2;
				}
				*piVar5 = iVar4;
			}
		LAB_0005178c:
			E->flags = E->flags | 1 << (uVar10 & 0x1f);
		}

	LAB_0005179c:
		iVar9 = iVar9 + 0x10;
		local_t3_52 = local_t3_52 + 4;
		plVar11 = plVar11 + 4;
		local_t6_52 = local_t6_52 + 4;
		local_a0_52 = local_a0_52 + 4;
		uVar10 = uVar10 + 1;
		local_t9_52 = local_t9_52 + 4;

		if (3 < (int)uVar10)
			return;

	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalcEffPos2(struct __envsound *ep /*stack 0*/, struct __envsoundinfo *E /*$s7*/, int pl /*$a2*/)
 // line 1744, offset 0x000517d0
	/* begin block 1 */
		// Start line: 1745
		// Start offset: 0x000517D0
		// Variables:
	// 		int j; // stack offset -56
	// 		int me; // $s5

		/* begin block 1.1 */
			// Start line: 1756
			// Start offset: 0x000518D8
		/* end block 1.1 */
		// End offset: 0x000518D8
		// End Line: 1756
	/* end block 1 */
	// End offset: 0x00051F0C
	// End Line: 1810

	/* begin block 2 */
		// Start line: 4010
	/* end block 2 */
	// End Line: 4011

	/* begin block 3 */
		// Start line: 4013
	/* end block 3 */
	// End Line: 4014

// [D] [A] unprocessed arrays
void CalcEffPos2(__envsound* ep, __envsoundinfo* E, int pl)
{
	bool bVar1;
	int iVar2;
	float uVar3;
	float uVar4;
	__envsound* p_Var5;
	int iVar6;
	int iVar7;
	long lVar8;
	uint uVar9;
	int iVar10;
	float* pfVar11;
	float* local_s1_176;
	float uVar12;
	long* plVar13;
	int* piVar14;
	long lVar15;
	__envsoundinfo* p_Var16;
	int iVar17;
	uint local_38;
	int local_34;
	int local_30;

	local_38 = 0;
	local_34 = 0;
	local_30 = 0;
	p_Var16 = E;

	do {
		iVar17 = *(int*)((int)E->thisS + local_30);

		if ((-1 < iVar17) && (uVar9 = 1 << (local_38 & 0x1f), (E->flags & uVar9) == 0))
		{
			p_Var5 = ep + iVar17;

			if ((p_Var5->type == 2) || (p_Var5->type == 4))
			{
				pfVar11 = E->g;
				local_s1_176 = (float*)((int)pfVar11 + local_30);


				//iVar2 = __gesf2(*local_s1_176, 0);
				//if (iVar2 < 0)
				if (*local_s1_176 < 0)
				{
					uVar3 = -*local_s1_176;// __negsf2(*local_s1_176);

					//iVar2 = __ltsf2(uVar3, 0x3f800000);
					//if (-1 < iVar2) 
					if (uVar3 >= 1.0f)
						goto LAB_000519c0;

				LAB_000518d8:
					uVar3 = 1.0f / *(float*)((int)pfVar11 + local_30); //__divsf3(0x3f800000, *(float*)((int)pfVar11 + local_30));
					uVar4 = (E->cam_pos).vx; // __floatsisf((E->cam_pos).vx);
					uVar4 = uVar4 * uVar3; // __mulsf3(uVar4, uVar3);
					p_Var5 = ep + iVar17;
					uVar12 = (p_Var5->pos).vx; // __floatsisf((p_Var5->pos).vx);
					uVar12 = uVar12 / uVar3; // __divsf3(uVar12, uVar3);
					uVar4 = uVar4 + uVar12; // __addsf3(uVar4, uVar12);
					uVar12 = (E->cam_pos).vz; // __floatsisf((E->cam_pos).vz);
					uVar4 = uVar4 + uVar12; // __addsf3(uVar4, uVar12);
					uVar12 = (p_Var5->pos).vz; // __floatsisf((p_Var5->pos).vz);
					uVar4 = uVar4 - uVar12; // __subsf3(uVar4, uVar12);
					uVar12 = 1.0f / uVar3; // __divsf3(0x3f800000, uVar3);
					uVar12 = uVar12 + uVar3; // __addsf3(uVar12, uVar3);
					uVar4 = uVar4 / uVar12; // __divsf3(uVar4, uVar12);
					iVar2 = uVar4; // __fixsfsi(uVar4);
					p_Var16->eff_pos[0].vx = iVar2;
					uVar4 = iVar2 - (p_Var5->pos).vx; // __floatsisf(iVar2 - (p_Var5->pos).vx);
					uVar3 = uVar4 / uVar3; //__divsf3(uVar4, uVar3);
				}
				else
				{
					//iVar2 = __ltsf2(*local_s1_176, 0x3f800000);
					//if (iVar2 < 0) 
					if (*local_s1_176 < 1.0f)
						goto LAB_000518d8;

				LAB_000519c0:
					uVar3 = (E->cam_pos).vx; // __floatsisf((E->cam_pos).vx);
					uVar12 = *(float*)((int)pfVar11 + local_30);
					uVar3 = uVar3 / uVar12; // __divsf3(uVar3, uVar12);
					p_Var5 = ep + iVar17;
					uVar4 = (p_Var5->pos).vx; // __floatsisf((p_Var5->pos).vx);
					uVar4 = uVar4 * uVar12;// __mulsf3(uVar4, uVar12);
					uVar3 = uVar3 + uVar4;// __addsf3(uVar3, uVar4);
					uVar4 = (E->cam_pos).vz; //  __floatsisf((E->cam_pos).vz);
					uVar3 = uVar3 + uVar4; //__addsf3(uVar3, uVar4);
					uVar4 = (p_Var5->pos).vz; // __floatsisf((p_Var5->pos).vz);
					uVar3 = uVar3 - uVar4;// __subsf3(uVar3, uVar4);
					uVar4 = 1.0f / uVar12; //__divsf3(0x3f800000, uVar12);
					uVar4 = uVar12 + uVar4; // __addsf3(uVar12, uVar4);
					uVar3 = uVar3 / uVar4; // __divsf3(uVar3, uVar4);
					iVar2 = uVar3; // __fixsfsi(uVar3);
					p_Var16->eff_pos[0].vx = iVar2;
					uVar3 = iVar2 - (p_Var5->pos).vx; // __floatsisf(iVar2 - (p_Var5->pos).vx);
					uVar3 = uVar3 * *(float*)((int)pfVar11 + local_30); // __mulsf3(uVar3, *(float*)((int)pfVar11 + local_30));
				}

				plVar13 = &E->eff_pos[0].vz;
				uVar4 = ep[iVar17].pos.vz; // __floatsisf(ep[iVar17].pos.vz);
				uVar3 = uVar3 + uVar4;//__addsf3(uVar3, uVar4);
				uVar3 = uVar3;// __fixsfsi(uVar3);
				*(float*)((int)plVar13 + local_34) = uVar3;
				p_Var5 = ep + iVar17;

				if (p_Var5->type == 2)
				{
					iVar2 = (p_Var5->pos2).vx;
					iVar7 = (p_Var5->pos).vx;
					iVar6 = iVar2;

					if (iVar2 < iVar7)
						iVar6 = iVar7;

					iVar10 = p_Var16->eff_pos[0].vx;

					if (iVar6 < iVar10)
					{
						if (iVar2 < iVar7)
							iVar2 = iVar7;

						p_Var16->eff_pos[0].vx = iVar2;
					}
					else
					{
						iVar6 = iVar2;
						if (iVar7 < iVar2)
							iVar6 = iVar7;

						if (iVar10 < iVar6)
						{
							if (iVar7 < iVar2)
								iVar2 = iVar7;

							p_Var16->eff_pos[0].vx = iVar2;
						}
					}
					p_Var5 = ep + iVar17;
					iVar17 = (p_Var5->pos2).vz;
					iVar2 = (p_Var5->pos).vz;
					piVar14 = (int*)((int)plVar13 + local_34);

					if (iVar17 < iVar2)
						iVar17 = iVar2;

					if (iVar17 < *piVar14)
					{
						iVar17 = (p_Var5->pos2).vz;

						if (iVar17 < iVar2)
							iVar17 = iVar2;

						*piVar14 = iVar17;
					}
					else
					{
						iVar17 = (p_Var5->pos2).vz;
						iVar6 = iVar17;

						if (iVar2 < iVar17)
							iVar6 = iVar2;

						if (*piVar14 < iVar6)
						{
							if (iVar2 < iVar17)
								iVar17 = iVar2;

							*piVar14 = iVar17;
						}
					}
					E->flags = E->flags | 1 << (local_38 & 0x1f);
				}
				else if (p_Var5->type == 4)
				{
					if ((p_Var5->flags & 8) == 0) {
						iVar6 = (p_Var5->pos2).vz;
						iVar7 = (p_Var5->pos).vz;
						iVar2 = iVar6;

						if (iVar6 < iVar7)
							iVar2 = iVar7;

						iVar10 = (E->cam_pos).vz;
						if (iVar2 < iVar10)
						{
							iVar10 = iVar6;

							if (iVar6 < iVar7)
								iVar10 = iVar7;

						LAB_00051d80:
							*(int*)((int)plVar13 + local_34) = iVar10;
						}
						else
						{
							if (*(int*)((int)plVar13 + local_34) < iVar10)
								goto LAB_00051d80;
						}

						//iVar2 = __ltsf2(*(float*)((int)pfVar11 + local_30), 0);
						//if (-1 < iVar2)
						if (*(float*)((int)pfVar11 + local_30) >= 0)
							goto LAB_00051df8;

						p_Var5 = ep + iVar17;
						iVar17 = (p_Var5->pos2).vx;
						lVar8 = (p_Var5->pos).vx;
						if (iVar17 < lVar8) {
							iVar17 = lVar8;
						}
						iVar2 = (E->cam_pos).vx;
						if (iVar17 < iVar2)
						{
							lVar15 = (p_Var5->pos2).vx;
							bVar1 = lVar15 < lVar8;
							goto LAB_00051e40;
						}
						bVar1 = p_Var16->eff_pos[0].vx < iVar2;
					LAB_00051e60:
						if (bVar1) {
							p_Var16->eff_pos[0].vx = iVar2;
						}
					}
					else
					{
						iVar6 = (p_Var5->pos2).vz;
						iVar7 = (p_Var5->pos).vz;
						iVar2 = iVar6;

						if (iVar7 < iVar6)
							iVar2 = iVar7;

						iVar10 = (E->cam_pos).vz;
						if (iVar10 < iVar2)
						{
							iVar10 = iVar6;
							if (iVar7 < iVar6)
								iVar10 = iVar7;

						LAB_00051c98:
							*(int*)((int)plVar13 + local_34) = iVar10;
						}
						else
						{
							if (iVar10 < *(int*)((int)plVar13 + local_34))
								goto LAB_00051c98;
						}

						//iVar2 = __gtsf2(*(float*)((int)pfVar11 + local_30), 0);
						//if (iVar2 < 1) {
						if (*(float*)((int)pfVar11 + local_30) <= 0)
						{
						LAB_00051df8:
							p_Var5 = ep + iVar17;
							iVar17 = (p_Var5->pos2).vx;
							lVar8 = (p_Var5->pos).vx;

							if (lVar8 < iVar17)
								iVar17 = lVar8;

							iVar2 = (E->cam_pos).vx;

							if (iVar17 <= iVar2)
							{
								bVar1 = iVar2 < p_Var16->eff_pos[0].vx;
								goto LAB_00051e60;
							}

							lVar15 = (p_Var5->pos2).vx;
							bVar1 = lVar8 < lVar15;
						}
						else
						{
							p_Var5 = ep + iVar17;
							iVar17 = (p_Var5->pos2).vx;
							lVar8 = (p_Var5->pos).vx;

							if (iVar17 < lVar8)
								iVar17 = lVar8;

							iVar2 = (E->cam_pos).vx;

							if (iVar2 <= iVar17)
							{
								bVar1 = p_Var16->eff_pos[0].vx < iVar2;
								goto LAB_00051e60;
							}

							lVar15 = (p_Var5->pos2).vx;
							bVar1 = lVar15 < lVar8;
						}
					LAB_00051e40:
						if (bVar1)
							lVar15 = lVar8;

						p_Var16->eff_pos[0].vx = lVar15;
					}
				}
			}
			else
			{
				p_Var16->eff_pos[0].vx = (p_Var5->pos).vx;
				*(long*)((int)&E->eff_pos[0].vz + local_34) = (p_Var5->pos).vz;
				E->flags = E->flags | uVar9;
			}
		}

		p_Var16 = (__envsoundinfo*)(p_Var16->eff_pos + 1);
		local_30 = local_30 + 4;
		local_38 = local_38 + 1;
		*(int*)((int)&E->eff_pos[0].vy + local_34) = -(E->cam_pos).vy;
		local_34 = local_34 + 0x10;

		if (3 < (int)local_38)
			return;

	} while (true);

}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateEnvSnd(struct __envsound *ep /*stack 0*/, struct __envsoundinfo *E /*$s4*/, int pl /*stack 8*/)
 // line 1812, offset 0x00051f0c
	/* begin block 1 */
		// Start line: 1813
		// Start offset: 0x00051F0C
		// Variables:
	// 		int i; // stack offset -48
	/* end block 1 */
	// End offset: 0x00052168
	// End Line: 1841

	/* begin block 2 */
		// Start line: 4442
	/* end block 2 */
	// End Line: 4443

	/* begin block 3 */
		// Start line: 4445
	/* end block 3 */
	// End Line: 4446

// [D] [A] unprocessed arrays
void UpdateEnvSnd(__envsound* ep, __envsoundinfo* E, int pl)
{
	int iVar1;
	int channel;
	long* velocity;
	int* piVar2;
	int* piVar3;
	int* piVar4;
	int iVar5;
	__envsoundinfo* p_Var6;
	__envsoundinfo* position;
	int i;
	int local_2c;

	piVar3 = E->thisS;
	iVar5 = 0;
	piVar4 = E->playing_sound;
	local_2c = 0;
	i = 3;
	p_Var6 = E;
	position = E;

	do {
		channel = *piVar3;
		if (channel < 0)
		{
			if (-1 < *piVar4)
			{
				piVar2 = (int*)((int)E->chan + iVar5);
				StopChannel(*piVar2);
				UnlockChannel(*piVar2);
				*piVar4 = -1;
			}
		}
		else
		{
			if (*piVar4 != channel)
			{
				iVar1 = (int)&E->eff_pos[0].vx + local_2c;
				channel = Start3DSoundVolPitch(-1, ep[channel].bank, ep[channel].sample, p_Var6->eff_pos[0].vx, *(int*)(iVar1 + 4), *(int*)(iVar1 + 8), 0, 0x1000);
				piVar2 = (int*)((int)E->chan + iVar5);
				*piVar2 = channel;

				LockChannel(channel);

				if (NumPlayers > 1 && NoPlayerControl == 0)
					SetPlayerOwnsChannel(*piVar2, (char)pl);

				*(int*)((int)E->playing_sound + iVar5) = *piVar3;
			}

			if ((ep[*piVar3].flags & 0x10) == 0)
				velocity = NULL;
			else
				velocity = player[pl].camera_vel;

			SetChannelPosition3(*(int*)((int)E->chan + iVar5), (VECTOR*)position, velocity, ep[*piVar3].vol + -2500, 0x1000, (uint)ep[*piVar3].flags & 0x20);
		}
		piVar3 = piVar3 + 1;
		position = (__envsoundinfo*)(position->eff_pos + 1);
		piVar4 = piVar4 + 1;
		iVar5 = iVar5 + 4;
		p_Var6 = (__envsoundinfo*)(p_Var6->eff_pos + 1);
		local_2c = local_2c + 0x10;
		i = i + -1;
	} while (-1 < i);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitLeadHorn()
 // line 1852, offset 0x00052948
	/* begin block 1 */
		// Start line: 7797
	/* end block 1 */
	// End Line: 7798

/* WARNING: Unknown calling convention yet parameter storage is locked */

unsigned int horn_time;

void InitLeadHorn(void)
{
	horn_time = 0;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ LeadHorn(struct _CAR_DATA *cp /*$s0*/)
 // line 1855, offset 0x00052954
	/* begin block 1 */
		// Start line: 1856
		// Start offset: 0x00052954
		// Variables:
	// 		static unsigned int rnd; // offset 0x8
	/* end block 1 */
	// End offset: 0x00052A28
	// End Line: 1867

	/* begin block 2 */
		// Start line: 7803
	/* end block 2 */
	// End Line: 7804

	/* begin block 3 */
		// Start line: 7805
	/* end block 3 */
	// End Line: 7806

// [D]
void LeadHorn(_CAR_DATA* cp)
{
	static unsigned int rnd = 0;

	int bVar1;
	int uVar2;

	if (horn_time == 0)
		rnd = (cp->hd.where.t[0] ^ cp->hd.where.t[2]) * (FrameCnt ^ cp->hd.where.t[1]) & 0x7f;

	horn_time++;

	if (horn_time == rnd)
	{
		if (cp->ap.model == 4)
			uVar2 = ResidentModelsBodge();
		else if (cp->ap.model < 3)
			uVar2 = cp->ap.model;
		else
			uVar2 = cp->ap.model - 1;

		int ch = Start3DTrackingSound(-1, 3, uVar2 * 3 + 2, (VECTOR*)cp->hd.where.t, cp->st.n.linearVelocity);

		horn_time = 0;
	}
}





