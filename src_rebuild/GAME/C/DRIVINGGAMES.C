#include "DRIVER2.H"
#include "DRIVINGGAMES.H"
#include "SCORES.H"
#include "MISSION.H"
#include "CUTSCENE.H"
#include "MAIN.H"
#include "SYSTEM.H"
#include "DRAW.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "COSMETIC.H"
#include "BCOLLIDE.H"
#include "CAMERA.H"
#include "CONVERT.H"
#include "MAP.H"
#include "SOUND.H"
#include "GLAUNCH.H"

#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"
#include <stdlib.h>

MODEL* gTrailblazerConeModel; 
SMASHED_CONE smashed_cones[6];

TRAILBLAZER_DATA *gTrailblazerData;
int gTrailblazerConeCount;
int gTrailblazerConeIndex;
static int gTrailblazerPrevConeDelay = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ InitDrivingGames()
 // line 231, offset 0x0004310c
	/* begin block 1 */
		// Start line: 233
		// Start offset: 0x0004310C
		// Variables:
	// 		char filename[64]; // stack offset -72
	// 		int i; // $a0
	// 		int j; // $v1
	/* end block 1 */
	// End offset: 0x0004326C
	// End Line: 288

	/* begin block 2 */
		// Start line: 462
	/* end block 2 */
	// End Line: 463

	/* begin block 3 */
		// Start line: 463
	/* end block 3 */
	// End Line: 464

	/* begin block 4 */
		// Start line: 466
	/* end block 4 */
	// End Line: 467

/* WARNING: Unknown calling convention yet parameter storage is locked */

static int wrongside[2][6];
static int current_smashed_cone = 0;

