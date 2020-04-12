#include "THISDUST.H"
#include "DENTING.H"
#include "SYSTEM.H"
#include "MISSION.H"

char* DentingFiles[] =
{
	"LEVELS\\CHICAGO.DEN",
	"LEVELS\\HAVANA.DEN",
	"LEVELS\\VEGAS.DEN",
	"LEVELS\\RIO.DEN",
};

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
	return;
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

void DentCar(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	short *psVar2;
	short *psVar3;
	byte bVar4;
	short sVar5;
	ushort uVar6;
	short sVar7;
	int iVar8;
	uint uVar9;
	int iVar10;
	undefined4 *puVar11;
	DENTUVS *pDVar12;
	short *psVar13;
	int iVar14;
	int iVar15;
	byte *pbVar16;
	short *psVar17;
	int iVar18;
	SVECTOR *pSVar19;
	undefined4 *puVar20;
	DENTUVS *pDVar21;
	MODEL *pMVar22;
	uint uVar23;
	int iVar24;

	iVar24 = 0;
	puVar20 = &DAT_1f800044;
	uVar23 = (uint)(byte)(cp->ap).model;
	cp->lowDetail = -1;
	(cp->ap).qy = 0;
	(cp->ap).qw = 0;
	pMVar22 = gCarCleanModelPtr5[uVar23];
	if (pMVar22 != (MODEL *)0x0) {
		iVar14 = 0;
		if (pMVar22->num_vertices != 0) {
			puVar11 = &DAT_1f800044;
			do {
				*(undefined2 *)puVar11 = 0;
				iVar14 = iVar14 + 1;
				puVar11 = (undefined4 *)((int)puVar11 + 2);
			} while (iVar14 < (int)(uint)pMVar22->num_vertices);
		}
		iVar8 = 0;
		iVar14 = 0;
		do {
			sVar5 = *(short *)((int)(cp->ap).damage + iVar8);
			iVar10 = (int)sVar5;
			if (iVar24 < iVar10) {
				iVar24 = iVar10;
			}
			iVar15 = 0;
			iVar18 = iVar14 + 1;
			while ((iVar15 < 0x32 &&
				(gCarDamageZoneVerts[iVar15 + iVar8 * 0x10 + iVar14 * 0x12 + uVar23 * 300] != 0xff))) {
				puVar11 = (undefined4 *)
					((int)&DAT_1f800044 +
					(uint)gCarDamageZoneVerts[iVar15 + iVar8 * 0x10 + iVar14 * 0x12 + uVar23 * 300] *
						2);
				if ((int)*(short *)puVar11 == 0) {
					sVar7 = *(short *)puVar11 + sVar5;
				}
				else {
					sVar7 = (short)((int)*(short *)puVar11 + iVar10 >> 1);
				}
				*(short *)puVar11 = sVar7;
				iVar15 = iVar15 + 1;
			}
			iVar8 = iVar18 * 2;
			iVar14 = iVar18;
		} while (iVar18 < 6);
	}
	pSVar19 = &gTempCarVertDump + (uint)(byte)cp->id * 0x84;
	psVar17 = (short *)gCarDamModelPtr5[uVar23]->vertices;
	psVar13 = (short *)gCarCleanModelPtr5[uVar23]->vertices;
	if (((gCarCleanModelPtr5[uVar23] != (MODEL *)0x0) && (gCarDamModelPtr5[uVar23] != (MODEL *)0x0))
		&& (iVar24 = 0, pMVar22->num_vertices != 0)) {
		do {
			pSVar19->vx = *psVar13 +
				(short)(((int)*psVar17 - (int)*psVar13) * (int)*(short *)puVar20 >> 0xc);
			pSVar19->vy = psVar13[1] +
				(short)(((int)psVar17[1] - (int)psVar13[1]) * (int)*(short *)puVar20 >> 0xc);
			psVar1 = psVar17 + 2;
			psVar2 = psVar13 + 2;
			sVar5 = *(short *)puVar20;
			iVar24 = iVar24 + 1;
			puVar20 = (undefined4 *)((int)puVar20 + 2);
			psVar17 = psVar17 + 4;
			psVar3 = psVar13 + 2;
			psVar13 = psVar13 + 4;
			pSVar19->vz = *psVar3 + (short)(((int)*psVar1 - (int)*psVar2) * (int)sVar5 >> 0xc);
			pSVar19 = pSVar19 + 1;
		} while (iVar24 < (int)(uint)pMVar22->num_vertices);
	}
	pDVar21 = &gTempHDCarUVDump + (uint)(byte)cp->id * 0xff;
	if (pMVar22 != (MODEL *)0x0) {
		iVar24 = 0;
		pDVar12 = pDVar21;
		if (pMVar22->num_polys != 0) {
			do {
				pDVar12->u3 = '\0';
				iVar24 = iVar24 + 1;
				pDVar12 = pDVar21 + iVar24;
			} while (iVar24 < (int)(uint)pMVar22->num_polys);
		}
		iVar14 = 0;
		iVar24 = 0;
		do {
			uVar6 = *(ushort *)((int)(cp->ap).damage + iVar14);
			iVar14 = 0;
			iVar8 = iVar24 + 1;
			while ((iVar14 < 0x46 &&
				(pDVar12 = pDVar21 + gHDCarDamageZonePolys[iVar14 + iVar24 * 0x46 + uVar23 * 0x1a4],
					gHDCarDamageZonePolys[iVar14 + iVar24 * 0x46 + uVar23 * 0x1a4] != 0xff))) {
				uVar9 = (uint)(byte)pDVar12->u3 + ((int)((uint)uVar6 << 0x10) >> 0x1a);
				pDVar12->u3 = (char)uVar9;
				if (2 < (uVar9 & 0xff)) {
					pDVar12->u3 = '\x02';
				}
				iVar14 = iVar14 + 1;
			}
			iVar14 = iVar8 * 2;
			iVar24 = iVar8;
		} while (iVar8 < 6);
		pbVar16 = &gHDCarDamageLevels + uVar23 * 0xff;
		iVar24 = 0;
		if (pMVar22->num_polys != 0) {
			do {
				bVar4 = *pbVar16;
				pbVar16 = pbVar16 + 1;
				iVar24 = iVar24 + 1;
				pDVar21->u3 = (char)(((uint)bVar4 ^ 1 ^ ((uint)bVar4 ^ 1 | (uint)(byte)pDVar21->u3)) << 6);
				pDVar21 = pDVar21 + 1;
			} while (iVar24 < (int)(uint)pMVar22->num_polys);
		}
	}
	return;*/
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

void CreateDentableCar(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	DENTUVS *pDVar5;
	short *psVar6;
	MODEL *pMVar7;
	SVECTOR *pSVar8;
	int iVar9;
	uint uVar10;
	uint uVar11;

	uVar11 = (uint)(byte)(cp->ap).model;
	pMVar7 = gCarCleanModelPtr5[uVar11];
	if (pMVar7 != (MODEL *)0x0) {
		psVar6 = (short *)pMVar7->vertices;
		uVar10 = (uint)pMVar7->num_vertices;
		pSVar8 = &gTempCarVertDump + (uint)(byte)cp->id * 0x84;
		while (uVar10 = uVar10 - 1, uVar10 != 0xffffffff) {
			sVar2 = *psVar6;
			sVar3 = psVar6[1];
			sVar4 = psVar6[2];
			psVar6 = psVar6 + 4;
			pSVar8->vx = sVar2;
			pSVar8->vy = sVar3;
			pSVar8->vz = sVar4;
			pSVar8 = pSVar8 + 1;
		}
		iVar9 = 0;
		bVar1 = cp->id;
		pDVar5 = &gTempHDCarUVDump + (uint)bVar1 * 0xff;
		if (gCarCleanModelPtr5[uVar11]->num_polys != 0) {
			do {
				pDVar5->u3 = '\0';
				iVar9 = iVar9 + 1;
				pDVar5 = &gTempHDCarUVDump + (uint)bVar1 * 0xff + iVar9;
			} while (iVar9 < (int)(uint)gCarCleanModelPtr5[uVar11]->num_polys);
		}
	}
	pMVar7 = gCarLowModelPtr5[uVar11];
	if (pMVar7 != (MODEL *)0x0) {
		iVar9 = 0;
		bVar1 = cp->id;
		pDVar5 = &gTempLDCarUVDump + (uint)bVar1 * 0x86;
		if (pMVar7->num_polys != 0) {
			do {
				pDVar5->u3 = '\0';
				iVar9 = iVar9 + 1;
				pDVar5 = &gTempLDCarUVDump + (uint)bVar1 * 0x86 + iVar9;
			} while (iVar9 < (int)(uint)gCarLowModelPtr5[uVar11]->num_polys);
		}
	}
	iVar9 = 5;
	if (gDontResetCarDamage == 0) {
		psVar6 = (cp->ap).damage + 5;
		do {
			*psVar6 = 0;
			iVar9 = iVar9 + -1;
			psVar6 = psVar6 + -1;
		} while (-1 < iVar9);
		cp->totalDamage = 0;
	}
	return;*/
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

void InitHubcap(void)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;

	uVar1 = Random2(1);
	gHubcapTime = uVar1 & 0x7ff;
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
	return;*/
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

unsigned char gCarDamageZoneVerts[5][6][50];
unsigned char gHDCarDamageZonePolys[5][6][70];
unsigned char gHDCarDamageLevels[5][255];

// [D]
void ProcessDentLump(char *lump_ptr, int lump_size)
{
	// [A] This function causes buffer overrun and corrupts HEAP
	UNIMPLEMENTED();
	/*
	unsigned char uVar1;
	int *local_v1_316;
	int *piVar2;
	int iVar3;
	int *piVar4;
	int *piVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;

	

	iVar6 = 0;
	do {
		iVar3 = MissionHeader->residentModels[iVar6];

		if (iVar3 == 0xd)
		{
			iVar3 = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);
			if (iVar3 < 1) {
				iVar3 = 1;
			}
			else {
				if (4 < iVar3) {
					iVar3 = 4;
				}
			}
		}

		iVar7 = iVar6 + 1;

		if (iVar3 != -1) 
		{
			local_v1_316 = (int *)(gCarDamageZoneVerts + iVar6 * 300);
			piVar4 = (int *)(lump_ptr + *(int *)(lump_ptr + iVar3 * 4));
			piVar2 = piVar4;

			// memcpy
			if (((uint)piVar4 & 3) == 0) {
				do {
					iVar3 = piVar2[1];
					iVar8 = piVar2[2];
					iVar9 = piVar2[3];
					*local_v1_316 = *piVar2;
					local_v1_316[1] = iVar3;
					local_v1_316[2] = iVar8;
					local_v1_316[3] = iVar9;
					piVar2 = piVar2 + 4;
					local_v1_316 = local_v1_316 + 4;
				} while (piVar2 != piVar4 + 0x48);
			}
			else {
				do {
					iVar3 = piVar2[1];
					iVar8 = piVar2[2];
					iVar9 = piVar2[3];
					*local_v1_316 = *piVar2;
					local_v1_316[1] = iVar3;
					local_v1_316[2] = iVar8;
					local_v1_316[3] = iVar9;
					piVar2 = piVar2 + 4;
					local_v1_316 = local_v1_316 + 4;
				} while (piVar2 != piVar4 + 0x48);
			}

			iVar3 = piVar2[1];
			iVar8 = piVar2[2];
			*local_v1_316 = *piVar2;
			local_v1_316[1] = iVar3;
			local_v1_316[2] = iVar8;
			piVar2 = (int *)(gHDCarDamageZonePolys + iVar6 * 0x1a4);
			piVar5 = piVar4 + 0x4b;

			// memcpy
			if (((uint)piVar5 & 3) == 0) {
				do {
					iVar9 = piVar5[1];
					iVar3 = piVar5[2];
					iVar8 = piVar5[3];
					*piVar2 = *piVar5;
					piVar2[1] = iVar9;
					piVar2[2] = iVar3;
					piVar2[3] = iVar8;
					piVar5 = piVar5 + 4;
					piVar2 = piVar2 + 4;
				} while (piVar5 != piVar4 + 0xb3);
			}
			else {
				do {
					iVar3 = piVar5[1];
					iVar8 = piVar5[2];
					iVar9 = piVar5[3];
					*piVar2 = *piVar5;
					piVar2[1] = iVar3;
					piVar2[2] = iVar8;
					piVar2[3] = iVar9;
					piVar5 = piVar5 + 4;
					piVar2 = piVar2 + 4;
				} while (piVar5 != piVar4 + 0xb3);
			}

			*piVar2 = *piVar5;
			piVar2 = (int *)(&gHDCarDamageLevels + iVar6 * 0xff);
			piVar5 = piVar4 + 0xb4;

			// memcpy
			if ((((uint)piVar5 | (uint)piVar2) & 3) == 0) {
				do {
					iVar6 = piVar5[1];
					iVar3 = piVar5[2];
					iVar8 = piVar5[3];
					*piVar2 = *piVar5;
					piVar2[1] = iVar6;
					piVar2[2] = iVar3;
					piVar2[3] = iVar8;
					piVar5 = piVar5 + 4;
					piVar2 = piVar2 + 4;
				} while (piVar5 != piVar4 + 0xf0);
			}
			else {
				do {
					iVar6 = piVar5[1];
					iVar3 = piVar5[2];
					iVar8 = piVar5[3];
					*piVar2 = *piVar5;
					piVar2[1] = iVar6;
					piVar2[2] = iVar3;
					piVar2[3] = iVar8;
					piVar5 = piVar5 + 4;
					piVar2 = piVar2 + 4;
				} while (piVar5 != piVar4 + 0xf0);
			}

			iVar6 = piVar5[1];
			iVar3 = piVar5[2];
			uVar1 = *(unsigned char *)(piVar5 + 3);
			*piVar2 = *piVar5;
			piVar2[1] = iVar6;
			piVar2[2] = iVar3;
			*(unsigned char *)(piVar2 + 3) = uVar1;
			uVar1 = *(unsigned char *)((int)piVar5 + 0xe);
			*(unsigned char *)((int)piVar2 + 0xd) = *(unsigned char *)((int)piVar5 + 0xd);
			*(unsigned char *)((int)piVar2 + 0xe) = uVar1;
		}
		iVar6 = iVar7;
	} while (iVar7 < 5);*/
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
	unsigned char *from;
	unsigned char *to;

	from = (unsigned char*)gCarDamageZoneVerts[4];
	to = (unsigned char*)&gCarDamageZoneVerts[4][5][50]; // [A]
	if (true) {
		do {
			*from = *loadbuffer;
			from = from + 1;
			loadbuffer = (char *)((unsigned char *)loadbuffer + 1);
		} while (from < to);
	}

	from = (unsigned char*)gHDCarDamageZonePolys[4];
	to = (unsigned char*)&gHDCarDamageZonePolys[4][5][70]; // [A]
	if (true) {
		do {
			*from = *loadbuffer;
			from = from + 1;
			loadbuffer = (char *)((unsigned char *)loadbuffer + 1);
		} while (from < to);
	}

	from = (unsigned char*)gHDCarDamageLevels[4];
	to = (unsigned char*)&gHDCarDamageLevels[4][255]; // [A]
	if (true) {
		do {
			*from = *loadbuffer;
			from = from + 1;
			loadbuffer = (char *)((unsigned char *)loadbuffer + 1);
		} while (from < to);
	}
}





