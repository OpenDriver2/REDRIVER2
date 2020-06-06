#include "THISDUST.H"
#include "DENTING.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "STRINGS.H"
#include "MODELS.H"
#include "CARS.H"
#include "CONVERT.H"

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

// [D]
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

// [D]
void DentCar(_CAR_DATA *cp)
{
	short *psVar1;
	short *psVar2;
	unsigned char bVar3;
	short sVar4;
	ushort uVar5;
	short sVar6;
	int iVar7;
	uint uVar8;
	int iVar9;
	short *puVar10;
	short *psVar11;
	DENTUVS *pDVar12;
	SVECTOR *CleanVertPtr;
	int iVar13;
	int iVar14;
	unsigned char *pbVar15;
	unsigned char* DamPtr;
	SVECTOR *DamVertPtr;
	int iVar16;
	SVECTOR *pSVar17;
	short *psVar18;
	DENTUVS *pDVar19;
	MODEL *pMVar20;
	uint uVar21;
	int iVar22;

	short tempDamage[512];
	memset(tempDamage, 0, sizeof(tempDamage));

	iVar22 = 0;
	psVar18 = tempDamage;
	uVar21 = cp->ap.model;
	cp->lowDetail = -1;
	(cp->ap).qy = 0;
	(cp->ap).qw = 0;

	pMVar20 = gCarCleanModelPtr[uVar21];
	if (pMVar20 != NULL) 
	{
		iVar13 = 0;

		if (pMVar20->num_vertices != 0) 
		{
			puVar10 = tempDamage;
			do {
				*puVar10++ = 0;
				iVar13++;
			} while (iVar13 < pMVar20->num_vertices);
		}

		iVar7 = 0;
		iVar13 = 0;

		do {
			iVar9 = cp->ap.damage[iVar7];

			if (iVar22 < iVar9) 
				iVar22 = iVar9; // MaxDamage?

			iVar14 = 0;
			iVar16 = iVar13 + 1;

			DamPtr = gCarDamageZoneVerts[cp->ap.model][iVar7];

			while (iVar14 < 50 && *DamPtr != 0xff)
			{
				psVar11 = (short *)(tempDamage + *DamPtr);

				if (*psVar11 == 0)
					*psVar11 += iVar9;
				else 
					*psVar11 += iVar9 / 2;

				iVar14++;
				DamPtr++;
			}

			iVar7 = iVar16;
			iVar13 = iVar16;
		} while (iVar16 < 6);
	}

	iVar22 = 0;
	if ((gCarCleanModelPtr[uVar21] != NULL && gCarDamModelPtr[uVar21] != NULL) && pMVar20->num_vertices != 0) 
	{
		pSVar17 = gTempCarVertDump[cp->id];
		DamVertPtr = (SVECTOR *)gCarDamModelPtr[uVar21]->vertices;
		CleanVertPtr = (SVECTOR *)gCarCleanModelPtr[uVar21]->vertices;

		do {
			pSVar17->vx = CleanVertPtr->vx + FIXED((DamVertPtr->vx - CleanVertPtr->vx) * *psVar18 / 2);
			pSVar17->vy = CleanVertPtr->vy + FIXED((DamVertPtr->vy - CleanVertPtr->vy) * *psVar18 / 2);
			pSVar17->vz = CleanVertPtr->vz + FIXED((DamVertPtr->vz - CleanVertPtr->vz) * *psVar18 / 2);

			iVar22++;
			psVar18++;
			DamVertPtr++;
			CleanVertPtr++;

			pSVar17++;
		} while (iVar22 < pMVar20->num_vertices);
	}

	pDVar19 = gTempHDCarUVDump[cp->id];
	
	if (pMVar20 != NULL) 
	{
		iVar22 = 0;
		pDVar12 = pDVar19;
		if (pMVar20->num_polys != 0) 
		{
			do {
				pDVar12->u3 = 0;
				iVar22++;
				pDVar12++;
			} while (iVar22 < pMVar20->num_polys);
		}

		iVar13 = 0;
		iVar22 = 0;

		do {
			uVar5 = *(ushort *)(cp->ap.damage + iVar13);

			iVar13 = 0;
			iVar7 = iVar22 + 1;

			while (iVar13 < 70 && gHDCarDamageZonePolys[cp->ap.model][iVar22][iVar13] != 0xFF)
			{
				pDVar12 = pDVar19 + gHDCarDamageZonePolys[cp->ap.model][iVar22][iVar13];

				uVar8 = pDVar12->u3 + ((int)((uint)uVar5 << 0x10) >> 0x1a);
				pDVar12->u3 = uVar8;

				if (2 < (uVar8 & 0xff))
					pDVar12->u3 = 2;

				iVar13 = iVar13 + 1;
			}

			iVar13 = iVar7;
			iVar22 = iVar7;
		} while (iVar7 < 6);

		pbVar15 = gHDCarDamageLevels[uVar21];
		iVar22 = 0;

		if (pMVar20->num_polys != 0) 
		{
			do {
				bVar3 = *pbVar15;
				pbVar15 = pbVar15 + 1;
				iVar22 = iVar22 + 1;
				pDVar19->u3 = ((bVar3 ^ 1 ^ (bVar3 ^ 1 | pDVar19->u3))
					<< 6);
				pDVar19 = pDVar19 + 1;
			} while (iVar22 < pMVar20->num_polys);
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

// [D]
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

void InitHubcap(void)
{
	gHubcapTime = Random2(1) & 0x7ff;
	gHubcap.Present[0] = 1;
	gHubcap.Present[1] = 1;
	gHubcap.Present[2] = 1;
	gHubcap.Present[3] = 1;
	gHubcap.Offset[0].vx = 0xcd;
	gHubcap.Offset[0].vy = -7;
	gHubcap.Offset[0].vz = 0x122;
	gHubcap.Offset[1].vx = 0xcd;
	gHubcap.Offset[1].vy = -7;
	gHubcap.Offset[1].vz = -0x113;
	gHubcap.Offset[2].vx = -0xcd;
	gHubcap.Offset[2].vy = -7;
	gHubcap.Offset[2].vz = 0x122;
	gHubcap.Offset[3].vx = -0xcd;
	gHubcap.Offset[3].vy = -7;
	gHubcap.Offset[3].vz = -0x113;
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

void LoseHubcap(int Hubcap, int Velocity)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	undefined4 local_40;
	undefined4 local_3c;
	long local_1c;

	local_40 = DAT_000aa398;
	local_3c = DAT_000aa39c;
	if (-1 < car_data[0].hd.wheel_speed) {
		if (gHubcap.Present[Hubcap] != 0) {
			gHubcap.Present[Hubcap] = 0;
			gHubcap.Position.vx = gHubcap.Offset[Hubcap].vx;
			gHubcap.Position.vy = gHubcap.Offset[Hubcap].vy;
			gHubcap.Position.vz = gHubcap.Offset[Hubcap].vz;
			SetRotMatrix(0xd1288);
			_MatrixRotate(&gHubcap.Position);
			gHubcap.Position.vx = gHubcap.Position.vx + car_data[0].hd.where.t[0];
			gHubcap.Position.vy = gHubcap.Position.vy - car_data[0].hd.where.t[1];
			gHubcap.Position.vz = gHubcap.Position.vz + car_data[0].hd.where.t[2];
			gHubcap.Orientation.m[0]._0_4_ = car_data[0].hd.drawCarMat.m[0]._0_4_;
			gHubcap.Orientation.m._4_4_ = car_data[0].hd.drawCarMat.m._4_4_;
			gHubcap.Orientation.m[1]._2_4_ = car_data[0].hd.drawCarMat.m[1]._2_4_;
			gHubcap.Orientation.m[2]._0_4_ = car_data[0].hd.drawCarMat.m[2]._0_4_;
			gHubcap.Orientation._16_4_ = car_data[0].hd.drawCarMat._16_4_;
			gHubcap.Orientation.t[0] = car_data[0].hd.drawCarMat.t[0];
			gHubcap.Orientation.t[1] = car_data[0].hd.drawCarMat.t[1];
			gHubcap.Orientation.t[2] = car_data[0].hd.drawCarMat.t[2];
			Calc_Object_MatrixYZX(&gHubcap.LocalOrientation, (SVECTOR *)&local_40);
			if (Hubcap - 2U < 2) {
				gHubcap.Orientation.m[0]._0_4_ =
					gHubcap.Orientation.m[0]._0_4_ & 0xffff0000 |
					(uint)(ushort)-gHubcap.Orientation.m[0][0];
				gHubcap.Orientation.m[2]._0_4_ =
					gHubcap.Orientation.m[2]._0_4_ & 0xffff0000 |
					(uint)(ushort)-gHubcap.Orientation.m[2][0];
				gHubcap.Orientation.m._4_4_ =
					CONCAT22(-gHubcap.Orientation.m[1][0], -(short)gHubcap.Orientation.m._4_4_);
				gHubcap.Orientation.m[1]._2_4_ =
					gHubcap.Orientation.m[1]._2_4_ & 0xffff |
					(uint)(ushort)-gHubcap.Orientation.m[1][2] << 0x10;
				gHubcap.Orientation._16_4_ =
					gHubcap.Orientation._16_4_ & 0xffff0000 | (uint)(ushort)-gHubcap.Orientation.m[2][2];
			}
			iVar1 = (car_data[0].st._44_4_ >> 0xc) * gHubcap.Offset[Hubcap].vz;
			if (iVar1 < 0) {
				iVar1 = iVar1 + 0xfff;
			}
			iVar2 = -(car_data[0].st._44_4_ >> 0xc) * gHubcap.Offset[Hubcap].vx;
			if (iVar2 < 0) {
				iVar2 = iVar2 + 0xfff;
			}
			gHubcap.Duration = 100;
			gHubcap.Direction.vx = (iVar1 >> 0xc) + (car_data[0].st._28_4_ >> 0xc);
			gHubcap.Direction.vy = car_data[0].st._32_4_ >> 0xc;
			gHubcap.Direction.vz = (iVar2 >> 0xc) + (car_data[0].st._36_4_ >> 0xc);
			gHubcap.Direction.pad = local_1c;
		}
	}
	return;
	*/
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

void MoveHubcap(void)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	int Velocity;
	VECTOR local_50;
	MATRIX MStack64;
	CVECTOR local_20[2];

	local_20[0] = (CVECTOR)PTR_DAT_000aa3a0;
	if ((pauseflag == 0) && (0 < gHubcapTime)) {
		gHubcapTime = gHubcapTime + -1;
	}
	if ((gHubcap.Duration < 1) && (gHubcapTime == 0)) {
		Velocity = car_data[0].st._40_4_ + car_data[0].st._44_4_ + car_data[0].st._48_4_;
		if (Velocity < -1000000) {
			uVar1 = Random2(2);
			LoseHubcap(uVar1 & 1 | 2, Velocity);
			Velocity = 3;
		}
		else {
			if (Velocity < 0xf4241) {
				return;
			}
			uVar1 = Random2(4);
			LoseHubcap(uVar1 & 1, Velocity);
			Velocity = 5;
		}
		uVar1 = Random2(Velocity);
		gHubcapTime = uVar1 & 0x417;
	}
	else {
		if (pauseflag == 0) {
			gHubcap.Duration = gHubcap.Duration + -1;
		}
		if (0 < gHubcap.Duration) {
			if (pauseflag == 0) {
				gHubcap.Position.vx = gHubcap.Position.vx + gHubcap.Direction.vx;
				gHubcap.Position.vy = gHubcap.Position.vy + gHubcap.Direction.vy;
				gHubcap.Position.vz = gHubcap.Position.vz + gHubcap.Direction.vz;
				_RotMatrixX(&gHubcap.LocalOrientation, -0xdc);
				gHubcap.Direction.vy = gHubcap.Direction.vy + 5;
				Velocity = MapHeight(&gHubcap.Position);
				if (-0x3c - Velocity <= gHubcap.Position.vy) {
					gHubcap.Direction.vy = -(gHubcap.Direction.vy / 2);
					gHubcap.Position.vy = -0x3c - Velocity;
				}
			}
			MulMatrix0(0xc9450, 0xc9470, &MStack64);
			ShadowPos.vx = gHubcap.Position.vx - camera_position.vx;
			local_50.vy = gHubcap.Position.vy - camera_position.vy;
			ShadowPos.vz = gHubcap.Position.vz - camera_position.vz;
			local_50.vx = ShadowPos.vx;
			local_50.vz = ShadowPos.vz;
			SetRotMatrix(&inv_camera_matrix);
			Velocity = MapHeight(&gHubcap.Position);
			ShadowPos.vy = -Velocity;
			_MatrixRotate(&local_50);
			Velocity = combointensity;
			if (gTimeOfDay == 3) {
				uVar1 = (combointensity & 0xffU) / 3;
				combointensity = uVar1 << 0x10 | uVar1 << 8 | uVar1;
			}
			RenderModel(gHubcapModelPtr, &MStack64, &local_50, 0, 0);
			ShadowPos.vy = ShadowPos.vy - camera_position.vy;
			combointensity = Velocity;
			RoundShadow(&ShadowPos, local_20, 0x41);
		}
	}
	return;*/
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

// [D]
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

// [D]
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

// [D]
void SetupSpecDenting(char *loadbuffer)
{
	// [A] this is better
	memcpy(*gCarDamageZoneVerts[4], loadbuffer, 300);
	memcpy(*gHDCarDamageZonePolys[4], loadbuffer + 300, 420);
	memcpy(gHDCarDamageLevels[4], loadbuffer + 300 + 420, 255);
}





