#include "THISDUST.H"
#include "SHADOW.H"
#include "TEXTURE.H"
#include "SYSTEM.H"
#include "MAIN.H"
#include "CAMERA.H"
#include "DRAW.H"

#include "INLINE_C.H"
#include "GTEREG.H"
#include "STRINGS.H"

// decompiled code
// original method signature: 
// void /*$ra*/ InitTyreTracks()
 // line 253, offset 0x00077524
	/* begin block 1 */
		// Start line: 255
		// Start offset: 0x00077524
		// Variables:
	// 		int loop; // $a0
	/* end block 1 */
	// End offset: 0x00077558
	// End Line: 262

	/* begin block 2 */
		// Start line: 2806
	/* end block 2 */
	// End Line: 2807

	/* begin block 3 */
		// Start line: 506
	/* end block 3 */
	// End Line: 507

	/* begin block 4 */
		// Start line: 2807
	/* end block 4 */
	// End Line: 2808

	/* begin block 5 */
		// Start line: 2809
	/* end block 5 */
	// End Line: 2810

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitTyreTracks(void)
{
	UNIMPLEMENTED();
	/*
	int *piVar1;
	int *piVar2;
	int iVar3;

	piVar1 = &num_tyre_tracks;
	piVar2 = &tyre_track_offset;
	iVar3 = 3;
	do {
		*piVar1 = 0;
		piVar1 = piVar1 + 1;
		*piVar2 = 0;
		iVar3 = iVar3 + -1;
		piVar2 = piVar2 + 1;
	} while (-1 < iVar3);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetTyreTrackPositions(struct _CAR_DATA *cp /*$s3*/, int player_id /*$s7*/)
 // line 272, offset 0x00075408
	/* begin block 1 */
		// Start line: 273
		// Start offset: 0x00075408
		// Variables:
	// 		struct CAR_COSMETICS *car_cos; // $s4
	// 		struct VECTOR WheelPos; // stack offset -88
	// 		struct VECTOR target_pos; // stack offset -72
	// 		struct VECTOR normal; // stack offset -56
	// 		int loop; // $s2

		/* begin block 1.1 */
			// Start line: 283
			// Start offset: 0x00075458
		/* end block 1.1 */
		// End offset: 0x00075480
		// End Line: 288
	/* end block 1 */
	// End offset: 0x00075540
	// End Line: 298

	/* begin block 2 */
		// Start line: 544
	/* end block 2 */
	// End Line: 545

void GetTyreTrackPositions(_CAR_DATA *cp, int player_id)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	SVECTOR *pSVar3;
	uint uVar4;
	CAR_COSMETICS *pCVar5;
	VECTOR local_58[3];

	pCVar5 = (cp->ap).carCos;
	SetRotMatrix(&(cp->hd).drawCarMat);
	uVar4 = 0;
	pSVar3 = pCVar5->wheelDisp;
	do {
		if ((uVar4 & 2) == 0) {
			local_58[0].vx = (int)pSVar3->vx + -0x11;
		}
		else {
			local_58[0].vx = (int)pSVar3->vx + 0x11;
		}
		local_58[0].vy = 0;
		pSVar3 = pSVar3 + 2;
		local_58[0].vz = -(int)pCVar5->wheelDisp[uVar4 + 1 & 3].vz;
		_MatrixRotate(local_58);
		iVar2 = (int)uVar4 >> 1;
		uVar4 = uVar4 + 2;
		local_58[0].vy = (cp->hd).where.t[1];
		local_58[0].vx = local_58[0].vx + (cp->hd).where.t[0];
		local_58[0].vz = local_58[0].vz + (cp->hd).where.t[2];
		iVar2 = iVar2 + player_id * 2;
		tyre_new_positions[iVar2].vx = local_58[0].vx;
		tyre_new_positions[iVar2].vz = local_58[0].vz;
		iVar1 = MapHeight(local_58);
		tyre_new_positions[iVar2].vy = iVar1;
	} while ((int)uVar4 < 4);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetTyreTrackOldPositions(int player_id /*$a0*/)
 // line 306, offset 0x00077558
	/* begin block 1 */
		// Start line: 2871
	/* end block 1 */
	// End Line: 2872

	/* begin block 2 */
		// Start line: 2916
	/* end block 2 */
	// End Line: 2917

	/* begin block 3 */
		// Start line: 2917
	/* end block 3 */
	// End Line: 2918

void SetTyreTrackOldPositions(int player_id)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	uint uVar2;
	undefined4 uVar3;
	long lVar4;
	undefined4 uVar5;
	long lVar6;
	long lVar7;

	uVar2 = player_id << 5 | 0x10;
	lVar4 = tyre_new_positions[player_id * 2].vy;
	lVar6 = tyre_new_positions[player_id * 2].vz;
	lVar7 = tyre_new_positions[player_id * 2].pad;
	tyre_save_positions[player_id * 2].vx = tyre_new_positions[player_id * 2].vx;
	tyre_save_positions[player_id * 2].vy = lVar4;
	tyre_save_positions[player_id * 2].vz = lVar6;
	tyre_save_positions[player_id * 2].pad = lVar7;
	uVar1 = *(undefined4 *)((int)&tyre_new_positions[0].vy + uVar2);
	uVar3 = *(undefined4 *)((int)&tyre_new_positions[0].vz + uVar2);
	uVar5 = *(undefined4 *)((int)&tyre_new_positions[0].pad + uVar2);
	*(undefined4 *)((int)&tyre_save_positions[0].vx + uVar2) =
		*(undefined4 *)((int)&tyre_new_positions[0].vx + uVar2);
	*(undefined4 *)((int)&tyre_save_positions[0].vy + uVar2) = uVar1;
	*(undefined4 *)((int)&tyre_save_positions[0].vz + uVar2) = uVar3;
	*(undefined4 *)((int)&tyre_save_positions[0].pad + uVar2) = uVar5;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddTyreTrack(int wheel /*$s2*/, int tracksAndSmoke /*$s6*/, int padid /*$s0*/)
 // line 330, offset 0x00075540
	/* begin block 1 */
		// Start line: 331
		// Start offset: 0x00075540
		// Variables:
	// 		struct VECTOR New1; // stack offset -168
	// 		struct VECTOR New2; // stack offset -152
	// 		struct VECTOR New3; // stack offset -136
	// 		struct VECTOR New4; // stack offset -120
	// 		struct VECTOR *old; // $s5
	// 		struct VECTOR *new; // $s3
	// 		struct TYRE_TRACK *tt_p; // $s1
	// 		int x; // $v1
	// 		int z; // $a1
	// 		int c; // $t1
	// 		int s; // $t0
	// 		unsigned int index; // $a2
	// 		static int Cont[4]; // offset 0x0
	// 		struct VECTOR psxoffset; // stack offset -104
	// 		struct VECTOR SmokeDrift; // stack offset -88
	// 		struct VECTOR SmokePosition; // stack offset -72
	// 		char trackSurface; // $s0

		/* begin block 1.1 */
			// Start line: 364
			// Start offset: 0x00075610
			// Variables:
		// 		struct ROUTE_DATA routeData; // stack offset -56
		// 		struct _sdPlane *SurfaceDataPtr; // $v0
		/* end block 1.1 */
		// End offset: 0x0007569C
		// End Line: 399

		/* begin block 1.2 */
			// Start line: 404
			// Start offset: 0x000756A8
		/* end block 1.2 */
		// End offset: 0x000756D0
		// End Line: 411

		/* begin block 1.3 */
			// Start line: 421
			// Start offset: 0x0007572C
			// Variables:
		// 		struct VECTOR grass_vector; // stack offset -48
		/* end block 1.3 */
		// End offset: 0x0007572C
		// End Line: 421
	/* end block 1 */
	// End offset: 0x000759B8
	// End Line: 506

	/* begin block 2 */
		// Start line: 679
	/* end block 2 */
	// End Line: 680

	/* begin block 3 */
		// Start line: 712
	/* end block 3 */
	// End Line: 713

