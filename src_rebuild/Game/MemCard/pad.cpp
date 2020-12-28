#include "THISDUST.H"
#include "PAD.H"


// decompiled code
// original method signature: 
// struct PAD * /*$ra*/ __3PADPc(struct PAD *this /*$s1*/, char *bufferPtr /*$a1*/)
 // line 32, offset 0x000feb70
	/* begin block 1 */
		// Start line: 33
		// Start offset: 0x000FEB70
	/* end block 1 */
	// End offset: 0x000FEC44
	// End Line: 60

	/* begin block 2 */
		// Start line: 64
	/* end block 2 */
	// End Line: 65

int FUN_MCARD__000feb70(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  FUN_MCARD__000f523c(param_1,0,0,0x200,0xb0,0x220,0xb0,param_2);
  FUN_MCARD__000f523c(param_1 + 0x410c,1,0,0x240,0xb0,0x230,0xb0,0);
  uVar1 = DAT_MCARD__0010ee08;
  *(undefined4 *)(&DAT_00008218 + param_1) = 0x10;
  *(undefined4 *)(&DAT_0000821c + param_1) = 0x18;
  *(undefined4 *)(&DAT_00008230 + param_1) = 0;
  *(undefined4 *)(&DAT_00008234 + param_1) = 0;
  *(undefined4 *)(&DAT_00008238 + param_1) = 0;
  *(undefined4 *)(&DAT_0000823c + param_1) = 0;
  *(undefined4 *)(&DAT_0000822c + param_1) = 0;
  if ((uVar1 & 8) != 0) {
    DAT_MCARD__0010ec88 = 0x1000;
    DAT_MCARD__0010ec8a = 0x2000;
    DAT_MCARD__0010ec8c = 0x4000;
    PTR_LAB_MCARD__00102000_MCARD__0010ec8e._0_2_ = 0x8000;
  }
  libcman_InitControllerLibrary(&DAT_MCARD__0010ec9c,0x20,&DAT_MCARD__0010ecbe,0x20);
  *(int *)(&DAT_00008248 + param_1) = param_1;
  *(int *)(&DAT_0000824c + param_1) = param_1 + 0x410c;
  *(undefined4 *)(&DAT_00008250 + param_1) = 0;
  *(undefined4 *)(&DAT_00008254 + param_1) = 4;
  uVar2 = FUN_MCARD__000f5474(param_1);
  *(undefined4 *)(&DAT_0000825c + param_1) = uVar2;
  *(undefined4 *)(&DAT_00008260 + param_1) = 0x1c;
  *(undefined4 *)(&DAT_00008264 + param_1) = 0x1c;
  *(undefined4 *)(&DAT_00008268 + param_1) = 0x1c;
  *(undefined4 *)(&DAT_0000826c + param_1) = 0x19;
  *(undefined4 *)(&DAT_00008270 + param_1) = 0x1c;
  *(undefined4 *)(&DAT_00008274 + param_1) = 0x1c;
  *(undefined4 *)(&DAT_00008278 + param_1) = 0x1c;
  *(undefined4 *)(&DAT_00008258 + param_1) = 0;
  return param_1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ _._3PAD(struct PAD *this /*$s1*/, int __in_chrg /*$s0*/)
 // line 89, offset 0x000ffe44
	/* begin block 1 */
		// Start line: 90
		// Start offset: 0x000FFE44
	/* end block 1 */
	// End offset: 0x000FFE44
	// End Line: 90

	/* begin block 2 */
		// Start line: 178
	/* end block 2 */
	// End Line: 179

void FUN_MCARD__000ffe44(int param_1,uint param_2)

{
  libcman_DeInitControllerLibrary();
  FUN_MCARD__000f52f0(param_1 + 0x410c,2);
  FUN_MCARD__000f52f0(param_1,2);
  if ((param_2 & 1) != 0) {
    __builtin_delete(param_1);
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ UpdateSlots__3PAD(struct PAD *this /*$s0*/)
 // line 103, offset 0x000ffea0
	/* begin block 1 */
		// Start line: 104
		// Start offset: 0x000FFEA0
	/* end block 1 */
	// End offset: 0x000FFEE0
	// End Line: 134

	/* begin block 2 */
		// Start line: 1328
	/* end block 2 */
	// End Line: 1329

undefined4 FUN_MCARD__000ffea0(int param_1)

{
  FUN_MCARD__000ffa1c();
  FUN_MCARD__000ffc98(param_1,*(undefined4 *)(&DAT_00008258 + param_1),1);
  return *(undefined4 *)(&DAT_00008258 + param_1);
}



// decompiled code
// original method signature: 
// unsigned short /*$ra*/ GetPadData__3PADi(struct PAD *this /*$s1*/, int pad /*$s0*/)
 // line 137, offset 0x000fecc0
	/* begin block 1 */
		// Start line: 138
		// Start offset: 0x000FECC0
		// Variables:
	// 		struct ControllerPacket cData; // stack offset -56
	// 		unsigned short retVal; // $s2
	/* end block 1 */
	// End offset: 0x000FF2CC
	// End Line: 433

	/* begin block 2 */
		// Start line: 319
	/* end block 2 */
	// End Line: 320

	/* begin block 3 */
		// Start line: 321
	/* end block 3 */
	// End Line: 322

/* WARNING: Could not reconcile some variable overlaps */

uint FUN_MCARD__000fecc0(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 local_38;
  undefined2 local_34;
  char cStack50;
  char cStack49;
  char local_30;
  undefined4 local_2c;
  undefined2 local_28 [12];
  
  uVar8 = 0;
  libcman_ReadControllers();
  puVar4 = (undefined4 *)&local_38;
  iVar3 = param_2 * 0x22;
  puVar1 = (undefined4 *)(&DAT_MCARD__0010ec9c + iVar3);
  puVar2 = puVar4;
  if (((uint)puVar1 & 3) == 0) {
    do {
      uVar5 = puVar1[1];
      uVar6 = puVar1[2];
      uVar7 = puVar1[3];
      *puVar2 = *puVar1;
      puVar2[1] = uVar5;
      puVar2[2] = uVar6;
      puVar2[3] = uVar7;
      puVar1 = puVar1 + 4;
      puVar2 = puVar2 + 4;
    } while (puVar1 != (undefined4 *)(iVar3 + 0x10ecbc));
  }
  else {
    do {
      uVar5 = puVar1[1];
      uVar6 = puVar1[2];
      uVar7 = puVar1[3];
      *puVar2 = *puVar1;
      puVar2[1] = uVar5;
      puVar2[2] = uVar6;
      puVar2[3] = uVar7;
      puVar1 = puVar1 + 4;
      puVar2 = puVar2 + 4;
    } while (puVar1 != (undefined4 *)(iVar3 + 0x10ecbc));
  }
  *(undefined2 *)puVar2 = *(undefined2 *)puVar1;
  *(undefined4 *)(&DAT_00008238 + param_1) = 0;
  *(undefined4 *)(&DAT_0000823c + param_1) = 0;
  if ((char)local_38 != '\0') {
    return 0;
  }
  puVar2 = (undefined4 *)(&DAT_MCARD__0010ec9c + param_2 * 0x22);
  puVar1 = (undefined4 *)(param_2 * 0x22 + 0x10ecbc);
  if (((uint)puVar2 & 3) == 0) {
    do {
      uVar6 = puVar2[1];
      uVar7 = puVar2[2];
      uVar5 = puVar2[3];
      *puVar4 = *puVar2;
      puVar4[1] = uVar6;
      puVar4[2] = uVar7;
      puVar4[3] = uVar5;
      puVar2 = puVar2 + 4;
      puVar4 = puVar4 + 4;
    } while (puVar2 != puVar1);
  }
  else {
    do {
      uVar5 = puVar2[1];
      uVar6 = puVar2[2];
      uVar7 = puVar2[3];
      *puVar4 = *puVar2;
      puVar4[1] = uVar5;
      puVar4[2] = uVar6;
      puVar4[3] = uVar7;
      puVar2 = puVar2 + 4;
      puVar4 = puVar4 + 4;
    } while (puVar2 != puVar1);
  }
  *(undefined2 *)puVar4 = *(undefined2 *)puVar2;
  if (*(uint *)(&DAT_00008240 + param_1) != (uint)(local_38._1_1_ >> 4)) {
    *(undefined4 *)(&DAT_0000822c + param_1) = 1;
  }
  switch(local_38._1_1_ >> 4) {
  case 1:
    if (((DAT_MCARD__0010ee08 ^ 1) & 1) == 0) {
      *(undefined4 *)(&DAT_0000823c + param_1) = 1;
      if ((local_38._2_2_ & 0x800) == 0) {
        uVar8 = (uint)(DAT_MCARD__0010ec8a | DAT_MCARD__0010ec8c);
      }
      if ((local_38._2_2_ & 0x400) == 0) {
        uVar8 = (uint)(ushort)PTR_LAB_MCARD__00102000_MCARD__0010ec8e;
      }
      if (local_34 == 0) {
        return uVar8;
      }
      iVar3 = *(int *)(&DAT_00008218 + param_1) + (int)(char)local_34;
      *(int *)(&DAT_00008218 + param_1) = iVar3;
      *(int *)(&DAT_0000821c + param_1) = *(int *)(&DAT_0000821c + param_1) + (int)local_34._1_1_;
joined_r0x000ff08c:
      if (0x1f0 < iVar3) {
        *(undefined4 *)(&DAT_00008218 + param_1) = 0x1f0;
      }
      if (*(int *)(&DAT_00008218 + param_1) < 0x10) {
        *(undefined4 *)(&DAT_00008218 + param_1) = 0x10;
      }
      if (0xe0 < *(int *)(&DAT_0000821c + param_1)) {
        *(undefined4 *)(&DAT_0000821c + param_1) = 0xe0;
      }
      if (*(int *)(&DAT_0000821c + param_1) < 0x18) {
        *(undefined4 *)(&DAT_0000821c + param_1) = 0x18;
        return uVar8;
      }
      return uVar8;
    }
  default:
LAB_MCARD__000ff2a8:
    *(undefined4 *)(&DAT_0000823c + param_1) = 0;
    return 0;
  case 2:
    if ((*(int *)(&DAT_00008234 + param_1) != 0) || ((DAT_MCARD__0010ee08 & 2) == 0)) {
      *(undefined4 *)(&DAT_0000823c + param_1) = 0;
      return 0;
    }
    *(undefined4 *)(&DAT_00008238 + param_1) = 1;
    *(undefined4 *)(&DAT_0000823c + param_1) = 1;
    if (local_34._1_1_ != '\0') {
      uVar8 = 0x4000;
    }
    if (cStack50 != '\0') {
      uVar8 = 0x8000;
    }
    if ((local_38._2_2_ & 0x2000) == 0) {
      uVar8 = 0x2000;
    }
    if ((local_38._2_2_ & 0x1000) == 0) {
      uVar8 = 0x1000;
    }
LAB_MCARD__000ff11c:
    if ((local_38._2_2_ & 0x10) == 0) {
      uVar8 = 0x10;
    }
    if ((local_38._2_2_ & 0x40) == 0) {
      uVar8 = 0x40;
    }
    if ((local_38._2_2_ & 0x80) == 0) {
      uVar8 = 0x80;
    }
    if ((local_38._2_2_ & 0x20) == 0) {
      return 0x20;
    }
    return uVar8;
  case 4:
    break;
  case 7:
    if ((*(int *)(&DAT_00008234 + param_1) != 0) || ((DAT_MCARD__0010ee08 & 4) == 0)) {
      *(undefined4 *)(&DAT_0000823c + param_1) = 0;
      return 0;
    }
    break;
  case 8:
    local_38._3_1_ = local_38._3_1_ >> 4;
    if (local_38._3_1_ == 2) {
      if ((*(int *)(&DAT_00008234 + param_1) != 0) || ((DAT_MCARD__0010ee08 & 4) == 0)) {
        *(undefined4 *)(&DAT_0000823c + param_1) = 0;
        return 0;
      }
      *(undefined4 *)(&DAT_00008238 + param_1) = 1;
      *(undefined4 *)(&DAT_0000823c + param_1) = 1;
      if (cStack49 != '\0') {
        uVar8 = 0x4000;
      }
      if (local_30 != '\0') {
        uVar8 = 0x8000;
      }
      if ((local_34 & 0x2000) == 0) {
        uVar8 = 0x2000;
      }
      if ((local_34 & 0x1000) == 0) {
        uVar8 = 0x1000;
      }
      goto LAB_MCARD__000ff11c;
    }
    if (local_38._3_1_ < 3) {
      if ((local_38._3_1_ == 1) && (((DAT_MCARD__0010ee08 ^ 1) & 1) == 0)) {
        *(uint *)(&DAT_0000823c + param_1) = (uint)local_38._3_1_;
        if ((local_34 & 0x800) == 0) {
          uVar8 = (uint)(DAT_MCARD__0010ec8a | DAT_MCARD__0010ec8c);
        }
        if ((local_34 & 0x400) == 0) {
          uVar8 = (uint)(ushort)PTR_LAB_MCARD__00102000_MCARD__0010ec8e;
        }
        if (((int)cStack50 == 0) && (cStack49 == '\0')) {
          return uVar8;
        }
        iVar3 = *(int *)(&DAT_00008218 + param_1) + (int)cStack50;
        *(int *)(&DAT_00008218 + param_1) = iVar3;
        *(int *)(&DAT_0000821c + param_1) = *(int *)(&DAT_0000821c + param_1) + (int)cStack49;
        goto joined_r0x000ff08c;
      }
      goto LAB_MCARD__000ff2a8;
    }
    if (local_38._3_1_ != 4) {
      if (local_38._3_1_ != 7) goto LAB_MCARD__000ff2a8;
      if ((*(int *)(&DAT_00008234 + param_1) != 0) || ((DAT_MCARD__0010ee08 & 4) == 0)) {
        *(undefined4 *)(&DAT_0000823c + param_1) = 0;
        return 0;
      }
    }
    if (*(int *)(&DAT_00008234 + param_1) != 0) {
      *(undefined4 *)(&DAT_0000823c + param_1) = 0;
      return 0;
    }
    goto LAB_MCARD__000ff1a8;
  }
  local_34 = local_38._2_2_;
  if (*(int *)(&DAT_00008234 + param_1) != 0) {
    *(undefined4 *)(&DAT_0000823c + param_1) = 0;
    return 0;
  }
LAB_MCARD__000ff1a8:
  *(undefined4 *)(&DAT_0000823c + param_1) = 1;
  return ~(uint)local_34 & 0xffff;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ NegConInserted__3PAD(struct PAD *this /*$a0*/)
 // line 437, offset 0x000ffee0
	/* begin block 1 */
		// Start line: 438
		// Start offset: 0x000FFEE0
	/* end block 1 */
	// End offset: 0x000FFF10
	// End Line: 445

	/* begin block 2 */
		// Start line: 1996
	/* end block 2 */
	// End Line: 1997

	/* begin block 3 */
		// Start line: 1997
	/* end block 3 */
	// End Line: 1998

undefined4 FUN_MCARD__000ffee0(int param_1)

{
  if ((DAT_MCARD__0010ee08 & 2) == 0) {
    return 0;
  }
  *(undefined4 *)(&DAT_00008238 + param_1) = 0;
  return 0;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ ControllerInserted__3PAD(struct PAD *this /*$a0*/)
 // line 448, offset 0x000fff10
	/* begin block 1 */
		// Start line: 449
		// Start offset: 0x000FFF10
	/* end block 1 */
	// End offset: 0x000FFF48
	// End Line: 460

	/* begin block 2 */
		// Start line: 2018
	/* end block 2 */
	// End Line: 2019

	/* begin block 3 */
		// Start line: 2022
	/* end block 3 */
	// End Line: 2023

	/* begin block 4 */
		// Start line: 2023
	/* end block 4 */
	// End Line: 2024

undefined4 FUN_MCARD__000fff10(int param_1)

{
  if (*(int *)(&DAT_0000823c + param_1) == 0) {
    *(undefined4 *)(&DAT_00008218 + param_1) = 0x10;
    *(undefined4 *)(&DAT_0000821c + param_1) = 0x10;
    *(undefined4 *)(&DAT_00008230 + param_1) = 0;
    *(undefined4 *)(&DAT_00008234 + param_1) = 0;
    *(undefined4 *)(&DAT_00008238 + param_1) = 0;
  }
  return *(undefined4 *)(&DAT_0000823c + param_1);
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ ControllerChanged__3PAD(struct PAD *this /*$a0*/)
 // line 463, offset 0x000fff48
	/* begin block 1 */
		// Start line: 464
		// Start offset: 0x000FFF48
	/* end block 1 */
	// End offset: 0x000FFF5C
	// End Line: 465

	/* begin block 2 */
		// Start line: 2052
	/* end block 2 */
	// End Line: 2053

	/* begin block 3 */
		// Start line: 2053
	/* end block 3 */
	// End Line: 2054

undefined4 FUN_MCARD__000fff48(int param_1)

{
  return *(undefined4 *)(&DAT_0000822c + param_1);
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ SetControllerType__3PAD(struct PAD *this /*$a0*/)
 // line 468, offset 0x000fff5c
	/* begin block 1 */
		// Start line: 469
		// Start offset: 0x000FFF5C
		// Variables:
	// 		struct ControllerPacket cData; // stack offset -40
	/* end block 1 */
	// End offset: 0x001000D0
	// End Line: 487

	/* begin block 2 */
		// Start line: 2062
	/* end block 2 */
	// End Line: 2063

	/* begin block 3 */
		// Start line: 2063
	/* end block 3 */
	// End Line: 2064

/* WARNING: Removing unreachable block (ram,0x000fff78) */
/* WARNING: Removing unreachable block (ram,0x000fff7c) */
/* WARNING: Removing unreachable block (ram,0x000fffc8) */
/* WARNING: Removing unreachable block (ram,0x0010001c) */
/* WARNING: Removing unreachable block (ram,0x00100020) */
/* WARNING: Removing unreachable block (ram,0x0010006c) */

void FUN_MCARD__000fff5c(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 local_28;
  undefined4 local_24 [3];
  undefined2 local_18 [12];
  
  puVar1 = &local_28;
  puVar3 = (undefined4 *)&DAT_MCARD__0010ec9c;
  puVar2 = puVar1;
  do {
    uVar4 = puVar3[1];
    uVar5 = puVar3[2];
    uVar6 = puVar3[3];
    *puVar2 = *puVar3;
    puVar2[1] = uVar4;
    puVar2[2] = uVar5;
    puVar2[3] = uVar6;
    puVar3 = puVar3 + 4;
    puVar2 = puVar2 + 4;
  } while (puVar3 != (undefined4 *)0x10ecbc);
  *(undefined2 *)puVar2 = uRam0010ecbc;
  puVar2 = (undefined4 *)&DAT_MCARD__0010ec9c;
  do {
    uVar5 = puVar2[1];
    uVar6 = puVar2[2];
    uVar4 = puVar2[3];
    *puVar1 = *puVar2;
    puVar1[1] = uVar5;
    puVar1[2] = uVar6;
    puVar1[3] = uVar4;
    puVar2 = puVar2 + 4;
    puVar1 = puVar1 + 4;
  } while (puVar2 != (undefined4 *)0x10ecbc);
  *(undefined2 *)puVar1 = uRam0010ecbc;
  *(undefined4 *)(&DAT_0000822c + param_1) = 0;
  *(uint *)(&DAT_00008240 + param_1) = (uint)(local_28._1_1_ >> 4);
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ MouseInserted__3PAD(struct PAD *this /*$a0*/)
 // line 490, offset 0x001000d0
	/* begin block 1 */
		// Start line: 491
		// Start offset: 0x001000D0
	/* end block 1 */
	// End offset: 0x00100158
	// End Line: 512

	/* begin block 2 */
		// Start line: 2105
	/* end block 2 */
	// End Line: 2106

	/* begin block 3 */
		// Start line: 2109
	/* end block 3 */
	// End Line: 2110

	/* begin block 4 */
		// Start line: 2110
	/* end block 4 */
	// End Line: 2111

undefined4 FUN_MCARD__001000d0(int param_1)

{
  if ((DAT_MCARD__0010ee08 & 1) == 0) {
    return 0;
  }
  if (*(int *)(&DAT_00008230 + param_1) != 0) {
    return *(undefined4 *)(&DAT_00008234 + param_1);
  }
  *(undefined4 *)(&DAT_00008230 + param_1) = 1;
  if ((DAT_MCARD__0010ec9d >> 4 == 1) || (DAT_MCARD__0010ec9f >> 4 == 1)) {
    *(undefined4 *)(&DAT_00008234 + param_1) = 1;
  }
  else {
    *(undefined4 *)(&DAT_00008234 + param_1) = 0;
  }
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetMouseX__3PAD(struct PAD *this /*$a0*/)
 // line 514, offset 0x00100158
	/* begin block 1 */
		// Start line: 515
		// Start offset: 0x00100158
	/* end block 1 */
	// End offset: 0x0010016C
	// End Line: 515

	/* begin block 2 */
		// Start line: 2160
	/* end block 2 */
	// End Line: 2161

undefined4 FUN_MCARD__00100158(int param_1)

{
  return *(undefined4 *)(&DAT_00008218 + param_1);
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetMouseY__3PAD(struct PAD *this /*$a0*/)
 // line 515, offset 0x0010016c
	/* begin block 1 */
		// Start line: 516
		// Start offset: 0x0010016C
	/* end block 1 */
	// End offset: 0x00100180
	// End Line: 516

	/* begin block 2 */
		// Start line: 2162
	/* end block 2 */
	// End Line: 2163

undefined4 FUN_MCARD__0010016c(int param_1)

{
  return *(undefined4 *)(&DAT_0000821c + param_1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResetPadData__3PAD(struct PAD *this /*$a0*/)
 // line 519, offset 0x00100180
	/* begin block 1 */
		// Start line: 520
		// Start offset: 0x00100180
	/* end block 1 */
	// End offset: 0x001001AC
	// End Line: 521

	/* begin block 2 */
		// Start line: 2170
	/* end block 2 */
	// End Line: 2171

	/* begin block 3 */
		// Start line: 2171
	/* end block 3 */
	// End Line: 2172

void FUN_MCARD__00100180(void)

{
  memset(&DAT_MCARD__0010ec9c,0,0x40);
  return;
}



// decompiled code
// original method signature: 
// char * /*$ra*/ port_name__3PADi(struct PAD *this /*$a2*/, int port /*$a1*/)
 // line 527, offset 0x000ff2cc
	/* begin block 1 */
		// Start line: 528
		// Start offset: 0x000FF2CC
	/* end block 1 */
	// End offset: 0x000FF3B8
	// End Line: 563

	/* begin block 2 */
		// Start line: 1124
	/* end block 2 */
	// End Line: 1125

	/* begin block 3 */
		// Start line: 1125
	/* end block 3 */
	// End Line: 1126

uint FUN_MCARD__000ff2cc(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)(param_2 < 8);
  switch(param_2) {
  case 0:
    uVar1 = DAT_MCARD__0010edac;
    if (*(int *)(&DAT_00008260 + param_1) != 0x1c) {
      return DAT_MCARD__0010edb0;
    }
    break;
  case 1:
    return DAT_MCARD__0010edb4;
  case 2:
    return DAT_MCARD__0010edb8;
  case 3:
    return DAT_MCARD__0010edbc;
  case 4:
    if (*(int *)(&DAT_00008270 + param_1) == 0x1c) {
      return DAT_MCARD__0010edc0;
    }
    return DAT_MCARD__0010edc4;
  case 5:
    return DAT_MCARD__0010edc8;
  case 6:
    return DAT_MCARD__0010edcc;
  case 7:
    return DAT_MCARD__0010edd0;
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ WaitUntilCardRemoved__3PADi(struct PAD *this /*$s3*/, int slot /*$a1*/)
 // line 569, offset 0x000ff3c0
	/* begin block 1 */
		// Start line: 570
		// Start offset: 0x000FF3C0
		// Variables:
	// 		struct RECT rect; // stack offset -48
	// 		short padData; // $a0
	// 		unsigned int bInBox; // $s2

		/* begin block 1.1 */
			// Start line: 577
			// Start offset: 0x000FF410

			/* begin block 1.1.1 */
				// Start line: 583
				// Start offset: 0x000FF448

				/* begin block 1.1.1.1 */
					// Start line: 570
					// Start offset: 0x000FF448
					// Variables:
				// 		struct PAD *this; // $s3

					/* begin block 1.1.1.1.1 */
						// Start line: 570
						// Start offset: 0x000FF448
					/* end block 1.1.1.1.1 */
					// End offset: 0x000FF4BC
					// End Line: 570
				/* end block 1.1.1.1 */
				// End offset: 0x000FF4BC
				// End Line: 570

				/* begin block 1.1.1.2 */
					// Start line: 584
					// Start offset: 0x000FF4C4

					/* begin block 1.1.1.2.1 */
						// Start line: 585
						// Start offset: 0x000FF4C4
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.1.1 */
							// Start line: 585
							// Start offset: 0x000FF4C4
						/* end block 1.1.1.2.1.1 */
						// End offset: 0x000FF4C4
						// End Line: 585
					/* end block 1.1.1.2.1 */
					// End offset: 0x000FF4C4
					// End Line: 585

					/* begin block 1.1.1.2.2 */
						// Start line: 585
						// Start offset: 0x000FF4C4
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.2.1 */
							// Start line: 585
							// Start offset: 0x000FF4C4
						/* end block 1.1.1.2.2.1 */
						// End offset: 0x000FF4C4
						// End Line: 585
					/* end block 1.1.1.2.2 */
					// End offset: 0x000FF4C4
					// End Line: 585

					/* begin block 1.1.1.2.3 */
						// Start line: 585
						// Start offset: 0x000FF4C4
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.3.1 */
							// Start line: 585
							// Start offset: 0x000FF4C4
						/* end block 1.1.1.2.3.1 */
						// End offset: 0x000FF4C4
						// End Line: 585
					/* end block 1.1.1.2.3 */
					// End offset: 0x000FF4C4
					// End Line: 585

					/* begin block 1.1.1.2.4 */
						// Start line: 570
						// Start offset: 0x000FF564
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.4.1 */
							// Start line: 570
							// Start offset: 0x000FF564
						/* end block 1.1.1.2.4.1 */
						// End offset: 0x000FF564
						// End Line: 570
					/* end block 1.1.1.2.4 */
					// End offset: 0x000FF564
					// End Line: 570

					/* begin block 1.1.1.2.5 */
						// Start line: 570
						// Start offset: 0x000FF57C
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.5.1 */
							// Start line: 570
							// Start offset: 0x000FF57C
						/* end block 1.1.1.2.5.1 */
						// End offset: 0x000FF57C
						// End Line: 570
					/* end block 1.1.1.2.5 */
					// End offset: 0x000FF57C
					// End Line: 570

					/* begin block 1.1.1.2.6 */
						// Start line: 570
						// Start offset: 0x000FF594
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.6.1 */
							// Start line: 570
							// Start offset: 0x000FF594
						/* end block 1.1.1.2.6.1 */
						// End offset: 0x000FF594
						// End Line: 570
					/* end block 1.1.1.2.6 */
					// End offset: 0x000FF594
					// End Line: 570

					/* begin block 1.1.1.2.7 */
						// Start line: 614
						// Start offset: 0x000FF5A4
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.7.1 */
							// Start line: 614
							// Start offset: 0x000FF5A4
						/* end block 1.1.1.2.7.1 */
						// End offset: 0x000FF5A4
						// End Line: 614
					/* end block 1.1.1.2.7 */
					// End offset: 0x000FF5A4
					// End Line: 614

					/* begin block 1.1.1.2.8 */
						// Start line: 614
						// Start offset: 0x000FF5A4
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.8.1 */
							// Start line: 614
							// Start offset: 0x000FF5A4
						/* end block 1.1.1.2.8.1 */
						// End offset: 0x000FF5A4
						// End Line: 614
					/* end block 1.1.1.2.8 */
					// End offset: 0x000FF5A4
					// End Line: 614
				/* end block 1.1.1.2 */
				// End offset: 0x000FF664
				// End Line: 625
			/* end block 1.1.1 */
			// End offset: 0x000FF6B4
			// End Line: 633
		/* end block 1.1 */
		// End offset: 0x000FF6B4
		// End Line: 633
	/* end block 1 */
	// End offset: 0x000FF6E4
	// End Line: 633

	/* begin block 2 */
		// Start line: 1208
	/* end block 2 */
	// End Line: 1209

undefined4 FUN_MCARD__000ff3c0(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  short local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  do {
    while( true ) {
      FUN_MCARD__000ffc98(param_1,*(int *)(&DAT_00008250 + param_2 * 4 + param_1),1);
      if (*(int *)(&DAT_0000825c + param_1 + *(int *)(&DAT_00008250 + param_2 * 4 + param_1) * 4) ==
          0x19) {
        return 1;
      }
      iVar2 = 0;
      if ((DAT_MCARD__0010ee08 & 1) != 0) {
        if (*(int *)(&DAT_00008230 + param_1) == 0) {
          *(undefined4 *)(&DAT_00008230 + param_1) = 1;
          if ((DAT_MCARD__0010ec9d >> 4 == 1) || (DAT_MCARD__0010ec9f >> 4 == 1)) {
            *(undefined4 *)(&DAT_00008234 + param_1) = 1;
          }
          else {
            *(undefined4 *)(&DAT_00008234 + param_1) = 0;
          }
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(&DAT_00008234 + param_1);
        }
      }
      if (iVar2 != 0) break;
      uVar1 = FUN_MCARD__000fecc0(param_1,0);
      if ((uVar1 & DAT_MCARD__0010ec8a) != 0) {
        do {
          uVar3 = FUN_MCARD__000fecc0(param_1,0);
        } while ((DAT_MCARD__0010ec8a & uVar3) != 0);
        return 0;
      }
    }
    DrawSync(0);
    VSync(0);
    uVar3 = 0;
    local_30 = *(short *)(DAT_MCARD__0010ec70 + 0x298);
    local_2e = *(undefined2 *)(DAT_MCARD__0010ec70 + 0x29c);
    local_2c = 0x10;
    local_2a = 0x10;
    LoadImage(&local_30,DAT_MCARD__0010ec70 + 0x2a0);
    DrawSync(0);
    iVar2 = DAT_MCARD__0010ec70;
    local_30 = (short)*(undefined4 *)(&DAT_00008218 + param_1);
    local_2e = (short)*(undefined4 *)(&DAT_0000821c + param_1);
    *(int *)(DAT_MCARD__0010ec70 + 0x298) = (int)local_30;
    *(int *)(iVar2 + 0x29c) = (int)local_2e;
    StoreImage(&local_30,iVar2 + 0x2a0);
    DrawSync(0);
    if ((int)DAT_MCARD__0010ec78 < *(int *)(&DAT_00008218 + param_1)) {
      iVar2 = 0;
      if (*(int *)(&DAT_00008218 + param_1) < (int)DAT_MCARD__0010ec78 + (int)DAT_MCARD__0010ec7c) {
        iVar2 = 0;
        if ((int)DAT_MCARD__0010ec7a < *(int *)(&DAT_0000821c + param_1)) {
          uVar3 = (uint)(*(int *)(&DAT_0000821c + param_1) <
                        (int)DAT_MCARD__0010ec7a + (int)DAT_MCARD__0010ec7e);
          goto LAB_MCARD__000ff5a4;
        }
      }
    }
    else {
LAB_MCARD__000ff5a4:
      iVar2 = uVar3 << 1;
    }
    iVar2 = iVar2 * 0x40 + uVar3 * 0x48 + 0x37;
    FUN_MCARD__000fe72c(DAT_MCARD__0010ec70,(int)DAT_MCARD__0010ec78,(int)DAT_MCARD__0010ec7a,
                        (int)DAT_MCARD__0010ec7c,(int)DAT_MCARD__0010ec7e,iVar2,iVar2,iVar2);
    FUN_MCARD__000facd4(DAT_MCARD__0010ec70,DAT_MCARD__0010ec70 + 0x44ac,
                        *(undefined4 *)(&DAT_00008218 + param_1),
                        *(undefined4 *)(&DAT_0000821c + param_1),0x80,0x80,0x80,0);
    uVar1 = FUN_MCARD__000fecc0(param_1,0);
    if (((uVar1 & DAT_MCARD__0010ec8a) != 0) && (uVar3 != 0)) {
      do {
        uVar3 = FUN_MCARD__000fecc0(param_1,0);
      } while ((DAT_MCARD__0010ec8a & uVar3) != 0);
      return 0;
    }
  } while( true );
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ WaitUntilAnyCardInserted__3PAD(struct PAD *this /*$s3*/)
 // line 655, offset 0x000ff6e4
	/* begin block 1 */
		// Start line: 656
		// Start offset: 0x000FF6E4
		// Variables:
	// 		struct RECT rect; // stack offset -48
	// 		unsigned int bInBox; // $s2

		/* begin block 1.1 */
			// Start line: 663
			// Start offset: 0x000FF730

			/* begin block 1.1.1 */
				// Start line: 675
				// Start offset: 0x000FF7A0

				/* begin block 1.1.1.1 */
					// Start line: 656
					// Start offset: 0x000FF7A0
					// Variables:
				// 		struct PAD *this; // $s3

					/* begin block 1.1.1.1.1 */
						// Start line: 656
						// Start offset: 0x000FF7A0
					/* end block 1.1.1.1.1 */
					// End offset: 0x000FF814
					// End Line: 656
				/* end block 1.1.1.1 */
				// End offset: 0x000FF814
				// End Line: 656

				/* begin block 1.1.1.2 */
					// Start line: 676
					// Start offset: 0x000FF81C

					/* begin block 1.1.1.2.1 */
						// Start line: 677
						// Start offset: 0x000FF81C
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.1.1 */
							// Start line: 677
							// Start offset: 0x000FF81C
						/* end block 1.1.1.2.1.1 */
						// End offset: 0x000FF81C
						// End Line: 677
					/* end block 1.1.1.2.1 */
					// End offset: 0x000FF81C
					// End Line: 677

					/* begin block 1.1.1.2.2 */
						// Start line: 677
						// Start offset: 0x000FF81C
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.2.1 */
							// Start line: 677
							// Start offset: 0x000FF81C
						/* end block 1.1.1.2.2.1 */
						// End offset: 0x000FF81C
						// End Line: 677
					/* end block 1.1.1.2.2 */
					// End offset: 0x000FF81C
					// End Line: 677

					/* begin block 1.1.1.2.3 */
						// Start line: 677
						// Start offset: 0x000FF81C
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.3.1 */
							// Start line: 677
							// Start offset: 0x000FF81C
						/* end block 1.1.1.2.3.1 */
						// End offset: 0x000FF81C
						// End Line: 677
					/* end block 1.1.1.2.3 */
					// End offset: 0x000FF81C
					// End Line: 677

					/* begin block 1.1.1.2.4 */
						// Start line: 656
						// Start offset: 0x000FF8C0
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.4.1 */
							// Start line: 656
							// Start offset: 0x000FF8C0
						/* end block 1.1.1.2.4.1 */
						// End offset: 0x000FF8C0
						// End Line: 656
					/* end block 1.1.1.2.4 */
					// End offset: 0x000FF8C0
					// End Line: 656

					/* begin block 1.1.1.2.5 */
						// Start line: 656
						// Start offset: 0x000FF8D8
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.5.1 */
							// Start line: 656
							// Start offset: 0x000FF8D8
						/* end block 1.1.1.2.5.1 */
						// End offset: 0x000FF8D8
						// End Line: 656
					/* end block 1.1.1.2.5 */
					// End offset: 0x000FF8D8
					// End Line: 656

					/* begin block 1.1.1.2.6 */
						// Start line: 656
						// Start offset: 0x000FF8F0
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.6.1 */
							// Start line: 656
							// Start offset: 0x000FF8F0
						/* end block 1.1.1.2.6.1 */
						// End offset: 0x000FF8F0
						// End Line: 656
					/* end block 1.1.1.2.6 */
					// End offset: 0x000FF8F0
					// End Line: 656

					/* begin block 1.1.1.2.7 */
						// Start line: 708
						// Start offset: 0x000FF900
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.7.1 */
							// Start line: 708
							// Start offset: 0x000FF900
						/* end block 1.1.1.2.7.1 */
						// End offset: 0x000FF900
						// End Line: 708
					/* end block 1.1.1.2.7 */
					// End offset: 0x000FF900
					// End Line: 708

					/* begin block 1.1.1.2.8 */
						// Start line: 708
						// Start offset: 0x000FF900
						// Variables:
					// 		struct PAD *this; // $s3

						/* begin block 1.1.1.2.8.1 */
							// Start line: 708
							// Start offset: 0x000FF900
						/* end block 1.1.1.2.8.1 */
						// End offset: 0x000FF900
						// End Line: 708
					/* end block 1.1.1.2.8 */
					// End offset: 0x000FF900
					// End Line: 708
				/* end block 1.1.1.2 */
				// End offset: 0x000FF9B0
				// End Line: 718
			/* end block 1.1.1 */
			// End offset: 0x000FF9EC
			// End Line: 726
		/* end block 1.1 */
		// End offset: 0x000FF9EC
		// End Line: 726
	/* end block 1 */
	// End offset: 0x000FFA1C
	// End Line: 726

	/* begin block 2 */
		// Start line: 1469
	/* end block 2 */
	// End Line: 1470

undefined4 FUN_MCARD__000ff6e4(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  short local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  do {
    while( true ) {
      FUN_MCARD__000ffc98(param_1,*(undefined4 *)(&DAT_00008258 + param_1),1);
      if (*(int *)(&DAT_0000825c + param_1 +
                  *(int *)(&DAT_00008250 + param_1 + *(int *)(&DAT_00008258 + param_1) * 4) * 4) !=
          0x19) {
        return 1;
      }
      if (*(int *)(&DAT_0000825c + param_1 +
                  *(int *)(&DAT_00008250 + param_1 + (1 - *(int *)(&DAT_00008258 + param_1)) * 4) *
                  4) != 0x19) {
        return 1;
      }
      iVar1 = 0;
      if ((DAT_MCARD__0010ee08 & 1) != 0) {
        if (*(int *)(&DAT_00008230 + param_1) == 0) {
          *(undefined4 *)(&DAT_00008230 + param_1) = 1;
          if ((DAT_MCARD__0010ec9d >> 4 == 1) || (DAT_MCARD__0010ec9f >> 4 == 1)) {
            *(undefined4 *)(&DAT_00008234 + param_1) = 1;
          }
          else {
            *(undefined4 *)(&DAT_00008234 + param_1) = 0;
          }
          iVar1 = 0;
        }
        else {
          iVar1 = *(int *)(&DAT_00008234 + param_1);
        }
      }
      if (iVar1 != 0) break;
      uVar3 = FUN_MCARD__000fecc0(param_1,0);
      if ((uVar3 & 0x4000) != 0) {
        do {
          uVar3 = FUN_MCARD__000fecc0(param_1,0);
        } while ((DAT_MCARD__0010ec8a & uVar3) != 0);
        return 0;
      }
    }
    DrawSync(0);
    VSync(0);
    uVar3 = 0;
    local_30 = *(short *)(DAT_MCARD__0010ec70 + 0x298);
    local_2e = *(undefined2 *)(DAT_MCARD__0010ec70 + 0x29c);
    local_2c = 0x10;
    local_2a = 0x10;
    LoadImage(&local_30,DAT_MCARD__0010ec70 + 0x2a0);
    DrawSync(0);
    iVar1 = DAT_MCARD__0010ec70;
    local_30 = (short)*(undefined4 *)(&DAT_00008218 + param_1);
    local_2e = (short)*(undefined4 *)(&DAT_0000821c + param_1);
    *(int *)(DAT_MCARD__0010ec70 + 0x298) = (int)local_30;
    *(int *)(iVar1 + 0x29c) = (int)local_2e;
    StoreImage(&local_30,iVar1 + 0x2a0);
    DrawSync(0);
    if ((int)DAT_MCARD__0010ec78 < *(int *)(&DAT_00008218 + param_1)) {
      iVar1 = 0;
      if (*(int *)(&DAT_00008218 + param_1) < (int)DAT_MCARD__0010ec78 + (int)DAT_MCARD__0010ec7c) {
        iVar1 = 0;
        if ((int)DAT_MCARD__0010ec7a < *(int *)(&DAT_0000821c + param_1)) {
          uVar3 = (uint)(*(int *)(&DAT_0000821c + param_1) <
                        (int)DAT_MCARD__0010ec7a + (int)DAT_MCARD__0010ec7e);
          goto LAB_MCARD__000ff900;
        }
      }
    }
    else {
LAB_MCARD__000ff900:
      iVar1 = uVar3 << 1;
    }
    iVar1 = iVar1 * 0x40 + uVar3 * 0x48 + 0x37;
    FUN_MCARD__000fe72c(DAT_MCARD__0010ec70,(int)DAT_MCARD__0010ec78,(int)DAT_MCARD__0010ec7a,
                        (int)DAT_MCARD__0010ec7c,(int)DAT_MCARD__0010ec7e,iVar1,iVar1,iVar1);
    FUN_MCARD__000facd4(DAT_MCARD__0010ec70,DAT_MCARD__0010ec70 + 0x44ac,
                        *(undefined4 *)(&DAT_00008218 + param_1),
                        *(undefined4 *)(&DAT_0000821c + param_1),0x80,0x80,0x80,0);
    uVar2 = FUN_MCARD__000fecc0(param_1,0);
    if (((uVar2 & 0x4000) != 0) && (uVar3 != 0)) {
      do {
        uVar3 = FUN_MCARD__000fecc0(param_1,0);
      } while ((DAT_MCARD__0010ec8a & uVar3) != 0);
      return 0;
    }
  } while( true );
}



// decompiled code
// original method signature: 
// char * /*$ra*/ GetPortName__3PADi(struct PAD *this /*$s1*/, int slot /*$s0*/)
 // line 733, offset 0x001001ac
	/* begin block 1 */
		// Start line: 734
		// Start offset: 0x001001AC
	/* end block 1 */
	// End offset: 0x00100214
	// End Line: 739

	/* begin block 2 */
		// Start line: 2598
	/* end block 2 */
	// End Line: 2599

undefined4 FUN_MCARD__001001ac(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_MCARD__000ffa1c();
  uVar1 = 0;
  if (*(int *)(param_1 + 0x8000 + *(int *)(param_1 + 0x8000 + param_2 * 4 + 0x250) * 4 + 0x25c) !=
      0x1c) {
    uVar1 = FUN_MCARD__000ff2cc(param_1);
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// char * /*$ra*/ GetControllerPortName__3PAD(struct PAD *this /*$s0*/)
 // line 757, offset 0x00100214
	/* begin block 1 */
		// Start line: 758
		// Start offset: 0x00100214
	/* end block 1 */
	// End offset: 0x00100244
	// End Line: 761

	/* begin block 2 */
		// Start line: 2641
	/* end block 2 */
	// End Line: 2642

	/* begin block 3 */
		// Start line: 2646
	/* end block 3 */
	// End Line: 2647

void FUN_MCARD__00100214(undefined4 param_1)

{
  FUN_MCARD__000ffa1c();
  FUN_MCARD__000ff2cc(param_1,0);
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardSelected__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
 // line 778, offset 0x00100244
	/* begin block 1 */
		// Start line: 779
		// Start offset: 0x00100244
	/* end block 1 */
	// End offset: 0x00100260
	// End Line: 780

	/* begin block 2 */
		// Start line: 2683
	/* end block 2 */
	// End Line: 2684

	/* begin block 3 */
		// Start line: 2688
	/* end block 3 */
	// End Line: 2689

	/* begin block 4 */
		// Start line: 2689
	/* end block 4 */
	// End Line: 2690

uint FUN_MCARD__00100244(int param_1,int param_2)

{
  return (uint)(*(int *)(&DAT_00008258 + param_1) == param_2);
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CurrCardInfoRead__3PAD(struct PAD *this /*$a0*/)
 // line 783, offset 0x00100260
	/* begin block 1 */
		// Start line: 784
		// Start offset: 0x00100260
	/* end block 1 */
	// End offset: 0x0010029C
	// End Line: 785

	/* begin block 2 */
		// Start line: 2698
	/* end block 2 */
	// End Line: 2699

	/* begin block 3 */
		// Start line: 2699
	/* end block 3 */
	// End Line: 2700

void FUN_MCARD__00100260(int param_1)

{
  FUN_MCARD__000f5dfc(*(undefined4 *)
                       (&DAT_00008248 + param_1 + *(int *)(&DAT_00008258 + param_1) * 4));
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ check_ports__3PAD(struct PAD *this /*$s1*/)
 // line 794, offset 0x000ffa1c
	/* begin block 1 */
		// Start line: 795
		// Start offset: 0x000FFA1C
	/* end block 1 */
	// End offset: 0x000FFC80
	// End Line: 896

	/* begin block 2 */
		// Start line: 1836
	/* end block 2 */
	// End Line: 1837

	/* begin block 3 */
		// Start line: 1839
	/* end block 3 */
	// End Line: 1840

void FUN_MCARD__000ffa1c(int param_1)

{
  if ((DAT_MCARD__0010ec9d >> 4 == 8) && (*(int *)(&DAT_00008260 + param_1) == 0x1c)) {
    *(undefined4 *)(&DAT_0000825c + param_1) = 0x19;
    *(undefined4 *)(&DAT_00008260 + param_1) = 0x19;
    *(undefined4 *)(&DAT_00008264 + param_1) = 0x19;
    *(undefined4 *)(&DAT_00008268 + param_1) = 0x19;
  }
  if ((DAT_MCARD__0010ecbf >> 4 == 8) && (*(int *)(&DAT_00008270 + param_1) == 0x1c)) {
    *(undefined4 *)(&DAT_0000826c + param_1) = 0x19;
    *(undefined4 *)(&DAT_00008270 + param_1) = 0x19;
    *(undefined4 *)(&DAT_00008274 + param_1) = 0x19;
    *(undefined4 *)(&DAT_00008278 + param_1) = 0x19;
  }
  if ((DAT_MCARD__0010ec9d >> 4 != 8) && (*(int *)(&DAT_00008260 + param_1) != 0x1c)) {
    *(undefined4 *)(&DAT_00008260 + param_1) = 0x1c;
    *(undefined4 *)(&DAT_00008264 + param_1) = 0x1c;
    *(undefined4 *)(&DAT_00008268 + param_1) = 0x1c;
    *(undefined4 *)(&DAT_0000825c + param_1) = 0x19;
    if (*(int *)(&DAT_00008250 + param_1) < 4) {
      if (*(int *)(&DAT_00008254 + param_1) == 0) {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_00008248 + param_1),1,0);
        *(undefined4 *)(&DAT_00008250 + param_1) = 4;
      }
      else {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_00008248 + param_1),0,0);
        *(undefined4 *)(&DAT_00008250 + param_1) = 0;
      }
    }
    if (*(int *)(&DAT_00008254 + param_1) < 4) {
      if (*(int *)(&DAT_00008250 + param_1) == 0) {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_0000824c + param_1),1,0);
        *(undefined4 *)(&DAT_00008254 + param_1) = 4;
      }
      else {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_0000824c + param_1),0,0);
        *(undefined4 *)(&DAT_00008254 + param_1) = 0;
      }
    }
  }
  if ((DAT_MCARD__0010ecbf >> 4 != 8) && (*(int *)(&DAT_00008270 + param_1) != 0x1c)) {
    *(undefined4 *)(&DAT_00008270 + param_1) = 0x1c;
    *(undefined4 *)(&DAT_00008274 + param_1) = 0x1c;
    *(undefined4 *)(&DAT_00008278 + param_1) = 0x1c;
    *(undefined4 *)(&DAT_0000826c + param_1) = 0x19;
    if (3 < *(int *)(&DAT_00008250 + param_1)) {
      if (*(int *)(&DAT_00008254 + param_1) == 0) {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_00008248 + param_1),1,0);
        *(undefined4 *)(&DAT_00008250 + param_1) = 4;
      }
      else {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_00008248 + param_1),0,0);
        *(undefined4 *)(&DAT_00008250 + param_1) = 0;
      }
    }
    if (3 < *(int *)(&DAT_00008254 + param_1)) {
      if (*(int *)(&DAT_00008250 + param_1) == 0) {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_0000824c + param_1),1,0);
        *(undefined4 *)(&DAT_00008254 + param_1) = 4;
      }
      else {
        FUN_MCARD__000f5c70(*(undefined4 *)(&DAT_0000824c + param_1),0,0);
        *(undefined4 *)(&DAT_00008254 + param_1) = 0;
      }
    }
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ search_ports__3PADib(struct PAD *this /*$s4*/, int slot /*$s0*/, unsigned int cycle /*$a2*/)
 // line 905, offset 0x000ffc98
	/* begin block 1 */
		// Start line: 906
		// Start offset: 0x000FFC98
	/* end block 1 */
	// End offset: 0x000FFE18
	// End Line: 951

	/* begin block 2 */
		// Start line: 2061
	/* end block 2 */
	// End Line: 2062

void FUN_MCARD__000ffc98(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  
  iVar6 = param_2 * 4;
  piVar5 = (int *)(&DAT_00008250 + param_1 + iVar6);
  iVar3 = *(int *)(&DAT_0000825c + param_1 + *piVar5 * 4);
  if (iVar3 != 0x18) {
    if (0x18 < iVar3) {
      if (iVar3 != 0x19) {
        return;
      }
      iVar3 = FUN_MCARD__0010029c(param_1);
      *piVar5 = iVar3;
      if (iVar3 == *(int *)(&DAT_00008250 + param_1 + (1 - param_2) * 4)) {
        iVar3 = FUN_MCARD__0010029c(param_1);
        *piVar5 = iVar3;
      }
      iVar2 = *piVar5;
      puVar4 = (undefined4 *)(&DAT_00008248 + iVar6 + param_1);
      iVar3 = iVar2;
      if (iVar2 < 0) {
        iVar3 = iVar2 + 3;
      }
      FUN_MCARD__000f5c70(*puVar4,iVar3 >> 2,iVar2 + (iVar3 >> 2) * -4);
      iVar3 = FUN_MCARD__000f3994(*puVar4);
      if (iVar3 == 0) {
        return;
      }
      uVar1 = FUN_MCARD__000f5474(*puVar4);
      *(undefined4 *)(&DAT_0000825c + param_1 + *piVar5 * 4) = uVar1;
      *(undefined4 *)(param_1 + iVar6 + 0x8224) = 1;
      return;
    }
    if (iVar3 != 0x14) {
      return;
    }
  }
  param_2 = param_2 * 4;
  param_1 = param_1 + 0x8000;
  iVar3 = FUN_MCARD__000f3828(*(undefined4 *)(param_1 + param_2 + 0x248));
  if (iVar3 != 0) {
    *(undefined4 *)(param_1 + *(int *)(param_1 + param_2 + 0x250) * 4 + 0x25c) = 0x19;
    *(undefined4 *)(param_1 + param_2 + 0x224) = 1;
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ next_port__3PADi(struct PAD *this /*$a0*/, int port /*$a1*/)
 // line 956, offset 0x0010029c
	/* begin block 1 */
		// Start line: 957
		// Start offset: 0x0010029C
	/* end block 1 */
	// End offset: 0x001002A4
	// End Line: 973

	/* begin block 2 */
		// Start line: 3044
	/* end block 2 */
	// End Line: 3045

	/* begin block 3 */
		// Start line: 3060
	/* end block 3 */
	// End Line: 3061

undefined4 FUN_MCARD__0010029c(undefined4 param_1,undefined4 param_2)

{
  return param_2;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetCurrNoUsedBlocks__3PAD(struct PAD *this /*$a0*/)
 // line 978, offset 0x001002a4
	/* begin block 1 */
		// Start line: 979
		// Start offset: 0x001002A4
	/* end block 1 */
	// End offset: 0x001002E0
	// End Line: 980

	/* begin block 2 */
		// Start line: 3088
	/* end block 2 */
	// End Line: 3089

	/* begin block 3 */
		// Start line: 3089
	/* end block 3 */
	// End Line: 3090

void FUN_MCARD__001002a4(int param_1)

{
  FUN_MCARD__000f5e84(*(undefined4 *)
                       (&DAT_00008248 + param_1 + *(int *)(&DAT_00008258 + param_1) * 4));
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CurrSlotBlocksShared__3PADii(struct PAD *this /*$a0*/, int block1 /*$a1*/, int block2 /*$a2*/)
 // line 984, offset 0x001002e0
	/* begin block 1 */
		// Start line: 985
		// Start offset: 0x001002E0
	/* end block 1 */
	// End offset: 0x0010031C
	// End Line: 986

	/* begin block 2 */
		// Start line: 3100
	/* end block 2 */
	// End Line: 3101

	/* begin block 3 */
		// Start line: 3101
	/* end block 3 */
	// End Line: 3102

void FUN_MCARD__001002e0(int param_1)

{
  FUN_MCARD__000f5d30(*(undefined4 *)
                       (&DAT_00008248 + param_1 + *(int *)(&DAT_00008258 + param_1) * 4));
  return;
}



// decompiled code
// original method signature: 
// struct MCSLOT * /*$ra*/ GetCurrSlotPtr__3PAD(struct PAD *this /*$a0*/)
 // line 1001, offset 0x0010031c
	/* begin block 1 */
		// Start line: 1002
		// Start offset: 0x0010031C
	/* end block 1 */
	// End offset: 0x00100340
	// End Line: 1003

	/* begin block 2 */
		// Start line: 3134
	/* end block 2 */
	// End Line: 3135

	/* begin block 3 */
		// Start line: 3135
	/* end block 3 */
	// End Line: 3136

undefined4 FUN_MCARD__0010031c(int param_1)

{
  return *(undefined4 *)(&DAT_00008248 + param_1 + *(int *)(&DAT_00008258 + param_1) * 4);
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetCurrSlot__3PAD(struct PAD *this /*$a0*/)
 // line 1006, offset 0x00100340
	/* begin block 1 */
		// Start line: 1007
		// Start offset: 0x00100340
	/* end block 1 */
	// End offset: 0x00100354
	// End Line: 1008

	/* begin block 2 */
		// Start line: 3144
	/* end block 2 */
	// End Line: 3145

	/* begin block 3 */
		// Start line: 3145
	/* end block 3 */
	// End Line: 3146

undefined4 FUN_MCARD__00100340(int param_1)

{
  return *(undefined4 *)(&DAT_00008258 + param_1);
}



// decompiled code
// original method signature: 
// struct MCSLOT * /*$ra*/ GetDestSlotPtr__3PAD(struct PAD *this /*$a0*/)
 // line 1011, offset 0x00100354
	/* begin block 1 */
		// Start line: 1012
		// Start offset: 0x00100354
	/* end block 1 */
	// End offset: 0x0010037C
	// End Line: 1013

	/* begin block 2 */
		// Start line: 3154
	/* end block 2 */
	// End Line: 3155

	/* begin block 3 */
		// Start line: 3155
	/* end block 3 */
	// End Line: 3156

/* WARNING: Control flow encountered bad instruction data */

MCSLOT * GetDestSlotPtr__3PAD(PAD *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardChanged__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
 // line 1017, offset 0x0010037c
	/* begin block 1 */
		// Start line: 1018
		// Start offset: 0x0010037C
	/* end block 1 */
	// End offset: 0x001003A8
	// End Line: 1022

	/* begin block 2 */
		// Start line: 3166
	/* end block 2 */
	// End Line: 3167

	/* begin block 3 */
		// Start line: 3167
	/* end block 3 */
	// End Line: 3168

undefined4 FUN_MCARD__0010037c(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x8224 + param_2 * 4);
  if (*piVar1 != 0) {
    *piVar1 = 0;
    return 1;
  }
  return 0;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardInserted__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
 // line 1029, offset 0x001003b0
	/* begin block 1 */
		// Start line: 1030
		// Start offset: 0x001003B0
	/* end block 1 */
	// End offset: 0x001003E4
	// End Line: 1031

	/* begin block 2 */
		// Start line: 3190
	/* end block 2 */
	// End Line: 3191

	/* begin block 3 */
		// Start line: 3191
	/* end block 3 */
	// End Line: 3192

uint FUN_MCARD__001003b0(int param_1,int param_2)

{
  return (uint)(*(int *)(param_1 + 0x8000 + *(int *)(param_1 + 0x8000 + param_2 * 4 + 0x250) * 4 +
                        0x25c) != 0x19);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CycleSelectedSlot__3PAD(struct PAD *this /*$a0*/)
 // line 1035, offset 0x001003e4
	/* begin block 1 */
		// Start line: 1036
		// Start offset: 0x001003E4
	/* end block 1 */
	// End offset: 0x0010042C
	// End Line: 1039

	/* begin block 2 */
		// Start line: 3202
	/* end block 2 */
	// End Line: 3203

	/* begin block 3 */
		// Start line: 3203
	/* end block 3 */
	// End Line: 3204

void FUN_MCARD__001003e4(int param_1)

{
  if (*(int *)(param_1 + 0x8000 +
               *(int *)(param_1 + 0x8000 + (1 - *(int *)(&DAT_00008258 + param_1)) * 4 + 0x250) * 4
              + 0x25c) != 0x19) {
    *(int *)(&DAT_00008258 + param_1) = 1 - *(int *)(&DAT_00008258 + param_1);
  }
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardFormatted__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
 // line 1049, offset 0x0010042c
	/* begin block 1 */
		// Start line: 1050
		// Start offset: 0x0010042C
	/* end block 1 */
	// End offset: 0x00100460
	// End Line: 1051

	/* begin block 2 */
		// Start line: 3230
	/* end block 2 */
	// End Line: 3231

	/* begin block 3 */
		// Start line: 3231
	/* end block 3 */
	// End Line: 3232

uint FUN_MCARD__0010042c(int param_1,int param_2)

{
  return (uint)(*(int *)(param_1 + 0x8000 + *(int *)(param_1 + 0x8000 + param_2 * 4 + 0x250) * 4 +
                        0x25c) != 0x18);
}



// decompiled code
// original method signature: 
// int /*$ra*/ FormatCard__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
 // line 1054, offset 0x00100460
	/* begin block 1 */
		// Start line: 1055
		// Start offset: 0x00100460
	/* end block 1 */
	// End offset: 0x001004C8
	// End Line: 1059

	/* begin block 2 */
		// Start line: 3240
	/* end block 2 */
	// End Line: 3241

	/* begin block 3 */
		// Start line: 3241
	/* end block 3 */
	// End Line: 3242

undefined4 FUN_MCARD__00100460(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  param_1 = param_1 + 0x8000;
  iVar1 = FUN_MCARD__000f3b04(*(undefined4 *)(param_1 + param_2 * 4 + 0x248));
  uVar2 = 0xffffffff;
  if (iVar1 == 0x14) {
    uVar2 = 0x14;
    *(undefined4 *)(param_1 + *(int *)(param_1 + param_2 * 4 + 0x250) * 4 + 0x25c) = 0x14;
  }
  return uVar2;
}





