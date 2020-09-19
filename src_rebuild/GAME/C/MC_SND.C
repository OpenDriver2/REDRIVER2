#include "DRIVER2.H"
#include "MC_SND.H"
#include "GAMESND.H"
#include "CUTSCENE.H"
#include "MISSION.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "CONVERT.H"
#include "SOUND.H"
#include "XAPLAY.H"
#include "GLAUNCH.H"

char missionstarts[42] = {
	0xFF, 0xFF, 0, 2, 4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	6, 8, 0xFF, 9, 0xFF, 0xC, 0xD, 0xFF, 0xE, 0xFF, 0x13,
	0x14, 0xFF, 0x15, 0x18, 0x1A, 0xFF, 0x1C, 0xFF, 0x1E,
	0x21, 0xFF, 0x25, 0x27, 0xFF, 0x29, 0xFF, 0xFF, 0xFF,
	0x2E, 0x30, 0x31
};

__io id_map[49] =
{
	{0, 0},
	{0, 1},
	{2, 0},
	{3, 1},
	{4, 0},
	{5, 1},
	{4, 0},
	{5, 1},
	{11, 0},
	{12, 0},
	{12, 1},
	{11, 2},
	{14, 0},
	{14, 0},
	{15, 0},
	{16, 1},
	{16, 2},
	{18, 3},
	{18, 4},
	{11, 0},
	{11, 0},
	{20, 0},
	{12, 1},
	{13, 2},
	{21, 0},
	{31, 1},
	{31, 0},
	{11, 1},
	{23, 0},
	{24, 1},
	{26, 0},
	{27, 1},
	{28, 2},
	{34, 0},
	{29, 1},
	{29, 2},
	{20, 3},
	{31, 0},
	{11, 1},
	{31, 0},
	{33, 1},
	{34, 0},
	{36, 1},
	{29, 2},
	{29, 3},
	{20, 4},
	{37, 0},
	{38, 1},
	{39, 0},
};

__xa_request xa_data[26] = {
	{0x10, 0, 0, 1, 0},
	{0x19, 0, 1, 2, 0},
	{0x1E, 0, 2, 3, 0},
	{0x26, 0, 3, 4, 0},
	{0x10, 0, 4, 9, 0},
	{0x82, 0, 5, 0xA, 0},
	{0x5A, 0, 6, 0xD, 0},
	{0x10, 0, 7, 0xE, 0},
	{0x280, 1, 0, 0x12, 1},
	{0x10, 1, 1, 0x16, 0},
	{0x1C2, 1, 2, 0x17, 0},
	{0x10, 1, 3, 0x19, 0},
	{0x10, 1, 4, 0x1A, 0},
	{0x14, 1, 5, 0x1B, 0},
	{0x28, 1, 6, 0x1C, 0},
	{0x15E, 1, 7, 0x1D, 1},
	{0x10, 2, 0, 0x1D, 0},
	{0x10, 2, 1, 0x1E, 0},
	{0x96, 2, 2, 0x1F, 0},
	{0x10, 2, 3, 0x20, 0},
	{0x10, 2, 4, 0x22, 0},
	{0x19, 2, 5, 0x23, 0},
	{0x10, 2, 6, 0x25, 0},
	{0x10, 2, 7, 0x27, 0},
	{0x2EE, 3, 0, 0x21, 1},
	{0, 0, 0, 0xFF, 0},
};

int cutscene_timer = 0;
long pos[3];
static int bodgevar = 0;

// decompiled code
// original method signature: 
// char /*$ra*/ GetMissionSound(char id /*$s1*/)
 // line 88, offset 0x0005d814
	/* begin block 1 */
		// Start line: 89
		// Start offset: 0x0005D814
		// Variables:
	// 		char c; // $s0
	// 		char start; // $s2
	// 		char end; // $a0
	// 		char rnd; // $t1
	/* end block 1 */
	// End offset: 0x0005D950
	// End Line: 106

	/* begin block 2 */
		// Start line: 176
	/* end block 2 */
	// End Line: 177

