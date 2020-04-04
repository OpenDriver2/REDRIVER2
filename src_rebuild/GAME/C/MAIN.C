#include "THISDUST.H"
#include "MAIN.H"

#include "LIBETC.H"
#include "LIBSPU.H"
#include "LIBGPU.H"
#include "LIBMCRD.H"

#include "SYSTEM.H"
#include "PAD.H"
#include "SOUND.H"
#include "FMVPLAY.H"
#include "E3STUFF.H"
#include "GAMESND.H"
#include "SCORES.H"
#include "GLAUNCH.H"
#include "LOADVIEW.H"
#include "REPLAYS.H"
#include "EVENT.H"
#include "MISSION.H"
#include "CUTSCENE.H"
#include "TEXTURE.H"
#include "SKY.H"
#include "PRES.H"
#include "DRAW.H"
#include "DENTING.H"
#include "PEDEST.H"
#include "SPOOL.H"
#include "MAP.H"
#include "OBJANIM.H"
#include "HANDLING.H"
#include "DRIVINGGAMES.H"
#include "BOMBERMAN.H"
#include "PLAYERS.H"
#include "AI.H"
#include "CIV_AI.H"
#include "COP_AI.H"
#include "CAMERA.H"
#include "OVERLAY.H"
#include "DEBRIS.H"
#include "JOB_FX.H"
#include "DIRECTOR.H"
#include "CONVERT.H"

#include "XAPLAY.H"
#include "SHADOW.H"

#include <stdlib.h>

#include "../FRONTEND/FEMAIN.H"

int scr_z = 0;

int levelstartpos[8][4] = {
	{0x12B1, 0xFFFFFC00, 0xFFFC9794, 0},
	{0xFFFC74AC, 0x800, 0xFFFC6961, 0},
	{0x383CB, 0xFFFFFC00, 0xABE1E, 0},
	{0x165EF, 0xFFFFFC00, 0xFFFAB3D9, 0},
	{0x24548, 0x1813, 0xFFFE4A80, 0},
	{ 0xFFFD67F0, 0x1813, 0x58228, 0},
	{ 0xFFFFD6FC, 0xFFFFE7ED, 0xFFFFA980, 0},
	{ 0xFFFFDCDD, 0xFFFFE7ED, 0xF8A7, 0},
};

// decompiled code
// original method signature: 
// void /*$ra*/ ProcessLumps(char *lump_ptr /*$s1*/, int lump_size /*$a1*/)
 // line 2672, offset 0x00058c08
	/* begin block 1 */
		// Start line: 2673
		// Start offset: 0x00058C08
		// Variables:
	// 		int quit; // $s3
	// 		int lump_type; // $v1
	// 		int seg_size; // $s0

		/* begin block 1.1 */
			// Start line: 2686
			// Start offset: 0x00058D94

			/* begin block 1.1.1 */
				// Start line: 2845
				// Start offset: 0x00058F7C
				// Variables:
			// 		struct DRIVER2_JUNCTION *dst; // $a0
			// 		unsigned long *src; // $a2
			// 		int i; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00058FC4
			// End Line: 2858

			/* begin block 1.1.2 */
				// Start line: 2865
				// Start offset: 0x00058FCC
				// Variables:
			// 		struct DRIVER2_JUNCTION *dst; // $a0
			// 		unsigned long *src; // $a2
			// 		int i; // $v1
			/* end block 1.1.2 */
			// End offset: 0x00059018
			// End Line: 2878
		/* end block 1.1 */
		// End offset: 0x00059024
		// End Line: 2890
	/* end block 1 */
	// End offset: 0x00059050
	// End Line: 2894

	/* begin block 2 */
		// Start line: 5344
	/* end block 2 */
	// End Line: 5345

void ProcessLumps(char *lump_ptr, int lump_size)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int *piVar2;
	int *piVar3;
	int *piVar4;
	int *piVar5;
	uint uVar6;
	int iVar7;
	DRIVER2_JUNCTION *pDVar8;
	ulong *puVar9;
	int lump_size_00;
	int *lump_ptr_00;

	bVar1 = false;
	do {
		iVar7 = *(int *)lump_ptr;
		lump_size_00 = ((int *)lump_ptr)[1];
		lump_ptr_00 = (int *)lump_ptr + 2;
		if (iVar7 == 0x15) {
			ProcessLowDetailTable((char *)lump_ptr_00, lump_size_00);
			piVar2 = (int *)car_models_lump;
			piVar3 = (int *)palette_lump;
			piVar4 = (int *)map_lump;
			piVar5 = (int *)texturename_buffer;
		LAB_00059028:
			texturename_buffer = (char *)piVar5;
			map_lump = (char *)piVar4;
			palette_lump = (char *)piVar3;
			car_models_lump = (char *)piVar2;
			uVar6 = lump_size_00 + 3U & 0xfffffffc;
		}
		else {
			piVar2 = (int *)car_models_lump;
			piVar3 = (int *)palette_lump;
			piVar4 = (int *)map_lump;
			piVar5 = (int *)texturename_buffer;
			if (0x15 < iVar7) {
				if (iVar7 == 0x21) {
					ProcessChairLump((char *)lump_ptr_00, lump_size_00);
					piVar2 = (int *)car_models_lump;
					piVar3 = (int *)palette_lump;
					piVar4 = (int *)map_lump;
					piVar5 = (int *)texturename_buffer;
				}
				else {
					if (iVar7 < 0x22) {
						piVar3 = lump_ptr_00;
						if (iVar7 != 0x19) {
							if (iVar7 < 0x1a) {
								if (iVar7 == 0x16) {
									ProcessMotionLump((char *)lump_ptr_00, lump_size_00);
									gLoadedMotionCapture = 1;
									piVar2 = (int *)car_models_lump;
									piVar3 = (int *)palette_lump;
									piVar4 = (int *)map_lump;
									piVar5 = (int *)texturename_buffer;
								}
								else {
									piVar3 = (int *)palette_lump;
									if (iVar7 == 0x18) {
										ProcessOverlayLump((char *)lump_ptr_00, lump_size_00);
										gLoadedOverlay = 1;
										piVar2 = (int *)car_models_lump;
										piVar3 = (int *)palette_lump;
										piVar4 = (int *)map_lump;
										piVar5 = (int *)texturename_buffer;
									}
								}
							}
							else {
								if (iVar7 == 0x1a) {
									ProcessSpoolInfoLump((char *)lump_ptr_00, lump_size);
									ProcessMapLump(map_lump, 0);
									region_buffer_xor = (cells_down >> 5 & 2U | cells_across >> 6 & 1U) << 2;

									// I don't think sdSelfModifyingCode were ever used by the game, but time will tell...
									//sdSelfModifyingCode =
									//	sdSelfModifyingCode ^ (sdSelfModifyingCode ^ region_buffer_xor) & 0xc;

									piVar2 = (int *)car_models_lump;
									piVar3 = (int *)palette_lump;
									piVar4 = (int *)map_lump;
									piVar5 = (int *)texturename_buffer;
								}
								else {
									piVar2 = lump_ptr_00;
									piVar3 = (int *)palette_lump;
									if (iVar7 != 0x1c) {
										piVar2 = (int *)car_models_lump;
									}
								}
							}
						}
					}
					else {
						if (iVar7 == 0x29) {
							ProcessCurvesDriver2Lump((char *)lump_ptr_00, lump_size_00);
							piVar2 = (int *)car_models_lump;
							piVar3 = (int *)palette_lump;
							piVar4 = (int *)map_lump;
							piVar5 = (int *)texturename_buffer;
						}
						else {
							if (iVar7 < 0x2a) {
								if (iVar7 == 0x22) {
									ProcessTextureInfo((char *)lump_ptr_00);
									piVar2 = (int *)car_models_lump;
									piVar3 = (int *)palette_lump;
									piVar4 = (int *)map_lump;
									piVar5 = (int *)texturename_buffer;
								}
								else {
									if (iVar7 == 0x28) {
										ProcessStraightsDriver2Lump((char *)lump_ptr_00, lump_size_00);
										piVar2 = (int *)car_models_lump;
										piVar3 = (int *)palette_lump;
										piVar4 = (int *)map_lump;
										piVar5 = (int *)texturename_buffer;
									}
								}
							}
							else {
								if (iVar7 == 0x2b) {
									ProcessJunctionsDriver2Lump((char *)lump_ptr_00, lump_size_00, 0);
									iVar7 = NumTempJunctions;
									pDVar8 = Driver2JunctionsPtr;
									puVar9 = Driver2TempJunctionsPtr;
									piVar2 = (int *)car_models_lump;
									piVar3 = (int *)palette_lump;
									piVar4 = (int *)map_lump;
									piVar5 = (int *)texturename_buffer;
									if (0 < NumTempJunctions) {
										do {
											iVar7 = iVar7 + -1;
											pDVar8->flags = *puVar9;
											pDVar8 = pDVar8 + 1;
											puVar9 = puVar9 + 1;
											piVar2 = (int *)car_models_lump;
											piVar3 = (int *)palette_lump;
											piVar4 = (int *)map_lump;
											piVar5 = (int *)texturename_buffer;
										} while (iVar7 != 0);
									}
								}
								else {
									if (iVar7 < 0x2b) {
										ProcessJunctionsDriver2Lump((char *)lump_ptr_00, lump_size_00, 1);
										iVar7 = NumTempJunctions;
										pDVar8 = Driver2JunctionsPtr;
										puVar9 = Driver2TempJunctionsPtr;
										piVar2 = (int *)car_models_lump;
										piVar3 = (int *)palette_lump;
										piVar4 = (int *)map_lump;
										piVar5 = (int *)texturename_buffer;
										if (0 < NumTempJunctions) {
											do {
												iVar7 = iVar7 + -1;
												pDVar8->flags = *puVar9;
												pDVar8 = pDVar8 + 1;
												puVar9 = puVar9 + 1;
												piVar2 = (int *)car_models_lump;
												piVar3 = (int *)palette_lump;
												piVar4 = (int *)map_lump;
												piVar5 = (int *)texturename_buffer;
											} while (iVar7 != 0);
										}
									}
									else {
										if (iVar7 == 0xff) {
											bVar1 = true;
										}
									}
								}
							}
						}
					}
				}
				goto LAB_00059028;
			}
			if (iVar7 == 9) {
				ProcessJunctionsLump((char *)lump_ptr_00, lump_size_00);
				piVar2 = (int *)car_models_lump;
				piVar3 = (int *)palette_lump;
				piVar4 = (int *)map_lump;
				piVar5 = (int *)texturename_buffer;
				goto LAB_00059028;
			}
			if (iVar7 < 10) {
				piVar5 = lump_ptr_00;
				if (iVar7 != 5) {
					if (iVar7 < 6) {
						if (iVar7 == 1) {
							ProcessMDSLump((char *)lump_ptr_00, lump_size_00);
							ProcessCarModelLump(car_models_lump, 0);
							InitModelNames();
							SetUpEvents(1);
							piVar2 = (int *)car_models_lump;
							piVar3 = (int *)palette_lump;
							piVar4 = (int *)map_lump;
							piVar5 = (int *)texturename_buffer;
						}
						else {
							piVar4 = lump_ptr_00;
							piVar5 = (int *)texturename_buffer;
							if (iVar7 != 2) {
								piVar4 = (int *)map_lump;
							}
						}
					}
					else {
						if (iVar7 == 7) {
							NewProcessRoadMapLump(&roadMapLumpData, (char *)lump_ptr_00);
							piVar2 = (int *)car_models_lump;
							piVar3 = (int *)palette_lump;
							piVar4 = (int *)map_lump;
							piVar5 = (int *)texturename_buffer;
						}
						else {
							piVar5 = (int *)texturename_buffer;
							if (iVar7 == 8) {
								ProcessRoadsLump((char *)lump_ptr_00, lump_size_00);
								piVar2 = (int *)car_models_lump;
								piVar3 = (int *)palette_lump;
								piVar4 = (int *)map_lump;
								piVar5 = (int *)texturename_buffer;
							}
						}
					}
				}
				goto LAB_00059028;
			}
			if (iVar7 == 0x10) {
				ProcessRoadBoundsLump((char *)lump_ptr_00, lump_size_00);
				piVar2 = (int *)car_models_lump;
				piVar3 = (int *)palette_lump;
				piVar4 = (int *)map_lump;
				piVar5 = (int *)texturename_buffer;
				goto LAB_00059028;
			}
			if (0x10 < iVar7) {
				if (iVar7 == 0x11) {
					ProcessJuncBoundsLump((char *)lump_ptr_00, lump_size_00);
					piVar2 = (int *)car_models_lump;
					piVar3 = (int *)palette_lump;
					piVar4 = (int *)map_lump;
					piVar5 = (int *)texturename_buffer;
				}
				else {
					if (iVar7 == 0x14) {
						ProcessSubDivisionLump((char *)lump_ptr_00, lump_size_00);
						piVar2 = (int *)car_models_lump;
						piVar3 = (int *)palette_lump;
						piVar4 = (int *)map_lump;
						piVar5 = (int *)texturename_buffer;
					}
				}
				goto LAB_00059028;
			}
			if (iVar7 == 10) goto LAB_00059028;
			if (iVar7 == 0xc) {
				uVar6 = lump_size_00 + 3U & 0xfffffffc;
				modelname_buffer = (char *)lump_ptr_00;
			}
			else {
				uVar6 = lump_size_00 + 3U & 0xfffffffc;
			}
		}
		lump_size = lump_size_00 + 3;
		lump_ptr = (char *)((int)lump_ptr_00 + uVar6);
		if (bVar1) {
			return;
		}
	} while (true);
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadGameLevel()
 // line 2896, offset 0x00059050
	/* begin block 1 */
		// Start line: 2898
		// Start offset: 0x00059050
		// Variables:
	// 		int sector; // stack offset -32
	// 		int nsectors; // $s1
	// 		char name[64]; // stack offset -96
	// 		char *malloc_lump; // $s2
	/* end block 1 */
	// End offset: 0x00059238
	// End Line: 2967

	/* begin block 2 */
		// Start line: 5806
	/* end block 2 */
	// End Line: 5807

	/* begin block 3 */
		// Start line: 5809
	/* end block 3 */
	// End Line: 5810

	/* begin block 4 */
		// Start line: 5810
	/* end block 4 */
	// End Line: 5811

	/* begin block 5 */
		// Start line: 5818
	/* end block 5 */
	// End Line: 5819

