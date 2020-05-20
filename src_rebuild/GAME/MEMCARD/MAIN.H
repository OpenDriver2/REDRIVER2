#ifndef MCMAIN_H
#define MCMAIN_H


extern int CallMemoryCard(int flags, int ingame); // 0x000872F0

extern void libcman_SelectSound(); // 0x000878D4

extern void libcman_ConfirmSound(); // 0x00087908

extern void libcman_CancelSound(); // 0x0008793C

extern void libcman_ErrorSound(); // 0x00087970

extern void libcman_InitControllerLibrary(char *a, int b, char *c, int d); // 0x000879A4

extern void libcman_DeInitControllerLibrary(); // 0x000879F4

extern void libcman_ReadControllers(); // 0x00087A34

extern int DoMemoryCard(); // 0x00087A64

extern char * LoadMemCardOverlay(); // 0x00087CE4

extern void StorePermanentTPage(); // 0x00087D68

extern void RestorePermanentTPage(); // 0x00087DDC

extern void PutCorrectIcon(int which); // 0x00087E50


#endif
