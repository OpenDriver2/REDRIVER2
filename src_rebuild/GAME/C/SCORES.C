#include "THISDUST.H"
#include "SCORES.H"


// decompiled code
// original method signature: 
// void /*$ra*/ InitialiseScoreTables()
 // line 58, offset 0x00074ec0
	/* begin block 1 */
		// Start line: 60
		// Start offset: 0x00074EC0
		// Variables:
	// 		int i; // $s3
	// 		int j; // $s1
	/* end block 1 */
	// End offset: 0x0007503C
	// End Line: 84

	/* begin block 2 */
		// Start line: 116
	/* end block 2 */
	// End Line: 117

	/* begin block 3 */
		// Start line: 117
	/* end block 3 */
	// End Line: 118

	/* begin block 4 */
		// Start line: 119
	/* end block 4 */
	// End Line: 120

/* WARNING: Unknown calling convention yet parameter storage is locked */

struct SCORE_TABLES ScoreTables;
struct PLAYER_SCORE gPlayerScore;

void InitialiseScoreTables(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	SCORE_ENTRY *table;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar3 = 0;
	iVar4 = 1;
	do {
		table = ScoreTables.GetawayTable + iVar3 * 10;
		iVar2 = 1;
		do {
			ResetTable(table);
			iVar2 = iVar2 + -1;
			table = table + 5;
		} while (-1 < iVar2);
		table = ScoreTables.CheckpointTable + iVar3 * 10;
		iVar2 = 1;
		do {
			ResetTable(table);
			iVar2 = iVar2 + -1;
			table = table + 5;
		} while (-1 < iVar2);
		table = ScoreTables.TrailblazerTable + iVar3 * 10;
		iVar2 = 1;
		do {
			ResetTable(table);
			iVar2 = iVar2 + -1;
			table = table + 5;
		} while (-1 < iVar2);
		table = ScoreTables.GateRaceTable + iVar3 * 10;
		iVar2 = 1;
		do {
			ResetTable(table);
			iVar2 = iVar2 + -1;
			table = table + 5;
		} while (-1 < iVar2);
		table = ScoreTables.SurvivalTable + iVar3 * 5;
		iVar3 = 0;
		do {
			ResetTable(table);
			iVar3 = iVar3 + -1;
			table = table + 5;
		} while (-1 < iVar3);
		bVar1 = iVar4 < 4;
		iVar3 = iVar4;
		iVar4 = iVar4 + 1;
	} while (bVar1);
	gPlayerScore.time = 0;
	gPlayerScore.P2time = 0;
	gPlayerScore.items = 0;
	gPlayerScore.P2items = 0;
	gPlayerScore.name._0_4_ = DAT_000aa8ec;
	gPlayerScore.name[4] = DAT_000aa8f0;
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ OnScoreTable(struct SCORE_ENTRY **tablept /*$s1*/)
 // line 86, offset 0x0007503c
	/* begin block 1 */
		// Start line: 87
		// Start offset: 0x0007503C
		// Variables:
	// 		struct SCORE_ENTRY *table; // $s0
	// 		int position; // $v0
	/* end block 1 */
	// End offset: 0x000751F8
	// End Line: 126

	/* begin block 2 */
		// Start line: 196
	/* end block 2 */
	// End Line: 197

	/* begin block 3 */
		// Start line: 199
	/* end block 3 */
	// End Line: 200

	/* begin block 4 */
		// Start line: 203
	/* end block 4 */
	// End Line: 204

int OnScoreTable(SCORE_ENTRY **tablept)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	SCORE_ENTRY *table;

	switch (GameType) {
	case GAME_GETAWAY:
		table = ScoreTables.GetawayTable + gSubGameNumber * 5 + GameLevel * 10;
		iVar1 = CheckGetawayPlacing(table);
		break;
	case GAME_GATERACE:
		iVar1 = 0xda278;
		goto LAB_00075180;
	case GAME_CHECKPOINT:
		table = (SCORE_ENTRY *)(GameLevel * 0x78 + gSubGameNumber * 0x3c + 0xda458);
		iVar1 = CheckCheckpointPlacing(table);
		break;
	case GAME_TRAILBLAZER:
		iVar1 = 0xda638;
	LAB_00075180:
		table = (SCORE_ENTRY *)(GameLevel * 0x78 + gSubGameNumber * 0x3c + iVar1);
		iVar1 = CheckTrailblazerPlacing(table);
		break;
	case GAME_SURVIVAL:
		table = (SCORE_ENTRY *)(GameLevel * 0x3c + gSubGameNumber * 0x3c + 0xda818);
		iVar1 = CheckSurvivalPlacing(table);
		break;
	default:
		return -1;
	}
	if (tablept != (SCORE_ENTRY **)0x0) {
		*tablept = table;
	}
	return iVar1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddScoreToTable(struct SCORE_ENTRY *table /*$a2*/, int entry /*$a1*/)
 // line 133, offset 0x000751f8
	/* begin block 1 */
		// Start line: 134
		// Start offset: 0x000751F8
		// Variables:
	// 		int i; // $a3
	/* end block 1 */
	// End offset: 0x0007526C
	// End Line: 149

	/* begin block 2 */
		// Start line: 289
	/* end block 2 */
	// End Line: 290

	/* begin block 3 */
		// Start line: 297
	/* end block 3 */
	// End Line: 298

	/* begin block 4 */
		// Start line: 301
	/* end block 4 */
	// End Line: 302

void AddScoreToTable(SCORE_ENTRY *table, int entry)
{
	UNIMPLEMENTED();
	/*

	undefined4 uVar1;
	undefined4 uVar2;
	int iVar3;

	table = table + 4;
	iVar3 = 3;
	if (entry < 4) {
		do {
			uVar1 = *(undefined4 *)&table[-1].items;
			uVar2 = *(undefined4 *)(table[-1].name + 2);
			iVar3 = iVar3 + -1;
			table->time = table[-1].time;
			*(undefined4 *)&table->items = uVar1;
			*(undefined4 *)(table->name + 2) = uVar2;
			table = table + -1;
		} while (entry <= iVar3);
	}
	table->time = gPlayerScore.time;
	table->items = gPlayerScore.items;
	strcpy(table->name, gPlayerScore.name);
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckGetawayPlacing(struct SCORE_ENTRY *table /*$a0*/)
 // line 162, offset 0x0007526c
	/* begin block 1 */
		// Start line: 163
		// Start offset: 0x0007526C
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x000752BC
	// End Line: 178

	/* begin block 2 */
		// Start line: 347
	/* end block 2 */
	// End Line: 348

	/* begin block 3 */
		// Start line: 361
	/* end block 3 */
	// End Line: 362

	/* begin block 4 */
		// Start line: 364
	/* end block 4 */
	// End Line: 365

int CheckGetawayPlacing(SCORE_ENTRY *table)
{
	UNIMPLEMENTED();

	int iVar1;

	iVar1 = 0;
	while ((gPlayerScore.time == -1 || ((table->time != -1 && (table->time <= gPlayerScore.time))))) {
		iVar1 = iVar1 + 1;
		table = table + 1;
		if (4 < iVar1) {
			return -1;
		}
	}
	return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckTrailblazerPlacing(struct SCORE_ENTRY *table /*$a0*/)
 // line 188, offset 0x000752bc
	/* begin block 1 */
		// Start line: 189
		// Start offset: 0x000752BC
		// Variables:
	// 		int i; // $a2
	/* end block 1 */
	// End offset: 0x00075338
	// End Line: 209

	/* begin block 2 */
		// Start line: 407
	/* end block 2 */
	// End Line: 408

	/* begin block 3 */
		// Start line: 418
	/* end block 3 */
	// End Line: 419

	/* begin block 4 */
		// Start line: 421
	/* end block 4 */
	// End Line: 422

int CheckTrailblazerPlacing(SCORE_ENTRY *table)
{
	UNIMPLEMENTED();

	int iVar1;

	iVar1 = 0;
	do {
		if (gPlayerScore.items == -1) {
			if (gPlayerScore.time != -1) {
				if (table->time == -1) {
					return iVar1;
				}
				if (table->time < gPlayerScore.time) {
					return iVar1;
				}
			}
		}
		else {
			if ((table->items == -1) || (table->items < gPlayerScore.items)) {
				return iVar1;
			}
		}
		iVar1 = iVar1 + 1;
		table = table + 1;
		if (4 < iVar1) {
			return -1;
		}
	} while (true);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckCheckpointPlacing(struct SCORE_ENTRY *table /*$a0*/)
 // line 218, offset 0x00075338
	/* begin block 1 */
		// Start line: 219
		// Start offset: 0x00075338
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x00075388
	// End Line: 234

	/* begin block 2 */
		// Start line: 477
	/* end block 2 */
	// End Line: 478

	/* begin block 3 */
		// Start line: 487
	/* end block 3 */
	// End Line: 488

	/* begin block 4 */
		// Start line: 490
	/* end block 4 */
	// End Line: 491

int CheckCheckpointPlacing(SCORE_ENTRY *table)
{
	UNIMPLEMENTED();

	int iVar1;

	iVar1 = 0;
	while ((gPlayerScore.time == -1 || ((table->time != -1 && (table->time <= gPlayerScore.time))))) {
		iVar1 = iVar1 + 1;
		table = table + 1;
		if (4 < iVar1) {
			return -1;
		}
	}
	return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckSurvivalPlacing(struct SCORE_ENTRY *table /*$a0*/)
 // line 243, offset 0x00075388
	/* begin block 1 */
		// Start line: 244
		// Start offset: 0x00075388
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x000753D8
	// End Line: 259

	/* begin block 2 */
		// Start line: 532
	/* end block 2 */
	// End Line: 533

	/* begin block 3 */
		// Start line: 542
	/* end block 3 */
	// End Line: 543

	/* begin block 4 */
		// Start line: 545
	/* end block 4 */
	// End Line: 546

int CheckSurvivalPlacing(SCORE_ENTRY *table)
{
	UNIMPLEMENTED();

	int iVar1;

	iVar1 = 0;
	while ((gPlayerScore.time == -1 || ((table->time != -1 && (gPlayerScore.time <= table->time))))) {
		iVar1 = iVar1 + 1;
		table = table + 1;
		if (4 < iVar1) {
			return -1;
		}
	}
	return iVar1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResetTable(struct SCORE_ENTRY *table /*$a0*/)
 // line 261, offset 0x000753d8
	/* begin block 1 */
		// Start line: 262
		// Start offset: 0x000753D8
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x00075408
	// End Line: 272

	/* begin block 2 */
		// Start line: 580
	/* end block 2 */
	// End Line: 581

	/* begin block 3 */
		// Start line: 583
	/* end block 3 */
	// End Line: 584

	/* begin block 4 */
		// Start line: 586
	/* end block 4 */
	// End Line: 587

void ResetTable(SCORE_ENTRY *table)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = 4;
	do {
		table->time = -1;
		table->items = -1;
		iVar1 = iVar1 + -1;
		*(undefined2 *)table->name = DAT_000aa8f4;
		table = table + 1;
	} while (-1 < iVar1);
	return;
	*/
}





