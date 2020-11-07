#include "DRIVER2.H"
#include "MDRAW.H"
#include "PRES.H"
#include "MISSION.H"
#include "OVERMAP.H"
#include "PRES.H"
#include "CUTSCENE.H"
#include "GLAUNCH.H"
#include "MDRAW.H"
#include "OVERLAY.H"
#include "REPLAYS.H"
#include "PAUSE.H"
#include "PLAYERS.H"
#include "MAIN.H"
#include "SPOOL.H"
#include "DR2ROADS.H"
#include "CARS.H"
#include "TARGETS.H"

// decompiled code
// original method signature: 
// void /*$ra*/ DrawMission()
 // line 58, offset 0x0005f2fc
	/* begin block 1 */
		// Start line: 60
		// Start offset: 0x0005F2FC

		/* begin block 1.1 */
			// Start line: 68
			// Start offset: 0x0005F390
			// Variables:
		// 		char *string; // $s1
		/* end block 1.1 */
		// End offset: 0x0005F418
		// End Line: 85
	/* end block 1 */
	// End offset: 0x0005F554
	// End Line: 124

	/* begin block 2 */
		// Start line: 116
	/* end block 2 */
	// End Line: 117

	/* begin block 3 */
		// Start line: 117
	/* end block 3 */
	// End Line: 118

/* WARNING: Unknown calling convention yet parameter storage is locked */

int gDisplayPosition = 0;

