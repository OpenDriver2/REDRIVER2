#include "THISDUST.H"
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

int gDisplayPosition = 1; // [A] was 0

// [D]
void DrawMission(void)
{
	char *string;

	if ((((gShowMap == 0) && (NoPlayerControl == 0)) && (gInGameCutsceneActive == 0)) &&
		(bMissionTitleFade == 0)) {
		if (gDisplayPosition != 0) {
			DisplayPlayerPosition();
		}
		if ((MissionHeader->type & 4U) == 0) {
			if (pauseflag == 0) {
				if (Mission.message_timer[0] != 0) {
					if (NumPlayers == 1) {
						DrawMessage(0x60, Mission.message_string[0]);
					}
					else {
						DrawMessage(0x40, Mission.message_string[0]);
					}
				}
				if (Mission.message_timer[1] != 0) {
					DrawMessage(0xc0, Mission.message_string[1]);
				}
			}
		}
		else {
			SetTextColour(0x80, 0x80, 0x40);

			if (g321GoDelay < 0x20)
			{
				string = "3";
			}
			else
			{
				if (g321GoDelay < 0x40)
				{
					string = "2";
				}
				else
				{
					string = "1";
				}
			}
			if (NumPlayers == 1) {
				PrintScaledString(0x60, string, 0x20 - (g321GoDelay & 0x1fU));
			}
			else {
				PrintScaledString(0x40, string, 0x20 - (g321GoDelay & 0x1fU));
				PrintScaledString(0xc0, string, 0x20 - (g321GoDelay & 0x1fU));
			}
		}
		if ((Mission.active != 0) && (NoPlayerControl == 0))
		{
			DrawWorldTargets();
			DrawTimer(Mission.timer);
			DrawTimer(Mission.timer + 1);

			DrawProximityBar(&ProxyBar);

			if (gOutOfTape != 0) {
				SetTextColour(-0x80, -0x80, '@');
				PrintString("Out of tape", 0x14, 0xec);
			}
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTimer(struct MR_TIMER *timer /*$s1*/)
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

void DrawTimer(MR_TIMER *timer)
{
	UNIMPLEMENTED();

	/*
	short sVar1;
	undefined2 extraout_var;
	char acStack32[16];

	if (((timer->flags & 1) != 0) && ((timer->flags & 0x20) == 0)) {
		if (NumPlayers == 1) {
			SetTextColour(-0x80, -0x80, -0x80);
		}
		else {
			if (timer == (MR_TIMER *)&DAT_000d7c24) {
				SetTextColour(-0x80, ' ', ' ');
			}
			else {
				SetTextColour(' ', -0x80, ' ');
			}
		}
		sprintf(acStack32, s__02d__02d_000110d8, (uint)timer->min, (uint)timer->sec);
		sVar1 = PrintDigit((int)timer->x, (int)timer->y, acStack32);
		sprintf(acStack32, s___02d_000aa698, (uint)timer->frac);
		PrintString(acStack32, CONCAT22(extraout_var, sVar1), (int)timer->y + 0xd);
	}
	return;
	*/
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

// [D]
void DisplayPlayerPosition(void)
{
	char string[32];

	sprintf(string, "X: %d, Z: %d", player[0].pos[0], player[0].pos[2]);
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

// [D]
void DrawMessage(int y, char *string)
{
	int iVar1;

	if (string != (char *)0x0) {
		SetTextColour(-0x80, -0x80, '@');
		iVar1 = StringWidth(string);
		if (iVar1 < 0x111) {
			PrintStringCentred(string, (short)((uint)((y + -10) * 0x10000) >> 0x10));
		}
		else {
			PrintStringBoxed(string, 0x18, y + -10);
		}
	}
	return;
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

// [D]
void DrawWorldTargets(void)
{
	int iVar1;
	int iVar2;

	if (Mission.active != 0) {
		iVar2 = 0;
		iVar1 = 0;
		do {
			iVar2 = iVar2 + 1;
			DrawWorldTarget((_TARGET *)((int)MissionTargets->data + iVar1));
			iVar1 = iVar2 * 0x40;
		} while (iVar2 < 0x10);
	}
	return;
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

// [D]
void DrawOverheadTargets(void)
{
	int iVar1;
	int iVar2;

	if (Mission.active != 0) {
		iVar2 = 0;
		iVar1 = 0;
		do {
			iVar2 = iVar2 + 1;
			DrawOverheadTarget((_TARGET *)((int)MissionTargets->data + iVar1));
			iVar1 = iVar2 * 0x40;
		} while (iVar2 < 0x10);
	}
	return;
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

// [D]
void DrawFullscreenTargets(void)
{
	int iVar1;
	int iVar2;

	if (Mission.active != 0) {
		iVar2 = 0;
		iVar1 = 0;
		do {
			iVar2 = iVar2 + 1;
			DrawFullscreenTarget((_TARGET *)((int)MissionTargets->data + iVar1));
			iVar1 = iVar2 * 0x40;
		} while (iVar2 < 0x10);
	}
	return;
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

// [D]
void DrawMultiplayerTargets(void)
{
	int iVar1;
	int iVar2;

	if (Mission.active != 0) {
		iVar2 = 0;
		iVar1 = 0;
		do {
			iVar2 = iVar2 + 1;
			DrawMultiplayerTarget((_TARGET *)((int)MissionTargets->data + iVar1));
			iVar1 = iVar2 * 0x40;
		} while (iVar2 < 0x10);
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawOverheadTarget(struct _TARGET *target /*$s0*/)
 // line 230, offset 0x0005fd7c
	/* begin block 1 */
		// Start line: 231
		// Start offset: 0x0005FD7C
		// Variables:
	// 		struct VECTOR tv; // stack offset -24
	/* end block 1 */
	// End offset: 0x0005FE84
	// End Line: 269

	/* begin block 2 */
		// Start line: 893
	/* end block 2 */
	// End Line: 894

// [D]
void DrawOverheadTarget(_TARGET *target)
{
	int iVar1;
	int *piVar2;
	VECTOR local_18;

	iVar1 = TargetComplete(target, -1);
	if (iVar1 != 0) {
		return;
	}
	if ((target->data[1] & 0x600U) == 0) {
		return;
	}
	iVar1 = target->data[0];
	if (iVar1 != 2) {
		if (2 < iVar1) {
			if (iVar1 != 3) {
				return;
			}
			piVar2 = (int *)target->data[4];
			local_18.vx = *piVar2;
			local_18.vy = piVar2[1];
			local_18.vz = piVar2[2];
			local_18.pad = piVar2[3];
			goto LAB_0005fe3c;
		}
		if (iVar1 != 1) {
			return;
		}
	}
	local_18.vx = target->data[3];
	local_18.vz = target->data[4];
	local_18.vy = 0;
LAB_0005fe3c:
	if ((target->data[2] & 0x10U) != 0) {
		DrawTargetBlip(&local_18, '@', '@', '@', 0x11);
	}
	if ((target->data[2] & 0x40U) != 0) {
		DrawTargetArrow(&local_18, 1);
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFullscreenTarget(struct _TARGET *target /*$s0*/)
 // line 271, offset 0x0005fe94
	/* begin block 1 */
		// Start line: 272
		// Start offset: 0x0005FE94
		// Variables:
	// 		struct VECTOR tv; // stack offset -24
	/* end block 1 */
	// End offset: 0x0005FF9C
	// End Line: 310

	/* begin block 2 */
		// Start line: 977
	/* end block 2 */
	// End Line: 978

// [D]
void DrawFullscreenTarget(_TARGET *target)
{
	int iVar1;
	int *piVar2;
	VECTOR local_18;

	iVar1 = TargetComplete(target, -1);
	if (iVar1 != 0) {
		return;
	}
	if ((target->data[1] & 0x600U) == 0) {
		return;
	}
	iVar1 = target->data[0];
	if (iVar1 != 2) {
		if (2 < iVar1) {
			if (iVar1 != 3) {
				return;
			}
			piVar2 = (int *)target->data[4];
			local_18.vx = *piVar2;
			local_18.vy = piVar2[1];
			local_18.vz = piVar2[2];
			local_18.pad = piVar2[3];
			goto LAB_0005ff54;
		}
		if (iVar1 != 1) {
			return;
		}
	}
	local_18.vx = target->data[3];
	local_18.vz = target->data[4];
	local_18.vy = 0;
LAB_0005ff54:
	if ((target->data[2] & 0x10U) != 0) {
		DrawTargetBlip(&local_18, '@', '@', '@', 0x14);
	}
	if ((target->data[2] & 0x40U) != 0) {
		DrawTargetArrow(&local_18, 4);
	}
	return;
}

// decompiled code
// original method signature: 
// void /*$ra*/ DrawWorldTarget(struct _TARGET *target /*$s0*/)
 // line 312, offset 0x0005f56c
	/* begin block 1 */
		// Start line: 313
		// Start offset: 0x0005F56C
		// Variables:
	// 		struct VECTOR tv; // stack offset -32
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

void DrawWorldTarget(_TARGET *target)
{
	UNIMPLEMENTED();

	/*
	int iVar1;
	int iVar2;
	ulong uVar3;
	uint uVar4;
	long *plVar5;
	uint flags;
	VECTOR local_20;

	iVar2 = TargetComplete(target, CurrentPlayerView);
	if (iVar2 != 0) {
		return;
	}
	iVar2 = TargetActive(target, CurrentPlayerView);
	if (iVar2 == 0) {
		return;
	}
	iVar2 = target->data[0];
	gDraw3DArrowBlue = 0;
	flags = 0;
	if (iVar2 == 2) {
		iVar2 = target->data[6];
		if (iVar2 == -1) {
			gDraw3DArrowBlue = 0;
			return;
		}
		local_20.vx = car_data[iVar2].hd.where.t[0];
		local_20.vz = car_data[iVar2].hd.where.t[2];
		local_20.vy = (int)-car_data[iVar2].hd.where.t[1];
		goto LAB_0005f7dc;
	}
	if (2 < iVar2) {
		if (iVar2 != 3) {
			gDraw3DArrowBlue = 0;
			return;
		}
		plVar5 = (long *)target->data[4];
		local_20.vx = *plVar5;
		local_20.vy = (int)plVar5[1];
		local_20.vz = plVar5[2];
		local_20.pad = plVar5[3];
		goto LAB_0005f7dc;
	}
	if (iVar2 != 1) {
		gDraw3DArrowBlue = 0;
		return;
	}
	local_20.vx = target->data[3];
	local_20.vz = target->data[4];
	local_20.vy = &DAT_00002710;
	uVar4 = target->data[1] & 0x30000;
	flags = 2;
	if (uVar4 == 0x20000) {
	LAB_0005f69c:
		gDraw3DArrowBlue = iVar2;
	}
	else {
		if (uVar4 < 0x20001) {
			if (uVar4 != 0x10000) {
			LAB_0005f6c8:
				gDraw3DArrowBlue = CurrentPlayerView;
			}
		}
		else {
			if (uVar4 != 0x30000) goto LAB_0005f6c8;
			iVar1 = CurrentPlayerView;
			if (gPlayerWithTheFlag != -1) {
				if (CurrentPlayerView == gPlayerWithTheFlag) {
					gDraw3DArrowBlue = 0;
					return;
				}
				local_20.vx = (&player)[gPlayerWithTheFlag].pos[0];
				local_20.vz = (&player)[gPlayerWithTheFlag].pos[2];
				iVar1 = gPlayerWithTheFlag;
			}
			if (iVar1 == 1) goto LAB_0005f69c;
		}
	}
	if (((gMultiplayerLevels == 0) || (doSpooling != 0)) &&
		(uVar3 = Long2DDistance(player.spoolXZ, &local_20), 0x3e1c < (int)uVar3)) {
		return;
	}
	if (target->data[7] == 0) {
		iVar2 = MapHeight(&local_20);
		local_20.vy = (int)-iVar2;
	}
	else {
		local_20.vy = (int)target->data[6];
	}
LAB_0005f7dc:
	if (((gMultiplayerLevels != 0) && (doSpooling == 0)) ||
		(uVar3 = Long2DDistance(player.spoolXZ, &local_20), (int)uVar3 < 0x3e1d)) {
		if ((target->data[2] & 0x20U) != 0) {
			flags = flags | 1;
		}
		if ((target->data[2] & 0x80U) != 0) {
			flags = flags | 0x20;
		}
		if (flags != 0) {
			Draw3DTarget(&local_20, flags);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMultiplayerTarget(struct _TARGET *target /*$s0*/)
 // line 419, offset 0x0005f864
	/* begin block 1 */
		// Start line: 420
		// Start offset: 0x0005F864
		// Variables:
	// 		struct VECTOR tv; // stack offset -40
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

void DrawMultiplayerTarget(_TARGET *target)
{
	UNIMPLEMENTED();

	/*
	int iVar1;
	uint uVar2;
	long *plVar3;
	uchar b;
	uchar g;
	uchar r;
	VECTOR local_28;

	iVar1 = TargetComplete(target, -1);
	if (iVar1 != 0) {
		return;
	}
	iVar1 = TargetActive(target, 0);
	if ((iVar1 == 0) && (iVar1 = TargetActive(target, 1), iVar1 == 0)) {
		return;
	}
	r = '@';
	g = '@';
	iVar1 = target->data[0];
	b = '@';
	if (iVar1 == 2) {
		local_28.vx = target->data[3];
		local_28.vz = target->data[4];
		local_28.vy = 0;
		goto LAB_0005fa40;
	}
	if (2 < iVar1) {
		if (iVar1 != 3) {
			return;
		}
		plVar3 = (long *)target->data[4];
		local_28.vx = *plVar3;
		local_28.vy = plVar3[1];
		local_28.vz = plVar3[2];
		local_28.pad = plVar3[3];
		goto LAB_0005fa40;
	}
	if (iVar1 != 1) {
		return;
	}
	local_28.vx = target->data[3];
	local_28.vz = target->data[4];
	local_28.vy = 0;
	uVar2 = target->data[1] & 0x30000;
	if (uVar2 == 0x20000) {
	LAB_0005f9e4:
		r = '\0';
		g = -0x80;
		b = '\0';
	}
	else {
		if (uVar2 < 0x20001) {
			if (uVar2 != 0x10000) {
			LAB_0005f998:
				if ((NumPlayers < 2) || (iVar1 = TargetActive(target, -1), iVar1 != 0)) goto LAB_0005fa40;
				iVar1 = TargetActive(target, 0);
				if (iVar1 == 0) goto LAB_0005f9e4;
			}
		}
		else {
			if (uVar2 != 0x30000) goto LAB_0005f998;
			if (gPlayerWithTheFlag == -1) goto LAB_0005fa40;
			local_28.vx = (&player)[gPlayerWithTheFlag].pos[0];
			local_28.vz = (&player)[gPlayerWithTheFlag].pos[2];
			local_28.vy = 0;
			if (gPlayerWithTheFlag != 0) goto LAB_0005f9e4;
		}
		r = -0x80;
		g = '\0';
		b = '\0';
	}
LAB_0005fa40:
	if ((target->data[2] & 0x10U) != 0) {
		DrawTargetBlip(&local_28, r, g, b, 0x30);
	}
	return;*/
}





