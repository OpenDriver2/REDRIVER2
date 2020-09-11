#include "DRIVER2.H"
#include "DENTING.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "STRINGS.H"
#include "MODELS.H"
#include "CARS.H"
#include "CONVERT.H"
#include "PAUSE.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "DR2ROADS.H"
#include "DEBRIS.H"
#include "PLAYERS.H"


char* DentingFiles[] =
{
	"LEVELS\\CHICAGO.DEN",
	"LEVELS\\HAVANA.DEN",
	"LEVELS\\VEGAS.DEN",
	"LEVELS\\RIO.DEN",
};

unsigned char gCarDamageZoneVerts[5][6][50];
unsigned char gHDCarDamageZonePolys[5][6][70];
unsigned char gHDCarDamageLevels[5][255];

// decompiled code
// original method signature: 
// void /*$ra*/ InitialiseDenting()
 // line 267, offset 0x0003b1c0
	/* begin block 1 */
		// Start line: 534
	/* end block 1 */
	// End Line: 535

	/* begin block 2 */
		// Start line: 1508
	/* end block 2 */
	// End Line: 1509

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitialiseDenting(void)
{
	LoadDenting(GameLevel);
	InitHubcap();
}


// decompiled code
// original method signature: 
// void /*$ra*/ DentCar(struct _CAR_DATA *cp /*$t7*/)
 // line 288, offset 0x0003a310
	/* begin block 1 */
		// Start line: 289
		// Start offset: 0x0003A310
		// Variables:
	// 		struct SVECTOR *VertPtr; // $t0
	// 		int MaxDamage; // $s0
	// 		unsigned char VertIndex; // $v0
	// 		unsigned char PolyIndex; // $v0
	// 		struct DENTUVS *dentptr; // $t1
	// 		unsigned char *DamPtr; // $a2
	// 		int model; // $t5
	// 		int Poly; // $a1
	// 		int Damage; // $v1
	// 		int Zone; // $a3
	// 		int VertNo; // $a2
	// 		short *tempDamage; // $t1
	// 		struct SVECTOR *DamVertPtr; // $a3
	// 		struct SVECTOR *CleanVertPtr; // $a1
	// 		struct MODEL *pCleanModel; // $t3

		/* begin block 1.1 */
			// Start line: 421
			// Start offset: 0x0003A690
		/* end block 1.1 */
		// End offset: 0x0003A690
		// End Line: 423
	/* end block 1 */
	// End offset: 0x0003A6E4
	// End Line: 428

	/* begin block 2 */
		// Start line: 576
	/* end block 2 */
	// End Line: 577

	/* begin block 3 */
		// Start line: 579
	/* end block 3 */
	// End Line: 580

