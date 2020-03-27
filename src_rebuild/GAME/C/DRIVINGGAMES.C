#include "THISDUST.H"
#include "DRIVINGGAMES.H"


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

void InitDrivingGames(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  SMASHED_CONE *pSVar4;
  int iVar5;
  char acStack72 [64];
  
  gPlayerScore.time = 0;
  gTrailblazerData = (TRAILBLAZER_DATA *)0x0;
  gPlayerScore.items = 0;
  gPlayerScore.P2time = 0;
  gPlayerScore.P2items = 0;
  if ((GameType == GAME_GATERACE) || (GameType == GAME_TRAILBLAZER)) {
    if ((uint)CutsceneBuffer.bytesFree < 0x4b0) {
      while (FrameCnt != 0x78654321) {
        trap(0x400);
      }
    }
    gTrailblazerConeCount = 0;
    gTrailblazerConeIndex = 0;
    gTrailblazerData = (TRAILBLAZER_DATA *)CutsceneBuffer.currentPointer;
    CutsceneBuffer.bytesFree = CutsceneBuffer.bytesFree + -0x4b0;
    sprintf(acStack72,s_TRAILS_TRAIL__d_00010854,gCurrentMissionNumber);
    iVar1 = FileExists(acStack72);
    if (iVar1 != 0) {
      Loadfile(acStack72,(char *)gTrailblazerData);
    }
  }
  iVar1 = 0;
  iVar5 = 0;
  do {
    iVar3 = 5;
    puVar2 = (undefined4 *)((int)&DAT_000cd9bc + iVar5);
    do {
      *puVar2 = 0;
      iVar3 = iVar3 + -1;
      puVar2 = puVar2 + -1;
    } while (-1 < iVar3);
    iVar1 = iVar1 + 1;
    iVar5 = iVar5 + 0x18;
  } while (iVar1 < 2);
  pSVar4 = smashed_cones;
  iVar1 = 5;
  do {
    iVar1 = iVar1 + -1;
    *(uint *)pSVar4 = *(uint *)pSVar4 & 0xffff80ff;
    pSVar4->cone = -1;
    pSVar4 = (SMASHED_CONE *)&(pSVar4->velocity).pad;
  } while (-1 < iVar1);
  current_smashed_cone = 0;
  gTrailblazerPrevConeDelay = 0;
  return;
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

void HandleDrivingGames(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  TRAILBLAZER_DATA *pTVar6;
  int player;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  VECTOR local_60;
  VECTOR VStack80;
  VECTOR VStack64;
  VECTOR *local_30;
  VECTOR *local_2c;
  
  if (0 < gTrailblazerPrevConeDelay) {
    gTrailblazerPrevConeDelay = gTrailblazerPrevConeDelay + -1;
  }
  if (GameType == GAME_GATERACE) {
    if (gTrailblazerData == (TRAILBLAZER_DATA *)0x0) goto LAB_0004386c;
    MoveSmashedCones();
    local_30 = &VStack80;
    if (NumPlayers != 0) {
      local_2c = &VStack64;
      player = 0;
LAB_0004330c:
      iVar10 = 0;
      iVar12 = player + 1;
      piVar11 = wrongside + player * 6;
LAB_0004333c:
      if (99 < gTrailblazerConeIndex + iVar10) goto LAB_00043658;
      GetConePos(gTrailblazerConeIndex + iVar10,local_30,0);
      GetConePos(gTrailblazerConeIndex + iVar10,local_2c,1);
      iVar5 = CarConeCollision(local_30,(int)(&player)[player].playerCarId);
      uVar9 = (uint)(iVar5 != 0);
      iVar3 = CarConeCollision(local_2c,(int)(&player)[player].playerCarId);
      iVar5 = gTrailblazerConeIndex;
      if (iVar3 != 0) {
        uVar9 = 2;
      }
      if (uVar9 == 0) {
        pTVar6 = gTrailblazerData + gTrailblazerConeIndex + iVar10;
        uVar9 = (int)pTVar6->rot & 0xfff;
        iVar8 = (&player)[player].pos[0] - pTVar6->x;
        iVar3 = (&player)[player].pos[2] - pTVar6->z;
        if (iVar8 * rcossin_tbl[uVar9 * 2] + iVar3 * rcossin_tbl[uVar9 * 2 + 1] < 1) {
          *piVar11 = 1;
          goto LAB_00043658;
        }
        iVar8 = iVar8 * rcossin_tbl[uVar9 * 2 + 1];
        if (wrongside[player * 6 + iVar10] == 0) goto LAB_00043658;
        iVar3 = iVar3 * rcossin_tbl[uVar9 * 2];
        iVar7 = iVar8 - iVar3;
        wrongside[player * 6 + iVar10] = 0;
        if (iVar7 < 0) {
          iVar7 = iVar3 - iVar8;
        }
        if ((600 - (iVar5 * 400 + iVar10) / 100) * 0x1000 <= iVar7) goto LAB_00043658;
        gTrailblazerConeIndex = iVar5 + 1 + iVar10;
        gTrailblazerPrevConeDelay = 10;
        gTrailblazerConeCount = gTrailblazerConeCount + 1;
        (&DAT_000d7c2c)[player * 3] = (&DAT_000d7c2c)[player * 3] + 3000;
        if (player == 0) {
          gPlayerScore.items = gPlayerScore.items + 1;
        }
        else {
          gPlayerScore.P2items = gPlayerScore.P2items + 1;
        }
        player = 0;
        iVar10 = 1;
        do {
          iVar5 = 5;
          puVar4 = &DAT_000cd9bc + player * 6;
          do {
            *puVar4 = 0;
            iVar5 = iVar5 + -1;
            puVar4 = puVar4 + -1;
          } while (-1 < iVar5);
          bVar2 = iVar10 < 2;
          player = iVar10;
          iVar10 = iVar10 + 1;
        } while (bVar2);
      }
      else {
        local_60.vx = *(int *)(car_data[(&player)[player].playerCarId].st + 0x1c);
        if (local_60.vx < 0) {
          local_60.vx = local_60.vx + 0xfff;
        }
        local_60.vx = local_60.vx >> 0xc;
        local_60.vy = -0x11;
        local_60.vz = *(int *)(car_data[(&player)[player].playerCarId].st + 0x24);
        if (local_60.vz < 0) {
          local_60.vz = local_60.vz + 0xfff;
        }
        local_60.vz = local_60.vz >> 0xc;
        SetSmashedCone(gTrailblazerConeIndex + iVar10,&local_60,player,uVar9 - 1);
        gTrailblazerConeIndex = gTrailblazerConeIndex + 1 + iVar10;
        (&DAT_000d7c2c)[player * 3] = (&DAT_000d7c2c)[player * 3] + -3000;
        SetPlayerMessage(player,s__1_secondo_00010864,2,1);
      }
      goto LAB_00043668;
    }
  }
  else {
    if ((GameType != GAME_TRAILBLAZER) || (gTrailblazerData == (TRAILBLAZER_DATA *)0x0))
    goto LAB_0004386c;
    MoveSmashedCones();
    if (NumPlayers != 0) {
      player = 0;
      do {
        iVar10 = 0;
        iVar12 = player + 1;
        do {
          if (gTrailblazerConeIndex + iVar10 < 100) {
            GetConePos(gTrailblazerConeIndex + iVar10,&VStack80,-1);
            iVar5 = CarConeCollision(&VStack80,(int)(&player)[player].playerCarId);
            if (iVar5 != 0) {
              cVar1 = (&player)[player].playerCarId;
              (&DAT_000d7c2c)[player * 3] = (&DAT_000d7c2c)[player * 3] + 3000;
              local_60.vx = *(int *)(car_data[cVar1].st + 0x1c);
              if (local_60.vx < 0) {
                local_60.vx = local_60.vx + 0xfff;
              }
              local_60.vx = local_60.vx >> 0xc;
              local_60.vy = -0x11;
              local_60.vz = *(int *)(car_data[cVar1].st + 0x24);
              if (local_60.vz < 0) {
                local_60.vz = local_60.vz + 0xfff;
              }
              local_60.vz = local_60.vz >> 0xc;
              SetSmashedCone(gTrailblazerConeIndex + iVar10,&local_60,player,0);
              gTrailblazerConeCount = gTrailblazerConeCount + 1;
              gTrailblazerConeIndex = gTrailblazerConeIndex + 1 + iVar10;
              if (player == 0) {
                gPlayerScore.items = gPlayerScore.items + 1;
              }
              else {
                gPlayerScore.P2items = gPlayerScore.P2items + 1;
              }
            }
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < 6);
        player = iVar12;
      } while (iVar12 < (int)(uint)NumPlayers);
    }
  }
LAB_00043828:
  if (gTrailblazerConeIndex == 100) {
    (MissionTargets + NumPlayers)[-1].data[1] = (MissionTargets + NumPlayers)[-1].data[1] | 0x102;
  }
LAB_0004386c:
  if (DAT_000d7c2c < 0) {
    DAT_000d7c2c = 0;
  }
  if (DAT_000d7c38 < 0) {
    DAT_000d7c38 = 0;
  }
  gPlayerScore.time = DAT_000d7c2c;
  gPlayerScore.P2time = DAT_000d7c38;
  return;
LAB_00043658:
  iVar10 = iVar10 + 1;
  piVar11 = piVar11 + 1;
  if (5 < iVar10) goto LAB_00043668;
  goto LAB_0004333c;
LAB_00043668:
  player = iVar12;
  if ((int)(uint)NumPlayers <= iVar12) goto LAB_00043828;
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

void DrawDrivingGames(void)

{
  bool bVar1;
  int cone;
  int iVar2;
  VECTOR VStack24;
  
  if ((((GameType != GAME_GATERACE) && (GameType != GAME_TRAILBLAZER)) ||
      (gTrailblazerConeModel == (MODEL *)0x0)) || (gTrailblazerData == (TRAILBLAZER_DATA *)0x0)) {
    return;
  }
  iVar2 = 0;
  SetFrustrumMatrix();
  bVar1 = true;
  if (gTrailblazerPrevConeDelay == 0) goto LAB_000439dc;
  iVar2 = -1;
  do {
    while( true ) {
      bVar1 = iVar2 < 6;
LAB_000439dc:
      if (!bVar1) {
        DrawSmashedCones();
        return;
      }
      cone = gTrailblazerConeIndex + iVar2;
      if (cone < 100) break;
LAB_000439d4:
      iVar2 = iVar2 + 1;
    }
    if (GameType != GAME_GATERACE) {
      GetConePos(cone,&VStack24,-1);
      DrawCone(&VStack24,gTrailblazerConeIndex + iVar2);
      goto LAB_000439d4;
    }
    GetConePos(cone,&VStack24,0);
    DrawCone(&VStack24,gTrailblazerConeIndex + iVar2);
    GetConePos(gTrailblazerConeIndex + iVar2,&VStack24,1);
    DrawCone(&VStack24,gTrailblazerConeIndex + iVar2);
    iVar2 = iVar2 + 1;
  } while( true );
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

int CarConeCollision(VECTOR *pPos,int car)

{
  uint uVar1;
  int iVar2;
  CDATA2D local_d8;
  long local_74;
  long local_6c;
  int local_34;
  int local_30;
  int local_2c;
  int local_c;
  
  local_d8.x.vx = pPos->vx;
  local_d8.x.vz = pPos->vz;
  local_d8.length[0] = 0x28;
  local_d8.length[1] = 0x28;
  local_d8.theta = 0;
  if (car_data[car].controlType == '\0') {
    iVar2 = 0;
  }
  else {
    uVar1 = (uint)(byte)car_data[car].ap.model;
    local_74 = car_data[car].hd.where.t[0];
    local_30 = (int)car_cosmetics[uVar1].colBox.vz;
    local_2c = (int)car_cosmetics[uVar1].colBox.vx;
    local_34 = car_data[car].hd.direction;
    local_6c = car_data[car].hd.where.t[2];
    local_c = local_30;
    iVar2 = bcollided2d(&local_d8,1);
  }
  return iVar2;
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

void SetSmashedCone(int cone,VECTOR *velocity,int player,int side)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  int chan;
  TRAILBLAZER_DATA *pTVar4;
  int iVar5;
  uint *puVar6;
  
  chan = current_smashed_cone;
  iVar1 = current_smashed_cone + 1;
  iVar5 = current_smashed_cone * 0x14;
  puVar6 = (uint *)(&smashed_cones[0].cone + iVar5);
  current_smashed_cone = iVar1;
  if (5 < iVar1) {
    current_smashed_cone = 0;
  }
  *puVar6 = *puVar6 & 0xffff00ff | 0x100 | (side & 1U) << 0xf;
  *(char *)puVar6 = (char)cone;
  iVar1 = velocity->vx >> 10;
  *(int *)(&smashed_cones[0].rot_speed + chan * 10) = iVar1;
  *(int *)((int)&smashed_cones[0].velocity + iVar5 + 4) = velocity->vz >> 10;
  if (iVar1 < 0) {
    ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx = velocity->vx;
  }
  else {
    ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx = -velocity->vx;
  }
  if (*(int *)((int)&smashed_cones[0].velocity + iVar5 + 4) < 0) {
    lVar2 = ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx + velocity->vz;
  }
  else {
    lVar2 = ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx - velocity->vz;
  }
  ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx = lVar2;
  ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx =
       ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx >> 1;
  uVar3 = rand();
  if ((uVar3 & 1) == 0) {
    *(short *)(&smashed_cones[0].side + iVar5) =
         -*(short *)&((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx;
  }
  else {
    *(undefined2 *)(&smashed_cones[0].side + iVar5) =
         *(undefined2 *)&((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx;
  }
  if (((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx < -100) {
    ((VECTOR *)((int)&smashed_cones[0].velocity + iVar5))->vx = -100;
  }
  chan = GetFreeChannel();
  if (chan != -1) {
    if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
      SetPlayerOwnsChannel(chan,(char)player);
    }
    pTVar4 = gTrailblazerData + cone;
    Start3DSoundVolPitch(chan,1,5,pTVar4->x,(int)pTVar4->y,pTVar4->z,-2000,800);
  }
  return;
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

void MoveSmashedCones(void)

{
  TRAILBLAZER_DATA *pTVar1;
  TRAILBLAZER_DATA *pTVar2;
  SMASHED_CONE *pSVar3;
  VECTOR *pVVar4;
  int iVar5;
  
  pTVar1 = gTrailblazerData;
  if (gTrailblazerData != (TRAILBLAZER_DATA *)0x0) {
    pSVar3 = smashed_cones;
    iVar5 = 5;
    pVVar4 = &smashed_cones[0].velocity;
    do {
      if ((int)pSVar3->cone != -1) {
        pTVar2 = pTVar1 + (int)pSVar3->cone;
        if ((int)pTVar2->y < 0x32 - player.pos[1]) {
          pTVar2->x = pTVar2->x + pVVar4[-1].pad;
          pTVar2->y = pTVar2->y + *(short *)&pVVar4->vx;
          pTVar2->z = pTVar2->z + (pSVar3->velocity).vy;
          pVVar4->vx = pVVar4->vx + 10;
          *(uint *)pSVar3 =
               *(uint *)pSVar3 & 0xffff80ff | ((*(uint *)pSVar3 >> 8 & 0x7f) + 1 & 0x7f) << 8;
        }
        else {
          pSVar3->cone = -1;
          *(uint *)pSVar3 = *(uint *)pSVar3 & 0xffff80ff;
        }
      }
      pSVar3 = (SMASHED_CONE *)&(pSVar3->velocity).pad;
      iVar5 = iVar5 + -1;
      pVVar4 = (VECTOR *)&pVVar4[1].vy;
    } while (-1 < iVar5);
  }
  return;
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

void DrawSmashedCones(void)

{
  bool bVar1;
  char cVar2;
  SMASHED_CONE *sc;
  int iVar3;
  int iVar4;
  VECTOR VStack40;
  
  if (gTrailblazerData != (TRAILBLAZER_DATA *)0x0) {
    iVar4 = 0;
    iVar3 = 5;
    do {
      sc = (SMASHED_CONE *)(&smashed_cones[0].cone + iVar4);
      if ((*(uint *)sc & 0x7f00) != 0) {
        if (GameType == GAME_GATERACE) {
          bVar1 = (*(uint *)sc & 0x8000) != 0;
          if (bVar1) {
            cVar2 = sc->cone;
          }
          else {
            cVar2 = sc->cone;
          }
          GetConePos((int)cVar2,&VStack40,(uint)bVar1);
          DrawSmashedCone(sc,&VStack40);
        }
        else {
          GetConePos((int)sc->cone,&VStack40,-1);
          DrawSmashedCone(sc,&VStack40);
        }
      }
      iVar4 = iVar4 + 0x14;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
  }
  return;
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

void DrawCone(VECTOR *position,int cone)

{
  int iVar1;
  MATRIX local_40;
  VECTOR local_20;
  
  if (((gTrailblazerData != (TRAILBLAZER_DATA *)0x0) &&
      (iVar1 = PositionVisible(position), iVar1 != 0)) &&
     (iVar1 = FrustrumCheck(position,(int)gTrailblazerConeModel->bounding_sphere), iVar1 != -1)) {
    local_40.m[0][0] = 0x1000;
    local_40.m[1][1] = 0x1000;
    local_40.m[2][2] = 0x1000;
    local_40.m[1][0] = 0;
    local_40.m[2][0] = 0;
    local_40.m[0][1] = 0;
    local_40.m[2][1] = 0;
    local_40.m[0][2] = 0;
    local_40.m[1][2] = 0;
    _RotMatrixY(&local_40,gTrailblazerData[cone].rot);
    local_20.vx = position->vx - camera_position.vx;
    local_20.vy = position->vy - camera_position.vy;
    local_20.vz = position->vz - camera_position.vz;
    setCopControlWord(2,0,inv_camera_matrix.m[0]._0_4_);
    setCopControlWord(2,0x800,inv_camera_matrix.m._4_4_);
    setCopControlWord(2,0x1000,inv_camera_matrix.m[1]._2_4_);
    setCopControlWord(2,0x1800,inv_camera_matrix.m[2]._0_4_);
    setCopControlWord(2,0x2000,inv_camera_matrix._16_4_);
    _MatrixRotate(&local_20);
    RenderModel(gTrailblazerConeModel,&local_40,&local_20,0,0);
  }
  return;
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

void DrawSmashedCone(SMASHED_CONE *sc,VECTOR *wpos)

{
  int iVar1;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  int local_20;
  int local_1c;
  int local_18;
  
  local_3a = 0;
  local_34 = 0;
  local_3e = 0;
  local_32 = 0;
  local_3c = 0;
  local_36 = 0;
  local_40 = 0x1000;
  local_38 = 0x1000;
  local_30 = 0x1000;
  RotMatrixY((int)*(short *)&sc->side * (*(uint *)sc >> 8 & 0x7f) * 3 & 0xfff,&local_40);
  RotMatrixZ((int)*(short *)&sc->side * (*(uint *)sc >> 8 & 0x7f) & 0xfff,&local_40);
  local_20 = wpos->vx - camera_position.vx;
  local_1c = wpos->vy - camera_position.vy;
  local_18 = wpos->vz - camera_position.vz;
  Apply_Inv_CameraMatrix(&local_20);
  SetRotMatrix(&local_40);
  setCopControlWord(2,0x2800,local_20);
  setCopControlWord(2,0x3000,local_1c);
  setCopControlWord(2,0x3800,local_18);
  SetFrustrumMatrix();
  iVar1 = FrustrumCheck(wpos,(int)gTrailblazerConeModel->bounding_sphere);
  if (iVar1 != -1) {
    PlotMDL_less_than_128(gTrailblazerConeModel);
  }
  return;
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

void GetConePos(int cone,VECTOR *pos,int side)

{
  short sVar1;
  TRAILBLAZER_DATA *pTVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (side == -1) {
    pTVar2 = gTrailblazerData + cone;
    pos->vx = pTVar2->x;
    pos->vy = (int)pTVar2->y;
    pos->vz = pTVar2->z;
  }
  else {
    pTVar2 = gTrailblazerData + cone;
    uVar3 = (int)pTVar2->rot & 0xfff;
    iVar4 = cone * -4 + 600;
    iVar6 = iVar4 * rcossin_tbl[uVar3 * 2 + 1];
    iVar5 = pTVar2->z;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xfff;
    }
    iVar4 = -iVar4 * (int)rcossin_tbl[uVar3 * 2];
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xfff;
    }
    iVar4 = iVar4 >> 0xc;
    if (side == 0) {
      pos->vx = pTVar2->x - (iVar6 >> 0xc);
      sVar1 = pTVar2->y;
      iVar4 = -iVar4;
    }
    else {
      pos->vx = pTVar2->x + (iVar6 >> 0xc);
      sVar1 = pTVar2->y;
    }
    pos->vz = iVar5 + iVar4;
    pos->vy = (int)sVar1;
  }
  return;
}





