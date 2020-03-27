#ifndef MGENERIC_H
#define MGENERIC_H


extern void StoreEndData(); // 0x00060740

extern void RestoreStartData(); // 0x000607E4

extern void StorePlayerPosition(struct SAVED_PLAYER_POS *data); // 0x0005FFAC

extern void RestorePlayerPosition(struct SAVED_PLAYER_POS *data); // 0x00060248

extern void StoreCarPosition(struct _TARGET *target, struct SAVED_CAR_POS *data); // 0x000603B0

extern void RestoreCarPosition(struct SAVED_CAR_POS *data); // 0x000604E4


#endif
