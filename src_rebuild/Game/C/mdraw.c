#include "driver2.h"
#include "mdraw.h"
#include "pres.h"
#include "mission.h"
#include "overmap.h"
#include "cutscene.h"
#include "glaunch.h"
#include "overlay.h"
#include "replays.h"
#include "pause.h"
#include "players.h"
#include "main.h"
#include "spool.h"
#include "dr2roads.h"
#include "cars.h"
#include "targets.h"
#include "system.h"

int gDisplayPosition = 0;

// [D] [T]
void DrawTimer(MR_TIMER* timer)
{
	short digit_pos;
	char string[16];

	if ((timer->flags & TIMER_FLAG_ACTIVE) && !(timer->flags & TIMER_FLAG_BOMB_TRIGGERED))
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

		sprintf(string, "%02d:%02d", (u_int)timer->min, (u_int)timer->sec);
		digit_pos = PrintDigit((int)timer->x, (int)timer->y, string);

		sprintf(string, ".%02d", (u_int)timer->frac);
		PrintString(string, digit_pos, (int)timer->y + 13);
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
	
	if (MissionHeader->type & 4)
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
			PrintScaledString(SCREEN_H / 4, string, 32 - (g321GoDelay & 0x1f));
			PrintScaledString(SCREEN_H / 2 + SCREEN_H / 4, string, 32 - (g321GoDelay & 0x1f));
		}
	}
	else if (!pauseflag)
	{
		if (Mission.message_timer[0] != 0)
		{
			if (NumPlayers == 1)
				DrawMessage(96, Mission.message_string[0]);
			else
				DrawMessage(SCREEN_H / 4, Mission.message_string[0]);
		}

		if (Mission.message_timer[1] != 0)
			DrawMessage(SCREEN_H / 2 + SCREEN_H / 4, Mission.message_string[1]);
	}

	if (Mission.active && !NoPlayerControl)
	{
		DrawWorldTargets();

		if (gDoOverlays)
		{
			DrawTimer(&Mission.timer[0]);
			DrawTimer(&Mission.timer[1]);

			DrawProximityBar(&ProxyBar);

			if (gOutOfTape)
			{
				SetTextColour(128, 128, 64);
				PrintString(G_LTXT(GTXT_OutOfTape), gOverlayXPos, SCREEN_H - 20);
			}
		}
	}
}

// [D] [T]
void DrawOverheadTarget(MS_TARGET *target)
{
	VECTOR tv;

	if (TargetComplete(target, -1))
		return;

	if (!(target->s.target_flags & TARGET_FLAG_VISIBLE_ALLP))
		return;

	switch(target->type)
	{
		case Target_Point:	// point or car target
		case Target_Car:
		{
			tv.vx = target->s.car.posX;
			tv.vz = target->s.car.posZ;
			tv.vy = 0;
			break;
		}
		case Target_Event:	// event target
			tv = *(*(VECTOR**)&target->s.event.eventPos);
			break;
		default:
			return;
	}

	if (target->s.display_flags & 0x10)
		DrawTargetBlip(&tv, 64, 64, 64, 0x11);

	if (target->s.display_flags & 0x40)
		DrawTargetArrow(&tv, 1);
}

// [D] [T]
void DrawFullscreenTarget(MS_TARGET *target)
{
	VECTOR tv;

	if (TargetComplete(target, -1))
		return;

	if (!(target->s.target_flags & TARGET_FLAG_VISIBLE_ALLP))
		return;

	switch(target->type)
	{
		case Target_Point:	// point or car target
		case Target_Car:
		{
			tv.vx = target->s.car.posX;
			tv.vz = target->s.car.posZ;
			tv.vy = 0;
			break;
		}
		case Target_Event:	// event target
			tv = *(*(VECTOR**)&target->s.event.eventPos);
			break;
		default:
			return;
	}

	if (target->s.display_flags & 0x10)
		DrawTargetBlip(&tv, 64, 64, 64, 0x14);

	if (target->s.display_flags & 0x40)
		DrawTargetArrow(&tv, 4);
}

