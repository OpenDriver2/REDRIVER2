#ifndef PAD_H
#define PAD_H


extern struct PAD * __3PADPc(struct PAD *this, char *bufferPtr); // 0x000FEB70

extern void _._3PAD(struct PAD *this, int __in_chrg); // 0x000FFE44

extern int UpdateSlots__3PAD(struct PAD *this); // 0x000FFEA0

extern unsigned short GetPadData__3PADi(struct PAD *this, int pad); // 0x000FECC0

extern unsigned int NegConInserted__3PAD(struct PAD *this); // 0x000FFEE0

extern unsigned int ControllerInserted__3PAD(struct PAD *this); // 0x000FFF10

extern unsigned int ControllerChanged__3PAD(struct PAD *this); // 0x000FFF48

extern unsigned int SetControllerType__3PAD(struct PAD *this); // 0x000FFF5C

extern unsigned int MouseInserted__3PAD(struct PAD *this); // 0x001000D0

extern int GetMouseX__3PAD(struct PAD *this); // 0x00100158

extern int GetMouseY__3PAD(struct PAD *this); // 0x0010016C

extern void ResetPadData__3PAD(struct PAD *this); // 0x00100180

extern char * port_name__3PADi(struct PAD *this, int port); // 0x000FF2CC

extern unsigned int WaitUntilCardRemoved__3PADi(struct PAD *this, int slot); // 0x000FF3C0

extern unsigned int WaitUntilAnyCardInserted__3PAD(struct PAD *this); // 0x000FF6E4

extern char * GetPortName__3PADi(struct PAD *this, int slot); // 0x001001AC

extern char * GetControllerPortName__3PAD(struct PAD *this); // 0x00100214

extern unsigned int CardSelected__3PADi(struct PAD *this, int slot); // 0x00100244

extern unsigned int CurrCardInfoRead__3PAD(struct PAD *this); // 0x00100260

extern void check_ports__3PAD(struct PAD *this); // 0x000FFA1C

extern void search_ports__3PADib(struct PAD *this, int slot, unsigned int cycle); // 0x000FFC98

extern int next_port__3PADi(struct PAD *this, int port); // 0x0010029C

extern int GetCurrNoUsedBlocks__3PAD(struct PAD *this); // 0x001002A4

extern unsigned int CurrSlotBlocksShared__3PADii(struct PAD *this, int block1, int block2); // 0x001002E0

extern struct MCSLOT * GetCurrSlotPtr__3PAD(struct PAD *this); // 0x0010031C

extern int GetCurrSlot__3PAD(struct PAD *this); // 0x00100340

extern struct MCSLOT * GetDestSlotPtr__3PAD(struct PAD *this); // 0x00100354

extern unsigned int CardChanged__3PADi(struct PAD *this, int slot); // 0x0010037C

extern unsigned int CardInserted__3PADi(struct PAD *this, int slot); // 0x001003B0

extern void CycleSelectedSlot__3PAD(struct PAD *this); // 0x001003E4

extern unsigned int CardFormatted__3PADi(struct PAD *this, int slot); // 0x0010042C

extern int FormatCard__3PADi(struct PAD *this, int slot); // 0x00100460


#endif
