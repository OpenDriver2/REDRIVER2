#include "DRIVER2.H"
#include "SCORES.H"
#include "GLAUNCH.H"
#include "MISSION.H"

#include "STRINGS.H"

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

SCORE_TABLES ScoreTables;
PLAYER_SCORE gPlayerScore;

// [D] [T]
void InitialiseScoreTables(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 2; j++)
			ResetTable(ScoreTables.GetawayTable[i][j]);

		for (j = 0; j < 2; j++)
			ResetTable(ScoreTables.CheckpointTable[i][j]);

		for (j = 0; j < 2; j++)
			ResetTable(ScoreTables.TrailblazerTable[i][j]);

		for (j = 0; j < 2; j++)
			ResetTable(ScoreTables.GateRaceTable[i][j]);

		ResetTable(ScoreTables.SurvivalTable[i][0]);
	}

	gPlayerScore.time = 0;
	gPlayerScore.P2time = 0;
	gPlayerScore.items = 0;
	gPlayerScore.P2items = 0;

	strcpy(gPlayerScore.name, "Mr.X");
}



// decompiled code
// original method signature: 
// int /*$ra*/ OnScoreTable(SCORE_ENTRY **tablept /*$s1*/)
 // line 86, offset 0x0007503c
	/* begin block 1 */
		// Start line: 87
		// Start offset: 0x0007503C
		// Variables:
	// 		SCORE_ENTRY *table; // $s0
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

// [D] [T]
int OnScoreTable(SCORE_ENTRY **tablept)
{
	int position;
	SCORE_ENTRY *table;

	switch (GameType)
	{
		case GAME_GETAWAY:
			table = ScoreTables.GetawayTable[GameLevel][gSubGameNumber];
			position = CheckGetawayPlacing(table);
			break;
		case GAME_GATERACE:
			table = ScoreTables.GateRaceTable[GameLevel][gSubGameNumber];
			position = CheckTrailblazerPlacing(table);
			break;
		case GAME_CHECKPOINT:
			table = ScoreTables.CheckpointTable[GameLevel][gSubGameNumber];
			position = CheckCheckpointPlacing(table);
			break;
		case GAME_TRAILBLAZER:
			table = ScoreTables.TrailblazerTable[GameLevel][gSubGameNumber];
			position = CheckTrailblazerPlacing(table);
			break;
		case GAME_SURVIVAL:
			table = ScoreTables.SurvivalTable[GameLevel][gSubGameNumber];
			position = CheckSurvivalPlacing(table);
			break;
		default:
			return -1;
	}

	if (tablept != NULL)
		*tablept = table;

	return position;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddScoreToTable(SCORE_ENTRY *table /*$a2*/, int entry /*$a1*/)
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

// [D] [T]
void AddScoreToTable(SCORE_ENTRY *table, int entry)
{
	int i;

	i = 3;
	table = table + 4;
	while (entry <= i)
	{
		*table = table[-1];
		table--;
		i--;
	}

	table->time = gPlayerScore.time;
	table->items = gPlayerScore.items;

	strcpy(table->name, gPlayerScore.name);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckGetawayPlacing(SCORE_ENTRY *table /*$a0*/)
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

// [D] [T]
int CheckGetawayPlacing(SCORE_ENTRY *table)
{
	int i;

	i = 0;
	while (gPlayerScore.time == -1 || table->time != -1 && table->time <= gPlayerScore.time) 
	{
		i++;
		table++;

		if (i > 4)
			return -1;
	}

	return i;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckTrailblazerPlacing(SCORE_ENTRY *table /*$a0*/)
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

// [D] [T]
int CheckTrailblazerPlacing(SCORE_ENTRY *table)
{
	int i;

	i = 0;

	do {
		if (gPlayerScore.items == -1) 
		{
			if (gPlayerScore.time != -1) 
			{
				if (table->time == -1) 
					return i;

				if (table->time < gPlayerScore.time)
					return i;

			}
		}
		else if (table->items == -1 || table->items < gPlayerScore.items)
		{
			return i;
		}

		i++;
		table++;

		if (i > 4)
			return -1;

	} while (true);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckCheckpointPlacing(SCORE_ENTRY *table /*$a0*/)
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

// [D] [T]
int CheckCheckpointPlacing(SCORE_ENTRY *table)
{
	int i;

	i = 0;
	while (gPlayerScore.time == -1 || table->time != -1 && table->time <= gPlayerScore.time) 
	{
		i++;
		table++;

		if (i > 4)
			return -1;
	}
	return i;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckSurvivalPlacing(SCORE_ENTRY *table /*$a0*/)
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

// [D] [T]
int CheckSurvivalPlacing(SCORE_ENTRY *table)
{
	int i;

	i = 0;
	while (gPlayerScore.time == -1 || table->time != -1 && gPlayerScore.time <= table->time) 
	{
		i++;
		table++;
		if (i > 4) 
			return -1;
	}
	return i;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResetTable(SCORE_ENTRY *table /*$a0*/)
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

// [D] [T]
void ResetTable(SCORE_ENTRY *table)
{
	int i;

	i = 0;
	while (i < 5)
	{
		table->time = -1;
		table->items = -1;
		strcpy(table->name, "-");
		table++;
		i++;
	}
}





