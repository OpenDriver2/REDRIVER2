#include "driver2.h"
#include "convert.h"
#include "draw.h"
#include "camera.h"

// [D] [T]
void Calc_Object_MatrixYZX(MATRIX *mat, SVECTOR *angles)
{
	InitMatrix(*mat);

	RotMatrixX(angles->vx, mat);
	RotMatrixZ(angles->vz, mat);
	RotMatrixY(angles->vy, mat);
}

// [D] [T]
void _RotMatrixX(MATRIX *m, short ang)
{
	RotMatrixX(ang, m);
}

// [D] [T]
void _RotMatrixY(MATRIX *m, short ang)
{
	RotMatrixY(ang, m);
}

// [D] [T]
void _RotMatrixZ(MATRIX *m, short ang)
{
	RotMatrixZ(ang, m);
}

// [D] [T]
void RotMatrixXYZ(MATRIX *m, SVECTOR *r)
{
	RotMatrix(r, m);
}

// [D] [T]
void _MatrixRotate(VECTOR *pos)
{
	VECTOR temp;

	ApplyRotMatrixLV(pos, &temp);

	pos->vx = temp.vx;
	pos->vy = temp.vy;
	pos->vz = temp.vz;
}

// [D] [T]
void InvertMatrix(MATRIX *a, MATRIX *b)
{
	b->m[0][0] = a->m[0][0];
	b->m[0][1] = a->m[1][0];
	b->m[0][2] = a->m[2][0];
	b->m[1][0] = a->m[0][1];
	b->m[1][1] = a->m[1][1];
	b->m[1][2] = a->m[2][1];
	b->m[2][0] = a->m[0][2];
	b->m[2][1] = a->m[1][2];
	b->m[2][2] = a->m[2][2];
}

// [D] [T]
void BuildWorldMatrix(void)
{
	MATRIX newmatrix;

	newmatrix.m[0][0] = ONE;
	newmatrix.m[1][0] = 0;
	newmatrix.m[2][0] = 0;

	newmatrix.m[0][1] = 0;
	newmatrix.m[1][1] = ONE;
	newmatrix.m[2][1] = 0;

	newmatrix.m[0][2] = 0;
	newmatrix.m[1][2] = 0;
	newmatrix.m[2][2] = ONE;

	_RotMatrixY(&newmatrix, camera_angle.vy);
	_RotMatrixZ(&newmatrix, camera_angle.vz);
	_RotMatrixX(&newmatrix, camera_angle.vx);

	MulMatrix0(&aspect, &newmatrix, &inv_camera_matrix);
	InvertMatrix(&inv_camera_matrix, &camera_matrix);

	face_camera_work.m[0][0] = ONE;
	face_camera_work.m[0][2] = 0;
	face_camera_work.m[2][0] = 0;
	face_camera_work.m[2][2] = ONE;

	RotMatrixY(-(camera_angle.vy & 0xfff), &face_camera_work);
	MulMatrix0(&inv_camera_matrix, &face_camera_work, &face_camera);
}

// [D] [T]
void ScaleCamera(void)
{
	MATRIX temp;
	MATRIX temp2;
	MATRIX scale;
	MATRIX scaledcammat;
	VECTOR pos;
	SVECTOR tempang;

	tempang.vx = 0;
	tempang.vz = 0;
	pos.vz = 0;
	pos.vy = 0;
	pos.vx = 0;
	tempang.vy = camera_angle.vy;
	RotMatrixYXZ(&tempang, &temp);
	InvertMatrix(&temp, &temp2);

	scale.m[0][0] = ONE;
	scale.m[0][1] = 0;
	scale.m[0][2] = 0;

	scale.m[1][0] = 0;
	scale.m[1][1] = ONE;
	scale.m[1][2] = 0;

	scale.m[2][0] = 0;
	scale.m[2][1] = 0;
	scale.m[2][2] = ONE;

	MulMatrix0(&scale, &inv_camera_matrix, &scaledcammat);
	TransMatrix(&scaledcammat, &pos);
	SetRotMatrix(&scaledcammat);
	SetTransMatrix(&scaledcammat);
}

// [D] [T]
void Getlong(char *dest, char *source)
{
	*dest = *source;
	dest[1] = source[1];
	dest[2] = source[2];
	dest[3] = source[3];
}

static int rseed[17]; // offset 0xBD510
static int randomindex = 0;
static int randomcounter = 0;

// [D] [T]
// this function doesn't make difference anyway...
void RandomInit(int i1, int i2)
{
	int step;
	int count;

	int*sd;

	step = 0x3b1cb49;
	
	randomindex = 0;
	randomcounter = 0;
	rseed[0] = i1;
	rseed[1] = i2;

	count = 14;
	sd = rseed + 2;
	
	do {
		*sd++ = step;
		step += 0x1c05e5f;
		
		count--;
	} while (count > -1);

	step = 0;

	while (step < 68)
		Random2(step++);
}

extern int frameStart;

// [D] [T]
int Random2(int step)
{
	return (CameraCnt - frameStart) * (CameraCnt - frameStart) * 0x19660d + 0x3c6ef35fU >> 8 & 0xffff;
}
