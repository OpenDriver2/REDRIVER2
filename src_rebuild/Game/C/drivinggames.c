#include "driver2.h"
#include "drivinggames.h"
#include "scores.h"
#include "mission.h"
#include "cutscene.h"
#include "main.h"
#include "system.h"
#include "draw.h"
#include "cars.h"
#include "players.h"
#include "cosmetic.h"
#include "bcollide.h"
#include "camera.h"
#include "convert.h"
#include "gamesnd.h"
#include "map.h"
#include "sound.h"
#include "glaunch.h"

#include "ASM/rndrasm.h"

#include "INLINE_C.H"
#include "RAND.H"

MODEL* gTrailblazerConeModel; 
SMASHED_CONE smashed_cones[MAX_SMASHED_CONES];

TRAILBLAZER_DATA *gTrailblazerData;
int gTrailblazerConeCount;
int gTrailblazerConeIndex;
static int gTrailblazerPrevConeDelay = 0;

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

// [D] [T]
void DrawSmashedCones(void)
{
	SMASHED_CONE* sc;
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

// [D] [T]
void HandleDrivingGames(void)
{
	char playerCarId;
	TRAILBLAZER_DATA* tbd;
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
							for (j = 0; j < 2; j++)
							{
								for (k = 0; k < MAX_SMASHED_CONES; k++)
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
							SetPlayerMessage(id, G_LTXT(GTXT_Minus1second), 2, 1);
						}
					}
				}
			}

			if (gTrailblazerConeIndex == 100)
				MissionTargets[NumPlayers - 1].target_flags |= 0x102;
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
				MissionTargets[NumPlayers - 1].target_flags |= 0x102;
		}
	}

	if (Mission.timer[0].count < 0)
		Mission.timer[0].count = 0;

	if (Mission.timer[1].count < 0)
		Mission.timer[1].count = 0;

	gPlayerScore.time = Mission.timer[0].count;
	gPlayerScore.P2time = Mission.timer[1].count;
}

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