/* WARNING: Unknown calling convention yet parameter storage is locked */

void LoadGameLevel(void)
{
	UNIMPLEMENTED();
	/*
	char *addr;
	int nsectors;
	int local_20[2];

	seated_pedestrian = (SEATED_PEDESTRIANS *)0x0;
	LoadCosmetics(GameLevel);
	if (gMultiplayerLevels == 0) {
		if (gTimeOfDay == 3) {
			SetCityType(CITYTYPE_NIGHT);
		}
		else {
			SetCityType(CITYTYPE_DAY);
		}
	}
	else {
		if (gTimeOfDay == 3) {
			SetCityType(CITYTYPE_MULTI_NIGHT);
		}
		else {
			SetCityType(CITYTYPE_MULTI_DAY);
		}
	}
	ReportMode(0);
	local_20[0] = citylumps[GameLevel * 4].x;
	if (local_20[0] < 0) {
		local_20[0] = local_20[0] + 2047;
	}
	nsectors = citylumps[GameLevel * 4].y;
	local_20[0] = local_20[0] >> 0xb;
	if (nsectors < 0) {
		nsectors = nsectors + 2047;
	}
	nsectors = nsectors >> 0xb;
	loadsectors(&DAT_000fb400, local_20[0], nsectors);
	local_20[0] = local_20[0] + nsectors;
	ProcessLumps(&DAT_000fb408, nsectors << 0xb);
	LoadPermanentTPages(local_20);
	addr = mallocptr;
	local_20[0] = citylumps[GameLevel * 4 + 2].x;
	if (local_20[0] < 0) {
		local_20[0] = local_20[0] + 0x7ff;
	}
	nsectors = citylumps[GameLevel * 4 + 2].y;
	local_20[0] = local_20[0] >> 0xb;
	if (nsectors < 0) {
		nsectors = nsectors + 0x7ff;
	}
	nsectors = nsectors >> 0xb;
	mallocptr = mallocptr + nsectors * 0x800;
	loadsectors(addr, local_20[0], nsectors);
	local_20[0] = local_20[0] + nsectors;
	ProcessLumps(addr + 8, nsectors * 0x800);
	SpoolLumpOffset = citylumps[GameLevel * 4 + 3].x;
	Init_Reflection_Mapping();
	InitDebrisNames();
	InitShadow();
	InitTextureNames();
	ReportMode(1);
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ ReplayLog_Fnarr_He_Said_Log(int val /*$a0*/)
 // line 2973, offset 0x0005c81c
	/* begin block 1 */
		// Start line: 5946
	/* end block 1 */
	// End Line: 5947

	/* begin block 2 */
		// Start line: 9921
	/* end block 2 */
	// End Line: 9922

