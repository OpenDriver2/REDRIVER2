#ifndef FEMAIN_H
#define FEMAIN_H

struct PSXBUTTON
{
	short x;
	short y;
	short w;
	short h;
	unsigned char l;
	unsigned char r;
	unsigned char u;
	unsigned char d;
	int userDrawFunctionNum;
	short s_x;
	short s_y;
	int action;
	int var;
	char Name[32];
};

struct PSXSCREEN
{
	unsigned char index;
	unsigned char numButtons;
	unsigned char userFunctionNum;
	PSXBUTTON buttons[8];
};

extern int gInFrontend;
extern int bRedrawFrontend;

extern void DoFrontEnd(); // 0x001C296C
extern void SetFEDrawMode();
extern void LoadFrontendScreens();
extern void ReInitScreens();

#endif