void AddTyreTrack(int wheel, int tracksAndSmoke, int padid)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	_sdPlane *p_Var3;
	int iVar4;
	int *piVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	char cVar9;
	TYRE_TRACK *unaff_s1;
	VECTOR *pos;
	VECTOR *unaff_s5;
	short local_a8;
	short local_a4;
	short local_a0;
	short local_98;
	short local_90;
	short local_88;
	short local_84;
	short local_80;
	short local_78;
	short local_70;
	VECTOR local_68;
	VECTOR aVStack88[2];
	VECTOR local_30;

	pos = tyre_new_positions + wheel;
	iVar6 = tyre_new_positions[wheel].vz - camera_position.vz;
	if (&DAT_0000a000 < &DAT_00005000 + (pos->vx - camera_position.vx)) {
		return;
	}
	if (0x5000 < iVar6) {
		return;
	}
	if (iVar6 < -0x5000) {
		return;
	}
	if (tracksAndSmoke == 0) {
		p_Var3 = sdGetCell(pos);
		cVar9 = '\x01';
		if (p_Var3->surface == 6) {
			return;
		}
		iVar6 = wheel << 2;
		if (p_Var3->surface == 4) {
			cVar9 = '\x02';
		}
		goto LAB_000756d4;
	}
	iVar6 = wheel * 4;
	uVar8 = (&tyre_track_offset)[wheel] + (&num_tyre_tracks)[wheel];
	unaff_s5 = tyre_save_positions + wheel;
	if (0x3f < uVar8) {
		uVar8 = uVar8 & 0x3f;
	}
	unaff_s1 = track_buffer + uVar8 + wheel * 0x40;
	p_Var3 = sdGetCell(pos);
	if (p_Var3 == (_sdPlane *)0x0) {
	LAB_00075698:
		unaff_s1->surface = '\x01';
	}
	else {
		if (p_Var3->surface == 6) {
			return;
		}
		if (p_Var3->surface != 4) goto LAB_00075698;
		unaff_s1->surface = '\x02';
		(&player)[padid].onGrass = '\x01';
	}
	cVar9 = unaff_s1->surface;
