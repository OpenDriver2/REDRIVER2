#ifndef PRES_H
#define PRES_H

struct OUT_FONTINFO
{
	u_char x, y;
	char offx, offy;
	u_char width, height;
	u_short pad;
};

extern short fonttpage;

extern void InitButtonTextures(); // 0x00074E54

extern void LoadFont(char *buffer); // 0x00073CC8

// [A]
extern void SetTextScale(int scale, int saveLastScale);
extern void ResetTextScale();

extern void SetTextColour(u_char Red, u_char Green, u_char Blue); // 0x00074A10
extern int StringWidth(char *pString); // 0x00074A24

extern int OutputString(char *pString, int formatting, int x, int y, int xw, int r, int g, int b); // 0x00074AB0
extern int PrintStringRightAligned(char *pString, int x, int y); // 0x00074B8C
extern void PrintStringCentred(char *pString, short y); // 0x00074BD8
extern int PrintString(char *string, int x, int y); // 0x00073EA0
extern short PrintDigit(int x, int y, char *string); // 0x00074140
extern int PrintStringFeature(char *string, int x, int y, int w, int h, int transparent); // 0x00074D34
extern void PrintStringBoxed(char *string, int ix, int iy); // 0x00074364

extern void SetCLUT16Flags(ushort clutID, ushort mask, char transparent);

extern int PrintScaledString(int y, char *string, int scale); // 0x000745DC
extern char* GetNextWord(char *string, char *word); // 0x00074D54

extern void* DrawButton(u_char button, void *prim, int x, int y); // 0x00074858

extern void* SetFontTPage(void *prim); // 0x00074D94


#endif
