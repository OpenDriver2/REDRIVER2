#include "inline_c.h"
#include "libgte.h"
#include "gtereg.h"
#include "../GTE/PsyX_GTE.H"

unsigned int MFC2(int reg)
{
	switch (reg) {
	case 1:
	case 3:
	case 5:
	case 8:
	case 9:
	case 10:
	case 11:
		gteRegs.CP2D.p[reg].d = (int)gteRegs.CP2D.p[reg].sw.l;
		break;

	case 7:
	case 16:
	case 17:
	case 18:
	case 19:
		gteRegs.CP2D.p[reg].d = (unsigned int)gteRegs.CP2D.p[reg].w.l;
		break;

	case 15:
		gteRegs.CP2D.p[reg].d = C2_SXY2;
		break;

	case 28:
	case 29:
		gteRegs.CP2D.p[reg].d = LIM(C2_IR1 >> 7, 0x1f, 0, 0) | (LIM(C2_IR2 >> 7, 0x1f, 0, 0) << 5) | (LIM(C2_IR3 >> 7, 0x1f, 0, 0) << 10);
		break;
	}

	return gteRegs.CP2D.p[reg].d;
}

int MFC2_S(int reg)
{
	// FIXME: Is that modifiers should be signed too?
	switch (reg) {
	case 1:
	case 3:
	case 5:
	case 8:
	case 9:
	case 10:
	case 11:
		gteRegs.CP2D.p[reg].d = (int)gteRegs.CP2D.p[reg].sw.l;
		break;

	case 7:
	case 16:
	case 17:
	case 18:
	case 19:
		gteRegs.CP2D.p[reg].d = (unsigned int)gteRegs.CP2D.p[reg].w.l;
		break;

	case 15:
		gteRegs.CP2D.p[reg].d = C2_SXY2;
		break;

	case 28:
	case 29:
		gteRegs.CP2D.p[reg].d = LIM(C2_IR1 >> 7, 0x1f, 0, 0) | (LIM(C2_IR2 >> 7, 0x1f, 0, 0) << 5) | (LIM(C2_IR3 >> 7, 0x1f, 0, 0) << 10);
		break;
	}

	return gteRegs.CP2D.p[reg].sd;
}

void MTC2(unsigned int value, int reg) {
	switch (reg) {
	case 15:
		C2_SXY0 = C2_SXY1;
		C2_SXY1 = C2_SXY2;
		C2_SXY2 = value;
		break;

	case 28:
		C2_IR1 = (value & 0x1f) << 7;
		C2_IR2 = (value & 0x3e0) << 2;
		C2_IR3 = (value & 0x7c00) >> 3;
		break;

	case 30:
		C2_LZCR = gte_leadingzerocount(value);
		break;

	case 31:
		return;
	}

	gteRegs.CP2D.p[reg].d = value;
}

void MTC2_S(int value, int reg) {
	switch (reg) {
	case 15:
		C2_SXY0 = C2_SXY1;
		C2_SXY1 = C2_SXY2;
		C2_SXY2 = value;
		break;

	case 28:
		C2_IR1 = (value & 0x1f) << 7;
		C2_IR2 = (value & 0x3e0) << 2;
		C2_IR3 = (value & 0x7c00) >> 3;
		break;

	case 30:
		C2_LZCR = gte_leadingzerocount(value);
		break;

	case 31:
		return;
	}

	gteRegs.CP2D.p[reg].sd = value;
}

void CTC2(unsigned int value, int reg) {
	switch (reg) {
	case 4:
	case 12:
	case 20:
	case 26:
	case 27:
	case 29:
	case 30:
		value = (int)(short)value;
		break;

	case 31:
		value = value & 0x7ffff000;
		if ((value & 0x7f87e000) != 0)
			value |= 0x80000000;
		break;
	}

	gteRegs.CP2C.p[reg].d = value;
}

void CTC2_S(int value, int reg) {
	switch (reg) {
	case 4:
	case 12:
	case 20:
	case 26:
	case 27:
	case 29:
	case 30:
		value = (int)(short)value;
		break;

	case 31:
		value = value & 0x7ffff000;
		if ((value & 0x7f87e000) != 0)
			value |= 0x80000000;
		break;
	}

	gteRegs.CP2C.p[reg].sd = value;
}

unsigned int CFC2(int reg)
{
	// TODO: correct functionality

	return gteRegs.CP2C.p[reg].d;
}

int CFC2_S(int reg)
{
	// TODO: correct functionality

	return gteRegs.CP2C.p[reg].sd;
}

void gte_SetGeomScreen(int h)
{
	CTC2(*(uint*)&h, 26);
}