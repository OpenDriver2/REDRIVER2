#include "DRIVER2.H"
#include "MDRAW.H"
#include "PRES.H"
#include "MISSION.H"
#include "OVERMAP.H"
#include "CUTSCENE.H"
#include "GLAUNCH.H"
#include "OVERLAY.H"
#include "REPLAYS.H"
#include "PAUSE.H"
#include "PLAYERS.H"
#include "MAIN.H"
#include "SPOOL.H"
#include "DR2ROADS.H"
#include "CARS.H"
#include "TARGETS.H"
#include "OVERLAY.H"

int gDisplayPosition = 0;

// [D] [T]
void DrawTimer(MR_TIMER* timer)
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


// [D] [T]
void DisplayPlayerPosition(void)
{
	char string[40];

	sprintf(string, "X: %d, Y: %d, Z: %d", player[0].pos[0], player[0].pos[1], player[0].pos[2]);
	PrintString(string, 20, 210);
}

// [D] [T]
void DrawMessage(int y, char* string)
{
	if (!string)
		return;

	SetTextColour(128, 128, 64);

	if (StringWidth(string) < 273)
		PrintStringCentred(string, y - 10);
	else
		PrintStringBoxed(string, 24, y - 10);
}


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
			PrintString("Out of tape", gOverlayXPos, 236);
		}
	}
}

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

			// Capture the Flag target properties
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

			// Capture the Flag target properties
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


// [D] [T]
void DrawWorldTargets(void)
{
	int i;

	if (Mission.active == 0)
		return;

	for (i = 0; i < 16; i++)
		DrawWorldTarget(&MissionTargets[i]);
}


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