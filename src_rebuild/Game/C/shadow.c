#include "driver2.h"
#include "shadow.h"
#include "texture.h"
#include "system.h"
#include "main.h"
#include "camera.h"
#include "draw.h"
#include "dr2roads.h"
#include "players.h"
#include "debris.h"
#include "handling.h"
#include "convert.h"

#include "mission.h"
#include "tile.h"

struct TYRE_TRACK
{
	u_char type;
	u_char shade;
	u_char shade_type;
	u_char surface;
	SVECTOR_NOPAD p1;
	SVECTOR_NOPAD p2;
	SVECTOR_NOPAD p3;
	SVECTOR_NOPAD p4;
};

int gShadowTexturePage;
int gShadowTextureNum;

UV shadowuv;
POLYFT4 shadowpoly;

VECTOR tyre_new_positions[MAX_TYRE_PLAYERS][MAX_TYRE_TRACK_WHEELS];
VECTOR tyre_save_positions[MAX_TYRE_PLAYERS][MAX_TYRE_TRACK_WHEELS];
int smoke_count[MAX_TYRE_PLAYERS][MAX_TYRE_TRACK_WHEELS];

int tyre_track_offset[MAX_TYRE_TRACK_PLAYERS][MAX_TYRE_TRACK_WHEELS];
int num_tyre_tracks[MAX_TYRE_TRACK_PLAYERS][MAX_TYRE_TRACK_WHEELS];

TYRE_TRACK track_buffer[MAX_TYRE_TRACK_PLAYERS][MAX_TYRE_TRACK_WHEELS][64];

// [D] [T]
void InitTyreTracks(void)
{
	int i;
	for (i = 0; i < MAX_TYRE_TRACK_PLAYERS; i++)
	{
		ClearMem((char*)num_tyre_tracks[i], sizeof(num_tyre_tracks[0]));
		ClearMem((char*)tyre_track_offset[i], sizeof(tyre_track_offset[0]));
	}
}

// [A]
void ResetTyreTracks(CAR_DATA* cp, int player_id)
{
	// [A] reset tyre tracks
	if (player_id >= 0 && player_id < MAX_TYRE_TRACK_PLAYERS && cp->controlType != CONTROL_TYPE_NONE)
	{
		GetTyreTrackPositions(cp, player_id);
		SetTyreTrackOldPositions(player_id);
	}
}

// [D] [T]
void GetTyreTrackPositions(CAR_DATA *cp, int player_id)
{
	int loop, track;
	CAR_COSMETICS *car_cos;
	VECTOR WheelPos;
	VECTOR CarPos;

	CarPos.vx = cp->hd.where.t[0];
	CarPos.vy = cp->hd.where.t[1];
	CarPos.vz = cp->hd.where.t[2];

	car_cos = cp->ap.carCos;
	SetRotMatrix(&cp->hd.where);

	track = 0;
	for (loop = (2 / MAX_TYRE_TRACK_WHEELS); loop < 4; loop += (4 / MAX_TYRE_TRACK_WHEELS), track++)
	{
		WheelPos.vx = car_cos->wheelDisp[loop].vx;
		if (loop & 2) 
			WheelPos.vx += 17;
		else
			WheelPos.vx -= 17;

		WheelPos.vy = 0;
		WheelPos.vz = car_cos->wheelDisp[loop].vz;

		_MatrixRotate(&WheelPos);

		WheelPos.vx += CarPos.vx;
		WheelPos.vy = CarPos.vy;
		WheelPos.vz += CarPos.vz;

		tyre_new_positions[player_id][track].vx = WheelPos.vx;
		tyre_new_positions[player_id][track].vz = WheelPos.vz;
		tyre_new_positions[player_id][track].vy = MapHeight(&WheelPos);
	}
}


// [D] [T]
void SetTyreTrackOldPositions(int player_id)
{
	tyre_save_positions[player_id][0] = tyre_new_positions[player_id][0];
	tyre_save_positions[player_id][1] = tyre_new_positions[player_id][1];
	tyre_save_positions[player_id][2] = tyre_new_positions[player_id][2];
	tyre_save_positions[player_id][3] = tyre_new_positions[player_id][3];
}

