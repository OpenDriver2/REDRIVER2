#ifndef CMAN_H
#define CMAN_H


extern int card_manager(int operation, int options, char *textBuffer, struct FILEFORMAT *fileFormatPtr, struct SLICE *slicePtr, char *backImageName, char *bufferPtr96K); // 0x00102710

extern int cardman__FiiPcP10FILEFORMATP5SLICET2T2(int operation, int options, char *textBuffer, struct FILEFORMAT *fileFormatPtr, struct SLICE *slicePtr, char *backImageName, char *bufferPtr96K); // 0x001005E0

extern void LoadBackground__FPcT0(char *filename, char *buffer); // 0x00102744

extern int EnterName__FP3PADP7DISPMANPc(struct PAD *pad, struct DISPMAN *disp, char *username); // 0x00102364


#endif
