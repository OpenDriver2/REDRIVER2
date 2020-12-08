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
#include "GAMESND.H"
#include "MAP.H"
#include "SOUND.H"
#include "GLAUNCH.H"

#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"
#include "RAND.H"

MODEL* gTrailblazerConeModel; 
SMASHED_CONE smashed_cones[MAX_SMASHED_CONES];

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

static int wrongside[2][MAX_SMASHED_CONES];
static int current_smashed_cone = 0;

// [D] [T]
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

	if (GameType == GAME_GATERACE || GameType == GAME_TRAILBLAZER) 
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

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < MAX_SMASHED_CONES; j++)
            wrongside[i][j] = 0;
    }

	for (i = 0; i < MAX_SMASHED_CONES; i++)
	{
		smashed_cones[i].cone = -1;
		smashed_cones[i].active = 0;
		smashed_cones[i].side = 0;
		smashed_cones[i].rot_speed = 0;
    }

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
	// 		CAR_DATA *cp; // $a2
	// 		VECTOR vel; // stack offset -96
	// 		int i; // $s3
	// 		int j; // $v1
	// 		int k; // $a0
	// 		int id; // $s2
	// 		int dist; // $a1

		/* begin block 1.1 */
			// Start line: 351
			// Start offset: 0x00043354
			// Variables:
		// 		VECTOR pos1; // stack offset -80
		// 		VECTOR pos2; // stack offset -64
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
		// 		VECTOR pos; // stack offset -80
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