// [D] [T]
void AddTyreTrack(int wheel, int tracksAndSmoke, int player_id, int continuous_track)
{
	static int Cont[4] = { 0, 0, 0, 0 };

	short x, z;
	sdPlane *SurfaceDataPtr;
	char trackSurface;
	TYRE_TRACK *tt_p;
	VECTOR *newtp;
	VECTOR *oldtp;
	VECTOR New1, New2, New3, New4;
	VECTOR SmokeDrift, SmokePosition, grass_vector;

	newtp = &tyre_new_positions[player_id][wheel];

	// [A] disabled due to MP and SP bugs
	/*
	if (newtp->vx - camera_position.vx + 20480 > 40960)
		return;

	if (newtp->vz - camera_position.vz + 20480 > 40960)
		return;*/

	if (tracksAndSmoke != 0) 
	{
		oldtp = &tyre_save_positions[player_id][wheel];

		tt_p = track_buffer[player_id][wheel] + (tyre_track_offset[player_id][wheel] + num_tyre_tracks[player_id][wheel] & 0x3f);

		SurfaceDataPtr = sdGetCell(newtp);

		// check surface type
		if (SurfaceDataPtr != NULL) 
		{
			if (SurfaceDataPtr->surface == SURF_WATER)
				return;

			if (SurfaceDataPtr->surface == SURF_GRASS)
			{
				tt_p->surface = 2;
				player[player_id].onGrass = 1;
			}
			else
			{
				tt_p->surface = 1;
			}
		}
		else 
		{
			tt_p->surface = 1;
		}

		trackSurface = tt_p->surface;
	}
	else
	{
		SurfaceDataPtr = sdGetCell(newtp);
		trackSurface = 1;

		if (SurfaceDataPtr->surface == SURF_WATER)
			return;

		if (SurfaceDataPtr->surface == SURF_GRASS)
			trackSurface = 2;
	}
	
	SmokePosition.vx = newtp->vx;
	SmokePosition.vz = newtp->vz;
	SmokePosition.vy = -50 - newtp->vy;

	// make smoke
	if ((smoke_count[player_id][wheel]++ & 3) == 1)
	{
		GetSmokeDrift(&SmokeDrift);

		if (trackSurface == 2) 
		{
			grass_vector.vx = 0;
			grass_vector.vy = 50;
			grass_vector.vz = 0;
			grass_vector.pad = 0;

			Setup_Smoke(&SmokePosition, 50, 500, SMOKE_BROWN, 0, &SmokeDrift, 0);
			Setup_Sparks(&SmokePosition, &grass_vector, 5, 2);
		}
		else if (wetness == 0) 
		{
			Setup_Smoke(&SmokePosition, 50, 500, SMOKE_WHITE, 0, &SmokeDrift, 0);
		}
	}

	// lay down tracks to buffer
	if (tracksAndSmoke)
	{
		int dir;
		dir = -ratan2(oldtp->vz - newtp->vz, oldtp->vx - newtp->vx);

		x = FixHalfRound(RSIN(dir) * 35, 13);
		z = FixHalfRound(RCOS(dir) * 35, 13);
		
		New1.vy = oldtp->vy + 10;
		New3.vy = newtp->vy + 10;
		New2.vx = oldtp->vx;
		New1.vx = New2.vx + x;
		New2.vz = oldtp->vz;
		New1.vz = New2.vz + z;
		New2.vx = New2.vx - x;
		New2.vz = New2.vz - z;
		New4.vx = newtp->vx;
		New3.vx = New4.vx + x;
		New4.vz = newtp->vz;
		New3.vz = New4.vz + z;
		New4.vx = New4.vx - x;
		New4.vz = New4.vz - z;

		if (num_tyre_tracks[player_id][wheel] == 64)
		{
			tyre_track_offset[player_id][wheel]++;
			tyre_track_offset[player_id][wheel] &= 63;
		}
		else 
		{
			num_tyre_tracks[player_id][wheel]++;
		}

		if (Cont[wheel] == 1 && continuous_track == 1)
			tt_p->type = 1;
		else
			tt_p->type = 0;

		Cont[wheel] = 1;

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

// [D] [T]
void DrawTyreTracks(void)
{
	char last_duff;
	POLY_FT4 *poly;
	TYRE_TRACK *tt_p;
	int index, loop;
	int player_id, wheel_loop;
	POLY_FT4 *lasttyre;
	SVECTOR ps[4];
	int z;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	for (player_id = 0; player_id < MAX_TYRE_TRACK_PLAYERS; player_id++)
	{
		for (wheel_loop = 0; wheel_loop < MAX_TYRE_TRACK_WHEELS; wheel_loop++)
		{
			lasttyre = NULL;
			last_duff = 1;
			index = tyre_track_offset[player_id][wheel_loop];

			for (loop = 0; loop < num_tyre_tracks[player_id][wheel_loop]; loop++)
			{
				tt_p = track_buffer[player_id][wheel_loop] + index;

				index++;
				index &= 63;

				if (tt_p->type == 2)
					continue;

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

				poly = (POLY_FT4*)current->primptr;

				z = 0;

				if (lasttyre != NULL && tt_p->type != 0 && !last_duff)
				{
					last_duff = 1;

					if (ps[2].vx + 9000 <= 18000 && ps[2].vz + 9000 <= 18000)
					{
						gte_ldv0(&ps[2]);
						gte_rtps();

						gte_stsxy(&poly->x2);

						gte_stsz(&z);

						gte_ldv0(&ps[3]);
						gte_rtps();

						*(u_int*)&poly->x0 = *(u_int*)&lasttyre->x2;
						*(u_int*)&poly->x1 = *(u_int*)&lasttyre->x3;

						gte_stsxy(&poly->x3);
					}
				}
				else
				{
					last_duff = 1;

					if (ps[0].vx + 0x5000 <= 0xa000 && ps[0].vz + 0x5000 <= 0xa000)
					{
						gte_ldv3(&ps[0], &ps[1], &ps[2]);
						gte_rtpt();

						gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

						gte_stsz(&z);

						gte_ldv0(&ps[3]);
						gte_rtps();

						gte_stsxy(&poly->x3);
					}
					else
					{
						tt_p->type = 2;
					}
				}

				if (z > 50)
				{
					setPolyFT4(poly);
					setSemiTrans(poly, 1);

					if (tt_p->surface == 1)
					{
						poly->r0 = poly->g0 = poly->b0 = 26;
					}
					else
					{
						poly->r0 = 17;
						poly->g0 = poly->b0 = 35;
					}

					*(ushort*)&poly->u0 = *(ushort*)&gTyreTexture.coords.u0;
					*(ushort*)&poly->u1 = *(ushort*)&gTyreTexture.coords.u1;
					*(ushort*)&poly->u2 = *(ushort*)&gTyreTexture.coords.u2;
					*(ushort*)&poly->u3 = *(ushort*)&gTyreTexture.coords.u3;

					poly->tpage = gTyreTexture.tpageid | 0x40;
					poly->clut = gTyreTexture.clutid;

					addPrim(current->ot + (z >> 3), poly);
					current->primptr += sizeof(POLY_FT4);

					lasttyre = poly;
					last_duff = 0;
				}
			}
		}
	}

}

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

// [D] [A] - this is a fuckery
void SubdivShadow(long z0, long z1, long z2, long z3, POLY_FT4 *sps)
{
	// [A] we already have better car shadow code. This is UNUSED anyway
	POLY_FT4 *spd;

	spd = (POLY_FT4 *)current->primptr;
	current->primptr += sizeof(POLY_FT4);

	memcpy((u_char*)spd, (u_char*)sps, sizeof(POLY_FT4));

	addPrim(current->ot + (z0 * 2 + z3 * 6 >> 6), spd);
}


extern VECTOR dummy;

// [D] [T] [A] better shadow code
void PlaceShadowForCar(VECTOR *shadowPoints, int subdiv, int zOfs, int flag)
{	
	MVERTEX subdivVerts[5][5];
	SVECTOR points[4];

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

	plotContext.clut = (u_int)(*plotContext.ptexture_cluts)[pft4->texture_set][pft4->texture_id];
	plotContext.tpage = ((u_int)(*plotContext.ptexture_pages)[pft4->texture_set] | 0x40);

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

static int numcv;
static int lastcv;
static SVECTOR cv[12];

// [D] - refactored - NOT TESTED YET
int clipAgainstZ(void)
{
	SVECTOR *curr;
	SVECTOR *prev;
	int _tmp;
	int temp;
	int d;
	SVECTOR *dst;
	int flags;
	int srccount;
	int dstcount;

	dstcount = 0;

	curr = cv + lastcv;
	dst = cv + lastcv + 2;
	srccount = numcv-1;

	flags = ((curr + numcv * 0x1fffffff)[1].vz > 0) << 1;
	prev = curr + numcv * 0x1fffffff + 1;

	do {

		if (srccount < 0) 
		{
			numcv = dstcount;
			lastcv = lastcv + 2;
			return 0;
		}

		flags >>= 1;

		if (curr->vz > 0)
			flags |= 2;

		if (flags == 1) 
		{
			d = prev->vz - curr->vz;
			
			dst->vx = (curr->vx * prev->vz - prev->vx * curr->vz) / d;
			dst->vy = (curr->vy * prev->vz - prev->vy * curr->vz) / d;
			dst->pad = (curr->pad * prev->vz - prev->pad * curr->vz) / d;
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
				temp = curr->vz;
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

			d = prev->vz - curr->vz;

			dst->vx = (curr->vx * prev->vz - prev->vx * curr->vz) / d;
			dst->vy = (curr->vy * prev->vz - prev->vy * curr->vz) / d;
			dst->pad = (curr->pad * prev->vz - prev->pad * curr->vz) / d;
			dst->vz = 0;
			_tmp = curr->vz;
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
	// 		POLY_G3 *pg3; // $s0
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
	u_int *puVar12;

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
							psVar8[1] = (short)((int)(((u_int)(ushort)psVar8[1] + (int)*psVar8 * -2) * 0x10000) >>
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
						puVar12 = (u_int *)&spolys[1].x0;
						pDVar5->ot[iVar10] = pDVar5->ot[iVar10] & 0xff000000 | (u_int)spolys & 0xffffff;
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
						*in_a1 = *in_a1 & 0xff000000 | (u_int)puVar12 & 0xffffff;
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


// [D] [T]
void sQuad(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3, CVECTOR* light_col, int LightSortCorrect)
{
	int z1;
	int z[4];
	
	POLY_G4 *poly;

	poly = (POLY_G4*)current->primptr;

#if 0
	if (v0->vz < 1001 || v1->vz < 1001 || v2->vz < 1001 || v3->vz < 1001)
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
#endif
	{
		gte_ldv3(v0, v1, v3);

		gte_rtpt();

		setPolyG4(poly);
		setSemiTrans(poly, 1);

		poly->r1 = light_col->r;
		poly->g1 = light_col->g;
		poly->b1 = light_col->b;

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