// [D]
char GetMissionSound(char id)
{
	unsigned char bVar1;
	long lVar2;
	uint uVar3;
	char *pcVar4;
	uint uVar5;

	bVar1 = missionstarts[gCurrentMissionNumber];
	uVar5 = bVar1;
	lVar2 = Random2(5);
	if (bVar1 != 0xff) 
	{
		uVar3 = 1;

		do {
			bVar1 = missionstarts[gCurrentMissionNumber + (uVar3 & 0xff)];
			uVar3 = (uVar3 & 0xff) + 1;
		} while (bVar1 == 0xff);

		while (uVar5 < (uint)bVar1) {
			uVar3 = uVar5 + 1;
			if (id_map[uVar5].in == id) {
				pcVar4 = &id_map[uVar5].out;
				if ((uVar3 != (uint)bVar1) && (pcVar4 = &id_map[uVar5].out, id_map[uVar3].in == id))
				{
					pcVar4 = &id_map[uVar5 + (lVar2 % 2 & 0xffU)].out;
				}
				return *pcVar4 + phrase_top;
			}
			uVar5 = uVar3 & 0xff;
		}
	}
	return -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ RequestXA()
 // line 145, offset 0x0005f12c
	/* begin block 1 */
		// Start line: 146
		// Start offset: 0x0005F12C
	/* end block 1 */
	// End offset: 0x0005F1B4
	// End Line: 157

	/* begin block 2 */
		// Start line: 290
	/* end block 2 */
	// End Line: 291

	/* begin block 3 */
		// Start line: 927
	/* end block 3 */
	// End Line: 928

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void RequestXA(void)
{
	__xa_request *pXA;

	xa.delay = 0xFFFF;
	xa.bank = 0;
	xa.track = 0;
	xa.mission = -1;
	xa.cutscene = 0;

	pXA = xa_data;

	while (pXA->mission > -1)
	{
		if (pXA->mission == gCurrentMissionNumber && pXA->cutscene == gInGameCutsceneID) 
		{
			xa = *pXA;
			break;
		}

		pXA++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleRequestedXA()
 // line 164, offset 0x0005f1b4
	/* begin block 1 */
		// Start line: 166
		// Start offset: 0x0005F1B4
	/* end block 1 */
	// End offset: 0x0005F224
	// End Line: 170

	/* begin block 2 */
		// Start line: 957
	/* end block 2 */
	// End Line: 958

	/* begin block 3 */
		// Start line: 965
	/* end block 3 */
	// End Line: 966

	/* begin block 4 */
		// Start line: 966
	/* end block 4 */
	// End Line: 967

/* WARNING: Unknown calling convention yet parameter storage is locked */

__xa_request xa;

// [D]
void HandleRequestedXA(void)
{
	if (xa.cutscene == 0 && xa.mission != 0) 
	{
		PrepareXA();
		xa.mission = 0;
	}

	if (xa.delay == 0) 
		PlayXA(xa.bank, xa.track);

	if (xa.delay > -1) 
		xa.delay--;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitializeCutsceneSound(int cutscene /*$a0*/)
 // line 176, offset 0x0005f224
	/* begin block 1 */
		// Start line: 177
		// Start offset: 0x0005F224
		// Variables:
	// 		int i; // $a0
	/* end block 1 */
	// End offset: 0x0005F25C
	// End Line: 181

	/* begin block 2 */
		// Start line: 982
	/* end block 2 */
	// End Line: 983

	/* begin block 3 */
		// Start line: 989
	/* end block 3 */
	// End Line: 990

	/* begin block 4 */
		// Start line: 991
	/* end block 4 */
	// End Line: 992

// [D]
void InitializeCutsceneSound(int cutscene)
{
	int i;

	cutscene_timer = 0;
	i = 0;
	while (i < 8)
	{
		force_idle[i] = -1;
		force_siren[i++] = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoCutsceneSound()
 // line 187, offset 0x0005d950
	/* begin block 1 */
		// Start line: 188
		// Start offset: 0x0005D950

		/* begin block 1.1 */
			// Start line: 191
			// Start offset: 0x0005D99C

			/* begin block 1.1.1 */
				// Start line: 224
				// Start offset: 0x0005DA88

				/* begin block 1.1.1.1 */
					// Start line: 226
					// Start offset: 0x0005DAB0
					// Variables:
				// 		long *here; // $t0
				/* end block 1.1.1.1 */
				// End offset: 0x0005DAEC
				// End Line: 228
			/* end block 1.1.1 */
			// End offset: 0x0005DAEC
			// End Line: 229

			/* begin block 1.1.2 */
				// Start line: 244
				// Start offset: 0x0005DB9C

				/* begin block 1.1.2.1 */
					// Start line: 245
					// Start offset: 0x0005DBAC
					// Variables:
				// 		struct _CAR_DATA *you; // $s0
				/* end block 1.1.2.1 */
				// End offset: 0x0005DBF0
				// End Line: 248
			/* end block 1.1.2 */
			// End offset: 0x0005DC1C
			// End Line: 250
		/* end block 1.1 */
		// End offset: 0x0005DD00
		// End Line: 269
	/* end block 1 */
	// End offset: 0x0005DD10
	// End Line: 271

	/* begin block 2 */
		// Start line: 295
	/* end block 2 */
	// End Line: 296

	/* begin block 3 */
		// Start line: 377
	/* end block 3 */
	// End Line: 378

/* WARNING: Unknown calling convention yet parameter storage is locked */

int jericho_in_back = 0;
static int rio_alarm = 0;

// [D]
void DoCutsceneSound(void)
{
	char cVar1;

	cutscene_timer++;

	switch (gCurrentMissionNumber)
	{
		case 2:
			if (gInGameCutsceneID != 1) 
				return;

			if (0x4a < cutscene_timer) 
			{
				force_idle[1] = -1;
				return;
			}

			force_idle[1] = 0;
			break;
		case 5:
			if (gInGameCutsceneID != 0)
				return;

			if (cutscene_timer < 0x97)
			{
				if (0x8c < cutscene_timer) 
				{
					force_siren[1] = 1;
					force_siren[2] = 0;
					return;
				}

				force_siren[1] = 0;
				force_siren[2] = 0;
				return;
			}

			force_siren[2] = 1;
			force_siren[1] = 1;
			break;
		case 7:
			if (gInGameCutsceneID == 0) 
			{
				if (cutscene_timer < 100)
					force_idle[1] = 0;
				else
					force_idle[1] = -1;
			}
			if (gInGameCutsceneID != 1)
				return;

			force_idle[1] = 0;
			break;
		case 0x12:
			if (gInGameCutsceneID == 0) 
			{
				if (cutscene_timer == 1)
					MissionSay(15);

				if (cutscene_timer == 0xce) 
					Start3DSoundVolPitch(-1, 6, 4, car_data[2].hd.where.t[0], -car_data[2].hd.where.t[1], car_data[2].hd.where.t[2], -0x9c4, 0xc00);

			}
			if (gInGameCutsceneID == 1 && cutscene_timer == 6)
				PrepareXA();

			break;
		case 0x15:
			if (gInGameCutsceneID == 0)
				jericho_in_back = 1;

			break;
		case 0x19:
			if (gInGameCutsceneID == 1) 
				jericho_in_back = gInGameCutsceneID;

			break;
		case 0x1a:
			if (gInGameCutsceneID != 0)
				return;

			force_siren[2] = 1;
			force_siren[1] = 1;
			break;
		case 0x1b:
			if (gInGameCutsceneID != 0)
				return;

			if (cutscene_timer == 460) 
			{
				cVar1 = GetMissionSound(24);
				Start3DTrackingSound(-1, 5, cVar1, (VECTOR *)car_data[2].hd.where.t, NULL);
				force_siren[7] = 1;
				force_siren[6] = 1;
				force_siren[5] = 1;
				force_siren[4] = 1;
				force_siren[3] = 1;
				force_siren[2] = 1;
			}

			if (cutscene_timer == 0x1fe) 
				MissionSay(23);

			if (cutscene_timer < 0x33)
				return;

			force_idle[1] = 0;
			break;

		case 0x1d:
			if (gInGameCutsceneID == 1) 
			{
				if (cutscene_timer == 6)
					PrepareXA();

				if (cutscene_timer == 0xb4) 
				{
					cVar1 = GetMissionSound(26);
					Start3DTrackingSound(-1, 5, cVar1, (VECTOR *)car_data[2].hd.where.t,car_data[2].st.n.linearVelocity);
				}

				if (cutscene_timer < 0x281)
					force_siren[3] = 0;
				else 
					force_siren[3] = 1;
			}
			break;
		case 0x21:
			if (gInGameCutsceneID != 1)
				return;

			if (cutscene_timer == 6)
				PrepareXA();

			if (cutscene_timer == 0x3c0)
				SetEnvSndVol(rio_alarm, 3000);

			force_idle[1] = 0;
			break;

	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitializeMissionSound()
 // line 279, offset 0x0005dd10
	/* begin block 1 */
		// Start line: 280
		// Start offset: 0x0005DD10
		// Variables:
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x0005E020
	// End Line: 308

	/* begin block 2 */
		// Start line: 559
	/* end block 2 */
	// End Line: 560

	/* begin block 3 */
		// Start line: 568
	/* end block 3 */
	// End Line: 569

	/* begin block 4 */
		// Start line: 573
	/* end block 4 */
	// End Line: 574

/* WARNING: Unknown calling convention yet parameter storage is locked */

char es_mobile[1];
static int holdall;

// [D]
void InitializeMissionSound(void)
{
	int iVar1;
	char cVar2;
	char* pcVar3;
	int iVar4;

	iVar4 = 0;
	bodgevar = 0;
	holdall = -1;
	//MissionStartData.PlayerPos.vx = 0xffffffff;	// [A] something isn't quite right there

	es_mobile[0] = -1;

	jericho_in_back = 0;

	if (GameLevel == 0)
	{
		es_mobile[0] = AddEnvSnd(3, 0, 4, 4, -10000, 0, 0, 0, 0);
	}
	else if (GameLevel == 1) 
	{
		if (gCurrentMissionNumber - 0xfU < 2)
		{
			cVar2 = GetMissionSound(14);
			es_mobile[0] = AddEnvSnd(3, 32, 5, cVar2, 0, -10000, 0, 0, 0);
		}
		else if (gCurrentMissionNumber == 0x14)
		{
			jericho_in_back = 1;
		}
	}
	else if (GameLevel == 2)
	{
		if (gCurrentMissionNumber == 0x16) 
		{
			es_mobile[0] = AddEnvSnd(3, 0, 5, 0, -10000, 0, 0, 0, 0);
		}
		else if (gCurrentMissionNumber == 0x18)
		{
			cVar2 = GetMissionSound(31);
			AddEnvSnd(3, ' ', 5,  cVar2, 3000, -37000, 0x420a4, 0, 0);
		}
	}
	else if (GameLevel == 3)
	{
		if (gCurrentMissionNumber == 0x20) 
		{
			cVar2 = GetMissionSound(31);
			rio_alarm = AddEnvSnd(3, 32, 5, cVar2, -10000, -0x1e1c0, -0x3e300, 0, 0);
		}
		else if (gCurrentMissionNumber == 0x21) 
		{
			cVar2 = GetMissionSound(31);
			rio_alarm = AddEnvSnd(3, 32, 5, cVar2, -10000, -0x319f2, 0x52e2c, 0, 0);
		}
		else if (gCurrentMissionNumber == 0x23) 
		{
			cVar2 = GetMissionSound(36);
			iVar4 = AddEnvSnd(3, 32, 5, cVar2, -10000, 0, 0, 0, 0);
			es_mobile[0] = (char)iVar4;
		}
		else if (gCurrentMissionNumber == 0x28) 
		{
			cVar2 = GetMissionSound(39);
			holdall = Start3DSoundVolPitch(-1, 5, cVar2, 0, 0, 0, -10000, 0x1000);
			LockChannel(holdall);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoMissionSound()
 // line 321, offset 0x0005e020
	/* begin block 1 */
		// Start line: 322
		// Start offset: 0x0005E020
		// Variables:
	// 		int i; // $a2

		/* begin block 1.1 */
			// Start line: 400
			// Start offset: 0x0005E1E4
			// Variables:
		// 		long *pos; // $s5
		// 		long *vel; // $s4

			/* begin block 1.1.1 */
				// Start line: 404
				// Start offset: 0x0005E25C
				// Variables:
			// 		int chan; // $s1
			/* end block 1.1.1 */
			// End offset: 0x0005E25C
			// End Line: 404
		/* end block 1.1 */
		// End offset: 0x0005E25C
		// End Line: 404

		/* begin block 1.2 */
			// Start line: 475
			// Start offset: 0x0005E348
			// Variables:
		// 		struct VECTOR Q[3]; // stack offset -96
		// 		struct VECTOR P; // stack offset -48
		/* end block 1.2 */
		// End offset: 0x0005E410
		// End Line: 478

		/* begin block 1.3 */
			// Start line: 480
			// Start offset: 0x0005E424
			// Variables:
		// 		int i; // $s0
		/* end block 1.3 */
		// End offset: 0x0005E5B8
		// End Line: 484

		/* begin block 1.4 */
			// Start line: 523
			// Start offset: 0x0005E6F0
			// Variables:
		// 		struct VECTOR Q[3]; // stack offset -96
		// 		struct VECTOR P; // stack offset -48
		/* end block 1.4 */
		// End offset: 0x0005E7B8
		// End Line: 526

		/* begin block 1.5 */
			// Start line: 528
			// Start offset: 0x0005E7CC
			// Variables:
		// 		int i; // $s0
		/* end block 1.5 */
		// End offset: 0x0005E968
		// End Line: 532

		/* begin block 1.6 */
			// Start line: 557
			// Start offset: 0x0005EA74
			// Variables:
		// 		long V[3]; // stack offset -96
		// 		long *C; // $a1
		/* end block 1.6 */
		// End offset: 0x0005EB98
		// End Line: 566
	/* end block 1 */
	// End offset: 0x0005EE00
	// End Line: 628

	/* begin block 2 */
		// Start line: 645
	/* end block 2 */
	// End Line: 646

	/* begin block 3 */
		// Start line: 659
	/* end block 3 */
	// End Line: 660

	/* begin block 4 */
		// Start line: 661
	/* end block 4 */
	// End Line: 662

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void DoMissionSound(void)
{
	char cVar1;
	int y;
	int z;
	_TARGET* p_Var4;
	int x;
	int y_00;
	int z_00;
	int x_00;
	long lVar6;
	long lVar7;
	VECTOR P;
	long V[3];
	static int channel;

	switch (gCurrentMissionNumber) 
	{
		case 11:
		case 13:
		case 20:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				cVar1 = GetMissionSound(11);
				Start3DSoundVolPitch(channel, 5, cVar1, pos[0], pos[1], pos[2], -1000, 0x1000);
				bodgevar = 2;
			}
			else if (bodgevar == 3)
			{
				if (channel > -1)
					StopChannel(channel);

				bodgevar = 4;
			}
			break;
		case 21:
			if (bodgevar == 1) 
			{
				channel = GetFreeChannel();
				cVar1 = GetMissionSound(11);
				Start3DSoundVolPitch(channel, 5, cVar1, pos[0], pos[1], pos[2], -1000, 0x1000);
				bodgevar = 2;
			}
			else if (bodgevar == 3)
			{
				if (channel > -1)
					StopChannel(channel);

				bodgevar = 4;
			}
			break;
		case 23:
			if (holdall == -1) 
			{
				for (int i = 0; i < 16; i++)
				{
					if (MissionTargets[i].data[0] == 2)
					{
						holdall = MissionTargets[i].data[6];
						break;
					}
				}
			}
			else
			{
				z_00 = (int)player[0].playerCarId;
				if (z_00 == holdall)
				{
					if ((Mission.timer[0].count != 0) && (Mission.timer[0].count == (Mission.timer[0].count / 3000) * 3000)) 
					{
						x = GetFreeChannel();
						cVar1 = GetMissionSound(20);
						StartSound(x, 5, cVar1, -0x5dc, 0x1000);
						SetChannelPosition3(x, (VECTOR*)car_data[z_00].hd.where.t, car_data[z_00].st.n.linearVelocity, -0x5dc, 0x1000 - Mission.timer[0].count / 0x2ee, 0);
					}
				}
			}
			break;
		case 25:
			if (bodgevar == 1) {
				channel = GetFreeChannel();
				cVar1 = GetMissionSound(11);
				Start3DSoundVolPitch(channel, 5, cVar1, pos[0], pos[1], pos[2], -1000, 0x1000);
				holdall++;
				bodgevar = 2;
			}
			else if (bodgevar == 3)
			{
				if (channel > -1)
					StopChannel(channel);

				bodgevar = 4;
			}
			break;
		case 30:
			if (bodgevar > 0 && bodgevar < 4)
			{
				VECTOR Q[3] = {
					{0xFFFFD005,0xFFFFFEED,0xCD61B},
					{0xFFFFCB56,0xFFFFFF06,0xCD5E0},
					{0xFFFFC7D4,0xFFFFFEEC,0xCD383},
				};

				VECTOR *P = &Q[bodgevar - 1];

				cVar1 = GetMissionSound(34);
				Start3DSoundVolPitch(-1, 5, cVar1, P->vx, P->vy, P->vz, -1000, 0x1000);

				bodgevar += 4;
			}
			else if (bodgevar == 5)
			{
				x = (int)(((long long)Mission.timer[0].count * 0x57619f1) >> 0x20);

				if ((Mission.timer[0].count / 3000) * 3000 != Mission.timer[0].count + 100)
					return;

				cVar1 = GetMissionSound(29);
				Start3DSoundVolPitch(-1, 5, cVar1, -0x382c, -0x114, 0xcd383, -0x5dc, 0x1000 - ((x >> 4) - (Mission.timer[0].count >> 0x1f)));
			}
			else if (bodgevar < 8) // [A] capture 6 and 7
			{
				if (bodgevar == 7)
				{
					if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count + -0x514)
					{
						cVar1 = GetMissionSound(20);
						Start3DSoundVolPitch(-1, 5, cVar1, -0x2ffb, -0x113, 0xcd61b, -0x5dc, 0x1000 - Mission.timer[0].count / 0x2ee);
					}

					// bodgevar 6 & 7 (is this a bug?)
					if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count + -800)
					{
						cVar1 = GetMissionSound(20);
						Start3DSoundVolPitch(-1, 5, cVar1, -0x34aa, -0xfa, 0xcd5e0, -0x5dc, 0x1000 - Mission.timer[0].count / 0x2ee);
					}
				}


			}
			break;
		case 32:
			if (holdall == -1)
			{
				holdall = 0;
			}
			else
			{
				if (bodgevar == 1)
				{
					channel = GetFreeChannel();
					cVar1 = GetMissionSound(11);
					Start3DSoundVolPitch(channel, 5, cVar1, pos[0], pos[1], pos[2], -1000, 0x1000);
					bodgevar = 2;
				}
				else if (bodgevar == 3)
				{
					if (channel > -1)
						StopChannel(channel);

					if (++holdall == 2)
						SetEnvSndVol(rio_alarm, 3000);

					bodgevar = 4;
				}
			}
			break;
		case 33:
			if (holdall == -1) 
			{
				StartSound(2, 2, 0, -10000, 0x81);
				holdall = 0;
			}
			break;
		case 35:
			if ((bodgevar > 0) && (bodgevar < 4))
			{
				VECTOR Q[3] = {
					{0x31330, 0xFFFFFF4F, 0x5E0E0},
					{0x312B0, 0xFFFFFF4F, 0x5F050},
					{0x30AD0, 0xFFFFFF4F, 0x5F050}
				};

				VECTOR *P = &Q[bodgevar - 1];

				cVar1 = GetMissionSound(34);
				Start3DSoundVolPitch(-1, 5, cVar1, P->vx, P->vy, P->vz, -1000, 0x1000);

				bodgevar += 4;
			}
			else if (bodgevar == 5)
			{
				x = (int)(((long long)Mission.timer[0].count * 0x57619f1) >> 0x20);

				if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count + -300) {
					cVar1 = GetMissionSound(20);
					Start3DSoundVolPitch(-1, 5, cVar1, 0x31330, -0xb1, 0x5e0e0, -0x5dc, 0x1000 - ((x >> 4) - (Mission.timer[0].count >> 0x1f)));
				}
			}
			else if (bodgevar < 8) // [A] capture 6 and 7
			{
				if (bodgevar == 7)
				{
					if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count + -0x514)
					{
						cVar1 = GetMissionSound(20);
						Start3DSoundVolPitch(-1, 5, cVar1, 0x30ad0, -0xb1, 0x5f050, -0x5dc, 0x1000 - Mission.timer[0].count / 0x2ee);
					}
				}

				// bodgevar 6 & 7 (is this a bug?)
				if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count + -800)
				{
					cVar1 = GetMissionSound(20);
					Start3DSoundVolPitch(-1, 5, cVar1, 0x312b0, -0xb1, 0x5f050, -0x5dc, 0x1000 - Mission.timer[0].count / 0x2ee);
				}
			}
			break;
		case 39:
			if (holdall == -1) 
			{
				for (int i = 0; i < 16; i++)
				{
					if (MissionTargets[i].data[0] == 2)
					{
						if (holdall == -1)
						{
							holdall = 20;
						}
						else if (holdall == 20)
						{
							holdall = MissionTargets[i].data[6];
						}
					}
				}
			}
			else if (player[0].playerCarId == holdall)
			{
				jericho_in_back = 1;
			}
			break;
		case 40:
			if (bodgevar == 0)
			{
				if (holdall != -1) 
				{
					StopChannel(holdall);
					UnlockChannel(holdall);
					holdall = -1;
				}
			}
			else 
			{
				long V[4];
				long* C = (long*)bodgevar; // Ahhh, Reflections...

				x = car_data[player[0].playerCarId].hd.where.t[0];

				y_00 = C[0] - x;
				x = x - C[0];

				if (-1 < y_00)
					x = y_00;

				if (x < 0x8000)
				{
					x = car_data[player[0].playerCarId].hd.where.t[2];

					y_00 = C[2] - x;
					x = x - C[2];

					if (-1 < y_00)
						x = y_00;

					if (x < 0x8000)
					{
						V[0] = pos[0] - C[0];
						V[1] = pos[1] - C[1];
						V[2] = pos[2] - C[2];

						SetChannelPosition3(holdall, (VECTOR*)C, (long*)V, 0, 0x1000, 0);

						pos[0] = C[0];
						pos[1] = C[1];
						pos[2] = C[2];
						return;
					}
				}
			}
			break;
		// Havana sounds
		case 52:
		case 53:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				Start3DSoundVolPitch(channel, 5, 0, pos[0], pos[1], pos[2], -1000, 0x1000);
				bodgevar = 2;
			}
			else if (bodgevar == 3)
			{
				if (-1 < channel)
					StopChannel(channel);

				bodgevar = 4;
			}
			break;
		// Vegas sounds
		case 54:
		case 55:
			if (bodgevar == 1) 
			{
				channel = GetFreeChannel();
				Start3DSoundVolPitch(channel, 5, 1, pos[0], pos[1], pos[2], -1000, 0x1000);
				bodgevar = 2;
			}
			else if (bodgevar == 3)
			{
				if (channel > -1)
					StopChannel(channel);

				bodgevar = 4;
			}
			else if (bodgevar == 5)
			{
				// Vegas special garage door
				Start3DSoundVolPitch(-1, 5, 0, -0x26868, -0xfa, 0x9d274, -1000, 0x1000);
				bodgevar = 6;
			}
		// Rio sounds
		case 56:
		case 57:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				Start3DSoundVolPitch(channel, 5, 0, pos[0], pos[1], pos[2], -1000, 0x1000);
				bodgevar = 2;
			}
			else if (bodgevar == 3)
			{
				if (channel > -1)
					StopChannel(channel);

				bodgevar = 4;
			}
			break;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMSoundVar(int var /*$a0*/, struct VECTOR *V /*$a1*/)
 // line 636, offset 0x0005f25c
	/* begin block 1 */
		// Start line: 1453
	/* end block 1 */
	// End Line: 1454

	/* begin block 2 */
		// Start line: 1909
	/* end block 2 */
	// End Line: 1910

// [D]
void SetMSoundVar(int var, VECTOR *V)
{
	if (V)
	{
		pos[0] = V->vx;
		pos[1] = V->vy;
		pos[2] = V->vz;
	}

	bodgevar = var;
}



// decompiled code
// original method signature: 
// char /*$ra*/ SilenceThisCar(int car /*$a1*/)
 // line 652, offset 0x0005ee00
	/* begin block 1 */
		// Start line: 1316
	/* end block 1 */
	// End Line: 1317

	/* begin block 2 */
		// Start line: 1341
	/* end block 2 */
	// End Line: 1342

/* WARNING: Type propagation algorithm not settling */

// [D]
char SilenceThisCar(int car)
{
	int iVar1;
	bool bVar2;

	if (gInGameCutsceneActive == 0)
	{
		bVar2 = false;

		if (car_data[car].controlType == 7) 
		{
			bVar2 = car_data[car].ai.c.ctrlState == 7;
		}

		return (char)bVar2;
	}

	switch (gCurrentMissionNumber) 
	{
	case 1:
	case 0xe:
	case 0x11:
		if (gInGameCutsceneID != 0)
			return 0;

		if (car == 1)
			return 1;

		break;
	case 2:
		if (gInGameCutsceneID != 1)
			return 0;
	
		if (car == 2 && cutscene_timer < 200)
			return 1;

		if (car != 1)
			return 0;
	
		bVar2 = cutscene_timer < 0x23;
		goto LAB_0005ef14;
	case 3:
	case 0x19:
		if (gInGameCutsceneID != 0)
			return 0;

		iVar1 = 2;
		goto LAB_0005ef3c;
	case 6:
		if (gInGameCutsceneID == 0) 
		{
			bVar2 = car - 2U < 2;
		}
		else 
		{
			if (gInGameCutsceneID != 1)
				return 0;
		
			bVar2 = cutscene_timer < 0xfd;
		}
	LAB_0005ef14:
		if (bVar2)
			return 1;

		return 0;
	case 7:
	case 0x13:
	case 0x15:
	case 0x1c:
	case 0x1e:
	case 0x1f:
		if (gInGameCutsceneID != 0) {
			return 0;
		}
		return 1;
	case 10:
		if (gInGameCutsceneID != 0) {
			return 0;
		}
		iVar1 = 3;
	LAB_0005ef3c:
		if (car == iVar1) {
			return 1;
		}
		return 0;
	case 0x10:
		if (gInGameCutsceneID != 0)
			return 0;

		if (car != 1)
			return 1;

		break;
	case 0x12:
		if (gInGameCutsceneID == 0 && car != 1)
			return 1;

		if (gInGameCutsceneID == 1 && car > 2)
			return 1;

		if (car == 1)
		{
			bVar2 = cutscene_timer < 471;
			goto LAB_0005f098;
		}

		break;
	case 0x17:
		if (gInGameCutsceneID != 0) 
			return 0;

		if (cutscene_timer < 160)
			return 1;

		if (car != 1)
			return 0;

		bVar2 = cutscene_timer < 416;
		goto LAB_0005f098;
	case 0x1b:
		if (gInGameCutsceneID != 0)
			return 0;

		if (car - 6U < 2) {
			return 1;
		}
		if (1 < car - 2U) {
			return 0;
		}
		bVar2 = cutscene_timer < 681;
	LAB_0005f098:
		if (!bVar2)
			return 1;
	
		return 0;
	case 0x1d:
		if (gInGameCutsceneID == 0)
			return 1;

		if (gInGameCutsceneID == 1) 
		{
			bVar2 = car - 4U < 2;
			goto LAB_0005ef14;
		}
		break;
	case 0x21:
		if (gInGameCutsceneID == 1 && car != 1)
			return 1;

		break;
	case 0x26:
		if (gInGameCutsceneID == 0) 
		{
			bVar2 = car - 2U < 2;
			goto LAB_0005ef14;
		}

		break;
	case 0x27:
		if (gInGameCutsceneID == 0)
			return 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AdjustPlayerCarVolume()
 // line 749, offset 0x0005f294
	/* begin block 1 */
		// Start line: 2136
	/* end block 1 */
	// End Line: 2137

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void AdjustPlayerCarVolume(void)
{
	if (gInGameCutsceneID == 0) 
	{
		if (gCurrentMissionNumber == 3 || gCurrentMissionNumber == 5 || gCurrentMissionNumber == 27)
		{
			player[0].revsvol = -6750;
			player[0].idlevol = -10000;
		}
		else 
		{
			player[0].revsvol = -10000;
			player[0].idlevol = -8000;
		}
	}
}