int ReplayLog_Fnarr_He_Said_Log(int val)
{
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitModelNames()
 // line 3003, offset 0x00059238
	/* begin block 1 */
		// Start line: 3005
		// Start offset: 0x00059238
	/* end block 1 */
	// End offset: 0x00059330
	// End Line: 3067

	/* begin block 2 */
		// Start line: 6005
	/* end block 2 */
	// End Line: 6006

	/* begin block 3 */
		// Start line: 6042
	/* end block 3 */
	// End Line: 6043

	/* begin block 4 */
		// Start line: 6043
	/* end block 4 */
	// End Line: 6044

	/* begin block 5 */
		// Start line: 6050
	/* end block 5 */
	// End Line: 6051

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitModelNames(void)
{
	UNIMPLEMENTED();
	/*
	gHubcapModelPtr = FindModelPtrWithName(s_HUBCAP1_000aa648);
	gCleanWheelModelPtr = FindModelPtrWithName(s_CLEANWHEEL_00010cd0);
	gFastWheelModelPtr = FindModelPtrWithName(s_FASTWHEEL_00010cdc);
	gDamWheelModelPtr = FindModelPtrWithName(s_DAMWHEEL_00010ce8);
	gPed1HeadModelPtr = FindModelPtrWithName(s_PEDHEAD1_00010cf4);
	gPed2HeadModelPtr = FindModelPtrWithName(&DAT_000aa650);
	gPed3HeadModelPtr = FindModelPtrWithName(&DAT_000aa650);
	gPed4HeadModelPtr = FindModelPtrWithName(&DAT_000aa650);
	gBoxModelPtr = FindModelPtrWithName(s_CRATE_000aa658);
	gRotorPtr = FindModelPtrWithName(s_ROTOR_000aa660);
	gTrailblazerConeModel = FindModelPtrWithName(s_GREENCONE_00010d00);
	gBombModel = FindModelPtrWithName(&DAT_000aa668);
	MangleWheelModels();
	InitTanner();
	InitAnimatingObjects();
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GameInit()
 // line 3114, offset 0x00059330
	/* begin block 1 */
		// Start line: 3122
		// Start offset: 0x00059330

		/* begin block 1.1 */
			// Start line: 3226
			// Start offset: 0x000594C0
		/* end block 1.1 */
		// End offset: 0x000594D4
		// End Line: 3228

		/* begin block 1.2 */
			// Start line: 3263
			// Start offset: 0x000595B4
		/* end block 1.2 */
		// End offset: 0x000595B4
		// End Line: 3263

		/* begin block 1.3 */
			// Start line: 3271
			// Start offset: 0x000595DC
		/* end block 1.3 */
		// End offset: 0x00059604
		// End Line: 3277

		/* begin block 1.4 */
			// Start line: 3305
			// Start offset: 0x000596B0
			// Variables:
		// 		struct STREAM_SOURCE *pinfo; // $s0
		// 		char padid; // stack offset -48
		// 		int i; // $s2
		/* end block 1.4 */
		// End offset: 0x0005980C
		// End Line: 3359

		/* begin block 1.5 */
			// Start line: 3442
			// Start offset: 0x00059944
			// Variables:
		// 		int loop; // $s0

			/* begin block 1.5.1 */
				// Start line: 3445
				// Start offset: 0x0005994C
			/* end block 1.5.1 */
			// End offset: 0x0005994C
			// End Line: 3445
		/* end block 1.5 */
		// End offset: 0x0005996C
		// End Line: 3447

		/* begin block 1.6 */
			// Start line: 3455
			// Start offset: 0x0005998C
			// Variables:
		// 		int i; // $v1
		/* end block 1.6 */
		// End offset: 0x000599B8
		// End Line: 3460

		/* begin block 1.7 */
			// Start line: 3464
			// Start offset: 0x000599B8
		/* end block 1.7 */
		// End offset: 0x000599B8
		// End Line: 3475

		/* begin block 1.8 */
			// Start line: 3504
			// Start offset: 0x00059A0C
		/* end block 1.8 */
		// End offset: 0x00059A14
		// End Line: 3506
	/* end block 1 */
	// End offset: 0x00059A44
	// End Line: 3509

	/* begin block 2 */
		// Start line: 6262
	/* end block 2 */
	// End Line: 6263

	/* begin block 3 */
		// Start line: 6310
	/* end block 3 */
	// End Line: 6311

	/* begin block 4 */
		// Start line: 6317
	/* end block 4 */
	// End Line: 6318

/* WARNING: Unknown calling convention yet parameter storage is locked */

char g_allocatedMem[0x200000];	// 0x137400 (_ramsize). TODO: use real malloc
char* mallocptr = g_allocatedMem;

#define D_MALLOC(size)	mallocptr; mallocptr += size

// TODO: SPOOL?
char *packed_cell_pointers;
PACKED_CELL_OBJECT** pcoplist;
ulong* transparent_buffer;
ulong* tile_overflow_buffer;
CELL_OBJECT** coplist;

// system?
int gameinit = 0;
int leadAIRequired = 0;
int leadAILoaded = 0;
int pathAILoaded = 0;
int gMusicType = 0;
int allowSpecSpooling = 0;
int xa_timeout = 0;

int ThisMotion = 0;
int IconsLoaded = 0;

// TODO: AI.C?
SPEECH_QUEUE gSpeechQueue;

// TODO: CAMERA.C
char cameraview = 0;
int CameraCnt = 0;

// TODO: DIRECTOR.C
char tracking_car = 0;

// MISSION
_MISSION *MissionHeader;

// MGENERIC?
_PLAYER player[8];
STREAM_SOURCE* PlayerStartInfo[8];
int numPlayersToCreate = 0;
int gStartOnFoot = 0;
int gSinkingTimer = 100;
int gTimeInWater = 0x19;
char InWater = 0;
int gBobIndex = 0;
int gWeather = 0;
int gTimeOfDay = 0;
int gShowPlayerDamage = 0;

// PHYSICS
_CAR_DATA car_data[22];	// all cars

// active cars
_CAR_DATA* active_car_list[20];
BOUND_BOX bbox[20];
unsigned char lightsOnDelay[20];

// OVERLAY
int gLoadedOverlay = 0;

// MOTION_C
int gLoadedMotionCapture = 0;

// DRAWGAME.C ???
int FrAng = 0x200;
int wetness = 0;

// [D]
void GameInit(void)
{
	long lVar1;
	_PLAYER *p_Var2;
	STREAM_SOURCE *pSVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	char local_30[8];
	short totaldam;

	if (NewLevel == 0) {
		SetPleaseWait(NULL);
	}
	else {
		packed_cell_pointers = D_MALLOC(0x1000);
	}
	gameinit = 1;
	InitGameVariables();
	InitEvents();
	InitPadRecording();
	InitSpeechQueue(&gSpeechQueue);
	if (NewLevel != 0) {
		leadAIRequired = 0;
		leadAILoaded = 0;
		pathAILoaded = 0;
	}
	LoadMission(gCurrentMissionNumber);
	if (gCurrentMissionNumber == 0x26) {
		MissionHeader->residentModels[4] = 9;
	}
	if (GameType == GAME_MISSION) {
		SetupFadePolys();
	}
	if (NewLevel != 0) {
		ShowLoadingScreen(LoadingScreenNames[GameLevel], 1, 0x24);
	}
	if (AttractMode != 0) {
		TriggerInGameCutscene(0);
		NoPlayerControl = 1;
	}
	ResetSound();
	LockChannel(0);
	LockChannel(1);
	LockChannel(2);
	if (NumPlayers == 2) {
		LockChannel(3);
		LockChannel(4);
		LockChannel(5);
	}
	if (NewLevel != 0) {
		ShowLoading();
		LoadLevelSFX(gCurrentMissionNumber);
	}
	PauseSound();
	ThisMotion = 0;
	if (GameLevel == 1) {
		gMusicType = 1;
		if ((gCurrentMissionNumber & 1U) != 0) {
			gMusicType = 5;
		}
	}
	else {
		if (GameLevel < 2) {
			if ((GameLevel == 0) && (gMusicType = 2, (gCurrentMissionNumber & 1U) != 0)) {
				gMusicType = 6;
			}
		}
		else {
			if (GameLevel == 2) {
				gMusicType = 0;
				if ((gCurrentMissionNumber & 1U) == 0) {
					gMusicType = 3;
				}
			}
			else {
				if ((GameLevel == 3) && (gMusicType = 4, (gCurrentMissionNumber & 1U) != 0)) {
					gMusicType = 7;
				}
			}
		}
	}
	InitMusic(gMusicType);
	if (NewLevel == 0) {
		if (IconsLoaded == 0) {
			ReloadIcons();
		}
		IconsLoaded = 1;
		SetUpEvents(0);
	}
	else {
		LoadGameLevel();
		IconsLoaded = 1;
		LoadSky();
		LoadFont(NULL);
	}
	ClearMem((char *)car_data, 0x3968);
	player[0].spoolXZ = (VECTOR *)car_data[0].hd.where.t;
	car_data[0].hd.where.t[0] = (PlayerStartInfo[0]->position).vx;
	car_data[0].hd.where.t[2] = (PlayerStartInfo[0]->position).vz;
	CalcObjectRotationMatrices();
	InitialiseDenting();
	cameraview = 0;
	if (gLoadedMotionCapture != 0) {
		InitPedestrians();
	}
	InitSpooling();
	InitMap();
	InitSpecSpool();
	if ((NewLevel == 0) && (allowSpecSpooling == 1)) {
		QuickSpoolSpecial();
	}
	iVar4 = 0;
	int_garage_door();
	SpoolSYNC();
	InitialiseCarHandling();
	ClearMem((char *)&player, 0x3a0);
	InitDrivingGames();
	InitThrownBombs();
	if (0 < numPlayersToCreate) {
		iVar6 = 0;
		iVar5 = 0;
		do {
			pSVar3 = PlayerStartInfo[iVar4];
			local_30[0] = -(char)iVar4;

			if (iVar4 < (int)(uint)NumPlayers) {
				local_30[0] = (char)iVar4;
			}
			gStartOnFoot = (pSVar3->type == '\x02');

			InitPlayer((_PLAYER *)((int)player[0].pos + iVar5),
				(_CAR_DATA *)((int)car_data[0].hd.where.m + iVar6), pSVar3->controlType,
				(uint)pSVar3->rotation, (long(*)[4])&pSVar3->position, (uint)pSVar3->model,
				(uint)pSVar3->palette, local_30);

			if (gStartOnFoot == 0) {
				// copy damage values
				*(u_short *)((int)car_data[0].ap.damage + iVar6) = *(u_short *)pSVar3->damage;
				*(u_short *)((int)car_data[0].ap.damage + iVar6 + 2) =*(u_short *)(pSVar3->damage + 1);
				*(u_short *)((int)car_data[0].ap.damage + iVar6 + 4) =*(u_short *)(pSVar3->damage + 2);
				*(u_short *)((int)car_data[0].ap.damage + iVar6 + 6) =*(u_short *)(pSVar3->damage + 3);
				*(u_short *)((int)car_data[0].ap.damage + iVar6 + 8) =*(u_short *)(pSVar3->damage + 4);
				*(u_short *)((int)car_data[0].ap.damage + iVar6 + 10) =*(u_short *)(pSVar3->damage + 5);

				totaldam = *(short *)&pSVar3->totaldamage;
				(&car_data[0].ap.needsDenting)[iVar6] = '\x01';
				*(short *)((int)&car_data[0].totalDamage + iVar6) = totaldam;
			}

			iVar6 = iVar6 + 0x29c;	//sizeof(_CAR_DATA)
			iVar4 = iVar4 + 1;
			iVar5 = iVar5 + 0x74;	// sizeof(_PLAYER)
		} while (iVar4 < numPlayersToCreate);
	}
	if (pathAILoaded != 0) {
		InitCops();
	}
	InitCamera(&player[0]);
	if ((gLoadedOverlay != 0) && (NoPlayerControl == 0)) {
		InitOverlays();
		IconsLoaded = 0;
	}
	gSinkingTimer = 100;
	gTimeInWater = 0x19;
	InWater = 0;
	gBobIndex = 0;
	SetupRain();
	InitExObjects();
	if (NewLevel != 0) {
		pcoplist = (PACKED_CELL_OBJECT **)(mallocptr + 1024);
		transparent_buffer = (ulong *)(mallocptr + 2048);
		tile_overflow_buffer = (ulong *)mallocptr;
		coplist = (CELL_OBJECT **)mallocptr;
		mallocptr = mallocptr + 0x900;
	}
	if (NoPlayerControl == 0) {
		DeleteAllCameras();
	}
	else {
		FindNextChange(CameraCnt);
	}
	FrAng = 0x200;
	if (gWeather == 1) {
		wetness = 0x1b58;
	}
	else {
		wetness = 0;
	}
	if (gTimeOfDay == 2) {
		iVar4 = 0;
		do {
			lVar1 = Random2(0);
			lightsOnDelay[iVar4] = (unsigned char)lVar1;
			iVar4 = iVar4 + 1;
		} while (iVar4 < 0x14);
	}
	tracking_car = '\x01';
	if (NoPlayerControl == 0) {
		StoreGameFlags();
	}
	SetReverbState(0);
	p_Var2 = (_PLAYER*)&player;
	iVar4 = 2;
	do {
		(p_Var2->horn).request = '\0';
		(p_Var2->horn).time = '\0';
		(p_Var2->horn).on = '\0';
		iVar4 = iVar4 + -1;
		p_Var2 = p_Var2 + 1;
	} while (-1 < iVar4);
	gShowPlayerDamage = 1;
	InitThunder();
	GetXAData(-1);
	SetXAVolume(0);
	if (true) {
		switch (gCurrentMissionNumber) {
		case 2:
		case 3:
		case 6:
		case 0xb:
		case 0xd:
		case 0xe:
		case 0x13:
		case 0x1a:
		case 0x1c:
		case 0x22:
		case 0x26:
			FunkUpDaBGMTunez(1);
		}
	}
	xa_timeout = 0;
}

// decompiled code
// original method signature: 
// void /*$ra*/ StepSim()
 // line 3555, offset 0x00059a44
	/* begin block 1 */
		// Start line: 3557
		// Start offset: 0x00059A44
		// Variables:
	// 		static unsigned long t0; // offset 0x0
	// 		static char t1; // offset 0x4
	// 		static char t2; // offset 0x5
	// 		static int oldsp; // offset 0x8
	// 		struct _CAR_DATA *lcp; // $s0
	// 		int i; // $s2

		/* begin block 1.1 */
			// Start line: 3633
			// Start offset: 0x00059C70
			// Variables:
		// 		int eekTimer; // $s0

			/* begin block 1.1.1 */
				// Start line: 3639
				// Start offset: 0x00059CC4
			/* end block 1.1.1 */
			// End offset: 0x00059CC4
			// End Line: 3641
		/* end block 1.1 */
		// End offset: 0x00059D20
		// End Line: 3645

		/* begin block 1.2 */
			// Start line: 3649
			// Start offset: 0x00059D6C
		/* end block 1.2 */
		// End offset: 0x00059D6C
		// End Line: 3653

		/* begin block 1.3 */
			// Start line: 3556
			// Start offset: 0x00059FD8
		/* end block 1.3 */
		// End offset: 0x00059FD8
		// End Line: 3556

		/* begin block 1.4 */
			// Start line: 3838
			// Start offset: 0x0005A220
			// Variables:
		// 		int padsteer; // $a1

			/* begin block 1.4.1 */
				// Start line: 3868
				// Start offset: 0x0005A320
			/* end block 1.4.1 */
			// End offset: 0x0005A33C
			// End Line: 3872

			/* begin block 1.4.2 */
				// Start line: 3879
				// Start offset: 0x0005A374
			/* end block 1.4.2 */
			// End offset: 0x0005A374
			// End Line: 3879
		/* end block 1.4 */
		// End offset: 0x0005A374
		// End Line: 3879

		/* begin block 1.5 */
			// Start line: 3886
			// Start offset: 0x0005A394
		/* end block 1.5 */
		// End offset: 0x0005A3C8
		// End Line: 3888

		/* begin block 1.6 */
			// Start line: 3983
			// Start offset: 0x0005A650
			// Variables:
		// 		int i; // $s1
		// 		int j; // $s0
		// 		static int stupid_logic[4]; // offset 0x0

			/* begin block 1.6.1 */
				// Start line: 4003
				// Start offset: 0x0005A744
			/* end block 1.6.1 */
			// End offset: 0x0005A794
			// End Line: 4005
		/* end block 1.6 */
		// End offset: 0x0005A7B0
		// End Line: 4006

		/* begin block 1.7 */
			// Start line: 4033
			// Start offset: 0x0005A894
		/* end block 1.7 */
		// End offset: 0x0005A8AC
		// End Line: 4036
	/* end block 1 */
	// End offset: 0x0005A8DC
	// End Line: 4039

	/* begin block 2 */
		// Start line: 7193
	/* end block 2 */
	// End Line: 7194

	/* begin block 3 */
		// Start line: 7240
	/* end block 3 */
	// End Line: 7241

	/* begin block 4 */
		// Start line: 7241
	/* end block 4 */
	// End Line: 7242

	/* begin block 5 */
		// Start line: 7263
	/* end block 5 */
	// End Line: 7264

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StepSim(void)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	ushort uVar2;
	short *psVar3;
	int *piVar4;
	undefined3 extraout_var;
	int stream;
	undefined4 uVar5;
	int *piVar6;
	uint uVar7;
	_CAR_DATA *cp;
	_PLAYER *p_Var8;
	int i;
	int car;

	if ((gTimeOfDay == 0) || (gTimeOfDay == 2)) {
		DawnCount = DawnCount + 1;
	}
	SetUpTrafficLightPhase();
	MoveSmashable_object();
	animate_garage_door();
	StepEvents();
	HandleMission();
	HandleInGameCutscene();
	HandleDrivingGames();
	num_active_cars = 0;
	if ((NoPlayerControl != 0) && (ReplayParameterPtr->RecordingEnd + -2 < CameraCnt)) {
		ReleaseInGameCutscene();
		pauseflag = 1;
	}
	oldsp_21 = SetSp(&DAT_1f8003e8);
	lead_pad = (ulong)controller_bits;
	if ((int)player.playerCarId < 0) {
		psVar3 = &pedestrianFelony;
	}
	else {
		psVar3 = &car_data[(int)player.playerCarId].felonyRating;
	}
	if ((*psVar3 < 0x527) || (numRoadblockCars != 0)) {
	LAB_00059c00:
		if (roadblockCount == 0) goto LAB_00059c1c;
	}
	else {
		if (roadblockCount == 0) {
			if (((copsAreInPursuit != 0) && (MissionHeader->residentModels[3] == 0)) &&
				(gCurrentMissionNumber != 0x1a)) {
				requestRoadblock = 1;
			}
			goto LAB_00059c00;
		}
	}
	roadblockCount = roadblockCount + -1;
LAB_00059c1c:
	if ((requestStationaryCivCar == 1) || (requestRoadblock != 0)) {
		distFurthestCivCarSq = 0;
	}
	else {
		i = 0;
		if (gInGameChaseActive == 0) {
			if ((numCivCars < maxCivCars) && (NumPlayers == 1)) {
				i = 0;
				while ((i < 5 && (car = PingInCivCar((int)&DAT_00003e1c), car == 0))) {
					i = i + 1;
				}
			}
		}
		else {
			if ((PingBufferPos < 400) &&
				((uint)PingBuffer[PingBufferPos].frame <= (CameraCnt - frameStart & 0xffffU))) {
				while (true) {
					PingInCivCar((int)&DAT_00003e1c);
					i = i + 1;
					if (399 < PingBufferPos) break;
					if (((CameraCnt - frameStart & 0xffffU) < (uint)PingBuffer[PingBufferPos].frame) ||
						(10 < i)) break;
				}
			}
		}
		SetUpCivCollFlags();
	}
	uVar7 = 0xd43fc;
	numRoadblockCars = 0;
	numInactiveCars = 0;
	numParkedCars = 0;
	numActiveCops = 0;
	numCopCars = 0;
	numCivCars = 0;
	do {
		cVar1 = *(char *)(uVar7 + 0x189);
		if (cVar1 == '\x02') {
			numCivCars = numCivCars + 1;
			if ((*(byte *)(uVar7 + 0x18a) & 1) != 0) {
				numCopCars = numCopCars + 1;
			}
			if (((*(byte *)(uVar7 + 0x18a) & 2) != 0) && (*(char *)(uVar7 + 0x285) == '\x03')) {
				if (*(char *)(uVar7 + 0x198) == '\x05') {
					numParkedCars = numParkedCars + 1;
				}
				if ((*(byte *)(uVar7 + 0x18a) & 2) != 0) {
					numRoadblockCars = numRoadblockCars + 1;
				}
			}
		}
		else {
			if (cVar1 == '\x03') {
				numCopCars = numCopCars + 1;
				if (*(char *)(uVar7 + 0x19f) == '\0') {
					numActiveCops = numActiveCops + 1;
				}
			}
			else {
				if (cVar1 == '\0') {
					numInactiveCars = numInactiveCars + 1;
				}
			}
		}
		uVar7 = uVar7 - 0x29c;
	} while (0xd1267 < uVar7);
	if (numRoadblockCars != 0) {
		roadblockCount = roadblockDelay;
	}
	if ((((requestStationaryCivCar == 0) && (requestRoadblock != 0)) && (numRoadblockCars == 0)) &&
		(4 < maxCivCars - numCivCars)) {
		CreateRoadblock();
	}
	cp = car_data + 0x13;
	if (gInGameCutsceneActive == 0) {
		CheckSpecialSpool();
	}
	while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < cp) {
		switch (cp->controlType) {
		case '\x01':
			t0_18 = (ulong)Pads[**(char **)cp->ai].mapped;
			t1_19 = Pads[**(char **)cp->ai].mapanalog[2];
			t2_20 = Pads[**(char **)cp->ai].type & 4;
			if (NoPlayerControl == 0) {
				if (gStopPadReads != 0) {
					t0_18 = 0x80;
					if ((cp->hd).wheel_speed < 0x9001) {
						t0_18 = 0x10;
					}
					t1_19 = '\0';
					t2_20 = 1;
				}
				cjpRecord((int)**(char **)cp->ai, &t0_18, &t1_19, &t2_20);
			}
			else {
				cjpPlay((int)**(char **)cp->ai, &t0_18, &t1_19, &t2_20);
			}
			ProcessCarPad(cp, t0_18, t1_19, t2_20);
			break;
		case '\x02':
			CivControl(cp);
			break;
		case '\x03':
			CopControl(cp);
			break;
		case '\x04':
			t2_20 = 0;
			t1_19 = '\0';
			t0_18 = 0;
			t0_18 = func_0x000ec99c(cp);
			if (t0_18 == 0) {
				cp->handbrake = '\x01';
				cp->wheel_angle = 0;
			}
			else {
				ProcessCarPad(cp, t0_18, t1_19, t2_20);
			}
			break;
		case '\a':
			cjpPlay(-(int)**(char **)cp->ai, &t0_18, &t1_19, &t2_20);
			ProcessCarPad(cp, t0_18, t1_19, t2_20);
		}
		StepCarPhysics(cp);
		cp = cp + -1;
	}
	i = 0;
	p_Var8 = &player;
	car = 7;
	do {
		if (p_Var8->playerType == '\x02') {
			stream = (int)p_Var8->padid;
			if (stream < 0) {
				stream = cjpPlay(-stream, &t0_18, &t1_19, &t2_20);
				if (stream != 0) {
					ProcessTannerPad(*(PEDESTRIAN **)((int)&player.pPed + i), t0_18, t1_19, t2_20);
				}
			}
			else {
				if (Pads[stream].type == '\x04') {
					cVar1 = Pads[stream].mapanalog[3];
					if ((cVar1 < -0x40) && (-100 < cVar1)) {
						Pads[stream].mapped = Pads[stream].mapped | 0x1008;
					}
					else {
						if ((cVar1 < -100) && ('\x7f' < cVar1)) {
							stream = (int)p_Var8->padid;
							uVar2 = Pads[stream].mapped | 0x1000;
						}
						else {
							if (cVar1 < '!') goto LAB_0005a2dc;
							stream = (int)p_Var8->padid;
							uVar2 = Pads[stream].mapped | 0x4000;
						}
						(&Pads[0].mapped)[stream * 0x24] = uVar2;
					}
				}
			LAB_0005a2dc:
				stream = (int)(&player.padid)[i];
				t0_18 = (ulong)Pads[stream].mapped;
				t1_19 = Pads[stream].mapanalog[2];
				t2_20 = Pads[stream].type & 4;
				if (NoPlayerControl == 0) {
					if (gStopPadReads != 0) {
						t2_20 = 0;
						t1_19 = '\0';
						t0_18 = 0;
					}
					cjpRecord(stream, &t0_18, &t1_19, &t2_20);
				}
				else {
					stream = cjpPlay(stream, &t0_18, &t1_19, &t2_20);
					if (stream == 0) goto LAB_0005a3d0;
				}
				ProcessTannerPad(*(PEDESTRIAN **)((int)&player.pPed + i), t0_18, t1_19, t2_20);
			}
		}
	LAB_0005a3d0:
		i = i + 0x74;
		p_Var8 = p_Var8 + 1;
		car = car + -1;
	} while (-1 < car);
	if ((requestStationaryCivCar == 1) &&
		((numCivCars < maxCivCars ||
		(PingOutCar(car_data + (byte)furthestCivID), numCivCars < maxCivCars)))) {
		requestStationaryCivCar = 0;
	}
	if ((game_over == 0) && (ControlCops(), gLoadedMotionCapture != 0)) {
		HandlePedestrians();
	}
	i = 0;
	GlobalTimeStep();
	UpdatePlayers();
	DoScenaryCollisions();
	CheckPlayerMiscFelonies();
	SetSp(oldsp_21);
	CameraCnt = CameraCnt + 1;
	gBobIndex = gBobIndex + 0x3cU & 0xfff;
	if (NumPlayers != 0) {
		car = 0;
		p_Var8 = &player;
		do {
			if ((p_Var8->horn).on == '\0') {
			LAB_0005a5b8:
				stream = CarHasSiren((uint)(byte)car_data[(&player.playerCarId)[car]].ap.model);
				if ((stream == 0) && (p_Var8->pPed == (PEDESTRIAN *)0x0)) {
					stream = 2;
					if (i != 0) {
						stream = 5;
					}
					StopChannel(stream);
					(&player.horn.request)[car] = '\0';
					(&player.horn.time)[car] = '\0';
				}
			}
			else {
				uVar5 = 4;
				if (i != 0) {
					uVar5 = 0x20;
				}
				stream = SpuGetKeyStatus(uVar5);
				if (stream == 0) {
					stream = CarHasSiren((uint)(byte)car_data[p_Var8->playerCarId].ap.model);
					if (((stream == 0) && (p_Var8->pPed == (PEDESTRIAN *)0x0)) &&
						((p_Var8->horn).request == '\0')) {
						(p_Var8->horn).request = '\x01';
					}
					(p_Var8->horn).time = '\v';
				}
				else {
					if ((p_Var8->horn).on == '\0') goto LAB_0005a5b8;
				}
			}
			DealWithHorn(&player.horn.request + car, i);
			car = car + 0x74;
			i = i + 1;
			p_Var8 = p_Var8 + 1;
		} while (i < (int)(uint)NumPlayers);
	}
	SoundTasks();
	if (((gInGameCutsceneActive == 0) || (gCurrentMissionNumber != 0x17)) || (gInGameCutsceneID != 0))
	{
		stupid_logic_22 = (int)player.playerCarId;
	}
	else {
		stupid_logic_22 = 2;
	}
	i = 0;
	piVar4 = &stupid_logic_22;
	DAT_000d565c = (int)_PLAYER_ARRAY_000d979c[0].playerCarId;
	DAT_000d5660 = gThePlayerCar;
	DAT_000d5664 = leadCarId;
	do {
		car = i + 1;
		if (car < 4) {
			piVar6 = &stupid_logic_22 + car;
			do {
				if (*piVar4 == *piVar6) {
					*piVar6 = -1;
				}
				car = car + 1;
				piVar6 = piVar6 + 1;
			} while (car < 4);
		}
		i = i + 1;
		piVar4 = piVar4 + 1;
	} while (i < 3);
	car = 0;
	piVar4 = &stupid_logic_22;
	i = 0;
	do {
		stream = i;
		if ((*piVar4 != -1) && (cVar1 = SilenceThisCar(car), CONCAT31(extraout_var, cVar1) == 0)) {
			stream = i + 1;
			CheckCarEffects(car_data + *piVar4, i);
		}
		car = car + 1;
		piVar4 = piVar4 + 1;
	} while ((car < 4) && (i = stream, stream < 2));
	SwirlLeaves(car_data);
	if ((gStopPadReads == 1) &&
		(((lead_car != 0 && (saved_counter = saved_counter + 1, 0x14 < saved_counter)) &&
		(saved_leadcar_pos == 0)))) {
		saved_leadcar_pos = gStopPadReads;
		leadcar_pos.vx = car_data[lead_car].hd.where.t[0];
		leadcar_pos.vy = car_data[lead_car].hd.where.t[1];
		leadcar_pos.vz = car_data[lead_car].hd.where.t[2];
	}
	if ((gInGameCutsceneActive == 0) &&
		(((car = XAPrepared(), i = xa_timeout, car != 0 && (i = xa_timeout + -1, xa_timeout == 0)) ||
		(xa_timeout = i, xa_timeout == 0)))) {
		StopXA();
		UnprepareXA();
		StartSpooling();
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GameLoop()
 // line 4046, offset 0x0005a8dc
	/* begin block 1 */
		// Start line: 4048
		// Start offset: 0x0005A8DC
		// Variables:
	// 		int i; // $s0
	// 		struct RECT dest; // stack offset -24

		/* begin block 1.1 */
			// Start line: 4125
			// Start offset: 0x0005AA2C
			// Variables:
		// 		static struct POLY_FT3 buffer[2]; // offset 0x10
		// 		static struct POLY_FT3 *null; // offset 0xc
		/* end block 1.1 */
		// End offset: 0x0005AA98
		// End Line: 4140
	/* end block 1 */
	// End offset: 0x0005AB28
	// End Line: 4188

	/* begin block 2 */
		// Start line: 8546
	/* end block 2 */
	// End Line: 8547

	/* begin block 3 */
		// Start line: 8554
	/* end block 3 */
	// End Line: 8555

	/* begin block 4 */
		// Start line: 8555
	/* end block 4 */
	// End Line: 8556

	/* begin block 5 */
		// Start line: 8575
	/* end block 5 */
	// End Line: 8576

/* WARNING: Unknown calling convention yet parameter storage is locked */

void GameLoop(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	if (NewLevel != 0) {
		CloseShutters(2, 0x140, 0x200);
	}
	DisableDisplay();
	SetupDrawBuffers();
	EnableDisplay();
	srand((uint)&DAT_00001234);
	cameraview = 0;
	FrameCnt = 0;
	NoTextureMemory = 0;
	SpoolSYNC();
	if (CurrentGameMode != '\x04') {
		UnPauseSound();
	}
	iVar1 = 4;
	StartGameSounds();
	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);
	CloseControllers();
	InitControllers();
	VSync(0);
	do {
		iVar1 = iVar1 + -1;
		ReadControllers();
		VSync(0);
	} while (-1 < iVar1);
	while (game_over == 0) {
		StepGame();
		if ((FastForward == 0) || (FrameCnt == (FrameCnt / 7) * 7)) {
			DrawGame();
		}
		else {
			FrameCnt = FrameCnt + 1;
			iVar1 = (FrameCnt & 1U) * 0x20;
			null_27 = &buffer_26 + iVar1;
			*(undefined *)(iVar1 + 0xd566b) = 7;
			*(undefined *)(iVar1 + 0xd566f) = 0x24;
			*(undefined2 *)(iVar1 + 0xd5670) = 0xffff;
			*(undefined2 *)(iVar1 + 0xd5672) = 0xffff;
			*(undefined2 *)(iVar1 + 0xd5678) = 0xffff;
			*(undefined2 *)(iVar1 + 0xd567a) = 0xffff;
			*(undefined2 *)(iVar1 + 0xd5680) = 0xffff;
			*(undefined2 *)(iVar1 + 0xd5682) = 0xffff;
			*(undefined2 *)(iVar1 + 0xd567e) = 0x20;
			DrawPrim(&buffer_26 + iVar1);
			DrawSync(0);
		}
		CheckForPause();
	}
	if (NoPlayerControl == 0) {
		ReplayParameterPtr->RecordingEnd = CameraCnt;
	}
	StopPadVibration(0);
	StopPadVibration(1);
	StopAllChannels();
	FreeXM();
	iVar1 = XAPrepared();
	if (iVar1 != 0) {
		StopXA();
		UnprepareXA();
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepGame()
 // line 4196, offset 0x0005ab28
	/* begin block 1 */
		// Start line: 4198
		// Start offset: 0x0005AB28

		/* begin block 1.1 */
			// Start line: 4238
			// Start offset: 0x0005AB60
		/* end block 1.1 */
		// End offset: 0x0005AB70
		// End Line: 4240

		/* begin block 1.2 */
			// Start line: 4252
			// Start offset: 0x0005ABD8
			// Variables:
		// 		int i; // $a1
		/* end block 1.2 */
		// End offset: 0x0005AC3C
		// End Line: 4262

		/* begin block 1.3 */
			// Start line: 4336
			// Start offset: 0x0005AE20
		/* end block 1.3 */
		// End offset: 0x0005AE50
		// End Line: 4345

		/* begin block 1.4 */
			// Start line: 4361
			// Start offset: 0x0005AEC0
		/* end block 1.4 */
		// End offset: 0x0005AED0
		// End Line: 4368

		/* begin block 1.5 */
			// Start line: 4395
			// Start offset: 0x0005AF6C
			// Variables:
		// 		int strobe; // $v0
		/* end block 1.5 */
		// End offset: 0x0005AFB8
		// End Line: 4398

		/* begin block 1.6 */
			// Start line: 4536
			// Start offset: 0x0005B2E4
		/* end block 1.6 */
		// End offset: 0x0005B31C
		// End Line: 4538
	/* end block 1 */
	// End offset: 0x0005B384
	// End Line: 4547

	/* begin block 2 */
		// Start line: 8865
	/* end block 2 */
	// End Line: 8866

	/* begin block 3 */
		// Start line: 8874
	/* end block 3 */
	// End Line: 8875

	/* begin block 4 */
		// Start line: 8875
	/* end block 4 */
	// End Line: 8876

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StepGame(void)
{
	UNIMPLEMENTED();

	/*
	char cVar1;
	int iVar2;
	uint uVar3;
	uchar *puVar4;
	_PLAYER *p_Var5;

	if (CameraCnt == 3) {
		StartXM(0);
	}
	if (doSpooling != 0) {
		CheckValidSpoolData();
		ControlMap();
	}
	if (gTimeOfDay == 3) {
		PreLampStreak();
	}
	UpdatePadData();
	if (FrameCnt == 5) {
		SetDispMask(1);
	}
	if (((padd & 0x2000U) != 0) && ((padd & 0x8000U) != 0)) {
		padd = padd & 0x5fff;
	}
	uVar3 = (uint)NumPlayers;
	controller_bits = padd;
	if (NumPlayers != 0) {
		p_Var5 = &player;
		do {
			cVar1 = (p_Var5->horn).time;
			if ((cVar1 == '\0') || ((p_Var5->horn).on == '\0')) {
				(p_Var5->horn).time = '\0';
			}
			else {
				(p_Var5->horn).time = cVar1 + -1;
			}
			uVar3 = uVar3 - 1;
			p_Var5 = p_Var5 + 1;
		} while (uVar3 != 0);
	}
	ModifyCamera();
	lis_pos.vx = camera_position.vx;
	lis_pos.vy = camera_position.vy;
	lis_pos.vz = camera_position.vz;
	lis_pos.pad = camera_position.pad;
	FrAng = ratan2(0xa0, scr_z);
	if ((gTimeInWater == 0) || (gSinkingTimer < 100)) {
		gStopPadReads = 1;
		TargetCar = 0;
		cameraview = 0;
		gSinkingTimer = gSinkingTimer + -1;
		gCameraAngle = gCameraAngle - 0x16U & 0xfff;
		if (gCameraDistance < 1000) {
			gCameraMaxDistance = gCameraMaxDistance + 8;
			gCameraDistance = gCameraDistance + 8;
		}
		if (-1000 < CameraPos.vy) {
			CameraPos.vy = CameraPos.vy + -8;
		}
		if (gSinkingTimer < 0) {
			EnablePause(PAUSEMODE_GAMEOVER);
		}
	}
	if (gTimeOfDay == 1) {
		gLightsOn = 0;
		iVar2 = 0x4e;
		if (1 < gWeather - 1U) {
			iVar2 = 0x80;
		}
		goto LAB_0005aea0;
	}
	if (gTimeOfDay < 2) {
		if (gTimeOfDay == 0) {
			NightAmbient = (DawnCount >> 7) + 0x1a;
			gLightsOn = ZEXT14(DawnCount < 4000);
			iVar2 = 0x60;
			if (0x60 < NightAmbient) goto LAB_0005aea0;
		}
	}
	else {
		if (gTimeOfDay == 2) {
			if (DawnCount < 3000) {
				gLightsOn = 0;
			}
			else {
				gLightsOn = 1;
				puVar4 = &lightsOnDelay;
				do {
					if (*puVar4 != '\0') {
						*puVar4 = *puVar4 + -1;
					}
					puVar4 = puVar4 + 1;
				} while ((int)puVar4 < 0xd56e4);
			}
			NightAmbient = 0x4e;
			if (gWeather - 1U < 2) {
				iVar2 = DawnCount >> 7;
			}
			else {
				NightAmbient = 0x60;
				iVar2 = DawnCount >> 5;
			}
			NightAmbient = NightAmbient - iVar2;
			iVar2 = 0x2d;
			if (NightAmbient < 0x2d) goto LAB_0005aea0;
		}
		else {
			if (gTimeOfDay == 3) {
				gLightsOn = 1;
				iVar2 = 0x80;
			LAB_0005aea0:
				NightAmbient = iVar2;
			}
		}
	}
	if ((gWeather != 0) && (gWeather == 1)) {
		DoLightning();
		DoThunder();
	}
	HandleExplosion();
	if (FastForward == 0) {
		ColourCycle();
	}
	combointensity = NightAmbient | NightAmbient << 8 | NightAmbient << 0x10;
	if ((NoPlayerControl != 0) && (AttractMode == 0)) {
		ShowReplayOptions();
	}
	if ((FastForward != 0) &&
		(uVar3 = CameraCnt & 0x1f, CameraCnt < ReplayParameterPtr->RecordingEnd + -1)) {
		if (0xf < uVar3) {
			uVar3 = 0x20 - uVar3;
		}
		SetTextColour((uchar)((uVar3 & 0x1f) << 3), '\0', '\0');
		PrintStringFeature(s_Avanti_rapido_00010d0c, 100, 0x1e, 0x1000, 0x1000, 0);
	}
	if ((AttractMode == 0) && (pauseflag == 0)) {
		if (NoPlayerControl == 0) {
			if (2 < FrameCnt) {
				if (NumPlayers == 1) {
					if (((paddp == 0x800) && (bMissionTitleFade == 0)) && (gInGameCutsceneActive == 0)) {
						EnablePause(PAUSEMODE_PAUSE);
					}
				}
				else {
					if (paddp == 0x800) {
						EnablePause(PAUSEMODE_PAUSEP1);
					}
					else {
						if ((NumPlayers == 2) && ((Pads[1].dirnew & 0x800) != 0)) {
							EnablePause(PAUSEMODE_PAUSEP2);
						}
					}
				}
			}
			goto LAB_0005b0a8;
		}
	}
	else {
	LAB_0005b0a8:
		if (NoPlayerControl == 0) {
			if (((pad_connected < 1) && (2 < FrameCnt)) &&
				((bMissionTitleFade == 0 && (gInGameCutsceneActive == 0)))) {
				pauseflag = 1;
				PauseSound();
			}
			if ((NoPlayerControl == 0) && (NoTextureMemory != 0)) {
				NoTextureMemory = NoTextureMemory + -1;
			}
		}
	}
	CameraChanged = '\0';
	old_camera_change = camera_change;
	if ((pauseflag == 0) && (NoPlayerControl != 0)) {
		if (gInGameCutsceneActive == 0) {
			iVar2 = CheckCameraChange(CameraCnt);
			camera_change = (char)iVar2;
			goto LAB_0005b1e0;
		}
	}
	else {
		if (gInGameCutsceneActive == 0) {
			camera_change = '\0';
			goto LAB_0005b1e0;
		}
	}
	iVar2 = CutsceneCameraChange(CameraCnt);
	camera_change = (char)iVar2;
LAB_0005b1e0:
	if (pauseflag == 0) {
		StepSim();
		if (gDieWithFade != 0) {
			gDieWithFade = gDieWithFade + 1;
		}
		if (paused != 0) {
			CamerasSaved = 1;
			paused = 0;
		}
	}
	else {
		if (((NoPlayerControl == 0) && (AttractMode == 0)) && (game_over == 0)) {
			if (pad_connected < 1) {
				EnablePause(PAUSEMODE_PADERROR);
			}
			else {
				EnablePause(PAUSEMODE_PAUSE);
			}
		}
		paused = 1;
	}
	if ((NoPlayerControl != 0) && (AttractMode == 0)) {
		ControlReplay();
	}
	if (gRightWayUp != 0) {
		TempBuildHandlingMatrix(car_data + player.playerCarId, 0);
		gRightWayUp = 0;
	}
	if ((AttractMode != 0) && ((paddp != 0 || (ReplayParameterPtr->RecordingEnd <= CameraCnt)))) {
		EndGame(GAMEMODE_QUIT);
	}
	UpdatePlayerInformation();
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawGame()
 // line 4549, offset 0x0005c458
	/* begin block 1 */
		// Start line: 4551
		// Start offset: 0x0005C458
		// Variables:
	// 		static unsigned long frame; // offset 0xc8

		/* begin block 1.1 */
			// Start line: 4555
			// Start offset: 0x0005C480
		/* end block 1.1 */
		// End offset: 0x0005C4D0
		// End Line: 4561

		/* begin block 1.2 */
			// Start line: 4567
			// Start offset: 0x0005C4EC
		/* end block 1.2 */
		// End offset: 0x0005C554
		// End Line: 4577
	/* end block 1 */
	// End offset: 0x0005C574
	// End Line: 4583

	/* begin block 2 */
		// Start line: 10753
	/* end block 2 */
	// End Line: 10754

	/* begin block 3 */
		// Start line: 9098
	/* end block 3 */
	// End Line: 9099

	/* begin block 4 */
		// Start line: 10754
	/* end block 4 */
	// End Line: 10755

	/* begin block 5 */
		// Start line: 10756
	/* end block 5 */
	// End Line: 10757

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawGame(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	if ((NumPlayers == 1) || (NoPlayerControl != 0)) {
		ObjectDrawnValue = FrameCnt;
		DrawPauseMenus();
		RenderGame2(0);
		ObjectDrawnCounter = ObjectDrawnCounter + 1;
		do {
			iVar1 = VSync(0xffffffff);
		} while ((uint)(iVar1 - DAT_000aa670) < 2);
		DAT_000aa670 = VSync(0xffffffff);
		SwapDrawBuffers();
	}
	else {
		ObjectDrawnValue = FrameCnt;
		RenderGame2(0);
		ObjectDrawnCounter = ObjectDrawnCounter + 1;
		SwapDrawBuffers2(0);
		ObjectDrawnValue = ObjectDrawnValue + 0x10;
		DrawPauseMenus();
		RenderGame2(1);
		ObjectDrawnCounter = ObjectDrawnCounter + 1;
		SwapDrawBuffers2(1);
	}
	FrameCnt = FrameCnt + 1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ EndGame(enum GAMEMODE mode /*$a0*/)
 // line 4586, offset 0x0005c574
	/* begin block 1 */
		// Start line: 10823
	/* end block 1 */
	// End Line: 10824

	/* begin block 2 */
		// Start line: 10827
	/* end block 2 */
	// End Line: 10828

	/* begin block 3 */
		// Start line: 10829
	/* end block 3 */
	// End Line: 10830

void EndGame(GAMEMODE mode)
{
	UNIMPLEMENTED();
	/*
	WantedGameMode = mode;
	pauseflag = 0;
	game_over = 1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnablePause(enum PAUSEMODE mode /*$a0*/)
 // line 4593, offset 0x0005c590
	/* begin block 1 */
		// Start line: 10842
	/* end block 1 */
	// End Line: 10843

	/* begin block 2 */
		// Start line: 10843
	/* end block 2 */
	// End Line: 10844

void EnablePause(PAUSEMODE mode)
{
	UNIMPLEMENTED();
	/*
	if (((quick_replay != 0) || (NoPlayerControl == 0)) || (mode != PAUSEMODE_GAMEOVER)) {
		WantPause = 1;
		PauseMode = mode;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckForPause()
 // line 4602, offset 0x0005c5d0
	/* begin block 1 */
		// Start line: 4604
		// Start offset: 0x0005C5D0

		/* begin block 1.1 */
			// Start line: 4603
			// Start offset: 0x0005C5E4
		/* end block 1.1 */
		// End offset: 0x0005C614
		// End Line: 4603
	/* end block 1 */
	// End offset: 0x0005C668
	// End Line: 4618

	/* begin block 2 */
		// Start line: 10861
	/* end block 2 */
	// End Line: 10862

	/* begin block 3 */
		// Start line: 10862
	/* end block 3 */
	// End Line: 10863

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CheckForPause(void)
{
	UNIMPLEMENTED();
	/*
	if ((0xf < gDieWithFade) && ((quick_replay != 0 || (NoPlayerControl == 0)))) {
		PauseMode = PAUSEMODE_GAMEOVER;
		WantPause = 1;
	}
	if (WantPause != 0) {
		WantPause = 0;
		pauseflag = 1;
		PauseSound();
		ShowPauseMenu(PauseMode);
		if (game_over == 0) {
			UnPauseSound();
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ main()
 // line 4767, offset 0x0005b384
	/* begin block 1 */
		// Start line: 4768
		// Start offset: 0x0005B384

		/* begin block 1.1 */
			// Start line: 4768
			// Start offset: 0x0005B384

			/* begin block 1.1.1 */
				// Start line: 4768
				// Start offset: 0x0005B384
				// Variables:
			// 		char (*PALScreenNames[4]); // stack offset -24
			// 		char (*NTSCScreenNames[4]); // stack offset -40
			// 		char (*OPMScreenNames[4]); // stack offset -56
			/* end block 1.1.1 */
			// End offset: 0x0005B384
			// End Line: 4768
		/* end block 1.1 */
		// End offset: 0x0005B384
		// End Line: 4768
	/* end block 1 */
	// End offset: 0x0005B54C
	// End Line: 4868

	/* begin block 2 */
		// Start line: 9845
	/* end block 2 */
	// End Line: 9846

	/* begin block 3 */
		// Start line: 10066
	/* end block 3 */
	// End Line: 10067

/* WARNING: Unknown calling convention yet parameter storage is locked */

// decompiled code
// original method signature: 
// void SsSetSerialVol(char param_1,short param_2,short param_3);
 // line -1, offset 0x00092b3c
// function 'SsSetSerialVol' @0x00092B3C was found in the decompiled code exported from Ghidra, but not the original debug symbol data.
void SsSetSerialVol(char param_1, short param_2, short param_3)
{
	UNIMPLEMENTED();

	/*
	undefined4 local_30[4];
	short local_20;
	short local_1e;
	short local_14;
	short local_12;

	if (param_1 == '\0') {
		local_30[0] = 0xc0;
		if (0x7f < param_2) {
			param_2 = 0x7f;
		}
		if (0x7f < param_3) {
			param_3 = 0x7f;
		}
		local_20 = param_2 * 0x102;
		local_1e = param_3 * 0x102;
	}
	if (param_1 == '\x01') {
		local_30[0] = 0xc00;
		if (0x7f < param_2) {
			param_2 = 0x7f;
		}
		if (0x7f < param_3) {
			param_3 = 0x7f;
		}
		local_14 = param_2 * 0x102;
		local_12 = param_3 * 0x102;
	}
	SpuSetCommonAttr(local_30);
	return;
	*/
}

// [D]
#ifdef PSX
int main(void)
#else
int redriver2_main(void)
#endif // PSX
{
	char *PALScreenNames[4] = {		// [A] don't show publisher logo
	//	"GFX\\SPLASH2.TIM",
	//	"GFX\\SPLASH3.TIM",
		"GFX\\SPLASH1P.TIM",
		NULL
	};

	char *NTSCScreenNames[4] = {		// [A] don't show publisher logo
	//	"GFX\\SPLASH2.TIM",
	//	"GFX\\SPLASH3.TIM",
		"GFX\\SPLASH1N.TIM",
		NULL
	};

	char *OPMScreenNames[4] = {		// [A] don't show publisher logo
		//"GFX\\OPM1.TIM",
		"GFX\\OPM2.TIM",
		"GFX\\OPM3.TIM",
		NULL
	};

	//_stacksize = 0x4000;
	//_ramsize = 0x200000;

	SetDispMask(0);
	StopCallback();
	ResetCallback();
	ResetGraph(0);
	SsSetSerialVol(0, 0, 0);
	SetDispMask(0);
	SetGraphDebug(0);
	SetVideoMode(video_mode);
	CdInit();
	SsSetSerialVol(0, 0, 0);
	SpuInit();
	InitGeom();
	SetGeomOffset(160, 128);
	scr_z = 256;
	SetGeomScreen(256);
	MemCardInit(1);
	InitControllers();
	Init_FileSystem();
	InitSound();

	//PlayFMV(99);	// [A] don't show publisher logo

	ShowHiresScreens(OPMScreenNames, 300, 0); // [A]

	PlayFMV(0);		// play intro movie

	CheckForCorrectDisc(0);

	// Init frontend
#ifdef PSX
	Loadfile(s_FRONTEND_BIN_00010dc4, &DAT_001c0000);
#endif // PSX

	SpuSetMute(0);

	LoadSoundBankDynamic(NULL, 0, 0);
	LoadBankFromLump(1, 0);

	InitialiseScoreTables();
	DoFrontEnd();

	return 1;
}

// decompiled code
// original method signature: 
// void /*$ra*/ FadeScreen(int end_value /*$a1*/)
 // line 4870, offset 0x0005c668
	/* begin block 1 */
		// Start line: 4871
		// Start offset: 0x0005C668
		// Variables:
	// 		int tmp2; // $s1
	/* end block 1 */
	// End offset: 0x0005C6E0
	// End Line: 4888

	/* begin block 2 */
		// Start line: 11280
	/* end block 2 */
	// End Line: 11281

	/* begin block 3 */
		// Start line: 11397
	/* end block 3 */
	// End Line: 11398

void FadeScreen(int end_value)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = pauseflag;
	pauseflag = 1;
	SetupScreenFade(-0x20, end_value, 1);
	FadingScreen = 1;
	do {
		RenderGame();
	} while (FadingScreen != 0);
	DrawSync(0);
	SetDispMask(0);
	pauseflag = iVar1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdatePlayerInformation()
 // line 4893, offset 0x0005b54c
	/* begin block 1 */
		// Start line: 4895
		// Start offset: 0x0005B54C
		// Variables:
	// 		struct _CAR_DATA *cp; // $s1
	// 		int count; // $s0
	// 		int scale; // $v1
	// 		int wheel; // $t1
	// 		int wheelsonwater; // $t2
	/* end block 1 */
	// End offset: 0x0005B888
	// End Line: 4972

	/* begin block 2 */
		// Start line: 10293
	/* end block 2 */
	// End Line: 10294

	/* begin block 3 */
		// Start line: 10319
	/* end block 3 */
	// End Line: 10320

	/* begin block 4 */
		// Start line: 10320
	/* end block 4 */
	// End Line: 10321

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdatePlayerInformation(void)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	int iVar2;
	byte *pbVar3;
	WHEEL *pWVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	_CAR_DATA *p_Var9;

	p_Var9 = (_CAR_DATA *)0x0;
	PlayerDamageBar.max = (ushort)MaxPlayerDamage;
	Player2DamageBar.max = (ushort)INT_000aa714;
	if (gPlayerImmune != 0) {
		if ((int)player.playerCarId < 0) {
			psVar1 = &pedestrianFelony;
		}
		else {
			psVar1 = &car_data[(int)player.playerCarId].felonyRating;
		}
		*psVar1 = 0;
	}
	if ((int)player.playerCarId < 0) {
		psVar1 = &pedestrianFelony;
	}
	else {
		psVar1 = &car_data[(int)player.playerCarId].felonyRating;
	}
	FelonyBar.position = *psVar1;
	if (NumPlayers != 0) {
		iVar2 = 0;
		iVar8 = 0;
		do {
			iVar2 = (iVar2 * 4 + iVar8 * -3) * 4;
			if ((&player.playerType)[iVar2] == '\x01') {
				iVar2 = (int)(&player.playerCarId)[iVar2];
				p_Var9 = car_data + iVar2;
				if (gInvincibleCar != 0) {
					car_data[iVar2].totalDamage = 0;
					ClearMem((char *)car_data[iVar2].ap.damage, 0xc);
				}
				iVar6 = 0;
				iVar7 = iVar8 + 1;
				pWVar4 = car_data[iVar2].hd.wheel;
				pbVar3 = &car_data[iVar2].hd.wheel[0].surface;
				iVar5 = 3;
				do {
					if (((uint)*pbVar3 & 7) == 1) {
						if (pWVar4->susCompression == '\0') {
							if ((car_data[iVar2].hd.where.t[1] < -1000) && (gDieWithFade == 0)) {
								gDieWithFade = (uint)*pbVar3 & 7;
							}
						}
						else {
							iVar6 = iVar6 + 1;
						}
					}
					pWVar4 = pWVar4 + 1;
					iVar5 = iVar5 + -1;
					pbVar3 = pbVar3 + 4;
				} while (-1 < iVar5);
				if (iVar6 == 4) {
					car_data[iVar2].totalDamage =
						car_data[iVar2].totalDamage + (short)((&MaxPlayerDamage)[iVar8] / 0x50);
				}
				if ((&MaxPlayerDamage)[iVar8] < (int)(uint)car_data[iVar2].totalDamage) {
					car_data[iVar2].totalDamage = *(ushort *)(&MaxPlayerDamage + iVar8);
				}
				if (iVar8 == 0) {
					PlayerDamageBar.position = car_data[iVar2].totalDamage;
				}
				else {
					Player2DamageBar.position = car_data[iVar2].totalDamage;
				}
			}
			else {
				iVar7 = iVar8 + 1;
				if (iVar8 == 0) {
					PlayerDamageBar.position = 0;
					iVar7 = 1;
				}
				else {
					Player2DamageBar.position = 0;
				}
			}
			if (((0x1df < gCurrentMissionNumber) &&
				(((gCurrentMissionNumber < 0x1e2 ||
				((gCurrentMissionNumber < 0x1e6 && (0x1e3 < gCurrentMissionNumber)))) &&
					((p_Var9->hd).where.t[1] < -0x2ee)))) && (gDieWithFade == 0)) {
				gDieWithFade = 1;
			}
			iVar2 = iVar7 << 3;
			iVar8 = iVar7;
		} while (iVar7 < (int)(uint)NumPlayers);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RenderGame2(int view /*$s3*/)
 // line 5021, offset 0x0005b888
	/* begin block 1 */
		// Start line: 5022
		// Start offset: 0x0005B888
		// Variables:
	// 		int spaceFree; // $a1
	// 		int notInDreaAndStevesEvilLair; // $s0

		/* begin block 1.1 */
			// Start line: 5067
			// Start offset: 0x0005B9A4
			// Variables:
		// 		int strobe; // $v0
		/* end block 1.1 */
		// End offset: 0x0005B9EC
		// End Line: 5070

		/* begin block 1.2 */
			// Start line: 5073
			// Start offset: 0x0005B9EC
			// Variables:
		// 		int i; // $s1
		/* end block 1.2 */
		// End offset: 0x0005BA84
		// End Line: 5077

		/* begin block 1.3 */
			// Start line: 5090
			// Start offset: 0x0005BAE4
			// Variables:
		// 		struct POLY_F4 *poly; // $v1
		// 		int col; // $a1
		/* end block 1.3 */
		// End offset: 0x0005BC20
		// End Line: 5113

		/* begin block 1.4 */
			// Start line: 5121
			// Start offset: 0x0005BC40
		/* end block 1.4 */
		// End offset: 0x0005BC88
		// End Line: 5125
	/* end block 1 */
	// End offset: 0x0005BCE4
	// End Line: 5132

	/* begin block 2 */
		// Start line: 10644
	/* end block 2 */
	// End Line: 10645

	/* begin block 3 */
		// Start line: 10654
	/* end block 3 */
	// End Line: 10655

void RenderGame2(int view)
{
	UNIMPLEMENTED();

	/*
	DB *pDVar1;
	int iVar2;
	uint *puVar3;
	uint uVar4;
	char cVar5;
	char *pcVar6;
	_PLAYER *p_Var7;
	int iVar8;

	CurrentPlayerView = view;
	InitCamera(&player + view);
	Set_Inv_CameraMatrix();
	SetCameraVector();
	SetupDrawMapPSX();
	if (gLoadedMotionCapture != 0) {
		DrawAllPedestrians();
	}
	DisplayMissionTitle();
	DrawInGameCutscene();
	DrawEvents(1);
	Set_Inv_CameraMatrix();
	SetCameraVector();
	SetupDrawMapPSX();
	DrawDrivingGames();
	DrawThrownBombs();
	AddGroundDebris();
	DrawEvents(0);
	current->ot = current->ot + 10;
	DrawSmashable_sprites();
	HandleDebris();
	current->ot = current->ot + -10;
	DrawAllExplosions();
	if (AttractMode != 0) {
		uVar4 = CameraCnt & 0x1f;
		if (0xf < uVar4) {
			uVar4 = 0x20 - uVar4;
		}
		SetTextColour((uchar)((uVar4 & 0x1f) << 3), '\0', '\0');
		PrintString(&DAT_000aa674, 0x23, 0xf);
	}
	p_Var7 = &player;
	iVar8 = 2;
	do {
		iVar2 = CarHasSiren((uint)(byte)car_data[p_Var7->playerCarId].ap.model);
		if ((iVar2 != 0) && ((p_Var7->horn).on != '\0')) {
			AddCopCarLight(car_data + p_Var7->playerCarId);
		}
		iVar8 = iVar8 + -1;
		p_Var7 = p_Var7 + 1;
	} while (-1 < iVar8);
	if (gLoadedOverlay != 0) {
		DisplayOverlays();
	}
	DrawMission();
	if ((FastForward == 0) && (NumPlayers == 1)) {
		DrawLensFlare();
	}
	cVar5 = (char)(gDieWithFade << 4);
	if (gDieWithFade != 0) {
		if (0xff < gDieWithFade << 4) {
			cVar5 = -1;
		}
		puVar3 = (uint *)current->primptr;
		*(char *)((int)puVar3 + 7) = '*';
		*(char *)((int)puVar3 + 3) = '\x05';
		*(char *)(puVar3 + 1) = cVar5;
		*(char *)((int)puVar3 + 5) = cVar5;
		*(char *)((int)puVar3 + 6) = cVar5;
		pDVar1 = current;
		*(undefined2 *)(puVar3 + 2) = 0;
		*(undefined2 *)((int)puVar3 + 10) = 0;
		*(undefined2 *)(puVar3 + 3) = 0x140;
		*(undefined2 *)((int)puVar3 + 0xe) = 0;
		*(undefined2 *)(puVar3 + 4) = 0;
		*(undefined2 *)((int)puVar3 + 0x12) = 0x100;
		*(undefined2 *)(puVar3 + 5) = 0x140;
		*(undefined2 *)((int)puVar3 + 0x16) = 0x100;
		*puVar3 = *puVar3 & 0xff000000 | pDVar1->ot[8] & 0xffffff;
		pDVar1->ot[8] = pDVar1->ot[8] & 0xff000000 | (uint)puVar3 & 0xffffff;
		pcVar6 = pDVar1->primptr;
		pDVar1->primptr = pcVar6 + 0x18;
		pcVar6[0x1b] = '\a';
		pcVar6[0x1f] = '$';
		*(undefined2 *)(pcVar6 + 0x20) = 0xffff;
		*(undefined2 *)(pcVar6 + 0x22) = 0xffff;
		*(undefined2 *)(pcVar6 + 0x28) = 0xffff;
		*(undefined2 *)(pcVar6 + 0x2a) = 0xffff;
		*(undefined2 *)(pcVar6 + 0x30) = 0xffff;
		*(undefined2 *)(pcVar6 + 0x32) = 0xffff;
		*(undefined2 *)(pcVar6 + 0x2e) = 0x40;
		pDVar1 = current;
		*(uint *)(pcVar6 + 0x18) = *(uint *)(pcVar6 + 0x18) & 0xff000000 | current->ot[8] & 0xffffff;
		pDVar1->ot[8] = pDVar1->ot[8] & 0xff000000 | (uint)(pcVar6 + 0x18) & 0xffffff;
		pDVar1->primptr = pDVar1->primptr + 0x20;
	}
	iVar8 = Havana3DOcclusion(0xb0, (int *)&ObjectDrawnValue);
	ScaleCamera();
	if ((iVar8 != 0) &&
		(DrawSkyDome(), 40000 < (int)(current->primtab + -(int)(current->primptr + -0x1e000)))) {
		DoWeather(gWeather);
	}
	if (37000 < (int)(current->primtab + -(int)(current->primptr + -0x1e000))) {
		DrawTyreTracks();
	}
	DrawAllTheCars(view);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RenderGame()
 // line 5260, offset 0x0005c6e0
	/* begin block 1 */
		// Start line: 5262
		// Start offset: 0x0005C6E0

		/* begin block 1.1 */
			// Start line: 5262
			// Start offset: 0x0005C6E0

			/* begin block 1.1.1 */
				// Start line: 5262
				// Start offset: 0x0005C6E0
				// Variables:
			// 		static unsigned long frame; // offset 0xc8

				/* begin block 1.1.1.1 */
					// Start line: 5261
					// Start offset: 0x0005C714
				/* end block 1.1.1.1 */
				// End offset: 0x0005C764
				// End Line: 5261

				/* begin block 1.1.1.2 */
					// Start line: 5261
					// Start offset: 0x0005C780
				/* end block 1.1.1.2 */
				// End offset: 0x0005C7E8
				// End Line: 5261
			/* end block 1.1.1 */
			// End offset: 0x0005C7E8
			// End Line: 5261
		/* end block 1.1 */
		// End offset: 0x0005C7E8
		// End Line: 5261
	/* end block 1 */
	// End offset: 0x0005C81C
	// End Line: 5269

	/* begin block 2 */
		// Start line: 11914
	/* end block 2 */
	// End Line: 11915

	/* begin block 3 */
		// Start line: 12188
	/* end block 3 */
	// End Line: 12189

	/* begin block 4 */
		// Start line: 12189
	/* end block 4 */
	// End Line: 12190

/* WARNING: Unknown calling convention yet parameter storage is locked */

void RenderGame(void)
{
	UNIMPLEMENTED();

	/*
	int iVar1;

	UpdatePadData();
	if ((NumPlayers == 1) || (NoPlayerControl != 0)) {
		ObjectDrawnValue = FrameCnt;
		DrawPauseMenus();
		RenderGame2(0);
		ObjectDrawnCounter = ObjectDrawnCounter + 1;
		do {
			iVar1 = VSync(0xffffffff);
		} while ((uint)(iVar1 - DAT_000aa670) < 2);
		DAT_000aa670 = VSync(0xffffffff);
		SwapDrawBuffers();
	}
	else {
		ObjectDrawnValue = FrameCnt;
		RenderGame2(0);
		ObjectDrawnCounter = ObjectDrawnCounter + 1;
		SwapDrawBuffers2(0);
		ObjectDrawnValue = ObjectDrawnValue + 0x10;
		DrawPauseMenus();
		RenderGame2(1);
		ObjectDrawnCounter = ObjectDrawnCounter + 1;
		SwapDrawBuffers2(1);
	}
	FrameCnt = FrameCnt + 1;
	FadeGameScreen(0, 8);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitGameVariables()
 // line 5272, offset 0x0005bce4
	/* begin block 1 */
		// Start line: 5274
		// Start offset: 0x0005BCE4
	/* end block 1 */
	// End offset: 0x0005BF74
	// End Line: 5341

	/* begin block 2 */
		// Start line: 11050
	/* end block 2 */
	// End Line: 11051

	/* begin block 3 */
		// Start line: 11191
	/* end block 3 */
	// End Line: 11192

	/* begin block 4 */
		// Start line: 11192
	/* end block 4 */
	// End Line: 11193

/* WARNING: Unknown calling convention yet parameter storage is locked */

REPLAY_STREAM ReplayStreams[8];

int TargetCar = 0;

char gRainCount = 0;
int pauseflag = 0;

int HitLeadCar = 0;
int FastForward = 0;
int game_over = 0;
int saved_counter = 0;
int saved_leadcar_pos = 0;
int gStopPadReads = 0;
int DawnCount = 0;
int variable_weather = 0;
int current_camera_angle = 0x800;
int gDieWithFade = 0;

// replay
int FrameCnt = 0;

unsigned char defaultPlayerModel[2] = {0}; // offset 0xAA604
unsigned char defaultPlayerPalette = 0; // offset 0xAA606

// [D]
void InitGameVariables(void)
{
	int iVar1;
	int iVar2;
	uint uVar3;

	InitDebris();
	InitTyreTracks();
	TargetCar = 0;

	if (NewLevel != 0) {
		gLoadedOverlay = 0;
		gLoadedMotionCapture = 0;
	}

	gRainCount = '\0';

	if ((NoPlayerControl == 0) || (AttractMode != 0)) {
		pauseflag = 0;
	}
	else {
		pauseflag = 1;
	}

	HitLeadCar = 0;
	FastForward = 0;
	game_over = 0;
	saved_counter = 0;
	saved_leadcar_pos = 0;
	gStopPadReads = 0;
	DawnCount = 0;
	variable_weather = 0;
	current_camera_angle = 0x800;
	gDieWithFade = 0;

	srand(0x1234);
	RandomInit(0xd431, 0x350b1);
	FrameCnt = 0;
	CameraCnt = 0;

	ClearMem((char *)&lightsOnDelay, 0x14);

	PlayerStartInfo[0] = (STREAM_SOURCE*)ReplayStreams;
	ClearMem((char *)ReplayStreams, 0x30);

	((STREAM_SOURCE *)PlayerStartInfo[0])->type = '\x01';
	((STREAM_SOURCE *)PlayerStartInfo[0])->model = defaultPlayerModel[0];
	((STREAM_SOURCE *)PlayerStartInfo[0])->palette = defaultPlayerPalette;
	((STREAM_SOURCE *)PlayerStartInfo[0])->controlType = '\x01';
	((STREAM_SOURCE *)PlayerStartInfo[0])->flags = 0;
	((STREAM_SOURCE *)PlayerStartInfo[0])->rotation = levelstartpos[GameLevel][1];
	(((STREAM_SOURCE *)PlayerStartInfo[0])->position).vx = levelstartpos[GameLevel][0];		// [A] ??
	(((STREAM_SOURCE *)PlayerStartInfo[0])->position).vy = 0;
	(((STREAM_SOURCE *)PlayerStartInfo[0])->position).vz = levelstartpos[GameLevel][2];

	uVar3 = (uint)NumPlayers;
	numPlayersToCreate = 1;

	if (NumPlayers == 2) {
		PlayerStartInfo[1] = (STREAM_SOURCE *)(ReplayStreams + 1);
		ClearMem((char *)(ReplayStreams + 1), 0x30);
		PlayerStartInfo[1]->type = '\x01';
		PlayerStartInfo[1]->model = defaultPlayerModel[1];
		PlayerStartInfo[1]->palette = defaultPlayerPalette;
		PlayerStartInfo[1]->controlType = '\x01';
		PlayerStartInfo[1]->flags = 0;
		PlayerStartInfo[1]->rotation = levelstartpos[GameLevel][1];
		(PlayerStartInfo[1]->position).vx = levelstartpos[GameLevel][0] + 600;
		(PlayerStartInfo[1]->position).vy = 0;
		(PlayerStartInfo[1]->position).vz = levelstartpos[GameLevel][2];
		numPlayersToCreate = uVar3;
	}

	InitCivCars();
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DealWithHorn(char *hr /*$s2*/, int i /*$s1*/)
 // line 5345, offset 0x0005bf74
	/* begin block 1 */
		// Start line: 5346
		// Start offset: 0x0005BF74
		// Variables:
	// 		struct _CAR_DATA *car; // $s0

		/* begin block 1.1 */
			// Start line: 5348
			// Start offset: 0x0005C014
		/* end block 1.1 */
		// End offset: 0x0005C124
		// End Line: 5363
	/* end block 1 */
	// End offset: 0x0005C154
	// End Line: 5365

	/* begin block 2 */
		// Start line: 11377
	/* end block 2 */
	// End Line: 11378

	/* begin block 3 */
		// Start line: 11382
	/* end block 3 */
	// End Line: 11383

void DealWithHorn(char *hr, int i)
{
	UNIMPLEMENTED();

	/*
	byte bVar1;
	int channel;
	int channel_00;
	uint uVar2;

	channel = (int)(&player)[i].playerCarId;
	bVar1 = *hr;
	if (bVar1 == 1) {
		channel = 2;
		if (i != 0) {
			channel = 5;
		}
		StopChannel(channel);
	}
	else {
		if (bVar1 < 2) {
			if (bVar1 == 0) {
				return;
			}
		}
		else {
			if (bVar1 == 2) {
				bVar1 = car_data[channel].ap.model;
				if (bVar1 == 4) {
					uVar2 = ResidentModelsBodge();
				}
				else {
					if (bVar1 < 3) {
						uVar2 = (uint)(byte)car_data[channel].ap.model;
					}
					else {
						uVar2 = (uint)(byte)car_data[channel].ap.model - 1;
					}
				}
				channel_00 = 2;
				if (i != 0) {
					channel_00 = 5;
				}
				Start3DSoundVolPitch
				(channel_00, 3, uVar2 * 3 + 2, car_data[channel].hd.where.t[0],
					car_data[channel].hd.where.t[1], car_data[channel].hd.where.t[2], -10000, 0x1000);
				if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
					channel_00 = 2;
					if (i != 0) {
						channel_00 = 5;
					}
					SetPlayerOwnsChannel(channel_00, (char)i);
				}
				channel_00 = 2;
				if (i != 0) {
					channel_00 = 5;
				}
				SetChannelPosition3(channel_00, (VECTOR *)car_data[channel].hd.where.t,
					(long *)(car_data[channel].st + 0x1c), -2000, i * 8 + 0x1000, 0);
			}
		}
	}
	uVar2 = (uint)(byte)*hr + 1 & 0xff;
	*hr = (char)uVar2 - (((byte)((ulonglong)uVar2 * 0xaaaaaaab >> 0x20) & 0xfe) + (char)(uVar2 / 3));
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ Havana3DOcclusion(TDRFuncPtr_Havana3DOcclusion0func func /*$a3*/, int *param /*$fp*/)
 // line 5367, offset 0x0005c16c
	/* begin block 1 */
		// Start line: 5368
		// Start offset: 0x0005C16C
		// Variables:
	// 		int outside; // $s6
	// 		int otAltered; // $s5

		/* begin block 1.1 */
			// Start line: 5379
			// Start offset: 0x0005C208
			// Variables:
		// 		int draw; // $s2
		// 		int loop; // $s0
		/* end block 1.1 */
		// End offset: 0x0005C414
		// End Line: 5473
	/* end block 1 */
	// End offset: 0x0005C458
	// End Line: 5480

	/* begin block 2 */
		// Start line: 11426
	/* end block 2 */
	// End Line: 11427

	/* begin block 3 */
		// Start line: 11430
	/* end block 3 */
	// End Line: 11431

int Havana3DOcclusion(TDRFuncPtr_Havana3DOcclusion0func func, int *param)
{
	UNIMPLEMENTED();
	return 0;

	/*
	bool bVar1;
	undefined3 in_register_00000011;
	int iVar2;
	int unaff_s2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar5 = 1;
	if ((((GameLevel != 1) || (-0x68fdc < camera_position.vx)) || (camera_position.vx < -0x75416)) ||
		((-0x1b8ae < camera_position.vz || (camera_position.vz < -0x20cb3)))) goto LAB_0005c41c;
	if (camera_position.vy < 0x1bf) {
		unaff_s2 = 0x10;
		if (-0x729fc < camera_position.vx) {
			unaff_s2 = 0x11;
		}
	}
	else {
		iVar5 = 0;
		if (((camera_position.vx < -0x6e9e5) && (-0x6fa01 < camera_position.vx)) &&
			((camera_position.vz < -0x1e201 &&
			((-0x1f205 < camera_position.vz && (camera_position.vy < 0xf73)))))) {
			if (camera_position.vy < 0x4dd) {
			LAB_0005c2b4:
				unaff_s2 = 0xf;
			}
			else {
				bVar1 = camera_position.vy < 0xc00;
				if (camera_position.vy < 0x7d1) {
					unaff_s2 = 0xe;
				}
				else {
				LAB_0005c2d8:
					if (bVar1) {
						unaff_s2 = 0xd;
					}
				}
			}
		}
		else {
			if (camera_position.vy < 0x6c2) goto LAB_0005c2b4;
			unaff_s2 = 0xe;
			if (camera_position.vy < 0x834) {
				bVar1 = camera_position.vx < -0x73609;
				goto LAB_0005c2d8;
			}
			if ((((0xbff < camera_position.vy) && (-0x6fa01 < camera_position.vx)) ||
				(unaff_s2 = 0xc, camera_position.vz < -0x1f9db)) &&
				(unaff_s2 = 10, camera_position.vz < -0x1f9dc)) {
				unaff_s2 = 0xb;
			}
		}
	}
	events.camera = 1;
	iVar2 = unaff_s2 + -1;
	if (iVar2 < 10) {
		iVar2 = 10;
	}
	iVar3 = 0;
	while (true) {
		if (unaff_s2 + 1 < iVar2) {
			events.camera = 0;
			return iVar5;
		}
		if (iVar2 == 0x10) break;
		if (unaff_s2 != iVar2) {
			iVar3 = 200;
		}
		events.draw = iVar2;
		current->ot = current->ot + iVar3;
		(*(code *)CONCAT31(in_register_00000011, func))(param);
		iVar4 = iVar3;
		if (iVar3 != 0) {
			iVar4 = 0;
			current->ot = current->ot + iVar3 * 0x3fffffff;
		}
		iVar2 = iVar2 + 1;
		iVar3 = iVar4;
	}
	events.camera = 0;
	if ((unaff_s2 == 0xf) && (-0x6fd11 < camera_position.vx)) {
		events.camera = 0;
		return iVar5;
	}
LAB_0005c41c:
	(*(code *)CONCAT31(in_register_00000011, func))(param);
	return 1;
	*/
}





