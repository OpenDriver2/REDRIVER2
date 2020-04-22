#include "THISDUST.H"
#include "CONVERT.H"
#include "DRAW.H"
#include "CAMERA.H"

// decompiled code
// original method signature: 
// void /*$ra*/ Calc_Object_MatrixYZX(struct MATRIX *mat /*$s0*/, struct SVECTOR *angles /*$s1*/)
 // line 149, offset 0x0002d3f8
	/* begin block 1 */
		// Start line: 298
	/* end block 1 */
	// End Line: 299

void Calc_Object_MatrixYZX(MATRIX *mat, SVECTOR *angles)
{
	UNIMPLEMENTED();
	/*
	mat->m[0] = 0x1000;
	mat->m[1] = 0;
	mat->m[2] = 0;
	mat->m[3] = 0;
	mat->m[4] = 0x1000;
	mat->m[5] = 0;
	mat->m[6] = 0;
	mat->m[7] = 0;
	mat->m[8] = 0x1000;
	RotMatrixX((int)angles->vx, mat);
	RotMatrixZ((int)angles->vz, mat);
	RotMatrixY((int)angles->vy, mat);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ _RotMatrixX(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
 // line 182, offset 0x0002d470
	/* begin block 1 */
		// Start line: 508
	/* end block 1 */
	// End Line: 509

// [D]
void _RotMatrixX(MATRIX *m, short ang)
{
	RotMatrixX((int)ang, m);
}



// decompiled code
// original method signature: 
// void /*$ra*/ _RotMatrixY(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
 // line 187, offset 0x0002d49c
	/* begin block 1 */
		// Start line: 519
	/* end block 1 */
	// End Line: 520

// [D]
void _RotMatrixY(MATRIX *m, short ang)
{
	RotMatrixY((int)ang, m);
}



// decompiled code
// original method signature: 
// void /*$ra*/ _RotMatrixZ(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
 // line 192, offset 0x0002d4c8
	/* begin block 1 */
		// Start line: 530
	/* end block 1 */
	// End Line: 531

// [D]
void _RotMatrixZ(MATRIX *m, short ang)
{
	RotMatrixZ((int)ang, m);
}



// decompiled code
// original method signature: 
// void /*$ra*/ RotMatrixXYZ(struct MATRIX *m /*$v0*/, struct SVECTOR *r /*$a1*/)
 // line 199, offset 0x0002d4f4
	/* begin block 1 */
		// Start line: 545
	/* end block 1 */
	// End Line: 546

void RotMatrixXYZ(MATRIX *m, SVECTOR *r)
{
	RotMatrix(r, m);
}



// decompiled code
// original method signature: 
// void /*$ra*/ _MatrixRotate(struct VECTOR *pos /*$s0*/)
 // line 205, offset 0x0002d51c
	/* begin block 1 */
		// Start line: 206
		// Start offset: 0x0002D51C
		// Variables:
	// 		struct VECTOR temp; // stack offset -24
	/* end block 1 */
	// End offset: 0x0002D55C
	// End Line: 214

	/* begin block 2 */
		// Start line: 558
	/* end block 2 */
	// End Line: 559

void _MatrixRotate(VECTOR *pos)
{
	UNIMPLEMENTED();
	/*
	long local_18;
	long local_14;
	long local_10;

	ApplyRotMatrixLV(pos, &local_18);
	pos->vx = local_18;
	pos->vy = local_14;
	pos->vz = local_10;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InvertMatrix(struct MATRIX *a /*$a0*/, struct MATRIX *b /*$a1*/)
 // line 240, offset 0x0002d55c
	/* begin block 1 */
		// Start line: 620
	/* end block 1 */
	// End Line: 621

	/* begin block 2 */
		// Start line: 630
	/* end block 2 */
	// End Line: 631

	/* begin block 3 */
		// Start line: 632
	/* end block 3 */
	// End Line: 633

// [D]
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



// decompiled code
// original method signature: 
// void /*$ra*/ BuildWorldMatrix()
 // line 272, offset 0x0002d304
	/* begin block 1 */
		// Start line: 274
		// Start offset: 0x0002D304
		// Variables:
	// 		struct MATRIX newmatrix; // stack offset -48
	/* end block 1 */
	// End offset: 0x0002D3F8
	// End Line: 289

	/* begin block 2 */
		// Start line: 544
	/* end block 2 */
	// End Line: 545

	/* begin block 3 */
		// Start line: 545
	/* end block 3 */
	// End Line: 546

	/* begin block 4 */
		// Start line: 547
	/* end block 4 */
	// End Line: 548

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void BuildWorldMatrix(void)
{
	MATRIX newmatrix;

	newmatrix.m[0][0] = 0x1000;
	newmatrix.m[1][0] = 0;
	newmatrix.m[2][0] = 0;

	newmatrix.m[0][1] = 0;
	newmatrix.m[1][1] = 0x1000;
	newmatrix.m[2][1] = 0;

	newmatrix.m[0][2] = 0;
	newmatrix.m[1][2] = 0;
	newmatrix.m[2][2] = 0x1000;

	_RotMatrixY(&newmatrix, camera_angle.vy);
	_RotMatrixZ(&newmatrix, camera_angle.vz);
	_RotMatrixX(&newmatrix, camera_angle.vx);

	MulMatrix0(&aspect, &newmatrix, &inv_camera_matrix);
	InvertMatrix(&inv_camera_matrix, &camera_matrix);

	face_camera_work.m[0][0] = 0x1000;
	face_camera_work.m[0][2] = 0;
	face_camera_work.m[2][0] = 0;
	face_camera_work.m[2][2] = 0x1000;

	RotMatrixY(-(int)camera_angle.vy & 0xfff, &face_camera_work);
	MulMatrix0(&inv_camera_matrix, &face_camera_work, &face_camera);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ScaleCamera()
 // line 334, offset 0x0002d5c8
	/* begin block 1 */
		// Start line: 336
		// Start offset: 0x0002D5C8
		// Variables:
	// 		struct MATRIX temp; // stack offset -160
	// 		struct MATRIX temp2; // stack offset -128
	// 		struct MATRIX scale; // stack offset -96
	// 		struct MATRIX scaledcammat; // stack offset -64
	// 		struct VECTOR pos; // stack offset -32
	// 		struct SVECTOR tempang; // stack offset -16
	/* end block 1 */
	// End offset: 0x0002D678
	// End Line: 361

	/* begin block 2 */
		// Start line: 818
	/* end block 2 */
	// End Line: 819

	/* begin block 3 */
		// Start line: 819
	/* end block 3 */
	// End Line: 820

	/* begin block 4 */
		// Start line: 831
	/* end block 4 */
	// End Line: 832

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
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

	scale.m[0][0] = 0x1000;
	scale.m[0][1] = 0;
	scale.m[0][2] = 0;

	scale.m[1][0] = 0;
	scale.m[1][1] = 0x1000;
	scale.m[1][2] = 0;

	scale.m[2][0] = 0;
	scale.m[2][1] = 0;
	scale.m[2][2] = 0x1000;

	MulMatrix0(&scale, &inv_camera_matrix, &scaledcammat);
	TransMatrix(&scaledcammat, &pos);
	SetRotMatrix(&scaledcammat);
	SetTransMatrix(&scaledcammat);
}



// decompiled code
// original method signature: 
// void /*$ra*/ Getlong(char *dest /*$a0*/, char *source /*$a1*/)
 // line 365, offset 0x0002d678
	/* begin block 1 */
		// Start line: 899
	/* end block 1 */
	// End Line: 900

	/* begin block 2 */
		// Start line: 904
	/* end block 2 */
	// End Line: 905

	/* begin block 3 */
		// Start line: 906
	/* end block 3 */
	// End Line: 907

void Getlong(char *dest, char *source)
{
	*dest = *source;
	dest[1] = source[1];
	dest[2] = source[2];
	dest[3] = source[3];
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ RandomInit(long i1 /*$a0*/, long i2 /*$a1*/)
 // line 387, offset 0x0002d6a8
	/* begin block 1 */
		// Start line: 389
		// Start offset: 0x0002D6A8
		// Variables:
	// 		int count; // $s0
	/* end block 1 */
	// End offset: 0x0002D724
	// End Line: 402

	/* begin block 2 */
		// Start line: 948
	/* end block 2 */
	// End Line: 949

	/* begin block 3 */
		// Start line: 949
	/* end block 3 */
	// End Line: 950

	/* begin block 4 */
		// Start line: 952
	/* end block 4 */
	// End Line: 953

void RandomInit(long i1, long i2)
{
	UNIMPLEMENTED();
	/*
	int step;
	long *plVar1;
	int iVar2;

	plVar1 = &LONG_000bd518;
	step = 0x3b1cb49;
	iVar2 = 0xe;
	randomindex = 0;
	randomcounter = 0;
	rseed = i1;
	LONG_000bd514 = i2;
	do {
		*plVar1 = step;
		plVar1 = plVar1 + 1;
		iVar2 = iVar2 + -1;
		step = step + 0x1c05e5f;
	} while (-1 < iVar2);
	step = 0;
	do {
		Random2(step);
		step = step + 1;
	} while (step < 0x44);
	return;
	*/
}



// decompiled code
// original method signature: 
// long /*$ra*/ Random2(int step /*$a0*/)
 // line 414, offset 0x0002d724
	/* begin block 1 */
		// Start line: 416
		// Start offset: 0x0002D724
		// Variables:
	// 		unsigned int seed; // $a0
	/* end block 1 */
	// End offset: 0x0002D78C
	// End Line: 420

	/* begin block 2 */
		// Start line: 999
	/* end block 2 */
	// End Line: 1000

	/* begin block 3 */
		// Start line: 1012
	/* end block 3 */
	// End Line: 1013

	/* begin block 4 */
		// Start line: 1013
	/* end block 4 */
	// End Line: 1014

long Random2(int step)
{
	UNIMPLEMENTED();
	return 0;
	/*
	return (CameraCnt - frameStart) * (CameraCnt - frameStart) * 0x19660d + 0x3c6ef35fU >> 8 & 0xffff;
	*/
}
