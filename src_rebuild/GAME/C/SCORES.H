#ifndef SCORES_H
#define SCORES_H


extern void InitialiseScoreTables(); // 0x00074EC0

extern int OnScoreTable(struct SCORE_ENTRY **tablept); // 0x0007503C

extern void AddScoreToTable(struct SCORE_ENTRY *table, int entry); // 0x000751F8

extern int CheckGetawayPlacing(struct SCORE_ENTRY *table); // 0x0007526C

extern int CheckTrailblazerPlacing(struct SCORE_ENTRY *table); // 0x000752BC

extern int CheckCheckpointPlacing(struct SCORE_ENTRY *table); // 0x00075338

extern int CheckSurvivalPlacing(struct SCORE_ENTRY *table); // 0x00075388

extern void ResetTable(struct SCORE_ENTRY *table); // 0x000753D8


#endif
