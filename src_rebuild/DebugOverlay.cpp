#include "Game/driver2.h"

#include "Game/C/mission.h"
#include "Game/C/convert.h"
#include "Game/C/camera.h"
#include "Game/C/dr2roads.h"
#include "Game/C/system.h"
#include "Game/C/pres.h"
#include "Game/C/spool.h"
#include "Game/C/cars.h"
#include "Game/C/draw.h"
#include "Game/C/players.h"
#include "Game/C/glaunch.h"

#include <stdio.h>

#include "C/felony.h"


int gDisplayDrawStats = 0;

struct LineDef_t
{
	VECTOR posA, posB;
	CVECTOR color;
};

LineDef_t gDebug_Lines[512];
int gDebug_numLines = 0;

void DrawDebugOverlays()
{
	VECTOR _zerov = { 0 };

	while(gDebug_numLines > 0)
	{
		LineDef_t& ld = gDebug_Lines[gDebug_numLines-1];

		gte_SetTransVector(&_zerov);
		gte_SetRotMatrix(&inv_camera_matrix);

		SVECTOR a, b;
		a.vx = ld.posA.vx - camera_position.vx;
		a.vy = ld.posA.vy - camera_position.vy;
		a.vz = ld.posA.vz - camera_position.vz;

		b.vx = ld.posB.vx - camera_position.vx;
		b.vy = ld.posB.vy - camera_position.vy;
		b.vz = ld.posB.vz - camera_position.vz;

		gte_ldv3(&a, &b, &b);

		gte_rtpt();
		gte_avsz4();
		
		int z;
		gte_stopz(&z);

		if (z > 0)
		{
			LINE_F2* line = (LINE_F2*)current->primptr;
			setLineF2(line);
			setSemiTrans(line, 1);

			gte_stsxy0(&line->x0)
			gte_stsxy1(&line->x1);

			line->r0 = ld.color.r;
			line->g0 = ld.color.g;
			line->b0 = ld.color.b;

			addPrim(current->ot + 2, line);

			current->primptr += sizeof(LINE_F2);
		}
		gDebug_numLines--;
	}
	gDebug_numLines = 0;

	DR_TPAGE* tp = (DR_TPAGE*)current->primptr;
	setDrawTPage(tp, 1, 1, 0);
	addPrim(current->ot + 2, tp);
	current->primptr += sizeof(DR_TPAGE);

	char tempBuf[1024];

	int primTabLeft = current->primptr - current->primtab;

	if (gDisplayDrawStats)
	{
		SetTextColour(128, 120, 0);
		
		sprintf(tempBuf, "Primtab: %d of %d", primTabLeft, PRIMTAB_SIZE);
		PrintString(tempBuf, 10, 20);

		extern volatile int spoolactive;
		extern int numActiveCops;
		extern int numCopCars;
		extern int numCivCars;
		extern int numParkedCars;
		extern int maxCopCars;
		extern int maxCivCars;
		extern int current_region;
		extern int LoadedArea;

		Spool* spoolptr = (Spool*)(RegionSpoolInfo + spoolinfo_offsets[current_region]);

		sprintf(tempBuf, "Spooling: %d spec: %d, active: %d, Reg: %d, Ar: %d, Cn: %d %d", doSpooling, allowSpecSpooling, spoolactive, current_region, LoadedArea, spoolptr->connected_areas[0] & 0x3f, spoolptr->connected_areas[1] & 0x3f);
		PrintString(tempBuf, 10, 30);

		sprintf(tempBuf, "Civs: %d - %d parked - max %d", numCivCars, numParkedCars, maxCivCars);
		PrintString(tempBuf, 10, 40);

		sprintf(tempBuf, "Cops: %d - %d active - max %d - seen: %d", numCopCars, numActiveCops, maxCopCars, CopsCanSeePlayer);
		PrintString(tempBuf, 10, 50);

		sprintf(tempBuf, "Mission %d Chase: %d", gCurrentMissionNumber, gRandomChase);
		PrintString(tempBuf, 10, 60);

		int playerCar = player[0].playerCarId;
		if(playerCar >= 0)
		{
			
			int speed = car_data[playerCar].hd.speed;

			sprintf(tempBuf, "Car speed: %d     direction: %d", speed, car_data[playerCar].hd.direction);
			PrintString(tempBuf, 10, 80);

			VECTOR* carPos = (VECTOR*)car_data[playerCar].hd.where.t;
			
			DRIVER2_ROAD_INFO roadInfo;
			roadInfo.surfId = GetSurfaceIndex(carPos);

			
			if (GetSurfaceRoadInfo(&roadInfo, roadInfo.surfId))
			{
				int dx, dz;
				int segLen, distAlongSegment;
				int theta;

				if (roadInfo.straight)
				{
					dx = carPos->vx - roadInfo.straight->Midx;
					dz = carPos->vz - roadInfo.straight->Midz;
					
					segLen = roadInfo.straight->length;
					theta = roadInfo.straight->angle - ratan2(dx, dz);
					distAlongSegment = (segLen / 2) + FIXEDH(RCOS(theta) * SquareRoot0(dx * dx + dz * dz));
				}
				else
				{
					dx = carPos->vx - roadInfo.curve->Midx;
					dz = carPos->vz - roadInfo.curve->Midz;
					
					theta = ratan2(dx,dz);
					segLen = (roadInfo.curve->end - roadInfo.curve->start & 0xfffU); // *roadInfo.curve->inside * 11 / 7; // don't use physical length

					if (roadInfo.curve->inside < 10)
						distAlongSegment = (theta & 0xfffU) - roadInfo.curve->start & 0xf80;
					else if (roadInfo.curve->inside < 20)
						distAlongSegment = (theta & 0xfffU) - roadInfo.curve->start & 0xfc0;
					else
						distAlongSegment = (theta & 0xfffU) - roadInfo.curve->start & 0xfe0;
				}
				
				int lane = GetLaneByPositionOnRoad(&roadInfo, carPos);

				sprintf(tempBuf, "%s %d flg %d%d%d spd %d len %d",
					roadInfo.straight ? "STR" : "CRV",
					roadInfo.surfId,
					(roadInfo.NumLanes & 0x20) > 0,					// flag 0 - first lane?
					(roadInfo.NumLanes & 0x40) > 0,					// flag 1 - leftmost park
					(roadInfo.NumLanes & 0x80) > 0,					// flag 2 - rightmost park
					ROAD_SPEED_LIMIT(&roadInfo),					// speed limit id
					segLen
					);

				PrintString(tempBuf, 10, 180);

				sprintf(tempBuf, "dir %d lane %d/%d AI %d dist: %d",
					ROAD_LANE_DIR(&roadInfo, lane),					// direction bit
					lane + 1,
					ROAD_WIDTH_IN_LANES(&roadInfo),					// lane count. * 2 for both sides as roads are symmetric
					ROAD_IS_AI_LANE(&roadInfo, lane),				// lane AI driveable flag
					distAlongSegment
				);

				PrintString(tempBuf, 10, 195);

				sprintf(tempBuf, "c %d %d %d %d",
					(int)(*roadInfo.ConnectIdx)[0], (int)(*roadInfo.ConnectIdx)[1], (int)(*roadInfo.ConnectIdx)[2], (int)(*roadInfo.ConnectIdx)[3]);

				PrintString(tempBuf, 10, 205);
			}
			else if(IS_JUNCTION_SURFACE(roadInfo.surfId))
			{
				DRIVER2_JUNCTION* junc = GET_JUNCTION(roadInfo.surfId);
				
				sprintf(tempBuf, "JUN %d flg %d - c %d %d %d %d",roadInfo.surfId, junc->flags, 
					(int)(*roadInfo.ConnectIdx)[0], (int)(*roadInfo.ConnectIdx)[1], (int)(*roadInfo.ConnectIdx)[2], (int)(*roadInfo.ConnectIdx)[3]);
				
				PrintString(tempBuf, 10, 180);
			}

			
		}

	}
}