// [D] [T]
void DrawWorldTarget(MS_TARGET *target)
{
	u_int flags;
	VECTOR tv;

	if (TargetComplete(target, CurrentPlayerView))
		return;

	if (TargetActive(target, CurrentPlayerView) == 0)
		return;

	gDraw3DArrowBlue = 0;

	flags = 0x2;
	
	switch(target->type)
	{
		case Target_Point:
		{
			tv.vx = target->s.point.posX;
			tv.vz = target->s.point.posZ;
			tv.vy = 10000;

			// Capture the Flag target properties
			switch(target->s.target_flags & (TARGET_FLAG_POINT_CTF_BASE_P1 | TARGET_FLAG_POINT_CTF_BASE_P2 | TARGET_FLAG_POINT_CTF_FLAG))
			{
				case TARGET_FLAG_POINT_CTF_BASE_P1:
				{
					// [A]
					if(CurrentPlayerView != 0)
						flags = 0x10;
						
					gDraw3DArrowBlue = 0;
					break;
				}
				case TARGET_FLAG_POINT_CTF_BASE_P2:
				{
					// [A]
					if (CurrentPlayerView != 1)
						flags = 0x10;
						
					gDraw3DArrowBlue = 1;
					break;
				}
				case TARGET_FLAG_POINT_CTF_FLAG:
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
			}

			if (target->s.point.height != 0)
				tv.vy = target->s.point.posY;
			else 
				tv.vy = -MapHeight(&tv);
			
			break;
		}
		case Target_Car:
		{
			int slot;
			slot = target->s.car.slot;

			if (slot == -1)
				return;

			tv.vx = car_data[slot].hd.where.t[0];
			tv.vz = car_data[slot].hd.where.t[2];
			tv.vy = -car_data[slot].hd.where.t[1];
			break;
		}
		case Target_Event:
		{
			tv = *(*(VECTOR**)&target->s.event.eventPos);
			break;
		}
		default:
			return;
	}

	if (gMultiplayerLevels && doSpooling == 0 || Long2DDistance(player[0].spoolXZ, &tv) <= 15900)
	{
		if((flags & 0x10) == 0)
		{
			if (target->s.display_flags & 0x20)
				flags |= 0x1;

			if (target->s.display_flags & 0x80)
				flags |= 0x20;
		}

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

	switch(target->type)
	{
		case Target_Point:
		{
			tv.vx = target->s.point.posX;
			tv.vz = target->s.point.posZ;
			tv.vy = 10000;

			// Capture the Flag target properties
			switch(target->s.target_flags & (TARGET_FLAG_POINT_CTF_BASE_P1 | TARGET_FLAG_POINT_CTF_BASE_P2 | TARGET_FLAG_POINT_CTF_FLAG))
			{
				case TARGET_FLAG_POINT_CTF_BASE_P1:
				{
					r = 128;
					g = 0;
					b = 0;
					break;
				}
				case TARGET_FLAG_POINT_CTF_BASE_P2:
				{
					r = 0;
					g = 128;
					b = 0;
					break;
				}
				case TARGET_FLAG_POINT_CTF_FLAG:
				{
					if(gPlayerWithTheFlag != -1)
					{
						tv.vx = player[gPlayerWithTheFlag].pos[0];
						tv.vz = player[gPlayerWithTheFlag].pos[2];
					}

					break;
				}
			}

			if (target->s.point.height != 0)
				tv.vy = target->s.point.posY;
			else 
				tv.vy = -MapHeight(&tv);

			break;
		}
		case Target_Car:
		{
			int slot;
			slot = target->s.car.slot;

			if (slot == -1)
				return;

			tv.vx = car_data[slot].hd.where.t[0];
			tv.vz = car_data[slot].hd.where.t[2];
			tv.vy = -car_data[slot].hd.where.t[1];
			break;
		}
		case Target_Event:
		{
			tv = *(*(VECTOR**)&target->s.event.eventPos);
			break;
		}
		default:
			return;
	}

	if (target->s.display_flags & 0x10)
	{
		DrawTargetBlip(&tv, r, g, b, 0x30);
	}
}


// [D] [T]
void DrawWorldTargets(void)
{
	int i;

	if (!Mission.active)
		return;

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
		DrawWorldTarget(&MissionTargets[i]);
}


// [D] [T]
void DrawOverheadTargets(void)
{
	int i;

	if (!Mission.active)
		return;

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
		DrawOverheadTarget(&MissionTargets[i]);
}


// [D] [T]
void DrawFullscreenTargets(void)
{
	int i;

	if (!Mission.active)
		return;

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
		DrawFullscreenTarget(&MissionTargets[i]);
}

// [D] [T]
void DrawMultiplayerTargets(void)
{
	int i;

	if (!Mission.active)
		return;

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
		DrawMultiplayerTarget(&MissionTargets[i]);
}