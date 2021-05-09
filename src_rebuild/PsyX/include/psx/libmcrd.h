#ifndef LIBMCRD_H
#define LIBMCRD_H

#include "kernel.h"

typedef void (*MemCB)( long cmds, long rslt );

#define McFuncExist		(1)
#define McFuncAccept		(2)
#define McFuncReadFile		(3)
#define McFuncWriteFile		(4)
#define McFuncReadData		(5)
#define McFuncWriteData		(6)

#define	McErrNone		(0)
#define	McErrCardNotExist	(1)
#define	McErrCardInvalid	(2)
#define	McErrNewCard		(3)
#define	McErrNotFormat		(4)
#define	McErrFileNotExist	(5)
#define	McErrAlreadyExist	(6)
#define	McErrBlockFull		(7)
#define	McErrExtend		(0x8000)

extern void MemCardInit( long val );
extern void MemCardEnd( void );
extern void MemCardStart(void);
extern void MemCardStop(void);
extern long MemCardExist( long chan );
extern long MemCardAccept( long chan );
extern long MemCardOpen( long chan, char* file, long flag );
extern void MemCardClose(void);
extern long MemCardReadData( unsigned long* adrs, long ofs, long bytes );
extern long MemCardReadFile( long chan, char* file, unsigned long* adrs, long ofs, long bytes );
extern long MemCardWriteData( unsigned long* adrs, long ofs, long bytes );
extern long MemCardWriteFile( long chan, char* file, unsigned long* adrs, long ofs ,long bytes );
extern long MemCardCreateFile( long chan, char* file, long blocks );
extern long MemCardDeleteFile( long chan, char* file );
extern long MemCardFormat( long chan );
extern long MemCardUnformat(long chan);
extern long MemCardSync( long mode, long* cmds, long* rslt );
extern MemCB MemCardCallback( MemCB func );
extern long MemCardGetDirentry( long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max );

#endif
