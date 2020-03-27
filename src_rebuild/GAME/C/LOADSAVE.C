#include "THISDUST.H"
#include "LOADSAVE.H"


// decompiled code
// original method signature: 
// int /*$ra*/ CalcReplayDataSize()
 // line 37, offset 0x00057fd4
	/* begin block 1 */
		// Start line: 39
		// Start offset: 0x00057FD4
	/* end block 1 */
	// End offset: 0x00057FF4
	// End Line: 46

	/* begin block 2 */
		// Start line: 279
	/* end block 2 */
	// End Line: 280

	/* begin block 3 */
		// Start line: 74
	/* end block 3 */
	// End Line: 75

	/* begin block 4 */
		// Start line: 280
	/* end block 4 */
	// End Line: 281

	/* begin block 5 */
		// Start line: 282
	/* end block 5 */
	// End Line: 283

/* WARNING: Unknown calling convention yet parameter storage is locked */

int CalcReplayDataSize(void)

{
  int iVar1;
  
  iVar1 = SaveReplayToBuffer((char *)0x0);
  return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SaveReplayData(char *buffer /*$a0*/)
 // line 48, offset 0x00057ff4
	/* begin block 1 */
		// Start line: 50
		// Start offset: 0x00057FF4
	/* end block 1 */
	// End offset: 0x00058014
	// End Line: 54

	/* begin block 2 */
		// Start line: 298
	/* end block 2 */
	// End Line: 299

	/* begin block 3 */
		// Start line: 301
	/* end block 3 */
	// End Line: 302

	/* begin block 4 */
		// Start line: 302
	/* end block 4 */
	// End Line: 303

	/* begin block 5 */
		// Start line: 304
	/* end block 5 */
	// End Line: 305

int SaveReplayData(char *buffer)

{
  int iVar1;
  
  iVar1 = SaveReplayToBuffer(buffer);
  return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadReplayData(char *buffer /*$a0*/)
 // line 56, offset 0x00058014
	/* begin block 1 */
		// Start line: 314
	/* end block 1 */
	// End Line: 315

	/* begin block 2 */
		// Start line: 317
	/* end block 2 */
	// End Line: 318

	/* begin block 3 */
		// Start line: 318
	/* end block 3 */
	// End Line: 319

int LoadReplayData(char *buffer)

{
  int iVar1;
  
  iVar1 = LoadReplayFromBuffer(buffer);
  return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcGameDataSize()
 // line 62, offset 0x00058034
	/* begin block 1 */
		// Start line: 329
	/* end block 1 */
	// End Line: 330

	/* begin block 2 */
		// Start line: 332
	/* end block 2 */
	// End Line: 333

/* WARNING: Unknown calling convention yet parameter storage is locked */

int CalcGameDataSize(void)

{
  return 0x10c;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SaveGameData(char *buffer /*$s0*/)
 // line 69, offset 0x0005803c
	/* begin block 1 */
		// Start line: 70
		// Start offset: 0x0005803C
	/* end block 1 */
	// End offset: 0x000580CC
	// End Line: 83

	/* begin block 2 */
		// Start line: 343
	/* end block 2 */
	// End Line: 344

int SaveGameData(char *buffer)

{
  long *plVar1;
  MISSION_DATA *pMVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  ClearMem(buffer,0x10c);
  plVar1 = (long *)(buffer + 8);
  pMVar2 = &MissionEndData;
  *(undefined4 *)buffer = 0x54876421;
  buffer[4] = (char)gMissionLadderPos + '\x01';
  do {
    lVar3 = (pMVar2->PlayerPos).vx;
    lVar4 = (pMVar2->PlayerPos).vy;
    lVar5 = (pMVar2->PlayerPos).vz;
    *plVar1 = *(long *)&pMVar2->PlayerPos;
    plVar1[1] = lVar3;
    plVar1[2] = lVar4;
    plVar1[3] = lVar5;
    pMVar2 = (MISSION_DATA *)&(pMVar2->PlayerPos).felony;
    plVar1 = plVar1 + 4;
  } while (pMVar2 != (MISSION_DATA *)&MissionEndData.CarPos[5].vz);
  *plVar1 = MissionEndData.CarPos[5].vz;
  return 0x10c;
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadGameData(char *buffer /*$a0*/)
 // line 85, offset 0x000580cc
	/* begin block 1 */
		// Start line: 86
		// Start offset: 0x000580CC
		// Variables:
	// 		struct GAME_SAVE_HEADER *header; // $a0
	/* end block 1 */
	// End offset: 0x00058164
	// End Line: 99

	/* begin block 2 */
		// Start line: 379
	/* end block 2 */
	// End Line: 380

	/* begin block 3 */
		// Start line: 382
	/* end block 3 */
	// End Line: 383

	/* begin block 4 */
		// Start line: 386
	/* end block 4 */
	// End Line: 387

int LoadGameData(char *buffer)

{
  int pos;
  long lVar1;
  long lVar2;
  undefined4 *puVar3;
  MISSION_DATA *pMVar4;
  long lVar5;
  
  pos = 0;
  if (*(int *)buffer == 0x54876421) {
    pMVar4 = &MissionStartData;
    puVar3 = (undefined4 *)(buffer + 8);
    gMissionLadderPos = ZEXT14((byte)buffer[4]);
    gHaveStoredData = 1;
    do {
      lVar1 = puVar3[1];
      lVar2 = puVar3[2];
      lVar5 = puVar3[3];
      *(undefined4 *)&pMVar4->PlayerPos = *puVar3;
      (pMVar4->PlayerPos).vx = lVar1;
      (pMVar4->PlayerPos).vy = lVar2;
      (pMVar4->PlayerPos).vz = lVar5;
      pos = gMissionLadderPos;
      puVar3 = puVar3 + 4;
      pMVar4 = (MISSION_DATA *)&(pMVar4->PlayerPos).felony;
    } while (puVar3 != (undefined4 *)(buffer + 0xe8));
    *(undefined4 *)&pMVar4->PlayerPos = *puVar3;
    FindPrevMissionFromLadderPos(pos);
    pos = 1;
  }
  return pos;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcConfigDataSize()
 // line 102, offset 0x00058164
	/* begin block 1 */
		// Start line: 417
	/* end block 1 */
	// End Line: 418

	/* begin block 2 */
		// Start line: 421
	/* end block 2 */
	// End Line: 422

	/* begin block 3 */
		// Start line: 424
	/* end block 3 */
	// End Line: 425

/* WARNING: Unknown calling convention yet parameter storage is locked */

int CalcConfigDataSize(void)

{
  return 0x904;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SaveConfigData(char *buffer /*$a0*/)
 // line 109, offset 0x00057bf0
	/* begin block 1 */
		// Start line: 110
		// Start offset: 0x00057BF0
		// Variables:
	// 		struct CONFIG_SAVE_HEADER *header; // $s0
	// 		int i; // $t0
	/* end block 1 */
	// End offset: 0x00057DF0
	// End Line: 138

	/* begin block 2 */
		// Start line: 218
	/* end block 2 */
	// End Line: 219

int SaveConfigData(char *buffer)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  SCORE_TABLES *pSVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  
  ClearMem(buffer,0x904);
  iVar3 = gMasterVolume;
  iVar2 = gMusicVolume;
  iVar1 = gSoundMode;
  iVar10 = gVibration;
  iVar11 = gCopDifficultyLevel;
  iVar8 = gFurthestMission;
  *(undefined4 *)buffer = 0x36132479;
  *(int *)(buffer + 4) = iVar3;
  *(int *)(buffer + 8) = iVar2;
  *(int *)(buffer + 0xc) = iVar1;
  *(int *)(buffer + 0x10) = iVar10;
  *(int *)(buffer + 0x14) = iVar11;
  *(int *)(buffer + 0x18) = iVar8;
  iVar11 = 0;
  *(int *)(buffer + 0x8d4) = (int)draw_mode_pal.framex;
  *(int *)(buffer + 0x8d8) = (int)draw_mode_pal.framey;
  *(int *)(buffer + 0x8dc) = (int)draw_mode_ntsc.framex;
  iVar8 = (int)draw_mode_ntsc.framey;
  *(int *)(buffer + 0x8e4) = gSubtitles;
  *(int *)(buffer + 0x8e0) = iVar8;
  *(undefined4 *)(buffer + 0x8e8) = AvailableCheats;
  iVar8 = 0;
  do {
    iVar8 = iVar8 + iVar11;
    puVar6 = (undefined4 *)(buffer + iVar8 * 4 + 0x1c);
    puVar9 = (undefined4 *)(Pads[0].mappings.button_lookup + iVar8 * 4);
    puVar4 = (undefined4 *)(&Pads[0].mappings.swap_analog + iVar8 * 4);
    if (((uint)puVar6 & 3) == 0) {
      do {
        uVar12 = puVar9[1];
        uVar13 = puVar9[2];
        uVar14 = puVar9[3];
        *puVar6 = *puVar9;
        puVar6[1] = uVar12;
        puVar6[2] = uVar13;
        puVar6[3] = uVar14;
        puVar9 = puVar9 + 4;
        puVar6 = puVar6 + 4;
      } while (puVar9 != puVar4);
    }
    else {
      do {
        uVar12 = puVar9[1];
        uVar13 = puVar9[2];
        uVar14 = puVar9[3];
        *puVar6 = *puVar9;
        puVar6[1] = uVar12;
        puVar6[2] = uVar13;
        puVar6[3] = uVar14;
        puVar9 = puVar9 + 4;
        puVar6 = puVar6 + 4;
      } while (puVar9 != puVar4);
    }
    piVar7 = (int *)(buffer + 100);
    iVar11 = iVar11 + 1;
    *puVar6 = *puVar9;
    iVar8 = iVar11 * 8;
  } while (iVar11 < 2);
  pSVar5 = &ScoreTables;
  do {
    iVar8 = *(int *)&pSVar5->GetawayTable[0].items;
    iVar11 = *(int *)(pSVar5->GetawayTable[0].name + 2);
    iVar10 = pSVar5->GetawayTable[1].time;
    *piVar7 = pSVar5->GetawayTable[0].time;
    piVar7[1] = iVar8;
    piVar7[2] = iVar11;
    piVar7[3] = iVar10;
    pSVar5 = (SCORE_TABLES *)&pSVar5->GetawayTable[1].items;
    piVar7 = piVar7 + 4;
  } while (pSVar5 != (SCORE_TABLES *)&gPlayerScore);
  return 0x904;
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadConfigData(char *buffer /*$a0*/)
 // line 140, offset 0x00057df0
	/* begin block 1 */
		// Start line: 141
		// Start offset: 0x00057DF0
		// Variables:
	// 		struct CONFIG_SAVE_HEADER *header; // $t3
	// 		int i; // $t4
	/* end block 1 */
	// End offset: 0x00057FD4
	// End Line: 168

	/* begin block 2 */
		// Start line: 307
	/* end block 2 */
	// End Line: 308

	/* begin block 3 */
		// Start line: 310
	/* end block 3 */
	// End Line: 311

	/* begin block 4 */
		// Start line: 315
	/* end block 4 */
	// End Line: 316

int LoadConfigData(char *buffer)

{
  SCORE_TABLES *pSVar1;
  MAPPING *pMVar2;
  int *piVar3;
  undefined4 *puVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  
  iVar11 = 0;
  if (*(int *)buffer == 0x36132479) {
    piVar3 = (int *)(buffer + 100);
    gMasterVolume = *(int *)(buffer + 4);
    gMusicVolume = *(int *)(buffer + 8);
    gSoundMode = *(int *)(buffer + 0xc);
    gVibration = *(int *)(buffer + 0x10);
    gCopDifficultyLevel = *(int *)(buffer + 0x14);
    gFurthestMission = *(int *)(buffer + 0x18);
    draw_mode_pal.framex = *(short *)(buffer + 0x8d4);
    draw_mode_pal.framey = *(short *)(buffer + 0x8d8);
    draw_mode_ntsc.framex = *(short *)(buffer + 0x8dc);
    draw_mode_ntsc.framey = *(short *)(buffer + 0x8e0);
    gSubtitles = *(int *)(buffer + 0x8e4);
    AvailableCheats = *(undefined4 *)(buffer + 0x8e8);
    do {
      pMVar2 = &Pads[iVar11].mappings;
      pcVar5 = buffer + iVar11 * 0x24;
      puVar4 = (undefined4 *)(pcVar5 + 0x1c);
      iVar11 = iVar11 + 1;
      if (((uint)puVar4 & 3) == 0) {
        do {
          uVar8 = puVar4[1];
          uVar9 = puVar4[2];
          uVar10 = puVar4[3];
          *(undefined4 *)pMVar2->button_lookup = *puVar4;
          *(undefined4 *)(pMVar2->button_lookup + 2) = uVar8;
          *(undefined4 *)(pMVar2->button_lookup + 4) = uVar9;
          *(undefined4 *)(pMVar2->button_lookup + 6) = uVar10;
          puVar4 = puVar4 + 4;
          pMVar2 = (MAPPING *)(pMVar2->button_lookup + 8);
        } while (puVar4 != (undefined4 *)(pcVar5 + 0x3c));
      }
      else {
        do {
          uVar8 = puVar4[1];
          uVar9 = puVar4[2];
          uVar10 = puVar4[3];
          *(undefined4 *)pMVar2->button_lookup = *puVar4;
          *(undefined4 *)(pMVar2->button_lookup + 2) = uVar8;
          *(undefined4 *)(pMVar2->button_lookup + 4) = uVar9;
          *(undefined4 *)(pMVar2->button_lookup + 6) = uVar10;
          puVar4 = puVar4 + 4;
          pMVar2 = (MAPPING *)(pMVar2->button_lookup + 8);
        } while (puVar4 != (undefined4 *)(pcVar5 + 0x3c));
      }
      *(undefined4 *)pMVar2->button_lookup = *puVar4;
    } while (iVar11 < 2);
    pSVar1 = &ScoreTables;
    do {
      iVar11 = piVar3[1];
      iVar6 = piVar3[2];
      iVar7 = piVar3[3];
      pSVar1->GetawayTable[0].time = *piVar3;
      *(int *)&pSVar1->GetawayTable[0].items = iVar11;
      *(int *)(pSVar1->GetawayTable[0].name + 2) = iVar6;
      pSVar1->GetawayTable[1].time = iVar7;
      piVar3 = piVar3 + 4;
      pSVar1 = (SCORE_TABLES *)&pSVar1->GetawayTable[1].items;
    } while (piVar3 != (int *)(buffer + 0x8d4));
    return 1;
  }
  return 0;
}





