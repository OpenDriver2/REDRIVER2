#ifndef SYSTEM_H
#define SYSTEM_H

struct DRAW_MODE
{
	short x1, y1;
	short x2, y2;
	short width, height;
	short framex, framey;
};

enum CDTYPE
{
	CDTYPE_NODISC = 0,
	CDTYPE_SHELLOPEN = 1,
	CDTYPE_DISCERROR = 2,
	CDTYPE_WRONGDISC = 3,
	CDTYPE_CORRECTDISC = 4,
};

enum CITYTYPE
{
	CITYTYPE_DAY = 0,
	CITYTYPE_NIGHT = 1,
	CITYTYPE_MULTI_DAY = 2,
	CITYTYPE_MULTI_NIGHT = 3,
};


extern volatile char* _overlay_buffer;		// 0x1C0000
extern volatile char* _frontend_buffer;		// 0xFB400
extern volatile char* _other_buffer;		// 0xF3000
extern volatile char* _other_buffer2;		// 0xE7000

extern volatile OTTYPE* _OT1;				// 0xF3000
extern volatile OTTYPE* _OT2;				// 0xF7200

extern volatile char* _primTab1;			// 0xFB400
extern volatile char* _primTab2;			// 0x119400
extern volatile char* _sbank_buffer;		// 0x180000
extern volatile char* _replay_buffer;		// 0x1FABBC

extern char gDataFolder[32];

#define PSX_MALLOC_SIZE 870332

extern volatile char* malloctab;
extern volatile char* mallocptr;

#ifdef USE_CRT_MALLOC

extern char* sys_malloc(int size, char* funcname, int line);
extern char* sys_tempalloc(int size);
extern void sys_tempfree();

extern void sys_freeall();

#define D_TEMPFREE()		sys_tempfree()
#define D_TEMPALLOC(size)	sys_tempalloc(size)

#ifdef _DEBUG
#define D_MALLOC(size)		sys_malloc(size, __FUNCTION__, __LINE__)

#else
#define D_MALLOC(size)		sys_malloc(size, NULL, 0)
#endif

#else
#define D_MALLOC(size)		(char*)mallocptr; mallocptr += (((size) + 3) & -4);
#define D_TEMPALLOC(size)	(char*)mallocptr
#define D_TEMPFREE()
#endif

#ifdef _DEBUG
#define DMalloc_DebugPrint printWarning
#else
#define DMalloc_DebugPrint (void)
#endif

#define D_MALLOC_BEGIN() \
	{ \
		volatile const char* _oldmalloc = mallocptr;

#ifdef __GNUC__
#define D_MALLOC_END() \
		D_TEMPFREE();\
		if(mallocptr > _oldmalloc)\
			DMalloc_DebugPrint("malloc(%d) in %s, line %d. Malloc usage: %d\n", mallocptr-_oldmalloc, __FUNCTION__, __LINE__, (mallocptr-malloctab));\
	} // D_MALLOC_BEGIN block
#else
#define D_MALLOC_END() \
		D_TEMPFREE();\
		if(mallocptr > _oldmalloc)\
			DMalloc_DebugPrint("malloc(%d) in " __FUNCTION__ ", line %d. Malloc usage: %d\n", mallocptr-_oldmalloc, __LINE__, (mallocptr-malloctab));\
	} // D_MALLOC_BEGIN block
#endif

extern int leadAIRequired;
extern int leadAILoaded;
extern int pathAILoaded;

extern char* LevelNames[];
extern char* LoadingScreenNames[];

struct DB
{
	char* primptr;
	OTTYPE* ot;
	char* primtab;
	int id;
	DRAWENV draw;
	DISPENV disp;
};

extern DB MPBuff[2][2];
extern DB* last;
extern DB* current;

extern DRAW_MODE draw_mode_pal;
extern DRAW_MODE draw_mode_ntsc;

#define SCREEN_FB	512
#define SCREEN_FB_H	256

#ifdef PAL_VERSION
#define SCREEN_H	256
#define draw_mode draw_mode_pal
#define video_mode MODE_PAL
#else
#define SCREEN_H	240
#define draw_mode draw_mode_ntsc
#define video_mode MODE_NTSC
#endif // PAL

// ordering table size 
#ifdef PSX
#define	OTSIZE	0x1080
#else
#define	OTSIZE	0x2000
#endif

#ifdef USE_EXTENDED_PRIM_POINTERS
#	define PRIMTAB_SIZE 0xA0000
#else
#	define PRIMTAB_SIZE 0x1e000
#endif

#define CITYLUMP_DATA1		0
#define CITYLUMP_TPAGE		1
#define CITYLUMP_DATA2		2
#define CITYLUMP_SPOOL		3

extern int citystart[8];
extern XYPAIR citylumps[8][4];

#define CDSECTOR_SIZE 2048

extern void ClearMem(char *mem, int size); // 0x0007F3E8
extern void setMem8(unsigned char *mem, unsigned char val, int size); // 0x0007F47C
extern void setMem16(unsigned short *mem, unsigned short val, int size); // 0x0007F524

extern void Init_FileSystem(); // 0x0007F848

extern int FileExists(char *filename); // 0x0007F5C8
extern int Loadfile(char *name, char *addr); // 0x0007F354
extern int LoadfileSeg(char *name, char *addr, int offset, int loadsize); // 0x0007E9D0

extern void ReportMode(int on); // 0x0007F8B8

extern void loadsectors(char *addr, int sector, int nsectors); // 0x0007F904

extern void EnableDisplay(); // 0x0007F984
extern void DisableDisplay(); // 0x0007F9F0

extern void ClearCurrentDrawBuffers();

extern void SwapDrawBuffers(); // 0x0007F6FC
extern void SwapDrawBuffers2(int player); // 0x0007ECF0

extern void UpdatePadData(); // 0x0007FA10

extern void SetupDrawBuffers(); // 0x0007EDDC
extern void SetupDrawBufferData(int num_players); // 0x0007EF0C

extern void InitaliseDrawEnv(DB *pBuff, int x, int y, int w, int h); // 0x0007F7C0

extern void ResetCityType(); // 0x0007F5B4
extern void SetCityType(CITYTYPE type); // 0x0007F118

extern CITYTYPE GetCityType();
extern CDTYPE DiscSwapped(char *filename); // 0x0007F640


#endif