// [D]
void InitDrivingGames(void)
{
	char filename[64];
	int i;
	int j;

	gPlayerScore.time = 0;
	gTrailblazerData = NULL;
	gPlayerScore.items = 0;
	gPlayerScore.P2time = 0;
	gPlayerScore.P2items = 0;

	if ((GameType == GAME_GATERACE) || (GameType == GAME_TRAILBLAZER)) 
	{
		if (CutsceneBuffer.bytesFree < 1200)
		{
			while (FrameCnt != 0x78654321) 
			{
				trap(0x400);
			}
		}

		gTrailblazerConeCount = 0;
		gTrailblazerConeIndex = 0;
		gTrailblazerData = (TRAILBLAZER_DATA *)CutsceneBuffer.currentPointer;

		CutsceneBuffer.bytesFree -= 1200;
		sprintf(filename, "TRAILS\\TRAIL.%d", gCurrentMissionNumber);

		if (FileExists(filename) != 0) 
			Loadfile(filename, (char *)gTrailblazerData);
	}

    i = 0;
	while (i < 2)
	{
        j = 0;

		while (j < 6)
            wrongside[i][j++] = 0;

        i++;
    };

    i = 0;
    while(i < 6)
	{
		smashed_cones[i].cone = -1;
		smashed_cones[i].active = 0;
		smashed_cones[i].side = 0;
		smashed_cones[i++].rot_speed = 0;
    };

    current_smashed_cone = 0;
    gTrailblazerPrevConeDelay = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleDrivingGames()
 // line 290, offset 0x0004326c
	/* begin block 1 */
		// Start line: 292
		// Start offset: 0x0004326C
		// Variables:
	// 		struct _CAR_DATA *cp; // $a2
	// 		struct VECTOR vel; // stack offset -96
	// 		int i; // $s3
	// 		int j; // $v1
	// 		int k; // $a0
	// 		int id; // $s2
	// 		int dist; // $a1

		/* begin block 1.1 */
			// Start line: 351
			// Start offset: 0x00043354
			// Variables:
		// 		struct VECTOR pos1; // stack offset -80
		// 		struct VECTOR pos2; // stack offset -64
		// 		int x; // $t0
		// 		int z; // $a1
		// 		int r; // $v0
		// 		int side; // $s1
		// 		int radius; // $a0
		/* end block 1.1 */
		// End offset: 0x00043658
		// End Line: 413

		/* begin block 1.2 */
			// Start line: 435
			// Start offset: 0x00043700
			// Variables:
		// 		struct VECTOR pos; // stack offset -80
		/* end block 1.2 */
		// End offset: 0x00043800
		// End Line: 456
	/* end block 1 */
	// End offset: 0x000438DC
	// End Line: 475

	/* begin block 2 */
		// Start line: 600
	/* end block 2 */
	// End Line: 601

	/* begin block 3 */
		// Start line: 603
	/* end block 3 */
	// End Line: 604

	/* begin block 4 */
		// Start line: 604
	/* end block 4 */
	// End Line: 605

	/* begin block 5 */
		// Start line: 608
	/* end block 5 */
	// End Line: 609

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void HandleDrivingGames(void)
{
	char cVar1;
	bool bVar2;
	int iVar3;
	int *piVar4;
	int iVar5;
	TRAILBLAZER_DATA *pTVar6;
	int player_id;
	int iVar7;
	int iVar8;
	uint uVar9;
	int iVar10;
	long *plVar11;
	int iVar12;
	VECTOR vel;
	VECTOR pos1;
	VECTOR pos2;

	if (gTrailblazerPrevConeDelay > 0) 
		gTrailblazerPrevConeDelay--;

	if (GameType == GAME_GATERACE) 
	{
		if (gTrailblazerData == NULL)
			goto LAB_0004386c;

		MoveSmashedCones();

		if (NumPlayers != 0)
		{
			player_id = 0;
		LAB_0004330c:
			iVar10 = 0;
			iVar12 = player_id + 1;
			plVar11 = &Mission.timer[player_id].count;
			piVar4 = wrongside[player_id];
		LAB_0004333c:

			if (99 < gTrailblazerConeIndex + iVar10) 
				goto LAB_00043658;

			GetConePos(gTrailblazerConeIndex + iVar10, &pos1, 0);
			GetConePos(gTrailblazerConeIndex + iVar10, &pos2, 1);

			iVar5 = CarConeCollision(&pos1, (int)player[player_id].playerCarId);
			uVar9 = (uint)(iVar5 != 0);
			iVar3 = CarConeCollision(&pos2, (int)player[player_id].playerCarId);
			iVar5 = gTrailblazerConeIndex;

			if (iVar3 != 0)
				uVar9 = 2;

			if (uVar9 == 0) 
			{
				pTVar6 = gTrailblazerData + gTrailblazerConeIndex + iVar10;
				uVar9 = pTVar6->rot & 0xfff;
				iVar8 = player[player_id].pos[0] - pTVar6->x;
				iVar3 = player[player_id].pos[2] - pTVar6->z;

				if (iVar8 * rcossin_tbl[uVar9 * 2] + iVar3 * rcossin_tbl[uVar9 * 2 + 1] < 1) 
				{
					*piVar4 = 1;
					goto LAB_00043658;
				}

				iVar8 = iVar8 * rcossin_tbl[uVar9 * 2 + 1];

				if (wrongside[player_id * 6 + iVar10] == 0)
					goto LAB_00043658;

				iVar3 = iVar3 * rcossin_tbl[uVar9 * 2];
				iVar7 = iVar8 - iVar3;
				wrongside[player_id][iVar10] = 0;

				if (iVar7 < 0)
					iVar7 = iVar3 - iVar8;

				if ((600 - (iVar5 * 400 + iVar10) / 100) * 0x1000 <= iVar7) 
					goto LAB_00043658;

				gTrailblazerConeIndex = iVar5 + 1 + iVar10;
				plVar11 = &Mission.timer[player_id].count;
				gTrailblazerPrevConeDelay = 10;
				gTrailblazerConeCount = gTrailblazerConeCount + 1;
				*plVar11 = *plVar11 + 3000;
				if (player_id == 0)
					gPlayerScore.items++;
				else
					gPlayerScore.P2items++;

				player_id = 0;
				iVar10 = 1;
				do {
					iVar5 = 5;
					piVar4 = wrongside[player_id] + 5;

					do {
						*piVar4 = 0;
						iVar5 = iVar5 + -1;
						piVar4 = piVar4 + -1;
					} while (-1 < iVar5);

					bVar2 = iVar10 < 2;
					player_id = iVar10;
					iVar10 = iVar10 + 1;
				} while (bVar2);
			}
			else
			{
				iVar5 = car_data[player[player_id].playerCarId].st.n.linearVelocity[0];

				vel.vx = iVar5 >> 0xc;
				vel.vy = -0x11;
				iVar5 = car_data[player[player_id].playerCarId].st.n.linearVelocity[2];

				vel.vz = iVar5 >> 0xc;
				SetSmashedCone(gTrailblazerConeIndex + iVar10, &vel, player_id, uVar9 - 1);
				gTrailblazerConeIndex = gTrailblazerConeIndex + 1 + iVar10;
				*plVar11 = *plVar11 + -3000;
				SetPlayerMessage(player_id, "-1 second", 2, 1);
			}
			goto LAB_00043668;
		}
	}
	else
	{
		if (GameType != GAME_TRAILBLAZER || gTrailblazerData == NULL) 
			goto LAB_0004386c;

		MoveSmashedCones();

		if (NumPlayers != 0) 
		{
			player_id = 0;
			do {
				iVar10 = 0;
				iVar12 = player_id + 1;
				do {
					if (gTrailblazerConeIndex + iVar10 < 100) 
					{
						GetConePos(gTrailblazerConeIndex + iVar10, &pos1, -1);
						iVar5 = CarConeCollision(&pos1, (int)player[player_id].playerCarId);
						if (iVar5 != 0)
						{
							cVar1 = player[player_id].playerCarId;
							plVar11 = &Mission.timer[player_id].count;
							*plVar11 = *plVar11 + 3000;
							iVar5 = car_data[cVar1].st.n.linearVelocity[0];

							vel.vx = iVar5 >> 0xc;
							vel.vy = -0x11;
							iVar5 = car_data[cVar1].st.n.linearVelocity[2];

							vel.vz = iVar5 >> 0xc;
							SetSmashedCone(gTrailblazerConeIndex + iVar10, &vel, player_id, 0);
							gTrailblazerConeCount++;
							gTrailblazerConeIndex += 1 + iVar10;

							if (player_id == 0)
								gPlayerScore.items++;
							else
								gPlayerScore.P2items++;

						}
					}
					iVar10 = iVar10 + 1;
				} while (iVar10 < 6);

				player_id = iVar12;
			} while (iVar12 < NumPlayers);
		}
	}

	// FUCK, loosing the flow...
LAB_00043828:
	if (gTrailblazerConeIndex == 100) 
		MissionTargets[NumPlayers-1].data[1] =	MissionTargets[NumPlayers-1].data[1] | 0x102;

LAB_0004386c:
	if (Mission.timer[0].count < 0)
		Mission.timer[0].count = 0;

	if (Mission.timer[1].count < 0)
		Mission.timer[1].count = 0;

	gPlayerScore.time = Mission.timer[0].count;
	gPlayerScore.P2time = Mission.timer[1].count;

	return;

LAB_00043658:
	iVar10 = iVar10 + 1;
	piVar4 = piVar4 + 1;

	if (5 < iVar10) 
		goto LAB_00043668;

	goto LAB_0004333c;

LAB_00043668:
	player_id = iVar12;

	if (NumPlayers <= iVar12)
		goto LAB_00043828;

	goto LAB_0004330c;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawDrivingGames()
 // line 477, offset 0x000438dc
	/* begin block 1 */
		// Start line: 479
		// Start offset: 0x000438DC
		// Variables:
	// 		struct VECTOR wpos; // stack offset -24
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x000439FC
	// End Line: 526

	/* begin block 2 */
		// Start line: 1110
	/* end block 2 */
	// End Line: 1111

	/* begin block 3 */
		// Start line: 1113
	/* end block 3 */
	// End Line: 1114

	/* begin block 4 */
		// Start line: 1114
	/* end block 4 */
	// End Line: 1115

	/* begin block 5 */
		// Start line: 1117
	/* end block 5 */
	// End Line: 1118

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DrawDrivingGames(void)
{
	bool bVar1;
	int cone;
	int i;
	VECTOR wpos;

	if (GameType != GAME_GATERACE && GameType != GAME_TRAILBLAZER || gTrailblazerConeModel == NULL || gTrailblazerData == NULL) 
		return;

	i = 0;
	SetFrustrumMatrix();
	bVar1 = true;

	if (gTrailblazerPrevConeDelay == 0) 
		goto LAB_000439dc;

	i = -1;
	do {

		while (true) 
		{
			bVar1 = i < 6;
		LAB_000439dc:
			if (!bVar1) 
			{
				DrawSmashedCones();
				return;
			}

			cone = gTrailblazerConeIndex + i;
			if (cone < 100) 
				break;
		LAB_000439d4:
			i++;
		}

		if (GameType != GAME_GATERACE) 
		{
			GetConePos(cone, &wpos, -1);
			DrawCone(&wpos, gTrailblazerConeIndex + i);
			goto LAB_000439d4;
		}

		GetConePos(cone, &wpos, 0);
		DrawCone(&wpos, gTrailblazerConeIndex + i);
		GetConePos(gTrailblazerConeIndex + i, &wpos, 1);
		DrawCone(&wpos, gTrailblazerConeIndex + i);

		i++;
	} while (true);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarConeCollision(struct VECTOR *pPos /*$a0*/, int car /*$a1*/)
 // line 545, offset 0x000439fc
	/* begin block 1 */
		// Start line: 546
		// Start offset: 0x000439FC
		// Variables:
	// 		struct CDATA2D cd[2]; // stack offset -216
	// 		struct _CAR_DATA *cp1; // $t0
	// 		int carLength[2]; // stack offset -16

		/* begin block 1.1 */
			// Start line: 565
			// Start offset: 0x00043AD4
		/* end block 1.1 */
		// End offset: 0x00043AD4
		// End Line: 565
	/* end block 1 */
	// End offset: 0x00043AE8
	// End Line: 566

	/* begin block 2 */
		// Start line: 1244
	/* end block 2 */
	// End Line: 1245

	/* begin block 3 */
		// Start line: 1264
	/* end block 3 */
	// End Line: 1265

	/* begin block 4 */
		// Start line: 1276
	/* end block 4 */
	// End Line: 1277

// [D]
int CarConeCollision(VECTOR *pPos, int car)
{
	int model;
	CDATA2D cd[2];

	cd[0].x.vx = pPos->vx;
	cd[0].x.vz = pPos->vz;
	cd[0].length[0] = 0x28;
	cd[0].length[1] = 0x28;
	cd[0].theta = 0;

	if (car_data[car].controlType == 0) 
		return 0;

	model = car_data[car].ap.model;

	cd[1].x.vx = car_data[car].hd.where.t[0];
	cd[1].length[0] = car_cosmetics[model].colBox.vz;
	cd[1].length[1] = car_cosmetics[model].colBox.vx;

	cd[1].theta = car_data[car].hd.direction;
	cd[1].x.vz = car_data[car].hd.where.t[2];

	return bcollided2d(cd, 1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetSmashedCone(int cone /*$s1*/, struct VECTOR *velocity /*$a1*/, int player /*$s2*/, int side /*$a3*/)
 // line 578, offset 0x00043ae8
	/* begin block 1 */
		// Start line: 579
		// Start offset: 0x00043AE8
		// Variables:
	// 		struct SMASHED_CONE *sc; // $s0
	// 		int chan; // $s0
	/* end block 1 */
	// End offset: 0x00043CE0
	// End Line: 621

	/* begin block 2 */
		// Start line: 1339
	/* end block 2 */
	// End Line: 1340

	/* begin block 3 */
		// Start line: 1352
	/* end block 3 */
	// End Line: 1353

	/* begin block 4 */
		// Start line: 1356
	/* end block 4 */
	// End Line: 1357

// [D]
void SetSmashedCone(int cone, VECTOR *velocity, int player, int side)
{
	int iVar1;
	long lVar2;
	uint uVar3;
	int chan;
	TRAILBLAZER_DATA *pTVar4;
	SMASHED_CONE *sc;

	sc = smashed_cones + current_smashed_cone;
	current_smashed_cone++;

	if (5 < current_smashed_cone)
		current_smashed_cone = 0;

	//*(uint *)sc = *(uint *)sc & 0xffff00ff | 0x100 | (side & 1U) << 0xf;

	sc->rot_speed = 0x100;
	sc->side = side;
	sc->cone = cone;

	sc->velocity.vx = velocity->vx >> 10;
	sc->velocity.vz = velocity->vz >> 10;

	if (sc->velocity.vx < 0)
		sc->velocity.vy = velocity->vx;
	else
		sc->velocity.vy = -velocity->vx;

	if (sc->velocity.vz < 0)
		sc->velocity.vy += velocity->vz;
	else
		sc->velocity.vy -= velocity->vz;

	sc->velocity.vy = sc->velocity.vy >> 1;

	if ((rand() & 1) == 0)
		sc->rot_speed = -sc->velocity.vy;
	else
		sc->rot_speed = sc->velocity.vy;

	if (sc->velocity.vy < -100)
		sc->velocity.vy = -100;

	chan = GetFreeChannel();

	if (chan != -1) 
	{
		if (NumPlayers > 1 && NoPlayerControl == 0) 
			SetPlayerOwnsChannel(chan, player);

		pTVar4 = gTrailblazerData + cone;
		Start3DSoundVolPitch(chan, 1, 5, pTVar4->x, pTVar4->y, pTVar4->z, -2000, 800);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ MoveSmashedCones()
 // line 628, offset 0x00043ce0
	/* begin block 1 */
		// Start line: 630
		// Start offset: 0x00043CE0
		// Variables:
	// 		int i; // $t0
	/* end block 1 */
	// End offset: 0x00043DE4
	// End Line: 655

	/* begin block 2 */
		// Start line: 1453
	/* end block 2 */
	// End Line: 1454

	/* begin block 3 */
		// Start line: 1461
	/* end block 3 */
	// End Line: 1462

	/* begin block 4 */
		// Start line: 1462
	/* end block 4 */
	// End Line: 1463

	/* begin block 5 */
		// Start line: 1464
	/* end block 5 */
	// End Line: 1465

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void MoveSmashedCones(void)
{
	TRAILBLAZER_DATA *pTVar2;
	SMASHED_CONE *pSVar3;
	int i;

	if (gTrailblazerData == NULL)
		return;

	pSVar3 = smashed_cones;
	i = 5;
	do {
		if (pSVar3->cone != -1) 
		{
			pTVar2 = gTrailblazerData + pSVar3->cone;

			if (pTVar2->y < 50 - player[0].pos[1])
			{
				pTVar2->x += pSVar3->velocity.vx;
				pTVar2->y += pSVar3->velocity.vy;
				pTVar2->z += pSVar3->velocity.vz;

				pSVar3->velocity.vy += 10;
				pSVar3->active++;

			}
			else
			{
				pSVar3->cone = -1;
				pSVar3->active = 0;
			}
		}
		pSVar3++;
		i--;
	} while (-1 < i);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSmashedCones()
 // line 662, offset 0x00044168
	/* begin block 1 */
		// Start line: 664
		// Start offset: 0x00044168
		// Variables:
	// 		struct SMASHED_CONE *sc; // $s0
	// 		struct VECTOR wpos; // stack offset -40
	// 		int i; // $s1
	/* end block 1 */
	// End offset: 0x00044228
	// End Line: 696

	/* begin block 2 */
		// Start line: 1324
	/* end block 2 */
	// End Line: 1325

	/* begin block 3 */
		// Start line: 1732
	/* end block 3 */
	// End Line: 1733

	/* begin block 4 */
		// Start line: 1736
	/* end block 4 */
	// End Line: 1737

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DrawSmashedCones(void)
{
	bool bVar1;
	char cVar2;
	SMASHED_CONE *sc;
	int i;

	VECTOR wpos;

	if (gTrailblazerData == NULL)
		return;

	i = 0;
	while (i < 6)
	{
		sc = &smashed_cones[i];

		if (sc->active)
		{
			if (GameType == GAME_GATERACE)
			{
				GetConePos(sc->cone, &wpos, sc->side);
				DrawSmashedCone(sc, &wpos);
			}
			else 
			{
				GetConePos(sc->cone, &wpos, -1);
				DrawSmashedCone(sc, &wpos);
			}
		}

		i++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCone(struct VECTOR *position /*$s0*/, int cone /*$s1*/)
 // line 703, offset 0x00044034
	/* begin block 1 */
		// Start line: 704
		// Start offset: 0x00044034
		// Variables:
	// 		struct MATRIX matrix; // stack offset -64
	// 		struct VECTOR pos; // stack offset -32

		/* begin block 1.1 */
			// Start line: 713
			// Start offset: 0x00044064

			/* begin block 1.1.1 */
				// Start line: 715
				// Start offset: 0x00044084
			/* end block 1.1.1 */
			// End offset: 0x00044154
			// End Line: 721
		/* end block 1.1 */
		// End offset: 0x00044154
		// End Line: 722
	/* end block 1 */
	// End offset: 0x00044154
	// End Line: 723

	/* begin block 2 */
		// Start line: 1746
	/* end block 2 */
	// End Line: 1747

	/* begin block 3 */
		// Start line: 1406
	/* end block 3 */
	// End Line: 1407

	/* begin block 4 */
		// Start line: 1750
	/* end block 4 */
	// End Line: 1751

// [D]
void DrawCone(VECTOR *position, int cone)
{
	MATRIX matrix;
	VECTOR pos;

	if (gTrailblazerData == NULL)
		return;

	if (PositionVisible(position) != 0 && 
		FrustrumCheck(position, gTrailblazerConeModel->bounding_sphere) != -1)
	{
		matrix.m[0][0] = 0x1000;
		matrix.m[1][1] = 0x1000;
		matrix.m[2][2] = 0x1000;
		matrix.m[1][0] = 0;
		matrix.m[2][0] = 0;
		matrix.m[0][1] = 0;
		matrix.m[2][1] = 0;
		matrix.m[0][2] = 0;
		matrix.m[1][2] = 0;

		_RotMatrixY(&matrix, gTrailblazerData[cone].rot);

		pos.vx = position->vx - camera_position.vx;
		pos.vy = position->vy - camera_position.vy;
		pos.vz = position->vz - camera_position.vz;

		gte_SetRotMatrix(&inv_camera_matrix);

		_MatrixRotate(&pos);
		RenderModel(gTrailblazerConeModel, &matrix, &pos, 0, 0, 0);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSmashedCone(struct SMASHED_CONE *sc /*$s0*/, struct VECTOR *wpos /*$s1*/)
 // line 730, offset 0x00043dec
	/* begin block 1 */
		// Start line: 731
		// Start offset: 0x00043DEC
		// Variables:
	// 		struct MATRIX object_matrix; // stack offset -64
	// 		struct MATRIX *finalmatrix; // $s2
	// 		struct VECTOR pos; // stack offset -32
	/* end block 1 */
	// End offset: 0x00043F34
	// End Line: 750

	/* begin block 2 */
		// Start line: 1682
	/* end block 2 */
	// End Line: 1683

// [D]
void DrawSmashedCone(SMASHED_CONE *sc, VECTOR *wpos)
{
	MATRIX object_matrix;
	VECTOR pos;

	object_matrix.m[1][0] = 0;
	object_matrix.m[2][0] = 0;
	object_matrix.m[0][1] = 0;
	object_matrix.m[2][1] = 0;
	object_matrix.m[0][2] = 0;
	object_matrix.m[1][2] = 0;
	object_matrix.m[0][0] = 0x1000;
	object_matrix.m[1][1] = 0x1000;
	object_matrix.m[2][2] = 0x1000;

	RotMatrixY(sc->rot_speed * sc->active * 3 & 0xfff, &object_matrix);
	RotMatrixZ(sc->rot_speed * sc->active & 0xfff, &object_matrix);

	pos.vx = wpos->vx - camera_position.vx;
	pos.vy = wpos->vy - camera_position.vy;
	pos.vz = wpos->vz - camera_position.vz;

	// [A]
#ifndef PSX
	MulMatrix0(&aspect, &object_matrix, &object_matrix);
#endif

	Apply_Inv_CameraMatrix(&pos);
	SetRotMatrix(&object_matrix);

	gte_SetTransVector(&pos);

	SetFrustrumMatrix();

	if (FrustrumCheck(wpos, gTrailblazerConeModel->bounding_sphere) != -1)
	{
		PlotMDL_less_than_128(gTrailblazerConeModel);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetConePos(int cone /*$a0*/, struct VECTOR *pos /*$t2*/, int side /*$a2*/)
 // line 757, offset 0x00043f34
	/* begin block 1 */
		// Start line: 758
		// Start offset: 0x00043F34
		// Variables:
	// 		struct VECTOR offset; // stack offset -16
	// 		int x; // $t3
	// 		int z; // $t4
	// 		int r; // $v1
	// 		int radius; // $a1
	/* end block 1 */
	// End offset: 0x00044034
	// End Line: 792

	/* begin block 2 */
		// Start line: 1736
	/* end block 2 */
	// End Line: 1737

	/* begin block 3 */
		// Start line: 1744
	/* end block 3 */
	// End Line: 1745

// [D]
void GetConePos(int cone, VECTOR *pos, int side)
{
	short sVar1;
	TRAILBLAZER_DATA *pTVar2;
	uint uVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	if (side == -1)
	{
		pTVar2 = gTrailblazerData + cone;

		pos->vx = pTVar2->x;
		pos->vy = pTVar2->y;
		pos->vz = pTVar2->z;
	}
	else 
	{
		pTVar2 = gTrailblazerData + cone;

		uVar3 = pTVar2->rot & 0xfff;
		iVar4 = cone * -4 + 600;

		iVar6 = iVar4 * rcossin_tbl[uVar3 * 2 + 1];

		iVar4 = -iVar4 * rcossin_tbl[uVar3 * 2];
		iVar4 = iVar4 >> 0xc;

		if (side == 0) 
		{
			pos->vx = pTVar2->x - FIXEDH(iVar6);
			pos->vy = pTVar2->y;
			iVar4 = -iVar4;
		}
		else 
		{
			pos->vx = pTVar2->x + FIXEDH(iVar6);
			pos->vy = pTVar2->y;
		}

		pos->vz = pTVar2->z + iVar4;
	}
}