// [D] [T]
void HandleDrivingGames(void)
{
	char playerCarId;
	TRAILBLAZER_DATA *tbd;
	int id;
	VECTOR vel;
	VECTOR pos1;
	VECTOR pos2;
	int i, j, k;
	int side;
	int cone;

	if (gTrailblazerPrevConeDelay > 0) 
		gTrailblazerPrevConeDelay--;

	if (gTrailblazerData)
	{
		if (GameType == GAME_GATERACE)
		{
			MoveSmashedCones();

			for (id = 0; id < NumPlayers; id++)
			{
				playerCarId = player[id].playerCarId;

				for (i = 0; i < MAX_SMASHED_CONES; i++)
				{
					cone = gTrailblazerConeIndex + i;
					
					if (cone < 100)
					{
						GetConePos(cone, &pos1, 0);
						GetConePos(cone, &pos2, 1);

						side = 0;

						if (CarConeCollision(&pos1, playerCarId))
							side = 1;
						else if (CarConeCollision(&pos2, playerCarId))
							side = 2;

						if (side == 0)
						{
							int sn, cs;
							int dx, dz;
							int r, radius;

							tbd = &gTrailblazerData[cone];

							r = tbd->rot & 0xfff;
							radius = (600 - (gTrailblazerConeIndex * 400 + i) / 100) * 4096;

							sn = rcossin_tbl[r * 2];
							cs = rcossin_tbl[r * 2 + 1];

							dx = player[id].pos[0] - tbd->x;
							dz = player[id].pos[2] - tbd->z;

							if (dx * sn + dz * cs < 1)
							{
								wrongside[id][i] = 1;
								continue;
							}

							if (wrongside[id][i] == 0)
								continue;

							wrongside[id][i] = 0;

							if (ABS(dx * cs - dz * sn) < radius)
							{
								gTrailblazerConeCount++;

								Mission.timer[id].count += 3000;

								if (id == 0)
									gPlayerScore.items++;
								else
									gPlayerScore.P2items++;

								gTrailblazerConeIndex += i + 1;
								gTrailblazerPrevConeDelay = 10;
							}

							// reset side
							for(j = 0; j < 2; j++)
							{
								for(k = 0; k < MAX_SMASHED_CONES; k++)
									wrongside[j][k] = 0;
							}
						}
						else
						{
							vel.vx = FIXED(car_data[playerCarId].st.n.linearVelocity[0]);
							vel.vy = -17;
							vel.vz = FIXED(car_data[playerCarId].st.n.linearVelocity[2]);

							SetSmashedCone(cone, &vel, id, side - 1);
							gTrailblazerConeIndex += i + 1;

							Mission.timer[id].count -= 3000;
							SetPlayerMessage(id, "-1 second", 2, 1);
						}
					}
				}
			}

			if (gTrailblazerConeIndex == 100)
				MissionTargets[NumPlayers - 1].data[1] |= 0x102;
		}
		else if (GameType == GAME_TRAILBLAZER)
		{
			MoveSmashedCones();

			for (id = 0; id < NumPlayers; id++)
			{
				playerCarId = player[id].playerCarId;
				
				for (i = 0; i < MAX_SMASHED_CONES; i++)
				{
					cone = gTrailblazerConeIndex + i;
					
					if (cone < 100)
					{
						GetConePos(cone, &pos1, -1);

						if (CarConeCollision(&pos1, playerCarId))
						{
							Mission.timer[id].count += 3000;

							vel.vx = FIXED(car_data[playerCarId].st.n.linearVelocity[0]);
							vel.vy = -17;
							vel.vz = FIXED(car_data[playerCarId].st.n.linearVelocity[2]);
								
							SetSmashedCone(cone, &vel, id, 0);
							
							gTrailblazerConeCount++;
							gTrailblazerConeIndex += i + 1;

							if (id == 0)
								gPlayerScore.items++;
							else
								gPlayerScore.P2items++;
						}
					}
				}
			}

			if (gTrailblazerConeIndex == 100)
				MissionTargets[NumPlayers - 1].data[1] |= 0x102;
		}
	}

	if (Mission.timer[0].count < 0)
		Mission.timer[0].count = 0;

	if (Mission.timer[1].count < 0)
		Mission.timer[1].count = 0;

	gPlayerScore.time = Mission.timer[0].count;
	gPlayerScore.P2time = Mission.timer[1].count;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawDrivingGames()
 // line 477, offset 0x000438dc
	/* begin block 1 */
		// Start line: 479
		// Start offset: 0x000438DC
		// Variables:
	// 		VECTOR wpos; // stack offset -24
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

// [D] [T]
void DrawDrivingGames(void)
{
	int cone;
	int i;
	VECTOR wpos;

	if (GameType != GAME_GATERACE && GameType != GAME_TRAILBLAZER || 
		gTrailblazerConeModel == NULL || gTrailblazerData == NULL) 
		return;

	SetFrustrumMatrix();

	if (gTrailblazerConeIndex < 100)
	{
		for (i = 0; i < MAX_SMASHED_CONES; i++)
		{
			cone = gTrailblazerConeIndex + i;

			if (gTrailblazerPrevConeDelay)
				cone -= 1;

			if (GameType == GAME_GATERACE) 
			{
				GetConePos(cone, &wpos, 0);
				DrawCone(&wpos, cone);

				GetConePos(cone, &wpos, 1);
				DrawCone(&wpos, cone);
			}
			else
			{
				GetConePos(cone, &wpos, -1);
				DrawCone(&wpos, cone);
			}
		}
	}

	DrawSmashedCones();
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarConeCollision(VECTOR *pPos /*$a0*/, int car /*$a1*/)
 // line 545, offset 0x000439fc
	/* begin block 1 */
		// Start line: 546
		// Start offset: 0x000439FC
		// Variables:
	// 		CDATA2D cd[2]; // stack offset -216
	// 		CAR_DATA *cp1; // $t0
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

// [D] [T]
int CarConeCollision(VECTOR *pPos, int car)
{
	int model;
	CDATA2D cd[2];
	CAR_DATA* cp1;
	
	cd[0].x.vx = pPos->vx;
	cd[0].x.vz = pPos->vz;
	cd[0].length[0] = 40;
	cd[0].length[1] = 40;
	cd[0].theta = pPos->pad;

	cp1 = &car_data[car];

	if (cp1->controlType == CONTROL_TYPE_NONE) 
		return 0;

	model = cp1->ap.model;

	cd[1].x.vx = cp1->hd.where.t[0];
	cd[1].length[0] = car_cosmetics[model].colBox.vz;
	cd[1].length[1] = car_cosmetics[model].colBox.vx;

	cd[1].theta = cp1->hd.direction;
	cd[1].x.vz = cp1->hd.where.t[2];

	return bcollided2d(cd);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetSmashedCone(int cone /*$s1*/, VECTOR *velocity /*$a1*/, int player /*$s2*/, int side /*$a3*/)
 // line 578, offset 0x00043ae8
	/* begin block 1 */
		// Start line: 579
		// Start offset: 0x00043AE8
		// Variables:
	// 		SMASHED_CONE *sc; // $s0
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

// [D] [T]
void SetSmashedCone(int cone, VECTOR *velocity, int player, int side)
{
	int chan;
	TRAILBLAZER_DATA *tbd;
	SMASHED_CONE *sc;

	sc = smashed_cones + current_smashed_cone;
	current_smashed_cone++;

	if (current_smashed_cone > MAX_SMASHED_CONES-1)
		current_smashed_cone = 0;
	
	sc->rot_speed = 256;
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
	
	sc->velocity.vy /= 2;

	if ((rand() & 1) == 0)
		sc->rot_speed = -sc->velocity.vy;
	else
		sc->rot_speed = sc->velocity.vy;

	if (sc->velocity.vy < -67)
		sc->velocity.vy = -67;

	chan = GetFreeChannel();

	if (chan != -1) 
	{
		if (NumPlayers > 1 && NoPlayerControl == 0) 
			SetPlayerOwnsChannel(chan, player);

		tbd = &gTrailblazerData[cone];
		Start3DSoundVolPitch(chan, 1, SOUND_BANK_MISSION, tbd->x, tbd->y, tbd->z, -2000, 800);
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
	TRAILBLAZER_DATA *tbd;
	SMASHED_CONE *sc;
	int i;

	if (gTrailblazerData == NULL)
		return;

	sc = smashed_cones;

	for (i = 0;  i < MAX_SMASHED_CONES; i++)
	{
		if (sc->cone != -1) 
		{
			tbd = &gTrailblazerData[sc->cone];

			if (tbd->y < 50 - player[0].pos[1])
			{
				tbd->x += sc->velocity.vx;
				tbd->y += sc->velocity.vy;
				tbd->z += sc->velocity.vz;

				sc->velocity.vy += 10;
				sc->active++;

			}
			else
			{
				sc->cone = -1;
				sc->active = 0;
			}
		}
		
		sc++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSmashedCones()
 // line 662, offset 0x00044168
	/* begin block 1 */
		// Start line: 664
		// Start offset: 0x00044168
		// Variables:
	// 		SMASHED_CONE *sc; // $s0
	// 		VECTOR wpos; // stack offset -40
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

// [D] [T]
void DrawSmashedCones(void)
{
	SMASHED_CONE *sc;
	int i;

	VECTOR wpos;

	if (gTrailblazerData == NULL)
		return;

	for (i = 0; i < MAX_SMASHED_CONES; i++)
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
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCone(VECTOR *position /*$s0*/, int cone /*$s1*/)
 // line 703, offset 0x00044034
	/* begin block 1 */
		// Start line: 704
		// Start offset: 0x00044034
		// Variables:
	// 		MATRIX matrix; // stack offset -64
	// 		VECTOR pos; // stack offset -32

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

// [D] [T]
void DrawCone(VECTOR *position, int cone)
{
	MATRIX matrix;
	VECTOR pos;

	if (gTrailblazerData == NULL)
		return;

	if (PositionVisible(position) == 0 || FrustrumCheck(position, gTrailblazerConeModel->bounding_sphere) == -1)
		return;

	matrix.m[0][0] = ONE;
	matrix.m[1][1] = ONE;
	matrix.m[2][2] = ONE;
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
	RenderModel(gTrailblazerConeModel, &matrix, &pos, 0, 0, 0, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSmashedCone(SMASHED_CONE *sc /*$s0*/, VECTOR *wpos /*$s1*/)
 // line 730, offset 0x00043dec
	/* begin block 1 */
		// Start line: 731
		// Start offset: 0x00043DEC
		// Variables:
	// 		MATRIX object_matrix; // stack offset -64
	// 		MATRIX *finalmatrix; // $s2
	// 		VECTOR pos; // stack offset -32
	/* end block 1 */
	// End offset: 0x00043F34
	// End Line: 750

	/* begin block 2 */
		// Start line: 1682
	/* end block 2 */
	// End Line: 1683

// [D] [T]
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
	object_matrix.m[0][0] = ONE;
	object_matrix.m[1][1] = ONE;
	object_matrix.m[2][2] = ONE;

	RotMatrixY(sc->rot_speed * sc->active * 3 & 0xfff, &object_matrix);
	RotMatrixZ(sc->rot_speed * sc->active & 0xfff, &object_matrix);

	pos.vx = wpos->vx - camera_position.vx;
	pos.vy = wpos->vy - camera_position.vy;
	pos.vz = wpos->vz - camera_position.vz;

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
// void /*$ra*/ GetConePos(int cone /*$a0*/, VECTOR *pos /*$t2*/, int side /*$a2*/)
 // line 757, offset 0x00043f34
	/* begin block 1 */
		// Start line: 758
		// Start offset: 0x00043F34
		// Variables:
	// 		VECTOR offset; // stack offset -16
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

// [D] [T]
void GetConePos(int cone, VECTOR *pos, int side)
{
	TRAILBLAZER_DATA *tbd;
	int x, z, r;
	int radius;

	tbd = &gTrailblazerData[cone];

	if (side == -1)
	{
		pos->vx = tbd->x;
		pos->vy = tbd->y;
		pos->vz = tbd->z;
		pos->pad = tbd->rot;	// [A] store cone rotation
	}
	else 
	{
		r = tbd->rot & 0xfff;
		radius = cone * -4 + 600;

		x = radius * rcossin_tbl[r * 2 + 1];
		z = -radius * rcossin_tbl[r * 2];

		if (side == 0) 
		{
			pos->vx = tbd->x - FIXED(x);
			pos->vy = tbd->y;
			pos->vz = tbd->z - FIXED(z);
		}
		else 
		{
			pos->vx = tbd->x + FIXED(x);
			pos->vy = tbd->y;
			pos->vz = tbd->z + FIXED(z);
		}

		pos->pad = tbd->rot;	// [A] store cone rotation
	}
}





