#ifndef SLOT_H
#define SLOT_H


extern MCSLOT * __6MCSLOTiiiiiiPc(MCSLOT *this, int port, int card, int iconX, int iconY, int clutX, int clutY, char *bufferPtr); // 0x000F523C

extern void card_start__6MCSLOT(MCSLOT *this); // 0x000F3644

extern void _._6MCSLOT(MCSLOT *this, int __in_chrg); // 0x000F52F0

extern void card_stop__6MCSLOT(MCSLOT *this); // 0x000F534C

extern int CheckCard__6MCSLOT(MCSLOT *this); // 0x000F5474

extern int card_event__6MCSLOTi(MCSLOT *this, int timeout); // 0x000F555C

extern void clear_event__6MCSLOT(MCSLOT *this); // 0x000F5610

extern unsigned int CardRemoved__6MCSLOT(MCSLOT *this); // 0x000F3828

extern unsigned int CardInserted__6MCSLOT(MCSLOT *this); // 0x000F3994

extern int FormatCard__6MCSLOT(MCSLOT *this); // 0x000F3B04

extern void ReadCardDir__6MCSLOT(MCSLOT *this); // 0x000F3C74

extern void invalidate_info__6MCSLOT(MCSLOT *this); // 0x000F5668

extern int ReadCardInfo__6MCSLOTPc(MCSLOT *this, char *managerFilename); // 0x000F3DB8

extern void download_icon__6MCSLOTR9BLOCKINFOiiiii(MCSLOT *this, BLOCKINFO *blockInfo, int iconX, int iconY, int clutX, int clutY, int icon); // 0x000F56FC

extern int CopyBlock__6MCSLOTi(MCSLOT *this, int block); // 0x000F5860

extern int ReadSlice__6MCSLOTiiP5SLICEP10FILEFORMAT(MCSLOT *this, int block, int slice, SLICE *slicePtr, FILEFORMAT *fileFormatPtr); // 0x000F41A0

extern int read_block__6MCSLOTiPcR9BLOCKINFO(MCSLOT *this, int block, char *bufferPtr, BLOCKINFO *blockInfo); // 0x000F43A0

extern int PasteBlock__6MCSLOT(MCSLOT *this); // 0x000F5918

extern int ReadHeader__6MCSLOTii(MCSLOT *this, int block, int slice); // 0x000F5968

extern int RenameCopyBlock__6MCSLOTP10FILEFORMAT(MCSLOT *this, FILEFORMAT *fileFormatPtr); // 0x000F5A60

extern int WriteSlice__6MCSLOTiiP5SLICEP10FILEFORMATPc(MCSLOT *this, int block, int slice, SLICE *slicePtr, FILEFORMAT *fileFormatPtr, char *bufferPtr); // 0x000F5B38

extern int write_block__6MCSLOTR9BLOCKINFOPc(MCSLOT *this, BLOCKINFO *blockInfo, char *bufferPtr); // 0x000F46B4

extern int CreateBlock__6MCSLOTP10FILEFORMATP5SLICE(MCSLOT *this, FILEFORMAT *fileFormatPtr, SLICE *slicePtr); // 0x000F49E8

extern int DeleteBlock__6MCSLOTi(MCSLOT *this, int block); // 0x000F502C

extern void SetPort__6MCSLOTii(MCSLOT *this, int port, int card); // 0x000F5C70

extern unsigned int BlocksShared__6MCSLOTii(MCSLOT *this, int block1, int block2); // 0x000F5D30

extern int GetBlockSize__6MCSLOTi(MCSLOT *this, int block); // 0x000F5DC8

extern unsigned int CardInfoRead__6MCSLOT(MCSLOT *this); // 0x000F5DFC

extern TIMSTRUCT * GetBlockIconPtr__6MCSLOTi(MCSLOT *this, int block); // 0x000F5E08

extern int GetNoUsedBlocks__6MCSLOT(MCSLOT *this); // 0x000F5E84

extern short * GetBlockTitlePtr__6MCSLOTi(MCSLOT *this, int block); // 0x000F5EA0

extern char * GetBlockFilenamePtr__6MCSLOTi(MCSLOT *this, int block); // 0x000F5EE4

extern int FilenameUsed__6MCSLOTPc(MCSLOT *this, char *filename); // 0x000F5F1C

extern int GetNumGremBlocks__6MCSLOTPc(MCSLOT *this, char *filename); // 0x000F5FBC

extern int InsertSliceIntoCopyBuffer__6MCSLOTiPccccT2(MCSLOT *this, int slice, char *sliceName, char icon0, int icon1, int icon2, char *dataPtr); // 0x000F6088

extern int ExtractSliceFromCopyBuffer__6MCSLOTiPc(MCSLOT *this, int slice, char *bufferPtr); // 0x000F61F0

extern char * GetSliceFilenamePtr__6MCSLOTii(MCSLOT *this, int block, int slice); // 0x000F628C

extern unsigned int SliceUsed__6MCSLOTii(MCSLOT *this, int block, int slice); // 0x000F633C

extern int GetNoUsedSlices__6MCSLOTi(MCSLOT *this, int block); // 0x000F63EC

extern int GetSliceIconRef__6MCSLOTiii(MCSLOT *this, int block, int slice, int ref); // 0x000F6448

extern int GetNoSlices__6MCSLOTi(MCSLOT *this, int block); // 0x000F64F4

extern unsigned int GremlinBlock__6MCSLOTi(MCSLOT *this, int block); // 0x000F6550

extern void Ascii2ShiftJis__FPsPc(short *dest, char *source); // 0x000F512C


#endif
