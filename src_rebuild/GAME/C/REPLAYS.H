#ifndef REPLAYS_H
#define REPLAYS_H

extern int gOutOfTape;
extern REPLAY_PARAMETER_BLOCK *ReplayParameterPtr;

extern REPLAY_STREAM ReplayStreams[8];
extern int NumReplayStreams;

extern char *ReplayStart;
extern char *replayptr;

extern unsigned long PingBufferPos;
extern _PING_PACKET *PingBuffer;

extern int TimeToWay;
extern short PlayerWaypoints;
extern int way_distance;
extern SXYPAIR* PlayerWayRecordPtr;

extern PLAYBACKCAMERA *PlaybackCamera;

extern void InitPadRecording(); // 0x0001A09C

extern int SaveReplayToBuffer(char *buffer); // 0x0001A234

extern int LoadReplayFromBuffer(char *buffer); // 0x0001A798

extern int LoadAttractReplay(int mission); // 0x0001B118

extern char GetPingInfo(char *cookieCount); // 0x0001B090

extern int valid_region(int x, int z); // 0x0001AF34

extern int cjpPlay(int stream, unsigned long *ppad, char *psteer, char *ptype); // 0x0001AFFC

extern void cjpRecord(int stream, unsigned long *ppad, char *psteer, char *ptype); // 0x0001AD50

extern void AllocateReplayStream(struct REPLAY_STREAM *stream, int maxpad); // 0x0001B17C

extern int Get(int stream, unsigned long *pt0); // 0x0001B1F0

extern int Put(int stream, unsigned long *pt0); // 0x0001B280

extern void RecordWaypoint(); // 0x0001B364


#endif
