#ifndef SYSTEM_H
#define SYSTEM_H

extern char _overlay_buffer[0x50000];		// 0x1C0000
extern char _frontend_buffer[0x8000];		// 0xFB400

extern DRAW_MODE draw_mode_pal;
extern DRAW_MODE draw_mode_ntsc;

extern DB MPBuff[2][2];
extern DB* last;
extern DB* current;

extern long _tempOT1[0x10];
extern long _tempOT2[0x10];

extern char _tempPrimTab1[0x8000];		// 0xFB400
extern char _tempPrimTab2[0x8000];		// 0x119400

extern unsigned char NumPlayers;

#ifdef PAL
#define draw_mode draw_mode_pal
#define video_mode MODE_PAL
#else
#define draw_mode draw_mode_ntsc
#define video_mode MODE_NTSC
#endif // PAL

extern void ClearMem(char *mem, int size); // 0x0007F3E8

extern void setMem8(unsigned char *mem, unsigned char val, int size); // 0x0007F47C

extern void setMem16(unsigned short *mem, unsigned short val, int size); // 0x0007F524

extern void Init_FileSystem(); // 0x0007F848

extern void DoCDRetry(); // 0x0007F870

extern int Loadfile(char *name, char *addr); // 0x0007F354

extern int LoadfileSeg(char *name, char *addr, int offset, int loadsize); // 0x0007E9D0

extern void ReportMode(int on); // 0x0007F8B8

extern void data_ready(); // 0x0007FA44

extern void sector_ready(unsigned char intr, unsigned char *result); // 0x0007FA74

extern void loadsectors(char *addr, int sector, int nsectors); // 0x0007F904

extern void EnableDisplay(); // 0x0007F984

extern void DisableDisplay(); // 0x0007F9F0

extern void SwapDrawBuffers(); // 0x0007F6FC

extern void SwapDrawBuffers2(int player); // 0x0007ECF0

extern void UpdatePadData(); // 0x0007FA10

extern void SetupDrawBuffers(); // 0x0007EDDC

extern void SetupDrawBufferData(int num_players); // 0x0007EF0C

extern void InitaliseDrawEnv(struct DB *pBuff, int x, int y, int w, int h); // 0x0007F7C0

extern void ResetCityType(); // 0x0007F5B4

extern void SetCityType(enum CITYTYPE type); // 0x0007F118

extern int FileExists(char *filename); // 0x0007F5C8

extern enum CDTYPE DiscSwapped(char *filename); // 0x0007F640


#endif
