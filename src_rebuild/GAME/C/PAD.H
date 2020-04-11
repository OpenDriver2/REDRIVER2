#ifndef PAD_H
#define PAD_H

#include "LIBPAD.H"

extern int pad_connected;
extern int numPadsConnected;
extern int gVibration;

extern void InitControllers(); // 0x0006B480

extern void CloseControllers(); // 0x0006BDF8

extern void ReadControllers(); // 0x0006B5A8

extern void SetPadVibration(int pad, unsigned char type); // 0x0006BE38

extern void StopPadVibration(int pad); // 0x0006BEB4

extern void StopDualShockMotors(); // 0x0006BEEC

extern void SetDuplicatePadData(char *buffer, int size); // 0x0006BEF4

extern void MapPad(int pad, struct PADRAW *pData); // 0x0006B6F0

extern void ClearPad(int pad); // 0x0006BF24

extern void HandleDualShock(); // 0x0006B8E0

extern void HandlePadVibration(int pad); // 0x0006BBC4


#endif
