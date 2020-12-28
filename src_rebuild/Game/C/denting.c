#include "driver2.h"
#include "denting.h"
#include "system.h"
#include "mission.h"
#include "models.h"
#include "cars.h"
#include "convert.h"
#include "pause.h"
#include "camera.h"
#include "draw.h"
#include "dr2roads.h"
#include "debris.h"
#include "players.h"
#include "main.h"

#include "STRINGS.H"

char* DentingFiles[] =
{
	"LEVELS\\CHICAGO.DEN",
	"LEVELS\\HAVANA.DEN",
	"LEVELS\\VEGAS.DEN",
	"LEVELS\\RIO.DEN",
};

// DO NOT CHANGE THIS!
#define NUM_DAMAGE_ZONES			6
#define MAX_FILE_DAMAGE_ZONE_VERTS	50
#define MAX_FILE_DAMAGE_ZONE_POLYS	70
#define MAX_FILE_DAMAGE_LEVELS		256

unsigned char gCarDamageZoneVerts[MAX_CAR_MODELS][NUM_DAMAGE_ZONES][MAX_DAMAGE_ZONE_VERTS];
unsigned char gHDCarDamageZonePolys[MAX_CAR_MODELS][NUM_DAMAGE_ZONES][MAX_DAMAGE_ZONE_POLYS];
unsigned char gHDCarDamageLevels[MAX_CAR_MODELS][MAX_DAMAGE_LEVELS];

// [D] [T]
void InitialiseDenting(void)
{
	LoadDenting(GameLevel);
	InitHubcap();
}

// [D] [T]
void DentCar(CAR_DATA *cp)
{
	int Zone;
	int Damage;
	int MaxDamage;
	DENTUVS *dentptr;
	SVECTOR *CleanVertPtr;
	int VertNo;
	unsigned char *DamPtr;
	SVECTOR *DamVertPtr;
	MODEL *pCleanModel;
	int model;
	int Poly;

	short tempDamage[256];
	memset((u_char*)tempDamage, 0, sizeof(tempDamage));

	MaxDamage = 0;
	model = cp->ap.model;
	cp->lowDetail = -1;
	cp->ap.qy = 0;
	cp->ap.qw = 0;

	pCleanModel = gCarCleanModelPtr[model];

	// collect vertices from zones
	if (pCleanModel != NULL) 
	{
		VertNo = 0;
		while (VertNo < pCleanModel->num_vertices)
			tempDamage[VertNo++] = 0;

		Zone = 0;
		do {
			Damage = cp->ap.damage[Zone];

			if (Damage > MaxDamage)
				MaxDamage = Damage;

			DamPtr = gCarDamageZoneVerts[cp->ap.model][Zone];

			VertNo = 0;
			while (VertNo < MAX_DAMAGE_ZONE_VERTS && *DamPtr != 0xFF)
			{
				if (tempDamage[*DamPtr] == 0)
					tempDamage[*DamPtr] += Damage;
				else 
					tempDamage[*DamPtr] += Damage / 2;

				DamPtr++;

				VertNo++;
			}

			Zone++;
		} while (Zone < NUM_DAMAGE_ZONES);
	}

	// update vertices positon
	if (gCarCleanModelPtr[model] != NULL && gCarDamModelPtr[model] != NULL) 
	{
		DamVertPtr = (SVECTOR *)gCarDamModelPtr[model]->vertices;
		CleanVertPtr = (SVECTOR *)gCarCleanModelPtr[model]->vertices;

		VertNo = 0;
		while (VertNo < pCleanModel->num_vertices)
		{
			gTempCarVertDump[cp->id][VertNo].vx = CleanVertPtr->vx + FIXEDH((DamVertPtr->vx - CleanVertPtr->vx) * tempDamage[VertNo] / 2);
			gTempCarVertDump[cp->id][VertNo].vy = CleanVertPtr->vy + FIXEDH((DamVertPtr->vy - CleanVertPtr->vy) * tempDamage[VertNo] / 2);
			gTempCarVertDump[cp->id][VertNo].vz = CleanVertPtr->vz + FIXEDH((DamVertPtr->vz - CleanVertPtr->vz) * tempDamage[VertNo] / 2);

			DamVertPtr++;
			CleanVertPtr++;

			VertNo++;
		}
	}

	// update polygon UVs
	if (pCleanModel != NULL) 
	{
		dentptr = gTempHDCarUVDump[cp->id];

		// reset UV coordinates
		Poly = 0;
		while (Poly < pCleanModel->num_polys)
		{
			dentptr->u3 = 0;
			Poly++;
			dentptr++;
		}

		Zone = 0;
		do {
			Damage = cp->ap.damage[Zone];

			Poly = 0;
			while (Poly < MAX_DAMAGE_ZONE_POLYS && gHDCarDamageZonePolys[cp->ap.model][Zone][Poly] != 0xFF)
			{
				dentptr = gTempHDCarUVDump[cp->id] + gHDCarDamageZonePolys[cp->ap.model][Zone][Poly];

				// add a damage level
				dentptr->u3 += (Damage >> 0xA);

				// clamp level
				if (dentptr->u3 > 2)
					dentptr->u3 = 2;

				Poly++;
			}

			Zone++;
		} while (Zone < NUM_DAMAGE_ZONES);

		Poly = 0;

		DamPtr = gHDCarDamageLevels[model];
		dentptr = gTempHDCarUVDump[cp->id];

		while (Poly < pCleanModel->num_polys)
		{
			// calculate the UV offset with strange XORs
			if(dentptr->u3 > 0)
				dentptr->u3 = (*DamPtr ^ 1 ^ (*DamPtr ^ 1 | dentptr->u3)) * 64;

			dentptr++;
			
			DamPtr++;
			Poly++;
		}
	}
}

