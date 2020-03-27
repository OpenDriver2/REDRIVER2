#include "THISDUST.H"
#include "BCOLL3D.H"


// decompiled code
// original method signature: 
// void /*$ra*/ PointFaceCheck(struct _CAR_DATA *cp0 /*$t7*/, struct _CAR_DATA *cp1 /*$t8*/, int i /*$t9*/, struct TestResult *least /*$a3*/, int nSign /*stack 16*/)
 // line 83, offset 0x0001c160
	/* begin block 1 */
		// Start line: 84
		// Start offset: 0x0001C160
		// Variables:
	// 		int k; // $t5
	// 		struct VECTOR normal; // stack offset -56
	// 		struct VECTOR diff; // stack offset -40
	// 		struct VECTOR point; // stack offset -24
	// 		int depth; // $t0

		/* begin block 1.1 */
			// Start line: 106
			// Start offset: 0x0001C250
			// Variables:
		// 		int partialDepth; // $v1
		/* end block 1.1 */
		// End offset: 0x0001C2EC
		// End Line: 119
	/* end block 1 */
	// End offset: 0x0001C380
	// End Line: 130

	/* begin block 2 */
		// Start line: 166
	/* end block 2 */
	// End Line: 167

void PointFaceCheck(_CAR_DATA *cp0,_CAR_DATA *cp1,int i,TestResult *least,int nSign)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  SVECTOR_NOPAD *pSVar8;
  int iVar9;
  int local_38;
  int local_34;
  int local_30;
  int local_18;
  int local_14;
  int local_10;
  
  local_18 = (cp1->hd).oBox.location.vx;
  local_38 = (int)(cp0->hd).where.m[i];
  psVar2 = (cp0->hd).where.m + i;
  local_14 = (cp1->hd).oBox.location.vy;
  local_34 = (int)psVar2[3];
  local_10 = (cp1->hd).oBox.location.vz;
  local_30 = (int)psVar2[6];
  iVar4 = (local_18 - (cp0->hd).oBox.location.vx) * local_38 +
          (local_14 - (cp0->hd).oBox.location.vy) * local_34 +
          (local_10 - (cp0->hd).oBox.location.vz) * local_30 + 0x800 >> 0xc;
  if (iVar4 < 0) {
    local_38 = -local_38;
    local_34 = -local_34;
    local_30 = -local_30;
  }
  else {
    iVar4 = -iVar4;
  }
  pSVar8 = (cp1->hd).oBox.radii;
  iVar9 = 2;
  psVar7 = &(cp1->hd).oBox.radii[0].vz;
  psVar2 = &(cp1->hd).oBox.radii[0].vy;
  iVar4 = iVar4 + (cp0->hd).oBox.length[i];
  do {
    iVar3 = (int)pSVar8->vx;
    iVar5 = (int)*psVar2;
    iVar6 = (int)*psVar7;
    iVar1 = iVar3 * local_38 + iVar5 * local_34 + iVar6 * local_30 + 0x800 >> 0xc;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    else {
      iVar3 = -iVar3;
      iVar5 = -iVar5;
      iVar6 = -iVar6;
    }
    local_14 = local_14 + iVar5;
    local_18 = local_18 + iVar3;
    local_10 = local_10 + iVar6;
    iVar4 = iVar4 + iVar1;
    pSVar8 = pSVar8 + 1;
    psVar7 = psVar7 + 3;
    iVar9 = iVar9 + -1;
    psVar2 = psVar2 + 3;
  } while (-1 < iVar9);
  if ((iVar4 < least->depth) && (least->depth = iVar4, -1 < iVar4)) {
    (least->location).vx = local_18;
    (least->location).vy = local_14;
    (least->location).vz = local_10;
    if (nSign < 0) {
      local_38 = -local_38;
      local_34 = -local_34;
      local_30 = -local_30;
    }
    (least->normal).vx = local_38;
    (least->normal).vy = local_34;
    (least->normal).vz = local_30;
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ collided3d(struct _CAR_DATA *cp0 /*$s3*/, struct _CAR_DATA *cp1 /*$s2*/, struct TestResult *least /*$s1*/)
 // line 133, offset 0x0001c408
	/* begin block 1 */
		// Start line: 134
		// Start offset: 0x0001C408
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x0001C51C
	// End Line: 151

	/* begin block 2 */
		// Start line: 353
	/* end block 2 */
	// End Line: 354

	/* begin block 3 */
		// Start line: 266
	/* end block 3 */
	// End Line: 267

int collided3d(_CAR_DATA *cp0,_CAR_DATA *cp1,TestResult *least)

{
  int i;
  
  least->depth = 0x40000000;
  PointFaceCheck(cp0,cp1,1,least,1);
  if ((-1 < least->depth) && (PointFaceCheck(cp1,cp0,1,least,-1), -1 < least->depth)) {
    least->depth = 0x40000000;
    i = 0;
    while (PointFaceCheck(cp0,cp1,i,least,1), -1 < least->depth) {
      PointFaceCheck(cp1,cp0,i,least,-1);
      i = i + 2;
      if (least->depth < 0) {
        return 0;
      }
      if (2 < i) {
        return 1;
      }
    }
  }
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarCarCollision3(struct _CAR_DATA *c0 /*$a0*/, struct _CAR_DATA *c1 /*$a1*/, int *depth /*$s2*/, struct VECTOR *where /*$s0*/, struct VECTOR *normal /*stack 16*/)
 // line 153, offset 0x0001c380
	/* begin block 1 */
		// Start line: 154
		// Start offset: 0x0001C380
		// Variables:
	// 		struct TestResult tr; // stack offset -56
	// 		int res; // $t1
	/* end block 1 */
	// End offset: 0x0001C408
	// End Line: 165

	/* begin block 2 */
		// Start line: 336
	/* end block 2 */
	// End Line: 337

	/* begin block 3 */
		// Start line: 360
	/* end block 3 */
	// End Line: 361

int CarCarCollision3(_CAR_DATA *c0,_CAR_DATA *c1,int *depth,VECTOR *where,VECTOR *normal)

{
  int iVar1;
  TestResult local_38;
  
  iVar1 = collided3d(c0,c1,&local_38);
  if (iVar1 != 0) {
    *depth = local_38.depth;
    where->vx = local_38.location.vx;
    where->vy = local_38.location.vy;
    where->vz = local_38.location.vz;
    normal->vx = local_38.normal.vx;
    normal->vy = local_38.normal.vy;
    normal->vz = local_38.normal.vz;
  }
  return iVar1;
}





