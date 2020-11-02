

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



enum SoundBankIds
{
	SBK_ID_MENU					= 0,	// frontend, alpha 1.6 used it in ingame menu as well
	
	SBK_ID_SFX					= 1,
	SBK_CAR_SOUNDS_START		= 2,
	
	SBK_ID_JERICHO				= 19,	// jericho_in_back
	SBK_ID_JONES				= 20,
	
	SBK_CITY_EFFECTS_START		= 21,


	
	SBK_COP_PHRASES_START		= 29,
	SBK_ID_COUNTDOWN			= 44,

	// Mission banks start
	// Jones banks
	SBK_ID_MISSION_2			= 45,	// Chase the witness
	SBK_ID_MISSION_3			= 46,	// Train pursuit
	SBK_ID_MISSION_4			= 47,
	SBK_ID_MISSION_10			= 48,

	SBK_ID_MISSION_11			= 49,	// Hijack the truck
	SBK_ID_MISSION_13			= 50,	// Steal the truck
	SBK_ID_FERRY				= 51,	// Escape to ferry / To the docks
	SBK_ID_MISSION_18			= 52,	// Tail Jericho
	SBK_ID_MISSION_22			= 53,	// Beat the train
	SBK_ID_MISSION_23			= 54,	// Car bomb
	SBK_ID_MISSION_24			= 55,	// Stake out
	SBK_ID_MISSION_27			= 56,
	SBK_ID_MISSION_29			= 57,	// C4 deal
	SBK_ID_MISSION_30			= 58,	// Destroy the yard
	SBK_ID_MISSION_32			= 59,	// Steal the cop car
	SBK_ID_MISSION_33			= 60,	// Caine's cash - UNUSED
	SBK_ID_MISSION_35			= 61,	// Boat jump
	SBK_ID_MISSION_39			= 62,	// Lenny escaping - UNUSED
	SBK_ID_MISSION_40			= 63,	// Lenny gets caught

	SBK_ID_HAVANA_TAKEADRIVE	= 64,
	SBK_ID_VEGAS_TAKEADRIVE		= 65,

	SBK_ID_TANNER				= 66,
	SBK_ID_SPECIAL_SIREN1		= 67,
	SBK_ID_SPECIAL_SIREN2		= 68,
	SBK_COP_SIREN_START			= 69,
};

typedef void(*envsoundfunc)(__envsound* ep /*$s1*/, __envsoundinfo* E /*$a1*/, int pl /*$a2*/);

void IdentifyZone(envsound* ep, envsoundinfo* E, int pl);
void CalcEffPos(envsound* ep, envsoundinfo* E, int pl);
void CalcEffPos2(envsound* ep, envsoundinfo* E, int pl);
void UpdateEnvSnd(envsound* ep, envsoundinfo* E, int pl);

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
	0xB, 0xC, 0xB, 0xB, 8, 0xB, 0xF, 0xC,
};

int* xm_coptrackpos;
int gDriver1Music = 0;

SPEECH_QUEUE gSpeechQueue;
static char cop_bank = 0;
char phrase_top = 0;

static othercarsound siren_noise[MAX_SIREN_NOISES];
static othercarsound car_noise[MAX_CAR_NOISES];
static int loudhail_time = 0;

static int copmusic = 0;
int current_music_id;

static char header_pt[sizeof(XMHEADER)];
static char song_pt[sizeof(XMSONG)];

static envsound envsnd[MAX_LEVEL_ENVSOUNDS];
static envsoundinfo ESdata[2];
tunnelinfo tunnels;