LAB_000756d4:
	uVar8 = *(uint *)((int)smoke_count + iVar6);
	local_68.vx = pos->vx;
	local_68.vz = tyre_new_positions[wheel].vz;
	local_68.vy = -0x32 - tyre_new_positions[wheel].vy;
	*(uint *)((int)smoke_count + iVar6) = uVar8 + 1;
	if ((uVar8 & 3) == 1) {
		GetSmokeDrift(aVStack88);
		if (cVar9 == '\x02') {
			local_30.vx = DAT_00011ce4;
			local_30.vy = DAT_00011ce8;
			local_30.vz = DAT_00011cec;
			local_30.pad = DAT_00011cf0;
			Setup_Smoke(&local_68, 100, 500, 3, 0, aVStack88, 0);
			Setup_Sparks(&local_68, &local_30, 5, '\x02');
		}
		else {
			if (wetness == 0) {
				Setup_Smoke(&local_68, 100, 500, 2, 0, aVStack88, 0);
			}
		}
	}
	if (tracksAndSmoke != 0) {
		iVar4 = ratan2(unaff_s5->vz - tyre_new_positions[wheel].vz, unaff_s5->vx - pos->vx);
		iVar7 = (int)rcossin_tbl[(-iVar4 & 0xfffU) * 2 + 1] * 0x23;
		if (iVar7 < 0) {
			iVar7 = iVar7 + 0x1fff;
		}
		iVar4 = (int)rcossin_tbl[(-iVar4 & 0xfffU) * 2] * 0x23;
		if (iVar4 < 0) {
			iVar4 = iVar4 + 0x1fff;
		}
		local_a4 = (short)unaff_s5->vy + -10;
		local_84 = (short)tyre_new_positions[wheel].vy + -10;
		local_98 = (short)unaff_s5->vx;
		sVar1 = (short)(iVar4 >> 0xd);
		local_a8 = local_98 + sVar1;
		local_90 = (short)unaff_s5->vz;
		sVar2 = (short)(iVar7 >> 0xd);
		local_a0 = local_90 + sVar2;
		local_98 = local_98 - sVar1;
		local_90 = local_90 - sVar2;
		local_78 = (short)pos->vx;
		local_88 = local_78 + sVar1;
		local_70 = (short)tyre_new_positions[wheel].vz;
		local_80 = local_70 + sVar2;
		local_78 = local_78 - sVar1;
		local_70 = local_70 - sVar2;
		iVar7 = *(int *)((int)&num_tyre_tracks + iVar6);
		if (iVar7 == 0x40) {
			piVar5 = (int *)((int)&tyre_track_offset + iVar6);
			iVar4 = *piVar5;
			iVar7 = iVar4 + 1;
			*piVar5 = iVar7;
			if (0x3f < iVar7) {
				*piVar5 = iVar4 + -0x3f;
			}
		}
		else {
			*(int *)((int)&num_tyre_tracks + iVar6) = iVar7 + 1;
		}
		if ((*(int *)(&Cont_12 + iVar6) == 1) && (continuous_track == '\x01')) {
			unaff_s1->type = '\x01';
		}
		else {
			unaff_s1->type = '\0';
		}
		*(undefined4 *)(&Cont_12 + iVar6) = 1;
		(unaff_s1->p1).vx = local_a8;
		(unaff_s1->p1).vy = local_a4;
		(unaff_s1->p1).vz = local_a0;
		(unaff_s1->p2).vx = local_98;
		(unaff_s1->p2).vy = local_a4;
		(unaff_s1->p2).vz = local_90;
		(unaff_s1->p3).vx = local_88;
		(unaff_s1->p3).vy = local_84;
		(unaff_s1->p3).vz = local_80;
		(unaff_s1->p4).vx = local_78;
		(unaff_s1->p4).vy = local_84;
		(unaff_s1->p4).vz = local_70;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTyreTracks()
 // line 517, offset 0x000759e0
	/* begin block 1 */
		// Start line: 519
		// Start offset: 0x000759E0
		// Variables:
	// 		struct VECTOR p[4]; // stack offset -136
	// 		struct SVECTOR ps[4]; // stack offset -72
	// 		struct TYRE_TRACK *tt_p; // $t0
	// 		int z; // stack offset -40
	// 		int temp; // $a2
	// 		int loop; // $t7
	// 		int wheel_loop; // $s0
	// 		int index; // $t2
	// 		char last_duff; // $s1
	// 		struct POLY_FT4 *poly; // $a3
	// 		struct POLY_FT4 *lasttyre; // $t8
	/* end block 1 */
	// End offset: 0x00075F34
	// End Line: 645

	/* begin block 2 */
		// Start line: 1219
	/* end block 2 */
	// End Line: 1220

	/* begin block 3 */
		// Start line: 1220
	/* end block 3 */
	// End Line: 1221

	/* begin block 4 */
		// Start line: 1228
	/* end block 4 */
	// End Line: 1229

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawTyreTracks(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	bool bVar2;
	DB *pDVar3;
	ushort uVar4;
	undefined4 in_zero;
	undefined4 in_at;
	char cVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	uint *puVar9;
	char *pcVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	int iVar15;
	uint *puVar16;
	undefined4 local_48;
	uint local_44;
	undefined4 local_40;
	uint local_3c;
	undefined4 local_38;
	uint local_34;
	undefined4 local_30;
	uint local_2c;
	int local_28;

	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopControlWord(2, 0x2800, dummy.vx);
	setCopControlWord(2, 0x3000, dummy.vy);
	setCopControlWord(2, 0x3800, dummy.vz);
	iVar7 = 0;
	iVar14 = 0;
	do {
		iVar15 = iVar14 + 1;
		if (*(int *)((int)&num_tyre_tracks + iVar7) != 0) {
			puVar16 = (uint *)0x0;
			bVar1 = true;
			iVar11 = *(int *)((int)&tyre_track_offset + iVar7);
			iVar13 = 0;
			if (0 < *(int *)((int)&num_tyre_tracks + iVar7)) {
				iVar6 = iVar11 * 0x1c;
				do {
					iVar12 = iVar6 + 0x1c;
					iVar11 = iVar11 + 1;
					pcVar10 = &track_buffer[iVar14 * 0x40].type + iVar6;
					if (iVar11 == 0x40) {
						iVar12 = 0;
						iVar11 = 0;
					}
					if (*pcVar10 != '\x02') {
						if (((puVar16 == (uint *)0x0) || (*pcVar10 == '\0')) || (bVar2 = true, bVar1)) {
							iVar6 = ((uint)*(ushort *)(pcVar10 + 4) - (uint)(ushort)camera_position.vx) * 0x10000;
							bVar1 = true;
							if (&DAT_00005000 + (iVar6 >> 0x10) < (undefined *)0xa001) {
								uVar8 = (uint)*(ushort *)(pcVar10 + 8) - (uint)(ushort)camera_position.vz;
								if (&DAT_00005000 + ((int)(uVar8 * 0x10000) >> 0x10) < (undefined *)0xa001) {
									local_44 = local_44 & 0xffff0000 | uVar8 & 0xffff;
									local_48 = CONCAT22(-(ushort)camera_position.vy - *(short *)(pcVar10 + 6),
										(short)((uint)iVar6 >> 0x10));
									local_34 = local_34 & 0xffff0000 |
										(uint)(ushort)(*(short *)(pcVar10 + 0x14) - (ushort)camera_position.vz)
										;
									local_38 = CONCAT22(-(ushort)camera_position.vy - *(short *)(pcVar10 + 0x12),
										*(short *)(pcVar10 + 0x10) - (ushort)camera_position.vx);
									local_40 = CONCAT22(-(ushort)camera_position.vy - *(short *)(pcVar10 + 0xc),
										*(short *)(pcVar10 + 10) - (ushort)camera_position.vx);
									uVar8 = (uint)*(ushort *)(pcVar10 + 0xe) - (uint)(ushort)camera_position.vz;
									local_3c = local_3c & 0xffff0000 | uVar8 & 0xffff;
									puVar9 = (uint *)current->primptr;
									setCopReg(2, in_zero, local_48);
									setCopReg(2, in_at, local_44);
									setCopReg(2, &local_48, local_40);
									setCopReg(2, uVar8, local_3c);
									setCopReg(2, current, local_38);
									setCopReg(2, (uint)(ushort)camera_position.vy, local_34);
									copFunction(2, 0x280030);
									local_2c = local_2c & 0xffff0000 |
										(uint)(ushort)(*(short *)(pcVar10 + 0x1a) - (ushort)camera_position.vz)
										;
									local_30 = CONCAT22(-(ushort)camera_position.vy - *(short *)(pcVar10 + 0x18),
										*(short *)(pcVar10 + 0x16) - (ushort)camera_position.vx);
									uVar8 = getCopReg(2, 0xc);
									puVar9[2] = uVar8;
									uVar8 = getCopReg(2, 0xd);
									puVar9[4] = uVar8;
									uVar8 = getCopReg(2, 0xe);
									puVar9[6] = uVar8;
									local_28 = getCopReg(2, 0x13);
									setCopReg(2, in_zero, local_30);
									setCopReg(2, in_at, local_2c);
									copFunction(2, 0x180001);
									uVar8 = getCopReg(2, 0xe);
									puVar9[8] = uVar8;
									if (0x32 < local_28) goto LAB_00075dbc;
									goto LAB_00075eec;
								}
							}
							*pcVar10 = '\x02';
						}
						else {
							iVar6 = ((uint)*(ushort *)(pcVar10 + 0x10) - (uint)(ushort)camera_position.vx) *
								0x10000;
							puVar9 = (uint *)current->primptr;
							bVar1 = bVar2;
							if (&DAT_00002328 + (iVar6 >> 0x10) <= &DAT_00004650) {
								if (&DAT_00002328 +
									((int)(((uint)*(ushort *)(pcVar10 + 0x14) - (uint)(ushort)camera_position.vz) *
										0x10000) >> 0x10) < (undefined *)0x4651) {
									local_34 = local_34 & 0xffff0000 |
										(uint)*(ushort *)(pcVar10 + 0x14) - (uint)(ushort)camera_position.vz &
										0xffff;
									local_38 = CONCAT22(-(ushort)camera_position.vy - *(short *)(pcVar10 + 0x12),
										(short)((uint)iVar6 >> 0x10));
									setCopReg(2, in_zero, local_38);
									setCopReg(2, in_at, local_34);
									copFunction(2, 0x180001);
									local_30 = CONCAT22(-(ushort)camera_position.vy - *(short *)(pcVar10 + 0x18),
										*(short *)(pcVar10 + 0x16) - (ushort)camera_position.vx);
									local_2c = local_2c & 0xffff0000 |
										(uint)(ushort)(*(short *)(pcVar10 + 0x1a) - (ushort)camera_position.vz)
										;
									uVar8 = getCopReg(2, 0xe);
									puVar9[6] = uVar8;
									local_28 = getCopReg(2, 0x13);
									setCopReg(2, in_zero, local_30);
									setCopReg(2, in_at, local_2c);
									copFunction(2, 0x180001);
									if (0x32 < local_28) {
										puVar9[2] = puVar16[6];
										puVar9[4] = puVar16[8];
										uVar8 = getCopReg(2, 0xe);
										puVar9[8] = uVar8;
									LAB_00075dbc:
										*(char *)((int)puVar9 + 3) = '\t';
										*(char *)((int)puVar9 + 7) = ',';
										if (pcVar10[3] == '\x01') {
											cVar5 = '\x1a';
											*(char *)(puVar9 + 1) = '\x1a';
										}
										else {
											cVar5 = '#';
											*(char *)(puVar9 + 1) = '\x11';
										}
										*(char *)((int)puVar9 + 5) = cVar5;
										*(char *)((int)puVar9 + 6) = cVar5;
										*(uchar *)(puVar9 + 3) = gTyreTexture.coords.u0;
										*(uchar *)((int)puVar9 + 0xd) = gTyreTexture.coords.v0;
										*(uchar *)(puVar9 + 5) = gTyreTexture.coords.u1;
										*(uchar *)((int)puVar9 + 0x15) = gTyreTexture.coords.v1;
										*(uchar *)(puVar9 + 7) = gTyreTexture.coords.u2;
										*(uchar *)((int)puVar9 + 0x1d) = gTyreTexture.coords.v2;
										*(uchar *)(puVar9 + 9) = gTyreTexture.coords.u3;
										*(uchar *)((int)puVar9 + 0x25) = gTyreTexture.coords.v3;
										*(ushort *)((int)puVar9 + 0x16) = gTyreTexture.tpageid | 0x40;
										uVar4 = gTyreTexture.clutid;
										*(byte *)((int)puVar9 + 7) = *(byte *)((int)puVar9 + 7) | 2;
										pDVar3 = current;
										*(ushort *)((int)puVar9 + 0xe) = uVar4;
										*puVar9 = *puVar9 & 0xff000000 | pDVar3->ot[local_28 >> 3] & 0xffffff;
										pDVar3->ot[local_28 >> 3] =
											pDVar3->ot[local_28 >> 3] & 0xff000000 | (uint)puVar9 & 0xffffff;
										pDVar3->primptr = pDVar3->primptr + 0x28;
										puVar16 = puVar9;
										bVar1 = false;
									}
								}
							}
						}
					}
				LAB_00075eec:
					iVar13 = iVar13 + 1;
					iVar6 = iVar12;
				} while (iVar13 < *(int *)((int)&num_tyre_tracks + iVar7));
			}
		}
		iVar7 = iVar15 * 4;
		iVar14 = iVar15;
		if (3 < iVar15) {
			return;
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitShadow()
 // line 659, offset 0x00075f34
	/* begin block 1 */
		// Start line: 661
		// Start offset: 0x00075F34
		// Variables:
	// 		struct TPAN pos; // stack offset -16
	// 		struct TEXINF *texinf; // $v0
	// 		int i; // $a2
	// 		int j; // $a3

		/* begin block 1.1 */
			// Start line: 682
			// Start offset: 0x00076090
		/* end block 1.1 */
		// End offset: 0x00076090
		// End Line: 684
	/* end block 1 */
	// End offset: 0x00076108
	// End Line: 697

	/* begin block 2 */
		// Start line: 1652
	/* end block 2 */
	// End Line: 1653

	/* begin block 3 */
		// Start line: 1667
	/* end block 3 */
	// End Line: 1668

	/* begin block 4 */
		// Start line: 1668
	/* end block 4 */
	// End Line: 1669

	/* begin block 5 */
		// Start line: 1672
	/* end block 5 */
	// End Line: 1673

/* WARNING: Unknown calling convention yet parameter storage is locked */

int gShadowTexturePage;
int gShadowTextureNum;

UV shadowuv;
POLY_FT4 shadowPolys[2][20];

// [D]
void InitShadow(void)
{
	unsigned char uVar1;
	ushort uVar2;
	ushort uVar3;
	unsigned char uVar4;
	unsigned char uVar5;
	unsigned char uVar6;
	unsigned char uVar7;
	unsigned char uVar8;
	unsigned char uVar9;

	TEXINF *texinf;
	unsigned char uVar10;
	POLY_FT4 *pPVar11;
	int iVar12;
	int iVar13;
	TPAN pos;

	texinf = GetTextureInfoName("CARSHAD", &pos);

	gShadowTexturePage = pos.texture_page;
	gShadowTextureNum = pos.texture_number;

	uVar1 = texinf->x;
	uVar10 = texinf->x + texinf->width + -1;
	shadowuv.v1 = texinf->y;
	shadowuv.u2 = texinf->x;
	shadowuv.v2 = texinf->y + texinf->height + -1;
	shadowuv.u3 = texinf->x + texinf->width + -1;
	shadowuv.v3 = texinf->y + texinf->height + -1;
	shadowuv.v0 = texinf->y;

	if (GameLevel == 3) 
	{
		shadowuv.v1 = shadowuv.v1 + 1;
		shadowuv.v0 = texinf->y + 1;
	}

	uVar5 = shadowuv.v1;
	uVar4 = shadowuv.v0;

	uVar2 = texture_pages[gShadowTexturePage];
	uVar3 = texture_cluts[gShadowTexturePage][gShadowTextureNum];

	iVar12 = 0;
	shadowuv.u0 = uVar1;
	shadowuv.u1 = uVar10;

	do {
		iVar13 = iVar12 + 1;

		pPVar11 = shadowPolys[iVar12];

		iVar12 = 0x13;

		do {
			uVar9 = shadowuv.v3;
			uVar8 = shadowuv.u3;
			uVar7 = shadowuv.v2;
			uVar6 = shadowuv.u2;

			setPolyFT4(pPVar11);

			pPVar11->r0 = 'P';
			pPVar11->g0 = 'P';
			pPVar11->b0 = 'P';

			pPVar11->tpage = uVar2 | 0x40;
			pPVar11->clut = uVar3;
			setSemiTrans(pPVar11, 1);

			pPVar11->u0 = uVar1;
			pPVar11->v0 = uVar4;
			pPVar11->u1 = uVar10;
			pPVar11->v1 = uVar5;
			pPVar11->u2 = uVar6;
			pPVar11->v2 = uVar7;
			pPVar11->u3 = uVar8;
			pPVar11->v3 = uVar9;

			pPVar11 ++;
			iVar12--;
		} while (-1 < iVar12);

		iVar12 = iVar13;
	} while (iVar13 < 2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SubdivShadow(long z0 /*$t7*/, long z1 /*$t9*/, long z2 /*$t8*/, long z3 /*$t6*/, struct POLY_FT4 *sps /*stack 16*/)
 // line 717, offset 0x00076108
	/* begin block 1 */
		// Start line: 718
		// Start offset: 0x00076108
		// Variables:
	// 		struct POLY_FT4 *spd; // $t3
	// 		int i; // $t4

		/* begin block 1.1 */
			// Start line: 735
			// Start offset: 0x000761B8
			// Variables:
		// 		unsigned long A0; // $v1
		// 		unsigned long A1; // $a1
		// 		unsigned long E0; // $a3
		// 		unsigned long E1; // $t0
		// 		unsigned long C0; // $a0
		// 		unsigned long C1; // $a2
		// 		unsigned long B0; // $v1
		// 		unsigned long B1; // $a1
		// 		unsigned long D0; // $a0
		// 		unsigned long D1; // $a2
		/* end block 1.1 */
		// End offset: 0x000761B8
		// End Line: 735

		/* begin block 1.2 */
			// Start line: 735
			// Start offset: 0x000761B8
			// Variables:
		// 		unsigned long A0; // $a1
		// 		unsigned long A1; // $a2
		// 		unsigned long E0; // $a3
		// 		unsigned long E1; // $t0
		// 		unsigned long C0; // $a0
		// 		unsigned long C1; // $v1
		// 		unsigned long B0; // $a1
		// 		unsigned long B1; // $a2
		// 		unsigned long D0; // $a0
		// 		unsigned long D1; // $v1
		/* end block 1.2 */
		// End offset: 0x000761B8
		// End Line: 735
	/* end block 1 */
	// End offset: 0x000766CC
	// End Line: 861

	/* begin block 2 */
		// Start line: 1788
	/* end block 2 */
	// End Line: 1789

	/* begin block 3 */
		// Start line: 1809
	/* end block 3 */
	// End Line: 1810

// [D] [A] - this is a fuckery
void SubdivShadow(long z0, long z1, long z2, long z3, POLY_FT4 *sps)
{
#if 0
	ushort uVar1;
	ushort uVar3;
	ulong uVar4;
	ushort uVar5;
	ushort uVar6;
	uint iVar7;
	uint uVar8;
	ushort uVar9;
	POLY_FT4 *pPVar10;
	uint uVar11;
	uint iVar12;
	uint iVar13;
	uint uVar14;
	uint uVar15;
	uint uVar16;
	uint uVar17;
	uint iVar18;
	uint iVar19;
	uint uVar20;
	uint iVar21;
	uint iVar22;
	uint uVar23;
	POLY_FT4 *spd;
	uint iVar24;

	spd = (POLY_FT4 *)current->primptr;
	current->primptr += sizeof(POLY_FT4)*8;

	uVar4 = sps->tag;
	
	spd[7].tag = uVar4;
	spd[6].tag = uVar4;
	spd[5].tag = uVar4;
	spd[4].tag = uVar4;
	spd[3].tag = uVar4;
	spd[2].tag = uVar4;
	spd[1].tag = uVar4;
	spd->tag = uVar4;


	uVar6 = *(uint *)&sps->r0;
	*(uint *)&spd[7].r0 = uVar6;
	*(uint *)&spd[6].r0 = uVar6;
	*(uint *)&spd[5].r0 = uVar6;
	*(uint *)&spd[4].r0 = uVar6;
	*(uint *)&spd[3].r0 = uVar6;
	*(uint *)&spd[2].r0 = uVar6;
	*(uint *)&spd[1].r0 = uVar6;
	*(uint *)&spd->r0 = uVar6;

	pPVar10 = spd;

	iVar24 = 7;
	do {
		*(uint *)&pPVar10->u0 = *(uint *)&sps->u0;
		*(uint *)&pPVar10->u1 = *(uint *)&sps->u1;
		*(uint *)&pPVar10->u2 = *(uint *)&sps->u2;
		iVar24 = iVar24 + -1;
		*(uint *)&pPVar10->u3 = *(uint *)&sps->u3;
		pPVar10 = pPVar10 + 1;
	} while (-1 < iVar24);

	iVar12 = *(uint *)&sps->x1;
	iVar18 = *(uint *)&sps->x2;
	iVar21 = *(uint *)&sps->x3;
	iVar7 = *(uint *)&sps->x0 +0x8000800;
	iVar13 = iVar12 +0x8000800;
	*(uint *)&spd->x0 = *(uint *)&sps->x0;
	iVar24 = ((uint)(iVar7 + iVar13) >> 1) +0xf7fff800;
	iVar19 = iVar18 +0x8000800;
	*(uint *)&spd[4].x1 = iVar12;
	uVar11 = (uint)(iVar7 + iVar19) >> 1;
	uVar8 = iVar7 + uVar11 >> 1;
	*(uint *)&spd->x1 = iVar24;
	*(uint *)&spd[4].x0 = iVar24;
	iVar24 = uVar8 +0xf7fff800;
	iVar22 = iVar21 +0x8000800;
	uVar16 = (uint)(iVar13 + iVar22) >> 1;
	uVar14 = iVar13 + uVar16 >> 1;
	iVar7 = (uVar8 + uVar14 >> 1) +0xf7fff800;
	iVar12 = uVar14+0xf7fff800;
	*(uint *)&spd->x2 = iVar24;
	*(uint *)&spd[1].x0 = iVar24;
	iVar24 = (uVar11 + uVar16 >> 1) +0xf7fff800;
	*(uint *)&spd->x3 = iVar7;
	*(uint *)&spd[4].x2 = iVar7;
	*(uint *)&spd[1].x1 = iVar7;
	*(uint *)&spd[5].x0 = iVar7;
	uVar8 = iVar19 + uVar11 >> 1;
	*(uint *)&spd[1].x3 = iVar24;
	*(uint *)&spd[5].x2 = iVar24;
	*(uint *)&spd[2].x1 = iVar24;
	*(uint *)&spd[6].x0 = iVar24;
	iVar24 = uVar8 +0xf7fff800;
	uVar14 = iVar22 + uVar16 >> 1;
	iVar7 = (uVar8 + uVar14 >> 1) +0xf7fff800;
	iVar13 = uVar14 +0xf7fff800;
	*(uint *)&spd[2].x2 = iVar24;
	*(uint *)&spd[3].x0 = iVar24;
	iVar24 = ((uint)(iVar19 + iVar22) >> 1) +0xf7fff800;
	*(uint *)&spd[4].x3 = iVar12;
	*(uint *)&spd[5].x1 = iVar12;
	*(uint *)&spd[1].x2 = uVar11 +0xf7fff800;
	*(uint *)&spd[5].x3 = uVar16 +0xf7fff800;
	*(uint *)&spd[2].x0 = uVar11 +0xf7fff800;
	*(uint *)&spd[6].x1 = uVar16 +0xf7fff800;
	*(uint *)&spd[2].x3 = iVar7;
	*(uint *)&spd[6].x2 = iVar7;
	*(uint *)&spd[6].x3 = iVar13;
	*(uint *)&spd[3].x1 = iVar7;
	*(uint *)&spd[7].x0 = iVar7;
	*(uint *)&spd[7].x1 = iVar13;
	*(uint *)&spd[3].x2 = iVar18;
	*(uint *)&spd[3].x3 = iVar24;
	*(uint *)&spd[7].x2 = iVar24;
	*(uint *)&spd[7].x3 = iVar21;

	uVar1 = *(ushort *)&sps->u3;
	uVar11 = (uint)*(ushort *)&sps->u0 & 0xfeff;
	uVar16 = (uint)*(ushort *)&sps->u1 & 0xfeff;
	uVar20 = (uint)*(ushort *)&sps->u2 & 0xfeff;
	uVar14 = uVar11 + uVar20 >> 1 & 0xfeff;
	*(ushort *)&spd->u0 = (ushort)uVar11;
	uVar15 = uVar11 + uVar14 >> 1;
	uVar23 = (uint)uVar1 & 0xfeff;
	uVar8 = uVar16 + uVar23 >> 1 & 0xfeff;
	*(ushort *)&spd[4].u1 = (ushort)uVar16;
	uVar17 = uVar16 + uVar8 >> 1;
	uVar3 = (ushort)(uVar11 + uVar16 >> 1);
	*(ushort *)&spd->u1 = uVar3;
	*(ushort *)&spd[4].u0 = uVar3;
	uVar3 = (ushort)(uVar15 + uVar17 >> 1);
	*(ushort *)&spd->u3 = uVar3;
	*(ushort *)&spd[4].u2 = uVar3;
	*(ushort *)&spd[1].u1 = uVar3;
	*(ushort *)&spd[5].u0 = uVar3;
	*(ushort *)&spd[1].u2 = (ushort)uVar14;
	*(ushort *)&spd[2].u0 = (ushort)uVar14;
	uVar16 = uVar20 + uVar14 >> 1;
	*(ushort *)&spd[5].u3 = (ushort)uVar8;
	*(ushort *)&spd[6].u1 = (ushort)uVar8;
	uVar11 = uVar23 + uVar8 >> 1;
	uVar3 = (ushort)(uVar14 + uVar8 >> 1);
	*(ushort *)&spd[1].u3 = uVar3;
	*(ushort *)&spd[5].u2 = uVar3;
	*(ushort *)&spd[2].u1 = uVar3;
	*(ushort *)&spd[6].u0 = uVar3;
	uVar3 = (ushort)uVar15;
	*(ushort *)&spd->u2 = uVar3;
	uVar5 = (ushort)uVar17;
	*(ushort *)&spd[4].u3 = uVar5;
	*(ushort *)&spd[1].u0 = uVar3;
	*(ushort *)&spd[5].u1 = uVar5;
	uVar9 = (ushort)uVar16;
	*(ushort *)&spd[2].u2 = uVar9;
	uVar3 = (ushort)(uVar16 + uVar11 >> 1);
	*(ushort *)&spd[2].u3 = uVar3;
	*(ushort *)&spd[6].u2 = uVar3;
	uVar5 = (ushort)uVar11;
	*(ushort *)&spd[6].u3 = uVar5;
	*(ushort *)&spd[3].u0 = uVar9;
	*(ushort *)&spd[3].u1 = uVar3;
	*(ushort *)&spd[7].u0 = uVar3;
	*(ushort *)&spd[7].u1 = uVar5;
	*(short *)&spd[3].u2 = (short)uVar20;
	
	uVar3 = (ushort)(uVar20 + uVar23 >> 1);
	*(ushort *)&spd[3].u3 = uVar3;
	*(ushort *)&spd[7].u2 = uVar3;
	*(short *)&spd[7].u3 = (short)uVar23;
	
#ifndef PSX
	setPolyFT4(&spd[7]);
	setPolyFT4(&spd[6]);
	setPolyFT4(&spd[5]);
	setPolyFT4(&spd[4]);
	setPolyFT4(&spd[3]);
	setPolyFT4(&spd[2]);
	setPolyFT4(&spd[1]);
	setPolyFT4(&spd[0]);
#endif // PSX

	iVar24 = z0 * 7 + z3 >> 6;
	addPrim(current->ot + iVar24, &spd[0]);
	
	//spd->tag = spd->tag & 0xff000000 | current->ot[iVar24] & 0xffffff;
	//pDVar2->ot[iVar24] = pDVar2->ot[iVar24] & 0xff000000 | (uint)spd & 0xffffff;
	iVar24 = z0 * 5 + z3 * 3 >> 6;
	addPrim(current->ot + iVar24, &spd[1]);  // spd[1].tag = spd[1].tag & 0xff000000 | pDVar2->ot[iVar24] & 0xffffff;
	iVar7 = z0 * 3 + z3 * 5 >> 6;
	//pDVar2->ot[iVar24] = pDVar2->ot[iVar24] & 0xff000000 | (uint)(spd + 1) & 0xffffff;
	iVar24 = z0 + z3 * 7 >> 6;
	addPrim(current->ot + iVar7, &spd[2]);  // spd[2].tag = spd[2].tag & 0xff000000 | pDVar2->ot[iVar7] & 0xffffff;
	//pDVar2->ot[iVar7] = pDVar2->ot[iVar7] & 0xff000000 | (uint)(spd + 2) & 0xffffff;
	iVar7 = z1 * 7 + z2 >> 6;
	addPrim(current->ot + iVar24, &spd[3]);  // spd[3].tag = spd[3].tag & 0xff000000 | pDVar2->ot[iVar24] & 0xffffff;
	//pDVar2->ot[iVar24] = pDVar2->ot[iVar24] & 0xff000000 | (uint)(spd + 3) & 0xffffff;
	addPrim(current->ot + iVar7, &spd[4]);  // spd[4].tag = spd[4].tag & 0xff000000 | pDVar2->ot[iVar7] & 0xffffff;
	iVar24 = z1 * 5 + z2 * 3 >> 6;
	//pDVar2->ot[iVar7] = pDVar2->ot[iVar7] & 0xff000000 | (uint)(spd + 4) & 0xffffff;
	addPrim(current->ot + iVar24, &spd[5]);  // spd[5].tag = spd[5].tag & 0xff000000 | pDVar2->ot[iVar24] & 0xffffff;
	iVar7 = z1 * 3 + z2 * 5 >> 6;
	//pDVar2->ot[iVar24] = pDVar2->ot[iVar24] & 0xff000000 | (uint)(spd + 5) & 0xffffff;
	iVar24 = z1 + z2 * 7 >> 6;
	addPrim(current->ot + iVar7, &spd[6]);  // spd[6].tag = spd[6].tag & 0xff000000 | pDVar2->ot[iVar7] & 0xffffff;
	//pDVar2->ot[iVar7] = pDVar2->ot[iVar7] & 0xff000000 | (uint)(spd + 6) & 0xffffff;
	addPrim(current->ot + iVar24, &spd[7]);  // spd[7].tag = spd[7].tag & 0xff000000 | pDVar2->ot[iVar24] & 0xffffff;
	//pDVar2->ot[iVar24] = pDVar2->ot[iVar24] & 0xff000000 | (uint)(spd + 7) & 0xffffff;
#else
	POLY_FT4 *spd;

	spd = (POLY_FT4 *)current->primptr;
	current->primptr += sizeof(POLY_FT4) * 4;

	memcpy(spd, sps, sizeof(POLY_FT4)*4);

	addPrim(current->ot + (z0 * 2 + z3 * 6 >> 6), spd);
#endif // PSX
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaceShadowForCar(struct VECTOR *shadowPoints /*$t0*/, int slot /*$s0*/, struct VECTOR *CarPos /*$a2*/, int zclip /*$a3*/)
 // line 864, offset 0x000766cc
	/* begin block 1 */
		// Start line: 865
		// Start offset: 0x000766CC
		// Variables:
	// 		struct SVECTOR points[4]; // stack offset -64
	// 		long z; // $a0
	// 		long z0; // stack offset -32
	// 		long z1; // stack offset -28
	// 		long z2; // stack offset -24
	// 		long z3; // stack offset -20
	// 		struct POLY_FT4 *spt; // $a3
	/* end block 1 */
	// End offset: 0x00076A40
	// End Line: 933

	/* begin block 2 */
		// Start line: 2526
	/* end block 2 */
	// End Line: 2527

	/* begin block 3 */
		// Start line: 2530
	/* end block 3 */
	// End Line: 2531

	/* begin block 4 */
		// Start line: 2535
	/* end block 4 */
	// End Line: 2536

extern VECTOR dummy;

// [D]
void PlaceShadowForCar(VECTOR *shadowPoints, int slot, VECTOR *CarPos, int zclip)
{

	uint uVar1;
	long z0_00;
	long z1_00;
	long z2_00;
	long z3_00;
	POLY_FT4 *sps;
	SVECTOR points[4];
	long z0;
	long z1;
	long z2;
	long z3;

	if (slot < 0) {
		while (FrameCnt != 0x78654321) 
		{
			trap(0x400);
		}
	}

	points[0].vx = shadowPoints[0].vx - camera_position.vx;
	points[0].vy = -shadowPoints[0].vy - camera_position.vy;
	points[0].vz = shadowPoints[0].vz - camera_position.vz;

	points[1].vx = shadowPoints[1].vx - camera_position.vx;
	points[1].vy = -shadowPoints[1].vy - camera_position.vy;
	points[1].vz = shadowPoints[1].vz - camera_position.vz;

	points[2].vx = shadowPoints[3].vx - camera_position.vx;
	points[2].vy = -shadowPoints[3].vy - camera_position.vy;
	points[2].vz = shadowPoints[3].vz - camera_position.vz;

	gte_SetTransVector(&dummy);
	gte_SetRotMatrix(&inv_camera_matrix);

	sps = &shadowPolys[current->id][slot];

	gte_ldv3(&points[0], &points[1], &points[2]);

	docop2(0x280030);

	points[3].vx = shadowPoints[2].vx - camera_position.vx;
	points[3].vy = -shadowPoints[2].vy - camera_position.vy;
	points[3].vz = shadowPoints[2].vz - camera_position.vz;

	gte_stsxy3(&sps->x0, &sps->x1, &sps->x3);

	gte_stsz3(&z0,&z1,&z2);

	gte_ldv0(&points[3]);

	docop2(0x180001);

	gte_stsz(&z3);
	gte_stsxy(&sps->x2);

	if (z0 < z1) {
		z0 = (z0 + z1) / 2;
	}
	else {
		z1 = (z0 + z1) / 2;
	}
	if (z2 < z3) {
		z2 = (z2 + z3) / 2;
	}
	else {
		z3 = (z2 + z3) / 2;
	}
	z0_00 = 8;
	if (0x1c < z0) {
		z0_00 = z0 + -0x14;
	}
	z1_00 = 8;
	if (0x1c < z1) {
		z1_00 = z1 + -0x14;
	}
	z2_00 = 8;
	if (0x1c < z2) {
		z2_00 = z2 + -0x14;
	}
	z3_00 = 8;
	if (0x1c < z3) {
		z3_00 = z3 + -0x14;
	}

	SubdivShadow(z0_00, z1_00, z2_00, z3_00, sps);
}



// decompiled code
// original method signature: 
// int /*$ra*/ clipAgainstZ()
 // line 1038, offset 0x00076a40
	/* begin block 1 */
		// Start line: 1040
		// Start offset: 0x00076A40
		// Variables:
	// 		int srccount; // $t4
	// 		int dstcount; // $t5
	// 		struct SVECTOR *current; // $t2
	// 		struct SVECTOR *previous; // $t1
	// 		struct SVECTOR *dst; // $a3
	// 		int flags; // $t3

		/* begin block 1.1 */
			// Start line: 1057
			// Start offset: 0x00076AC0
			// Variables:
		// 		int q; // $a2
		/* end block 1.1 */
		// End offset: 0x00076AC0
		// End Line: 1057

		/* begin block 1.2 */
			// Start line: 1063
			// Start offset: 0x00076BB8
			// Variables:
		// 		int q; // $a2
		/* end block 1.2 */
		// End offset: 0x00076BB8
		// End Line: 1063
	/* end block 1 */
	// End offset: 0x00076CD4
	// End Line: 1079

	/* begin block 2 */
		// Start line: 2837
	/* end block 2 */
	// End Line: 2838

	/* begin block 3 */
		// Start line: 2906
	/* end block 3 */
	// End Line: 2907

	/* begin block 4 */
		// Start line: 2907
	/* end block 4 */
	// End Line: 2908

	/* begin block 5 */
		// Start line: 2908
	/* end block 5 */
	// End Line: 2909

/* WARNING: Unknown calling convention yet parameter storage is locked */

int clipAgainstZ(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	SVECTOR *pSVar1;
	SVECTOR *pSVar2;
	undefined4 uVar3;
	int iVar4;
	int iVar5;
	SVECTOR *pSVar6;
	int iVar7;
	SVECTOR *pSVar8;
	uint uVar9;
	int iVar10;
	int iVar11;

	iVar11 = 0;
	pSVar8 = &cv + lastcv;
	pSVar6 = SVECTOR_ARRAY_000da940 + lastcv;
	iVar10 = numcv + -1;
	uVar9 = (uint)(0 < (pSVar8 + numcv * 0x1fffffff)[1].vz) << 1;
	pSVar2 = pSVar8 + numcv * 0x1fffffff + 1;
	do {
		pSVar1 = pSVar8;
		if (iVar10 < 0) {
			numcv = iVar11;
			lastcv = lastcv + 2;
			return 0;
		}
		iVar7 = (int)pSVar1->vz;
		uVar9 = (int)uVar9 >> 1;
		if (0 < iVar7) {
			uVar9 = uVar9 | 2;
		}
		if (uVar9 == 1) {
			iVar5 = (int)pSVar2->vz;
			iVar4 = iVar5 - iVar7;
			if (iVar4 == 0) {
				trap(7);
			}
			pSVar6->vx = (short)((pSVar1->vx * iVar5 - pSVar2->vx * iVar7) / iVar4);
			if (iVar4 == 0) {
				trap(7);
			}
			pSVar6->vy = (short)((pSVar1->vy * iVar5 - pSVar2->vy * iVar7) / iVar4);
			if (iVar4 == 0) {
				trap(7);
			}
			pSVar6->pad = (short)((pSVar1->pad * iVar5 - pSVar2->pad * iVar7) / iVar4);
			pSVar6->vz = 0;
		LAB_00076ca4:
			pSVar6 = pSVar6 + -1;
			iVar11 = iVar11 + 1;
		}
		else {
			if (uVar9 < 2) {
				if (uVar9 != 0) {
				LAB_00076c84:
					uVar3 = *(undefined4 *)&pSVar1->vz;
					*(undefined4 *)pSVar6 = *(undefined4 *)pSVar1;
					*(undefined4 *)&pSVar6->vz = uVar3;
					goto LAB_00076ca4;
				}
			}
			else {
				if (uVar9 != 2) goto LAB_00076c84;
				iVar5 = (int)pSVar2->vz;
				iVar4 = iVar5 - iVar7;
				if (iVar4 == 0) {
					trap(7);
				}
				pSVar6->vx = (short)((pSVar1->vx * iVar5 - pSVar2->vx * iVar7) / iVar4);
				if (iVar4 == 0) {
					trap(7);
				}
				pSVar6->vy = (short)((pSVar1->vy * iVar5 - pSVar2->vy * iVar7) / iVar4);
				if (iVar4 == 0) {
					trap(7);
				}
				pSVar6->pad = (short)((pSVar1->pad * iVar5 - pSVar2->pad * iVar7) / iVar4);
				pSVar6->vz = 0;
				uVar3 = *(undefined4 *)&pSVar1->vz;
				*(undefined4 *)(pSVar6 + -1) = *(undefined4 *)pSVar1;
				*(undefined4 *)&pSVar6[-1].vz = uVar3;
				pSVar6 = pSVar6 + -2;
				iVar11 = iVar11 + 2;
			}
		}
		iVar10 = iVar10 + -1;
		pSVar8 = pSVar1 + -1;
		pSVar2 = pSVar1;
	} while (true);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ clippedPoly()
 // line 1081, offset 0x00076cd4
	/* begin block 1 */
		// Start line: 1083
		// Start offset: 0x00076CD4
		// Variables:
	// 		int i; // $a3
	// 		int j; // $t0
	// 		int z1; // $v1
	// 		struct POLY_G3 *pg3; // $s0
	// 		int z[3]; // stack offset -24
	/* end block 1 */
	// End offset: 0x00077128
	// End Line: 1156

	/* begin block 2 */
		// Start line: 2993
	/* end block 2 */
	// End Line: 2994

	/* begin block 3 */
		// Start line: 2996
	/* end block 3 */
	// End Line: 2997

	/* begin block 4 */
		// Start line: 2997
	/* end block 4 */
	// End Line: 2998

	/* begin block 5 */
		// Start line: 2999
	/* end block 5 */
	// End Line: 3000

/* WARNING: Unknown calling convention yet parameter storage is locked */

void clippedPoly(void)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	int iVar2;
	int iVar3;
	POLY_F3 *pPVar4;
	DB *pDVar5;
	undefined4 in_zero;
	undefined4 in_at;
	int iVar6;
	SVECTOR *pSVar7;
	short *psVar8;
	ulong *in_a1;
	short *psVar9;
	int iVar10;
	int iVar11;
	uint *puVar12;

	pPVar4 = spolys;
	iVar11 = numcv + -1;
	if (iVar11 != -1) {
		in_a1 = (ulong *)0xffffffff;
		psVar8 = &(&cv)[lastcv].vz;
		do {
			iVar11 = iVar11 + -1;
			*psVar8 = *psVar8 * 2 - psVar8[-2];
			psVar8 = psVar8 + -4;
		} while (iVar11 != -1);
	}
	clipAgainstZ();
	if (2 < numcv) {
		iVar11 = numcv + -1;
		if (numcv != 0) {
			in_a1 = (ulong *)0xffffffff;
			pSVar7 = &cv + lastcv;
			do {
				iVar11 = iVar11 + -1;
				pSVar7->vz = pSVar7->vz + pSVar7->vx * 2;
				pSVar7 = pSVar7 + -1;
			} while (iVar11 != -1);
		}
		clipAgainstZ();
		if (2 < numcv) {
			iVar11 = numcv + -1;
			if (numcv != 0) {
				in_a1 = (ulong *)&(&cv)[lastcv].vy;
				do {
					iVar11 = iVar11 + -1;
					*(short *)((int)in_a1 + 2) =
						*(short *)((int)in_a1 + 2) - (*(short *)((int)in_a1 + -2) + *(short *)in_a1 * 2);
					in_a1 = in_a1 + -2;
				} while (iVar11 != -1);
			}
			clipAgainstZ();
			if (2 < numcv) {
				iVar11 = numcv + -1;
				if (numcv != 0) {
					in_a1 = (ulong *)0xffffffff;
					psVar8 = &(&cv)[lastcv].vy;
					do {
						iVar11 = iVar11 + -1;
						psVar8[1] = psVar8[1] + *psVar8 * 4;
						psVar8 = psVar8 + -4;
					} while (iVar11 != -1);
				}
				clipAgainstZ();
				if (2 < numcv) {
					iVar11 = numcv + -1;
					if (numcv != 0) {
						in_a1 = (ulong *)0xffffffff;
						psVar8 = &(&cv)[lastcv].vy;
						do {
							iVar11 = iVar11 + -1;
							psVar8[1] = (short)((int)(((uint)(ushort)psVar8[1] + (int)*psVar8 * -2) * 0x10000) >>
								0x11);
							psVar8 = psVar8 + -4;
						} while (iVar11 != -1);
					}
					iVar11 = numcv + -3;
					iVar3 = lastcv;
					spolys = pPVar4;
					while (-1 < iVar11) {
						iVar6 = iVar3 * 8;
						setCopReg(2, in_zero, *(undefined4 *)(&cv + lastcv));
						setCopReg(2, in_at, *(undefined4 *)&(&cv)[lastcv].vz);
						setCopReg(2, &DAT_000da928 + iVar6, *(undefined4 *)(&DAT_000da928 + iVar6));
						setCopReg(2, &Cont_12 + iVar6, *(undefined4 *)(&DAT_000da92c + iVar6));
						setCopReg(2, &cv + lastcv, *(undefined4 *)(&Cont_12 + iVar6));
						setCopReg(2, in_a1, *(undefined4 *)(&DAT_000da924 + iVar6));
						copFunction(2, 0x280030);
						*(undefined *)((int)&spolys->tag + 3) = 6;
						spolys->code = '2';
						spolys->r0 = *(uchar *)&(&cv)[lastcv].pad;
						spolys->g0 = *(uchar *)&(&cv)[lastcv].pad;
						psVar9 = &(&cv)[iVar3 + -1].pad;
						spolys->b0 = *(uchar *)&(&cv)[lastcv].pad;
						*(undefined *)&spolys->x1 = *(undefined *)psVar9;
						*(undefined *)((int)&spolys->x1 + 1) = *(undefined *)psVar9;
						psVar8 = &(&cv)[iVar3 + -2].pad;
						*(undefined *)&spolys->y1 = *(undefined *)psVar9;
						*(undefined *)&spolys[1].tag = *(undefined *)psVar8;
						*(undefined *)((int)&spolys[1].tag + 1) = *(undefined *)psVar8;
						*(undefined *)((int)&spolys[1].tag + 2) = *(undefined *)psVar8;
						uVar1 = getCopReg(2, 0xc);
						*(undefined4 *)&spolys->x0 = uVar1;
						uVar1 = getCopReg(2, 0xd);
						*(undefined4 *)&spolys->x2 = uVar1;
						uVar1 = getCopReg(2, 0xe);
						*(undefined4 *)&spolys[1].r0 = uVar1;
						pDVar5 = current;
						iVar6 = getCopReg(2, 0x11);
						iVar10 = getCopReg(2, 0x12);
						iVar2 = getCopReg(2, 0x13);
						iVar6 = (iVar6 + iVar10 + iVar2) / 3 + LightSortCorrect;
						iVar10 = iVar6 >> 3;
						if (iVar6 < 0x40) {
							iVar10 = 8;
						}
						spolys->tag = spolys->tag & 0xff000000 | current->ot[iVar10] & 0xffffff;
						puVar12 = (uint *)&spolys[1].x0;
						pDVar5->ot[iVar10] = pDVar5->ot[iVar10] & 0xff000000 | (uint)spolys & 0xffffff;
						*(undefined *)((int)&spolys[1].y0 + 1) = 7;
						*(undefined *)((int)&spolys[1].y1 + 1) = 0x24;
						pDVar5 = current;
						spolys[1].x2 = -1;
						spolys[1].y2 = -1;
						*(undefined2 *)&spolys[2].r0 = 0xffff;
						*(undefined2 *)&spolys[2].b0 = 0xffff;
						spolys[2].x1 = -1;
						spolys[2].y1 = -1;
						spolys[2].y0 = 0x20;
						*puVar12 = *puVar12 & 0xff000000 | pDVar5->ot[iVar10] & 0xffffff;
						iVar11 = iVar11 + -1;
						in_a1 = pDVar5->ot + iVar10;
						*in_a1 = *in_a1 & 0xff000000 | (uint)puVar12 & 0xffffff;
						spolys = (POLY_F3 *)&spolys[2].x2;
						pDVar5->primptr = pDVar5->primptr + 0x20;
						iVar3 = iVar3 + -1;
					}
				}
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ sQuad(struct SVECTOR *v0 /*$a0*/, struct SVECTOR *v1 /*$s5*/, struct SVECTOR *v2 /*$s6*/, struct SVECTOR *v3 /*$s4*/)
 // line 1160, offset 0x00077138
	/* begin block 1 */
		// Start line: 1161
		// Start offset: 0x00077138
		// Variables:
	// 		int z1; // $v0
	// 		int z[4]; // stack offset -48

		/* begin block 1.1 */
			// Start line: 1168
			// Start offset: 0x000771B4
			// Variables:
		// 		struct POLY_G4 *pf4; // $t2
		/* end block 1.1 */
		// End offset: 0x000772B4
		// End Line: 1190
	/* end block 1 */
	// End offset: 0x00077524
	// End Line: 1222

	/* begin block 2 */
		// Start line: 3251
	/* end block 2 */
	// End Line: 3252

void sQuad(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	undefined4 uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	POLY_F3 *pPVar6;
	DB *pDVar7;
	undefined4 in_zero;
	undefined4 in_at;
	int iVar8;
	undefined4 in_v1;
	uint *puVar9;

	pPVar6 = spolys;
	if ((((v0->vz < 0x3e9) || (v1->vz < 0x3e9)) || (v2->vz < 0x3e9)) ||
		(bVar1 = v3->vz < 0x3e9, bVar1)) {
		if (((0 < v0->vz) || (0 < v1->vz)) || ((0 < v2->vz || (0 < v3->vz)))) {
			cv._0_4_ = *(undefined4 *)v0;
			SVECTOR_000da938._0_4_ = *(undefined4 *)v1;
			SVECTOR_ARRAY_000da940[0]._0_4_ = *(undefined4 *)v3;
			cv._4_4_ = *(uint *)&v0->vz & 0xffff;
			SVECTOR_ARRAY_000da940[0]._4_4_ = *(uint *)&v3->vz & 0xffff;
			numcv = 3;
			lastcv = 2;
			SVECTOR_000da938._4_4_ = *(uint *)&v1->vz & 0xffff | (uint)(ushort)light_col << 0x10;
			clippedPoly();
			cv._0_4_ = *(undefined4 *)v2;
			SVECTOR_000da938._0_4_ = *(undefined4 *)v1;
			SVECTOR_ARRAY_000da940[0]._0_4_ = *(undefined4 *)v3;
			cv._4_4_ = *(uint *)&v2->vz & 0xffff;
			SVECTOR_ARRAY_000da940[0]._4_4_ = *(uint *)&v3->vz & 0xffff;
			numcv = 3;
			lastcv = 2;
			SVECTOR_000da938._4_4_ = *(uint *)&v1->vz & 0xffff | (uint)(ushort)light_col << 0x10;
			clippedPoly();
		}
	}
	else {
		setCopReg(2, in_zero, *(undefined4 *)v0);
		setCopReg(2, in_at, *(undefined4 *)&v0->vz);
		setCopReg(2, (uint)bVar1, *(undefined4 *)v1);
		setCopReg(2, in_v1, *(undefined4 *)&v1->vz);
		setCopReg(2, v0, *(undefined4 *)v3);
		setCopReg(2, v1, *(undefined4 *)&v3->vz);
		copFunction(2, 0x280030);
		spolys->code = ':';
		*(undefined *)((int)&pPVar6->tag + 3) = 8;
		*(undefined *)&pPVar6->x1 = (undefined)light_col;
		*(undefined *)((int)&pPVar6->x1 + 1) = (undefined)light_col;
		pPVar6->r0 = '\0';
		pPVar6->g0 = '\0';
		pPVar6->b0 = '\0';
		*(undefined *)&pPVar6[1].tag = 0;
		*(undefined *)((int)&pPVar6[1].tag + 1) = 0;
		*(undefined *)((int)&pPVar6[1].tag + 2) = 0;
		*(undefined *)&pPVar6[1].x0 = 0;
		*(undefined *)((int)&pPVar6[1].x0 + 1) = 0;
		*(undefined *)&pPVar6[1].y0 = 0;
		*(undefined *)&pPVar6->y1 = (undefined)light_col;
		uVar2 = getCopReg(2, 0xc);
		*(undefined4 *)&pPVar6->x0 = uVar2;
		uVar2 = getCopReg(2, 0xd);
		*(undefined4 *)&pPVar6->x2 = uVar2;
		uVar2 = getCopReg(2, 0xe);
		*(undefined4 *)&pPVar6[1].r0 = uVar2;
		iVar8 = getCopReg(2, 0x11);
		iVar3 = getCopReg(2, 0x12);
		iVar4 = getCopReg(2, 0x13);
		setCopReg(2, in_zero, *(undefined4 *)v2);
		setCopReg(2, in_at, *(undefined4 *)&v2->vz);
		copFunction(2, 0x180001);
		uVar2 = getCopReg(2, 0xe);
		*(undefined4 *)&pPVar6[1].x1 = uVar2;
		pDVar7 = current;
		iVar5 = getCopReg(2, 0x13);
		iVar8 = (iVar8 + iVar3 + iVar4 + iVar5 >> 2) + LightSortCorrect;
		if (iVar8 < 0) {
			iVar8 = 0;
		}
		iVar8 = iVar8 >> 3;
		puVar9 = (uint *)&pPVar6[1].x2;
		spolys->tag = spolys->tag & 0xff000000 | current->ot[iVar8] & 0xffffff;
		pDVar7->ot[iVar8] = pDVar7->ot[iVar8] & 0xff000000 | (uint)spolys & 0xffffff;
		*(undefined *)((int)&pPVar6[1].y2 + 1) = 7;
		*(undefined *)((int)&pPVar6[2].tag + 3) = 0x24;
		pDVar7 = current;
		*(undefined2 *)&pPVar6[2].r0 = 0xffff;
		*(undefined2 *)&pPVar6[2].b0 = 0xffff;
		pPVar6[2].x1 = -1;
		pPVar6[2].y1 = -1;
		*(undefined2 *)&pPVar6[3].tag = 0xffff;
		*(undefined2 *)((int)&pPVar6[3].tag + 2) = 0xffff;
		pPVar6[2].y2 = 0x20;
		*puVar9 = *puVar9 & 0xff000000 | pDVar7->ot[iVar8] & 0xffffff;
		pDVar7->ot[iVar8] = pDVar7->ot[iVar8] & 0xff000000 | (uint)puVar9 & 0xffffff;
		spolys = (POLY_F3 *)&pPVar6[3].x1;
		pDVar7->primptr = pDVar7->primptr + 0x20;
	}
	return;*/
}