// [D] [T]
void CreateDentableCar(CAR_DATA *cp)
{
	MODEL *srcModel;
	SVECTOR *dst;
	int count;
	SVECTOR *src;
	int vcount;
	int model;

	model = cp->ap.model;

	srcModel = gCarCleanModelPtr[model];
	if (srcModel != NULL)
	{
		src = (SVECTOR *)srcModel->vertices;
		dst = gTempCarVertDump[cp->id];

		vcount = srcModel->num_vertices;

		while (vcount-- != -1) 
			*dst++ = *src++;

		count = 0;
		while (count < srcModel->num_polys)
		{
			gTempHDCarUVDump[cp->id][count].u3 = 0;
			count++;
		}
	}
	else
	{
		printError("gCarCleanModelPtr is NULL in CreateDentableCar\n");
	}

	srcModel = gCarLowModelPtr[model];
	if (srcModel != NULL)
	{
		count = 0;
		while (count < srcModel->num_polys)
		{
			gTempLDCarUVDump[cp->id][count].u3 = 0;
			count++;
		}
	}
	else
	{
		printError("gCarLowModelPtr is NULL in CreateDentableCar\n");
	}

	if (gDontResetCarDamage == 0) 
	{
		count = 0;
		while (count < NUM_DAMAGE_ZONES)
		{
			cp->ap.damage[count] = 0;
			count++;
		}

		cp->totalDamage = 0;
	}
}

extern HUBCAP gHubcap;
int gHubcapTime = 0;

// [D] [T]
void InitHubcap(void)
{
	gHubcapTime = Random2(1) & 0x7ff;

	gHubcap.Present[0] = 1;
	gHubcap.Present[1] = 1;
	gHubcap.Present[2] = 1;
	gHubcap.Present[3] = 1;

	// right
	gHubcap.Offset[0].vx = 205;
	gHubcap.Offset[0].vy = -7;
	gHubcap.Offset[0].vz = 290;

	gHubcap.Offset[1].vx = 205;
	gHubcap.Offset[1].vy = -7;
	gHubcap.Offset[1].vz = -275;

	// left
	gHubcap.Offset[2].vx = -205;
	gHubcap.Offset[2].vy = -7;
	gHubcap.Offset[2].vz = 290;

	gHubcap.Offset[3].vx = -205;
	gHubcap.Offset[3].vy = -7;
	gHubcap.Offset[3].vz = -275;
}