void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color)
{
	if (gDebug_numLines + 1 > 512)
		return;

	int dx = camera_position.vx - pointA.vx;
	int dz = camera_position.vz - pointA.vz;

	if (dx * dx + dz * dz > (15000*15000))
		return;

	LineDef_t& ld = gDebug_Lines[gDebug_numLines++];
	ld.posA = pointA;
	ld.posB = pointB;
	ld.color = color;

	ld.posA.vy *= -1;
	ld.posB.vy *= -1;
}

void Debug_Line2D(SXYPAIR& pointA, SXYPAIR& pointB, CVECTOR& color)
{
	LINE_F2* line = (LINE_F2*)current->primptr;
	setLineF2(line);

	line->x0 = pointA.x;
	line->y0 = pointA.y;
	
	line->x1 = pointB.x;
	line->y1 = pointB.y;

	line->r0 = color.r;
	line->g0 = color.g;
	line->b0 = color.b;

#if defined(USE_PGXP) && defined(USE_EXTENDED_PRIM_POINTERS)
	line->pgxp_index = 0xFFFF;
#endif

	addPrim(current->ot, line);

	current->primptr += sizeof(LINE_F2);
}

void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color)
{
	if (gDebug_numLines + 1 > 512)
		return;

	int dx = camera_position.vx - ofs.vx;
	int dz = camera_position.vz - ofs.vz;

	if (dx * dx + dz * dz > (15000 * 15000))
		return;

	LineDef_t& ld = gDebug_Lines[gDebug_numLines++];
	ld.posA = pointA;
	ld.posB = pointB;
	ld.color = color;

	ld.posA.vx += ofs.vx;
	ld.posA.vy += ofs.vy;
	ld.posA.vz += ofs.vz;

	ld.posB.vx += ofs.vx;
	ld.posB.vy += ofs.vy;
	ld.posB.vz += ofs.vz;

	ld.posA.vy *= -1;
	ld.posB.vy *= -1;
}