// [D] [T]
void DentCar(_CAR_DATA *cp)
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

	short tempDamage[512];
	memset(tempDamage, 0, sizeof(tempDamage));


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
			while (VertNo < 50 && *DamPtr != 0xff)
			{
				if (tempDamage[*DamPtr] == 0)
					tempDamage[*DamPtr] += Damage;
				else 
					tempDamage[*DamPtr] += Damage / 2;

				DamPtr++;

				VertNo++;
			}

			Zone++;
		} while (Zone < 6);
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
			while (Poly < 70 && gHDCarDamageZonePolys[cp->ap.model][Zone][Poly] != 0xFF)
			{
				dentptr = gTempHDCarUVDump[cp->id] + gHDCarDamageZonePolys[cp->ap.model][Zone][Poly];
				dentptr->u3 += ((uint)Damage << 0x10) >> 0x1a;

				if (dentptr->u3 > 2)
					dentptr->u3 = 2;

				Poly++;
			}

			Zone++;
		} while (Zone < 6);

		Poly = 0;

		DamPtr = gHDCarDamageLevels[model];
		dentptr = gTempHDCarUVDump[cp->id];

		while (Poly < pCleanModel->num_polys)
		{
			dentptr->u3 = ((*DamPtr ^ 1 ^ (*DamPtr ^ 1 | dentptr->u3)) << 6);
			dentptr++;
			DamPtr++;
			Poly++;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CreateDentableCar(struct _CAR_DATA *cp /*$t2*/)
 // line 458, offset 0x0003a6e4
	/* begin block 1 */
		// Start line: 459
		// Start offset: 0x0003A6E4
		// Variables:
	// 		struct DENTUVS *dentptr; // $a3
	// 		int Zone; // $v1
	// 		int count; // $a2
	// 		int model; // $t3

		/* begin block 1.1 */
			// Start line: 478
			// Start offset: 0x0003A710
			// Variables:
		// 		struct SVECTOR *dst; // $a2
		// 		struct SVECTOR *src; // $a3
		// 		int count; // $t0

			/* begin block 1.1.1 */
				// Start line: 484
				// Start offset: 0x0003A748
				// Variables:
			// 		int x; // $v0
			// 		int y; // $v1
			// 		int z; // $a0
			/* end block 1.1.1 */
			// End offset: 0x0003A748
			// End Line: 484
		/* end block 1.1 */
		// End offset: 0x0003A770
		// End Line: 493
	/* end block 1 */
	// End offset: 0x0003A874
	// End Line: 534

	/* begin block 2 */
		// Start line: 1092
	/* end block 2 */
	// End Line: 1093

	/* begin block 3 */
		// Start line: 1123
	/* end block 3 */
	// End Line: 1124

	/* begin block 4 */
		// Start line: 1138
	/* end block 4 */
	// End Line: 1139

// [D] [T]
void CreateDentableCar(_CAR_DATA *cp)
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


	if (gDontResetCarDamage == 0) 
	{
		count = 0;
		while (count < 6)
		{
			cp->ap.damage[count] = 0;
			count++;
		}

		cp->totalDamage = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitHubcap()
 // line 549, offset 0x0003a874
	/* begin block 1 */
		// Start line: 552
		// Start offset: 0x0003A874
	/* end block 1 */
	// End offset: 0x0003A8F8
	// End Line: 573

	/* begin block 2 */
		// Start line: 1330
	/* end block 2 */
	// End Line: 1331

	/* begin block 3 */
		// Start line: 1346
	/* end block 3 */
	// End Line: 1347

	/* begin block 4 */
		// Start line: 1348
	/* end block 4 */
	// End Line: 1349

/* WARNING: Unknown calling convention yet parameter storage is locked */

extern HUBCAP gHubcap;
long gHubcapTime = 0;

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



// decompiled code
// original method signature: 
// void /*$ra*/ LoseHubcap(int Hubcap /*$s3*/, int Velocity /*$a1*/)
 // line 600, offset 0x0003a8f8
	/* begin block 1 */
		// Start line: 601
		// Start offset: 0x0003A8F8
		// Variables:
	// 		struct _CAR_DATA *car_data_pt; // $s1
	// 		struct SVECTOR InitialLocalAngle; // stack offset -64

		/* begin block 1.1 */
			// Start line: 671
			// Start offset: 0x0003AA84
			// Variables:
		// 		struct VECTOR R; // stack offset -56
		// 		struct VECTOR VW; // stack offset -40
		// 		long AY; // $t0
		/* end block 1.1 */
		// End offset: 0x0003AAE0
		// End Line: 681
	/* end block 1 */
	// End offset: 0x0003AB2C
	// End Line: 694

	/* begin block 2 */
		// Start line: 1441
	/* end block 2 */
	// End Line: 1442

	/* begin block 3 */
		// Start line: 1469
	/* end block 3 */
	// End Line: 1470

	/* begin block 4 */
		// Start line: 1471
	/* end block 4 */
	// End Line: 1472

// [D]
void LoseHubcap(int car, int Hubcap, int Velocity)
{
	int iVar1;
	int iVar2;
	SVECTOR InitialLocalAngle = { 0, 0, 10 };
	VECTOR R;
	VECTOR VW;
	_CAR_DATA* cp;

	cp = &car_data[car];

	if (cp->hd.wheel_speed > -1)
	{
		if ((cp->ap.flags & (1 << Hubcap)) == 0) //gHubcap.Present[Hubcap] != 0) 
		{
			cp->ap.flags |= (1 << Hubcap);
			//gHubcap.Present[Hubcap] = 0;

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
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ MoveHubcap()
 // line 706, offset 0x0003ab4c
	/* begin block 1 */
		// Start line: 708
		// Start offset: 0x0003AB4C
		// Variables:
	// 		struct _CAR_DATA *car_data_pt; // $a1
	// 		struct VECTOR Position; // stack offset -80
	// 		struct MATRIX Orientation; // stack offset -64
	// 		struct CVECTOR col; // stack offset -32
	// 		int VelocityMagnitude; // $s0
	// 		int CurrentMapHeight; // $a0
	// 		int savecombo; // $s0

		/* begin block 1.1 */
			// Start line: 731
			// Start offset: 0x0003ABF8
		/* end block 1.1 */
		// End offset: 0x0003AC18
		// End Line: 734

		/* begin block 1.2 */
			// Start line: 738
			// Start offset: 0x0003AC28
		/* end block 1.2 */
		// End offset: 0x0003AC58
		// End Line: 741

		/* begin block 1.3 */
			// Start line: 762
			// Start offset: 0x0003ACA4
		/* end block 1.3 */
		// End offset: 0x0003AD24
		// End Line: 780
	/* end block 1 */
	// End offset: 0x0003AE44
	// End Line: 805

	/* begin block 2 */
		// Start line: 1741
	/* end block 2 */
	// End Line: 1742

	/* begin block 3 */
		// Start line: 1742
	/* end block 3 */
	// End Line: 1743

	/* begin block 4 */
		// Start line: 1745
	/* end block 4 */
	// End Line: 1746

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void MoveHubcap(int playerId)
{
	int savecombo;
	int cmb;
	int CurrentMapHeight;
	int VelocityMagnitude;
	VECTOR ShadowPos;
	VECTOR Position;
	MATRIX Orientation;
	CVECTOR col = {72,72,72};
	_CAR_DATA* cp;
	int playerCarId;

	if (pauseflag == 0 && gHubcapTime > 0 && playerId == 0)
		gHubcapTime--;

	playerCarId = player[playerId].playerCarId;

	if (playerCarId < 0)
		return;
	
	cp = &car_data[playerCarId];

	if (gHubcap.Duration < 1 && (gHubcapTime == 0))
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
	else if(playerId == 0)
	{
		if (pauseflag == 0) 
			gHubcap.Duration--;

		if (0 < gHubcap.Duration) 
		{
			if (pauseflag == 0)
			{
				gHubcap.Position.vx += gHubcap.Direction.vx;
				gHubcap.Position.vy += gHubcap.Direction.vy;
				gHubcap.Position.vz += gHubcap.Direction.vz;

				_RotMatrixX(&gHubcap.LocalOrientation, -220);

				gHubcap.Direction.vy += 5;

				CurrentMapHeight = MapHeight(&gHubcap.Position);

				if (-60 - CurrentMapHeight <= gHubcap.Position.vy)
				{
					gHubcap.Direction.vy = -(gHubcap.Direction.vy / 2);
					gHubcap.Position.vy = -60 - CurrentMapHeight;
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

			RenderModel(gHubcapModelPtr, &Orientation, &Position, 0, 0, 0);
			ShadowPos.vy -= camera_position.vy;

			combointensity = savecombo;

			RoundShadow(&ShadowPos, &col, 65);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadDenting(int level /*$a0*/)
 // line 815, offset 0x0003b1f0
	/* begin block 1 */
		// Start line: 817
		// Start offset: 0x0003B1F0
	/* end block 1 */
	// End offset: 0x0003B240
	// End Line: 830

	/* begin block 2 */
		// Start line: 2602
	/* end block 2 */
	// End Line: 2603

	/* begin block 3 */
		// Start line: 2603
	/* end block 3 */
	// End Line: 2604

	/* begin block 4 */
		// Start line: 2610
	/* end block 4 */
	// End Line: 2611

// [D] [T]
void LoadDenting(int level)
{
	LoadfileSeg(DentingFiles[level], _other_buffer, 0, 0x31b7);
	ProcessDentLump(_other_buffer, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessDentLump(char *lump_ptr /*$t2*/, int lump_size /*$a1*/)
 // line 838, offset 0x0003ae60
	/* begin block 1 */
		// Start line: 839
		// Start offset: 0x0003AE60
		// Variables:
	// 		int i; // $a3
	// 		int model; // $a0
	// 		int offset; // $a0
	/* end block 1 */
	// End offset: 0x0003B1C0
	// End Line: 868

	/* begin block 2 */
		// Start line: 2047
	/* end block 2 */
	// End Line: 2048

// [D] [T]
void ProcessDentLump(char *lump_ptr, int lump_size)
{
	int model;
	int i;
	int offset;

	i = 0;

	while (i < 5)
	{
		model = MissionHeader->residentModels[i];

		if (model == 13)
		{
			model = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);

			if (model < 1) 
			{
				model = 1;
			}
			else if(model > 4)
			{
				model = 4;
			}
		}

		if (model != -1) 
		{
			offset = *(int *)(lump_ptr + model * 4);

			memcpy(*gCarDamageZoneVerts[i], lump_ptr+offset, 300);
			memcpy(*gHDCarDamageZonePolys[i], lump_ptr + offset + 300, 420);
			memcpy(gHDCarDamageLevels[i], lump_ptr + offset + 300 + 420, 255);
		}

		i++;
	};
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupSpecDenting(char *loadbuffer /*$a0*/)
 // line 877, offset 0x0003b240
	/* begin block 1 */
		// Start line: 878
		// Start offset: 0x0003B240
		// Variables:
	// 		char *from; // $a0
	// 		char *to; // $v1
	// 		char *limit; // $a1
	/* end block 1 */
	// End offset: 0x0003B2E4
	// End Line: 911

	/* begin block 2 */
		// Start line: 2681
	/* end block 2 */
	// End Line: 2682

	/* begin block 3 */
		// Start line: 2729
	/* end block 3 */
	// End Line: 2730

	/* begin block 4 */
		// Start line: 2739
	/* end block 4 */
	// End Line: 2740

// [D] [T]
void SetupSpecDenting(char *loadbuffer)
{
	// [A] this is better
	memcpy(*gCarDamageZoneVerts[4], loadbuffer, 300);
	memcpy(*gHDCarDamageZonePolys[4], loadbuffer + 300, 420);
	memcpy(gHDCarDamageLevels[4], loadbuffer + 300 + 420, 255);
}





