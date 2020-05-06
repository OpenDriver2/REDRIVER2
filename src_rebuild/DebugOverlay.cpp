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
#include "GAME/C/PRES.H"
#include "GAME/C/SPOOL.H"

int gDisplayDrawStats = 0;

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
		setSemiTrans(line, 1);
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

	char tempBuf[128];

	int primTabLeft = current->primptr - current->primtab;

	if (gDisplayDrawStats)
	{
		sprintf(tempBuf, "Primtab: %d of %d", primTabLeft, 0x1a180);
		PrintString(tempBuf, 10, 80);

		extern volatile int spoolactive;
		sprintf(tempBuf, "Spooling: %d spec: %d, active: %d", doSpooling, allowSpecSpooling, spoolactive);
		PrintString(tempBuf, 10, 90);
	}
}

void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color)
{
	if (gDebug_numLines + 1 > 512)
		return;

	LineDef_t& ld = gDebug_Lines[gDebug_numLines++];
	ld.posA = pointA;
	ld.posB = pointB;
	ld.color = color;

	ld.posA.vy *= -1;
	ld.posB.vy *= -1;
}

void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color)
{
	if (gDebug_numLines + 1 > 512)
		return;

	LineDef_t& ld = gDebug_Lines[gDebug_numLines++];
	ld.posA = pointA;
	ld.posB = pointB;
	ld.color = color;

	ld.posA.vx += ofs.vx;
	ld.posA.vy += ofs.vy;
	ld.posA.vz += ofs.vz;

	ld.posB.vx += ofs.vx;
	ld.posB.vy += ofs.vy;
	ld.posB.vz += ofs.vz;

	ld.posA.vy *= -1;
	ld.posB.vy *= -1;
}