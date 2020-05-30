#ifndef PRES_H
#define PRES_H

extern short fonttpage;

extern void SetTextColour(unsigned char Red, unsigned char Green, unsigned char Blue); // 0x00074A10

extern int StringWidth(char *pString); // 0x00074A24

extern int OutputString(char *pString, int formatting, int x, int y, int xw, int r, int g, int b); // 0x00074AB0

extern void PrintStringRightAligned(char *pString, int x, int y); // 0x00074B8C

extern void PrintStringCentred(char *pString, short y); // 0x00074BD8

extern void LoadFont(char *buffer); // 0x00073CC8

extern void StoreClut2(unsigned long *pDest, int x, int y); // 0x00074C28

extern void SetCLUT16Flags(unsigned short clutID, unsigned short mask, char transparent); // 0x00074C64

extern int PrintString(char *string, int x, int y); // 0x00073EA0

extern short PrintDigit(int x, int y, char *string); // 0x00074140

extern int PrintStringFeature(char *string, int x, int y, int w, int h, int transparent); // 0x00074D34

extern void PrintStringBoxed(char *string, int ix, int iy); // 0x00074364

extern void InitButtonTextures(); // 0x00074E54

extern int PrintScaledString(int y, char *string, int scale); // 0x000745DC

extern char * GetNextWord(char *string, char *word); // 0x00074D54

extern void * DrawButton(unsigned char button, void *prim, int x, int y); // 0x00074858

extern void * SetFontTPage(void *prim); // 0x00074D94


#endif
