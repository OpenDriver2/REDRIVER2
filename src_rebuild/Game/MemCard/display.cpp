#include "THISDUST.H"
#include "DISPLAY.H"


// decompiled code
// original method signature: 
// struct DISPMAN * /*$ra*/ __7DISPMANPlPPlP3PADP10FILEFORMATib(struct DISPMAN *this /*$s2*/, long *imagePtr /*$a1*/, long **sliceIconPtrs /*stack 8*/, struct PAD *pad /*$a3*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/, int language /*stack 20*/, unsigned int save /*stack 24*/)
 // line 49, offset 0x000f65a8
	/* begin block 1 */
		// Start line: 50
		// Start offset: 0x000F65A8
		// Variables:
	// 		int n; // $s1
	// 		struct RECT rect; // stack offset -112
	/* end block 1 */
	// End offset: 0x000F727C
	// End Line: 389

	/* begin block 2 */
		// Start line: 98
	/* end block 2 */
	// End Line: 99

undefined4 *
FUN_MCARD__000f65a8(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4,
                   int param_5,undefined4 param_6,int param_7)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  undefined **ppuVar10;
  int *piVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined2 *puVar14;
  undefined2 *puVar15;
  undefined2 local_70;
  undefined2 local_6e;
  undefined2 local_6c;
  undefined2 local_6a;
  undefined4 *local_68;
  undefined4 *local_64;
  undefined4 *local_60;
  undefined4 *local_5c;
  undefined4 *local_58;
  undefined2 *local_54;
  undefined4 *local_50;
  undefined4 *local_4c;
  undefined4 *local_48;
  undefined4 *local_44;
  undefined4 *local_40;
  undefined2 *local_3c;
  undefined4 *local_38;
  undefined4 *local_34;
  DRAWENV *local_30;
  
  DAT_MCARD__0010ec70 = param_1;
  param_1[0x1179] = param_4;
  param_1[0x11a2] = param_5;
  sprintf((char *)(param_1 + 0x119a),s__sGREM_c00_MCARD__000f303c,param_5 + 0x62,
          (uint)*(byte *)(param_5 + 0x6f));
  param_1[1] = param_6;
  GetDispEnv(param_1 + 0x9c);
  GetDrawEnv(param_1 + 0x85);
  DrawSync(0);
  if ((DAT_MCARD__0010ee08 & 0x80) != 0) {
    FUN_MCARD__000fd86c(param_1,0x80,0x20);
  }
  SetDispMask(0);
  local_30 = (DRAWENV *)(param_1 + 0x69);
  param_1[0x65] = 0x200;
  param_1[0x88a] = 0;
  param_1[0x88b] = 0;
  param_1[0x66] = 0x100;
  param_1[0x67] = (int)draw_mode_pal.framex;
  iVar12 = 0x18;
  param_1[0x68] = (int)draw_mode_pal.framey;
  SetDefDrawEnv(local_30,0,0,0x200,0x100);
  SetDefDispEnv((DISPENV *)(param_1 + 0x80),param_1[0x88a],param_1[0x88b],param_1[0x65],
                param_1[0x66]);
  local_40 = param_1 + 0x89b;
  local_3c = (undefined2 *)((int)param_1 + 0x226e);
  local_64 = param_1 + 0xc29;
  local_60 = param_1 + 0x42;
  local_5c = param_1 + 0x45;
  local_48 = param_1 + 0x1131;
  local_4c = param_1 + 0x112b;
  local_38 = param_1 + 0x1140;
  local_34 = param_1 + 0x1143;
  local_68 = param_1 + 0x117b;
  local_44 = param_1 + 0x88f;
  puVar5 = param_1 + 0x6f8;
  *(undefined *)(param_1 + 0x6f) = 1;
  *(undefined *)((int)param_1 + 0x1bb) = 1;
  *(undefined2 *)(param_1 + 0x83) = 0x100;
  *(undefined *)((int)param_1 + 0x1bd) = 0;
  *(undefined *)((int)param_1 + 0x1be) = 0;
  *(undefined *)((int)param_1 + 0x1bf) = 0;
  *(undefined *)(param_1 + 0x84) = 0;
  *(undefined *)((int)param_1 + 0x211) = 0;
  param_1[0x88d] = 0x50;
  param_1[0x88c] = 0;
  param_1[0x88e] = 0;
  *(undefined2 *)(param_1 + 0x82) = *(undefined2 *)(param_1 + 0x67);
  *(undefined2 *)((int)param_1 + 0x20a) = *(undefined2 *)(param_1 + 0x68);
  *(undefined2 *)((int)param_1 + 0x20e) = *(undefined2 *)(param_1 + 0x66);
  do {
    SetPolyFT4(puVar5);
    iVar12 = iVar12 + -1;
    puVar5 = puVar5 + 10;
  } while (-1 < iVar12);
  param_1[0xa2] = 0;
  puVar5 = param_1 + 0x7f2;
  iVar12 = 0x13;
  do {
    SetPolyG3(puVar5);
    iVar12 = iVar12 + -1;
    puVar5 = puVar5 + 7;
  } while (-1 < iVar12);
  param_1[0xa3] = 0;
  param_1[0xa4] = 0;
  param_1[0xa1] = 0;
  param_1[0xa5] = 0;
  PutDrawEnv(local_30);
  PutDispEnv((DISPENV *)(param_1 + 0x80));
  *(undefined *)(param_1 + 0x6f) = 0;
  *(undefined2 *)((int)param_1 + 0x231e) = 0x10;
  FUN_MCARD__000fd658(param_1,&LAB_MCARD__001027e8,param_1 + 0x1128,2,0,0,0,0,0);
  FUN_MCARD__000fd658(param_1,&LAB_MCARD__001027e8,param_1 + 0x112e,1,0,0,0,0,0);
  if (param_1[1] != 9) {
    local_50 = param_1 + 0x9c4;
    puVar13 = param_1 + 0x9cb;
    puVar15 = (undefined2 *)((int)param_1 + 0x272e);
    local_58 = param_1 + 0xafb;
    local_54 = (undefined2 *)((int)param_1 + 0x2bee);
    ppuVar10 = &PTR_LAB_MCARD__001045f4_MCARD__001043f8;
    iVar12 = 0x3c;
    puVar5 = param_1 + 0x898;
    puVar2 = local_40;
    puVar14 = local_3c;
    do {
      FUN_MCARD__000fd658(param_1,*ppuVar10,puVar5,1,0,0,0,0,0);
      iVar12 = iVar12 + -1;
      *(undefined2 *)puVar2 = *(undefined2 *)(ppuVar10 + 1);
      puVar2 = puVar2 + 4;
      puVar1 = (undefined2 *)((int)ppuVar10 + 6);
      ppuVar10 = ppuVar10 + 2;
      *puVar14 = *puVar1;
      puVar14 = puVar14 + 8;
      puVar5 = puVar5 + 4;
    } while (-1 < iVar12);
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__001072bc_MCARD__001045e0,param_1 + 0x9c0,1,0,0,0,0,0)
    ;
    iVar12 = 0x3c;
    *(undefined2 *)(param_1 + 0x9c3) = DAT_MCARD__001045e4;
    *(undefined2 *)((int)param_1 + 0x270e) = DAT_MCARD__001045e6;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__001073c4_MCARD__001045e8,local_50,1,0,0,0,0,0);
    *(undefined2 *)(param_1 + 0x9c7) = DAT_MCARD__001045ec;
    ppuVar10 = &PTR_LAB_MCARD__001076b8_MCARD__001074cc;
    *(undefined2 *)((int)param_1 + 0x271e) = DAT_MCARD__001045ee;
    puVar5 = param_1 + 0x9c8;
    do {
      FUN_MCARD__000fd658(param_1,*ppuVar10,puVar5,1,0,0,0,0,0);
      iVar12 = iVar12 + -1;
      *(undefined2 *)puVar13 = *(undefined2 *)(ppuVar10 + 1);
      puVar13 = puVar13 + 4;
      puVar14 = (undefined2 *)((int)ppuVar10 + 6);
      ppuVar10 = ppuVar10 + 2;
      *puVar15 = *puVar14;
      puVar15 = puVar15 + 8;
      puVar5 = puVar5 + 4;
    } while (-1 < iVar12);
    ppuVar10 = &PTR_LAB_MCARD__001097dc_MCARD__001095f0;
    iVar12 = 0x3c;
    puVar5 = param_1 + 0xaf8;
    puVar2 = local_58;
    puVar14 = local_54;
    do {
      FUN_MCARD__000fd658(param_1,*ppuVar10,puVar5,1,0,0,0,0,0);
      iVar12 = iVar12 + -1;
      *(undefined2 *)puVar2 = *(undefined2 *)(ppuVar10 + 1);
      puVar2 = puVar2 + 4;
      puVar15 = (undefined2 *)((int)ppuVar10 + 6);
      ppuVar10 = ppuVar10 + 2;
      *puVar14 = *puVar15;
      puVar14 = puVar14 + 8;
      puVar5 = puVar5 + 4;
    } while (-1 < iVar12);
  }
  puVar2 = param_1 + 0xc28;
  iVar12 = 0xff;
  puVar5 = local_64;
  do {
    *(undefined2 *)puVar2 = 0;
    *puVar5 = 0;
    puVar5 = puVar5 + 5;
    iVar12 = iVar12 + -1;
    puVar2 = puVar2 + 5;
  } while (-1 < iVar12);
  param_1[0x1182] = 0;
  DrawSync(0);
  ClearOTag(DAT_MCARD__0010ec74,1);
  if ((DAT_MCARD__0010ee08 & 0x800) != 0) {
    FUN_MCARD__000fe834(param_1,DAT_MCARD__0010ece0,0xff,100,0,1000,0x80,0x80,0x80,0);
  }
  VSync(0);
  puVar2 = local_40 + 0xf4;
  puVar14 = local_3c + 0x1e8;
  DrawOTag(DAT_MCARD__0010ec74);
  DrawSync(0);
  SetDispMask(1);
  *(undefined2 *)((int)param_1 + 0x152) = 0xd4;
  *(undefined2 *)(param_1 + 0x48) = 0;
  *(undefined2 *)((int)param_1 + 0x122) = 0;
  *(undefined2 *)(param_1 + 0x49) = 0xea;
  *(undefined2 *)((int)param_1 + 0x126) = 0x40;
  *(undefined2 *)(param_1 + 0x4a) = 0;
  *(undefined2 *)((int)param_1 + 0x12a) = 0x40;
  *(undefined2 *)(param_1 + 0x4b) = 0xea;
  *(undefined2 *)((int)param_1 + 0x12e) = 0x34;
  *(undefined2 *)(param_1 + 0x4c) = 0xea;
  *(undefined2 *)((int)param_1 + 0x132) = 0;
  *(undefined2 *)(param_1 + 0x4d) = 0x88;
  *(undefined2 *)((int)param_1 + 0x136) = 0x74;
  *(undefined2 *)(param_1 + 0x4e) = 0x172;
  *(undefined2 *)((int)param_1 + 0x13a) = 0;
  *(undefined2 *)(param_1 + 0x4f) = 0x8e;
  *(undefined2 *)((int)param_1 + 0x13e) = 0x74;
  *(undefined2 *)(param_1 + 0x50) = 0;
  *(undefined2 *)((int)param_1 + 0x142) = 0x74;
  *(undefined2 *)(param_1 + 0x51) = 0xea;
  *(undefined2 *)((int)param_1 + 0x146) = 0x60;
  *(undefined2 *)(param_1 + 0x52) = 0xea;
  *(undefined2 *)((int)param_1 + 0x14a) = 0x74;
  *(undefined2 *)(param_1 + 0x53) = 0x116;
  *(undefined2 *)((int)param_1 + 0x14e) = 0x60;
  *(undefined2 *)(param_1 + 0x54) = 0;
  *(undefined2 *)(param_1 + 0x55) = 0x200;
  *(undefined2 *)((int)param_1 + 0x156) = 0x2c;
  *(undefined2 *)(param_1 + 0x56) = 0;
  *(undefined2 *)((int)param_1 + 0x15a) = 0x100;
  *(undefined2 *)(param_1 + 0x57) = 0xea;
  *(undefined2 *)((int)param_1 + 0x15e) = 0x40;
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined2 *)((int)param_1 + 0x162) = 0x140;
  *(undefined2 *)((int)param_1 + 0x17a) = 0x174;
  *(undefined2 *)((int)param_1 + 0x182) = 0x174;
  *(undefined2 *)((int)param_1 + 0x18a) = 0x1d4;
  *(undefined2 *)(param_1 + 0x59) = 0xea;
  *(undefined2 *)((int)param_1 + 0x166) = 0x34;
  *(undefined2 *)(param_1 + 0x5a) = 0xea;
  *(undefined2 *)((int)param_1 + 0x16a) = 0x100;
  *(undefined2 *)(param_1 + 0x5b) = 0x88;
  *(undefined2 *)((int)param_1 + 0x16e) = 0x74;
  *(undefined2 *)(param_1 + 0x5c) = 0x172;
  *(undefined2 *)((int)param_1 + 0x172) = 0x100;
  *(undefined2 *)(param_1 + 0x5d) = 0x8e;
  *(undefined2 *)((int)param_1 + 0x176) = 0x74;
  *(undefined2 *)(param_1 + 0x5e) = 0;
  *(undefined2 *)(param_1 + 0x5f) = 0xea;
  *(undefined2 *)((int)param_1 + 0x17e) = 0x60;
  *(undefined2 *)(param_1 + 0x60) = 0xea;
  *(undefined2 *)(param_1 + 0x61) = 0x116;
  *(undefined2 *)((int)param_1 + 0x186) = 0x60;
  *(undefined2 *)(param_1 + 0x62) = 0;
  *(undefined2 *)(param_1 + 99) = 0x200;
  *(undefined2 *)((int)param_1 + 0x18e) = 0x2c;
  local_6e = 0x7f;
  local_70 = 0xea;
  local_6c = 0x116;
  local_6a = 0x4a;
  SetDrawArea(local_60,&local_70);
  SetDrawArea(local_5c,local_30);
  FUN_MCARD__000fd658(param_1,&LAB_MCARD__001029b8,local_48,0,0,0,0,0,0);
  FUN_MCARD__000fd658(param_1,&LAB_MCARD__001028f0,local_4c,0,0,0,0,0,0);
  iVar12 = 3;
  FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00102d70_MCARD__00102d68,local_38,0,0,0,0,0,0);
  FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103070_MCARD__00102d6c,local_34,0,0,0,0,0,0);
  ppuVar10 = &PTR_LAB_MCARD__00103390_MCARD__00103370;
  puVar5 = param_1 + 0x98c;
  do {
    puVar7 = *ppuVar10;
    ppuVar10 = ppuVar10 + 1;
    iVar12 = iVar12 + -1;
    FUN_MCARD__000fd658(param_1,puVar7,puVar5,1,0,0,0,0,0);
    *(undefined2 *)puVar2 = 0x20;
    *puVar14 = 0x14;
    puVar14 = puVar14 + 8;
    puVar2 = puVar2 + 4;
    puVar5 = puVar5 + 4;
  } while (-1 < iVar12);
  if ((DAT_MCARD__0010ee08 & 8) != 0) {
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103390_MCARD__00103370,param_1 + 0x98c,1,0,0,0,0,0)
    ;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103510_MCARD__00103374,param_1 + 0x994,1,0,0,0,0,0)
    ;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103690_MCARD__00103378,param_1 + 0x998,1,0,0,0,0,0)
    ;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103810_MCARD__0010337c,param_1 + 0x990,1,0,0,0,0,0)
    ;
  }
  iVar12 = 3;
  puVar14 = local_3c + 0x208;
  puVar2 = local_40 + 0x104;
  ppuVar10 = &PTR_LAB_MCARD__00104000_MCARD__00103ff0;
  puVar5 = param_1 + 0x99c;
  do {
    puVar7 = *ppuVar10;
    ppuVar10 = ppuVar10 + 1;
    iVar12 = iVar12 + -1;
    FUN_MCARD__000fd658(param_1,puVar7,puVar5,1,0,0,0,0,0);
    *(undefined2 *)puVar2 = 0x11;
    *puVar14 = 0x11;
    puVar14 = puVar14 + 8;
    puVar2 = puVar2 + 4;
    puVar5 = puVar5 + 4;
  } while (-1 < iVar12);
  ppuVar10 = &PTR_LAB_MCARD__00103990_MCARD__00103380;
  iVar12 = 3;
  puVar14 = local_3c + 0x228;
  puVar2 = local_40 + 0x114;
  puVar5 = param_1 + 0x9ac;
  do {
    puVar7 = *ppuVar10;
    ppuVar10 = ppuVar10 + 1;
    iVar12 = iVar12 + -1;
    FUN_MCARD__000fd658(param_1,puVar7,puVar5,1,0,0,0,0,0);
    *(undefined2 *)puVar2 = 0x24;
    *puVar14 = 0x13;
    puVar14 = puVar14 + 8;
    puVar2 = puVar2 + 4;
    puVar5 = puVar5 + 4;
  } while (-1 < iVar12);
  if ((DAT_MCARD__0010ee08 & 8) != 0) {
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103990_MCARD__00103380,param_1 + 0x9ac,1,0,0,0,0,0)
    ;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103b28_MCARD__00103384,param_1 + 0x9b4,1,0,0,0,0,0)
    ;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103cc0_MCARD__00103388,param_1 + 0x9b8,1,0,0,0,0,0)
    ;
    FUN_MCARD__000fd658(param_1,PTR_LAB_MCARD__00103e58_MCARD__0010338c,param_1 + 0x9b0,1,0,0,0,0,0)
    ;
  }
  *(undefined2 *)(param_1 + 0x9ae) = 0x23;
  *(undefined2 *)(param_1 + 0x9b2) = 0x23;
  *(undefined2 *)(param_1 + 0x9b6) = 0x23;
  *(undefined2 *)(param_1 + 0x9ba) = 0x23;
  FUN_MCARD__000fe908(param_1,0x260,0xb0,0x220,0xc0);
  iVar12 = 1;
  if (*(int *)(param_3 + 4) != 0) {
    piVar11 = (int *)(param_3 + 4);
    puVar5 = param_1 + 0x1149;
    do {
      iVar9 = iVar12;
      if (iVar12 < 0) {
        iVar9 = iVar12 + 7;
      }
      iVar8 = *piVar11;
      piVar11 = piVar11 + 1;
      FUN_MCARD__000fd658(param_1,iVar8,puVar5,1,1,0x220,iVar12 + 0xc0,
                          (iVar12 + (iVar9 >> 3) * -8) * 4 + 0x260,(iVar9 >> 3) * 0x10 + 0xb0);
      iVar12 = iVar12 + 1;
    } while ((*piVar11 != 0) && (puVar5 = puVar5 + 3, iVar12 < 0x10));
  }
  if (param_7 == 0) {
    param_1[0x118b] = 4;
    param_1[0x1191] = DAT_MCARD__0010ece8;
  }
  else {
    param_1[0x118b] = 5;
    param_1[0x1191] = DAT_MCARD__0010ecf0;
  }
  param_1[0x118a] = param_1[0x118b];
  param_1[0x1192] = DAT_MCARD__0010ecf8;
  param_1[0x1193] = DAT_MCARD__0010ed00;
  param_1[0x1194] = DAT_MCARD__0010ed08;
  param_1[0x1195] = DAT_MCARD__0010ed10;
  param_1[0x1196] = DAT_MCARD__0010ed04;
  uVar3 = DAT_MCARD__0010ed9c;
  param_1[0x1199] = 0xf3048;
  param_1[0x1183] = 2;
  param_1[0x1184] = 0;
  param_1[0x1185] = 0;
  param_1[0x1186] = 0;
  param_1[0x1187] = 0;
  param_1[0x896] = 0xffffffff;
  param_1[0x897] = 0;
  param_1[0x1197] = uVar3;
  uVar3 = FUN_MCARD__00100158(param_1[0x1179]);
  iVar12 = 6;
  param_1[0xa6] = uVar3;
  uVar4 = FUN_MCARD__0010016c(param_1[0x1179]);
  uVar3 = DAT_MCARD__0010ec74;
  param_1[0xa7] = uVar4;
  ClearOTag(uVar3,1);
  puVar5 = local_68 + 6;
  do {
    *puVar5 = 0xffffffff;
    iVar12 = iVar12 + -1;
    puVar5 = puVar5 + -1;
  } while (-1 < iVar12);
  uVar6 = DAT_MCARD__0010ee08 & 8;
  *param_1 = 0;
  if (uVar6 == 0) {
    param_1[0x118c] = 0x40;
    FUN_MCARD__000fa684(param_1,s_ABCDEFGHIJKLMNOPQRSTUVWXYZ_MCARD__000f304c,0,0,100,0x80,0x80,0x80)
    ;
    FUN_MCARD__000fa684(param_1,s_abcdefghijklmnopqrstuvwxyz_MCARD__000f306c,0,0,100,0x80,0x80,0x80)
    ;
    FUN_MCARD__000fa684(param_1,s_0123456789_MCARD__000f308c,0,0,100,0x80,0x80,0x80);
  }
  else {
    param_1[0x118c] = 0x100;
  }
  SetDispMask(0);
  FUN_MCARD__000fa174(param_1);
  iVar12 = 6;
  puVar5 = local_44;
  do {
    *puVar5 = 1;
    FUN_MCARD__000fa174(param_1);
    iVar12 = iVar12 + -1;
    puVar5 = puVar5 + 1;
  } while (-1 < iVar12);
  if ((DAT_MCARD__0010ee08 & 0x100) != 0) {
    FUN_MCARD__000fea44(param_1,0x100,0,0x20);
  }
  SetDispMask(1);
  return param_1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ _._7DISPMAN(struct DISPMAN *this /*$s2*/, int __in_chrg /*$s3*/)
 // line 392, offset 0x000fdad8
	/* begin block 1 */
		// Start line: 393
		// Start offset: 0x000FDAD8
		// Variables:
	// 		struct RECT rect; // stack offset -32
	/* end block 1 */
	// End offset: 0x000FDB38
	// End Line: 406

	/* begin block 2 */
		// Start line: 784
	/* end block 2 */
	// End Line: 785

	/* begin block 3 */
		// Start line: 5334
	/* end block 3 */
	// End Line: 5335

void FUN_MCARD__000fdad8(int param_1,uint param_2)

{
  DRAWENV *pDVar1;
  
  if ((DAT_MCARD__0010ee08 & 0x80) == 0) {
    if ((DAT_MCARD__0010ee08 & 0x100) != 0) {
      FUN_MCARD__000fea44(param_1,0,0x100,0x20);
    }
  }
  else {
    FUN_MCARD__000fd86c(param_1,0x80,0x20);
  }
  SetDispMask(0);
  pDVar1 = (DRAWENV *)(param_1 + 0x1a4);
  *(undefined *)(param_1 + 0x1bc) = 1;
  PutDrawEnv(pDVar1);
  *(undefined4 *)(param_1 + 0x1a4) = *(undefined4 *)(param_1 + 0x270);
  *(undefined4 *)(param_1 + 0x1a8) = *(undefined4 *)(param_1 + 0x274);
  PutDrawEnv(pDVar1);
  *(undefined4 *)(param_1 + 0x1a4) = *(undefined4 *)(param_1 + 0x214);
  *(undefined4 *)(param_1 + 0x1a8) = *(undefined4 *)(param_1 + 0x218);
  PutDrawEnv(pDVar1);
  PutDrawEnv((DRAWENV *)(param_1 + 0x214));
  PutDispEnv((DISPENV *)(param_1 + 0x270));
  if ((param_2 & 1) != 0) {
    __builtin_delete(param_1);
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTitleBar__7DISPMAN(struct DISPMAN *this /*$s3*/)
 // line 472, offset 0x000f72b8
	/* begin block 1 */
		// Start line: 473
		// Start offset: 0x000F72B8
		// Variables:
	// 		char *titleText; // $s2

		/* begin block 1.1 */
			// Start line: 473
			// Start offset: 0x000F72B8

			/* begin block 1.1.1 */
				// Start line: 478
				// Start offset: 0x000F72E4

				/* begin block 1.1.1.1 */
					// Start line: 528
					// Start offset: 0x000F740C

					/* begin block 1.1.1.1.1 */
						// Start line: 530
						// Start offset: 0x000F742C
						// Variables:
					// 		char *titleText2; // $s0
					// 		int i; // $t0
					/* end block 1.1.1.1.1 */
					// End offset: 0x000F7454
					// End Line: 544
				/* end block 1.1.1.1 */
				// End offset: 0x000F74E8
				// End Line: 548
			/* end block 1.1.1 */
			// End offset: 0x000F74EC
			// End Line: 551
		/* end block 1.1 */
		// End offset: 0x000F74EC
		// End Line: 551
	/* end block 1 */
	// End offset: 0x000F74EC
	// End Line: 551

	/* begin block 2 */
		// Start line: 1469
	/* end block 2 */
	// End Line: 1470

void FUN_MCARD__000f72b8(int param_1)

{
  int iVar1;
  char *pcVar2;
  char *unaff_s2;
  char *pcVar3;
  
  if (*(int *)(&DAT_0000223c + param_1) == 0) {
    return;
  }
  MoveImage(param_1 + 0x158,(int)*(short *)(param_1 + 0x120),(int)*(short *)(param_1 + 0x122));
  DrawSync(0);
  iVar1 = *(int *)(&DAT_00004628 + param_1);
  pcVar2 = unaff_s2;
  if (iVar1 != 2) {
    if (iVar1 < 3) {
      pcVar3 = unaff_s2;
      pcVar2 = DAT_MCARD__0010ecf4;
      if (iVar1 != 1) goto LAB_MCARD__000f7414;
    }
    else {
      if (((iVar1 < 6) && (3 < iVar1)) && (pcVar2 = DAT_MCARD__0010ecec, gMemCardMode != 0x20)) {
        if (gMemCardMode < 0x21) {
          pcVar2 = DAT_MCARD__0010edec;
          if (gMemCardMode != 0x10) {
            pcVar3 = DAT_MCARD__0010ede8;
            if (gMemCardMode != 0x11) {
              pcVar3 = unaff_s2;
            }
            goto LAB_MCARD__000f7414;
          }
        }
        else {
          pcVar2 = DAT_MCARD__0010edf4;
          if (gMemCardMode != 0x80) {
            if (gMemCardMode < 0x81) {
              pcVar3 = DAT_MCARD__0010ece4;
              if (gMemCardMode != 0x21) {
                pcVar3 = unaff_s2;
              }
            }
            else {
              pcVar3 = DAT_MCARD__0010edf0;
              if (gMemCardMode != 0x81) {
                pcVar3 = unaff_s2;
              }
            }
            goto LAB_MCARD__000f7414;
          }
        }
      }
    }
  }
  pcVar3 = pcVar2;
LAB_MCARD__000f7414:
  iVar1 = FUN_MCARD__000fcc54(param_1);
  if (iVar1 < 0xc9) {
    FUN_MCARD__000fe834(param_1,pcVar3,0x82,0x15,2,1000,0x80,0x80,0x80,0);
    *(undefined4 *)(&DAT_0000223c + param_1) = 0;
  }
  else {
    iVar1 = 0;
    pcVar2 = pcVar3;
    while (*pcVar2 != ' ') {
      pcVar2 = pcVar2 + 1;
      iVar1 = iVar1 + 1;
    }
    FUN_MCARD__000fe834(param_1,pcVar3,0x82,0x13,0,iVar1,0x80,0x80,0x80,0);
    FUN_MCARD__000fe834(param_1,pcVar2 + 1,0x82,0x24,0,1000,0x80,0x80,0x80,0);
    *(undefined4 *)(&DAT_0000223c + param_1) = 0;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCards__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 555, offset 0x000f7508
	/* begin block 1 */
		// Start line: 556
		// Start offset: 0x000F7508
	/* end block 1 */
	// End offset: 0x000F7670
	// End Line: 590

	/* begin block 2 */
		// Start line: 1642
	/* end block 2 */
	// End Line: 1643

void FUN_MCARD__000f7508(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (*(int *)(&DAT_00002240 + param_1) == 0) {
    if ((((*(int *)(&DAT_00002258 + param_1) < 0) && (*(int *)(&DAT_0000460c + param_1) == 1)) &&
        (iVar1 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar1 != 0)) &&
       (iVar1 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar1 != 0)) {
      uVar2 = FUN_MCARD__001001ac(*(undefined4 *)(&DAT_000045e4 + param_1),0);
      FUN_MCARD__000fe30c(param_1,0x41,0x46,uVar2,(uint)(*(int *)(&DAT_0000460c + param_1) == 1));
    }
  }
  else {
    MoveImage(param_1 + 0x160,(int)*(short *)(param_1 + 0x128),(int)*(short *)(param_1 + 0x12a));
    DrawSync(0);
    iVar1 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),0);
    if (iVar1 != 0) {
      uVar3 = 0;
      uVar2 = FUN_MCARD__001001ac(*(undefined4 *)(&DAT_000045e4 + param_1),0);
      iVar1 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),0);
      if (iVar1 != 0) {
        uVar3 = (uint)(*(int *)(&DAT_0000460c + param_1) == 1);
      }
      FUN_MCARD__000fe30c(param_1,0x41,0x46,uVar2,uVar3);
      iVar1 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),0);
      if ((iVar1 != 0) && ((DAT_MCARD__0010ee08 & 0x20) != 0)) {
        FUN_MCARD__000fe61c(param_1,param_1 + 0x4500,0x14,0x48,0x80,0x80,0x80,0);
      }
    }
    *(undefined4 *)(&DAT_00002240 + param_1) = 0;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMenu__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 602, offset 0x000f7688
	/* begin block 1 */
		// Start line: 603
		// Start offset: 0x000F7688
	/* end block 1 */
	// End offset: 0x000F79AC
	// End Line: 694

	/* begin block 2 */
		// Start line: 1736
	/* end block 2 */
	// End Line: 1737