char _sbank_buffer[0x80000];		// 0x180000


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

		if (j != 9)
			return 3;
	}
	else if (GameLevel == 1) 
	{
		if (j - 8U > 1) 
			return 3;
	}
	else if (GameLevel == 2)
	{
		i = 8;

		if (j != i)
			return 3;
	}
	else if (GameLevel == 3)
	{
		i = 11;

		if (j != i)
			return 3;
	}
	else
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
int gDoCopSpeech = 1;

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
		LoadBankFromLump(SOUND_BANK_CARS, MapCarIndexToBank(i));
		i++;
	} while (i < 3);

	ShowLoading();

	// load footsteps, car effects etc
	LoadBankFromLump(SOUND_BANK_SFX, SBK_ID_MENU);
	LoadBankFromLump(SOUND_BANK_SFX, SBK_ID_SFX);
	LoadBankFromLump(SOUND_BANK_TANNER, SBK_ID_TANNER );

	if (GameLevel & 2)
		LoadBankFromLump(SOUND_BANK_VOICES, SBK_COP_SIREN_START + (GameLevel & 1) * 2);
	else
		LoadBankFromLump(SOUND_BANK_VOICES, SBK_COP_SIREN_START + (GameLevel & 3));

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
			LoadBankFromLump(SOUND_BANK_VOICES, SBK_COP_PHRASES_START + (GameLevel & 1) * 8 + (GameLevel & 1) * 2);
			LoadBankFromLump(SOUND_BANK_VOICES, SBK_COP_PHRASES_START + (GameLevel & 1) * 10 + cop_bank);
		}
		else
		{
			LoadBankFromLump(SOUND_BANK_VOICES, SBK_COP_PHRASES_START + (GameLevel & 3) * 4 + (GameLevel & 3));
			LoadBankFromLump(SOUND_BANK_VOICES, SBK_COP_PHRASES_START + (GameLevel & 3) * 5 + cop_bank);
		}
	}

	ShowLoading();

	// load ambient effects
	if (NumPlayers < 2 || NoPlayerControl != 0)
	{
		if (GameLevel == 0)
			LoadBankFromLump(SOUND_BANK_ENVIRONMENT, SBK_CITY_EFFECTS_START + city_night_fx);
		else if (GameLevel == 1)
			LoadBankFromLump(SOUND_BANK_ENVIRONMENT, SBK_CITY_EFFECTS_START + city_night_fx + 2);
		else if (GameLevel == 2)
			LoadBankFromLump(SOUND_BANK_ENVIRONMENT, SBK_CITY_EFFECTS_START + city_night_fx + 4);
		else if (GameLevel == 3)
			LoadBankFromLump(SOUND_BANK_ENVIRONMENT, SBK_CITY_EFFECTS_START + city_night_fx + 6);
	}

	// total phrases
	phrase_top = 0;

	if (missionNum - 2U < 3 || missionNum == 9 || missionNum == 10 || missionNum == 27)
	{
		LoadBankFromLump(SOUND_BANK_MISSION, SBK_ID_JONES);
		phrase_top = 7;
	}
	else if (missionNum - 20U < 2 || missionNum == 25 || missionNum == 39)
	{
		LoadBankFromLump(SOUND_BANK_MISSION, SBK_ID_JERICHO);
		phrase_top = 3;
	}

	switch (missionNum)
	{
		case 2:
			index = SBK_ID_MISSION_2;
			break;
		case 3:
			index = SBK_ID_MISSION_3;
			break;
		case 4:
			index = SBK_ID_MISSION_4;
			break;
		case 10:
			index = SBK_ID_MISSION_10;
			break;
		case 13:
			index = SBK_ID_MISSION_13;
			break;
		case 15:
			index = SBK_ID_FERRY;
			break;
		case 16:
			index = SBK_ID_FERRY;
			break;
		case 18:
			index = SBK_ID_MISSION_18;
			break;
		case 22:
			index = SBK_ID_MISSION_22;
			break;
		case 23:
			index = SBK_ID_MISSION_23;
			break;
		case 24:
			index = SBK_ID_MISSION_24;
			break;
		case 27:
			index = SBK_ID_MISSION_27;
			break;
		case 29:
			index = SBK_ID_MISSION_29;
			break;
		case 30:
			index = SBK_ID_MISSION_30;
			break;
		case 25:
		case 32:
			index = SBK_ID_MISSION_32;
			break;
		case 33:
			index = SBK_ID_MISSION_33;
			break;
		case 35:
			index = SBK_ID_MISSION_35;
			break;
		case 39:
			index = SBK_ID_MISSION_39;
			break;
		case 40:
			index = SBK_ID_MISSION_40;
			break;
		case 52:
		case 53:
			index = SBK_ID_HAVANA_TAKEADRIVE;	// [A] load Havana bank again
			break;
		case 54:
		case 55:
			index = SBK_ID_VEGAS_TAKEADRIVE;
			break;
		case 11:
		case 20:
		case 21:
		case 56:
		case 57:
			index = SBK_ID_MISSION_11;
			break;
		default:
			index = 0;
	}

	if (index != 0)
		LoadBankFromLump(SOUND_BANK_MISSION, index);

	if (GameLevel == 0 || GameLevel == 3)
		LoadBankFromLump(SOUND_BANK_SFX, SBK_ID_SPECIAL_SIREN1);
	else if (GameLevel == 2)
		LoadBankFromLump(SOUND_BANK_SFX, SBK_ID_SPECIAL_SIREN2);

	LoadSoundBankDynamic(NULL, 1, 0);
	LoadSoundBankDynamic(NULL, 3, 3);

	if (gCurrentMissionNumber - 39 < 2)
		LoadBankFromLump(SOUND_BANK_CARS, MapCarIndexToBank(4));
	else
		LoadBankFromLump(SOUND_BANK_CARS, SpecialVehicleKludge(0));

	if (missionNum != 24 && missionNum != 27 &&
		missionNum != 29 && missionNum != 30 &&
		missionNum != 35)
	{
		LoadBankFromLump(SOUND_BANK_CARS, SpecialVehicleKludge(1));
	}

	if (missionNum - 50U < 16)
	{
		LoadBankFromLump(SOUND_BANK_CARS, SpecialVehicleKludge(2));
	}

	// disable cop speech on specific missions (gangs)
	// and set cop model (car sound bank)
	if (gCurrentMissionNumber == 7 || gCurrentMissionNumber == 9 ||
		gCurrentMissionNumber == 11 || gCurrentMissionNumber == 20 ||
		gCurrentMissionNumber == 26 || gCurrentMissionNumber == 31 ||
		gCurrentMissionNumber == 33 || gCurrentMissionNumber == 40)
	{
		gDoCopSpeech = 0;

		i = 0;

		do {
			if (MissionHeader->residentModels[i] == MissionHeader->residentModels[3])
				cop_model = i;

			i++;
		} while (i < 3);
	}
	else
	{
		gDoCopSpeech = 1;
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
	// 		VECTOR *cp; // $s2
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
	PLAYER* lcp;
	CAR_DATA* cp;
	int sample;
	int pitch;
	int car_model;
	int siren;

	TimeSinceLastSpeech = 0;

	lcp = player;

	i = 0;

	while (i < NumPlayers)
	{
		if (lcp->playerType == 1)
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

			Start3DSoundVolPitch(channel, SOUND_BANK_CARS, sample * 3 + 1, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -10000, pitch);

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

			Start3DSoundVolPitch(channel, SOUND_BANK_CARS, sample, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -10000, pitch);

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
		InitEnvSnd(MAX_LEVEL_ENVSOUNDS);
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
// unsigned short /*$ra*/ GetEngineRevs(CAR_DATA *cp /*$t2*/)
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
ushort GetEngineRevs(CAR_DATA* cp)
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
// void /*$ra*/ ControlCarRevs(CAR_DATA *cp /*$s0*/)
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
void ControlCarRevs(CAR_DATA* cp)
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
		StartSound(chan, SOUND_BANK_MISSION, sound - 100, 0, 4096);
	else if (sound != 0)
		StartSound(chan, SOUND_BANK_VOICES, sound, -1500, 4096);
}



// decompiled code
// original method signature: 
// char /*$ra*/ PlaySpeech(SPEECH_QUEUE *pSpeechQueue /*$a0*/, int sound /*$a1*/)
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
		pSpeechQueue->slot[i + 1] = pSpeechQueue->slot[i];
		i--;
	}

	pSpeechQueue->slot[0] = sound;
	pSpeechQueue->count++;

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSpeechQueue(SPEECH_QUEUE *pSpeechQueue /*$s0*/)
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
// void /*$ra*/ ControlSpeech(SPEECH_QUEUE *pSpeechQueue /*$s0*/)
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
		TimeSinceLastSpeech = 0;
	}
	else if (SpuGetKeyStatus(SPU_VOICECH(pSpeechQueue->chan)) == 0)
	{
		pSpeechQueue->count--;

		DoSpeech(pSpeechQueue->chan, pSpeechQueue->slot[pSpeechQueue->count]);
		TimeSinceLastSpeech = 0;
	}
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
	if (!gDoCopSpeech)
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
	} while (true);

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
	} while (i < MAX_SIREN_NOISES);

	i = 0;
	do {
		car_noise[i].chan = -1;
		car_noise[i].chan = -1;
		car_noise[i].car = 20;
		car_noise[i].in_use = 0;
		i++;
	} while (i < MAX_CAR_NOISES);

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
	// 		CAR_DATA *car_ptr; // $s2
	// 		VECTOR *pp; // $a1
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

// [D] [T]
void DoDopplerSFX(void)
{
	int pitch, volume, sample;
	short* playerFelony;
	int i, j;
	int car;
	uint car_flags;
	int num_noisy_cars;
	int sirens;

	ulong car_dist[MAX_CARS];
	ushort indexlist[MAX_CARS];

	CAR_DATA* car_ptr;
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
	while (i < num_noisy_cars - 1)
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
	for (i = 0; i < num_noisy_cars && sirens < 2; i++)
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

		// sound up ambulance we're going to steal
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
		// vans in 'Caine's Compound' should not listen to it
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

	// stop unused siren noises
	for (i = 0; i < MAX_SIREN_NOISES; i++)
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

	// start sirens
	for (i = 0; i < num_noisy_cars; i++)
	{
		if (car_flags & 1 << indexlist[i])
		{
			car = indexlist[i];

			// dispatch siren sounds
			for (j = 0; j < MAX_SIREN_NOISES; j++)
			{
				if (siren_noise[j].in_use != 0)
					continue;

				siren_noise[j].in_use = 1;
				siren_noise[j].stopped = 0;
				siren_noise[j].car = car;

				if (car_data[car].controlType != CONTROL_TYPE_CIV_AI)
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
					siren_noise[j].chan = Start3DTrackingSound(-1, SOUND_BANK_ENVIRONMENT, 5,
						(VECTOR*)car_data[car].hd.where.t,
						car_data[car].st.n.linearVelocity);
				}

				LockChannel(siren_noise[j].chan);
				break;
			}
		}
	}

	// update sirens
	for (j = 0; j < MAX_SIREN_NOISES; j++)
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

	// siren noises occupy car noise channels
	num_noisy_cars = MIN(num_noisy_cars, MAX_CAR_NOISES - sirens);

	car_flags = 0;

	for (j = 0; j < num_noisy_cars; j++)
	{
		car = indexlist[j];

		if (car_data[car].controlType != CONTROL_TYPE_PURSUER_AI || car_data[car].ai.p.dying == 0)
			car_flags |= 1 << car;
	}

	for (j = 0; j < MAX_CAR_NOISES; j++)
	{
		int noise;

		noise = (car_flags & (1 << car_noise[j].car)) != 0;
		car_noise[j].in_use = noise;

		car_flags &= ~(noise << car_noise[j].car);
	}

	for (j = 0; j < MAX_CAR_NOISES; j++)
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

	// start new sounds
	// pick free car noise slot and play
	for (i = 0; i < num_noisy_cars; i++)
	{
		if (car_flags & 1 << indexlist[i])
		{
			car = indexlist[i];
			for (j = 0; j < MAX_CAR_NOISES; j++)
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

				car_noise[j].chan = Start3DTrackingSound(-1, SOUND_BANK_CARS, sample, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity);

				LockChannel(car_noise[j].chan);
				break;
			}
		}
	}


	// update sounds of cars (swap between idle and rev)
	for (j = 0; j < MAX_CAR_NOISES; j++)
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

			car_noise[j].chan = Start3DTrackingSound(-1, SOUND_BANK_CARS, sample, (VECTOR*)car_data[car].hd.where.t, car_data[car].st.n.linearVelocity);
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
	for (j = 0; j < MAX_SFX_CHANNELS; j++)
	{
		if (channels[j].loop == 0 && channels[j].time != 0 && channels[j].srcposition != NULL)
		{
			SetChannelPosition3(j,
				channels[j].srcposition, channels[j].srcvelocity,
				channels[j].srcvolume, channels[j].srcpitch, 0);
		}
	}
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
		// 		CAR_DATA *car_ptr; // $a3
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

