#include "THISDUST.H"

#include "LIBGTE.H"
#include "LIBGPU.H"
#include "INLINE_C.H"
#include "GTEREG.H"

#include "GAME/ASM/ASMTEST.H"
#include "GAME/C/CONVERT.H"
#include "GAME/C/CAMERA.H"
#include "GAME/C/DRAW.H"
#include "GAME/C/SYSTEM.H"


struct LineDef_t
{
	VECTOR posA, posB;
	CVECTOR color;
};

LineDef_t gDebug_Lines[512];
int gDebug_numLines = 0;

void DrawDebugOverlays()
{
	VECTOR _zerov = { 0 };

	while(gDebug_numLines > 0)
	{
		LineDef_t& ld = gDebug_Lines[gDebug_numLines-1];

		gte_SetTransVector(&_zerov);
		gte_SetRotMatrix(&inv_camera_matrix);

		SVECTOR a, b;
		a.vx = ld.posA.vx - camera_position.vx;
		a.vy = ld.posA.vy - camera_position.vy;
		a.vz = ld.posA.vz - camera_position.vz;

		b.vx = ld.posB.vx - camera_position.vx;
		b.vy = ld.posB.vy - camera_position.vy;
		b.vz = ld.posB.vz - camera_position.vz;

		gte_ldv0(&a);
		gte_ldv1(&b);

		docop2(0x280030);

		LINE_F2* line = (LINE_F2*)current->primptr;
		setLineF2(line);
		line->x0 = SX0;
		line->y0 = SY0;
		line->x1 = SX1;
		line->y1 = SY1;
		line->r0 = ld.color.r;
		line->g0 = ld.color.g;
		line->b0 = ld.color.b;

		addPrim(current->ot + 2, line);

		current->primptr += sizeof(LINE_F2);
		gDebug_numLines--;
	}
	gDebug_numLines = 0;
}

void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color)
{
	LineDef_t& ld = gDebug_Lines[gDebug_numLines++];
	ld.posA = pointA;
	ld.posB = pointB;
	ld.color = color;
}