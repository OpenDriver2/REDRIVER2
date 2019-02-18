#include "../decomp_defs.h"

/*
 * Offset 0x608B4
 * D:\driver2\game\C\MISSION.C (line 1347)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ InitialiseMissionDefaults()
{ // line 2, address 0x608b4
	int i; // $a0
} // line 88, address 0x60adc
/*
 * Offset 0x60ADC
 * D:\driver2\game\C\MISSION.C (line 1437)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ LoadMission(int missionnum /*$s0*/)
{ // line 1, address 0x60adc
	char filename[32]; // stack address -64
	unsigned long header; // stack address -32
	unsigned long address; // $s0
	unsigned long length; // $s1
	int size; // $t1
	int i; // $v0
	{ // line 240, address 0x60df0
		int flags; // $a1
		int time; // $a2
	} // line 261, address 0x60e6c
	{ // line 330, address 0x60fec
		struct _ROUTE_INFO *rinfo; // $s0
	} // line 356, address 0x6108c
	{ // line 393, address 0x61164
		int num; // $v1
	} // line 404, address 0x61190
} // line 442, address 0x612c0
/*
 * Offset 0x612DC
 * D:\driver2\game\C\MISSION.C (line 1881)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ HandleMission()
{
}
/*
 * Offset 0x6150C
 * D:\driver2\game\C\MISSION.C (line 1962)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ HandleTimer(struct MR_TIMER *timer /*$s0*/)
{
}
/*
 * Offset 0x616EC
 * D:\driver2\game\C\MISSION.C (line 2015)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ RegisterChaseHit(int car1 /*$a0*/, int car2 /*$a1*/)
{
}
/*
 * Offset 0x617EC
 * D:\driver2\game\C\MISSION.C (line 2140)
 * Stack frame base $sp, length 720
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ Swap2Cars(int curslot /*$a3*/, int newslot /*$s1*/)
{ // line 1, address 0x617ec
	struct _CAR_DATA cd; // stack address -704
	struct _CAR_DATA *cp; // $s0
	int ctrlNodeCurId; // $s4
	int pnodeCurId; // $s5
	int ctrlNodeNewId; // $t2
	int pnodeNewId; // $t3
} // line 81, address 0x61cc4
/*
 * Offset 0x61CC4
 * D:\driver2\game\C\MISSION.C (line 2234)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleMissionThreads()
{ // line 2, address 0x61cc4
	struct MR_THREAD *thread; // $s0
	int running; // $s1
	unsigned long value; // $a1
	int i; // $a0
} // line 43, address 0x61ea4
/*
 * Offset 0x61EA4
 * D:\driver2\game\C\MISSION.C (line 2279)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ MRCommand(struct MR_THREAD *thread /*$s1*/, unsigned long cmd /*$a1*/)
{ // line 1, address 0x61ea4
	unsigned long val1; // $s0
	unsigned long val2; // $s0
} // line 160, address 0x624d8
/*
 * Offset 0x624D8
 * D:\driver2\game\C\MISSION.C (line 2701)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ MRProcessTarget(struct MR_THREAD *thread /*$s7*/, struct _TARGET *target /*$s5*/)
{ // line 1, address 0x624d8
	struct VECTOR tv; // stack address -96
	struct VECTOR pv; // stack address -80
	int ret; // $fp
	unsigned long dist; // $s6
	int slot; // stack address -48
	int message; // $v0
	int sample; // $a0
	{ // line 158, address 0x62a24
		unsigned long message; // $s1
		unsigned long timer; // $s0
		unsigned long delay; // $s2
	} // line 173, address 0x62a94
	{ // line 233, address 0x62c64
		int direction; // $s0
		long pos[4]; // stack address -64
		int *inform; // $s4
		struct _CAR_DATA *cp; // $v0
	} // line 239, address 0x62c64
	{ // line 368, address 0x63090
		long pos[4]; // stack address -64
	} // line 375, address 0x630f8
	{ // line 403, address 0x63204
	} // line 403, address 0x63204
	{ // line 434, address 0x632bc
	} // line 434, address 0x632bc
	{ // line 457, address 0x63380
	} // line 457, address 0x63380
} // line 593, address 0x63790
/*
 * Offset 0x63790
 * D:\driver2\game\C\MISSION.C (line 3311)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ MRCreateCar(struct _TARGET *target /*$s1*/)
{ // line 1, address 0x63790
	long pos[4]; // stack address -64
	int actAsCop; // $s2
	int damaged; // $s7
	int model; // $s4
	int palette; // $s5
	int dir; // $s3
	int rot; // $a2
	int id; // $s0
	char playerid; // stack address -48
} // line 79, address 0x63a08
/*
 * Offset 0x63A08
 * D:\driver2\game\C\MISSION.C (line 3398)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ PreProcessTargets()
{ // line 2, address 0x63a08
	struct _TARGET *target; // $s0
	int i; // $s1
} // line 52, address 0x63be0
/*
 * Offset 0x63BE0
 * D:\driver2\game\C\MISSION.C (line 3469)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ HandleGameOver()
{ // line 3, address 0x63be0
	{ // line 5, address 0x63c20
		struct _PLAYER *lp; // $s0
		struct _CAR_DATA *cp; // $a2
		int i; // $s2
		int playersdead; // $s3
		{ // line 41, address 0x63d4c
			int surfInd; // $v1
		} // line 53, address 0x63de4
	} // line 96, address 0x63f4c
} // line 120, address 0x63fec
/*
 * Offset 0x63FEC
 * D:\driver2\game\C\MISSION.C (line 3623)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetMissionComplete()
{
}
/*
 * Offset 0x64210
 * D:\driver2\game\C\MISSION.C (line 3716)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ActivateNextFlag()
{ // line 2, address 0x64210
	int i; // $a3
	int j; // $a1
} // line 23, address 0x642d0
/*
 * Offset 0x642D0
 * D:\driver2\game\C\MISSION.C (line 2046)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ PauseMissionTimer(int pause /*$a0*/)
{
}
/*
 * Offset 0x64310
 * D:\driver2\game\C\MISSION.C (line 2060)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetMissionMessage(char *message /*$a0*/, int priority /*$a1*/, int seconds /*$a2*/)
{ // line 1, address 0x64310
	int i; // $a3
} // line 19, address 0x643a8
/*
 * Offset 0x643B0
 * D:\driver2\game\C\MISSION.C (line 2081)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetPlayerMessage(int player /*$a0*/, char *message /*$a1*/, int priority /*$a2*/, int seconds /*$a3*/)
{
}
/*
 * Offset 0x6442C
 * D:\driver2\game\C\MISSION.C (line 2094)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ TargetComplete(struct _TARGET *target /*$a0*/, int player /*$a1*/)
{ // line 1, address 0x6442c
	unsigned long complete; // $a0
} // line 21, address 0x64470
/*
 * Offset 0x64470
 * D:\driver2\game\C\MISSION.C (line 2117)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ TargetActive(struct _TARGET *target /*$a0*/, int player /*$a1*/)
{ // line 1, address 0x64470
	unsigned long active; // $a0
} // line 21, address 0x644b4
/*
 * Offset 0x644B4
 * D:\driver2\game\C\MISSION.C (line 2223)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetConfusedCar(int slot /*$a0*/)
{
}
/*
 * Offset 0x64500
 * D:\driver2\game\C\MISSION.C (line 2441)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ MROperator(struct MR_THREAD *thread /*$s3*/, unsigned long op /*$s0*/)
{ // line 1, address 0x64500
	int result; // $s2
	long val1; // $s1
	long val2; // $a1
} // line 51, address 0x64614
/*
 * Offset 0x64614
 * D:\driver2\game\C\MISSION.C (line 2494)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ MRFunction(struct MR_THREAD *thread /*$s0*/, unsigned long fnc /*$a1*/)
{ // line 1, address 0x64614
} // line 17, address 0x6467c
/*
 * Offset 0x6467C
 * D:\driver2\game\C\MISSION.C (line 2514)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MRInitialiseThread(struct MR_THREAD *thread /*$a0*/, unsigned long *pc /*$a1*/, unsigned char player /*$a2*/)
{
}
/*
 * Offset 0x64698
 * D:\driver2\game\C\MISSION.C (line 2526)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ MRStartThread(struct MR_THREAD *callingthread /*$t0*/, unsigned long addr /*$a1*/, unsigned char player /*$a2*/)
{ // line 1, address 0x64698
	int i; // $v1
} // line 17, address 0x646e8
/*
 * Offset 0x646F8
 * D:\driver2\game\C\MISSION.C (line 2545)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ MRStopThread(struct MR_THREAD *thread /*$a0*/)
{
}
/*
 * Offset 0x64704
 * D:\driver2\game\C\MISSION.C (line 2551)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ MRCommitThreadGenocide()
{ // line 2, address 0x64704
	int i; // $s0
} // line 6, address 0x64748
/*
 * Offset 0x64748
 * D:\driver2\game\C\MISSION.C (line 2560)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ MRJump(struct MR_THREAD *thread /*$a2*/, long jump /*$a1*/)
{
}
/*
 * Offset 0x64794
 * D:\driver2\game\C\MISSION.C (line 2575)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MRPush(struct MR_THREAD *thread /*$a0*/, long value /*$a1*/)
{
}
/*
 * Offset 0x647AC
 * D:\driver2\game\C\MISSION.C (line 2585)
 * Stack frame base $sp, length 0
 */
