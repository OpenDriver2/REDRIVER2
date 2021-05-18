#ifndef LIBPAD_H
#define LIBPAD_H

#define PadStateDiscon		0
#define PadStateFindPad		1
#define PadStateFindCTP1	2
#define PadStateFindCTP2	3
#define PadStateReqInfo		4
#define PadStateExecCmd		5
#define PadStateStable		6

#define InfoModeCurID		1
#define InfoModeCurExID		2
#define InfoModeCurExOffs	3
#define InfoModeIdTable		4

#define InfoActFunc		1
#define InfoActSub		2
#define InfoActSize		3
#define InfoActCurr		4
#define InfoActSign		5

#define PadMaxCurr		60
#define PadCurrCTP1		10

#define MAX_CONTROLLERS 2		// TODO: multi-tap (2 ports * 5 taps (1st is Direct))

typedef struct PADRAW
{
	unsigned char status; // size=0, offset=0
	unsigned char id; // size=0, offset=1
	unsigned char buttons[2]; // size=2, offset=2
	unsigned char analog[4]; // size=4, offset=4
} *LPPADRAW;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void PadInitDirect(unsigned char* pad1, unsigned char* pad2);
extern void PadInitMtap(unsigned char* unk00, unsigned char* unk01);
extern void PadInitGun(unsigned char* unk00, int unk01);
extern int PadChkVsync();
extern void PadStartCom();
extern void PadStopCom();
extern unsigned int PadEnableCom(unsigned int unk00);
extern void PadEnableGun(unsigned char unk00);
extern void PadRemoveGun();
extern int PadGetState(int port);
extern int PadInfoMode(int port, int term, int offs);
extern int PadInfoAct(int port, int acno, int term);
extern int PadInfoComb(int unk00, int, int unk01);
extern int PadSetActAlign(int port, unsigned char* table);
extern int PadSetMainMode(int socket, int offs, int lock);
extern void PadSetAct(int port, unsigned char* table, int len);
	
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif