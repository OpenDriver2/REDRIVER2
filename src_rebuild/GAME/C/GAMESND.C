

#include "THISDUST.H"
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

typedef void(*envsoundfunc)(struct __envsound *ep /*$s1*/, struct __envsoundinfo *E /*$a1*/, int pl /*$a2*/);

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

// TODO: AI.C?
SPEECH_QUEUE gSpeechQueue;
static char cop_bank = 0;
char phrase_top = 0;

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

// [D]
void LoadBankFromLump(int bank, int lump)
{
	static unsigned int blockLimit[73] = {0};

	int size;
	char* name;

	name = "SOUND\\VOICES2.BLK";

	if (blockLimit[1] == 0)
		LoadfileSeg(name, (char *)blockLimit, 0, sizeof(blockLimit));

	size = blockLimit[lump+1] - blockLimit[lump];
	LoadfileSeg(name, _sbank_buffer, blockLimit[lump], size);

	LoadSoundBankDynamic(_sbank_buffer, size, bank);
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

int CarHasSiren(int index)
{
	return 1;
/*
	int iVar1;
	int iVar2;
	int *piVar3;

	if (index == 4) {
		if (GameLevel == 2) {
			iVar2 = MissionHeader->residentModels[4];
			iVar1 = 9;
		}
		else {
			if (GameLevel < 3) {
				if (GameLevel != 0) {
					piVar3 = &MissionHeader->weather;
					goto LAB_00052374;
				}
				iVar2 = MissionHeader->residentModels[4];
				iVar1 = 8;
			}
			else {
				if (GameLevel != 3) {
					piVar3 = &MissionHeader->weather;
					goto LAB_00052374;
				}
				iVar2 = MissionHeader->residentModels[4];
				iVar1 = 10;
			}
		}
		if (iVar2 == iVar1) {
			return 0x110;
		}
	}
	piVar3 = &MissionHeader->id + index;
LAB_00052374:
	return (uint)(piVar3[0x18] == 0) << 9;
*/
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

// [D]
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

// [D]
int ResidentModelsBodge(void)
{
	int iVar1;
	int iVar2;

	iVar2 = MissionHeader->residentModels[4];
	if ((((gCurrentMissionNumber == 0x18) || (gCurrentMissionNumber == 0x1b)) ||
		(gCurrentMissionNumber == 0x1d)) ||
		((gCurrentMissionNumber == 0x1e || (gCurrentMissionNumber == 0x23)))) {
		return 3;
	}
	if ((gCurrentMissionNumber - 0x32U < 0x10) && (iVar2 == 0xc)) {
		return 5;
	}
	if (GameLevel == 1) {
		if (1 < iVar2 - 8U) {
			return 3;
		}
	}
	else {
		if (GameLevel < 2) {
			if (GameLevel != 0) {
				return 3;
			}
			iVar1 = 0xb;
			if (iVar2 == 9) {
				return 4;
			}
		}
		else {
			if (GameLevel == 2) {
				iVar1 = 8;
			}
			else {
				if (GameLevel != 3) {
					return 3;
				}
				iVar1 = 0xb;
			}
		}
		if (iVar2 != iVar1) {
			return 3;
		}
	}
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

// [D]
int MapCarIndexToBank(int index)
{
	static char car_banks[4][9]=
	{
		{12, 4, 13, 5, 16, 9, 2, 15, 10},
		{10, 11, 7, 6, 17, 17, 2, 5, 4},
		{14, 3, 4, 6, 11, 9, 2, 17, 10},
		{8, 7, 13, 9, 2, 17, 17, 11, 16},
	};

	int iVar1;
	int iVar2;

	iVar1 = MissionHeader->residentModels[index];

	if ((gCurrentMissionNumber - 39 < 2) && (iVar1 == 0xd)) 
	{
		iVar2 = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);
		iVar1 = iVar2;
		if (iVar2 < 1) {
			iVar1 = 1;
		}
		if (4 < iVar2) {
			iVar1 = 4;
		}
	}

	iVar2 = iVar1-1;

	if (iVar1 == 0) 
		iVar2 = 1;

	if (6 < iVar2)
		iVar2 = iVar2-3;

	return car_banks[GameLevel][iVar2];
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

// [D]
void LoadLevelSFX(int missionNum)
{
	int lump;
	uint uVar1;
	int index;
	int *piVar2;
	uint uVar3;

	uVar3 = (gTimeOfDay == 3);
	index = missionNum;

	if (missionNum < 0)
		index = missionNum + 3;

	cop_bank = missionNum - (index / 4) * 4 + 1;
	cop_model = 3;
	LoadSoundBankDynamic(NULL, 0, 0);
	index = 0;

	do {
		lump = MapCarIndexToBank(index);
		LoadBankFromLump(3, lump);
		index++;
	} while (index < 3);

	ShowLoading();

	LoadBankFromLump(1, 0);
	LoadBankFromLump(1, 1);
	LoadBankFromLump(6, 66);

	if ((GameLevel & 2U) == 0) 
		uVar1 = GameLevel & 3;
	else
		uVar1 = (GameLevel & 1U) * 2;

	LoadBankFromLump(2, uVar1 + 69);

	if (((((3 < missionNum - 1U) && (missionNum != 6)) && (missionNum != 7)) &&
		(((missionNum != 9 && (missionNum != 10)) &&
		((missionNum != 0xb && ((missionNum != 0xd && (missionNum != 0xe)))))))) &&
		(((missionNum != 0x12 &&
		((((missionNum != 0x13 && (missionNum != 0x14)) && (missionNum != 0x16)) &&
		((missionNum != 0x1a && (missionNum != 0x1c)))))) &&
		((((missionNum != 0x1f && ((missionNum != 0x21 && (missionNum != 0x22)))) &&
		(missionNum != 0x26)) && (missionNum != 0x28)))))) 
	{
		if ((GameLevel & 2U) == 0) 
		{
			uVar1 = GameLevel & 3;
			index = uVar1 * 4;
		}
		else 
		{
			uVar1 = (GameLevel & 1U) * 2;
			index = (GameLevel & 1U) * 8;
		}

		LoadBankFromLump(2, index + uVar1 + 0x1d);

		if ((GameLevel & 2U) == 0) 
			index = (GameLevel & 3U) * 5 + cop_bank + 0x1d;
		else
			index = (GameLevel & 1U) * 10 + cop_bank + 0x1d;

		LoadBankFromLump(2, index);
	}

	ShowLoading();

	if ((NumPlayers < 2) || (NoPlayerControl != 0)) 
	{
		if (GameLevel == 1)
		{
			LoadBankFromLump(4, uVar3 + 0x17);
		}
		else 
		{
			if (GameLevel < 2) 
			{
				if (GameLevel == 0)
					LoadBankFromLump(4, uVar3 + 0x15);
			}
			else 
			{
				if (GameLevel == 2) 
				{
					LoadBankFromLump(4, uVar3 + 0x19);
				}
				else if (GameLevel == 3)
				{
					LoadBankFromLump(4, uVar3 + 0x1b);
				}
			}
		}
	}

	phrase_top = 0;

	if ((((missionNum - 2U < 3) || (missionNum == 9)) || (missionNum == 10)) || (missionNum == 0x1b))
	{
		LoadBankFromLump(5, 20);
		phrase_top = 7;
	}
	if (((missionNum - 0x14U < 2) || (missionNum == 0x19)) || (missionNum == 0x27))
	{
		LoadBankFromLump(5, 19);
		phrase_top = 3;
	}
	if (missionNum == 2)
	{
		index = 45;
		goto LAB_0004dc60;
	}
	if (missionNum == 3)
	{
		index = 46;
		goto LAB_0004dc60;
	}
	if (missionNum == 4)
	{
		index = 47;
		goto LAB_0004dc60;
	}
	if (missionNum == 10) 
	{
		index = 48;
		goto LAB_0004dc60;
	}
	if (missionNum != 11)
	{
		if (missionNum == 13)
		{
			index = 50;
			goto LAB_0004dc60;
		}
		if ((missionNum == 15) || (missionNum == 16))
		{
			index = 51;
			goto LAB_0004dc60;
		}
		if (missionNum == 18)
		{
			index = 52;
			goto LAB_0004dc60;
		}
		if ((missionNum != 20) && (missionNum != 21))
		{
			if (missionNum == 22)
			{
				index = 53;
				goto LAB_0004dc60;
			}
			if (missionNum == 23)
			{
				index = 0x36;
				goto LAB_0004dc60;
			}
			if (missionNum == 0x18)
			{
				index = 0x37;
				goto LAB_0004dc60;
			}
			if (missionNum != 0x19)
			{
				if (missionNum == 0x1b)
				{
					index = 0x38;
					goto LAB_0004dc60;
				}
				if (missionNum == 0x1d) 
				{
					index = 0x39;
					goto LAB_0004dc60;
				}
				if (missionNum == 0x1e)
				{
					index = 0x3a;
					goto LAB_0004dc60;
				}
				if (missionNum != 0x20) 
				{
					if (missionNum == 0x21) 
					{
						index = 0x3c;
						goto LAB_0004dc60;
					}
					if (missionNum == 0x23)
					{
						index = 0x3d;
						goto LAB_0004dc60;
					}
					if (missionNum == 0x27)
					{
						index = 0x3e;
						goto LAB_0004dc60;
					}
					if (missionNum == 0x28) 
					{
						index = 0x3f;
						goto LAB_0004dc60;
					}
					if ((missionNum != 0x34) && (missionNum != 0x35)) {
						if ((missionNum == 0x36) || (missionNum == 0x37)) {
							index = 0x41;
							goto LAB_0004dc60;
						}
						if ((missionNum != 0x38) && (index = 0, missionNum != 0x39))
							goto LAB_0004dc60;
					}
					goto LAB_0004dbc4;
				}
			}
			index = 0x3b;
			goto LAB_0004dc60;
		}
	}
LAB_0004dbc4:
	index = 0x31;

LAB_0004dc60:
	if (index != 0) 
		LoadBankFromLump(5, index);

	if ((GameLevel == 0) || (GameLevel == 3)) 
		LoadBankFromLump(1, 0x43);

	if (GameLevel == 2)
		LoadBankFromLump(1, 0x44);

	LoadSoundBankDynamic(NULL, 1, 0);
	LoadSoundBankDynamic(NULL, 3, 3);

	if (gCurrentMissionNumber - 0x27U < 2) 
	{
		index = MapCarIndexToBank(4);
		LoadBankFromLump(3, index);
	}
	else 
	{
		index = SpecialVehicleKludge(0);
		LoadBankFromLump(3, index);
	}

	if ((((missionNum != 0x18) && (missionNum != 0x1b)) && (missionNum != 0x1d)) && ((missionNum != 0x1e && (missionNum != 0x23)))) 
	{
		index = SpecialVehicleKludge(1);
		LoadBankFromLump(3, index);
	}

	if (missionNum - 0x32U < 0x10) 
	{
		index = SpecialVehicleKludge(2);
		LoadBankFromLump(3, index);
	}

	if (((gCurrentMissionNumber == 7) || (gCurrentMissionNumber == 9)) ||
		((gCurrentMissionNumber == 0xb ||
		((((gCurrentMissionNumber == 0x14 || (gCurrentMissionNumber == 0x1a)) ||
		(gCurrentMissionNumber == 0x1f)) ||
		((gCurrentMissionNumber == 0x21 || (gCurrentMissionNumber == 0x28)))))))) 
	{
		index = 0;
		piVar2 = MissionHeader->residentModels;
		do {
			if (*piVar2 == MissionHeader->residentModels[3])
			{
				cop_model = (char)index;
			}
			index = index + 1;
			piVar2 = piVar2 + 1;
		} while (index < 3);
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

char first_offence = 0;
int TimeSinceLastSpeech = 0;

// [D]
void StartGameSounds(void)
{
	unsigned char bVar1;
	char playerId;
	uint uVar2;
	int channel;
	uint index;
	int iVar3;
	_PLAYER *pPVar5;
	int local_2c;
	int pitch;

	iVar3 = 0;
	TimeSinceLastSpeech = 0;

	if (NumPlayers != 0) 
	{
		pPVar5 = player;
		do {
			bVar1 = car_data[pPVar5->playerCarId].ap.model;
			index = bVar1;

			if (bVar1 == 4)
			{
				uVar2 = ResidentModelsBodge();
			}
			else 
			{
				uVar2 = index;
				if (2 < bVar1)
				{
					uVar2 = index - 1;
				}
			}

			channel = 1;
			if (iVar3 == 0) {
				local_2c = 16383;
			}
			else {
				channel = 4;
				local_2c = 129;
			}
			Start3DSoundVolPitch(channel, 3, uVar2 * 3 + 1, car_data[0].hd.where.t[0], car_data[0].hd.where.t[1], car_data[0].hd.where.t[2], -10000, local_2c);

			if (bVar1 == 4) 
			{
				channel = ResidentModelsBodge();
				channel = channel * 3;
			}
			else 
			{
				if (bVar1 < 3)
					channel = index * 3;

				else
					channel = (index - 1) * 3;
			}

			local_2c = 0;
			if (iVar3 == 0) {
				pitch = 0x3fff;
			}
			else {
				local_2c = 3;
				pitch = 0x81;
			}
			Start3DSoundVolPitch(local_2c, 3, channel, car_data[0].hd.where.t[0], car_data[0].hd.where.t[1], car_data[0].hd.where.t[2], -10000, pitch);
			index = CarHasSiren(index);

			if (index != 0) 
			{
				channel = 2;
				if (iVar3 != 0) 
					channel = 5;

				Start3DSoundVolPitch(channel, (index & 0xff00) >> 8, index & 0xff, car_data[0].hd.where.t[0], car_data[0].hd.where.t[1], car_data[0].hd.where.t[2], -10000, 129);
			}

			if ((1 < NumPlayers) && (NoPlayerControl == 0)) 
			{
				channel = 0;
				if (iVar3 != 0) 
					channel = 3;

				playerId = iVar3;
				SetPlayerOwnsChannel(channel, playerId);
				channel = 1;
				if (iVar3 != 0)
					channel = 4;

				SetPlayerOwnsChannel(channel, playerId);
				channel = 2;
				if (iVar3 != 0)
					channel = 5;

				SetPlayerOwnsChannel(channel, playerId);
			}
			player[iVar3].crash_timer = 0;

			pPVar5->revsvol = -10000;
			pPVar5->idlevol = -8000;
			pPVar5 = pPVar5 + 1;
			iVar3 = iVar3 + 1;
		} while (iVar3 < (int)(uint)NumPlayers);
	}

	if (NumPlayers != 0) 
	{
		if (NumPlayers != 1) 
			goto LAB_0004e0dc;
		SpuSetVoiceAR(5, 0x1b);
	}

	SpuSetVoiceAR(2, 0x1b);

LAB_0004e0dc:

	if ((NumPlayers < 2) || (NoPlayerControl != 0)) 
	{
		InitEnvSnd(0x20);
		AddEnvSounds(GameLevel, gTimeOfDay);
	}

	InitDopplerSFX();
	InitSkidding();
	AddTunnels(GameLevel);
	first_offence = '\x01';
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

// [D]
ushort GetEngineRevs(_CAR_DATA *cp)
{
	bool bVar1;
	short sVar2;
	int iVar3;
	GEAR_DESC *pGVar4;
	int uVar5;
	int uVar6;
	short sVar7;
	int iVar8;
	int iVar9;
	int uVar10;

	uVar5 = cp->hd.gear;
	iVar8 = cp->hd.wheel_speed;
	sVar2 = cp->thrust;

	uVar10 = (cp->controlType == 2);

	if (iVar8 < 1) {
		iVar9 = -iVar8;

		//if (0 < iVar8) 
		//	iVar9 += 0x7ff;

		sVar7 = iVar9 / 2048;
		uVar6 = 0;
		iVar9 = uVar10 * 4;

		cp->hd.gear = 0;
	}
	else 
	{
		iVar8 = iVar8 / 2048;
		sVar7 = iVar8;

		if (false) 
			uVar5 = 0;

		if (3 < uVar5) 
			uVar5 = 3;

		iVar9 = uVar10 * 4;
		pGVar4 = &geard[uVar10][uVar5];

		do {
			if (sVar2 < 1) 
				iVar3 = pGVar4->lowidl_ws;
			else
				iVar3 = pGVar4->low_ws;

			uVar6 = uVar5;
			if (iVar8 < iVar3)
			{
				pGVar4 = pGVar4 + -1;
				uVar6 = uVar5 - 1;
			}

			if (pGVar4->hi_ws < iVar8) 
			{
				pGVar4 = pGVar4 + 1;
				uVar6 = uVar6 + 1;
			}

			bVar1 = uVar5 != uVar6;
			uVar5 = uVar6;
		} while (bVar1);

		cp->hd.gear = uVar6;
	}

	
	if (sVar2 != 0)
		return sVar7 * geard[uVar10][uVar6].ratio_ac;// [A] - indexing might be incorrect

	return sVar7 * geard[uVar10][uVar6].ratio_id;
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

int maxrevdrop = 1440;
int maxrevrise = 1600;

// [D]
void ControlCarRevs(_CAR_DATA *cp)
{
	int uVar1;
	int iVar2;
	int uVar3;
	int sVar4;
	int puVar5;
	int sVar6;
	char spin;

	sVar6 = cp->thrust;
	spin = cp->wheelspin;

	iVar2 = GetPlayerId(cp);

	uVar1 = cp->hd.revs;
	puVar5 = uVar1;
	iVar2 = iVar2;

	cp->hd.changingGear = 0;

	if ((spin == 0 && (cp->hd.wheel[1].susCompression != 0 || (cp->hd.wheel[3].susCompression != 0))) || (sVar6 == 0))
	{
		uVar1 = GetEngineRevs(cp);
		uVar3 = uVar1;
	}
	else 
	{
		uVar3 = 20160;

		if(cp->hd.wheel[1].susCompression == 0 && cp->hd.wheel[3].susCompression == 0) 
		{
			uVar3 = 30719;
			spin = 1;
		}

		if (uVar1 < 8000) 
			puVar5 = 8000;

		cp->hd.gear = 0;
	}

	if (maxrevdrop < puVar5-uVar3) 
	{
		sVar6 = 0;
		uVar3 = maxrevdrop & 0xffff;

		cp->hd.changingGear = 1;

		uVar3 = (puVar5 - uVar3) & 0xffff;
	}

	maxrevrise = uVar3;

	if (maxrevrise < uVar3 - puVar5)
		maxrevrise = puVar5 + maxrevrise;

	cp->hd.revs = maxrevrise;

	if (-1 < iVar2) 
	{
		if (sVar6 == 0 && maxrevrise < 7001)
		{
			sVar6 = player[iVar2].revsvol;
			sVar4 = player[iVar2].idlevol+200;

			player[iVar2].idlevol = sVar4;
			player[iVar2].revsvol = sVar6-200;

			if (-6000 < sVar4) 
				player[iVar2].idlevol = -6000;

			if (player[iVar2].revsvol < -10000)
				player[iVar2].revsvol = -10000;
		}
		else {
			sVar4 = -6750;
			if (sVar6 != 0) {
				sVar4 = -5500;
			}
			if (spin == 0) 
				sVar6 = -64;
			else 
				sVar6 = -256;

			player[iVar2].idlevol += sVar6;

			if (spin == 0) 
				sVar6 = 175;
			else
				sVar6 = 700;

			player[iVar2].revsvol = player[iVar2].revsvol + sVar6;

			if (player[iVar2].idlevol < -10000) 
				player[iVar2].idlevol = -10000;

			if (sVar4 < player[iVar2].revsvol) 
				player[iVar2].revsvol = sVar4;
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

// [D]
void DoSpeech(int chan, int sound)
{
	if (sound < 100)
	{
		if (sound != 0) 
		{
			StartSound(chan, 2, sound, -0x5dc, 0x1000);
		}
	}
	else
	{
		StartSound(chan, 5, sound + -100, 0, 0x1000);
	}
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

// [D]
char PlaySpeech(SPEECH_QUEUE *pSpeechQueue, int sound)
{
	int iVar1;
	int *piVar2;
	int iVar3;

	iVar1 = pSpeechQueue->count;
	if (iVar1 < 7) 
	{
		pSpeechQueue->count = iVar1 + 1;

		iVar3 = iVar1 + -1;

		if (iVar3 != -1)
		{
			piVar2 = pSpeechQueue->slot + iVar1;
			do {
				iVar3 = iVar3 + -1;
				*piVar2 = piVar2[-1];
				piVar2 = piVar2 + -1;
			} while (iVar3 != -1);
		}

		pSpeechQueue->slot[0] = sound;

		return 1;
	}
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSpeechQueue(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
 // line 587, offset 0x00052654
	/* begin block 1 */
		// Start line: 5265
	/* end block 1 */
	// End Line: 5266

// [D]
void InitSpeechQueue(SPEECH_QUEUE *pSpeechQueue)
{
	ClearMem((char *)pSpeechQueue, 0x28);

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

void ControlSpeech(SPEECH_QUEUE *pSpeechQueue)
{
	UNIMPLEMENTED();

	/*
	char cVar1;
	int iVar2;
	uint uVar3;

	if (GameType != GAME_MISSION) goto LAB_0004e5d0;
	if ((bMissionTitleFade == 0) || (pSpeechQueue->allowed = '\x01', bMissionTitleFade == 0)) {
		cVar1 = pSpeechQueue->allowed;
		if (cVar1 == '\x01') {
			pSpeechQueue->allowed = '\x02';
			goto LAB_0004e5c0;
		}
	}
	else {
	LAB_0004e5c0:
		cVar1 = pSpeechQueue->allowed;
	}
	if (cVar1 != '\x02') {
		return;
	}
LAB_0004e5d0:
	if (pSpeechQueue->count < 1) {
		TimeSinceLastSpeech = TimeSinceLastSpeech + 1;
		if ((pSpeechQueue->is_playing != '\0') &&
			(iVar2 = SpuGetKeyStatus(1 << ((uint)(byte)pSpeechQueue->chan & 0x1f)), iVar2 == 0)) {
			SetReverbChannelState((uint)(byte)pSpeechQueue->chan, (uint)(byte)pSpeechQueue->reverb);
			UnlockChannel((uint)(byte)pSpeechQueue->chan);
			pSpeechQueue->is_playing = '\0';
		}
	}
	else {
		if (pSpeechQueue->is_playing == '\0') {
			uVar3 = GetFreeChannel();
			pSpeechQueue->chan = (char)uVar3;
			LockChannel(uVar3 & 0xff);
			iVar2 = SetReverbChannelState((uint)(byte)pSpeechQueue->chan, 0);
			pSpeechQueue->reverb = (char)iVar2;
			pSpeechQueue->is_playing = '\x01';
			(&channels)[(byte)pSpeechQueue->chan].time = 0;
			iVar2 = pSpeechQueue->count + -1;
			pSpeechQueue->count = iVar2;
			DoSpeech((uint)(byte)pSpeechQueue->chan, pSpeechQueue->slot[iVar2]);
		}
		else {
			iVar2 = SpuGetKeyStatus(1 << ((uint)(byte)pSpeechQueue->chan & 0x1f));
			if (iVar2 == 0) {
				iVar2 = pSpeechQueue->count + -1;
				pSpeechQueue->count = iVar2;
				DoSpeech((uint)(byte)pSpeechQueue->chan, pSpeechQueue->slot[iVar2]);
			}
		}
		TimeSinceLastSpeech = 0;
	}
	return;
	*/
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
	if (((((gCurrentMissionNumber != 7) && (gCurrentMissionNumber != 9)) &&
		(gCurrentMissionNumber != 0xb)) &&
		((gCurrentMissionNumber != 0x14 && (gCurrentMissionNumber != 0x1a)))) &&
		((gCurrentMissionNumber != 0x1f &&
		((gCurrentMissionNumber != 0x21 && (gCurrentMissionNumber != 0x28)))))) 
	{
		PlaySpeech(&gSpeechQueue, phrase);

		if (phrase == 10)
		{
			if (cop_bank == '\x01') {
				return;
			}
			if ((cop_bank != '\x02') && (cop_bank != '\x03')) {
				return;
			}
		}
		else 
		{
			if (phrase != 0xf) 
				return;

			if (cop_bank != 1)
			{
				if (cop_bank == 2)
					return;

				if (cop_bank == 3)
					return;

				if (cop_bank != 4)
					return;
			}
		}

		PlaySpeech(&gSpeechQueue, direction + 1);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ BodSay(int phrase /*$a1*/)
 // line 677, offset 0x00052694
	/* begin block 1 */
		// Start line: 5445
	/* end block 1 */
	// End Line: 5446

// [D]
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

// [D]
void MissionSay(int phrase)
{
	char cVar1;
	cVar1 = GetMissionSound(phrase);

	if (cVar1 != -1)
		PlaySpeech(&gSpeechQueue, cVar1 + 100);
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

// [D]
long jsqrt(ulong a)
{
	int iVar1;
	uint uVar2;
	uint uVar3;

	if (a < 2)
		return a;

	uVar2 = a >> 1;

	if (a < 0x40000000) 
	{
		if (uVar2 < 0x8000) 
			goto LAB_0005277c;
	}
	else 
	{
		if (uVar2 < 0x10000)
			goto LAB_0005277c;
	}

	uVar2 = 0xffff;
	if (a < 0x40000000)
		uVar2 = 0x7fff;

LAB_0005277c:
	do {
		if (uVar2 == 0) 
			trap(7);

		uVar3 = uVar2 + a / uVar2 >> 1;
		iVar1 = uVar2 - uVar3;

		if (iVar1 < 0)
			iVar1 = uVar3 - uVar2;

		uVar2 = uVar3;
	} while (100 < iVar1);

	return uVar3;
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

void InitDopplerSFX(void)
{
	UNIMPLEMENTED();
	/*
	__othercarsound *p_Var1;
	int iVar2;

	p_Var1 = &siren_noise;
	iVar2 = 1;
	do {
		p_Var1->chan = -1;
		p_Var1->car = 0x14;
		p_Var1->in_use = '\0';
		iVar2 = iVar2 + -1;
		p_Var1 = p_Var1 + 1;
	} while (-1 < iVar2);
	p_Var1 = &car_noise;
	iVar2 = 3;
	do {
		p_Var1->chan = -1;
		p_Var1->car = 0x14;
		p_Var1->in_use = '\0';
		iVar2 = iVar2 + -1;
		p_Var1 = p_Var1 + 1;
	} while (-1 < iVar2);
	loudhail_time = 0x4b;
	if (GameType == GAME_GETAWAY) {
		loudhail_time = 0xf5;
	}
	return;*/
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

void DoDopplerSFX(void)
{
	static struct __othercarsound siren_noise[2];
	static struct __othercarsound car_noise[4];

	UNIMPLEMENTED();

	// FIXME: THIS IS FUCKING MESS
#if 0
	unsigned char bVar1;
	ushort uVar2;
	bool bVar3;
	uint *puVar4;
	char cVar5;
	int pitch;
	long lVar6;
	short *psVar7;
	char *puVar8;
	uint uVar9;
	uint uVar10;
	__othercarsound *p_Var11;
	int *piVar12;
	ushort *puVar13;
	int iVar14;
	VECTOR *position;
	ushort *puVar15;
	long *plVar16;
	CHANNEL_DATA *pCVar17;
	int car;
	int channel;
	int sample;
	uint uVar18;
	int cars;
	ulong car_dist[20];
	ushort indexlist[20];
	char sirens;
	uint local_34;
	uint local_30;

	cars = 0;
	car = 0;
	channel = 0;
	sample = 0;
	_sirens = 0;

	for(car = 0; car < 20; car++)
	{
		pitch = car_data[car].hd.where.t[0] - camera_position.vx;

		if (pitch < 0) 
			pitch = camera_position.vx - car_data[car].hd.where.t[0];

		if (pitch < 0x4000) 
		{
			pitch = car_data[car].hd.where.t[2] - camera_position.vz;

			if (pitch < 0)
				pitch = camera_position.vz - car_data[car].hd.where.t[2];

			if (pitch < 0x4000) 
			{
				bVar1 = car_data[car].controlType;

				if (bVar1 < 5)
				{
					if (2 < bVar1)
						goto LAB_0004e930;

					if (((bVar1 != 2) || (car_data[car].ai.c.ctrlState == 5)) || (car_data[car].ai.c.ctrlState == 7))
						continue;

					iVar14 = car_data[car].hd.where.t[0] - camera_position.vx;
					pitch = car_data[car].hd.where.t[2] - camera_position.vz;

					indexlist[cars] = car;

					lVar6 = jsqrt(iVar14 * iVar14 + pitch * pitch);

					pitch = lVar6 + 0x6000;
				}
				else 
				{
					if ((bVar1 != 7) || (cVar5 = SilenceThisCar(car), cVar5 != 0))
						goto LAB_0004e984;

				LAB_0004e930:

					iVar14 = car_data[car].hd.where.t[2];
					pitch = car_data[car].hd.where.t[0];

					indexlist[cars] = car;
					pitch = jsqrt((iVar14 - camera_position.vx) * (iVar14 - camera_position.vx) + (pitch - camera_position.vz) * (pitch - camera_position.vz));
				}

				cars++;
				car_dist[car] = pitch;
			}
		}
	}

	local_34 = (cars < 3);
	local_30 = (cars < 5);

	if (0 < cars)
	{
		car = 0;
		do {
			channel = car + 1;

			if (channel < cars) 
			{
				puVar15 = indexlist + car;
				puVar13 = indexlist + channel;
				car = cars - channel;
				do {
					uVar2 = *puVar15;
					if (car_dist[*puVar13] < car_dist[uVar2]) 
					{
						*puVar15 = *puVar13;
						*puVar13 = uVar2;
					}
					car = car + -1;
					puVar13 = puVar13 + 1;
				} while (car != 0);
			}

			car = channel;
		} while (channel < cars);
	}
	uVar18 = 0;
	car = 0;

	if ((0 < cars) && (_sirens < 2)) 
	{
		puVar13 = indexlist;
		channel = 0;
		do {
			uVar10 = (uint)*(ushort *)(puVar8 + 0x68);

			if ((((handlingType[car_data[uVar10].hndType].fourWheelDrive == 1) &&
				(car_data[uVar10].controlType == 3)) && (car_data[uVar10].ai.p.dying < 75)) &&
				(sample = CarHasSiren(car_data[uVar10].ap.model), sample != 0))
				goto LAB_0004eba8;

			if (gCurrentMissionNumber == 0x1a)
			{
				if ((car_data[uVar10].ap.model == 4) && (car_data[uVar10].controlType == 7))
				{
				LAB_0004eba8:
					uVar2 = *puVar13;
					goto LAB_0004ebac;
				}

			LAB_0004eb68:
				if ((gInGameCutsceneActive != 0) && ((car_data[uVar10].controlType == 7 && (force_siren[*puVar13] != 0))))
					goto LAB_0004eba8;
			}
			else {
				if (((gCurrentMissionNumber == 7) || (car_data[uVar10].controlType != 2)) || ((2 < car_data[uVar10].ap.model || (uVar2 = *puVar13, uVar2 != 1))))
					goto LAB_0004eb68;
			LAB_0004ebac:
				uVar18 = uVar18 | 1 << ((uint)uVar2 & 0x1f);
				if (gInGameCutsceneActive == 0) {
					_sirens = _sirens + 1 & 0xff;
				}
			}
			puVar13++;
			car++;
		} while ((car < cars) && (puVar8 = &stack0xffffff3a + channel, channel = channel + 2, _sirens < 2));
	}

	p_Var11 = siren_noise;
	car = 1;
	do {
		puVar4 = (uint *)&p_Var11->car;
		car = car + -1;
		bVar3 = (uVar18 & 1 << (*puVar4 & 0x1f)) != 0;
		*(bool *)&p_Var11->in_use = bVar3;
		p_Var11 = p_Var11 + 1;
		uVar18 = uVar18 & ~((uint)bVar3 << (*puVar4 & 0x1f));
	} while (-1 < car);

	p_Var11 = siren_noise;
	car = 1;

	do {
		if ((p_Var11->in_use == 0) && (p_Var11->stopped == 0)) 
		{
			StopChannel(p_Var11->chan);
			UnlockChannel(p_Var11->chan);
			p_Var11->chan = -1;
			p_Var11->car = 0x14;
			p_Var11->stopped = 1;
		}

		car = car + -1;
		p_Var11 = p_Var11 + 1;
	} while (-1 < car);

	car = 0;
	do {
		do {
			channel = cars;
			if (local_34 == 0)
				channel = 2;

			if (channel <= car) 
			{
				car = 0;
				p_Var11 = siren_noise;
				do {
					if (p_Var11->in_use != '\0')
					{
						channel = p_Var11->car;
						uVar18 = 0;

						if (car_data[channel].controlType == 3)
							uVar18 = car_data[channel].ai.p.dying;

						SetChannelPosition3(p_Var11->chan, (VECTOR *)car_data[channel].hd.where.t, car_data[channel].st.n.linearVelocity, uVar18 * -30 - 3000, car * 4 - (uVar18 * 48 - 4096), 0);
					}

					car = car + 1;
					p_Var11 = p_Var11 + 1;
				} while (car < 2);

				uVar18 = 0;
				car = 0;
				puVar13 = indexlist;
				while (true)
				{
					channel = cars;

					if ((4 - _sirens) < cars)
						channel = 4 - _sirens;

					if (channel <= car)
						break;

					uVar10 = (uint)*puVar13;

					if ((car_data[uVar10].controlType != 3) || (car_data[uVar10].ai.p.dying == 0))
						uVar18 = uVar18 | 1 << (uVar10 & 0x1f);

					puVar13 = puVar13 + 1;
					car = car + 1;
				}
				p_Var11 = car_noise;
				car = 3;

				do {
					puVar4 = (uint *)&p_Var11->car;
					car = car + -1;
					bVar3 = (uVar18 & 1 << (*puVar4 & 0x1f)) != 0;
					*(bool *)&p_Var11->in_use = bVar3;
					p_Var11 = p_Var11 + 1;
					uVar18 = uVar18 & ~((uint)bVar3 << (*puVar4 & 0x1f));
				} while (-1 < car);

				p_Var11 = car_noise;
				car = 3;

				do {
					if ((p_Var11->in_use == 0) && (p_Var11->stopped == 0)) 
					{
						StopChannel(p_Var11->chan);
						UnlockChannel(p_Var11->chan);
						p_Var11->chan = -1;
						p_Var11->car = 0x14;
						p_Var11->stopped = '\x01';
					}
					car = car + -1;
					p_Var11 = p_Var11 + 1;
				} while (-1 < car);

				car = 0;
				do {
					do {
						channel = cars;
						if (local_30 == 0) 
							channel = 4;

						if (channel <= car) 
						{
							car = 0;

							do {
								if (car_noise[car].in_use != 0)
								{
									channel = car_noise[car].car;
									cVar5 = car_noise[car].idle;
									bVar3 = gInGameCutsceneActive != 0;

									car_noise[car].idle = car_data[channel].hd.speed < 0x11;

									if ((bVar3) && (-1 < force_idle[channel])) 
										car_noise[car].idle = force_idle[channel];

									if (cVar5 != car_noise[car].idle)
									{
										StopChannel(car_noise[car].chan);
										UnlockChannel(car_noise[car].chan);
										bVar1 = car_data[channel].ap.model;
										if (bVar1 == 3) {
											bVar1 = cop_model;
										}
										uVar18 = (uint)bVar1;
										if (car_noise[car].idle == 0)
										{
											if (bVar1 == 4) 
											{
												sample = ResidentModelsBodge();
												sample = sample * 3;
											}
											else
											{
												sample = uVar18 << 1;
												if (2 < bVar1) 
												{
													uVar18 = uVar18 - 1;
													sample = uVar18 * 2;
												}
												sample = sample + uVar18;
											}
										}
										else 
										{
											if (bVar1 == 4)
											{
												sample = ResidentModelsBodge();
												sample = sample * 3 + 1;
											}
											else 
											{
												sample = uVar18 << 1;
												if (2 < bVar1)
												{
													uVar18 = uVar18 - 1;
													sample = uVar18 * 2;
												}
												sample = sample + uVar18 + 1;
											}
										}
										sample = Start3DTrackingSound(-1, 3, sample, (VECTOR *)car_data[channel].hd.where.t, car_data[channel].st.n.linearVelocity);
										car_noise[car].chan = sample;
										LockChannel(sample);
									}

									sample = -6250;

									if (car_data[channel].controlType == 2) 
										sample = -7000;

									iVar14 = (car_data[channel].hd.revs << 0x10) >> 0x12;
									pitch = iVar14 + 1500;

									if (car_noise[car].idle != 0)
										pitch = iVar14 + 0x1000;

									SetChannelPosition3(car_noise[car].chan, (VECTOR *)car_data[channel].hd.where.t, car_data[channel].st.n.linearVelocity, sample, pitch, 0);
								}
								car++;
							} while ((int)piVar12 < 0xce694);

							if (CopsCanSeePlayer != 0) 
							{
								if (player[0].playerCarId < 0) 
									psVar7 = &pedestrianFelony;
								else 
									psVar7 = &car_data[(int)player[0].playerCarId].felonyRating;

								if (0x292 < *psVar7)
									DoPoliceLoudhailer(cars, indexlist, car_dist);
							}

							car = 0;
							do {

								if ((channels[car].loop == 0 && (channels[car].time != 0)) && (position = channels[car].srcposition, position != NULL))
									SetChannelPosition3(car, position, channels[car].srcvelocity, channels[car].srcvolume, channels[car].srcpitch, 0);

								car++;
							} while (car < 16);

							return;
						}
						puVar13 = indexlist + car;
						car = car + 1;
					} while ((uVar18 & 1 << (*puVar13 & 0x1f)) == 0);

					channel = 0;
					p_Var11 = car_noise;

					do {
						if (p_Var11->in_use == '\0') 
						{
							uVar10 = (uint)*puVar13;
							p_Var11->in_use = 1;
							p_Var11->stopped = 1;
							uVar2 = *puVar13;
							p_Var11->car = (uint)uVar2;

							bVar3 = gInGameCutsceneActive != 0;

							p_Var11->idle = car_data[uVar10].hd.speed < 0x11;

							if ((bVar3) && (-1 < force_idle[uVar2])) 
								p_Var11->idle = force_idle[uVar2];

							bVar1 = car_data[uVar10].ap.model;
							if (bVar1 == 3) {
								bVar1 = cop_model;
							}
							uVar9 = (uint)bVar1;
							if (p_Var11->idle == '\0') {
								if (bVar1 == 4) {
									sample = ResidentModelsBodge();
									channel = sample << 1;
								}
								else {
									if (bVar1 < 3) {
										channel = uVar9 * 3;
										goto LAB_0004f134;
									}
									sample = uVar9 - 1;
									channel = sample * 2;
								}
								channel = channel + sample;
							}
							else {
								if (bVar1 == 4) {
									channel = ResidentModelsBodge();
									channel = channel * 3 + 1;
								}
								else {
									channel = uVar9 << 1;
									if (2 < bVar1) {
										uVar9 = uVar9 - 1;
										channel = uVar9 * 2;
									}
									channel = channel + uVar9 + 1;
								}
							}
						LAB_0004f134:
							channel = Start3DTrackingSound(-1, 3, channel, (VECTOR *)car_data[uVar10].hd.where.t, car_data[uVar10].st.n.linearVelocity);
							p_Var11->chan = channel;
							LockChannel(channel);
							break;
						}
						channel = channel + 1;
						p_Var11 = p_Var11 + 1;
					} while (channel < 4);
				} while (true);
			}
			puVar13 = indexlist + car;
			car = car + 1;
		} while ((uVar18 & 1 << ((uint)*puVar13 & 0x1f)) == 0);

		channel = 0;
		piVar12 = siren_noise.chan;
		p_Var11 = siren_noise;

		do {
			channel = channel + 1;
			if (p_Var11->in_use == '\0')
			{
				uVar10 = (uint)*puVar13;
				p_Var11->in_use = '\x01';
				p_Var11->stopped = '\0';
				bVar3 = gCurrentMissionNumber == 0x1a;
				p_Var11->car = (uint)*puVar13;

				if ((bVar3) || (car_data[uVar10].controlType != '\x02')) 
				{
					uVar9 = CarHasSiren(car_data[uVar10].ap.model);
					channel = Start3DTrackingSound(-1, (uVar9 & 0xff00) >> 8, uVar9 & 0xff, (VECTOR *)car_data[uVar10].hd.where.t, car_data[uVar10].st.n.linearVelocity);
					*piVar12 = channel;
				}
				else 
				{
					channel = Start3DTrackingSound(-1, 4, 5, (VECTOR *)car_data[uVar10].hd.where.t, car_data[uVar10].st.n.linearVelocity);
					*piVar12 = channel;
				}

				LockChannel(channel);
				break;
			}

			piVar12 = piVar12 + 3;
			p_Var11 = p_Var11 + 1;

		} while (channel < 2);
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

void DoPoliceLoudhailer(int cars, ushort *indexlist, ulong *dist)
{
	UNIMPLEMENTED();
	/*
	long lVar1;
	uint uVar2;
	uint uVar3;
	int iVar4;
	int iVar5;

	lVar1 = Random2(0x4e);
	iVar5 = 0x113;
	if (GameType == GAME_GETAWAY) {
		iVar5 = 0x1db;
	}
	if ((((gCurrentMissionNumber != 7) && (gCurrentMissionNumber != 9)) &&
		(gCurrentMissionNumber != 0xb)) &&
		(((gCurrentMissionNumber != 0x14 && (gCurrentMissionNumber != 0x1a)) &&
		((gCurrentMissionNumber != 0x1f &&
			((gCurrentMissionNumber != 0x21 && (gCurrentMissionNumber != 0x28)))))))) {
		iVar4 = 0;
		if (0 < cars) {
			do {
				uVar2 = (uint)*indexlist;
				uVar3 = dist[uVar2];
				if (0x6000 < uVar3) {
					dist[uVar2] = uVar3 - 0x6000;
				}
				if ((((car_data[uVar2].controlType == '\x03') && (car_data[uVar2].ai[0x13] == 0)) &&
					(iVar5 < loudhail_time)) && (lVar1 == (lVar1 / 0x1f) * 0x1f)) {
					Start3DTrackingSound
					(-1, 2, lVar1 % 2 + 0xd, (VECTOR *)car_data[uVar2].hd.where.t,
						(long *)(car_data[uVar2].st + 0x1c));
					loudhail_time = 0;
					break;
				}
				iVar4 = iVar4 + 1;
				indexlist = indexlist + 1;
			} while (iVar4 < cars);
		}
		if (loudhail_time <= iVar5) {
			loudhail_time = loudhail_time + 1;
		}
	}
	return;*/
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
void CollisionSound(char player_id, _CAR_DATA *cp, int impact, int car_car)
{
	int iVar1;
	uint uVar2;
	long lVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	uint phrase;
	int sample;

	uVar7 = player_id;
	sample = 8;
	phrase = 0;

	if (impact < 25)
		return;

	if ((((int)uVar7 < 0) && (uVar7 = 0, 1 < NumPlayers)) && (NoPlayerControl == 0))
	{
		iVar4 = cp->hd.where.t[0];
		iVar5 = iVar4 - player[0].pos[0];
		iVar1 = cp->hd.where.t[2];
		iVar6 = iVar1 - player[0].pos[2];
		iVar4 = iVar4 - player[1].pos[0];
		iVar1 = iVar1 - player[1].pos[2];
		uVar7 = (uint)((uint)(iVar4 * iVar4 + iVar1 * iVar1) < (uint)(iVar5 * iVar5 + iVar6 * iVar6));
	}

	if (player[uVar7].crash_timer != 0)
		return;

	if (car_car == 0)
	{
		if (0x30c < impact) goto LAB_0004f7a8;
	LAB_0004f7b4:
		if (car_car == 0)
		{
			if (0x15e < impact) goto LAB_0004f7d8;
		}
		else 
		{
			if (0x17c < impact)
			{
			LAB_0004f7d8:
				sample = 9;
				phrase = 2;
			}
		}
	}
	else 
	{
		if (impact < 0x385) goto LAB_0004f7b4;
	LAB_0004f7a8:
		sample = 10;
		phrase = 1;
	}

	uVar2 = GetFreeChannel();
	SetPlayerOwnsChannel(uVar2 & 0xff, (char)uVar7);
	iVar1 = impact;

	if (impact < 0)
		iVar1 = impact + 0x3ff;
	
	Start3DSoundVolPitch(uVar2 & 0xff, 1, sample, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2750, impact + (iVar1 >> 10) * -1024 + 3584);

	sample = GetPlayerId(cp);
	if ((sample != 0) || ((((2 < gCurrentMissionNumber - 2U && (gCurrentMissionNumber != 9)) && 
		((gCurrentMissionNumber != 10 && (gCurrentMissionNumber != 0x1b)))) || ((impact & 5U) == 0)))) 
		goto LAB_0004f930;

	lVar3 = Random2(1);

	if (lVar3 == (lVar3 / 3) * 3) 
	{
		phrase = phrase | 4;
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

			goto LAB_0004f930;
		}

		if (phrase == 0) 
			goto LAB_0004f930;

		uVar2 = Random2(1);
		phrase = 2;

		if ((uVar2 & 1) != 0) 
			phrase = 1;
	}
	BodSay(phrase);
LAB_0004f930:
	player[uVar7].crash_timer = 2;
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

void ExplosionSound(VECTOR *pos, int type)
{
	UNIMPLEMENTED();
	/*
	char id;
	long lVar1;
	undefined3 extraout_var;
	int iVar2;
	int iVar3;
	int iVar4;
	int unaff_s1;
	int unaff_s2;
	int sample;
	int iVar5;

	sample = 0xff;
	lVar1 = Random2(4);
	if (gCurrentMissionNumber == 0x17) {
	LAB_0004fa04:
		id = '\f';
	LAB_0004fa10:
		id = GetMissionSound(id);
		sample = CONCAT31(extraout_var, id);
	}
	else {
		if (gCurrentMissionNumber < 0x18) {
			if (gCurrentMissionNumber == 0xd) goto LAB_0004fa04;
		}
		else {
			if ((gCurrentMissionNumber == 0x1e) || (gCurrentMissionNumber == 0x23)) {
				id = '\x1d';
				goto LAB_0004fa10;
			}
		}
	}
	if (sample == 0xff) {
		return;
	}
	iVar3 = pos->vx;
	if (type == 1) {
		unaff_s2 = 3;
		unaff_s1 = 1;
	}
	else {
		if (type < 2) {
			iVar5 = iVar3 * unaff_s2;
			if (type != 0) goto LAB_0004fab8;
			unaff_s2 = 2;
			unaff_s1 = 2;
		}
		else {
			iVar5 = iVar3 * unaff_s2;
			if (type != 0x29a) goto LAB_0004fab8;
			unaff_s2 = 1;
			unaff_s1 = 3;
		}
	}
	iVar5 = iVar3 * unaff_s2;
LAB_0004fab8:
	iVar5 = iVar5 + player.cameraPos.vx * unaff_s1;
	if (iVar5 < 0) {
		iVar5 = iVar5 + 3;
	}
	iVar4 = pos->vy * unaff_s2 + player.cameraPos.vy * unaff_s1;
	if (iVar4 < 0) {
		iVar4 = iVar4 + 3;
	}
	iVar2 = pos->vz * unaff_s2 + player.cameraPos.vz * unaff_s1;
	if (iVar2 < 0) {
		iVar2 = iVar2 + 3;
	}
	Start3DSoundVolPitch
	(-1, 5, sample, iVar5 >> 2, iVar4 >> 2, iVar2 >> 2, 0,
		((FrameCnt * iVar3 ^ lVar1 * pos->vz) & 0x3ffU) + 0xe00);
	return;
	*/
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

void JerichoSpeak(void)
{
	UNIMPLEMENTED();

	/*
	uint uVar1;
	long lVar2;
	short *psVar3;

	lVar2 = Random2(3);
	uVar1 = j_said_78;
	if (CopsCanSeePlayer != 0) {
		if ((int)player.playerCarId < 0) {
			psVar3 = &pedestrianFelony;
		}
		else {
			psVar3 = &car_data[(int)player.playerCarId].felonyRating;
		}
		if (((0x292 < *psVar3) && (lVar2 == (lVar2 / 5) * 5)) &&
			(uVar1 = j_said_78 + 1, 0x3c < j_said_78)) {
			BodSay(lVar2 % 3);
			j_said_78 = 0;
			uVar1 = j_said_78;
		}
	}
	j_said_78 = uVar1;
	return;
	*/
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

void FunkUpDaBGMTunez(int funk)
{
	UNIMPLEMENTED();
	/*
	if (funk == 0) {
		if (copmusic != 0) {
			copmusic = 0;
			XM_SetSongPos(Song_ID, 0);
		}
	}
	else {
		if (copmusic == 0) {
			copmusic = 1;
			XM_SetSongPos(Song_ID, *(ushort *)(coptrackpos + current_music_id));
		}
	}
	return;
	*/
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

// [D]
void SoundTasks(void)
{
	static struct __envsoundtags EStags;

	int channel;
	int channel_00;
	int uVar1;
	VECTOR *position;
	long *velocity;
	int volume;
	int *piVar2;
	int iVar3;
	int iVar4;
	_PLAYER *pPVar5;

	iVar3 = 0;
	if (NumPlayers != 0)
	{
		pPVar5 = player;

		do {
			channel_00 = pPVar5->playerCarId;

			if ((pPVar5->cameraView == 2) || (pPVar5->cameraView == 0)) 
			{
				pPVar5->camera_vel[0] = car_data[channel_00].st.n.linearVelocity[0];
				pPVar5->camera_vel[1] = car_data[channel_00].st.n.linearVelocity[1];
				pPVar5->camera_vel[2] = car_data[channel_00].st.n.linearVelocity[2];
			}
			else {
				pPVar5->camera_vel[0] = 0;
				pPVar5->camera_vel[1] = 0;
				pPVar5->camera_vel[2] = 0;
			}

			piVar2 = &pPVar5->car_sound_timer;

			if (-1 < *piVar2) {
				*piVar2 = *piVar2 + -1;
			}

			if (*piVar2 == 4) 
			{
				Start3DSoundVolPitch(-1, 6, 4, car_data[channel_00].hd.where.t[0],-car_data[channel_00].hd.where.t[1], car_data[channel_00].hd.where.t[2],-2500, 3072);
			}

			if (*piVar2 == 0) 
				pPVar5->car_is_sounding = 0;

			piVar2 = &pPVar5->crash_timer;
			channel = *piVar2;

			if (0 < channel) 
				*piVar2 = channel + -1;

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

				position = (VECTOR *)car_data[channel_00].hd.where.t;
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

	if ((NumPlayers < 2) || (NoPlayerControl != 0))
	{
		UNIMPLEMENTED();
		/*
		UpdateEnvSounds[EStags.func_cnt](&envsnd, ESdata, 0);

		iVar4 = EStags.func_cnt + 1;
		iVar3 = iVar4;
		if (iVar4 < 0) {
			iVar3 = EStags.func_cnt + 4;
		}
		EStags.func_cnt = iVar4 + (iVar3 >> 2) * -4;
		DoDopplerSFX();
		Tunnels(&tunnels);
		*/
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
		LeadHorn(car_data + 1);

	if ((force_idle[8] != 0) && (((gCurrentMissionNumber - 0x14U < 2 || (gCurrentMissionNumber == 0x19)) || (gCurrentMissionNumber == 0x27)))) 
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

void InitMusic(int musicnum)
{
	UNIMPLEMENTED();

	/*
	char *addr;
	int iVar1;
	int local_20;
	int local_1c;
	int local_18;

	copmusic = 0;
	puts(s_NewLevel_in_InitMusic___00010b04);
	AllocateReverb(3, 0x4000);
	current_music_id = musicnum;
	LoadfileSeg(s_SOUND_MUSIC_BIN_00010af4, (char *)&local_20, musicnum << 3, 0xc);
	addr = mallocptr;
	if (NewLevel != 0) {
		DAT_000aa524 = (uchar *)mallocptr;
		DAT_000aa528 = mallocptr + ((local_1c - local_20) + 3U & 0xfffffffc);
		mallocptr = DAT_000aa528;
		LoadfileSeg(s_SOUND_MUSIC_BIN_00010af4, addr, local_20,
			(local_1c - local_20) + (local_18 - local_1c));
	}
	if (Song_ID == -1) {
		VABID = XM_GetFreeVAB();
		if (NewLevel != 0) {
			iVar1 = LoadSoundBank(DAT_000aa528, local_18 - local_1c, 0);
			xm_samples_90 = (byte)iVar1;
		}
		UpdateXMSamples((uint)xm_samples_90);
		XM_GetFileHeaderSize();
		XM_SetFileHeaderAddress((uchar *)header_pt);
		XM_GetSongSize();
		XM_SetSongAddress((uchar *)song_pt);
	}
	InitXMData(DAT_000aa524, 0, 0);
	Song_ID = XM_Init(VABID, 0, 0, 0x10, 1, -1, 0, 0);
	if (music_paused != 0) {
		XM_Pause(Song_ID);
	}
	return;
	*/
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

__tunnelinfo tunnels;

// [D]
void InitTunnels(char n)
{
	if (0x1D < n) 
		n = 0x1D;

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

void Tunnels(__tunnelinfo *T)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int *piVar3;
	int iVar4;
	int iVar5;
	int on;

	iVar5 = 0;
	gTunnelNum = -1;
	on = 0;
	if (T->tunnel_cnt != '\0') {
		iVar4 = 0;
		do {
			piVar3 = (int *)((int)&T->coords[0].p2.vx + iVar4);
			iVar1 = *piVar3;
			iVar2 = *(int *)((int)&T->coords[0].p1.vx + iVar4);
			if (iVar2 < iVar1) {
				iVar1 = iVar2;
			}
			if (iVar1 < camera_position.vx) {
				iVar1 = *piVar3;
				if (iVar1 < iVar2) {
					iVar1 = iVar2;
				}
				if (camera_position.vx < iVar1) {
					piVar3 = (int *)((int)&T->coords[0].p2.vy + iVar4);
					iVar1 = *piVar3;
					iVar2 = *(int *)((int)&T->coords[0].p1.vy + iVar4);
					if (iVar2 < iVar1) {
						iVar1 = iVar2;
					}
					if (iVar1 < camera_position.vy) {
						iVar1 = *piVar3;
						if (iVar1 < iVar2) {
							iVar1 = iVar2;
						}
						if (camera_position.vy < iVar1) {
							piVar3 = (int *)((int)&T->coords[0].p2.vz + iVar4);
							iVar1 = *piVar3;
							iVar4 = *(int *)((int)&T->coords[0].p1.vz + iVar4);
							if (iVar4 < iVar1) {
								iVar1 = iVar4;
							}
							if (iVar1 < camera_position.vz) {
								iVar1 = *piVar3;
								if (iVar1 < iVar4) {
									iVar1 = iVar4;
								}
								if (camera_position.vz < iVar1) {
									on = 1;
									gTunnelNum = iVar5;
									break;
								}
							}
						}
					}
				}
			}
			iVar5 = iVar5 + 1;
			iVar4 = iVar5 * 0x20;
		} while (iVar5 < (int)(uint)(byte)T->tunnel_cnt);
	}
	SetReverbInGameState(on);
	return;
	*/
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
	long z2;
	long x1;
	long z1;
	long x2;
	long local_18;

	if (level == 1) 
	{
		InitTunnels(4);
		AddTunnel(-0x6153a, 0, -0x274e8, -0x5314c, 2000, -0x19258);
		AddTunnel(0x429a0, 0, 0xa0f0, 0x3e418, 2000, 0x29298);
		AddTunnel(-0x749a0, 0, -0x1b83c, -0x60ec8, 0x1f40, -0x206c0);

		z2 = -0xae38;
		x1 = -0x2d613;
		z1 = -0xa1ea;
		x2 = -0x2bdc2;
		local_18 = -1000;
	}
	else 
	{
		if (level < 2) 
		{
			if (level != 0)
				return;

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
			z2 = -0x57702;
			x1 = -0x351f1;
			z1 = -0x55f12;
			x2 = -0x30a1d;
			local_18 = -500;
		}
		else 
		{
			if (level != 2)
			{
				if (level != 3)
					return;

				InitTunnels(5);
				AddTunnel(0x24f68, 0, -0x3d374, 0x25cb0, -400, -0x398e6);
				AddTunnel(-0x1c19c, 0, -0x2f2b0, -0x1ba94, -400, -0x20594);
				AddTunnel(-0x118dc, 0, -0x3f7a, -0x11fb2, -400, -0x6f54);
				AddTunnel(0x131dc, 0, -0x28fdc, 0x14212, -500, -0x297de);
				AddTunnel(0x2a5ee, 0, 0x3c668, 0x2b624, -500, 0x3be34);
				return;
			}
			InitTunnels(2);
			AddTunnel(0x2678a, 0, 0xb4b9a, 0x2918a, -2000, 0xb139b);
			z2 = 0xb06da;
			x1 = 0x28550;
			z1 = 0xb139b;
			x2 = 0x2918a;
			local_18 = -2000;
		}
	}

	AddTunnel(x1, 0, z1, x2, local_18, z2);
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

void InitEnvSnd(int num_envsnds)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	__envsound *p_Var2;
	uint uVar3;
	int *piVar4;
	int iVar5;
	int iVar6;
	int iVar7;

	if (0x20 < num_envsnds) {
		num_envsnds = 0x20;
	}
	if (0 < num_envsnds) {
		p_Var2 = &envsnd;
		iVar5 = num_envsnds;
		do {
			p_Var2->type = '\0';
			iVar5 = iVar5 + -1;
			p_Var2 = p_Var2 + 1;
		} while (iVar5 != 0);
	}
	uVar3 = (uint)NumPlayers;
	if (NumPlayers != 0) {
		iVar5 = 0;
		iVar7 = 1;
		do {
			iVar6 = 3;
			piVar4 = ESdata[iVar5].playing_sound + 3;
			do {
				*piVar4 = -1;
				iVar6 = iVar6 + -1;
				piVar4 = piVar4 + -1;
			} while (-1 < iVar6);
			bVar1 = iVar7 < (int)uVar3;
			iVar5 = iVar7;
			iVar7 = iVar7 + 1;
		} while (bVar1);
	}
	EStags.frame_cnt = 0;
	EStags.func_cnt = 0;
	EStags.num_envsnds = num_envsnds;
	EStags.envsnd_cnt = 0;
	return;
	*/
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

int SetEnvSndVol(int snd, int vol)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	iVar1 = (&envsnd)[snd].vol;
	(&envsnd)[snd].vol = vol;
	return iVar1;
	*/
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

void SetEnvSndPos(int snd, long px, long pz)
{
	UNIMPLEMENTED();
	/*
	if ((&envsnd)[snd].type == '\x03') {
		(&envsnd)[snd].pos2.vx = px;
		(&envsnd)[snd].pos.vx = px;
		(&envsnd)[snd].pos2.vz = pz;
		(&envsnd)[snd].pos.vz = pz;
	}
	return;
	*/
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

int AddEnvSnd(int type, char flags, int bank, int sample, int vol, long px, long pz)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int in_stack_0000001c;
	long in_stack_00000020;

	iVar1 = EStags.envsnd_cnt;
	if (EStags.num_envsnds <= EStags.envsnd_cnt) {
		return -1;
	}
	(&envsnd)[EStags.envsnd_cnt].type = (uchar)type;
	(&envsnd)[iVar1].bank = bank;
	(&envsnd)[iVar1].sample = sample;
	(&envsnd)[iVar1].flags = flags;
	(&envsnd)[iVar1].vol = vol;
	iVar1 = EStags.envsnd_cnt;
	switch (type) {
	case 1:
	case 2:
	case 4:
		(&envsnd)[EStags.envsnd_cnt].pos.vx = px;
		(&envsnd)[iVar1].pos2.vx = in_stack_0000001c;
		(&envsnd)[iVar1].pos2.vz = in_stack_00000020;
		(&envsnd)[iVar1].pos.vz = pz;
		break;
	case 3:
		(&envsnd)[EStags.envsnd_cnt].pos2.vx = px;
		(&envsnd)[iVar1].pos.vx = px;
		(&envsnd)[iVar1].pos2.vz = pz;
		(&envsnd)[iVar1].pos.vz = pz;
		break;
	case 5:
		(&envsnd)[EStags.envsnd_cnt].type = '\x01';
		(&envsnd)[iVar1].pos.vx = px - in_stack_0000001c;
		(&envsnd)[iVar1].pos.vz = pz - in_stack_0000001c;
		(&envsnd)[iVar1].pos2.vx = px + in_stack_0000001c;
		(&envsnd)[iVar1].pos2.vz = pz + in_stack_0000001c;
	}
	if ((&envsnd)[EStags.envsnd_cnt].pos.vx == (&envsnd)[EStags.envsnd_cnt].pos2.vx) {
		(&envsnd)[EStags.envsnd_cnt].flags = (&envsnd)[EStags.envsnd_cnt].flags | 1;
	}
	if ((&envsnd)[EStags.envsnd_cnt].pos.vz == (&envsnd)[EStags.envsnd_cnt].pos2.vz) {
		(&envsnd)[EStags.envsnd_cnt].flags = (&envsnd)[EStags.envsnd_cnt].flags | 2;
	}
	if (type != 3) {
		(&envsnd)[EStags.envsnd_cnt].flags = (&envsnd)[EStags.envsnd_cnt].flags | 0x20;
	}
	iVar1 = EStags.envsnd_cnt;
	EStags.envsnd_cnt = EStags.envsnd_cnt + 1;
	return iVar1;
	*/
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

void IdentifyZone(__envsound *ep, __envsoundinfo *E, int pl)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	float *pfVar2;
	undefined4 uVar3;
	undefined4 uVar4;
	float fVar5;
	undefined *puVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	long lVar10;
	uint *puVar11;
	int iVar12;
	int iVar13;
	undefined *puVar14;
	int iVar15;
	int iVar16;
	uint uVar17;
	double in_f12_13;
	undefined8 uVar18;
	undefined8 uVar19;
	uint auStack96[3];
	float local_54[5];
	uint local_40;
	uint local_3c;
	uint *local_38;
	uint *local_34;
	uint *local_30;

	iVar16 = 3;
	local_34 = auStack96;
	pfVar2 = local_54;
	local_3c = 0;
	local_40 = 0;
	do {
		*pfVar2 = -NAN;
		iVar16 = iVar16 + -1;
		pfVar2 = pfVar2 + -1;
	} while (-1 < iVar16);
	(E->cam_pos).vx = (&player)[pl].cameraPos.vx;
	(E->cam_pos).vy = (&player)[pl].cameraPos.vy;
	iVar16 = 0;
	(E->cam_pos).vz = (&player)[pl].cameraPos.vz;
	uVar17 = 0;
	local_38 = (uint *)E->this;
	if ((0 < EStags.envsnd_cnt) && ((int)local_54[0] < 0)) {
		local_30 = auStack96;
		do {
			if ((ep->type != '\0') && (-0x1d4c < ep->vol)) {
				iVar9 = (ep->pos2).vx;
				iVar12 = (ep->pos).vx;
				iVar13 = iVar9;
				if (iVar12 < iVar9) {
					iVar13 = iVar12;
				}
				puVar14 = (undefined *)((ep->vol + 0x1d4c) * 4);
				puVar6 = puVar14;
				if ((int)puVar14 < 0) {
					puVar6 = (undefined *)0x0;
				}
				if (22000 < (int)puVar6) {
					puVar6 = &DAT_000055f0;
				}
				iVar15 = (E->cam_pos).vx;
				if (iVar13 - (int)puVar6 < iVar15) {
					if (iVar9 < iVar12) {
						iVar9 = iVar12;
					}
					puVar6 = puVar14;
					if ((int)puVar14 < 0) {
						puVar6 = (undefined *)0x0;
					}
					if (22000 < (int)puVar6) {
						puVar6 = &DAT_000055f0;
					}
					if (iVar15 < (int)(puVar6 + iVar9)) {
						iVar13 = (ep->pos2).vz;
						iVar12 = (ep->pos).vz;
						iVar9 = iVar13;
						if (iVar12 < iVar13) {
							iVar9 = iVar12;
						}
						puVar6 = puVar14;
						if ((int)puVar14 < 0) {
							puVar6 = (undefined *)0x0;
						}
						if (22000 < (int)puVar14) {
							puVar6 = &DAT_000055f0;
						}
						iVar15 = (E->cam_pos).vz;
						if (iVar9 - (int)puVar6 < iVar15) {
							iVar9 = iVar13;
							if (iVar13 < iVar12) {
								iVar9 = iVar12;
							}
							iVar7 = (ep->vol + 0x1d4c) * 4;
							iVar8 = iVar7;
							if (iVar7 < 0) {
								iVar8 = 0;
							}
							puVar6 = (undefined *)(iVar9 + iVar8);
							if (22000 < iVar7) {
								puVar6 = &DAT_000055f0 + iVar9;
							}
							if (iVar15 < (int)puVar6) {
								if (((ep->type == '\x02') || (ep->type == '\x04')) && ((ep->flags & 3) == 0)) {
									pfVar2 = local_54 + iVar16 + 1;
									uVar3 = __floatsisf(iVar13 - iVar12);
									iVar9 = (ep->pos).vx;
									uVar4 = __floatsisf((ep->pos2).vx - iVar9);
									fVar5 = (float)__divsf3(uVar3, uVar4);
									lVar10 = (E->cam_pos).vx;
									*pfVar2 = fVar5;
									uVar3 = __floatsisf(lVar10);
									uVar3 = __mulsf3(fVar5, uVar3);
									uVar4 = __floatsisf(iVar9);
									uVar4 = __mulsf3(fVar5, uVar4);
									uVar3 = __subsf3(uVar3, uVar4);
									uVar4 = __floatsisf(iVar15);
									uVar3 = __subsf3(uVar3, uVar4);
									uVar4 = __floatsisf(iVar12);
									uVar3 = __addsf3(uVar3, uVar4);
									uVar18 = __extendsfdf2(uVar3);
									iVar9 = __fixunssfsi(*pfVar2);
									iVar13 = __fixunssfsi(*pfVar2);
									iVar9 = iVar9 * iVar13 + 1;
									uVar19 = __floatsidf(iVar9);
									if (iVar9 < 0) {
										uVar19 = __adddf3((int)((ulonglong)uVar19 >> 0x20), (int)uVar19, 0, 0x41f00000);
									}
									sqrt(in_f12_13);
									uVar19 = __divdf3((int)((ulonglong)uVar18 >> 0x20), (int)uVar18,
										(int)((ulonglong)uVar19 >> 0x20), (int)uVar19);
									uVar3 = __truncdfsf2((int)((ulonglong)uVar19 >> 0x20), (int)uVar19);
									if (ep->type == '\x02') {
										iVar9 = __gesf2(uVar3, 0);
										if (iVar9 < 0) {
										LAB_000511e8:
											uVar3 = __negsf2(uVar3);
										}
									}
									else {
										if ((ep->flags & 8) != 0) goto LAB_000511e8;
									}
									puVar14 = (undefined *)((ep->vol + 0x1d4c) * 4);
									puVar6 = puVar14;
									if ((int)puVar14 < 0) {
										puVar6 = (undefined *)0x0;
									}
									if (22000 < (int)puVar14) {
										puVar6 = &DAT_000055f0;
									}
									uVar4 = __floatsisf(puVar6);
									iVar9 = __ltsf2(uVar3, uVar4);
									if (iVar9 < 0) {
										iVar16 = iVar16 + 1;
										*local_30 = uVar17;
										local_30 = local_30 + 1;
									}
								}
								else {
									iVar16 = iVar16 + 1;
									*local_30 = uVar17;
									local_30 = local_30 + 1;
								}
							}
						}
					}
				}
			}
			uVar17 = uVar17 + 1;
			ep = ep + 1;
		} while (((int)uVar17 < EStags.envsnd_cnt) && ((int)local_54[0] < 0));
	}
	iVar16 = 0;
	puVar11 = local_34;
	while (true) {
		bVar1 = iVar16 < EStags.envsnd_cnt;
		if (4 < EStags.envsnd_cnt) {
			bVar1 = iVar16 < 4;
		}
		if (!bVar1) break;
		uVar17 = *puVar11;
		if (-1 < (int)uVar17) {
			if ((int)uVar17 < 0x20) {
				local_3c = local_3c | 1 << (uVar17 & 0x1f);
			}
			else {
				local_40 = local_40 | 1 << (uVar17 - 0x20 & 0x1f);
			}
		}
		puVar11 = puVar11 + 1;
		iVar16 = iVar16 + 1;
	}
	iVar16 = 3;
	puVar11 = local_38;
	do {
		uVar17 = *puVar11;
		if (-1 < (int)uVar17) {
			if ((int)uVar17 < 0x20) {
				if ((local_3c & 1 << (uVar17 & 0x1f)) != 0) goto LAB_00051370;
				*puVar11 = 0xffffffff;
			}
			else {
				if ((local_40 & 1 << (uVar17 - 0x20 & 0x1f)) == 0) {
					*puVar11 = 0xffffffff;
				}
				else {
				LAB_00051370:
					uVar17 = *puVar11;
					if ((int)uVar17 < 0x20) {
						local_3c = local_3c & ~(1 << (uVar17 & 0x1f));
					}
					else {
						local_40 = local_40 & ~(1 << (uVar17 - 0x20 & 0x1f));
					}
				}
			}
		}
		iVar16 = iVar16 + -1;
		puVar11 = puVar11 + 1;
		if (iVar16 < 0) {
			iVar9 = 1;
			iVar16 = 0;
			do {
				uVar17 = local_34[iVar16];
				iVar13 = iVar9;
				if (-1 < (int)uVar17) {
					if ((int)uVar17 < 0x20) {
						uVar17 = local_3c & 1 << (uVar17 & 0x1f);
					}
					else {
						uVar17 = local_40 & 1 << (uVar17 - 0x20 & 0x1f);
					}
					if (uVar17 != 0) {
						iVar9 = 0;
						while (iVar13 = iVar16 + 1, iVar9 < 4) {
							if ((int)local_38[iVar9] < 0) {
								local_38[iVar9] = local_34[iVar16];
								E->g[iVar9] = local_54[iVar16 + 1];
								break;
							}
							iVar9 = iVar9 + 1;
						}
					}
				}
				iVar9 = iVar13 + 1;
				iVar16 = iVar13;
				if (3 < iVar13) {
					return;
				}
			} while (true);
		}
	} while (true);
	*/
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

void CalcEffPos(__envsound *ep, __envsoundinfo *E, int pl)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	VECTOR *pVVar2;
	__envsoundinfo *p_Var3;
	int iVar4;
	__envsound *p_Var5;
	int iVar6;
	int *piVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	__envsoundinfo *p_Var11;
	int iVar12;
	uint uVar13;
	VECTOR *pVVar14;
	VECTOR *pVVar15;
	VECTOR *pVVar16;
	__envsoundinfo *p_Var17;

	uVar13 = 0;
	iVar12 = 0;
	pVVar15 = (VECTOR *)&E->eff_pos[0].vz;
	p_Var3 = E;
	p_Var11 = E;
	pVVar14 = pVVar15;
	pVVar16 = pVVar15;
	p_Var17 = E;
	do {
		E->flags = E->flags & ~(1 << (uVar13 & 0x1f));
		iVar10 = E->this[uVar13];
		if (-1 < iVar10) {
			p_Var5 = ep + iVar10;
			if (p_Var5->type == '\x01') {
				iVar4 = (p_Var5->pos2).vx;
				iVar6 = (p_Var5->pos).vx;
				iVar9 = iVar4;
				if (iVar6 < iVar4) {
					iVar9 = iVar6;
				}
				iVar8 = (E->cam_pos).vx;
				if (iVar8 < iVar9) {
					if (iVar6 < iVar4) {
						iVar4 = iVar6;
					}
					p_Var17->eff_pos[0].vx = iVar4;
				}
				else {
					iVar9 = iVar4;
					if (iVar4 < iVar6) {
						iVar9 = iVar6;
					}
					if (iVar9 < iVar8) {
						if (iVar4 < iVar6) {
							iVar4 = iVar6;
						}
						p_Var3->eff_pos[0].vx = iVar4;
					}
					else {
						p_Var11->eff_pos[0].vx = iVar8;
					}
				}
				p_Var5 = ep + iVar10;
				iVar10 = (p_Var5->pos2).vz;
				iVar4 = (p_Var5->pos).vz;
				if (iVar4 < iVar10) {
					iVar10 = iVar4;
				}
				iVar9 = (E->cam_pos).vz;
				if (iVar9 < iVar10) {
					iVar10 = (p_Var5->pos2).vz;
					if (iVar4 < iVar10) {
						iVar10 = iVar4;
					}
					pVVar14->vx = iVar10;
				}
				else {
					iVar10 = (p_Var5->pos2).vz;
					iVar6 = iVar10;
					if (iVar10 < iVar4) {
						iVar6 = iVar4;
					}
					if (iVar6 < iVar9) {
						if (iVar10 < iVar4) {
							iVar10 = iVar4;
						}
						pVVar16->vx = iVar10;
					}
					else {
						p_Var11->eff_pos[0].vz = iVar9;
					}
				}
			}
			else {
				if (p_Var5->type != '\x02') goto LAB_0005179c;
				if ((p_Var5->flags & 1) == 0) {
					if ((p_Var5->flags & 2) == 0) goto LAB_0005179c;
					p_Var11->eff_pos[0].vz = (p_Var5->pos).vz;
					iVar10 = (p_Var5->pos2).vx;
					iVar4 = (p_Var5->pos).vx;
					if (iVar4 < iVar10) {
						iVar10 = iVar4;
					}
					iVar9 = (E->cam_pos).vx;
					if (iVar10 <= iVar9) {
						iVar6 = (p_Var5->pos2).vx;
						iVar10 = iVar6;
						if (iVar6 < iVar4) {
							iVar10 = iVar4;
						}
						if (iVar9 <= iVar10) {
							pVVar2 = E->eff_pos;
							goto LAB_00051788;
						}
						pVVar2 = E->eff_pos;
						goto LAB_0005176c;
					}
					iVar6 = (p_Var5->pos2).vx;
					piVar7 = (int *)((int)&E->eff_pos[0].vx + iVar12);
					bVar1 = iVar4 < iVar6;
				}
				else {
					p_Var11->eff_pos[0].vx = (p_Var5->pos).vx;
					iVar10 = (p_Var5->pos2).vz;
					iVar4 = (p_Var5->pos).vz;
					if (iVar4 < iVar10) {
						iVar10 = iVar4;
					}
					iVar9 = (E->cam_pos).vz;
					if (iVar9 < iVar10) {
						iVar6 = (p_Var5->pos2).vz;
						piVar7 = (int *)((int)&pVVar15->vx + iVar12);
						bVar1 = iVar4 < iVar6;
					}
					else {
						iVar6 = (p_Var5->pos2).vz;
						iVar10 = iVar6;
						if (iVar6 < iVar4) {
							iVar10 = iVar4;
						}
						pVVar2 = pVVar15;
						if (iVar9 <= iVar10) {
						LAB_00051788:
							*(int *)((int)&pVVar2->vx + iVar12) = iVar9;
							goto LAB_0005178c;
						}
					LAB_0005176c:
						piVar7 = (int *)((int)&pVVar2->vx + iVar12);
						bVar1 = iVar6 < iVar4;
					}
				}
				if (bVar1) {
					iVar6 = iVar4;
				}
				*piVar7 = iVar6;
			}
		LAB_0005178c:
			E->flags = E->flags | 1 << (uVar13 & 0x1f);
		}
	LAB_0005179c:
		iVar12 = iVar12 + 0x10;
		p_Var11 = (__envsoundinfo *)(p_Var11->eff_pos + 1);
		pVVar16 = pVVar16 + 1;
		pVVar14 = pVVar14 + 1;
		p_Var3 = (__envsoundinfo *)(p_Var3->eff_pos + 1);
		uVar13 = uVar13 + 1;
		p_Var17 = (__envsoundinfo *)(p_Var17->eff_pos + 1);
		if (3 < (int)uVar13) {
			return;
		}
	} while (true);
	*/
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

void CalcEffPos2(__envsound *ep, __envsoundinfo *E, int pl)
{
	UNIMPLEMENTED();
/*
	bool bVar1;
	int iVar2;
	undefined4 uVar3;
	undefined4 uVar4;
	__envsound *p_Var5;
	int iVar6;
	int iVar7;
	long lVar8;
	uint uVar9;
	int iVar10;
	float *pfVar11;
	undefined4 *puVar12;
	undefined4 uVar13;
	long *plVar14;
	int *piVar15;
	long lVar16;
	__envsoundinfo *p_Var17;
	int iVar18;
	uint local_38;
	int local_34;
	int local_30;

	local_38 = 0;
	local_34 = 0;
	local_30 = 0;
	p_Var17 = E;
	do {
		iVar18 = *(int *)((int)E->this + local_30);
		if ((-1 < iVar18) && (uVar9 = 1 << (local_38 & 0x1f), (E->flags & uVar9) == 0)) {
			p_Var5 = ep + iVar18;
			if ((p_Var5->type == '\x02') || (p_Var5->type == '\x04')) {
				pfVar11 = E->g;
				puVar12 = (undefined4 *)((int)pfVar11 + local_30);
				iVar2 = __gesf2(*puVar12, 0);
				if (iVar2 < 0) {
					uVar3 = __negsf2(*puVar12);
					iVar2 = __ltsf2(uVar3, 0x3f800000);
					if (-1 < iVar2) goto LAB_000519c0;
				LAB_000518d8:
					uVar3 = __divsf3(0x3f800000, *(undefined4 *)((int)pfVar11 + local_30));
					uVar4 = __floatsisf((E->cam_pos).vx);
					uVar4 = __mulsf3(uVar4, uVar3);
					p_Var5 = ep + iVar18;
					uVar13 = __floatsisf((p_Var5->pos).vx);
					uVar13 = __divsf3(uVar13, uVar3);
					uVar4 = __addsf3(uVar4, uVar13);
					uVar13 = __floatsisf((E->cam_pos).vz);
					uVar4 = __addsf3(uVar4, uVar13);
					uVar13 = __floatsisf((p_Var5->pos).vz);
					uVar4 = __subsf3(uVar4, uVar13);
					uVar13 = __divsf3(0x3f800000, uVar3);
					uVar13 = __addsf3(uVar13, uVar3);
					uVar4 = __divsf3(uVar4, uVar13);
					iVar2 = __fixsfsi(uVar4);
					p_Var17->eff_pos[0].vx = iVar2;
					uVar4 = __floatsisf(iVar2 - (p_Var5->pos).vx);
					uVar3 = __divsf3(uVar4, uVar3);
				}
				else {
					iVar2 = __ltsf2(*puVar12, 0x3f800000);
					if (iVar2 < 0) goto LAB_000518d8;
				LAB_000519c0:
					uVar3 = __floatsisf((E->cam_pos).vx);
					uVar13 = *(undefined4 *)((int)pfVar11 + local_30);
					uVar3 = __divsf3(uVar3, uVar13);
					p_Var5 = ep + iVar18;
					uVar4 = __floatsisf((p_Var5->pos).vx);
					uVar4 = __mulsf3(uVar4, uVar13);
					uVar3 = __addsf3(uVar3, uVar4);
					uVar4 = __floatsisf((E->cam_pos).vz);
					uVar3 = __addsf3(uVar3, uVar4);
					uVar4 = __floatsisf((p_Var5->pos).vz);
					uVar3 = __subsf3(uVar3, uVar4);
					uVar4 = __divsf3(0x3f800000, uVar13);
					uVar4 = __addsf3(uVar13, uVar4);
					uVar3 = __divsf3(uVar3, uVar4);
					iVar2 = __fixsfsi(uVar3);
					p_Var17->eff_pos[0].vx = iVar2;
					uVar3 = __floatsisf(iVar2 - (p_Var5->pos).vx);
					uVar3 = __mulsf3(uVar3, *(undefined4 *)((int)pfVar11 + local_30));
				}
				plVar14 = &E->eff_pos[0].vz;
				uVar4 = __floatsisf(ep[iVar18].pos.vz);
				uVar3 = __addsf3(uVar3, uVar4);
				uVar3 = __fixsfsi(uVar3);
				*(undefined4 *)((int)plVar14 + local_34) = uVar3;
				p_Var5 = ep + iVar18;
				if (p_Var5->type == '\x02') {
					iVar2 = (p_Var5->pos2).vx;
					iVar7 = (p_Var5->pos).vx;
					iVar6 = iVar2;
					if (iVar2 < iVar7) {
						iVar6 = iVar7;
					}
					iVar10 = p_Var17->eff_pos[0].vx;
					if (iVar6 < iVar10) {
						if (iVar2 < iVar7) {
							iVar2 = iVar7;
						}
						p_Var17->eff_pos[0].vx = iVar2;
					}
					else {
						iVar6 = iVar2;
						if (iVar7 < iVar2) {
							iVar6 = iVar7;
						}
						if (iVar10 < iVar6) {
							if (iVar7 < iVar2) {
								iVar2 = iVar7;
							}
							p_Var17->eff_pos[0].vx = iVar2;
						}
					}
					p_Var5 = ep + iVar18;
					iVar18 = (p_Var5->pos2).vz;
					iVar2 = (p_Var5->pos).vz;
					piVar15 = (int *)((int)plVar14 + local_34);
					if (iVar18 < iVar2) {
						iVar18 = iVar2;
					}
					if (iVar18 < *piVar15) {
						iVar18 = (p_Var5->pos2).vz;
						if (iVar18 < iVar2) {
							iVar18 = iVar2;
						}
						*piVar15 = iVar18;
					}
					else {
						iVar18 = (p_Var5->pos2).vz;
						iVar6 = iVar18;
						if (iVar2 < iVar18) {
							iVar6 = iVar2;
						}
						if (*piVar15 < iVar6) {
							if (iVar2 < iVar18) {
								iVar18 = iVar2;
							}
							*piVar15 = iVar18;
						}
					}
					E->flags = E->flags | 1 << (local_38 & 0x1f);
				}
				else {
					if (p_Var5->type == '\x04') {
						if ((p_Var5->flags & 8) == 0) {
							iVar6 = (p_Var5->pos2).vz;
							iVar7 = (p_Var5->pos).vz;
							iVar2 = iVar6;
							if (iVar6 < iVar7) {
								iVar2 = iVar7;
							}
							iVar10 = (E->cam_pos).vz;
							if (iVar2 < iVar10) {
								iVar10 = iVar6;
								if (iVar6 < iVar7) {
									iVar10 = iVar7;
								}
							LAB_00051d80:
								*(int *)((int)plVar14 + local_34) = iVar10;
							}
							else {
								if (*(int *)((int)plVar14 + local_34) < iVar10) goto LAB_00051d80;
							}
							iVar2 = __ltsf2(*(undefined4 *)((int)pfVar11 + local_30), 0);
							if (-1 < iVar2) goto LAB_00051df8;
							p_Var5 = ep + iVar18;
							iVar18 = (p_Var5->pos2).vx;
							lVar8 = (p_Var5->pos).vx;
							if (iVar18 < lVar8) {
								iVar18 = lVar8;
							}
							iVar2 = (E->cam_pos).vx;
							if (iVar18 < iVar2) {
								lVar16 = (p_Var5->pos2).vx;
								bVar1 = lVar16 < lVar8;
								goto LAB_00051e40;
							}
							bVar1 = p_Var17->eff_pos[0].vx < iVar2;
						LAB_00051e60:
							if (bVar1) {
								p_Var17->eff_pos[0].vx = iVar2;
							}
						}
						else {
							iVar6 = (p_Var5->pos2).vz;
							iVar7 = (p_Var5->pos).vz;
							iVar2 = iVar6;
							if (iVar7 < iVar6) {
								iVar2 = iVar7;
							}
							iVar10 = (E->cam_pos).vz;
							if (iVar10 < iVar2) {
								iVar10 = iVar6;
								if (iVar7 < iVar6) {
									iVar10 = iVar7;
								}
							LAB_00051c98:
								*(int *)((int)plVar14 + local_34) = iVar10;
							}
							else {
								if (iVar10 < *(int *)((int)plVar14 + local_34)) goto LAB_00051c98;
							}
							iVar2 = __gtsf2(*(undefined4 *)((int)pfVar11 + local_30), 0);
							if (iVar2 < 1) {
							LAB_00051df8:
								p_Var5 = ep + iVar18;
								iVar18 = (p_Var5->pos2).vx;
								lVar8 = (p_Var5->pos).vx;
								if (lVar8 < iVar18) {
									iVar18 = lVar8;
								}
								iVar2 = (E->cam_pos).vx;
								if (iVar18 <= iVar2) {
									bVar1 = iVar2 < p_Var17->eff_pos[0].vx;
									goto LAB_00051e60;
								}
								lVar16 = (p_Var5->pos2).vx;
								bVar1 = lVar8 < lVar16;
							}
							else {
								p_Var5 = ep + iVar18;
								iVar18 = (p_Var5->pos2).vx;
								lVar8 = (p_Var5->pos).vx;
								if (iVar18 < lVar8) {
									iVar18 = lVar8;
								}
								iVar2 = (E->cam_pos).vx;
								if (iVar2 <= iVar18) {
									bVar1 = p_Var17->eff_pos[0].vx < iVar2;
									goto LAB_00051e60;
								}
								lVar16 = (p_Var5->pos2).vx;
								bVar1 = lVar16 < lVar8;
							}
						LAB_00051e40:
							if (bVar1) {
								lVar16 = lVar8;
							}
							p_Var17->eff_pos[0].vx = lVar16;
						}
					}
				}
			}
			else {
				p_Var17->eff_pos[0].vx = (p_Var5->pos).vx;
				*(long *)((int)&E->eff_pos[0].vz + local_34) = (p_Var5->pos).vz;
				E->flags = E->flags | uVar9;
			}
		}
		p_Var17 = (__envsoundinfo *)(p_Var17->eff_pos + 1);
		local_30 = local_30 + 4;
		local_38 = local_38 + 1;
		*(int *)((int)&E->eff_pos[0].vy + local_34) = -(E->cam_pos).vy;
		local_34 = local_34 + 0x10;
		if (3 < (int)local_38) {
			return;
		}
	} while (true);
	*/
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

void UpdateEnvSnd(__envsound *ep, __envsoundinfo *E, int pl)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int channel;
	long *velocity;
	int *piVar2;
	int *piVar3;
	int *piVar4;
	int iVar5;
	__envsoundinfo *p_Var6;
	__envsoundinfo *position;
	int local_30;
	int local_2c;

	piVar3 = E->this;
	iVar5 = 0;
	piVar4 = E->playing_sound;
	local_2c = 0;
	local_30 = 3;
	p_Var6 = E;
	position = E;
	do {
		channel = *piVar3;
		if (channel < 0) {
			if (-1 < *piVar4) {
				piVar2 = (int *)((int)E->chan + iVar5);
				StopChannel(*piVar2);
				UnlockChannel(*piVar2);
				*piVar4 = -1;
			}
		}
		else {
			if (*piVar4 != channel) {
				iVar1 = (int)&E->eff_pos[0].vx + local_2c;
				channel = Start3DSoundVolPitch
				(-1, ep[channel].bank, ep[channel].sample, p_Var6->eff_pos[0].vx,
					*(int *)(iVar1 + 4), *(int *)(iVar1 + 8), 0, 0x1000);
				piVar2 = (int *)((int)E->chan + iVar5);
				*piVar2 = channel;
				LockChannel(channel);
				if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
					SetPlayerOwnsChannel(*piVar2, (char)pl);
				}
				*(int *)((int)E->playing_sound + iVar5) = *piVar3;
			}
			if ((ep[*piVar3].flags & 0x10) == 0) {
				velocity = (long *)0x0;
			}
			else {
				velocity = (&player)[pl].camera_vel;
			}
			SetChannelPosition3(*(int *)((int)E->chan + iVar5), (VECTOR *)position, velocity,
				ep[*piVar3].vol + -0x9c4, 0x1000, (uint)ep[*piVar3].flags & 0x20);
		}
		piVar3 = piVar3 + 1;
		position = (__envsoundinfo *)(position->eff_pos + 1);
		piVar4 = piVar4 + 1;
		iVar5 = iVar5 + 4;
		p_Var6 = (__envsoundinfo *)(p_Var6->eff_pos + 1);
		local_2c = local_2c + 0x10;
		local_30 = local_30 + -1;
	} while (-1 < local_30);
	return;
	*/
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

void LeadHorn(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	uint uVar2;

	if (horn_time == 0) {
		rnd_139 = ((cp->hd).where.t[0] ^ (cp->hd).where.t[2]) * (FrameCnt ^ (cp->hd).where.t[1]) & 0x7f;
	}
	horn_time = horn_time + 1;
	if (horn_time == rnd_139) {
		bVar1 = (cp->ap).model;
		if (bVar1 == 4) {
			uVar2 = ResidentModelsBodge();
		}
		else {
			if (bVar1 < 3) {
				uVar2 = (uint)(byte)(cp->ap).model;
			}
			else {
				uVar2 = (uint)(byte)(cp->ap).model - 1;
			}
		}
		Start3DTrackingSound(-1, 3, uVar2 * 3 + 2, (VECTOR *)(cp->hd).where.t, (long *)(cp->st + 0x1c));
		horn_time = 0;
	}
	return;
	*/
}





