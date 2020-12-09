#ifndef SCORES_H
#define SCORES_H

extern SCORE_TABLES ScoreTables;
extern PLAYER_SCORE gPlayerScore;

extern void InitialiseScoreTables(); // 0x00074EC0

extern int OnScoreTable(SCORE_ENTRY **tablept); // 0x0007503C

extern void AddScoreToTable(SCORE_ENTRY *table, int entry); // 0x000751F8
extern void ResetTable(SCORE_ENTRY *table); // 0x000753D8


#endif