int g_FreeCameraControls = 0;
int g_FreeCameraEnabled = 0;
VECTOR g_FreeCameraPosition;
SVECTOR g_FreeCameraRotation;
VECTOR g_FreeCameraVelocity;
extern int cursorX, cursorY, cursorOldX, cursorOldY;

extern VECTOR lis_pos;

void BuildFreeCameraMatrix()
{
	if (g_FreeCameraEnabled == 0)
		return;

	player[0].cameraPos = g_FreeCameraPosition;
	camera_position = g_FreeCameraPosition;
	camera_angle = g_FreeCameraRotation;
	lis_pos = camera_position;

	BuildWorldMatrix();
}

void DoFreeCamera()
{
	if (g_FreeCameraEnabled == 0)
	{
		g_FreeCameraPosition = camera_position;
		g_FreeCameraRotation = camera_angle;
		g_FreeCameraVelocity.vx = 0;
		g_FreeCameraVelocity.vy = 0;
		g_FreeCameraVelocity.vz = 0;
		return;
	}

	BuildFreeCameraMatrix();

	g_FreeCameraPosition.vx += FIXEDH(g_FreeCameraVelocity.vx);
	g_FreeCameraPosition.vy += FIXEDH(g_FreeCameraVelocity.vy);
	g_FreeCameraPosition.vz += FIXEDH(g_FreeCameraVelocity.vz);

	// deaccel
	g_FreeCameraVelocity.vx -= (g_FreeCameraVelocity.vx / 8);
	g_FreeCameraVelocity.vy -= (g_FreeCameraVelocity.vy / 8);
	g_FreeCameraVelocity.vz -= (g_FreeCameraVelocity.vz / 8);

	// accel
	if ((g_FreeCameraControls & 0x1) || (g_FreeCameraControls & 0x2)) // forward/back
	{
		int sign = (g_FreeCameraControls & 0x2) ? -1 : 1;

		g_FreeCameraVelocity.vx += (inv_camera_matrix.m[2][0] * 32) * sign;
		g_FreeCameraVelocity.vy += (inv_camera_matrix.m[2][1] * 32) * sign;
		g_FreeCameraVelocity.vz += (inv_camera_matrix.m[2][2] * 32) * sign;
	}

	// side
	if ((g_FreeCameraControls & 0x4) || (g_FreeCameraControls & 0x8)) // right/left
	{
		int sign = (g_FreeCameraControls & 0x8) ? 1 : -1;

		g_FreeCameraVelocity.vx += (inv_camera_matrix.m[0][0] * 32) * sign;
		g_FreeCameraVelocity.vy += (inv_camera_matrix.m[0][1] * 32) * sign;
		g_FreeCameraVelocity.vz += (inv_camera_matrix.m[0][2] * 32) * sign;
	}


}