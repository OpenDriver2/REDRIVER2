#ifndef MGENERIC_H
#define MGENERIC_H


extern void StoreEndData(); // 0x00060740

extern void RestoreStartData(); // 0x000607E4

extern void StorePlayerPosition(SAVED_PLAYER_POS *data); // 0x0005FFAC

extern void RestorePlayerPosition(SAVED_PLAYER_POS *data); // 0x00060248

extern void StoreCarPosition(MS_TARGET *target, SAVED_CAR_POS *data); // 0x000603B0

extern void RestoreCarPosition(SAVED_CAR_POS *data); // 0x000604E4


#endif
