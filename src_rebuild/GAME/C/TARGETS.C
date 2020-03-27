#include "THISDUST.H"
#include "TARGETS.H"


SVECTOR targetArrowVerts[43] =
{
  { 65491, 65266, 0, 0 },
  { 45, 65266, 0, 0 },
  { 45, 65446, 0, 0 },
  { 90, 65446, 0, 0 },
  { 0, 0, 0, 0 },
  { 65446, 65446, 0, 0 },
  { 65491, 65446, 0, 0 },
  { 65440, 64768, 0, 0 },
  { 96, 64768, 0, 0 },
  { 96, 65320, 0, 0 },
  { 65440, 65320, 0, 0 },
  { 88, 65476, 0, 0 },
  { 36, 65528, 0, 0 },
  { 65500, 65528, 0, 0 },
  { 65448, 65476, 0, 0 },
  { 65448, 65404, 0, 0 },
  { 65500, 65352, 0, 0 },
  { 36, 65352, 0, 0 },
  { 88, 65404, 0, 0 },
  { 177, 65417, 0, 0 },
  { 73, 65521, 0, 0 },
  { 65463, 65521, 0, 0 },
  { 65359, 65417, 0, 0 },
  { 65359, 65271, 0, 0 },
  { 65463, 65167, 0, 0 },
  { 73, 65167, 0, 0 },
  { 177, 65271, 0, 0 },
  { 65488, 65152, 0, 0 },
  { 65488, 65104, 0, 0 },
  { 65440, 65104, 0, 0 },
  { 65440, 65056, 0, 0 },
  { 96, 65056, 0, 0 },
  { 96, 65104, 0, 0 },
  { 48, 65104, 0, 0 },
  { 48, 65152, 0, 0 },
  { 221, 65387, 0, 0 },
  { 91, 65517, 0, 0 },
  { 65445, 65517, 0, 0 },
  { 65315, 65387, 0, 0 },
  { 65315, 65205, 0, 0 },
  { 65445, 65075, 0, 0 },
  { 91, 65075, 0, 0 },
  { 221, 65205, 0, 0 }
};

char normalTargetArrowTris[] = { 0, 1, 2, 0, 2, 6, 5, 3, 4 };

char loseTailTargetArrowTris[] = { 7, 8, 9, 7, 9, 0xA, 0xB, 0xC, 0xD, 0xB, 0xD, 0xE };

char windowTargetArrowTris[] = {
	0x13, 0x14, 0x15, 0x13, 0x15, 0x16, 0x1A, 0x13, 0x16,
	0x1A, 0x16, 0x17, 0x19, 0x1A, 0x17, 0x19, 0x17, 0x18,
	0x1B, 0x1C, 0x22, 0x1C, 0x21, 0x22, 0x1D, 0x1E, 0x1F,
	0x1D, 0x1F, 0x20
};

char maxSpeedTargetArrowTris[] = {
	0x23, 0x24, 0x25, 0x23, 0x25, 0x26, 0x2A, 0x23, 0x26,
	0x2A, 0x26, 0x27, 0x29, 0x2A, 0x27, 0x29, 0x27, 0x28
};

TARGET_ARROW_MODEL targetArrowModel[4] =
{
  { &targetArrowVerts, &normalTargetArrowTris, sizeof(normalTargetArrowTris) / 3 },
  { &targetArrowVerts, &loseTailTargetArrowTris, sizeof(loseTailTargetArrowTris) / 3 },
  { &targetArrowVerts, &windowTargetArrowTris, sizeof(windowTargetArrowTris) / 3 },
  { &targetArrowVerts, &maxSpeedTargetArrowTris, sizeof(maxSpeedTargetArrowTris) / 3 }
};


// decompiled code
// original method signature: 
// void /*$ra*/ Draw3DTarget(struct VECTOR *position /*$s0*/, int flags /*$s2*/)
 // line 213, offset 0x0007fb44
	/* begin block 1 */
		// Start line: 214
		// Start offset: 0x0007FB44
		// Variables:
	// 		struct VECTOR pos; // stack offset -32
	// 		int shadow; // $s1
	/* end block 1 */
	// End offset: 0x0007FD48
	// End Line: 262

	/* begin block 2 */
		// Start line: 426
	/* end block 2 */
	// End Line: 427

