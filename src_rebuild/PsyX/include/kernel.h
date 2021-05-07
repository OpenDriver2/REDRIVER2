#ifndef KERNEL_H
#define KERNEL_H

#ifndef R3000_H
#include "r3000.h"
#endif

#ifndef ASM_H
#include "asm.h"
#endif

#define DescMask 	0xff000000
#define DescTH 		DescMask
#define DescHW   	0xf0000000
#define DescEV   	0xf1000000
#define DescRC   	0xf2000000
#define DescUEV   	0xf3000000
#define DescSW   	0xf4000000

#define HwVBLANK	(DescHW|0x01)
#define HwGPU		(DescHW|0x02)
#define HwCdRom		(DescHW|0x03)
#define HwDMAC		(DescHW|0x04)
#define HwRTC0		(DescHW|0x05)
#define HwRTC1		(DescHW|0x06)
#define HwRTC2		(DescHW|0x07)
#define HwCNTL		(DescHW|0x08)
#define HwSPU		(DescHW|0x09)
#define HwPIO		(DescHW|0x0a)
#define HwSIO		(DescHW|0x0b)

#define HwCPU		(DescHW|0x10)
#define HwCARD		(DescHW|0x11)
#define HwCARD_0	(DescHW|0x12)
#define HwCARD_1	(DescHW|0x13)
#define SwCARD		(DescSW|0x01)
#define SwMATH          (DescSW|0x02)

#define RCntCNT0     	(DescRC|0x00)
#define RCntCNT1  	(DescRC|0x01)
#define RCntCNT2  	(DescRC|0x02) 
#define RCntCNT3  	(DescRC|0x03)

#define RCntMdINTR	0x1000
#define RCntMdNOINTR	0x2000
#define RCntMdSC	0x0001
#define RCntMdSP	0x0000
#define RCntMdFR	0x0000
#define RCntMdGATE	0x0010

#define EvSpCZ		0x0001		/* counter becomes zero */
#define EvSpINT		0x0002		/* interrupted */
#define EvSpIOE		0x0004		/* end of i/o */
#define EvSpCLOSE	0x0008		/* file was closed */
#define EvSpACK		0x0010		/* command acknowledged */
#define EvSpCOMP	0x0020		/* command completed */
#define EvSpDR		0x0040		/* data ready */
#define EvSpDE		0x0080		/* data end */
#define EvSpTIMOUT      0x0100          /* time out */
#define EvSpUNKNOWN     0x0200          /* unknown command */
#define EvSpIOER	0x0400		/* end of read buffer */
#define EvSpIOEW	0x0800		/* end of write buffer */
#define EvSpTRAP       	0x1000          /* general interrupt */
#define EvSpNEW		0x2000		/* new device */
#define EvSpSYSCALL	0x4000		/* system call instruction */
#define EvSpERROR	0x8000		/* error happned */
#define EvSpPERROR	0x8001		/* previous write error happned */
#define EvSpEDOM        0x0301		/* domain error in libmath */
#define EvSpERANGE      0x0302		/* range error in libmath */

#define EvMdINTR	0x1000
#define EvMdNOINTR	0x2000

#define EvStUNUSED    	0x0000
#define EvStWAIT    	0x1000
#define EvStACTIVE    	0x2000
#define EvStALREADY   	0x4000

#define TcbMdRT		0x1000		/* reserved by system */
#define TcbMdPRI	0x2000		/* reserved by system */

#define TcbStUNUSED	0x1000
#define	TcbStACTIVE	0x4000

struct ToT {
	unsigned long *head;
	long size;
};

struct TCBH {
	struct TCB *entry;	/* NULL */
	long flag;
};

struct TCB {
	long status;
	long mode;
	unsigned long reg[NREGS];	/* never change the offset of this */
	long system[6];			/* reserved by system */
};

struct EvCB {
	unsigned long desc;	
	long status;
	long spec;
	long mode;
	long (*FHandler)();
	long system[2];			/* reserved by system */
};

//#if !defined(D3D9)
#if 0///@FIXME Really not defined D3D9 :/
struct EXEC {                   
        unsigned long pc0;      
        unsigned long gp0;      
        unsigned long t_addr;   
        unsigned long t_size;   
        unsigned long d_addr;   
        unsigned long d_size;   
        unsigned long b_addr;   
        unsigned long b_size;   
	unsigned long s_addr;
	unsigned long s_size;
	unsigned long sp,fp,gp,ret,base;
};


struct XF_HDR {
	char key[8];
	unsigned long text;
	unsigned long data;
	struct EXEC exec;
	char title[60];		/* "PlayStation(tm) Executable A1" */
};
#endif

struct DIRENTRY {
	char name[20];
	long attr;
	long size;
	struct DIRENTRY *next;
	long head;
	char system[4];
};


extern struct ToT SysToT[32];

extern long SysClearRCnt[];

#ifndef NULL
#define NULL (0)
#endif

#endif /* _KERNEL_H */