long /*$ra*/ MRPop(struct MR_THREAD *thread /*$a0*/)
{ // line 1, address 0x647ac
} // line 12, address 0x647c8
/*
 * Offset 0x647C8
 * D:\driver2\game\C\MISSION.C (line 2600)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
long /*$ra*/ MRGetParam(struct MR_THREAD *thread /*$s0*/)
{ // line 1, address 0x647c8
	long value; // $a1
} // line 20, address 0x64834
/*
 * Offset 0x64834
 * D:\driver2\game\C\MISSION.C (line 2622)
 * Stack frame base $sp, length 0
 */
long /*$ra*/ MRGetVariable(struct MR_THREAD *thread /*$a2*/, unsigned long var /*$a1*/)
{
}
/*
 * Offset 0x64918
 * D:\driver2\game\C\MISSION.C (line 2648)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MRSetVariable(struct MR_THREAD *thread /*$v1*/, unsigned long var /*$a1*/, long value /*$a2*/)
{
}
/*
 * Offset 0x64A4C
 * D:\driver2\game\C\MISSION.C (line 3296)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ MRRequestCar(struct _TARGET *target /*$a0*/)
{
}
/*
 * Offset 0x64A8C
 * D:\driver2\game\C\MISSION.C (line 3305)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ MRHandleCarRequests()
{
}
/*
 * Offset 0x64AB8
 * D:\driver2\game\C\MISSION.C (line 3392)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MRCancelCarRequest(struct _TARGET *target /*$a0*/)
{
}
/*
 * Offset 0x64ADC
 * D:\driver2\game\C\MISSION.C (line 3452)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ Handle321Go()
{ // line 2, address 0x64adc
} // line 15, address 0x64b38
/*
 * Offset 0x64B38
 * D:\driver2\game\C\MISSION.C (line 3591)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ CompleteAllActiveTargets(int player /*$a0*/)
{ // line 2, address 0x64b38
	int i; // $a1
	int flag1; // $a3
	int flag2; // $a2
} // line 30, address 0x64ba0
/*
 * Offset 0x64BA0
 * D:\driver2\game\C\MISSION.C (line 3684)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetMissionFailed(enum FAIL_REASON reason /*$a0*/)
{
}
/*
 * Offset 0x64C40
 * D:\driver2\game\C\MISSION.C (line 3704)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetMissionOver(enum PAUSEMODE mode /*$a0*/)
{
}
/*
 * Offset 0x64C8C
 * D:\driver2\game\C\MISSION.C (line 3760)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CalcLapTime(int player /*$a0*/, int time /*$a1*/, int lap /*$a2*/)
{ // line 1, address 0x64c8c
	int i; // $a2
	int ptime; // $a3
} // line 8, address 0x64cc8
/*
 * Offset 0x64CC8
 * D:\driver2\game\C\MISSION.C (line 3770)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SetCarToBeStolen(struct _TARGET *target /*$s0*/, int player /*$s1*/)
{
}
/*
 * Offset 0x64D38
 * D:\driver2\game\C\MISSION.C (line 3781)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MakePhantomCarEqualPlayerCar()
{
}