void Draw3DTarget(VECTOR *position,int flags)

{
  uint shadow;
  VECTOR local_20;
  
  shadow = (uint)((flags & 2U) != 0);
  if ((flags & 1U) != 0) {
    local_20.vx = position->vx;
    local_20.vz = position->vz;
    local_20.pad = position->pad;
    local_20.vy = position->vy + -300 + (CameraCnt & 0xfU) * 0x10;
    if ((CurrentPlayerView != 1) || (GameType != GAME_COPSANDROBBERS)) {
      DrawTargetArrowModel(&targetArrowModel,&local_20,shadow,0);
    }
  }
  if ((flags & 0x20U) != 0) {
    local_20.vx = position->vx;
    local_20.vz = position->vz;
    local_20.pad = position->pad;
    local_20.vy = position->vy + 900 + (CameraCnt & 0xfU) * -0x10;
    if ((CurrentPlayerView != 1) || (GameType != GAME_COPSANDROBBERS)) {
      DrawTargetArrowModel(&targetArrowModel,&local_20,shadow,1);
    }
  }
  if ((flags & 4U) != 0) {
    local_20.vx = position->vx;
    local_20.vz = position->vz;
    local_20.pad = position->pad;
    local_20.vy = position->vy + -300;
    DrawTargetArrowModel(&TARGET_ARROW_MODEL_000a1e14,&local_20,shadow,0);
  }
  if ((flags & 8U) != 0) {
    local_20.vx = position->vx;
    local_20.vz = position->vz;
    local_20.pad = position->pad;
    local_20.vy = position->vy + -300;
    DrawTargetArrowModel(&TARGET_ARROW_MODEL_000a1e20,&local_20,shadow,0);
  }
  if ((flags & 0x10U) != 0) {
    local_20.vx = position->vx;
    local_20.vz = position->vz;
    local_20.pad = position->pad;
    local_20.vy = position->vy + -300;
    DrawTargetArrowModel(&TARGET_ARROW_MODEL_000a1e2c,&local_20,shadow,0);
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTargetArrowModel(struct TARGET_ARROW_MODEL *pTargetArrowModel /*$s1*/, struct VECTOR *pPosition /*$s2*/, int shadow /*$s4*/, int invert /*$s3*/)
 // line 267, offset 0x0007fd48
	/* begin block 1 */
		// Start line: 268
		// Start offset: 0x0007FD48

		/* begin block 1.1 */
			// Start line: 271
			// Start offset: 0x0007FD9C
			// Variables:
		// 		struct VECTOR tempVec; // stack offset -56
		// 		struct SVECTOR *pVerts; // $s0
		// 		struct SVECTOR temp; // stack offset -40
		// 		char *pVertIndex; // $a3

			/* begin block 1.1.1 */
				// Start line: 283
				// Start offset: 0x0007FE2C
				// Variables:
			// 		struct POLY_F3 *poly; // $t0
			// 		int z; // stack offset -32
			/* end block 1.1.1 */
			// End offset: 0x00080044
			// End Line: 323
		/* end block 1.1 */
		// End offset: 0x000800D8
		// End Line: 329
	/* end block 1 */
	// End offset: 0x000800F8
	// End Line: 330

	/* begin block 2 */
		// Start line: 555
	/* end block 2 */
	// End Line: 556

	/* begin block 3 */
		// Start line: 561
	/* end block 3 */
	// End Line: 562

void DrawTargetArrowModel
               (TARGET_ARROW_MODEL *pTargetArrowModel,VECTOR *pPosition,int shadow,int invert)

{
  ushort uVar1;
  uint uVar2;
  DB *pDVar3;
  undefined4 in_zero;
  undefined4 in_at;
  int iVar4;
  SVECTOR *pSVar5;
  VECTOR *pVVar6;
  uint uVar7;
  VECTOR *pCameraPositionOut;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  uint *puVar11;
  SVECTOR *pSVar12;
  VECTOR local_38;
  undefined4 local_28;
  uint local_24;
  int local_20;
  
  iVar4 = PositionVisible(pPosition);
  if (iVar4 != 0) {
    iVar4 = FrustrumCheck(pPosition,800);
    pCameraPositionOut = &local_38;
    if (iVar4 != -1) {
      pSVar12 = pTargetArrowModel->pVerts;
      WorldToCameraPositions(pPosition,pCameraPositionOut,1);
      setCopControlWord(2,0,norot.m[0]._0_4_);
      setCopControlWord(2,0x800,norot.m._4_4_);
      setCopControlWord(2,0x1000,norot.m[1]._2_4_);
      setCopControlWord(2,0x1800,norot.m[2]._0_4_);
      setCopControlWord(2,0x2000,norot._16_4_);
      pVVar6 = &local_38;
      setCopControlWord(2,0x2800,local_38.vx);
      setCopControlWord(2,0x3000,local_38.vy);
      setCopControlWord(2,0x3800,local_38.vz);
      uVar7 = (uint)(byte)pTargetArrowModel->numTris;
      pbVar10 = (byte *)pTargetArrowModel->pTris;
      if (pbVar10 < pbVar10 + uVar7 * 3) {
        do {
          puVar11 = (uint *)current->primptr;
          if (invert == 0) {
            setCopReg(2,in_zero,*(undefined4 *)(pSVar12 + *pbVar10));
            setCopReg(2,in_at,*(undefined4 *)&pSVar12[*pbVar10].vz);
            pSVar5 = pSVar12 + pbVar10[1];
            setCopReg(2,pSVar5,*(undefined4 *)pSVar5);
            setCopReg(2,pVVar6,*(undefined4 *)&pSVar5->vz);
            setCopReg(2,uVar7,*(undefined4 *)(pSVar12 + pbVar10[2]));
            setCopReg(2,pCameraPositionOut,*(undefined4 *)&pSVar12[pbVar10[2]].vz);
          }
          else {
            local_28 = CONCAT22(-pSVar12[*pbVar10].vy,pSVar12[*pbVar10].vx);
            pbVar8 = pbVar10 + 1;
            uVar2 = local_24 & 0xffff0000;
            local_24 = uVar2 | (ushort)pSVar12[*pbVar10].vz;
            setCopReg(2,in_zero,local_28);
            setCopReg(2,in_at,local_24);
            local_28 = CONCAT22(-pSVar12[*pbVar8].vy,pSVar12[*pbVar8].vx);
            uVar1 = pSVar12[*pbVar8].vz;
            pbVar9 = pbVar10 + 2;
            local_24 = uVar2 | uVar1;
            setCopReg(2,pSVar12 + *pbVar8,local_28);
            setCopReg(2,(uint)uVar1,local_24);
            local_28 = CONCAT22(-pSVar12[*pbVar9].vy,pSVar12[*pbVar9].vx);
            local_24 = uVar2 | (ushort)pSVar12[*pbVar9].vz;
            setCopReg(2,uVar7,local_28);
            setCopReg(2,pCameraPositionOut,local_24);
          }
          pbVar10 = pbVar10 + 3;
          copFunction(2,0x280030);
          *(char *)((int)puVar11 + 3) = '\x04';
          *(char *)((int)puVar11 + 7) = ' ';
          if (gDraw3DArrowBlue == 0) {
            *(char *)(puVar11 + 1) = -1;
            *(char *)((int)puVar11 + 5) = '\0';
          }
          else {
            *(char *)(puVar11 + 1) = '\0';
            *(char *)((int)puVar11 + 5) = -1;
          }
          *(char *)((int)puVar11 + 6) = '\0';
          uVar7 = getCopReg(2,0xc);
          puVar11[2] = uVar7;
          uVar7 = getCopReg(2,0xd);
          puVar11[3] = uVar7;
          uVar7 = getCopReg(2,0xe);
          puVar11[4] = uVar7;
          pDVar3 = current;
          local_20 = getCopReg(2,0x13);
          local_20 = local_20 >> 3;
          if (local_20 < 9) {
            local_20 = 9;
          }
          *puVar11 = *puVar11 & 0xff000000 | current->ot[local_20] & 0xffffff;
          pCameraPositionOut = (VECTOR *)(pDVar3->ot + local_20);
          pCameraPositionOut->vx = pCameraPositionOut->vx & 0xff000000U | (uint)puVar11 & 0xffffff;
          pDVar3->primptr = pDVar3->primptr + 0x14;
          uVar7 = (uint)(byte)pTargetArrowModel->numTris;
          pVVar6 = (VECTOR *)(uVar7 * 3);
        } while (pbVar10 < pTargetArrowModel->pTris + (int)pVVar6);
      }
      if (shadow != 0) {
        DrawStopZone(pPosition);
      }
    }
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawStopZone(struct VECTOR *pPosition /*$s5*/)
 // line 412, offset 0x000800f8
	/* begin block 1 */
		// Start line: 413
		// Start offset: 0x000800F8
		// Variables:
	// 		struct VECTOR *pVector; // $s0
	// 		struct VECTOR pStopZonePt[4]; // stack offset -128
	// 		struct POLY_FT4 *pPoly; // $s1
	// 		long *pOut; // $s2
	// 		long sz; // stack offset -48

		/* begin block 1.1 */
			// Start line: 430
			// Start offset: 0x000801FC
			// Variables:
		// 		struct SVECTOR temp; // stack offset -64
		// 		long p; // stack offset -56
		// 		long flag; // stack offset -52
		/* end block 1.1 */
		// End offset: 0x0008030C
		// End Line: 465
	/* end block 1 */
	// End offset: 0x0008047C
	// End Line: 489

	/* begin block 2 */
		// Start line: 890
	/* end block 2 */
	// End Line: 891

	/* begin block 3 */
		// Start line: 899
	/* end block 3 */
	// End Line: 900

void DrawStopZone(VECTOR *pPosition)

{
  bool bVar1;
  DB *pDVar2;
  ushort uVar3;
  undefined **ppuVar4;
  int iVar5;
  VECTOR *pVVar6;
  long lVar7;
  int iVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  VECTOR *pos;
  uint *puVar12;
  uint *puVar13;
  undefined *local_80;
  undefined *local_7c;
  undefined *local_78 [14];
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined auStack56 [4];
  undefined auStack52 [12];
  
  pos = (VECTOR *)&local_80;
  ppuVar4 = (undefined **)&DAT_00011e14;
  pVVar6 = pos;
  do {
    puVar9 = ppuVar4[1];
    puVar10 = ppuVar4[2];
    puVar11 = ppuVar4[3];
    *(undefined **)&pVVar6->vx = *ppuVar4;
    *(undefined **)&pVVar6->vy = puVar9;
    *(undefined **)&pVVar6->vz = puVar10;
    *(undefined **)&pVVar6->pad = puVar11;
    ppuVar4 = ppuVar4 + 4;
    pVVar6 = pVVar6 + 1;
  } while (ppuVar4 != switchdataD_00011e54);
  puVar12 = (uint *)current->primptr;
  puVar13 = puVar12 + 2;
  setCopControlWord(2,0,norot.m[0]._0_4_);
  setCopControlWord(2,0x800,norot.m._4_4_);
  setCopControlWord(2,0x1000,norot.m[1]._2_4_);
  setCopControlWord(2,0x1800,norot.m[2]._0_4_);
  setCopControlWord(2,0x2000,norot._16_4_);
  setCopControlWord(2,0x2800,dummy.vx);
  setCopControlWord(2,0x3000,dummy.vy);
  setCopControlWord(2,0x3800,dummy.vz);
  *(char *)((int)puVar12 + 3) = '\t';
  *(char *)((int)puVar12 + 7) = ',';
  while (pos < (VECTOR *)&local_40) {
    iVar8 = -CameraCnt;
    iVar5 = iVar8;
    if (0 < CameraCnt) {
      iVar5 = iVar8 + 0xf;
    }
    iVar8 = iVar8 + (iVar5 >> 4) * -0x10;
    iVar5 = pos->vx * iVar8;
    if (iVar5 < 0) {
      iVar5 = iVar5 + 0xf;
    }
    iVar8 = pos->vz * iVar8;
    lVar7 = pPosition->vy;
    pos->vx = iVar5 >> 4;
    pos->vy = lVar7;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xf;
    }
    pos->vx = (iVar5 >> 4) + pPosition->vx;
    pos->vz = (iVar8 >> 4) + pPosition->vz;
    iVar8 = MapHeight(pos);
    pos->vx = pos->vx - camera_position.vx;
    pos->vy = -camera_position.vy - iVar8;
    pos->vz = pos->vz - camera_position.vz;
    Apply_Inv_CameraMatrix(pos);
    local_40 = *(undefined2 *)&pos->vx;
    local_3e = *(undefined2 *)&pos->vy;
    local_3c = *(undefined2 *)&pos->vz;
    RotTransPers((VECTOR *)&local_40,puVar13,auStack56,auStack52);
    if (puVar13 == puVar12 + 2) {
      puVar13 = puVar12 + 4;
    }
    else {
      bVar1 = puVar13 == puVar12 + 4;
      puVar13 = puVar12 + 8;
      if (bVar1) {
        puVar13 = puVar12 + 6;
      }
    }
    pos = pos + 1;
  }
  iVar8 = getCopReg(2,0x13);
  *(char *)(puVar12 + 1) = '@';
  *(char *)((int)puVar12 + 5) = '@';
  *(char *)((int)puVar12 + 6) = '@';
  *(byte *)((int)puVar12 + 7) = *(byte *)((int)puVar12 + 7) | 2;
  *(uchar *)(puVar12 + 3) = light_texture.coords.u0;
  *(uchar *)((int)puVar12 + 0xd) = light_texture.coords.v0;
  *(uchar *)(puVar12 + 5) = light_texture.coords.u1;
  *(uchar *)((int)puVar12 + 0x15) = light_texture.coords.v1;
  *(uchar *)(puVar12 + 7) = light_texture.coords.u2;
  *(uchar *)((int)puVar12 + 0x1d) = light_texture.coords.v2;
  *(uchar *)(puVar12 + 9) = light_texture.coords.u3;
  *(uchar *)((int)puVar12 + 0x25) = light_texture.coords.v3;
  if (gTimeOfDay == 3) {
    uVar3 = light_texture.tpageid | 0x20;
  }
  else {
    uVar3 = light_texture.tpageid | 0x40;
  }
  *(ushort *)((int)puVar12 + 0x16) = uVar3;
  pDVar2 = current;
  *(ushort *)((int)puVar12 + 0xe) = light_texture.clutid;
  *puVar12 = *puVar12 & 0xff000000 | pDVar2->ot[(iVar8 >> 4) + 0x200] & 0xffffff;
  (pDVar2->ot + (iVar8 >> 4))[0x200] =
       (pDVar2->ot + (iVar8 >> 4))[0x200] & 0xff000000 | (uint)puVar12 & 0xffffff;
  pDVar2->primptr = pDVar2->primptr + 0x28;
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToCameraPositions(struct VECTOR *pGlobalPositionIn /*$s1*/, struct VECTOR *pCameraPositionOut /*$s0*/, int count /*$s2*/)
 // line 496, offset 0x0008047c
	/* begin block 1 */
		// Start line: 497
		// Start offset: 0x0008047C

		/* begin block 1.1 */
			// Start line: 500
			// Start offset: 0x000804B8
			// Variables:
		// 		struct VECTOR temp; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x000804B8
		// End Line: 502
	/* end block 1 */
	// End offset: 0x00080528
	// End Line: 511

	/* begin block 2 */
		// Start line: 1144
	/* end block 2 */
	// End Line: 1145

	/* begin block 3 */
		// Start line: 1152
	/* end block 3 */
	// End Line: 1153

void WorldToCameraPositions(VECTOR *pGlobalPositionIn,VECTOR *pCameraPositionOut,int count)

{
  int iVar1;
  
  iVar1 = count + -1;
  if (count != 0) {
    do {
      pCameraPositionOut->vx = pGlobalPositionIn->vx - camera_position.vx;
      iVar1 = iVar1 + -1;
      pCameraPositionOut->vy = pGlobalPositionIn->vy - camera_position.vy;
      pCameraPositionOut->vz = pGlobalPositionIn->vz - camera_position.vz;
      Apply_Inv_CameraMatrix(pCameraPositionOut);
      pGlobalPositionIn = pGlobalPositionIn + 1;
      pCameraPositionOut = pCameraPositionOut + 1;
    } while (iVar1 != -1);
  }
  return;
}





