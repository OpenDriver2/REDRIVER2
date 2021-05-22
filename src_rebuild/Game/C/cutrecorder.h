#ifndef CUTRECORDER_H
#define CUTRECORDER_H

extern int gCutsceneChaseAutoTest;
extern int gCutsceneAsReplay;
extern int gCutsceneAsReplay_PlayerId;
extern int gCutsceneAsReplay_PlayerChanged;
extern int gCutsceneAsReplay_ReserveSlots;
extern char gCutsceneRecorderPauseText[64];
extern char gCurrentChasePauseText[64];

extern void		InitChaseAutoTest(char* configFilename);
extern void		InitCutsceneRecorder(char* configFilename);

extern void		CutRec_Reset();
extern void		CutRec_Step();
extern void		CutRec_Draw();
extern int		CutRec_StorePingInfo(int cookieCount, int carId);
extern void		CutRec_CheckInvalidatePing(int carId, int howHard);
extern void		CutRec_NextChase(int dir);
extern void		CutRec_ReserveSlots();
extern void		CutRec_HandleCarRequest();
extern int		CutRec_InitPlayers();
extern int		CutRec_InitMission(char* filename);
extern int		CutRec_RecordPad(CAR_DATA* cp, uint* t0, char* t1, char* t2);
extern int		CutRec_SaveReplayToFile(char* filename);

#ifdef CUTSCENE_RECORDER

#define _CutRec_IsAutoTestOn()				(gCutsceneChaseAutoTest != 0)
#define _CutRec_IsOn()						(gCutsceneAsReplay != 0)
#define _CutRec_Step()						CutRec_Step()
#define _CutRec_Draw()						CutRec_Draw()
#define _CutRec_Reset()						CutRec_Reset()
#define _CutRec_StorePingInfo(a,b)			CutRec_StorePingInfo(a,b)
#define _CutRec_CheckInvalidatePing(a,b)	CutRec_CheckInvalidatePing(a, b)
#define _CutRec_NextChase(a)				CutRec_NextChase(a)
#define _CutRec_ReserveSlots()				CutRec_ReserveSlots
#define _CutRec_HandleCarRequest()			CutRec_HandleCarRequest()
#define _CutRec_InitPlayers()				CutRec_InitPlayers()
#define _CutRec_InitMission(a)				CutRec_InitMission(a)
#define _CutRec_RecordPad(a, b, c, d)		CutRec_RecordPad(a, b, c, d)

#else

#define _CutRec_IsOn()						(0)
#define _CutRec_Step()						(0)
#define _CutRec_Draw()						(0)
#define _CutRec_Reset()						(0)
#define _CutRec_StorePingInfo(a,b)			(0)
#define _CutRec_CheckInvalidatePing(a,b)	(0)
#define _CutRec_NextChase(a)				(0)
#define _CutRec_ReserveSlots()				(0)
#define _CutRec_HandleCarRequest()			(0)
#define _CutRec_InitPlayers()				(0)
#define _CutRec_InitMission(a)				(0)
#define _CutRec_RecordPad(a, b, c, d)		(0)

#endif


#endif // CUTRECORDER_H