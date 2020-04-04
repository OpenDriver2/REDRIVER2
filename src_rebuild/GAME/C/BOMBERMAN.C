#include "THISDUST.H"
#include "BOMBERMAN.H"


// decompiled code
// original method signature: 
// void /*$ra*/ InitThrownBombs()
 // line 222, offset 0x0001f570
	/* begin block 1 */
		// Start line: 224
		// Start offset: 0x0001F570
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x0001F5F4
	// End Line: 235

	/* begin block 2 */
		// Start line: 1445
	/* end block 2 */
	// End Line: 1446

	/* begin block 3 */
		// Start line: 444
	/* end block 3 */
	// End Line: 445

	/* begin block 4 */
		// Start line: 1446
	/* end block 4 */
	// End Line: 1447

	/* begin block 5 */
		// Start line: 1448
	/* end block 5 */
	// End Line: 1449

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitThrownBombs(void)
{
	UNIMPLEMENTED();
	/*
	BOMB *pBVar1;
	long lVar2;
	int iVar3;
	int in_a0;

	iVar3 = 4;
	pBVar1 = &BOMB_000aca68;
	do {
		pBVar1->flags = '\0';
		iVar3 = iVar3 + -1;
		pBVar1 = pBVar1 + -1;
	} while (-1 < iVar3);
	lVar2 = Random2(in_a0);
	ThrownBombDelay = lVar2 % 0x2d + 8;
	CurrentBomb = 0;
	gWantFlash = 0;
	gBombTargetVehicle = (_CAR_DATA *)0x0;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleThrownBombs()
 // line 245, offset 0x0001e3e8
	/* begin block 1 */
		// Start line: 247
		// Start offset: 0x0001E3E8
		// Variables:
	// 		struct BOMB *bomb; // $s1
	// 		struct VECTOR velocity; // stack offset -48
	// 		struct _CAR_DATA *cp; // $s0
	// 		int i; // $s5
	// 		int y; // $a0

		/* begin block 1.1 */
			// Start line: 258
			// Start offset: 0x0001E42C
		/* end block 1.1 */
		// End offset: 0x0001E5C8
		// End Line: 301

		/* begin block 1.2 */
			// Start line: 319
			// Start offset: 0x0001E670
			// Variables:
		// 		int len; // $v1
		/* end block 1.2 */
		// End offset: 0x0001E6E8
		// End Line: 330
	/* end block 1 */
	// End offset: 0x0001E7E8
	// End Line: 357

	/* begin block 2 */
		// Start line: 490
	/* end block 2 */
	// End Line: 491

	/* begin block 3 */
		// Start line: 491
	/* end block 3 */
	// End Line: 492

	/* begin block 4 */
		// Start line: 497
	/* end block 4 */
	// End Line: 498

/* WARNING: Unknown calling convention yet parameter storage is locked */

void HandleThrownBombs(void)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	long lVar2;
	int iVar3;
	ulong uVar4;
	uint uVar5;
	int iVar6;
	int in_a0;
	VECTOR *pos;
	_CAR_DATA *cp;
	BOMB *pBVar7;
	int iVar8;
	undefined4 in_stack_ffffffcc;
	int local_30;
	undefined4 in_stack_ffffffd4;

	if (gBombTargetVehicle != (_CAR_DATA *)0x0) {
		ThrownBombDelay = ThrownBombDelay + -1;
		if (ThrownBombDelay == -1) {
			lVar2 = Random2(in_a0);
			iVar8 = CurrentBomb;
			pBVar7 = &ThrownBombs + CurrentBomb;
			ThrownBombDelay = lVar2 % 0x2d + 8;
			CurrentBomb = (CurrentBomb + 1) % 5;
			pBVar7->flags = '\x01';
			(&ThrownBombs)[iVar8].active = '\x01';
			cp = gBombTargetVehicle;
			(&ThrownBombs)[iVar8].position.vx = (gBombTargetVehicle->hd).where.t[0];
			(&ThrownBombs)[iVar8].position.vy = (cp->hd).where.t[1] + -200;
			(&ThrownBombs)[iVar8].position.vz = (cp->hd).where.t[2];
			iVar6 = *(int *)(cp->st + 0x1c);
			if (iVar6 < 0) {
				iVar6 = iVar6 + 0xfff;
			}
			local_30 = iVar6 >> 0xc;
			iVar3 = *(int *)(cp->st + 0x24);
			if (iVar3 < 0) {
				iVar3 = iVar3 + 0xfff;
			}
			(&ThrownBombs)[iVar8].velocity.vx = iVar6 >> 0x16;
			(&ThrownBombs)[iVar8].velocity.vz = iVar3 >> 0x16;
			uVar4 = Long2DDistance(&(&ThrownBombs)[iVar8].position,
				(VECTOR *)car_data[player.playerCarId].hd.where.t);
			(&ThrownBombs)[iVar8].velocity.vy = -(uVar4 >> 7);
			uVar5 = rand();
			if ((uVar5 & 1) == 0) {
				(&ThrownBombs)[iVar8].rot_speed = -*(short *)&(&ThrownBombs)[iVar8].velocity.vy;
			}
			else {
				(&ThrownBombs)[iVar8].rot_speed = *(short *)&(&ThrownBombs)[iVar8].velocity.vy;
			}
			if ((&ThrownBombs)[iVar8].velocity.vy < -100) {
				(&ThrownBombs)[iVar8].velocity.vy = -100;
			}
		}
		pBVar7 = &ThrownBombs;
		iVar8 = 0;
		do {
			if ((pBVar7->flags & 1) != 0) {
				pos = &pBVar7->position;
				iVar3 = (pBVar7->velocity).vy;
				(pBVar7->position).vx = (pBVar7->position).vx + (pBVar7->velocity).vx;
				iVar6 = (pBVar7->velocity).vz;
				uVar1 = pBVar7->active;
				(pBVar7->position).vy = (pBVar7->position).vy + iVar3;
				(pBVar7->position).vz = (pBVar7->position).vz + iVar6;
				(pBVar7->velocity).vy = iVar3 + 10;
				pBVar7->active = uVar1 + '\x01';
				iVar6 = MapHeight(pos);
				iVar6 = -iVar6;
				if (iVar6 < (pBVar7->position).vy) {
					if ((pBVar7->flags & 2) == 0) {
						iVar3 = (pBVar7->velocity).vy;
						pBVar7->flags = pBVar7->flags | 2;
						(pBVar7->position).vy = iVar6;
						(pBVar7->velocity).vy = -iVar3 / 2;
					}
					else {
						pBVar7->flags = '\0';
						(pBVar7->position).vy = iVar6;
						AddExplosion((VECTOR)CONCAT412(in_stack_ffffffd4,
							CONCAT48(local_30, CONCAT44(in_stack_ffffffcc, 1))),
							(pBVar7->position).vx);
						AddFlash(pos);
						iVar3 = (pBVar7->position).vx - player.pos[0];
						iVar6 = (pBVar7->position).vz - player.pos[2];
						if (iVar3 * iVar3 + iVar6 * iVar6 >> 0xc < 0x400) {
							SetPadVibration((int)**(char **)car_data[player.playerCarId].ai, '\x03');
						}
					}
				}
				cp = car_data;
				do {
					if (((cp != gBombTargetVehicle) && (cp->controlType != '\0')) &&
						(iVar6 = BombCollisionCheck(cp, pos), iVar6 != 0)) {
						pBVar7->flags = '\0';
						AddExplosion((VECTOR)(ZEXT1216(CONCAT48(in_stack_ffffffd4,
							CONCAT44(local_30, in_stack_ffffffcc))) << 0x20),
							(pBVar7->position).vx);
						AddFlash(pos);
					}
					cp = cp + 1;
				} while (cp < car_data + 0x14);
			}
			pBVar7 = pBVar7 + 1;
			iVar8 = iVar8 + 1;
		} while (iVar8 < 5);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawThrownBombs()
 // line 381, offset 0x0001e810
	/* begin block 1 */
		// Start line: 383
		// Start offset: 0x0001E810
		// Variables:
	// 		struct MATRIX object_matrix; // stack offset -80
	// 		struct MATRIX *finalmatrix; // $s2
	// 		struct BOMB *bomb; // $s0
	// 		struct VECTOR pos; // stack offset -48
	// 		int i; // $s3

		/* begin block 1.1 */
			// Start line: 397
			// Start offset: 0x0001E86C
		/* end block 1.1 */
		// End offset: 0x0001E998
		// End Line: 414

		/* begin block 1.2 */
			// Start line: 420
			// Start offset: 0x0001E9B4
		/* end block 1.2 */
		// End offset: 0x0001E9DC
		// End Line: 424
	/* end block 1 */
	// End offset: 0x0001E9DC
	// End Line: 425

	/* begin block 2 */
		// Start line: 864
	/* end block 2 */
	// End Line: 865

	/* begin block 3 */
		// Start line: 865
	/* end block 3 */
	// End Line: 866

	/* begin block 4 */
		// Start line: 871
	/* end block 4 */
	// End Line: 872

/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawThrownBombs(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	BOMB *pBVar2;
	int iVar3;
	undefined4 local_50;
	undefined4 local_4c;
	undefined4 local_48;
	undefined4 local_44;
	undefined4 local_40;
	int local_30;
	long local_2c;
	int local_28;

	if (gBombModel != (MODEL *)0x0) {
		pBVar2 = &ThrownBombs;
		iVar3 = 4;
		do {
			if ((pBVar2->flags & 1) != 0) {
				local_50 = 0x1000;
				local_44 = 0;
				local_4c = 0;
				local_48 = 0x1000;
				local_40 = CONCAT22(local_40._2_2_, 0x1000);
				RotMatrixY((int)pBVar2->rot_speed * (uint)pBVar2->active * 3 & 0xfff, &local_50);
				RotMatrixZ((int)pBVar2->rot_speed * (uint)pBVar2->active & 0xfff, &local_50);
				local_30 = (pBVar2->position).vx - camera_position.vx;
				local_2c = (pBVar2->position).vy - camera_position.vy;
				local_28 = (pBVar2->position).vz - camera_position.vz;
				Apply_Inv_CameraMatrix(&local_30);
				setCopControlWord(2, 0, local_50);
				setCopControlWord(2, 0x800, local_4c);
				setCopControlWord(2, 0x1000, local_48);
				setCopControlWord(2, 0x1800, local_44);
				setCopControlWord(2, 0x2000, local_40);
				setCopControlWord(2, 0x2800, local_30);
				setCopControlWord(2, 0x3000, local_2c);
				setCopControlWord(2, 0x3800, local_28);
				local_30 = (pBVar2->position).vx;
				local_2c = (pBVar2->position).vy;
				local_28 = (pBVar2->position).vz;
				SetFrustrumMatrix();
				iVar1 = FrustrumCheck(&local_30, (int)gBombModel->bounding_sphere);
				if (iVar1 != -1) {
					PlotMDL_less_than_128(gBombModel);
				}
			}
			iVar3 = iVar3 + -1;
			pBVar2 = pBVar2 + 1;
		} while (-1 < iVar3);
		if (gWantFlash != 0) {
			add_haze(flashval, flashval, 7);
			flashval = flashval + -10;
			if (flashval < 1) {
				gWantFlash = 0;
			}
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ BombThePlayerToHellAndBack(int car /*$s3*/)
 // line 432, offset 0x0001ea00
	/* begin block 1 */
		// Start line: 433
		// Start offset: 0x0001EA00
		// Variables:
	// 		struct BOMB *bomb; // $t3
	/* end block 1 */
	// End offset: 0x0001EC3C
	// End Line: 486

	/* begin block 2 */
		// Start line: 1001
	/* end block 2 */
	// End Line: 1002

void BombThePlayerToHellAndBack(int car)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	ushort uVar2;
	int iVar3;
	int iVar4;
	long lVar5;
	long *plVar6;
	long *plVar7;
	BOMB *pBVar8;
	long *plVar9;

	if (car != -1) {
		car_data[car].ap.damage[0] = 0xfff;
		car_data[car].ap.damage[1] = 0xfff;
		car_data[car].ap.damage[2] = 0xfff;
		car_data[car].ap.damage[3] = 0xfff;
		car_data[car].ap.damage[4] = 0xfff;
		car_data[car].ap.damage[5] = 0xfff;
		uVar2 = (ushort)MaxPlayerDamage;
		car_data[car].ap.needsDenting = '\x01';
		car_data[car].totalDamage = uVar2;
		DentCar(car_data + car);
		iVar1 = CurrentBomb;
		if (maxCivCars == 0) {
			trap(7);
		}
		gBombTargetVehicle = car_data + (car + 1) % maxCivCars;
		plVar7 = car_data[car].hd.where.t;
		pBVar8 = &ThrownBombs + CurrentBomb;
		CurrentBomb = (CurrentBomb + 1) % 5;
		plVar6 = car_data[car].hd.where.t + 1;
		plVar9 = car_data[car].hd.where.t + 2;
		pBVar8->flags = '\x01';
		(&ThrownBombs)[iVar1].active = '\x01';
		iVar3 = CurrentBomb;
		(&ThrownBombs)[iVar1].position.vx = *plVar7;
		(&ThrownBombs)[iVar1].position.vy = *plVar6;
		lVar5 = *plVar9;
		(&ThrownBombs)[iVar1].velocity.vx = 0;
		(&ThrownBombs)[iVar1].velocity.vy = 0;
		(&ThrownBombs)[iVar1].velocity.vz = 0;
		(&ThrownBombs)[iVar1].position.vz = lVar5;
		pBVar8 = &ThrownBombs + CurrentBomb;
		CurrentBomb = (CurrentBomb + 1) % 5;
		pBVar8->flags = '\x01';
		(&ThrownBombs)[iVar3].active = '\x01';
		iVar1 = CurrentBomb;
		(&ThrownBombs)[iVar3].position.vx = *plVar7 + 0xaa;
		(&ThrownBombs)[iVar3].position.vy = *plVar6;
		iVar4 = *plVar9;
		(&ThrownBombs)[iVar3].velocity.vx = 0;
		(&ThrownBombs)[iVar3].velocity.vy = 0;
		(&ThrownBombs)[iVar3].velocity.vz = 0;
		(&ThrownBombs)[iVar3].position.vz = iVar4 + 0x49;
		pBVar8 = &ThrownBombs + CurrentBomb;
		CurrentBomb = (CurrentBomb + 1) % 5;
		pBVar8->flags = '\x01';
		(&ThrownBombs)[iVar1].active = '\x01';
		(&ThrownBombs)[iVar1].position.vx = *plVar7 + -0x6d;
		(&ThrownBombs)[iVar1].position.vy = *plVar6;
		iVar3 = *plVar9;
		(&ThrownBombs)[iVar1].velocity.vx = 0;
		(&ThrownBombs)[iVar1].velocity.vy = 0;
		(&ThrownBombs)[iVar1].velocity.vz = 0;
		(&ThrownBombs)[iVar1].position.vz = iVar3 + -0x93;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ BombCollisionCheck(struct _CAR_DATA *cp /*$a0*/, struct VECTOR *pPos /*$a1*/)
 // line 496, offset 0x0001ec58
	/* begin block 1 */
		// Start line: 497
		// Start offset: 0x0001EC58
		// Variables:
	// 		struct CDATA2D cd[2]; // stack offset -216
	// 		int carLength[2]; // stack offset -16

		/* begin block 1.1 */
			// Start line: 497
			// Start offset: 0x0001EC58
		/* end block 1.1 */
		// End offset: 0x0001EC58
		// End Line: 497
	/* end block 1 */
	// End offset: 0x0001ED18
	// End Line: 523

	/* begin block 2 */
		// Start line: 1230
	/* end block 2 */
	// End Line: 1231

	/* begin block 3 */
		// Start line: 1235
	/* end block 3 */
	// End Line: 1236

int BombCollisionCheck(_CAR_DATA *cp, VECTOR *pPos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint uVar1;
	int iVar2;
	CDATA2D local_d8;
	long local_74;
	long local_6c;
	int local_34;
	int local_30;
	int local_2c;
	int local_c;

	uVar1 = (uint)(byte)(cp->ap).model;
	local_34 = (cp->hd).direction;
	local_30 = (int)car_cosmetics[uVar1].colBox.vz;
	local_2c = (int)car_cosmetics[uVar1].colBox.vx;
	local_74 = (cp->hd).where.t[0];
	local_6c = (cp->hd).where.t[2];
	local_d8.x.vx = pPos->vx;
	local_d8.x.vz = pPos->vz;
	local_d8.length[0] = 0x28;
	local_d8.length[1] = 0x28;
	local_d8.theta = 0;
	local_d8.avel = 0;
	local_d8.vel.vx = 0;
	local_d8.vel.vy = 0;
	local_d8.vel.vz = 0;
	local_c = local_30;
	iVar2 = bcollided2d(&local_d8, 1);
	return (uint)(iVar2 != 0);
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ExplosionCollisionCheck(struct _CAR_DATA *cp /*$s1*/, struct _ExOBJECT *pE /*$s3*/)
 // line 534, offset 0x0001ed18
	/* begin block 1 */
		// Start line: 535
		// Start offset: 0x0001ED18
		// Variables:
	// 		struct CDATA2D cd[2]; // stack offset -352
	// 		int carLength[2]; // stack offset -152
	// 		static int setUsed; // offset 0x28
	// 		int tanner; // $s6

		/* begin block 1.1 */
			// Start line: 546
			// Start offset: 0x0001ED74

			/* begin block 1.1.1 */
				// Start line: 546
				// Start offset: 0x0001ED74
			/* end block 1.1.1 */
			// End offset: 0x0001ED74
			// End Line: 546

			/* begin block 1.1.2 */
				// Start line: 553
				// Start offset: 0x0001EE0C
			/* end block 1.1.2 */
			// End offset: 0x0001EE80
			// End Line: 558

			/* begin block 1.1.3 */
				// Start line: 561
				// Start offset: 0x0001EE80
				// Variables:
			// 		int x; // $a1
			// 		int z; // $v1
			// 		struct VECTOR *pos; // $v0
			/* end block 1.1.3 */
			// End offset: 0x0001EF54
			// End Line: 600

			/* begin block 1.1.4 */
				// Start line: 623
				// Start offset: 0x0001EF94
				// Variables:
			// 		struct CRET2D collisionResult; // stack offset -144

				/* begin block 1.1.4.1 */
					// Start line: 626
					// Start offset: 0x0001EF94
					// Variables:
				// 		struct VECTOR velocity; // stack offset -104
				// 		long pointVel[4]; // stack offset -88
				// 		long reaction[4]; // stack offset -72
				// 		long lever[4]; // stack offset -56
				// 		int strikeVel; // $s0

					/* begin block 1.1.4.1.1 */
						// Start line: 688
						// Start offset: 0x0001F210
					/* end block 1.1.4.1.1 */
					// End offset: 0x0001F250
					// End Line: 695

					/* begin block 1.1.4.1.2 */
						// Start line: 698
						// Start offset: 0x0001F250
						// Variables:
					// 		int twistY; // $a1
					// 		int lever_dot_n; // $a0
					// 		int displacementsquared; // $v1
					// 		int denom; // $v1
					/* end block 1.1.4.1.2 */
					// End offset: 0x0001F360
					// End Line: 710
				/* end block 1.1.4.1 */
				// End offset: 0x0001F4A8
				// End Line: 732
			/* end block 1.1.4 */
			// End offset: 0x0001F4A8
			// End Line: 733
		/* end block 1.1 */
		// End offset: 0x0001F4A8
		// End Line: 734
	/* end block 1 */
	// End offset: 0x0001F4F4
	// End Line: 740

	/* begin block 2 */
		// Start line: 1339
	/* end block 2 */
	// End Line: 1340

	/* begin block 3 */
		// Start line: 1351
	/* end block 3 */
	// End Line: 1352

/* WARNING: Removing unreachable block (ram,0x0001ef54) */

void ExplosionCollisionCheck(_CAR_DATA *cp, _ExOBJECT *pE)
{
	UNIMPLEMENTED();
	/*
	ExplosionType EVar1;
	bool bVar2;
	uint uVar3;
	_PLAYER *p_Var4;
	int strikeVel;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	CDATA2D local_160;
	long local_fc;
	long local_f4;
	int local_bc;
	int local_b8;
	int local_b4;
	int local_94;
	CRET2D local_90;
	VECTOR local_68;
	int local_58;
	int local_54;
	int local_50;
	int local_38;
	int local_34;
	int local_30;

	bVar2 = cp != car_data + 0x14;
	if ((player.playerType == '\x02') || (bVar2)) {
		uVar3 = (uint)(byte)(cp->ap).model;
		local_fc = (cp->hd).where.t[0];
		local_b8 = (int)car_cosmetics[uVar3].colBox.vz;
		local_b4 = (int)car_cosmetics[uVar3].colBox.vx;
		local_bc = (cp->hd).direction;
		local_f4 = (cp->hd).where.t[2];
		if (pE->type < 2) {
			strikeVel = pE->speed;
			if (strikeVel == 0) {
				trap(7);
			}
			if (strikeVel == 0) {
				trap(7);
			}
			if (0x1000 / strikeVel == 0) {
				trap(7);
			}
			local_160.length[1] =
				minBoxSize + ((pE->time / strikeVel) * littleBoxRange) / (0x1000 / strikeVel);
		}
		else {
			if (pE->type == HEY_MOMMA) {
				p_Var4 = (_PLAYER *)(cp->hd).where.t;
				if (!bVar2) {
					p_Var4 = &player;
				}
				strikeVel = (pE->pos).vx;
				local_160.length[1] = strikeVel - p_Var4->pos[0];
				if (local_160.length[1] < 0) {
					local_160.length[1] = p_Var4->pos[0] - strikeVel;
				}
				iVar5 = (pE->pos).vz;
				strikeVel = iVar5 - p_Var4->pos[2];
				if (strikeVel < 0) {
					strikeVel = p_Var4->pos[2] - iVar5;
				}
				if (local_160.length[1] < strikeVel) {
					local_160.length[1] = strikeVel;
				}
				if (local_160.length[1] < 3000) {
					if (bVar2) {
						if ((int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2 == (int)player.playerCarId) {
							cp->totalDamage = (ushort)MaxPlayerDamage;
							player.dying = '\x01';
							lockAllTheDoors = '\x01';
						}
					}
					else {
						bKillTanner = 1;
						player.dying = '\x01';
					}
				}
				else {
					local_160.length[1] = 10;
				}
			}
			else {
				local_160.length[1] = 0;
			}
		}
		local_160.x.vx = (pE->pos).vx;
		local_160.x.vz = (pE->pos).vz;
		local_160.theta = 0;
		local_160.avel = 0;
		local_160.vel.vx = 0;
		local_160.vel.vy = 0;
		local_160.vel.vz = 0;
		local_160.length[0] = local_160.length[1];
		local_94 = local_b8;
		strikeVel = bcollided2d(&local_160, 1);
		if (strikeVel != 0) {
			bFindCollisionPoint(&local_160, &local_90);
			iVar8 = *(int *)(cp->st + 0x2c);
			iVar7 = (cp->hd).where.t[2] + (local_90.penetration * local_90.surfNormal.vz + 0x800 >> 0xc);
			local_30 = local_90.hit.vz - iVar7;
			local_34 = (cp->hd).where.t[1];
			local_90.hit.vy = local_34 + 0x3c;
			iVar5 = *(int *)(cp->st + 0x30);
			local_34 = local_90.hit.vy - local_34;
			iVar6 = (cp->hd).where.t[0] + (local_90.penetration * local_90.surfNormal.vx + 0x800 >> 0xc);
			local_38 = local_90.hit.vx - iVar6;
			strikeVel = *(int *)(cp->st + 0x28);
			local_90.surfNormal.vy = 0;
			(cp->hd).where.t[2] = iVar7;
			(cp->hd).where.t[0] = iVar6;
			local_58 = ((iVar8 * local_30 - iVar5 * local_34) + 0x800 >> 0xc) + *(int *)(cp->st + 0x1c);
			local_54 = ((iVar5 * local_38 - strikeVel * local_30) + 0x800 >> 0xc) +
				*(int *)(cp->st + 0x20);
			local_50 = ((strikeVel * local_34 - iVar8 * local_38) + 0x800 >> 0xc) +
				*(int *)(cp->st + 0x24);
			EVar1 = pE->type;
			if (EVar1 == LITTLE_BANG) {
				strikeVel = pE->speed;
				if (strikeVel == 0) {
					trap(7);
				}
				if (strikeVel == 0) {
					trap(7);
				}
				if (0x1000 / strikeVel == 0) {
					trap(7);
				}
				strikeVel = halfStrike - ((pE->time / strikeVel) * halfStrike) / (0x1000 / strikeVel);
			}
			else {
				if (EVar1 < 2) {
					strikeVel = fullStrike;
					if (EVar1 != BIG_BANG) {
						strikeVel = 0;
					}
				}
				else {
					strikeVel = 0;
					if (EVar1 == HEY_MOMMA) {
						strikeVel = fullStrike << 1;
					}
				}
			}
			DAT_000aa0ec = 1;
			if (0 < strikeVel) {
				local_68.vx = *(int *)(cp->st + 0x1c);
				local_90.hit.vy = -local_90.hit.vy;
				if (local_68.vx < 0) {
					local_68.vx = local_68.vx + 0xfff;
				}
				local_68.vx = local_68.vx >> 0xc;
				local_68.vz = *(int *)(cp->st + 0x24);
				local_68.vy = -0x11;
				if (local_68.vz < 0) {
					local_68.vz = local_68.vz + 0xfff;
				}
				local_68.vz = local_68.vz >> 0xc;
				if (0x3600 < strikeVel) {
					local_90.hit.vy = local_90.hit.vy + 0x1e;
					local_68.vy = -0x25;
					Setup_Sparks((VECTOR *)&local_90, &local_68, 4, '\0');
					local_90.hit.vy = local_90.hit.vy + -0x1e;
					local_68.vy = local_68.vy + 0x14;
					if (0x1b000 < strikeVel) {
						iVar5 = GetDebrisColour(cp);
						Setup_Debris((VECTOR *)&local_90, &local_68, 6, iVar5 << 0x10);
						if (cp->controlType == '\x01') {
							SetPadVibration((int)**(char **)cp->ai, '\x01');
						}
					}
				}
				DamageCar(cp, &local_160, &local_90, strikeVel);
				iVar5 = local_38 * local_90.surfNormal.vx + local_34 * local_90.surfNormal.vy +
					local_30 * local_90.surfNormal.vz + 0x800 >> 0xc;
				iVar5 = (((local_38 * local_38 + local_30 * local_30) - iVar5 * iVar5) *
					(int)car_cosmetics[(byte)(cp->ap).model].twistRateY + 0x800 >> 0xc) + 0x1000;
				if (strikeVel < 0x7f001) {
					strikeVel = (strikeVel << 0xc) / iVar5;
					if (iVar5 == 0) {
						trap(7);
					}
				}
				else {
					if (iVar5 == 0) {
						trap(7);
					}
					strikeVel = strikeVel / iVar5 << 0xc;
				}
				if (strikeVel < 0) {
					strikeVel = strikeVel + 0x3f;
				}
				strikeVel = strikeVel >> 6;
				if (local_90.surfNormal.vx < 0) {
					local_90.surfNormal.vx = local_90.surfNormal.vx + 0x3f;
				}
				iVar5 = strikeVel * (local_90.surfNormal.vx >> 6);
				if (local_90.surfNormal.vy < 0) {
					local_90.surfNormal.vy = local_90.surfNormal.vy + 0x3f;
				}
				iVar6 = strikeVel * (local_90.surfNormal.vy >> 6);
				if (local_90.surfNormal.vz < 0) {
					local_90.surfNormal.vz = local_90.surfNormal.vz + 0x3f;
				}
				strikeVel = strikeVel * (local_90.surfNormal.vz >> 6);
				*(int *)(cp->st + 0x1c) = *(int *)(cp->st + 0x1c) + iVar5;
				*(int *)(cp->st + 0x20) = *(int *)(cp->st + 0x20) + iVar6;
				*(int *)(cp->st + 0x24) = *(int *)(cp->st + 0x24) + strikeVel;
				(cp->hd).aacc[2] =
					((cp->hd).aacc[2] + (local_38 * iVar6 + 0x800 >> 0xc)) -
					(local_34 * iVar5 + 0x800 >> 0xc);
				(cp->hd).aacc[0] =
					((cp->hd).aacc[0] + (local_34 * strikeVel + 0x800 >> 0xc)) -
					(local_30 * iVar6 + 0x800 >> 0xc);
				(cp->hd).aacc[1] =
					((cp->hd).aacc[1] + (local_30 * iVar5 + 0x800 >> 0xc)) -
					(local_38 * strikeVel + 0x800 >> 0xc);
			}
		}
		if (bVar2) {
			return;
		}
	}
	if (DAT_000aa0ec != 0) {
		pE->type = BANG_USED;
		DAT_000aa0ec = 0;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddFlash(struct VECTOR *pos /*$a0*/)
 // line 747, offset 0x0001f4f4
	/* begin block 1 */
		// Start line: 748
		// Start offset: 0x0001F4F4
		// Variables:
	// 		int dist; // $a0
	/* end block 1 */
	// End offset: 0x0001F570
	// End Line: 761

	/* begin block 2 */
		// Start line: 1947
	/* end block 2 */
	// End Line: 1948

	/* begin block 3 */
		// Start line: 1955
	/* end block 3 */
	// End Line: 1956

	/* begin block 4 */
		// Start line: 1958
	/* end block 4 */
	// End Line: 1959

void AddFlash(VECTOR *pos)
{
	UNIMPLEMENTED();
	/*
	ulong uVar1;
	_PLAYER *pPoint2;

	if (NoPlayerControl == 0) {
		pPoint2 = &player;
	}
	else {
		pPoint2 = (_PLAYER *)&player.cameraPos;
	}
	uVar1 = Long2DDistance(pos, (VECTOR *)pPoint2);
	if ((int)uVar1 < 0x9c4) {
		gWantFlash = 1;
		flashval = 0x96 - (int)uVar1 / 0x14;
	}
	return;*/
}