// [D] [T]
void DoPoliceLoudhailer(int cars, ushort* indexlist, ulong* dist)
{
	long rnd;
	int carId;
	int i;
	int time;

	if (!gDoCopSpeech)
		return;

	rnd = Random2(78);

	if (GameType == GAME_GETAWAY)
		time = 475;
	else
		time = 275;

	i = 0;

	while (i < cars)
	{
		CAR_DATA* car_ptr;

		carId = indexlist[i];

		car_ptr = &car_data[carId];

		if (dist[carId] > 0x6000)
			dist[carId] -= 0x6000;

		if (car_ptr->controlType == CONTROL_TYPE_PURSUER_AI && car_ptr->ai.p.dying == 0 &&
			time < loudhail_time && rnd == (rnd / 31) * 31)
		{
			Start3DTrackingSound(-1, SOUND_BANK_VOICES, rnd % 2 + 13, (VECTOR*)car_ptr->hd.where.t, car_ptr->st.n.linearVelocity);
			loudhail_time = 0;
			break;
		}

		i++;
	}

	if (loudhail_time <= time)
		loudhail_time++;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CollisionSound(char player_id /*$s0*/, CAR_DATA *cp /*$s5*/, int impact /*$s2*/, int car_car /*$s7*/)
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

// [D] [T]
void CollisionSound(char player_id, CAR_DATA* cp, int impact, int car_car)
{
	int chan;
	long rnd;
	int playerid;
	int phrase;
	int sample;

	playerid = player_id < 0 ? 0 : player_id;

	if (impact < 25)
		return;

	// get player
	if (NumPlayers > 1 && NoPlayerControl == 0)
	{
		int dx, dz;
		unsigned long p0dst;
		unsigned long p1dst;

		dx = cp->hd.where.t[0] - player[0].pos[0];
		dz = cp->hd.where.t[2] - player[0].pos[2];

		p0dst = (dx * dx + dz * dz);

		dx = cp->hd.where.t[0] - player[1].pos[0];
		dz = cp->hd.where.t[2] - player[1].pos[2];

		p1dst = (dx * dx + dz * dz);

		playerid = p1dst < p0dst;
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
	Start3DSoundVolPitch(chan, SOUND_BANK_SFX, sample, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2750, impact - (impact / 1024) * 1024 + 3584);

	player[playerid].crash_timer = 2;

	if (GetPlayerId(cp) == 0 && (gCurrentMissionNumber - 2 <= 2 || gCurrentMissionNumber == 9 || gCurrentMissionNumber == 10 || gCurrentMissionNumber == 27) && (impact & 5) != 0)
	{
		rnd = Random2(1);

		if (rnd == (rnd / 3) * 3)
		{
			phrase |= 4;
		}
		else
		{
			if (car_car != 2)
			{
				if (phrase != 0)
				{
					if ((Random2(1) & 1) == 0)
						sample = 3;
					else
						sample = 0;

					BodSay(sample);
				}

				return;
			}

			if (phrase == 0)
				return;

			if ((Random2(1) & 1) != 0)
				phrase = 1;
			else
				phrase = 2;
		}

		BodSay(phrase);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ExplosionSound(VECTOR *pos /*$s4*/, int type /*$s0*/)
 // line 1019, offset 0x0004f984
	/* begin block 1 */
		// Start line: 1020
		// Start offset: 0x0004F984
		// Variables:
	// 		int bang; // $s5
	// 		int pitch; // $t0
	// 		int rnd; // $s3
	// 		VECTOR P; // stack offset -48
	// 		int sc1; // $s2
	// 		int sc2; // $s1
	/* end block 1 */
	// End offset: 0x0004FB70
	// End Line: 1048

	/* begin block 2 */
		// Start line: 2380
	/* end block 2 */
	// End Line: 2381

// [D] [T]
void ExplosionSound(VECTOR* pos, int type)
{
	long rnd;
	int sc2;
	int sc1;
	int bang;
	VECTOR P;

	bang = 255;
	rnd = Random2(4);

	if (gCurrentMissionNumber == 13 || gCurrentMissionNumber == 23)
	{
		bang = GetMissionSound(12);
	}
	else if (gCurrentMissionNumber == 30 || gCurrentMissionNumber == 35)
	{
		bang = GetMissionSound(29);
	}

	if (bang == 255)
		return;

	if (type == BIG_BANG)
	{
		sc1 = 2;
		sc2 = 2;
	}
	else if (type == LITTLE_BANG)
	{
		sc1 = 3;
		sc2 = 1;
	}
	else if (type == HEY_MOMMA)
	{
		sc1 = 1;
		sc2 = 3;
	}

	P.vx = pos->vx * sc1 + player[0].cameraPos.vx * sc2;
	P.vy = pos->vy * sc1 + player[0].cameraPos.vy * sc2;
	P.vz = pos->vz * sc1 + player[0].cameraPos.vz * sc2;

	Start3DSoundVolPitch(-1, SOUND_BANK_MISSION,
		bang, P.vx / 4, P.vy / 4, P.vz / 4,
		0, ((FrameCnt * pos->vx ^ rnd * pos->vz) & 0x3ffU) + 0xe00);
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

// [D] [T]
void JerichoSpeak(void)
{
	static unsigned int j_said = 0;
	long rnd;
	short* playerFelony;

	rnd = Random2(3);

	if (CopsCanSeePlayer == 0)
		return;

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	if (*playerFelony > FELONY_MIN_VALUE && rnd == rnd / 5 * 5)
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

// [D] [T]
void FunkUpDaBGMTunez(int funk)
{
	if (funk == 0)
	{
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
	// 		CAR_DATA *cp; // $s1
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

// [D] [T]
void SoundTasks(void)
{
	static __envsoundtags EStags;

	int chan;
	int vol;
	VECTOR* position;
	long* velocity;

	PLAYER* lcp;
	CAR_DATA* cp;
	int i;

	UpdateEnvSounds[EStags.func_cnt++](envsnd, ESdata, 0);
	EStags.func_cnt %= 4;
	
	lcp = player;
	i = 0;
	while (i < NumPlayers)
	{
		cp = lcp->playerCarId > -1 ? &car_data[lcp->playerCarId] : NULL;

		// doppler camera velocity
		if (cp && (lcp->cameraView == 2 || lcp->cameraView == 0))
		{
			lcp->camera_vel[0] = cp->st.n.linearVelocity[0];
			lcp->camera_vel[1] = cp->st.n.linearVelocity[1];
			lcp->camera_vel[2] = cp->st.n.linearVelocity[2];
		}
		else
		{
			lcp->camera_vel[0] = 0;
			lcp->camera_vel[1] = 0;
			lcp->camera_vel[2] = 0;
		}

		if (lcp->car_sound_timer > -1)
			lcp->car_sound_timer--;

		// play engine start sound
		if (cp && lcp->car_sound_timer == 4)
		{
			Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 4, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2500, 3072);
		}

		if (lcp->car_sound_timer == 0)
			lcp->car_is_sounding = 0;

		if (lcp->crash_timer > 0)
			lcp->crash_timer--;

		// car engine sounds
		if (cp)
		{
			position = (VECTOR*)cp->hd.where.t;
			velocity = cp->st.n.linearVelocity;

			if (lcp->car_is_sounding == 0)
				vol = lcp->idlevol;
			else
				vol = -10000;

			chan = i == 0 ? 1 : 4;
			SetChannelPosition3(chan, position, velocity, vol, cp->hd.revs / 4 + 4096, 0);

			if (lcp->car_is_sounding < 2)
				vol = lcp->revsvol;
			else
				vol = -10000;

			chan = i == 0 ? 0 : 3;
			SetChannelPosition3(chan, position, velocity, vol, cp->hd.revs / 4 + lcp->revsvol / 64 + 1500, 0);

			// siren sound control
			if (CarHasSiren(cp->ap.model) != 0)
			{
				chan = i == 0 ? 2 : 5;

				if (lcp->horn.on == 0)
					SpuSetVoicePitch(chan, 0);		// don't stop it really
				else
					SetChannelPosition3(chan, position, velocity, 0, 4096, 0);
			}
		}
		else
		{
			chan = i == 0 ? 1 : 4;
			SetChannelVolume(chan, -10000, 0);

			chan = i == 0 ? 0 : 3;
			SetChannelVolume(chan, -10000, 0);

			chan = i == 0 ? 2 : 5;
			SetChannelVolume(chan, -10000, 0);
		}

		lcp++;
		i++;
	}

	if (NumPlayers < 2 || NoPlayerControl != 0)
	{
		UpdateEnvSounds[EStags.func_cnt++](envsnd, ESdata, 0);
		EStags.func_cnt %= 4;

		DoDopplerSFX();
		Tunnels(&tunnels);
	}

	ControlSpeech(&gSpeechQueue);

	// various mission and cutscene stuff
	if (gInGameCutsceneActive != 0)
	{
		HandleRequestedXA();
		DoCutsceneSound();
	}
	else
	{
		DoMissionSound();
	}

	// do annoying lead car horn
	if (gInGameChaseActive != 0 && player[0].targetCarId >= 0)
		LeadHorn(&car_data[player[0].targetCarId]);		// use target id instead

	// FIXME: move it to MC_SND?
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
	char* addr;
	int musicpos[3];

	
	char* musicname = "SOUND\\MUSIC.BIN";

#ifndef PSX
	char* d1musicName = "SOUND\\D1MUSIC.BIN";
	// search for Driver 1 music file
	if (gDriver1Music && FileExists(d1musicName))
	{
		name = d1musicName;
		xm_coptrackpos = xm_coptrackpos_d1;
	}
	else
#endif
	{
		name = musicname;
		xm_coptrackpos = xm_coptrackpos_d2;
		gDriver1Music = 0;
	}

	copmusic = 0;

	printInfo("NewLevel in InitMusic()\n");
	AllocateReverb(3, 16384);

	current_music_id = musicnum;
	LoadfileSeg(name, (char*)musicpos, musicnum * 8, sizeof(musicpos));

	MALLOC_BEGIN()

		sample_len = musicpos[2] - musicpos[1];
	music_len = musicpos[1] - musicpos[0];

	if (NewLevel != 0)
	{
		music_pt = D_MALLOC(music_len + 3U & 0xfffffffc);
		sample_pt = D_TEMPALLOC(sample_len);

#ifdef USE_CRT_MALLOC
		LoadfileSeg(name, music_pt, musicpos[0], music_len);
		LoadfileSeg(name, sample_pt, musicpos[0] + music_len, sample_len);
#else
		LoadfileSeg(name, music_pt, musicpos[0], music_len + sample_len);
#endif
	}

	if (Song_ID == -1)
	{
		VABID = XM_GetFreeVAB();

		if (NewLevel != 0)
		{
			xm_samples = LoadSoundBank(sample_pt, sample_len, 0);
			D_TEMPFREE();
		}

		UpdateXMSamples(xm_samples);

		XM_GetFileHeaderSize();
		XM_SetFileHeaderAddress((unsigned char*)header_pt);
		XM_GetSongSize();
		XM_SetSongAddress((unsigned char*)song_pt);
	}

	MALLOC_END();

	InitXMData((unsigned char*)music_pt, 0, 0);

	// 8 XM channels start after first sfx channels
	Song_ID = XM_Init(VABID, 0, 0, MAX_SFX_CHANNELS, 1, -1, 0, 0);

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
	// 		tunnelinfo *T; // $a1
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

// [D] [T]
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
	// 		tunnelinfo *T; // $t0
	/* end block 1 */
	// End offset: 0x000528FC
	// End Line: 1344

	/* begin block 2 */
		// Start line: 6755
	/* end block 2 */
	// End Line: 6756

// [D] [T]
int AddTunnel(long x1, long y1, long z1, long x2, long y2, long z2)
{
	if (tunnels.tunnel_cnt >= tunnels.num_tunnels)
		return -1;

	tunnels.coords[tunnels.tunnel_cnt].p1.vx = x1;
	tunnels.coords[tunnels.tunnel_cnt].p1.vy = y1;
	tunnels.coords[tunnels.tunnel_cnt].p1.vz = z1;

	tunnels.coords[tunnels.tunnel_cnt].p2.vx = x2;
	tunnels.coords[tunnels.tunnel_cnt].p2.vy = y2;
	tunnels.coords[tunnels.tunnel_cnt].p2.vz = z2;

	return tunnels.tunnel_cnt++;
}



// decompiled code
// original method signature: 
// void /*$ra*/ Tunnels(tunnelinfo *T /*$a0*/)
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

// [D] [T]
void Tunnels(tunnelinfo* T)
{
	int i;
	int verb;

	gTunnelNum = -1;
	NoRainIndoors = 0;
	verb = 0;

	i = 0;
	while (i < T->tunnel_cnt)
	{
		if (MIN(T->coords[i].p1.vx, T->coords[i].p2.vx) < camera_position.vx &&
			MAX(T->coords[i].p1.vx, T->coords[i].p2.vx) > camera_position.vx &&

			MIN(T->coords[i].p1.vy, T->coords[i].p2.vy) < camera_position.vy &&
			MAX(T->coords[i].p1.vy, T->coords[i].p2.vy) > camera_position.vy &&

			MIN(T->coords[i].p1.vz, T->coords[i].p2.vz) < camera_position.vz &&
			MAX(T->coords[i].p1.vz, T->coords[i].p2.vz) > camera_position.vz)
		{
			verb = 1;
			gTunnelNum = i;
			NoRainIndoors = 1;
			break;
		}

		i++;
	}

	SetReverbInGameState(verb);
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

// [D] [T]
void AddTunnels(int level)
{
	if (level == 0)
	{
		InitTunnels(29);

		AddTunnel(-78200, 0, -125000, -43800, -800, -159500);
		AddTunnel(-65000, 0, -122700, -68000, -800, -125000);
		AddTunnel(-48600, 0, -237000, -50350, -800, -235900);

		AddTunnel(-219895, 0, 675067, -208647, -2500, 668935);

		AddTunnel(-294644, 0, 319973, -288508, -800, 316917);
		AddTunnel(-282105, 0, 321774, -275985, -800, 315638);
		AddTunnel(-268534, 0, 320244, -262410, -800, 314176);
		AddTunnel(-293886, 0, 308728, -289806, -800, 305656);
		AddTunnel(-278274, 0, 308728, -277246, -800, 305664);
		AddTunnel(-298238, 0, 301568, -289018, -800, 298496);
		AddTunnel(-292102, 0, 298496, -289018, -800, 295416);
		AddTunnel(-283386, 0, 297460, -280314, -800, 294396);
		AddTunnel(-283390, 0, 294396, -274182, -800, 291328);
		AddTunnel(-290443, 0, 278252, -282239, -800, 275192);
		AddTunnel(-281338, 0, 276976, -278238, -800, 273920);
		AddTunnel(-288502, 0, 269048, -285434, -800, 265984);
		AddTunnel(-289411, 0, 259814, -288395, -800, 256762);
		AddTunnel(-297210, 0, 252666, -291090, -800, 249590);
		AddTunnel(-284414, 0, 252666, -278286, -800, 249590);
		AddTunnel(-268538, 0, 252666, -262398, -800, 249590);
		AddTunnel(-298498, 0, 240889, -290310, -800, 237825);
		AddTunnel(-266490, 0, 243189, -260358, -800, 240133);
		AddTunnel(-281846, 0, 233719, -280830, -800, 230655);
		AddTunnel(-280830, 0, 230655, -274690, -800, 227587);
		AddTunnel(-285438, 0, 207353, -284422, -800, 204285);
		AddTunnel(-292609, 0, 200184, -274181, -800, 194052);
		AddTunnel(-267521, 0, 198136, -264453, -800, 192000);
		AddTunnel(-268542, 0, 192000, -265477, -800, 185864);

		AddTunnel(-217585, 0, -352018, -199197, -800, -358146);
	}
	else if (level == 1)
	{
		InitTunnels(4);

		AddTunnel(-398650, 0, -161000, -340300, 2000, -103000);
		AddTunnel(272800, 0, 41200, 255000, 2000, 168600);
		AddTunnel(-477600, 0, -112700, -397000, 8000, -132800);
		AddTunnel(-185875, 0, -41450, -179650, -1000, -44600);
	}
	else if (level == 2)
	{
		InitTunnels(2);

		AddTunnel(157578, 0, 740250, 168330, -2000, 725915);
		AddTunnel(165200, 0, 725915, 168330, -2000, 722650);
	}
	else if (level == 3)
	{
		InitTunnels(5);

		AddTunnel(151400, 0, -250740, 154800, -400, -235750);
		AddTunnel(-115100, 0, -193200, -113300, -400, -132500);
		AddTunnel(-71900, 0, -16250, -73650, -400, -28500);
		AddTunnel(78300, 0, -167900, 82450, -500, -169950);
		AddTunnel(173550, 0, 247400, 177700, -500, 245300);
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
	// 		__envsoundtags *T; // $t1
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

static __envsoundtags EStags;

// [D] [T]
void InitEnvSnd(int num_envsnds)
{
	int i, p;

	if (num_envsnds > MAX_LEVEL_ENVSOUNDS)
		num_envsnds = MAX_LEVEL_ENVSOUNDS;

	i = 0;
	while (i < num_envsnds)
	{
		envsnd[i].type = 0;
		i++;
	}

	i = 0;
	while (i < NumPlayers)
	{
		p = 0;
		while (p < 4)
		{
			ESdata[i].playing_sound[p] = -1;
			ESdata[i].thisS[p] = -1;
			p++;
		}
		i++;
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

// [D] [T]
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

// [D] [T]
void SetEnvSndPos(int snd, long px, long pz)
{
	if (envsnd[snd].type != 3)
		return;

	envsnd[snd].pos2.vx = px;
	envsnd[snd].pos.vx = px;
	envsnd[snd].pos2.vz = pz;
	envsnd[snd].pos.vz = pz;
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
	// 		envsound *ep; // $t1
	// 		__envsoundtags *T; // $t0
	// 		long s; // $a1
	/* end block 1 */
	// End offset: 0x00050E08
	// End Line: 1635

	/* begin block 2 */
		// Start line: 3577
	/* end block 2 */
	// End Line: 3578

// [D] [T]
int AddEnvSnd(int type, char flags, int bank, int sample, int vol, long px, long pz, long px2, long pz2)
{
	envsound* ep;

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
		ep->flags |= 1;

	if (ep->pos.vz == ep->pos2.vz)
		ep->flags |= 2;

	if (type != 3)
		ep->flags |= 0x20;

	return EStags.envsnd_cnt++;
}



// decompiled code
// original method signature: 
// void /*$ra*/ IdentifyZone(envsound *ep /*$a3*/, envsoundinfo *E /*stack 4*/, int pl /*$a2*/)
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
	// 		__bitfield64 zones; // stack offset -64
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

// [D] [T]
void IdentifyZone(envsound* ep, envsoundinfo* E, int pl)
{
	int i, j;
	int vol;

	int tmp[4];
	float _g[4];
	__bitfield64 zones;
	int snd;

	// [A] does it really needed? we don't have that much sounds to be played
	zones.l = 0;
	zones.h = 0;

	i = 0;
	do {
		tmp[i++] = -1;
	} while (i < 4);

	E->cam_pos.vx = player[pl].cameraPos.vx;
	E->cam_pos.vy = player[pl].cameraPos.vy;
	E->cam_pos.vz = player[pl].cameraPos.vz;

	j = 0;
	for (i = 0; i < EStags.envsnd_cnt && tmp[3] < 0; i++)
	{
		if (ep[i].type == 0 || ep[i].vol <= -7500)
			continue;

		vol = (ep[i].vol + 7500) * 4;
		vol = MAX(MIN(vol, 22000), 0);

		if (MIN(ep[i].pos.vx, ep[i].pos2.vx) - vol < E->cam_pos.vx &&
			MAX(ep[i].pos.vx, ep[i].pos2.vx) + vol > E->cam_pos.vx &&

			MIN(ep[i].pos.vz, ep[i].pos2.vz) - vol < E->cam_pos.vz &&
			MAX(ep[i].pos.vz, ep[i].pos2.vz) + vol > E->cam_pos.vz)
		{
			if ((ep[i].type == 2 || ep[i].type == 4) && (ep[i].flags & 3) == 0)
			{
				// [A] new distance estimation code, should be efficient enough
				// Plane method

				// build a plane from line segment
				float ldx, ldz, ndx, ndz, dist, l_inv_len, offset;
				ldx = ep[i].pos2.vx - ep[i].pos.vx;
				ldz = ep[i].pos2.vz - ep[i].pos.vz;
				
				// find inverse length of line
				l_inv_len = 1.0 / sqrtf(ldx * ldx + ldz * ldz);
				
				// find normal (perpendicular) by using cross product and normalize
				ndx = ldz * l_inv_len;
				ndz = -ldx * l_inv_len;

				// line pos1 offset along normal
				offset = ndx * ep[i].pos.vx + ndz * ep[i].pos.vz;

				dist = ndx * E->cam_pos.vx + ndz * E->cam_pos.vz - offset;

				if (ep->type == 2)
				{
					if (dist < 0)
						dist = -dist;
				}
				else if ((ep->flags & 8) != 0) // flipped flag
				{
					dist = -dist;
				}

				if (dist < vol)
				{
					if (i < 32)
						zones.l |= 1 << (i & 0x1f);
					else
						zones.h |= 1 << (i & 0x1f);

					tmp[j] = i;
					
					// also store length
					_g[j] = l_inv_len;
					j++;
				}
			}
			else
			{
				if (i < 32)
					zones.l |= 1 << (i & 0x1f);
				else
					zones.h |= 1 << (i & 0x1f);

				tmp[j] = i;
				j++;
			}
		}
	}

	// off the sound
	for (i = 0; i < 4; i++)
	{
		snd = E->thisS[i];

		if (snd == -1)
			continue;

		if (snd < 32)
		{
			if ((zones.l & 1 << (snd & 0x1f)) == 0)
			{
				E->thisS[i] = -1;
				continue;
			}
		}
		else
		{
			if ((zones.h & 1 << (snd & 0x1f)) == 0)
			{
				E->thisS[i] = -1;
				continue;
			}
		}

		if (snd < 32)
			zones.l &= ~(1 << (snd & 0x1f));
		else
			zones.h &= ~(1 << (snd & 0x1f));
	}

	// assign to the envsound
	for (i = 0; i < 4; i++)
	{
		snd = tmp[i];

		if (snd == -1)
			continue;

		if (snd < 32)
			snd = zones.l & 1 << (snd & 0x1f);
		else
			snd = zones.h & 1 << (snd & 0x1f);

		if (snd == 0)
			continue;

		// assign free slot
		for (j = 0; j < 4; j++)
		{
			if (E->thisS[j] < 0)
			{
				E->thisS[j] = tmp[i];
				E->g[j] = _g[i];
				break;
			}
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalcEffPos(envsound *ep /*$s1*/, envsoundinfo *E /*$a1*/, int pl /*$a2*/)
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
void CalcEffPos(envsound* ep, envsoundinfo* E, int pl)
{
	int minX, maxX;
	int minZ, maxZ;
	int i;

	for (i = 0; i < 4; i++)
	{
		int snd;
		
		E->flags &= ~(1 << (i & 0x1f));
	
		snd = E->thisS[i];
		
		if (snd == -1)
			continue;

		// BOX type
		if (ep[snd].type == 1)
		{
			// clamp to bounds when outside
			minX = MIN(ep[snd].pos.vx, ep[snd].pos2.vx);
			maxX = MAX(ep[snd].pos.vx, ep[snd].pos2.vx);
			
			if (minX > E->cam_pos.vx)
				E->eff_pos[i].vx = minX;
			else if (maxX < E->cam_pos.vx)
				E->eff_pos[i].vx = maxX;
			else
				E->eff_pos[i].vx = E->cam_pos.vx;

			minZ = MIN(ep[snd].pos.vz, ep[snd].pos2.vz);
			maxZ = MAX(ep[snd].pos.vz, ep[snd].pos2.vz);

			if (minZ > E->cam_pos.vz)
				E->eff_pos[i].vz = minZ;
			else if (maxZ < E->cam_pos.vz)
				E->eff_pos[i].vz = maxZ;
			else
				E->eff_pos[i].vz = E->cam_pos.vz;
		}
		else if (ep[snd].type == 2)
		{
			// point type
			// really can be a line in one axis (which is not used)
			if ((ep[snd].flags & 1) != 0)
			{
				E->eff_pos[i].vx = ep[snd].pos.vx;
				
				minZ = MIN(ep[snd].pos.vz, ep[snd].pos2.vz);
				maxZ = MAX(ep[snd].pos.vz, ep[snd].pos2.vz);

				if (minZ > E->cam_pos.vz)
					E->eff_pos[i].vz = minZ;
				else if (maxZ < E->cam_pos.vz)
					E->eff_pos[i].vz = maxZ;
				else
					E->eff_pos[i].vz = E->cam_pos.vz;
			}
			else if ((ep[snd].flags & 2) != 0)
			{
				E->eff_pos[i].vz = ep[snd].pos.vz;

				minX = MIN(ep[snd].pos.vx, ep[snd].pos2.vx);
				maxX = MAX(ep[snd].pos.vx, ep[snd].pos2.vx);

				if (minX > E->cam_pos.vx)
					E->eff_pos[i].vx = minX;
				else if (maxX < E->cam_pos.vx)
					E->eff_pos[i].vx = maxX;
				else
					E->eff_pos[i].vx = E->cam_pos.vx;
			}
			else
			{
				// type 2 and type 4 (floating point ones) are processed in CalcEffPos2
				// which are unused, too
				continue;
			}
		}
		else
			continue;

		E->flags |= 1 << (i & 0x1f);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalcEffPos2(envsound *ep /*stack 0*/, envsoundinfo *E /*$s7*/, int pl /*$a2*/)
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
void CalcEffPos2(envsound* ep, envsoundinfo* E, int pl)
{
	int snd;
	int i;

	i = 0;
	do {
		snd = E->thisS[i];

		if (snd > -1 && (E->flags & 1 << i) == 0)
		{
			if (ep[snd].type == 2 || ep[snd].type == 4)
			{
				// [A] determine sound position on line
				// Plane method

				// build a plane from line segment
				float ldx, ldz, ndx, ndz, dist, l_inv_len, offset;
				ldx = ep[snd].pos2.vx - ep[snd].pos.vx;
				ldz = ep[snd].pos2.vz - ep[snd].pos.vz;

				// find inverse length of line
				l_inv_len = E->g[i];

				// find normal (perpendicular) by using cross product and normalize
				ndx = ldz * l_inv_len;
				ndz = -ldx * l_inv_len;

				// line pos1 offset along normal
				offset = ndx * ep[snd].pos.vx + ndz * ep[snd].pos.vz;

				// now need distance
				dist = ndx * E->cam_pos.vx + ndz * E->cam_pos.vz - offset;

				// clamp to side
				E->eff_pos[i].vx = E->cam_pos.vx - ndx * dist;
				E->eff_pos[i].vz = E->cam_pos.vz - ndz * dist;

				if (ep[snd].type == 2)
				{
					int minX, maxX, minZ, maxZ;
					
					maxX = MAX(ep[snd].pos.vx, ep[snd].pos2.vx);
					minX = MIN(ep[snd].pos.vx, ep[snd].pos2.vx);

					if (E->eff_pos[i].vx > maxX)
					{
						E->eff_pos[i].vx = maxX;
					}
					else if (E->eff_pos[i].vx < minX)
					{
						E->eff_pos[i].vx = minX;
					}

					maxZ = MAX(ep[snd].pos.vz, ep[snd].pos2.vz);
					minZ = MIN(ep[snd].pos.vz, ep[snd].pos2.vz);

					if (E->eff_pos[i].vz > maxZ)
					{
						E->eff_pos[i].vz = maxZ;
					}
					else if (E->eff_pos[i].vz < minZ)
					{
						E->eff_pos[i].vz = minZ;
					}
					
					E->flags |= 1 << (i & 0x1f);
				}
				else if (ep[snd].type == 4)
				{
					if ((ep[snd].flags & 8) == 0) 
					{
						int minX, maxX, maxZ;

						maxZ = MAX(ep[snd].pos.vz, ep[snd].pos2.vz);
						
						if (E->cam_pos.vz > maxZ)
						{
							E->eff_pos[i].vz = maxZ;
						}
						else if (E->cam_pos.vz > E->eff_pos[i].vz)
						{
							E->eff_pos[i].vz = E->cam_pos.vz;
						}

						// clamp axis select based on distance sign
						if (E->g[i] < 0)
						{
							maxX = MAX(ep[snd].pos.vx, ep[snd].pos2.vx);

							if (E->cam_pos.vx > maxX)
							{
								E->eff_pos[i].vx = maxX;
							}
							else if (E->cam_pos.vx > E->eff_pos[i].vx) 
							{
								E->eff_pos[i].vx = (E->cam_pos).vx;
							}
						}
						else
						{
							minX = MIN(ep[snd].pos.vx, ep[snd].pos2.vx);
							
							if (minX > E->cam_pos.vx)
							{
								E->eff_pos[i].vx = minX;
							}
							else if (E->cam_pos.vx < E->eff_pos[i].vx)
							{
								E->eff_pos[i].vx = E->cam_pos.vx;
							}
						}
					}
					else
					{
						int minX, maxX, minZ;

						minZ = MIN(ep[snd].pos.vz, ep[snd].pos2.vz);
						
						if (E->cam_pos.vz < minZ)
						{
							E->eff_pos[i].vz = minZ;
						}
						else if (E->cam_pos.vz < E->eff_pos[i].vz)
						{
							E->eff_pos[i].vz = E->cam_pos.vz;
						}

						// clamp axis select based on distance sign
						if (E->g[i] > 0)
						{
							maxX = MAX(ep[snd].pos.vx, ep[snd].pos2.vx);

							if (E->cam_pos.vx > maxX)
							{
								E->eff_pos[i].vx = maxX;
							}
							else if (E->cam_pos.vx > E->eff_pos[i].vx) 
							{
								E->eff_pos[i].vx = E->cam_pos.vx;
							}
						}
						else
						{
							minX = MIN(ep[snd].pos.vx, ep[snd].pos2.vx);
							
							if (E->cam_pos.vx < minX)
							{
								E->eff_pos[i].vx = minX;
							}
							else if (E->cam_pos.vx < E->eff_pos[i].vx)
							{
								E->eff_pos[i].vx = E->cam_pos.vx;
							}
						}
					}

					
				}
			}
			else
			{
				E->eff_pos[i].vx = ep[snd].pos.vx;
				E->eff_pos[i].vz = ep[snd].pos.vz;
				
				E->flags |= (1 << i);
			}
		}

		E->eff_pos[i].vy = -E->cam_pos.vy;

		i++;
	} while (i < 4);

}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateEnvSnd(envsound *ep /*stack 0*/, envsoundinfo *E /*$s4*/, int pl /*stack 8*/)
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

// [D] [T]
void UpdateEnvSnd(envsound* ep, envsoundinfo* E, int pl)
{
	int channel;
	long* velocity;
	int i;
	int snd;

	for (i = 0; i < 4; i++)
	{
		snd = E->thisS[i];

		if (snd >= 0)
		{
			// start the new sound if it's changed
			if (E->playing_sound[i] != snd)
			{
				channel = Start3DSoundVolPitch(-1, ep[snd].bank, ep[snd].sample, E->eff_pos[i].vx, E->eff_pos[i].vy, E->eff_pos[i].vz, 0, 4096);
				E->chan[i] = channel;

				LockChannel(channel);

				if (NumPlayers > 1 && NoPlayerControl == 0)
					SetPlayerOwnsChannel(channel, pl);

				E->playing_sound[i] = snd;
			}

			if (ep[snd].flags & 0x10)
				velocity = player[pl].camera_vel;
			else
				velocity = NULL;

			SetChannelPosition3(E->chan[i], &E->eff_pos[i], velocity, ep[snd].vol - 2500, 4096, ep[snd].flags & 0x20);
		}
		else
		{
			if (E->playing_sound[i] > -1)
			{
				StopChannel(E->chan[i]);
				UnlockChannel(E->chan[i]);
				
				E->playing_sound[i] = -1;
			}
		}
	}
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

// [D] [T]
void InitLeadHorn(void)
{
	horn_time = 0;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ LeadHorn(CAR_DATA *cp /*$s0*/)
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

// [D] [T]
void LeadHorn(CAR_DATA* cp)
{
	static unsigned int rnd = 0;

	int carBank;

	if (horn_time == 0)
		rnd = (cp->hd.where.t[0] ^ cp->hd.where.t[2]) * (FrameCnt ^ cp->hd.where.t[1]) & 0x7f;

	horn_time++;

	if (horn_time == rnd)
	{
		if (cp->ap.model == 4)
			carBank = ResidentModelsBodge();
		else if (cp->ap.model < 3)
			carBank = cp->ap.model;
		else
			carBank = cp->ap.model - 1;

		Start3DTrackingSound(-1, SOUND_BANK_CARS, carBank * 3 + 2, (VECTOR*)cp->hd.where.t, cp->st.n.linearVelocity);

		horn_time = 0;
	}
}





