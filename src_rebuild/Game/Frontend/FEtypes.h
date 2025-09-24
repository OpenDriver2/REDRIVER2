#ifndef FETYPES_H
#define FETYPES_H

// Platform types
#include <types.h>

struct FE_CHARDATA
{
	u_char u;
	u_char v;
	u_char w;
	u_char h;
};

struct FE_FONT
{
	int NumFonts;
	FE_CHARDATA CharInfo[256];
};

struct PSXBUTTON
{
	short x, y, w, h;
	u_char l, r;		// left, right next item id
	u_char u, d;		// up, down next item id
	int userDrawFunctionNum;
	short s_x, s_y;
	int action, var;
	char Name[32];
};

#ifdef PSX
typedef struct PSXBUTTON FE_BUTTON;
#else
struct FE_BUTTON
{
	short x, y, w, h;
	u_char l, r;		// left, right next item id
	u_char u, d;		// up, down next item id
	u_char cR, cG, cB, justify;
	short s_x, s_y, s_w, s_h;
	short action, var;
	char Name[32];
};

static_assert(sizeof(FE_BUTTON) == sizeof(PSXBUTTON), "SIZE INVALID");
#endif

typedef struct PSXSCREEN
{
	u_char index;
	u_char numButtons;
	u_char userFunctionNum;
	FE_BUTTON buttons[8];
} FE_SCREEN;

typedef int(*screenFunc)(int bSetup);

#define FN_OK	0
#define FN_DONE	1

#define FE_NULLVAR -1
#define FE_MAKEVAR(code, value)		((code & 0xffff) << 8 | (value & 0xff))

#endif