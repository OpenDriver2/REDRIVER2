#include "DRIVER2.H"
#include "SHADOW.H"
#include "TEXTURE.H"
#include "SYSTEM.H"
#include "MAIN.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "DR2ROADS.H"
#include "PLAYERS.H"
#include "DEBRIS.H"
#include "HANDLING.H"
#include "CONVERT.H"

#include "INLINE_C.H"
#include "STRINGS.H"
#include "MISSION.H"
#include "TILE.H"

int gShadowTexturePage;
int gShadowTextureNum;

UV shadowuv;
POLYFT4 shadowpoly;

VECTOR tyre_new_positions[4];
VECTOR tyre_save_positions[4];
int tyre_track_offset[4];
int num_tyre_tracks[4];
TYRE_TRACK track_buffer[4][64];
int smoke_count[4];


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

// [D] [T]
void InitTyreTracks(void)
{
	int i;

	i = 0;
	while (i < 4)
	{
		num_tyre_tracks[i] = 0;
		tyre_track_offset[i] = 0;
		i++;
	}
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

// [D] [T]
void GetTyreTrackPositions(_CAR_DATA *cp, int player_id)
{
	int track;
	uint loop;
	CAR_COSMETICS *car_cos;
	VECTOR WheelPos;
	VECTOR CarPos;

	CarPos.vx = cp->hd.where.t[0];
	CarPos.vy = cp->hd.where.t[1];
	CarPos.vz = cp->hd.where.t[2];

	car_cos = (cp->ap).carCos;
	SetRotMatrix(&cp->hd.drawCarMat);

	loop = 0;

	do {
		if (loop & 2) 
			WheelPos.vx = car_cos->wheelDisp[loop].vx + 17;
		else
			WheelPos.vx = car_cos->wheelDisp[loop].vx - 17;

		WheelPos.vy = 0;
		WheelPos.vz = -car_cos->wheelDisp[loop + 1 & 3].vz;

		_MatrixRotate(&WheelPos);

		WheelPos.vx += CarPos.vx;
		WheelPos.vy = CarPos.vy;
		WheelPos.vz += CarPos.vz;

		track = player_id * 2 + (loop / 2);

		tyre_new_positions[track].vx = WheelPos.vx;
		tyre_new_positions[track].vz = WheelPos.vz;
		tyre_new_positions[track].vy = MapHeight(&WheelPos);

		loop += 2;
	} while (loop < 4);
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

// [D] [T]
void SetTyreTrackOldPositions(int player_id)
{
	int idx = player_id * 2;

	tyre_save_positions[idx].vx = tyre_new_positions[idx].vx;
	tyre_save_positions[idx].vy = tyre_new_positions[idx].vy;
	tyre_save_positions[idx].vz = tyre_new_positions[idx].vz;

	tyre_save_positions[idx + 1].vx = tyre_new_positions[idx + 1].vx;
	tyre_save_positions[idx + 1].vy = tyre_new_positions[idx + 1].vy;
	tyre_save_positions[idx + 1].vz = tyre_new_positions[idx + 1].vz;
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

// [D]
void AddTyreTrack(int wheel, int tracksAndSmoke, int padid)
{
	static int Cont[4] = { 0, 0, 0, 0 };

	short sVar1;
	short sVar2;
	_sdPlane *SurfaceDataPtr;
	long lVar3;
	int *piVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	int iVar8;
	char trackSurface;
	TYRE_TRACK *tt_p;
	VECTOR *newtp;
	VECTOR *oldtp;
	VECTOR unk;
	VECTOR New1;
	VECTOR New2;
	VECTOR New3;
	VECTOR New4;
	VECTOR psxoffset;
	VECTOR SmokeDrift;
	VECTOR SmokePosition;
	ROUTE_DATA routeData;
	VECTOR grass_vector;

	newtp = &tyre_new_positions[wheel];

	if (newtp->vx - camera_position.vx + 0x5000 > 0xa000)
		return;

	if (newtp->vz - camera_position.vz + 0x5000 > 0xa000)
		return;

	if (tracksAndSmoke == 0) 
	{
		SurfaceDataPtr = sdGetCell(newtp);
		trackSurface = 1;
		if (SurfaceDataPtr->surface == 6)
			return;

		iVar5 = wheel / 4;

		if (SurfaceDataPtr->surface == 4)
			trackSurface = 2;
	}
	else
	{
		iVar5 = wheel * 4;

		uVar7 = tyre_track_offset[wheel] + num_tyre_tracks[wheel] & 0x3f;
		oldtp = &tyre_save_positions[wheel];

		tt_p = track_buffer[wheel] + uVar7;
		SurfaceDataPtr = sdGetCell(newtp);

		if (SurfaceDataPtr == NULL) 
		{
		LAB_00075698:
			tt_p->surface = 1;
		}
		else 
		{
			if (SurfaceDataPtr->surface == 6) 
				return;

			if (SurfaceDataPtr->surface != 4) 
				goto LAB_00075698;

			tt_p->surface = 2;
			player[padid].onGrass = 1;
		}

		trackSurface = tt_p->surface;
	}

	uVar7 = *(uint *)((int)smoke_count + iVar5);
	*(uint *)((int)smoke_count + iVar5) = uVar7 + 1;

	psxoffset.vx = newtp->vx;
	psxoffset.vz = newtp->vz;
	psxoffset.vy = -50 - newtp->vy;
	
	if ((uVar7 & 3) == 1) 
	{
		GetSmokeDrift(&SmokeDrift);

		if (trackSurface == 2) 
		{
			grass_vector.vx = 0;
			grass_vector.vy = 50;
			grass_vector.vz = 0;
			grass_vector.pad = 0;

			Setup_Smoke(&psxoffset, 100, 500, 3, 0, &SmokeDrift, 0);
			Setup_Sparks(&psxoffset, &grass_vector, 5, 2);
		}
		else if (wetness == 0) 
		{
			Setup_Smoke(&psxoffset, 100, 500, 2, 0, &SmokeDrift, 0);
		}
	}

	if (tracksAndSmoke != 0)
	{
		lVar3 = ratan2(oldtp->vz - newtp->vz, oldtp->vx - newtp->vx);

		iVar6 = rcossin_tbl[(-lVar3 & 0xfffU) * 2 + 1] * 0x23;
		iVar8 = rcossin_tbl[(-lVar3 & 0xfffU) * 2] * 0x23;

		New1.vy = oldtp->vy + 10;
		New3.vy = newtp->vy + 10;
		New2.vx = oldtp->vx;
		sVar1 = (iVar8 >> 0xd);
		New1.vx = New2.vx + sVar1;
		New2.vz = oldtp->vz;
		sVar2 = (iVar6 >> 0xd);
		New1.vz = New2.vz + sVar2;
		New2.vx = New2.vx - sVar1;
		New2.vz = New2.vz - sVar2;
		New4.vx = newtp->vx;
		New3.vx = New4.vx + sVar1;
		New4.vz = newtp->vz;
		New3.vz = New4.vz + sVar2;
		New4.vx = New4.vx - sVar1;
		New4.vz = New4.vz - sVar2;

		iVar6 = *(int *)((int)&num_tyre_tracks + iVar5);

		if (iVar6 == 0x40)
		{
			piVar4 = (int *)((int)&tyre_track_offset + iVar5);
			iVar8 = *piVar4;
			iVar6 = iVar8 + 1;
			*piVar4 = iVar6;

			if (iVar6 > 63) 
				*piVar4 = iVar8 - 63;

		}
		else 
		{
			*(int *)((int)&num_tyre_tracks + iVar5) = iVar6 + 1;
		}

		if ((*(int *)((int)Cont + iVar5) == 1) && (continuous_track == 1))
			tt_p->type = 1;
		else
			tt_p->type = 0;

		*(int *)((int)Cont + iVar5) = 1;

		tt_p->p1.vx = New1.vx;
		tt_p->p1.vy = New1.vy;
		tt_p->p1.vz = New1.vz;
		
		tt_p->p2.vx = New2.vx;
		tt_p->p2.vy = New1.vy;
		tt_p->p2.vz = New2.vz;
		
		tt_p->p3.vx = New3.vx;
		tt_p->p3.vy = New3.vy;
		tt_p->p3.vz = New3.vz;
		
		tt_p->p4.vx = New4.vx;
		tt_p->p4.vy = New3.vy;
		tt_p->p4.vz = New4.vz;
	}
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

// [D]
void DrawTyreTracks(void)
{
	bool bVar2;
	bool bVar3;
	unsigned char col;
	POLY_FT4 *poly;
	TYRE_TRACK *tt_p;
	int iVar11;
	int iVar13;
	int iVar14;
	POLY_FT4 *lasttyre;
	SVECTOR ps[4];
	int z;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	iVar14 = 0;

	do {
		if (num_tyre_tracks[iVar14] != 0)
		{
			lasttyre = NULL;
			bVar2 = true;
			iVar11 = tyre_track_offset[iVar14];
			iVar13 = 0;

			if (0 < num_tyre_tracks[iVar14])
			{
				do {
					tt_p = track_buffer[iVar14] + iVar11;

					iVar11++;

					if (iVar11 == 64) 
						iVar11 = 0;

					if (tt_p->type != 2)
					{
						ps[0].vx = tt_p->p1.vx - camera_position.vx;
						ps[0].vy = -camera_position.vy - tt_p->p1.vy;
						ps[0].vz = tt_p->p1.vz - camera_position.vz;

						ps[1].vx = tt_p->p2.vx - camera_position.vx;
						ps[1].vy = -camera_position.vy - tt_p->p2.vy;
						ps[1].vz = tt_p->p2.vz - camera_position.vz;

						ps[2].vx = tt_p->p3.vx - camera_position.vx;
						ps[2].vy = -camera_position.vy - tt_p->p3.vy;
						ps[2].vz = tt_p->p3.vz - camera_position.vz;

						ps[3].vx = tt_p->p4.vx - camera_position.vx;
						ps[3].vy = -camera_position.vy - tt_p->p4.vy;
						ps[3].vz = tt_p->p4.vz - camera_position.vz;

						if ((lasttyre == NULL || tt_p->type == 0) || (bVar3 = true, bVar2))
						{
							bVar2 = true;

							if (0x5000 + ps[0].vx < 0xa001)
							{
								if (0x5000 + ps[0].vz < 0xa001)
								{
									poly = (POLY_FT4 *)current->primptr;

									gte_ldv3(&ps[0], &ps[1], &ps[2]);
									gte_rtpt();

									gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

									gte_stsz(&z);

									gte_ldv0(&ps[3]);
									gte_rtps();

									gte_stsxy(&poly->x3);

									if (0x32 < z)
										goto LAB_00075dbc;

									goto LAB_00075eec;
								}
							}

							tt_p->type = 2;
						}
						else
						{
							poly = (POLY_FT4 *)current->primptr;
							bVar2 = bVar3;

							if (0x2328 + ps[2].vx <= 0x4650)
							{
								if (0x2328 + ps[2].vz < 0x4651)
								{
									gte_ldv0(&ps[2]);
									gte_rtps();

									gte_stsxy(&poly->x2);

									gte_stsz(&z);

									gte_ldv0(&ps[3]);
									gte_rtps();

									if (50 < z)
									{
										*(uint *)&poly->x0 = *(uint *)&lasttyre->x2;
										*(uint *)&poly->x1 = *(uint *)&lasttyre->x3;

										gte_stsxy(&poly->x3);

									LAB_00075dbc:
										setPolyFT4(poly);
										setSemiTrans(poly, 1);

										if (tt_p->surface == 1)
										{
											col = 0x1a;
											poly->r0 = 0x1a;
										}
										else
										{
											col = 35;
											poly->r0 = 0x11;
										}

										poly->g0 = col;
										poly->b0 = col;

										poly->u0 = gTyreTexture.coords.u0;
										poly->v0 = gTyreTexture.coords.v0;
										poly->u1 = gTyreTexture.coords.u1;
										poly->v1 = gTyreTexture.coords.v1;
										poly->u2 = gTyreTexture.coords.u2;
										poly->v2 = gTyreTexture.coords.v2;
										poly->u3 = gTyreTexture.coords.u3;
										poly->v3 = gTyreTexture.coords.v3;
										poly->tpage = gTyreTexture.tpageid | 0x40;
										poly->clut = gTyreTexture.clutid;

										addPrim(current->ot + (z >> 3), poly);
										current->primptr += sizeof(POLY_FT4);

										lasttyre = poly;
										bVar2 = false;
									}
								}
							}
						}
					}
				LAB_00075eec:
					iVar13++;
				} while (iVar13 < num_tyre_tracks[iVar14]);
			}
		}
		iVar14++;
	} while (iVar14 < 4);
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

// [D] [T] [A] now better shadow code
void InitShadow(void)
{
	TEXINF *texinf;
	TPAN pos;

	texinf = GetTextureInfoName("CARSHAD", &pos);

	gShadowTexturePage = pos.texture_page;
	gShadowTextureNum = pos.texture_number;

	shadowuv.u0 = texinf->x;
	shadowuv.u1 = texinf->x + texinf->width - 1;
	shadowuv.v1 = texinf->y;
	shadowuv.u2 = texinf->x;
	shadowuv.v2 = texinf->y + texinf->height - 1;
	shadowuv.u3 = texinf->x + texinf->width - 1;
	shadowuv.v3 = texinf->y + texinf->height - 1;
	shadowuv.v0 = texinf->y;

	if (GameLevel == 3) 
	{
		shadowuv.v1 += 1;
		shadowuv.v0 += 1;
	}

	shadowpoly.id = 4;
	shadowpoly.texture_set = pos.texture_page;
	shadowpoly.texture_id = pos.texture_number;

	shadowpoly.v0 = 0;
	shadowpoly.v1 = 1;
	shadowpoly.v2 = 2;
	shadowpoly.v3 = 3;

	*(ushort*)&shadowpoly.uv0 = *(ushort*)&shadowuv.u0;
	*(ushort*)&shadowpoly.uv1 = *(ushort*)&shadowuv.u1;
	*(ushort*)&shadowpoly.uv2 = *(ushort*)&shadowuv.u3;
	*(ushort*)&shadowpoly.uv3 = *(ushort*)&shadowuv.u2;
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
		*(uint *)&pPVar10->u3 = *(uint *)&sps->u3;

		pPVar10->tpage = sps->tpage;
		pPVar10->clut = sps->clut;

		pPVar10 = pPVar10 + 1;
		iVar24 = iVar24 + -1;
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
	current->primptr += sizeof(POLY_FT4);

	memcpy(spd, sps, sizeof(POLY_FT4));

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

// [D] [T] [A] better shadow code
void PlaceShadowForCar(VECTOR *shadowPoints, int subdiv, int zOfs, int flag)
{	
	MVERTEX subdivVerts[5][5];
	SVECTOR points[4];
	_pct plotContext;

	points[0].vx = shadowPoints[0].vx - camera_position.vx;
	points[0].vy = -shadowPoints[0].vy - camera_position.vy;
	points[0].vz = shadowPoints[0].vz - camera_position.vz;

	points[1].vx = shadowPoints[1].vx - camera_position.vx;
	points[1].vy = -shadowPoints[1].vy - camera_position.vy;
	points[1].vz = shadowPoints[1].vz - camera_position.vz;

	points[2].vx = shadowPoints[3].vx - camera_position.vx;
	points[2].vy = -shadowPoints[3].vy - camera_position.vy;
	points[2].vz = shadowPoints[3].vz - camera_position.vz;

	points[3].vx = shadowPoints[2].vx - camera_position.vx;
	points[3].vy = -shadowPoints[2].vy - camera_position.vy;
	points[3].vz = shadowPoints[2].vz - camera_position.vz;

	gte_SetTransVector(&dummy);
	gte_SetRotMatrix(&inv_camera_matrix);

	plotContext.primptr = current->primptr;
	plotContext.ptexture_pages = (ushort(*)[128])texture_pages;
	plotContext.ptexture_cluts = (ushort(*)[128][32])texture_cluts;
	plotContext.ot = current->ot + 10 + zOfs;
	plotContext.flags = flag;
	plotContext.colour = 80 | (80 << 8) | (80 << 16) | 0x2e000000;
	plotContext.current = current;

	POLYFT4* pft4 = &shadowpoly;

	plotContext.clut = (uint)(*plotContext.ptexture_cluts)[pft4->texture_set][pft4->texture_id] << 0x10;
	plotContext.tpage = ((uint)(*plotContext.ptexture_pages)[pft4->texture_set] | 0x40) << 0x10;

	copyVector(&subdivVerts[0][0], &points[pft4->v0]);
	subdivVerts[0][0].uv.val = *(ushort*)&pft4->uv0;

	copyVector(&subdivVerts[0][1], &points[pft4->v1]);
	subdivVerts[0][1].uv.val = *(ushort*)&pft4->uv1;

	copyVector(&subdivVerts[0][2], &points[pft4->v3]);
	subdivVerts[0][2].uv.val = *(ushort*)&pft4->uv3;

	copyVector(&subdivVerts[0][3], &points[pft4->v2]);
	subdivVerts[0][3].uv.val = *(ushort*)&pft4->uv2;

	makeMesh((MVERTEX(*)[5][5])subdivVerts, subdiv, subdiv);
	drawMesh((MVERTEX(*)[5][5])subdivVerts, subdiv, subdiv, &plotContext);

	current->primptr = plotContext.primptr;
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

static int numcv;
static int lastcv;
static SVECTOR cv[12];

// [D]
int clipAgainstZ(void)
{
	SVECTOR *_curr;
	SVECTOR *prev;
	int _tmp;
	int temp;
	int iVar1;
	SVECTOR *dst;
	SVECTOR *curr;
	uint flags;
	int srccount;
	int dstcount;

	dstcount = 0;

	curr = cv + lastcv;
	dst = cv + lastcv + 2;
	srccount = numcv-1;

	flags = (uint)((curr + numcv * 0x1fffffff)[1].vz > 0) << 1;
	prev = curr + numcv * 0x1fffffff + 1;

	do {
		_curr = curr;
		if (srccount < 0) 
		{
			numcv = dstcount;
			lastcv = lastcv + 2;
			return 0;
		}

		flags >>= 1;

		if (_curr->vz > 0)
			flags |= 2;

		if (flags == 1) 
		{
			iVar1 = prev->vz - _curr->vz;
			
			dst->vx = (_curr->vx * prev->vz - prev->vx * _curr->vz) / iVar1;
			dst->vy = (_curr->vy * prev->vz - prev->vy * _curr->vz) / iVar1;
			dst->pad = (_curr->pad * prev->vz - prev->pad * _curr->vz) / iVar1;
			dst->vz = 0;
		LAB_00076ca4:
			dst--;
			dstcount++;
		}
		else if (flags < 2)
		{
			if (flags != 0)
			{
			LAB_00076c84:
				temp = _curr->vz;
				dst->vx = prev->vx;
				dst->vz = temp;
				goto LAB_00076ca4;
			}
		}
		else
		{
			if (flags != 2)
			{
				goto LAB_00076c84;
			}

			iVar1 = prev->vz - _curr->vz;

			dst->vx = (short)((_curr->vx * prev->vz - prev->vx * _curr->vz) / iVar1);
			dst->vy = (short)((_curr->vy * prev->vz - prev->vy * _curr->vz) / iVar1);
			dst->pad = (short)((_curr->pad * prev->vz - prev->pad * _curr->vz) / iVar1);
			dst->vz = 0;
			_tmp = _curr->vz;
			dst[-1].vx = prev->vx;
			dst[-1].vz = _tmp;
			dst -= 2;
			dstcount += 2;
		}

		srccount--;
		prev = curr--;
	} while (true);
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
	int track;
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
						track = getCopReg(2, 0x13);
						iVar6 = (iVar6 + iVar10 + track) / 3 + LightSortCorrect;
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

// [D]
void sQuad(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3, int light_col, int LightSortCorrect)
{
	int z1;
	int z[4];
	
	POLY_G4 *poly;

	poly = (POLY_G4*)current->primptr;

	if (false) // (v0->vz < 1001 || v1->vz < 1001 || v2->vz < 1001 || v3->vz < 1001)
	{
		if (v0->vz > 0 || v1->vz > 0 || v2->vz > 0 || v3->vz > 0)
		{
			cv[0] = *v0;
			cv[1] = *v1;
			cv[2] = *v3;

			cv[1].pad = light_col;

			numcv = 3;
			lastcv = 2;
			clippedPoly();

			cv[0] = *v2;
			cv[1] = *v1;
			cv[2] = *v3;

			cv[1].pad = light_col;

			numcv = 3;
			lastcv = 2;
			clippedPoly();
		}
	}
	else 
	{
		gte_ldv3(v0, v1, v3);

		gte_rtpt();

		setPolyG4(poly);
		setSemiTrans(poly, 1);

		poly->r1 = light_col;
		poly->g1 = light_col;
		poly->b1 = light_col;

		poly->r0 = 0;
		poly->g0 = 0;
		poly->b0 = 0;

		poly->r2 = 0;
		poly->g2 = 0;
		poly->b2 = 0;

		poly->r3 = 0;
		poly->g3 = 0;
		poly->b3 = 0;

		gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

		gte_stsz3(&z[0], &z[1], &z[2]);

		gte_ldv0(v2);

		gte_rtps();

		gte_stsxy(&poly->x3);

		gte_stsz(&z[3]);
		
		z1 = (z[0] + z[1] + z[2] + z[3] >> 2) + LightSortCorrect;

		if (z1 < 0)
			z1 = 0;
	
		z1 >>= 3;

		addPrim(current->ot + z1, poly);
		current->primptr += sizeof(POLY_G4);

		POLY_FT3* null = (POLY_FT3*)current->primptr;

		setPolyFT3(null);
		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = 0x20;

		addPrim(current->ot + z1, null);
		current->primptr += sizeof(POLY_FT3);
	}
}





