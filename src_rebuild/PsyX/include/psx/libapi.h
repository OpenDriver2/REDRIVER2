#ifndef LIBAPI_H
#define LIBAPI_H

#ifndef KERNEL_H
#include "kernel.h"
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern long SetRCnt(long spec, unsigned short target, long mode);
extern long GetRCnt(long spec);
extern long ResetRCnt(long spec);
extern long StartRCnt(long spec);
extern long StopRCnt(long spec);

extern long OpenEvent(unsigned long desc,long spec,long mode,long(*func)());
extern long CloseEvent(unsigned long event);
extern long WaitEvent(unsigned long event);
extern long TestEvent(unsigned long event);
extern long EnableEvent(unsigned long event);
extern long DisableEvent(unsigned long event);
extern void DeliverEvent(unsigned long ev1, long ev2);
extern void UnDeliverEvent(unsigned long ev1, long ev2);

extern long OpenTh(long (*func)(), unsigned long , unsigned long);
extern int CloseTh(long unk00);
extern int ChangeTh(long unk00);
	
/*
extern long open(char* unk00, unsigned long);
extern long close(long unk00);
extern long lseek(long unk00, long, long);
extern long read(long unk00, void *, long);
extern long write(long unk00, void *, long);
extern long ioctl(long unk00, long, long);
	
extern struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY *);
extern struct DIRENTRY* nextfile(struct DIRENTRY* unk00);
	
extern long erase(char* unk00);
extern long undelete(char* unk00);
extern long format(char* unk00);
extern long rename(char* unk00, char *);
extern long cd(char* unk00);
*/
	
extern long LoadTest(char*  unk00, struct EXEC *);
extern long Load(char * unk00, struct EXEC *);
extern long Exec(struct EXEC * unk00, long, char **);
extern long LoadExec(char * unk00, unsigned long, unsigned long);

extern long InitPAD(char * unk00,long ,char *,long);
extern long StartPAD();
extern void StopPAD();
extern void EnablePAD();
extern void DisablePAD();

extern void FlushCache();
extern void ReturnFromException();
extern int  EnterCriticalSection();
extern void ExitCriticalSection();
extern void Exception();
extern void SwEnterCriticalSection();
extern void SwExitCriticalSection();

extern unsigned long SetSp(unsigned long newsp);
extern unsigned long GetSp();
extern unsigned long GetGp();
extern unsigned long GetCr();
extern unsigned long GetSr();
extern unsigned long GetSysSp();

extern long SetConf(unsigned long,unsigned long,unsigned long);
extern void GetConf(unsigned long *,unsigned long *,unsigned long *);

/*
extern long _get_errno(void);
extern long _get_error(long);
*/
extern void SystemError( char, long);
extern void SetMem(long);

extern long Krom2RawAdd( unsigned long );
extern long Krom2RawAdd2(unsigned short);

extern void _96_init(void);
extern void _96_remove(void);
extern void _boot(void);

extern void ChangeClearPAD( long );

/* prototypes added by shino 96/05/22 */
extern void InitCARD(long val);
extern long StartCARD();
extern long StopCARD();
extern void _bu_init();
extern long _card_info(long chan);
extern long _card_clear(long chan);
extern long _card_load(long chan);
extern long _card_auto(long val);
extern void _new_card();
extern long _card_status(long drv);
extern long _card_wait(long drv);
extern unsigned long _card_chan(void);
extern long _card_write(long chan, long block, unsigned char *buf);
extern long _card_read(long chan, long block, unsigned char *buf);
extern long _card_format(long chan);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif


#endif