// [D] [T]
void DrawMission(void)
{
	char *string;

	if (gShowMap || NoPlayerControl || gInGameCutsceneActive || bMissionTitleFade)
		return;

	if (gDisplayPosition)
		DisplayPlayerPosition();

	if ((MissionHeader->type & 4) == 0)
	{
		if (!pauseflag)
		{
			if (Mission.message_timer[0] != 0) 
			{
				if (NumPlayers == 1) 
					DrawMessage(96, Mission.message_string[0]);
				else 
					DrawMessage(64, Mission.message_string[0]);
			}

			if (Mission.message_timer[1] != 0)
				DrawMessage(192, Mission.message_string[1]);
		}
	}
	else 
	{
		SetTextColour(128, 128, 64);

		if (g321GoDelay < 32)
			string = "3";
		else if(g321GoDelay < 64)
			string = "2";
		else
			string = "1";

		if (NumPlayers == 1) 
		{
			PrintScaledString(96, string, 32 - (g321GoDelay & 0x1f));
		}
		else 
		{
			PrintScaledString(64, string, 32 - (g321GoDelay & 0x1f));
			PrintScaledString(192, string, 32 - (g321GoDelay & 0x1f));
		}
	}

	if (Mission.active && NoPlayerControl == 0)
	{
		DrawWorldTargets();
		DrawTimer(Mission.timer);
		DrawTimer(Mission.timer + 1);

		DrawProximityBar(&ProxyBar);

		if (gOutOfTape)
		{
			SetTextColour(128, 128, 64);
			PrintString("Out of tape", 20, 236);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTimer(MR_TIMER *timer /*$s1*/)
 // line 126, offset 0x0005fa88
	/* begin block 1 */
		// Start line: 127
		// Start offset: 0x0005FA88
		// Variables:
	// 		char string[16]; // stack offset -32
	/* end block 1 */
	// End offset: 0x0005FB68
	// End Line: 153

	/* begin block 2 */
		// Start line: 252
	/* end block 2 */
	// End Line: 253

// [D] [T]
void DrawTimer(MR_TIMER *timer)
{
	short digit_pos;
	char string[16];

	if ((timer->flags & 1) && (timer->flags & 0x20) == 0) 
	{
		if (NumPlayers == 1)
		{
			SetTextColour(128, 128, 128);
		}
		else
		{
			if (timer == Mission.timer) 
				SetTextColour(128, 32, 32);
			else 
				SetTextColour(32, 128, 32);
		}

		sprintf(string, "%02d:%02d", (uint)timer->min, (uint)timer->sec);
		digit_pos = PrintDigit((int)timer->x, (int)timer->y, string);

		sprintf(string, ".%02d", (uint)timer->frac);
		PrintString(string, digit_pos, (int)timer->y + 0xd);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayPlayerPosition()
 // line 155, offset 0x0005fb7c
	/* begin block 1 */
		// Start line: 157
		// Start offset: 0x0005FB7C
		// Variables:
	// 		char string[32]; // stack offset -40
	/* end block 1 */
	// End offset: 0x0005FBC4
	// End Line: 161

	/* begin block 2 */
		// Start line: 735
	/* end block 2 */
	// End Line: 736

	/* begin block 3 */
		// Start line: 736
	/* end block 3 */
	// End Line: 737

	/* begin block 4 */
		// Start line: 738
	/* end block 4 */
	// End Line: 739

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DisplayPlayerPosition(void)
{
	char string[40];

	sprintf(string, "X: %d, Y: %d, Z: %d", player[0].pos[0], player[0].pos[1], player[0].pos[2]);
	PrintString(string, 20, 210);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMessage(int y /*$s1*/, char *string /*$s0*/)
 // line 163, offset 0x0005fbc4
	/* begin block 1 */
		// Start line: 164
		// Start offset: 0x0005FBC4

		/* begin block 1.1 */
			// Start line: 167
			// Start offset: 0x0005FBE0
		/* end block 1.1 */
		// End offset: 0x0005FC28
		// End Line: 176
	/* end block 1 */
	// End offset: 0x0005FC3C
	// End Line: 177

	/* begin block 2 */
		// Start line: 748
	/* end block 2 */
	// End Line: 749

	/* begin block 3 */
		// Start line: 751
	/* end block 3 */
	// End Line: 752

// [D] [T]
void DrawMessage(int y, char *string)
{
	if (!string )
		return;

	SetTextColour(128, 128, 64);

	if (StringWidth(string) < 273) 
		PrintStringCentred(string, y - 10);
	else
		PrintStringBoxed(string, 24, y - 10);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawWorldTargets()
 // line 179, offset 0x0005fc3c
	/* begin block 1 */
		// Start line: 181
		// Start offset: 0x0005FC3C
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x0005FC7C
	// End Line: 188

	/* begin block 2 */
		// Start line: 780
	/* end block 2 */
	// End Line: 781

	/* begin block 3 */
		// Start line: 783
	/* end block 3 */
	// End Line: 784

	/* begin block 4 */
		// Start line: 784
	/* end block 4 */
	// End Line: 785

	/* begin block 5 */
		// Start line: 786
	/* end block 5 */
	// End Line: 787

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawWorldTargets(void)
{
	int i;

	if (Mission.active == 0)
		return;

	for(i = 0; i < 16; i++)
		DrawWorldTarget(&MissionTargets[i]);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawOverheadTargets()
 // line 190, offset 0x0005fc8c
	/* begin block 1 */
		// Start line: 192
		// Start offset: 0x0005FC8C
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x0005FCCC
	// End Line: 199

	/* begin block 2 */
		// Start line: 807
	/* end block 2 */
	// End Line: 808

	/* begin block 3 */
		// Start line: 808
	/* end block 3 */
	// End Line: 809

	/* begin block 4 */
		// Start line: 810
	/* end block 4 */
	// End Line: 811

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawOverheadTargets(void)
{
	int i;

	if (Mission.active == 0)
		return;

	i = 0;

	do {
			
		DrawOverheadTarget(MissionTargets + i);
		i++;
	} while (i < 16);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFullscreenTargets()
 // line 201, offset 0x0005fcdc
	/* begin block 1 */
		// Start line: 203
		// Start offset: 0x0005FCDC
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x0005FD1C
	// End Line: 210

	/* begin block 2 */
		// Start line: 831
	/* end block 2 */
	// End Line: 832

	/* begin block 3 */
		// Start line: 832
	/* end block 3 */
	// End Line: 833

	/* begin block 4 */
		// Start line: 834
	/* end block 4 */
	// End Line: 835

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawFullscreenTargets(void)
{
	int i;

	if (Mission.active == 0) 
		return;

	i = 0;

	do {
		DrawFullscreenTarget(&MissionTargets[i++]);
	} while (i < 16);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMultiplayerTargets()
 // line 212, offset 0x0005fd2c
	/* begin block 1 */
		// Start line: 214
		// Start offset: 0x0005FD2C
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x0005FD6C
	// End Line: 221

	/* begin block 2 */
		// Start line: 855
	/* end block 2 */
	// End Line: 856

	/* begin block 3 */
		// Start line: 856
	/* end block 3 */
	// End Line: 857

	/* begin block 4 */
		// Start line: 858
	/* end block 4 */
	// End Line: 859

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawMultiplayerTargets(void)
{
	int i;

	if (Mission.active == 0)
		return;

	i = 0;
	do {
		DrawMultiplayerTarget(&MissionTargets[i++]);
	} while (i < 16);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawOverheadTarget(MS_TARGET *target /*$s0*/)
 // line 230, offset 0x0005fd7c
	/* begin block 1 */
		// Start line: 231
		// Start offset: 0x0005FD7C
		// Variables:
	// 		VECTOR tv; // stack offset -24
	/* end block 1 */
	// End offset: 0x0005FE84
	// End Line: 269

	/* begin block 2 */
		// Start line: 893
	/* end block 2 */
	// End Line: 894


// [D] [T]
void DrawOverheadTarget(MS_TARGET *target)
{
	VECTOR tv;

	if (TargetComplete(target, -1))
		return;

	if ((target->data[1] & 0x600) == 0)  // invisible flag
		return;

	switch(target->data[0])
	{
		case 1:	// point or car target
		case 2:
		{
			tv.vx = target->data[3];
			tv.vz = target->data[4];
			tv.vy = 0;
			break;
		}
		case 3:	// event target
			tv = *(VECTOR*)target->data[4];
			break;
		default:
			return;
	}

	if (target->data[2] & 0x10)
		DrawTargetBlip(&tv, 64, 64, 64, 0x11);

	if (target->data[2] & 0x40)
		DrawTargetArrow(&tv, 1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFullscreenTarget(MS_TARGET *target /*$s0*/)
 // line 271, offset 0x0005fe94
	/* begin block 1 */
		// Start line: 272
		// Start offset: 0x0005FE94
		// Variables:
	// 		VECTOR tv; // stack offset -24
	/* end block 1 */
	// End offset: 0x0005FF9C
	// End Line: 310

	/* begin block 2 */
		// Start line: 977
	/* end block 2 */
	// End Line: 978

// [D] [T]
void DrawFullscreenTarget(MS_TARGET *target)
{
	VECTOR tv;

	if (TargetComplete(target, -1))
		return;

	if ((target->data[1] & 0x600) == 0)
		return;

	switch(target->data[0])
	{
		case 1:	// point or car target
		case 2:
		{
			tv.vx = target->data[3];
			tv.vz = target->data[4];
			tv.vy = 0;
			break;
		}
		case 3:	// event target
			tv = *(VECTOR*)target->data[4];
			break;
		default:
			return;
	}

	if (target->data[2] & 0x10)
		DrawTargetBlip(&tv, 64, 64, 64, 0x14);

	if (target->data[2] & 0x40)
		DrawTargetArrow(&tv, 4);
}

// decompiled code
// original method signature: 
// void /*$ra*/ DrawWorldTarget(MS_TARGET *target /*$s0*/)
 // line 312, offset 0x0005f56c
	/* begin block 1 */
		// Start line: 313
		// Start offset: 0x0005F56C
		// Variables:
	// 		VECTOR tv; // stack offset -32
	// 		int slot; // $v1
	// 		int flags; // $s1
	/* end block 1 */
	// End offset: 0x0005F850
	// End Line: 417

	/* begin block 2 */
		// Start line: 628
	/* end block 2 */
	// End Line: 629

	/* begin block 3 */
		// Start line: 633
	/* end block 3 */
	// End Line: 634

// [D]
void DrawWorldTarget(MS_TARGET *target)
{
	uint flags;
	VECTOR tv;

	if (TargetComplete(target, CurrentPlayerView))
		return;

	if (TargetActive(target, CurrentPlayerView) == 0)
		return;

	gDraw3DArrowBlue = 0;

	flags = 2;
	
	switch(target->data[0])
	{
		case 1:
		{
			tv.vx = target->data[3];
			tv.vz = target->data[4];
			tv.vy = 10000;

			switch(target->data[1] & 0x30000)
			{
				case 0x20000:
				{
					gDraw3DArrowBlue = 1;
					break;
				}
				case 0x30000:
				{
					if (gPlayerWithTheFlag == -1) 
					{
						if (CurrentPlayerView == 1)
							gDraw3DArrowBlue = 1;
					}
					else
					{
						if (CurrentPlayerView == gPlayerWithTheFlag) 
							return;

						tv.vx = player[gPlayerWithTheFlag].pos[0];
						tv.vz = player[gPlayerWithTheFlag].pos[2];

						if (gPlayerWithTheFlag == 1)
							gDraw3DArrowBlue = 1;
					}

					break;
				}
				case 0x10000:
				{
					gDraw3DArrowBlue = CurrentPlayerView;
					break;
				}
			}

			if (target->data[7] != 0) 
				tv.vy = target->data[6];
			else 
				tv.vy = -MapHeight(&tv);
			
			break;
		}
		case 2:
		{
			int slot;
			slot = target->data[6];

			if (slot == -1)
				return;

			tv.vx = car_data[slot].hd.where.t[0];
			tv.vz = car_data[slot].hd.where.t[2];
			tv.vy = -car_data[slot].hd.where.t[1];
			break;
		}
		case 3:
		{
			tv = *(VECTOR*)target->data[4];
			break;
		}
		default:
			return;
	}

	if (gMultiplayerLevels != 0 && doSpooling == 0 || Long2DDistance(player[0].spoolXZ, &tv) <= 15900)
	{
		if (target->data[2] & 0x20)
			flags |= 0x1;

		if (target->data[2] & 0x80)
			flags |= 0x20;

		if (flags) 
			Draw3DTarget(&tv, flags);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMultiplayerTarget(MS_TARGET *target /*$s0*/)
 // line 419, offset 0x0005f864
	/* begin block 1 */
		// Start line: 420
		// Start offset: 0x0005F864
		// Variables:
	// 		VECTOR tv; // stack offset -40
	// 		unsigned char r; // $s3
	// 		unsigned char g; // $s2
	// 		unsigned char b; // $s1
	/* end block 1 */
	// End offset: 0x0005FA6C
	// End Line: 517

	/* begin block 2 */
		// Start line: 859
	/* end block 2 */
	// End Line: 860

// [D] [T]
void DrawMultiplayerTarget(MS_TARGET *target)
{
	u_char b;
	u_char g;
	u_char r;
	VECTOR tv;
	int activeTargets;

	if (TargetComplete(target, -1))
		return;

	activeTargets = TargetActive(target, 0) ? 0x1 : 0x0;
	activeTargets |= TargetActive(target, 1) ? 0x2 : 0x0;

	if (activeTargets == 0)
		return;

	r = 64;
	g = 64;
	b = 64;

	if(activeTargets == 1)
	{
		r = 128;
		g = 0;
		b = 0;
	}
	else if(activeTargets == 2)
	{
		r = 0;
		g = 128;
		b = 0;
	}

	switch(target->data[0])
	{
		case 1:
		{
			tv.vx = target->data[3];
			tv.vz = target->data[4];
			tv.vy = 10000;

			switch(target->data[1] & 0x30000)
			{
				case 0x10000:
				{
					r = 128;
					g = 0;
					b = 0;
					break;
				}
				case 0x20000:
				{
					r = 0;
					g = 128;
					b = 0;
					break;
				}
				case 0x30000:
				{
					if(gPlayerWithTheFlag != -1)
					{
						tv.vx = player[gPlayerWithTheFlag].pos[0];
						tv.vz = player[gPlayerWithTheFlag].pos[2];
					}

					break;
				}
			}

			if (target->data[7] != 0) 
				tv.vy = target->data[6];
			else 
				tv.vy = -MapHeight(&tv);

			break;
		}
		case 2:
		{
			int slot;
			slot = target->data[6];

			if (slot == -1)
				return;

			tv.vx = car_data[slot].hd.where.t[0];
			tv.vz = car_data[slot].hd.where.t[2];
			tv.vy = -car_data[slot].hd.where.t[1];
			break;
		}
		case 3:
		{
			tv = *(VECTOR*)target->data[4];
			break;
		}
		default:
			return;
	}

	if (target->data[2] & 0x10) 
	{
		DrawTargetBlip(&tv, r, g, b, 0x30);
	}
}





