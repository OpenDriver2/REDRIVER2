
#include "../decomp_defs.h"

char AnalogueUnpack[] = { 0, 0xCD, 0xC1, 0xB5, 0xA9, 0x9D, 0x91, 0x85, 0, 0x33, 0x3F, 0x4B, 0x57, 0x63, 0x6F, 0x7B };

/*
 * Offset 0x1A104
 * D:\driver2\game\C\REPLAYS.C (line 498)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitPadRecording()
{ // line 2, address 0x1a104
	int i; // $s0
	int remain; // $s0
} // line 152, address 0x1a29c
/*
 * Offset 0x1A29C
 * D:\driver2\game\C\REPLAYS.C (line 657)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ SaveReplayToBuffer(char *buffer /*$s0*/)
{ // line 1, address 0x1a29c
	struct REPLAY_SAVE_HEADER *header; // $s2
	int i; // $a2
	int length; // $s1
	int numstreams; // $s6
} // line 76, address 0x1a800
/*
 * Offset 0x1A800
 * D:\driver2\game\C\REPLAYS.C (line 740)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ LoadReplayFromBuffer(char *buffer /*$s1*/)
{ // line 2, address 0x1a800
	struct REPLAY_SAVE_HEADER *header; // $s3
	struct REPLAY_STREAM_HEADER *sheader; // $t0
	int i; // $a1
	int length; // $s0
} // line 73, address 0x1adb8
/*
 * Offset 0x1ADB8
 * D:\driver2\game\C\REPLAYS.C (line 1310)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ cjpRecord(int stream /*$s1*/, unsigned long *ppad /*$s4*/, char *psteer /*$s2*/, char *ptype /*$s3*/)
{ // line 1, address 0x1adb8
	unsigned long t0; // stack address -32
	int t1; // $s0
} // line 60, address 0x1af7c
/*
 * Offset 0x1AF9C
 * D:\driver2\game\C\REPLAYS.C (line 1222)
 * Stack frame base $sp, length 8
 */
int /*$ra*/ valid_region(int x /*$a0*/, int z /*$a1*/)
{ // line 2, address 0x1af9c
	struct XYPAIR region_coords; // stack address -8
	int region; // $a0
} // line 47, address 0x1b064
/*
 * Offset 0x1B064
 * D:\driver2\game\C\REPLAYS.C (line 1271)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ cjpPlay(int stream /*$a0*/, unsigned long *ppad /*$s2*/, char *psteer /*$s0*/, char *ptype /*$s1*/)
{ // line 1, address 0x1b064
	int ret; // $a0
	unsigned long t0; // stack address -24
	int t1; // $v1
} // line 20, address 0x1b0f8
/*
 * Offset 0x1B0F8
 * D:\driver2\game\C\REPLAYS.C (line 1182)
 * Stack frame base $sp, length 0
 */
char /*$ra*/ GetPingInfo(char *cookieCount /*$a2*/)
{ // line 1, address 0x1b0f8
	struct _PING_PACKET *pp; // $a1
	char retCarId; // $v0
} // line 24, address 0x1b180
/*
 * Offset 0x1B180
 * D:\driver2\game\C\REPLAYS.C (line 1059)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: ra
 */
int /*$ra*/ LoadAttractReplay(int mission /*$a2*/)
{ // line 1, address 0x1b180
	char filename[32]; // stack address -40
} // line 12, address 0x1b1e4
/*
 * Offset 0x1B1E4
 * D:\driver2\game\C\REPLAYS.C (line 1383)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ AllocateReplayStream(struct REPLAY_STREAM *stream /*$a0*/, int maxpad /*$a1*/)
{
}
/*
 * Offset 0x1B258
 * D:\driver2\game\C\REPLAYS.C (line 1402)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ Get(int stream /*$a0*/, unsigned long *pt0 /*$a1*/)
{ // line 1, address 0x1b258
	struct REPLAY_STREAM *rstream; // $a2
	unsigned long t0; // $a0
} // line 36, address 0x1b2e8
/*
 * Offset 0x1B2E8
 * D:\driver2\game\C\REPLAYS.C (line 1440)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ Put(int stream /*$a0*/, unsigned long *pt0 /*$a1*/)
{ // line 2, address 0x1b2e8
	struct REPLAY_STREAM *rstream; // $a0
	unsigned char **pstream; // $a3
	unsigned long t0; // $a1
} // line 37, address 0x1b3cc
/*
 * Offset 0x1B3CC
 * D:\driver2\game\C\REPLAYS.C (line 1479)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RecordWaypoint()
{
}