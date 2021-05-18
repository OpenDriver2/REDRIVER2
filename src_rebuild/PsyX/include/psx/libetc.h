#ifndef LIBETC_H
#define LIBETC_H

#include "types.h"

extern int PadIdentifier;

#define PADLup     (1<<12)
#define PADLdown   (1<<14)
#define PADLleft   (1<<15)
#define PADLright  (1<<13)
#define PADRup     (1<< 4)
#define PADRdown   (1<< 6)
#define PADRleft   (1<< 7)
#define PADRright  (1<< 5)
#define PADi       (1<< 9)
#define PADj       (1<<10)
#define PADk       (1<< 8)
#define PADl       (1<< 3)
#define PADm       (1<< 1)
#define PADn       (1<< 2)
#define PADo       (1<< 0)
#define PADh       (1<<11)
#define PADL1      PADn
#define PADL2      PADo
#define PADR1      PADl
#define PADR2      PADm
#define PADstart   PADh
#define PADselect  PADk
		    
#define MOUSEleft  (1<<3)
#define MOUSEright (1<<2)

#define _PAD(x,y) ((y)<<((x)<<4))

#define getScratchAddr(offset)  ((u_long *)(_scratchData+(offset)*4))

#define MODE_NTSC 0
#define MODE_PAL 1

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern char* _scratchData;

extern int CheckCallback(void);
extern void PadInit(int mode);
extern int ResetCallback(void);
extern int RestartCallback(void);
extern int StopCallback(void);
extern int VSync(int mode);
extern int VSyncCallback(void (*f)(void)) ;
extern long GetVideoMode (void);
extern long SetVideoMode (long mode);
extern u_long PadRead(int id);
extern void PadStop(void);
extern void(*vsync_callback)(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif



#endif


