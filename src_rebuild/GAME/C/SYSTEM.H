#ifndef SYSTEM_H
#define SYSTEM_H

extern char* _overlay_buffer;		// 0x1C0000
extern char* _frontend_buffer;		// 0xFB400
extern char* _other_buffer;			// 0xF3000
extern char* _other_buffer2;		// 0xE7000

extern OTTYPE* _OT1;				// 0xF3000
extern OTTYPE* _OT2;				// 0xF7200

extern char* _primTab1;				// 0xFB400
extern char* _primTab2;				// 0x119400
extern char* _replay_buffer;		// 0x1FABBC

extern const char* mallocptr_start;

extern char* mallocptr;

#ifdef USE_CRT_MALLOC

extern char* sys_malloc(int size, char* funcname, int line);
extern void sys_freeall();

#ifdef _DEBUG
#define D_MALLOC(size)	sys_malloc(size, __FUNCTION__, __LINE__)
#else
#define D_MALLOC(size)	sys_malloc(size, NULL, 0)
#endif

#else
#define D_MALLOC(size)	mallocptr; mallocptr += (size)
#endif

#define MALLOC_BEGIN() \
	{ \
		char* _oldmalloc = mallocptr;

#define MALLOC_END() \
	if(mallocptr > _oldmalloc) printWarning("malloc(%d) in %s, line %d. Malloc usage: %d\n", mallocptr-_oldmalloc, __FUNCTION__, __LINE__, (mallocptr-mallocptr_start));\
}

extern int leadAIRequired;
extern int leadAILoaded;
extern int pathAILoaded;

extern char* LoadingScreenNames[];

struct DB // hashcode: 0xE4F25C4D (dec: -453878707)
{
	char* primptr; // size=0, offset=0
	OTTYPE* ot; // size=0, offset=4
	char* primtab; // size=0, offset=8
	int id; // size=0, offset=12
	DRAWENV draw; // size=92, offset=16
	DISPENV disp; // size=20, offset=108
};

extern DRAW_MODE draw_mode_pal;
extern DRAW_MODE draw_mode_ntsc;

extern DB MPBuff[2][2];
extern DB* last;
extern DB* current;

#define OTLEN	13
#define	OTSIZE	(1<<OTLEN)		/* ordering table size */

#ifdef USE_32_BIT_ADDR
#	define PRIMTAB_SIZE 0x50000
#else
#	define PRIMTAB_SIZE 0x1e000
#endif

#define CITYLUMP_DATA1		0
#define CITYLUMP_TPAGE		1
#define CITYLUMP_DATA2		2
#define CITYLUMP_SPOOL		3

extern int citystart[8];
extern XYPAIR citylumps[8][4];

#ifdef PAL
#define draw_mode draw_mode_pal
#define video_mode MODE_PAL
#else
#define draw_mode draw_mode_ntsc
#define video_mode MODE_NTSC
#endif // PAL

#define CDSECTOR_SIZE 2048

extern void ClearMem(char *mem, int size); // 0x0007F3E8

extern void setMem8(unsigned char *mem, unsigned char val, int size); // 0x0007F47C

extern void setMem16(unsigned short *mem, unsigned short val, int size); // 0x0007F524

extern void Init_FileSystem(); // 0x0007F848

extern void DoCDRetry(); // 0x0007F870

extern int Loadfile(char *name, char *addr); // 0x0007F354

extern int LoadfileSeg(char *name, char *addr, int offset, int loadsize); // 0x0007E9D0

extern void ReportMode(int on); // 0x0007F8B8

#ifdef PSX
extern void loadsectors(char *addr, int sector, int nsectors); // 0x0007F904
#else
extern void loadsectorsPC(char* filename, char *addr, int sector, int nsectors);
#endif // PSX

extern void EnableDisplay(); // 0x0007F984

extern void DisableDisplay(); // 0x0007F9F0

extern void ClearCurrentDrawBuffers();

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
