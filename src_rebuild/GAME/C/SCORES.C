#include "DRIVER2.H"
#include "SCORES.H"
#include "GLAUNCH.H"
#include "MISSION.H"

#include "STRINGS.H"

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