void FUN_MCARD__000f7688(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (*(int *)(&DAT_00002244 + param_1) == 0) {
    if (*(int *)(&DAT_0000460c + param_1) == 2) {
      iVar1 = *(int *)(&DAT_00004610 + param_1);
      if (iVar1 == 3) {
        if (*(int *)(&DAT_0000462c + param_1) == 5) {
          uVar2 = *(undefined4 *)(&DAT_00002234 + param_1);
          FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004650 + param_1),0xfa,0x3f,0,0xe,uVar2
                              ,uVar2,uVar2,0);
        }
        else {
          uVar2 = *(undefined4 *)(&DAT_00002234 + param_1);
          FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004650 + param_1),0xfa,0x28,0,0xe,uVar2
                              ,uVar2,uVar2,0);
        }
      }
      else {
        uVar2 = *(undefined4 *)(&DAT_00002234 + param_1);
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004644 + param_1 + iVar1 * 4),0xfa,
                            iVar1 * 0x17 + 0x11,0,0xe,uVar2,uVar2,uVar2,0);
      }
    }
  }
  else {
    MoveImage(param_1 + 0x168,(int)*(short *)(param_1 + 0x130),(int)*(short *)(param_1 + 0x132));
    DrawSync(0);
    if (*(int *)(&DAT_0000462c + param_1) == 5) {
      FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004650 + param_1),0xfa,0x3f,0,0xe,0x80,0x80
                          ,0x80,0);
      *(undefined4 *)(&DAT_0000463c + param_1) = 0;
      *(undefined4 *)(&DAT_00004640 + param_1) = 1;
      iVar1 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
      if (iVar1 < 1) {
        *(undefined4 *)(&DAT_00004638 + param_1) = 0;
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004648 + param_1),0xfa,0x28,0,0xe,0x20,
                            0x20,0x20,1);
      }
      else {
        *(undefined4 *)(&DAT_00004638 + param_1) = 1;
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004648 + param_1),0xfa,0x28,0,0xe,0x80,
                            0x80,0x80,0);
      }
    }
    else {
      FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004650 + param_1),0xfa,0x28,0,0xe,0x80,0x80
                          ,0x80,0);
      *(undefined4 *)(&DAT_00004638 + param_1) = 0;
      *(undefined4 *)(&DAT_0000463c + param_1) = 0;
      *(undefined4 *)(&DAT_00004640 + param_1) = 1;
    }
    uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar1 = FUN_MCARD__000f5fbc(uVar2,param_1 + 0x4668);
    if ((iVar1 < 1) && (*(int *)(&DAT_0000462c + param_1) != 5)) {
      *(undefined4 *)(&DAT_00004634 + param_1) = 0;
      FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004644 + param_1),0xfa,0x11,0,0xe,0x20,0x20
                          ,0x20,1);
    }
    else {
      *(undefined4 *)(&DAT_00004634 + param_1) = 1;
      FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004644 + param_1),0xfa,0x11,0,0xe,0x80,0x80
                          ,0x80,0);
    }
    uVar3 = *(uint *)(&DAT_00004610 + param_1);
    iVar1 = *(int *)(&DAT_00004634 + param_1 + uVar3 * 4);
    while (iVar1 == 0) {
      uVar3 = uVar3 + 1 & 3;
      *(uint *)(&DAT_00004610 + param_1) = uVar3;
      iVar1 = *(int *)(&DAT_00004634 + param_1 + uVar3 * 4);
    }
    *(undefined4 *)(&DAT_00002244 + param_1) = 0;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawKeyInfo__7DISPMAN(struct DISPMAN *this /*$s3*/)
 // line 701, offset 0x000f79c8
	/* begin block 1 */
		// Start line: 702
		// Start offset: 0x000F79C8
	/* end block 1 */
	// End offset: 0x000F7C30
	// End Line: 742

	/* begin block 2 */
		// Start line: 1944
	/* end block 2 */
	// End Line: 1945

void FUN_MCARD__000f79c8(int param_1)

{
  int iVar1;
  
  if (*(int *)(&DAT_00002248 + param_1) != 0) {
    MoveImage(param_1 + 0x170,(int)*(short *)(param_1 + 0x138),(int)*(short *)(param_1 + 0x13a));
    DrawSync(0);
    iVar1 = FUN_MCARD__001000d0(*(undefined4 *)(&DAT_000045e4 + param_1));
    if (iVar1 == 0) {
      iVar1 = FUN_MCARD__000ffee0(*(undefined4 *)(&DAT_000045e4 + param_1));
      if (iVar1 == 0) {
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_0000465c + param_1),0x1ae,0x56,1,1000,0x80,
                            0x80,0x80,0);
        FUN_MCARD__000fe61c(param_1,param_1 + 0x2630,0x183,0x58,0x80,0x80,0x80,0);
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004658 + param_1),0x1ae,0x34,1,1000,0x80,
                            0x80,0x80,0);
        FUN_MCARD__000fe61c(param_1,param_1 + 0x2660,0x183,0x36,0x80,0x80,0x80,0);
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004654 + param_1),0x1ae,0x12,1,1000,0x80,
                            0x80,0x80,0);
        FUN_MCARD__000fe61c(param_1,param_1 + 0x2650,0x183,0x14,0x80,0x80,0x80,0);
        *(undefined4 *)(&DAT_00002248 + param_1) = 0;
      }
      else {
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_0000465c + param_1),0x1ae,0x56,1,1000,0x80,
                            0x80,0x80,0);
        FUN_MCARD__000fe61c(param_1,param_1 + 0x26b0,0x183,0x58,0x80,0x80,0x80,0);
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004658 + param_1),0x1ae,0x34,1,1000,0x80,
                            0x80,0x80,0);
        FUN_MCARD__000fe61c(param_1,param_1 + 0x26e0,0x183,0x36,0x80,0x80,0x80,0);
        FUN_MCARD__000fd000(param_1,*(undefined4 *)(&DAT_00004654 + param_1),0x1ae,0x12,1,1000,0x80,
                            0x80,0x80,0);
        FUN_MCARD__000fe61c(param_1,param_1 + 0x26d0,0x183,0x14,0x80,0x80,0x80,0);
        *(undefined4 *)(&DAT_00002248 + param_1) = 0;
      }
    }
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawBlocks__7DISPMAN(struct DISPMAN *this /*$s1*/)
 // line 747, offset 0x000f7c4c
	/* begin block 1 */
		// Start line: 748
		// Start offset: 0x000F7C4C
		// Variables:
	// 		int x; // $s6
	// 		int y; // $s2
	/* end block 1 */
	// End offset: 0x000F816C
	// End Line: 834

	/* begin block 2 */
		// Start line: 2036
	/* end block 2 */
	// End Line: 2037

void FUN_MCARD__000f7c4c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_34;
  int local_30;
  int local_2c;
  
  if (*(int *)(&DAT_0000224c + param_1) == 0) {
    if (0xe < *(uint *)(&DAT_00002258 + param_1)) {
      iVar6 = 0;
      if (*(int *)(&DAT_0000460c + param_1) != 4) {
        return;
      }
      do {
        iVar5 = 0;
        iVar9 = iVar6 + 1;
        iVar8 = 0x1a;
        iVar1 = iVar6 * 5;
        iVar7 = 0x1a;
        do {
          if ((*(int *)(&DAT_00004614 + param_1) == iVar1) ||
             (iVar2 = FUN_MCARD__001002e0(*(undefined4 *)(&DAT_000045e4 + param_1),
                                          *(int *)(&DAT_00004614 + param_1),iVar1), iVar2 != 0)) {
            uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
            uVar3 = FUN_MCARD__000f5e08(uVar3,iVar1);
            local_50 = *(undefined4 *)(&DAT_00002234 + param_1);
            FUN_MCARD__000fe434(param_1,uVar3,iVar7,iVar6 * 0x1a + 0x82,local_50,local_50,local_50,0
                                ,1);
          }
          iVar2 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar4 = *(int *)(&DAT_00004614 + param_1);
          if (((iVar4 == iVar2) && (iVar4 <= iVar1)) &&
             (iVar1 < (int)(iVar4 + (uint)**(byte **)(&DAT_00004688 + param_1)))) {
            uVar3 = *(undefined4 *)(&DAT_00002234 + param_1);
            FUN_MCARD__000fe434(param_1,&DAT_000045d8 + param_1,iVar8,iVar6 * 0x1a + 0x82,uVar3,
                                uVar3,uVar3,0,1);
          }
          iVar8 = iVar8 + 0x2a;
          iVar1 = iVar1 + 1;
          iVar5 = iVar5 + 1;
          iVar7 = iVar7 + 0x2a;
        } while (iVar5 < 5);
        iVar6 = iVar9;
      } while (iVar9 < 3);
      return;
    }
    if (*(int *)(&DAT_0000460c + param_1) == 4) {
      uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      uVar3 = FUN_MCARD__000f5e08(uVar3,*(undefined4 *)(&DAT_00002258 + param_1));
      FUN_MCARD__000fe434(param_1,uVar3,(*(int *)(&DAT_00002258 + param_1) % 5) * 0x2a + 0x1a,
                          (*(int *)(&DAT_00002258 + param_1) / 5) * 0x1a + 0x82,0x50,0x50,0x50,0,1);
    }
    else {
      uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      uVar3 = FUN_MCARD__000f5e08(uVar3,*(undefined4 *)(&DAT_00002258 + param_1));
      FUN_MCARD__000fe434(param_1,uVar3,(*(int *)(&DAT_00002258 + param_1) % 5) * 0x2a + 0x1a,
                          (*(int *)(&DAT_00002258 + param_1) / 5) * 0x1a + 0x82,0x2d,0x2d,0x2d,1,1);
    }
    *(undefined4 *)(&DAT_00002258 + param_1) = 0xffffffff;
  }
  else {
    MoveImage(param_1 + 0x178,(int)*(short *)(param_1 + 0x140),(int)*(short *)(param_1 + 0x142));
    DrawSync(0);
    iVar6 = 2;
    do {
      iVar8 = 0;
      iVar1 = iVar6 + -1;
      iVar7 = iVar6 * 0x1a;
      iVar9 = 0x1a;
      local_34 = 0x1a;
      local_30 = 0x1a;
      local_2c = 0x1a;
      do {
        iVar5 = iVar6 * 5 + iVar8;
        if ((*(int *)(&DAT_00004614 + param_1) == iVar5) ||
           (iVar2 = FUN_MCARD__001002e0(*(undefined4 *)(&DAT_000045e4 + param_1),
                                        *(int *)(&DAT_00004614 + param_1),iVar5), iVar2 != 0)) {
          if (*(int *)(&DAT_0000225c + param_1) < 1) {
            uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
            uVar3 = FUN_MCARD__000f5e08(uVar3,iVar5);
            local_50 = 0x2d;
            local_4c = 0x2d;
            local_48 = 0x2d;
            local_44 = 1;
            iVar5 = local_2c;
            goto LAB_MCARD__000f7dfc;
          }
          uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          uVar3 = FUN_MCARD__000f5e08(uVar3,iVar5);
          iVar5 = *(int *)(&DAT_0000225c + param_1) * -8 + 0xb4;
          FUN_MCARD__000fe434(param_1,uVar3,iVar9,iVar7 + 0x82,iVar5,iVar5,iVar5,1,1);
        }
        else {
          if (*(int *)(&DAT_0000460c + param_1) == 4) {
            uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
            uVar3 = FUN_MCARD__000f5e08(uVar3,iVar5);
            local_50 = 0x50;
            local_4c = 0x50;
            local_48 = 0x50;
            local_44 = 0;
            iVar5 = local_30;
LAB_MCARD__000f7dfc:
            FUN_MCARD__000fe434(param_1,uVar3,iVar5,iVar7 + 0x82,local_50,local_4c,local_48,local_44
                                ,1);
          }
          else {
            uVar3 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
            uVar3 = FUN_MCARD__000f5e08(uVar3,iVar5);
            FUN_MCARD__000fe434(param_1,uVar3,local_34,iVar7 + 0x82,0x2d,0x2d,0x2d,1,1);
          }
        }
        local_34 = local_34 + 0x2a;
        local_30 = local_30 + 0x2a;
        iVar8 = iVar8 + 1;
        local_2c = local_2c + 0x2a;
        iVar9 = iVar9 + 0x2a;
      } while (iVar8 < 5);
      iVar6 = iVar1;
    } while (-1 < iVar1);
    *(undefined4 *)(&DAT_0000224c + param_1) = 0;
    if (*(int *)(&DAT_0000225c + param_1) != 0) {
      return;
    }
  }
  FUN_MCARD__000fe040(param_1,6);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSlices__7DISPMAN(struct DISPMAN *this /*$s2*/)
 // line 839, offset 0x000f819c
	/* begin block 1 */
		// Start line: 840
		// Start offset: 0x000F819C
		// Variables:
	// 		int n; // $s3
	// 		char textBuffer[50]; // stack offset -104
	// 		int iconRef; // $v1
	// 		int maxIcons; // $s1

		/* begin block 1.1 */
			// Start line: 868
			// Start offset: 0x000F82BC

			/* begin block 1.1.1 */
				// Start line: 869
				// Start offset: 0x000F82CC

				/* begin block 1.1.1.1 */
					// Start line: 870
					// Start offset: 0x000F82CC

					/* begin block 1.1.1.1.1 */
						// Start line: 874
						// Start offset: 0x000F8304

						/* begin block 1.1.1.1.1.1 */
							// Start line: 877
							// Start offset: 0x000F8304

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 887
								// Start offset: 0x000F83BC

								/* begin block 1.1.1.1.1.1.1.1 */
									// Start line: 887
									// Start offset: 0x000F83BC

									/* begin block 1.1.1.1.1.1.1.1.1 */
										// Start line: 896
										// Start offset: 0x000F8404

										/* begin block 1.1.1.1.1.1.1.1.1.1 */
											// Start line: 896
											// Start offset: 0x000F8404

											/* begin block 1.1.1.1.1.1.1.1.1.1.1 */
												// Start line: 896
												// Start offset: 0x000F841C

												/* begin block 1.1.1.1.1.1.1.1.1.1.1.1 */
													// Start line: 898
													// Start offset: 0x000F841C

													/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1 */
														// Start line: 898
														// Start offset: 0x000F8460

														/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
															// Start line: 900
															// Start offset: 0x000F8460

															/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																// Start line: 902
																// Start offset: 0x000F847C

																/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																	// Start line: 903
																	// Start offset: 0x000F847C

																	/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																		// Start line: 904
																		// Start offset: 0x000F8484

																		/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																			// Start line: 905
																			// Start offset: 0x000F8484

																			/* begin block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																				// Start line: 906
																				// Start offset: 0x000F84A8
																			/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																			// End offset: 0x000F84A8
																			// End Line: 907
																		/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																		// End offset: 0x000F8574
																		// End Line: 919
																	/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																	// End offset: 0x000F8574
																	// End Line: 919
																/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
																// End offset: 0x000F8770
																// End Line: 955
															/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
															// End offset: 0x000F8770
															// End Line: 955
														/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1.1 */
														// End offset: 0x000F8770
														// End Line: 955
													/* end block 1.1.1.1.1.1.1.1.1.1.1.1.1 */
													// End offset: 0x000F8770
													// End Line: 955
												/* end block 1.1.1.1.1.1.1.1.1.1.1.1 */
												// End offset: 0x000F8784
												// End Line: 961
											/* end block 1.1.1.1.1.1.1.1.1.1.1 */
											// End offset: 0x000F8784
											// End Line: 961
										/* end block 1.1.1.1.1.1.1.1.1.1 */
										// End offset: 0x000F8784
										// End Line: 961
									/* end block 1.1.1.1.1.1.1.1.1 */
									// End offset: 0x000F8784
									// End Line: 961
								/* end block 1.1.1.1.1.1.1.1 */
								// End offset: 0x000F8784
								// End Line: 961
							/* end block 1.1.1.1.1.1.1 */
							// End offset: 0x000F8784
							// End Line: 961
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000F8784
						// End Line: 961
					/* end block 1.1.1.1.1 */
					// End offset: 0x000F8784
					// End Line: 961
				/* end block 1.1.1.1 */
				// End offset: 0x000F8784
				// End Line: 961
			/* end block 1.1.1 */
			// End offset: 0x000F87D4
			// End Line: 975
		/* end block 1.1 */
		// End offset: 0x000F8AE8
		// End Line: 1022
	/* end block 1 */
	// End offset: 0x000F8B28
	// End Line: 1028

	/* begin block 2 */
		// Start line: 2225
	/* end block 2 */
	// End Line: 2226

	/* begin block 3 */
		// Start line: 2237
	/* end block 3 */
	// End Line: 2238