// [D] [T]
void LoseHubcap(int car, int Hubcap, int Velocity)
{
	SVECTOR InitialLocalAngle = { 0, 0, 10 };
	CAR_DATA* cp;

	cp = &car_data[car];

	// check speed and if hubcap lost
	if (cp->hd.wheel_speed < 0 || (cp->ap.flags & 1 << Hubcap))
		return;

	cp->ap.flags |= (1 << Hubcap);		// [A] cars now hold hubcaps

	gHubcap.Position.vx = gHubcap.Offset[Hubcap].vx;
	gHubcap.Position.vy = gHubcap.Offset[Hubcap].vy;
	gHubcap.Position.vz = gHubcap.Offset[Hubcap].vz;

	SetRotMatrix(&cp->hd.where);
	_MatrixRotate(&gHubcap.Position);

	gHubcap.Position.vx = gHubcap.Position.vx + cp->hd.where.t[0];
	gHubcap.Position.vy = gHubcap.Position.vy - cp->hd.where.t[1];
	gHubcap.Position.vz = gHubcap.Position.vz + cp->hd.where.t[2];

	gHubcap.Orientation = cp->hd.where;

	Calc_Object_MatrixYZX(&gHubcap.LocalOrientation, &InitialLocalAngle);

	if (Hubcap > 1)
	{
		gHubcap.Orientation.m[0][0] = -gHubcap.Orientation.m[0][0];
		gHubcap.Orientation.m[1][0] = -gHubcap.Orientation.m[1][0];

		gHubcap.Orientation.m[2][0] = -gHubcap.Orientation.m[2][0];
		gHubcap.Orientation.m[0][2] = -gHubcap.Orientation.m[0][2];

		gHubcap.Orientation.m[1][2] = -gHubcap.Orientation.m[1][2];
		gHubcap.Orientation.m[2][2] = -gHubcap.Orientation.m[2][2];
	}

	gHubcap.Duration = 100;
	gHubcap.Direction.vx = FIXEDH(FIXEDH(cp->st.n.angularVelocity[1]) * gHubcap.Offset[Hubcap].vz) + FIXEDH(cp->st.n.linearVelocity[0]);
	gHubcap.Direction.vy = FIXEDH(cp->st.n.linearVelocity[1]);
	gHubcap.Direction.vz = FIXEDH(-FIXEDH(cp->st.n.angularVelocity[1]) * gHubcap.Offset[Hubcap].vx) + FIXEDH(cp->st.n.linearVelocity[2]);
}


// [A]
void HandlePlayerHubcaps(int playerId)
{
	int VelocityMagnitude;
	CAR_DATA* cp;
	int playerCarId;

	playerCarId = player[playerId].playerCarId;

	if (playerCarId < 0)
		return;

	cp = &car_data[playerCarId];

	if (gHubcap.Duration < 1 && gHubcapTime == 0)
	{
		VelocityMagnitude = cp->st.n.angularVelocity[0] + cp->st.n.angularVelocity[1] + cp->st.n.angularVelocity[2];

		if (VelocityMagnitude < -1000000)
		{
			LoseHubcap(playerCarId, Random2(2) & 1, VelocityMagnitude);
			VelocityMagnitude = 3;
		}
		else if (VelocityMagnitude > 1000001)
		{
			LoseHubcap(playerCarId, Random2(4) & 1 | 2, VelocityMagnitude);
			VelocityMagnitude = 5;
		}
		else
			return;

		gHubcapTime = Random2(VelocityMagnitude) & 0x417;
	}
}

