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
	6, 8, 0xFF, 9, 0xFF, 12, 13, 0xFF, 14, 0xFF, 19,
	20, 0xFF, 21, 24, 26, 0xFF, 28, 0xFF, 30,
	33, 0xFF, 37, 39, 0xFF, 41, 0xFF, 0xFF, 0xFF,
	46, 48, 49
};

__io id_map[49] =
{
	{0, 0},{0, 1},
	
	{2, 0},
	{3, 1},
	{4, 0},
	{5, 1},
	{4, 0},
	{5, 1},
	{11, 0},
	
	{12, 0},{12, 1},
	
	{11, 2},
	
	{14, 0},{14, 0},
	
	{15, 0},
	
	{16, 1},{16, 2},
	
	{18, 3},{18, 4},
	
	{11, 0},{11, 0},
	
	{20, 0},
	
	{12, 1},
	
	{13, 2},

	{21, 0},
	{31, 1},{31, 0},
	{11, 1},
	{23, 0},
	{24, 1},
	{26, 0},
	{27, 1},
	{28, 2},
	{34, 0},
	
	{29, 1}, {29, 2},
	
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
	{16, 0, 0, 1, 0},
	{25, 0, 1, 2, 0},
	{30, 0, 2, 3, 0},
	{38, 0, 3, 4, 0},
	{16, 0, 4, 9, 0},
	{130, 0, 5, 10, 0},
	{90, 0, 6, 13, 0},
	{16, 0, 7, 14, 0},
	{640, 1, 0, 18, 1},
	{16, 1, 1, 22, 0},
	{450, 1, 2, 23, 0},
	{16, 1, 3, 25, 0},
	{16, 1, 4, 26, 0},
	{20, 1, 5, 27, 0},
	{40, 1, 6, 28, 0},
	{350, 1, 7, 29, 1},
	{16, 2, 0, 29, 0},
	{16, 2, 1, 30, 0},
	{150, 2, 2, 31, 0},
	{16, 2, 3, 32, 0},
	{16, 2, 4, 34, 0},
	{25, 2, 5, 35, 0},
	{16, 2, 6, 37, 0},
	{16, 2, 7, 39, 0},
	{750, 3, 0, 33, 1},
	
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

// [D] [T]
char GetMissionSound(char id)
{
	u_char end;
	u_char rnd;
	u_char c;
	u_char start;

	start =  missionstarts[gCurrentMissionNumber];
	rnd = Random2(5);

	if (start != 0xff)
	{
		c = 1;
		do {
			end = missionstarts[gCurrentMissionNumber + c];
			c++;
		} while (end == 0xff);

		while (start < end) 
		{
			c = start + 1;
	
			if (id_map[start].in == id) 
			{
				if (c == end)
					return id_map[start].out + phrase_top;
				
				if(id_map[c].in == id)
					return id_map[start + (rnd % 2 & 0xffU)].out + phrase_top;

				return id_map[start].out + phrase_top;

			}
	
			start = c;
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

__xa_request xa;

// [D] [T]
void RequestXA(void)
{
	__xa_request* pXA;

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

// [D] [T]
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

// [D] [T]
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
				// 		CAR_DATA *you; // $s0
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

// [D] [T]
void DoCutsceneSound(void)
{
	cutscene_timer++;

	switch (gCurrentMissionNumber)
	{
		case 2:
			if (gInGameCutsceneID != 1)
				return;

			if (cutscene_timer > 74)
				force_idle[1] = -1;
			else
				force_idle[1] = 0;
			break;
		case 5:
			if (gInGameCutsceneID != 0)
				return;

			if (cutscene_timer > 150)
			{
				force_siren[2] = 1;
				force_siren[1] = 1;
			}
			else if (cutscene_timer > 140)
			{
				force_siren[1] = 1;
				force_siren[2] = 0;
			}
			else
			{
				force_siren[1] = 0;
				force_siren[2] = 0;
			}

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
		case 18:
			if (gInGameCutsceneID == 0)
			{
				if (cutscene_timer == 1)
					MissionSay(15);

				if (cutscene_timer == 206)
					Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 4, car_data[2].hd.where.t[0], -car_data[2].hd.where.t[1], car_data[2].hd.where.t[2], -2500, 3072);
			}
		
			if (gInGameCutsceneID == 1 && cutscene_timer == 6)
			{
				PrepareXA();
			}

			break;
		case 21:
			if (gInGameCutsceneID == 0)
				jericho_in_back = 1;

			break;
		case 25:
			if (gInGameCutsceneID == 1)
				jericho_in_back = gInGameCutsceneID;

			break;
		case 26:
			if (gInGameCutsceneID != 0)
				return;

			force_siren[2] = 1;
			force_siren[1] = 1;
			break;
		case 27:
			if (gInGameCutsceneID != 0)
				return;

			if (cutscene_timer == 460)
			{
				Start3DTrackingSound(-1, SOUND_BANK_MISSION, GetMissionSound(24), (VECTOR*)car_data[2].hd.where.t, NULL);
				force_siren[7] = 1;
				force_siren[6] = 1;
				force_siren[5] = 1;
				force_siren[4] = 1;
				force_siren[3] = 1;
				force_siren[2] = 1;
			}

			if (cutscene_timer == 510)
				MissionSay(23);

			if (cutscene_timer < 51)
				return;

			force_idle[1] = 0;
			break;

		case 29:
			if (gInGameCutsceneID == 1)
			{
				if (cutscene_timer == 6)
					PrepareXA();

				if (cutscene_timer == 180)
				{
					Start3DTrackingSound(-1, SOUND_BANK_MISSION,
						GetMissionSound(26), 
						(VECTOR*)car_data[2].hd.where.t,
						(LONGVECTOR3*)car_data[2].st.n.linearVelocity);
				}

				if (cutscene_timer < 641)
					force_siren[3] = 0;
				else
					force_siren[3] = 1;
			}
			break;
		case 33:
			if (gInGameCutsceneID != 1)
				return;

			if (cutscene_timer == 6)
				PrepareXA();

			if (cutscene_timer == 960)
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

// [D] [T]
void InitializeMissionSound(void)
{
	bodgevar = 0;
	holdall = -1;

	es_mobile[0] = -1;

	jericho_in_back = 0;

	if (GameLevel == 0)
	{
		es_mobile[0] = AddEnvSnd(3, 0, SOUND_BANK_ENVIRONMENT, 4, -10000, 0, 0, 0, 0);
	}
	else if (GameLevel == 1)
	{
		if (gCurrentMissionNumber - 15U < 2)
		{
			es_mobile[0] = AddEnvSnd(3, 0x20, SOUND_BANK_MISSION, GetMissionSound(14), 0, -10000, 0, 0, 0);
		}
		else if (gCurrentMissionNumber == 0x14)
		{
			jericho_in_back = 1;
		}
	}
	else if (GameLevel == 2)
	{
		if (gCurrentMissionNumber == 22)
		{
			es_mobile[0] = AddEnvSnd(3, 0, SOUND_BANK_MISSION, 0, -10000, 0, 0, 0, 0);
		}
		else if (gCurrentMissionNumber == 24)
		{
			AddEnvSnd(3, 0x20, SOUND_BANK_MISSION, GetMissionSound(31), 3000, -37000, 270500, 0, 0);
		}
	}
	else if (GameLevel == 3)
	{
		if (gCurrentMissionNumber == 32)
		{
			rio_alarm = AddEnvSnd(3, 32, SOUND_BANK_MISSION, GetMissionSound(31), -10000, -123328, -254720, 0, 0);
		}
		else if (gCurrentMissionNumber == 33)
		{
			rio_alarm = AddEnvSnd(3, 32, SOUND_BANK_MISSION, GetMissionSound(31), -10000, -203250, 339500, 0, 0);
		}
		else if (gCurrentMissionNumber == 35)
		{
			es_mobile[0] = AddEnvSnd(3, 32, SOUND_BANK_MISSION, GetMissionSound(36), -10000, 0, 0, 0, 0);
		}
		else if (gCurrentMissionNumber == 40)
		{
			holdall = Start3DSoundVolPitch(-1, SOUND_BANK_MISSION, GetMissionSound(39), 0, 0, 0, -10000, 4096);
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
		// 		VECTOR Q[3]; // stack offset -96
		// 		VECTOR P; // stack offset -48
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
		// 		VECTOR Q[3]; // stack offset -96
		// 		VECTOR P; // stack offset -48
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

// [D] [T]
void DoMissionSound(void)
{
	int chan;
	LONGVECTOR4 V;
	VECTOR* P;
	int i;
	static int channel = 0;

	switch (gCurrentMissionNumber)
	{
		case 11:
		case 13:
		case 20:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				
				Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, GetMissionSound(11), pos[0], pos[1], pos[2], -1000, 0x1000);
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

				Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, GetMissionSound(11), pos[0], pos[1], pos[2], -1000, 4096);
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
				for (i = 0; i < 16; i++)
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
				// car bomb timer
				int carId = player[0].playerCarId;

				if (carId == holdall)
				{
					if ((Mission.timer[0].count != 0) && (Mission.timer[0].count == (Mission.timer[0].count / 3000) * 3000))
					{
						chan = GetFreeChannel();

						StartSound(chan, SOUND_BANK_MISSION, GetMissionSound(20), -1500, 4096);
						SetChannelPosition3(chan, 
							(VECTOR*)car_data[carId].hd.where.t, 
							(LONGVECTOR3*)car_data[carId].st.n.linearVelocity, 
							-1500, 4096 - Mission.timer[0].count / 750, 0);
					}
				}
			}
			break;
		case 24:
			break;
		case 25:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();

				Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, GetMissionSound(11), pos[0], pos[1], pos[2], -1000, 0x1000);
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
		{
			VECTOR Q[3] = {
				{-12283,-275,841243},
				{-13482,-250,841184},
				{-14380,-276,840579},
			};

			if (bodgevar > 0 && bodgevar < 4)
			{
				P = &Q[bodgevar - 1];

				Start3DSoundVolPitch(-1, SOUND_BANK_MISSION, GetMissionSound(34), P->vx, P->vy, P->vz, -1000, 0x1000);

				bodgevar += 4;
			}
			else if (bodgevar >= 5)
			{
				// bomb ticks
				for (i = 0; i < 3; i++)
				{
					if ((bodgevar - 5) >= i)
					{
						P = &Q[i];

						if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count - (300 + 500 * i))
						{
							Start3DSoundVolPitch(-1, SOUND_BANK_MISSION, GetMissionSound(20), P->vx, P->vy, P->vz, -1500, 4096 - Mission.timer[0].count / 750);
						}
					}
				}
			}
			break;
		}
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
					Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, GetMissionSound(11), pos[0], pos[1], pos[2], -1000, 0x1000);
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
				StartSound(2, SOUND_BANK_VOICES, 0, -10000, 0x81);
				holdall = 0;
			}
			break;
		case 35:
		{
			VECTOR Q[3] = {
				{201520, -177, 385248},
				{201392, -177, 389200},
				{199376, -177, 389200}
			};

			if (bodgevar > 0 && bodgevar < 4)
			{
				// make click sound
				P = &Q[bodgevar - 1];

				Start3DSoundVolPitch(-1, SOUND_BANK_MISSION, GetMissionSound(34), P->vx, P->vy, P->vz, -1000, 4096);

				bodgevar += 4;
			}
			else if (bodgevar >= 5)
			{
				// bomb ticks
				for (i = 0; i < 3; i++)
				{
					if ((bodgevar - 5) >= i)
					{
						P = &Q[i];

						if ((Mission.timer[0].count / 3000) * 3000 == Mission.timer[0].count - (300 + 500 * i))
						{
							Start3DSoundVolPitch(-1, SOUND_BANK_MISSION, GetMissionSound(20), P->vx, P->vy, P->vz, -1500, 4096 - Mission.timer[0].count / 750);
						}
					}
				}
			}
			break;
		}
		case 39:
			if (holdall == -1)
			{
				for (i = 0; i < 16; i++)
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
				int dx, dz;
				long* C = (long*)bodgevar; // Ahhh, Reflections...

				dx = C[0] - car_data[player[0].playerCarId].hd.where.t[0];
				dz = C[2] - car_data[player[0].playerCarId].hd.where.t[2];

				if (ABS(dx) < 32768 && ABS(dz) < 32768)
				{
					V[0] = pos[0] - C[0];
					V[1] = pos[1] - C[1];
					V[2] = pos[2] - C[2];

					SetChannelPosition3(holdall, (VECTOR*)C, (LONGVECTOR3*)V, 0, 4096, 0);

					pos[0] = C[0];
					pos[1] = C[1];
					pos[2] = C[2];
				}
			}
			break;
		case 52:	// Havana sounds
		case 53:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, 0, pos[0], pos[1], pos[2], -1000, 4096);
				bodgevar = 2;
			}
			else if(bodgevar == 2)
			{
				if(channel > -1)
					SetChannelPosition3(channel, (VECTOR*)pos, NULL, -1000, 4096, 0 );
			}
			else if (bodgevar == 3)
			{
				if (channel > -1)
					StopChannel(channel);
				channel = -1;

				bodgevar = 4;
			}
			break;

		case 54:	// Vegas sounds
		case 55:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, 1, pos[0], pos[1], pos[2], -1000, 4096);
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
				Start3DSoundVolPitch(-1, SOUND_BANK_MISSION, 0, -157800, -250, 643700, -1000, 4096);
				bodgevar = 6;
			}
			// Rio sounds
		case 56:
		case 57:
			if (bodgevar == 1)
			{
				channel = GetFreeChannel();
				Start3DSoundVolPitch(channel, SOUND_BANK_MISSION, 0, pos[0], pos[1], pos[2], -1000, 4096);
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
// void /*$ra*/ SetMSoundVar(int var /*$a0*/, VECTOR *V /*$a1*/)
 // line 636, offset 0x0005f25c
	/* begin block 1 */
		// Start line: 1453
	/* end block 1 */
	// End Line: 1454

	/* begin block 2 */
		// Start line: 1909
	/* end block 2 */
	// End Line: 1910

// [D] [T]
void SetMSoundVar(int var, VECTOR* V)
{
	if (V)
	{
		pos[0] = V->vx;
		pos[1] = -V->vy;
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
	if (gInGameCutsceneActive == 0)
	{
		return car_data[car].controlType == CONTROL_TYPE_CUTSCENE && car_data[car].ai.c.ctrlState == 7;
	}

	switch (gCurrentMissionNumber)
	{
		case 1:
		case 14:
		case 17:
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

			if (cutscene_timer < 35)
				return 1;

			return 0;
		case 3:
		case 25:
			if (gInGameCutsceneID != 0)
				return 0;

			if (car == 2)
				return 1;

			return 0;
		case 6:
			if (gInGameCutsceneID == 0)
			{
				if (car - 2U < 2)
					return 1;
			}
			else
			{
				if (gInGameCutsceneID != 1)
					return 0;

				if (cutscene_timer < 253)
					return 1;
			}

			return 0;
		case 7:
		case 19:
		case 21:
		case 28:
		case 30:
		case 31:
			if (gInGameCutsceneID != 0)
				return 0;

			return 1;
		case 10:
			if (gInGameCutsceneID != 0)
				return 0;

			if (car == 3)
				return 1;

			return 0;
		case 16:
			if (gInGameCutsceneID != 0)
				return 0;

			if (car != 1)
				return 1;

			break;
		case 18:
			if (gInGameCutsceneID == 0 && car != 1)
				return 1;

			if (gInGameCutsceneID == 1 && car > 2)
				return 1;

			if (car == 1)
			{
				if (cutscene_timer >= 471)
					return 1;

				return 0;
			}

			break;
		case 23:
			if (gInGameCutsceneID != 0)
				return 0;

			if (cutscene_timer < 160)
				return 1;

			if (car != 1)
				return 0;

			if (cutscene_timer >= 416)
				return 1;

			return 0;
		case 27:
			if (gInGameCutsceneID != 0)
				return 0;

			if (car - 6U < 2)
				return 1;

			if (car - 2U > 1)
				return 0;

			if (cutscene_timer >= 681)
				return 1;

			return 0;
		case 29:
			if (gInGameCutsceneID == 0)
				return 1;

			if (gInGameCutsceneID == 1)
			{
				if (car - 4U < 2)
					return 1;

				return 0;
			}
			break;
		case 33:
			if (gInGameCutsceneID == 1 && car != 1)
				return 1;

			break;
		case 38:
			if (gInGameCutsceneID == 0)
			{
				if (car - 2U < 2)
					return 1;

				return 0;
			}

			break;
		case 39:
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
	if (gInGameCutsceneID != 0)
		return;

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