void FUN_MCARD__000f819c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char acStack104 [56];
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar7 = 0;
  iVar8 = 0;
  FUN_MCARD__0010eb20(DAT_MCARD__0010ec74,param_1 + 0x114);
  while( true ) {
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar2 = FUN_MCARD__000f64f4(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
    if (iVar2 <= iVar8) break;
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    uVar6 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8,0);
    if ((uVar6 < 0x10) && (uVar7 == 0)) {
      uVar7 = 1;
    }
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    uVar6 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8,1);
    if ((uVar6 < 0x10) && (uVar7 < 2)) {
      uVar7 = 2;
    }
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    uVar6 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8,2);
    if ((uVar6 < 0x10) && (uVar7 < 3)) {
      uVar7 = 3;
    }
    iVar8 = iVar8 + 1;
  }
  if (*(int *)(&DAT_00002250 + param_1) == 0) {
    if ((*(int *)(&DAT_0000460c + param_1) == 5) &&
       ((*(int *)(&DAT_00004628 + param_1) - 4U < 2 || (*(int *)(&DAT_00004628 + param_1) == 1)))) {
      uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar8 = FUN_MCARD__000f5f1c(uVar1,param_1 + 0x4668);
      if ((iVar8 != -1) || (*(int *)(&DAT_00004628 + param_1) != 5)) {
        uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
        iVar8 = FUN_MCARD__000f6550(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
        if (iVar8 == 0) {
          sprintf((char *)(param_1 + 8),DAT_MCARD__0010ed24,*(int *)(&DAT_00004688 + param_1) + 1);
          local_30 = *(undefined4 *)(param_1 + 0x148);
          local_2c = *(undefined4 *)(param_1 + 0x14c);
          uVar1 = *(undefined4 *)(&DAT_00002234 + param_1);
          FUN_MCARD__000f8b28(param_1,local_30,local_2c,(char *)(param_1 + 8),0,uVar1,uVar1,uVar1);
        }
        else {
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          uVar1 = FUN_MCARD__000f628c(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),
                                      *(undefined4 *)(&DAT_00004618 + param_1));
          uVar4 = *(undefined4 *)(&DAT_00002234 + param_1);
          FUN_MCARD__000fd000(param_1,uVar1,(3 - uVar7) * -0x19 + 0x154,
                              *(int *)(&DAT_00004618 + param_1) * 0x19 -
                              (*(int *)(&DAT_0000461c + param_1) + -0x98),0,0x1c,uVar4,uVar4,uVar4,0
                             );
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          uVar7 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),
                                      *(undefined4 *)(&DAT_00004618 + param_1),0);
          if (uVar7 < 0x10) {
            uVar1 = *(undefined4 *)(&DAT_00002234 + param_1);
            FUN_MCARD__000fe434(param_1,param_1 + uVar7 * 0xc + 0x4518,0xff,
                                *(int *)(&DAT_00004618 + param_1) * 0x19 -
                                (*(int *)(&DAT_0000461c + param_1) + -0x9e),uVar1,uVar1,uVar1,0,1);
          }
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          uVar7 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),
                                      *(undefined4 *)(&DAT_00004618 + param_1),1);
          if (uVar7 < 0x10) {
            uVar1 = *(undefined4 *)(&DAT_00002234 + param_1);
            FUN_MCARD__000fe434(param_1,param_1 + uVar7 * 0xc + 0x4518,0x11a,
                                *(int *)(&DAT_00004618 + param_1) * 0x19 -
                                (*(int *)(&DAT_0000461c + param_1) + -0x9e),uVar1,uVar1,uVar1,0,1);
          }
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          uVar7 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),
                                      *(undefined4 *)(&DAT_00004618 + param_1),2);
          if (uVar7 < 0x10) {
            uVar1 = *(undefined4 *)(&DAT_00002234 + param_1);
            FUN_MCARD__000fe434(param_1,param_1 + uVar7 * 0xc + 0x4518,0x135,
                                *(int *)(&DAT_00004618 + param_1) * 0x19 -
                                (*(int *)(&DAT_0000461c + param_1) + -0x9e),uVar1,uVar1,uVar1,0,1);
          }
        }
      }
    }
  }
  else {
    MoveImage(param_1 + 0x180,(int)*(short *)(param_1 + 0x148),(int)*(short *)(param_1 + 0x14a));
    DrawSync(0);
    if ((*(int *)(&DAT_00004628 + param_1) - 4U < 2) || (*(int *)(&DAT_00004628 + param_1) == 1)) {
      iVar8 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
      if (((*(int *)(&DAT_00004614 + param_1) == iVar8) &&
          ((*(int *)(&DAT_00004628 + param_1) == 5 && (*(int *)(&DAT_0000460c + param_1) == 4)))) &&
         ((iVar8 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar8 != 0 ||
          (iVar8 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),1), iVar8 != 0)))) {
        local_30 = *(undefined4 *)(param_1 + 0x148);
        local_2c = *(undefined4 *)(param_1 + 0x14c);
        FUN_MCARD__000f8b28(param_1,local_30,local_2c,DAT_MCARD__0010ed50,0,0x80,0x80,0x80);
      }
      else {
        uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
        iVar8 = FUN_MCARD__000f6550(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
        if (((iVar8 != 0) ||
            ((iVar8 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar8 == 0 &&
             (iVar8 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),1), iVar8 == 0)))
            ) && (*(int *)(&DAT_0000460c + param_1) - 4U < 2)) {
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar8 = FUN_MCARD__000f64f4(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
          iVar8 = iVar8 + -1;
          if (-2 < iVar8) {
            iVar2 = iVar8 * 0x19;
            do {
              if ((iVar2 - *(int *)(&DAT_0000461c + param_1)) + 0x2bU < 0x5f) {
                if (iVar8 == -1) {
                  uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                  iVar3 = FUN_MCARD__000f64f4(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
                  if (iVar3 < 2) {
                    FUN_MCARD__000fd000(param_1,*(int *)(&DAT_00004688 + param_1) + 1,0x109,
                                        -0x19 - (*(int *)(&DAT_0000461c + param_1) + -0x98),0,1000,
                                        0x80,0x80,0x80,0);
                  }
                  else {
                    memset(acStack104,0,0x32);
                    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                    uVar1 = FUN_MCARD__000f63ec(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
                    uVar4 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                    iVar3 = FUN_MCARD__000f64f4(uVar4,*(undefined4 *)(&DAT_00004614 + param_1));
                    uVar4 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                    iVar5 = FUN_MCARD__000f63ec(uVar4,*(undefined4 *)(&DAT_00004614 + param_1));
                    sprintf(acStack104,s__d__s___d__s_MCARD__000f309c,uVar1,DAT_MCARD__0010ed1c,
                            iVar3 - iVar5,DAT_MCARD__0010ed20);
                    FUN_MCARD__000fe834(param_1,acStack104,0x176,
                                        -0x19 - (*(int *)(&DAT_0000461c + param_1) + -0x98),0,1000,
                                        0x80,0x80,0x80,0);
                  }
                }
                else {
                  uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                  uVar1 = FUN_MCARD__000f628c(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8);
                  FUN_MCARD__000fd000(param_1,uVar1,(3 - uVar7) * -0x19 + 0x154,
                                      iVar2 - (*(int *)(&DAT_0000461c + param_1) + -0x98),0,0x1c,
                                      0x80,0x80,0x80,0);
                  uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                  uVar6 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8,0
                                             );
                  if (uVar6 < 0x10) {
                    FUN_MCARD__000fe434(param_1,param_1 + uVar6 * 0xc + 0x4518,0xff,
                                        iVar2 - (*(int *)(&DAT_0000461c + param_1) + -0x9e),0x50,
                                        0x50,0x50,0,1);
                  }
                  uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                  uVar6 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8,1
                                             );
                  if (uVar6 < 0x10) {
                    FUN_MCARD__000fe434(param_1,param_1 + uVar6 * 0xc + 0x4518,0x11a,
                                        iVar2 - (*(int *)(&DAT_0000461c + param_1) + -0x9e),0x50,
                                        0x50,0x50,0,1);
                  }
                  uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
                  uVar6 = FUN_MCARD__000f6448(uVar1,*(undefined4 *)(&DAT_00004614 + param_1),iVar8,2
                                             );
                  if (uVar6 < 0x10) {
                    FUN_MCARD__000fe434(param_1,param_1 + uVar6 * 0xc + 0x4518,0x135,
                                        iVar2 - (*(int *)(&DAT_0000461c + param_1) + -0x9e),0x50,
                                        0x50,0x50,0,1);
                  }
                }
              }
              iVar2 = iVar2 + -0x19;
              iVar8 = iVar8 + -1;
            } while (-2 < iVar8);
          }
        }
      }
    }
    if (*(int *)(&DAT_0000461c + param_1) == *(int *)(&DAT_00004618 + param_1) * 0x19) {
      *(undefined4 *)(&DAT_00002250 + param_1) = 0;
    }
    else {
      if (*(int *)(&DAT_00004620 + param_1) != 0) {
        *(int *)(&DAT_0000461c + param_1) =
             *(int *)(&DAT_0000461c + param_1) + *(int *)(&DAT_00004620 + param_1);
        *(undefined4 *)(&DAT_00004620 + param_1) = 0;
      }
      *(int *)(&DAT_0000461c + param_1) =
           *(int *)(&DAT_0000461c + param_1) + *(int *)(&DAT_00004624 + param_1);
    }
  }
  FUN_MCARD__0010eb20(DAT_MCARD__0010ec74,param_1 + 0x108);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ write_mess_in_box__7DISPMANG4RECTPciiii(struct DISPMAN *this /*$s5*/, struct RECT box /*stack 4*/, char *text /*$fp*/, int font /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 1031, offset 0x000f8b28
	/* begin block 1 */
		// Start line: 1032
		// Start offset: 0x000F8B28
		// Variables:
	// 		int n; // $s1
	// 		int textY; // $s2
	// 		int messCount; // $s6
	// 		int lineCount; // $s0
	/* end block 1 */
	// End offset: 0x000F8D24
	// End Line: 1056

	/* begin block 2 */
		// Start line: 2627
	/* end block 2 */
	// End Line: 2628

	/* begin block 3 */
		// Start line: 2628
	/* end block 3 */
	// End Line: 2629

void FUN_MCARD__000f8b28(int param_1,undefined4 param_2,int param_3,char *param_4,int param_5,
                        undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short local_res4;
  short sStackX6;
  short local_res8;
  
  iVar3 = 0;
  iVar4 = 0;
  sVar1 = strlen(param_4);
  do {
    local_res8 = (short)param_3;
    iVar2 = FUN_MCARD__000fce00(param_1,param_4 + iVar3,param_5,(int)local_res8);
    iVar3 = iVar3 + iVar2;
    iVar4 = iVar4 + ((int)*(short *)(&DAT_0000231e + param_1 + param_5 * 0x4c0) * 0xb) / 10;
  } while (iVar3 < (int)sVar1);
  iVar3 = 0;
  sStackX6 = (short)((uint)param_2 >> 0x10);
  iVar4 = ((int)sStackX6 + ((param_3 >> 0x10) - (param_3 >> 0x1f) >> 1)) - iVar4 / 2;
  do {
    iVar2 = FUN_MCARD__000fce00(param_1,param_4 + iVar3,param_5,(int)local_res8);
    local_res4 = (short)param_2;
    FUN_MCARD__000fe834(param_1,param_4 + iVar3,
                        (int)local_res4 +
                        (((param_3 << 0x10) >> 0x10) - ((param_3 << 0x10) >> 0x1f) >> 1),iVar4,
                        param_5,iVar2,param_6,param_7,param_8,0);
    iVar3 = iVar3 + iVar2;
    iVar4 = iVar4 + ((int)*(short *)(&DAT_0000231e + param_1 + param_5 * 0x4c0) * 0xb) / 10;
  } while (iVar3 < (int)sVar1);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawBlockName__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 1060, offset 0x000f8d24
	/* begin block 1 */
		// Start line: 1061
		// Start offset: 0x000F8D24
	/* end block 1 */
	// End offset: 0x000F8ED4
	// End Line: 1100

	/* begin block 2 */
		// Start line: 2709
	/* end block 2 */
	// End Line: 2710

void FUN_MCARD__000f8d24(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(&DAT_00002254 + param_1) == 0) {
    return;
  }
  MoveImage(param_1 + 0x188,(int)*(short *)(param_1 + 0x150),(int)*(short *)(param_1 + 0x152));
  DrawSync(0);
  iVar2 = *(int *)(&DAT_0000460c + param_1);
  uVar1 = DAT_MCARD__0010ed8c;
  if (iVar2 != 2) {
    if (2 < iVar2) {
      if (iVar2 == 4) {
        if (-1 < *(int *)(&DAT_00002258 + param_1)) {
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          uVar1 = FUN_MCARD__000f5ea0(uVar1,*(undefined4 *)(&DAT_00002258 + param_1));
          FUN_MCARD__000fe1b0(param_1,uVar1,0x100,0xd1,0x40,0x80,0x80,0x80);
          *(undefined4 *)(&DAT_00002254 + param_1) = 0;
          return;
        }
        uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
        uVar1 = FUN_MCARD__000f5ea0(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
        FUN_MCARD__000fe1b0(param_1,uVar1,0x100,0xd1,0x40,0x80,0x80,0x80);
        *(undefined4 *)(&DAT_00002254 + param_1) = 0;
        return;
      }
      if (iVar2 != 5) {
        return;
      }
      FUN_MCARD__000fe834(param_1,DAT_MCARD__0010ed90,0x100,0xcf,0,1000,0x80,0x80,0x80,0);
      return;
    }
    uVar1 = DAT_MCARD__0010ed88;
    if (iVar2 != 1) {
      return;
    }
  }
  FUN_MCARD__000fe834(param_1,uVar1,0x100,0xcf,0,1000,0x80,0x80,0x80,0);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawEnterName__7DISPMANPc(struct DISPMAN *this /*$s0*/, char *ascii /*$a3*/)
 // line 1105, offset 0x000fdbec
	/* begin block 1 */
		// Start line: 1106
		// Start offset: 0x000FDBEC
		// Variables:
	// 		char message[64]; // stack offset -72
	/* end block 1 */
	// End offset: 0x000FDC6C
	// End Line: 1111

	/* begin block 2 */
		// Start line: 6763
	/* end block 2 */
	// End Line: 6764

void FUN_MCARD__000fdbec(int param_1,undefined4 param_2)

{
  char acStack72 [64];
  
  sprintf(acStack72,s__s__s_MCARD__000f30ac,DAT_MCARD__0010ee00,param_2);
  FUN_MCARD__000fd000(param_1,acStack72,0x18,0xd1,0,1000,0x80,0x80,0x80,0);
  FUN_MCARD__000fe598(param_1,param_1 + 0x188,param_1 + 0x150);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMenuOption__7DISPMANi(struct DISPMAN *this /*$s0*/, int menuOption /*$s1*/)
 // line 1114, offset 0x000fdc6c
	/* begin block 1 */
		// Start line: 1115
		// Start offset: 0x000FDC6C
	/* end block 1 */
	// End offset: 0x000FDCA8
	// End Line: 1121

	/* begin block 2 */
		// Start line: 6787
	/* end block 2 */
	// End Line: 6788

void FUN_MCARD__000fdc6c(int param_1,uint param_2)

{
  if (*(int *)(&DAT_00004634 + param_1 + (param_2 & 3) * 4) != 0) {
    FUN_MCARD__000fdcc4(param_1,2);
    *(uint *)(&DAT_00004610 + param_1) = param_2 & 3;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetActiveFunction__7DISPMANi(struct DISPMAN *this /*$a0*/, int menuOption /*$a1*/)
 // line 1125, offset 0x000fdcbc
	/* begin block 1 */
		// Start line: 1126
		// Start offset: 0x000FDCBC
	/* end block 1 */
	// End offset: 0x000FDCC4
	// End Line: 1127

	/* begin block 2 */
		// Start line: 6812
	/* end block 2 */
	// End Line: 6813

	/* begin block 3 */
		// Start line: 6813
	/* end block 3 */
	// End Line: 6814

void FUN_MCARD__000fdcbc(int param_1,undefined4 param_2)

{
  *(undefined4 *)(&DAT_00004628 + param_1) = param_2;
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MoveActiveAreaTo__7DISPMANi(struct DISPMAN *this /*$s0*/, int area /*$s1*/)
 // line 1131, offset 0x000fdcc4
	/* begin block 1 */
		// Start line: 1132
		// Start offset: 0x000FDCC4
	/* end block 1 */
	// End offset: 0x000FDD0C
	// End Line: 1136

	/* begin block 2 */
		// Start line: 6824
	/* end block 2 */
	// End Line: 6825

void FUN_MCARD__000fdcc4(int param_1,undefined4 param_2)

{
  FUN_MCARD__000fe040(param_1,*(undefined4 *)(&DAT_0000460c + param_1));
  FUN_MCARD__000fe040(param_1,param_2);
  *(undefined4 *)(&DAT_0000460c + param_1) = param_2;
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SelectNewBlock__7DISPMANi(struct DISPMAN *this /*$s0*/, int newBlock /*$a1*/)
 // line 1249, offset 0x000fdd0c
	/* begin block 1 */
		// Start line: 1250
		// Start offset: 0x000FDD0C
	/* end block 1 */
	// End offset: 0x000FDDC0
	// End Line: 1265

	/* begin block 2 */
		// Start line: 7060
	/* end block 2 */
	// End Line: 7061

	/* begin block 3 */
		// Start line: 7061
	/* end block 3 */
	// End Line: 7062

/* WARNING: Control flow encountered bad instruction data */

void SelectNewBlock__7DISPMANi(DISPMAN *this,int newBlock)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// decompiled code
// original method signature: 
// void /*$ra*/ ActiveAreaLeft__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 1327, offset 0x000f8ee4
	/* begin block 1 */
		// Start line: 1328
		// Start offset: 0x000F8EE4
		// Variables:
	// 		int start; // $s1
	/* end block 1 */
	// End offset: 0x000F9018
	// End Line: 1370

	/* begin block 2 */
		// Start line: 3243
	/* end block 2 */
	// End Line: 3244

void FUN_MCARD__000f8ee4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(&DAT_0000460c + param_1);
  if (iVar3 != 2) {
    if (iVar3 < 3) {
      if (((iVar3 == 1) &&
          (iVar3 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),1), iVar3 != 0)) &&
         (iVar3 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar3 != 0)) {
        FUN_MCARD__001003e4(*(undefined4 *)(&DAT_000045e4 + param_1));
        *(undefined4 *)(&DAT_00004614 + param_1) = 0;
        FUN_MCARD__000fe040(param_1,1);
        FUN_MCARD__000fe040(param_1,4);
        FUN_MCARD__000fe040(param_1,5);
        libcman_SelectSound();
      }
    }
    else {
      if (iVar3 == 4) {
        iVar3 = *(int *)(&DAT_00004614 + param_1);
        do {
          iVar1 = *(int *)(&DAT_00004614 + param_1);
          if (iVar1 < 1) goto code_r0x000f8fe8;
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar1 = *(int *)(&DAT_00004614 + param_1);
          *(int *)(&DAT_00004614 + param_1) = iVar1 + -1;
          iVar1 = FUN_MCARD__000f5dc8(uVar2,iVar1 + -1);
        } while (iVar1 == 0);
        iVar1 = *(int *)(&DAT_00004614 + param_1);
code_r0x000f8fe8:
        if (iVar3 != iVar1) {
          FUN_MCARD__000fe040(param_1,4);
          FUN_MCARD__000fe040(param_1,5);
          *(undefined4 *)(&DAT_00004618 + param_1) = 0;
          *(undefined4 *)(&DAT_0000461c + param_1) = 0;
          *(undefined4 *)(&DAT_00004624 + param_1) = 0;
          *(undefined4 *)(&DAT_00004620 + param_1) = 0;
          libcman_SelectSound();
        }
      }
    }
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ActiveAreaRight__7DISPMAN(struct DISPMAN *this /*$s1*/)
 // line 1375, offset 0x000f902c
	/* begin block 1 */
		// Start line: 1376
		// Start offset: 0x000F902C
		// Variables:
	// 		int start; // $s2
	/* end block 1 */
	// End offset: 0x000F9258
	// End Line: 1432

	/* begin block 2 */
		// Start line: 3339
	/* end block 2 */
	// End Line: 3340

void FUN_MCARD__000f902c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(&DAT_0000460c + param_1);
  if (iVar3 == 2) {
    return;
  }
  if (iVar3 < 3) {
    if (iVar3 != 1) {
      return;
    }
    iVar3 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),0);
    if (iVar3 == 0) {
      return;
    }
    iVar3 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),1);
    if (iVar3 == 0) {
      return;
    }
    FUN_MCARD__001003e4(*(undefined4 *)(&DAT_000045e4 + param_1));
    *(undefined4 *)(&DAT_00004614 + param_1) = 0;
    FUN_MCARD__000fe040(param_1,1);
    FUN_MCARD__000fe040(param_1,4);
    FUN_MCARD__000fe040(param_1,5);
    libcman_SelectSound();
    return;
  }
  if (iVar3 != 4) {
    return;
  }
  iVar4 = *(int *)(&DAT_00004614 + param_1);
  iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
  uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
  iVar2 = FUN_MCARD__000f5dc8(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
  if (*(int *)(&DAT_00004614 + param_1) < iVar3 - iVar2) {
    do {
      iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
      if (iVar3 + -1 <= *(int *)(&DAT_00004614 + param_1)) break;
      uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar3 = *(int *)(&DAT_00004614 + param_1);
      *(int *)(&DAT_00004614 + param_1) = iVar3 + 1;
      iVar3 = FUN_MCARD__000f5dc8(uVar1,iVar3 + 1);
    } while (iVar3 == 0);
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar3 = FUN_MCARD__000f5dc8(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
    if (iVar3 == 0) {
      *(int *)(&DAT_00004614 + param_1) = iVar4;
    }
  }
  else {
    if ((DAT_MCARD__0010ee08 & 0x40) == 0) {
      uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar3 = FUN_MCARD__000f5f1c(uVar1,param_1 + 0x4668);
      if (iVar3 != -1) goto LAB_MCARD__000f9220;
    }
    if ((*(int *)(&DAT_00004628 + param_1) == 5) &&
       (iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1)),
       iVar3 <= (int)(0xf - (uint)**(byte **)(&DAT_00004688 + param_1)))) {
      uVar1 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
      *(undefined4 *)(&DAT_00004614 + param_1) = uVar1;
    }
  }
LAB_MCARD__000f9220:
  if (iVar4 != *(int *)(&DAT_00004614 + param_1)) {
    FUN_MCARD__000fe040(param_1,5);
    FUN_MCARD__000fe040(param_1,4);
    *(undefined4 *)(&DAT_0000461c + param_1) = 0;
    *(undefined4 *)(&DAT_00004618 + param_1) = 0;
    *(undefined4 *)(&DAT_00004624 + param_1) = 0;
    *(undefined4 *)(&DAT_00004620 + param_1) = 0;
    libcman_SelectSound();
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ActiveAreaUp__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 1437, offset 0x000f9270
	/* begin block 1 */
		// Start line: 1438
		// Start offset: 0x000F9270
	/* end block 1 */
	// End offset: 0x000F940C
	// End Line: 1488

	/* begin block 2 */
		// Start line: 3465
	/* end block 2 */
	// End Line: 3466

void FUN_MCARD__000f9270(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(&DAT_0000460c + param_1);
  if (iVar3 == 2) {
    do {
      uVar2 = *(int *)(&DAT_00004610 + param_1) - 1U & 3;
      *(uint *)(&DAT_00004610 + param_1) = uVar2;
    } while (*(int *)(&DAT_00004634 + uVar2 * 4 + param_1) == 0);
    libcman_SelectSound();
    FUN_MCARD__000fe040(param_1,2);
  }
  else {
    if (2 < iVar3) {
      if (iVar3 == 4) {
        if (4 < *(int *)(&DAT_00004614 + param_1)) {
          *(int *)(&DAT_00004614 + param_1) = *(int *)(&DAT_00004614 + param_1) + -4;
          do {
            if (*(int *)(&DAT_00004614 + param_1) < 1) break;
            uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
            iVar3 = *(int *)(&DAT_00004614 + param_1);
            *(int *)(&DAT_00004614 + param_1) = iVar3 + -1;
            iVar3 = FUN_MCARD__000f5dc8(uVar1,iVar3 + -1);
          } while (iVar3 == 0);
          FUN_MCARD__000fe040(param_1,4);
          FUN_MCARD__000fe040(param_1,5);
          *(undefined4 *)(&DAT_0000461c + param_1) = 0;
          *(undefined4 *)(&DAT_00004618 + param_1) = 0;
          *(undefined4 *)(&DAT_00004624 + param_1) = 0;
          *(undefined4 *)(&DAT_00004620 + param_1) = 0;
          libcman_SelectSound();
        }
      }
      else {
        if (iVar3 == 5) {
          uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar3 = FUN_MCARD__000f6550(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
          if ((iVar3 != 0) && (0 < *(int *)(&DAT_00004618 + param_1))) {
            iVar4 = *(int *)(&DAT_00004618 + param_1) + -1;
            iVar3 = iVar4 * 0x19 - *(int *)(&DAT_0000461c + param_1);
            *(int *)(&DAT_00004618 + param_1) = iVar4;
            *(int *)(&DAT_00004624 + param_1) = iVar3 / 3;
            *(int *)(&DAT_00004620 + param_1) = iVar3 % 3;
            FUN_MCARD__000fe040(param_1,5);
            libcman_SelectSound();
          }
        }
      }
    }
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ActiveAreaDown__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 1493, offset 0x000f941c
	/* begin block 1 */
		// Start line: 1494
		// Start offset: 0x000F941C
		// Variables:
	// 		int start; // $s1
	/* end block 1 */
	// End offset: 0x000F96DC
	// End Line: 1564

	/* begin block 2 */
		// Start line: 3584
	/* end block 2 */
	// End Line: 3585

void FUN_MCARD__000f941c(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(&DAT_0000460c + param_1);
  if (iVar3 == 2) {
    do {
      uVar2 = *(int *)(&DAT_00004610 + param_1) + 1U & 3;
      *(uint *)(&DAT_00004610 + param_1) = uVar2;
    } while (*(int *)(&DAT_00004634 + uVar2 * 4 + param_1) == 0);
    FUN_MCARD__000fe040(param_1,2);
    libcman_SelectSound();
    return;
  }
  if (iVar3 < 3) {
    return;
  }
  if (iVar3 != 4) {
    if (iVar3 != 5) {
      return;
    }
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar3 = FUN_MCARD__000f6550(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
    if (iVar3 == 0) {
      return;
    }
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar3 = FUN_MCARD__000f64f4(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
    if (iVar3 + -1 <= *(int *)(&DAT_00004618 + param_1)) {
      return;
    }
    libcman_SelectSound();
    iVar3 = (*(int *)(&DAT_00004618 + param_1) + 1) * 0x19 - *(int *)(&DAT_0000461c + param_1);
    *(int *)(&DAT_00004618 + param_1) = *(int *)(&DAT_00004618 + param_1) + 1;
    *(int *)(&DAT_00004624 + param_1) = iVar3 / 3;
    *(int *)(&DAT_00004620 + param_1) = iVar3 % 3;
    FUN_MCARD__000fe040(param_1,5);
    return;
  }
  iVar4 = *(int *)(&DAT_00004614 + param_1);
  iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
  if (*(int *)(&DAT_00004614 + param_1) < iVar3 + -5) {
    *(int *)(&DAT_00004614 + param_1) = *(int *)(&DAT_00004614 + param_1) + 6;
    do {
      if (*(int *)(&DAT_00004614 + param_1) < 1) break;
      uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar3 = *(int *)(&DAT_00004614 + param_1);
      *(int *)(&DAT_00004614 + param_1) = iVar3 + -1;
      iVar3 = FUN_MCARD__000f5dc8(uVar1,iVar3 + -1);
    } while (iVar3 == 0);
    uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar3 = FUN_MCARD__000f5dc8(uVar1,*(undefined4 *)(&DAT_00004614 + param_1));
    if (iVar3 == 0) {
      *(int *)(&DAT_00004614 + param_1) = iVar4;
    }
  }
  else {
    if ((DAT_MCARD__0010ee08 & 0x40) == 0) {
      uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar3 = FUN_MCARD__000f5f1c(uVar1,param_1 + 0x4668);
      if (iVar3 != -1) goto LAB_MCARD__000f95a4;
    }
    if (((*(int *)(&DAT_00004628 + param_1) == 5) &&
        (iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1)),
        iVar3 <= (int)(0xf - (uint)**(byte **)(&DAT_00004688 + param_1)))) &&
       (iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1)),
       *(int *)(&DAT_00004614 + param_1) <=
       (int)(iVar3 + (uint)**(byte **)(&DAT_00004688 + param_1) + -5))) {
      uVar1 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
      *(undefined4 *)(&DAT_00004614 + param_1) = uVar1;
    }
  }
LAB_MCARD__000f95a4:
  if (iVar4 != *(int *)(&DAT_00004614 + param_1)) {
    FUN_MCARD__000fe040(param_1,5);
    FUN_MCARD__000fe040(param_1,4);
    *(undefined4 *)(&DAT_00004618 + param_1) = 0;
    *(undefined4 *)(&DAT_00004624 + param_1) = 0;
    *(undefined4 *)(&DAT_00004620 + param_1) = 0;
    libcman_SelectSound();
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ActiveAreaSelect__7DISPMANii(struct DISPMAN *this /*$s1*/, int x /*$s2*/, int y /*$s0*/)
 // line 1568, offset 0x000f96f0
	/* begin block 1 */
		// Start line: 1569
		// Start offset: 0x000F96F0
		// Variables:
	// 		int selected; // $s0
	// 		int newArea; // $a0
	/* end block 1 */
	// End offset: 0x000F9BAC
	// End Line: 1706

	/* begin block 2 */
		// Start line: 3745
	/* end block 2 */
	// End Line: 3746

undefined4 FUN_MCARD__000f96f0(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar1 = FUN_MCARD__000fddd0();
  if (((iVar1 == 0) || (iVar1 == 3)) || (iVar1 == 6)) {
    return 0;
  }
  if ((iVar1 == 5) && ((DAT_MCARD__0010ee08 & 0x200) != 0)) {
    return 0;
  }
  if (iVar1 == 4) {
    if (((*(int *)(&DAT_0000462c + param_1) == 5) && (*(int *)(&DAT_00004628 + param_1) == 1)) &&
       (*(int *)(&DAT_00004638 + param_1) == 0)) {
      return 0;
    }
    if (((*(int *)(&DAT_0000462c + param_1) == 4) && (*(int *)(&DAT_00004628 + param_1) == 4)) &&
       (*(int *)(&DAT_00004634 + param_1) == 0)) {
      return 0;
    }
  }
  FUN_MCARD__000fe040(param_1,*(undefined4 *)(&DAT_0000460c + param_1));
  uVar2 = FUN_MCARD__000fddd0(param_1,param_2,param_3);
  *(undefined4 *)(&DAT_0000460c + param_1) = uVar2;
  FUN_MCARD__000fe040(param_1,uVar2);
  iVar1 = *(int *)(&DAT_0000460c + param_1);
  if (iVar1 == 2) {
    iVar1 = (param_3 + -0x11) / 0x17;
    if (3 < iVar1) {
      iVar1 = 3;
    }
    iVar3 = iVar1 << 2;
    if (iVar1 < 0) {
      iVar1 = 0;
      iVar3 = 0;
    }
    puVar4 = &DAT_00004634 + param_1;
    if (*(int *)(puVar4 + iVar3) == 0) {
      iVar3 = iVar1 + 1;
      if (((iVar1 < 3) && (*(int *)(puVar4 + iVar3 * 4) != 0)) ||
         ((iVar3 = iVar1 + 2, iVar1 < 2 && (*(int *)(puVar4 + iVar3 * 4) != 0)))) {
        *(int *)(&DAT_00004610 + param_1) = iVar3;
      }
    }
    else {
      *(int *)(&DAT_00004610 + param_1) = iVar1;
    }
  }
  else {
    if (iVar1 < 3) {
      if (iVar1 != 1) {
        return 0;
      }
      if (((0x75 < param_2) &&
          (iVar1 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar1 != 0)) &&
         (iVar1 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),1), iVar1 != 0)) {
        FUN_MCARD__001003e4(*(undefined4 *)(&DAT_000045e4 + param_1));
        *(undefined4 *)(&DAT_00004614 + param_1) = 0;
        FUN_MCARD__000fe040(param_1,1);
        FUN_MCARD__000fe040(param_1,4);
        FUN_MCARD__000fe040(param_1,5);
      }
      if (((param_2 < 0x75) &&
          (iVar1 = FUN_MCARD__00100244(*(undefined4 *)(&DAT_000045e4 + param_1),1), iVar1 != 0)) &&
         (iVar1 = FUN_MCARD__001003b0(*(undefined4 *)(&DAT_000045e4 + param_1),0), iVar1 != 0)) {
        FUN_MCARD__001003e4(*(undefined4 *)(&DAT_000045e4 + param_1));
        *(undefined4 *)(&DAT_00004614 + param_1) = 0;
        FUN_MCARD__000fe040(param_1,1);
        FUN_MCARD__000fe040(param_1,4);
        FUN_MCARD__000fe040(param_1,5);
      }
    }
    else {
      if (iVar1 != 4) {
        if (iVar1 != 5) {
          return 0;
        }
        if (param_3 < 0x94) {
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar1 = FUN_MCARD__000f6550(uVar2,*(undefined4 *)(&DAT_00004614 + param_1));
          if (iVar1 == 0) {
            return 0;
          }
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar1 = FUN_MCARD__000f6550(uVar2,*(undefined4 *)(&DAT_00004614 + param_1));
          if (iVar1 == 0) {
            return 0;
          }
          if (*(int *)(&DAT_00004618 + param_1) < 1) {
            return 0;
          }
          iVar1 = *(int *)(&DAT_00004618 + param_1) + -1;
        }
        else {
          if (param_3 < 0xb5) goto LAB_MCARD__000f9b80;
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar1 = FUN_MCARD__000f6550(uVar2,*(undefined4 *)(&DAT_00004614 + param_1));
          if (iVar1 == 0) {
            return 0;
          }
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar1 = FUN_MCARD__000f64f4(uVar2,*(undefined4 *)(&DAT_00004614 + param_1));
          if (iVar1 + -1 <= *(int *)(&DAT_00004618 + param_1)) {
            return 0;
          }
          iVar1 = *(int *)(&DAT_00004618 + param_1) + 1;
        }
        iVar3 = iVar1 * 0x19 - *(int *)(&DAT_0000461c + param_1);
        *(int *)(&DAT_00004618 + param_1) = iVar1;
        *(int *)(&DAT_00004624 + param_1) = iVar3 / 3;
        *(int *)(&DAT_00004620 + param_1) = iVar3 % 3;
        FUN_MCARD__000fe040(param_1,5);
        return 0;
      }
      iVar3 = ((param_3 + -0x7d) / 0x1a) * 5 + (param_2 + 0x1a) / 0x2a;
      iVar1 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
      if (iVar3 < iVar1 + 1) {
        *(int *)(&DAT_00004614 + param_1) = iVar3;
        do {
          if (*(int *)(&DAT_00004614 + param_1) < 1) break;
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar1 = *(int *)(&DAT_00004614 + param_1);
          *(int *)(&DAT_00004614 + param_1) = iVar1 + -1;
          iVar1 = FUN_MCARD__000f5dc8(uVar2,iVar1 + -1);
        } while (iVar1 == 0);
      }
      FUN_MCARD__000fe040(param_1,5);
    }
  }
LAB_MCARD__000f9b80:
  uVar2 = FUN_MCARD__000f9bac(param_1);
  return uVar2;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetArea__7DISPMANii(struct DISPMAN *this /*$a0*/, int x /*$a1*/, int y /*$a2*/)
 // line 1710, offset 0x000fddd0
	/* begin block 1 */
		// Start line: 1711
		// Start offset: 0x000FDDD0
		// Variables:
	// 		int n; // $a3
	/* end block 1 */
	// End offset: 0x000FDE48
	// End Line: 1725

	/* begin block 2 */
		// Start line: 7987
	/* end block 2 */
	// End Line: 7988

	/* begin block 3 */
		// Start line: 7990
	/* end block 3 */
	// End Line: 7991

int FUN_MCARD__000fddd0(int param_1,int param_2,int param_3)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = (short *)(param_1 + 0x126);
  while ((((param_2 <= (int)psVar1[-3] || ((int)psVar1[-3] + (int)psVar1[-1] <= param_2)) ||
          (param_3 <= (int)psVar1[-2])) || ((int)psVar1[-2] + (int)*psVar1 <= param_3))) {
    iVar2 = iVar2 + 1;
    psVar1 = psVar1 + 4;
    if (6 < iVar2) {
      return 0;
    }
  }
  return iVar2;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ActiveAreaConfirm__7DISPMAN(struct DISPMAN *this /*$s1*/)
 // line 1728, offset 0x000f9bac
	/* begin block 1 */
		// Start line: 1729
		// Start offset: 0x000F9BAC
	/* end block 1 */
	// End offset: 0x000F9FAC
	// End Line: 1958

	/* begin block 2 */
		// Start line: 4074
	/* end block 2 */
	// End Line: 4075

undefined4 FUN_MCARD__000f9bac(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(&DAT_0000460c + param_1);
  if (iVar3 != 2) {
    if (iVar3 < 3) {
      if (iVar3 == 1) {
        *(undefined4 *)(&DAT_0000460c + param_1) = 2;
        FUN_MCARD__000fe040(param_1,2);
        FUN_MCARD__000fe040(param_1,1);
        libcman_ConfirmSound();
        return 0;
      }
      return 0;
    }
    if (iVar3 != 4) {
      if (iVar3 != 5) {
        return 0;
      }
      iVar3 = *(int *)(&DAT_00004628 + param_1);
      if (iVar3 == 4) {
        uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
        iVar3 = FUN_MCARD__000f633c(uVar2,*(undefined4 *)(&DAT_00004614 + param_1),
                                    *(undefined4 *)(&DAT_00004618 + param_1));
        if (iVar3 != 0) {
          libcman_ConfirmSound();
          return 7;
        }
        return 0;
      }
      if (iVar3 < 5) {
        return 0;
      }
      if (iVar3 == 5) {
        return 6;
      }
      return 0;
    }
    iVar3 = *(int *)(&DAT_00004628 + param_1);
    if (iVar3 == 2) {
      return 0;
    }
    if (iVar3 < 3) {
      if (iVar3 == 1) {
        libcman_ConfirmSound();
        return 1;
      }
      return 0;
    }
    if (5 < iVar3) {
      return 0;
    }
    if (iVar3 < 4) {
      return 0;
    }
    uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
    iVar3 = FUN_MCARD__000f6550(uVar2,*(undefined4 *)(&DAT_00004614 + param_1));
    if (iVar3 != 0) {
      libcman_ConfirmSound();
      uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar3 = FUN_MCARD__000f64f4(uVar2,*(undefined4 *)(&DAT_00004614 + param_1));
      if (1 < iVar3) {
        FUN_MCARD__000fe040(param_1,4);
        FUN_MCARD__000fe040(param_1,5);
        *(undefined4 *)(&DAT_0000460c + param_1) = 5;
        return 0;
      }
      if (*(int *)(&DAT_00004628 + param_1) != 5) {
        return 7;
      }
      return 6;
    }
    iVar3 = FUN_MCARD__001002a4(*(undefined4 *)(&DAT_000045e4 + param_1));
    if ((*(int *)(&DAT_00004614 + param_1) != iVar3) || (*(int *)(&DAT_00004628 + param_1) != 5)) {
      libcman_ErrorSound();
      return 0;
    }
LAB_MCARD__000f9f5c:
    libcman_ConfirmSound();
    return 5;
  }
  iVar3 = *(int *)(&DAT_00004610 + param_1);
  if (iVar3 == 1) {
    *(undefined4 *)(&DAT_00004628 + param_1) = 1;
    *(undefined4 *)(&DAT_0000460c + param_1) = 4;
    FUN_MCARD__000fe040(param_1,2);
    FUN_MCARD__000fe040(param_1,4);
    FUN_MCARD__000fe040(param_1,5);
    *(undefined4 *)(&DAT_00004614 + param_1) = 0;
    libcman_ConfirmSound();
  }
  else {
    if (iVar3 < 2) {
      if (iVar3 == 0) {
        *(undefined4 *)(&DAT_00004628 + param_1) = *(undefined4 *)(&DAT_0000462c + param_1);
        FUN_MCARD__000fe040(param_1,0);
        if (*(int *)(&DAT_00004628 + param_1) == 4) {
          libcman_ConfirmSound();
          *(undefined4 *)(&DAT_00004614 + param_1) = 0;
          *(undefined4 *)(&DAT_0000460c + param_1) = 4;
        }
        else {
          if (*(int *)(&DAT_00004628 + param_1) != 5) goto LAB_MCARD__000f9f7c;
          uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
          iVar3 = FUN_MCARD__000f5fbc(uVar2,param_1 + 0x4668);
          if (iVar3 < 1) {
            bVar1 = **(byte **)(&DAT_00004688 + param_1);
            uVar2 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
            iVar3 = FUN_MCARD__000f5e84(uVar2);
            if (0xf - iVar3 < (int)(uint)bVar1) {
              libcman_ErrorSound();
              return 5;
            }
            libcman_ConfirmSound();
            *(undefined4 *)(&DAT_0000460c + param_1) = 4;
            *(undefined4 *)(&DAT_00004614 + param_1) = 0;
          }
          else {
            libcman_ConfirmSound();
            *(undefined4 *)(&DAT_0000460c + param_1) = 4;
            *(undefined4 *)(&DAT_00004614 + param_1) = 0;
          }
        }
        FUN_MCARD__000fe040(param_1,2);
        FUN_MCARD__000fe040(param_1,5);
        FUN_MCARD__000fe040(param_1,4);
      }
    }
    else {
      if (iVar3 == 2) {
        *(undefined4 *)(&DAT_0000460c + param_1) = 5;
        *(undefined4 *)(&DAT_00004628 + param_1) = *(undefined4 *)(&DAT_0000462c + param_1);
        FUN_MCARD__000fe040(param_1,2);
        FUN_MCARD__000fe040(param_1,0);
        FUN_MCARD__000fe040(param_1,5);
        goto LAB_MCARD__000f9f5c;
      }
      if (iVar3 == 3) {
        libcman_ConfirmSound();
        return 0xb;
      }
    }
  }
LAB_MCARD__000f9f7c:
  FUN_MCARD__000fe040(param_1,0);
  FUN_MCARD__000fe040(param_1,5);
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ActiveAreaCancel__7DISPMAN(struct DISPMAN *this /*$s0*/)
 // line 1962, offset 0x000fde50
	/* begin block 1 */
		// Start line: 1963
		// Start offset: 0x000FDE50
	/* end block 1 */
	// End offset: 0x000FDF58
	// End Line: 2015

	/* begin block 2 */
		// Start line: 8491
	/* end block 2 */
	// End Line: 8492

undefined4 FUN_MCARD__000fde50(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(&DAT_0000460c + param_1);
  if (iVar2 == 4) {
    *(undefined4 *)(&DAT_0000460c + param_1) = 2;
    FUN_MCARD__000fe040(param_1,0);
    FUN_MCARD__000fe040(param_1,2);
    FUN_MCARD__000fe040(param_1,4);
    FUN_MCARD__000fe040(param_1,5);
    *(undefined4 *)(&DAT_00004614 + param_1) = 0;
    libcman_CancelSound();
  }
  else {
    if ((4 < iVar2) && (iVar2 == 5)) {
      uVar1 = FUN_MCARD__0010031c(*(undefined4 *)(&DAT_000045e4 + param_1));
      iVar2 = FUN_MCARD__000f5fbc(uVar1,param_1 + 0x4668);
      if (iVar2 < 2) {
        *(undefined4 *)(&DAT_0000460c + param_1) = 2;
        FUN_MCARD__000fe040(param_1,2);
        FUN_MCARD__000fe040(param_1,5);
      }
      else {
        *(undefined4 *)(&DAT_0000460c + param_1) = 4;
        FUN_MCARD__000fe040(param_1,4);
        FUN_MCARD__000fe040(param_1,5);
      }
      libcman_CancelSound();
    }
  }
  return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddingBlock__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
 // line 2028, offset 0x000fdf58
	/* begin block 1 */
		// Start line: 2029
		// Start offset: 0x000FDF58
	/* end block 1 */
	// End offset: 0x000FDF60
	// End Line: 2029

	/* begin block 2 */
		// Start line: 8624
	/* end block 2 */
	// End Line: 8625

/* WARNING: Control flow encountered bad instruction data */

void AddingBlock__7DISPMANi(DISPMAN *this,int n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// decompiled code
// original method signature: 
// void /*$ra*/ DeletingCurrBlock__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
 // line 2030, offset 0x000fdf60
	/* begin block 1 */
		// Start line: 2031
		// Start offset: 0x000FDF60
	/* end block 1 */
	// End offset: 0x000FDF68
	// End Line: 2031

	/* begin block 2 */
		// Start line: 8628
	/* end block 2 */
	// End Line: 8629

/* WARNING: Control flow encountered bad instruction data */

void DeletingCurrBlock__7DISPMANi(DISPMAN *this,int n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// decompiled code
// original method signature: 
// void /*$ra*/ InvalidateArea__7DISPMANG4RECT(struct DISPMAN *this /*$s3*/, struct RECT rect /*stack 4*/)
 // line 2033, offset 0x000fdf68
	/* begin block 1 */
		// Start line: 2034
		// Start offset: 0x000FDF68
		// Variables:
	// 		int n; // $s2
	/* end block 1 */
	// End offset: 0x000FE040
	// End Line: 2040

	/* begin block 2 */
		// Start line: 8634
	/* end block 2 */
	// End Line: 8635

void FUN_MCARD__000fdf68(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint *puVar4;
  undefined4 *puVar5;
  int iVar6;
  
  puVar4 = (uint *)(&DAT_0000223c + param_1);
  puVar5 = (undefined4 *)(param_1 + 0x120);
  iVar6 = 6;
  do {
    uVar2 = *puVar5;
    puVar1 = puVar5 + 1;
    puVar5 = puVar5 + 2;
    iVar3 = FUN_MCARD__000f9fac(param_1,param_2,param_3,uVar2,*puVar1);
    iVar6 = iVar6 + -1;
    *puVar4 = (uint)(*puVar4 != 0 || iVar3 != 0);
    puVar4 = puVar4 + 1;
  } while (-1 < iVar6);
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ intersect__7DISPMANG4RECTT1(struct DISPMAN *this /*$a0*/, struct RECT rect1 /*stack 4*/, struct RECT rect2 /*stack 12*/)
 // line 2044, offset 0x000f9fac
	/* begin block 1 */
		// Start line: 2045
		// Start offset: 0x000F9FAC
		// Variables:
	// 		int n; // $t0
	// 		struct POINT p[4]; // stack offset -40
	// 		char bitPattern[2]; // stack offset -8
	/* end block 1 */
	// End offset: 0x000FA174
	// End Line: 2078

	/* begin block 2 */
		// Start line: 4717
	/* end block 2 */
	// End Line: 4718

	/* begin block 3 */
		// Start line: 4731
	/* end block 3 */
	// End Line: 4732

undefined4
FUN_MCARD__000f9fac(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  short local_res4;
  short sStackX6;
  short local_res8;
  short sStackX10;
  short local_resc;
  short sStackX14;
  int local_28 [8];
  bool local_8;
  bool local_7;
  
  local_resc = (short)param_4;
  iVar4 = (int)local_resc;
  uVar5 = 0;
  local_res4 = (short)param_2;
  local_28[0] = (int)local_res4;
  piVar6 = local_28 + 1;
  sStackX14 = (short)((uint)param_4 >> 0x10);
  iVar3 = (int)sStackX14;
  sStackX6 = (short)((uint)param_2 >> 0x10);
  local_28[1] = (int)sStackX6;
  sStackX10 = (short)((uint)param_3 >> 0x10);
  local_28[3] = local_28[1];
  local_res8 = (short)param_3;
  local_28[5] = local_28[1] + sStackX10;
  local_28[6] = local_28[0];
  local_28[7] = local_28[1] + sStackX10;
  local_28[2] = local_28[0] + local_res8;
  local_28[4] = local_28[0] + local_res8;
  iVar2 = 0;
  while( true ) {
    local_8 = false;
    bVar1 = *(int *)((int)local_28 + iVar2) < iVar4;
    if (bVar1) {
      local_8 = true;
    }
    local_8 = bVar1;
    if (iVar4 + (short)param_5 < *(int *)((int)local_28 + iVar2)) {
      local_8 = (bool)(bVar1 | 2);
    }
    if (*(int *)((int)piVar6 + iVar2) < iVar3) {
      local_8 = (bool)(local_8 | 4);
    }
    uVar5 = uVar5 + 1;
    if (iVar3 + param_5._2_2_ < *(int *)((int)piVar6 + iVar2)) {
      local_8 = (bool)(local_8 | 8);
    }
    local_7 = false;
    bVar1 = local_28[(uVar5 & 3) * 2] < iVar4;
    if (bVar1) {
      local_7 = true;
    }
    local_7 = bVar1;
    if (iVar4 + (short)param_5 < local_28[(uVar5 & 3) * 2]) {
      local_7 = (bool)(bVar1 | 2);
    }
    if (piVar6[(uVar5 & 3) * 2] < iVar3) {
      local_7 = (bool)(local_7 | 4);
    }
    if (iVar3 + param_5._2_2_ < piVar6[(uVar5 & 3) * 2]) {
      local_7 = (bool)(local_7 | 8);
    }
    if ((local_8 & local_7) == 0) break;
    iVar2 = uVar5 * 8;
    if (3 < (int)uVar5) {
      return 0;
    }
  }
  return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InvalidateArea__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
 // line 2081, offset 0x000fe040
	/* begin block 1 */
		// Start line: 2082
		// Start offset: 0x000FE040
		// Variables:
	// 		int i; // $a2
	/* end block 1 */
	// End offset: 0x000FE090
	// End Line: 2095

	/* begin block 2 */
		// Start line: 8741
	/* end block 2 */
	// End Line: 8742

	/* begin block 3 */
		// Start line: 8745
	/* end block 3 */
	// End Line: 8746

void FUN_MCARD__000fe040(int param_1,uint param_2)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  iVar4 = 0;
  if (param_2 < 8) {
    puVar3 = (uint *)(&DAT_000045ec + param_1);
    if (*(int *)(&DAT_000045ec + param_1) != -1) {
      uVar1 = *puVar3;
      puVar2 = puVar3;
      do {
        puVar2 = puVar2 + 1;
        if (uVar1 == param_2) {
          return;
        }
        uVar1 = *puVar2;
        iVar4 = iVar4 + 1;
      } while (uVar1 != 0xffffffff);
    }
    puVar3[iVar4] = param_2;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawArea__7DISPMANi(struct DISPMAN *this /*$a2*/, int n /*$a1*/)
 // line 2100, offset 0x000fe098
	/* begin block 1 */
		// Start line: 2101
		// Start offset: 0x000FE098
	/* end block 1 */
	// End offset: 0x000FE134
	// End Line: 2126

	/* begin block 2 */
		// Start line: 8779
	/* end block 2 */
	// End Line: 8780

void FUN_MCARD__000fe098(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
    FUN_MCARD__000f72b8(param_1);
    break;
  case 1:
    FUN_MCARD__000f7508(param_1);
    break;
  case 2:
    FUN_MCARD__000f7688(param_1);
    break;
  case 3:
    FUN_MCARD__000f79c8(param_1);
    break;
  case 4:
    FUN_MCARD__000f7c4c(param_1);
    break;
  case 5:
    FUN_MCARD__000f819c(param_1);
    break;
  case 6:
    FUN_MCARD__000f8d24(param_1);
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FlashOn__7DISPMAN(struct DISPMAN *this /*$a0*/)
 // line 2129, offset 0x000fe144
	/* begin block 1 */
		// Start line: 2130
		// Start offset: 0x000FE144
	/* end block 1 */
	// End offset: 0x000FE150
	// End Line: 2130

	/* begin block 2 */
		// Start line: 8837
	/* end block 2 */
	// End Line: 8838

void FUN_MCARD__000fe144(int param_1)

{
  *(undefined4 *)(&DAT_00002238 + param_1) = 1;
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FlashOff__7DISPMAN(struct DISPMAN *this /*$a0*/)
 // line 2132, offset 0x000fe150
	/* begin block 1 */
		// Start line: 2133
		// Start offset: 0x000FE150
	/* end block 1 */
	// End offset: 0x000FE160
	// End Line: 2135

	/* begin block 2 */
		// Start line: 8843
	/* end block 2 */
	// End Line: 8844

	/* begin block 3 */
		// Start line: 8845
	/* end block 3 */
	// End Line: 8846

void FUN_MCARD__000fe150(int param_1)

{
  *(undefined4 *)(&DAT_00002238 + param_1) = 0;
  *(undefined4 *)(&DAT_00002234 + param_1) = 0xa0;
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ Update__7DISPMAN(struct DISPMAN *this /*$s1*/)
 // line 2139, offset 0x000fa174
	/* begin block 1 */
		// Start line: 2140
		// Start offset: 0x000FA174
		// Variables:
	// 		int n; // $s0
	// 		struct RECT rect; // stack offset -32

		/* begin block 1.1 */
			// Start line: 2167
			// Start offset: 0x000FA238

			/* begin block 1.1.1 */
				// Start line: 2168
				// Start offset: 0x000FA260

				/* begin block 1.1.1.1 */
					// Start line: 2140
					// Start offset: 0x000FA260
					// Variables:
				// 		struct DISPMAN *this; // $s1

					/* begin block 1.1.1.1.1 */
						// Start line: 2140
						// Start offset: 0x000FA260
						// Variables:
					// 		int i; // $a0
					/* end block 1.1.1.1.1 */
					// End offset: 0x000FA2A4
					// End Line: 2140
				/* end block 1.1.1.1 */
				// End offset: 0x000FA2A4
				// End Line: 2140

				/* begin block 1.1.1.2 */
					// Start line: 2140
					// Start offset: 0x000FA2A4
					// Variables:
				// 		struct DISPMAN *this; // $s1

					/* begin block 1.1.1.2.1 */
						// Start line: 2140
						// Start offset: 0x000FA2A4
						// Variables:
					// 		int i; // $a0
					/* end block 1.1.1.2.1 */
					// End offset: 0x000FA2EC
					// End Line: 2140
				/* end block 1.1.1.2 */
				// End offset: 0x000FA2EC
				// End Line: 2140

				/* begin block 1.1.1.3 */
					// Start line: 2140
					// Start offset: 0x000FA2EC
					// Variables:
				// 		struct DISPMAN *this; // $s1

					/* begin block 1.1.1.3.1 */
						// Start line: 2140
						// Start offset: 0x000FA2EC
						// Variables:
					// 		int i; // $a0
					/* end block 1.1.1.3.1 */
					// End offset: 0x000FA334
					// End Line: 2140
				/* end block 1.1.1.3 */
				// End offset: 0x000FA334
				// End Line: 2140

				/* begin block 1.1.1.4 */
					// Start line: 2140
					// Start offset: 0x000FA334
					// Variables:
				// 		struct DISPMAN *this; // $s1

					/* begin block 1.1.1.4.1 */
						// Start line: 2140
						// Start offset: 0x000FA334
						// Variables:
					// 		int i; // $a0
					/* end block 1.1.1.4.1 */
					// End offset: 0x000FA37C
					// End Line: 2140
				/* end block 1.1.1.4 */
				// End offset: 0x000FA37C
				// End Line: 2140

				/* begin block 1.1.1.5 */
					// Start line: 2140
					// Start offset: 0x000FA37C
					// Variables:
				// 		struct DISPMAN *this; // $s1

					/* begin block 1.1.1.5.1 */
						// Start line: 2140
						// Start offset: 0x000FA37C
					/* end block 1.1.1.5.1 */
					// End offset: 0x000FA39C
					// End Line: 2140
				/* end block 1.1.1.5 */
				// End offset: 0x000FA39C
				// End Line: 2140
			/* end block 1.1.1 */
			// End offset: 0x000FA39C
			// End Line: 2177
		/* end block 1.1 */
		// End offset: 0x000FA39C
		// End Line: 2177

		/* begin block 1.2 */
			// Start line: 2188
			// Start offset: 0x000FA3D8

			/* begin block 1.2.1 */
				// Start line: 2191
				// Start offset: 0x000FA3E8

				/* begin block 1.2.1.1 */
					// Start line: 2192
					// Start offset: 0x000FA3E8

					/* begin block 1.2.1.1.1 */
						// Start line: 2192
						// Start offset: 0x000FA3EC

						/* begin block 1.2.1.1.1.1 */
							// Start line: 2140
							// Start offset: 0x000FA3EC
							// Variables:
						// 		struct DISPMAN *this; // $s1
						// 		int n; // $s0

							/* begin block 1.2.1.1.1.1.1 */
								// Start line: 2140
								// Start offset: 0x000FA3EC
							/* end block 1.2.1.1.1.1.1 */
							// End offset: 0x000FA47C
							// End Line: 2140
						/* end block 1.2.1.1.1.1 */
						// End offset: 0x000FA47C
						// End Line: 2140
					/* end block 1.2.1.1.1 */
					// End offset: 0x000FA47C
					// End Line: 2192
				/* end block 1.2.1.1 */
				// End offset: 0x000FA488
				// End Line: 2192
			/* end block 1.2.1 */
			// End offset: 0x000FA488
			// End Line: 2192
		/* end block 1.2 */
		// End offset: 0x000FA488
		// End Line: 2192
	/* end block 1 */
	// End offset: 0x000FA684
	// End Line: 2266

	/* begin block 2 */
		// Start line: 4986
	/* end block 2 */
	// End Line: 4987

uint FUN_MCARD__000fa174(int *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  int *piVar7;
  uint uVar8;
  short local_20;
  short local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  DrawSync(0);
  VSync(0);
  iVar2 = FUN_MCARD__001000d0(param_1[0x1179]);
  if (iVar2 == 0) {
    if ((*param_1 == 0) && ((DAT_MCARD__0010ee08 & 8) != 0)) {
      do {
        iVar2 = VSync(1);
      } while (iVar2 < 100);
    }
  }
  else {
    local_20 = *(short *)(param_1 + 0xa6);
    local_1e = *(short *)(param_1 + 0xa7);
    local_1c = 0x10;
    local_1a = 0x10;
    LoadImage(&local_20,param_1 + 0xa8);
    DrawSync(0);
  }
  piVar6 = param_1 + 0x117b;
  iVar2 = FUN_MCARD__0010037c(param_1[0x1179],0);
  if ((iVar2 != 0) || (iVar2 = FUN_MCARD__0010037c(param_1[0x1179],1), iVar2 != 0)) {
    iVar2 = 0;
    if (param_1[0x117b] != -1) {
      iVar3 = *piVar6;
      piVar7 = piVar6;
      do {
        piVar7 = piVar7 + 1;
        if (iVar3 == 1) goto LAB_MCARD__000fa2a4;
        iVar3 = *piVar7;
        iVar2 = iVar2 + 1;
      } while (iVar3 != -1);
    }
    piVar6[iVar2] = 1;
LAB_MCARD__000fa2a4:
    iVar2 = 0;
    if (param_1[0x117b] != -1) {
      iVar3 = *piVar6;
      piVar7 = piVar6;
      do {
        piVar7 = piVar7 + 1;
        if (iVar3 == 2) goto LAB_MCARD__000fa2ec;
        iVar3 = *piVar7;
        iVar2 = iVar2 + 1;
      } while (iVar3 != -1);
    }
    piVar6[iVar2] = 2;
LAB_MCARD__000fa2ec:
    iVar2 = 0;
    if (param_1[0x117b] != -1) {
      iVar3 = *piVar6;
      piVar7 = piVar6;
      do {
        piVar7 = piVar7 + 1;
        if (iVar3 == 4) goto LAB_MCARD__000fa334;
        iVar3 = *piVar7;
        iVar2 = iVar2 + 1;
      } while (iVar3 != -1);
    }
    piVar6[iVar2] = 4;
LAB_MCARD__000fa334:
    iVar2 = 0;
    if (param_1[0x117b] != -1) {
      iVar3 = *piVar6;
      piVar7 = piVar6;
      do {
        piVar7 = piVar7 + 1;
        if (iVar3 == 5) goto LAB_MCARD__000fa37c;
        iVar3 = *piVar7;
        iVar2 = iVar2 + 1;
      } while (iVar3 != -1);
    }
    piVar6[iVar2] = 5;
LAB_MCARD__000fa37c:
    FUN_MCARD__000fe040(param_1,param_1[0x1183]);
    FUN_MCARD__000fe040(param_1,2);
    param_1[0x1183] = 2;
  }
  if (param_1[0x117b] != -1) {
    param_1[param_1[0x117b] + 0x88f] = 1;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *piVar6 = piVar6[1];
    piVar6 = piVar6 + 1;
  } while (iVar2 < 6);
  param_1[0x1181] = -1;
  if (*param_1 == 0) {
    uVar8 = 6;
    bVar1 = true;
    do {
      if (bVar1) {
                    /* WARNING: Could not recover jumptable at 0x000fa40c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar4 = (*(code *)(&PTR_LAB_MCARD__000fa414_MCARD__000f30b4)[uVar8])();
        return uVar4;
      }
      uVar8 = uVar8 - 1;
      bVar1 = uVar8 < 7;
    } while (-1 < (int)uVar8);
  }
  DrawOTag(DAT_MCARD__0010ec74);
  DrawSync(0);
  ClearOTag(DAT_MCARD__0010ec74,1);
  iVar2 = FUN_MCARD__001000d0(param_1[0x1179]);
  if (iVar2 != 0) {
    local_20 = FUN_MCARD__00100158(param_1[0x1179]);
    local_1e = FUN_MCARD__0010016c(param_1[0x1179]);
    local_1c = 0x10;
    local_1a = 0x10;
    param_1[0xa7] = (int)local_1e;
    param_1[0xa6] = (int)local_20;
    StoreImage(&local_20,param_1 + 0xa8);
    DrawSync(0);
    uVar4 = FUN_MCARD__00100158(param_1[0x1179]);
    uVar5 = FUN_MCARD__0010016c(param_1[0x1179]);
    FUN_MCARD__000facd4(param_1,param_1 + 0x112b,uVar4,uVar5,0x80,0x80,0x80,0);
  }
  iVar2 = 0xff;
  piVar6 = param_1 + 0x1124;
  do {
    *piVar6 = 0;
    iVar2 = iVar2 + -1;
    piVar6 = piVar6 + -5;
  } while (-1 < iVar2);
  param_1[0xa1] = 0;
  param_1[0xa5] = 0;
  param_1[0xa4] = 0;
  param_1[0xa2] = 0;
  param_1[0xa3] = 0;
  if (param_1[0x88e] != 0) {
    iVar3 = param_1[0x88c];
    iVar2 = iVar3 + 0x50;
    if (0x4f < iVar3) {
      iVar2 = 0xf0 - iVar3;
    }
    param_1[0x88d] = iVar2;
    if (param_1[0x1183] == 1) {
      iVar2 = param_1[0x88c] + 8;
    }
    else {
      iVar2 = param_1[0x88c] + 0x10;
    }
    param_1[0x88c] = iVar2;
    if (0xa0 < param_1[0x88c]) {
      param_1[0x88c] = 0;
    }
  }
  if (((param_1[0x118a] != 5) &&
      (iVar2 = FUN_MCARD__001002a4(param_1[0x1179]), param_1[0x1185] == iVar2)) ||
     (iVar2 = FUN_MCARD__001002a4(param_1[0x1179]), iVar2 < param_1[0x1185])) {
    iVar2 = FUN_MCARD__001002a4(param_1[0x1179]);
    param_1[0x1185] = iVar2 + -1;
  }
  if (param_1[0x1185] < 0) {
    param_1[0x1185] = 0;
  }
  return (uint)(param_1[0x117b] == -1);
}



// decompiled code
// original method signature: 
// int /*$ra*/ PrintKanji__7DISPMANPsiiiiii(struct DISPMAN *this /*$s1*/, short *string /*$s0*/, int x /*$s4*/, int y /*$fp*/, int maxChars /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 2271, offset 0x000fa684
	/* begin block 1 */
		// Start line: 2272
		// Start offset: 0x000FA684
		// Variables:
	// 		char textBuffer[256]; // stack offset -312
	// 		int lookup; // $a1
	// 		int n; // stack offset -48
	// 		short *sjisPtr; // $s0
	// 		short sjisCode[3]; // stack offset -56
	// 		int chars; // $v1
	/* end block 1 */
	// End offset: 0x000FA97C
	// End Line: 2350

	/* begin block 2 */
		// Start line: 5284
	/* end block 2 */
	// End Line: 5285

int FUN_MCARD__000fa684(int param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                       undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  short local_138;
  short local_136 [127];
  short local_38;
  undefined2 local_36;
  undefined2 local_34;
  int local_30;
  int local_2c;
  
  local_30 = 0;
  local_36 = 0;
  local_34 = 0;
  memset(&local_138,0,0x100);
  FUN_MCARD__000f512c(&local_138,param_2);
  psVar2 = &local_138;
  local_2c = FUN_MCARD__000fe258(psVar2,1000);
  if (local_2c < param_5) {
    param_5 = local_2c;
  }
  local_2c = local_2c << 3;
  local_38 = local_138;
  if ((local_138 != 0) && (0 < param_5)) {
    do {
      local_30 = local_30 + 2;
      iVar1 = FUN_MCARD__000fe160(param_1,(int)local_38);
      iVar3 = param_1 + 0x30a4;
      psVar2 = psVar2 + 1;
      if (iVar1 == -1) {
        iVar1 = *(int *)(&DAT_00004608 + param_1);
        if (*(int *)(iVar3 + iVar1 * 0x14) == 1) {
          do {
            *(int *)(&DAT_00004608 + param_1) = iVar1 + 1;
            if (iVar1 + 1 == *(int *)(&DAT_00004630 + param_1)) {
              *(undefined4 *)(&DAT_00004608 + param_1) = 0;
            }
            iVar1 = *(int *)(&DAT_00004608 + param_1);
          } while (*(int *)(iVar3 + iVar1 * 0x14) == 1);
        }
        iVar1 = Krom2Tim(&local_38,param_1 + 0x4a0,
                         (*(uint *)(&DAT_00004608 + param_1) & 0x1f) << 2 | 0x200,
                         ((int)*(uint *)(&DAT_00004608 + param_1) >> 5) << 4,0x200,0xfe,0xffff,0);
        if (iVar1 != -1) {
          FUN_MCARD__000fd658(param_1,param_1 + 0x4a0,
                              *(int *)(&DAT_00004608 + param_1) * 0x14 + param_1 + 0x30a8,0,0,0,0,0,
                              0);
          *(short *)(&DAT_000030a0 + param_1 + *(int *)(&DAT_00004608 + param_1) * 0x14) = local_38;
          *(undefined2 *)(&DAT_000030b0 + param_1 + *(int *)(&DAT_00004608 + param_1) * 0x14) = 0x10
          ;
          *(undefined2 *)(&DAT_000030b2 + param_1 + *(int *)(&DAT_00004608 + param_1) * 0x14) = 0x10
          ;
        }
        iVar1 = *(int *)(&DAT_00004608 + param_1);
        *(int *)(&DAT_00004608 + param_1) = iVar1 + 1;
        if (iVar1 + 1 == *(int *)(&DAT_00004630 + param_1)) {
          *(undefined4 *)(&DAT_00004608 + param_1) = 0;
        }
        if (iVar1 != -1) goto LAB_MCARD__000fa8cc;
      }
      else {
LAB_MCARD__000fa8cc:
        FUN_MCARD__000fe61c(param_1,iVar1 * 0x14 + param_1 + 0x30a8,param_3,param_4 + 4,param_6,
                            param_7,param_8,0);
        *(undefined4 *)(iVar3 + iVar1 * 0x14) = 1;
      }
      local_38 = *psVar2;
    } while ((local_38 != 0) && (param_3 = param_3 + 0x10, local_30 < param_5));
  }
  return local_2c;
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindKanji__7DISPMANs(struct DISPMAN *this /*$a0*/, short sjisCode /*$a1*/)
 // line 2355, offset 0x000fe160
	/* begin block 1 */
		// Start line: 2356
		// Start offset: 0x000FE160
		// Variables:
	// 		int n; // $v1
	/* end block 1 */
	// End offset: 0x000FE1A8
	// End Line: 2367

	/* begin block 2 */
		// Start line: 9290
	/* end block 2 */
	// End Line: 9291

	/* begin block 3 */
		// Start line: 9293
	/* end block 3 */
	// End Line: 9294

int FUN_MCARD__000fe160(int param_1,short param_2)

{
  int iVar1;
  short *psVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(&DAT_00004630 + param_1)) {
    psVar2 = (short *)(&DAT_000030a0 + param_1);
    do {
      if (*psVar2 == param_2) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      psVar2 = psVar2 + 10;
    } while (iVar1 < *(int *)(&DAT_00004630 + param_1));
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CentrePrintKanji__7DISPMANPsiiiiii(struct DISPMAN *this /*$s5*/, short *string /*$s3*/, int x /*$s6*/, int y /*$s7*/, int maxChars /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 2371, offset 0x000fe1b0
	/* begin block 1 */
		// Start line: 2372
		// Start offset: 0x000FE1B0
	/* end block 1 */
	// End offset: 0x000FE258
	// End Line: 2375

	/* begin block 2 */
		// Start line: 9325
	/* end block 2 */
	// End Line: 9326

void FUN_MCARD__000fe1b0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                        undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  
  iVar1 = FUN_MCARD__000fe258(param_2,param_5);
  FUN_MCARD__000fa684(param_1,param_2,param_3 + iVar1 * -4,param_4,param_5,param_6,param_7,param_8);
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ KanjiStrLen__FPsi(short *kanjiStringPtr /*$s1*/, int maxChars /*$s0*/)
 // line 2379, offset 0x000fe258
	/* begin block 1 */
		// Start line: 2380
		// Start offset: 0x000FE258
		// Variables:
	// 		short textBuffer[128]; // stack offset -272
	// 		int totalLen; // $a1
	/* end block 1 */
	// End offset: 0x000FE2F4
	// End Line: 2396

	/* begin block 2 */
		// Start line: 9342
	/* end block 2 */
	// End Line: 9343

int FUN_MCARD__000fe258(undefined4 param_1,int param_2)

{
  size_t sVar1;
  short *psVar2;
  uint uVar3;
  uint uVar4;
  short asStack274 [129];
  
  memset(asStack274 + 1,0,0x100);
  FUN_MCARD__000f512c(asStack274 + 1,param_1);
  sVar1 = strlen((char *)(asStack274 + 1));
  uVar4 = sVar1 >> 1;
  if (param_2 / 2 < (int)(sVar1 >> 1)) {
    uVar4 = param_2 / 2;
  }
  psVar2 = asStack274 + uVar4;
  do {
    uVar3 = uVar4 - 1;
    if (*psVar2 != 0x4081) break;
    psVar2 = psVar2 + -1;
    uVar4 = uVar3;
  } while (0 < (int)uVar3);
  return uVar4 << 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ darken__7DISPMANG4RECT(struct DISPMAN *this /*$s0*/, struct RECT rect /*stack 4*/)
 // line 2402, offset 0x000fa97c
	/* begin block 1 */
		// Start line: 2403
		// Start offset: 0x000FA97C
	/* end block 1 */
	// End offset: 0x000FACC4
	// End Line: 2433

	/* begin block 2 */
		// Start line: 5581
	/* end block 2 */
	// End Line: 5582

void FUN_MCARD__000fa97c(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  short local_res4;
  short sStackX6;
  short local_res8;
  short sStackX10;
  
  if (*(int *)(param_1 + 0x288) < 0x19) {
    local_res4 = (short)param_2;
    *(short *)(&DAT_00001be8 + param_1 + *(int *)(param_1 + 0x288) * 0x28) = local_res4;
    local_res8 = (short)param_3;
    *(short *)(&DAT_00001bf0 + param_1 + *(int *)(param_1 + 0x288) * 0x28) = local_res4 + local_res8
    ;
    *(short *)(&DAT_00001bf8 + param_1 + *(int *)(param_1 + 0x288) * 0x28) = local_res4;
    *(short *)(param_1 + *(int *)(param_1 + 0x288) * 0x28 + 0x1c00) = local_res4 + local_res8;
    sStackX6 = (short)((uint)param_2 >> 0x10);
    *(short *)(&DAT_00001bea + param_1 + *(int *)(param_1 + 0x288) * 0x28) = sStackX6;
    *(short *)(&DAT_00001bf2 + param_1 + *(int *)(param_1 + 0x288) * 0x28) = sStackX6;
    sStackX10 = (short)((uint)param_3 >> 0x10);
    *(short *)(&DAT_00001bfa + param_1 + *(int *)(param_1 + 0x288) * 0x28) = sStackX6 + sStackX10;
    *(short *)(&DAT_00001c02 + param_1 + *(int *)(param_1 + 0x288) * 0x28) = sStackX6 + sStackX10;
    (&DAT_00001bec)[param_1 + *(int *)(param_1 + 0x288) * 0x28] = (&DAT_000044a4)[param_1];
    (&DAT_00001bf4)[param_1 + *(int *)(param_1 + 0x288) * 0x28] =
         (&DAT_000044a8)[param_1] + (&DAT_000044a4)[param_1] + -1;
    (&DAT_00001bfc)[param_1 + *(int *)(param_1 + 0x288) * 0x28] = (&DAT_000044a4)[param_1];
    (&DAT_00001c04)[param_1 + *(int *)(param_1 + 0x288) * 0x28] =
         (&DAT_000044a8)[param_1] + (&DAT_000044a4)[param_1] + -1;
    (&DAT_00001bed)[param_1 + *(int *)(param_1 + 0x288) * 0x28] = (&DAT_000044a6)[param_1];
    (&DAT_00001bf5)[param_1 + *(int *)(param_1 + 0x288) * 0x28] = (&DAT_000044a6)[param_1];
    (&DAT_00001bfd)[param_1 + *(int *)(param_1 + 0x288) * 0x28] =
         (&DAT_000044aa)[param_1] + (&DAT_000044a6)[param_1] + -1;
    (&DAT_00001c05)[param_1 + *(int *)(param_1 + 0x288) * 0x28] =
         (&DAT_000044aa)[param_1] + (&DAT_000044a6)[param_1] + -1;
    *(undefined2 *)(&DAT_00001bf6 + param_1 + *(int *)(param_1 + 0x288) * 0x28) =
         *(undefined2 *)(&DAT_000044a2 + param_1);
    *(undefined2 *)(&DAT_00001bee + param_1 + *(int *)(param_1 + 0x288) * 0x28) =
         *(undefined2 *)(&DAT_000044a0 + param_1);
    (&DAT_00001be4)[*(int *)(param_1 + 0x288) * 0x28 + param_1] = 0x60;
    (&DAT_00001be5)[*(int *)(param_1 + 0x288) * 0x28 + param_1] = 0x60;
    (&DAT_00001be6)[*(int *)(param_1 + 0x288) * 0x28 + param_1] = 0x60;
    (&DAT_00001be4)[*(int *)(param_1 + 0x288) * 0x28 + param_1] = 0xff;
    (&DAT_00001be5)[*(int *)(param_1 + 0x288) * 0x28 + param_1] = 0xff;
    (&DAT_00001be6)[*(int *)(param_1 + 0x288) * 0x28 + param_1] = 0xff;
    SetSemiTrans(param_1 + *(int *)(param_1 + 0x288) * 0x28 + 0x1be0,2);
    uVar1 = DAT_MCARD__0010ec74;
    iVar2 = *(int *)(param_1 + 0x288);
    *(int *)(param_1 + 0x288) = iVar2 + 1;
    FUN_MCARD__0010eb20(uVar1,param_1 + iVar2 * 0x28 + 0x1be0);
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetCurrBlock__7DISPMAN(struct DISPMAN *this /*$a0*/)
 // line 2474, offset 0x000fe2f4
	/* begin block 1 */
		// Start line: 2475
		// Start offset: 0x000FE2F4
	/* end block 1 */
	// End offset: 0x000FE300
	// End Line: 2475

	/* begin block 2 */
		// Start line: 9538
	/* end block 2 */
	// End Line: 9539

undefined4 FUN_MCARD__000fe2f4(int param_1)

{
  return *(undefined4 *)(&DAT_00004614 + param_1);
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetCurrSlice__7DISPMAN(struct DISPMAN *this /*$a0*/)
 // line 2476, offset 0x000fe300
	/* begin block 1 */
		// Start line: 2477
		// Start offset: 0x000FE300
	/* end block 1 */
	// End offset: 0x000FE30C
	// End Line: 2477

	/* begin block 2 */
		// Start line: 9542
	/* end block 2 */
	// End Line: 9543

undefined4 FUN_MCARD__000fe300(int param_1)

{
  return *(undefined4 *)(&DAT_00004618 + param_1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ draw_card__7DISPMANiiPcb(struct DISPMAN *this /*$s1*/, int x /*$s2*/, int y /*$s3*/, char *text /*$a1*/, unsigned int selected /*stack 16*/)
 // line 2480, offset 0x000fe30c
	/* begin block 1 */
		// Start line: 2481
		// Start offset: 0x000FE30C
	/* end block 1 */
	// End offset: 0x000FE418
	// End Line: 2495

	/* begin block 2 */
		// Start line: 9550
	/* end block 2 */
	// End Line: 9551

void FUN_MCARD__000fe30c(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_5 == 0) {
    FUN_MCARD__000fe834(param_1,param_4,param_2 + 0x18,param_3 + 0xe,0,6,0x50,0x50,0x50,0);
    if ((DAT_MCARD__0010ee08 & 0x10) != 0) {
      FUN_MCARD__000fe61c(param_1,param_1 + 0x44c4,param_2,param_3,0x50,0x50,0x50,0);
    }
  }
  else {
    iVar2 = *(int *)(&DAT_00002234 + param_1) + -0x14;
    FUN_MCARD__000fe834(param_1,param_4,param_2 + 0x18,param_3 + 0xe,0,6,iVar2,iVar2,iVar2,0);
    if ((DAT_MCARD__0010ee08 & 0x10) != 0) {
      uVar1 = *(undefined4 *)(&DAT_00002234 + param_1);
      FUN_MCARD__000fe61c(param_1,param_1 + 0x44c4,param_2,param_3,uVar1,uVar1,uVar1,0);
    }
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AddIcon__7DISPMANP9TIMSTRUCTiiiiiib(struct DISPMAN *this /*$a0*/, struct TIMSTRUCT *tim /*$t2*/, int x /*$a2*/, int y /*$a1*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/, unsigned int scale /*stack 32*/)
 // line 2515, offset 0x000fe434
	/* begin block 1 */
		// Start line: 2516
		// Start offset: 0x000FE434
		// Variables:
	// 		int XPlusW; // $t1
	// 		int YPlusH; // $a0
	// 		struct POLY_FT4 *polyFT4Ptr; // $t0
	/* end block 1 */
	// End offset: 0x000FE590
	// End Line: 2560

	/* begin block 2 */
		// Start line: 9620
	/* end block 2 */
	// End Line: 9621

undefined4
FUN_MCARD__000fe434(int param_1,ushort *param_2,uint param_3,int param_4,uint param_5,int param_6,
                   int param_7,int param_8,int param_9)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  if (param_2 != (ushort *)0x0) {
    puVar4 = (uint *)(param_1 + *(int *)(param_1 + 0x288) * 0x28 + 0x1be0);
    *(int *)(param_1 + 0x288) = *(int *)(param_1 + 0x288) + 1;
    if (param_9 == 0) {
      uVar2 = (uint)param_2[4];
    }
    else {
      uVar2 = (int)((uint)param_2[4] * 3) >> 1;
    }
    uVar1 = param_2[5];
    puVar4[2] = param_4 << 0x10 | param_3;
    puVar4[4] = param_4 << 0x10 | param_3 + uVar2;
    uVar3 = (param_4 + (uint)uVar1) * 0x10000;
    puVar4[6] = uVar3 | param_3;
    puVar4[8] = uVar3 | param_3 + uVar2;
    uVar3 = (uint)param_2[2] + (uint)param_2[4];
    uVar2 = ((uint)param_2[3] + (uint)param_2[5]) * 0x100;
    puVar4[3] = (uint)*param_2 << 0x10 | (uint)param_2[3] << 8 | (uint)param_2[2];
    puVar4[5] = (uint)param_2[1] << 0x10 | (uint)param_2[3] << 8 | uVar3;
    uVar1 = param_2[2];
    puVar4[9] = uVar2 | uVar3;
    puVar4[7] = uVar2 | uVar1;
    puVar4[1] = param_8 << 0x19 | param_7 << 0x10 | 0x2c000000U | param_6 << 8 | param_5;
    *puVar4 = *DAT_MCARD__0010ec74 | 0x9000000;
    *DAT_MCARD__0010ec74 = (uint)puVar4 & 0xffffff;
    return 0;
  }
  return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AddMoveImage__7DISPMANP4RECTT1(struct DISPMAN *this /*$s0*/, struct RECT *srect /*$a1*/, struct RECT *drect /*$t0*/)
 // line 2616, offset 0x000fe598
	/* begin block 1 */
		// Start line: 2617
		// Start offset: 0x000FE598
		// Variables:
	// 		struct DR_MOVE *movePtr; // $s0
	/* end block 1 */
	// End offset: 0x000FE61C
	// End Line: 2625

	/* begin block 2 */
		// Start line: 9886
	/* end block 2 */
	// End Line: 9887

undefined4 FUN_MCARD__000fe598(int param_1,undefined4 param_2,short *param_3)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = *(int *)(param_1 + 0x294);
  *(int *)(param_1 + 0x294) = iVar1 + 1;
  puVar2 = (uint *)(param_1 + iVar1 * 0x18 + 0x21f8);
  SetDrawMove(puVar2,param_2,(int)*param_3,(int)param_3[1]);
  *puVar2 = *DAT_MCARD__0010ec74 | 0x5000000;
  *DAT_MCARD__0010ec74 = (uint)puVar2 & 0xffffff;
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AddSprite__7DISPMANP9TIMSTRUCTiiiiii(struct DISPMAN *this /*$a0*/, struct TIMSTRUCT *tim /*$a1*/, int x /*$a2*/, int y /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/)
 // line 2630, offset 0x000fe61c
	/* begin block 1 */
		// Start line: 2631
		// Start offset: 0x000FE61C
		// Variables:
	// 		struct SPRT *spritePtr; // $t0
	// 		struct DR_TPAGE *tpagePtr; // $a0
	/* end block 1 */
	// End offset: 0x000FE72C
	// End Line: 2666

	/* begin block 2 */
		// Start line: 9920
	/* end block 2 */
	// End Line: 9921

	/* begin block 3 */
		// Start line: 9931
	/* end block 3 */
	// End Line: 9932

	/* begin block 4 */
		// Start line: 9945
	/* end block 4 */
	// End Line: 9946

undefined4
FUN_MCARD__000fe61c(int param_1,ushort *param_2,uint param_3,int param_4,uint param_5,int param_6,
                   int param_7,int param_8)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x284);
  puVar3 = (uint *)(param_1 + iVar4 * 0x14 + 0x600);
  *(int *)(param_1 + 0x284) = iVar4 + 1;
  puVar3[2] = param_4 << 0x10 | param_3;
  puVar3[3] = (uint)*param_2 << 0x10 | (uint)param_2[3] << 8 | (uint)param_2[2];
  uVar1 = *(uint *)(param_2 + 4);
  puVar3[1] = param_8 << 0x19 | param_7 << 0x10 | 0x64000000U | param_6 << 8 | param_5;
  puVar3[4] = uVar1;
  puVar2 = (uint *)(param_1 + iVar4 * 8 + 0x15a0);
  *puVar3 = *DAT_MCARD__0010ec74 | 0x4000000;
  *DAT_MCARD__0010ec74 = (uint)puVar3 & 0xffffff;
  *(undefined *)((int)puVar2 + 3) = 1;
  puVar3 = DAT_MCARD__0010ec74;
  puVar2[1] = (uint)param_2[1] & 0x9ff | 0xe1000000;
  *puVar2 = *puVar3 | 0x1000000;
  *DAT_MCARD__0010ec74 = (uint)puVar2 & 0xffffff;
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DrawSprite__7DISPMANP9TIMSTRUCTiiiiii(struct DISPMAN *this /*$s0*/, struct TIMSTRUCT *tim /*$s1*/, int x /*$s2*/, int y /*$s3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/)
 // line 2670, offset 0x000facd4
	/* begin block 1 */
		// Start line: 2671
		// Start offset: 0x000FACD4
	/* end block 1 */
	// End offset: 0x000FAED0
	// End Line: 2695

	/* begin block 2 */
		// Start line: 6118
	/* end block 2 */
	// End Line: 6119

undefined4
FUN_MCARD__000facd4(int param_1,undefined2 *param_2,undefined2 param_3,undefined2 param_4,
                   undefined param_5,undefined param_6,undefined param_7,undefined4 param_8)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined2 *)0x0) {
    uVar1 = 1;
  }
  else {
    if (*(int *)(param_1 + 0x284) < 200) {
      SetDrawTPage(param_1 + *(int *)(param_1 + 0x284) * 8 + 0x15a0,0,0,(uint)(ushort)param_2[1]);
      DrawPrim(param_1 + *(int *)(param_1 + 0x284) * 8 + 0x15a0);
      *(undefined2 *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x608) = param_3;
      *(undefined2 *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x60a) = param_4;
      *(undefined *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x60c) =
           *(undefined *)(param_2 + 2);
      *(undefined *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x60d) =
           *(undefined *)(param_2 + 3);
      *(undefined2 *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x610) = param_2[4];
      *(undefined2 *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x612) = param_2[5];
      *(undefined2 *)(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x60e) = *param_2;
      *(undefined *)(*(int *)(param_1 + 0x284) * 0x14 + param_1 + 0x604) = param_5;
      *(undefined *)(*(int *)(param_1 + 0x284) * 0x14 + param_1 + 0x605) = param_6;
      *(undefined *)(*(int *)(param_1 + 0x284) * 0x14 + param_1 + 0x606) = param_7;
      SetSemiTrans(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x600,param_8);
      DrawPrim(param_1 + *(int *)(param_1 + 0x284) * 0x14 + 0x600);
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DrawBox__7DISPMANiiiiiii(struct DISPMAN *this /*$a0*/, int x /*$s2*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 2699, offset 0x000fe72c
	/* begin block 1 */
		// Start line: 2700
		// Start offset: 0x000FE72C
		// Variables:
	// 		struct LINE_F4 strF4; // stack offset -88
	// 		struct LINE_F2 strF2; // stack offset -56
	/* end block 1 */
	// End offset: 0x000FE834
	// End Line: 2731

	/* begin block 2 */
		// Start line: 10151
	/* end block 2 */
	// End Line: 10152

	/* begin block 3 */
		// Start line: 10155
	/* end block 3 */
	// End Line: 10156

undefined4
FUN_MCARD__000fe72c(undefined4 param_1,short param_2,short param_3,short param_4,short param_5,
                   undefined param_6,undefined param_7,undefined param_8)

{
  undefined auStack88 [4];
  undefined local_54;
  undefined local_53;
  undefined local_52;
  short local_50;
  short local_4e;
  short local_4c;
  short local_4a;
  short local_48;
  short local_46;
  short local_44;
  short local_42;
  undefined auStack56 [4];
  undefined local_34;
  undefined local_33;
  undefined local_32;
  short local_30;
  short local_2e;
  short local_2c;
  short local_2a;
  
  SetLineF4(auStack88);
  SetLineF2(auStack56);
  local_54 = param_6;
  local_53 = param_7;
  local_52 = param_8;
  local_34 = local_54;
  local_33 = local_53;
  local_32 = local_52;
  SetSemiTrans(auStack88,0);
  SetSemiTrans(auStack56,0);
  local_4c = param_2 + param_4;
  local_46 = param_3 + param_5;
  local_50 = param_2;
  local_4e = param_3;
  local_4a = param_3;
  local_48 = local_4c;
  local_44 = param_2;
  local_42 = local_46;
  local_30 = param_2;
  local_2e = local_46;
  local_2c = param_2;
  local_2a = param_3;
  DrawPrim(auStack88);
  DrawPrim(auStack56);
  DrawSync(0);
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AddCircleG16__7DISPMANiiiiiiii(struct DISPMAN *this /*$s0*/, int x /*stack 4*/, int y /*stack 8*/, int diameter /*$a3*/, int complete /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/, int divisor /*stack 32*/)
 // line 2743, offset 0x000faed0
	/* begin block 1 */
		// Start line: 2744
		// Start offset: 0x000FAED0
		// Variables:
	// 		int modX; // $s6
	// 		int modY; // $s5

		/* begin block 1.1 */
			// Start line: 2753
			// Start offset: 0x000FAF54
			// Variables:
		// 		int n; // $s3
		/* end block 1.1 */
		// End offset: 0x000FB304
		// End Line: 2774
	/* end block 1 */
	// End offset: 0x000FB304
	// End Line: 2774

	/* begin block 2 */
		// Start line: 6264
	/* end block 2 */
	// End Line: 6265

	/* begin block 3 */
		// Start line: 6269
	/* end block 3 */
	// End Line: 6270

void FUN_MCARD__000faed0(int param_1,short param_2,short param_3,int param_4,int param_5,int param_6
                        ,int param_7,int param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;
  int iVar7;
  int *piVar8;
  
  iVar1 = (param_4 * 1000) / 0xd7;
  if (0x10 < param_5) {
    param_5 = 0x10;
  }
  iVar7 = 0;
  piVar8 = &DAT_MCARD__0010eb70;
  do {
    *(short *)(&DAT_00001fd0 + *(int *)(param_1 + 0x28c) * 0x1c + param_1) =
         (short)((param_4 * 8 * *piVar8 + 500) / 1000) + param_2;
    *(short *)(&DAT_00001fd2 + *(int *)(param_1 + 0x28c) * 0x1c + param_1) =
         (short)((iVar1 * (&DAT_MCARD__0010eb74)[iVar7 * 4] + 500) / 1000) + param_3;
    *(short *)(&DAT_00001fd8 + *(int *)(param_1 + 0x28c) * 0x1c + param_1) =
         (short)((param_4 * 8 * (&DAT_MCARD__0010eb78)[iVar7 * 4] + 500) / 1000) + param_2;
    *(short *)(&DAT_00001fda + *(int *)(param_1 + 0x28c) * 0x1c + param_1) =
         (short)((iVar1 * piVar8[3] + 500) / 1000) + param_3;
    *(short *)(*(int *)(param_1 + 0x28c) * 0x1c + param_1 + 0x1fe0) = param_2;
    *(short *)(&DAT_00001fe2 + *(int *)(param_1 + 0x28c) * 0x1c + param_1) = param_3;
    if (param_9 == 0) {
      trap(7);
    }
    uVar6 = (undefined)(param_6 / param_9);
    (&DAT_00001fcc)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = uVar6;
    if (param_9 == 0) {
      trap(7);
    }
    uVar5 = (undefined)(param_7 / param_9);
    (&DAT_00001fcd)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = uVar5;
    if (param_9 == 0) {
      trap(7);
    }
    uVar4 = (undefined)(param_8 / param_9);
    (&DAT_00001fce)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = uVar4;
    if (param_9 == 0) {
      trap(7);
    }
    (&DAT_00001fd4)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = uVar6;
    if (param_9 == 0) {
      trap(7);
    }
    (&DAT_00001fd5)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = uVar5;
    if (param_9 == 0) {
      trap(7);
    }
    (&DAT_00001fd6)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = uVar4;
    (&DAT_00001fdc)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = (char)param_6;
    (&DAT_00001fdd)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = (char)param_7;
    (&DAT_00001fde)[*(int *)(param_1 + 0x28c) * 0x1c + param_1] = (char)param_8;
    SetSemiTrans(param_1 + *(int *)(param_1 + 0x28c) * 0x1c + 0x1fc8,0);
    uVar2 = DAT_MCARD__0010ec74;
    if (iVar7 < param_5) {
      iVar3 = *(int *)(param_1 + 0x28c);
      *(int *)(param_1 + 0x28c) = iVar3 + 1;
      FUN_MCARD__0010eb20(uVar2,param_1 + iVar3 * 0x1c + 0x1fc8);
    }
    iVar7 = iVar7 + 1;
    piVar8 = piVar8 + 4;
  } while (iVar7 < 0x10);
  return;
}



// decompiled code
// original method signature: 
// short /*$ra*/ MessageBox__7DISPMANiPcbT3(struct DISPMAN *this /*$s5*/, int type /*stack 4*/, char *text /*stack 8*/, unsigned int bIgnoreEvents /*stack 12*/, unsigned int bSwapKeys /*stack 16*/)
 // line 2786, offset 0x000fb304
	/* begin block 1 */
		// Start line: 2787
		// Start offset: 0x000FB304
		// Variables:
	// 		int boxHeight; // $s6
	// 		int boxTop; // stack offset -72
	// 		int maxTextLen; // stack offset -68
	// 		int textLen; // $s0
	// 		int textY; // $s3
	// 		int lineCount; // $s1
	// 		struct RECT darkRect; // stack offset -304
	// 		struct RECT rect; // stack offset -296
	// 		char textBuffer[128]; // stack offset -288
	// 		int sel; // $fp
	// 		unsigned int cardState; // stack offset -64
	// 		unsigned int bInBox; // $s4
	// 		int n; // $s2
	// 		int messCount; // $s7
	// 		short padData; // $s4

		/* begin block 1.1 */
			// Start line: 2888
			// Start offset: 0x000FB79C
			// Variables:
		// 		struct DISPMAN *this; // $s5
		// 		struct RECT rect; // stack offset -148

			/* begin block 1.1.1 */
				// Start line: 2888
				// Start offset: 0x000FB79C
				// Variables:
			// 		int n; // $s2
			/* end block 1.1.1 */
			// End offset: 0x000FB8D0
			// End Line: 2899
		/* end block 1.1 */
		// End offset: 0x000FB8D0
		// End Line: 2899

		/* begin block 1.2 */
			// Start line: 2903
			// Start offset: 0x000FB8D0

			/* begin block 1.2.1 */
				// Start line: 2906
				// Start offset: 0x000FB8FC

				/* begin block 1.2.1.1 */
					// Start line: 2910
					// Start offset: 0x000FB954

					/* begin block 1.2.1.1.1 */
						// Start line: 2913
						// Start offset: 0x000FB984

						/* begin block 1.2.1.1.1.1 */
							// Start line: 2915
							// Start offset: 0x000FB9A8
							// Variables:
						// 		struct DISPMAN *this; // $s5
						// 		int y; // $s3

							/* begin block 1.2.1.1.1.1.1 */
								// Start line: 2915
								// Start offset: 0x000FB9A8
								// Variables:
							// 		struct LINE_F2 strF2; // stack offset -88
							// 		struct LINE_F4 strF4; // stack offset -120
							/* end block 1.2.1.1.1.1.1 */
							// End offset: 0x000FB9A8
							// End Line: 2915
						/* end block 1.2.1.1.1.1 */
						// End offset: 0x000FB9A8
						// End Line: 2915

						/* begin block 1.2.1.1.1.2 */
							// Start line: 2916
							// Start offset: 0x000FBA68
							// Variables:
						// 		struct DISPMAN *this; // $s5
						// 		int y; // $s3

							/* begin block 1.2.1.1.1.2.1 */
								// Start line: 2916
								// Start offset: 0x000FBA68
								// Variables:
							// 		struct LINE_F2 strF2; // stack offset -128
							// 		struct LINE_F4 strF4; // stack offset -160
							/* end block 1.2.1.1.1.2.1 */
							// End offset: 0x000FBA68
							// End Line: 2916
						/* end block 1.2.1.1.1.2 */
						// End offset: 0x000FBA68
						// End Line: 2916

						/* begin block 1.2.1.1.1.3 */
							// Start line: 2919
							// Start offset: 0x000FBB2C
							// Variables:
						// 		struct DISPMAN *this; // $s5
						// 		int y; // $s3

							/* begin block 1.2.1.1.1.3.1 */
								// Start line: 2919
								// Start offset: 0x000FBB2C
								// Variables:
							// 		struct LINE_F2 strF2; // stack offset -128
							// 		struct LINE_F4 strF4; // stack offset -160
							/* end block 1.2.1.1.1.3.1 */
							// End offset: 0x000FBBC8
							// End Line: 2919
						/* end block 1.2.1.1.1.3 */
						// End offset: 0x000FBBC8
						// End Line: 2919
					/* end block 1.2.1.1.1 */
					// End offset: 0x000FBBC8
					// End Line: 2922
				/* end block 1.2.1.1 */
				// End offset: 0x000FBBC8
				// End Line: 2922

				/* begin block 1.2.1.2 */
					// Start line: 2927
					// Start offset: 0x000FBC34

					/* begin block 1.2.1.2.1 */
						// Start line: 2962
						// Start offset: 0x000FBD50

						/* begin block 1.2.1.2.1.1 */
							// Start line: 2965
							// Start offset: 0x000FBD80

							/* begin block 1.2.1.2.1.1.1 */
								// Start line: 2787
								// Start offset: 0x000FBDD4
								// Variables:
							// 		struct DISPMAN *this; // $s5
							// 		int y; // $s3
							// 		int r; // $s2
							// 		int g; // $s1
							// 		int b; // $s0

								/* begin block 1.2.1.2.1.1.1.1 */
									// Start line: 2787
									// Start offset: 0x000FBDD4
									// Variables:
								// 		struct LINE_F2 strF2; // stack offset -128
								// 		struct LINE_F4 strF4; // stack offset -160
								/* end block 1.2.1.2.1.1.1.1 */
								// End offset: 0x000FBDD4
								// End Line: 2787
							/* end block 1.2.1.2.1.1.1 */
							// End offset: 0x000FBDD4
							// End Line: 2787

							/* begin block 1.2.1.2.1.1.2 */
								// Start line: 2787
								// Start offset: 0x000FBEFC
								// Variables:
							// 		struct DISPMAN *this; // $s5
							// 		int y; // $s3
							// 		int r; // $s2
							// 		int g; // $s1
							// 		int b; // $s0

								/* begin block 1.2.1.2.1.1.2.1 */
									// Start line: 2787
									// Start offset: 0x000FBEFC
									// Variables:
								// 		struct LINE_F2 strF2; // stack offset -128
								// 		struct LINE_F4 strF4; // stack offset -160
								/* end block 1.2.1.2.1.1.2.1 */
								// End offset: 0x000FBEFC
								// End Line: 2787
							/* end block 1.2.1.2.1.1.2 */
							// End offset: 0x000FBEFC
							// End Line: 2787

							/* begin block 1.2.1.2.1.1.3 */
								// Start line: 2974
								// Start offset: 0x000FC01C
								// Variables:
							// 		struct DISPMAN *this; // $s5
							// 		int y; // $s3
							// 		int r; // $s1

								/* begin block 1.2.1.2.1.1.3.1 */
									// Start line: 2974
									// Start offset: 0x000FC01C
									// Variables:
								// 		struct LINE_F2 strF2; // stack offset -128
								// 		struct LINE_F4 strF4; // stack offset -160
								/* end block 1.2.1.2.1.1.3.1 */
								// End offset: 0x000FC0CC
								// End Line: 2974
							/* end block 1.2.1.2.1.1.3 */
							// End offset: 0x000FC0CC
							// End Line: 2974
						/* end block 1.2.1.2.1.1 */
						// End offset: 0x000FC0CC
						// End Line: 2977
					/* end block 1.2.1.2.1 */
					// End offset: 0x000FC0CC
					// End Line: 2977
				/* end block 1.2.1.2 */
				// End offset: 0x000FC138
				// End Line: 2993
			/* end block 1.2.1 */
			// End offset: 0x000FC278
			// End Line: 3019

			/* begin block 1.2.2 */
				// Start line: 3022
				// Start offset: 0x000FC280

				/* begin block 1.2.2.1 */
					// Start line: 3026
					// Start offset: 0x000FC2B0

					/* begin block 1.2.2.1.1 */
						// Start line: 3027
						// Start offset: 0x000FC2F0

						/* begin block 1.2.2.1.1.1 */
							// Start line: 3030
							// Start offset: 0x000FC2FC

							/* begin block 1.2.2.1.1.1.1 */
								// Start line: 2787
								// Start offset: 0x000FC390
								// Variables:
							// 		struct DISPMAN *this; // $s5
							// 		int y; // $s3

								/* begin block 1.2.2.1.1.1.1.1 */
									// Start line: 2787
									// Start offset: 0x000FC390
									// Variables:
								// 		struct LINE_F2 strF2; // stack offset -128
								// 		struct LINE_F4 strF4; // stack offset -160
								/* end block 1.2.2.1.1.1.1.1 */
								// End offset: 0x000FC390
								// End Line: 2787
							/* end block 1.2.2.1.1.1.1 */
							// End offset: 0x000FC390
							// End Line: 2787

							/* begin block 1.2.2.1.1.1.2 */
								// Start line: 2787
								// Start offset: 0x000FC474
								// Variables:
							// 		struct DISPMAN *this; // $s5
							// 		int y; // $s3

								/* begin block 1.2.2.1.1.1.2.1 */
									// Start line: 2787
									// Start offset: 0x000FC474
									// Variables:
								// 		struct LINE_F2 strF2; // stack offset -128
								// 		struct LINE_F4 strF4; // stack offset -160
								/* end block 1.2.2.1.1.1.2.1 */
								// End offset: 0x000FC474
								// End Line: 2787
							/* end block 1.2.2.1.1.1.2 */
							// End offset: 0x000FC474
							// End Line: 2787
						/* end block 1.2.2.1.1.1 */
						// End offset: 0x000FC540
						// End Line: 3052

						/* begin block 1.2.2.1.1.2 */
							// Start line: 3069
							// Start offset: 0x000FC650
							// Variables:
						// 		struct DISPMAN *this; // $s5
						// 		int y; // $s3
						// 		int w; // $v0

							/* begin block 1.2.2.1.1.2.1 */
								// Start line: 3069
								// Start offset: 0x000FC650
								// Variables:
							// 		struct LINE_F2 strF2; // stack offset -128
							// 		struct LINE_F4 strF4; // stack offset -160
							/* end block 1.2.2.1.1.2.1 */
							// End offset: 0x000FC650
							// End Line: 3069
						/* end block 1.2.2.1.1.2 */
						// End offset: 0x000FC650
						// End Line: 3069

						/* begin block 1.2.2.1.1.3 */
							// Start line: 3094
							// Start offset: 0x000FC848
							// Variables:
						// 		struct DISPMAN *this; // $s5
						// 		int y; // $s3
						// 		int w; // $v0

							/* begin block 1.2.2.1.1.3.1 */
								// Start line: 3094
								// Start offset: 0x000FC848
								// Variables:
							// 		struct LINE_F2 strF2; // stack offset -128
							// 		struct LINE_F4 strF4; // stack offset -160
							/* end block 1.2.2.1.1.3.1 */
							// End offset: 0x000FC8E8
							// End Line: 3094
						/* end block 1.2.2.1.1.3 */
						// End offset: 0x000FC8E8
						// End Line: 3094
					/* end block 1.2.2.1.1 */
					// End offset: 0x000FC8F0
					// End Line: 3099
				/* end block 1.2.2.1 */
				// End offset: 0x000FC8F0
				// End Line: 3099
			/* end block 1.2.2 */
			// End offset: 0x000FC8F0
			// End Line: 3099
		/* end block 1.2 */
		// End offset: 0x000FC8F0
		// End Line: 3099
	/* end block 1 */
	// End offset: 0x000FC950
	// End Line: 3107

	/* begin block 2 */
		// Start line: 6380
	/* end block 2 */
	// End Line: 6381

/* WARNING: Could not reconcile some variable overlaps */

uint FUN_MCARD__000fb304(undefined4 *param_1,int param_2,char *param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  size_t sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  char cVar12;
  undefined uVar13;
  uint *puVar14;
  char cVar15;
  undefined uVar16;
  short sVar17;
  undefined4 *puVar18;
  char cVar19;
  undefined uVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  undefined4 local_130;
  uint local_12c;
  short local_128;
  short local_126;
  undefined2 local_124;
  undefined2 local_122;
  char acStack288 [128];
  undefined4 local_a0;
  uint local_9c;
  short local_98;
  short local_96;
  undefined4 local_94;
  uint local_90;
  short local_8c;
  short local_8a;
  undefined4 local_88;
  uint local_84;
  undefined4 local_80;
  uint local_7c;
  short local_78;
  short local_76;
  short local_74;
  undefined2 local_72;
  undefined2 local_70;
  short local_6e;
  short local_6c;
  short local_6a;
  short local_68;
  short local_66;
  undefined2 local_64;
  short local_62;
  undefined auStack88 [4];
  undefined local_54;
  undefined local_53;
  undefined local_52;
  undefined2 local_50;
  short local_4e;
  undefined2 local_4c;
  short local_4a;
  int local_48;
  int local_44;
  int local_40;
  uint local_3c;
  uint *local_38;
  int local_34;
  uint local_30;
  int local_2c;
  
  bVar1 = false;
  iVar23 = (int)*(short *)((int)param_1 + 0x231e);
  iVar21 = 0;
  local_44 = 0;
  sVar5 = strlen(param_3);
  while( true ) {
    iVar6 = FUN_MCARD__000fce00(param_1,param_3 + iVar21,0,0x1b8);
    iVar21 = iVar21 + iVar6;
    if ((int)sVar5 <= iVar21) break;
    iVar23 = iVar23 + ((int)*(short *)((int)param_1 + 0x231e) * 0xb) / 10;
  }
  if (param_2 != 6) {
    iVar23 = iVar23 + ((int)*(short *)((int)param_1 + 0x231e) * 0xb) / 10;
  }
  iVar21 = 0;
  local_38 = param_1 + 0x88f;
  iVar6 = (int)param_1[0x66] / 2 - iVar23 / 2;
  local_48 = iVar6 + -4;
  while( true ) {
    iVar7 = FUN_MCARD__000fce00(param_1,param_3 + iVar21,0,0x1b8);
    iVar8 = FUN_MCARD__000fe834(param_1,param_3 + iVar21,0xff,iVar6,0,iVar7,0x80,0x80,0x80,0);
    if (local_44 < iVar8) {
      local_44 = iVar8;
    }
    iVar21 = iVar21 + iVar7;
    if ((int)sVar5 <= iVar21) break;
    iVar6 = iVar6 + ((int)*(short *)((int)param_1 + 0x231e) * 0xb) / 10;
  }
  if (param_2 == 4) {
    iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
    if (iVar21 < 0) {
      iVar21 = iVar21 + 7;
    }
    iVar6 = iVar6 + (iVar21 >> 3);
    sprintf(acStack288,(char *)&PTR_DAT_MCARD__000f30d0,DAT_MCARD__0010ed2c);
    iVar21 = FUN_MCARD__000fe834(param_1,acStack288,0xff,iVar6,0,1000,0x80,0x80,0x80,0);
    bVar2 = local_44 < iVar21;
LAB_MCARD__000fb790:
    if (bVar2) {
      local_44 = iVar21;
    }
  }
  else {
    if (param_2 < 5) {
      if (param_2 == 3) {
        iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
        if (iVar21 < 0) {
          iVar21 = iVar21 + 7;
        }
        iVar6 = iVar6 + (iVar21 >> 3);
        sprintf(acStack288,(char *)&PTR_DAT_MCARD__000f30d0,DAT_MCARD__0010ed10);
        iVar21 = FUN_MCARD__000fcc54(param_1,acStack288,0,0xff);
        sprintf(acStack288,(char *)&PTR_DAT_MCARD__000f30d0,DAT_MCARD__0010ed04);
        iVar7 = FUN_MCARD__000fcc54(param_1,acStack288,0,0xff);
        iVar7 = iVar21 + 0x14 + iVar7;
        if (local_44 < iVar7) {
          local_44 = iVar7;
        }
        sprintf(acStack288,(char *)&PTR_DAT_MCARD__000f30d0,DAT_MCARD__0010ed10);
        iVar21 = local_44;
        if (local_44 < 0) {
          iVar21 = local_44 + 3;
        }
        FUN_MCARD__000fe834(param_1,acStack288,0xff - (iVar21 >> 2),iVar6,0,1000,0x80,0x80,0x80,0);
        sprintf(acStack288,(char *)&PTR_DAT_MCARD__000f30d0,DAT_MCARD__0010ed04);
        FUN_MCARD__000fe834(param_1,acStack288,(iVar21 >> 2) + 0xff,iVar6,0,1000,0x80,0x80,0x80,0);
      }
    }
    else {
      if (param_2 == 7) {
        iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
        if (iVar21 < 0) {
          iVar21 = iVar21 + 7;
        }
        iVar6 = iVar6 + (iVar21 >> 3);
        sprintf(acStack288,(char *)&PTR_DAT_MCARD__000f30d0,DAT_MCARD__0010ed04);
        iVar21 = FUN_MCARD__000fe834(param_1,acStack288,0xff,iVar6,0,1000,0x80,0x80,0x80,0);
        bVar2 = local_44 < iVar21;
        goto LAB_MCARD__000fb790;
      }
    }
  }
  puVar14 = local_38;
  local_2c = local_44 >> 0x1f;
  local_30 = local_44 + 0x20;
  local_130 = CONCAT22((short)local_48,0xf3 - (short)(local_44 / 2));
  local_12c = local_30 & 0xffff | (uint)(ushort)((short)iVar23 + 0x14) << 0x10;
  local_a0 = local_130;
  local_9c = local_12c;
  iVar21 = 6;
  FUN_MCARD__000fa97c(param_1,local_130,local_12c);
  *param_1 = 1;
  FUN_MCARD__000fa174(param_1);
  puVar18 = param_1 + 0x48;
  *param_1 = 0;
  local_94 = local_130;
  local_90 = local_12c;
  do {
    local_88 = local_94;
    local_84 = local_90;
    local_80 = *puVar18;
    local_7c = puVar18[1];
    puVar18 = puVar18 + 2;
    iVar23 = FUN_MCARD__000f9fac(param_1,local_94,local_90,local_80,local_7c);
    iVar21 = iVar21 + -1;
    *puVar14 = (uint)(*puVar14 != 0 || iVar23 != 0);
    puVar14 = puVar14 + 1;
  } while (-1 < iVar21);
  uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
  local_40 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
  iVar21 = FUN_MCARD__001000d0(param_1[0x1179]);
  sVar4 = (short)iVar6;
  if (iVar21 != 0) {
    sVar3 = (short)((int)local_30 / 2);
    sVar17 = 0x108 - sVar3;
    local_34 = local_44 + 0x16;
    DAT_MCARD__0010ec7c = (short)local_34;
    iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
    if (iVar21 < 0) {
      iVar21 = iVar21 + 7;
    }
    DAT_MCARD__0010ec7e = (short)(iVar21 >> 3);
    DAT_MCARD__0010ec78 = sVar17;
    DAT_MCARD__0010ec7a = sVar4;
    if (param_2 == 3) {
      iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
      if (iVar21 < 0) {
        iVar21 = iVar21 + 7;
      }
      SetLineF4(&local_78);
      SetLineF2(auStack88);
      local_74 = 0x3737;
      local_72 = CONCAT11(local_72._1_1_,0x37);
      local_54 = 0x37;
      local_53 = 0x37;
      local_52 = 0x37;
      SetSemiTrans(&local_78,0);
      SetSemiTrans(auStack88,0);
      local_6c = sVar3 + 0xfd;
      local_66 = sVar4 + (short)(iVar21 >> 3);
      local_70 = 0x103;
      local_64 = 0x103;
      local_50 = 0x103;
      local_4c = 0x103;
      local_6e = sVar4;
      local_6a = sVar4;
      local_68 = local_6c;
      local_62 = local_66;
      local_4e = local_66;
      local_4a = sVar4;
      DrawPrim(&local_78);
      DrawPrim(auStack88);
      DrawSync(0);
      iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
      if (iVar21 < 0) {
        iVar21 = iVar21 + 7;
      }
      SetLineF4(&local_a0);
      SetLineF2(&local_80);
      local_9c = local_9c & 0xff000000 | 0x373737;
      local_7c = local_7c & 0xff000000 | 0x373737;
      SetSemiTrans(&local_a0,0);
      SetSemiTrans(&local_80,0);
      local_8a = sVar4 + (short)(iVar21 >> 3);
      local_98 = 0x102;
      local_94 = CONCAT22(sVar4,0x108 - sVar3);
      local_90 = CONCAT22(local_8a,0x108 - sVar3);
      local_8c = 0x102;
      local_78 = 0x102;
      local_74 = 0x102;
      local_96 = sVar4;
      local_76 = local_8a;
      local_72 = sVar4;
      DrawPrim(&local_a0);
      DrawPrim(&local_80);
      DrawSync(0);
    }
    else {
      if (param_2 == 4) {
        iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
        if (iVar21 < 0) {
          iVar21 = iVar21 + 7;
        }
        SetLineF4(&local_a0);
        SetLineF2(&local_80);
        local_9c = local_9c & 0xff000000 | 0x808080;
        local_7c = local_7c & 0xff000000 | 0x808080;
        SetSemiTrans(&local_a0,0);
        SetSemiTrans(&local_80,0);
        local_8a = sVar4 + (short)(iVar21 >> 3);
        sVar3 = sVar17 + (short)local_34;
        local_94 = CONCAT22(sVar4,sVar3);
        local_90 = CONCAT22(local_8a,sVar3);
        local_98 = sVar17;
        local_96 = sVar4;
        local_8c = sVar17;
        local_78 = sVar17;
        local_76 = local_8a;
        local_74 = sVar17;
        local_72 = sVar4;
        DrawPrim(&local_a0);
        DrawPrim(&local_80);
        DrawSync(0);
      }
    }
    if (1 < param_2 - 3U) {
      return 0;
    }
    do {
      sVar3 = FUN_MCARD__000fecc0(param_1[0x1179],0);
      uVar22 = SEXT24(sVar3);
      if ((uVar22 & DAT_MCARD__0010ec8a) != 0) {
        iVar21 = FUN_MCARD__00100158(param_1[0x1179]);
        iVar23 = local_44 - local_2c >> 1;
        if ((((0x102 - iVar23 < iVar21) &&
             (iVar21 = FUN_MCARD__00100158(param_1[0x1179]), iVar21 < iVar23 + 0x102)) &&
            (iVar21 = FUN_MCARD__0010016c(param_1[0x1179]), iVar6 < iVar21)) &&
           (iVar21 = FUN_MCARD__0010016c(param_1[0x1179]), iVar21 < iVar6 + 0x1e))
        goto LAB_MCARD__000fc1e0;
      }
      uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
      iVar21 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
      if (((iVar21 != local_40) || (iVar21 = FUN_MCARD__000fff48(param_1[0x1179]), iVar21 != 0)) &&
         (param_4 == 0)) goto LAB_MCARD__000fc1e0;
      FUN_MCARD__000ffea0(param_1[0x1179]);
      DrawSync(0);
      local_128 = *(short *)(param_1 + 0xa6);
      local_126 = *(short *)(param_1 + 0xa7);
      local_124 = 0x10;
      local_122 = 0x10;
      LoadImage(&local_128,param_1 + 0xa8);
      DrawSync(0);
      bVar1 = false;
      local_128 = FUN_MCARD__00100158(param_1[0x1179]);
      local_126 = FUN_MCARD__0010016c(param_1[0x1179]);
      param_1[0xa7] = (int)local_126;
      param_1[0xa6] = (int)local_128;
      StoreImage(&local_128,param_1 + 0xa8);
      DrawSync(0);
      iVar21 = FUN_MCARD__00100158(param_1[0x1179]);
      if (((DAT_MCARD__0010ec78 < iVar21) &&
          (iVar21 = FUN_MCARD__00100158(param_1[0x1179]),
          iVar21 < (int)DAT_MCARD__0010ec78 + (int)DAT_MCARD__0010ec7c)) &&
         (iVar21 = FUN_MCARD__0010016c(param_1[0x1179]), DAT_MCARD__0010ec7a < iVar21)) {
        iVar21 = FUN_MCARD__0010016c(param_1[0x1179]);
        bVar1 = iVar21 < (int)DAT_MCARD__0010ec7a + (int)DAT_MCARD__0010ec7e;
      }
      iVar21 = FUN_MCARD__00100158(param_1[0x1179]);
      bVar2 = iVar21 < 0x102;
      if (param_2 == 3) {
        iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
        iVar23 = (int)local_30 / 2;
        if (iVar21 < 0) {
          iVar21 = iVar21 + 7;
        }
        cVar19 = (bVar1 && !bVar2) * -0x38 + '7';
        cVar15 = (bVar1 && !bVar2) * -0x38 + '7';
        cVar12 = (bVar1 && !bVar2) * -0x38 + '7';
        SetLineF4(&local_a0);
        SetLineF2(&local_80);
        local_9c._0_2_ = CONCAT11(cVar15,cVar19);
        local_9c._0_3_ = CONCAT12(cVar12,(undefined2)local_9c);
        local_9c = local_9c & 0xff000000 | (uint)(uint3)local_9c;
        local_7c._0_2_ = CONCAT11(cVar15,cVar19);
        local_7c._0_3_ = CONCAT12(cVar12,(undefined2)local_7c);
        local_7c = local_7c & 0xff000000 | (uint)(uint3)local_7c;
        SetSemiTrans(&local_a0,0);
        SetSemiTrans(&local_80,0);
        sVar3 = (short)iVar23;
        sVar17 = sVar3 + 0xfd;
        local_8a = sVar4 + (short)(iVar21 >> 3);
        local_98 = 0x103;
        local_94 = CONCAT22(sVar4,sVar17);
        local_90 = CONCAT22(local_8a,sVar17);
        local_8c = 0x103;
        local_78 = 0x103;
        local_74 = 0x103;
        local_96 = sVar4;
        local_76 = local_8a;
        local_72 = sVar4;
        DrawPrim(&local_a0);
        DrawPrim(&local_80);
        DrawSync(0);
        iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
        if (iVar21 < 0) {
          iVar21 = iVar21 + 7;
        }
        cVar19 = (bVar1 && bVar2) * -0x38 + '7';
        cVar15 = (bVar1 && bVar2) * -0x38 + '7';
        cVar12 = (bVar1 && bVar2) * -0x38 + '7';
        SetLineF4(&local_a0);
        SetLineF2(&local_80);
        local_9c._0_2_ = CONCAT11(cVar15,cVar19);
        local_9c._0_3_ = CONCAT12(cVar12,(undefined2)local_9c);
        local_9c = local_9c & 0xff000000 | (uint)(uint3)local_9c;
        local_7c._0_2_ = CONCAT11(cVar15,cVar19);
        local_7c._0_3_ = CONCAT12(cVar12,(undefined2)local_7c);
        local_7c = local_7c & 0xff000000 | (uint)(uint3)local_7c;
        SetSemiTrans(&local_a0,0);
        SetSemiTrans(&local_80,0);
        sVar3 = 0x108 - sVar3;
        local_8a = sVar4 + (short)(iVar21 >> 3);
        local_98 = 0x102;
        local_94 = CONCAT22(sVar4,sVar3);
        local_90 = CONCAT22(local_8a,sVar3);
        local_8c = 0x102;
        local_78 = 0x102;
        local_74 = 0x102;
        local_96 = sVar4;
        local_76 = local_8a;
        local_72 = sVar4;
        DrawPrim(&local_a0);
        DrawPrim(&local_80);
        DrawSync(0);
      }
      else {
        if (param_2 == 4) {
          iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
          sVar3 = 0x108 - (short)((int)local_30 / 2);
          if (iVar21 < 0) {
            iVar21 = iVar21 + 7;
          }
          SetLineF4(&local_a0);
          SetLineF2(&local_80);
          local_9c = local_9c & 0xff000000 | 0x10101;
          local_7c = local_7c & 0xff000000 | 0x10101;
          SetSemiTrans(&local_a0,0);
          SetSemiTrans(&local_80,0);
          local_8a = sVar4 + (short)(iVar21 >> 3);
          sVar17 = sVar3 + (short)local_34;
          local_94 = CONCAT22(sVar4,sVar17);
          local_90 = CONCAT22(local_8a,sVar17);
          local_98 = sVar3;
          local_96 = sVar4;
          local_8c = sVar3;
          local_78 = sVar3;
          local_76 = local_8a;
          local_74 = sVar3;
          local_72 = sVar4;
          DrawPrim(&local_a0);
          DrawPrim(&local_80);
          DrawSync(0);
        }
      }
      uVar9 = FUN_MCARD__00100158(param_1[0x1179]);
      uVar10 = FUN_MCARD__0010016c(param_1[0x1179]);
      FUN_MCARD__000facd4(param_1,param_1 + 0x112b,uVar9,uVar10,0x80,0x80,0x80,0);
      if ((DAT_MCARD__0010ee08 & 0x400) != 0) {
        FUN_MCARD__00100180(param_1[0x1179]);
      }
      VSync(0);
    } while( true );
  }
  do {
    uVar22 = FUN_MCARD__000fecc0(param_1[0x1179],0);
  } while ((uVar22 & (ushort)(DAT_MCARD__0010ec96 | DAT_MCARD__0010ec8a | DAT_MCARD__0010ec94)) != 0
          );
  if (param_2 == 4) {
    iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
    local_98 = 0x108 - (short)((int)local_30 / 2);
    if (iVar21 < 0) {
      iVar21 = iVar21 + 7;
    }
    SetLineF4(&local_a0);
    SetLineF2(&local_80);
    local_9c = local_9c & 0xff000000 | 0xffffff;
    local_7c = local_7c & 0xff000000 | 0xffffff;
    SetSemiTrans(&local_a0,0);
    SetSemiTrans(&local_80,0);
    local_8a = sVar4 + (short)(iVar21 >> 3);
    sVar3 = local_98 + (short)local_44 + 0x16;
    local_94 = CONCAT22(sVar4,sVar3);
    local_90 = CONCAT22(local_8a,sVar3);
    local_96 = sVar4;
    local_8c = local_98;
    local_78 = local_98;
    local_76 = local_8a;
    local_74 = local_98;
    local_72 = sVar4;
    DrawPrim(&local_a0);
    DrawPrim(&local_80);
    DrawSync(0);
    while( true ) {
      sVar4 = FUN_MCARD__000fecc0(param_1[0x1179],0);
      uVar22 = SEXT24(sVar4);
      if ((uVar22 & DAT_MCARD__0010ec8a) != 0) break;
      uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
      iVar21 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
      if (((iVar21 != local_40) || (iVar21 = FUN_MCARD__000fff48(param_1[0x1179]), iVar21 != 0)) &&
         (param_4 == 0)) break;
      FUN_MCARD__000ffea0(param_1[0x1179]);
      if ((DAT_MCARD__0010ee08 & 0x400) != 0) {
        FUN_MCARD__00100180(param_1[0x1179]);
      }
      VSync(0);
    }
    libcman_ConfirmSound();
    if ((uVar22 != 0) || ((DAT_MCARD__0010ec8a & 1) == 0)) {
      uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
      iVar21 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
      if ((iVar21 == local_40) && (iVar21 = FUN_MCARD__000fff48(param_1[0x1179]), iVar21 == 0))
      goto LAB_MCARD__000fc8f0;
    }
  }
  else {
    if (4 < param_2) {
      if (param_2 != 7) {
        return 0;
      }
      iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
      local_98 = 0x108 - (short)((int)local_30 / 2);
      if (iVar21 < 0) {
        iVar21 = iVar21 + 7;
      }
      SetLineF4(&local_a0);
      SetLineF2(&local_80);
      local_9c = local_9c & 0xff000000 | 0xffffff;
      local_7c = local_7c & 0xff000000 | 0xffffff;
      SetSemiTrans(&local_a0,0);
      SetSemiTrans(&local_80,0);
      local_8a = sVar4 + (short)(iVar21 >> 3);
      sVar3 = local_98 + (short)local_44 + 0x16;
      local_94 = CONCAT22(sVar4,sVar3);
      local_90 = CONCAT22(local_8a,sVar3);
      local_96 = sVar4;
      local_8c = local_98;
      local_78 = local_98;
      local_76 = local_8a;
      local_74 = local_98;
      local_72 = sVar4;
      DrawPrim(&local_a0);
      DrawPrim(&local_80);
      DrawSync(0);
      return 0;
    }
    if (param_2 != 3) {
      return 0;
    }
    local_3c = local_30;
    while( true ) {
      sVar3 = FUN_MCARD__000fecc0(param_1[0x1179],0);
      uVar22 = SEXT24(sVar3);
      if ((uVar22 & DAT_MCARD__0010ec8a) != 0) break;
      uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
      iVar21 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
      if (((iVar21 != local_40) || (iVar21 = FUN_MCARD__000fff48(param_1[0x1179]), iVar21 != 0)) &&
         (param_4 == 0)) break;
      FUN_MCARD__000ffea0(param_1[0x1179]);
      if ((DAT_MCARD__0010ee08 & 0x400) != 0) {
        FUN_MCARD__00100180(param_1[0x1179]);
      }
      VSync(0);
      iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
      iVar23 = (int)local_3c / 2;
      if (iVar21 < 0) {
        iVar21 = iVar21 + 7;
      }
      uVar20 = 0;
      if (!bVar1) {
        uVar20 = 0xff;
      }
      uVar16 = 0;
      if (!bVar1) {
        uVar16 = 0xff;
      }
      uVar13 = 0;
      if (!bVar1) {
        uVar13 = 0xff;
      }
      SetLineF4(&local_a0);
      SetLineF2(&local_80);
      local_9c._0_2_ = CONCAT11(uVar16,uVar20);
      local_9c._0_3_ = CONCAT12(uVar13,(undefined2)local_9c);
      local_9c = local_9c & 0xff000000 | (uint)(uint3)local_9c;
      local_7c._0_2_ = CONCAT11(uVar16,uVar20);
      local_7c._0_3_ = CONCAT12(uVar13,(undefined2)local_7c);
      local_7c = local_7c & 0xff000000 | (uint)(uint3)local_7c;
      SetSemiTrans(&local_a0,0);
      SetSemiTrans(&local_80,0);
      sVar3 = (short)iVar23;
      sVar17 = sVar3 + 0xfd;
      local_8a = sVar4 + (short)(iVar21 >> 3);
      local_98 = 0x103;
      local_94 = CONCAT22(sVar4,sVar17);
      local_90 = CONCAT22(local_8a,sVar17);
      local_8c = 0x103;
      local_78 = 0x103;
      local_74 = 0x103;
      local_96 = sVar4;
      local_76 = local_8a;
      local_72 = sVar4;
      DrawPrim(&local_a0);
      DrawPrim(&local_80);
      DrawSync(0);
      iVar21 = (int)*(short *)((int)param_1 + 0x231e) * 0xb;
      if (iVar21 < 0) {
        iVar21 = iVar21 + 7;
      }
      uVar20 = 0;
      if (bVar1) {
        uVar20 = 0xff;
      }
      uVar16 = 0;
      if (bVar1) {
        uVar16 = 0xff;
      }
      uVar13 = 0;
      if (bVar1) {
        uVar13 = 0xff;
      }
      SetLineF4(&local_a0);
      SetLineF2(&local_80);
      local_9c._0_2_ = CONCAT11(uVar16,uVar20);
      local_9c._0_3_ = CONCAT12(uVar13,(undefined2)local_9c);
      local_9c = local_9c & 0xff000000 | (uint)(uint3)local_9c;
      local_7c._0_2_ = CONCAT11(uVar16,uVar20);
      local_7c._0_3_ = CONCAT12(uVar13,(undefined2)local_7c);
      local_7c = local_7c & 0xff000000 | (uint)(uint3)local_7c;
      SetSemiTrans(&local_a0,0);
      SetSemiTrans(&local_80,0);
      sVar3 = 0x108 - sVar3;
      local_8a = sVar4 + (short)(iVar21 >> 3);
      local_98 = 0x102;
      local_94 = CONCAT22(sVar4,sVar3);
      local_90 = CONCAT22(local_8a,sVar3);
      local_8c = 0x102;
      local_78 = 0x102;
      local_74 = 0x102;
      local_96 = sVar4;
      local_76 = local_8a;
      local_72 = sVar4;
      DrawPrim(&local_a0);
      DrawPrim(&local_80);
      DrawSync(0);
      if (((uVar22 & 0x80) != 0) && (!bVar1)) {
        bVar1 = true;
        libcman_SelectSound();
      }
      if (((uVar22 & 0x20) != 0) && (bVar1)) {
        bVar1 = false;
        libcman_SelectSound();
      }
    }
    if ((uVar22 != 0) || ((DAT_MCARD__0010ec8a & 1) == 0)) {
      uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
      iVar21 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
      if ((iVar21 == local_40) &&
         ((iVar21 = FUN_MCARD__000fff48(param_1[0x1179]), iVar21 == 0 && (bVar1))))
      goto LAB_MCARD__000fc8f0;
    }
  }
LAB_MCARD__000fc804:
  uVar22 = SEXT24(DAT_MCARD__0010ec8c);
LAB_MCARD__000fc8f0:
  do {
    uVar11 = FUN_MCARD__000fecc0(param_1[0x1179],0);
  } while ((DAT_MCARD__0010ec8a & uVar11) != 0);
  FUN_MCARD__000fa174(param_1);
  return uVar22;
LAB_MCARD__000fc1e0:
  uVar9 = FUN_MCARD__00100340(param_1[0x1179]);
  iVar21 = FUN_MCARD__001003b0(param_1[0x1179],uVar9);
  if (((iVar21 == local_40) && (iVar21 = FUN_MCARD__000fff48(param_1[0x1179]), iVar21 == 0)) ||
     (param_4 != 0)) {
    if (param_2 == 3) {
      iVar21 = FUN_MCARD__00100158(param_1[0x1179]);
      if (iVar21 < 0x103) {
        uVar22 = SEXT24((short)DAT_MCARD__0010ec8a);
      }
      else {
        uVar22 = SEXT24(DAT_MCARD__0010ec8c);
      }
    }
    libcman_ConfirmSound();
    goto LAB_MCARD__000fc8f0;
  }
  goto LAB_MCARD__000fc804;
}



// decompiled code
// original method signature: 
// struct RECT /*$ra*/ ProgressBox__7DISPMANPci(struct DISPMAN *this /*$s3*/, char *text /*$fp*/, int progress /*stack 12*/)
 // line 3112, offset 0x000fc950
	/* begin block 1 */
		// Start line: 3113
		// Start offset: 0x000FC950
		// Variables:
	// 		int boxHeight; // $s4
	// 		int boxTop; // stack offset -48
	// 		int maxTextLen; // $s7
	// 		int textLen; // $v1
	// 		int textY; // $s1
	// 		int lineCount; // $s0
	// 		struct RECT darkRect; // stack offset -192
	// 		char textBuffer[128]; // stack offset -184
	// 		int n; // $s2
	// 		int messCount; // $s6
	/* end block 1 */
	// End offset: 0x000FCB08
	// End Line: 3151

	/* begin block 2 */
		// Start line: 7202
	/* end block 2 */
	// End Line: 7203

undefined4 *
FUN_MCARD__000fc950(undefined4 *param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  short sVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 local_c0;
  undefined4 local_bc;
  
  iVar8 = 0;
  iVar6 = 0;
  iVar7 = (int)*(short *)((int)param_2 + 0x231e);
  sVar2 = strlen(param_3);
  while( true ) {
    iVar3 = FUN_MCARD__000fce00(param_2,param_3 + iVar6,0,0x1b8);
    iVar6 = iVar6 + iVar3;
    if ((int)sVar2 <= iVar6) break;
    iVar7 = iVar7 + ((int)*(short *)((int)param_2 + 0x231e) * 0xb) / 10;
  }
  iVar3 = 0;
  iVar7 = iVar7 + ((int)*(short *)((int)param_2 + 0x231e) * 0xb) / 10;
  iVar6 = (int)param_2[0x66] / 2 - iVar7 / 2;
  sVar1 = (short)iVar6;
  while( true ) {
    iVar4 = FUN_MCARD__000fce00(param_2,param_3 + iVar3,0,0x1b8);
    iVar5 = FUN_MCARD__000fe834(param_2,param_3 + iVar3,0xff,iVar6,0,iVar4,0x80,0x80,0x80,0);
    if (iVar8 < iVar5) {
      iVar8 = iVar5;
    }
    iVar3 = iVar3 + iVar4;
    if ((int)sVar2 <= iVar3) break;
    iVar6 = iVar6 + ((int)*(short *)((int)param_2 + 0x231e) * 0xb) / 10;
  }
  FUN_MCARD__000faed0(param_2,0xff,
                      iVar6 + ((int)*(short *)((int)param_2 + 0x231e) * 0xb) / 10 +
                      ((int)*(short *)((int)param_2 + 0x231e) * 7) / 10,0x1a,param_4,0xff,0xff,0xff,
                      0xf);
  local_bc = CONCAT22((short)iVar7 + 0x10,(short)iVar8 + 0x20);
  local_c0 = CONCAT22(sVar1 + -4,0xf3 - (short)(iVar8 / 2));
  FUN_MCARD__000fa97c(param_2,local_c0,local_bc);
  *param_2 = 1;
  FUN_MCARD__000fa174(param_2);
  *param_2 = 0;
  *param_1 = local_c0;
  param_1[1] = local_bc;
  return param_1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ write_mess_c__7DISPMANPciiiiiiii(struct DISPMAN *this /*$s0*/, char *mesPtr /*$s1*/, int x /*stack 8*/, int y /*$s4*/, int font /*stack 16*/, int maxChars /*stack 20*/, int r /*stack 24*/, int g /*stack 28*/, int b /*stack 32*/, int trans /*stack 36*/)
 // line 3172, offset 0x000fe834
	/* begin block 1 */
		// Start line: 3173
		// Start offset: 0x000FE834
		// Variables:
	// 		int w; // $s0
	/* end block 1 */
	// End offset: 0x000FE908
	// End Line: 3178

	/* begin block 2 */
		// Start line: 11144
	/* end block 2 */
	// End Line: 11145

int FUN_MCARD__000fe834(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                       undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                       undefined4 param_9,undefined4 param_10)

{
  int iVar1;
  
  iVar1 = FUN_MCARD__000fcc54(param_1,param_2,param_5,param_6);
  FUN_MCARD__000fd000(param_1,param_2,param_3 - iVar1 / 2,param_4,param_5,param_6,param_7,param_8,
                      param_9,param_10);
  return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ message_width__7DISPMANPcii(struct DISPMAN *this /*$s3*/, char *mesPtr /*$s1*/, int font /*$a2*/, int maxChars /*$s6*/)
 // line 3182, offset 0x000fcc54
	/* begin block 1 */
		// Start line: 3183
		// Start offset: 0x000FCC54
		// Variables:
	// 		char c; // $a1
	// 		int fRef; // $s0
	// 		int w; // $s2
	// 		int n; // $s5

		/* begin block 1.1 */
			// Start line: 3183
			// Start offset: 0x000FCC54

			/* begin block 1.1.1 */
				// Start line: 3189
				// Start offset: 0x000FCC98

				/* begin block 1.1.1.1 */
					// Start line: 3183
					// Start offset: 0x000FCC98
					// Variables:
				// 		short *kanjiStringPtr; // $s1
				// 		int maxChars; // $s6

					/* begin block 1.1.1.1.1 */
						// Start line: 3183
						// Start offset: 0x000FCC98
						// Variables:
					// 		int totalLen; // $a1
					// 		short textBuffer[128]; // stack offset -296
					/* end block 1.1.1.1.1 */
					// End offset: 0x000FCD04
					// End Line: 3183
				/* end block 1.1.1.1 */
				// End offset: 0x000FCD04
				// End Line: 3183
			/* end block 1.1.1 */
			// End offset: 0x000FCD0C
			// End Line: 3190
		/* end block 1.1 */
		// End offset: 0x000FCE00
		// End Line: 3209
	/* end block 1 */
	// End offset: 0x000FCE00
	// End Line: 3209

	/* begin block 2 */
		// Start line: 7380
	/* end block 2 */
	// End Line: 7381

	/* begin block 3 */
		// Start line: 7395
	/* end block 3 */
	// End Line: 7396

int FUN_MCARD__000fcc54(int param_1,byte *param_2,int param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  size_t sVar3;
  int iVar4;
  short *psVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  short asStack298 [129];
  
  iVar8 = 0;
  if (*(int *)(param_1 + 4) == 9) {
    memset(asStack298 + 1,0,0x100);
    FUN_MCARD__000f512c(asStack298 + 1,param_2);
    sVar3 = strlen((char *)(asStack298 + 1));
    uVar7 = sVar3 >> 1;
    if (param_4 / 2 < (int)(sVar3 >> 1)) {
      uVar7 = param_4 / 2;
    }
    psVar5 = asStack298 + uVar7;
    do {
      uVar6 = uVar7 - 1;
      if (*psVar5 != 0x4081) break;
      psVar5 = psVar5 + -1;
      uVar7 = uVar6;
    } while (0 < (int)uVar6);
    iVar8 = uVar7 << 4;
  }
  else {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if ((bVar1 != 0) && (iVar9 = 1, 0 < param_4)) {
      do {
        uVar6 = FUN_MCARD__000fd410(param_1,(uint)bVar1,0);
        uVar7 = uVar6;
        if (uVar6 == 100) {
          uVar7 = 0xff;
          iVar8 = iVar8 + *(short *)(&DAT_0000233c + param_3 * 0x4c0 + param_1);
        }
        if ((uVar6 < 4) && (iVar4 = FUN_MCARD__000fd410(param_1,(uint)param_2[-2],1), iVar4 == 0x29)
           ) {
          uVar7 = uVar7 + 0x41;
        }
        if (uVar7 != 0xff) {
          iVar8 = iVar8 + 2 +
                  (int)*(short *)(&DAT_0000226c + param_1 + uVar7 * 0x10 + param_3 * 0x4c0);
        }
        bVar1 = *param_2;
        param_2 = param_2 + 1;
      } while ((bVar1 != 0) && (bVar2 = iVar9 < param_4, iVar9 = iVar9 + 1, bVar2));
    }
  }
  return iVar8;
}



// decompiled code
// original method signature: 
// int /*$ra*/ justify_mess__7DISPMANPcii(struct DISPMAN *this /*$fp*/, char *messPtr /*$s3*/, int font /*stack 8*/, int maxLineLength /*$s7*/)
 // line 3214, offset 0x000fce00
	/* begin block 1 */
		// Start line: 3215
		// Start offset: 0x000FCE00
		// Variables:
	// 		char c; // $s0
	// 		short kanji; // $s0
	// 		char word[128]; // stack offset -168
	// 		int wordCount; // $s1
	// 		int lineLength; // $s6
	// 		int lineCount; // $s4
	/* end block 1 */
	// End offset: 0x000FD000
	// End Line: 3331

	/* begin block 2 */
		// Start line: 7461
	/* end block 2 */
	// End Line: 7462

int FUN_MCARD__000fce00(int param_1,byte *param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte local_a8 [128];
  
  iVar5 = 0;
  iVar8 = 0;
  iVar7 = 0;
  if (500 < param_4) {
    param_4 = 500;
  }
  if (*(int *)(param_1 + 4) == 9) {
    while( true ) {
      sVar2 = CONCAT11(*param_2,param_2[1]);
      if ((sVar2 == 0) || (pbVar4 = local_a8 + iVar5, sVar2 == 0x2020)) {
        local_a8[iVar5] = 0;
        local_a8[iVar5 + 1] = 0;
        iVar3 = FUN_MCARD__000fcc54(param_1,local_a8,param_3,1000);
        iVar8 = iVar8 + iVar3;
        if (param_4 < iVar8) {
          if (iVar7 == 0) {
            return iVar5 + 2;
          }
          return iVar7;
        }
        iVar7 = iVar7 + iVar5 + 2;
        iVar5 = 0;
        pbVar4 = local_a8;
      }
      iVar3 = iVar5 + 1;
      iVar5 = iVar5 + 2;
      *pbVar4 = *param_2;
      pbVar4 = param_2 + 1;
      param_2 = param_2 + 2;
      local_a8[iVar3] = *pbVar4;
      if (sVar2 == 0) break;
      if (0x7f < iVar5) {
        return iVar7;
      }
    }
    return iVar7;
  }
  bVar1 = *param_2;
  if (bVar1 == 0xf0) {
    local_a8[0] = 0x20;
    param_2 = param_2 + 1;
  }
  uVar6 = (uint)(bVar1 == 0xf0);
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if (bVar1 == 0x20) {
LAB_MCARD__000fcf88:
      local_a8[uVar6] = 0;
      iVar5 = FUN_MCARD__000fcc54(param_1,local_a8,param_3,1000);
      iVar8 = iVar8 + iVar5;
      if (param_4 < iVar8) {
        return iVar7;
      }
      iVar7 = iVar7 + uVar6;
      uVar6 = 0;
LAB_MCARD__000fcfbc:
      local_a8[uVar6] = bVar1;
    }
    else {
      if (0x20 < bVar1) {
        if (bVar1 == 0xf0) {
          local_a8[uVar6] = 0;
          return iVar7 + uVar6;
        }
        goto LAB_MCARD__000fcfbc;
      }
      if (bVar1 == 0) goto LAB_MCARD__000fcf88;
      local_a8[uVar6] = bVar1;
    }
    uVar6 = uVar6 + 1;
    if (bVar1 == 0) {
      return iVar7;
    }
  } while( true );
}



// decompiled code
// original method signature: 
// int /*$ra*/ write_mess__7DISPMANPciiiiiiii(struct DISPMAN *this /*$s2*/, char *mesPtr /*$s6*/, int x /*$s3*/, int y /*stack 12*/, int font /*stack 16*/, int maxChars /*stack 20*/, int r /*stack 24*/, int g /*stack 28*/, int b /*stack 32*/, int trans /*stack 36*/)
 // line 3337, offset 0x000fd000
	/* begin block 1 */
		// Start line: 3338
		// Start offset: 0x000FD000
		// Variables:
	// 		int fRef; // $s1
	// 		int n; // stack offset -56
	// 		char c; // $s0

		/* begin block 1.1 */
			// Start line: 3338
			// Start offset: 0x000FD000

			/* begin block 1.1.1 */
				// Start line: 3346
				// Start offset: 0x000FD080

				/* begin block 1.1.1.1 */
					// Start line: 3348
					// Start offset: 0x000FD0F4

					/* begin block 1.1.1.1.1 */
						// Start line: 3357
						// Start offset: 0x000FD124

						/* begin block 1.1.1.1.1.1 */
							// Start line: 3358
							// Start offset: 0x000FD134

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 3359
								// Start offset: 0x000FD134
								// Variables:
							// 		struct DISPMAN *this; // $s2
							// 		struct TIMSTRUCT *tim; // $a3
							// 		int y; // stack offset 12
							// 		int r; // $t1
							// 		int g; // $t0
							// 		int b; // $a3
							// 		int trans; // $v0

								/* begin block 1.1.1.1.1.1.1.1 */
									// Start line: 3359
									// Start offset: 0x000FD134
									// Variables:
								// 		struct DR_TPAGE *tpagePtr; // $a2
								// 		struct SPRT *spritePtr; // $a1
								/* end block 1.1.1.1.1.1.1.1 */
								// End offset: 0x000FD27C
								// End Line: 3366
							/* end block 1.1.1.1.1.1.1 */
							// End offset: 0x000FD27C
							// End Line: 3366
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000FD27C
						// End Line: 3366
					/* end block 1.1.1.1.1 */
					// End offset: 0x000FD27C
					// End Line: 3366

					/* begin block 1.1.1.1.2 */
						// Start line: 3376
						// Start offset: 0x000FD2A4

						/* begin block 1.1.1.1.2.1 */
							// Start line: 3377
							// Start offset: 0x000FD2B0

							/* begin block 1.1.1.1.2.1.1 */
								// Start line: 3338
								// Start offset: 0x000FD2B0
								// Variables:
							// 		struct DISPMAN *this; // $s2
							// 		struct TIMSTRUCT *tim; // $a3
							// 		int x; // $s3
							// 		int y; // stack offset 12
							// 		int r; // $t1
							// 		int g; // $t0
							// 		int b; // $a3
							// 		int trans; // $v0

								/* begin block 1.1.1.1.2.1.1.1 */
									// Start line: 3338
									// Start offset: 0x000FD2B0
									// Variables:
								// 		struct DR_TPAGE *tpagePtr; // $a2
								// 		struct SPRT *spritePtr; // $a1
								/* end block 1.1.1.1.2.1.1.1 */
								// End offset: 0x000FD2B0
								// End Line: 3338
							/* end block 1.1.1.1.2.1.1 */
							// End offset: 0x000FD2B0
							// End Line: 3338
						/* end block 1.1.1.1.2.1 */
						// End offset: 0x000FD3A4
						// End Line: 3381
					/* end block 1.1.1.1.2 */
					// End offset: 0x000FD3A4
					// End Line: 3381
				/* end block 1.1.1.1 */
				// End offset: 0x000FD3A4
				// End Line: 3381
			/* end block 1.1.1 */
			// End offset: 0x000FD410
			// End Line: 3386
		/* end block 1.1 */
		// End offset: 0x000FD410
		// End Line: 3386
	/* end block 1 */
	// End offset: 0x000FD410
	// End Line: 3386

	/* begin block 2 */
		// Start line: 7751
	/* end block 2 */
	// End Line: 7752

uint FUN_MCARD__000fd000(int param_1,byte *param_2,uint param_3,int param_4,int param_5,int param_6,
                        uint param_7,int param_8,int param_9,int param_10)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  int iVar11;
  undefined *puVar12;
  int local_38;
  
  if (*(int *)(param_1 + 4) == 9) {
    param_3 = FUN_MCARD__000fa684(param_1,param_2,param_3,param_4,param_6,param_7,param_8,param_9);
  }
  else {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if ((bVar1 != 0) && (local_38 = 1, 0 < param_6)) {
      puVar12 = &DAT_0000226c + param_1;
      param_5 = param_5 * 0x4c0;
      param_7 = param_10 << 0x19 | param_9 << 0x10 | 0x64000000U | param_8 << 8 | param_7;
      do {
        uVar5 = FUN_MCARD__000fd410(param_1,(uint)bVar1,1);
        uVar6 = uVar5 - 0x97;
        if (uVar5 == 100) {
          uVar5 = 0xff;
          param_3 = param_3 + (int)*(short *)(&DAT_0000233c + param_1 + param_5);
          uVar6 = 0x68;
        }
        if (uVar6 < 0x68) {
          uVar6 = uVar5 - 100;
          uVar5 = FUN_MCARD__000fd410(param_1,(uint)bVar1,0);
          iVar11 = (uVar6 & 0xff) * 0x10;
          iVar8 = *(int *)(param_1 + 0x284);
          iVar10 = iVar11 + param_5 + param_1;
          uVar2 = *(ushort *)(puVar12 + uVar5 * 0x10 + param_5);
          uVar3 = *(ushort *)(puVar12 + iVar11 + param_5);
          *(int *)(param_1 + 0x284) = iVar8 + 1;
          puVar7 = (uint *)(param_1 + iVar8 * 0x14 + 0x600);
          puVar7[2] = param_4 << 0x10 |
                      (param_3 +
                      (((int)((uint)uVar2 << 0x10) >> 0x10) - ((int)((uint)uVar2 << 0x10) >> 0x1f)
                      >> 1)) - (((int)((uint)uVar3 << 0x10) >> 0x10) -
                                ((int)((uint)uVar3 << 0x10) >> 0x1f) >> 1);
          puVar7[3] = (uint)*(ushort *)(&DAT_00002260 + iVar10) << 0x10 |
                      (uint)*(ushort *)(&DAT_00002266 + iVar10) << 8 |
                      (uint)*(ushort *)(&DAT_00002264 + iVar10);
          uVar6 = *(uint *)(&DAT_00002268 + iVar10);
          puVar7[1] = param_7;
          puVar7[4] = uVar6;
          puVar9 = (uint *)(param_1 + iVar8 * 8 + 0x15a0);
          *puVar7 = *DAT_MCARD__0010ec74 | 0x4000000;
          *DAT_MCARD__0010ec74 = (uint)puVar7 & 0xffffff;
          *(undefined *)((int)puVar9 + 3) = 1;
          puVar7 = DAT_MCARD__0010ec74;
          puVar9[1] = (uint)*(ushort *)(&DAT_00002262 + iVar10) & 0x9ff | 0xe1000000;
          *puVar9 = *puVar7 | 0x1000000;
          *DAT_MCARD__0010ec74 = (uint)puVar9 & 0xffffff;
        }
        if ((uVar5 < 4) && (iVar8 = FUN_MCARD__000fd410(param_1,(uint)param_2[-2],1), iVar8 == 0x29)
           ) {
          uVar5 = uVar5 + 0x41;
        }
        if (uVar5 != 0xff) {
          iVar8 = *(int *)(param_1 + 0x284);
          iVar10 = uVar5 * 0x10 + param_5 + param_1;
          puVar7 = (uint *)(param_1 + iVar8 * 0x14 + 0x600);
          puVar9 = (uint *)(param_1 + iVar8 * 8 + 0x15a0);
          *(int *)(param_1 + 0x284) = iVar8 + 1;
          puVar7[2] = param_4 << 0x10 | param_3;
          puVar7[3] = (uint)*(ushort *)(&DAT_00002260 + iVar10) << 0x10 |
                      (uint)*(ushort *)(&DAT_00002266 + iVar10) << 8 |
                      (uint)*(ushort *)(&DAT_00002264 + iVar10);
          uVar6 = *(uint *)(&DAT_00002268 + iVar10);
          puVar7[1] = param_7;
          puVar7[4] = uVar6;
          *puVar7 = *DAT_MCARD__0010ec74 | 0x4000000;
          *DAT_MCARD__0010ec74 = (uint)puVar7 & 0xffffff;
          *(undefined *)((int)puVar9 + 3) = 1;
          puVar7 = DAT_MCARD__0010ec74;
          puVar9[1] = (uint)*(ushort *)(&DAT_00002262 + iVar10) & 0x9ff | 0xe1000000;
          *puVar9 = *puVar7 | 0x1000000;
          *DAT_MCARD__0010ec74 = (uint)puVar9 & 0xffffff;
          param_3 = param_3 + 2 + (int)*(short *)(puVar12 + uVar5 * 0x10 + param_5);
        }
        bVar1 = *param_2;
        param_2 = param_2 + 1;
      } while ((bVar1 != 0) && (bVar4 = local_38 < param_6, local_38 = local_38 + 1, bVar4));
    }
  }
  return param_3;
}



// decompiled code
// original method signature: 
// int /*$ra*/ font_ref__7DISPMANcb(struct DISPMAN *this /*$a0*/, char c /*$a1*/, unsigned int accent /*$a2*/)
 // line 3392, offset 0x000fd410
	/* begin block 1 */
		// Start line: 3393
		// Start offset: 0x000FD410
	/* end block 1 */
	// End offset: 0x000FD650
	// End Line: 3519

	/* begin block 2 */
		// Start line: 7871
	/* end block 2 */
	// End Line: 7872

uint FUN_MCARD__000fd410(undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  param_2 = param_2 & 0xff;
  switch(param_2) {
  case 0x20:
  case 0x5f:
  case 0xf0:
    return 100;
  case 0x21:
    return 0x2e;
  case 0x27:
  case 0x60:
    return 0x28;
  case 0x28:
    return 0x2f;
  case 0x29:
    return 0x30;
  case 0x2c:
    return 0x25;
  case 0x2d:
    return 0x29;
  case 0x2e:
    return 0x24;
  case 0x2f:
  case 0x5c:
    return 0x2a;
  case 0x3a:
    return 0x27;
  case 0x3b:
    return 0x26;
  case 0x3f:
    return 0x2c;
  case 0x80:
  case 0x87:
    return 0x33;
  case 0x86:
  case 0x8f:
    return 0x31;
  case 0x91:
  case 0x92:
    return 0x35;
  case 0xa8:
    return 0x2b;
  case 0xad:
    return 0x2d;
  case 0xb1:
    return 0x41;
  case 0xb2:
    return 0x42;
  case 0xb3:
    return 0x43;
  case 0xb4:
    return 0x44;
  case 0xba:
    return 0x3d;
  case 0xbb:
    return 0x3e;
  case 0xbc:
    return 0x3f;
  case 0xbd:
    return 0x40;
  case 0xe1:
    return 0x32;
  case 0xe8:
    return 0x34;
  case 0xec:
    return 0x36;
  case 0xed:
    return 0x37;
  case 0xfe:
    return 0x4a;
  case 0xff:
    return 0x4b;
  }
  if (0x5a < param_2) {
    if (param_3 == 0) {
      switch(param_2) {
      case 0x81:
      case 0x96:
      case 0x97:
      case 0x9a:
      case 0xa3:
        return 0x14;
      case 0x82:
      case 0x88:
      case 0x89:
      case 0x8a:
      case 0x90:
        return 4;
      case 0x83:
      case 0x84:
      case 0x85:
      case 0x8e:
      case 0xa0:
      case 0xa9:
        return 0;
      case 0x8b:
      case 0x8c:
      case 0x8d:
      case 0xa1:
        return 8;
      case 0x93:
      case 0x94:
      case 0x95:
      case 0x99:
      case 0xa2:
      case 0xaa:
        return 0xe;
      case 0x98:
        return 0x18;
      case 0xa4:
      case 0xa5:
        return 0xd;
      }
    }
    if ((0x5a < param_2) && (param_3 != 0)) {
      switch(param_2) {
      case 0x81:
      case 0x84:
      case 0x89:
      case 0x8b:
      case 0x8e:
      case 0x94:
      case 0x98:
      case 0x99:
      case 0x9a:
        return 0x9f;
      case 0x82:
      case 0x90:
      case 0xa0:
      case 0xa1:
      case 0xa2:
      case 0xa3:
        return 0x9c;
      case 0x83:
      case 0x88:
      case 0x8c:
      case 0x93:
      case 0x96:
        return 0x9e;
      case 0x85:
      case 0x8a:
      case 0x8d:
      case 0x95:
      case 0x97:
        return 0x9d;
      case 0xa4:
      case 0xa5:
      case 0xa9:
      case 0xaa:
        return 0xa0;
      }
    }
  }
  uVar1 = param_2 - 0x41;
  if (0x19 < (uVar1 & 0xff)) {
    uVar1 = param_2 - 0x61;
    if (0x19 < (uVar1 & 0xff)) {
      if (param_2 - 0x30 < 10) {
        return param_2 - 0x16;
      }
      return 0xff;
    }
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ Tim2VRAM__7DISPMANPlP9TIMSTRUCTibiiii(struct DISPMAN *this /*$a0*/, long *timDataPtr /*$s0*/, struct TIMSTRUCT *destTimPtr /*$s2*/, int abr /*$s1*/, unsigned int setCoords /*stack 16*/, int clutX /*stack 20*/, int clutY /*stack 24*/, int iconX /*stack 28*/, int iconY /*stack 32*/)
 // line 3524, offset 0x000fd658
	/* begin block 1 */
		// Start line: 3525
		// Start offset: 0x000FD658
		// Variables:
	// 		long flag; // $a0
	// 		struct RECT *timRect; // $a2

		/* begin block 1.1 */
			// Start line: 3543
			// Start offset: 0x000FD6A4

			/* begin block 1.1.1 */
				// Start line: 3549
				// Start offset: 0x000FD6B8

				/* begin block 1.1.1.1 */
					// Start line: 3558
					// Start offset: 0x000FD6D8

					/* begin block 1.1.1.1.1 */
						// Start line: 3563
						// Start offset: 0x000FD6F0

						/* begin block 1.1.1.1.1.1 */
							// Start line: 3564
							// Start offset: 0x000FD6F0
							// Variables:
						// 		int n; // $a0
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000FD718
						// End Line: 3569
					/* end block 1.1.1.1.1 */
					// End offset: 0x000FD718
					// End Line: 3569
				/* end block 1.1.1.1 */
				// End offset: 0x000FD718
				// End Line: 3569
			/* end block 1.1.1 */
			// End offset: 0x000FD740
			// End Line: 3576
		/* end block 1.1 */
		// End offset: 0x000FD740
		// End Line: 3576
	/* end block 1 */
	// End offset: 0x000FD86C
	// End Line: 3611

	/* begin block 2 */
		// Start line: 8135
	/* end block 2 */
	// End Line: 8136

	/* begin block 3 */
		// Start line: 8140
	/* end block 3 */
	// End Line: 8141

void FUN_MCARD__000fd658(undefined4 param_1,int param_2,u_short *param_3,uint param_4,int param_5,
                        undefined2 param_6,undefined2 param_7,undefined2 param_8,undefined2 param_9)

{
  u_short uVar1;
  ushort *puVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  
  uVar3 = *(uint *)(param_2 + 4);
  uVar6 = uVar3 & 7;
  if (2 < uVar6) {
                    /* WARNING: Subroutine does not return */
    exit(-1);
  }
  piVar5 = (int *)(param_2 + 8);
  if ((uVar3 & 8) != 0) {
    if (param_5 != 0) {
      *(undefined2 *)(param_2 + 0xc) = param_6;
      *(undefined2 *)(param_2 + 0xe) = param_7;
    }
    uVar1 = GetClut((int)*(short *)(param_2 + 0xc),(int)*(short *)(param_2 + 0xe));
    *param_3 = uVar1;
    if (0 < (int)param_4) {
      puVar2 = (ushort *)(param_2 + 0x14);
      iVar4 = 0xf;
      do {
        if (*puVar2 != 0) {
          *puVar2 = *puVar2 | 0x8000;
        }
        iVar4 = iVar4 + -1;
        puVar2 = puVar2 + 1;
      } while (-1 < iVar4);
    }
    DrawSync(0);
    LoadImage(param_2 + 0xc,param_2 + 0x14);
    DrawSync(0);
    piVar5 = (int *)((int)piVar5 + *piVar5);
  }
  if (param_5 != 0) {
    *(undefined2 *)(piVar5 + 1) = param_8;
    *(undefined2 *)((int)piVar5 + 6) = param_9;
  }
  param_3[1] = (ushort)((uVar3 & 3) << 7) | (ushort)((param_4 & 3) << 5) |
               (short)(*(ushort *)((int)piVar5 + 6) & 0x100) >> 4 |
               (ushort)(((uint)*(ushort *)(piVar5 + 1) & 0x3ff) >> 6) |
               (ushort)(((uint)*(ushort *)((int)piVar5 + 6) & 0x200) << 2);
  param_3[3] = (ushort)*(byte *)((int)piVar5 + 6);
  if (uVar6 == 0) {
    param_3[2] = (u_short)(((uint)*(ushort *)(piVar5 + 1) & 0x3f) << 2);
    uVar1 = (u_short)((int)*(short *)(piVar5 + 2) << 2);
  }
  else {
    if (uVar6 == 1) {
      param_3[2] = (u_short)(((uint)*(ushort *)(piVar5 + 1) & 0x3f) << 1);
      uVar1 = (u_short)((int)*(short *)(piVar5 + 2) << 1);
    }
    else {
      param_3[2] = *(ushort *)(piVar5 + 1) & 0x3f;
      uVar1 = *(u_short *)(piVar5 + 2);
    }
  }
  param_3[4] = uVar1;
  param_3[5] = *(u_short *)((int)piVar5 + 10);
  DrawSync(0);
  LoadImage(piVar5 + 1,piVar5 + 3);
  DrawSync(0);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ download_block_icon__7DISPMANiiii(struct DISPMAN *this /*$s2*/, int iconX /*$s3*/, int iconY /*$s1*/, int clutX /*$a3*/, int clutY /*stack 16*/)
 // line 3615, offset 0x000fe908
	/* begin block 1 */
		// Start line: 3616
		// Start offset: 0x000FE908
		// Variables:
	// 		struct RECT rect; // stack offset -32
	// 		struct TIMSTRUCT *timPtr; // $s0
	// 		unsigned short *clutWordPtr; // $v1

		/* begin block 1.1 */
			// Start line: 3616
			// Start offset: 0x000FE908
			// Variables:
		// 		int n; // $a0
		/* end block 1.1 */
		// End offset: 0x000FE998
		// End Line: 3637
	/* end block 1 */
	// End offset: 0x000FEA44
	// End Line: 3657

	/* begin block 2 */
		// Start line: 12032
	/* end block 2 */
	// End Line: 12033

void FUN_MCARD__000fe908(int param_1,uint param_2,uint param_3,short param_4,short param_5)

{
  ushort uVar1;
  u_short uVar2;
  int iVar3;
  int iVar4;
  short local_20;
  ushort local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  local_1c = 0x10;
  local_1a = 1;
  local_1e = param_5;
  local_20 = param_4;
  uVar2 = GetClut((int)param_4,(int)param_5);
  iVar4 = 0x70;
  iVar3 = 0xf;
  *(u_short *)(&DAT_000045d8 + param_1) = uVar2;
  do {
    uVar1 = *(ushort *)(*(int *)(&DAT_00004688 + param_1) + iVar4);
    if (uVar1 != 0) {
      *(ushort *)(*(int *)(&DAT_00004688 + param_1) + iVar4) = uVar1 | 0x8000;
    }
    iVar3 = iVar3 + -1;
    iVar4 = iVar4 + 2;
  } while (-1 < iVar3);
  LoadImage(&local_20,*(int *)(&DAT_00004688 + param_1) + 0x70);
  DrawSync(0);
  local_1e = (ushort)param_3;
  local_20 = (short)param_2;
  *(ushort *)(&DAT_000045de + param_1) = local_1e & 0xff;
  *(ushort *)(&DAT_000045da + param_1) =
       (short)(local_1e & 0x100) >> 4 | (ushort)((param_2 & 0x3ff) >> 6) | 0x20 |
       (ushort)((param_3 & 0x200) << 2);
  *(short *)(&DAT_000045dc + param_1) = (short)((param_2 & 0x3f) << 2);
  *(undefined2 *)(&DAT_000045e0 + param_1) = 0x10;
  *(undefined2 *)(&DAT_000045e2 + param_1) = 0x10;
  local_1c = 4;
  local_1a = 0x10;
  LoadImage(&local_20,*(int *)(&DAT_00004688 + param_1) + 0x90);
  DrawSync(0);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ wipe_screen__7DISPMANii(struct DISPMAN *this /*$s1*/, int wt /*$s3*/, int step /*$s5*/)
 // line 3749, offset 0x000fd86c
	/* begin block 1 */
		// Start line: 3750
		// Start offset: 0x000FD86C
		// Variables:
	// 		int i; // $s2
	// 		struct DRAWENV drawenv; // stack offset -248
	// 		struct DISPENV de; // stack offset -152
	// 		unsigned long fadeOt[3]; // stack offset -128
	// 		struct POLY_GT3 FadeSetTp; // stack offset -112
	// 		struct POLY_G4 FadePol; // stack offset -72
	/* end block 1 */
	// End offset: 0x000FDAD8
	// End Line: 3806

	/* begin block 2 */
		// Start line: 8595
	/* end block 2 */
	// End Line: 8596

/* WARNING: Could not reconcile some variable overlaps */

void FUN_MCARD__000fd86c(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 local_f8;
  undefined4 local_f4;
  short local_f0;
  short local_ee;
  uchar local_e2;
  uchar local_e1;
  uchar local_e0;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined auStack128 [16];
  undefined auStack112 [3];
  undefined local_6d;
  undefined local_69;
  undefined2 local_68;
  undefined2 local_66;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_56;
  undefined2 local_50;
  undefined2 local_4e;
  undefined auStack72 [3];
  undefined local_45;
  undefined local_44;
  undefined local_43;
  undefined local_42;
  undefined local_41;
  short local_40;
  short local_3e;
  undefined local_3c;
  undefined local_3b;
  undefined local_3a;
  short local_38;
  short local_36;
  undefined local_34;
  undefined local_33;
  undefined local_32;
  short local_30;
  short local_2e;
  undefined local_2c;
  undefined local_2b;
  undefined local_2a;
  short local_28;
  short local_26;
  
  GetDispEnv((DISPENV *)&local_98);
  GetDrawEnv(&local_f8);
  if ((short)local_8c == -1) {
    local_98 = *(undefined4 *)(param_1 + 0x200);
    local_94 = *(undefined4 *)(param_1 + 0x204);
    local_90 = *(undefined4 *)(param_1 + 0x208);
    local_8c = *(undefined4 *)(param_1 + 0x20c);
    local_88 = *(undefined4 *)(param_1 + 0x210);
  }
  local_f8 = local_98;
  local_f4 = local_94;
  local_ee = 0;
  local_f0 = 0;
  local_e0 = '\0';
  local_e2 = '\x01';
  local_e1 = '\x01';
  PutDrawEnv((DRAWENV *)&local_f8);
  PutDispEnv((DISPENV *)&local_98);
  local_45 = 8;
  local_41 = 0x38;
  SetSemiTrans(auStack72,1);
  local_44 = 0xff;
  local_43 = 0xff;
  local_42 = 0xff;
  local_34 = 0xff;
  local_33 = 0xff;
  local_32 = 0xff;
  local_3c = 0;
  local_3b = 0;
  local_3a = 0;
  local_2c = 0;
  local_2b = 0;
  local_2a = 0;
  local_6d = 9;
  local_69 = 0x34;
  SetSemiTrans(auStack112,1);
  local_56 = 0x48;
  local_68 = 0xffff;
  local_66 = 0xffff;
  local_5c = 0xffff;
  local_5a = 0xffff;
  local_50 = 0xffff;
  local_4e = 0xffff;
  DrawSync(0);
  iVar1 = -param_2;
  if (iVar1 < (int)(short)local_94 + 0x80) {
    do {
      local_40 = (short)local_98 + (short)iVar1;
      local_38 = local_40 + (short)param_2;
      local_30 = local_40 + -0x80;
      local_3e = local_98._2_2_;
      local_36 = local_98._2_2_;
      local_2e = local_98._2_2_ + local_94._2_2_;
      local_28 = local_38 + -0x80;
      local_26 = local_2e;
      ClearOTag(auStack128,2);
      FUN_MCARD__0010eb20(auStack128,auStack72);
      FUN_MCARD__0010eb20(auStack128,auStack112);
      VSync(0);
      DrawOTag(auStack128);
      DrawSync(0);
      iVar1 = iVar1 + param_3;
    } while (iVar1 < (int)(short)local_94 + 0x80);
  }
  DrawSync(0);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ move_screen__7DISPMANiii(struct DISPMAN *this /*$s0*/, int startY /*$a1*/, int finishY /*$s3*/, int steps /*$a3*/)
 // line 3809, offset 0x000fea44
	/* begin block 1 */
		// Start line: 3810
		// Start offset: 0x000FEA44
		// Variables:
	// 		int screenY; // $s1
	/* end block 1 */
	// End offset: 0x000FEB00
	// End Line: 3835

	/* begin block 2 */
		// Start line: 12479
	/* end block 2 */
	// End Line: 12480

	/* begin block 3 */
		// Start line: 12485
	/* end block 3 */
	// End Line: 12486

void FUN_MCARD__000fea44(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (param_3 - param_2) / param_4;
  param_2 = param_2 + *(int *)(&DAT_0000222c + param_1);
  if (param_4 == 0) {
    trap(7);
  }
  iVar1 = param_2 + iVar2 * param_4;
  while (param_2 != iVar1) {
    SetDefDispEnv((DISPENV *)(param_1 + 0x200),*(undefined4 *)(&DAT_00002228 + param_1),param_2,
                  *(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0x198));
    *(undefined2 *)(param_1 + 0x20c) = 0x100;
    *(undefined2 *)(param_1 + 0x208) = *(undefined2 *)(param_1 + 0x19c);
    *(undefined2 *)(param_1 + 0x20a) = *(undefined2 *)(param_1 + 0x1a0);
    *(short *)(param_1 + 0x20e) = *(short *)(param_1 + 0x198) - (short)param_2;
    PutDispEnv((DISPENV *)(param_1 + 0x200));
    VSync(0);
    param_2 = param_2 + iVar2;
    SetDispMask(1);
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetCyclesPerSecond__7DISPMAN(struct DISPMAN *this /*$a0*/)
 // line 3840, offset 0x000feb24
	/* begin block 1 */
		// Start line: 3841
		// Start offset: 0x000FEB24
	/* end block 1 */
	// End offset: 0x000FEB70
	// End Line: 3854

	/* begin block 2 */
		// Start line: 12559
	/* end block 2 */
	// End Line: 12560

	/* begin block 3 */
		// Start line: 12560
	/* end block 3 */
	// End Line: 12561

undefined4 FUN_MCARD__000feb24(int param_1)

{
  if (DAT_MCARD__0010ec70 == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x198) != 0xf0) {
    if (*(int *)(param_1 + 0x198) == 0x100) {
      return 0x32;
    }
    return 0;
  }
  return 0x3c;
}