// [D] [T]
void MoveHubcap()
{
	int CurrentMapHeight;
	int savecombo;
	int cmb;
	VECTOR ShadowPos;
	VECTOR Position;
	MATRIX Orientation;
	CVECTOR col = {72,72,72};

	if (pauseflag == 0)
	{
		if(gHubcapTime > 0)
			gHubcapTime--;
	}

	// draw current hubcap
	if (gHubcap.Duration > 0) 
	{
		if (pauseflag == 0 && CurrentPlayerView == 0)
		{
			gHubcap.Duration--;

			// move hubcap
			gHubcap.Position.vx += gHubcap.Direction.vx;
			gHubcap.Position.vy += gHubcap.Direction.vy;
			gHubcap.Position.vz += gHubcap.Direction.vz;

			_RotMatrixX(&gHubcap.LocalOrientation, -220);

			gHubcap.Direction.vy += 5;

			CurrentMapHeight = MapHeight(&gHubcap.Position);

			if (gHubcap.Position.vy >= -40 - CurrentMapHeight)
			{
				gHubcap.Direction.vy = -(gHubcap.Direction.vy / 2);
				gHubcap.Position.vy = -40 - CurrentMapHeight;
			}
		}

		MulMatrix0(&gHubcap.Orientation, &gHubcap.LocalOrientation, &Orientation);

		ShadowPos.vx = gHubcap.Position.vx - camera_position.vx;
		ShadowPos.vy = -MapHeight(&gHubcap.Position);
		ShadowPos.vz = gHubcap.Position.vz - camera_position.vz;

		Position.vx = ShadowPos.vx;
		Position.vy = gHubcap.Position.vy - camera_position.vy;
		Position.vz = ShadowPos.vz;

		SetRotMatrix(&inv_camera_matrix);

		_MatrixRotate(&Position);
		savecombo = combointensity;

		if (gTimeOfDay == 3)
		{
			cmb = (combointensity & 0xffU) / 3;
			combointensity = cmb << 0x10 | cmb << 8 | cmb;
		}

		RenderModel(gHubcapModelPtr, &Orientation, &Position, 0, 0, 0, 0);
		ShadowPos.vy -= camera_position.vy;

		combointensity = savecombo;

		RoundShadow(&ShadowPos, &col, 65);
	}
}

#ifndef PSX
// [A] loads car model from file
char* LoadCarDentingFromFile(char* dest, int modelNumber)
{
	char* mem;
	char filename[64];

	sprintf(filename, "LEVELS\\%s\\CARMODEL_%d.DEN", LevelNames[GameLevel], modelNumber);
	if(FileExists(filename))
	{
		mem = dest ? dest : (_other_buffer2 + modelNumber * 0x1000);

		// get model from file
		Loadfile(filename, mem);
		return mem;
	}

	return NULL;
}
#endif

// [D] [T]
void ProcessDentLump(char *lump_ptr, int lump_size)
{
	int model;
	int i;
	int offset;
	u_char* mem;

	i = 0;

	while (i < MAX_CAR_MODELS)
	{
		model = MissionHeader->residentModels[i];

		if (model == 13)
		{
			model = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);

			if (model < 1) 
				model = 1;
			else if(model > 4)
				model = 4;
		}

		if (model != -1) 
		{
			offset = *(int *)(lump_ptr + model * 4);
			mem = (u_char*)lump_ptr;
#ifndef PSX
			char* newDenting = LoadCarDentingFromFile(NULL, model);
			if(newDenting)
			{
				mem = (u_char*)newDenting;
				offset = 0;
			}
#endif

			memcpy((u_char*)gCarDamageZoneVerts[i], mem + offset, NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_VERTS);
			offset += NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_VERTS;
			
			memcpy((u_char*)gHDCarDamageZonePolys[i], mem + offset, NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_POLYS);
			offset += NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_POLYS;
			
			memcpy((u_char*)gHDCarDamageLevels[i], mem + offset, MAX_FILE_DAMAGE_LEVELS);
		}

		i++;
	}
}


// [D] [T]
void SetupSpecDenting(char *loadbuffer)
{
	int offset;

	// [A] this is better
	memcpy((u_char*)gCarDamageZoneVerts[4], (u_char*)loadbuffer, NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_VERTS);
	offset = NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_VERTS;

	memcpy((u_char*)gHDCarDamageZonePolys[4], (u_char*)loadbuffer + offset, NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_POLYS);
	offset += NUM_DAMAGE_ZONES * MAX_FILE_DAMAGE_ZONE_POLYS;

	memcpy((u_char*)gHDCarDamageLevels[4], (u_char*)loadbuffer + offset, MAX_FILE_DAMAGE_LEVELS);
}

// [D] [T]
void LoadDenting(int level)
{
	LoadfileSeg(DentingFiles[level], _other_buffer, 0, 12727);
	ProcessDentLump(_other_buffer, 0);
}



